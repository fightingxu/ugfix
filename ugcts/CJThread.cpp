// CJThread.cpp: implementation of the CCJThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "CJThread.h"
#include "KSCTS.h"
#include "ugate.h"

V_REALDONE m_VRealDone;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCJThread::CCJThread()
{
   m_ID = -1;
}

CCJThread::~CCJThread()
{

}

int CCJThread::Initialize(char *eMsg)
{
   m_bs = BSNewHandle(g_KSCTS.GetXPackFile());
   if (m_bs==NULL)
   {
      sprintf(eMsg,"Fail to BSNewHandle(%s)!",g_KSCTS.GetXPackFile());
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
   int delayms=1;
   m_lastcxlchk = time(NULL);
   m_cjjs = 0;
   // 先将m_bs绑定到BCCSVR的成交接收消息句柄上
   g_KSCTS.BindCJRecv(m_bs);
   SQLDebugLog(300,"CJThread Start!");
   while (g_KSCTS.IsRunning() && m_lastcxlchk>0)
   {
      rtn = BSReceiveMsg(m_bs,eMsg,sizeof(eMsg));
      // 其实这里都不关心其内部是否有数据收到与否，
      // 何况成交接收的功能号都是外部推送过来的消息，不处理请求数据:
      // 具体数据通过直接查询数据库中的数据来完成的!
      switch (rtn)
      {
      case 3:   // a request
         SQLDebugLog(31001,"Received a Request,Not support R-A mode yet.");
      case 1:  // PM0 Message:
      case 2:  // PM1 Message:
         // 哈哈，看来有成交/撤单/撤单拒绝消息过来了
         if (g_KSCTS.m_CJSJRY<=0)
         {
            CheckBSData(); // 通过检查BCCSVR接收到的数据包，进行对应的成交/撤单/撤单拒绝消息
         }
         break;
      case -1: // No Message received.
      case 0:  // Forward reply processed...
         if (delayms>0)
            mysleep(delayms);
         break;
      default:
         SQLDebugLog(3101,"BSReceiveMsg (Error) return %d-%s",rtn,eMsg);
         mysleep(100);
         break;
      }
      if (g_KSCTS.m_CJSJRY>0)
      {
         // 自己来查一下看看:
         rtn = g_KSCTS.FetchCJHBRecords(); // 其实内部在有数据的时候，将会回调到HaveARealDone
      }
      if (rtn<=0)  // 有空的时候，去处理一下撤单拒绝的情况
      {
         // 唉，都没有啥事情:
         if (m_lastcxlchk>0 && time(NULL)>m_lastcxlchk+1)
         {
            // 2 秒检查一次:
            //PUTLINE("Before CheckCxlReject()");
            rtn = g_KSCTS.CheckCxlReject();  // 这里触发检查撤单拒绝的情况
            //PUTLINE("After CheckCxlReject()");
            m_lastcxlchk = time(NULL);
         }
         if (rtn<=0)
            delayms = 10;  // 多休息一下吧，不够在Windows下，似乎没有啥区别
      }
      else
      {
         m_cjjs += rtn;  // 可能有重复处理的
         delayms = -1;
      }
   }
   SQLDebugLog(301,"CJThread Stop!");
   return(0);
}

void CCJThread::ToStopCJProcess()
{
   m_lastcxlchk = -1;
}


bool CCJThread::Restore(const char *partnerid, char *emsg)
{
   g_KSCTS.FetchCJHBRecords();
   g_KSCTS.CheckCxlReject();
   return(true);
}


// 函数名: CCJThread::CheckBSData
// 编程  : 陈永华 2012-6-6 21:54:56
// 描述  : 根据m_bs中的消息数据进行对应的操作
// 返回  : int : 0 - 无意义消息；1 - 处理了一条消息
int CCJThread::CheckBSData()
{
   int rtn = 0;
   T_REAL_DONE tRealDone;
   if (BSGetRecordCount(m_bs)<=0)
      return(0);
   switch (BSGetRequestType(m_bs))
   {
   case 400106: // 成交记录:
      /* 400106 -- 成交 或 撤单 数据
      scust_no='',客户号
      smarket_code='',市场代码
      semp_no='',席位号
      sholder_ac_no='',申报股东帐号
      sstock_code='',证券代码 即SEC_CODE
      damt0='',成交价格  即 DONE_PRICE
      lvol0='',成交数量  即 DONE_VOL
      sserial0='',报盘合同号
      sdate0='',成交日期
      stime0='',成交时间 HH:MM:SS
      lserial0='',成交编号
      sholder_type='',买卖  即BS
      sholder_type2='',业务代码
      semp='',职工代码
      scust_auth='',备注
      sstation0='',新成交编号 即 DONE_NO
      sserial1='',委托合同号 即 REAL_DONE中的CONTRACT_NO
      stime1='',处理时间 HH:MM:SS
      */
      tRealDone.lDONE_ID = -2; // 表示不用检查重复成交，直接给FS
      tRealDone.sCONTRACT_NO[0]='\0'; // 非常重要，需要保护
      BSGetStringFieldByName(m_bs,0,"sserial0",tRealDone.sCONTRACT_NO,sizeof(tRealDone.sCONTRACT_NO));
      mytrim(tRealDone.sCONTRACT_NO);
      BSGetStringFieldByName(m_bs,0,"sstock_code",tRealDone.sSEC_CODE,sizeof(tRealDone.sSEC_CODE));
      //mytrim(tRealDone.sSEC_CODE);
      BSGetStringFieldByName(m_bs,0,"sholder_type",tRealDone.sBS,sizeof(tRealDone.sBS));
      BSGetDoubleFieldByName(m_bs,0,"sstation0",&(tRealDone.dDONE_NO));
      BSGetIntFieldByName(m_bs,0,"lvol0",&(tRealDone.lDONE_VOL));
      BSGetDoubleFieldByName(m_bs,0,"damt0",&(tRealDone.dDONE_PRICE));
      BSGetStringFieldByName(m_bs,0,"stime0",tRealDone.sDONE_TIME,sizeof(tRealDone.sDONE_TIME));
      BSGetStringFieldByName(m_bs,0,"stime1",tRealDone.sOCCUR_TIME,sizeof(tRealDone.sOCCUR_TIME));
      g_KSCTS.HaveARealDone(&tRealDone);
      rtn = 1;
      break;
   case 400107: // 撤单被拒绝的消息，是通过报盘获取的
      /*
      scust_no='',客户号
      smarket_code='',市场代码
      semp_no='',席位号
      sserial0='',报盘合同号
      sdate0='',成交日期
      scust_auth='',备注
      sserial1='',委托合同号 即 CONTRACT_NO      
      */
      BSGetStringFieldByName(m_bs,0,"sserial1",tRealDone.sCONTRACT_NO,sizeof(tRealDone.sCONTRACT_NO));
      mytrim(tRealDone.sCONTRACT_NO);
      g_KSCTS.HaveACancelReject(tRealDone.sCONTRACT_NO);
      rtn = 1;
      break;
   default:
      SQLDebugLog(31002,"Undefined RequestType=%d in CJThread",BSGetRequestType(m_bs));
      break;
   }
   return(rtn);
}
