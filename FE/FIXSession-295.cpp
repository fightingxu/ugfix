// FIXSession.cpp: implementation of the CFIXSession class.
// 2012/4/3 10:36:10 从此以后，FIXIII2012版本，不再用OrigClOrdID或ClOrdID，而是用OrderID，作为SS_OData的关键字
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
   return ((bmCancel&0x01)==0 // 考虑到 unsolicited cancel 的情况
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
//DEL       inMsgMutexEvent.WaitEventTime(g_iInWait);  // 2010-6-24 10:46:15 从10 改为 g_iInWait
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
//DEL       outMsgMutexEvent.WaitEventTime(g_iOutWait); // 2010-6-23 15:50:42 从10 改为 g_iOutWait
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

// 这是打开本Session的指令同步处理
// 以便从FS服务器中获得相关数据
bool CFIXSession::PreOpen(char *eMsg)
{
   // 1. 清除原来的数据
//    inMsgs.clear();
//    outMsgs[0].clear();
//    outMsgs[1].clear();

   SS_OData.clear();

   // 2. 先检查处理DFD 和 EOD
   // BatchProcess(); -- 这个应该在UG的主线程中完成，不要在这里去考虑它
   // 3. 恢复OUT消息
   RestoreOutFIXMsgs();
   // 4. 恢复IN消息
   RestoreInFIXMsgs();
   return(true);
}

int CFIXSession::UpdateSSData(T_UGDATA *pUGData, const char *fixmsg)
{
   IT_ORDDATA iod;

   // 这里只有OUT的 MsgType='8' or '9'的消息，可能也有IN的'F'/'G'
   if (pUGData->sExecType[0]=='I'
      ||pUGData->sExecTransType[0]=='3'
      ||memcmp(pUGData->sExecID,"0d-",3)==0)  // 2012/6/10 20:51:57 ErrNo=60102:Duplicated ClOrdID 以拒绝方式通知对方
   {
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg)); // 属于普通的状态查询类，没有做啥
   }
   CPMUTEX pMutex(&m_SSDMutex);
   // '8' or '9'
   iod = CheckSSOrderData(pUGData);
   if (iod==SS_OData.end())
   {
      // 这种应该是sOrderID为空的情况，该好好查属于那种情况
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
   }
   if (strcmp(pUGData->sMsgType,"9")==0)
   {
      // 由于撤单部分是按照 ClOrdID=OrigClOrdID，来判断是否需要PendingCancel消息先发送的，
      // 不再采用 HaveInCancel 来设置 0x01了。2012/4/3 11:02:54
      //iod->second.bmCancel &= 0xFE;  // 去除 撤单返回标记
      return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
   }
   else if (pUGData->lExecNoCnt<=iod->second.SentSeqNo)
   {
      /***********************************************
      2012/4/3 12:05:20 这种情况先不处理，看看是否有问题?
      // 可能属于该消息被重复接受，所以后来的，就该被抛弃
      // 在KSMBCC的推送过程中，有可能出现这种情况
      if ((iod->second.bmCancel&0x10)==0x10
         && memcmp(pUGData->sExecID,"0d-",3)==0)
      {
         // 对重复订单号的特殊处理，用“0d-”表示重复订单号返回: 2011-09-06
         iod->second.bmCancel &= 0x0F;  // 去掉0x10，表示原始重发已处理
         return(g_FIXEngine.SendFIXMessage2FE(fixmsg));
      }
      */
      if (fixmsg!=NULL)  // 为了安全而加的判断
      {
         UG_WriteLog(8884,"FIX-OutMsg not be sent.(%s)",fixmsg);
      }
      return(0); 
   }
   if (pUGData->lExecNoCnt>=CANCELEDSNO)
   {
      if (pUGData->sClOrdID[0]!='\0' && strcmp(pUGData->sOrigClOrdID,pUGData->sClOrdID))
      {
         // 则需要先发送Pending Cancel消息
         iod->second.bmCancel |= 0x01;
      }
   }
   if (pUGData->lExecNoCnt>=CANCELEDSNO  // 对于FIXIII201204以后，不再会有执行序号为999999了
      && pUGData->dCumQty-iod->second.CumQty<MIN_QTY
      && (iod->second.SentSeqNo>0  // 2009-9-8 10:55:46 SLJ：必须先有New Confirmation发送后才能发送包括 unsolicited cancel
         && MaySendCancel(iod->second.bmCancel)
      || pUGData->lDays>0) // 且已经有消息发给对方了，或为GTn类消息的后续日
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
      // 找顺序插入到ExecList中
      for (ioe=iod->second.ExecList.begin();ioe!=iod->second.ExecList.end();++ioe)
      {
         if (ioe->ExecID>exdata.ExecID)
            break;
         if (ioe->ExecID==exdata.ExecID)
            return(0); // 已经存在了，没有必要再处理下去了
      }
      if (ioe==iod->second.ExecList.end())
         iod->second.ExecList.push_back(exdata);
      else
         iod->second.ExecList.insert(ioe,exdata);
      return(0); // 不用做下去了，因为也不用发送给FE
   }
   // else  pUGData->lExecNoCnt==iod->second.SentSeqNo+1
   //-------------------------------------------------------------
   // 先将本消息向Partner(BuySide)发送:
   g_FIXEngine.SendFIXMessage2FE(fixmsg);
   iod->second.SentSeqNo = pUGData->lExecNoCnt;
   /* Removed by CHENYH @ 2013/8/16 17:53:36
   在特殊情况下，如ExecType=G : Trade Correct 、D = Restated的时候，就会导致CumQty会变小的
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
   // 看看后续是否有被挂起的消息也要被发送的:
   for (ioe=iod->second.ExecList.begin();ioe!=iod->second.ExecList.end();)
   {
      ioe1=ioe++;
      if (ioe1->ExecID==iod->second.SentSeqNo+1
         ||(ioe1->ExecID>=CANCELEDSNO // 对于FIXIII201204以后，不再会有执行序号为999999了
         && ioe1->CumQty-iod->second.CumQty<MIN_QTY
         && (iod->second.SentSeqNo>0  // 2009-9-8 10:55:46 SLJ：必须先有New Confirmation发送后才能发送包括 unsolicited cancel
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
         break; // 结束，不用看下去了
   }
   return(0);
   //-------------------------------------------------------------
}



IT_ORDDATA CFIXSession::CheckSSOrderData(T_UGDATA *pUGData)
{
   IT_ORDDATA iod;
#if 1  // FIXIII-201204  由于出现了改单情况，因此，OrigClOrdID一直保持不变了，只有OrderID不会变
   if (pUGData->sOrderID[0]=='\0')
   {
      UG_WriteLog(20403,"No OrderID for CheckSSOrderData(%s:%s|%s-%s)",
         m_PartnerID.c_str(),pUGData->sOrigClOrdID,pUGData->sClOrdID,pUGData->sMsgType);
      return(SS_OData.end());
   }
   iod = SS_OData.find(string(pUGData->sOrderID));
   if (iod!=SS_OData.end())
      return(iod); // 找到了
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
      return(iod); // 找到了
   COrderData order;
   order.ClOrdID = clordid;
   order.OrderQty = pUGData->dOrderQty;
   iod = SS_OData.insert(make_pair(string(clordid),order)).first;
   return(iod);
#endif
}

void CFIXSession::RestoreOutFIXMsgs()
{
   L_MSGDATA pmlist;  // FE中的消息队列数据
   L_MSGDATA::iterator iml,nml;
   T_UGDATA ugdata;
   // 先获取本地的OUT消息，包括:
   //    BuySide - ExecReport(CancelReject)
   //    SellSide - NewOrderSingle(D) / OrderCancelRequest(F)
   int n = g_FIXEngine.ReadFEMsgData("OUT",m_PartnerID.c_str(),pmlist);
   for (iml=pmlist.begin();iml!=pmlist.end();)
   {
      nml = iml++;
      if (UG_FIXMsg2UGData(nml->msgbuf,nml->msglen,&ugdata,NULL,0)>0)
      {
         // 属于正常的FIX消息:
         if (strcmp(ugdata.sMsgType,"8")==0
            ||strcmp(ugdata.sMsgType,"9")==0)
         {
            UpdateSSData(&ugdata,NULL);  // 建立完整的SS_OData订单状态列表
//             pmlist.erase(nml);  // 后面的BSOut恢复也需要这些数据
         }
//          除了 ‘8’、‘9’外，都先保留下来，为了比较
//          // 就只是留下 ->SellSide - NewOrderSingle(D) / OrderCancelRequest(F)
//          // 为后续从后台恢复的 ->SellSide的消息，做比较，以免重复发送
//          if (strcmp(ugdata.sMsgType,"D")
//             && strcmp(ugdata.sMsgType,"F"))
//          {
//             pmlist.erase(nml); // 删除这些或者已经登记在SS_OData中的或者不需要恢复的消息
//          }
      }
      else
      {
         pmlist.erase(nml);
      }
   }
   // 从平台那里获取向SellSide发送(还没有得到对方反馈)的NewOrderSingle(D) / OrderCancelRequest(F)
   L_MSGDATA lmlist;   // 平台上要发送给SellSide的未决的消息
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
         // 有匹配的: 即表示本消息已经发送给了对手了
         pmlist.erase(nml);  // 不会再用它了吧:)
      }
      else
      {
         // 在FE端，没找到这个消息: 需要提交给FE
         HaveOutMsg(iml->msglen,iml->msgbuf,0);  // 这些是委托、撤单请求，所以要有 0级优先（最高）
      }
   }
   lmlist.clear(); // 好清空了，呵呵
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
         // 有匹配的: 即表示本消息已经发送给了对手了
         pmlist.erase(nml);  // 不会再用它了吧:)
      }
      else
      {
         // 在FE端，没找到这个消息: 需要提交给FE
         HaveOutMsg(iml->msglen,iml->msgbuf,0);  // 这些是委托、撤单请求，所以要有 0级优先（最高）
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
   发现尽管在m_InOpen=true, 但如GL处于:GL:0:0:(1)RC0-close:1:1 状态的时候，执行g_FIXEngine.DoEOD将会导致FE的异常，
   因此，必须采用其他方式来判断是否可以执行g_FIXEngine.DoEOD
   if (!m_InOpen)
   ***************************************/
   if (m_LastStatus<FS_CONNECTING)  // 2013/5/6 11:31:52 -- 改为用这个来判断，以防止FE内部已经Close了（这时FE已经没该Session了）
   //////////////////////////////////////////////////////////////////////////
   {
      // 2012/12/20 0:18:57 改为尽量多次ResetFIXSessionData，以获得成功
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
   // if (rtn>=0)  不管其是否做了EOD与否均Reset这些值 2013/4/27 14:33:18
   {
      m_InMsgSeqNo = 0;
      m_InMsgs = m_OutMsgs = 1;
   }
   return(rtn);
}

void CFIXSession::RestoreInFIXMsgs()
{
   L_MSGDATA pmlist;  // FE中的消息队列数据
   L_MSGDATA::iterator iml;
   // 先获得本地的IN消息，包括:
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
      // 属于正常的FIX消息:
      if (ugdata.lMsgSeqNum>m_InMsgSeqNo)
         m_InMsgSeqNo = ugdata.lMsgSeqNum;
      else
         return(0);  // 已经处理过了

      if (strcmp(ugdata.sMsgType,"D")==0  // NewOrderSingle
         || strcmp(ugdata.sMsgType,"E")==0  // NewOrderList
         || strcmp(ugdata.sMsgType,"F")==0  // OrderCancelRequest
         || strcmp(ugdata.sMsgType,"G")==0)  // Order Cancel/Replace Request
      {
         // 这些重要消息，就重新发送一次，看看
      }
      else if (strcmp(ugdata.sMsgType,"8")==0)  // Execution Report
      {
         // 过滤属于状态返回信息
         if (strcmp(ugdata.sExecType,"I")==0
            ||strcmp(ugdata.sExecTransType,"3")==0)
            return(0);
      }
      else if (strcmp(ugdata.sMsgType,"9")==0)  // Order Cancel Rejected
      {
         // 和MsgType=8的实际的执行消息相同处理
      }
      else 
         return(0); // 其他消息就忽略了
      // 这些保留下来的，都需要恢复
      UG_RestoreFIXInMsg(NULL,fixmsg); // 用NULL代替m_PartnerID.c_str()是因为不需要来自于FIXEngine的消息设置SenderCompID的值了
   }
   return(0);
}

int CFIXSession::GetReloadCount()
{
   return(m_reload++);
}

void CFIXSession::StatusChanged(int newState, int oldState, int reasonCode, const char *reasonText)
{
   char statusinfo[300];  // statusinfo格式为: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
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

// 2013/4/25 16:35:09 在海通UAT发现在获取FIXSTAT的时候，会串数据，比如A-Session的状态数据，串到了B-Session下了
// 怀疑FE中的对该接口多线程不安全的。因此，使用全局独立的CMUTEX对象:
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
      // 2013/4/27 18:33:48 发现当GL在FE内部自动Close后，然后在自动做EOD的时候，本线程有可能会出现Block的情况
      // 为此，特别调整，一旦状态为非Open状态，则不能具体处理这些后续工作!!!!!
      m_OTRunTime = time(NULL); // 表示本线程启动了
      if (m_bStop)
         break;
      if (m_LastStatus>FS_CONNECTING)  // 2013/4/27 18:33:48 避免在未连接之前做实际处理和状态查询工作
      {
         msglen = UG_GetOutMsg(m_PartnerID.c_str(),g_iOutWait,m_OutMsg);
         if (msglen>0 && UG_FIXMsg2UGData(m_OutMsg,msglen,&ugdata,NULL,0)>0)
         {
            if (strcmp(ugdata.sMsgType,"8")==0
               ||strcmp(ugdata.sMsgType,"9")==0)
               UpdateSSData(&ugdata,m_OutMsg);
            else
               g_FIXEngine.SendFIXMessage2FE(m_OutMsg);
            if (m_OTRunTime>lstime+4) // 即使很忙也要更新监控状态
               bReflush = true;
         }
         // 2013/4/24 16:07:42 Added Status updated
         else
         {
            if (m_OTRunTime>lstime) // 空闲的时候，则以每秒更新一次
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
      else  // 2013/4/27 18:33:48 避免在未连接之前做实际处理和状态查询工作
      {
         mysleep(500);
      }
      /////// End of  2013/4/27 18:33:48 避免在未连接之前做实际处理和状态查询工作
   }
   m_OTRunTime = 0; // 表示本线程退出了
   UG_WriteLog(802,"FIXSession(%s) OutThread Stopped",m_PartnerID.c_str());
}

void CFIXSession::ToStopThreads()
{
   // 目前规划只有一个OutThread
   time_t tb = time(NULL);
   m_bStop = true;

//    outMsgMutexEvent.Lock();
//    outMsgMutexEvent.SetEvent();  // 要求OThread退出，别等在那里了。。。
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

// 2013/4/24 15:45:38 为了避免在主线程中，要通过FE去刷新状态，怕被Block住!
void CFIXSession::ReflushStatus()
{
   g_FIXEngine.ReflushStatus(this);
#if 0 // 这种似乎要core的
   CFixStatus m_fixStat; // 2013/4/24 14:40:30 为了将Session内部状态获取，转到OThread中，以免影响其他Session及其对其控制等
   SetError(transState(m_fixStat.getFixState()),
      m_fixStat.getStateReasonText().c_str(),
      m_fixStat.getExpectedInSeqNum(),
      m_fixStat.getExpectedOutSeqNum());
#endif
}


// Function name: CFIXSession::CheckEODAfterOpen
// Author       : CHENYH 2013/4/27 14:48:08
// Description  : 由于在关闭状态下，FS已经要求做本Session的EOD，但因本Session并没有打开，因此在打开后，被调用执行FE的EOD
//                只能在FE中正常打开本Session后调用, 实际只能被g_FIXEngine在OpenSession的时候调用一下
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
