/********************************************************************
	created:	2011/10/22
	created:	22:10:2011   21:34
	filename: 	C:\dd\projects\FIXIII\UGate\ugfmq\UGFMQ.cpp
	file path:	C:\dd\projects\FIXIII\UGate\ugfmq
	file base:	UGFMQ
	file ext:	cpp
	author:		CHENYH
	
	purpose:	UGFMQ，采用KSFMQ(金仕达文件消息队列)模式与外系统对接。
      该模式支持单一个对手，即一个PartnerID；
      （尽管可以写得复杂一点，可如UGFIX那样支持多个对手，
      但实际部署中，单个对手似乎更适合实际的运行模式）
      支持对手可为BuySide和SellSide；

      当本UGate支持的对手为：LocalID -- PartnerID
      将通过一个目录，作为FMQ的host目录；
         该目录下，将有如下FMQ名：(由于UGate支持的大订单类型，导致巨量的执行消息，因此，特别有如下FMQ分类)
         1. <LocalID>为BuySide；而<PartnerID>为SellSide:
            1.1 OR2<PartnerID> -- 为<LocalID>发送给<PartnerID>的订单请求类消息FMQ；<LocalID> -> <PartnerID>
               包括 MsgType: 'D'; 'F'; 'H'; 'E' 等，这类直接和订单有关的请求消息；
               即: <LocalID>为BuySide；而<PartnerID>为SellSide的有关订单类的消息队列；
            1.2 OE2<PartnerID> -- 为<PartnerID>发送给<LocalID>的订单执行类消息FMQ；<PartnerID> -> <LocalID>
               包括 MsgType: '8'; '9'; 等，这类和订单的执行相关的返回消息；
               即: <LocalID>为BuySide；而<PartnerID>为SellSide的有关订单类的消息队列；
         2. <PartnerID>为BuySide；而<LocalID>为SellSide:
            2.1 OR2<LocalID> -- 为<PartnerID>发送给<LocalID>的订单请求类消息FMQ；<PartnerID> -> <LocalID>
            包括 MsgType: 'D'; 'F'; 'H'; 'E' 等，这类直接和订单有关的请求消息；
            即: <PartnerID>为BuySide；而<LocalID>为SellSide的有关订单类的消息队列；
            2.2 OE2<LocalID> -- 为<LocalID>发送给<PartnerID>的订单执行类消息FMQ；<LocalID> -> <PartnerID>
            包括 MsgType: '8'; '9'; 等，这类和订单的执行相关的返回消息；
            即: <PartnerID>为BuySide；而<LocalID>为SellSide的有关订单类的消息队列；

         3. 其他消息的发送与接收:（这类消息不需要恢复）
            3.1 2<LocalID> -- 为<PartnerID>发送给<LocalID>的其他消息FMQ；<PartnerID> -> <LocalID>
            3.2 2<PartnerID> -- 为<LocalID>发送给<PartnerID>的其他消息FMQ；<LocalID> -> <PartnerID>
         另外，再有两个独立文件，以表示双方启动状态 -- 即让对方检查其是否在线：
            <LocalID>.sts; <PartnerID>.sts


      本UGate模式下，由于接口支持全面，统一，但又同时可支持BuySide和SellSide。
      作为UGate的对手方，在FMQ模式下，可以衍生出各类第三方系统对接模式，
      因此，比较灵活，经过测试，FMQ本身的读写处理能力：
         在WinXP笔记本上(ThinkPad X200)上交换速度可达近4000消息/秒；

      由于UGFMQ模式的UGate，在消息发送和接收彻底采用异步处理的，因此，
      只要一个输出线程和一个输入线程即可，其中的输出线程，即为UGate框架
      中的一个线程，因此，本模块中，只要再派生一个输入线程即可。
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
      *pc = '\0'; // 就只能是第一个
   UG_INIReadTString("KSFMQ","FMQPATH","fmqhost",m_FMQPath,sizeof(m_FMQPath));
   if (access(m_FMQPath,0)!=0)
      MAKEPATH(m_FMQPath);

   hLocal.Open(m_FMQPath,m_LocalID,true);
   rtn = hPartner.Open(m_FMQPath,m_PartnerID,true); // 都由UGate来创建
   if (rtn<0)
   {
      UG_WriteLog(10000,"Fail to open FMQStatusFile(%s,%s,%s):%d",
         m_FMQPath,m_LocalID,m_PartnerID,rtn);
      return(-1);
   }
   if (OpenAllFMQ()<0)
   {
      // 第一次创建和打开
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

// 获取状态信息，同时也是和对方建立一种心跳机制
// statusmsg-- <PartnerID1>:<status>:<load>:<errmsg>
int CUGFMQ::GetStatus(char *statusmsg, unsigned int smsize)
{
   unsigned int dtime;
   CheckPartnerStatus(); // 交换本端和对端的状态信息
   dtime = hLocal.status.lasttime-hPartner.status.partnertm;
   if (m_Status>FS_CLOSE)
   {
      if (hPartner.status.status==FS_OPEN 
         && dtime<15)  // 即在对方对本方的状态反馈在15秒之内
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
   
   // 做重置和恢复处理:
   m_Status = FS_CONNECTING;  // 处于正在连接状态
   // statusinfo格式为: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
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
   
   m_Status = FS_OPEN;  // 进入Open状态
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
   rtn = ResetAllFMQ();  // 在UGate这端，强制Reset所有的FMQ
   if (rtn<0)
   {
      sprintf(emsg,"Fail to Reset all FMQ:%d",rtn);
      return(rtn);  // 出问题了。。。
   }
   rtn = OpenAllFMQ();
   if (rtn<0)
   {
      sprintf(emsg,"Fail to Open all FMQ:%d",rtn);
      return(rtn);  // 出问题了。。。
   }
   hLocal.status.sormsgs = 0;    // 发送给对方的订单类消息总数(从上次EOD开始)
   hLocal.status.soemsgs = 0;     // 发送给对方的执行类消息总数
   hLocal.status.smsgs = 0;      // 发送给对方的常规请求、应答类消息
   hLocal.status.rormsgs = 0;     // 接收到对方的订单类消息总数(从上次EOD开始)
   hLocal.status.roemsgs = 0;     // 接收到对方的执行类消息总数
   hLocal.status.rmsgs = 0;      // 接收到对方的常规请求、应答类消息
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

// 主要为刷新状态和读取返回消息
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
   // 做一些数据恢复的工作
   hLocal.status.status = FS_OPEN;
#if 0
   if (hLocal.status.rmsgs>0 
      ||hLocal.status.smsgs>0)
      return(true);  // 之前已经启动过了，那么就不做下面的回复了
#endif
   hLocal.status.sormsgs = 0;    // 发送给对方的订单类消息总数(从上次EOD开始)
   hLocal.status.soemsgs = 0;     // 发送给对方的执行类消息总数
   hLocal.status.smsgs = 0;      // 发送给对方的常规请求、应答类消息
   hLocal.status.rormsgs = 0;     // 接收到对方的订单类消息总数(从上次EOD开始)
   hLocal.status.roemsgs = 0;     // 接收到对方的执行类消息总数
   hLocal.status.rmsgs = 0;      // 接收到对方的常规请求、应答类消息
   
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
   // 只是对m_OR2Partner;m_OE2Partner的消息进行恢复
   UG_GetSSAllOrders(m_PartnerID,omsgs);
   // 这是启动阶段，慢点就慢点吧：
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
