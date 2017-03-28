/********************************************************************
	created:	2011/09/29
	created:	29:9:2011   17:18
	filename: 	C:\dd\projects\FIXIII\UGate\ugfts\OutThread.cpp
	file path:	C:\dd\projects\FIXIII\UGate\ugfts
	file base:	OutThread
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 这部分为处理来自FS的业务消息处理模块，本代码专与KSFTS对接
   注意：
   -- 委托状态
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, '!', '委托状态'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'n', '等待发出'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 's', '正在申报'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'a', '已经报入'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'p', '部分成交'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'c', '全部成交'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'b', '部成部撤'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'f', '等待撤除'  )
   --insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'g', '撤单发出'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'd', '已经撤销'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'e', '错误委托'  )
   -- jq 20070118 主机拒绝改为场内拒绝
   --insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'q', '主机拒绝'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'q', '场内拒绝'  )

  FUNCTION 854041 Description  "查询当日委托单"  reqlevel 1
输入：操作员,席位号,客户号,客户类,合约号,委托状态集合,所有委托单标记,币种,是否不输出合计标记,强平标记,定单类型, 组合非组合查询标志, 开平仓标志，排序方式
INPUT:SCUST_NO,SSERIAL2,SHOLDER_AC_NO,SSERIAL1,SCUST_AUTH,SBANK_PWD2,SMAIN_FLAG,SCURRENCY_TYPE,SSTATUS3,SSTATUS1,SNAME2, SSTATUS2, SSTATUS0,SSTATUS4
输出：委托号,操作员,客户号,客户名称,交易所代码,品种代码,交割期,委托单状态,开平标记,投保标记,买卖方向,委托价,委托量,剩余量,成交价,成交量,系统号,委托时间,申报时间,交易编码,委托方式,撤单用户,撤单时间,委托单类型,席位号,币种,备注,修改批次,强平标志,指令编号,下单席位,本地标志,组合策略,合约1,合约2,合约3,合约4,定单类型,成交属性,组合类型,止损（盈）价,触发时间,下单人类型,私有信息,私有标识,私有流水号 
OUTPUT:LSERIAL0,SCUST_NO,SHOLDER_AC_NO,SNAME,SMARKET_CODE,SSTOCK_CODE,SDATE1,SSTATUS0,SSTATUS3,SSTATUS4,SSTATUS2,DAMT0,LVOL0,LVOL2,DAMT2,LVOL1,SORDER0,STIME0,STIME1,SHOLDER_AC_NO2,SHOLDER_TYPE,SCUST_NO2,STIME2,SSTAT_TYPE2,SSERIAL2,SCURRENCY_TYPE,SNOTE,LWITHDRAW_FLAG,SSTATUS1,LSERIAL1,VSVARSTR1,SMAIN_FLAG,SPOST_CODE2,SPHONE,SPHONE2,SPHONE3,SPAGER,SCUST_TYPE,SCUST_TYPE2,SSTAT_TYPE,DAMT3,STIME3,SMAIN_FLAG2,sstation1,semp_no,scust_limit
*********************************************************************/
// OutThread.cpp: implementation of the COutThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "fixbase.h"
#include "ugate.h"
#include "MsgDataList.h"
#include "OutThread.h"
#include "KSFTS.h"
#include "GetErrInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutThread::COutThread()
{
   m_omsgcnt = 0;
}

COutThread::~COutThread()
{

}


#ifdef _MSC_VER
void OutProcess(void *pv)
#else
void *OutProcess(void *pv)
#endif
{
   COutThread *pOutThread = (COutThread *)pv;
   pOutThread->Run();
}


int COutThread::Initialize(int id, char *emsg)
{
   m_ID = id;
   m_bc = BCNewHandle(g_KSFTS.GetXPackFile());
   if (m_bc==NULL)
   {
      sprintf(emsg,"Fail to BCNewHandle(%s)!",g_KSFTS.GetXPackFile());
      return(-2);
   }
   m_fh = FIXDataNew();
   if (m_fh==NULL)
   {
      sprintf(emsg,"Fail to allocate FIXData!");
      return(-3);
   }
   
   return(0);
}

void COutThread::Exit()
{
   if (m_fh!=NULL)
   {
      FIXDataDelete(m_fh);
      m_fh = NULL;
   }
   if (m_bc!=NULL)
   {
      BCDeleteHandle(m_bc);
      m_bc = NULL;
   }
}

int COutThread::Run()
{
   int rtn;
   SQLDebugLog(400,"OutThread[%d] Start",m_ID);
   while (g_KSFTS.IsRunning() && m_omsgcnt>=0)
   {
      //rtn = UG_GetOutMsg(g_KSFTS.m_PartnerID,10,m_fixmsg);
      rtn = g_KSFTS.GetOutMsg(m_fixmsg);
      if (rtn<0)
         break;
      if (rtn==0)
      {
         // 无，继续。。。
      }
      else if (FIXDataSetData(m_fh,m_fixmsg,rtn)<=0)
      {
         SQLDebugLog(4001,"OThread[%d] Get invalid outmsg:%s",m_ID,m_fixmsg);
      }
      else if (FIXDataGetUGData(m_fh,&m_ugdata,NULL,0)<=0)
      {
         SQLDebugLog(4002,"OThread[%d] Get invalid outmsg:%s",m_ID,m_fixmsg);
      }
      else
      {
         OProcess();
      }
   }
   SQLDebugLog(401,"OutThread[%d] Stop",m_ID);
   m_omsgcnt = -1;
   return(rtn);
}

bool COutThread::ToStartOutProcess(char *emsg)
{
   if (StartThread(OutProcess,this)<0)
   {
      sprintf(emsg,"Fail to start OutProcess[%d]!",m_ID);
      return(false);
   }
   return(true);
}

void COutThread::ToStopOutProcess()
{
   m_omsgcnt = -2;
}

int COutThread::OProcess()
{
   ++m_omsgcnt;
   if (strcmp(m_ugdata.sMsgType,"D")==0)
      return(HandleNewOrderSingle());
   if (strcmp(m_ugdata.sMsgType,"F")==0)
      return(HandleOrderCancelRequest());
   if (strcmp(m_ugdata.sMsgType,"KSFR")==0)
      return(QueryFundStatus());  // 这个为单记录查询返回例子
   if (strcmp(m_ugdata.sMsgType,"KSPR")==0)
      return(QueryPositionStatus()); // 这个为多记录查询返回例子
   SQLDebugLog(50001,"Unsupported MsgType=%s @ FTS-OUTThread!",m_ugdata.sMsgType);
   return(-1);
}

// 在使用ExtCall的时候，如果通讯平台或目标服务端异常
#define MIN_XCALLERR 9985
//#define MAX_XCALLERR 9988  // V2.73以上
#define MAX_XCALLERR 10000  // under 2.72

#define TAG_HedgeFlag  8009 // 	8009	HedgeFlag		Y		投机套保标志 按照期货间数据接口中的定义
int COutThread::HandleNewOrderSingle()
{
   char fvalue[256];
   //char sOpenClose[2];
   char sFTSMarketCode[4];
   char sBuySell[2];
   char sOrdType[2];   
   // 2010-9-11 20:34:20 新增，为了给出确定的“成交属性”
   char sDealMode[2];  /*  FIX TimeInForce -> 成交属性 */
   //////////////////////////////////////////////////////////////////////////
   int rtn;
   char *pcustno,*pseat;

   STRNCPY(m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID);  // 为了后面这个函数，另外也为后面的消息准备
   rtn = QueryFTSOrders(&m_ugdata);
   if (rtn>0)
   {
      // 即FTS内部已经有该订单了
      if (g_KSFTS.m_Status<FS_OPEN)
      {
         // 即属于Open前的Restore阶段:
         if (rtn>1)
         {
            g_KSFTS.RegisterWTHClOrdID(m_sWTH[1],m_ugdata.sOrigClOrdID,m_vsvarstr1[1]);
         }
         g_KSFTS.RegisterWTHClOrdID(m_sWTH[0],m_ugdata.sOrigClOrdID,m_vsvarstr1[0]);
      }
      else  // ??? 这里可能该以订单拒绝的方式给FS的, 但是本来这个应该在FS上就已经被控制了，为啥呢?? 这种场景能够再现吗？
         SQLDebugLog(7011,"Duplicated Order:%s",m_fixmsg);
      // 给出该订单的状态，以补充之前或许没有给出的成交数据: 只是补充委托部分，对撤单部分，则由对应的撤单去完成
      m_ugdata.dOrderQty = m_OrderQty[0]+m_OrderQty[1];
      m_ugdata.dCumQty = m_CumQty[0]+m_CumQty[1];
      m_ugdata.dAvgPx = m_ugdata.dCumQty>MIN_QTY ? (m_AvxPx[0]*m_CumQty[0]+m_AvxPx[1]*m_CumQty[1])/m_ugdata.dCumQty : 0;
      m_ugdata.dLastQty = m_ugdata.dCumQty;
      m_ugdata.dLastPx = m_ugdata.dAvgPx;
      m_ugdata.dLeavesQty = m_ugdata.dOrderQty-m_ugdata.dCumQty;
      strcpy(m_ugdata.sOrderID,m_sWTH[0]);
      switch (m_WTZT[0])
      {
      case 'e':   // 'e', '错误委托'
      case 'q':   // 'q', '场内拒绝'
         // 则为错误委托
         strcpy(m_ugdata.sOrdStatus,"8");
         strcpy(m_ugdata.sExecType,"8");
         sprintf(fvalue,"R-%s",m_sWTH[0]);
         STRNCPY(m_ugdata.sExecID,fvalue);
         m_ugdata.dLeavesQty = 0;
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         return(g_KSFTS.SendToFIXSvr(m_fixmsg));
#if 0    // 看来要用成交明细来恢复，这种很容易导致成交重复
      case 'p':   // 'p', '部分成交'
      case 'c':   // 'c', '全部成交'
      case 'b':   // 'b', '部成部撤'
         if (m_ugdata.dLeavesQty>MIN_QTY)
            strcpy(m_ugdata.sOrdStatus,"1");
         else
            strcpy(m_ugdata.sOrdStatus,"2");
         strcpy(m_ugdata.sExecType,"F");
         sprintf(fvalue,"F-%s",m_sWTH[0]);
         STRNCPY(m_ugdata.sExecID,fvalue);
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         return(g_KSFTS.SendToFIXSvr(m_fixmsg));
#endif
      }
      return(0);
   }
   if (rtn<0)  // ??? 这里要核查 可能有问题的！
   {
      // 常常为通讯链路异常啦！
      if (g_KSFTS.m_Status==FS_OPEN)
      {
         // 那么 这时候FS一般不会重复发送请求的：
         m_ugdata.lOrdRejReason = 0;  // 0 = Broker / Exchange option
//          sprintf(m_ugdata.vsmess,"Unsupported SecurityExchange(%s)",
//             m_ugdata.sSecurityExchange);
         return(ReturnOrderReject());
      }
      return(-1);
   }

   if (g_KSFTS.m_Status<FS_OPEN && m_ugdata.sOrderID[0]!='\0')
      return(0);

   m_ugdata.vsmess[0]='\0'; // 清除原来的如: "没有查询结果"

   if (g_KSFTS.GetMarketCode(&m_ugdata,sFTSMarketCode)==NULL)
   {
      m_ugdata.lOrdRejReason = 11; // 11 = Unsupported order characteristic
      sprintf(m_ugdata.vsmess,"Unsupported SecurityExchange(%s)",
         m_ugdata.sSecurityExchange);
      return(ReturnOrderReject());
   }
   
   switch (m_ugdata.sSide[0])
   {
   case '1':
   case '2':
      sBuySell[0]=m_ugdata.sSide[0]-1; // 1->0,2->1
      sBuySell[1]='\0';
      break;
   default:
      m_ugdata.lOrdRejReason = 11;  // 11 = Unsupported order characteristic
      sprintf(m_ugdata.vsmess,"Unsupported Side(%s)",
         m_ugdata.sSide);
      return(ReturnOrderReject());
   }

   // 期货柜台里 0 限价； 1 市价
   sOrdType[0] = '1';
   sOrdType[1] = '\0';
   switch (m_ugdata.sOrdType[0])
   {
   case '1':  // Market
      m_ugdata.dPrice = 0;
      if (strcmp(m_ugdata.sSecurityExchange,"sfe")==0
         ||strcmp(m_ugdata.sSecurityExchange,"XSGE")==0)
      {
         // 要对上期所做特别处理
         if (QueryLimitPrice(&m_ugdata,sFTSMarketCode)<0)
         {
            m_ugdata.lOrdRejReason = 0;
            return(ReturnOrderReject());
         }
         sOrdType[0] = '0';
      }
      break;
   case '2':   // limit
      sOrdType[0]='0';
      break;
   default:
      m_ugdata.lOrdRejReason = 11;
      sprintf(m_ugdata.vsmess,"Unsupported OrdType(TAG40):%s",m_ugdata.sOrdType);
      return(ReturnOrderReject());
   }

   // 2010-9-11 20:34:20 新增，为了给出确定的“成交属性”
   switch (m_ugdata.sTimeInForce[0])
   {
   case '4': // 4 = Fill or Kill (FOK)
      sDealMode[0]='1';  // 1, FOK全成或全撤 FIX: 4
      break;
   case '3': // 3 = IOC (FAK)
      // 2, FAK剩余即撤销 FIX: 3 - IOC
      sDealMode[0]='2';
      break;
   default:
      sDealMode[0]='0'; // 0, GFD当日有效   FIX: 空或0
      break;
   }
   sDealMode[1]='\0';
   //////////////////////////////////////////////////////////////////////////

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854002);  // 字段的设置必须和查委托的时候一致
   // 客户号	sholder_ac_no
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(m_ugdata.sClientID,fvalue)); 
   // 私有标识	semp_no
   STRNCPY(fvalue,UG_GetPartners());
   BCSetStringFieldByName(m_bc,0,"semp_no",fvalue);      
   // 私有流水号	scust_limit
   BCSetStringFieldByName(m_bc,0,"scust_limit",m_ugdata.sOrigClOrdID);    
   // 买卖方向	sstatus2
   BCSetStringFieldByName(m_bc,0,"sstatus2",sBuySell);
   // 操作员	scust_no
   BCSetStringFieldByName(m_bc,0,"scust_no",g_KSFTS.GetOperator()); 
   // 交易编码	sholder_ac_no2
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no2",m_ugdata.sAccount); 
   // 交易所代码	smarket_code
   BCSetStringFieldByName(m_bc,0,"smarket_code",sFTSMarketCode);
   // 合约号	scust_auth
   BCSetStringFieldByName(m_bc,0,"scust_auth",m_ugdata.sSymbol);
   // 申报手数	lvol0
   BCSetIntFieldByName(m_bc,0,"lvol0",(int)(m_ugdata.dOrderQty+MIN_QTY));
   // 申报价格	damt0
   BCSetDoubleFieldByName(m_bc,0,"damt0",m_ugdata.dPrice);
   // 开平标记	sstatus3
   switch (m_ugdata.sOpenClose[0])
   {
   case 'C':   // C = Close
      BCSetStringFieldByName(m_bc,0,"sstatus3","1");
      break;
   case '2':   // 平今
      BCSetStringFieldByName(m_bc,0,"sstatus3","3");
      break;
   case 'O':   // O = Open
   default:    // R = Rolled;  F = FIFO 都用开仓来处理
      BCSetStringFieldByName(m_bc,0,"sstatus3","0");
      break;
   }
   // 投保标记	sstatus4
   rtn = sizeof(fvalue);
   if (FIXDataGetTag(m_fh,TAG_HedgeFlag,fvalue,&rtn)<0)
   {
      strcpy(fvalue,"0");
   }
   else
   {
      //       投机套保标志，取值范围：
      //          0=投机
      //          1=套保
      //BCSetStringFieldByName(m_bc,0,"sstatus4",fvalue);
   }
   BCSetStringFieldByName(m_bc,0,"sstatus4",fvalue);
   // 席位号	sserial2 -- 不填了

   // 下单人类型	smain_flag2
   BCSetStringFieldByName(m_bc,0,"smain_flag2","1");
   // 委托方式	sholder_type
   BCSetStringFieldByName(m_bc,0,"sholder_type","7");
   // 币种	scurrency_type -- 必须填，目前就只用RMB
   BCSetStringFieldByName(m_bc,0,"scurrency_type","1");
   // BCSetStringFieldByName(m_bc,0,"",);
   // 强平标志	sstatus0 : 0不强平  1强平 -- 不填了 0和不填 一样的效果

   // 定单类型	scust_type:  0 限价； 1 市价
   BCSetStringFieldByName(m_bc,0,"scust_type",sOrdType);
   // 成交属性	scust_type2:
   BCSetStringFieldByName(m_bc,0,"scust_type2",sDealMode);
   // 止损止盈价	damt3  -- 99	StopPx
   rtn = sizeof(fvalue);
   if (FIXDataGetTag(m_fh,99,fvalue,&rtn)<0)
   {
      // 那就不填了
   }
   else
   {
      BCSetStringFieldByName(m_bc,0,"damt3",fvalue);
   }

   // 私有信息	sstation1
   sprintf(fvalue,"From %s-%s",m_ugdata.sOnBehalfOfCompID,m_ugdata.sOnBehalfOfSubID);
   BCSetStringFieldByName(m_bc,0,"sstation1",fvalue);

   rtn = g_KSFTS.CallSvr(m_bc,fvalue);
   int n=-1;
   if (rtn>=0 
      && BCGetRetCode(m_bc,&rtn) 
      && (rtn<MIN_XCALLERR||rtn>MAX_XCALLERR))
   {
      if (rtn!=0)
      {
         // 服务器返回委托失败:
         BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue)); mytrim(fvalue);
         sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue);
		 SetErrCodeInfo(FUTURE_MCODE,m_ugdata.vsmess, "Rejected by KSFTS, ErrNo=", m_ugdata.vsmess);
         m_ugdata.lOrdRejReason = 0;
         return(ReturnOrderReject());
      }
      BCGetRecordCount(m_bc,&rtn);
      if (rtn>2)
         rtn = 2; // 目前一次只能有两笔
      pcustno = fvalue;
      pseat = fvalue+100;
      for (n=0;n<rtn;++n)
      {
         int l;
         // 委托号	lserial0
         BCGetIntFieldByName(m_bc,n,"lserial0",&l);
         // 客户号	sholder_ac_no
         BCGetStringFieldByName(m_bc,0,"sholder_ac_no",pcustno,100);
         mytrim(pcustno);
         // 席位号	sserial2
         BCGetStringFieldByName(m_bc,0,"sserial2",pseat,100);
         mytrim(pseat);

         g_KSFTS.GetWTH(l,pcustno,pseat,m_sWTH[n]);
         
         // 下单席位
         BCGetStringFieldByName(m_bc,n,"vsvarstr1",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         STRNCPY(m_vsvarstr1[n],fvalue);

         // 委托状态	sstatus0
         BCGetStringFieldByName(m_bc,n,"sstatus0",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         m_WTZT[n]=fvalue[0];
      }
   }
   else
   {
      n = QueryFTSOrders(&m_ugdata);
   }
   if (n<=0)
   {
      // 似乎FTS异常或者其他错误
      sprintf(m_ugdata.vsmess,"Invalid KSFTS, ErrNo=%d:%s",7011,fvalue);
      m_ugdata.lOrdRejReason = 0;
      return(ReturnOrderReject());
   }
   if (n>1)
   {
      g_KSFTS.RegisterWTHClOrdID(m_sWTH[1],m_ugdata.sOrigClOrdID,m_vsvarstr1[1]);
   }
   g_KSFTS.RegisterWTHClOrdID(m_sWTH[0],m_ugdata.sOrigClOrdID,m_vsvarstr1[0]);
   // 下单成功:
   sprintf(fvalue,"1_%s",m_ugdata.sClOrdID);  // 这里和常规的成交执行号特殊一些 '_',防止重复
   STRNCPY(m_ugdata.sExecID,fvalue);
   strcpy(m_ugdata.sOrdStatus,"0");  // as NewConfirmation return.
   strcpy(m_ugdata.sExecType,"0");  // as NewConfirmation return.
   STRNCPY(m_ugdata.sOrderID,m_sWTH[0]);
   m_ugdata.dLastPx = m_ugdata.dLastQty = m_ugdata.dCumQty = m_ugdata.dAvgPx = 0;
   m_ugdata.dLeavesQty = m_ugdata.dOrderQty;
   UG_UGDataReturn(&m_ugdata);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}

int COutThread::HandleOrderCancelRequest()
{
   char fvalue[256];
   int n = 0;
   m_WTZT[0]=m_WTZT[1]='?'; // 均为未知
   m_OrderQty[0]=m_CumQty[0]=0;
   m_AvxPx[0]=m_AvxPx[1]=0;
   m_OrderQty[1]=m_CumQty[1]=0;
   if (g_KSFTS.m_Status>=FS_OPEN)
   {
      // 还是这样快，到后台去调用功能，肯定慢了，反正有记录数据了
      n = GetAllWTH(m_ugdata.sOrigClOrdID);
   }
   else if (m_ugdata.sOrderID[0])
   {
      return(0); // 为恢复状态，已经有OrderID，则说明已经有返回了，则不需要再发请求了。
   }
   if (n<1)
      n = QueryFTSOrders(&m_ugdata);
   if (n<1)
   {
      if (g_KSFTS.m_Status>=FS_OPEN)
      {
         m_ugdata.lCxlRejReason = 1;  // 1 = Unknown order
         STRNCPY(m_ugdata.sOrderID,"NONE");
         return(ReturnCancelRejected());         
      }
      else
      {
         // 恢复阶段，这些其实都不用了。估计上次也是被这样毙了的。
         return(0);
      }
   }
   // 这里需要加入是否已经做撤单处理的判断，即查询原单的状态信息
   m_ugdata.dOrderQty = m_ugdata.dCumQty = m_ugdata.dLastQty = m_ugdata.dLeavesQty = 0;
   m_ugdata.dLastPx = m_ugdata.dAvgPx = 0;
   UG_UGDataReturn(&m_ugdata);
   if (n>1)
   {
      switch (m_WTZT[1])
      {
      case 'b': // 'b', '部成部撤' 
      case 'd': // 'd', '已经撤销'
         // 都已经做了撤单: 对于恢复阶段，则要返回撤单成功的消息:      
         m_ugdata.dOrderQty = m_OrderQty[1];
         m_ugdata.dCumQty = m_CumQty[1];
         sprintf(fvalue,"C-%s",m_sWTH[1]);  // 用sWTH是为了多个WTH的撤单回报需要，这样就不会重复了，呵呵
         STRNCPY(m_ugdata.sExecID,fvalue);
         strcpy(m_ugdata.sOrdStatus,"4");
         strcpy(m_ugdata.sExecType,"4"); // 表示撤单
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         g_KSFTS.SendToFIXSvr(m_fixmsg);
         break;
      }
   }
   switch (m_WTZT[0])
   {
   case 'f': // 'f', '等待撤除'
      // 都已经做了撤单:
      return(0);
   case 'b': // 'b', '部成部撤' 
   case 'd': // 'd', '已经撤销'
      // 都已经做了撤单: 对于恢复阶段，则要返回撤单成功的消息:      
      m_ugdata.dOrderQty = m_OrderQty[0];
      m_ugdata.dCumQty = m_CumQty[0];
      sprintf(fvalue,"C-%s",m_sWTH[0]);  // 用sWTH是为了多个WTH的撤单回报需要，这样就不会重复了，呵呵
      STRNCPY(m_ugdata.sExecID,fvalue);
      strcpy(m_ugdata.sOrdStatus,"4");
      strcpy(m_ugdata.sExecType,"4"); // 表示撤单
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSFTS.SendToFIXSvr(m_fixmsg));
   case 'c': // 'c', '全部成交'
   case 'e': // 'e', '错误委托'
   case 'q': // 'q', '场内拒绝'
      return(1);
   }
   
   // m_iCancelledQty = 0;
   m_ugdata.dOrderQty = m_ugdata.dCumQty = m_ugdata.dLastQty = m_ugdata.dLeavesQty = 0;
   m_OrderQty[0]=m_CumQty[0]=0;
   m_AvxPx[0]=0;
   m_OrderQty[1]=m_CumQty[1]=0;
   m_AvxPx[1]=0;
   m_WTZT[0]=m_WTZT[1]='?';

   if (n>1)
   {
      if (CancelAnOrder(1,fvalue)==0)
      {
         // 说明撤单被接受了, 看看是否内部撤单了
         if (m_WTZT[1]=='d')
         {
            sprintf(fvalue,"C-%s",m_sWTH[1]);
            STRNCPY(m_ugdata.sExecID,fvalue);
            m_ugdata.dOrderQty = m_OrderQty[1];
            m_ugdata.dCumQty = m_CumQty[1];
            strcpy(m_ugdata.sOrdStatus,"4");
            strcpy(m_ugdata.sExecType,"4"); // 表示撤单
            UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
            g_KSFTS.SendToFIXSvr(m_fixmsg);
         }
      }
   }
   if (CancelAnOrder(0,fvalue)==0)
   {
      // 说明撤单被接受了, 看看是否内部撤单了
      if (m_WTZT[0]=='d')
      {
         sprintf(fvalue,"C-%s",m_sWTH[0]);
         STRNCPY(m_ugdata.sExecID,fvalue);
         m_ugdata.dOrderQty = m_OrderQty[0];
         m_ugdata.dCumQty = m_CumQty[0];
         strcpy(m_ugdata.sOrdStatus,"4");
         strcpy(m_ugdata.sExecType,"4"); // 表示撤单
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         return(g_KSFTS.SendToFIXSvr(m_fixmsg));
      }
      return(0);  // 不用给任何返回的，或者给PendingCancel返回。但是FS无所谓的。
   }
   // 这种就是撤单被拒绝了：
   m_ugdata.lCxlRejReason = 99;
   STRNCPY(m_ugdata.sOrderID,m_sWTH[0]);
   return(ReturnCancelRejected());
}

bool COutThread::Restore(const char *partnerid, char *emsg)
{
   L_MSGDATA lOutMsgs;
   L_MSGDATA::iterator it;
   int rtn;
   rtn = UG_GetSSAllOrders(g_KSFTS.m_PartnerID,lOutMsgs);
   for (it=lOutMsgs.begin();it!=lOutMsgs.end();++it)
   {
      if (FIXDataSetData(m_fh,it->msgbuf,it->msglen)>0
         && FIXDataGetUGData(m_fh,&m_ugdata,NULL,0)>0)
      {
         OProcess();
         g_KSFTS.HaveAnOutMsg();
      }
   }
   return(true);
}

int COutThread::QueryFTSOrders(T_UGDATA *pUGData)
{
   char fvalue[256];
   int rtn;
   int n;
   char *pcustno,*pseat;
   memset(m_WTZT,0,sizeof(m_WTZT));
   m_OrderQty[0]=m_CumQty[0]=0;
   m_AvxPx[0]=0;
   m_OrderQty[1]=m_CumQty[1]=0;
   m_AvxPx[1]=0;
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854118);  // 查指定订单在FTS中的    下面字段的设置必须和委托的时候一致
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(pUGData->sClientID,fvalue)); // 客户号	sholder_ac_no
   STRNCPY(fvalue,UG_GetPartners());
   BCSetStringFieldByName(m_bc,0,"semp_no",fvalue);      // 私有标识	semp_no
   BCSetStringFieldByName(m_bc,0,"scust_limit",pUGData->sOrigClOrdID);  // 私有流水号	scust_limit  

   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);  // 这里由于对重复请求无所谓，所以选用了TryCallSvr
   if (rtn<0)
   {
      SQLDebugLog(7001,"Fail to CallFTSSvr(854118,%s,%s):%d-%s",
         pUGData->sClientID,pUGData->sOrigClOrdID,rtn,fvalue);
      STRNCPY(pUGData->vsmess,fvalue);
      return(rtn);
   }
   BCGetRetCode(m_bc,&rtn);
   if (rtn!=0)
   {
      // rtn=9999 : 应用服务器: 没有查询结果
      BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
      mytrim(fvalue);  // 
      STRNCPY(pUGData->vsmess,fvalue);
      SQLDebugLog(7002,"CallFTSSvr(854118,%s,%s):retCode=%d-%s",
         pUGData->sClientID,pUGData->sOrigClOrdID,rtn,fvalue);
      return(0); //
   }
   BCGetRecordCount(m_bc,&rtn);
   if (rtn<=0)
   {
      STRNCPY(pUGData->vsmess,"Unknown Order");
      return(0);
   }
   if (rtn>2)
      rtn = 2; // 目前一次只能有两笔
   pcustno = fvalue;
   pseat = fvalue+100;
   for (n=0;n<rtn;++n)
   {
      int l;
      BCGetIntFieldByName(m_bc,n,"lserial0",&l);
      // 客户号	sholder_ac_no
      BCGetStringFieldByName(m_bc,0,"sholder_ac_no",pcustno,100);
      mytrim(pcustno);
      // 席位号	sserial2
      BCGetStringFieldByName(m_bc,0,"sserial2",pseat,100);
      mytrim(pseat);
         
      g_KSFTS.GetWTH(l,pcustno,pseat,m_sWTH[n]);

      // 下单席位
      BCGetStringFieldByName(m_bc,n,"vsvarstr1",fvalue,sizeof(fvalue));
      mytrim(fvalue);
      STRNCPY(m_vsvarstr1[n],fvalue);

      // 委托状态	sstatus0
      BCGetStringFieldByName(m_bc,n,"sstatus0",fvalue,sizeof(fvalue));
      mytrim(fvalue);
      m_WTZT[n]=fvalue[0];
      // 委托量	lvol0
      BCGetIntFieldByName(m_bc,n,"lvol0",m_OrderQty+n);
      // 成交量	lvol1
      BCGetIntFieldByName(m_bc,n,"lvol1",m_CumQty+n);
      // 成交价	damt2
      BCGetDoubleFieldByName(m_bc,n,"damt2",m_AvxPx+n);
   }
   return(n);
}

char * COutThread::GetClientNo(const char *sClientID, char *sClientNo)
{
   sClientNo[0]='\0';
   GetSubString(sClientID,'-',0,sClientNo,16,NULL);
   return(sClientNo);
}

int COutThread::ReturnOrderReject()
{
   strcpy(m_ugdata.sMsgType,"8");
   strcpy(m_ugdata.sExecType,"8");
   UG_UGDataReturn(&m_ugdata);
   m_ugdata.dCumQty = m_ugdata.dLeavesQty = m_ugdata.dLastQty = 0;
   m_ugdata.dAvgPx = m_ugdata.dLastPx = 0;
   sprintf(m_fixmsg,"R_%s",m_ugdata.sClOrdID);
   STRNCPY(m_ugdata.sExecID,m_fixmsg);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}

int COutThread::QueryLimitPrice(T_UGDATA *pUGData, char *sFTSMarketCode)
{
   char fvalue[256];
   int rtn;
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854132);  // 查指定合约的行情数据
   BCSetStringFieldByName(m_bc,0,"scust_no", g_KSFTS.GetOperator());          //操作员
   BCSetStringFieldByName(m_bc,0,"smarket_code",sFTSMarketCode);     //交易所代码	smarket_code
   BCSetStringFieldByName(m_bc,0,"scust_auth", pUGData->sSymbol);    //合约号
   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);
   if (rtn<0)
   {
      sprintf(pUGData->vsmess,"Fail to GetMarketData(%s,%s)",sFTSMarketCode,pUGData->sSymbol);
      SQLDebugLog(7003,"Fail to CallFTSSvr(854132,%s,%s):%d-%s",
         sFTSMarketCode,pUGData->sSymbol,rtn,fvalue);
      return(rtn);
   }
   BCGetRetCode(m_bc,&rtn);
   if (rtn!=0)
   {
      sprintf(pUGData->vsmess,"Fail to GetMarketData(%s,%s)",sFTSMarketCode,pUGData->sSymbol);
      BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
      SQLDebugLog(7002,"CallFTSSvr(854132,%s,%s):retCode=%d-%s",
         sFTSMarketCode,pUGData->sSymbol,rtn,fvalue);
      return(-1);
   }
   switch (pUGData->sSide[0])
   {
   case '1': // Buy:
      BCGetDoubleFieldByName(m_bc,0,"damt27",&(pUGData->dPrice));
      break;
   case '2': // Sell:
      BCGetDoubleFieldByName(m_bc,0,"damt28",&(pUGData->dPrice));
      break;
   }
   return(0);
}

// 即对一个WTH进行撤单请求处理, iwt: 0 or 1; 
int COutThread::CancelAnOrder(int iwt, char *fvalue256)
{
   int rtn;
   int lvol0,lvol2;
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854018);  // 撤销委托
   // 操作员	scust_no
   BCSetStringFieldByName(m_bc,0,"scust_no",g_KSFTS.GetOperator()); 
   // 客户号	sholder_ac_no
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",g_KSFTS.GetCustNoFromWTH(m_sWTH[iwt],fvalue256,256));
   // 席位号	sserial2  -- 这个先不要看看
   BCSetStringFieldByName(m_bc,0,"sserial2",g_KSFTS.GetSeatNoFromWTH(m_sWTH[iwt],fvalue256,256));

   // 下单人类型	smain_flag2
   BCSetStringFieldByName(m_bc,0,"smain_flag2","1");

   // 委托号	lserial0
   BCSetIntFieldByName(m_bc,0,"lserial0",g_KSFTS.GetIWTH(m_sWTH[iwt])); 

   // 下单席位	vsvarstr1
   BCSetStringFieldByName(m_bc,0,"vsvarstr1",m_vsvarstr1[iwt]); 
   
   g_KSFTS.UpdateClOrdID(m_sWTH[iwt],m_ugdata.sClOrdID);
   
   rtn = g_KSFTS.CallSvr(m_bc,fvalue256);
   if (rtn<0)
   {
      SQLDebugLog(7021,"Fail to CallFTSSvr(854018,%s,%s):%d-%s",
         m_ugdata.sOrigClOrdID,m_sWTH[iwt],rtn,fvalue256);
      sprintf(m_ugdata.vsmess,"Fail to Call KSFTS, ErrNo=%d:%s",rtn,fvalue256);
      return(rtn);
   }
   BCGetRetCode(m_bc,&rtn);
   if (rtn!=0)
   {
      BCGetStringFieldByName(m_bc,0,"vsmess",fvalue256,256);
      SQLDebugLog(7022,"CallFTSSvr(854018,%s,%s):retCode=%d-%s",
         m_ugdata.sOrigClOrdID,m_sWTH[iwt],rtn,fvalue256);
	  sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue256);
		 SetErrCodeInfo(FUTURE_MCODE,m_ugdata.vsmess, "Cancel Rejected by KSFTS, ErrNo=", m_ugdata.vsmess);
      return(rtn);
   }
   // 委托状态	sstatus0
   BCGetStringFieldByName(m_bc,0,"sstatus0",fvalue256,256);
   mytrim(fvalue256);
   m_WTZT[iwt]=fvalue256[0];
   //if (m_ugdata.sOrdStatus[0]=='d')  // 'd', '已经撤销'
   {
      // 申报手数	lvol0
      BCGetIntFieldByName(m_bc,0,"lvol0",&lvol0); 
      m_OrderQty[iwt]=lvol0;
      // 剩余手数	lvol2
      BCGetIntFieldByName(m_bc,0,"lvol2",&lvol2);  // 这个应该是0
      m_CumQty[iwt]=lvol0-lvol2;
   }
   return(0);
}

int COutThread::ReturnCancelRejected()
{
   strcpy(m_ugdata.sCxlRejResponseTo,"1");  // 1 = Order Cancel Request
   STRNCPY(m_ugdata.sOrdStatus,"8");  // 
   STRNCPY(m_ugdata.sExecType,"8"); 
   UG_UGDataReturn(&m_ugdata);
   UG_CancelRejectFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}


// 函数名: COutThread::MayToBeCanceled
// 编程  : 陈永华 2011-10-2 10:43:51
// 描述  : 检查通过委托状态，以判断是否可以下撤单，若不可以，则给出撤单拒绝
// 返回  : int =0: 不可下撤单请求；否则，可下撤单请求
// 参数  : int iwt[IN]: 0 或 1，表示对m_sWTH[0]-m_WTZT[0]或m_sWTH[1]-m_WTZT[1]
int COutThread::MayToBeCanceled(int iwt)
{
   if (iwt<0 || iwt>1)
      return(0);
   STRNCPY(m_ugdata.sOrderID,m_sWTH[iwt]);
   switch (m_WTZT[iwt])
   {
   case 'c': // 全部成交
      m_ugdata.lCxlRejReason = 0;
      strcpy(m_ugdata.vsmess,"The order has been filled!");
      ReturnCancelRejected();
      return(0);
   case 'f': // 等待撤单
      if (g_KSFTS.m_Status>=FS_OPEN)
      {
         // 为正常Open状态，新下的撤单请求，则要给撤单拒绝，但由于FS控制，应该不会出现的
         m_ugdata.lCxlRejReason = 3;
         ReturnCancelRejected();
      }
      return(0);
   case 'q': // 场内拒绝
      // 则该以委托拒绝返回, 为了防止在断线期间，没有将推送过来的消息处理
#if 0
      // 这部分用NewOrderSingle恢复的时候，返回提示即可
      strcpy(m_ugdata.sExecType,"8");
      strcpy(m_ugdata.sOrdStatus,"8");
      sprintf(m_fixmsg,"R-%s",m_sWTH[iwt]);
      STRNCPY(m_ugdata.sExecID,m_fixmsg);
      m_ugdata.dLeavesQty = 0;
      UG_UGDataReturn(&m_ugdata);
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      g_KSFTS.SendToFIXSvr(m_fixmsg);
#endif
      return(0);
   case 'b': // 部成部撤
   case 'd': // 已经撤销
      // 则返回撤单成功返回
      strcpy(m_ugdata.sExecType,"4");
      strcpy(m_ugdata.sOrdStatus,"4");
      m_ugdata.dOrderQty = m_OrderQty[iwt];
      m_ugdata.dCumQty = m_CumQty[iwt];
      m_ugdata.dLeavesQty = m_OrderQty[iwt]-m_CumQty[iwt];
      m_ugdata.dLastPx = m_ugdata.dLastQty = 0;
      sprintf(m_fixmsg,"C-%s",m_sWTH[iwt]);  // 用sWTH是为了多个WTH的撤单回报需要，这样就不会重复了，呵呵
      STRNCPY(m_ugdata.sExecID,m_fixmsg);
      UG_UGDataReturn(&m_ugdata);
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      g_KSFTS.SendToFIXSvr(m_fixmsg);
      return(0);
   default:  // 其他，则准许继续撤单请求处理
      return(1);
   }
}


int COutThread::GetAllWTH(const char *sOrigClOrdID)
{
   CPMUTEX pMutex(&(g_KSFTS.m_WTHMutex));
   M_CLORDID::iterator it;
   int n=0;
   for (it=g_KSFTS.m_WTHMap.begin();it!=g_KSFTS.m_WTHMap.end();++it)
   {
      if (strcmp(sOrigClOrdID,it->second.sOrigClOrdID)==0)
      {
         strcpy(m_sWTH[n],it->first.c_str());
         strcpy(m_vsvarstr1[n],it->second.sVsvarstr1);
         if (++n>=2)
            break;
      }
   }
   return(n);
}

// 查询客户资金状态
/* 854051:
   scust_no='',操作员
   sholder_ac_no='',客户号
   sserial1='',客户类
   scurrency_type='',币种
   sstatus0='',生成合计

  sholder_ac_no='',客户号
  scurrency_type='',币种
  sall_name='',客户简称/客户类名称
  damt3='',上日结存
  damt26='',可用资金
  damt29='',买冻结
  damt30='',卖冻结
  damt6='',手续费
  damt13='',买保证金
  damt1='',卖保证金
  damt11='',平仓盈亏
  damt8='',浮动盈亏
  damt10='',在途资金
  damt18='',未交割盈亏
  damt28='',动态权益
  damt4='',当日出入金
  damt25='',总冻结
  damt23='',总保证金
  damt24='',总交易所保证金
  damt19='',质押金额
  damt31='',信用金额
  damt22='',风险度1
  damt33='',冻结手续费
  sstatus3='',风险级别
  damt21='',风险度2
*/
#define TAG_RequestID 8088
#define TAG_RejReason 8072
#define TAG_PresentRetNum 8027
#define TAG_NextFlag 8095
int COutThread::QueryFundStatus()  // 这个作为单记录返回的查询例子
{
   char fvalue[256];
   int rtn;
   double dv;
   double dv1;
   char reqid[40];

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854051);  // 查询客户资金状态
   BCSetStringFieldByName(m_bc,0,"scust_no", g_KSFTS.GetOperator());          //操作员
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(m_ugdata.sClientID,fvalue)); // 客户号	sholder_ac_no
   // scurrency_type='',币种
   BCSetStringFieldByName(m_bc,0,"scurrency_type","1"); // RMB
   // sstatus0='',生成合计
   BCSetStringFieldByName(m_bc,0,"sstatus0","0"); // 不要合计


   UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
   // 先为各类应答做好准备

   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);  // 这里由于对重复请求无所谓，所以选用了TryCallSvr
   if (rtn<0)
   {
      SQLDebugLog(5101,"Fail to CallFTSSvr(854051,%s):%d-%s",
         m_ugdata.sClientID,rtn,fvalue);
      return(ReturnRequestRejected(944,fvalue));
   }
   BCGetRetCode(m_bc,&rtn);
   if (rtn!=0)
   {
      BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
      mytrim(fvalue);
      return(ReturnRequestRejected(rtn,fvalue));
   }
   BCGetRecordCount(m_bc,&rtn);
   if (rtn<=0)
   {
      sprintf(fvalue,"Not found the account:%s",m_ugdata.sClientID);
      return(ReturnRequestRejected(951,fvalue));
   }

   // 先从原始请求中获得 RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
      strcpy(reqid,"NONE");
   }

   // 应该是单记录的:
   FIXDataReset(m_fh,NULL,NULL,NULL);
   strcpy(fvalue,"KSFA"); // Fund status Return
   FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);

   //UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为应答
   FIXDataAddTag(m_fh,TAG_SenderCompID,m_ugdata.sSenderCompID,0);
   FIXDataAddTag(m_fh,TAG_TargetCompID,m_ugdata.sTargetCompID,0);
   FIXDataAddTag(m_fh,TAG_DeliverToCompID,m_ugdata.sDeliverToCompID,0);
   FIXDataAddTag(m_fh,TAG_OnBehalfOfCompID,m_ugdata.sOnBehalfOfCompID,0);
   FIXDataAddTag(m_fh,TAG_DeliverToSubID,m_ugdata.sDeliverToSubID,0);
   FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfSubID,0);

   FIXDataAddTag(m_fh,TAG_RequestID,reqid,0);
   FIXDataAddTag(m_fh,TAG_ClientID,m_ugdata.sClientID,0);
   FIXDataAddTag(m_fh,TAG_SecurityExchange,m_ugdata.sSecurityExchange,0);
   if (m_ugdata.sCurrency[0])
   {
      FIXDataAddTag(m_fh,TAG_Currency,m_ugdata.sCurrency,0);
   }
   if (m_ugdata.sAccount[0])
   {
      FIXDataAddTag(m_fh,TAG_Account,m_ugdata.sAccount,0);
   }
   FIXDataAddTag(m_fh,TAG_PresentRetNum,"1",0);
   FIXDataAddTag(m_fh,TAG_NextFlag,"N",0);  // 因为是单记录

   // damt3='',上日结存
   BCGetStringFieldByName(m_bc,0,"damt3",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8081,fvalue,0);

   // damt26='',可用资金
   BCGetStringFieldByName(m_bc,0,"damt26",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8084,fvalue,0);
   
   dv = atof(fvalue);
   // ?? 可取资金 就简单的 用可用资金代替吧:
   // 可用 - 质押金额 - 浮动 - 平仓 - 信用金额
   BCGetDoubleFieldByName(m_bc,0,"damt19",&dv1);
   dv -= dv1;

   BCGetDoubleFieldByName(m_bc,0,"damt8",&dv1);
   dv -= dv1;

   BCGetDoubleFieldByName(m_bc,0,"damt11",&dv1);
   dv -= dv1;

   BCGetDoubleFieldByName(m_bc,0,"damt31",&dv1);
   dv -= dv1;

   sprintf(fvalue,"%.2lf",dv);
   FIXDataAddTag(m_fh,8098,fvalue,0);

   FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));

   return(g_KSFTS.SendToFIXSvr(m_fixmsg)); 
}


int COutThread::ReturnRequestRejected(int rejcode, char *errmsg)
{
   char fvalue[256];
   int rtn;
   char reqid[40];

   // 先从原始请求中获得 RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
      strcpy(reqid,"NONE");
   }

   FIXDataReset(m_fh,NULL,NULL,NULL);
   strcpy(fvalue,"KSRJ");   
   FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);   
   // UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
   FIXDataAddTag(m_fh,TAG_SenderCompID,m_ugdata.sSenderCompID,0);
   FIXDataAddTag(m_fh,TAG_TargetCompID,m_ugdata.sTargetCompID,0);
   FIXDataAddTag(m_fh,TAG_DeliverToCompID,m_ugdata.sDeliverToCompID,0);
   FIXDataAddTag(m_fh,TAG_OnBehalfOfCompID,m_ugdata.sOnBehalfOfCompID,0);
   FIXDataAddTag(m_fh,TAG_DeliverToSubID,m_ugdata.sDeliverToSubID,0);
   FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfSubID,0);

   FIXDataAddTag(m_fh,TAG_RequestID,reqid,0);
   
   sprintf(fvalue,"%d",rejcode);
   FIXDataAddTag(m_fh,TAG_RejReason,fvalue,0);
   FIXDataAddTag(m_fh,TAG_TEXT,errmsg,0);

   FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}

int COutThread::QueryPositionStatus()  // 这个作为多记录返回的查询例子
{
   char fvalue[256];
   int rtn;
   int i,n;
   char *ps2;
   char reqid[40];
   
   // 先从原始请求中获得 RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
      strcpy(reqid,"NONE");
   }

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854048);  // 查询客户持仓状态
   BCSetStringFieldByName(m_bc,0,"scust_no", g_KSFTS.GetOperator());          //操作员
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(m_ugdata.sClientID,fvalue)); // 客户号	sholder_ac_no
   // 交易编码	sholder_ac_no2
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no2",m_ugdata.sAccount); 
   // 合约号	scust_auth
   BCSetStringFieldByName(m_bc,0,"scust_auth",m_ugdata.sSymbol);
   // 买卖方向	sstatus2
   switch (m_ugdata.sSide[0])
   {
   case '1':
   case '2':
      fvalue[0] = m_ugdata.sSide[0]-1;  // 1->0;2->1 
      fvalue[1] = '\0';
      BCSetStringFieldByName(m_bc,0,"sstatus2",fvalue);
      break;
   default:
      // 不限
      break;
   }

   // sstatus3='',是否不输出合计标记--1不输出小计和合计；其它值则输出小计和合计
   BCSetStringFieldByName(m_bc,0,"sstatus3","1");
   // sstatus0='',汇总标记--0不输出汇总，1输出汇总
   BCSetStringFieldByName(m_bc,0,"sstatus0","0");

   UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
   // 先为各类应答做好准备
   
   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);  // 这里由于对重复请求无所谓，所以选用了TryCallSvr
   if (rtn<0)
   {
      SQLDebugLog(4801,"Fail to CallFTSSvr(854048,%s):%d-%s",
         m_ugdata.sClientID,rtn,fvalue);
      return(ReturnRequestRejected(944,fvalue));
   }

   // 可能为多记录的结果集
   n = 1;
   FIXDataReset(m_fh,NULL,NULL,NULL);
   strcpy(fvalue,"KSPA"); // Position status Return
   FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);

   // UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
   FIXDataAddTag(m_fh,TAG_SenderCompID,m_ugdata.sSenderCompID,0);
   FIXDataAddTag(m_fh,TAG_TargetCompID,m_ugdata.sTargetCompID,0);
   FIXDataAddTag(m_fh,TAG_DeliverToCompID,m_ugdata.sDeliverToCompID,0);
   FIXDataAddTag(m_fh,TAG_OnBehalfOfCompID,m_ugdata.sOnBehalfOfCompID,0);
   FIXDataAddTag(m_fh,TAG_DeliverToSubID,m_ugdata.sDeliverToSubID,0);
   FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfSubID,0);
   
   FIXDataAddTag(m_fh,TAG_RequestID,reqid,0);

   FIXDataAddTag(m_fh,TAG_ClientID,m_ugdata.sClientID,0);
   ps2 = fvalue+100;
   do 
   {
      BCGetRetCode(m_bc,&rtn);
      if (rtn!=0)
      {
         BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         return(ReturnRequestRejected(rtn,fvalue));
      }
      BCGetRecordCount(m_bc,&rtn);
      if (rtn<=0)
      {
         sprintf(fvalue,"Not found Position Data of %s",m_ugdata.sClientID);
         return(ReturnRequestRejected(948,fvalue));
      }

      for (i=0;i<rtn;++i)
      {
         // 注意下面都要用FIXDataUpdateTag, 而不是FIXDataAddTag
         sprintf(fvalue,"%d",n++);
         FIXDataUpdateTag(m_fh,-1,TAG_PresentRetNum,fvalue,0);
         if (i+1<rtn || BCHaveNextPack(m_bc))
            strcpy(fvalue,"Y");
         else
            strcpy(fvalue,"N");
         FIXDataUpdateTag(m_fh,-1,TAG_NextFlag,fvalue,0);
         //       smarket_code='',交易所代码  -- 需要转换为标准交易所代码
         BCGetStringFieldByName(m_bc,i,"smarket_code",fvalue,sizeof(fvalue));
         STRNCPY(m_ugdata.sSecurityExchange,g_KSFTS.GetExchange(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_SecurityExchange,m_ugdata.sSecurityExchange,0);
         // sholder_ac_no2='',交易编码
         BCGetStringFieldByName(m_bc,i,"sholder_ac_no2",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_Account,fvalue,0);
         //  sstock_code='',品种代码  "al"
         BCGetStringFieldByName(m_bc,i,"sstock_code",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         for (ps2=fvalue;*ps2;++ps2);
         //ps2 = strstr(fvalue,"");  // 找到结束位置，以后加“交割期”，最后生成合约号
         //  sdate1='',交割期
         BCGetStringFieldByName(m_bc,i,"sdate1",ps2,100);
         mytrim(ps2);
         FIXDataUpdateTag(m_fh,-1,TAG_Symbol,fvalue,0);
         // sstatus4='',投保标记
         BCGetStringFieldByName(m_bc,i,"sstatus4",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_HedgeFlag,fvalue,0);
         // sstatus2='',买卖方向
         BCGetStringFieldByName(m_bc,i,"sstatus2",m_ugdata.sSide,sizeof(m_ugdata.sSide));
         m_ugdata.sSide[0] += 1;  // '0'->'1'; '1'->'2' 
         FIXDataUpdateTag(m_fh,-1,TAG_Side,m_ugdata.sSide,0);
         // lvol5='',持仓手数
         BCGetStringFieldByName(m_bc,i,"lvol5",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,53,fvalue,0);  // Quantity
         if (m_ugdata.sSide[0]=='1')
         {
            // 买持仓:
            FIXDataUpdateTag(m_fh,-1,704,fvalue,0); // Long Quantity
            strcpy(fvalue,"0");
            FIXDataUpdateTag(m_fh,-1,705,fvalue,0); // Short Quantity
         }
         else
         {
            // 卖持仓:
            FIXDataUpdateTag(m_fh,-1,705,fvalue,0); // Short Quantity
            strcpy(fvalue,"0");
            FIXDataUpdateTag(m_fh,-1,704,fvalue,0); // Long Quantity
         }
         // damt23='',最新价
         BCGetStringFieldByName(m_bc,i,"damt23",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_Price,fvalue,0);  // Price
         // damt21='',持仓均价: 为昨结算价
         // damt26='',开仓均价  -- 即实际的持仓成本价
         BCGetStringFieldByName(m_bc,i,"damt26",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_AvgPx,fvalue,0);  // AvxPx
         // 暂时先给出这些TAG域了。
         //////////////////////////////////////////////////////////////////////////
         FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));
         g_KSFTS.SendToFIXSvr(m_fixmsg);
      }
      if (!BCHaveNextPack(m_bc))
         break; // 结束了，没有后续数据记录了
      if (g_KSFTS.CallNext(m_bc,fvalue)<0)
      {
         return(ReturnRequestRejected(944,fvalue));  // 用拒绝来结束
      }
   } while (1);
   return(n);
}


