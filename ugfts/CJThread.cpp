/********************************************************************
	created:	2011/09/30
	created:	30:9:2011   11:00
	filename: 	C:\dd\projects\FIXIII\UGate\ugfts\CJThread.cpp
	file path:	C:\dd\projects\FIXIII\UGate\ugfts
	file base:	CJThread
	file ext:	cpp
	author:		CHENYH
	
	purpose:	本模块是UGFTS中接收并处理KSFTS推送过来的各类有关成交回报等
   消息；对一些不关心的功能，则直接采用忽略方式，在必要的时候，再进行添加。
   2011/09/30:
      目前关注的功能号包括：
      854020: 交易所委托回报 - 主要关注委托被拒绝的情况等

  
*********************************************************************/
// CJThread.cpp: implementation of the CCJThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "ugate.h"
#include "CJThread.h"
#include "KSFTS.h"
#include "GetErrInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCJThread::CCJThread()
{

}

CCJThread::~CCJThread()
{

}

int CCJThread::Initialize(char *eMsg)
{
   m_bs = BSNewHandle(g_KSFTS.GetXPackFile());
   if (m_bs==NULL)
   {
      sprintf(eMsg,"Fail to BSNewHandle(%s)!",g_KSFTS.GetXPackFile());
      return(-1);
   }
   return(0);
}

void CCJThread::Exit()
{
   if (m_bs!=NULL)
   {
      BSDeleteHandle(m_bs);
      m_bs = NULL;
   }
}

#ifdef _MSC_VER
void CJProcess(void *pv)
#else
void *CJProcess(void *pv)
#endif
{
   CCJThread *pCJThread = (CCJThread *)pv;
   pCJThread->Run();
}


bool CCJThread::ToStartCJProcess(char *emsg)
{
   if (StartThread(CJProcess,this)<0)
   {
      strcpy(emsg,"Fail to start CJProcess!");
      return(false);
   }
   return(true);
}

int CCJThread::Run()
{
   char eMsg[256];
   int rtn;
   m_lasttm = time(NULL);
   m_cjjs = 0;
   // 先将m_bs绑定到BCCSVR的成交接收消息句柄上
   g_KSFTS.BindCJRecv(m_bs);
   SQLDebugLog(300,"CJThread Start!");
   while (g_KSFTS.IsRunning() && m_lasttm>0)
   {
      rtn = BSReceiveMsg(m_bs,eMsg,sizeof(eMsg));
      // 其实这里都不关心其内部是否有数据收到与否，
      // 何况成交接收的功能号都是外部推送过来的消息，不处理请求数据:
      // 具体数据通过直接查询数据库中的数据来完成的!
      switch (rtn)
      {
      case 3:   // a request
         SQLDebugLog(31001,"Received a Request,Not support R-A mode yet.");
         break;
      case 1:  // PM0 Message:
      case 2:  // PM1 Message:
         // 哈哈，看来有成交或撤单成功的消息过来了
         if (ToProcessPM(eMsg)>=0)
         {
            m_lasttm = time(NULL);
            ++m_cjjs;
         }
         break;
      case -1: // No Message received.
      case 0:  // Forward reply processed...
         break;
      default:
         SQLDebugLog(3101,"BSReceiveMsg (Error) return %d-%s",rtn,eMsg);
         mysleep(100);
         break;
      }

   }
   SQLDebugLog(301,"CJThread Stop!");
   return(0);
}

int CCJThread::ToProcessPM(char *emsg)
{
   switch (BSGetRequestType(m_bs))
   {
   case 854020:  // 交易所委托回报
      return(F854020(emsg));
   case 854021:
      return(F854021(emsg));
   case 854024:
      return(F854024(emsg));
   default:
      // 其他的都暂时没有用，但不知道有哪些，记录一下？
      SQLDebugLog(3000,"CJThread received PM: RequestType=%d, Skipped!",
         BSGetRequestType(m_bs));
      return(-100);
   }
}

// 交易所委托回报
int CCJThread::F854020(char *emsg)
{
   char sWTH[40];
   char fvalue[256];
   memset(&m_ugdata,0,sizeof(m_ugdata));
   GetWTH(sWTH);
   // 委托状态	sstatus0
   BSGetStringFieldByName(m_bs,0,"sstatus0",fvalue,sizeof(fvalue));
   if (g_KSFTS.GetClOrdID(sWTH,m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID)!=1)
   {
      // 没有找到对应的订单:
      SQLDebugLog(30201,"854020: Not found ClOrdID for WTH(%s):Status(%s)",sWTH,fvalue);
      return(-1);
   }
   char sMkt_code[5]={0}; 
   switch (fvalue[0])
   {
   case 'q': // 'q', '场内拒绝'
      STRNCPY(m_ugdata.sClOrdID,m_ugdata.sOrigClOrdID); // 仍采用原新订单的编号
      sprintf(fvalue,"R-%s",sWTH);
      STRNCPY(m_ugdata.sExecID,fvalue);
      strcpy(m_ugdata.sOrdStatus,"8"); // 8 - Rejected
      strcpy(m_ugdata.sExecType,"8"); // 8 - Rejected
      /*********************************************************
      可是由于在期货交易系统中有可能一单分两笔，这样这个OrderQty就不对了
      且FS内部，对8,8消息，并不在意这些数量等信息，以其内部数据为准
      // 申报手数	lvol0
      BSGetStringFieldByName(m_bs,0,"lvol0",fvalue,sizeof(fvalue));
      m_ugdata.dOrderQty = atoi(fvalue);
      *********************************************************/
      m_ugdata.dLeavesQty = 0;          // 强制为0
      // 备注	saddr2  nnnnnn--????:XXXXXXXXXXX
      BSGetStringFieldByName(m_bs,0,"saddr2",fvalue,sizeof(fvalue));
	  BSGetStringFieldByName(m_bs,0,"smarket_code",sMkt_code,sizeof(sMkt_code));
      mytrim(fvalue);
	  mytrim(sMkt_code);
	  SetErrCodeInfo(sMkt_code[0],fvalue, "Rejected by Exchange,ErrNo=", m_ugdata.vsmess);
      /*if (atoi(fvalue)!=0)
      {
         sprintf(m_ugdata.vsmess,"Rejected by Exchange,ErrNo=%s",fvalue);
      }
      else
      {
         sprintf(m_ugdata.vsmess,"Rejected by Exchange,%s",fvalue);
      }*/
      break;
//    case 'a': // 'a', '已经报入' 2010-8-30 17:02:33 国联期货要求给出这个通知消息
//       break;
   default:
      return(0);
   }
   STRNCPY(m_ugdata.sOrderID,sWTH);
   STRNCPY(m_ugdata.sClOrdID,m_ugdata.sOrigClOrdID);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}

char * CCJThread::GetWTH(char *sWTH)
{
   long lv;
   char fvalue[256];
   char *pcustno,*pseat;
   pcustno = fvalue;
   pseat = fvalue+100;

   // 这里稍稍有一点不完全准确的隐患，就是在同席位多KSFTS共享的环境下，
   // 理论上，有相同的：委托号+客户好+席位号，但不一定就是本接口中的委托

   // 委托号	lserial0
   BSGetIntFieldByName(m_bs,0,"lserial0",&lv);

   // 客户号	sholder_ac_no
   BSGetStringFieldByName(m_bs,0,"sholder_ac_no",pcustno,100);
   mytrim(pcustno);
   // 席位号	sserial2
   BSGetStringFieldByName(m_bs,0,"sserial2",pseat,100);
   mytrim(pseat);
   
   g_KSFTS.GetWTH(lv,pcustno,pseat,sWTH);

//    // 下单席位	vsvarstr1
//    BSGetStringFieldByName(m_bs,0,"vsvarstr1",fvalue,sizeof(fvalue));
//    mytrim(fvalue);
//    strcpy(sWTH+i,fvalue);
   return(sWTH);
}

// 交易所撤单回报
int CCJThread::F854021(char *emsg)
{
   char sWTH[40];
   char fvalue[256];
   long lvol0,lvol1;
   memset(&m_ugdata,0,sizeof(m_ugdata));
   GetWTH(sWTH);
   if (g_KSFTS.GetClOrdID(sWTH,m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID)!=1)
   {
      // 没有找到对应的订单:
      SQLDebugLog(30201,"854020: Not found ClOrdID for WTH(%s)",sWTH);
      return(-1);
   }
   STRNCPY(m_ugdata.sOrderID,sWTH);
   // 合约	scust_auth
   BSGetStringFieldByName(m_bs,0,"scust_auth",m_ugdata.sSymbol,sizeof(m_ugdata.sSymbol));
   mytrim(m_ugdata.sSymbol);
   // 委托状态	sstatus0
   BSGetStringFieldByName(m_bs,0,"sstatus0",fvalue,sizeof(fvalue));
   mytrim(fvalue);
   char sMkt_code[5]={0}; 
   switch (fvalue[0])
   {
   case 'a':   // 'a', '已经报入'
   case 'p':   // 'p', '部分成交'
   case 'c':   // 'c', '全部成交'
      // 这类都属于撤单拒绝
      m_ugdata.lCxlRejReason = 99; // Other
      // 备注	saddr2  nnnnnn--????:XXXXXXXXXXX
      BSGetStringFieldByName(m_bs,0,"saddr2",fvalue,sizeof(fvalue));
	  BSGetStringFieldByName(m_bs,0,"smarket_code",sMkt_code,sizeof(sMkt_code));
	  mytrim(fvalue);
	  mytrim(sMkt_code);
	  SetErrCodeInfo(sMkt_code[0],fvalue, "Rejected by Exchange,ErrNo=", m_ugdata.vsmess);
      /*if (atoi(fvalue)!=0)
      {
         sprintf(m_ugdata.vsmess,"Rejected by Exchange,ErrNo=%s",fvalue);
      }
      else
      {
         sprintf(m_ugdata.vsmess,"Rejected by Exchange,%s",fvalue);
      }*/
      UG_CancelRejectFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSFTS.SendToFIXSvr(m_fixmsg));
   case 'b':   // 'b', '部成部撤'
   case 'd':   // 'd', '已经撤销'
      // 这些是撤单成功 ExecType=4的情况下，只要
      // 有OrigClOrdID,ClOrdID,dOrderQty-dCumQty为撤单成功数量，就够了
      BSGetIntFieldByName(m_bs,0,"lvol0",&lvol0);  // 申报手数	lvol0
      BSGetIntFieldByName(m_bs,0,"lvol1",&lvol1);  // 成交数量	lvol1
      m_ugdata.dOrderQty = lvol0;
      m_ugdata.dCumQty = lvol1;
      strcpy(m_ugdata.sOrdStatus,"4");
      strcpy(m_ugdata.sExecType,"4");  // 撤单成功，
      // 还有一个ExecID:
      sprintf(fvalue,"C-%s",sWTH);  // 用sWTH是为了多个WTH的撤单回报需要，这样就不会重复了，呵呵
      STRNCPY(m_ugdata.sExecID,fvalue);
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSFTS.SendToFIXSvr(m_fixmsg));
   default:   // 其他就不管了
      return(-10);
   }
}

// 交易所成交回报
int CCJThread::F854024(char *emsg)
{
   char sWTH[40];
   char fvalue[256];
   long  lvol0;
   memset(&m_ugdata,0,sizeof(m_ugdata));
   GetWTH(sWTH);
   if (g_KSFTS.GetClOrdID(sWTH,m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID)!=1)
   {
      // 没有找到对应的订单:
      SQLDebugLog(30201,"854020: Not found ClOrdID for WTH(%s)",sWTH);
      // 私有流水号	scust_limit
//       BSGetStringFieldByName(m_bs,0,"scust_limit",m_ugdata.sOrigClOrdID,sizeof(m_ugdata.sOrigClOrdID));
//       mytrim(m_ugdata.sOrigClOrdID);
      return(-1); // 既然没有，那就不是本接口的订单成交数据
   }
   STRNCPY(m_ugdata.sClOrdID,m_ugdata.sOrigClOrdID);  // 对成交，则用原新订单号
   STRNCPY(m_ugdata.sOrderID,sWTH);
   // 合约	scust_auth
   BSGetStringFieldByName(m_bs,0,"scust_auth",m_ugdata.sSymbol,sizeof(m_ugdata.sSymbol));
   mytrim(m_ugdata.sSymbol);
   // 委托状态	sstatus0
   BSGetStringFieldByName(m_bs,0,"sstatus0",fvalue,sizeof(fvalue));
   mytrim(fvalue);
   strcpy(m_ugdata.sOrdStatus,"1");
   strcpy(m_ugdata.sExecType,"F"); // Trading - filled
   // 成交手数	lvol0
   BSGetIntFieldByName(m_bs,0,"lvol0",&lvol0);
   m_ugdata.dLastQty = lvol0;
   // 成交价格	damt0
   BSGetDoubleFieldByName(m_bs,0,"damt0",&(m_ugdata.dLastPx));
#if 0
   // 由于目前暂时还只是用查委托来恢复的，怕重复，更麻烦
   // 成交总手数	lvol1
   BSGetIntFieldByName(m_bs,0,"lvol1",lvol0);
   m_ugdata.dCumQty = lvol0;
   // 剩余手数	lvol2
   BSGetIntFieldByName(m_bs,0,"lvol2",lvol0);
   m_ugdata.dLeavesQty = lvol0;
   m_ugdata.dOrderQty = m_ugdata.dCumQty+m_ugdata.dLeavesQty;
   // 成交均价	damt5
   BSGetDoubleFieldByName(m_bs,0,"damt5",&(m_ugdata.dAvgPx));
#endif

   // 交易所成交号	sserial0
   BSGetStringFieldByName(m_bs,0,"sserial0",fvalue,sizeof(fvalue));
   mytrim(fvalue);
   lvol0 = strlen(fvalue);
   fvalue[lvol0++]='-';
   strcpy(fvalue+lvol0,sWTH);
   STRNCPY(m_ugdata.sExecID,fvalue);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}

bool CCJThread::Restore(const char *partnerid, char *emsg)
{
   // 经核查，似乎只有854042	查询当日成交这个功能比较合适，但只能恢复成交部分
   return(g_KSFTS.RestoreCJ(emsg)>=0);
}

void CCJThread::ToStopCJProcess()
{
   m_lasttm = -1;
}


