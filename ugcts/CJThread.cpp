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
   // �Ƚ�m_bs�󶨵�BCCSVR�ĳɽ�������Ϣ�����
   g_KSCTS.BindCJRecv(m_bs);
   SQLDebugLog(300,"CJThread Start!");
   while (g_KSCTS.IsRunning() && m_lastcxlchk>0)
   {
      rtn = BSReceiveMsg(m_bs,eMsg,sizeof(eMsg));
      // ��ʵ���ﶼ���������ڲ��Ƿ��������յ����
      // �ο��ɽ����յĹ��ܺŶ����ⲿ���͹�������Ϣ����������������:
      // ��������ͨ��ֱ�Ӳ�ѯ���ݿ��е���������ɵ�!
      switch (rtn)
      {
      case 3:   // a request
         SQLDebugLog(31001,"Received a Request,Not support R-A mode yet.");
      case 1:  // PM0 Message:
      case 2:  // PM1 Message:
         // �����������гɽ�/����/�����ܾ���Ϣ������
         if (g_KSCTS.m_CJSJRY<=0)
         {
            CheckBSData(); // ͨ�����BCCSVR���յ������ݰ������ж�Ӧ�ĳɽ�/����/�����ܾ���Ϣ
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
         // �Լ�����һ�¿���:
         rtn = g_KSCTS.FetchCJHBRecords(); // ��ʵ�ڲ��������ݵ�ʱ�򣬽���ص���HaveARealDone
      }
      if (rtn<=0)  // �пյ�ʱ��ȥ����һ�³����ܾ������
      {
         // ������û��ɶ����:
         if (m_lastcxlchk>0 && time(NULL)>m_lastcxlchk+1)
         {
            // 2 ����һ��:
            //PUTLINE("Before CheckCxlReject()");
            rtn = g_KSCTS.CheckCxlReject();  // ���ﴥ����鳷���ܾ������
            //PUTLINE("After CheckCxlReject()");
            m_lastcxlchk = time(NULL);
         }
         if (rtn<=0)
            delayms = 10;  // ����Ϣһ�°ɣ�������Windows�£��ƺ�û��ɶ����
      }
      else
      {
         m_cjjs += rtn;  // �������ظ������
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


// ������: CCJThread::CheckBSData
// ���  : ������ 2012-6-6 21:54:56
// ����  : ����m_bs�е���Ϣ���ݽ��ж�Ӧ�Ĳ���
// ����  : int : 0 - ��������Ϣ��1 - ������һ����Ϣ
int CCJThread::CheckBSData()
{
   int rtn = 0;
   T_REAL_DONE tRealDone;
   if (BSGetRecordCount(m_bs)<=0)
      return(0);
   switch (BSGetRequestType(m_bs))
   {
   case 400106: // �ɽ���¼:
      /* 400106 -- �ɽ� �� ���� ����
      scust_no='',�ͻ���
      smarket_code='',�г�����
      semp_no='',ϯλ��
      sholder_ac_no='',�걨�ɶ��ʺ�
      sstock_code='',֤ȯ���� ��SEC_CODE
      damt0='',�ɽ��۸�  �� DONE_PRICE
      lvol0='',�ɽ�����  �� DONE_VOL
      sserial0='',���̺�ͬ��
      sdate0='',�ɽ�����
      stime0='',�ɽ�ʱ�� HH:MM:SS
      lserial0='',�ɽ����
      sholder_type='',����  ��BS
      sholder_type2='',ҵ�����
      semp='',ְ������
      scust_auth='',��ע
      sstation0='',�³ɽ���� �� DONE_NO
      sserial1='',ί�к�ͬ�� �� REAL_DONE�е�CONTRACT_NO
      stime1='',����ʱ�� HH:MM:SS
      */
      tRealDone.lDONE_ID = -2; // ��ʾ���ü���ظ��ɽ���ֱ�Ӹ�FS
      tRealDone.sCONTRACT_NO[0]='\0'; // �ǳ���Ҫ����Ҫ����
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
   case 400107: // �������ܾ�����Ϣ����ͨ�����̻�ȡ��
      /*
      scust_no='',�ͻ���
      smarket_code='',�г�����
      semp_no='',ϯλ��
      sserial0='',���̺�ͬ��
      sdate0='',�ɽ�����
      scust_auth='',��ע
      sserial1='',ί�к�ͬ�� �� CONTRACT_NO      
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
