/********************************************************************
	created:	2011/09/29
	created:	29:9:2011   17:18
	filename: 	C:\dd\projects\FIXIII\UGate\ugfts\OutThread.cpp
	file path:	C:\dd\projects\FIXIII\UGate\ugfts
	file base:	OutThread
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 �ⲿ��Ϊ��������FS��ҵ����Ϣ����ģ�飬������ר��KSFTS�Խ�
   ע�⣺
   -- ί��״̬
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, '!', 'ί��״̬'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'n', '�ȴ�����'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 's', '�����걨'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'a', '�Ѿ�����'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'p', '���ֳɽ�'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'c', 'ȫ���ɽ�'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'b', '���ɲ���'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'f', '�ȴ�����'  )
   --insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'g', '��������'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'd', '�Ѿ�����'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'e', '����ί��'  )
   -- jq 20070118 �����ܾ���Ϊ���ھܾ�
   --insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'q', '�����ܾ�'  )
   insert dictionary( dict_no, dict_value, dict_caption ) values( 009, 'q', '���ھܾ�'  )

  FUNCTION 854041 Description  "��ѯ����ί�е�"  reqlevel 1
���룺����Ա,ϯλ��,�ͻ���,�ͻ���,��Լ��,ί��״̬����,����ί�е����,����,�Ƿ�����ϼƱ��,ǿƽ���,��������, ��Ϸ���ϲ�ѯ��־, ��ƽ�ֱ�־������ʽ
INPUT:SCUST_NO,SSERIAL2,SHOLDER_AC_NO,SSERIAL1,SCUST_AUTH,SBANK_PWD2,SMAIN_FLAG,SCURRENCY_TYPE,SSTATUS3,SSTATUS1,SNAME2, SSTATUS2, SSTATUS0,SSTATUS4
�����ί�к�,����Ա,�ͻ���,�ͻ�����,����������,Ʒ�ִ���,������,ί�е�״̬,��ƽ���,Ͷ�����,��������,ί�м�,ί����,ʣ����,�ɽ���,�ɽ���,ϵͳ��,ί��ʱ��,�걨ʱ��,���ױ���,ί�з�ʽ,�����û�,����ʱ��,ί�е�����,ϯλ��,����,��ע,�޸�����,ǿƽ��־,ָ����,�µ�ϯλ,���ر�־,��ϲ���,��Լ1,��Լ2,��Լ3,��Լ4,��������,�ɽ�����,�������,ֹ��ӯ����,����ʱ��,�µ�������,˽����Ϣ,˽�б�ʶ,˽����ˮ�� 
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
      return(QueryFundStatus());  // ���Ϊ����¼��ѯ��������
   if (strcmp(m_ugdata.sMsgType,"KSPR")==0)
      return(QueryPositionStatus()); // ���Ϊ���¼��ѯ��������
   SQLDebugLog(50001,"Unsupported MsgType=%s @ FTS-OUTThread!",m_ugdata.sMsgType);
   return(-1);
}

// ��ʹ��ExtCall��ʱ�����ͨѶƽ̨��Ŀ�������쳣
#define MIN_XCALLERR 9985
//#define MAX_XCALLERR 9988  // V2.73����
#define MAX_XCALLERR 10000  // under 2.72

#define TAG_HedgeFlag  8009 // 	8009	HedgeFlag		Y		Ͷ���ױ���־ �����ڻ������ݽӿ��еĶ���
int COutThread::HandleNewOrderSingle()
{
   char fvalue[256];
   //char sOpenClose[2];
   char sFTSMarketCode[4];
   char sBuySell[2];
   char sOrdType[2];   
   // 2010-9-11 20:34:20 ������Ϊ�˸���ȷ���ġ��ɽ����ԡ�
   char sDealMode[2];  /*  FIX TimeInForce -> �ɽ����� */
   //////////////////////////////////////////////////////////////////////////
   int rtn;
   char *pcustno,*pseat;

   STRNCPY(m_ugdata.sOrigClOrdID,m_ugdata.sClOrdID);  // Ϊ�˺����������������ҲΪ�������Ϣ׼��
   rtn = QueryFTSOrders(&m_ugdata);
   if (rtn>0)
   {
      // ��FTS�ڲ��Ѿ��иö�����
      if (g_KSFTS.m_Status<FS_OPEN)
      {
         // ������Openǰ��Restore�׶�:
         if (rtn>1)
         {
            g_KSFTS.RegisterWTHClOrdID(m_sWTH[1],m_ugdata.sOrigClOrdID,m_vsvarstr1[1]);
         }
         g_KSFTS.RegisterWTHClOrdID(m_sWTH[0],m_ugdata.sOrigClOrdID,m_vsvarstr1[0]);
      }
      else  // ??? ������ܸ��Զ����ܾ��ķ�ʽ��FS��, ���Ǳ������Ӧ����FS�Ͼ��Ѿ��������ˣ�Ϊɶ��?? ���ֳ����ܹ�������
         SQLDebugLog(7011,"Duplicated Order:%s",m_fixmsg);
      // �����ö�����״̬���Բ���֮ǰ����û�и����ĳɽ�����: ֻ�ǲ���ί�в��֣��Գ������֣����ɶ�Ӧ�ĳ���ȥ���
      m_ugdata.dOrderQty = m_OrderQty[0]+m_OrderQty[1];
      m_ugdata.dCumQty = m_CumQty[0]+m_CumQty[1];
      m_ugdata.dAvgPx = m_ugdata.dCumQty>MIN_QTY ? (m_AvxPx[0]*m_CumQty[0]+m_AvxPx[1]*m_CumQty[1])/m_ugdata.dCumQty : 0;
      m_ugdata.dLastQty = m_ugdata.dCumQty;
      m_ugdata.dLastPx = m_ugdata.dAvgPx;
      m_ugdata.dLeavesQty = m_ugdata.dOrderQty-m_ugdata.dCumQty;
      strcpy(m_ugdata.sOrderID,m_sWTH[0]);
      switch (m_WTZT[0])
      {
      case 'e':   // 'e', '����ί��'
      case 'q':   // 'q', '���ھܾ�'
         // ��Ϊ����ί��
         strcpy(m_ugdata.sOrdStatus,"8");
         strcpy(m_ugdata.sExecType,"8");
         sprintf(fvalue,"R-%s",m_sWTH[0]);
         STRNCPY(m_ugdata.sExecID,fvalue);
         m_ugdata.dLeavesQty = 0;
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         return(g_KSFTS.SendToFIXSvr(m_fixmsg));
#if 0    // ����Ҫ�óɽ���ϸ���ָ������ֺ����׵��³ɽ��ظ�
      case 'p':   // 'p', '���ֳɽ�'
      case 'c':   // 'c', 'ȫ���ɽ�'
      case 'b':   // 'b', '���ɲ���'
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
   if (rtn<0)  // ??? ����Ҫ�˲� ����������ģ�
   {
      // ����ΪͨѶ��·�쳣����
      if (g_KSFTS.m_Status==FS_OPEN)
      {
         // ��ô ��ʱ��FSһ�㲻���ظ���������ģ�
         m_ugdata.lOrdRejReason = 0;  // 0 = Broker / Exchange option
//          sprintf(m_ugdata.vsmess,"Unsupported SecurityExchange(%s)",
//             m_ugdata.sSecurityExchange);
         return(ReturnOrderReject());
      }
      return(-1);
   }

   if (g_KSFTS.m_Status<FS_OPEN && m_ugdata.sOrderID[0]!='\0')
      return(0);

   m_ugdata.vsmess[0]='\0'; // ���ԭ������: "û�в�ѯ���"

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

   // �ڻ���̨�� 0 �޼ۣ� 1 �м�
   sOrdType[0] = '1';
   sOrdType[1] = '\0';
   switch (m_ugdata.sOrdType[0])
   {
   case '1':  // Market
      m_ugdata.dPrice = 0;
      if (strcmp(m_ugdata.sSecurityExchange,"sfe")==0
         ||strcmp(m_ugdata.sSecurityExchange,"XSGE")==0)
      {
         // Ҫ�����������ر���
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

   // 2010-9-11 20:34:20 ������Ϊ�˸���ȷ���ġ��ɽ����ԡ�
   switch (m_ugdata.sTimeInForce[0])
   {
   case '4': // 4 = Fill or Kill (FOK)
      sDealMode[0]='1';  // 1, FOKȫ�ɻ�ȫ�� FIX: 4
      break;
   case '3': // 3 = IOC (FAK)
      // 2, FAKʣ�༴���� FIX: 3 - IOC
      sDealMode[0]='2';
      break;
   default:
      sDealMode[0]='0'; // 0, GFD������Ч   FIX: �ջ�0
      break;
   }
   sDealMode[1]='\0';
   //////////////////////////////////////////////////////////////////////////

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854002);  // �ֶε����ñ���Ͳ�ί�е�ʱ��һ��
   // �ͻ���	sholder_ac_no
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(m_ugdata.sClientID,fvalue)); 
   // ˽�б�ʶ	semp_no
   STRNCPY(fvalue,UG_GetPartners());
   BCSetStringFieldByName(m_bc,0,"semp_no",fvalue);      
   // ˽����ˮ��	scust_limit
   BCSetStringFieldByName(m_bc,0,"scust_limit",m_ugdata.sOrigClOrdID);    
   // ��������	sstatus2
   BCSetStringFieldByName(m_bc,0,"sstatus2",sBuySell);
   // ����Ա	scust_no
   BCSetStringFieldByName(m_bc,0,"scust_no",g_KSFTS.GetOperator()); 
   // ���ױ���	sholder_ac_no2
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no2",m_ugdata.sAccount); 
   // ����������	smarket_code
   BCSetStringFieldByName(m_bc,0,"smarket_code",sFTSMarketCode);
   // ��Լ��	scust_auth
   BCSetStringFieldByName(m_bc,0,"scust_auth",m_ugdata.sSymbol);
   // �걨����	lvol0
   BCSetIntFieldByName(m_bc,0,"lvol0",(int)(m_ugdata.dOrderQty+MIN_QTY));
   // �걨�۸�	damt0
   BCSetDoubleFieldByName(m_bc,0,"damt0",m_ugdata.dPrice);
   // ��ƽ���	sstatus3
   switch (m_ugdata.sOpenClose[0])
   {
   case 'C':   // C = Close
      BCSetStringFieldByName(m_bc,0,"sstatus3","1");
      break;
   case '2':   // ƽ��
      BCSetStringFieldByName(m_bc,0,"sstatus3","3");
      break;
   case 'O':   // O = Open
   default:    // R = Rolled;  F = FIFO ���ÿ���������
      BCSetStringFieldByName(m_bc,0,"sstatus3","0");
      break;
   }
   // Ͷ�����	sstatus4
   rtn = sizeof(fvalue);
   if (FIXDataGetTag(m_fh,TAG_HedgeFlag,fvalue,&rtn)<0)
   {
      strcpy(fvalue,"0");
   }
   else
   {
      //       Ͷ���ױ���־��ȡֵ��Χ��
      //          0=Ͷ��
      //          1=�ױ�
      //BCSetStringFieldByName(m_bc,0,"sstatus4",fvalue);
   }
   BCSetStringFieldByName(m_bc,0,"sstatus4",fvalue);
   // ϯλ��	sserial2 -- ������

   // �µ�������	smain_flag2
   BCSetStringFieldByName(m_bc,0,"smain_flag2","1");
   // ί�з�ʽ	sholder_type
   BCSetStringFieldByName(m_bc,0,"sholder_type","7");
   // ����	scurrency_type -- �����Ŀǰ��ֻ��RMB
   BCSetStringFieldByName(m_bc,0,"scurrency_type","1");
   // BCSetStringFieldByName(m_bc,0,"",);
   // ǿƽ��־	sstatus0 : 0��ǿƽ  1ǿƽ -- ������ 0�Ͳ��� һ����Ч��

   // ��������	scust_type:  0 �޼ۣ� 1 �м�
   BCSetStringFieldByName(m_bc,0,"scust_type",sOrdType);
   // �ɽ�����	scust_type2:
   BCSetStringFieldByName(m_bc,0,"scust_type2",sDealMode);
   // ֹ��ֹӯ��	damt3  -- 99	StopPx
   rtn = sizeof(fvalue);
   if (FIXDataGetTag(m_fh,99,fvalue,&rtn)<0)
   {
      // �ǾͲ�����
   }
   else
   {
      BCSetStringFieldByName(m_bc,0,"damt3",fvalue);
   }

   // ˽����Ϣ	sstation1
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
         // ����������ί��ʧ��:
         BCGetStringFieldByName(m_bc,0,"vsmess",fvalue,sizeof(fvalue)); mytrim(fvalue);
         sprintf(m_ugdata.vsmess,"%d:%s",rtn,fvalue);
		 SetErrCodeInfo(FUTURE_MCODE,m_ugdata.vsmess, "Rejected by KSFTS, ErrNo=", m_ugdata.vsmess);
         m_ugdata.lOrdRejReason = 0;
         return(ReturnOrderReject());
      }
      BCGetRecordCount(m_bc,&rtn);
      if (rtn>2)
         rtn = 2; // Ŀǰһ��ֻ��������
      pcustno = fvalue;
      pseat = fvalue+100;
      for (n=0;n<rtn;++n)
      {
         int l;
         // ί�к�	lserial0
         BCGetIntFieldByName(m_bc,n,"lserial0",&l);
         // �ͻ���	sholder_ac_no
         BCGetStringFieldByName(m_bc,0,"sholder_ac_no",pcustno,100);
         mytrim(pcustno);
         // ϯλ��	sserial2
         BCGetStringFieldByName(m_bc,0,"sserial2",pseat,100);
         mytrim(pseat);

         g_KSFTS.GetWTH(l,pcustno,pseat,m_sWTH[n]);
         
         // �µ�ϯλ
         BCGetStringFieldByName(m_bc,n,"vsvarstr1",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         STRNCPY(m_vsvarstr1[n],fvalue);

         // ί��״̬	sstatus0
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
      // �ƺ�FTS�쳣������������
      sprintf(m_ugdata.vsmess,"Invalid KSFTS, ErrNo=%d:%s",7011,fvalue);
      m_ugdata.lOrdRejReason = 0;
      return(ReturnOrderReject());
   }
   if (n>1)
   {
      g_KSFTS.RegisterWTHClOrdID(m_sWTH[1],m_ugdata.sOrigClOrdID,m_vsvarstr1[1]);
   }
   g_KSFTS.RegisterWTHClOrdID(m_sWTH[0],m_ugdata.sOrigClOrdID,m_vsvarstr1[0]);
   // �µ��ɹ�:
   sprintf(fvalue,"1_%s",m_ugdata.sClOrdID);  // ����ͳ���ĳɽ�ִ�к�����һЩ '_',��ֹ�ظ�
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
   m_WTZT[0]=m_WTZT[1]='?'; // ��Ϊδ֪
   m_OrderQty[0]=m_CumQty[0]=0;
   m_AvxPx[0]=m_AvxPx[1]=0;
   m_OrderQty[1]=m_CumQty[1]=0;
   if (g_KSFTS.m_Status>=FS_OPEN)
   {
      // ���������죬����̨ȥ���ù��ܣ��϶����ˣ������м�¼������
      n = GetAllWTH(m_ugdata.sOrigClOrdID);
   }
   else if (m_ugdata.sOrderID[0])
   {
      return(0); // Ϊ�ָ�״̬���Ѿ���OrderID����˵���Ѿ��з����ˣ�����Ҫ�ٷ������ˡ�
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
         // �ָ��׶Σ���Щ��ʵ�������ˡ������ϴ�Ҳ�Ǳ��������˵ġ�
         return(0);
      }
   }
   // ������Ҫ�����Ƿ��Ѿ�������������жϣ�����ѯԭ����״̬��Ϣ
   m_ugdata.dOrderQty = m_ugdata.dCumQty = m_ugdata.dLastQty = m_ugdata.dLeavesQty = 0;
   m_ugdata.dLastPx = m_ugdata.dAvgPx = 0;
   UG_UGDataReturn(&m_ugdata);
   if (n>1)
   {
      switch (m_WTZT[1])
      {
      case 'b': // 'b', '���ɲ���' 
      case 'd': // 'd', '�Ѿ�����'
         // ���Ѿ����˳���: ���ڻָ��׶Σ���Ҫ���س����ɹ�����Ϣ:      
         m_ugdata.dOrderQty = m_OrderQty[1];
         m_ugdata.dCumQty = m_CumQty[1];
         sprintf(fvalue,"C-%s",m_sWTH[1]);  // ��sWTH��Ϊ�˶��WTH�ĳ����ر���Ҫ�������Ͳ����ظ��ˣ��Ǻ�
         STRNCPY(m_ugdata.sExecID,fvalue);
         strcpy(m_ugdata.sOrdStatus,"4");
         strcpy(m_ugdata.sExecType,"4"); // ��ʾ����
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         g_KSFTS.SendToFIXSvr(m_fixmsg);
         break;
      }
   }
   switch (m_WTZT[0])
   {
   case 'f': // 'f', '�ȴ�����'
      // ���Ѿ����˳���:
      return(0);
   case 'b': // 'b', '���ɲ���' 
   case 'd': // 'd', '�Ѿ�����'
      // ���Ѿ����˳���: ���ڻָ��׶Σ���Ҫ���س����ɹ�����Ϣ:      
      m_ugdata.dOrderQty = m_OrderQty[0];
      m_ugdata.dCumQty = m_CumQty[0];
      sprintf(fvalue,"C-%s",m_sWTH[0]);  // ��sWTH��Ϊ�˶��WTH�ĳ����ر���Ҫ�������Ͳ����ظ��ˣ��Ǻ�
      STRNCPY(m_ugdata.sExecID,fvalue);
      strcpy(m_ugdata.sOrdStatus,"4");
      strcpy(m_ugdata.sExecType,"4"); // ��ʾ����
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      return(g_KSFTS.SendToFIXSvr(m_fixmsg));
   case 'c': // 'c', 'ȫ���ɽ�'
   case 'e': // 'e', '����ί��'
   case 'q': // 'q', '���ھܾ�'
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
         // ˵��������������, �����Ƿ��ڲ�������
         if (m_WTZT[1]=='d')
         {
            sprintf(fvalue,"C-%s",m_sWTH[1]);
            STRNCPY(m_ugdata.sExecID,fvalue);
            m_ugdata.dOrderQty = m_OrderQty[1];
            m_ugdata.dCumQty = m_CumQty[1];
            strcpy(m_ugdata.sOrdStatus,"4");
            strcpy(m_ugdata.sExecType,"4"); // ��ʾ����
            UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
            g_KSFTS.SendToFIXSvr(m_fixmsg);
         }
      }
   }
   if (CancelAnOrder(0,fvalue)==0)
   {
      // ˵��������������, �����Ƿ��ڲ�������
      if (m_WTZT[0]=='d')
      {
         sprintf(fvalue,"C-%s",m_sWTH[0]);
         STRNCPY(m_ugdata.sExecID,fvalue);
         m_ugdata.dOrderQty = m_OrderQty[0];
         m_ugdata.dCumQty = m_CumQty[0];
         strcpy(m_ugdata.sOrdStatus,"4");
         strcpy(m_ugdata.sExecType,"4"); // ��ʾ����
         UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
         return(g_KSFTS.SendToFIXSvr(m_fixmsg));
      }
      return(0);  // ���ø��κη��صģ����߸�PendingCancel���ء�����FS����ν�ġ�
   }
   // ���־��ǳ������ܾ��ˣ�
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
   BCSetRequestType(m_bc,854118);  // ��ָ��������FTS�е�    �����ֶε����ñ����ί�е�ʱ��һ��
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(pUGData->sClientID,fvalue)); // �ͻ���	sholder_ac_no
   STRNCPY(fvalue,UG_GetPartners());
   BCSetStringFieldByName(m_bc,0,"semp_no",fvalue);      // ˽�б�ʶ	semp_no
   BCSetStringFieldByName(m_bc,0,"scust_limit",pUGData->sOrigClOrdID);  // ˽����ˮ��	scust_limit  

   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);  // �������ڶ��ظ���������ν������ѡ����TryCallSvr
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
      // rtn=9999 : Ӧ�÷�����: û�в�ѯ���
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
      rtn = 2; // Ŀǰһ��ֻ��������
   pcustno = fvalue;
   pseat = fvalue+100;
   for (n=0;n<rtn;++n)
   {
      int l;
      BCGetIntFieldByName(m_bc,n,"lserial0",&l);
      // �ͻ���	sholder_ac_no
      BCGetStringFieldByName(m_bc,0,"sholder_ac_no",pcustno,100);
      mytrim(pcustno);
      // ϯλ��	sserial2
      BCGetStringFieldByName(m_bc,0,"sserial2",pseat,100);
      mytrim(pseat);
         
      g_KSFTS.GetWTH(l,pcustno,pseat,m_sWTH[n]);

      // �µ�ϯλ
      BCGetStringFieldByName(m_bc,n,"vsvarstr1",fvalue,sizeof(fvalue));
      mytrim(fvalue);
      STRNCPY(m_vsvarstr1[n],fvalue);

      // ί��״̬	sstatus0
      BCGetStringFieldByName(m_bc,n,"sstatus0",fvalue,sizeof(fvalue));
      mytrim(fvalue);
      m_WTZT[n]=fvalue[0];
      // ί����	lvol0
      BCGetIntFieldByName(m_bc,n,"lvol0",m_OrderQty+n);
      // �ɽ���	lvol1
      BCGetIntFieldByName(m_bc,n,"lvol1",m_CumQty+n);
      // �ɽ���	damt2
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
   BCSetRequestType(m_bc,854132);  // ��ָ����Լ����������
   BCSetStringFieldByName(m_bc,0,"scust_no", g_KSFTS.GetOperator());          //����Ա
   BCSetStringFieldByName(m_bc,0,"smarket_code",sFTSMarketCode);     //����������	smarket_code
   BCSetStringFieldByName(m_bc,0,"scust_auth", pUGData->sSymbol);    //��Լ��
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

// ����һ��WTH���г���������, iwt: 0 or 1; 
int COutThread::CancelAnOrder(int iwt, char *fvalue256)
{
   int rtn;
   int lvol0,lvol2;
   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854018);  // ����ί��
   // ����Ա	scust_no
   BCSetStringFieldByName(m_bc,0,"scust_no",g_KSFTS.GetOperator()); 
   // �ͻ���	sholder_ac_no
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",g_KSFTS.GetCustNoFromWTH(m_sWTH[iwt],fvalue256,256));
   // ϯλ��	sserial2  -- ����Ȳ�Ҫ����
   BCSetStringFieldByName(m_bc,0,"sserial2",g_KSFTS.GetSeatNoFromWTH(m_sWTH[iwt],fvalue256,256));

   // �µ�������	smain_flag2
   BCSetStringFieldByName(m_bc,0,"smain_flag2","1");

   // ί�к�	lserial0
   BCSetIntFieldByName(m_bc,0,"lserial0",g_KSFTS.GetIWTH(m_sWTH[iwt])); 

   // �µ�ϯλ	vsvarstr1
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
   // ί��״̬	sstatus0
   BCGetStringFieldByName(m_bc,0,"sstatus0",fvalue256,256);
   mytrim(fvalue256);
   m_WTZT[iwt]=fvalue256[0];
   //if (m_ugdata.sOrdStatus[0]=='d')  // 'd', '�Ѿ�����'
   {
      // �걨����	lvol0
      BCGetIntFieldByName(m_bc,0,"lvol0",&lvol0); 
      m_OrderQty[iwt]=lvol0;
      // ʣ������	lvol2
      BCGetIntFieldByName(m_bc,0,"lvol2",&lvol2);  // ���Ӧ����0
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


// ������: COutThread::MayToBeCanceled
// ���  : ������ 2011-10-2 10:43:51
// ����  : ���ͨ��ί��״̬�����ж��Ƿ�����³������������ԣ�����������ܾ�
// ����  : int =0: �����³������󣻷��򣬿��³�������
// ����  : int iwt[IN]: 0 �� 1����ʾ��m_sWTH[0]-m_WTZT[0]��m_sWTH[1]-m_WTZT[1]
int COutThread::MayToBeCanceled(int iwt)
{
   if (iwt<0 || iwt>1)
      return(0);
   STRNCPY(m_ugdata.sOrderID,m_sWTH[iwt]);
   switch (m_WTZT[iwt])
   {
   case 'c': // ȫ���ɽ�
      m_ugdata.lCxlRejReason = 0;
      strcpy(m_ugdata.vsmess,"The order has been filled!");
      ReturnCancelRejected();
      return(0);
   case 'f': // �ȴ�����
      if (g_KSFTS.m_Status>=FS_OPEN)
      {
         // Ϊ����Open״̬�����µĳ���������Ҫ�������ܾ���������FS���ƣ�Ӧ�ò�����ֵ�
         m_ugdata.lCxlRejReason = 3;
         ReturnCancelRejected();
      }
      return(0);
   case 'q': // ���ھܾ�
      // �����ί�оܾ�����, Ϊ�˷�ֹ�ڶ����ڼ䣬û�н����͹�������Ϣ����
#if 0
      // �ⲿ����NewOrderSingle�ָ���ʱ�򣬷�����ʾ����
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
   case 'b': // ���ɲ���
   case 'd': // �Ѿ�����
      // �򷵻س����ɹ�����
      strcpy(m_ugdata.sExecType,"4");
      strcpy(m_ugdata.sOrdStatus,"4");
      m_ugdata.dOrderQty = m_OrderQty[iwt];
      m_ugdata.dCumQty = m_CumQty[iwt];
      m_ugdata.dLeavesQty = m_OrderQty[iwt]-m_CumQty[iwt];
      m_ugdata.dLastPx = m_ugdata.dLastQty = 0;
      sprintf(m_fixmsg,"C-%s",m_sWTH[iwt]);  // ��sWTH��Ϊ�˶��WTH�ĳ����ر���Ҫ�������Ͳ����ظ��ˣ��Ǻ�
      STRNCPY(m_ugdata.sExecID,m_fixmsg);
      UG_UGDataReturn(&m_ugdata);
      UG_ExecutionFIXMsg(&m_ugdata,m_fixmsg,sizeof(m_fixmsg));
      g_KSFTS.SendToFIXSvr(m_fixmsg);
      return(0);
   default:  // ��������׼���������������
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

// ��ѯ�ͻ��ʽ�״̬
/* 854051:
   scust_no='',����Ա
   sholder_ac_no='',�ͻ���
   sserial1='',�ͻ���
   scurrency_type='',����
   sstatus0='',���ɺϼ�

  sholder_ac_no='',�ͻ���
  scurrency_type='',����
  sall_name='',�ͻ����/�ͻ�������
  damt3='',���ս��
  damt26='',�����ʽ�
  damt29='',�򶳽�
  damt30='',������
  damt6='',������
  damt13='',��֤��
  damt1='',����֤��
  damt11='',ƽ��ӯ��
  damt8='',����ӯ��
  damt10='',��;�ʽ�
  damt18='',δ����ӯ��
  damt28='',��̬Ȩ��
  damt4='',���ճ����
  damt25='',�ܶ���
  damt23='',�ܱ�֤��
  damt24='',�ܽ�������֤��
  damt19='',��Ѻ���
  damt31='',���ý��
  damt22='',���ն�1
  damt33='',����������
  sstatus3='',���ռ���
  damt21='',���ն�2
*/
#define TAG_RequestID 8088
#define TAG_RejReason 8072
#define TAG_PresentRetNum 8027
#define TAG_NextFlag 8095
int COutThread::QueryFundStatus()  // �����Ϊ����¼���صĲ�ѯ����
{
   char fvalue[256];
   int rtn;
   double dv;
   double dv1;
   char reqid[40];

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854051);  // ��ѯ�ͻ��ʽ�״̬
   BCSetStringFieldByName(m_bc,0,"scust_no", g_KSFTS.GetOperator());          //����Ա
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(m_ugdata.sClientID,fvalue)); // �ͻ���	sholder_ac_no
   // scurrency_type='',����
   BCSetStringFieldByName(m_bc,0,"scurrency_type","1"); // RMB
   // sstatus0='',���ɺϼ�
   BCSetStringFieldByName(m_bc,0,"sstatus0","0"); // ��Ҫ�ϼ�


   UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
   // ��Ϊ����Ӧ������׼��

   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);  // �������ڶ��ظ���������ν������ѡ����TryCallSvr
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

   // �ȴ�ԭʼ�����л�� RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
      strcpy(reqid,"NONE");
   }

   // Ӧ���ǵ���¼��:
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
   if (m_ugdata.sAccount[0])
   {
      FIXDataAddTag(m_fh,TAG_Account,m_ugdata.sAccount,0);
   }
   FIXDataAddTag(m_fh,TAG_PresentRetNum,"1",0);
   FIXDataAddTag(m_fh,TAG_NextFlag,"N",0);  // ��Ϊ�ǵ���¼

   // damt3='',���ս��
   BCGetStringFieldByName(m_bc,0,"damt3",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8081,fvalue,0);

   // damt26='',�����ʽ�
   BCGetStringFieldByName(m_bc,0,"damt26",fvalue,sizeof(fvalue));
   FIXDataAddTag(m_fh,8084,fvalue,0);
   
   dv = atof(fvalue);
   // ?? ��ȡ�ʽ� �ͼ򵥵� �ÿ����ʽ�����:
   // ���� - ��Ѻ��� - ���� - ƽ�� - ���ý��
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
   return(g_KSFTS.SendToFIXSvr(m_fixmsg));
}

int COutThread::QueryPositionStatus()  // �����Ϊ���¼���صĲ�ѯ����
{
   char fvalue[256];
   int rtn;
   int i,n;
   char *ps2;
   char reqid[40];
   
   // �ȴ�ԭʼ�����л�� RequestID
   rtn = sizeof(reqid);
   if (FIXDataGetTag(m_fh,TAG_RequestID,reqid,&rtn)<0)
   {
      strcpy(reqid,"NONE");
   }

   BCResetHandle(m_bc);
   BCSetRequestType(m_bc,854048);  // ��ѯ�ͻ��ֲ�״̬
   BCSetStringFieldByName(m_bc,0,"scust_no", g_KSFTS.GetOperator());          //����Ա
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no",GetClientNo(m_ugdata.sClientID,fvalue)); // �ͻ���	sholder_ac_no
   // ���ױ���	sholder_ac_no2
   BCSetStringFieldByName(m_bc,0,"sholder_ac_no2",m_ugdata.sAccount); 
   // ��Լ��	scust_auth
   BCSetStringFieldByName(m_bc,0,"scust_auth",m_ugdata.sSymbol);
   // ��������	sstatus2
   switch (m_ugdata.sSide[0])
   {
   case '1':
   case '2':
      fvalue[0] = m_ugdata.sSide[0]-1;  // 1->0;2->1 
      fvalue[1] = '\0';
      BCSetStringFieldByName(m_bc,0,"sstatus2",fvalue);
      break;
   default:
      // ����
      break;
   }

   // sstatus3='',�Ƿ�����ϼƱ��--1�����С�ƺͺϼƣ�����ֵ�����С�ƺͺϼ�
   BCSetStringFieldByName(m_bc,0,"sstatus3","1");
   // sstatus0='',���ܱ��--0��������ܣ�1�������
   BCSetStringFieldByName(m_bc,0,"sstatus0","0");

   UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
   // ��Ϊ����Ӧ������׼��
   
   rtn = g_KSFTS.TryCallSvr(m_bc,fvalue);  // �������ڶ��ظ���������ν������ѡ����TryCallSvr
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

   // UG_UGDataReturn(&m_ugdata);  // ��m_ugdata�еļ�����Ϣ���ݷ���תһ�£���Ϊ�������Ӧ���Ǳ����
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
         STRNCPY(m_ugdata.sSecurityExchange,g_KSFTS.GetExchange(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_SecurityExchange,m_ugdata.sSecurityExchange,0);
         // sholder_ac_no2='',���ױ���
         BCGetStringFieldByName(m_bc,i,"sholder_ac_no2",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         FIXDataUpdateTag(m_fh,-1,TAG_Account,fvalue,0);
         //  sstock_code='',Ʒ�ִ���  "al"
         BCGetStringFieldByName(m_bc,i,"sstock_code",fvalue,sizeof(fvalue));
         mytrim(fvalue);
         for (ps2=fvalue;*ps2;++ps2);
         //ps2 = strstr(fvalue,"");  // �ҵ�����λ�ã��Ժ�ӡ������ڡ���������ɺ�Լ��
         //  sdate1='',������
         BCGetStringFieldByName(m_bc,i,"sdate1",ps2,100);
         mytrim(ps2);
         FIXDataUpdateTag(m_fh,-1,TAG_Symbol,fvalue,0);
         // sstatus4='',Ͷ�����
         BCGetStringFieldByName(m_bc,i,"sstatus4",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_HedgeFlag,fvalue,0);
         // sstatus2='',��������
         BCGetStringFieldByName(m_bc,i,"sstatus2",m_ugdata.sSide,sizeof(m_ugdata.sSide));
         m_ugdata.sSide[0] += 1;  // '0'->'1'; '1'->'2' 
         FIXDataUpdateTag(m_fh,-1,TAG_Side,m_ugdata.sSide,0);
         // lvol5='',�ֲ�����
         BCGetStringFieldByName(m_bc,i,"lvol5",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,53,fvalue,0);  // Quantity
         if (m_ugdata.sSide[0]=='1')
         {
            // ��ֲ�:
            FIXDataUpdateTag(m_fh,-1,704,fvalue,0); // Long Quantity
            strcpy(fvalue,"0");
            FIXDataUpdateTag(m_fh,-1,705,fvalue,0); // Short Quantity
         }
         else
         {
            // ���ֲ�:
            FIXDataUpdateTag(m_fh,-1,705,fvalue,0); // Short Quantity
            strcpy(fvalue,"0");
            FIXDataUpdateTag(m_fh,-1,704,fvalue,0); // Long Quantity
         }
         // damt23='',���¼�
         BCGetStringFieldByName(m_bc,i,"damt23",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_Price,fvalue,0);  // Price
         // damt21='',�ֲ־���: Ϊ������
         // damt26='',���־���  -- ��ʵ�ʵĳֲֳɱ���
         BCGetStringFieldByName(m_bc,i,"damt26",fvalue,sizeof(fvalue));
         FIXDataUpdateTag(m_fh,-1,TAG_AvgPx,fvalue,0);  // AvxPx
         // ��ʱ�ȸ�����ЩTAG���ˡ�
         //////////////////////////////////////////////////////////////////////////
         FIXDataGetFIXData(m_fh,m_fixmsg,sizeof(m_fixmsg));
         g_KSFTS.SendToFIXSvr(m_fixmsg);
      }
      if (!BCHaveNextPack(m_bc))
         break; // �����ˣ�û�к������ݼ�¼��
      if (g_KSFTS.CallNext(m_bc,fvalue)<0)
      {
         return(ReturnRequestRejected(944,fvalue));  // �þܾ�������
      }
   } while (1);
   return(n);
}


