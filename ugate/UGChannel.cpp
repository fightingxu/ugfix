// UGChannel.cpp: implementation of the CUGChannel class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "logfile.h"
#include "UGChannel.h"
#include "UDLInterface.h"
#include "UGateManage.h"
#include "ugate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUGChannel::CUGChannel()
{
   m_Status = -1;
}

CUGChannel::~CUGChannel()
{

}

int CUGChannel::OpenChannel()
{
   int rtn;
   char emsg[256]={0};
   m_Status = 0; // ��ʾ��Ҫ���������״̬��Ҫͨ������������
   g_UGate.CheckEOD(1,m_PartnerID);  // ���������ģ���Ҫ�ȼ��һ��EOD
//    if (m_Status<0)
//       return(m_Status);
   rtn = UDLOpen(UG_GetLocalID(),m_PartnerID,emsg);
   UG_WriteLog(201,"Channel(%s_%s) Open, %d:%s",
      UG_GetLocalID(),m_PartnerID,rtn,emsg);
//    if (rtn<0)
//    {
//       ͨ��״̬��ѯ�������״̬����: �������Ͳ�����
//       sprintf(rtnmsg,"%s|%s|1|0|Fail to open, ErrCode=%d:%s",
//          rtn,emsg);
//       UG_SendMessageIn(411731,1,rtnmsg);
//       return(rtn);
//    }
   LoadLuaFile();
   return(0);  // ͨ���������ظ�Channel��״̬
}

int CUGChannel::CloseChannel()
{
   int rtn;
   char emsg[80]={0};
   if (g_UGate.m_OutMode)
   {
      m_bStop = true;
   
      outMsgMutexEvent.Lock();
      outMsgMutexEvent.SetEvent();  // Ҫ��OThread�˳�������������ˡ�����
      outMsgMutexEvent.UnLock();
   }
   rtn = UDLClose(UG_GetLocalID(),m_PartnerID,emsg);
   UG_WriteLog(202,"Channel(%s_%s) Close, %d:%s",
      UG_GetLocalID(),m_PartnerID,rtn,emsg);
   // ���ر�ʧ�ܣ�������������ʾ��
   //    if (rtn<0)
   //    {
   //       sprintf(rtnmsg,"0|?|Fail to close, ErrCode=%d:%s",
   //          rtn,emsg);
   //       UG_SendMessageIn(411731,1,rtnmsg);
   //       return(rtn);
   //    }
   CloseLuaFile();
   return(rtn);  // ͨ���������ظ�Channel��״̬
}

//DEL int CUGChannel::EODChannel()
//DEL {
//DEL    int rtn;
//DEL    char emsg[80]={0};
//DEL    rtn = UDLEndOfDay(UG_GetLocalID(),m_PartnerID,emsg);
//DEL    UG_WriteLog(203,"Channel(%s_%s) EOD Process, %d:%s",
//DEL       UG_GetLocalID(),m_PartnerID,rtn,emsg);
//DEL    if (rtn>=0)
//DEL    {
//DEL       // ��ʾEOD����ɹ�: ��ƽ̨����EOD�����־
//DEL       g_UGate.EODDone(m_PartnerID);      
//DEL    }
//DEL    return(-1);
//DEL }

void CUGChannel::ChannelStatus(int status, int load, const char *eMsg)
{
   m_Status = status;
   m_Load = load;
}

void CUGChannel::UpdateStatus(int status)
{
   if (status>=0)
   {
      //  ϣ��Open��Channel
      if (m_Status<=0)
         OpenChannel();
   }
   else
   {
      // ϣ���رո�Channel
      if (m_Status>0)
         CloseChannel();
   }
}

void CUGChannel::HaveOutMsg(int msglen, const char *msg, int &plevel)
{
   CMsgData mdata(msglen,msg);
   plevel = plevel ? 1:0;
   outMsgMutexEvent.Lock();
   outMsgs[plevel].push_back(mdata);
   if (outMsgs[0].size()+outMsgs[1].size()<2)
      outMsgMutexEvent.SetEvent();
   outMsgMutexEvent.UnLock();
}

int CUGChannel::GetOutMsg(int outwaitms, char *msgbuf)
{
   int len;
   L_MSGDATA::iterator lmit;
   int i;
   outMsgMutexEvent.Lock();
   for (i=0;i<100;++i)
   {
      if (outMsgs[0].size()>0 || outMsgs[1].size()>0)
         break;
      outMsgMutexEvent.WaitEventTime(outwaitms); // 2010-6-23 15:50:42 ��10 ��Ϊ g_iOutWait
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

int CUGChannel::GetOutMsgSize()
{
   return(outMsgs[0].size()+outMsgs[1].size());
}

void CUGChannel::FormatInFIXData(CFIXData *pfixdata)
{
   CPMUTEX pMutex(&m_LuaMutex);
   m_LuaFIX.LuaC_CheckFIXMsg(pfixdata,LUA_INMSG);
}

void CUGChannel::FormatOutFIXData(CFIXData *pfixdata)
{
   CPMUTEX pMutex(&m_LuaMutex);
   m_LuaFIX.LuaC_CheckFIXMsg(pfixdata,LUA_OUTMSG);
}

bool CUGChannel::LoadLuaFile()
{
   char luafile[256];
   CPMUTEX pMutex(&m_LuaMutex);
   sprintf(luafile,"%s.kfx",m_PartnerID);
   if (m_LuaFIX.LuaC_Open(luafile)==0)
   {
      UG_WriteLog(521,"Loaded '%s' OK!",luafile);
      return(true);
   }
   else
   {
      UG_WriteLog(522,"Fail to load '%s'!",luafile);
      return(false);
   }
}

void CUGChannel::CloseLuaFile()
{
   CPMUTEX pMutex(&m_LuaMutex);
   m_LuaFIX.LuaC_Close();
}
