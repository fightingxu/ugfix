/********************************************************************
	created:	2011/09/30
	created:	30:9:2011   11:00
	filename: 	C:\dd\projects\FIXIII\UGate\ugfts\CJThread.cpp
	file path:	C:\dd\projects\FIXIII\UGate\ugfts
	file base:	CJThread
	file ext:	cpp
	author:		CHENYH
	
	purpose:	��ģ����UGFTS�н��ղ�����KSFTS���͹����ĸ����йسɽ��ر���
   ��Ϣ����һЩ�����ĵĹ��ܣ���ֱ�Ӳ��ú��Է�ʽ���ڱ�Ҫ��ʱ���ٽ�����ӡ�
   2011/09/30:
      Ŀǰ��ע�Ĺ��ܺŰ�����
      854020: ������ί�лر� - ��Ҫ��עί�б��ܾ��������

  
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
   // �Ƚ�m_bs�󶨵�BCCSVR�ĳɽ�������Ϣ�����
   g_KSFTS.BindCJRecv(m_bs);
   SQLDebugLog(300,"CJThread Start!");
   while (g_KSFTS.IsRunning() && m_lasttm>0)
   {
      rtn = BSReceiveMsg(m_bs,eMsg,sizeof(eMsg));
      // ��ʵ���ﶼ���������ڲ��Ƿ��������յ����
      // �ο��ɽ����յĹ��ܺŶ����ⲿ���͹�������Ϣ����������������:
      // ��������ͨ��ֱ�Ӳ�ѯ���ݿ��е���������ɵ�!
      switch (rtn)
      {
      case 3:   // a request
         SQLDebugLog(31001,"Received a Request,Not support R-A mode yet.");
         break;
      case 1:  // PM0 Message:
      case 2:  // PM1 Message:
         // �����������гɽ��򳷵��ɹ�����Ϣ������
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
   case 854020:  // ������ί�лر�
      return(F854020(emsg));
   case 854021:
      return(F854021(emsg));
   case 854024:
      return(F854024(emsg));
   default:
      // �����Ķ���ʱû���ã�����֪������Щ����¼һ�£�
      SQLDebugLog(3000,"CJThread received PM: RequestType=%d, Skipped!",
         BSGetRequestType(m_bs));
      return(-100);
   }
}

// ������ί�лر�
int CCJThread::F854020(char *emsg)
{
   char sWTH[40];
   char fvalue[256];
   memset(&m_ugdata,0,sizeof(m_ugdata));
   GetWTH(sWTH);
   // ί��״̬	sstatus0
   BSGetStringFieldByName(m_bs,0,"sstatus0",fvalue,sizeof(fvalue));
   if (g_KSFTS.GetClOrdID(sWTH,m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID)!=1)
   {
      // û���ҵ���Ӧ�Ķ���:
      SQLDebugLog(30201,"854020: Not found ClOrdID for WTH(%s):Status(%s)",sWTH,fvalue);
      return(-1);
   }
   char sMkt_code[5]={0}; 
   switch (fvalue[0])
   {
   case 'q': // 'q', '���ھܾ�'
      STRNCPY(m_ugdata.sClOrdID,m_ugdata.sOrigClOrdID); // �Բ���ԭ�¶����ı��
      sprintf(fvalue,"R-%s",sWTH);
      STRNCPY(m_ugdata.sExecID,fvalue);
      strcpy(m_ugdata.sOrdStatus,"8"); // 8 - Rejected
      strcpy(m_ugdata.sExecType,"8"); // 8 - Rejected
      /*********************************************************
      �����������ڻ�����ϵͳ���п���һ�������ʣ��������OrderQty�Ͳ�����
      ��FS�ڲ�����8,8��Ϣ������������Щ��������Ϣ�������ڲ�����Ϊ׼
      // �걨����	lvol0
      BSGetStringFieldByName(m_bs,0,"lvol0",fvalue,sizeof(fvalue));
      m_ugdata.dOrderQty = atoi(fvalue);
      *********************************************************/
      m_ugdata.dLeavesQty = 0;          // ǿ��Ϊ0
      // ��ע	saddr2  nnnnnn--????:XXXXXXXXXXX
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
//    case 'a': // 'a', '�Ѿ�����' 2010-8-30 17:02:33 �����ڻ�Ҫ��������֪ͨ��Ϣ
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

   // ����������һ�㲻��ȫ׼ȷ��������������ͬϯλ��KSFTS����Ļ����£�
   // �����ϣ�����ͬ�ģ�ί�к�+�ͻ���+ϯλ�ţ�����һ�����Ǳ��ӿ��е�ί��

   // ί�к�	lserial0
   BSGetIntFieldByName(m_bs,0,"lserial0",&lv);

   // �ͻ���	sholder_ac_no
   BSGetStringFieldByName(m_bs,0,"sholder_ac_no",pcustno,100);
   mytrim(pcustno);
   // ϯλ��	sserial2
   BSGetStringFieldByName(m_bs,0,"sserial2",pseat,100);
   mytrim(pseat);
   
   g_KSFTS.GetWTH(lv,pcustno,pseat,sWTH);

//    // �µ�ϯλ	vsvarstr1
//    BSGetStringFieldByName(m_bs,0,"vsvarstr1",fvalue,sizeof(fvalue));
//    mytrim(fvalue);
//    strcpy(sWTH+i,fvalue);
   return(sWTH);
}

// �����������ر�
int CCJThread::F854021(char *emsg)
{
   char sWTH[40];
   char fvalue[256];
   long lvol0,lvol1;
   memset(&m_ugdata,0,sizeof(m_ugdata));
   GetWTH(sWTH);
   if (g_KSFTS.GetClOrdID(sWTH,m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID)!=1)
   {
      // û���ҵ���Ӧ�Ķ���:
      SQLDebugLog(30201,"854020: Not found ClOrdID for WTH(%s)",sWTH);
      return(-1);
   }
   STRNCPY(m_ugdata.sOrderID,sWTH);
   // ��Լ	scust_auth
   BSGetStringFieldByName(m_bs,0,"scust_auth",m_ugdata.sSymbol,sizeof(m_ugdata.sSymbol));
   mytrim(m_ugdata.sSymbol);
   // ί��״̬	sstatus0
   BSGetStringFieldByName(m_bs,0,"sstatus0",fvalue,sizeof(fvalue));
   mytrim(fvalue);
   char sMkt_code[5]={0}; 
   switch (fvalue[0])
   {
   case 'a':   // 'a', '�Ѿ�����'
   case 'p':   // 'p', '���ֳɽ�'
   case 'c':   // 'c', 'ȫ���ɽ�'
      // ���඼���ڳ����ܾ�
      m_ugdata.lCxlRejReason = 99; // Other
      // ��ע	saddr2  nnnnnn--????:XXXXXXXXXXX
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
   case 'b':   // 'b', '���ɲ���'
   case 'd':   // 'd', '�Ѿ�����'
      // ��Щ�ǳ����ɹ� ExecType=4������£�ֻҪ
      // ��OrigClOrdID,ClOrdID,dOrderQty-dCumQtyΪ�����ɹ��������͹���
      BSGetIntFieldByName(m_bs,0,"lvol0",&lvol0);  // �걨����	lvol0
      BSGetIntFieldByName(m_bs,0,"lvol1",&lvol1);  // �ɽ�����	lvol1
      m_ugdata.dOrderQty = lvol0;
      m_ugdata.dCumQty = lvol1;
      strcpy(m_ugdata.sOrdStatus,"4");
      strcpy(m_ugdata.sExecType,"4");  // �����ɹ���
      // ����һ��ExecID:
      sprintf(fvalue,"C-%s",sWTH);  // ��sWTH��Ϊ�˶��WTH�ĳ����ر���Ҫ�������Ͳ����ظ��ˣ��Ǻ�
      STRNCPY(m_ugdata.sExecID,fvalue);
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSFTS.SendToFIXSvr(m_fixmsg));
   default:   // �����Ͳ�����
      return(-10);
   }
}

// �������ɽ��ر�
int CCJThread::F854024(char *emsg)
{
   char sWTH[40];
   char fvalue[256];
   long  lvol0;
   memset(&m_ugdata,0,sizeof(m_ugdata));
   GetWTH(sWTH);
   if (g_KSFTS.GetClOrdID(sWTH,m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID)!=1)
   {
      // û���ҵ���Ӧ�Ķ���:
      SQLDebugLog(30201,"854020: Not found ClOrdID for WTH(%s)",sWTH);
      // ˽����ˮ��	scust_limit
//       BSGetStringFieldByName(m_bs,0,"scust_limit",m_ugdata.sOrigClOrdID,sizeof(m_ugdata.sOrigClOrdID));
//       mytrim(m_ugdata.sOrigClOrdID);
      return(-1); // ��Ȼû�У��ǾͲ��Ǳ��ӿڵĶ����ɽ�����
   }
   STRNCPY(m_ugdata.sClOrdID,m_ugdata.sOrigClOrdID);  // �Գɽ�������ԭ�¶�����
   STRNCPY(m_ugdata.sOrderID,sWTH);
   // ��Լ	scust_auth
   BSGetStringFieldByName(m_bs,0,"scust_auth",m_ugdata.sSymbol,sizeof(m_ugdata.sSymbol));
   mytrim(m_ugdata.sSymbol);
   // ί��״̬	sstatus0
   BSGetStringFieldByName(m_bs,0,"sstatus0",fvalue,sizeof(fvalue));
   mytrim(fvalue);
   strcpy(m_ugdata.sOrdStatus,"1");
   strcpy(m_ugdata.sExecType,"F"); // Trading - filled
   // �ɽ�����	lvol0
   BSGetIntFieldByName(m_bs,0,"lvol0",&lvol0);
   m_ugdata.dLastQty = lvol0;
   // �ɽ��۸�	damt0
   BSGetDoubleFieldByName(m_bs,0,"damt0",&(m_ugdata.dLastPx));
#if 0
   // ����Ŀǰ��ʱ��ֻ���ò�ί�����ָ��ģ����ظ������鷳
   // �ɽ�������	lvol1
   BSGetIntFieldByName(m_bs,0,"lvol1",lvol0);
   m_ugdata.dCumQty = lvol0;
   // ʣ������	lvol2
   BSGetIntFieldByName(m_bs,0,"lvol2",lvol0);
   m_ugdata.dLeavesQty = lvol0;
   m_ugdata.dOrderQty = m_ugdata.dCumQty+m_ugdata.dLeavesQty;
   // �ɽ�����	damt5
   BSGetDoubleFieldByName(m_bs,0,"damt5",&(m_ugdata.dAvgPx));
#endif

   // �������ɽ���	sserial0
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
   // ���˲飬�ƺ�ֻ��854042	��ѯ���ճɽ�������ܱȽϺ��ʣ���ֻ�ָܻ��ɽ�����
   return(g_KSFTS.RestoreCJ(emsg)>=0);
}

void CCJThread::ToStopCJProcess()
{
   m_lasttm = -1;
}


