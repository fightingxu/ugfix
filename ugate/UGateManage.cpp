// UGateManage.cpp: implementation of the CUGateManage class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "cpack.h"
#include "XPack.h"
#include "bupub.h"
#include "bdefine.h"
#include "mypub.h"
#include "logfile.h"
#include "FIXData.h"
#include "fixbase.h"
#include "UGateManage.h"
#include "ugate.h"
#include "UDLInterface.h"

extern ST_BUNIT g_BUnit;
extern CSvrLink *g_pSvrLink;  // ��ҵ��������ĵ�����
extern CLogFile g_LogFile;   // ���Ƶ�SvrLink.cpp�У���Ϊϵͳ��Ҫ������
extern CXPack *g_pXPack;  //

#define UGINNAME "UGIN"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUGateManage::CUGateManage()
{
   m_lastUDLTime = time(NULL);
   m_UDLStatusRtn = 0; // Ĭ��Ϊ��������
   m_OutMode = 0;
}

CUGateManage::~CUGateManage()
{
   m_inifile.Close();
   g_LogFile.Close();
}

int CUGateManage::LoadIni(const char *inifile)
{   
   char tmp[256];
   
   SetLogShowLevel(0);
   memset(&g_BUnit,0,sizeof(g_BUnit));
   if (!(m_inifile.Open((char *)inifile)))
   {
      printf("Fail to open inifile:%s\n",inifile);
      exit(-1001);
   }
   UG_INIReadTString("COMMON","LOGPATH","uglog",tmp,sizeof(tmp));
   g_LogFile.Open(tmp);
   g_LogFile.RemoveOverdueLogFile(m_inifile.ReadInt("COMMON","LOGOVERDUE",10));
   m_inifile.ReadString("COMMON","GID","",g_BUnit.szBUGroupID,sizeof(g_BUnit.szBUGroupID)-1);

   m_inifile.ReadTString("COMMON","LOCALID","UG1",m_LocalID,sizeof(m_LocalID));

   // ML;THOMSON;GL;BLP;BNP;BCL;SWHK;CLSA or KSCTS
   m_inifile.ReadTString("COMMON","PARTNERID","",m_PartnerID,sizeof(m_PartnerID));
   //////////////////////////////////////////////////////////////////////////

   //m_OutMode = m_inifile.ReadInt("COMMON","OUTMODE",0);

   m_iDebug = m_inifile.ReadInt("COMMON","DEBUG",3); 

   m_UDLRefStatus = m_inifile.ReadInt("COMMON","ST_INT",5);

   m_inifile.ReadString("BCC","BCCSVR","127.0.0.1:6666",tmp,sizeof(tmp)-1);
   
   if (GetSubString(tmp,':',1,g_BUnit.szSvrIP,sizeof(g_BUnit.szSvrIP),NULL)<=0)
   {
      sprintf(tmp,"�����ļ�<%s>��������[BCC] BCCSVR=???? ����! ��ʽΪ��BCCSVR=xxx.xxx.xxx.xxx:port\n",inifile);
      DEBUG_RUNTIME_MSGOUT(tmp);
      exit(-1000);
   }
   g_BUnit.iSvrPort = atoi(g_BUnit.szSvrIP);
   GetSubString(tmp,':',0,g_BUnit.szSvrIP,sizeof(g_BUnit.szSvrIP),NULL);
   g_BUnit.iHBInterval = m_inifile.ReadInt("BCC","HEARTBEAT",3000);
   if (g_BUnit.iHBInterval<100)
      g_BUnit.iHBInterval = 100;
   
   m_inifile.ReadTString("BCC","MQNAME","",tmp,150);
   BUSetMQName(tmp);
   
   m_FSDestNo = m_inifile.ReadInt("UGATE","FSDESTNO",0);
   m_FSFuncNo = m_inifile.ReadInt("UGATE","FSFUNCNO",5600);
   m_FSAckTime = m_inifile.ReadInt("UGATE","FSACKTIME",10000)/1000;
   if (m_FSAckTime<5)
      m_FSAckTime = 5;  // ��С5��

   m_UGDestNo = m_inifile.ReadInt("UGATE","UGDESTNO",0);

   // 2012/8/16 22:55:11
   m_bFilterASC = m_inifile.ReadInt("UGATE","FILTERASC",1)!=0;
   
   return(1);
}

int CUGateManage::Initialize()
{
   ST_BUNIT xpBUnit;
   int i,rtn;
   CUGChannel *pChannel;
   // 1. �ȼ��������ϵ����ã�������UG�Ƿ������������ʹ����������Ҳ�ô��ڵȴ�״̬��ֻ�ǲ�����UDL
   //m_nChannels = 0;
   pChannel = m_Channel;
   for (i=0;i<MAXCHANNELS;++i,++pChannel)
   {
      if (GetSubString(m_PartnerID,';',i,pChannel->m_PartnerID,sizeof(pChannel->m_PartnerID),NULL)<=0)
         break;
      mytrim(pChannel->m_PartnerID);
      if (pChannel->m_PartnerID[0]=='\0')
         break;
      pChannel->m_Status = -3;
   }
   m_nChannels = i;

   // UGate��¼�����һ�ȡ�¹ҵ�Channel��״̬
   if (!CheckUGParameter())
   {
      // Fail to Call FS(%d:%d) for UGate Login-411701(%s)!
      // �������õȴ��󣬷�������׼����������
      //       73001: No UGID(??) defined��
      //       73002: UG Login forbidden;
      //       73003: Invalid R_FUNCNO(%d)[!=UGFUNCNO(%d)] for UGID=%s!;
      return(-10001);
   }
   // 2. ����XPLink:
   memcpy(&xpBUnit,&g_BUnit,sizeof(xpBUnit));
   strcpy(xpBUnit.szBUGroupID,UGINNAME);
   if (m_XPLink.ToLink(&xpBUnit)<=0)
   {
      // ����ʧ�ܣ��и������أ�����Ϊksmbcc.ini�У�û������ "UGIN"���BU��
      g_LogFile.WriteLogEx(10001,"������'%s'������BCC�����ӣ�'%s'-UGate����˳�!",UGINNAME,g_BUnit.szBUGroupID);
      ToExit();
      return(-10002);      
   }

   m_UDLStatusRtn = 0; // Ĭ��Ϊ��������
   m_lastUDLTime = time(NULL);

   // 3. ���������Ѿ��������Channel:
   pChannel = m_Channel;
   rtn = 0;
   for (i=0;i<MAXCHANNELS;++i,++pChannel)
   {
      if (pChannel->m_Status>=0)
      {
         if (pChannel->OpenChannel()>=0)
            ++rtn;
      }
   }
   m_lastEODTime = time(NULL);
   return(rtn);
}

// ר�������ռ�UDL��״̬�ģ�����������ʽ�ύ��FIX������
int CUGateManage::Run()
{
   // �ƺ�����Ҫ��������߳�?? ����Ŀǰû�з����������Ҫ��UDL״̬��Processing�������???
   return(1);
}

bool CUGateManage::CheckUGParameter()
{
   // �����Ѿ��������ӵ�g_pSvrLink��FS�ύ����������󣬲���ʾLOGON:
   ST_CPACK rpack;
   ST_SDPACK *psd=(ST_SDPACK *)(&(rpack.pack));
   ResetNormalCPack(&rpack,0,1);
   rpack.head.RequestType = RT_UGUDLCMD;
   psd->usDataLength = sprintf((char *)(psd->data),"%s|%s|1|%d|%d",
      m_LocalID,m_PartnerID,g_pSvrLink->bccBFuncNo,m_UGDestNo);
   if (g_pSvrLink->ExtCall(0,m_FSDestNo,m_FSFuncNo,0,m_FSAckTime,&rpack,&rpack,NULL)<0)
   {
      g_LogFile.WriteLogEx(70301,"Fail to Call FS(%d:%d) for UGate Login-%d(%s)!",
         m_FSDestNo,m_FSFuncNo,RT_UGUDLCMD,psd->data);
      return(false);
   }
   if (rpack.head.retCode!=0)
   {
      // �������õȴ��󣬷�������׼����������
      g_LogFile.WriteLogEx(rpack.head.retCode,"%s",psd->data);
      return(false);
   }
   // OK: psd->data : <LocalID>|<��PartnerIDs(ML:0;CLSA:0;SWHK:-1;NOP:-3)>��
   g_LogFile.WriteLogEx(100,"%s",psd->data);
   char tmp[256];
   if (GetSubString(psd->data,'|',1,tmp,sizeof(tmp),NULL)<=0)
   {
      // ��Ӧ�õģ������϶�Ҫ�Բ��е�
   }
   int i;
   for (i=0;;++i)
   {
      char vtmp[28];
      char stmp[12];
      if (GetSubString(tmp,';',i,vtmp,sizeof(vtmp),NULL)<=0)
         break;
      GetSubString(vtmp,':',0,stmp,sizeof(stmp),NULL);
      CUGChannel *pChannel = FindChannel(stmp);
      if (pChannel!=NULL)
      {
         GetSubString(vtmp,':',1,stmp,sizeof(stmp),NULL);
         pChannel->m_Status = atoi(stmp);
      }
   }

   return(true);
}

void CUGateManage::ToExit()
{
   ToLogout();
   m_XPLink.bExit = true;
   m_XPLink.Close();
   g_pSvrLink->bExit = true;
   g_pSvrLink->Close();
}

CUGChannel * CUGateManage::FindChannel(const char *sPartnerID)
{
   int i;
   for (i=0;i<m_nChannels;++i)
   {
      if (strcmp(m_Channel[i].m_PartnerID,sPartnerID)==0)
      {
         return(m_Channel+i);
      }
   }
   return(NULL);
}

int CUGateManage::Processing()
{
   CheckUDLStatus();
   if (m_UDLStatusRtn<0)
   {
      g_LogFile.WriteLogEx(12001,"UDL is abnormal, ErrCode=%d! Exit...",m_UDLStatusRtn);
      ToExit();
      return(m_UDLStatusRtn);
   }
   if (time(NULL)>=m_lastEODTime+60)
   {
      CheckEOD_AllChannel();
      m_lastEODTime = time(NULL);
   }
   return(g_pSvrLink->Processing(&g_BUnit));   
}

void CUGateManage::ToLogout()
{
   char indata[256];
   int i;
   sprintf(indata,"%s|%s|0|%d|%d",
      m_LocalID,m_PartnerID,g_pSvrLink->bccBFuncNo,m_UGDestNo);
   HaveMessageIn(RT_UGUDLCMD,0,indata);
   for (i=0;i<m_nChannels;++i)
   {
      m_Channel[i].UpdateStatus(FS_DISABLE);
   }
   mysleep(100);  // �Ե�һ�£���PushData������Ϻ��ٷ���
}

int CUGateManage::HaveMessageIn(int reqtype, int pmode, const char *inmsg)
{
   ST_CPACK rpack;
   ST_SDPACK *psd=(ST_SDPACK *)(&(rpack.pack));
   char pm;
   if (!m_XPLink.LinkOK())
   {
      g_LogFile.WriteLogEx(12017,"UGateIn Link(%s:%d:%d) not ready!",
         UGINNAME,m_FSDestNo,m_FSFuncNo);
      m_UDLStatusRtn = -100; // ͨ������ǿ��UDL�˳�
      return(-1);  // �ڲ�����û��׼����
   }

   ResetNormalCPack(&rpack,0,1);
   rpack.head.RequestType = reqtype;
   // ����һ���fix��Ϣ���Ȳ��ᳬ����ST_PACK����
   //    if (psd->usDataLength>g_pXPack->GetPackLength())
   //       return(-1);
   psd->usDataLength = strlen(inmsg);
   strncpy(psd->data,inmsg,psd->usDataLength);

   psd->usDataLength = FormatInMsg(psd->data,psd->usDataLength);

   if (psd->usDataLength==0)
   {
      g_LogFile.WriteLogEx(12522,"No MsgType Formated in (%s), ignore it!",inmsg);
      return(0);
   }
   if (pmode)
   {
      pm = PM_ACK;
      if (m_iDebug>0)
      {
         g_LogFile.WriteLogEx(556,"MsgIn:%d-%s",reqtype,psd->data);
      }
   }
   else
   {
      pm = PM_INACK;
      if (m_iDebug&0x02)
      {
         g_LogFile.WriteLogEx(666,"MsgIn:%d-%s",reqtype,psd->data);
      }
   }

   CPMUTEX pMutex(&m_XPLMutex);
   return(m_XPLink.PushData(0,m_FSDestNo,m_FSFuncNo,0,&rpack,pm,0,NULL));
}


// ��ƽ̨�����յ���������Ϣ�������:
int CUGateManage::xProcess(TRUSERID *handle, char *rdata, int rdlen, int *iRetCode, char *szMsg)
{
   // ��Դ�� FS �� FM��
   int i;
   int rtn;
   ST_CPACK rcpack;
   
   SetAnswerMode(AM_CONFIRM);  // �Ƿ��������ͷ�ʽ�������أ�
   rtn = DecodeBuf((unsigned char *)rdata,rdlen,&rcpack,szMsg);
   if (rtn<sizeof(ST_PACKHEAD))
   {
      // ˵���յ��Ĳ������������ݰ���Ӧ�ûᱻBCC���˵ģ����Ժ��Լ���
      return(-1);
   }
   ST_SDPACK *psd = (ST_SDPACK *)&(rcpack.pack);
   char *pCmd;
   // ��������Ϣ��
   // 1. ��UGate�ڲ�����
   // 2. ֱ�ӷ��͸�UDL����
   switch (rcpack.head.RequestType)
   {
   case RT_UGUDLCMD: 
   case RT_UPSTATUS: // �յ����ָ��Channel��״̬
      // <LocalID>|<PartnerID>:<status>
      pCmd = strstr((const char *)(psd->data),"|");
      if (pCmd!=NULL)
         HandleChannelStatus(pCmd+1);
      break;
   case RT_CLOSEUDL:  // �رո���Channel
      for (i=0;i<m_nChannels;++i)
      {
         m_Channel[i].UpdateStatus(FS_DISABLE);
      }
      break;
   default:  // �������Ķ���ᵽҵ����FIX��Ϣ
//    case RT_NEWORDER:    // 411701   // IN / OUT: NewOrderSingle FIX Message
//    case RT_ORDERCXL:    // 411702   // IN / OUT: OrderCancel FIX Message
//    case RT_CXLREJECT:   // 411703   // IN / OUT: Cancel Reject FIX Message
//    case RT_ORDSTREQ:    // 411704   // IN / OUT: Order Status Request FIX Message
//    case RT_EXECREP:     // 411705   // IN / OUT: Execution Report FIX Message
//    case RT_OTHERBUS:    // 411799   // IN / OUT: һЩ��ͨ��ѯ��Ӧ���FIXҵ����Ϣ
      HandleOutFIXMessage((char *)psd->data);
      break;
   }
   return(0);   
}



int CUGateManage::CheckUDLStatus()
{
   char *pStatus;
   if (time(NULL)>=m_lastUDLTime+m_UDLRefStatus)
   {
      m_lastUDLTime = time(NULL);
      int len = sprintf(m_UDLStatus,"%s|",m_LocalID);
      pStatus = m_UDLStatus+len;
      if (sizeof(m_UDLStatus)>sizeof(ST_PACK)-sizeof(unsigned short))
         len = sizeof(ST_PACK)-sizeof(unsigned short)-len;
      else
         len = sizeof(m_UDLStatus)-len;
      m_UDLStatusRtn = UDLGetStatus(pStatus,len);
      if (m_UDLStatusRtn>=0)
      {
         // pStatus -- <PartnerID1>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>|...|<PartnerIDx>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>
         InChannelStatus(pStatus);
         // ��FSƽ̨����UDL��״̬
         HaveMessageIn(RT_UPSTATUS,0,m_UDLStatus);  // �Է��ղ������Ǿ��´���
      }
      else
      {
         g_LogFile.WriteLogEx(10667,"UDLStatus:%d-%s",m_UDLStatusRtn,m_UDLStatus);
      }
   }
   return(m_UDLStatusRtn);
}

int CUGateManage::InChannelStatus(char *instatus)
{
   // instatus  - <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerIDx>:<status>:<load>:<errmsg>
   char segtmp[512];
   int i;
   char partnerid[12]={0};
   int load;
   char eMsg[256]={0};
   int status;
   CUGChannel *pChannel;

   for (i=0;;++i)
   {
      if (GetSubString(instatus,'|',i,segtmp,sizeof(segtmp),NULL)<=0)
         break;
      GetSubString(segtmp,':',0,partnerid,sizeof(partnerid),NULL);
      mytrim(partnerid);
      GetSubString(segtmp,':',1,eMsg,sizeof(eMsg),NULL);
      status = atoi(eMsg);
      GetSubString(segtmp,':',2,eMsg,sizeof(eMsg),NULL);
      load = atoi(eMsg);
      GetSubString(segtmp,':',3,eMsg,sizeof(eMsg),NULL);
      pChannel = FindChannel(partnerid);
      if (pChannel!=NULL)
      {
         pChannel->ChannelStatus(status,load,eMsg);
      }
   }
   return(i);
}

void CUGateManage::HandleChannelStatus(const char *cmd)
{
   // cmd: <PartnerID>:<status>
   CUGChannel *pChannel;
   char tmp[256]={0};
   int status;
   if (GetSubString(cmd,':',0,tmp,sizeof(tmp),NULL)<=0)
      return;
   pChannel = FindChannel(tmp);
   if (pChannel==NULL)
      return;
   GetSubString(cmd,':',1,tmp,sizeof(tmp),NULL);
   status = atoi(tmp);
   if (status==FS_EOD)
   {
      // ��ר��EOD����
      if (UDLEndOfDay(m_LocalID,pChannel->m_PartnerID,tmp)>=0)
         EODDone(pChannel->m_PartnerID);
      else
         g_LogFile.WriteLogEx(75603,"Fail to EOD(%s): %s",pChannel->m_PartnerID,tmp);
   }
   else
      pChannel->UpdateStatus(status);
}

void FilterASC(CFIXData *pfixdata)
{
   // ��Ҫ�����µ�Լ������Text-Tag58�е������ַ���������
   char text[1024];  // �Ϊ1024
   int tlen = sizeof(text);
   int i;
   int tno;
   if ((tno=pfixdata->GetTag(TAG_TEXT,text,tlen))>=0)
   {
      for (i=0;text[0];++i)
      {
         if (text[i]>=127||text[i]<=0)
         {
            text[i]=0;
            break;
         }
      }
      if (i<=0)
         pfixdata->RemoveTagNo(tno);
      else
         pfixdata->UpdateTag(tno,TAG_TEXT,text,i+1);
   }
}

void CUGateManage::HandleOutFIXMessage(const char *fixmsg, const char *partnerid)
{
   // 8=<BeginString><SOH>35=<MsgType><SOH>49=<LocalID><SOH>56=<PartnerID><SOH>...
   char eMsg[256]={0};
   // ����TAG 49 Ϊ LocalID: �ڶ�ͨ��������£��������������:
   CFIXData fixdata;
   CUGChannel *pChannel;
   int rtn;
   char nfixmsg[MAXFIXMSGLEN];

   if (!fixdata.SetData(fixmsg,strlen(fixmsg)))
   {
      g_LogFile.WriteLogEx(10555,"Invalid OutMsg:%s",fixmsg);      
      return;
   }
   if (partnerid!=NULL && partnerid[0]!='\0')
   {
      fixdata.UpdateTag(-1,TAG_TargetCompID,partnerid);
   }
   fixdata.GetTag(TAG_TargetCompID,eMsg,(rtn=sizeof(eMsg)));
   if ((pChannel=FindChannel(eMsg))==NULL)
   {
      g_LogFile.WriteLogEx(10555,"Invalid TAG(%d) In OutMsg:%s",TAG_TargetCompID,fixmsg);
      return;
   }
   fixdata.UpdateTag(-1,TAG_SenderCompID,m_LocalID);
   if (m_bFilterASC) // Ŀ����Ϊ������FIXEngine�ģ���Ϊ���ܴ�����  2012/8/16 22:54:30
      fixdata.FilterNonASC();
   
   pChannel->FormatOutFIXData(&fixdata);  // ����Lua���Ը������ֶ���Ϣ�������䴦��

   fixdata.GetFIXData(nfixmsg,sizeof(nfixmsg));

   if (fixdata.GetTag(TAG_MsgType,eMsg,rtn=sizeof(eMsg))<0)
   {
      sprintf(eMsg,"MsgType(35) undefined!");
      rtn = -3;
   }
   else 
   {
      if (m_OutMode)
      {
         if (strcmp(eMsg,"D")==0
            // || strcmp(partnerid,"F")==0
            || strcmp(eMsg,"E")==0
            || strcmp(eMsg,"AB")==0)
            rtn = 0;  // �����ȼ�
         else
            rtn = 1;  // �ɽ��������ȶ����õ����ȼ�
         pChannel->HaveOutMsg(strlen(nfixmsg),nfixmsg,rtn);
         strcpy(eMsg,"ToOutQueue");
      }
      else // ֻ��UGFMQʹ�ñ�ģʽ
      {
         rtn = UDLOnMessageOut(nfixmsg,eMsg);
      }
   }
   if (m_iDebug>0)
   {
      g_LogFile.WriteLogEx(555,"MsgOut(%d-%s):%s",rtn,eMsg,nfixmsg);
   }
   else if (rtn<0)
   {
      g_LogFile.WriteLogEx(10555,"UDLOut Failure(%d-%s):%s",rtn,eMsg,nfixmsg);
   }
}

int CUGateManage::CheckEOD(int imode, const char *partnerid)
{
   // RT_CHECKEOD  411756   // IN: Check EOD of Partner <0-UG>|<UGID>|<PARTNERID>
   if (imode==0)
   {
      // 2012/5/10 13:31:47 ������Processing�У��д�������������ܴ�����ˣ�������ExtCall��ʽ
      char indata[256];
      sprintf(indata,"0|%s|%s",m_LocalID,partnerid);
      HaveMessageIn(RT_CHECKEOD,0,indata);  /* ��Ϊֻ�Ǵ���FS����EOD��飬FS�ڷ�����ҪEOD�Ļ�������ͨ��
                                            ��UGate����411730 or 411731 FS_EOD״̬��Ϣ������UDLEndOfDay���� */
      return(0);
   }
   else
   {
      // ��Ӧ�������������ģʽ
      ST_CPACK rpack;
      ST_SDPACK *psd = (ST_SDPACK *)&(rpack.pack);
      ResetNormalCPack(&rpack,0,1);
      rpack.head.RequestType = RT_CHECKEOD;
      psd->usDataLength = sprintf((char *)(psd->data),"1|%s|%s",m_LocalID,partnerid); // ��Ӧ�������������ģʽ
      if (g_pSvrLink->ExtCall(0,m_FSDestNo,m_FSFuncNo,0,m_FSAckTime,&rpack,&rpack,NULL)<0)
      {
         g_LogFile.WriteLogEx(75601,"Fail to Call FS(%d:%d) for UGate CheckEOD-%d(%s)!",
            m_FSDestNo,m_FSFuncNo,RT_CHECKEOD,psd->data);
         return(0);
      }
      if (rpack.head.retCode==0)
      {
         if (UDLEndOfDay(m_LocalID,partnerid,(char *)psd->data)>=0)
            EODDone(partnerid);
         else
         {
            g_LogFile.WriteLogEx(75602,"Fail to EOD(%s): %s",partnerid,(char *)psd->data);
         }
         return(1); // ��ʾ����EOD����
      }
      else
         return(0); // ��ʾ������EOD
   }
}

int CUGateManage::EODDone(const char *partnerid)
{
   // RT_CEODDONE  411757   // IN: Channel EOD Done Notification <UGID>|<PARTNERID>
   ST_CPACK rpack;
   ST_SDPACK *psd = (ST_SDPACK *)&(rpack.pack);
   ResetNormalCPack(&rpack,0,1);
   rpack.head.RequestType = RT_CEODDONE;
   psd->usDataLength = sprintf((char *)(psd->data),"%s|%s",m_LocalID,partnerid);
   if (g_pSvrLink->ExtCall(0,m_FSDestNo,m_FSFuncNo,0,m_FSAckTime,&rpack,&rpack,NULL)<0)
   {
      g_LogFile.WriteLogEx(75701,"Fail to Call FS(%d:%d) for Channel EOD Done Notification-%d(%s)!",
         m_FSDestNo,m_FSFuncNo,RT_CEODDONE,psd->data);
      return(-75701);
   }
   return(0);
}

// ��GetSSOrders(...)������ 2011-9-30 23:12:20
//DEL int CUGateManage::GetSSPendingOrders(const char *partnerid, L_MSGDATA &msglist)
//DEL {
//DEL    // RT_GETSSORD  411769   // IN: Get SSOrders from FS <flag>|<SellSide>...
//DEL    //  ��ȡ��UG_SSORDERS��SSORDERIDΪ�յļ�¼����SSCLORDID������
//DEL    ST_CPACK rpack;
//DEL    ST_PACK parray[100];
//DEL    ST_SDPACK *psd = (ST_SDPACK *)&(rpack.pack);
//DEL    msglist.clear();
//DEL    ResetNormalCPack(&rpack,0,1);
//DEL    rpack.head.RequestType = RT_GETSSORD;
//DEL    psd->usDataLength = sprintf((char *)(psd->data),"0|%s",partnerid);
//DEL    if (g_pSvrLink->ExtCall(0,m_FSDestNo,m_FSFuncNo,0,m_FSAckTime,&rpack,&rpack,parray)<0)
//DEL    {
//DEL       g_LogFile.WriteLogEx(76901,"Fail to Call FS(%d:%d) for Fetching SSOrders from FS -%d(%s)!",
//DEL          m_FSDestNo,m_FSFuncNo,RT_GETSSORD,psd->data);
//DEL       return(-76901);
//DEL    }
//DEL    while (1)
//DEL    {
//DEL       if (rpack.head.retCode!=0)
//DEL          break;
//DEL       for (int i=0;i<rpack.head.recCount;++i)
//DEL       {
//DEL          if (i>0)
//DEL             psd = (ST_SDPACK *)(parray+i-1);
//DEL          else
//DEL             psd = (ST_SDPACK *)&(rpack.pack);
//DEL          CMsgData md(psd->usDataLength,(const char *)psd->data);
//DEL          msglist.push_back(md);
//DEL       }
//DEL       if (rpack.head.nextflag==0)
//DEL          break;
//DEL       if (g_pSvrLink->ExtCallNext(m_FSAckTime,&rpack,parray)<0)
//DEL          break;
//DEL    }
//DEL    return(msglist.size());
//DEL }

int CUGateManage::GetBSExecRepts(const char *partnerid, L_MSGDATA &msglist)
{
   // RT_GETBSEXEC  411768   // IN: Get BSExec from FS <flag>|<BuySide>...
   ST_CPACK rpack;
   ST_PACK parray[100];
   ST_SDPACK *psd = (ST_SDPACK *)&(rpack.pack);
   msglist.clear();
   ResetNormalCPack(&rpack,0,1);
   rpack.head.RequestType = RT_GETBSEXE;
   psd->usDataLength = sprintf((char *)(psd->data),"0|%s",partnerid);
   if (g_pSvrLink->ExtCall(0,m_FSDestNo,m_FSFuncNo,0,m_FSAckTime,&rpack,&rpack,parray)<0)
   {
      g_LogFile.WriteLogEx(76801,"Fail to Call FS(%d:%d) for fetching BSExec from FS -%d(%s)!",
         m_FSDestNo,m_FSFuncNo,RT_GETBSEXE,psd->data);
      return(-76801);
   }
   while (1)
   {
      if (rpack.head.retCode!=0)
         break;
      for (int i=0;i<rpack.head.recCount;++i)
      {
         if (i>0)
            psd = (ST_SDPACK *)(parray+i-1);
         else
            psd = (ST_SDPACK *)&(rpack.pack);
         CMsgData md(psd->usDataLength,(const char *)psd->data);
         msglist.push_back(md);
      }
      if (rpack.head.nextflag==0)
         break;
      if (g_pSvrLink->ExtCallNext(m_FSAckTime,&rpack,parray)<0)
         break;
   }
   return(msglist.size());
}


const char * CUGateManage::GetPartners()
{
   // <PartnerID1>;<PartnerID2>;...;<PartnerIDn>
   return(m_PartnerID);
}

int CUGateManage::CheckEOD_AllChannel()
{
   int i;
   for (i=0;i<m_nChannels;++i)
   {
      if (m_Channel[i].m_Status>=0)
         CheckEOD(0,m_Channel[i].m_PartnerID);  // ������飬ʵ��EOD��FS����411731������
      // 2013/3/7 17:02:30 Ϊ���ܹ���ֹ��̨EOD�����һ���Ӻö�����Ϊ����һ��ʱ����
      mysleep(100);
   }
   return(i);
}

int CUGateManage::HaveOutMsg(const char *partnerid, const char *msg, int plevel)
{
   // ������ʹ�ñ��ӿڣ�ֻ���ڴ����������Ϣ�����쳣��ʱ���Զ����Է�����Ϣ��ʱ����
   // ����ҪԤ�������msg   -- 2012/5/18 11:03:27
//    CUGChannel *pChannel;
//    pChannel = FindChannel(partnerid);
//    if (pChannel==NULL)
//       return(-2);
// 
//    pChannel->HaveOutMsg(strlen(msg),msg,plevel);
//    return(plevel);
   HandleOutFIXMessage(msg,partnerid);
   return(plevel);
}

int CUGateManage::GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf)
{
   CUGChannel *pChannel;
   pChannel = FindChannel(partnerid);
   if (pChannel==NULL)
      return(-2);
   return(pChannel->GetOutMsg(outwaitms,msgbuf));
}

void CUGateManage::ToSetOutMode(int outmode)
{
   m_OutMode = outmode;
}

int CUGateManage::GetOutMsgSize(const char *partnerid)
{
   CUGChannel *pChannel;
   pChannel = FindChannel(partnerid);
   if (pChannel==NULL)
      return(-2);
   return(pChannel->GetOutMsgSize());   
}

int CUGateManage::GetSSOrders(int flag,const char *partnerid, L_MSGDATA &msglist)
{
   // RT_GETSSORD  411769   // IN: Get SSOrders from FS <flag>|<SellSide>...
   //  ��ȡ��UG_SSORDERS��SellSide�ļ�¼����SSCLORDID����������OrderIDֵ�ˣ�����Ҫ����37=OrderID
   ST_CPACK rpack;
   ST_PACK parray[100];
   ST_SDPACK *psd = (ST_SDPACK *)&(rpack.pack);
   msglist.clear();
   ResetNormalCPack(&rpack,0,1);
   rpack.head.RequestType = RT_GETSSORD;
   psd->usDataLength = sprintf((char *)(psd->data),"%d|%s",flag,partnerid);
   if (g_pSvrLink->ExtCall(0,m_FSDestNo,m_FSFuncNo,0,m_FSAckTime,&rpack,&rpack,parray)<0)
   {
      g_LogFile.WriteLogEx(76901,"Fail to Call FS(%d:%d) for Fetching SSOrders from FS -%d(%s)!",
         m_FSDestNo,m_FSFuncNo,RT_GETSSORD,psd->data);
      return(-76901);
   }
   while (1)
   {
      if (rpack.head.retCode!=0)
         break;
      for (int i=0;i<rpack.head.recCount;++i)
      {
         if (i>0)
            psd = (ST_SDPACK *)(parray+i-1);
         else
            psd = (ST_SDPACK *)&(rpack.pack);
         CMsgData md(psd->usDataLength,(const char *)psd->data);
         msglist.push_back(md);
      }
      if (rpack.head.nextflag==0)
         break;
      if (g_pSvrLink->ExtCallNext(m_FSAckTime,&rpack,parray)<0)
         break;
   }
   return(msglist.size());
}

// �����ڲ���������ĸ�����Ϣ�����ж��ַ���Ϣ����:
int CUGateManage::FormatInMsg(char *inmsg, int imlen)
{
   CFIXData fixdata;
   if (fixdata.SetData(inmsg,imlen))
   {
      // ֻ������FIX����ϢҪ���й�������:
      CUGChannel *pChannel;
      char partnerid[12];
      int rtn;
      if (fixdata.GetTag(TAG_SenderCompID,partnerid,rtn=sizeof(partnerid))<0)
      {
         // ��Ϣ���޶��ַ�����Ϣ
         return(imlen);
      }
      if ((pChannel=FindChannel(partnerid))==NULL)
      {
         // Ϊɶ���ַ�û���ڱ��������أ�
         return(imlen);
      }
      
      pChannel->FormatInFIXData(&fixdata);  // ����Lua���Ը������ֶ���Ϣ�������䴦��
      if (fixdata.GetTag(TAG_MsgType,partnerid,rtn=sizeof(partnerid))<0)
         return(0);  // ��ʾ�ϲ㣬��Ҫ��������ύ������

      imlen = fixdata.GetFIXData(inmsg,sizeof(ST_PACK)-sizeof(unsigned int));
   }
   // ���������Ҫ������inmsg�е�ʵ�ʳ���
   return(imlen);
}

bool CUGateManage::GetChannelInfo(int iChannel, char *info256)
{
   const char *pst;
   if (iChannel<0||iChannel>=m_nChannels)
      return(false);
   switch (m_Channel[iChannel].m_Status)
   {
   case FS_OPEN:
      pst = "Open";
      break;
   case FS_CONNECTING:
      pst = "Connecting";
      break;
   case FS_CLOSE:
      pst = "Closed";
      break;
   case FS_DISABLE:
      pst = "Disabled";
      break;
   default:
      pst = "Error";
      break;
   }
   sprintf(info256,"%s:%s:%d",
      m_Channel[iChannel].m_PartnerID,pst,m_Channel[iChannel].m_Load);
   return(true);
}

void CUGateManage::ReloadKFXFile(int iChannel)
{
   if (iChannel<0||iChannel>=m_nChannels)
      return;
   m_Channel[iChannel].LoadLuaFile();
}

int CUGateManage::HaveMessageIn(int reqtype, int pmode, CFIXData *pfixdata)
{
   ST_CPACK rpack;
   ST_SDPACK *psd=(ST_SDPACK *)(&(rpack.pack));
   char pm;
   if (!m_XPLink.LinkOK())
   {
      g_LogFile.WriteLogEx(12017,"UGateIn Link(%s:%d:%d) not ready!",
         UGINNAME,m_FSDestNo,m_FSFuncNo);
      m_UDLStatusRtn = -100; // ͨ������ǿ��UDL�˳�
      return(-1);  // �ڲ�����û��׼����
   }
   
   ResetNormalCPack(&rpack,0,1);
   rpack.head.RequestType = reqtype;

   CUGChannel *pChannel;
   char partnerid[12];
   int rtn;
   psd->usDataLength = 0;
   if (pfixdata->GetTag(TAG_SenderCompID,partnerid,rtn=sizeof(partnerid))>=0)
   {
      if ((pChannel=FindChannel(partnerid))!=NULL)
      {
         // ��ô��Ҫ����һ��:
         pChannel->FormatInFIXData(pfixdata);
         psd->usDataLength = pfixdata->GetFIXData(psd->data,sizeof(ST_PACK)-sizeof(unsigned int));
         if (pfixdata->GetTag(TAG_MsgType,partnerid,rtn=sizeof(partnerid))<0)
         {
            g_LogFile.WriteLogEx(12522,"No MsgType formated, Ignore a Msg(%s)!",psd->data);
            return(0);
         }
      }
   }
   if (psd->usDataLength<=0)
   {
      psd->usDataLength = pfixdata->GetFIXData(psd->data,sizeof(ST_PACK)-sizeof(unsigned int));      
   }
   if (pmode)
   {
      pm = PM_ACK;
      if (m_iDebug>0)
      {
         g_LogFile.WriteLogEx(556,"MsgIn:%d-%s",reqtype,psd->data);
      }
   }
   else
   {
      pm = PM_INACK;
      if (m_iDebug&0x02)
      {
         g_LogFile.WriteLogEx(666,"MsgIn:%d-%s",reqtype,psd->data);
      }
   }
      
   CPMUTEX pMutex(&m_XPLMutex);
   return(m_XPLink.PushData(0,m_FSDestNo,m_FSFuncNo,0,&rpack,pm,0,NULL));
}
