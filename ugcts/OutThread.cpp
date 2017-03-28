// OutThread.cpp: implementation of the COutThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "ugate.h"
#include "MsgDataList.h"
#include "OutThread.h"
#include "KSCTS.h"
#include "GetErrInfo.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 在使用ExtCall的时候，如果通讯平台或目标服务端异常
#define MIN_XCALLERR 9985
//#define MAX_XCALLERR 9988  // V2.73以上
#define MAX_XCALLERR 10000  // under 2.72

COutThread::COutThread()
{
   m_omsgcnt = 0;
}

COutThread::~COutThread()
{

}

int COutThread::Initialize(int id, char *emsg)
{
   m_ID = id;
   m_bc = BCNewHandle(g_KSCTS.GetXPackFile());
   if (m_bc==NULL)
   {
      sprintf(emsg,"Fail to BCNewHandle(%s)!",g_KSCTS.GetXPackFile());
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

#ifdef _MSC_VER
void OutProcess(void *pv)
#else
void *OutProcess(void *pv)
#endif
{
   COutThread *pOutThread = (COutThread *)pv;
   pOutThread->Run();
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

int COutThread::Run()
{
   int rtn;
   SQLDebugLog(400,"OutThread[%d] Start",m_ID);
   while (g_KSCTS.IsRunning() && m_omsgcnt>=0)
   {
      //rtn = UG_GetOutMsg(g_KSCTS.m_PartnerID,10,m_fixmsg);
      rtn = g_KSCTS.GetOutMsg(m_fixmsg);
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
   SQLDebugLog(50001,"Unsupported MsgType=%s @ CTS-OUTThread!",m_ugdata.sMsgType);
   return(-1);
}

int COutThread::HandleNewOrderSingle()
{
   if (m_ugdata.sOrderID[0]!='\0' 
      && g_KSCTS.m_Status<FS_OPEN)
   {
      // 则说明属于恢复阶段的，并且已经被处理过了，Skipped
      return(0);
   }

   STRNCPY(m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID);  // 后面在查询KSCTS中的ENTRUST表有用
   if (m_ugdata.sOrdType[0]=='Z')
   {
      // 非交易类订单， 目前只是支持EC、ER： ETF申购赎回
      if (strcmp(m_ugdata.sNonTradingOrdType,"EC")==0)
      {
         // EC=ETF申购订单
         return(HandleKSCTSETFRequest('D'));
      }
      if (strcmp(m_ugdata.sNonTradingOrdType,"ER")==0)
      {
         // ER=ETF赎回订单
         return(HandleKSCTSETFRequest('E')); // E = Redeem (e.g. ETF)[赎回]
      }
      // ....
      SQLDebugLog(70101,"Unsupported (OrdType='Z') NonTradingOrdType(TAG8526=%s) :%s",
         m_ugdata.sNonTradingOrdType,m_fixmsg);
      return(-7011);      
   }
   switch (m_ugdata.sSide[0])
   {
   case '1':   // buy
   case '2':   // sell
      return(HandleNewOrderSingleNormal());
   case 'D':   // D = Subscribe (e.g. ETF)[申购]
   case 'E':   // E = Redeem (e.g. ETF)[赎回]
      return(HandleKSCTSETFRequest(m_ugdata.sSide[0]));
   default:
      SQLDebugLog(70102,"Unsupported Side(TAG54=%s) :%s",
         m_ugdata.sSide,m_fixmsg);
      return(-7012);      
   }
}

int COutThread::ReturnOrderReject()
{
   strcpy(m_ugdata.sMsgType,"8");
   strcpy(m_ugdata.sExecType,"8");
   UG_UGDataReturn(&m_ugdata);
   m_ugdata.dCumQty = m_ugdata.dLeavesQty = m_ugdata.dLastQty = 0;
   m_ugdata.dAvgPx = m_ugdata.dLastPx = 0;
   sprintf(m_ugdata.sExecID,"%sREJ",m_ugdata.sClOrdID);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSCTS.SendToFIXSvr(m_fixmsg));
}



int COutThread::HandleNewOrderSingleNormal()
{
   char fvalue[256];
   char *pv;
   int rtn;
   // 先检查数据库中是否已经有本记录了 - 以防止重复处理
   if ((rtn=g_KSCTS.GetDBEntrustStatus(&m_ugdata))>0)
   {
      // 那就不用做了，直接返回
      SQLDebugLog(7011,"Duplicated Order:%s",m_fixmsg);
      return(0);
   }
   if (rtn<0)
      return(-1);

   // 向KSCTS发起432001请求：
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,423001);
   // !!!!! KSCTS的新委托的时候，就直接用ClOrdID作为合同号，以方便后续处理!!! 但在设置KSCTS对手参数的时候，要采用 "nnn%07d"
   BCSetStringFieldByName(m_bc,0,"sorder0",m_ugdata.sClOrdID); // 合同号码 sorder0[11] !!! 这里直接用sClOrdID

   pv =(char *)UG_GetIMarket(m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
   if (pv==NULL)
   {
      m_ugdata.lOrdRejReason = 0;
      sprintf(m_ugdata.vsmess,"Unsupported IMarket(%s,%s,%s)",
         m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
      return(ReturnOrderReject());
   }

   char sOMSMarketCode[8] = {0};
   STRNCPY(sOMSMarketCode, pv);
   BCSetStringFieldByName(m_bc,0,"smarket_code",pv);   // smarket_code='1301',市场代码☆
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',发生营业部☆
   // 兼容申万约定的ClientID: <cust_no>-<子账号>:
   GetSubString(m_ugdata.sClientID,'-',0,fvalue,sizeof(fvalue),NULL);
   BCSetStringFieldByName(m_bc,0,"scust_no",fvalue);     // scust_no='',客户号☆
   pv = strstr(m_ugdata.sClientID,"-");
   if (pv!=NULL)
   {
      BCSetStringFieldByName(m_bc,0,"sorder1",pv);// sorder1='',交易签名(缺省为'')不处理
      sprintf(fvalue,"%s:%s",pv,m_ugdata.sClOrdID);
      BCSetStringFieldByName(m_bc,0,"snote",fvalue); // snote='',备注信息  (ClientID):(ClOrderID)
   }
   if (m_ugdata.sOnBehalfOfSubID[0])
   {
      /* ****** Updated by CHENYH at 2011-9-25 16:14:23 ****** 
      通过FS的转交，原OnBehalfOfCompID -> OnBehalfOfSubID了
      pv = g_KSCTS.GetHWGSDM(m_ugdata.sOnBehalfOfCompID);
      */
      PUTLINE(m_ugdata.sOnBehalfOfSubID);
      pv = g_KSCTS.GetHWGSDM(m_ugdata.sOnBehalfOfSubID);
      if (pv!=NULL)
      {
         PUTLINE(pv);
         BCSetStringFieldByName(m_bc,0,"snation_code",pv); // 海外公司代码 snation_code
      }
   }
   if (m_ugdata.sAccount[0])
   {
      BCSetStringFieldByName(m_bc,0,"sholder_ac_no",m_ugdata.sAccount); // sholder_ac_no='',证券账号☆
   }
   BCSetIntFieldByName(m_bc,0,"lvol0",(int)(m_ugdata.dOrderQty+MIN_QTY)); // lvol0='',委托数量☆

   BCSetStringFieldByName(m_bc,0,"sstock_code",m_ugdata.sSymbol); // sstock_code='',证券代码☆

   BCSetStringFieldByName(m_bc,0,"sstat_type",m_ugdata.sSide); // sstat_type='',买卖类型☆(1买2卖5转股7预买8预卖0基金申购9基金赎回Q行权 (k预受要约l解除要约(深圳)) U-基金合并 P-基金分拆)
   BCSetDoubleFieldByName(m_bc,0,"damt0",m_ugdata.dPrice); // damt0='',委托价格☆
   BCSetStringFieldByName(m_bc,0,"sbank_code2",g_KSCTS.m_WTFSx); // sbank_code2='',委托方式☆
   BCSetStringFieldByName(m_bc,0,"sstation0","KSFIXIII");   // sstation0='',委托来源☆
   /************************************************************************/
   /* 2011/6/27 为交易所扩展业务而支持的子业务分类：
   sroom_no='',委托子业务☆
   (000 正常委托 
   002 深对手方最优价格委托（市价1）
   003 深本方最优价格委托（市价2）
   004 深即时成交剩余撤销委托（市价3）
   005 深沪最优五档并撤销委托(市价4) FAK / IOC
   006 深全额成交或撤销委托（市价5）FOK
   007 沪最优五档并转限价委托（市价6）  OrdType=K
   z10 定价委托 
   z20 意向申报 
   z30 配对成交 
   z40 成交确认)
   
     40	OrdType	订单类型:	必填
     1 = Market 市价单	
     2 = Limit 限价单	
     3 = Stop 止损市价单	
     4 = Stop limit 止损限价单	
     x = 本方最优价	
     y = 对方最优价	
     K = 市价转限价   
   */

   // 顾金国修改于20120328
   switch (m_ugdata.sOrdType[0])
   {
   case 'K': 
	   BCSetStringFieldByName(m_bc,0, "sroom_no","007");  //   委托子业务 (上交所)
	   break;
   case 'x':
	   BCSetStringFieldByName(m_bc,0,"sroom_no","003");  //   委托子业务 (深交所)
	   break;
   case 'y':
	   BCSetStringFieldByName(m_bc,0, "sroom_no","002");  //   委托子业务 (深交所)
	   break;
   case '1': // 1 = Market 市价单
	   switch (m_ugdata.sTimeInForce[0])
	   {
	   case '4': // 4 = Fill or Kill (FOK)
		   BCSetStringFieldByName(m_bc, 0,"sroom_no","006");  //   委托子业务 (深交所)
		   break;
	   case '3': // 3 = IOC (FAK)
		   BCSetStringFieldByName(m_bc,0,"sroom_no","005");  //   委托子业务 (深交所，上交所)
		   break;
	   case '0': // 0 = Day (or session)
	   case '\0':
		   // 2012/2/28 10:37:32 新增，为了那些老外的市价委托，缺省指定如下模式
		   // 1 = Market 市价单 007 沪最优五档并转限价委托（市价6）/ 002 深对手方最优价格委托（市价1）
		   switch (sOMSMarketCode[0])
		   {
		   case '2':
		   case '4':
			   // 深圳
			   BCSetStringFieldByName(m_bc, 0, "sroom_no","002");  //   委托子业务 (深交所)
			   break;
		   default:
			   // 上海
			   BCSetStringFieldByName(m_bc,0, "sroom_no","007");  //   委托子业务 (深交所)
			   break;
		   }
		   break;
		   default:
			   break;
	   }
	   break;
	   case '2':
	   case '\0':
		   if (m_ugdata.sTimeInForce[0]=='\0'||m_ugdata.sTimeInForce[0]=='0')
		   {
			   BCSetStringFieldByName(m_bc, 0, "sroom_no","000");  //   000 正常委托
			   break;
		   }
	   default:
		   break;
   }
   //顾金国修改于20120328

#if 0
   switch (m_ugdata.sTimeInForce[0])
   {
   case '4': // 4 = Fill or Kill (FOK)
      BCSetStringFieldByName(m_bc,0,"sroom_no","006");  //   委托子业务
      break;
   case '3': // 3 = IOC (FAK)
      BCSetStringFieldByName(m_bc,0,"sroom_no","005");  //   委托子业务
      break;
   default:
      switch (m_ugdata.sOrdType[0])
      {
      case 'K': 
         BCSetStringFieldByName(m_bc,0,"sroom_no","007");  //   委托子业务
         break;
      case 'x':
         BCSetStringFieldByName(m_bc,0,"sroom_no","003");  //   委托子业务
         break;
      case 'y':
         BCSetStringFieldByName(m_bc,0,"sroom_no","002");  //   委托子业务
         break;
      default:
         // ????????
         break;
      }
      break;
   }  
#endif

   /************************************************************************/
   strcpy(m_ugdata.sOrdStatus,"A"); // as PendingNew
//    if (g_KSCTS.InsertFIXEntrust(&m_ugdata)<0)
//    {
//       m_ugdata.lOrdRejReason = 0;
//       strcpy(m_ugdata.vsmess,"Fail to Insert FIX_Entrust");
//       return(ReturnOrderReject());
//    }
   //g_KSCTS.CallSvr(m_bc,fvalue);
   // 不管三七二十一，都去后台查一下数据:
   //rtn = 0;
   rtn=g_KSCTS.CallSvr(m_bc,fvalue);

   
   //通讯错误，需要查询
   if(rtn<0 || (BCGetRetCode(m_bc,&rtn) && (rtn>=MIN_XCALLERR && rtn<=MAX_XCALLERR)))
   {
	   //查询不到
	   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
	   {
		  //则说明下单没有成功

		  strcpy(fvalue,"Network or KSCTS irregular!");
		  rtn = 9988;

	   }
	   else
	   {
		   rtn =0;   //认为成功
	   }
   }
   //下单成功，判断返回码
   else
   {
	   if(rtn!=0 && rtn!=2366)
		   BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));	
	   else
		   rtn =0;   //认为成功
   }

   if (rtn!=0)
   {
	   m_ugdata.lOrdRejReason = 0;
	   sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue);
	   SetErrCodeInfo(STOCK_MCODE,m_ugdata.vsmess, "KSCTS Rejected,ErrNo=", m_ugdata.vsmess);
	   return(ReturnOrderReject());
   }
   
   /*
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // 则说明下单没有成功
      if (BCGetRetCode(m_bc,&rtn) && rtn!=0)
      {
         BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
      }
      else
      {
         strcpy(fvalue,"Network or KSCTS irregular!");
         rtn = 9988;
      }
   }
   else 
   {
      // 这类委托失败，可以让CJThread去完成
      // 检查委托状态清单:
//       switch (m_ugdata.sOrdStatus[0])
//       {
//       case '':
//          break;
//       default:
//          break;
//       }
   }
   if (rtn!=0)
   {
      m_ugdata.lOrdRejReason = 0;
      sprintf(m_ugdata.vsmess,"KSCTS Rejected,ErrNo=%d:%s",rtn,fvalue);
      return(ReturnOrderReject());
   }
   */
   // 下单成功:
   sprintf(m_ugdata.sExecID,"1_%s",m_ugdata.sClOrdID);  // 这里和常规的成交执行编号特殊一些 '_',防止重复
   strcpy(m_ugdata.sExecType,"0");  // as NewConfirmation return.
   strcpy(m_ugdata.sOrderID,m_ugdata.sClOrdID);
   m_ugdata.dLastPx = m_ugdata.dLastQty = m_ugdata.dCumQty = m_ugdata.dAvgPx = 0;
   m_ugdata.dLeavesQty = m_ugdata.dOrderQty;
   UG_UGDataReturn(&m_ugdata);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSCTS.SendToFIXSvr(m_fixmsg));
}

// ETF的申购与赎回
int COutThread::HandleKSCTSETFRequest(char cSide)
{
   char fvalue[256];
   char *pv;
   int rtn;
   // 先检查数据库中是否已经有本记录了 - 以防止重复处理
   if ((rtn=g_KSCTS.GetDBEntrustStatus(&m_ugdata))>0)
   {
      // 那就不用做了，直接返回
      SQLDebugLog(7011,"Duplicated Order:%s",m_fixmsg);
      return(0);
   }
   if (rtn<0)
      return(-1);

   // 向KSCTS发起130225- ETF基金申购/赎回
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,130225);
   // !!!!! KSCTS的新委托的时候，就直接用ClOrdID作为合同号，以方便后续处理!!! 但在设置KSCTS对手参数的时候，要采用 "nnn%07d"
   BCSetStringFieldByName(m_bc,0,"sorder2",m_ugdata.sClOrdID); // 合同号码 sorder0[11] !!! 这里直接用sClOrdID

   pv =(char *)UG_GetIMarket(m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
   if (pv==NULL)
   {
      m_ugdata.lOrdRejReason = 0;
      sprintf(m_ugdata.vsmess,"Unsupported IMarket(%s,%s,%s)",
         m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
      return(ReturnOrderReject());
   }
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',发生营业部☆
   BCSetStringFieldByName(m_bc,0,"smarket_code",pv);   // smarket_code='1301',市场代码☆
   // 兼容申万约定的ClientID: <cust_no>-<子账号>:
   GetSubString(m_ugdata.sClientID,'-',0,fvalue,sizeof(fvalue),NULL);
   BCSetStringFieldByName(m_bc,0,"scust_no",fvalue);     // scust_no='',客户号☆
   pv = strstr(m_ugdata.sClientID,"-");
   if (pv!=NULL)
   {
      BCSetStringFieldByName(m_bc,0,"sorder1",pv);// sorder1='',交易签名(缺省为'')不处理
      sprintf(fvalue,"%s:%s",pv,m_ugdata.sClOrdID);
      BCSetStringFieldByName(m_bc,0,"snote",fvalue); // snote='',备注信息  (ClientID):(ClOrderID)
   }
   
   if (m_ugdata.sAccount[0])
   {
      BCSetStringFieldByName(m_bc,0,"sholder_ac_no",m_ugdata.sAccount); // sholder_ac_no='',证券账号☆
   }
   BCSetIntFieldByName(m_bc,0,"lvol0",(int)(m_ugdata.dOrderQty+MIN_QTY)); // lvol0='1000000',委托数量(申购/赎回份额)
   BCSetStringFieldByName(m_bc,0,"sstatus0",g_KSCTS.m_WTFSi); // sstatus0='',委托方式代码   ☆
   BCSetStringFieldByName(m_bc,0,"sstock_code2",m_ugdata.sSymbol);  // sstock_code2='',申购赎回代码	510051  ☆

   strcpy(fvalue,cSide=='D'?"1":"2");
   BCSetStringFieldByName(m_bc,0,"smain_flag",fvalue); // smain_flag='',买卖类别	1买入(申购)/2卖出(赎回) ☆
   
   // sdate0='',席位代码 ☆  ???
   strcpy(fvalue,"KSFIXIII");
   BCSetStringFieldByName(m_bc,0,"sstation0",fvalue);   // sstation0='',委托来源☆
   g_KSCTS.CallSvr(m_bc,fvalue);
   // 不管三七二十一，都去后台查一下数据:
   rtn = 0;
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // 则说明下单没有成功
      if (BCGetRetCode(m_bc,&rtn) && rtn!=0)
      {
         BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
      }
      else
      {
         strcpy(fvalue,"Network or KSCTS irregular!");
         rtn = 9988;
      }
   }
   else 
   {
      // 其他不考虑其失败与否了
   }
   if (rtn!=0)
   {
	  m_ugdata.lOrdRejReason = 0;
	  sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue);
	  SetErrCodeInfo(STOCK_MCODE,m_ugdata.vsmess, "KSCTS Rejected,ErrNo=", m_ugdata.vsmess);
      return(ReturnOrderReject());
   }
   // 下单成功:
   sprintf(m_ugdata.sExecID,"1_%s",m_ugdata.sClOrdID);  // 这里和常规的成交执行编号特殊一些 '_',防止重复
   strcpy(m_ugdata.sExecType,"0");  // as NewConfirmation return.
   strcpy(m_ugdata.sOrderID,m_ugdata.sClOrdID);
   m_ugdata.dLastPx = m_ugdata.dLastQty = m_ugdata.dCumQty = m_ugdata.dAvgPx = 0;
   m_ugdata.dLeavesQty = m_ugdata.dOrderQty;
   UG_UGDataReturn(&m_ugdata);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSCTS.SendToFIXSvr(m_fixmsg));
}

// 处理撤单请求:
int COutThread::HandleOrderCancelRequest()
{
   char fvalue[256];
   int rtn;
   if (g_KSCTS.m_Status<FS_OPEN)
   {
//       if (strcmp(m_ugdata.sOrderID,"NONE")==0)
//       {
//          // 为恢复阶段，并且原来本CancelRequest是被拒绝了的。
//          return(0); // Skipped
//       }
      if (m_ugdata.sOrderID[0]!='\0')
      {
         // 在恢复阶段，若有这个TAG，则说明本撤单，已经被处理，并且完毕了，
         // 因为这里不会给PendingCancel，唯一对该Cancel只有Rejected或Cancelled,也就不用恢复了。
         return(0); // Skipped
      }
   }
   // 先检查数据库中是否已经有本记录了 - 以防止重复处理
   if ((rtn=g_KSCTS.GetDBEntrustStatus(&m_ugdata))>0)
   {
      switch (m_ugdata.sOrdStatus[0])  // ENTRUST_STATUS
      {
      case '9': // /*schui 20061208 撤单作废*/
         // 这里可以再次对原委托进行撤单的那些委托状态：
         // TODO:
         break;
      default:
         //SQLDebugLog(7011,"Duplicated Cancel:%s",m_fixmsg); 由于这里也被恢复的时候调用，因此就不管了
         return(0);         
      }
   }
   if (rtn<0)
      return(-1);
   strcpy(m_ugdata.sMsgType,"D"); // 准备读取原始委托记录数据:
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // 晕!!! 原始单都没有 TAT
      m_ugdata.lCxlRejReason = 1; // 1 = Unknown order,
      strcpy(m_ugdata.sCxlRejResponseTo,"1");  // 1 = Order Cancel Request
      STRNCPY(m_ugdata.sOrdStatus,"8");  // 
      STRNCPY(m_ugdata.sExecType,"8"); 
      STRNCPY(m_ugdata.sOrderID,"NONE");
      sprintf(m_ugdata.vsmess,"Unknown Order:OrigClOrdID=%s",m_ugdata.sOrigClOrdID);
      UG_UGDataReturn(&m_ugdata);
      UG_CancelRejectFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSCTS.SendToFIXSvr(m_fixmsg));
   }
   // OK: sClientID = CUST_NO; sAccount = HOLDER_ACC_NO; sSellSide = MARKET_CODE; sOrdStatus=ENTRUST_STATUS

   m_ugdata.lCxlRejReason = 0;
   // 似乎应该对此有所区别耶:(
   switch (m_ugdata.sOrdStatus[0])
   {
   // case '0': //      0 未报
   // case '1': //      1 正报
   // case '2': //      2 已报
   // case '7': //      7 部成

   case '3': //      3 已报待撤
   case '4': //      4 部成待撤
      // 已经有撤单正在进行中:
      m_ugdata.lCxlRejReason = 3; // 3 = Order already in Pending Cancel or Pending Replace status
   case '5': //      5 部撤
   case '6': //      6 已撤（场外）
   case '8': //      8 已成
   case '9': //      9 废单
   case 'A': //      A 已撤（场内）
      // Too late to cancel:
      //  m_ugdata.lCxlRejReason = 0; // 0 = Too late to cancel
      strcpy(m_ugdata.sCxlRejResponseTo,"1");  // 1 = Order Cancel Request
      STRNCPY(m_ugdata.sOrderID,m_ugdata.sOrigClOrdID);
      UG_UGDataReturn(&m_ugdata);
      UG_CancelRejectFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSCTS.SendToFIXSvr(m_fixmsg));
   }

   // 后续结果，则由CJThread中的处理完成，这里登记一下:
   g_KSCTS.RegisterCancelOrder(m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID);
#ifdef USE_423002  // : 测试结果, 本功能太慢: 150上需要 22ms左右的， 而用 130105则只要用5ms左右; 因此不使用它
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,423002);
   BCSetStringFieldByName(m_bc,0,"scust_no",m_ugdata.sClientID);   // scust_no='',客户号   ☆
   BCSetStringFieldByName(m_bc,0,"smarket_code",m_ugdata.sSellSide);   // smarket_code='',市场代码   ☆
   BCSetStringFieldByName(m_bc,0,"lvol4",m_ugdata.sOrigClOrdID);    // lvol4='',合同号   ☆
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',发生营业部  ☆
#else
   // 向KSCTS发起130105请求：
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,130105);
   BCSetStringFieldByName(m_bc,0,"scust_no",m_ugdata.sClientID);   // scust_no='',客户号   ☆
   BCSetStringFieldByName(m_bc,0,"smarket_code",m_ugdata.sSellSide);   // smarket_code='',市场代码   ☆
   BCSetStringFieldByName(m_bc,0,"sorder0",m_ugdata.sOrigClOrdID);    // sorder0='',合同号   ☆
      // lvol1='',批号   ☆
   BCSetIntFieldByName(m_bc,0,"lvol0",1);    // lvol0='',撤单模式 lvol0 1:则按合同号，2:按批号
   BCSetIntFieldByName(m_bc,0,"lvol2",1);   // lvol2='',是否重复撤单 1==重复撤单,其他=不允许重复撤单   ☆
      // lcert_code='',委托种类 0-普通委托,1-补委托   ☆
      // lwithdraw_flag='',审核标志  ☆
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',发生营业部  ☆
   BCSetStringFieldByName(m_bc,0,"semp","SYSTEM");   // semp='',职工代码  ☆
   BCSetStringFieldByName(m_bc,0,"sstation0","KSFIXIII");   // sstation0='',网卡号  ☆
#endif
   g_KSCTS.CallSvr(m_bc,fvalue);
   // 不管三七二十一，都去后台查一下数据:
   rtn = 0; m_ugdata.lCxlRejReason = -1;
   strcpy(m_ugdata.sMsgType,"F");  // 为了查撤单记录
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // 则说明下单没有成功
      if (BCGetRetCode(m_bc,&rtn) && rtn!=0)
      {
         BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));
      }
      else
      {
         strcpy(fvalue,"Network or KSCTS irregular!");
         rtn = 9988;
      }      
   }
   else
   {
      // 这部分由成交回报部分去处理，这里先不用
//       switch (m_ugdata.sOrdStatus[0])
//       {
//       case '9': // 废单
//          rtn = atoi(m_ugdata.sExecInst); // EXCHANGE_ERR_CODE
//          strcpy(fvalue,"Cancel Rejected by OMS");
//          break;
//       }
   }

   if (rtn!=0)
   {
      // 本次撤单以拒绝返回
      g_KSCTS.ClOrderCxlDone(&m_ugdata);
      strcpy(m_ugdata.sCxlRejResponseTo,"1");  // 1 = Order Cancel Request
      m_ugdata.lCxlRejReason = 2;
      sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue);
	  SetErrCodeInfo(STOCK_MCODE,m_ugdata.vsmess, "Cancel Rejected by KSCTS,ErrNo=", m_ugdata.vsmess);
      STRNCPY(m_ugdata.sOrderID,"NONE");
      UG_UGDataReturn(&m_ugdata);
      UG_CancelRejectFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSCTS.SendToFIXSvr(m_fixmsg));
   }
   return(0);
}

bool COutThread::Restore(const char *partnerid, char *emsg)
{
   L_MSGDATA msglist; 
   L_MSGDATA::iterator it,nt;
   int rtn;
   m_omsgcnt = 0;
   rtn = UG_GetSSAllOrders(partnerid,msglist);
   if (rtn<0)
   {
      sprintf(emsg,"Fail to UG_GetSSAllOrders(%s):%d",partnerid,rtn);
      return(false);
   }
   for (it=msglist.begin();it!=msglist.end();)
   {
      if (FIXDataSetData(m_fh,it->msgbuf,it->msglen)>0
         && FIXDataGetUGData(m_fh,&m_ugdata,NULL,0)>0)
      {
         // 由于在OProcess中，已经具体防止重复处理能力，因此就直接由它来处理了
         OProcess();
      }
      nt = it++;
      msglist.erase(nt);
   }
   return(true);
}



#define TAG_RequestID 8088
#define TAG_RejReason 8072
#define TAG_PresentRetNum 8027
#define TAG_NextFlag 8095
/*
sbranch_code0=''
scurrency_type=''
scust_no='00500323'
sbank_code=''
sbank_code2='FIX'
sbank_acc=''
semp=''
sstation0='KSFIXIII'
*/
int COutThread::QueryFundStatus()  // 这个作为单记录返回的查询例子
{
   char fvalue[256];
   int rtn;
   char reqid[40];
   char sCurrency[12];

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,422101);  // 查询客户资金状态
   
   BCSetStringFieldByName(m_bc,0,"sbranch_code0", g_KSCTS.m_WTYYB);		//营业部  


   g_KSCTS.GetCurrcncy(m_ugdata.sCurrency,sCurrency,0);

   BCSetStringFieldByName(m_bc,0,"scurrency_type", sCurrency);   //币种

   BCSetStringFieldByName(m_bc,0,"scust_no", m_ugdata.sClientID);   //客户号
   BCSetStringFieldByName(m_bc,0,"sbank_code2", g_KSCTS.m_WTFSx);   //委托方式
   BCSetStringFieldByName(m_bc,0,"semp","SYSTEM");   // semp='',职工代码  ☆
   BCSetStringFieldByName(m_bc,0,"sstation0", "KSFIXIII");   //请求来源


   UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
   // 先为各类应答做好准备

   rtn = g_KSCTS.TryCallSvr(m_bc,fvalue);  // 这里由于对重复请求无所谓，所以选用了TryCallSvr
   if (rtn<0)
   {
      SQLDebugLog(5101,"Fail to CallFTSSvr(422101,%s):%d-%s",
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
   else
   {
	   BCGetStringFieldByName(m_bc,0,"scurrency_type",fvalue,sizeof(fvalue));
	   g_KSCTS.GetCurrcncy(m_ugdata.sCurrency,fvalue,1);
	   FIXDataAddTag(m_fh,TAG_Currency,m_ugdata.sCurrency,0);
   }
   if (m_ugdata.sAccount[0])
   {
      FIXDataAddTag(m_fh,TAG_Account,m_ugdata.sAccount,0);
   }
   FIXDataAddTag(m_fh,TAG_PresentRetNum,"1",0);
   FIXDataAddTag(m_fh,TAG_NextFlag,"N",0);  // 因为是单记录

   // damt0,资金余额
   BCGetStringFieldByName(m_bc,0,"damt0",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8081,fvalue,0);

   // damt1,可用资金
   BCGetStringFieldByName(m_bc,0,"damt1",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8084,fvalue,0);
   
   // damt2,可取资金
   BCGetStringFieldByName(m_bc,0,"damt2",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8098,fvalue,0);


   FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));

   return(g_KSCTS.SendToFIXSvr(m_fixmsg)); 
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
   return(g_KSCTS.SendToFIXSvr(m_fixmsg));
}

/*
 *	
 sbranch_code0=''
 scust_no='00500323'
 smarket_code=''
 sstock_code=''
 lvol0='0'
 sbank_code2='FIX'
 lvol1='0'
 */
int COutThread::QueryPositionStatus()  // 这个作为多记录返回的查询例子
{
   char fvalue[256];
   int rtn;
   int i,n;
   char *pv;
   //char *ps2;
   char reqid[40];

   // 先从原始请求中获得 RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
	   strcpy(reqid,"NONE");
   }

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,423102);  // 查询客户持仓状态

   BCSetStringFieldByName(m_bc,0,"sbranch_code0", g_KSCTS.m_WTYYB);		//营业部  
   
   BCSetStringFieldByName(m_bc,0,"scust_no", m_ugdata.sClientID);   //客户号
   //BCSetStringFieldByName(m_bc,0,"smarket_code", m_ugdata.sSecurityExchange);   //市场代码

   if(strlen(m_ugdata.sSecurityExchange) >0)
   {
   
	   pv =(char *)UG_GetIMarket(m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
	   if (pv==NULL)
	   {
		   SQLDebugLog(4801,"Unsupported IMarket(%s,%s,%s)",
			   m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
		   return(ReturnRequestRejected(944,fvalue));
		   
		   
	   }
	   BCSetStringFieldByName(m_bc,0,"smarket_code", pv);   //市场代码
   }
   else
	   BCSetStringFieldByName(m_bc,0,"smarket_code", "");   //市场代码
   BCSetStringFieldByName(m_bc,0,"sstock_code", "");   //证券代码
   BCSetIntFieldByName(m_bc,0,"lvol0", 0);   //最多返回数量
   BCSetIntFieldByName(m_bc,0,"lvol1", 0);   //是否返回合计值 1：返回合计值，其他不返回


   BCSetStringFieldByName(m_bc,0,"sbank_code2", g_KSCTS.m_WTFSx);   //委托方式

   UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
   // 先为各类应答做好准备
   
   rtn = g_KSCTS.TryCallSvr(m_bc,fvalue);  // 这里由于对重复请求无所谓，所以选用了TryCallSvr
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
	  
	  //UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
	  FIXDataAddTag(m_fh,TAG_SenderCompID,m_ugdata.sSenderCompID,0);
	  FIXDataAddTag(m_fh,TAG_TargetCompID,m_ugdata.sTargetCompID,0);
	  FIXDataAddTag(m_fh,TAG_DeliverToCompID,m_ugdata.sDeliverToCompID,0);
	  FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfCompID,0);
	  FIXDataAddTag(m_fh,TAG_DeliverToSubID,m_ugdata.sDeliverToSubID,0);
	  FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfSubID,0);
	  
	  FIXDataAddTag(m_fh,TAG_RequestID,reqid,0);
	  
	  FIXDataAddTag(m_fh,TAG_ClientID,m_ugdata.sClientID,0);
   
   
   //FIXDataAddTag(m_fh,TAG_DeliverToCompID,m_ugdata.sOnBehalfOfCompID,0);
   //ps2 = fvalue+100;
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
/*
	  FIXDataReset(m_fh,NULL,NULL,NULL);
	  FIXDataAddTag(m_fh,TAG_RequestID,fvalue,0);
	  strcpy(fvalue,"KSPA"); // Position status Return
	  FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);
	  
	  UG_UGDataReturn(&m_ugdata);  // 将m_ugdata中的几个消息传递方向反转一下，作为请求类的应答是必须的
	  FIXDataAddTag(m_fh,TAG_SenderCompID,m_ugdata.sSenderCompID,0);
	  FIXDataAddTag(m_fh,TAG_TargetCompID,m_ugdata.sTargetCompID,0);
	  FIXDataAddTag(m_fh,TAG_DeliverToCompID,m_ugdata.sDeliverToCompID,0);
	  FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfCompID,0);
	  FIXDataAddTag(m_fh,TAG_DeliverToSubID,m_ugdata.sDeliverToSubID,0);
	  FIXDataAddTag(m_fh,TAG_OnBehalfOfSubID,m_ugdata.sOnBehalfOfSubID,0);
	  
	  FIXDataAddTag(m_fh,TAG_RequestID,reqid,0);
	  
	  FIXDataAddTag(m_fh,TAG_ClientID,m_ugdata.sClientID,0);
*/
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
         //STRNCPY(m_ugdata.sSecurityExchange,g_KSFTS.GetExchange(fvalue));

		 if(strcmp(fvalue,"1" )==0 || strcmp(fvalue,"3" )==0)
			STRNCPY(m_ugdata.sSecurityExchange,"XSHG");
		 else
			STRNCPY(m_ugdata.sSecurityExchange,"XSHE");
         FIXDataUpdateTag(m_fh,-1,TAG_SecurityExchange,m_ugdata.sSecurityExchange,0);

		 //股东账号
         BCGetStringFieldByName(m_bc,i,"sholder_ac_no",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_Account,fvalue,0);


		 //客户号
		 FIXDataUpdateTag(m_fh,-1,TAG_ClientID,m_ugdata.sClientID,0);

         //证券代码
         BCGetStringFieldByName(m_bc,i,"sstock_code",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_Symbol,fvalue,0);

		 /*余额(加上当日成交)*/
		 BCGetStringFieldByName(m_bc,i,"lvol6",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,53,fvalue,0);  //53  Quantity

		 /*买入平均价格*/
		 BCGetStringFieldByName(m_bc,i,"damt4",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_AvgPx,fvalue,0);

		 
		 // damt23='',最新价
         BCGetStringFieldByName(m_bc,i,"damt10",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_Price,fvalue,0);  // Price
         

         // 暂时先给出这些TAG域了。
         //////////////////////////////////////////////////////////////////////////
         FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));
         g_KSCTS.SendToFIXSvr(m_fixmsg);
      }
      if (!BCHaveNextPack(m_bc))
         break; // 结束了，没有后续数据记录了
      if (g_KSCTS.CallNext(m_bc,fvalue)<0)
      {
         return(ReturnRequestRejected(944,fvalue));  // 用拒绝来结束
      }
   } while (1);
   return(n);
}
