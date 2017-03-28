/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   10:39
	filename: 	C:\DD\PROJECTS\FIXIII\UGATE\ugate\ugate.cpp
	file path:	C:\DD\PROJECTS\FIXIII\UGATE\ugate
	file base:	ugate
	file ext:	cpp
	author:		CHENYH
	
	purpose:	这里采用 C 接口定义，以供UDL等调用
*********************************************************************/
#include "stdafx.h"
#ifdef _MSC_VER
#include <process.h>
#else
#include <pthread.h>
#endif
#include "FIXData.h"
#include "fixbase.h"
#include "XPack.h"
#include "cpack.h"
#include "bdefine.h"
#include "bupub.h"
#include "mypub.h"
#include "logfile.h"
#include "UGateManage.h"
#include "MsgDataList.h"
#include "ugate.h"

CUGateManage g_UGate;
ST_BUNIT g_BUnit;
CSvrLink *g_pSvrLink;  // 与业务调度中心的连接
CLogFile g_LogFile;   // 被移到SvrLink.cpp中，作为系统必要的属性
CXPack *g_pXPack;  //

//////////////////////////////////////////////////////////////////////////
typedef struct {
   char Exchange[8];  // 交易所代码，XSHG/XSHE etc.
   char Account[40];  // 交易编码 / 股东代码 模式匹配表达式
   char Symbol[40];   // 证券代码 模式匹配表达式
   char IMarket[8];   // 交易内部市场代码: 1,2,3,4 etc. 
} T_MARKET;  // 用于根据委托数据，获得IMarket或Exchange等信息的基础表结构

int g_nMarkets=-1;  // 市场列表中，分类的个数
T_MARKET *g_Markets=NULL;

struct T_INMSGTYPEFUNC 
{
   char MsgType[8];
   int reqtype;
};

T_INMSGTYPEFUNC g_InMsgFuncs[]=
{
   {"D",411701},
   {"8",411705},
   {"9",411705},
   {"F",411702},
   {"G",411702},
   {"H",411704},
   {"",411799}
};


// 函数名: UG_LoadMarkets
// 编程  : 陈永华 2011-9-15 23:13:06
// 描述  : 装载交易市场的内部代码匹配文件
// 返回  : int >0: 成功装载匹配项个数；
//             <=0: 装载失败  -1:文件打开异常; 0:没有准确定义清单;
//             -2: 申请内存失败；
// 参数  : const char *imarketfile
int UG_LoadMarkets(const char *imarketfile)
{
   FILE *fp;
   char buf[512];
   T_MARKET *pMarket;

   if (g_Markets!=NULL)
   {
      delete []g_Markets;
      g_Markets = NULL;
   }
   g_nMarkets = 0;
   fp = fopen(imarketfile,"rt");
   if (fp==NULL)
   {
      return(-1); // 表示文件打开异常
   }
   while (fgets(buf,sizeof(buf),fp))
   {
      ++g_nMarkets;
   }
   if (g_nMarkets<=0)
   {
      fclose(fp);
      return(0);
   }
   g_Markets = new T_MARKET[g_nMarkets];
   if (g_Markets==NULL)
   {
      fclose(fp);
      return(-2); // 表示申请空间异常
   }
   fseek(fp,0,SEEK_SET); // 从头开始重新读取
   g_nMarkets = 0;
   pMarket = g_Markets;
   while (fgets(buf,sizeof(buf),fp))
   {      
      /* 
      //EXCHANGE|ACCOUNT|SYMBOL|IMARKET|NOTE  -- 第一行是为了描述下面配置数据的含义而加的，程序将不会读取，请别改动!!!!!
      XSHG|!C*|*|1|上海A股
      XSHG|C*|*|3|上海B股
      XSHE|*|!2*,!4*,!36*|2|除了投票类的深圳A股
      XSHE|*|2*|4|除了投票类的深圳B股
      XSHE|*|40*,43*|5|深圳A股转让
      XSHE|*|42*|6|深圳B股转让
      XSHE|0*,40*,480*|36*|2|深圳A股投票
      XSHE|!0*,!40*,!480*|36*|4|深圳B股投票
      */
      mytrim(buf);
      if (buf[0]=='/')
         continue;
      if (GetSubString(buf,'|',0,pMarket->Exchange,sizeof(pMarket->Exchange),NULL)<=0)
         continue;
      mytrim(pMarket->Exchange);
      if (GetSubString(buf,'|',1,pMarket->Account,sizeof(pMarket->Account),NULL)<=0)
         continue;
      mytrim(pMarket->Account);
      if (GetSubString(buf,'|',2,pMarket->Symbol,sizeof(pMarket->Symbol),NULL)<=0)
         continue;
      mytrim(pMarket->Symbol);
      if (GetSubString(buf,'|',3,pMarket->IMarket,sizeof(pMarket->IMarket),NULL)<=0)
         continue;
      mytrim(pMarket->IMarket);
      if (strlen(pMarket->IMarket)>0)
      {
         ++pMarket;
         ++g_nMarkets;
      }
   }
   fclose(fp);
   return(g_nMarkets);
}


// 函数名: UG_GetIMarket
// 编程  : 陈永华 2011-9-15 23:18:45
// 描述  : 根据输入的各代码，找出内部市场代码；必须之前成功调用UG_LoadMarkets
// 返回  : const char *: NULL - 没有找到; 否则返回交易市场内部代码
// 参数  : const char *exchcode[IN]: KSFIX平台提供的交易所代码，如 "XSHE"
// 参数  : const char *account[IN]: 股东代码或投资者帐号，可以为空(则不一定准确)
// 参数  : const char *symbol[IN]: 证券代码或合约代码，可以为空(则不一定准确)
const char *UG_GetIMarket(const char *exchcode, const char *account, const char *symbol)
{
   int i;
   for (i=0;i<g_nMarkets;++i)
   {
      if (strcmp(g_Markets[i].Exchange,exchcode))
         continue;
      if (account!=NULL && account[0] 
         && CYHStringMatch(account,g_Markets[i].Account)==0)
         continue;
      if (symbol!=NULL && symbol[0]
         && CYHStringMatch(symbol,g_Markets[i].Symbol)==0)
         continue;
      return(g_Markets[i].IMarket);
   }
   return(NULL);
}


// 函数名: UG_GetExchange
// 编程  : 陈永华 2011-9-15 23:23:38
// 描述  : 根据输入的各代码，找出交易所代码；必须之前成功调用UG_LoadMarkets
// 返回  : const char *: NULL - 没有找到; 否则返回平台的交易所代码
// 参数  : const char *imarket[IN]: 交易系统内部的市场代码，如 "1"
// 参数  : const char *account[IN]: 股东代码或投资者帐号，可以为空(则不一定准确)
// 参数  : const char *symbol[IN]: 证券代码或合约代码，可以为空(则不一定准确)
const char *UG_GetExchange(const char *imarket, const char *account, const char *symbol)
{
   int i;
   for (i=0;i<g_nMarkets;++i)
   {
      if (strcmp(g_Markets[i].IMarket,imarket))
         continue;
      if (account!=NULL && account[0] 
         && CYHStringMatch(account,g_Markets[i].Account)==0)
         continue;
      if (symbol!=NULL && symbol[0]
         && CYHStringMatch(symbol,g_Markets[i].Symbol)==0)
         continue;
      return(g_Markets[i].Exchange);
   }
   return(NULL);
}



//////////////////////////////////////////////////////////////////////////
// !! 如下两个函数，专门在OUTMODE!=0的配置下，被UDL调用的，内部不用
// 函数名: UG_GetOutMsg
// 编程  : 陈永华 2011-9-16 22:30:51
// 描述  : UDL获取需要处理的OUT消息
// 返回  : int >0: 获取成功，并返回msgbuf中的消息长度；
//             0: 在等待outwaitms*100 (ms)时间内，没有需要OUT处理的消息；
//             -2: 非法的partnerid，本UGATE没有定义这个对手
// 参数  : const char *partnerid [IN]: 对手方的ID，即OUT消息中的 TargetCompID
// 参数  : int outwaitms [IN]: 等待消息的时间控制，实际等待的最长时间为 outwaitms*100 (ms)
// 参数  : char *msgbuf [OUT]: 存放得到的需要OUT处理的消息，缓存长度即为系统实际处理的最长，建议为MAXFIXMSGLEN
int UG_GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf)
{
   return(g_UGate.GetOutMsg(partnerid,outwaitms,msgbuf));
}

int UG_GetOutMsgSize(const char *partnerid)
{
   return(g_UGate.GetOutMsgSize(partnerid));
}



// 函数名: UG_HaveOutMsg
// 编程  : 陈永华 2011-9-16 22:30:54
// 描述  : 供UDL暂时将OUT消息，缓存到UGATE框架管理下的OUT消息队列中
// 返回  : int : 0/1 - 实际的plevel，即实际被存放的OUT消息队列优先级，0比1高
//             -2: 非法的partnerid，本UGATE没有定义这个对手
// 参数  : const char *parterid [IN]: 对手方的ID，即OUT消息中的 TargetCompID
// 参数  : const char *msg [IN]: 要缓存的fixmsg，以'\0'结束
// 参数  : int plevel [IN]: 即缓存队列优先级: 0或1, 0比1高, 即在UG_GetOutMsg的时候，先取0队列中的消息，然后取1队列中的消息
int UG_HaveOutMsg(const char *parterid, const char *msg, int plevel)
{
   return(g_UGate.HaveOutMsg(parterid,msg,plevel));
}

//////////////////////////////////////////////////////////////////////////


// 函数名: StartThread
// 编程  : 陈永华 2011-8-17 21:15:38
// 描述  : 用ThreadRun函数作为线程的入口，启动一个线程
// 返回  : int <0: 启动失败；否则成功
// 参数  : THREADENTRY ThreadRun [IN]: 线程入口函数
// 参数  : void *pArv [IN]: 启动的时候的带入的参数
int StartThread(THREADENTRY ThreadRun,void *pArv)
{
#ifdef _MSC_VER
   if (_beginthread(ThreadRun,0,pArv)==-1)
      return(-1);
   else
      return(1);
#else
   pthread_attr_t attr;
   pthread_t hThread;
   pthread_attr_init (&attr);
   pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
   if((pthread_create(&hThread,&attr,ThreadRun, pArv))==0)
      return(1);
   else
      return(-1);
#endif
}

// 函数名: UG_INIReadTString
// 编程  : 陈永华 2011-8-17 14:16:47
// 描述  : 以字符串方式读取配置文件中的指定配置项（去除了前后空字符串）
// 返回  : char * : 
// 参数  : const char *section [IN]: 配置段
// 参数  : const char *entry [IN]: 配置项
// 参数  : const char *defvalue [IN]: 缺省值
// 参数  : char *buffer [OUT]: 存放读取的配置值
// 参数  : int bufLen [IN]: buffer缓存的字节长度
char *UG_INIReadTString(const char *section, const char *entry, const char *defvalue,char *buffer,int bufLen)
{
   return(g_UGate.m_inifile.ReadTString(section,entry,defvalue,buffer,bufLen));
}


// 函数名: UG_INIReadInt
// 编程  : 陈永华 2011-8-17 21:13:26
// 描述  : 以整形方式读取配置文件中的指定的配置项
// 返回  : int :返回读取的整数值
// 参数  : const char *section [IN]: 配置段
// 参数  : const char *entry [IN]: 配置项
// 参数  : int defvalue [IN]: 缺省值
int UG_INIReadInt(const char *section, const char *entry,int defvalue)
{
   return(g_UGate.m_inifile.ReadInt(section,entry,defvalue));
}



int WriteAppInfo(int bccBaseFuncNo,int bccID)
{
   // 似乎没有啥可以做的，即没有需要为本BU组创建什么或初始化什么的，若有则可以加在这里。
   return(0);
}

int xProcess(TRUSERID *handle,char *rdata,int rdlen,int *iRetCode, char *szMsg)
{
   return(g_UGate.xProcess(handle,rdata,rdlen,iRetCode,szMsg));
}



// 函数名: UG_LoadIni
// 编程  : 陈永华 2011-8-17 14:33:40
// 描述  : 打开并装载UGate的主体配置参数
// 返回  : int >0: 成功，否则程序将会退出
// 参数  : const char *inifile [IN]: 配置文件
int UG_LoadIni(const char *inifile)
{
   g_pSvrLink = BUPubInitialize(NULL, NULL, WriteAppInfo, &g_LogFile, xProcess);
   g_pXPack = (CXPack *)GetDefaultXPack();
   return(g_UGate.LoadIni(inifile));
}


void UG_ToExit()
{
   g_UGate.ToExit();
}


// 函数名: UG_BCCLinkOK
// 编程  : 陈永华 2011-8-17 15:13:47
// 描述  : UGate与BCC连接是否正常，若不正常，则说明要求强制退出
// 返回  : int >0: 连接正常
int UG_BCCLinkOK()
{
   if (g_pSvrLink->LinkOK())
      return(1);
   else
      return(-1);
}


// 函数名: UG_GetLocalID
// 编程  : 陈永华 2011-8-20 15:56:58
// 描述  : 取本UGate的LocalID
// 返回  : const char *
const char *UG_GetLocalID()
{
   return(g_UGate.m_LocalID);
}


// Function name: UGGetChannelInfo
// Author       : CHENYH 2012/5/18 23:39:30
// Description  : 取UG内部的各个Channel的状态
// Return type  : int >=0: 获取成功；<0: 失败，错误的iChannel号
// Argument : int iChannel [IN]:从0开始的Channel编号
// Argument : char *info256 [OUT]: 以"<PartnerID>:<状态>:<负载>" 格式返回的信息
int UGGetChannelInfo(int iChannel, char *info256)
{
   info256[0]='\0';
   if (g_UGate.GetChannelInfo(iChannel,info256))
   {
      return(iChannel);
   }
   else
      return(-1);
}

void UGReloadKFXFile(int iChannel)
{
   g_UGate.ReloadKFXFile(iChannel);
}


// 函数名: UG_Init
// 编程  : 陈永华 2011-8-17 14:49:22
// 描述  : 初始化UGate的主体模块
// 返回  : int <0: 失败；否则成功
int UG_Init()
{
   int rtn;
   // 初始化与BCC连接：
   do 
   {
      rtn = g_pSvrLink->ToLink(&g_BUnit);
      if (rtn==1)
      {
         DEBUG_RUNTIME_MSGOUT("与业务调度中心(BCC)的连接成功!\n");
         break;
      }
      else if (rtn==-100)
      {
         DEBUG_RUNTIME_MSGOUT("估计业务调度中心(BCC)尚未正式启动，或者检查配置中的[SERVER]项参数\n");
         mysleep(g_BUnit.iHBInterval);
      }
      else
      {
         // 应该属于故障，或对方并不是BCC
         return(rtn);
      }
   } while (1);

   return (g_UGate.Initialize());  
}

int UG_Processing()
{
   return(g_UGate.Processing());
}

int UG_SendMessageIn(int reqtype, int pmode, const char *inmsg)
{
   return(g_UGate.HaveMessageIn(reqtype,pmode,inmsg));
}

// 函数名: UG_PickupTagValue
// 编程  : 陈永华 2011-8-22 17:07:51
// 描述  : 从fixmsg中快速获得tag的值，但只能取第一个
// 用于临时获取个别特殊tag，如: MsgType; BeginString; SenderCompID; TargetCompID等
// 返回  : const char * : 返回NULL表示没有找到指定的tag，或tvsize不足; 否则，取到了
// 参数  : const char *fixmsg [IN]: 被提取的FIX格式的消息串
// 参数  : int tag [IN]: 要找的指定TAG
// 参数  : char *tvalue [OUT]: 填写获取的tag的值
// 参数  : unsigned int tvsize [IN]: tvalue的缓存长度，不可以<=0的
const char *UG_PickupTagValue(const char *fixmsg, int tag, char *tvalue, unsigned int tvsize)
{
   char part[12];
   const char *pc;
   int plen = sprintf(part,"%d=",tag);
   tvalue[0]='\0';
   for (pc=fixmsg;*pc;++pc)
   {
      if (memcmp(pc,part,plen)==0)
      {
         // 找到了:
         int i;
         pc += plen;
         for (i=0;i<tvsize;++i)
         {
            switch (pc[i])
            {
            case 0x01:
            case 0:
               tvalue[i]='\0';
               return(tvalue);
            default:
               tvalue[i]=pc[i];
               break;
            }
         }
         return(NULL); // 超界了
      }
      while (*pc!=0x01 && *pc!='\0') ++pc;
      if (*pc=='\0')
      {
         break;
      }
   }
   return(NULL);
}


int FIXDataGetUGData(FIXDATAHANDLE h, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize)
{
   int ino;
   int n;
   int lXValue = 0;
   char tv453[4];
   memset(tv453,0,sizeof(tv453));
   memset(pUGData,0,sizeof(T_UGDATA));
   
   pUGData->lListSeqNo = -1;
   pUGData->lMsgSeqNum = -1;
   pUGData->lOrdRejReason = -1;
   pUGData->lCxlRejReason = -1;

   pUGData->dOrderQty = -1;
   pUGData->dCashOrderQty = -1;
   pUGData->dPrice = -1;
   pUGData->dAvgPx = -1;
   pUGData->dCumQty = -1;
   pUGData->dLeavesQty = -1;
   pUGData->dCommission = -1;
   pUGData->dLastPx = -1;
   pUGData->dLastQty = -1;

   n = FIXDataGetTagCount(h);
   for (ino=0;ino<n;++ino)
   {
      int tag;
      char tvalue[256];
      int vlen=sizeof(tvalue);
      FIXDataGetTagNo(h,ino,&tag,tvalue,&vlen);
      switch (tag)
      {
      case TAG_Account: // =1,		/*2.TAG1 股东代码*/
         STRNCPY(pUGData->sAccount,tvalue);
         break;
      case TAG_SenderCompID: // =49,		/*6.TAG49 发送方ID*/
         STRNCPY(pUGData->sSenderCompID,tvalue);
         break;
      case TAG_TargetCompID: // =56,		/*7.TAG56 接收方ID*/
         STRNCPY(pUGData->sTargetCompID,tvalue);
         break;
      case TAG_MsgSeqNum: // =34,		/*19.TAG34 FIX 消息序号*/
         pUGData->lMsgSeqNum = atol(tvalue);
         break;
      case TAG_CxlRejReason: // =102,		/*27.TAG102 撤单拒绝原因*/
         pUGData->lCxlRejReason = atol(tvalue);
         break;
      case TAG_OrdRejReason: // =103,		/*28.TAG103订单拒绝原因 */
         pUGData->lOrdRejReason = atol(tvalue);
         break;
      case TAG_Price: // =44,		/*32.TAG44  委托价格*/
         pUGData->dPrice = atof(tvalue);
         break;
      case TAG_LastPx: // =31,		/*33.TAG31 本次成交价格*/
         pUGData->dLastPx = atof(tvalue);
         break;
      case TAG_AvgPx: // =6,		/*34.TAG6 平均成交价格*/
         pUGData->dAvgPx = atof(tvalue);
         break;
      case TAG_Commission: // =12,		/*35.TAG12 期货的手续费*/
         pUGData->dCommission = atof(tvalue);
         break;
      case TAG_OrderQty: // =38,		/*37.TAG38 委托数量*/
         pUGData->dOrderQty = atof(tvalue);
         break;
      case TAG_CashOrderQty: // =152,		/*37.TAG152 委托金额*/
         pUGData->dCashOrderQty = atof(tvalue);
         break;
      case TAG_LastQty: // =32,		/*38.TAG32 本次成交数量*/
         pUGData->dLastQty = atof(tvalue);
         break;
      case TAG_LeavesQty: // =151,		/*39.TAG151 剩余未执行数量*/
         pUGData->dLeavesQty = atof(tvalue);
         break;
      case TAG_CumQty: // =14,		/*40.TAG14 累计成交量*/
         pUGData->dCumQty = atof(tvalue);
         break;
      case TAG_HandlInst: // =21,		/*68.TAG21 定单类型，目前填1*/
         STRNCPY(pUGData->sHandlInst,tvalue);
         break;
      case TAG_Side: // =54,		/*69.TAG54 客户类别2*/
         STRNCPY(pUGData->sSide,tvalue);
         break;
      case TAG_ExecTransType: // =20,		/*70.TAG20 交易类型标识符*/
         STRNCPY(pUGData->sExecTransType,tvalue);
         break;
      case TAG_TimeInForce: // =59,		/*72.TAG59  委托有效时效*/
         STRNCPY(pUGData->sTimeInForce,tvalue);
         break;
      case TAG_CxlRejResponseTo: // =434,		/*73.TAG434 撤单拒绝相应(1or2)*/
         STRNCPY(pUGData->sCxlRejResponseTo,tvalue);
         break;
      case TAG_ClOrdID: // =11,		/*89.TAG11 客户订单编号，唯一*/
         STRNCPY(pUGData->sClOrdID,tvalue);
         break;
      case TAG_OrigClOrdID: // =41,		/*90.TAG41 客户原始订单编号*/
         STRNCPY(pUGData->sOrigClOrdID,tvalue);
         break;
       case TAG_SvrTime: // =10101,		/*93.TAG10101:Svr时间 */
          pUGData->lSvrTime = atol(tvalue);
          break;
      case TAG_MsgType: // =35,		/*95.TAG35 消息类型*/
         STRNCPY(pUGData->sMsgType,tvalue);
         break;
      case TAG_Symbol: // =55,		/*97.TAG 55 交易品种(证券)代码*/
         STRNCPY(pUGData->sSymbol,tvalue);
         break;
      case TAG_SecurityID: // =48
         STRNCPY(pUGData->sSecurityID,tvalue);
         break;
      case TAG_IDSource: // =22
         STRNCPY(pUGData->sIDSource,tvalue);
         break;
      case TAG_ClientID: // =109,		/*99.TAG109 客户账户(约定)*/
         STRNCPY(pUGData->sClientID,tvalue);
         break;
      case TAG_TransactTime: // =60,		/*100.TAG60 UTC 格林威治时间*/
         STRNCPY(pUGData->sTransactTime,tvalue);
         break;
      case TAG_OrdStatus: // =39,		/*108.TAG39 订单状态*/
         STRNCPY(pUGData->sOrdStatus,tvalue);
         break;
      case TAG_ExecType: // =150,		/*109.TAG150, 执行类型*/
         STRNCPY(pUGData->sExecType,tvalue);
         break;
      case TAG_BeginString: // =8,		/*118.TAG8 消息头和协议版本号*/
         STRNCPY(pUGData->sBeginString,tvalue);
         break;
      case TAG_OnBehalfOfCompID: // =115,		/*119.TAG115 公司编号(Buy Side)*/
         STRNCPY(pUGData->sOnBehalfOfCompID,tvalue);
         break;
      case TAG_DeliverToCompID: // =128,		/*120.TAG128 公司编号(Sell Side)*/
         STRNCPY(pUGData->sDeliverToCompID,tvalue);
         break;
      case TAG_OnBehalfOfSubID: // =116,
         STRNCPY(pUGData->sOnBehalfOfSubID,tvalue);
         break;
      case TAG_DeliverToSubID: // =129,
         STRNCPY(pUGData->sDeliverToSubID,tvalue);
         break;
      case TAG_SenderSubID: // =50,
         STRNCPY(pUGData->sSenderSubID,tvalue);
         break;
      case TAG_TargetSubID: // =57,
         STRNCPY(pUGData->sTargetSubID,tvalue);
         break;
      case TAG_NonTradingOrdType: // =8526,		/*125.TAG8526 非交易订单类型 */
         STRNCPY(pUGData->sNonTradingOrdType,tvalue);
         break;
      case TAG_ExecID: // =17,		/*133.TAG17 执行编号*/
         STRNCPY(pUGData->sExecID,tvalue);
         break;
      case TAG_OrdType: // =40,		/*139.TAG40 订单类型*/
         STRNCPY(pUGData->sOrdType,tvalue);
         break;
      case TAG_OpenClose: // =77,		/*140.TAG77 开平标志（期货）*/
         STRNCPY(pUGData->sOpenClose,tvalue);
         break;
      case TAG_Currency: // =15,		/*141.TAG15 币种*/
         STRNCPY(pUGData->sCurrency,tvalue);
         break;
      case TAG_SecurityExchange: // =207,		/*142.TAG207 交易所代码, Session不同*/
         STRNCPY(pUGData->sSecurityExchange,tvalue);
         break;
      case TAG_OrderID: // =37,		/*153.TAG37 SellSide返回的订单序号*/
         STRNCPY(pUGData->sOrderID,tvalue);
         break;
      case TAG_TEXT: // =58		      /*176.TAG58 TEXT*/
         STRNCPY(pUGData->vsmess,tvalue);
         break;
      case TAG_PossResend: // 97
         pUGData->sPossResend=tvalue[0];  // 'Y' or 'N'
         break;
      case TAG_ExpireDate: // 交易本地时间的日期部分: Date of Local Market (vs. UTC) in YYYYMMDD format.  Valid values: YYYY = 0000-9999, MM = 01-12, DD = 01-31.
         STRNCPY(pUGData->sExpireDate,tvalue);   
         break;
      case TAG_ExpireTime: // 126  UTCTime YYYYMMDD-HH:MM:SS / YYYYMMDD-HH:MM:SS.sss
         //Strncpy(pUGData->sExpireDate,tvalue,9);
         STRNCPY(pUGData->sExpireTime,tvalue);
         break;
      case TAG_Password: // 554 String:
         STRNCPY(pUGData->sPassword,tvalue);
         break;
      case TAG_ExecInst: // 18 MultiString
         STRNCPY(pUGData->sExecInst,tvalue);
         break;
      case TAG_SecondaryExecID: // 527
         STRNCPY(pUGData->sSecondaryExecID,tvalue);
         break;
      case TAG_PartyRole:  // 453
         STRNCPY(tv453,tvalue);
         break;
      case TAG_PartyID: // 448 PartyID as ClientID when 453=3
         if (strcmp(tv453,"3")==0)
         {
            STRNCPY(pUGData->sClientID,tvalue);
            tv453[0]='\0';  // 后面就不会是了
         }
         break;
      default:
         if (addfixmsg!=NULL && 7+vlen+lXValue<afmsize-1)
         {
            sprintf(addfixmsg+lXValue,"%d=%s%c",
               tag,tvalue,C_SOH);
            lXValue += strlen(addfixmsg+lXValue);
         }
         break;         
      }
   }
#if 1
   // ExecID: nnnDmmm-XXXXXXXX:
   pUGData->lExecNoCnt = atoi(pUGData->sExecID);
   pUGData->lDays = 0;
   for (ino=0;pUGData->sExecID[ino]!='\0';ino++)
   {
      if (pUGData->sExecID[ino]=='D')
      {
         pUGData->lDays = atoi(pUGData->sExecID+ino+1);
         break;
      }
      if (pUGData->sExecID[ino]<'0'
         || pUGData->sExecID[ino]>'9')
         break; // 算了
   }
#else  
   // 原兼容格式: xxxxxxxNNNNNN
   if (strlen(pUGData->sExecID)<8)
      pUGData->lExecNoCnt = 0;
   else
      pUGData->lExecNoCnt = atoi(pUGData->sExecID+7);
#endif
   return(n);
}


// 函数名: UG_UGDataReturn
// 编程  : 陈永华 2011-9-17 14:54:09
// 描述  : 交换pUGData中的sSenderCompID、sTargetCompID和sOnBehalfOfCompID、sDeliverToCompID
// 返回  : void 
// 参数  : T_UGDATA *pUGData [IN/OUT]
void UG_UGDataReturn(T_UGDATA *pUGData)
{
   char fvalue[256];
   STRNCPY(fvalue,pUGData->sSenderCompID);
   STRNCPY(pUGData->sSenderCompID,pUGData->sTargetCompID);
   STRNCPY(pUGData->sTargetCompID,fvalue);
   
   STRNCPY(fvalue,pUGData->sOnBehalfOfCompID);
   STRNCPY(pUGData->sOnBehalfOfCompID,pUGData->sDeliverToCompID);
   STRNCPY(pUGData->sDeliverToCompID,fvalue);
   
   STRNCPY(fvalue,pUGData->sOnBehalfOfSubID);
   STRNCPY(pUGData->sOnBehalfOfSubID,pUGData->sDeliverToSubID);
   STRNCPY(pUGData->sDeliverToSubID,fvalue);

   STRNCPY(fvalue,pUGData->sSenderSubID);
   STRNCPY(pUGData->sSenderSubID,pUGData->sTargetSubID);
   STRNCPY(pUGData->sTargetSubID,fvalue);
}



// 函数名: UG_CancelRejectFIXMsg
// 编程  : 陈永华 2011-9-17 14:58:17
// 描述  : 将pUGData转换为CancelReject的FIX消息串
// 返回  : int :返回生成的串的长度
// 参数  : T_UGDATA *pUGData[IN]: 基本数据
// 参数  : char *fixmsg [OUT]: 生成的FIX消息串的缓存
// 参数  : unsigned int fmsize[IN]: fixmsg的缓存长度
int UG_CancelRejectFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize)
{
   int fmlen = 0;
   int rtn;
   
   rtn = FVString2FIXMsg(TAG_BeginString,pUGData->sBeginString,fixmsg,fmsize);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_MsgType,"9"/*pUGData->sMsgType*/,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderCompID,pUGData->sSenderCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetCompID,pUGData->sTargetCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfCompID,pUGData->sOnBehalfOfCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToCompID,pUGData->sDeliverToCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfSubID,pUGData->sOnBehalfOfSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToSubID,pUGData->sDeliverToSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderSubID,pUGData->sSenderSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetSubID,pUGData->sTargetSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrderID,pUGData->sOrderID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClOrdID,pUGData->sClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrigClOrdID,pUGData->sOrigClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdStatus,pUGData->sOrdStatus,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ListID,pUGData->sListID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVInt2FIXMsg(TAG_ListSeqNo,pUGData->lListSeqNo,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,pUGData->sAccount,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_CxlRejResponseTo,pUGData->sCxlRejResponseTo,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVInt2FIXMsg(TAG_CxlRejReason,pUGData->lCxlRejReason,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TEXT,pUGData->vsmess,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (strcmp(pUGData->sBeginString,"FIX.4.2")<=0)  // 20110309
   {
      rtn = FVString2FIXMsg(TAG_ClientID,pUGData->sClientID,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }   
         
   return(fmlen);
}


// 函数名: UG_ExecutionFIXMsg
// 编程  : 陈永华 2011-9-17 15:02:55
// 描述  : 将pUGData转换为Execution Report的FIX消息串
// 返回  : int :返回生成的串的长度
// 参数  : T_UGDATA *pUGData[IN]: 基本数据
// 参数  : char *fixmsg [OUT]: 生成的FIX消息串的缓存
// 参数  : unsigned int fmsize[IN]: fixmsg的缓存长度
int UG_ExecutionFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize)
{
   int fmlen = 0;
   int rtn;
   rtn = FVString2FIXMsg(TAG_BeginString,pUGData->sBeginString,fixmsg,fmsize);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_MsgType,"8"/*pUGData->sMsgType*/,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_SenderCompID,pUGData->sSenderCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetCompID,pUGData->sTargetCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfCompID,pUGData->sOnBehalfOfCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToCompID,pUGData->sDeliverToCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfSubID,pUGData->sOnBehalfOfSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToSubID,pUGData->sDeliverToSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderSubID,pUGData->sSenderSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetSubID,pUGData->sTargetSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,pUGData->sAccount,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ListID,pUGData->sListID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVInt2FIXMsg(TAG_ListSeqNo,pUGData->lListSeqNo,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVDouble2FIXMsg(TAG_Price,pUGData->dPrice,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (pUGData->sExecType[0]=='I' || pUGData->sExecTransType[0]=='3')
   {
      // 属于PossResend='Y' & ClOrdID duplicated, 则返回订单状态查询的情况:
   }
   else
   {
      rtn = FVDouble2FIXMsg(TAG_LastPx,pUGData->dLastPx,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
      
      rtn = FVQty2FIXMsg(TAG_LastQty,pUGData->dLastQty,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;      
   }

   rtn = FVDouble2FIXMsg(TAG_AvgPx,pUGData->dAvgPx,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVQty2FIXMsg(TAG_OrderQty,pUGData->dOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_CashOrderQty,pUGData->dCashOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVQty2FIXMsg(TAG_LeavesQty,pUGData->dLeavesQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_CumQty,pUGData->dCumQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
      
   rtn = FVString2FIXMsg(TAG_OrigClOrdID,pUGData->sOrigClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClOrdID,pUGData->sClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrderID,pUGData->sOrderID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExecID,pUGData->sExecID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_SecondaryExecID,pUGData->sSecondaryExecID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Symbol,pUGData->sSymbol,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityID,pUGData->sSecurityID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_IDSource,pUGData->sIDSource,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_Side,pUGData->sSide,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdStatus,pUGData->sOrdStatus,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (strcmp(pUGData->sBeginString,"FIX.4.2")<=0)
   {
      rtn = FVString2FIXMsg(TAG_ExecTransType,pUGData->sExecTransType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
      
      rtn = FVString2FIXMsg(TAG_ExecType,pUGData->sExecType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }
   else
   {
      if (strcmp(pUGData->sExecType,"1")==0
         ||strcmp(pUGData->sExecType,"2")==0)
         rtn = FVString2FIXMsg(TAG_ExecType,"F",fixmsg+fmlen,fmsize-fmlen);  // F = Trade (partial fill or fill)
      else
         rtn = FVString2FIXMsg(TAG_ExecType,pUGData->sExecType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;         
   }
   
   rtn = FVString2FIXMsg(TAG_SecurityExchange,pUGData->sSecurityExchange,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdType,pUGData->sOrdType,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_TimeInForce,pUGData->sTimeInForce,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_ExpireDate,pUGData->sExpireDate,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExpireTime ,pUGData->sExpireTime,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OpenClose ,pUGData->sOpenClose,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_HandlInst,pUGData->sHandlInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExecInst,pUGData->sExecInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;


   if (strcmp(pUGData->sBeginString,"FIX.4.2")<=0)  // 20110309
   {
      rtn = FVString2FIXMsg(TAG_ClientID,pUGData->sClientID,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }   

   rtn = FVString2FIXMsg(TAG_TEXT,pUGData->vsmess,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (pUGData->sOrdStatus[0]=='8')
   {
      // 即订单被拒绝的情况,可能就会有该字段
      rtn = FVInt2FIXMsg(TAG_OrdRejReason,pUGData->lOrdRejReason,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }

   rtn = FVString2FIXMsg(TAG_Currency,pUGData->sCurrency,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   

   return(fmlen);
}


// 函数名: UG_NewOrderSingle2FIXMsg
// 编程  : 陈永华 2011-9-17 15:14:13
// 描述  : 将pUGData转换为NewOrderSingle的FIX消息串
// 返回  : int :返回生成的串的长度
// 参数  : T_UGDATA *pUGData[IN]: 基本数据
// 参数  : char *fixmsg [OUT]: 生成的FIX消息串的缓存
// 参数  : unsigned int fmsize[IN]: fixmsg的缓存长度
int UG_NewOrderSingle2FIXMsg(T_UGDATA *pUGData, const char *addfixmsg, char *fixmsg, int fmsize)
{
   int fmlen = 0;
   int rtn;
   fixmsg[0]='\0';
   
   rtn = FVString2FIXMsg(TAG_BeginString,pUGData->sBeginString,fixmsg,fmsize);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_MsgType,"D",fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderCompID,pUGData->sSenderCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetCompID,pUGData->sTargetCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfCompID,pUGData->sOnBehalfOfCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToCompID,pUGData->sDeliverToCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfSubID,pUGData->sOnBehalfOfSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToSubID,pUGData->sDeliverToSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderSubID,pUGData->sSenderSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetSubID,pUGData->sTargetSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClOrdID,pUGData->sClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClientID,pUGData->sClientID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,pUGData->sAccount,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_HandlInst,pUGData->sHandlInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExecInst,pUGData->sExecInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Symbol,pUGData->sSymbol,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityID,pUGData->sSecurityID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_IDSource,pUGData->sIDSource,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityExchange,pUGData->sSecurityExchange,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Side,pUGData->sSide,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_OrderQty,pUGData->dOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_CashOrderQty,pUGData->dCashOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdType,pUGData->sOrdType,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVDouble2FIXMsg(TAG_Price,pUGData->dPrice,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Currency,pUGData->sCurrency,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   //long	lSvrTime;		/*93.TAG10101:Svr时间 */
   rtn = FVInt2FIXMsg(TAG_SvrTime,pUGData->lSvrTime,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   //char	sTimeInForce[4];		/*72.TAG59  委托有效时效*/
   rtn = FVString2FIXMsg(TAG_TimeInForce ,pUGData->sTimeInForce,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExpireDate,pUGData->sExpireDate,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExpireTime ,pUGData->sExpireTime,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVDouble2FIXMsg(TAG_Commission,pUGData->dCommission,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TEXT, pUGData->vsmess,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OpenClose ,pUGData->sOpenClose,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   if (pUGData->sOrdType[0]=='Z')
   {
      rtn = FVString2FIXMsg(TAG_NonTradingOrdType,pUGData->sNonTradingOrdType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }
   
   if (addfixmsg!=NULL)
   {
      rtn = strlen(addfixmsg);
      if (rtn>fmsize-fmlen)
         rtn = fmsize-fmlen;
      while (rtn>0 && addfixmsg[rtn-1]!=C_SOH)
         --rtn;
      if (rtn>0)
      {
         memcpy(fixmsg+fmlen,addfixmsg,rtn);
         fmlen += rtn;
         fixmsg[fmlen]='\0';
      }
   }
   return(fmlen);
}

// 函数名: UG_FIXMsg2UGData
// 编程  : 陈永华 2011-8-25 16:41:02
// 描述  : 提取fixmsg中的关键数据到pUGData中，不能提取的，则存放到addfixmsg中
// 返回  : int <0: 失败,fixmsg不是合规的消息串或系统异常；>0: 成功，返回共有多少个字段域
// 参数  : const char *fixmsg [IN]: 被提取的FIX消息串
// 参数  : int fmlen [IN]: fixmsg的串长
// 参数  : T_UGDATA *pUGData [OUT]: 要被填写的关键字段值
// 参数  : const char *addfixmsg [IN]: 没有能够被填写到pUGData中的非关键域的FIX附加串；NULL-不填 
// 参数  : unsigned int afmsize [IN]:  addfixmsg的缓存字节数
int UG_FIXMsg2UGData(const char *fixmsg, int fmlen, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize)
{
   int n;
   FIXDATAHANDLE h;
   h = FIXDataNew();
   if (h==NULL)
      return(-1);
   if (FIXDataSetData(h,fixmsg,fmlen)<0)
      n = -2;
   else
      n = FIXDataGetUGData(h,pUGData,addfixmsg,afmsize);
   FIXDataDelete(h);
   return(n);
}

// UDL主动导出通道状态变更信息，以更新平台监控
// statusinfo格式为: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>|...|<PartnerIDx>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>
int UDLHaveChannelStatusInfo(const char *statusinfo)
{
   return(g_UGate.HaveMessageIn(RT_UPSTATUS,0,statusinfo));
}

// 函数名: UDLHaveMessageIn
// 编程  : 陈永华 2011-8-19 23:42:29
// 描述  : UDL从对方收到信息，需要通过UG提交给FS平台
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *sPartnerID [IN]: 为该消息来自于那个Partner，也可以为NULL
// 参数  : const char *fixmsg [IN]: UDL提交给UG进行处理的FIX消息内容
int UDLHaveMessageIn(const char *PartnerID,const char *infixmsg)
{
   char msgtype[8];
   CFIXData fixdata;
   char fixmsg[MAXFIXDATALENGTH];
   if (fixdata.SetData(infixmsg,strlen(infixmsg)))
   {
      fixdata.UpdateTag(-1,TAG_TargetCompID,g_UGate.m_LocalID);  // TargetCompID updated with LocalID
      if (PartnerID!=NULL)
      {
         fixdata.UpdateTag(-1,TAG_SenderCompID,PartnerID);
      }
      int tvlen = sizeof(msgtype);
      if (fixdata.GetTag(TAG_MsgType,msgtype,tvlen)>=0)
      {
         fixdata.GetFIXData(fixmsg,sizeof(fixmsg));
         int i;
         for (i=0;g_InMsgFuncs[i].MsgType[0];++i)
         {
            if (strcmp(g_InMsgFuncs[i].MsgType,msgtype)==0)
            {
               return(g_UGate.HaveMessageIn(g_InMsgFuncs[i].reqtype,1,&fixdata));
            }
         }
         return(g_UGate.HaveMessageIn(RT_OTHERBUS,1,&fixdata));   
      }
   }
   g_LogFile.WriteLogEx(11556,"Invalid MsgIn:%s",infixmsg);
   return(-1);
}


int FIXTagComp(FIXDATAHANDLE h1, FIXDATAHANDLE h2, int tag)
{
   char tvalue1[256]={0};
   char tvalue2[256]={0};
   int tvlen;

   tvlen=sizeof(tvalue1); FIXDataGetTag(h1,tag,tvalue1,&tvlen);
   tvlen=sizeof(tvalue2); FIXDataGetTag(h2,tag,tvalue2,&tvlen);
   return(strcmp(tvalue1,tvalue2));
}


// 函数名: UG_FIXMsgKeyTagCmp
// 编程  : 陈永华 2011-8-26 17:35:24
// 描述  : 比较两个FIX消息中的最关键域，确认是否基本为相同的消息
// 返回  : int =0: 表示相同；
//       否则为不同的-- 1:MsgType; 2: NewOrderSingle; 3:OrderCancel/OrderModification; 
//                      4:Execution Report; 5:Order Cancel Reject; 6:New Order List
// 参数  : const char *fixmsg1 [IN]: 被比较的FIX消息1
// 参数  : const char *fixmsg2 [IN]: 被比较的FIX消息2
int UG_FIXMsgKeyTagCmp(const char *fixmsg1, const char *fixmsg2)
{
   FIXDATAHANDLE h1,h2;
   char msgtype[8];
   int tvlen;

#define FIXCMPRETURN(a) { FIXDataDelete(h1); FIXDataDelete(h2); return(a); }

   h1 = FIXDataNew(); h2 = FIXDataNew();
   FIXDataSetData(h1,fixmsg1,-1);
   FIXDataSetData(h2,fixmsg2,-1);
   if (FIXTagComp(h1,h2,TAG_MsgType))
      FIXCMPRETURN(1); // 这个都不同，那就不用比较了
   tvlen=sizeof(msgtype); FIXDataGetTag(h1,TAG_MsgType,msgtype,&tvlen);
   switch (msgtype[0])
   {
   case 'D': // New Order Single Request
      // 只要比较一下ClOrdID，应该就可以了
      if (FIXTagComp(h1,h2,TAG_ClOrdID))
         FIXCMPRETURN(2);
      break;
   case 'E': // E = New Order List
      if (FIXTagComp(h1,h2,TAG_ListID)         
         ||FIXTagComp(h1,h2,TAG_ClOrdID))
         FIXCMPRETURN(6);
      break;
   case 'F': // F = Order Cancel Request
   case 'G': // G= Order Cancel/Replace Request
      if (FIXTagComp(h1,h2,TAG_ClOrdID)
         ||FIXTagComp(h1,h2,TAG_OrigClOrdID))
         FIXCMPRETURN(3);
      break;
   case '8': // 8 = Execution Report
      //"8|11|17|39|150",       // Execution|ClOrdID|ExecID|OrdStatus|ExecType
      if (FIXTagComp(h1,h2,TAG_ClOrdID)
         ||FIXTagComp(h1,h2,TAG_ExecID)
         ||FIXTagComp(h1,h2,TAG_OrdStatus)
         ||FIXTagComp(h1,h2,TAG_ExecType))
         FIXCMPRETURN(4);
      break;
   case '9': // 9 = Order Cancel Reject
      //"9|11|41|39|434|102",   // CancelRej|ClOrdID|OrigClOrdID|OrdStatus|CxlRejResponseTo|CxlRejReason
      if (FIXTagComp(h1,h2,TAG_ClOrdID)
         ||FIXTagComp(h1,h2,TAG_OrigClOrdID)
         ||FIXTagComp(h1,h2,TAG_OrdStatus)
         ||FIXTagComp(h1,h2,TAG_CxlRejResponseTo)
         ||FIXTagComp(h1,h2,TAG_CxlRejReason))
         FIXCMPRETURN(5);
      break;
//    default:  // 当作相同还是不同呢？
//       FIXCMPRETURN(0); // 以相同，表示不用恢复的消息
   }
   FIXCMPRETURN(0); // 以相同，表示不用恢复的消息

#undef FIXCMPRETURN
}


// 函数名: UG_GetSSPendingOrders
// 编程  : 陈永华 2011-8-24 22:14:35
// 描述  : UG接口中，用于从FS平台获得还没有OrderID(即不知道是否已经发送给SellSide)的New Order Request / Order Cancel Request消息列表
// 返回  : int 返回得到的消息个数
// 参数  : const char *SSPartnerid [IN]: 即SellSide的PartnerID
// 参数  : L_MSGDATA &msglist [OUT]: 得到的未决的消息
int UG_GetSSPendingOrders(const char *SSPartnerid, L_MSGDATA &msglist)
{
   // RT_GETSSORD  411769   // IN: Get SSOrders from FS <flag>|<SellSide>...
   //  获取在UG_SSORDERS中SSORDERID为空的记录，以SSCLORDID递增序
   return(g_UGate.GetSSOrders(0,SSPartnerid,msglist));   
}


// 函数名: UG_GetBSExecRepts
// 编程  : 陈永华 2011-8-24 22:24:36
// 描述  : UG接口中，用于从FS平台获得所有保存的
// 返回  : int 返回得到的消息个数
// 参数  : const char *BSPartnerID [IN]: 即BuySide的PartnerID
// 参数  : L_MSGDATA &msglist [OUT]: 得到的消息
int UG_GetBSExecRepts(const char *BSPartnerID, L_MSGDATA &msglist)
{
   // 获得UG_EXEC中的该Partner的消息
   return(g_UGate.GetBSExecRepts(BSPartnerID,msglist));
}

// 函数名: UG_GetSSAllOrders
// 编程  : 陈永华 2011-9-30 23:02:08
// 描述  : UG接口中，用于从FS平台获得所有属于该SellSide的NewOrderRequest和OrderCancelRequest消息，
//       若已经有处理返回的，则会在消息中，带有OrderID的域，即 37=<OrderID>的域。
// 返回  : int 返回得到的消息个数
// 参数  : const char *sSSPartnerID [IN]: 即SellSide的PartnerID
// 参数  : L_MSGDATA &msglist [OUT]: 返回的属于本SellSide的SSOrders消息列表
int UG_GetSSAllOrders(const char *sSSPartnerID, L_MSGDATA &msglist)
{
   return(g_UGate.GetSSOrders(1,sSSPartnerID,msglist));
}


// 函数名: UG_RestoreFIXInMsg
// 编程  : 陈永华 2011-8-28 16:17:02
// 描述  : 以恢复的方式将FIX IN的消息提交给FS
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *fixmsg [IN]: IN FIX Message
int UG_RestoreFIXInMsg(const char *partnerid, const char *infixmsg)
{
   CFIXData fixdata;
   //char fixmsg[MAXFIXDATALENGTH];
   if (!fixdata.SetData(infixmsg,strlen(infixmsg)))
      return(-1); // 不正常的消息
   fixdata.UpdateTag(-1,TAG_TargetCompID,g_UGate.m_LocalID);  // TargetCompID updated with LocalID
   if (partnerid!=NULL)
      fixdata.UpdateTag(-1,TAG_SenderCompID,partnerid);
   //fixdata.GetFIXData(fixmsg,sizeof(fixmsg));
   // 以恢复的方式将FIX IN的消息提交给FS
   return(g_UGate.HaveMessageIn(RT_RESINMSG,1,&fixdata));
}

// 函数名: UG_CheckEOD
// 编程  : 陈永华 2011-8-27 21:42:47
// 描述  : 检查FS平台，返回是否需要做EOD处理，同时提醒FS是否需要DFD
// 返回  : int  0 - 表示不用做EOD；否则表示要做EOD处理
// 参数  : const char *partnerid [IN]: 对手方标识
// int UG_CheckEOD(const char *partnerid)
// {
//    // RT_CHECKEOD  411756   // IN: Check EOD of Partner <0-UG>|<UGID>|<PARTNERID>
//    return(g_UGate.CheckEOD(partnerid));     
// }



// 函数名: UG_GetPartners
// 编程  : 陈永华 2011-8-29 23:58:55
// 描述  : 取系统定义的属于本UG的各个Partner
// 返回  : const char * : 返回有效PartnerID序列: <PartnerID1>;<PartnerID2>;...;<PartnerIDn>
const char *UG_GetPartners()
{
   return(g_UGate.GetPartners());
}

void UG_SetOutMode(int outmode)
{
   g_UGate.ToSetOutMode(outmode);
}