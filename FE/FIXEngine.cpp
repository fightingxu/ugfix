// FIXEngine.cpp: implementation of the CFIXEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <exception>
#include "StdAfx_Fmi.h"
#include "FIXSession.h"
#include "FIXEngine.h"
#include "fixbase.h"
#include "xpub.h"
#include "ugate.h"
#include "CListenerWrapper.h"
#include "UDLInterface.h"

#include "com/mintech/utils/fmi/JNIException.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CFixEngineFactory.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CProperties.h"
#include "com/sungard/cs/fix/fixgateway/api/capi/CFixStatus.h"

using com::sungard::cs::fix::fixgateway::api::capi::CFixEngineFactory;
using com::sungard::cs::fix::fixgateway::api::capi::CProperties;
using com::sungard::cs::fix::fixgateway::api::capi::CFixStatus;

CFIXEngine g_FIXEngine;
unsigned int g_iInWait;
unsigned int g_iOutWait;


// ������: UDLInitialize
// ���  : ������ 2011-8-17 14:42:01
// ����  : ��ʼ��UDLģ�飬������Ҫ���������������Ϣ
//       �ڲ�������������������Ϣ
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLInitialize()
{
   if (g_FIXEngine.Start())
      return(1);
   else
      return(-1);
}

// ������: UDLExit
// ���  : ������ 2011-8-18 21:03:38
// ����  : UGateҪ��UDL�˳�
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLExit()
{
   g_FIXEngine.Exit();
   return(1);
}


// ������: UDLGetStatus
// ���  : ������ 2011-8-21 10:15:51
// ����  : ���UDLģ���ڲ�״̬�����ڲ��쳣���򷵻�<0
//         �������ڲ�����ͨ������ڲ����������ٷ�����״̬��
//         ����ͨ�������������ʱ����UDL�ڲ���״̬��
//         ���������ٻ���һ���쳣��UGate�ᱻǿ���˳� (��Ҫ��������)
// ����  : int <0 : UDL�쳣�������������������ú��ָܻ���>=0:״̬���سɹ�����������
// ����  : char *statusmsg [OUT]: �����¸�ʽ���ظ���Partner��״̬��
//             <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerID2>:<status>:<load>:<errmsg>
//             status: 0 - û��������1 - �Ѿ���������
//             load: ����ֵ������û�б������OUT��Ϣ����
// ����  : unsigned int smsize [IN]: statusmsg�Ļ����ֽ���(��Ž�4000���ֽ�) 
int UDLGetStatus(char *statusmsg,unsigned int smsize)
{
   return(g_FIXEngine.GetSessionStatus(statusmsg,smsize));
}



// ������: UDLOpen
// ���  : ������ 2011-8-19 23:20:46
// ����  : ��ʽ�������Ự(Session)����Է�ϵͳ�Խ�
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLOpen(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   return(g_FIXEngine.OpenSession(sLocalID,sPartnerID,emsg));
}


// ������: UDLClose
// ���  : ������ 2011-8-19 23:34:35
// ����  : �ر���Է������ӣ�����Close״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLClose(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   return(g_FIXEngine.CloseSession(sLocalID,sPartnerID,emsg));
}


// ������: UDLEndOfDay
// ���  : ������ 2011-8-19 23:35:58
// ����  : �Ա�������Reset�������֮ǰ����������ݣ�������ر�״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLEndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   return(g_FIXEngine.EndOfDay(sLocalID,sPartnerID,emsg));
}

// ������: UDLOnMessageOut
// ���  : ������ 2011-8-18 20:39:40
// ����  : UG�յ�����FSƽ̨��FIX��Ϣ����Ҫͨ��UDL�������͸����ַ�
//          
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *fixmsg [IN]: ҵ����� FIX��ʽ��Message (�ο�Э��)
// ����  : char *eMsg [OUT]: ��ʧ�ܵ�ʱ��(��Э����ʧ��)�����ش�����Ϣ(<80�ֽ�)
int UDLOnMessageOut(const char *fixmsg, char *eMsg)
{
   SQLDebugLog(80000,"Error @ UGate Framework for OUTMODE!");
   strcpy(eMsg,"UGATE Error for OUTMODE!");
   return(-1);
//   return(g_FIXEngine.OnMessageOut(fixmsg,eMsg));
}


bool EmptyDataFile(const char *filename)
{
   FILE *fp;
   //fp = fopen(filename,"w");  // �����������ַ�ʽ�Ƿ������ 2012/12/20 0:04:44
   fp = sh_fopen(filename,"w",SH_DENYNO);
   if (fp!=NULL)
   {
      fclose(fp);
      return(true);
   }
   else
   {
      UG_WriteLog(8109,"Fail to open(%s) for empty:errno=%",filename,errno);
      return(false);
   }
}

bool ResetFSInOutFile(const char *filename,const char *sid)
{
   FILE *fp;
   //fp = fopen(filename,"wt");
   fp = sh_fopen(filename,"wt",SH_DENYNO);
   if (fp!=NULL)
   {
      fprintf(fp, 
         "#-- listing properties --\n"
         "%s_IN=1\n"
         "%s_OUT=1\n",
         sid,
         sid
         );
      fclose(fp);
      return(true);
   }
   else
   {
      UG_WriteLog(8119,"Fail to open(%s) for Reset:errno=%d",filename,errno);
      return(false);
   }
}

//////////////////////////////////////////////////////////////////////
// CFIXEngine Class
//////////////////////////////////////////////////////////////////////
// 2013/4/25 16:35:09 �ں�ͨUAT�����ڻ�ȡFIXSTAT��ʱ�򣬻ᴮ���ݣ�����A-Session��״̬���ݣ�������B-Session����
// ����FE�еĶԸýӿڶ��̲߳���ȫ�ġ���ˣ�ʹ��ȫ�ֶ�����CMUTEX����:
extern CMUTEX g_FIXMutex;  // �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIXEngine::CFIXEngine()
{
   m_vm = NULL;
   m_nSessions = 0;
}

CFIXEngine::~CFIXEngine()
{
   if (m_vm!=NULL)
   {
//       Environment::closeJVM();
//       m_vm = NULL;
   }
}

bool CFIXEngine::Start()
{
   if (m_vm!=NULL)
      return(true);
   /* Removed by CHENYH @ 2012/8/24 17:08:35
   // ��ֱ������Channel�е���Ϣ���д������ٲ���Session�еĶ���
   UG_SetOutMode(0); // ��0ģʽ��FIXEngine�ڲ�����OutMsg
   */
   UG_SetOutMode(1); // ����1ģʽ 2012/8/27 11:00:36
   strcpy(sLocalID,UG_GetLocalID());
   // ML;THOMSON;GL;BLP;BNP;BCL;SWHK;CLSA or KSCTS
   strcpy(sPartnerIDs,UG_GetPartners());
   //////////////////////////////////////////////////////////////////////////

   CFIXSession *pSession=m_Session;
   int i;

   for (i=0;i<MAXFIXSESSIONS;++i,++pSession)
   {
      if (GetSubString(sPartnerIDs,';',i,jar_path,sizeof(jar_path),NULL)<=0)
         break;
      mytrim(jar_path);
      if (jar_path[0]=='\0')
         break;
      pSession->Set(sLocalID,jar_path);
   }
   m_nSessions = i;

   g_iInWait = UG_INIReadInt("KSFIX","INWAIT",10);  // 2010-6-24 10:54:59  ����ƣ�GetInMsg(...)�е�WaitEventTime������CPU���ġ���Ϣ������Ӧʱ��
   if (g_iInWait<0)
      g_iInWait = 0;
   if (g_iInWait>1000)
      g_iInWait = 1000;
   
   g_iOutWait = UG_INIReadInt("KSFIX","OUTWAIT",10);  // 2010-6-24 10:55:16 ����ƣ�GetOutMsg(...)�е�WaitEventTime������CPU���ġ���Ϣ������Ӧʱ��
   if (g_iOutWait<0)
      g_iOutWait = 0;
   else if (g_iOutWait>1000)
      g_iOutWait = 1000;

   m_bOutMsgLog = (UG_INIReadInt("KSFIX","OUTLOG",0)!=0);  // 2012/6/10 20:38:08

   UG_INIReadTString("KSFIX","JARPATH",".;./fixengine.jar",jar_path,sizeof(jar_path));
   UG_INIReadTString("KSFIX","JARPARAM","-Duser.timezone=GMT+8",jar_param,sizeof(jar_param));
   receive_mode = UG_INIReadInt("KSFIX","RECEIVE_MODE",0);
   UG_INIReadTString("KSFIX","WORK_DIRECTORY","./FIXDATA/",workPath,sizeof(workPath));

   m_vm = Environment::initJVM(jar_path, jar_param);
   if (!m_vm)
   {
      UG_WriteLog(80000,"initJVM(%s,%s) is failed!",jar_path,jar_param);
      //throw std::bad_exception("initJVM is failed!");
      return(false);
   }
   try {
      createManagedAPI("default.cfg");
      m_managedAPI.attach(WrapCApiListener(&m_apilistener));
      if (receive_mode == 0)
         m_managedAPI.startRealtimeDispatcher();
      else
         m_managedAPI.startDispatcher();
   }
   catch (...) 
   {       
//       Environment::closeJVM();
//       m_vm = NULL;
      return(false);
   }
   return(true);
}

void CFIXEngine::createManagedAPI(const char *config_file)
{
   try {
      m_defaultprop = CFixEngineFactory::createProperties(config_file);
      m_defaultprop.put("WORK_DIRECTORY",workPath); // ����
      m_managedAPI = CFixEngineFactory::createFixEngine(m_defaultprop);
   }
   catch (JNIException je) {
      std::string strinfo = std::string(je.getMessage())+std::string(je.getStack());
      OutErrorFile("FE_throw0", je.getStack(), __FILE__, __LINE__);
      //UG_WriteLog(80001,"%s",strinfo.c_str());
      throw std::bad_exception(strinfo.c_str());
   }
   catch (...) {
      throw std::bad_exception("unknown error information!");
   }
}

void CFIXEngine::Exit()
{
   int i;
   CPMUTEX pMutex(&g_FIXMutex); // �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52 
   for (i=0;i<m_nSessions;++i)
   {
      m_Session[i].m_bStop = true;
   }
   // ��������Ϊ������ʾ�˳������沿�ָ������Ϊ�˼���Ƿ������˳�
   for (i=0;i<m_nSessions;++i)
   {
      m_Session[i].ToStopThreads();
   }
   if (m_vm!=NULL)
   {
      if (receive_mode == 0)
         m_managedAPI.stopRealtimeDispatcher();
      else
         m_managedAPI.stopDispatcher();
      m_managedAPI.close();
//       Environment::closeJVM();
//       m_vm = NULL;
   }
}

int CFIXEngine::GetSessionStatus(char *statusmsg,unsigned int smsize)
{
   // <PartnerID1>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>|...|<PartnerID2>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>
   if (m_vm==NULL)
   {
      // ��ʾû������������������:
      return(-1);
   }
   int i;
   if (m_nSessions<=0)
   {
      statusmsg[0]='\0';
      return(0);
   }
   unsigned int sisize = smsize/m_nSessions;
   int os=0;
   for (i=0;i<m_nSessions;++i)
   {
#if 0  // 2013/4/24 15:49:00  ����ֱ��ͨ��FEȡ״̬���°����̸߳�������
      int rtn;
      if (m_Session[i].IsLoadFESession() && (rtn=GetFESessionStatus(m_Session+i,statusmsg+os,sisize))>0)
      {
         os += rtn;
      }
      else
#endif
      {
         os += m_Session[i].GetStatusInfo(statusmsg+os,sisize);
      }
      if (i+1<m_nSessions)
      {
         statusmsg[os++]='|'; statusmsg[os]='\0';
      }
   }
   return(m_nSessions);   
}

int CFIXEngine::OpenSession(const char *localid, const char *partnerid, char *emsg)
{
   CFIXSession *pSession;
   if ((pSession=FindFIXSession(partnerid,localid))==NULL)
   {
      sprintf(emsg,"Invalid Session(%s-%s) to open",partnerid,localid?localid:"");
      return(-1);
   }
   // ��鵱ǰSession�Ƿ����������У���ΪConnecting��Open�У�����ǣ���ô�Ͳ�׼��
   // ����ֻ�ܳ����˳�����������:(
   if (pSession->m_LastStatus>0 && pSession->IsRun())
   {
      sprintf(emsg,"%s is in <%s>",partnerid,pSession->m_LastStatus>1?"OPEN":"CONNECTING");
      return(0);
   }
   
   pSession->ToStopThreads();

   if (!pSession->PreOpen(emsg))
   {
      pSession->SetError(FS_ERROR,"Fail to pre-open",0,0);
      return(-2);
   }
   if (!ToOpenFESession(pSession,emsg))
   {
      pSession->SetError(FS_ERROR,"Fail to Open FE Session",0,0);
      return(-3);
   }

   /* Removed by CHENYH @ 2013/5/8 10:09:30
   // ������Ҳ�ᵼ�����쳣�����������ڸո�����FE�е�Session�����ܻᵼ��FE�쳣���籨��
   05/08 09:14:42 FILE:c:\dd\projects\fix_oms\01����\ugate\fe\fixengine.cpp LINENO:426 -- [java.lang.OutOfMemoryError: unable to create new native thread
   
     at java.lang.Thread.start0(Native Method)
     
       at java.lang.Thread.start(Thread.java:574)
       
         at com.sungard.cs.fix.fixgateway.utl.SortedQueue.startDispatcher(SortedQueue.java:405)
         
           at com.sungard.cs.fix.fixgateway.utl.SortedQueue.flush(SortedQueue.java:437)
           
             at com.sungard.cs.fix.fixgateway.ses.FixSession.performEODOutgoing(FixSession.java:1383)
             
               at com.sungard.cs.fix.fixgateway.ses.FixSession.performEOD(FixSession.java:1337)
               
                 at com.sungard.cs.fix.fixgateway.ses.InConnectState.handleAPI_EOD(InConnectState.java:155)
                 
                   at com.sungard.cs.fix.fixgateway.ses.FixSession.EOD(FixSession.java:1190)
                   
                     at com.sungard.cs.fix.fixgateway.api.BasicAPI.controlCommand(BasicAPI.java:396)
                     
                       at com.sungard.cs.fix.fixgateway.api.MultiAPI.controlCommand(MultiAPI.java:336)
                       
                         at com.sungard.cs.fix.fixgateway.api.DecoratorAPI.controlCommand(DecoratorAPI.java:68)
                         
                           at com.sungard.cs.fix.fixgateway.api.ManagedAPIImpl.controlCommand(ManagedAPIImpl.java:418)
                           
                             at com.sungard.cs.fix.fixgateway.api.capi.CManagedAPI.controlCommand(CManagedAPI.java:96)
                             
                               ]
   ��ֱ̫�ɶ���! ����������Ҳû��ɶ��ϵ�ģ���Ϊ����Close�׶��Ѿ���IN/OUT����Ϣ�ļ��Ѿ�Reset�ˡ�2013/5/8 10:17:21

   pSession->CheckEODAfterOpen(); // 2013/4/27 14:53:38 �����CloseSession��ʱ���Ƿ�FSҪ����EOD��
   ***************************************/

   // ���������߳�:
   if (StartThread(OThreadRun,pSession)<0)
   {
      pSession->SetError(FS_ERROR,"Fail to Start Out Thread",0,0);
      return(-4);
   }
   pSession->GetReloadCount();
   return(1);
}


int CFIXEngine::CloseSession(const char *localid, const char *partnerid, char *emsg)
{
   char cmd[40];
   CFIXSession *pSession = FindFIXSession(partnerid);
   if (NULL!=pSession)
   {
      pSession->m_InOpen=false;
   }
   try
   {
      sprintf(cmd,"CLOSE %s__%s",sLocalID,partnerid);

      UG_WriteLog(1857,"FIXSession(%s) do FE-Close",partnerid);

      CPMUTEX pMutex(&g_FIXMutex); // �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52 
      m_managedAPI.controlCommand(cmd);
      return(1);
   }
   catch (JNIThrowable &je)
   {
      OutErrorFile("FE_throwCLOSE", je.getStack(), __FILE__, __LINE__);
      //throw je;
   }
   sprintf(emsg,"Fail to %s",cmd);
   return(-1);
}

int CFIXEngine::DoEOD(const char *partnerid)
{
   // �Ƿ�Ҫ�����ݱ��ݳ���?
   UG_WriteLog(1856,"FIXSession(%s) FE-EOD",partnerid);
   try
   {
      CPMUTEX pMutex(&g_FIXMutex); // �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52 
      char sessionID[32];
      sprintf(sessionID,"%s__%s",sLocalID,partnerid);
      string cmd("EOD ");
      cmd += sessionID;
      m_managedAPI.controlCommand(cmd);
      return(1);
   }
   catch (JNIThrowable &je)
   {
      OutErrorFile("FE_throwEOD", je.getStack(), __FILE__, __LINE__);
      //throw je;
   }
   return(-1);
}

//DEL int CFIXEngine::OnMessageOut(const char *fixmsg, char *eMsg)
//DEL {
//DEL    char partnerid[12]={0};
//DEL    char msgtype[8]={0};
//DEL    CFIXSession *pSession;
//DEL    int plevel=0;
//DEL    if (UG_PickupTagValue(fixmsg,TAG_TargetCompID,partnerid,sizeof(partnerid))==NULL
//DEL       || (pSession=FindFIXSession(partnerid))==NULL)
//DEL    {
//DEL       sprintf(eMsg,"Invalid TargetCompID=%s",partnerid);
//DEL       return(-1);
//DEL    }
//DEL    if (UG_PickupTagValue(fixmsg,TAG_MsgType,msgtype,sizeof(msgtype))==NULL)
//DEL    {
//DEL       strcpy(eMsg,"No MsgType in fixmsg");
//DEL       return(-2);
//DEL    }
//DEL    if (strcmp(msgtype,"8")==0)
//DEL    {
//DEL       // ����ִ�б��棬�ͷ��ڵ����ȼ��Ķ����У����������NewOrder����Ҫ��Ϣ
//DEL       // ��Ϊ��ƽ̨֧�ִ󶩵�������˲����д�����ִ�б��棨�ɽ��ر�����Ϣ
//DEL       plevel = 1;
//DEL    }
//DEL    pSession->HaveOutMsg(strlen(fixmsg),fixmsg,plevel);
//DEL    return(0); // ��ʾ�������д���δ�������
//DEL }

// ������: CFIXEngine::SendFIXMessage2FE
// ���  : ������ 2011-8-24 13:49:33
// ����  : ������������󣬽�FIX��Ϣ�ύ��FIXEngine������ʽ����
//       ע��: ���뾭����ЧSession�ļ��󣬲��ܵ���
// ����  : int <0: ����ʧ�ܣ�����: ���ͳɹ�
// ����  : const char *fixmsg [IN]: ��Ҫ���͵�FIX��Ϣ
int CFIXEngine::SendFIXMessage2FE(const char *fixmsg)
{
   if (fixmsg==NULL||fixmsg[0]=='\0')
      return(0);
   try
   {
      if (m_bOutMsgLog)  // 2012/6/10 20:53:16 Ϊ�˸����ڲ������Ч��
      {
         UG_WriteLog(5551,"Out2FE:%s",fixmsg);
      }
      std::string cs(fixmsg);
      CPMUTEX pMutex(&g_FIXMutex); // �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52 
      m_managedAPI.sendMessage(cs);
   }
   catch (JNIThrowable &je)
   {
      UG_WriteLog(80010,"Error to FESendFIXMsg:%s",fixmsg);
      OutErrorFile("FE_throwSEND", je.getStack(), __FILE__, __LINE__);
      return(-10);
   }
   return(1);
}

CFIXSession * CFIXEngine::FindFIXSession(const char *partnerid, const char *localid)
{
   int i;
   for (i=0;i<m_nSessions;++i)
   {
      if (m_Session[i].m_PartnerID.compare(partnerid)==0
         &&(localid==NULL||m_Session[i].m_LocalID.compare(localid)==0))
      {
         return(m_Session+i);
      }
   }
   return(NULL);
}

int PushInLMsgData(char *msg, int msglen, L_MSGDATA &mlist)
{
   try
   {
      CMsgData mdata(msglen,msg);
      mlist.push_back(mdata);
      return(1);
   }
   catch (exception e)
   {
      return(0);   	
   }
}

#define IDXCACHELEN 64
#define KEYLENGTH   17
// ��ȡFIXEngine������In��Outҵ����Ϣ���ݣ����ڻָ�
int CFIXEngine::ReadFEMsgData(const char *IN_OUT, const char *partnerid, L_MSGDATA &mlist)
{
   char rfile[MAXFIXMSGLEN];
   FILE *fpIdx;
   FILE *fpData;
   FILE *fpBase;
   int i,ilastmsgseqnum;
   char key[40];
   mlist.clear();  // ���б����
   // CYHPSW__CYHLSW:  2012/12/23 0:13:11 Ϊ��ȫ������Ȼ����һ��MsgSeqNumber
   sprintf(rfile,"%s%s__%s/%s__%s",
      workPath,sLocalID,partnerid,
      sLocalID,partnerid);
   fpBase = sh_fopen(rfile,"rt",SH_DENYNO);
   if (fpBase==NULL)
   {
      UG_WriteLog(8000,"Fail to open FEMsgData %s",rfile);
      return(0);
   }
   i = sprintf(key,"%s__%s_%s=",sLocalID,partnerid,IN_OUT);
   ilastmsgseqnum = 1;
   while (fgets(rfile,1024,fpBase))
   {
      if (memcmp(rfile,key,i)==0)
      {
         ilastmsgseqnum = atoi(rfile+i);
         break;
      }
   }
   fclose(fpBase);

   // <workPath>/<local>__<remote>/ 
   sprintf(rfile,"%s%s__%s/%s.idx",
      workPath,sLocalID,partnerid,IN_OUT);
   fpIdx = sh_fopen(rfile,"rb",SH_DENYNO);
   sprintf(rfile,"%s%s__%s/%s.dat",
      workPath,sLocalID,partnerid,IN_OUT);
   fpData = sh_fopen(rfile,"rb",SH_DENYNO);
   if (fpIdx==NULL || fpData==NULL)
   {
      UG_WriteLog(8001,"Fail to open FEMsgData %s",rfile);
      if (fpIdx!=NULL)
         fclose(fpIdx);
      if (fpData!=NULL)
         fclose(fpData);
      return(0);
   }
   int n=0;
   // idx: 4                0,191                                          
   while (fread(rfile,IDXCACHELEN,1,fpIdx)>0)
   {
      long offset;
      int length;
      int ims;
      rfile[IDXCACHELEN]='\0';
      char *pc = strstr(rfile+KEYLENGTH,",");
      length = atoi(pc+1); 
      *pc='\0';
      offset = atoi(rfile+KEYLENGTH);
      rfile[KEYLENGTH]='\0';
      ims = atoi(rfile);
      if (length<=KEYLENGTH||offset<0
         ||ims>=ilastmsgseqnum) // 2012/12/23 0:12:57 ����MsgSeqNum�ж�
         break;
      fseek(fpData,offset,SEEK_SET);
      if (fread(rfile,length,1,fpData)<=0)
         break;
      rfile[length]='\0';
      if (PushInLMsgData(rfile+KEYLENGTH,length-KEYLENGTH,mlist)<=0)
         break;
      ++n;
   }
   fclose(fpData);
   fclose(fpIdx);
   return(n);
}

int CFIXEngine::EndOfDay(const char *localid, const char *partnerid, char *emsg)
{
   CFIXSession *pSession;
   if ((pSession=FindFIXSession(partnerid,localid))==NULL)
   {
      sprintf(emsg,"Invalid Session(%s-%s) to open",localid?localid:"",partnerid);
      return(-1);
   }
   if (pSession->DoEODProcess()<0)
   {
      sprintf(emsg,"Fail to do EOD (%s-%s)",localid?localid:"",partnerid);
      return(-1);
   }
   return(1);
}

bool CFIXEngine::ToOpenFESession(CFIXSession *pSession, char *emsg)
{
   char tmp[40];
   sprintf(tmp,"%s.cfg",pSession->m_PartnerID.c_str());
   UG_WriteLog(1859,"FIXSession(%s) do FE-Open",pSession->m_PartnerID.c_str());
   try
   {
      CPMUTEX pMutex(&g_FIXMutex); // �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52 
      CProperties m_properties = CFixEngineFactory::createProperties(tmp);
//      m_properties.put("WORK_DIRECTORY",workPath); // ����
//       printf("Open %s__%s\n",
//          m_properties.get("SENDER_COMP_ID[0]").c_str(),
//          m_properties.get("TARGET_COMP_ID[0]").c_str());
      int reload = pSession->GetReloadCount();
      if (reload>0)
      {
         sprintf(tmp,"%d",reload);
         m_properties.put("RELOAD_FLAG[0]",tmp);  // �Ƿ������Ҫ�أ�
      }
      sprintf(tmp,"Open %s__%s",sLocalID,pSession->m_PartnerID.c_str());
      m_managedAPI.newAPI(m_properties);
      m_managedAPI.controlCommand(tmp);

      //sprintf(tmp,"%s__%s",sLocalID,pSession->m_PartnerID.c_str());

      // 2013/4/24 15:11:04 ��Ϊ��Open�󣬾��ȸ�һ���ӿ����ں���״̬����
      // pSession->m_fixStat = m_managedAPI.getStatus(tmp);
      //////////////////////////////////////////////////////////////////////////
      
      pSession->m_InOpen = true;
      return(true);
   }
   catch (JNIThrowable &je) {
      OutErrorFile("FE_throwOPEN", je.getStack(), __FILE__, __LINE__);
      //throw je;
   }
   sprintf(emsg,"Fail to %s",tmp);
   return(false);
}

void CFIXEngine::UpdateStatusChanged(const char *sessionID, int newState, int oldState, int reasonCode, const char *reasonText)
{
   CFIXSession *pSession;
   const char *pp;
   if (sessionID==NULL||(pp=strstr(sessionID,"__"))==NULL)
      return;
   pp += 2;  // ����"__"
   pSession = FindFIXSession(pp,NULL);
   if (pSession==NULL)
      return;
   pSession->StatusChanged(newState,oldState,reasonCode,reasonText);
}

// ��FIXEngine�ڲ��ص��������ʾ��һ��FIXMsg�յ���
// ����Ҫ�����߳�ȥ�����ˣ���ֱ����FE�ص���ֱ���ύ��FS��
void CFIXEngine::FEHaveInMessage(const char *fixmsg)
{
   // ��MsgType='F'/'G'Ҫ�ڲ�ȥ����һ��
   CFIXSession *pSession;
   char partnerid[12];
   //char msgtype[8];
   char origclordid[24];

   //UG_PickupTagValue(fixmsg,TAG_MsgType,msgtype,sizeof(msgtype));

   UG_PickupTagValue(fixmsg,TAG_SenderCompID,partnerid,sizeof(partnerid));
   pSession = FindFIXSession(partnerid,NULL);
   if (pSession==NULL)
   {
      UG_WriteLog(80556,"Invalid FE InMsg:%s",fixmsg);
      return; // ��Ҫ������ȥ�ˣ���ô�����أ�
   }
   // ȡMsgSeqNumֵ���Է�ֹ�ظ��ύ
   UG_PickupTagValue(fixmsg,TAG_MsgSeqNum, origclordid,sizeof(origclordid));
   if (pSession->IsNewInMsg(atoi(origclordid)))   
   {
      // ����SS_OData��PK����OrderID����ˣ������������ 2012/4/3 11:32:28
//       if (strcmp(msgtype,"F")==0
//          ||strcmp(msgtype,"G")==0)
//       {
//          UG_PickupTagValue(fixmsg,TAG_OrigClOrdID, origclordid,sizeof(origclordid));
//          pSession->HaveInCancel(origclordid);
//       }
//       else if (strcmp(msgtype,"D")==0)
//       {
//          // Ϊ�ظ�������Ϣ�������ر���Ҫ��
//          UG_PickupTagValue(fixmsg,TAG_ClOrdID, origclordid,sizeof(origclordid));
//          pSession->HaveInNewOrder(origclordid);
//       }
      UDLHaveMessageIn(partnerid,fixmsg);
   }
   else
   {
      UG_WriteLog(80557,"Overdue FE InMsg:%s",fixmsg);
   }
}


int transState(int oldState);

int CFIXEngine::GetFESessionStatus(CFIXSession *pSession, char *statusinfo, unsigned int sisize)
{
#if 0  // ����ʹ�����������߳��б����� 2013/4/25 21:31:18
   // ����������FE��ֱ�Ӷ�ȡSession��״̬��Ϣ��<PartnerID1>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>
//   return(0);
   CFixStatus fixStat;
   char sid[36];
   sprintf(sid,"%s__%s",
      sLocalID,
      pSession->m_PartnerID.c_str());
//    string sid(sLocalID);
//    sid +="__"+pSession->m_PartnerID;
   try
   {
      /* TODO Tracing @ 2013/4/24 10:17:18
      ������ٵĵط�: 
         �����ض�����£���������Ϊ�������߳��У��ṩ����̨�����ͱ�UGFIX״̬��Ϣ������ط����쳣��
         û����MsgIn 411731�����������������FE�еĺ���ʱ����FE�ڲ���Blockס��:(
         ��������.... �д��ڸ���������FE��־���������ʱ��������FE�ڲ�һ��Session������Opne-Close��Ϣ��
      ************************************************************************/
      fixStat = m_managedAPI.getStatus(sid);
//      string pn = fixStat.getTargetCompID();
      int ostate = transState(fixStat.getFixState());
      //string ertxt = fixStat.getStateReasonText();
//       if (fixStat.getTargetCompID().empty())
//          return(-1);
      int len = sprintf(statusinfo,"%s:%d:%u:",
         pSession->m_PartnerID.c_str(),
         ostate,
         pSession->GetLoad());
      int imsgs=fixStat.getExpectedInSeqNum();
      int omsgs=fixStat.getExpectedOutSeqNum();
      int nlen = sprintf(statusinfo+len,"RC(%d)",
//          fixStat.getExpectedInSeqNum(),
//          fixStat.getExpectedOutSeqNum(),
         fixStat.getStateReasonCode());
      pSession->SetError(ostate,statusinfo+len,imsgs,omsgs);
      len += nlen;
      len += sprintf(statusinfo+len,":%d:%d",imsgs,omsgs);
      return(len);
   }
   catch (JNIThrowable &je) 
   {
      OutErrorFile("FE_throwSTAT", je.getStack(), __FILE__, __LINE__);
      return(-10);
   }
   catch (...)
#endif
   {
   	return(-100);
   }
}

bool CFIXEngine::ResetFIXSessionData(const char *partnerid)
{
   char rfile[256];
   char dpath[256];
   char sid[40];
   sprintf(sid,"%s__%s",sLocalID,partnerid);
   sprintf(dpath,"%s%s",
      workPath,
      sid);  // C:\dd\projects\FIXIII\UGate\ksugbu\FIXDATA\CYHUG1__GL

   sprintf(rfile,"%s/IN.idx",dpath);
   if (!EmptyDataFile(rfile))
      return(false);

   sprintf(rfile,"%s/IN.dat",dpath);
   if (!EmptyDataFile(rfile))
      return(false);

   sprintf(rfile,"%s/OUT.idx",dpath);
   if (!EmptyDataFile(rfile))
      return(false);

   sprintf(rfile,"%s/OUT.dat",dpath);
   if (!EmptyDataFile(rfile))
      return(false);

   sprintf(rfile,"%s/%s",
      dpath,
      sid); // C:\dd\projects\FIXIII\UGate\ksugbu\FIXDATA\CYHUG1__GL\CYHUG1__GL
   if (!ResetFSInOutFile(rfile,sid))
      return(false);

   sprintf(rfile,"%s/%s_bak",
      dpath,
      sid); // C:\dd\projects\FIXIII\UGate\ksugbu\FIXDATA\CYHUG1__GL\CYHUG1__GL_bak
   /* Removed by CHENYH @ 2013/4/24 9:29:43 ��Ȼ�Ǵ����:(
   if (ResetFSInOutFile(rfile,sid))
   ***************************************/
   if (!ResetFSInOutFile(rfile,sid))
      return(false);

   return(true);
}

// �ⲿ������g_FIXMutex��ռʹ�ã�����CFIXSession��ȥ������
// �ǳ�����FE��m_managedAPI�Ƿ��ڶ��߳���Ϊ��ȫ�ģ���ˣ����������������� 2013/4/25 21:24:52 
void CFIXEngine::ReflushStatus(CFIXSession *pSession)
{
   CFixStatus m_fixStat; // 2013/4/24 14:40:30 Ϊ�˽�Session�ڲ�״̬��ȡ��ת��OThread�У�����Ӱ������Session���������Ƶ�
   char tmp[256];
   sprintf(tmp,"%s__%s",pSession->m_LocalID.c_str(),pSession->m_PartnerID.c_str());
   try
   {
      m_fixStat = m_managedAPI.getStatus(tmp);
      //SNPRINTF(tmp,sizeof(tmp)-1,"RC(%d)",m_fixStat.getStateReasonCode());
      
      pSession->SetError(transState(m_fixStat.getFixState()),
         NULL, // ���޸�ԭ����״̬��Ϣ����
         m_fixStat.getExpectedInSeqNum(),
         m_fixStat.getExpectedOutSeqNum());
   }
   catch (JNIThrowable &je)
   {
      OutErrorFile("FE_throwSTAT", je.getStack(), __FILE__, __LINE__);
   }
}
