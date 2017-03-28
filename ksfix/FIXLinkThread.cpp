// FIXLinkThread.cpp: implementation of the CFIXLinkThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "FIXLinkThread.h"

bool UpdateCheckPath(char *path, char *defsub);

#ifdef _KSFIXSERVER
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

#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIXLinkThread::CFIXLinkThread()
{
   m_connectmode = CM_TCP_SERVER;
   m_opentime = -1;
   m_closetime = -1;
   m_eodtime = -1;
   strcpy(m_FSName,"FIXSessionName");
}

CFIXLinkThread::~CFIXLinkThread()
{

}

void CFIXLinkThread::SetLogPath(const char *logpath)
{
   char path[260];
   strcpy(path,logpath);
   UpdateCheckPath(path,"FIXLOG");
   m_logpath = path;
}

void CFIXLinkThread::SetUserPassword(const char *lusername, const char *lpassword, const char *pusername, const char *ppassword)
{
   m_luser = lusername;
   m_lpass = lpassword;
   m_puser = pusername;
   m_ppass = ppassword;
}

void CFIXLinkThread::SetSession(const char *localid, const char *partnerid, const char *fixversion)
{
   char logpath[260];
   CPMUTEX pMutex(&m_mutex);
   m_localid = localid;
   m_partnerid = partnerid;
   m_fixversion = fixversion;
   if (m_FSName[0]!='\0')
   {
      sprintf(m_FSName,"%s-%s",m_localid.c_str(),m_partnerid.c_str());
   }
   if (m_logpath.length()>0)
   {
      sprintf(logpath,"%s%s-%s",m_logpath.c_str(),m_localid.c_str(),m_partnerid.c_str());
      m_LogFile.Open(logpath);
   }
   m_Persistence.Close();
   inMsgs.clear();
   outMsgs[0].clear();
   outMsgs[1].clear();
}

bool CFIXLinkThread::SetFIXPath(const char *mpath, const char *bkpath)
{
   char path[260];
   strcpy(path,mpath);
   if (!UpdateCheckPath(path,NULL))
      return(false);
   mfpath = path;
   if (bkpath==NULL||bkpath[0]=='\0')
      bfpath = "";
   else
   {
      strcpy(path,bkpath);
      if (UpdateCheckPath(path,NULL))
         bfpath = path;
   }
   return(mpath[0]!='\0');
}


void CFIXLinkThread::SetEODTime(int iHHMM)
{
   m_eodtime = iHHMM;
}


int CFIXLinkThread::ToOpen(const char *svrip, int svrport)
{
   int rtn;
   CPMUTEX pMutex(&m_mutex);
   if (m_state!=FIXST_CLOSE)
      return(-100); // �Ѿ���ʹ����
   m_state = FIXST_CONNECTING;
   m_connectmode = CM_TCP_CLIENT;

   // ����Է���������...
   if (!m_sock.ConnectTcp(svrip,svrport,m_outHeartBtInt*1000))
   {
      m_LogFile.WriteLogEx(2137,"Fail to connect with FIXPartner(%s:%d)!",svrip,svrport);
      ToClose();
      return(-1);
   }
   unsigned short pport;
   m_sock.GetPeerName(m_partnerip,pport);
   m_partnerport = pport;
   m_LogFile.WriteLogEx(245,"Connected with FIXPartner(%s:%d)!",m_partnerip,m_partnerport);

   if (!OpenFIXStorePath(mfpath.c_str(),bfpath.c_str()))
   {
      m_LogFile.WriteLogEx(2240,"Fail to Open FIX Store Path(%s)",mfpath.c_str());
      ToClose();
      return(-2);
   }
   logon=logout=0;
   CheckEOD(-1); // �ڲ���ȡ��ǰʱ�����

   // �ȷ���Logon��Ϣ���Է�:
   rtn = SendLogon(m_luser.c_str(),m_lpass.c_str());
   if (rtn<0)
   {
      return(rtn-100);
   }
   while (logon==1)
   {
      if (!CheckRecvFIXData(m_inHeartBtInt*1000))
      {
         // ��Ȼ�������⣬����m_iHeartBtInt����������
         m_LogFile.WriteLogEx(81029,"Timeout(%dS) to receive InMsg!",m_inHeartBtInt);
         ToClose();
         return(-3);
      }
      OnRecvInMsg();
      if (m_state==FIXST_CLOSE)
         return(-4);
   }
   tmLogon = time(NULL);
   m_state = FIXST_OPEN;
   return(StartWorkThread());
}

void CFIXLinkThread::CheckEOD(time_t tmnow)
{
   struct tm tmn;
   struct tm tmlast;
   if (m_eodtime<0)
      return; // û�����ã����Բ�����
   if (tmnow==-1)
   {
      tmnow = time(NULL);
   }
   time_t lasttime = m_Persistence.GetLastEODTime();
   if (lasttime>=tmnow)
      return; // ��������
   if (tmnow<lasttime+24*3600)
   {
      tmn = *localtime(&tmnow);
      if (tmn.tm_hour*100+tmn.tm_min<=m_eodtime)
      {
         // ����EODTIME=06:00 ���ڵ�ʱ���Ϊ05:00 ��ô֮ǰ����EOD��ʱ����Ϊ�����06:00
         tmnow -= 86400;
         tmlast = *localtime(&tmnow);
         tmn.tm_year =tmlast.tm_year;
         tmn.tm_mon = tmlast.tm_mon;
         tmn.tm_mday = tmlast.tm_mday;
      }
      // else ����֮ǰ����EOD��ʱ���Ϊ�����06:00
      tmn.tm_hour = m_eodtime/100;
      tmn.tm_min = m_eodtime%100;
      tmlast = *localtime(&lasttime);
      if (tmn.tm_year>tmlast.tm_year
         ||tmn.tm_mon>tmlast.tm_mon
         ||tmn.tm_mday>tmlast.tm_mday
         ||tmn.tm_hour>tmlast.tm_hour
         ||tmn.tm_min>tmlast.tm_min)
      {
         // ����ϴ���EOD��ʱ��� < ֮ǰ����EOD��ʱ���
      }
      else
      {
         return;
      }
   }
   if (DoEndOfDay()==0)
   {
      if (m_state==FIXST_OPEN)
      {
         // ��ô��Ҫ֪ͨ�Է�:
         SendLogon(m_luser.c_str(),m_lpass.c_str(),true);
      }
   }
}


int CFIXLinkThread::StartWorkThread()
{
   sprintf(szName,"%s-%s",m_localid.c_str(),m_partnerid.c_str());
   if (CreateThread())
      return(0);
   else
   {
      m_LogFile.WriteLogEx(71403,"Fail to start FIXLinkThread(%s)",m_FSName);
      return(-10);
   }
}

int CFIXLinkThread::Run()
{
   m_LogFile.WriteLogEx(405,"Begin of FIXLinkThread(%s)",m_FSName);
   m_mutex.Lock();
   m_bStop = false;
   while (m_state>=FIXST_OPEN)
   {
      m_OTRunTime = time(NULL);
//       if (m_sock.IsFree())
//          break;
      if (CheckRecvFIXData(0))
      {
         OnRecvInMsg();
      }
      else
      {
         m_mutex.UnLock();
         int rtn = m_sock.CheckSRAvailableUS(100000);
         switch(rtn)
         {
         case 1:
         case 3:
            // �����ⷢ������:
            MayOutMsg();
            break;
         }
         m_mutex.Lock();
         if (rtn!=2 && rtn!=3)
         {
            // ����ǰ�ƺ�û����Ϣ���ݽ�����
            ToCheckTest();
         }
         if (m_bStop)
         {
            if (m_GapFillSeqNo<=0 && logout<1)
            {
               SendLogout("Requested by application/operator.");
            }
         }
      }
   }
   if (m_state!=FIXST_CLOSE)
      ToClose();
   m_mutex.UnLock();
   m_LogFile.WriteLogEx(406,"End of FIXLinkThread(%s)",m_FSName);
   return(0);
}

// ���ⲿ���õ�
int CFIXLinkThread::ToDoEndOfDay()
{
   CPMUTEX pMutex(&m_mutex);
   //logon = 0; // Ϊ��������
   int rtn = DoEndOfDay();
   m_LogFile.WriteLogEx(145,"Do EOD by Application: %d",rtn);
   if (rtn==0)
   {
      if (m_state==FIXST_OPEN)
      {
         // �Ȳ���logon����������������
         return(SendLogon(m_luser.c_str(),m_lpass.c_str(),TRUE));
      }
      else
         return(0);
   }
   else
      return(-1);
}

void CFIXLinkThread::ToCloseSession()
{
   m_bStop = true;
}

int CFIXLinkThread::OnLogon()
{
   char flag[40];
   int vlen;
   if (m_puser.length()>0)
   {
      vlen = sizeof(flag);
      if (m_recvFIXData.GetTag(553,flag,vlen)<0||m_puser.compare(flag)!=0)
      {
         m_LogFile.WriteLogEx(71519,"Invalid UserName(%s) != (%s) setup",
            flag,m_puser.c_str());
         ToClose();
         return(-1);
      }
      if (m_ppass.length()>0)
      {
         vlen = sizeof(flag);
         if (m_recvFIXData.GetTag(554,flag,vlen)<0||m_ppass.compare(flag)!=0)
         {
            m_LogFile.WriteLogEx(71522,"Invalid Password(%s)",flag);
            ToClose();
            return(-2);
         }
      }
   }
   if (m_recvFIXData.GetTag(141,flag,vlen)>=0 && flag[0] == 'Y')
   {
      if ((logon&0x01)==0)  // ������ΪLOGON�Ľ��շ�(EOD)
      {
         m_LogFile.WriteLogEx(1509,"Do EOD for partner's request:%d",DoEndOfDay());
      }
   }
   else
   {
      flag[0]='N';
      if (logon>1)
      {
         m_LogFile.WriteLogEx(11340,"Why received LOGON without EOD ?");
      }
   }
   if (CheckInSequenceNumber()<0)
      return(-4);

   ++logon; logout=0;

   if ((logon&0x01)==1)
   {
      SendLogon(m_luser.c_str(),m_lpass.c_str(),(flag[0]=='Y'));
   }
   return(0);
}

void CFIXLinkThread::OnRecvInMsg()
{
   if (!ValidRecvSessionID())
   {
      ToClose();
      return;
   }
   if (strcmp(m_rejmsg.RefMsgType,"4")!=0
      && strcmp(m_rejmsg.RefMsgType,"A")!=0) // LOGON��������ŵĿ��ܣ���EOD�������
   {
      if (CheckInSequenceNumber()<0)
         return;
   }
   if (m_rejmsg.RefMsgType[0]=='\0')
      return; // �����������
   if (m_rejmsg.RefMsgType[1]=='\0')
   {
      switch (m_rejmsg.RefMsgType[0])
      {
      case '0': // 0 = Heartbeat
         OnHeartBeat();
         return;
      case '1': // Test Request
         OnTestReq();
         return;
      case '2': // Resend Request
         OnResendRequest();
         return;
      case '3': // Reject
         OnReject();
         return;
      case '4': // Sequence Reset
         OnSequenceReset();
         return;
      case '5': // Logout
         OnLogout();
         return;
      case 'A': // Logon
         // ����ִ��EOD��ʱ�򣬻ύ�������Ϣ�ġ�
         OnLogon();
         return;
      }
   }
   if (logon>=2)
   {
      // ֻ�е�¼�ɹ��������������ҵ������
      HaveInMsg();
   }
   else
   {
      m_LogFile.WriteLogEx(82109,"Received (MsgType=%s) before LOGON ?",m_rejmsg.RefMsgType);
      ToClose();
   }
}

void CFIXLinkThread::HaveInMsg()
{
   char msg[MAXFIXDATALENGTH];
   int msglen;
   msglen = m_recvFIXData.GetFIXData(msg,sizeof(msg));
   CMsgData mdata(msglen,msg);
   inMsgMutexEvent.Lock();
   inMsgs.push_back(mdata);
#if 1
   if (inMsgs.size()<2)
      inMsgMutexEvent.SetEvent();
#else
   inMsgMutexEvent.SetEvent();
#endif
   inMsgMutexEvent.UnLock();
}

// ���ȴ�ʱ��Ϊwaitms
int CFIXLinkThread::GetInMsg(char *msgbuf, unsigned int waitms)
{
   int len;
   L_MSGDATA::iterator lmit;
   inMsgMutexEvent.Lock();
#if 1
   int i;
   waitms /= 100;
   for (i=0;i<100;++i)
   {
      if (inMsgs.size()>0)
         break;
      inMsgMutexEvent.WaitEventTime(waitms);
   }
#else
   //if (inMsgs.size()<=0)
   inMsgMutexEvent.WaitEventTime(10);
#endif
   lmit = inMsgs.begin();
   if (lmit==inMsgs.end())
   {
      inMsgMutexEvent.UnLock();
      return(0);
   }
   len = lmit->msglen;
   if (len>0)
   {
      memcpy(msgbuf,lmit->msgbuf,len);
      msgbuf[len]=0;
   }
   inMsgs.pop_front();
   inMsgMutexEvent.UnLock();
   return(len);
}

int CFIXLinkThread::GetOutMsg(char *msgbuf)
{
   int len;
   L_MSGDATA::iterator lmit;
   int i;
   outMsgMutexEvent.Lock();
   for (i=0;i<2;++i)
   {
      if (outMsgs[0].size()>0 || outMsgs[1].size()>0)
         break;
      outMsgMutexEvent.WaitEventTime(1); // 2010-6-23 15:50:42 ��10 ��Ϊ g_iOutWait
      if (m_bStop)
         break;
   }
   lmit = outMsgs[0].begin(); i=0;
   if (lmit==outMsgs[0].end())
   {
      lmit = outMsgs[1].begin(); i=1;
      if (lmit==outMsgs[1].end())
      {
         outMsgMutexEvent.UnLock();
         return(0);
      }
   }
   len = lmit->msglen;
   if (len>0)
   {
      memcpy(msgbuf,lmit->msgbuf,len);
      msgbuf[len]=0;
   }
   outMsgs[i].pop_front();
   outMsgMutexEvent.UnLock();
   return(len);
}

void CFIXLinkThread::HaveOutMsg(int msglen, const char *msg, int plevel)
{
   CMsgData mdata(msglen,msg);
   plevel = plevel ? 1:0;
   outMsgMutexEvent.Lock();
   outMsgs[plevel].push_back(mdata);
   if (outMsgs[0].size()+outMsgs[1].size()<2)
      outMsgMutexEvent.SetEvent();
   outMsgMutexEvent.UnLock();
}

// �ڲ����߳���ʹ�ã������ڿ��Է��������ҵ����Ϣ
void CFIXLinkThread::MayOutMsg()
{
   char fixmsg[MAXFIXDATALENGTH];
   int fmlen = GetOutMsg(fixmsg);
   if (fmlen>0)
   {
      // �������������Ҫ������:
      CFIXData fixdata;
      if (fixdata.SetData(fixmsg,fmlen))
      {
         CPMUTEX pMutex(&m_mutex); // Ҫʹ��sock�ͱ��ڲ�������Դ���д�����
         char tmp[40];
         sprintf(tmp,"%d",++outgoingSeqNumber);
         fixdata.UpdateTag(-1,34,tmp);
         fixdata.UpdateTag(-1,49,m_localid.c_str());
         fixdata.UpdateTag(-1,56,m_partnerid.c_str());
         fixdata.UpdateTag(-1,52,BuildTag52(tmp));
         fmlen = fixdata.GetStdFIXMessage(fixmsg,MAXFIXDATALENGTH,m_fixversion.c_str());
         m_Persistence.SetSeqNo(-1,outgoingSeqNumber);
         m_Persistence.Put(FAD_OUT,outgoingSeqNumber,fixmsg,fmlen);
         SendFIXMsg(fixmsg,fmlen);
      }
      else
      {
         m_LogFile.WriteLogEx(72152,"Invalid Out-Application FIXMsg[%d](%s)",
            fmlen,fixmsg);
      }
   }
   else
   {
      if (time(NULL)>tmLastSent+m_outHeartBtInt)
      {
         SendHeartBt(NULL);
      }
   }
}

// ��CM_TCP_SERVERģʽ�£�ֻ�б���ԴIsFree������£��ſ���ʹ�ñ�FIXLinkThread��
bool CFIXLinkThread::IsFree()
{
   return(m_state==FIXST_CLOSE && time(NULL)>m_OTRunTime+5);
}

void CFIXLinkThread::OnReject()
{
   char refseqnum[40];
   char text[1024];
   int vlen;
   if (m_recvFIXData.GetTag(45,text,(vlen=sizeof(text)))<0)
      strcpy(refseqnum,"No RefSeqNum");
   else
      SNPRINTF(refseqnum,sizeof(refseqnum),"TAG45=%s",text);
   if (m_recvFIXData.GetTag(58,text,(vlen=sizeof(text)))<0)
      strcpy(text,"---");
   m_LogFile.WriteLogEx(28703,"Received Reject: %s, Text=%s",refseqnum,text);
}
