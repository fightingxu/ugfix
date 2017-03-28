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

// ��ʹ��ExtCall��ʱ�����ͨѶƽ̨��Ŀ�������쳣
#define MIN_XCALLERR 9985
//#define MAX_XCALLERR 9988  // V2.73����
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
         // �ޣ�����������
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
	   return(QueryFundStatus());  // ���Ϊ����¼��ѯ��������
   if (strcmp(m_ugdata.sMsgType,"KSPR")==0)
	   return(QueryPositionStatus()); // ���Ϊ���¼��ѯ��������
   SQLDebugLog(50001,"Unsupported MsgType=%s @ CTS-OUTThread!",m_ugdata.sMsgType);
   return(-1);
}

int COutThread::HandleNewOrderSingle()
{
   if (m_ugdata.sOrderID[0]!='\0' 
      && g_KSCTS.m_Status<FS_OPEN)
   {
      // ��˵�����ڻָ��׶εģ������Ѿ���������ˣ�Skipped
      return(0);
   }

   STRNCPY(m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID);  // �����ڲ�ѯKSCTS�е�ENTRUST������
   if (m_ugdata.sOrdType[0]=='Z')
   {
      // �ǽ����ඩ���� Ŀǰֻ��֧��EC��ER�� ETF�깺���
      if (strcmp(m_ugdata.sNonTradingOrdType,"EC")==0)
      {
         // EC=ETF�깺����
         return(HandleKSCTSETFRequest('D'));
      }
      if (strcmp(m_ugdata.sNonTradingOrdType,"ER")==0)
      {
         // ER=ETF��ض���
         return(HandleKSCTSETFRequest('E')); // E = Redeem (e.g. ETF)[���]
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
   case 'D':   // D = Subscribe (e.g. ETF)[�깺]
   case 'E':   // E = Redeem (e.g. ETF)[���]
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
   // �ȼ�����ݿ����Ƿ��Ѿ��б���¼�� - �Է�ֹ�ظ�����
   if ((rtn=g_KSCTS.GetDBEntrustStatus(&m_ugdata))>0)
   {
      // �ǾͲ������ˣ�ֱ�ӷ���
      SQLDebugLog(7011,"Duplicated Order:%s",m_fixmsg);
      return(0);
   }
   if (rtn<0)
      return(-1);

   // ��KSCTS����432001����
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,423001);
   // !!!!! KSCTS����ί�е�ʱ�򣬾�ֱ����ClOrdID��Ϊ��ͬ�ţ��Է����������!!! ��������KSCTS���ֲ�����ʱ��Ҫ���� "nnn%07d"
   BCSetStringFieldByName(m_bc,0,"sorder0",m_ugdata.sClOrdID); // ��ͬ���� sorder0[11] !!! ����ֱ����sClOrdID

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
   BCSetStringFieldByName(m_bc,0,"smarket_code",pv);   // smarket_code='1301',�г������
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',����Ӫҵ����
   // ��������Լ����ClientID: <cust_no>-<���˺�>:
   GetSubString(m_ugdata.sClientID,'-',0,fvalue,sizeof(fvalue),NULL);
   BCSetStringFieldByName(m_bc,0,"scust_no",fvalue);     // scust_no='',�ͻ��š�
   pv = strstr(m_ugdata.sClientID,"-");
   if (pv!=NULL)
   {
      BCSetStringFieldByName(m_bc,0,"sorder1",pv);// sorder1='',����ǩ��(ȱʡΪ'')������
      sprintf(fvalue,"%s:%s",pv,m_ugdata.sClOrdID);
      BCSetStringFieldByName(m_bc,0,"snote",fvalue); // snote='',��ע��Ϣ  (ClientID):(ClOrderID)
   }
   if (m_ugdata.sOnBehalfOfSubID[0])
   {
      /* ****** Updated by CHENYH at 2011-9-25 16:14:23 ****** 
      ͨ��FS��ת����ԭOnBehalfOfCompID -> OnBehalfOfSubID��
      pv = g_KSCTS.GetHWGSDM(m_ugdata.sOnBehalfOfCompID);
      */
      PUTLINE(m_ugdata.sOnBehalfOfSubID);
      pv = g_KSCTS.GetHWGSDM(m_ugdata.sOnBehalfOfSubID);
      if (pv!=NULL)
      {
         PUTLINE(pv);
         BCSetStringFieldByName(m_bc,0,"snation_code",pv); // ���⹫˾���� snation_code
      }
   }
   if (m_ugdata.sAccount[0])
   {
      BCSetStringFieldByName(m_bc,0,"sholder_ac_no",m_ugdata.sAccount); // sholder_ac_no='',֤ȯ�˺š�
   }
   BCSetIntFieldByName(m_bc,0,"lvol0",(int)(m_ugdata.dOrderQty+MIN_QTY)); // lvol0='',ί��������

   BCSetStringFieldByName(m_bc,0,"sstock_code",m_ugdata.sSymbol); // sstock_code='',֤ȯ�����

   BCSetStringFieldByName(m_bc,0,"sstat_type",m_ugdata.sSide); // sstat_type='',�������͡�(1��2��5ת��7Ԥ��8Ԥ��0�����깺9�������Q��Ȩ (kԤ��ҪԼl���ҪԼ(����)) U-����ϲ� P-����ֲ�)
   BCSetDoubleFieldByName(m_bc,0,"damt0",m_ugdata.dPrice); // damt0='',ί�м۸��
   BCSetStringFieldByName(m_bc,0,"sbank_code2",g_KSCTS.m_WTFSx); // sbank_code2='',ί�з�ʽ��
   BCSetStringFieldByName(m_bc,0,"sstation0","KSFIXIII");   // sstation0='',ί����Դ��
   /************************************************************************/
   /* 2011/6/27 Ϊ��������չҵ���֧�ֵ���ҵ����ࣺ
   sroom_no='',ί����ҵ���
   (000 ����ί�� 
   002 ����ַ����ż۸�ί�У��м�1��
   003 ������ż۸�ί�У��м�2��
   004 �ʱ�ɽ�ʣ�೷��ί�У��м�3��
   005 ������嵵������ί��(�м�4) FAK / IOC
   006 ��ȫ��ɽ�����ί�У��м�5��FOK
   007 �������嵵��ת�޼�ί�У��м�6��  OrdType=K
   z10 ����ί�� 
   z20 �����걨 
   z30 ��Գɽ� 
   z40 �ɽ�ȷ��)
   
     40	OrdType	��������:	����
     1 = Market �м۵�	
     2 = Limit �޼۵�	
     3 = Stop ֹ���м۵�	
     4 = Stop limit ֹ���޼۵�	
     x = �������ż�	
     y = �Է����ż�	
     K = �м�ת�޼�   
   */

   // �˽���޸���20120328
   switch (m_ugdata.sOrdType[0])
   {
   case 'K': 
	   BCSetStringFieldByName(m_bc,0, "sroom_no","007");  //   ί����ҵ�� (�Ͻ���)
	   break;
   case 'x':
	   BCSetStringFieldByName(m_bc,0,"sroom_no","003");  //   ί����ҵ�� (���)
	   break;
   case 'y':
	   BCSetStringFieldByName(m_bc,0, "sroom_no","002");  //   ί����ҵ�� (���)
	   break;
   case '1': // 1 = Market �м۵�
	   switch (m_ugdata.sTimeInForce[0])
	   {
	   case '4': // 4 = Fill or Kill (FOK)
		   BCSetStringFieldByName(m_bc, 0,"sroom_no","006");  //   ί����ҵ�� (���)
		   break;
	   case '3': // 3 = IOC (FAK)
		   BCSetStringFieldByName(m_bc,0,"sroom_no","005");  //   ί����ҵ�� (������Ͻ���)
		   break;
	   case '0': // 0 = Day (or session)
	   case '\0':
		   // 2012/2/28 10:37:32 ������Ϊ����Щ������м�ί�У�ȱʡָ������ģʽ
		   // 1 = Market �м۵� 007 �������嵵��ת�޼�ί�У��м�6��/ 002 ����ַ����ż۸�ί�У��м�1��
		   switch (sOMSMarketCode[0])
		   {
		   case '2':
		   case '4':
			   // ����
			   BCSetStringFieldByName(m_bc, 0, "sroom_no","002");  //   ί����ҵ�� (���)
			   break;
		   default:
			   // �Ϻ�
			   BCSetStringFieldByName(m_bc,0, "sroom_no","007");  //   ί����ҵ�� (���)
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
			   BCSetStringFieldByName(m_bc, 0, "sroom_no","000");  //   000 ����ί��
			   break;
		   }
	   default:
		   break;
   }
   //�˽���޸���20120328

#if 0
   switch (m_ugdata.sTimeInForce[0])
   {
   case '4': // 4 = Fill or Kill (FOK)
      BCSetStringFieldByName(m_bc,0,"sroom_no","006");  //   ί����ҵ��
      break;
   case '3': // 3 = IOC (FAK)
      BCSetStringFieldByName(m_bc,0,"sroom_no","005");  //   ί����ҵ��
      break;
   default:
      switch (m_ugdata.sOrdType[0])
      {
      case 'K': 
         BCSetStringFieldByName(m_bc,0,"sroom_no","007");  //   ί����ҵ��
         break;
      case 'x':
         BCSetStringFieldByName(m_bc,0,"sroom_no","003");  //   ί����ҵ��
         break;
      case 'y':
         BCSetStringFieldByName(m_bc,0,"sroom_no","002");  //   ί����ҵ��
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
   // �������߶�ʮһ����ȥ��̨��һ������:
   //rtn = 0;
   rtn=g_KSCTS.CallSvr(m_bc,fvalue);

   
   //ͨѶ������Ҫ��ѯ
   if(rtn<0 || (BCGetRetCode(m_bc,&rtn) && (rtn>=MIN_XCALLERR && rtn<=MAX_XCALLERR)))
   {
	   //��ѯ����
	   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
	   {
		  //��˵���µ�û�гɹ�

		  strcpy(fvalue,"Network or KSCTS irregular!");
		  rtn = 9988;

	   }
	   else
	   {
		   rtn =0;   //��Ϊ�ɹ�
	   }
   }
   //�µ��ɹ����жϷ�����
   else
   {
	   if(rtn!=0 && rtn!=2366)
		   BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue));	
	   else
		   rtn =0;   //��Ϊ�ɹ�
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
      // ��˵���µ�û�гɹ�
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
      // ����ί��ʧ�ܣ�������CJThreadȥ���
      // ���ί��״̬�嵥:
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
   // �µ��ɹ�:
   sprintf(m_ugdata.sExecID,"1_%s",m_ugdata.sClOrdID);  // ����ͳ���ĳɽ�ִ�б������һЩ '_',��ֹ�ظ�
   strcpy(m_ugdata.sExecType,"0");  // as NewConfirmation return.
   strcpy(m_ugdata.sOrderID,m_ugdata.sClOrdID);
   m_ugdata.dLastPx = m_ugdata.dLastQty = m_ugdata.dCumQty = m_ugdata.dAvgPx = 0;
   m_ugdata.dLeavesQty = m_ugdata.dOrderQty;
   UG_UGDataReturn(&m_ugdata);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSCTS.SendToFIXSvr(m_fixmsg));
}

// ETF���깺�����
int COutThread::HandleKSCTSETFRequest(char cSide)
{
   char fvalue[256];
   char *pv;
   int rtn;
   // �ȼ�����ݿ����Ƿ��Ѿ��б���¼�� - �Է�ֹ�ظ�����
   if ((rtn=g_KSCTS.GetDBEntrustStatus(&m_ugdata))>0)
   {
      // �ǾͲ������ˣ�ֱ�ӷ���
      SQLDebugLog(7011,"Duplicated Order:%s",m_fixmsg);
      return(0);
   }
   if (rtn<0)
      return(-1);

   // ��KSCTS����130225- ETF�����깺/���
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,130225);
   // !!!!! KSCTS����ί�е�ʱ�򣬾�ֱ����ClOrdID��Ϊ��ͬ�ţ��Է����������!!! ��������KSCTS���ֲ�����ʱ��Ҫ���� "nnn%07d"
   BCSetStringFieldByName(m_bc,0,"sorder2",m_ugdata.sClOrdID); // ��ͬ���� sorder0[11] !!! ����ֱ����sClOrdID

   pv =(char *)UG_GetIMarket(m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
   if (pv==NULL)
   {
      m_ugdata.lOrdRejReason = 0;
      sprintf(m_ugdata.vsmess,"Unsupported IMarket(%s,%s,%s)",
         m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
      return(ReturnOrderReject());
   }
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',����Ӫҵ����
   BCSetStringFieldByName(m_bc,0,"smarket_code",pv);   // smarket_code='1301',�г������
   // ��������Լ����ClientID: <cust_no>-<���˺�>:
   GetSubString(m_ugdata.sClientID,'-',0,fvalue,sizeof(fvalue),NULL);
   BCSetStringFieldByName(m_bc,0,"scust_no",fvalue);     // scust_no='',�ͻ��š�
   pv = strstr(m_ugdata.sClientID,"-");
   if (pv!=NULL)
   {
      BCSetStringFieldByName(m_bc,0,"sorder1",pv);// sorder1='',����ǩ��(ȱʡΪ'')������
      sprintf(fvalue,"%s:%s",pv,m_ugdata.sClOrdID);
      BCSetStringFieldByName(m_bc,0,"snote",fvalue); // snote='',��ע��Ϣ  (ClientID):(ClOrderID)
   }
   
   if (m_ugdata.sAccount[0])
   {
      BCSetStringFieldByName(m_bc,0,"sholder_ac_no",m_ugdata.sAccount); // sholder_ac_no='',֤ȯ�˺š�
   }
   BCSetIntFieldByName(m_bc,0,"lvol0",(int)(m_ugdata.dOrderQty+MIN_QTY)); // lvol0='1000000',ί������(�깺/��طݶ�)
   BCSetStringFieldByName(m_bc,0,"sstatus0",g_KSCTS.m_WTFSi); // sstatus0='',ί�з�ʽ����   ��
   BCSetStringFieldByName(m_bc,0,"sstock_code2",m_ugdata.sSymbol);  // sstock_code2='',�깺��ش���	510051  ��

   strcpy(fvalue,cSide=='D'?"1":"2");
   BCSetStringFieldByName(m_bc,0,"smain_flag",fvalue); // smain_flag='',�������	1����(�깺)/2����(���) ��
   
   // sdate0='',ϯλ���� ��  ???
   strcpy(fvalue,"KSFIXIII");
   BCSetStringFieldByName(m_bc,0,"sstation0",fvalue);   // sstation0='',ί����Դ��
   g_KSCTS.CallSvr(m_bc,fvalue);
   // �������߶�ʮһ����ȥ��̨��һ������:
   rtn = 0;
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // ��˵���µ�û�гɹ�
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
      // ������������ʧ�������
   }
   if (rtn!=0)
   {
	  m_ugdata.lOrdRejReason = 0;
	  sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue);
	  SetErrCodeInfo(STOCK_MCODE,m_ugdata.vsmess, "KSCTS Rejected,ErrNo=", m_ugdata.vsmess);
      return(ReturnOrderReject());
   }
   // �µ��ɹ�:
   sprintf(m_ugdata.sExecID,"1_%s",m_ugdata.sClOrdID);  // ����ͳ���ĳɽ�ִ�б������һЩ '_',��ֹ�ظ�
   strcpy(m_ugdata.sExecType,"0");  // as NewConfirmation return.
   strcpy(m_ugdata.sOrderID,m_ugdata.sClOrdID);
   m_ugdata.dLastPx = m_ugdata.dLastQty = m_ugdata.dCumQty = m_ugdata.dAvgPx = 0;
   m_ugdata.dLeavesQty = m_ugdata.dOrderQty;
   UG_UGDataReturn(&m_ugdata);
   UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
   return(g_KSCTS.SendToFIXSvr(m_fixmsg));
}

// ����������:
int COutThread::HandleOrderCancelRequest()
{
   char fvalue[256];
   int rtn;
   if (g_KSCTS.m_Status<FS_OPEN)
   {
//       if (strcmp(m_ugdata.sOrderID,"NONE")==0)
//       {
//          // Ϊ�ָ��׶Σ�����ԭ����CancelRequest�Ǳ��ܾ��˵ġ�
//          return(0); // Skipped
//       }
      if (m_ugdata.sOrderID[0]!='\0')
      {
         // �ڻָ��׶Σ��������TAG����˵�����������Ѿ���������������ˣ�
         // ��Ϊ���ﲻ���PendingCancel��Ψһ�Ը�Cancelֻ��Rejected��Cancelled,Ҳ�Ͳ��ûָ��ˡ�
         return(0); // Skipped
      }
   }
   // �ȼ�����ݿ����Ƿ��Ѿ��б���¼�� - �Է�ֹ�ظ�����
   if ((rtn=g_KSCTS.GetDBEntrustStatus(&m_ugdata))>0)
   {
      switch (m_ugdata.sOrdStatus[0])  // ENTRUST_STATUS
      {
      case '9': // /*schui 20061208 ��������*/
         // ��������ٴζ�ԭί�н��г�������Щί��״̬��
         // TODO:
         break;
      default:
         //SQLDebugLog(7011,"Duplicated Cancel:%s",m_fixmsg); ��������Ҳ���ָ���ʱ����ã���˾Ͳ�����
         return(0);         
      }
   }
   if (rtn<0)
      return(-1);
   strcpy(m_ugdata.sMsgType,"D"); // ׼����ȡԭʼί�м�¼����:
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // ��!!! ԭʼ����û�� TAT
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
   // �ƺ�Ӧ�öԴ���������Ү:(
   switch (m_ugdata.sOrdStatus[0])
   {
   // case '0': //      0 δ��
   // case '1': //      1 ����
   // case '2': //      2 �ѱ�
   // case '7': //      7 ����

   case '3': //      3 �ѱ�����
   case '4': //      4 ���ɴ���
      // �Ѿ��г������ڽ�����:
      m_ugdata.lCxlRejReason = 3; // 3 = Order already in Pending Cancel or Pending Replace status
   case '5': //      5 ����
   case '6': //      6 �ѳ������⣩
   case '8': //      8 �ѳ�
   case '9': //      9 �ϵ�
   case 'A': //      A �ѳ������ڣ�
      // Too late to cancel:
      //  m_ugdata.lCxlRejReason = 0; // 0 = Too late to cancel
      strcpy(m_ugdata.sCxlRejResponseTo,"1");  // 1 = Order Cancel Request
      STRNCPY(m_ugdata.sOrderID,m_ugdata.sOrigClOrdID);
      UG_UGDataReturn(&m_ugdata);
      UG_CancelRejectFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSCTS.SendToFIXSvr(m_fixmsg));
   }

   // �������������CJThread�еĴ�����ɣ�����Ǽ�һ��:
   g_KSCTS.RegisterCancelOrder(m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID);
#ifdef USE_423002  // : ���Խ��, ������̫��: 150����Ҫ 22ms���ҵģ� ���� 130105��ֻҪ��5ms����; ��˲�ʹ����
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,423002);
   BCSetStringFieldByName(m_bc,0,"scust_no",m_ugdata.sClientID);   // scust_no='',�ͻ���   ��
   BCSetStringFieldByName(m_bc,0,"smarket_code",m_ugdata.sSellSide);   // smarket_code='',�г�����   ��
   BCSetStringFieldByName(m_bc,0,"lvol4",m_ugdata.sOrigClOrdID);    // lvol4='',��ͬ��   ��
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',����Ӫҵ��  ��
#else
   // ��KSCTS����130105����
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,130105);
   BCSetStringFieldByName(m_bc,0,"scust_no",m_ugdata.sClientID);   // scust_no='',�ͻ���   ��
   BCSetStringFieldByName(m_bc,0,"smarket_code",m_ugdata.sSellSide);   // smarket_code='',�г�����   ��
   BCSetStringFieldByName(m_bc,0,"sorder0",m_ugdata.sOrigClOrdID);    // sorder0='',��ͬ��   ��
      // lvol1='',����   ��
   BCSetIntFieldByName(m_bc,0,"lvol0",1);    // lvol0='',����ģʽ lvol0 1:�򰴺�ͬ�ţ�2:������
   BCSetIntFieldByName(m_bc,0,"lvol2",1);   // lvol2='',�Ƿ��ظ����� 1==�ظ�����,����=�������ظ�����   ��
      // lcert_code='',ί������ 0-��ͨί��,1-��ί��   ��
      // lwithdraw_flag='',��˱�־  ��
   BCSetStringFieldByName(m_bc,0,"sbranch_code0",g_KSCTS.m_WTYYB);   // sbranch_code0='',����Ӫҵ��  ��
   BCSetStringFieldByName(m_bc,0,"semp","SYSTEM");   // semp='',ְ������  ��
   BCSetStringFieldByName(m_bc,0,"sstation0","KSFIXIII");   // sstation0='',������  ��
#endif
   g_KSCTS.CallSvr(m_bc,fvalue);
   // �������߶�ʮһ����ȥ��̨��һ������:
   rtn = 0; m_ugdata.lCxlRejReason = -1;
   strcpy(m_ugdata.sMsgType,"F");  // Ϊ�˲鳷����¼
   if (g_KSCTS.GetDBEntrustStatus(&m_ugdata)<=0)
   {
      // ��˵���µ�û�гɹ�
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
      // �ⲿ���ɳɽ��ر�����ȥ���������Ȳ���
//       switch (m_ugdata.sOrdStatus[0])
//       {
//       case '9': // �ϵ�
//          rtn = atoi(m_ugdata.sExecInst); // EXCHANGE_ERR_CODE
//          strcpy(fvalue,"Cancel Rejected by OMS");
//          break;
//       }
   }

   if (rtn!=0)
   {
      // ���γ����Ծܾ�����
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
         // ������OProcess�У��Ѿ������ֹ�ظ�������������˾�ֱ��������������
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
int COutThread::QueryFundStatus()  // �����Ϊ����¼���صĲ�ѯ����
{
   char fvalue[256];
   int rtn;
   char reqid[40];
   char sCurrency[12];

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,422101);  // ��ѯ�ͻ��ʽ�״̬
   
   BCSetStringFieldByName(m_bc,0,"sbranch_code0", g_KSCTS.m_WTYYB);		//Ӫҵ��  


   g_KSCTS.GetCurrcncy(m_ugdata.sCurrency,sCurrency,0);

   BCSetStringFieldByName(m_bc,0,"scurrency_type", sCurrency);   //����

   BCSetStringFieldByName(m_bc,0,"scust_no", m_ugdata.sClientID);   //�ͻ���
   BCSetStringFieldByName(m_bc,0,"sbank_code2", g_KSCTS.m_WTFSx);   //ί�з�ʽ
   BCSetStringFieldByName(m_bc,0,"semp","SYSTEM");   // semp='',ְ������  ��
   BCSetStringFieldByName(m_bc,0,"sstation0", "KSFIXIII");   //������Դ


   UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
   // ��Ϊ����Ӧ������׼��

   rtn = g_KSCTS.TryCallSvr(m_bc,fvalue);  // �������ڶ��ظ���������ν������ѡ����TryCallSvr
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
   
   // �ȴ�ԭʼ�����л�� RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
	   strcpy(reqid,"NONE");
   }


   FIXDataReset(m_fh,NULL,NULL,NULL);
   
   strcpy(fvalue,"KSFA"); // Fund status Return
   FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);

   //UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���ΪӦ��
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
   FIXDataAddTag(m_fh,TAG_NextFlag,"N",0);  // ��Ϊ�ǵ���¼

   // damt0,�ʽ����
   BCGetStringFieldByName(m_bc,0,"damt0",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8081,fvalue,0);

   // damt1,�����ʽ�
   BCGetStringFieldByName(m_bc,0,"damt1",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8084,fvalue,0);
   
   // damt2,��ȡ�ʽ�
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
   
   // �ȴ�ԭʼ�����л�� RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
	   strcpy(reqid,"NONE");
   }
   
   FIXDataReset(m_fh,NULL,NULL,NULL);   
   strcpy(fvalue,"KSRJ");
   FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);
   // UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
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
int COutThread::QueryPositionStatus()  // �����Ϊ���¼���صĲ�ѯ����
{
   char fvalue[256];
   int rtn;
   int i,n;
   char *pv;
   //char *ps2;
   char reqid[40];

   // �ȴ�ԭʼ�����л�� RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
	   strcpy(reqid,"NONE");
   }

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,423102);  // ��ѯ�ͻ��ֲ�״̬

   BCSetStringFieldByName(m_bc,0,"sbranch_code0", g_KSCTS.m_WTYYB);		//Ӫҵ��  
   
   BCSetStringFieldByName(m_bc,0,"scust_no", m_ugdata.sClientID);   //�ͻ���
   //BCSetStringFieldByName(m_bc,0,"smarket_code", m_ugdata.sSecurityExchange);   //�г�����

   if(strlen(m_ugdata.sSecurityExchange) >0)
   {
   
	   pv =(char *)UG_GetIMarket(m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
	   if (pv==NULL)
	   {
		   SQLDebugLog(4801,"Unsupported IMarket(%s,%s,%s)",
			   m_ugdata.sSecurityExchange,m_ugdata.sAccount,m_ugdata.sSymbol);
		   return(ReturnRequestRejected(944,fvalue));
		   
		   
	   }
	   BCSetStringFieldByName(m_bc,0,"smarket_code", pv);   //�г�����
   }
   else
	   BCSetStringFieldByName(m_bc,0,"smarket_code", "");   //�г�����
   BCSetStringFieldByName(m_bc,0,"sstock_code", "");   //֤ȯ����
   BCSetIntFieldByName(m_bc,0,"lvol0", 0);   //��෵������
   BCSetIntFieldByName(m_bc,0,"lvol1", 0);   //�Ƿ񷵻غϼ�ֵ 1�����غϼ�ֵ������������


   BCSetStringFieldByName(m_bc,0,"sbank_code2", g_KSCTS.m_WTFSx);   //ί�з�ʽ

   UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
   // ��Ϊ����Ӧ������׼��
   
   rtn = g_KSCTS.TryCallSvr(m_bc,fvalue);  // �������ڶ��ظ���������ν������ѡ����TryCallSvr
   if (rtn<0)
   {
      SQLDebugLog(4801,"Fail to CallFTSSvr(854048,%s):%d-%s",
         m_ugdata.sClientID,rtn,fvalue);
      return(ReturnRequestRejected(944,fvalue));
   }

   // ����Ϊ���¼�Ľ����
   n = 1;
	  FIXDataReset(m_fh,NULL,NULL,NULL);
	  
	  strcpy(fvalue,"KSPA"); // Position status Return
	  FIXDataAddTag(m_fh,TAG_MsgType,fvalue,0);
	  
	  //UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
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
	  
	  UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
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
         // ע�����涼Ҫ��FIXDataUpdateTag, ������FIXDataAddTag
         sprintf(fvalue,"%d",n++);
         FIXDataUpdateTag(m_fh,-1,TAG_PresentRetNum,fvalue,0);
         if (i+1<rtn || BCHaveNextPack(m_bc))
            strcpy(fvalue,"Y");
         else
            strcpy(fvalue,"N");
         FIXDataUpdateTag(m_fh,-1,TAG_NextFlag,fvalue,0);
         //       smarket_code='',����������  -- ��Ҫת��Ϊ��׼����������
         BCGetStringFieldByName(m_bc,i,"smarket_code",fvalue,sizeof(fvalue));
         //STRNCPY(m_ugdata.sSecurityExchange,g_KSFTS.GetExchange(fvalue));

		 if(strcmp(fvalue,"1" )==0 || strcmp(fvalue,"3" )==0)
			STRNCPY(m_ugdata.sSecurityExchange,"XSHG");
		 else
			STRNCPY(m_ugdata.sSecurityExchange,"XSHE");
         FIXDataUpdateTag(m_fh,-1,TAG_SecurityExchange,m_ugdata.sSecurityExchange,0);

		 //�ɶ��˺�
         BCGetStringFieldByName(m_bc,i,"sholder_ac_no",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_Account,fvalue,0);


		 //�ͻ���
		 FIXDataUpdateTag(m_fh,-1,TAG_ClientID,m_ugdata.sClientID,0);

         //֤ȯ����
         BCGetStringFieldByName(m_bc,i,"sstock_code",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_Symbol,fvalue,0);

		 /*���(���ϵ��ճɽ�)*/
		 BCGetStringFieldByName(m_bc,i,"lvol6",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,53,fvalue,0);  //53  Quantity

		 /*����ƽ���۸�*/
		 BCGetStringFieldByName(m_bc,i,"damt4",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_AvgPx,fvalue,0);

		 
		 // damt23='',���¼�
         BCGetStringFieldByName(m_bc,i,"damt10",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_Price,fvalue,0);  // Price
         

         // ��ʱ�ȸ�����ЩTAG���ˡ�
         //////////////////////////////////////////////////////////////////////////
         FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));
         g_KSCTS.SendToFIXSvr(m_fixmsg);
      }
      if (!BCHaveNextPack(m_bc))
         break; // �����ˣ�û�к������ݼ�¼��
      if (g_KSCTS.CallNext(m_bc,fvalue)<0)
      {
         return(ReturnRequestRejected(944,fvalue));  // �þܾ�������
      }
   } while (1);
   return(n);
}
