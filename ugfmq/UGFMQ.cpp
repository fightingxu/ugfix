/********************************************************************
	created:	2011/10/22
	created:	22:10:2011   21:34
	filename: 	C:\dd\projects\FIXIII\UGate\ugfmq\UGFMQ.cpp
	file path:	C:\dd\projects\FIXIII\UGate\ugfmq
	file base:	UGFMQ
	file ext:	cpp
	author:		CHENYH
	
	purpose:	UGFMQ������KSFMQ(���˴��ļ���Ϣ����)ģʽ����ϵͳ�Խӡ�
      ��ģʽ֧�ֵ�һ�����֣���һ��PartnerID��
      �����ܿ���д�ø���һ�㣬����UGFIX����֧�ֶ�����֣�
      ��ʵ�ʲ����У����������ƺ����ʺ�ʵ�ʵ�����ģʽ��
      ֧�ֶ��ֿ�ΪBuySide��SellSide��

      ����UGate֧�ֵĶ���Ϊ��LocalID -- PartnerID
      ��ͨ��һ��Ŀ¼����ΪFMQ��hostĿ¼��
         ��Ŀ¼�£���������FMQ����(����UGate֧�ֵĴ󶩵����ͣ����¾�����ִ����Ϣ����ˣ��ر�������FMQ����)
         1. <LocalID>ΪBuySide����<PartnerID>ΪSellSide:
            1.1 OR2<PartnerID> -- Ϊ<LocalID>���͸�<PartnerID>�Ķ�����������ϢFMQ��<LocalID> -> <PartnerID>
               ���� MsgType: 'D'; 'F'; 'H'; 'E' �ȣ�����ֱ�ӺͶ����йص�������Ϣ��
               ��: <LocalID>ΪBuySide����<PartnerID>ΪSellSide���йض��������Ϣ���У�
            1.2 OE2<PartnerID> -- Ϊ<PartnerID>���͸�<LocalID>�Ķ���ִ������ϢFMQ��<PartnerID> -> <LocalID>
               ���� MsgType: '8'; '9'; �ȣ�����Ͷ�����ִ����صķ�����Ϣ��
               ��: <LocalID>ΪBuySide����<PartnerID>ΪSellSide���йض��������Ϣ���У�
         2. <PartnerID>ΪBuySide����<LocalID>ΪSellSide:
            2.1 OR2<LocalID> -- Ϊ<PartnerID>���͸�<LocalID>�Ķ�����������ϢFMQ��<PartnerID> -> <LocalID>
            ���� MsgType: 'D'; 'F'; 'H'; 'E' �ȣ�����ֱ�ӺͶ����йص�������Ϣ��
            ��: <PartnerID>ΪBuySide����<LocalID>ΪSellSide���йض��������Ϣ���У�
            2.2 OE2<LocalID> -- Ϊ<LocalID>���͸�<PartnerID>�Ķ���ִ������ϢFMQ��<LocalID> -> <PartnerID>
            ���� MsgType: '8'; '9'; �ȣ�����Ͷ�����ִ����صķ�����Ϣ��
            ��: <PartnerID>ΪBuySide����<LocalID>ΪSellSide���йض��������Ϣ���У�

         3. ������Ϣ�ķ��������:��������Ϣ����Ҫ�ָ���
            3.1 2<LocalID> -- Ϊ<PartnerID>���͸�<LocalID>��������ϢFMQ��<PartnerID> -> <LocalID>
            3.2 2<PartnerID> -- Ϊ<LocalID>���͸�<PartnerID>��������ϢFMQ��<LocalID> -> <PartnerID>
         ���⣬�������������ļ����Ա�ʾ˫������״̬ -- ���öԷ�������Ƿ����ߣ�
            <LocalID>.sts; <PartnerID>.sts


      ��UGateģʽ�£����ڽӿ�֧��ȫ�棬ͳһ������ͬʱ��֧��BuySide��SellSide��
      ��ΪUGate�Ķ��ַ�����FMQģʽ�£��������������������ϵͳ�Խ�ģʽ��
      ��ˣ��Ƚ����������ԣ�FMQ����Ķ�д����������
         ��WinXP�ʼǱ���(ThinkPad X200)�Ͻ����ٶȿɴ��4000��Ϣ/�룻

      ����UGFMQģʽ��UGate������Ϣ���ͺͽ��ճ��ײ����첽����ģ���ˣ�
      ֻҪһ������̺߳�һ�������̼߳��ɣ����е�����̣߳���ΪUGate���
      �е�һ���̣߳���ˣ���ģ���У�ֻҪ������һ�������̼߳��ɡ�
*********************************************************************/
// UGFMQ.cpp: implementation of the CUGFMQ class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "UDLInterface.h"
#include "fixbase.h"
#include "ugate.h"
#include "MsgDataList.h"
#include "UGFMQ.h"

#ifdef _MSC_VER
#include <direct.h>
#define PATHMARK  '\\'
#define MAKEPATH(a) mkdir(a)
#else
#include <sys/types.h>
#include <dirent.h>
#define PATHMARK  '/'
#define MAKEPATH(a) mkdir(a,0777)
#endif

#ifdef _MSC_VER
void InProcess(void *pv)
#else
void *InProcess(void *pv)
#endif
{
   g_UGFMQ.Run();
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUGFMQ::CUGFMQ()
{
   m_Status = 0;  // FS_CLOSE
   m_InRunStatus = 0; // FS_CLOSE;
}

CUGFMQ::~CUGFMQ()
{

}

int CUGFMQ::Initialize()
{
   int rtn;
   char *pc;
   STRNCPY(m_LocalID,UG_GetLocalID());
   STRNCPY(m_PartnerID,UG_GetPartners());
   pc = strstr(m_PartnerID,";");
   if (pc!=NULL)
      *pc = '\0'; // ��ֻ���ǵ�һ��
   UG_INIReadTString("KSFMQ","FMQPATH","fmqhost",m_FMQPath,sizeof(m_FMQPath));
   if (access(m_FMQPath,0)!=0)
      MAKEPATH(m_FMQPath);

   hLocal.Open(m_FMQPath,m_LocalID,true);
   rtn = hPartner.Open(m_FMQPath,m_PartnerID,true); // ����UGate������
   if (rtn<0)
   {
      UG_WriteLog(10000,"Fail to open FMQStatusFile(%s,%s,%s):%d",
         m_FMQPath,m_LocalID,m_PartnerID,rtn);
      return(-1);
   }
   if (OpenAllFMQ()<0)
   {
      // ��һ�δ����ʹ�
      ResetAllFMQ();
      return(OpenAllFMQ());
   }
   return(0);
}

int CUGFMQ::ResetAllFMQ()
{
   char tmp[256];
   sprintf(tmp,"OR2%s",m_PartnerID);
   m_2Partner.Reset(m_FMQPath,tmp);
   sprintf(tmp,"OE2%s",m_LocalID);
   m_2Partner.Reset(m_FMQPath,tmp);

   sprintf(tmp,"OR2%s",m_LocalID);
   m_2Partner.Reset(m_FMQPath,tmp);
   sprintf(tmp,"OE2%s",m_PartnerID);
   m_2Partner.Reset(m_FMQPath,tmp);
   
   sprintf(tmp,"2%s",m_LocalID);
   m_2Partner.Reset(m_FMQPath,tmp);
   sprintf(tmp,"2%s",m_PartnerID);
   return(m_2Partner.Reset(m_FMQPath,tmp));
}

// ��ȡ״̬��Ϣ��ͬʱҲ�ǺͶԷ�����һ����������
// statusmsg-- <PartnerID1>:<status>:<load>:<errmsg>
int CUGFMQ::GetStatus(char *statusmsg, unsigned int smsize)
{
   unsigned int dtime;
   CheckPartnerStatus(); // �������˺ͶԶ˵�״̬��Ϣ
   dtime = hLocal.status.lasttime-hPartner.status.partnertm;
   if (m_Status>FS_CLOSE)
   {
      if (hPartner.status.status==FS_OPEN 
         && dtime<15)  // ���ڶԷ��Ա�����״̬������15��֮��
      {
         sprintf(statusmsg,"%s:%d:%u:(%u)OR2P=%u;OE2L=%u|OR2L=%u;OE2P=%u|2L=%u;2P=%u",
            m_PartnerID,FS_OPEN,hLocal.status.smsgs-hPartner.status.rmsgs,
            hLocal.status.lasttime,
            hLocal.status.sormsgs,hLocal.status.roemsgs,
            hLocal.status.rormsgs,hLocal.status.soemsgs,
            hLocal.status.rmsgs,hLocal.status.smsgs
            );
      }
      else
      {
         sprintf(statusmsg,"%s:%d:%u:(%u)OR2P=%u;OE2L=%u|OR2L=%u;OE2P=%u|2L=%u;2P=%u",
            m_PartnerID,FS_CONNECTING,hLocal.status.smsgs-hPartner.status.rmsgs,
            hLocal.status.lasttime,
            hLocal.status.sormsgs,hLocal.status.roemsgs,
            hLocal.status.rormsgs,hLocal.status.soemsgs,
            hLocal.status.rmsgs,hLocal.status.smsgs
            );
      }
   }
   else
   {
      sprintf(statusmsg,"%s:%d:%u:(%u)Disconnected",
         m_PartnerID,m_Status,hLocal.status.smsgs-hPartner.status.rmsgs,
         hLocal.status.lasttime
         );
   }
   return(0);
}

int CUGFMQ::CheckPartnerStatus()
{
   hLocal.status.sormsgs = m_OR2Partner.Size();
   hLocal.status.soemsgs = m_OE2Partner.Size();
   hLocal.status.smsgs = m_2Partner.Size()+hLocal.status.sormsgs+hLocal.status.soemsgs;

   hLocal.status.rormsgs = m_OR2Local.RMsgs();
   hLocal.status.roemsgs = m_OE2Local.RMsgs();
   hLocal.status.rmsgs = m_2Local.RMsgs()+hLocal.status.rormsgs+hLocal.status.roemsgs;

   hPartner.InStatus();
   hLocal.status.status = m_Status;
   hLocal.status.partnertm = hPartner.status.lasttime;
   return(hLocal.OutStatus());
}

int CUGFMQ::OpenAllFMQ()
{
   char tmp[256];
   int rtn;
   sprintf(tmp,"OR2%s",m_PartnerID);
   rtn = m_OR2Partner.Open(m_FMQPath,tmp);   
   if (rtn<0)
   {
      UG_WriteLog(10001,"Fail to open FMQ(%s,%s):%d",m_FMQPath,tmp,rtn);
      return(-2);
   }
   
   sprintf(tmp,"OE2%s",m_LocalID);
   rtn = m_OE2Local.Open(m_FMQPath,tmp);
   if (rtn<0)
   {
      UG_WriteLog(10001,"Fail to open FMQ(%s,%s):%d",m_FMQPath,tmp,rtn);
      return(-3);
   }
      
   sprintf(tmp,"OR2%s",m_LocalID);
   rtn = m_OR2Local.Open(m_FMQPath,tmp);
   if (rtn<0)
   {
      UG_WriteLog(10001,"Fail to open FMQ(%s,%s):%d",m_FMQPath,tmp,rtn);
      return(-6);
   }
   sprintf(tmp,"OE2%s",m_PartnerID);
   rtn = m_OE2Partner.Open(m_FMQPath,tmp);
   if (rtn<0)
   {
      UG_WriteLog(10001,"Fail to open FMQ(%s,%s):%d",m_FMQPath,tmp,rtn);
      return(-7);
   }
   
   sprintf(tmp,"2%s",m_LocalID);
   rtn = m_2Local.Open(m_FMQPath,tmp);
   if (rtn<0)
   {
      UG_WriteLog(10001,"Fail to open FMQ(%s,%s):%d",m_FMQPath,tmp,rtn);
      return(-8);
   }
   sprintf(tmp,"2%s",m_PartnerID);
   rtn = m_2Partner.Open(m_FMQPath,tmp);
   if (rtn<0)
   {
      UG_WriteLog(10001,"Fail to open FMQ(%s,%s):%d",m_FMQPath,tmp,rtn);
      return(-9);
   }
   return(0);
}

int CUGFMQ::Open(const char *sLocalID, const char *sPartnerID, char *emsg)
{
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
   
   // �����úͻָ�����:
   m_Status = FS_CONNECTING;  // ������������״̬
   // statusinfo��ʽΪ: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
   sprintf(emsg,"%s|%s:1:0:In PreOpen",m_LocalID,m_PartnerID); 
   UDLHaveChannelStatusInfo(emsg);
   if (!PreOpen(emsg))
   {
      m_Status = FS_DISABLE;
      return(-3);
   }

   if (StartThread(InProcess,this)<0)
   {
      m_Status = FS_DISABLE;
      return(-4);
   }
   
   m_Status = FS_OPEN;  // ����Open״̬
   return(0);  // Start OK!
}

int CUGFMQ::OnMessageOut(const char *fixmsg, char *eMsg)
{
   char *pmt = strstr(fixmsg,"35=");
   //int rtn;
   if (pmt!=NULL)
   {
      switch (pmt[3])
      {
      case 'D':   // D = Order Single
      case 'E':   // E = Order List
      case 'F':   // F = Order Cancel Request
      case 'G':   // G= Order Cancel/Replace Request
      case 'H':   // H= Order Status Request
      case 'K':   // K = List Cancel Request
         return(m_OR2Partner.Send(strlen(fixmsg),fixmsg));
      case '8':   // 8 = Execution Report
      case '9':   // 9 = Order Cancel Reject
      case 'L':   // L = List Execute
         return(m_OE2Partner.Send(strlen(fixmsg),fixmsg));
      }
   }
   return(m_2Partner.Send(strlen(fixmsg),fixmsg));
}

int CUGFMQ::EndOfDay(const char *sLocalID, const char *sPartnerID, char *emsg)
{
   int rtn;
   rtn = ResetAllFMQ();  // ��UGate��ˣ�ǿ��Reset���е�FMQ
   if (rtn<0)
   {
      sprintf(emsg,"Fail to Reset all FMQ:%d",rtn);
      return(rtn);  // �������ˡ�����
   }
   rtn = OpenAllFMQ();
   if (rtn<0)
   {
      sprintf(emsg,"Fail to Open all FMQ:%d",rtn);
      return(rtn);  // �������ˡ�����
   }
   hLocal.status.sormsgs = 0;    // ���͸��Է��Ķ�������Ϣ����(���ϴ�EOD��ʼ)
   hLocal.status.soemsgs = 0;     // ���͸��Է���ִ������Ϣ����
   hLocal.status.smsgs = 0;      // ���͸��Է��ĳ�������Ӧ������Ϣ
   hLocal.status.rormsgs = 0;     // ���յ��Է��Ķ�������Ϣ����(���ϴ�EOD��ʼ)
   hLocal.status.roemsgs = 0;     // ���յ��Է���ִ������Ϣ����
   hLocal.status.rmsgs = 0;      // ���յ��Է��ĳ�������Ӧ������Ϣ
   return(0);
}

int CUGFMQ::Close(const char *sLocalID, const char *sPartnerID, char *emsg)
{
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
   m_Status = FS_CLOSE;
   return(0);
}

int CUGFMQ::Exit()
{
   time_t ltm=time(NULL);
   m_Status = FS_CLOSE;
   while (time(NULL)<ltm+5 && m_InRunStatus==FS_OPEN);
   return(0);
}

// ��ҪΪˢ��״̬�Ͷ�ȡ������Ϣ
int CUGFMQ::Run()
{
//   int rno;
   char fixmsg[MAXFIXMSGLEN];
   time_t ltm=time(NULL);
   int loops=0;

   UG_WriteLog(100,"Start InFMQ(%s) Processing",m_PartnerID);
   m_InRunStatus = FS_OPEN;
   while (m_Status>FS_CLOSE)
   {
      while (m_OR2Local.Recv(0,fixmsg,sizeof(fixmsg))>0)
      {
         UDLHaveMessageIn(m_PartnerID,fixmsg);
         loops = 0;
      }
      if (m_OE2Local.Recv(0,fixmsg,sizeof(fixmsg))>0)
      {
         UDLHaveMessageIn(m_PartnerID,fixmsg);
         loops = 0;
      }
      if (m_2Local.Recv(0,fixmsg,sizeof(fixmsg))>0)
      {
         UDLHaveMessageIn(m_PartnerID,fixmsg);
         loops = 0;
      }
      if (time(NULL)>ltm)
      {
         ltm = time(NULL);
         CheckPartnerStatus();
      }
      if (++loops>100)
      {
         mysleep(1);
         loops = 0;
      }
   }
   UG_WriteLog(101,"Stop InFMQ(%s) Processing",m_PartnerID);
   m_InRunStatus = FS_CLOSE;
   return(0);
}

bool CUGFMQ::PreOpen(char *emsg)
{
   // ��һЩ���ݻָ��Ĺ���
   hLocal.status.status = FS_OPEN;
#if 0
   if (hLocal.status.rmsgs>0 
      ||hLocal.status.smsgs>0)
      return(true);  // ֮ǰ�Ѿ��������ˣ���ô�Ͳ�������Ļظ���
#endif
   hLocal.status.sormsgs = 0;    // ���͸��Է��Ķ�������Ϣ����(���ϴ�EOD��ʼ)
   hLocal.status.soemsgs = 0;     // ���͸��Է���ִ������Ϣ����
   hLocal.status.smsgs = 0;      // ���͸��Է��ĳ�������Ӧ������Ϣ
   hLocal.status.rormsgs = 0;     // ���յ��Է��Ķ�������Ϣ����(���ϴ�EOD��ʼ)
   hLocal.status.roemsgs = 0;     // ���յ��Է���ִ������Ϣ����
   hLocal.status.rmsgs = 0;      // ���յ��Է��ĳ�������Ӧ������Ϣ
   
   if (!RestoreOut(emsg))
   {
      UG_WriteLog(10010,"Restore OutMsg Fail:%s",emsg);
      return(false);
   }

   if (!RestoreIn(emsg))
   {
      UG_WriteLog(10011,"Restore InMsg Fail:%s",emsg);
      return(false);
   }

   CheckPartnerStatus();

   return(true);
}

bool CUGFMQ::RestoreOut(char *emsg)
{
   L_MSGDATA omsgs;
   L_MSGDATA::iterator omit;
   int msgno;
   char fixmsg[MAXFIXMSGLEN];
   char flag[2];
//   int l1,l2;
   // ֻ�Ƕ�m_OR2Partner;m_OE2Partner����Ϣ���лָ�
   UG_GetSSAllOrders(m_PartnerID,omsgs);
   // ���������׶Σ����������ɣ�
   for (msgno=1;;++msgno)
   {
      if (m_OR2Partner.Read(msgno,fixmsg,sizeof(fixmsg),flag)<=0)
         break;
      //l1 = strlen(fixmsg);
      for (omit=omsgs.begin();omit!=omsgs.end();omit++)
      {
//          l2 = strlen(omit->msgbuf);
//          if (l1==l2 && memcmp(omit->msgbuf,fixmsg,l2)==0)
         if (UG_FIXMsgKeyTagCmp(fixmsg,omit->msgbuf)==0)
         {
            omsgs.erase(omit);
            break;
         }
      }
   }
   for (omit=omsgs.begin();omit!=omsgs.end();++omit)
   {
      m_OR2Partner.Send(omit->msglen,omit->msgbuf);
   }
   omsgs.clear();
   //-----------------------------------------------------
   UG_GetBSExecRepts(m_PartnerID,omsgs);
   for (msgno=1;;++msgno)
   {
      if (m_OE2Partner.Read(msgno,fixmsg,sizeof(fixmsg),flag)<=0)
         break;
//       l1 = strlen(fixmsg);
      for (omit=omsgs.begin();omit!=omsgs.end();omit++)
      {
//          l2 = strlen(omit->msgbuf);
//          if (l1==l2 && memcmp(omit->msgbuf,fixmsg,l2)==0)
         if (UG_FIXMsgKeyTagCmp(omit->msgbuf,fixmsg)==0)
         {
            omsgs.erase(omit);
            break;
         }
      }
   }
   for (omit=omsgs.begin();omit!=omsgs.end();++omit)
   {
      m_OE2Partner.Send(omit->msglen,omit->msgbuf);
   }
   
   return(true);
}

bool CUGFMQ::RestoreIn(char *emsg)
{
   char fixmsg[MAXFIXMSGLEN];
   while (m_OR2Local.Recv(0,fixmsg,sizeof(fixmsg))>0)
   {
      UG_RestoreFIXInMsg(m_PartnerID,fixmsg);
   }

   while (m_OE2Local.Recv(0,fixmsg,sizeof(fixmsg))>0)
   {
      UG_RestoreFIXInMsg(m_PartnerID,fixmsg);
   }

//    while (m_2Local.Recv(0,fixmsg,sizeof(fixmsg))>0)
//    {
//       UG_RestoreFIXInMsg(m_PartnerID,fixmsg);
//    }
   return(true);
}
