// FIXSession.cpp: implementation of the CFIXSession class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "FIXData.h"
#include "logfile.h"
#include "FIXSession.h"

//extern int g_iDebug;

char *BuildTag52(char *tag52)
{
   time_t tmnow;
   int millis;
   GetTimeMillis(&tmnow,&millis);
   GetFIXUTCDateTime(tmnow,tag52,millis);
   return(tag52);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFIXSession::CFIXSession()
{
   m_dklen = 0;
   tmLastRecv = 0;
   tmLastSent = 0;
   m_state = FIXST_CLOSE;
   incomingSeqNumber = outgoingSeqNumber = 0; // 表示还没有到可用状态
   TestReqID = 1;
   bNeedSendingTime = true;  // 由于FIX没规定StandardHeader中非要这个TAG
   strcpy(m_FSMPath,"FIXDATA");
   m_FSBPath[0]='\0';
   m_GapFillSeqNo = 0;
   logon = 0; logout = 2; // 表示处于logout状态
}

CFIXSession::~CFIXSession()
{

}

void CFIXSession::InitOutFIXData(CFIXData *pFIXData, const char *MsgType)
{
   char utctime[24];  // YYYYMMDD-HH:MM:SS.xxx
   pFIXData->Reset(m_fixversion.c_str());
   //   pFIXData->AddTag(8,m_fixversion.c_str());
   pFIXData->AddTag(35,MsgType);
   pFIXData->AddTag(49,m_localid.c_str());
   pFIXData->AddTag(56,m_partnerid.c_str());
   pFIXData->AddTag(34,++outgoingSeqNumber);
   //if (bNeedSendingTime)
   {
      pFIXData->AddTag(52,BuildTag52(utctime));
   }
}

int CFIXSession::SendFIXMsg(const char *pmsg, int msglen)
{
   int rtn = m_sock.Send(pmsg,msglen);
   //if (g_iDebug>0)
   {
      m_LogFile.WriteLogEx(555,"OutFIXMsg @ %s(%d):%s",
         m_FSName,rtn,pmsg);
   }
   tmLastSent = time(NULL);
   if (rtn<0)
   {
      m_LogFile.WriteLogEx(5551,"Fail to Send FIXMsg(rtn=%d)",rtn);
      ToClose();
   }
   else
   {
      m_Persistence.SetSeqNo(-1,outgoingSeqNumber);
   }
   return(rtn);
}

int CFIXSession::SendFIXMsg(CFIXData *pfixdata)
{
   char sendmsg[MAXFIXDATALENGTH];
   int rtn = SendFIXMsg(sendmsg,pfixdata->GetStdFIXMessage(sendmsg));
   if (rtn>0)
      rtn = outgoingSeqNumber;
   return(rtn);
}

bool CFIXSession::CheckDataKeep()
{
   if (m_dklen>0)
   {
      char *p1 = strstr(m_datakeep,"\00110=");
      if (p1!=NULL)
      {
         char *p2 = strstr(p1+1,"\001"); 
         if (p2!=NULL)
         {
            char cnext = p2[1]; // 先保存一下
            p2[1]='\0';
            m_InMsgLen = (int)(p2-m_datakeep)+1;
            //if (g_iDebug>0)
            {
               m_LogFile.WriteLogEx(665,"InFIXData @ %s:%s",
                  m_FSName,m_datakeep);
            }
            if (!ValidFIXData(m_datakeep,m_InMsgLen))
            {
               // 收到的数据不符合基本的FIX格式，参考该函数中返回为false的。 
               /*
               m_sock.Close();  // 彻底关闭本连接
               m_dklen = 0;
               */
               ToClose();
               return(false);
            }
            p2[1]=cnext; // 恢复原始的消息
            if (m_datakeep+m_dklen>++p2)
            {
               m_dklen -= p2-m_datakeep;
               memcpy(m_datakeep,p2,m_dklen);
               m_datakeep[m_dklen]='\0';
            }
            else
            {
               m_dklen = 0;
            }
            return(true);
         }
      }
   }
   return(false);
}

// 函数名: CheckRecvFIXData
// 编程  : 陈永华 2011-4-7 23:50:30
// 描述  : 从连接中，检查和接收FIX消息数据，
// 返回  : bool: 若有完整的FIX数据包，则返回true, 并设置到m_recvFIXData中；否则，返回false
// 参数  : int timeout : 毫秒计等待接收
bool CFIXSession::CheckRecvFIXData(int timeout)
{
   if (CheckDataKeep())
      return(true);
   int rtn = m_sock.RecvPart(m_datakeep+m_dklen,sizeof(m_datakeep)-m_dklen-1,timeout);
   if (rtn>0)
   {
      // 说明收到了数据：
      tmLastRecv = time(NULL);
      m_dklen += rtn;
      m_datakeep[m_dklen]='\0';
      if (m_dklen>1)
      {
         if (memcmp(m_datakeep,"8=",2)!=0)
         {
            // 非FIX消息，则认为对方不可能为合法的对方
            m_LogFile.WriteLogEx(1012,"%s Closed for Invalid recvFIXData(%s)",
               m_FSName,
               m_datakeep);
            /*
            m_sock.Close();
            m_dklen = 0;
            */
            ToClose();
            return(false);
         }
      }
      return(CheckDataKeep());
   }
   else if (rtn<0)
   {
      rtn = m_sock.GetLastError(m_datakeep);
      m_LogFile.WriteLogEx(1011,"%s Closed for Error(%d:%s)",
         m_FSName,
         rtn,m_datakeep);
      /*
      m_sock.Close();
      m_dklen = 0;
      */
      ToClose();
   }
   return(false);
}

bool CFIXSession::ValidFIXData(const char *fixmsg,int fmlen)
{
   if (!m_recvFIXData.SetData(fixmsg,fmlen,&m_rejmsg)
      ||!m_recvFIXData.Valid(fixmsg,&m_rejmsg))
   {
      // 说明收到的消息，不符合FIX规范
      m_LogFile.WriteLogEx(6650,"Invalid FIXMsg(%s) @ InMsg(%s)",
         m_rejmsg.Text,fixmsg);
//       if (m_rejmsg.RefSeqNum>0)
//       {
//          SendRejectMsg(&m_rejmsg);
//       }
      return(false);
   }
   /* 由于本模块将会用于CM_TCP_SERVER模式，因此，在登陆的时候，localid,partnerid还没有被确定
   if (FIXGETTAG(m_recvFIXData,49,m_rejmsg.Text)<=0
      || m_partnerid.compare(m_rejmsg.Text)!=0)
   {
      m_LogFile.WriteLogEx(6650,"Invalid TAG49 of InMsg(%s)",fixmsg);
      return(false);
   }
   if (FIXGETTAG(m_recvFIXData,56,m_rejmsg.Text)<=0
      || m_localid.compare(m_rejmsg.Text)!=0)
   {
      m_LogFile.WriteLogEx(6650,"Invalid TAG56 of InMsg(%s)",fixmsg);
      return(false);
   }
   */
   /* 由于直接涉及流程控制及后续消息恢复，需要由上层来判断!  2012/5/25 10:10:19
   if (m_rejmsg.RefSeqNum!=incomingSeqNumber+1)
   {
      sprintf(m_rejmsg.Text,"InSeqNum (%d!=%d)",
         m_rejmsg.RefSeqNum,incomingSeqNumber+1);
      // 由于TCP通讯一定是有序的，因此，这里就算了，不做Resend Request
      m_LogFile.WriteLogEx(6650,"%s -%s:%s",
         m_FSName,m_rejmsg.Text,fixmsg);
   }
   incomingSeqNumber = m_rejmsg.RefSeqNum;
   */
   /* ****** Updated by CHENYH at 2011-4-20 15:52:01 ****** 
   这些消息就让上层去判断吧
   //for (iMsgType=0;iMsgType<VMT_MAXMSGTYPES;++iMsgType)
   //{
   //   if (strcmp(ValidMsgTypes[iMsgType],m_rejmsg.RefMsgType)==0)
   //      break;
   //}
   //if (iMsgType>=VMT_MAXMSGTYPES)
   //{
   //   m_rejmsg.RefTagID = 35;
   //   m_rejmsg.SessionRejectReason = 11;
   //   strcpy(m_rejmsg.Text,"Unsupported MsgType");
   //   SendRejectMsg(&m_rejmsg);
   //}
   */
   return(true);   
}

// 发送Reject消息
int CFIXSession::SendRejectMsg(T_REJECTMSG *pRejMsg)
{
   // 则先给出Reject消息：
   CFIXData rejfd;
   
   InitOutFIXData(&rejfd,"3");
   rejfd.AddTag(45,pRejMsg->RefSeqNum);
   if (pRejMsg->RefTagID>0)
   {
      rejfd.AddTag(371,pRejMsg->RefTagID);
   }
   if (pRejMsg->RefMsgType[0]!='\0')
   {
      rejfd.AddTag(372,pRejMsg->RefMsgType);
   }
   if (pRejMsg->SessionRejectReason>=0)
   {
      rejfd.AddTag(373,pRejMsg->SessionRejectReason);
   }
   if (pRejMsg->Text[0]!='\0')
   {
      rejfd.AddTag(58,pRejMsg->Text);
   }
   return(SendFIXMsg(&rejfd));
}

int CFIXSession::SendLogon(const char *UserName, const char *Password, bool bResetSeqNum)
{
   CFIXData outfd;
   logout=0;  // 表示正式连接开始
   ++logon;
   //outgoingSeqNumber = 1; 
   //incomingSeqNumber = 0;
   InitOutFIXData(&outfd,"A");  // 8=A
   outfd.AddTag(98,0);  // EncryptMethod
   outfd.AddTag(108,m_outHeartBtInt);  // //HeartBtInt
   // ?????: TO CONFIRM
   if (bResetSeqNum)
   {
      outfd.AddTag(141,"Y");  // ResetSeqNumFlag 告诉对方，从序号1开始
   }

   m_LogFile.WriteLogEx(710,"Sending LOGON(HBI=%d,ResetSeqNum=%c)",
      m_outHeartBtInt,bResetSeqNum?'Y':'N');

   if (UserName!=NULL && UserName[0]!='\0')
   {
      outfd.AddTag(553,UserName);
      if (Password!=NULL && Password[0]!='\0')
         outfd.AddTag(554,Password);
   }
   if (logon<3)
      tmLogon = time(NULL);
   return(SendFIXMsg(&outfd));
}

// The test request message forces a heartbeat from the opposing application.  
// The test request message checks sequence numbers or verifies communication line status.  
// The opposite application responds to the Test Request with a Heartbeat containing the TestReqID.
int CFIXSession::OnTestReq(const char *tag10031)
{
   char tmp[256];
   T_REJECTMSG rejmsg;
   rejmsg.RefSeqNum = m_recvFIXData.GetTagI(45);
   strcpy(rejmsg.RefMsgType,"1");
   rejmsg.SessionRejectReason = 3;  // 3 = Undefined Tag
   rejmsg.Text[0]='\0';
   if (FIXGETTAG(m_recvFIXData,112,tmp)<0)
   {
      rejmsg.RefTagID = 112;
      SendRejectMsg(&rejmsg);
      m_LogFile.WriteLogEx(2526,"No Tag 112 for TestRequest!");
      return(-112);
   }
   m_LogFile.WriteLogEx(701,"Received TestRequest(%s)",tmp);
   return(SendHeartBt(tmp,tag10031));
}

int CFIXSession::SendHeartBt(const char *TestReqID,const char *tag10031)
{
   CFIXData outfd;
   InitOutFIXData(&outfd,"0");
   if (TestReqID!=NULL && TestReqID[0]!='\0')
   {
      m_LogFile.WriteLogEx(800,"Sending HeartBeat(%s)",TestReqID);
      outfd.AddTag(112,TestReqID);
   }
   else
   {
      m_LogFile.WriteLogEx(800,"Sending HeartBeat(--)");
   }
   if (tag10031!=NULL && tag10031[0]!='\0')
      outfd.AddTag(10031,tag10031);
   return(SendFIXMsg(&outfd));
}

// When either end of a FIX connection has not sent any data for [HeartBtInt] seconds, 
// it will transmit a Heartbeat message.  
// When either end of the connection has not received any data for 
// (HeartBtInt + "some reasonable transmission time") seconds, 
// it will transmit a Test Request message.  
// If there is still no Heartbeat message received 
// after (HeartBtInt + "some reasonable transmission time") seconds 
// then the connection should be considered lost and corrective action be initiated.  
// If HeartBtInt is set to zero then no regular heartbeat messages will be generated.  
// Note that a test request message can still be sent independent of the value of the HeartBtInt, 
// which will force a Heartbeat message.
int CFIXSession::OnHeartBeat()
{
   char tmp[256];
   T_REJECTMSG rejmsg;
   rejmsg.RefSeqNum = m_recvFIXData.GetTagI(45);
   strcpy(rejmsg.RefMsgType,"0");
   rejmsg.SessionRejectReason = 3;  // 3 = Undefined Tag
   rejmsg.Text[0]='\0';
   if (FIXGETTAG(m_recvFIXData,112,tmp)<0)
   {
      // 在有的FE，对方会先发送一个HeartBeat，并没有TAG 112
      return(0); 
//       rejmsg.RefTagID = 112;
//       SendRejectMsg(&rejmsg);
//       m_LogFile.WriteLogEx(6112,"[%s,%s] OnHeartBeat: No Tag112",
//          m_FSName,m_partnerid.c_str());
//       return(-112);
   }
   unsigned int ireqid = atoui(tmp);
   if (ireqid==TestReqID)
   {
      tmTestReq = 0;  // 表示已经同步了
      m_LogFile.WriteLogEx(61,"[%s,%s] Synchronized @%s",
         m_FSName,m_partnerid.c_str(),tmp);
      return(0);
   }
   else
   {
      //tmTestReq = 0;  // 算了，随便它了
      m_LogFile.WriteLogEx(1126,"[%s,%s] OnHeartBeat(%s)!=%u",
         m_FSName,m_partnerid.c_str(),tmp,TestReqID);
      return(ireqid);
   }
}

int CFIXSession::SendLogout(const char *logouttxt)
{
   CFIXData outfd;
   ++logout;
   InitOutFIXData(&outfd,"5");
   if (logouttxt!=NULL && logouttxt[0]!='\0')
   {
      outfd.AddTag(58,logouttxt);
      m_LogFile.WriteLogEx(805,"Sending Logout(%s)",logouttxt);
   }
   else
   {
      m_LogFile.WriteLogEx(805,"Sending Logout(--)");
   }
   return(SendFIXMsg(&outfd));
}

int CFIXSession::SendTestReq()
{
   CFIXData outfd;
   InitOutFIXData(&outfd,"1");
   outfd.AddTag(112,++TestReqID);
   tmTestReq = time(NULL);
   return(SendFIXMsg(&outfd));
}

void CFIXSession::OnUndefinedInMsgType()
{
   char inmsg[MAXFIXDATALENGTH];
   m_recvFIXData.GetFIXData(inmsg,sizeof(inmsg));
   m_LogFile.WriteLogEx(6651,"[%s,%s] InMsg undefined:%s",
      m_FSName,m_partnerid.c_str(),inmsg);
}

// sessionid: <LocalID>-<PartnerID>
bool CFIXSession::SetSessionID(const char *sessionid)
{
   char tmp[64];
   if (GetSubString(sessionid,'-',0,tmp,sizeof(tmp),NULL)<=0)
      return(false);
   m_localid = tmp;
   if (GetSubString(sessionid,'-',1,tmp,sizeof(tmp),NULL)<=0)
      return(false);
   m_partnerid = tmp;
   if (m_FSName[0]=='\0')
   {
      sprintf(m_FSName,"%s-%s",m_localid.c_str(),m_partnerid.c_str());
   }
   return(true);
}

// ip_port - <PartnerIP>:<PartnerPort>
bool CFIXSession::SetPartnerConnect(const char *ip_port)
{
   char tmp[64];
   if (GetSubString(ip_port,':',0,m_partnerip,sizeof(m_partnerip),NULL)<=0)
      return(false);
   if (GetSubString(ip_port,':',1,tmp,sizeof(tmp),NULL)<=0)
      return(false);
   m_partnerport = atoi(tmp);
   if (m_partnerport<=0)
      return(false);
   return(true); 
}

// 专门用于从对方收到 ResendRequest 的消息时候，给予对方填补缺口用，因为本地没有具体的应用消息记录
int CFIXSession::SendSeqReset(int tag34, int NewSeqNum, bool Gap_Fill, bool dup)
{
   CFIXData outfd;
   //InitOutFIXData(&outfd,"4");
   char utctime[24];  // YYYYMMDD-HH:MM:SS.xxx

   outfd.Reset(m_fixversion.c_str());
   outfd.AddTag(35,"4");
   outfd.AddTag(49,m_localid.c_str());
   outfd.AddTag(56,m_partnerid.c_str());
   outfd.AddTag(34,tag34);
   outfd.AddTag(52,BuildTag52(utctime));
   if (dup)
      outfd.AddTag(43,"Y");
   if (Gap_Fill)
   {
      m_LogFile.WriteLogEx(804,"Sending SeqReset-GapFill(TAG36=%d)",NewSeqNum);
      outfd.AddTag(123,"Y");
   }
   else
   {
      m_LogFile.WriteLogEx(804,"Sending SeqReset-Reset(TAG36=%d)",NewSeqNum);
   }
   outfd.AddTag(36,NewSeqNum);
   return(SendFIXMsg(&outfd));
}

int CFIXSession::OnResendRequest()
{
   int beginSeqNo;
   int endSeqNo;
   int rtn;
   beginSeqNo = m_recvFIXData.GetTagI(7);
   endSeqNo = m_recvFIXData.GetTagI(16);
   m_LogFile.WriteLogEx(702,"Received ResendRequest(7=%d,16=%d)",
      beginSeqNo,endSeqNo);
   if (beginSeqNo>=outgoingSeqNumber)
   {
      // 怎么可能呢? 上次发送的消息序号为outgoingSeqNumber呀，为啥对方会要重发还没有的消息呢？
      m_LogFile.WriteLogEx(12526,"Invalid ResendRequest(BeginSeqNo7=%d,EndSeqNo16=%d), BeginSeqNo>=OutSeqNum(%d)",
         beginSeqNo,endSeqNo,outgoingSeqNumber);
      ToClose();
      return(-1);
   }
   if (beginSeqNo<1)
      beginSeqNo = 1;
   if (endSeqNo<=0 || endSeqNo>outgoingSeqNumber)
      endSeqNo=outgoingSeqNumber;

   int i,n;
   n = m_Persistence.GetCount(FAD_OUT);
   for (i=0;i<n;++i)
   {
      int seqno;
      char fixdata[MAXFIXDATALENGTH];
      int len = m_Persistence.GetData(FAD_OUT,i,&seqno,fixdata,sizeof(fixdata));
      if (seqno>endSeqNo)
         break;
      if (seqno<beginSeqNo)
      {
         // 不用重发这个消息。。。Skip
      }
      else
      {
         if (seqno>beginSeqNo)
         {
            // 需要发SeqReset, 34=beginSeqNo, 36=seqno, 123=Y
            rtn = SendSeqReset(beginSeqNo,seqno,true,true);
            if (rtn<0)
               return(rtn);
         }
         rtn = ResendFIXMsg(fixdata,len);
         if (rtn<0)
            return(rtn);
         beginSeqNo = seqno+1;
      }
   }
   /*
   if (beginSeqNo<outgoingSeqNumber+1)
   {
      return(SendSeqReset(beginSeqNo,outgoingSeqNumber+1,true,false));      
   }
   */
   if (beginSeqNo<endSeqNo+1)
   {
      return(SendSeqReset(beginSeqNo,endSeqNo+1,true,true));
   }
   if (endSeqNo>outgoingSeqNumber)
   {
      // 这个根本不可能的！！！！
      outgoingSeqNumber = endSeqNo;
      m_Persistence.SetSeqNo(-1,outgoingSeqNumber);
   }
   return(rtn);
   /*
   outgoingSeqNumber = beginSeqNo;
   if (endSeqNo<=0)
      endSeqNo = outgoingSeqNumber+1;
   */
   //return(SendSeqReset(endSeqNo,true,true));  // ??? 本处理过程似乎有点问题的 ???  从TCP通讯来说，这是不可能的
}

int CFIXSession::OnSequenceReset()
{
   // 收到Sequence Reset
   int newSeqNumber = m_recvFIXData.GetTagI(36);
   if (newSeqNumber<1)
   {
      m_LogFile.WriteLogEx(12526,"Invalid SequenceReset(newSeqNo36=%d)",newSeqNumber);
      ToClose();
      m_rejmsg.RefMsgType[0]='\0';
      return(-1);
   }
   char PossDupFlag[2];
   int vlen=sizeof(PossDupFlag);
   if (m_recvFIXData.GetTag(43,PossDupFlag,vlen)<0 || PossDupFlag[0]!='Y')
   {
      PossDupFlag[0]='N';
   }
   char GapFillFlag[2];
   vlen=sizeof(GapFillFlag);
   if (m_recvFIXData.GetTag(123,GapFillFlag,vlen)<0 || GapFillFlag[0]!='Y')
   {
      // 被认为是 SeqReset-Reset模式
      // 则incomingSeqNumber被强制到newSeqNumber
      m_LogFile.WriteLogEx(526,"Received SeqReset-Reset to Sync. (%d)",newSeqNumber);
   }
   else if (m_rejmsg.RefSeqNum <= incomingSeqNumber)
   {
      // 收到的SequenceNumber<预期该收到的SeqNumber: 异常
      m_LogFile.WriteLogEx(27031,"Received SeqReset-GapFill: InSeqNumber(%d) < expected (%d)",
         m_rejmsg.RefSeqNum,incomingSeqNumber+1);
      ToClose();
      m_rejmsg.RefMsgType[0]='\0';
      return(-4);      
   }
   else if (m_rejmsg.RefSeqNum > incomingSeqNumber+1)
   {
      // 怎么会收到序号超过预期，怕丢包:
      m_LogFile.WriteLogEx(27314,"Received SeqReset-GapFill: InSeqNumber(%d) > expected (%d) ?GapSeqNum=%d?",
         m_rejmsg.RefSeqNum,incomingSeqNumber+1,m_GapFillSeqNo);
      ToClose();
      return(-5);
   }
   else
   {
      // 属于GapFill Mode: 还是要检查序号，当然可以只检查newSeqNumber
      if (newSeqNumber>=m_GapFillSeqNo)
      {
         m_GapFillSeqNo = 0; // 表示已经同步了。。。
         m_LogFile.WriteLogEx(526,"Received SeqReset-GapFill to Sync. (%d)",newSeqNumber);
      }
      else
      {
         m_LogFile.WriteLogEx(704,"Received SeqReset-GapFill(%d), Gap(%d-%d) still",
            newSeqNumber,m_GapFillSeqNo);
      }
   }
   incomingSeqNumber = newSeqNumber-1;
   m_Persistence.SetSeqNo(incomingSeqNumber,-1);
   m_LogFile.WriteLogEx(526,"Incoming Sequence Reseted to %d",newSeqNumber);
   return(0);
}

void CFIXSession::SetHeartBtInt(int hbt, int hblatency)
{
   if (hbt<1)
      hbt = 5;
   if (hblatency<1)
      hblatency = 1;
   m_outHeartBtInt = hbt;
   m_inHeartBtInt = hbt+hblatency;
}

// 检查Test发送后的同步处理(tmTestReq>0)，或者若长时间没有收到对方的消息，则发起TestReq
int CFIXSession::ToCheckTest()
{
   time_t tmnow = time(NULL);
   if (tmnow>tmLastRecv+m_outHeartBtInt)
   {
      if (tmTestReq>0)
      {
         if (tmnow>tmTestReq+m_inHeartBtInt)
         {
            // 那就假设链路出现了问题了，或对方没有按照FIX规则，给予HeartBeat的回应
            m_LogFile.WriteLogEx(6179,"[%s,%s] No reply in %dS after TestReq(1) sent - ToClose",
               m_FSName,m_partnerid.c_str(),tmnow-tmTestReq);
            ToClose();
            return(-6179);
         }
         //return(0);  // 继续等待对方发送任何消息吧...
      }
      else
      {
         m_LogFile.WriteLogEx(2617,"[%s,%s] No Msg recv in %dS, Send a TestReq(1)",
            m_FSName,m_partnerid.c_str(),tmnow-tmLastRecv);
         return(SendTestReq());
      }
   }
   return(0);
}

void CFIXSession::ToClose()
{
   /*
   if (m_sock.IsFree())
      return;
   */
   tmLastSent = time(NULL);
   m_sock.Close();
   m_dklen = 0;
   //m_Persistence.Close();  // 也许后续还要使用，如EOD操作等
   m_LogFile.WriteLogEx(1027,"%s-%s Be Closed!",
      m_localid.c_str(),m_partnerid.c_str());
   // m_LogFile.Close();     // 也许后续还要使用，比如在做EOD操作的时候，需要写一些东西
   m_FSBPath[0]='\0';
   m_FSMPath[0]='\0';
   m_GapFillSeqNo = 0;
   m_state = FIXST_CLOSE;
}

void CFIXSession::SetSendingTime(bool bMandatory)
{
   bNeedSendingTime = bMandatory;
}

bool CFIXSession::IsLinkOK()
{
   return(!(m_sock.IsFree()));
}

bool CFIXSession::SetFIXVersion(const char *fixversion)
{
   m_fixversion = fixversion;
   return(m_fixversion.length()>0);
}

int CFIXSession::GetStatus()
{
   return(m_state);
}


// Function name: CFIXSession::OpenFIXStorePath
// Author       : CHENYH 2012/5/26 14:13:13
// Description  : 打开FIX状态持久化，并恢复InSeq和OutSeq，已准备正式数据交换
//  !!! 本操作要在正式确认为已设定的Session之后，才可调用。
//  CM_TCP_SERVER: 是在接受到对方连接，并得到Logon消息后，确认本连接的Session之后，准备发送Logon消息之前调用；
//  CM_TCP_CLIENT: 则是设定好Session之后，准备发送Logon消息之前调用。
// Return type  : bool 返回是否打开成功
// Argument : const char *mpath [IN]: 主存储目录路径，必须为有，并且可以创建的路径；否则，将返回失败
// Argument : const char *bkpath [OUT]: 备存储目录路径，可以为NULL或""来表示无备存储路径
bool CFIXSession::OpenFIXStorePath(const char *mpath, const char *bkpath)
{
   sprintf(m_FSMPath,"%s%s-%s",mpath,m_localid.c_str(),m_partnerid.c_str());
   if (bkpath==NULL ||bkpath[0]=='\0')
      m_FSBPath[0]='\0';
   else
      sprintf(m_FSBPath,"%s%s-%s",bkpath,m_localid.c_str(),m_partnerid.c_str());
   m_LogFile.WriteLogEx(225,"Set FIX Store Path: Main(%s) & Back(%s)",
      m_FSMPath,m_FSBPath[0]!='\0'?m_FSBPath:"NULL");
   if (m_Persistence.Init(m_FSMPath,m_FSBPath))
   {
      m_Persistence.GetLastSeqNo(incomingSeqNumber,outgoingSeqNumber);
      return(true);
   }
   return(false);
}

bool CFIXSession::ValidRecvSessionID()
{
   if (FIXGETTAG(m_recvFIXData,49,m_rejmsg.Text)<=0
      || m_partnerid.compare(m_rejmsg.Text)!=0)
   {
      m_LogFile.WriteLogEx(6650,"Invalid TAG49(%s!=%s) of InMsg",m_rejmsg.Text,m_partnerid.c_str());
      return(false);
   }
   if (FIXGETTAG(m_recvFIXData,56,m_rejmsg.Text)<=0
      || m_localid.compare(m_rejmsg.Text)!=0)
   {
      m_LogFile.WriteLogEx(6650,"Invalid TAG56(%s!=%s) of InMsg",m_rejmsg.Text,m_localid.c_str());
      return(false);
   }
   return(true);
}

int CFIXSession::ResendFIXMsg(char *fixdata, int fdlen)
{
   CFIXData outfd;
   if (!outfd.SetData(fixdata,fdlen,&m_rejmsg))
      return(-1);
   outfd.UpdateTag(-1,43,"Y");
   outfd.UpdateTag(-1,52,BuildTag52(fixdata));
   return(SendFIXMsg(fixdata,outfd.GetStdFIXMessage(fixdata)));
}

int CFIXSession::CheckInSequenceNumber()
{
   /* 由外部去选择。。。 2012-5-28 20:34:12
   if (strcmp(m_rejmsg.RefMsgType,"4")==0)
      return(4); // 交给OnSequenceReset去处理吧
   */
   // 获取InMsg的MsgSeqNum；
   if (m_rejmsg.RefSeqNum<=incomingSeqNumber)
   {
      // 收到的SequenceNumber<预期该收到的SeqNumber: 异常
      m_LogFile.WriteLogEx(27031,"InSeqNumber(%d) < expected (%d)",
         m_rejmsg.RefSeqNum,incomingSeqNumber+1);
      ToClose();
      m_rejmsg.RefMsgType[0]='\0';
      return(-4);
   }
   // 若MsgSeqNum>incomingSeqNo, 且MsgSeqNum>m_GapFill, 那么就需要ResendRequest了
   if (m_rejmsg.RefSeqNum==incomingSeqNumber+1)
   {
      //if (m_rejmsg.RefSeqNum>=m_GapFillSeqNo)
      m_GapFillSeqNo = 0; 
      incomingSeqNumber = m_rejmsg.RefSeqNum;  // ++incomingSeqNumber...
      m_Persistence.SetSeqNo(incomingSeqNumber,-1);
      return(0);  // 表示OK
   }
   // 收到的InSeqNo > incomingSeqNumber+1
   m_LogFile.WriteLogEx(2731,"InSeqNumber(%d) > expected (%d), To InSync Mode...",
      m_rejmsg.RefSeqNum,incomingSeqNumber+1);
   if (m_rejmsg.RefSeqNum>m_GapFillSeqNo)
   {
      if (m_GapFillSeqNo==0)
      {
         // 则需要对方填补:
         SendResendRequest(incomingSeqNumber+1,0);
      }
      m_GapFillSeqNo = m_rejmsg.RefSeqNum;
   }
   // 忽略这些消息，让对方重新发送有用的消息，或者发送Reset消息:
   // 将m_rejmsg.RefMsgType置空
   m_rejmsg.RefMsgType[0]='\0';
   return(0);
}

int CFIXSession::SendResendRequest(int beginSeqNo, int endSeqNo)
{
   CFIXData resendreq;
   tmTestReq = 0;  // 先清除原先发送的TestRequest，要求得到HeartBeat的检查
   InitOutFIXData(&resendreq,"2");
   resendreq.AddTag(7,beginSeqNo);
   resendreq.AddTag(16,endSeqNo);
   return(SendFIXMsg(&resendreq));
}



int CFIXSession::DoEndOfDay()
{
   if (m_Persistence.EndOfDay())
   {
      incomingSeqNumber = 0;
      outgoingSeqNumber = 0;
      return(0);
   }
   return(-1);
}

int CFIXSession::OnLogout()
{
   char text[1024];
   int tvlen=sizeof(text);
   if (m_recvFIXData.GetTag(58,text,tvlen)<0)
   {
      text[0]='\0';
   }
   if (m_GapFillSeqNo>0)
   {
      // 还在同步过程中，不能退出！
      m_LogFile.WriteLogEx(38705,"Received Logout(58=%s), InSeqNo(%d), GapFill(%d)?",
         text,m_rejmsg.RefSeqNum,m_GapFillSeqNo);
      tvlen = 0;
   }
   else
   {
      ++logout;
      m_LogFile.WriteLogEx(705,"Received Logout(58=%s)",text);
      if (logout==1)
      {
         tvlen = SendLogout("Replying to logout");
      }
      ToClose();
   }
   return(tvlen);
}


