// KSCTS.cpp: implementation of the CKSCTS class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "UDLInterface.h"
#include "fixbase.h"
#include "ugate.h"
#include "KSCTS.h"
#include "nbccclt.h"
#include "nbccsvr.h"
#include "UGDBFuncs.h"


CKSCTS g_KSCTS;
// 函数名: UDLInitialize
// 编程  : 陈永华 2011-8-17 14:42:01
// 描述  : 初始化UDL模块，但还不要建立具体的连接信息
//       内部包括各参数的配置信息
// 返回  : int <0: 表示初始化失败；否则，表示成功
int UDLInitialize()
{
   BCCSvrInit("fwd",600);
   UG_SetOutMode(1); // 采用调用UG_GetOutMsg处理
   return(g_KSCTS.Initialize());
}

// 函数名: UDLGetStatus
// 编程  : 陈永华 2011-8-21 10:15:51
// 描述  : 检查UDL模块内部状态，若内部异常，则返回<0
//         本函数内部必须通过检查内部变量，快速返回其状态，
//         不可通过大量处理等延时导出UDL内部的状态，
//         可以有所迟缓，一旦异常，UGate会被强制退出 (需要重新启动)
// 返回  : int <0 : UDL异常，程序必须重启或改配置后方能恢复；>=0:状态返回成功，继续跟踪
// 参数  : char *statusmsg [OUT]: 用如下格式返回各个Partner的状态：
//             <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerID2>:<status>:<load>:<errmsg>
//             status: 0 - 没有启动；1 - 已经正常启动
//             load: 负载值，即还没有被处理的OUT消息个数
// 参数  : unsigned int smsize [IN]: statusmsg的缓存字节数(大概近4000个字节) 
int UDLGetStatus(char *statusmsg,unsigned int smsize)
{
   return(g_KSCTS.GetStatus(statusmsg,smsize));
}

// 函数名: UDLExit
// 编程  : 陈永华 2011-8-18 21:03:38
// 描述  : UGate要求UDL退出
// 返回  : int <0: 表示初始化失败；否则，表示成功
int UDLExit()
{
   g_KSCTS.Exit();
   BCCSvrExit();
   return(0);
}

// 函数名: UDLOpen
// 编程  : 陈永华 2011-8-19 23:20:46
// 描述  : 正式启动本会话(Session)，与对方系统对接
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
// 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
int UDLOpen(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   int rtn;
   rtn = g_KSCTS.Open(sLocalID,sPartnerID,emsg);
   if (rtn<0)
      g_KSCTS.Close();
   return(rtn);
}


// 函数名: UDLClose
// 编程  : 陈永华 2011-8-19 23:34:35
// 描述  : 关闭与对方的连接，进入Close状态
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
// 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
int UDLClose(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   g_KSCTS.Close();
   return(0);
}


// 函数名: UDLEndOfDay
// 编程  : 陈永华 2011-8-19 23:35:58
// 描述  : 对本连接做Reset处理，清除之前处理缓存的数据，并进入关闭状态
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
// 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
int UDLEndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   return(g_KSCTS.EndOfDay(sLocalID,sPartnerID,emsg));
}

// 函数名: UDLOnMessageOut
// 编程  : 陈永华 2011-8-18 20:39:40
// 描述  : UG收到来自FS平台的FIX消息，需要通过UDL处理，发送给对手方
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *fixmsg [IN]: 业务类的 FIX格式的Message (参考协议)
// 参数  : char *eMsg [OUT]: 当失败的时候(非协议类失败)，返回错误信息(<80字节)
int UDLOnMessageOut(const char *fixmsg, char *eMsg)
{
   // 由于本模式采用OUTMODE=1，因此UGATE框架应该不调用本函数:
   SQLDebugLog(80000,"Error @ UGate Framework for OUTMODE!");
   strcpy(eMsg,"UGATE Error for OUTMODE!");
   return(-1);
}

//////////////////////////////////////////////////////////////////////////
void HaveDBRealDone(T_REAL_DONE *pRealDone)
{
   g_KSCTS.HaveARealDone(pRealDone);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ST_SQLDB g_SQLDB;


CKSCTS::CKSCTS()
{
   memset(m_PartnerID,0,sizeof(m_PartnerID));
   memset(m_LocalID,0,sizeof(m_LocalID));
   m_bRunning = false;
   m_pXComp = NULL;
   m_LastDoneID = -1;
   m_LastOutTime = m_LastDoneTime = time(NULL);  // 第一次是没有用的
   m_DoneCnt = 0;
   m_OutCnt = 0;
}

CKSCTS::~CKSCTS()
{

}


#define IMARKETFILE "imarket.txt"
int CKSCTS::Initialize()
{
   char tmp[256];
   int rtn,i;
   char *pc;

   m_bRunning = false;
   m_Status = FS_DISABLE; // 还没有正式启动
   STRNCPY(m_LocalID,UG_GetLocalID());
   STRNCPY(m_PartnerID,UG_GetPartners());
   pc = strstr(m_PartnerID,";");
   if (pc!=NULL)
      *pc = '\0'; // 就只能是第一个

   UG_INIReadTString("KSCTS","XPACK","cpack.dat",m_XPackFile,sizeof(m_XPackFile));

   // 先对数据库做连接初始化，这是本程序必须的。
   UG_INIReadTString("KSCTS", "DBNAME", "ksdbs", g_SQLDB.szServer, sizeof(g_SQLDB.szServer));
   UG_INIReadTString("KSCTS", "DBSVR", "127.0.0.1", g_SQLDB.szDatabase, sizeof(g_SQLDB.szDatabase));
   UG_INIReadTString("KSCTS", "LOGINUSER", "", g_SQLDB.szLogin, sizeof(g_SQLDB.szLogin));
   UG_INIReadTString("KSCTS", "PASSWORD", "", g_SQLDB.szPassword, sizeof(g_SQLDB.szPassword));

   UG_INIReadTString("KSCTS","KSCTSSVR","0:5800",tmp,sizeof(tmp));
   pc = strstr(tmp,":");
   if (pc==NULL)
   {
      SQLDebugLog(10000,"Invalid [KSCTS] KSCTSSVR=%s defined",tmp);
      return(-1);
   }
   *pc='\0'; ++pc;
   m_SvrDestNo = atoi(tmp);
   m_SvrFuncNo = atoi(pc);

   m_ReDoneIDCnt = UG_INIReadInt("KSCTS","CJXHRY",100);

   m_CJSJRY = UG_INIReadInt("KSCTS","CJSJRY",500);

   SQLInitialize(&g_SQLDB);
   if (SQLConnectToServer()!=0)
      return(-100); // 不行呀！

   // 初始化与交易系统对接的通信平台:
   rtn = m_DRouters.Initialize(tmp);
   if (rtn<0)
   {
      SQLDebugLog(10001,"Fail to load DRTP Info(%d):%s",rtn,tmp);
      return(rtn-100);
   }

   m_bch = BCNewHandle(GetXPackFile());
   if (m_bch==NULL)
   {
      SQLDebugLog(10005,"Fail to load XPACKFile(%s)",GetXPackFile());
      return(-500);
   }

   // 装载交易所代码和内部市场代码的对照表
   rtn = UG_LoadMarkets(IMARKETFILE);
   if (rtn<=0)
   {
      SQLDebugLog(10002,"Fail to load IMARKET(%d):%s",rtn,IMARKETFILE);
      return(rtn-200);
   }

   // 初始化成交回报线程
   rtn = m_CJThread.Initialize(tmp);
   if (rtn<0)
   {
      SQLDebugLog(10003,"Fail to Init CJTHREAD(%d):%s",rtn,tmp);
      return(rtn-300);
   }


   // 读取其他配置:
   m_OThreadCnt = UG_INIReadInt("KSCTS","OUTTHREADS",1);
   if (m_OThreadCnt>MAXOUTTHREADS)
      m_OThreadCnt = MAXOUTTHREADS;
   for (i=0;i<m_OThreadCnt;++i)
   {
      if ((rtn=m_OThreads[i].Initialize(i,tmp))<0)
      {
         SQLDebugLog(10004,"Fail to Init OUTTHREAD(%d):%s",rtn,tmp);
         return(rtn-400);
      }
   }

   m_IThreadCnt = UG_INIReadInt("KSCTS","INTHREADS",1);
   if (m_IThreadCnt>MAXINTHREADS)
      m_IThreadCnt = MAXINTHREADS;
   for (i=0;i<m_IThreadCnt;++i)
      m_IThreads[i].m_ID = i;

   UG_INIReadTString("KSCTS","WTYYB","088",m_WTYYB,sizeof(m_WTYYB));
   UG_INIReadTString("KSCTS","WTFSx","FIX",m_WTFSx,sizeof(m_WTFSx));
   UG_INIReadTString("KSCTS","WTFSi","f",m_WTFSi,sizeof(m_WTFSi));

   LoadHWGSDM();

   return(0);
}

void CKSCTS::Exit()
{
   SQLDisconnect1();
}

int CKSCTS::Open(const char *sLocalID, const char *sPartnerID, char *emsg)
{
   int i;

   if (sLocalID!=NULL && strcmp(m_LocalID,sLocalID))
   {
      sprintf(emsg,"Error LOCALID(%s!=%s) defined!",m_LocalID,sLocalID);
      return(-1);
   }
   if (strcmp(m_PartnerID,sPartnerID))
   {
      sprintf(emsg,"Error PARTNERID(%s!=%s) defined!",m_PartnerID,sPartnerID);
      return(-2);
   }

   // 2012/12/25 22:30:30 为了在数据库重启的时候，能恢复连接，特别做了这个处理
   SQLDisconnect1();
   if (SQLConnectToServer()!=0)
   {
      sprintf(emsg,"Fail to Connect Server(%s:%s)!",g_SQLDB.szDatabase,g_SQLDB.szServer);
      return(-100); // 不行呀！
   }
   //////////////////////////////////////////////////////////////////////////

   // 做重置和恢复处理:
   m_Status = FS_CONNECTING;  // 处于正在连接状态
   // statusinfo格式为: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
   sprintf(emsg,"%s|%s:1:0:In PreOpen",m_LocalID,m_PartnerID); 
   UDLHaveChannelStatusInfo(emsg);
   if (!PreOpen(emsg))
   {
      m_Status = FS_DISABLE;
      return(-3);
   }

   m_bRunning = true;  // 表示要各个线程正常处理运行中

   if (!m_DRouters.ToStartCJRecv(emsg))
   {
      return(-4);
   }

   if (!m_CJThread.ToStartCJProcess(emsg))
   {
      return(-5);
   }

   for (i=0;i<m_OThreadCnt;++i)
   {
      if (!m_OThreads[i].ToStartOutProcess(emsg))
         return(-6);
   }

   m_Status = FS_OPEN;  // 进入Open状态
   return(0);  // Start OK!
}

const char * CKSCTS::GetXPackFile()
{
   return(m_XPackFile);
}

bool CKSCTS::IsRunning()
{
   return(m_bRunning);
}

void CKSCTS::Close()
{
   int i;
   m_Status = FS_CLOSE;
   m_bRunning = false;

   for (i=0;i<m_OThreadCnt;++i)
   {
      m_OThreads[i].ToStopOutProcess();
   }
   m_CJThread.ToStopCJProcess();
   m_DRouters.ToStopCJRecv();
}

int CKSCTS::LoadHWGSDM()
{
   char tmp[512];
   char *pv;
   int i;
   FILE *fp;
   m_XCompCnt = 0;
   if (m_pXComp!=NULL)
   {
      delete []m_pXComp;
      m_pXComp = NULL;
   }
   fp = fopen("hwgsdm.txt","rt");
   if (fp==NULL)
      return(0);
   i = 0;
   while (fgets(tmp,sizeof(tmp),fp))
      ++i;
   if (i<=0)
   {
      fclose(fp);
      return(0);
   }
   m_pXComp = new T_HWGSDM[i];
   fseek(fp,0,SEEK_SET);
   i = 0;
   while (fgets(tmp,sizeof(tmp),fp))
   {
      mytrim(tmp);
      if (tmp[0]=='/')
         continue;
      pv = strstr(tmp,"|");
      if (pv==NULL)
         continue;
      *pv = '\0'; ++pv;
      mytrim(tmp); mytrim(pv);
      if (tmp[0] && pv[0])
      {
         STRNCPY(m_pXComp[i].onbehalf,tmp);
         STRNCPY(m_pXComp[i].hwgsdm,pv);
         ++i;
      }
   }
   m_XCompCnt = i;
   fclose(fp);
   return(i);
}



char * CKSCTS::GetHWGSDM(const char *onbehalf)
{
   int i;
   for (i=0;i<m_XCompCnt;++i)
   {
      if (strcmp(m_pXComp[i].onbehalf,onbehalf)==0)
         return(m_pXComp[i].hwgsdm);
   }
   return(NULL);
}

int CKSCTS::InsertFIXEntrust(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_DBMutex);
   return(DBInsertFIXEntrust(pUGData));
}


// 函数名: CKSCTS::GetDBEntrustStatus
// 编程  : 陈永华 2011-9-18 10:39:55
// 描述  : 从KSCTS的ENTRUST表中查指定委托的数据，当返回为1的时候:
//          sSellSide = ENTRUST.REPORT_SEAT;
//          sOrderID = ENTRUST.RPT_CONTRACT;
//          sOrdStatus = ENTRUST.ENTRUST_STATUS;
//          sExecInst = ENTRUST.EXCHANGE_ERR_CODE
// 返回  : int -1: 失败，数据库异常(也有可能有多条); 
//             0: 没有找到指定委托记录；
//             1: 找到，并对pUGData中的上述数据进行修改
// 参数  : T_UGDATA *pUGData[IN/OUT]: 用pUGData->sClOrdID作为委托合同号来指定委托记录；
//                   当返回1的时候，更改上述几个字段，但采用KSCTS的表示方式
int CKSCTS::GetDBEntrustStatus(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_DBMutex);
   return(DBGetEntrustStatus(m_WTYYB,m_WTFSi,pUGData));
}


// 函数名: CKSCTS::CallSvr
// 编程  : 陈永华 2011-9-18 11:26:31
// 描述  : 向KSCTS服务器调用功能
// 返回  : int <0: 调用失败, 参见errMsg的输出信息；-103:属于接收应答超时
//             >=0: 调用成功，检查bch中的返回信息
// 参数  : BCHANDLE bch [IN/OUT]: 调用和返回用的数据缓存句柄
// 参数  : char *errMsg [OUT]: 在返回失败的时候，填写具体的错误信息
int CKSCTS::CallSvr(BCHANDLE bch, char *errMsg)
{
   return(m_DRouters.CallSvr(bch,m_SvrDestNo,m_SvrFuncNo,errMsg));
}

int CKSCTS::FetchCJHBRecords()
{
   CPMUTEX pMutex(&m_DBMutex);
   int dsec = time(NULL)-m_LastDoneTime+2;  // 上次和本次的时间间隔(秒)+2秒
   m_LastDoneTime = time(NULL);
   return(DBFetchRDRecords(m_WTYYB,m_WTFSi,&m_LastDoneID,m_ReDoneIDCnt,dsec));
}


void CKSCTS::HaveARealDone(T_REAL_DONE *pRealDone)
{
   T_UGDATA ugdata;
   char fixmsg[MAXFIXMSGLEN];
   int fmlen;
   if (bDoneProcessed(pRealDone->lDONE_ID))
      return;  // 先过滤已经处理过的成交或撤单

   mytrim(pRealDone->sCONTRACT_NO);
   mytrim(pRealDone->sSEC_CODE);

   memset(&ugdata,0,sizeof(ugdata));
   STRNCPY(ugdata.sSenderCompID,m_PartnerID); 
   STRNCPY(ugdata.sOrderID,pRealDone->sCONTRACT_NO);
   strcpy(ugdata.sMsgType,"8");
   STRNCPY(ugdata.sSymbol,pRealDone->sSEC_CODE);
   STRNCPY(ugdata.sOrigClOrdID,pRealDone->sCONTRACT_NO);
   STRNCPY(ugdata.sOrderID,pRealDone->sCONTRACT_NO);  // 这些都是约定好了的，参考OUTThread中的相应处理

   //PUTLINE(ugdata.sOrigClOrdID);

   switch (pRealDone->sBS[1])
   {
   case '1':
      strcpy(ugdata.sSide,"1"); // buy
      break;
   case '2':
      strcpy(ugdata.sSide,"2");  // sell
      break;
   case 'M':    // D = Subscribe (e.g. ETF)[申购]
      strcpy(ugdata.sSide,"D");
      break;
   case 'N':    // E = Redeem (e.g. ETF)[赎回]
      strcpy(ugdata.sSide,"E");
      break;
   default:
      ugdata.sSide[0]=pRealDone->sBS[1];
      break;
   }

   switch (pRealDone->sBS[0])
   {
   case '0': // 属于成交
      //PUTLINE("Filled");
      strcpy(ugdata.sExecType,"F"); // Trade (filled)
      STRNCPY(ugdata.sClOrdID,pRealDone->sCONTRACT_NO);
      sprintf(fixmsg,"%.0lf-%s",
         pRealDone->dDONE_NO,pRealDone->sCONTRACT_NO); // 就用它来做其EXECID了
      STRNCPY(ugdata.sExecID,fixmsg);
      ugdata.dLastPx = pRealDone->dDONE_PRICE;
      ugdata.dLastQty = pRealDone->lDONE_VOL;
      // 其他数据，FS中不怎么关心了
      break;
   case '1': // 属于撤单
      //PUTLINE("Cancelled");
      strcpy(ugdata.sExecType,"4"); // Canceled
      GetCancelClOrdID(&ugdata);
      sprintf(ugdata.sExecID,"CXL-%s",pRealDone->sCONTRACT_NO);
      // 撤单成功数量:
      if (pRealDone->lDONE_VOL<0)
         pRealDone->lDONE_VOL = -pRealDone->lDONE_VOL;
      ugdata.dOrderQty = pRealDone->lDONE_VOL;
      ugdata.dCumQty = 0;
      // 用ugdata.dOrderQty-ugdata.dCumQty的差值，来表示撤单成功的数量
      //////////////////////////////////////////////////////////////////////////
      break;
   default:
      SQLDebugLog(20001,"Unknown BusinessCode:%s of DONEID(%ld)",
         pRealDone->sBS,pRealDone->lDONE_ID);
      return;
   }
   fmlen = UG_ExecutionFIXMsg(&ugdata,fixmsg,sizeof(fixmsg));
   //PUTLINE(fixmsg);
   SendToFIXSvr(fixmsg);
   AddDoneProcessed(pRealDone->lDONE_ID);
   if (strcmp(ugdata.sExecType,"4")==0)
      ClOrderCxlDone(&ugdata); // 表示本撤单已经closed
   ++m_DoneCnt;
}

bool CKSCTS::BindCJRecv(BSHANDLE bsh)
{
   return(m_DRouters.BindBSCJRecv(bsh));
}

// 根据当前撤单列表中的撤单检查数据库中的ENTRUST
int CKSCTS::CheckCxlReject()
{
   CPMUTEX pMutex(&m_CCMutex);
   M_CXLCLORDID::iterator it,nt;
   int n=0;
   for (it=m_Cancels.begin();it!=m_Cancels.end();)
   {
      nt = it++;
//      PUTLINE("In CheckCxlReject");
      if (CheckACancelReject(nt->first.c_str(),nt->second.c_str()))
      {
         m_Cancels.erase(nt); // 
         ++n;
      }
   }
   m_DoneCnt += n;
   return(n);
}

// 用执行序号检查本成交和撤单是否已经处理过了
bool CKSCTS::bDoneProcessed(long done_id)
{
   if (done_id>=0)
   {
      return (m_DoneIDSet.find(done_id)!=m_DoneIDSet.end());
   }
   return(false); // 否则，就按照需要处理的来完成 2012-6-6 22:06:57
}

// 添加已经处理了的成交和撤单执行序号(仅仅CJ线程间接调用)
void CKSCTS::AddDoneProcessed(long done_id)
{
   if (done_id>=0)
   {
      m_DoneIDSet.insert(done_id);
      if (m_DoneIDSet.size()>m_ReDoneIDCnt)
         m_DoneIDSet.erase(m_DoneIDSet.begin());  // 将第一个删除了
   }
}

// 由pUGData->sOrigClOrdID (即pRealDone->sCONTRACT_NO)，检查撤单表，获得撤单请求中的pUGData->sClOrdID
void CKSCTS::GetCancelClOrdID(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_CCMutex);
   M_CXLCLORDID::iterator it;
   it = m_Cancels.find(string(pUGData->sOrigClOrdID));
   if (it!=m_Cancels.end())
   {
      STRNCPY(pUGData->sClOrdID,it->second.c_str());
   }
   else
   {
      STRNCPY(pUGData->sClOrdID,pUGData->sOrigClOrdID);
   }
}

// 在撤单内存表中加入一笔撤单的订单编号对，
// 其中sOrigClOrdID为原订单的ClOrdID，也就是委托的合同号;
// 而sClOrdID为对sOrigClOrdID这笔委托单的撤单请求的ClOrdID。
void CKSCTS::RegisterCancelOrder(const char *sOrigClOrdID, const char *sClOrdID)
{
   CPMUTEX pMutex(&m_CCMutex);
   m_Cancels.insert(make_pair(string(sOrigClOrdID),string(sClOrdID)));
}

// 将对pUGData->sOrigClOrdID的撤单已经完成（或被拒绝了）
// 实际就是将撤单内存表中的记录删除了（让出空间来）
void CKSCTS::ClOrderCxlDone(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_CCMutex);
   m_Cancels.erase(string(pUGData->sOrigClOrdID));
}



// 函数名: CKSCTS::CheckACancelReject
// 编程  : 陈永华 2011-9-21 0:08:38
// 描述  : 通过检查KS.ENTRUST中的撤单记录，以发现是否被拒绝了
// 返回  : bool : true-本撤单被拒绝了；false-本撤单还没有被拒绝
// 参数  : const char *origclordid [IN]: 原始订单号OrigClOrdID, 同时也是原始的委托合同号: CONTRACT_NO
// 参数  : const char *clordid [IN]: 对应的撤单的ClOrdID
bool CKSCTS::CheckACancelReject(const char *origclordid, const char *clordid)
{
   T_UGDATA ugdata;
   char fixmsg[MAXFIXMSGLEN];
   int rtn;

   memset(&ugdata,0,sizeof(ugdata));
   STRNCPY(ugdata.sOrigClOrdID,origclordid);
   STRNCPY(ugdata.sClOrdID,clordid);
   strcpy(ugdata.sMsgType,"F");  // 只是查撤单的那笔记录
   if ((rtn=GetDBEntrustStatus(&ugdata))>0)
   {
      if (ugdata.sOrdStatus[0]!='9')
      {
         // 不是被交易所拒绝的废单，那么就由FetchCJHBRecords那里处理了
         return(false);
      }
      // OK:  '9' - 废单
      ugdata.lCxlRejReason = 2; // 2 = Broker / Exchange Option
      sprintf(ugdata.vsmess,"ErrNo=%s:Rejected by OMS/Exchange",ugdata.sExecInst);
   }
   else
   {
      // 没有记录，怎么可能呢？
      // 先报警一下吧
      SQLDebugLog(20002,"PE:Not found KS.ENTRUST(%s) for Cancel:%d!",origclordid,rtn);
      ugdata.lCxlRejReason = 1; // 1 = Unknown order
      strcpy(ugdata.vsmess,"PE:Not found order");
   }

   STRNCPY(ugdata.sSenderCompID,m_PartnerID); // 这样后面就不用带m_PartnerID了
   strcpy(ugdata.sCxlRejResponseTo,"1");
   rtn = UG_CancelRejectFIXMsg(&ugdata,fixmsg,sizeof(fixmsg));

   SendToFIXSvr(fixmsg);
   return(true);
}

bool CKSCTS::PreOpen(char *emsg)
{
   // 1. 先检查CTS服务器是否服务正常
   if (!CheckKSCTSSvr(emsg))
      return(false);
   // 2. 先恢复Out消息，即KSCTS支持的委托和撤单消息:
   if (!m_OThreads[0].Restore(m_PartnerID,emsg))
      return(false);

   if (!m_CJThread.Restore(m_PartnerID,emsg))
      return(false);

   return(true);
}

// 参数  : char *statusmsg [OUT]: 用如下格式返回各个Partner的状态：
//             <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerID2>:<status>:<load>:<errmsg>
//             status: 0 - 没有启动；1 - 已经正常启动
//             load: 负载值，即还没有被处理的OUT消息个数
// 参数  : unsigned int smsize [IN]: statusmsg的缓存字节数(大概近4000个字节) 
int CKSCTS::GetStatus(char *statusmsg, unsigned int smsize)
{
   char emsg[256];
   if (m_Status>FS_CLOSE)
   {
      if (CheckKSCTSSvr(emsg))
      {
         sprintf(statusmsg,"%s:%d:%d:Last-DoneID=%ld,Time=%ld; Out=%d,Time=%ld",
            m_PartnerID,FS_OPEN,
            UG_GetOutMsgSize(m_PartnerID),
            m_LastDoneID,m_LastDoneTime,m_OutCnt,m_LastOutTime);
      }
      else
      {
         sprintf(statusmsg,"%s:%d:%d:%s",
            m_PartnerID,FS_CONNECTING,
            UG_GetOutMsgSize(m_PartnerID),
            emsg);
      }
   }
   else
   {
      sprintf(statusmsg,"%s:%d:%d:Last-DoneID=%ld,Time=%ld; Out=%d,Time=%ld",
         m_PartnerID,m_Status,
         UG_GetOutMsgSize(m_PartnerID),
         m_LastDoneID,m_LastDoneTime,m_OutCnt,m_LastOutTime);
   }
   return(0);  // 这种模式下，除非数据库连接不行或配置错误，就当做不需要重启
}

// 描述  : 对本连接做Reset处理，清除之前处理缓存的数据，并进入关闭状态
// 返回  : int <0: 失败；否则，成功
// 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
// 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
int CKSCTS::EndOfDay(const char *sLocalID, const char *sPartnerID, char *emsg)
{
   CPMUTEX pMutex(&m_DBMutex);
   m_LastDoneTime = time(NULL);
   DBGetLastMaxDoneID(&m_LastDoneID);
   SQLDebugLog(500,"EndOfDay(%s): LastDoneID=%ld",sPartnerID,m_LastDoneID);
   m_Cancels.clear();
   return(0);
}

int CKSCTS::GetOutMsg(char *fixmsg)
{
   int rtn;
   rtn = UG_GetOutMsg(m_PartnerID,100,fixmsg);
   if (rtn>0)
   {
      m_LastOutTime = time(NULL);
      ++m_OutCnt;
   }
   return(rtn);
}

// 检查KSCTS应用服务器的状态（是否正常可以提供服务）
bool CKSCTS::CheckKSCTSSvr(char *emsg)
{
   BCResetHandle(m_bch);
   BCSetRequestType(m_bch,100319);  // 作为测试功能调用一下
//    if (CallSvr(m_bch,emsg)<0)
   if (m_DRouters.TryCallSvr(m_bch,m_SvrDestNo,m_SvrFuncNo,emsg)<0)
      return(false);
   return(true);
}

int CKSCTS::SendToFIXSvr(const char *fixmsg)
{
   if (m_Status==FS_OPEN)  // 已经处于正常运行状态
      return(UDLHaveMessageIn(m_PartnerID,fixmsg));
   else
      return(UG_RestoreFIXInMsg(m_PartnerID,fixmsg));
}

int CKSCTS::TryCallSvr(BCHANDLE bch, char *errMsg)
{
	return(m_DRouters.TryCallSvr(bch,m_SvrDestNo,m_SvrFuncNo,errMsg));
}

int CKSCTS::CallNext(BCHANDLE bch, char *errMsg)
{
	return(m_DRouters.CallNext(bch,errMsg));
}

/*
 *	fix		fix的标准货币代码
	local	后台的货币代码
	iflag	0 fix转local  1 local转fix
 */
void CKSCTS::GetCurrcncy(char *fix,char *local,int iflag)
{
	if(iflag == 0)
	{
		if(strcmp(fix,"CNY") == 0 || strcmp(fix,"") == 0)
			strcpy(local,"01");
		else if(strcmp(fix,"USD") == 0)
			strcpy(local,"02");
		else if(strcmp(fix,"HKD") == 0)
			strcpy(local,"03");
	}
	else if(iflag == 1)
	{
		if(strcmp(local,"01") == 0 || strcmp(local,"") == 0)
			strcpy(fix,"CNY");
		else if(strcmp(local,"02") == 0)
			strcpy(fix,"USD");
		else if(strcmp(local,"03") == 0)
			strcpy(fix,"HKD");
	}
}

// 2012-6-6 23:23:08 在收到撤单被拒绝的时候进行处理，减少CheckCxlReject的工作
bool CKSCTS::HaveACancelReject(const char *origclordid)
{
   CPMUTEX pMutex(&m_CCMutex);
   M_CXLCLORDID::iterator it;
   char clordid[40];
   it = m_Cancels.find((string)origclordid);
   if (it!=m_Cancels.end())
   {
      STRNCPY(clordid,it->second.c_str());
      if (CheckACancelReject(origclordid,clordid))
      {
         m_Cancels.erase(it);
         return(true);
      }
   }
   return(false);
}
