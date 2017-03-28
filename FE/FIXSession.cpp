// FIXSession.cpp: implementation of the CFIXSession class.
// 2012/4/3 10:36:10 �Ӵ��Ժ�FIXIII2012�汾��������OrigClOrdID��ClOrdID��������OrderID����ΪSS_OData�Ĺؼ���
//       
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "fixbase.h"
#include "StdAfx_Fmi.h"
#include "FIXEngine.h"
#include "UDLInterface.h"
#include "ugate.h"

extern unsigned int g_iInWait;
extern unsigned int g_iOutWait;


//////////////////////////////////////////////////////////////////////
// COrderData Class
//////////////////////////////////////////////////////////////////////
bool MaySendCancel(unsigned char bmCancel)
{
   return ((bmCancel&0x01)==0 // ���ǵ� unsolicited cancel �����
      ||(bmCancel&0x02));
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COrderData::COrderData()
{
   OrderQty = CumQty = 0;
   bmCancel = 0;
   SentSeqNo = -1;
}

COrderData::COrderData(const COrderData &copyData)
{
   ClOrdID = copyData.ClOrdID;
   OrderQty = copyData.OrderQty;
   CumQty = copyData.CumQty;
   bmCancel = copyData.bmCancel;
   SentSeqNo = copyData.SentSeqNo;   
}


COrderData::~COrderData()
{
   
}

//////////////////////////////////////////////////////////////////////
// COrdExec Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COrdExec::COrdExec()
{
   ExecType = 0;
   CumQty = 0;
}


COrdExec::COrdExec(const COrdExec &copyExec)
{
   ExecType = copyExec.ExecType;
   ExecID = copyExec.ExecID;
   CumQty = copyExec.CumQty;
   FIXMsg = copyExec.FIXMsg;   
}

COrdExec::~COrdExec()
{
   
}


// FIX Session Out Thread Entry:
void OThreadRun(void *pAvg)
{
   CFIXSession *pSession = (CFIXSession *)pAvg;
   if (pSession!=NULL)
   {
      pSession->OTRun();
   }
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIXSession::CFIXSession()
{
   m_LastStatus = FS_DISABLE;
   m_InMsgSeqNo = 0;
   m_reload = 0;
   memset(m_sStatusMsg,0,sizeof(m_sStatusMsg));
   strcpy(m_sStatusMsg,"Not started!");
   //m_StatusMsg = "Not started!";
   m_OTRunTime = 0;
   m_InOpen = false;
   m_InMsgs = m_OutMsgs = 0;
}

CFIXSession::~CFIXSession()
{

}

void CFIXSession::Set(const char *sLocalID, const char *sPartnerID)
{
   m_LocalID = sLocalID;
   m_PartnerID = sPartnerID;
}



void CFIXSession::HaveOutMsg(int msglen, const char *msg, int plevel)
{
/* Removed by CHENYH @ 2012/8/24 17:13:26
   CMsgData mdata(msglen,msg);
   plevel = plevel ? 1:0;
   outMsgMutexEvent.Lock();
   outMsgs[plevel].push_back(mdata);
   if (outMsgs[0].size()+outMsgs[1].size()<2)
      outMsgMutexEvent.SetEvent();
   outMsgMutexEvent.UnLock();
*/
   UG_HaveOutMsg(m_PartnerID.c_str(),msg,plevel);
}

//DEL int CFIXSession::GetInMsg(char *msgbuf)
//DEL {
//DEL    int len;
//DEL    L_MSGDATA::iterator lmit;
//DEL    inMsgMutexEvent.Lock();
//DEL #if 1
//DEL    int i;
//DEL    for (i=0;i<100;++i)
//DEL    {
//DEL       if (inMsgs.size()>0)
//DEL          break;
//DEL       inMsgMutexEvent.WaitEventTime(g_iInWait);  // 2010-6-24 10:46:15 ��10 ��Ϊ g_iInWait
//DEL    }
//DEL #else
//DEL    //if (inMsgs.size()<=0)
//DEL    inMsgMutexEvent.WaitEventTime(10);
//DEL #endif
//DEL    lmit = inMsgs.begin();
//DEL    if (lmit==inMsgs.end())
//DEL    {
//DEL       inMsgMutexEvent.UnLock();
//DEL       return(0);
//DEL    }
//DEL    len = lmit->msglen;
//DEL    if (len>0)
//DEL    {
//DEL       memcpy(msgbuf,lmit->msgbuf,len);
//DEL       msgbuf[len]=0;
//DEL    }
//DEL    inMsgs.pop_front();
//DEL    inMsgMutexEvent.UnLock();
//DEL    return(len);
//DEL }

//DEL int CFIXSession::GetOutMsg(char *msgbuf)
//DEL {
//DEL    len = UG_GetOutMsg(m_PartnerID.c_str(),g_iOutWait,msgbuf);
//DEL    int len;
//DEL    L_MSGDATA::iterator lmit;
//DEL    int i;
//DEL    outMsgMutexEvent.Lock();
//DEL    for (i=0;i<100;++i)
//DEL    {
//DEL       if (outMsgs[0].size()>0 || outMsgs[1].size()>0)
//DEL          break;
//DEL       outMsgMutexEvent.WaitEventTime(g_iOutWait); // 2010-6-23 15:50:42 ��10 ��Ϊ g_iOutWait
//DEL       if (m_bStop)
//DEL          break;
//DEL    }
//DEL    lmit = outMsgs[0].begin(); i=0;
//DEL    if (lmit==outMsgs[0].end())
//DEL    {
//DEL       lmit = outMsgs[1].begin(); i=1;
//DEL       if (lmit==outMsgs[1].end())
//DEL       {
//DEL          outMsgMutexEvent.UnLock();
//DEL          return(0);
//DEL       }
//DEL    }
//DEL    len = lmit->msglen;
//DEL    if (len>0)
//DEL    {
//DEL       memcpy(msgbuf,lmit->msgbuf,len);
//DEL       msgbuf[len]=0;
//DEL    }
//DEL    outMsgs[i].pop_front();
//DEL    outMsgMutexEvent.UnLock();
//DEL    return(len);
//DEL }

// ���Ǵ򿪱�Session��ָ��ͬ������
// �Ա��FS�������л���������
bool CFIXSession::PreOpen(char *eMsg)
{
   // 1. ���ԭ��������
//    inMsgs.clear();
//    outMsgs[0].clear();
//    outMsgs[1].clear();

   SS_OData.clear();

   // 2. �ȼ�鴦��DFD �� EOD
   // BatchProcess(); -- ���Ӧ����UG�����߳�����ɣ���Ҫ������ȥ������
   // 3. �ָ�OUT��Ϣ
   RestoreOutFIXMsgs();
   // 4. �ָ�IN��Ϣ
   RestoreInFIXMsgs();
   return(true);
}

int CFIXSession::UpdateSSData(T_UGDATA *pUGData, const char *fixmsg)
{
   IT_ORDDATA iod;

   // ����ֻ��OUT�� MsgType='8' or '9'����Ϣ������Ҳ��IN��'F'/'G'
   if (pUGData->sExecType[0]=='I'
      ||pUGData->sExecTransType[0]=='3'
      ||memcmp(pUGData->sExecID,"0d-",3)==0 // 2012/6/10 20:51:57 ErrNo=60102:Duplicated ClOrdID �Ծܾ���ʽ֪ͨ�Է�
	  ||(pUGData->sPossResend == 'Y')     // 2017/01/24 ADD BY XJF 20170124 �������Ƶ����ݣ�����Ҫ�κ�У��ֱ�����ͻ�FIX���ַ�����
	  )  
   {
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg)); // ������ͨ��״̬��ѯ�࣬û����ɶ
   }
   CPMUTEX pMutex(&m_SSDMutex);
   // '8' or '9'
   iod = CheckSSOrderData(pUGData);
   if (iod==SS_OData.end())
   {
      // ����Ӧ����sOrderIDΪ�յ�������úúò������������
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
   }
   if (strcmp(pUGData->sMsgType,"9")==0)
   {
      // ���ڳ��������ǰ��� ClOrdID=OrigClOrdID�����ж��Ƿ���ҪPendingCancel��Ϣ�ȷ��͵ģ�
      // ���ٲ��� HaveInCancel ������ 0x01�ˡ�2012/4/3 11:02:54
      //iod->second.bmCancel &= 0xFE;  // ȥ�� �������ر��
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
   }
   else if (pUGData->lExecNoCnt<=iod->second.SentSeqNo)
   {
      /***********************************************
      2012/4/3 12:05:20 ��������Ȳ����������Ƿ�������?
      // �������ڸ���Ϣ���ظ����ܣ����Ժ����ģ��͸ñ�����
      // ��KSMBCC�����͹����У��п��ܳ����������
      if ((iod->second.bmCancel&0x10)==0x10
         && memcmp(pUGData->sExecID,"0d-",3)==0)
      {
         // ���ظ������ŵ����⴦���á�0d-����ʾ�ظ������ŷ���: 2011-09-06
         iod->second.bmCancel &= 0x0F;  // ȥ��0x10����ʾԭʼ�ط��Ѵ���
         return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
      }
      */
      if (fixmsg!=NULL)  // Ϊ�˰�ȫ���ӵ��ж�
      {
         UG_WriteLog(8884,"FIX-OutMsg not be sent.(%s)",fixmsg);
      }
      return(0); 
   }
   if (pUGData->lExecNoCnt>=CANCELEDSNO)
   {
      if (pUGData->sClOrdID[0]!='\0' && strcmp(pUGData->sOrigClOrdID,pUGData->sClOrdID))
      {
         // ����Ҫ�ȷ���Pending Cancel��Ϣ
         iod->second.bmCancel |= 0x01;
      }
   }
   if (pUGData->lExecNoCnt>=CANCELEDSNO  // ����FIXIII201204�Ժ󣬲��ٻ���ִ�����Ϊ999999��
      && pUGData->dCumQty-iod->second.CumQty<MIN_QTY
      && (iod->second.SentSeqNo>0  // 2009-9-8 10:55:46 SLJ����������New Confirmation���ͺ���ܷ��Ͱ��� unsolicited cancel
         && MaySendCancel(iod->second.bmCancel)
      || pUGData->lDays>0) // ���Ѿ�����Ϣ�����Է��ˣ���ΪGTn����Ϣ�ĺ�����
      )
   {
      iod->second.SentSeqNo = pUGData->lExecNoCnt;
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
   }
   L_ORDEXEC::iterator ioe,ioe1;
   if (pUGData->lExecNoCnt>iod->second.SentSeqNo+1)
   {
      COrdExec exdata;
      exdata.ExecType = pUGData->sOrdStatus[0];
      exdata.ExecID = pUGData->lExecNoCnt;
      exdata.CumQty = pUGData->dCumQty;
      if (fixmsg!=NULL)
         exdata.FIXMsg = fixmsg;
      // ��˳����뵽ExecList��
      for (ioe=iod->second.ExecList.begin();ioe!=iod->second.ExecList.end();++ioe)
      {
         if (ioe->ExecID>exdata.ExecID)
            break;
         if (ioe->ExecID==exdata.ExecID)
            return(0); // �Ѿ������ˣ�û�б�Ҫ�ٴ�����ȥ��
      }
      if (ioe==iod->second.ExecList.end())
         iod->second.ExecList.push_back(exdata);
      else
         iod->second.ExecList.insert(ioe,exdata);
      return(0); // ��������ȥ�ˣ���ΪҲ���÷��͸�FE
   }
   // else  pUGData->lExecNoCnt==iod->second.SentSeqNo+1
   //-------------------------------------------------------------
   // �Ƚ�����Ϣ��Partner(BuySide)����:
   g_FIXEngine.SendFIXMessage2FE(fixmsg);
   iod->second.SentSeqNo = pUGData->lExecNoCnt;
   /* Removed by CHENYH @ 2013/8/16 17:53:36
   ����������£���ExecType=G : Trade Correct ��D = Restated��ʱ�򣬾ͻᵼ��CumQty���С��
   if (iod->second.CumQty<pUGData->dCumQty)
      iod->second.CumQty = pUGData->dCumQty;
   ****************************************/
   iod->second.CumQty = pUGData->dCumQty;
   //////////////////////////////////////////////////////////////////////////
   switch (pUGData->sOrdStatus[0])
   {
   case '6':  // Pending Cancel
      iod->second.bmCancel |= 0x02;
      break;
   }
   // ���������Ƿ��б��������ϢҲҪ�����͵�:
   for (ioe=iod->second.ExecList.begin();ioe!=iod->second.ExecList.end();)
   {
      ioe1=ioe++;
      if (ioe1->ExecID==iod->second.SentSeqNo+1
         ||(ioe1->ExecID>=CANCELEDSNO // ����FIXIII201204�Ժ󣬲��ٻ���ִ�����Ϊ999999��
         && ioe1->CumQty-iod->second.CumQty<MIN_QTY
         && (iod->second.SentSeqNo>0  // 2009-9-8 10:55:46 SLJ����������New Confirmation���ͺ���ܷ��Ͱ��� unsolicited cancel
         || iod->second.nDays>0)
         && MaySendCancel(iod->second.bmCancel)))
      {
         iod->second.SentSeqNo = ioe1->ExecID;
         iod->second.CumQty = ioe1->CumQty;
         switch (ioe1->ExecType)
         {
         case '6': // 6 = Pending Cancel (e.g. result of Order Cancel Request)
            iod->second.bmCancel |= 0x02;
            break;                     
         }
         g_FIXEngine.SendFIXMessage2FE(ioe1->FIXMsg.c_str());
         iod->second.ExecList.erase(ioe1);
      }
      else 
         break; // ���������ÿ���ȥ��
   }
   return(0);
   //-------------------------------------------------------------
}



IT_ORDDATA CFIXSession::CheckSSOrderData(T_UGDATA *pUGData)
{
   IT_ORDDATA iod;
#if 1  // FIXIII-201204  ���ڳ����˸ĵ��������ˣ�OrigClOrdIDһֱ���ֲ����ˣ�ֻ��OrderID�����
   if (pUGData->sOrderID[0]=='\0')
   {
      UG_WriteLog(20403,"No OrderID for CheckSSOrderData(%s:%s|%s-%s)",
         m_PartnerID.c_str(),pUGData->sOrigClOrdID,pUGData->sClOrdID,pUGData->sMsgType);
      return(SS_OData.end());
   }
   iod = SS_OData.find(string(pUGData->sOrderID));
   if (iod!=SS_OData.end())
      return(iod); // �ҵ���
   COrderData order;
   order.ClOrdID = pUGData->sOrigClOrdID[0]!='\0'? pUGData->sOrigClOrdID:pUGData->sClOrdID;
   order.OrderQty = pUGData->dOrderQty;
   order.nDays = pUGData->lDays;
   iod = SS_OData.insert(make_pair(string(pUGData->sOrderID),order)).first;
   return(iod);
#else
   char *clordid;
   if (pUGData->sOrigClOrdID[0]!='\0')
      clordid = pUGData->sOrigClOrdID;
   else
      clordid = pUGData->sClOrdID;
   iod = SS_OData.find(string(clordid));
   if (iod!=SS_OData.end())
      return(iod); // �ҵ���
   COrderData order;
   order.ClOrdID = clordid;
   order.OrderQty = pUGData->dOrderQty;
   iod = SS_OData.insert(make_pair(string(clordid),order)).first;
   return(iod);
#endif
}

void CFIXSession::RestoreOutFIXMsgs()
{
   L_MSGDATA pmlist;  // FE�е���Ϣ��������
   L_MSGDATA::iterator iml,nml;
   T_UGDATA ugdata;
   // �Ȼ�ȡ���ص�OUT��Ϣ������:
   //    BuySide - ExecReport(CancelReject)
   //    SellSide - NewOrderSingle(D) / OrderCancelRequest(F)
   int n = g_FIXEngine.ReadFEMsgData("OUT",m_PartnerID.c_str(),pmlist);
   for (iml=pmlist.begin();iml!=pmlist.end();)
   {
      nml = iml++;
      if (UG_FIXMsg2UGData(nml->msgbuf,nml->msglen,&ugdata,NULL,0)>0)
      {
         // ����������FIX��Ϣ:
         if (strcmp(ugdata.sMsgType,"8")==0
            ||strcmp(ugdata.sMsgType,"9")==0)
         {
            UpdateSSData(&ugdata,NULL);  // ����������SS_OData����״̬�б�
//             pmlist.erase(nml);  // �����BSOut�ָ�Ҳ��Ҫ��Щ����
         }
//          ���� ��8������9���⣬���ȱ���������Ϊ�˱Ƚ�
//          // ��ֻ������ ->SellSide - NewOrderSingle(D) / OrderCancelRequest(F)
//          // Ϊ�����Ӻ�̨�ָ��� ->SellSide����Ϣ�����Ƚϣ������ظ�����
//          if (strcmp(ugdata.sMsgType,"D")
//             && strcmp(ugdata.sMsgType,"F"))
//          {
//             pmlist.erase(nml); // ɾ����Щ�����Ѿ��Ǽ���SS_OData�еĻ��߲���Ҫ�ָ�����Ϣ
//          }
      }
      else
      {
         pmlist.erase(nml);
      }
   }
   // ��ƽ̨�����ȡ��SellSide����(��û�еõ��Է�����)��NewOrderSingle(D) / OrderCancelRequest(F)
   L_MSGDATA lmlist;   // ƽ̨��Ҫ���͸�SellSide��δ������Ϣ
   UG_GetSSPendingOrders(m_PartnerID.c_str(),lmlist);
   for (iml=lmlist.begin();iml!=lmlist.end();++iml)
   {
      for (nml=pmlist.begin();nml!=pmlist.end();++nml)
      {
         if (UG_FIXMsgKeyTagCmp(iml->msgbuf,nml->msgbuf)==0)
            break;
      }
      if (nml!=pmlist.end())
      {
         // ��ƥ���: ����ʾ����Ϣ�Ѿ����͸��˶�����
         pmlist.erase(nml);  // �����������˰�:)
      }
      else
      {
         // ��FE�ˣ�û�ҵ������Ϣ: ��Ҫ�ύ��FE
         HaveOutMsg(iml->msglen,iml->msgbuf,0);  // ��Щ��ί�С�������������Ҫ�� 0�����ȣ���ߣ�
      }
   }
   lmlist.clear(); // ������ˣ��Ǻ�
   UG_GetBSExecRepts(m_PartnerID.c_str(),lmlist);
   for (iml=lmlist.begin();iml!=lmlist.end();++iml)
   {
      for (nml=pmlist.begin();nml!=pmlist.end();++nml)
      {
         if (UG_FIXMsgKeyTagCmp(iml->msgbuf,nml->msgbuf)==0)
            break;
      }
      if (nml!=pmlist.end())
      {
         // ��ƥ���: ����ʾ����Ϣ�Ѿ����͸��˶�����
         pmlist.erase(nml);  // �����������˰�:)
      }
      else
      {
         // ��FE�ˣ�û�ҵ������Ϣ: ��Ҫ�ύ��FE
         HaveOutMsg(iml->msglen,iml->msgbuf,0);  // ��Щ��ί�С�������������Ҫ�� 0�����ȣ���ߣ�
      }
   }
   lmlist.clear();
   pmlist.clear();
}

#define EOD_RESETNUMBER 3 
int CFIXSession::DoEODProcess()
{
   int rtn;
   CPMUTEX pMutex(&m_SSDMutex);
   SS_OData.clear(); 
   /* Removed by CHENYH @ 2013/5/6 11:27:51
   ���־�����m_InOpen=true, ����GL����:GL:0:0:(1)RC0-close:1:1 ״̬��ʱ��ִ��g_FIXEngine.DoEOD���ᵼ��FE���쳣��
   ��ˣ��������������ʽ���ж��Ƿ����ִ��g_FIXEngine.DoEOD
   if (!m_InOpen)
   ***************************************/
   if (m_LastStatus<FS_CONNECTING)  // 2013/5/6 11:31:52 -- ��Ϊ��������жϣ��Է�ֹFE�ڲ��Ѿ�Close�ˣ���ʱFE�Ѿ�û��Session�ˣ�
   //////////////////////////////////////////////////////////////////////////
   {
      // 2012/12/20 0:18:57 ��Ϊ�������ResetFIXSessionData���Ի�óɹ�
      for (rtn=0;rtn<EOD_RESETNUMBER;++rtn)
      {
         if (g_FIXEngine.ResetFIXSessionData(m_PartnerID.c_str()))
            break;
         mysleep(500);
      }
      if (rtn>=EOD_RESETNUMBER)
      {
         UG_WriteLog(81900,"Fail to Reset FIXSessionData(%s)",m_PartnerID.c_str());
      }
      m_bToEOD = true;
   }
   else
   {
      UG_WriteLog(1854,"FIXSession(%s) do EOD",m_PartnerID.c_str());
      rtn = g_FIXEngine.DoEOD(m_PartnerID.c_str()); 
      UG_WriteLog(1855,"FIXSession(%s) EOD Done:%d",m_PartnerID.c_str(),rtn);
      m_bToEOD = false;
   }
   // if (rtn>=0)  �������Ƿ�����EOD����Reset��Щֵ 2013/4/27 14:33:18
   {
      m_InMsgSeqNo = 0;
      m_InMsgs = m_OutMsgs = 1;
   }
   return(rtn);
}

void CFIXSession::RestoreInFIXMsgs()
{
   L_MSGDATA pmlist;  // FE�е���Ϣ��������
   L_MSGDATA::iterator iml;
   // �Ȼ�ñ��ص�IN��Ϣ������:
   //    BuySide - NewOrderSingle(D) / OrderCancelRequest(F)  UG_ORDERS
   //    SellSide - ExecReport / CancelReject  UG_SSEXEC
   g_FIXEngine.ReadFEMsgData("IN",m_PartnerID.c_str(),pmlist);
   for (iml=pmlist.begin();iml!=pmlist.end();++iml)
   {
      RestoreInMsg(iml->msglen,iml->msgbuf);
   }
}

int CFIXSession::RestoreInMsg(int msglen, const char *fixmsg)
{
   T_UGDATA ugdata;
   if (UG_FIXMsg2UGData(fixmsg,msglen,&ugdata,NULL,0)>0)
   {
      // ����������FIX��Ϣ:
      if (ugdata.lMsgSeqNum>m_InMsgSeqNo)
         m_InMsgSeqNo = ugdata.lMsgSeqNum;
      else
         return(0);  // �Ѿ��������

      if (strcmp(ugdata.sMsgType,"D")==0  // NewOrderSingle
         || strcmp(ugdata.sMsgType,"E")==0  // NewOrderList
         || strcmp(ugdata.sMsgType,"F")==0  // OrderCancelRequest
         || strcmp(ugdata.sMsgType,"G")==0)  // Order Cancel/Replace Request
      {
         // ��Щ��Ҫ��Ϣ�������·���һ�Σ�����
      }
      else if (strcmp(ugdata.sMsgType,"8")==0)  // Execution Report
      {
         // ��������״̬������Ϣ
         if (strcmp(ugdata.sExecType,"I")==0
            ||strcmp(ugdata.sExecTransType,"3")==0)
            return(0);
      }
      else if (strcmp(ugdata.sMsgType,"9")==0)  // Order Cancel Rejected
      {
         // ��MsgType=8��ʵ�ʵ�ִ����Ϣ��ͬ����
      }
      else 
         return(0); // ������Ϣ�ͺ�����
      // ��Щ���������ģ�����Ҫ�ָ�
      UG_RestoreFIXInMsg(NULL,fixmsg); // ��NULL����m_PartnerID.c_str()����Ϊ����Ҫ������FIXEngine����Ϣ����SenderCompID��ֵ��
   }
   return(0);
}

int CFIXSession::GetReloadCount()
{
   return(m_reload++);
}

void CFIXSession::StatusChanged(int newState, int oldState, int reasonCode, const char *reasonText)
{
   char statusinfo[300];  // statusinfo��ʽΪ: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
   int len;

   SNPRINTF(statusinfo,sizeof(statusinfo),"RC%d-%s",reasonCode,reasonText!=NULL?reasonText:"NULL");
   SetError(newState,statusinfo,m_InMsgs,m_OutMsgs);
   len = sprintf(statusinfo,"%s|",
      m_LocalID.c_str());
   GetStatusInfo(statusinfo+len,sizeof(statusinfo)-len);
   UDLHaveChannelStatusInfo(statusinfo);
}


int CFIXSession::GetStatusInfo(char *statusinfo, unsigned int sisize)
{
   // <PartnerID1>:<status>:<load>:<errmsg>
#if 1  // 2013/4/24 15:37:07
   return(sprintf(statusinfo,"%s:%d:%u:(%d)%s:%d:%d",
         m_PartnerID.c_str(),m_LastStatus,GetLoad(),
         (int)(time(NULL)-m_OTRunTime),m_sStatusMsg,
         m_InMsgs,m_OutMsgs));
#else
   int length;
   {
      length = sprintf(statusinfo,"%s:%d:%u:%s:%d:%d",
         m_PartnerID.c_str(),m_LastStatus,GetLoad(),m_StatusMsg.ctr(),m_InMsgs,m_OutMsgs);
      //Strncpy(statusinfo+length,m_StatusMsg.c_str(),sisize-length);
   }
   char *pc;
   pc = strstr(statusinfo+length,"\n");
   if (pc!=NULL)
      *pc='\0';
   pc = strstr(statusinfo+length,"|");
   if (pc!=NULL)
      *pc='\0';
   return(length+strlen(statusinfo+length));
#endif
}

// 2013/4/25 16:35:09 �ں�ͨUAT�����ڻ�ȡFIXSTAT��ʱ�򣬻ᴮ���ݣ�����A-Session��״̬���ݣ�������B-Session����
// ����FE�еĶԸýӿڶ��̲߳���ȫ�ġ���ˣ�ʹ��ȫ�ֶ�����CMUTEX����:
CMUTEX g_FIXMutex;

void CFIXSession::OTRun()
{
   int msglen;
   T_UGDATA ugdata;
   time_t lstime=-1;
   bool bReflush=true;
   m_bStop = false;
   UG_WriteLog(801,"FIXSession(%s) OutThread Started",m_PartnerID.c_str());
   while (1)
   {
      // 2013/4/27 18:33:48 ���ֵ�GL��FE�ڲ��Զ�Close��Ȼ�����Զ���EOD��ʱ�򣬱��߳��п��ܻ����Block�����
      // Ϊ�ˣ��ر������һ��״̬Ϊ��Open״̬�����ܾ��崦����Щ��������!!!!!
      m_OTRunTime = time(NULL); // ��ʾ���߳�������
      if (m_bStop)
         break;
      if (m_LastStatus>FS_CONNECTING)  // 2013/4/27 18:33:48 ������δ����֮ǰ��ʵ�ʴ����״̬��ѯ����
      {
         msglen = UG_GetOutMsg(m_PartnerID.c_str(),g_iOutWait,m_OutMsg);
         if (msglen>0 && UG_FIXMsg2UGData(m_OutMsg,msglen,&ugdata,NULL,0)>0)
         {
            if (strcmp(ugdata.sMsgType,"8")==0
               ||strcmp(ugdata.sMsgType,"9")==0)
               UpdateSSData(&ugdata,m_OutMsg);
            else
               g_FIXEngine.SendFIXMessage2FE(m_OutMsg);
            if (m_OTRunTime>lstime+4) // ��ʹ��æҲҪ���¼��״̬
               bReflush = true;
         }
         // 2013/4/24 16:07:42 Added Status updated
         else
         {
            if (m_OTRunTime>lstime) // ���е�ʱ������ÿ�����һ��
               bReflush = true;
         }
         if (bReflush)
         {
            if (g_FIXMutex.TryLock()!=0)  // 2013/4/25 16:57:05
            {
               ReflushStatus();
               g_FIXMutex.UnLock();
               lstime = m_OTRunTime;
               bReflush = false;
            }
         }
         //////////////////////////////////////////////////////////////////////////
      }
      else  // 2013/4/27 18:33:48 ������δ����֮ǰ��ʵ�ʴ����״̬��ѯ����
      {
         mysleep(500);
      }
      /////// End of  2013/4/27 18:33:48 ������δ����֮ǰ��ʵ�ʴ����״̬��ѯ����
   }
   m_OTRunTime = 0; // ��ʾ���߳��˳���
   UG_WriteLog(802,"FIXSession(%s) OutThread Stopped",m_PartnerID.c_str());
}

void CFIXSession::ToStopThreads()
{
   // Ŀǰ�滮ֻ��һ��OutThread
   time_t tb = time(NULL);
   m_bStop = true;

//    outMsgMutexEvent.Lock();
//    outMsgMutexEvent.SetEvent();  // Ҫ��OThread�˳�������������ˡ�����
//    outMsgMutexEvent.UnLock();

   while (m_OTRunTime>0)
   {
      if (time(NULL)>tb+1+g_iOutWait/1000)
         break;
   }
}

bool CFIXSession::IsRun()
{
   return(m_OTRunTime>0);
}

void CFIXSession::SetError(int status, const char *eMsg, int inmsgs, int outmsgs)
{
   m_LastStatus = status;
   m_InMsgs = inmsgs;
   m_OutMsgs = outmsgs;
#if 1 // 2013/4/24 15:40:40   
   if (eMsg!=NULL)
   {
      int i,n;
      n = sizeof(m_sStatusMsg)-1;
      for (i=0;i<n;++i)
      {
         if (eMsg[i]=='\0'
            ||eMsg[i]=='\n'
            ||eMsg[i]=='|')
            break;
         m_sStatusMsg[i] = eMsg[i];
      }
      m_sStatusMsg[i]='\0';
   }
#else
   m_StatusMsg = eMsg;
#endif
}

bool CFIXSession::IsLoadFESession()
{
   return(m_reload>0);
}

unsigned int CFIXSession::GetLoad()
{
   return(UG_GetOutMsgSize(m_PartnerID.c_str()));
//   return(outMsgs[0].size()+outMsgs[1].size());
}

bool CFIXSession::IsNewInMsg(int msgseqnum)
{
   if (msgseqnum>m_InMsgSeqNo)
   {
      m_InMsgSeqNo = msgseqnum;
      return(true);
   }
   return(false);
}


int transState(int oldState);

// 2013/4/24 15:45:38 Ϊ�˱��������߳��У�Ҫͨ��FEȥˢ��״̬���±�Blockס!
void CFIXSession::ReflushStatus()
{
   g_FIXEngine.ReflushStatus(this);
#if 0 // �����ƺ�Ҫcore��
   CFixStatus m_fixStat; // 2013/4/24 14:40:30 Ϊ�˽�Session�ڲ�״̬��ȡ��ת��OThread�У�����Ӱ������Session���������Ƶ�
   SetError(transState(m_fixStat.getFixState()),
      m_fixStat.getStateReasonText().c_str(),
      m_fixStat.getExpectedInSeqNum(),
      m_fixStat.getExpectedOutSeqNum());
#endif
}


// Function name: CFIXSession::CheckEODAfterOpen
// Author       : CHENYH 2013/4/27 14:48:08
// Description  : �����ڹر�״̬�£�FS�Ѿ�Ҫ������Session��EOD������Session��û�д򿪣�����ڴ򿪺󣬱�����ִ��FE��EOD
//                ֻ����FE�������򿪱�Session�����, ʵ��ֻ�ܱ�g_FIXEngine��OpenSession��ʱ�����һ��
// Return type  : void 
void CFIXSession::CheckEODAfterOpen()
{
   assert(m_InOpen);
   if (m_bToEOD)
   {
      UG_WriteLog(1852,"FIXSession(%s) do EOD",m_PartnerID.c_str());
      g_FIXEngine.DoEOD(m_PartnerID.c_str());
      m_bToEOD = false;
   }
   UG_WriteLog(1853,"FIXSession(%s) EOD Check-Done!",m_PartnerID.c_str());
}
