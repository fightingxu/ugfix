// KSFTS.cpp: implementation of the CKSFTS class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "UDLInterface.h"
#include "fixbase.h"
#include "ugate.h"
#include "nbccclt.h"
#include "nbccsvr.h"
#include "KSFTS.h"

CKSFTS g_KSFTS;
// ������: UDLInitialize
// ���  : ������ 2011-8-17 14:42:01
// ����  : ��ʼ��UDLģ�飬������Ҫ���������������Ϣ
//       �ڲ�������������������Ϣ
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLInitialize()
{
   BCCSvrInit("fwd",600);
   UG_SetOutMode(1); // ���õ���UG_GetOutMsg����
   return(g_KSFTS.Initialize());
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
   return(g_KSFTS.GetStatus(statusmsg,smsize));
}

// ������: UDLExit
// ���  : ������ 2011-8-18 21:03:38
// ����  : UGateҪ��UDL�˳�
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLExit()
{
   g_KSFTS.Exit();
   BCCSvrExit();
   return(0);
}

// ������: UDLOpen
// ���  : ������ 2011-8-19 23:20:46
// ����  : ��ʽ�������Ự(Session)����Է�ϵͳ�Խ�
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLOpen(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   int rtn;
   rtn = g_KSFTS.Open(sLocalID,sPartnerID,emsg);
   if (rtn<0)
      g_KSFTS.Close();
   return(rtn);
}


// ������: UDLClose
// ���  : ������ 2011-8-19 23:34:35
// ����  : �ر���Է������ӣ�����Close״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLClose(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   g_KSFTS.Close();
   return(0);
}


// ������: UDLEndOfDay
// ���  : ������ 2011-8-19 23:35:58
// ����  : �Ա�������Reset�������֮ǰ����������ݣ�������ر�״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLEndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   return(g_KSFTS.EndOfDay(sLocalID,sPartnerID,emsg));
}

// ������: UDLOnMessageOut
// ���  : ������ 2011-8-18 20:39:40
// ����  : UG�յ�����FSƽ̨��FIX��Ϣ����Ҫͨ��UDL�������͸����ַ�
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *fixmsg [IN]: ҵ����� FIX��ʽ��Message (�ο�Э��)
// ����  : char *eMsg [OUT]: ��ʧ�ܵ�ʱ��(��Э����ʧ��)�����ش�����Ϣ(<80�ֽ�)
int UDLOnMessageOut(const char *fixmsg, char *eMsg)
{
   // ���ڱ�ģʽ����OUTMODE=1�����UGATE���Ӧ�ò����ñ�����:
   SQLDebugLog(80000,"Error @ UGate Framework for OUTMODE!");
   strcpy(eMsg,"UGATE Error for OUTMODE!");
   return(-1);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKSFTS::CKSFTS()
{
   memset(m_PartnerID,0,sizeof(m_PartnerID));
   memset(m_LocalID,0,sizeof(m_LocalID));
   m_bRunning = false;
   m_LastOutTime = m_LastDoneTime = time(NULL);  // ��һ����û���õ�
   memset(m_LastClOrdID,0,sizeof(m_LastClOrdID));
   memset(m_LastIContractNo,0,sizeof(m_LastIContractNo));
   m_DoneCnt = 0;
   m_OutCnt = 0;
   m_Status = FS_DISABLE;
}

CKSFTS::~CKSFTS()
{

}

#define IMARKETFILE "fmarket.txt"
int CKSFTS::Initialize()
{
   char tmp[256];
   int rtn,i;
   char *pc;
   
   m_bRunning = false;
   m_Status = FS_DISABLE; // ��û����ʽ����
   STRNCPY(m_LocalID,UG_GetLocalID());
   STRNCPY(m_PartnerID,UG_GetPartners());
   pc = strstr(m_PartnerID,";");
   if (pc!=NULL)
      *pc = '\0'; // ��ֻ���ǵ�һ��

   UG_INIReadTString("KSFTS","XPACK","cpack.dat",m_XPackFile,sizeof(m_XPackFile));
   
   UG_INIReadTString("KSFTS","KSFTSSVR","0:19900",tmp,sizeof(tmp));
   pc = strstr(tmp,":");
   if (pc==NULL)
   {
      SQLDebugLog(10000,"Invalid [KSFTS] KSFTSSVR=%s defined",tmp);
      return(-1);
   }
   *pc='\0'; ++pc;
   m_SvrDestNo = atoi(tmp);
   m_SvrFuncNo = atoi(pc);

   UG_INIReadTString("KSFTS","OPERATOR","FIXAPPSvr",m_Operator,sizeof(m_Operator));

   if (LoadMarketCode()<=0)
   {
      SQLDebugLog(10020,"Fail to load MarketCode File:%s",IMARKETFILE);
      return(-2);
   }

   // ��ʼ���뽻��ϵͳ�Խӵ�ͨ��ƽ̨:
   rtn = m_DRouters.Initialize(tmp);
   if (rtn<0)
   {
      SQLDebugLog(10001,"Fail to load DRTP Info(%d):%s",rtn,tmp);
      return(rtn-100);
   }
   
   m_bch = BCNewHandle(GetXPackFile());
   if (m_bch==NULL)
   {
      SQLDebugLog(10005,"Fail to load XPACKFile(%s)",GetXPackFile());
      return(-500);
   }
   // ��ʼ���ɽ��ر��߳�
   rtn = m_CJThread.Initialize(tmp);
   if (rtn<0)
   {
      SQLDebugLog(10003,"Fail to Init CJTHREAD(%d):%s",rtn,tmp);
      return(rtn-300);
   }
   
   
   // ��ȡ��������:
   m_OThreadCnt = UG_INIReadInt("KSFTS","OUTTHREADS",1);
   if (m_OThreadCnt>MAXOUTTHREADS)
      m_OThreadCnt = MAXOUTTHREADS;
   for (i=0;i<m_OThreadCnt;++i)
   {
      if ((rtn=m_OThreads[i].Initialize(i,tmp))<0)
      {
         SQLDebugLog(10004,"Fail to Init OUTTHREAD(%d):%s",rtn,tmp);
         return(rtn-400);
      }
   }
   
   m_IThreadCnt = UG_INIReadInt("KSFTS","INTHREADS",1);
   if (m_IThreadCnt>MAXINTHREADS)
      m_IThreadCnt = MAXINTHREADS;
   for (i=0;i<m_IThreadCnt;++i)
      m_IThreads[i].m_ID = i;
   
   UG_INIReadTString("KSFTS","WFSx","f",m_WTFSx,sizeof(m_WTFSx));

   return(0);
}

const char * CKSFTS::GetXPackFile()
{
   return(m_XPackFile);
}

// ���  : ������ 2011-9-18 11:26:31
// ����  : ��KSFTS���������ù���
// ����  : int <0: ����ʧ��, �μ�errMsg�������Ϣ��-103:���ڽ���Ӧ��ʱ
//             >=0: ���óɹ������bch�еķ�����Ϣ
// ����  : BCHANDLE bch [IN/OUT]: ���úͷ����õ����ݻ�����
// ����  : char *errMsg [OUT]: �ڷ���ʧ�ܵ�ʱ����д����Ĵ�����Ϣ
int CKSFTS::CallSvr(BCHANDLE bch, char *errMsg)
{
   return(m_DRouters.CallSvr(bch,m_SvrDestNo,m_SvrFuncNo,errMsg));
}

int CKSFTS::CallNext(BCHANDLE bch, char *errMsg)
{
   return(m_DRouters.CallNext(bch,errMsg));
}


int CKSFTS::LoadMarketCode()
{
   char tmp[512];
   char *pv;
   FILE *fp;
   int n=0;
   fp = fopen(IMARKETFILE,"rt");
   if (fp==NULL)
   {
      SQLDebugLog(10044,"Fail to open %s",IMARKETFILE);
      return(0);
   }
   while (fgets(tmp,sizeof(tmp),fp))
   {
      mytrim(tmp);
      if (tmp[0]=='/')
         continue;
      pv = strstr(tmp,"|");
      if (pv==NULL)
         continue;
      *pv = '\0'; ++pv;
      mytrim(tmp); mytrim(pv);
      if (tmp[0] && pv[0])
      {
         m_Market.insert(make_pair(string(tmp),string(pv)));
         ++n;
      }
   }
   fclose(fp);
   return(n);
}



int CKSFTS::Open(const char *sLocalID, const char *sPartnerID, char *emsg)
{
   int i;
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
   
   m_bRunning = true;  // ��ʾҪ�����߳���������������
   
   if (!m_DRouters.ToStartCJRecv(emsg))
   {
      return(-4);
   }
   
   if (!m_CJThread.ToStartCJProcess(emsg))
   {
      return(-5);
   }
   
   for (i=0;i<m_OThreadCnt;++i)
   {
      if (!m_OThreads[i].ToStartOutProcess(emsg))
         return(-6);
   }
   
   m_Status = FS_OPEN;  // ����Open״̬
   return(0);  // Start OK!
}


void CKSFTS::RegisterWTHClOrdID(const char *sWTH, const char *sOrigClOrdID,const char *vsvarstr1)
{
   CPMUTEX pMutex(&m_WTHMutex);
   T_CLORDINFO clinfo;
   STRNCPY(clinfo.sOrigClOrdID,sOrigClOrdID);
   STRNCPY(clinfo.sClOrdID,sOrigClOrdID);
   STRNCPY(clinfo.sVsvarstr1,vsvarstr1);
   m_WTHMap.insert(make_pair(string(sWTH),clinfo));
}

int CKSFTS::GetClOrdID(const char *sWTH, char *sOrigClOrdID, char *sClOrdID)
{
   CPMUTEX pMutex(&m_WTHMutex);
   M_CLORDID::iterator it;
   it = m_WTHMap.find(string(sWTH));
   if (it!=m_WTHMap.end())
   {
      strcpy(sOrigClOrdID,it->second.sOrigClOrdID);
      strcpy(sClOrdID,it->second.sClOrdID);
//       if (sClOrdID[0]=='\0')
//          strcpy(sClOrdID,sOrigClOrdID);
//       for (i=0;;++i)
//       {
//          sOrigClOrdID[i]=it->second[i];
//          if (sOrigClOrdID[i]=='\0'||sOrigClOrdID[i]=='|')
//             break;
//       }
//       if (sOrigClOrdID[i]=='\0')
//       {
//          strcpy(sClOrdID,sOrigClOrdID);
//       }
//       else
//       {
//          int j;
//          sOrigClOrdID[i++]='\0';
//          for (j=0;;++i,++j)
//          {
//             sClOrdID[j]=it->second[i];
//             if (sClOrdID[j]=='\0')
//                break;
//          }
//       }
      strcpy(m_LastClOrdID,sOrigClOrdID);
//      strcpy(m_LastIContractNo,sWTH);
      m_LastDoneTime=time(NULL);
      return(1);
   }
   return(0);
}

int CKSFTS::GetWTH(const char *sOrigClOrdID, char *sWTHs[], char *vsvarstrs[])
{
   CPMUTEX pMutex(&m_WTHMutex);
   M_CLORDID::iterator it;
   int l=strlen(sOrigClOrdID);
   int n=0;
   for (it=m_WTHMap.begin();it!=m_WTHMap.end();++it)
   {
      if (strcmp(sOrigClOrdID,it->second.sOrigClOrdID)==0)
      {
         strcpy(sWTHs[n],it->first.c_str());
         strcpy(vsvarstrs[n],it->second.sVsvarstr1);
         if (++n>=2)
            break;
      }
//       const char *ps = it->second.c_str();
//       if (memcmp(ps,sOrigClOrdID,l)==0
//          && (ps[l]=='\0'||ps[l]=='|'))
//       {
//          if (n==0)
//             strcpy(sWTH1,it->first.c_str());
//          else
//             strcpy(sWTH2,it->first.c_str());
//          ++n;
//          if (n>=2)
//             break;
//       }
   }
   return(n);
}



bool CKSFTS::PreOpen(char *emsg)
{
   // 1. �ȼ��CTS�������Ƿ��������
   if (!CheckKSFTSSvr(emsg))
      return(false);
   m_OutCnt = 0;
   m_WTHMap.clear();
   memset(m_LastClOrdID,0,sizeof(m_LastClOrdID));
   memset(m_LastIContractNo,0,sizeof(m_LastIContractNo));
   // 2. �Ȼָ�Out��Ϣ����KSCTS֧�ֵ�ί�кͳ�����Ϣ:
   if (!m_OThreads[0].Restore(m_PartnerID,emsg))
      return(false);
   
   if (!m_CJThread.Restore(m_PartnerID,emsg))
      return(false);
   
   return(true);

}

bool CKSFTS::CheckKSFTSSvr(char *emsg)
{
   BCResetHandle(m_bch);
   BCSetRequestType(m_bch,854102);  // ��Ϊ���Թ��ܵ���һ��, FTS���ݿ⵱ǰʱ��  stime3 
   BCSetStringFieldByName(m_bch,0,"scust_no",GetOperator());
   if (m_DRouters.TryCallSvr(m_bch,m_SvrDestNo,m_SvrFuncNo,emsg)<0)
      return(false);
   return(true);
}

int CKSFTS::SendToFIXSvr(const char *fixmsg)
{
   if (m_Status==FS_OPEN)  // �Ѿ�������������״̬
      return(UDLHaveMessageIn(m_PartnerID,fixmsg));
   else
      return(UG_RestoreFIXInMsg(m_PartnerID,fixmsg));
}

char * CKSFTS::GetMarketCode(T_UGDATA *pUGData, char *sMarketCode)
{
   M_MARKET::iterator it;
   it = m_Market.find(string(pUGData->sSecurityExchange));
   if (it!=m_Market.end())
   {
      strcpy(sMarketCode,it->second.c_str());
      return(sMarketCode);
   }
   return(NULL);
}

bool CKSFTS::IsRunning()
{
   return(m_bRunning);
}

int CKSFTS::GetOutMsg(char *fixmsg)
{
   int rtn;
   rtn = UG_GetOutMsg(m_PartnerID,100,fixmsg);
   if (rtn>0)
   {
      m_LastOutTime = time(NULL);
      ++m_OutCnt;
   }
   return(rtn);
}

bool CKSFTS::BindCJRecv(BSHANDLE bsh)
{
   return(m_DRouters.BindBSCJRecv(bsh));
}

int CKSFTS::GetStatus(char *statusmsg, unsigned int smsize)
{
   char emsg[256];
   if (m_Status>FS_CLOSE)
   {
      if (CheckKSFTSSvr(emsg))
      {
         sprintf(statusmsg,"%s:%d:%d:Last-ClOrdID=%s,Time=%ld; Out=%d,Time=%ld",
            m_PartnerID,FS_OPEN,
            UG_GetOutMsgSize(m_PartnerID),
            m_LastClOrdID,m_LastDoneTime,m_OutCnt,m_LastOutTime);
      }
      else
      {
         sprintf(statusmsg,"%s:%d:%d:%s",
            m_PartnerID,FS_CONNECTING,
            UG_GetOutMsgSize(m_PartnerID),
            emsg);
      }
   }
   else
   {
      sprintf(statusmsg,"%s:%d:%d:Last-ClOrdID=%s,Time=%ld; Out=%d,Time=%ld",
         m_PartnerID,m_Status,
         UG_GetOutMsgSize(m_PartnerID),
         m_LastClOrdID,m_LastDoneTime,m_OutCnt,m_LastOutTime);
   }
   return(0);  // ����ģʽ�£��������ݿ����Ӳ��л����ô��󣬾͵�������Ҫ����
}

void CKSFTS::Exit()
{
   // �ƺ�û��ɶ������:(
}

void CKSFTS::Close()
{
   int i;
   m_Status = FS_CLOSE;
   m_bRunning = false;
   
   for (i=0;i<m_OThreadCnt;++i)
   {
      m_OThreads[i].ToStopOutProcess();
   }
   m_CJThread.ToStopCJProcess();
   m_DRouters.ToStopCJRecv();
}

int CKSFTS::EndOfDay(const char *sLocalID, const char *sPartnerID, char *emsg)
{
   SQLDebugLog(500,"EndOfDay(%s): LastClOrdID=%s @ %ld",sPartnerID,m_LastClOrdID,m_LastDoneTime);
   m_LastDoneTime = time(NULL);
   m_LastOutTime = time(NULL);
   m_OutCnt = 0;
   memset(m_LastClOrdID,0,sizeof(m_LastClOrdID));
   m_WTHMap.clear();
   return(0);
}

int CKSFTS::UpdateClOrdID(const char *sWTH, const char *sClOrdID)
{
   CPMUTEX pMutex(&m_WTHMutex);
   M_CLORDID::iterator it;
   it = m_WTHMap.find(string(sWTH));
   if (it!=m_WTHMap.end())
   {
      STRNCPY(it->second.sClOrdID,sClOrdID);
      return(1);
   }
//   m_WTHMap.insert(make_pair(string(sWTH),string(sOrig_ClOrdID)));
   return(0);
}

int CKSFTS::RestoreCJ(char *emsg)
{
   int rtn;
   int i,n;
   T_UGDATA ugdata;
   int lv;
   char fvalue[1024];  // ��Ϊִ�б�����Ϣ�������㹻��
   char *pcustno,*pseat;
   pcustno = fvalue;
   pseat = fvalue+100;
   // ������m_bch�����������ָ��ɽ���
   BCResetHandle(m_bch);
   // 854042	��ѯ���ճɽ�	
   BCSetRequestType(m_bch,854042); 
   // in	����Ա	scust_no
   BCSetStringFieldByName(m_bch,0,"scust_no",GetOperator());
   // �ϲ���־	sstatus1 -- ��Ҫ��Ҫ��дΪ0
   BCSetStringFieldByName(m_bch,0,"sstatus1","0");
   // ���гɽ������	smain_flag ������0
   BCSetStringFieldByName(m_bch,0,"smain_flag","0");
   // �Ƿ�����ϼƱ��	sstatus3 ������дΪ1
   BCSetStringFieldByName(m_bch,0,"sstatus3","1");

   rtn = m_DRouters.TryCallSvr(m_bch,m_SvrDestNo,m_SvrFuncNo,emsg);
   if (rtn<0)
   {
      SQLDebugLog(54042,"Fail to RestoreCJ(854042) %d:%s",rtn,emsg);
      return(-1);
   }
   BCGetRetCode(m_bch,&rtn);
   if (rtn!=0)
   {
      BCGetStringFieldByName(m_bch,0,"vsmess",emsg,256);
      SQLDebugLog(4042,"RestoreCJ(854042) retCode=%d:%s",rtn,emsg);
      return(0); // �͵���û�гɽ���¼��, ���� _,_@_
   }
   n = 0;
   memset(&ugdata,0,sizeof(ugdata));
   strcpy(ugdata.sOrdStatus,"1");
   strcpy(ugdata.sExecType,"F");
   strcpy(ugdata.sMsgType,"8");
   do 
   {
      BCGetRecordCount(m_bch,&rtn);
      for (i=0;i<rtn;++i)
      {
         // ȡ����ĳɽ����ݣ�������Ӧ�Ĵ���:

         // ί�к�	lserial0
         BCGetIntFieldByName(m_bch,i,"lserial0",&lv);
         
         // �ͻ���	sholder_ac_no
         BCGetStringFieldByName(m_bch,i,"sholder_ac_no",pcustno,100);
         mytrim(pcustno);
         // ϯλ��	sserial2
         BCGetStringFieldByName(m_bch,i,"sserial2",pseat,100);
         mytrim(pseat);

         GetWTH(lv,pcustno,pseat,emsg);
         if (GetClOrdID(emsg,ugdata.sOrigClOrdID,ugdata.sClOrdID)>0)
         {
            // �����Ǳ�UGFTS�ĵ���:
            STRNCPY(ugdata.sClOrdID,ugdata.sOrigClOrdID);  // ���ڳɽ�ִ�е�

            // �������ɽ���	sserial0
            BCGetStringFieldByName(m_bch,i,"sserial0",fvalue,sizeof(fvalue));
            mytrim(fvalue);
            lv = strlen(fvalue);
            fvalue[lv++]='-';
            strcpy(fvalue+lv,emsg);  // <�������ɽ���>-<ί�к�|�ͻ���|ϯλ��>
            STRNCPY(ugdata.sExecID,fvalue); 

            // �ɽ���	lvol1
            BCGetIntFieldByName(m_bch,i,"lvol1",&lv);
            ugdata.dLastQty = lv;
            // �ɽ���	damt2          
            BCGetDoubleFieldByName(m_bch,i,"damt2",&(ugdata.dLastPx));
   
            // ���Խ���ʳɽ��ύ��FS��:
            UG_ExecutionFIXMsg(&ugdata,fvalue,sizeof(fvalue));
            SendToFIXSvr(fvalue);

            ++n;
         }
      }
      if (!BCHaveNextPack(m_bch))
         break;
      if (m_DRouters.CallNext(m_bch,emsg)<0)
      {
         SQLDebugLog(40421,"CallNext error @ row=%d:%s",n,emsg);
         break;
      }
   } while (1);
   return(n);
}

char * CKSFTS::GetOperator()
{
   return(m_Operator);
}

void CKSFTS::GetWTH(int iwth, const char *custno, const char *seatno, char *sWTH)
{
   sprintf(sWTH,"%d|%s|%s",iwth,custno,seatno);
}

int CKSFTS::GetIWTH(const char *sWTH)
{
   return(atoi(sWTH));
}



char * CKSFTS::GetCustNoFromWTH(const char *sWTH, char *buf, unsigned int bufsize)
{
   if (GetSubString(sWTH,'|',1,buf,bufsize,NULL)<=0)
   {
      buf[0]='\0';
   }
   return(buf);
}

char * CKSFTS::GetSeatNoFromWTH(const char *sWTH, char *buf, unsigned int bufsize)
{
   if (GetSubString(sWTH,'|',2,buf,bufsize,NULL)<=0)
   {
      buf[0]='\0';
   }
   return(buf);
}

void CKSFTS::HaveAnOutMsg()
{
   m_LastOutTime = time(NULL);
   ++m_OutCnt;
}

int CKSFTS::TryCallSvr(BCHANDLE bch, char *errMsg)
{
   return(m_DRouters.TryCallSvr(bch,m_SvrDestNo,m_SvrFuncNo,errMsg));
}

const char * CKSFTS::GetExchange(const char *sMarketCode)
{
   M_MARKET::iterator it;
   for (it=m_Market.begin();it!=m_Market.end();++it)
   {
      if (it->second.compare(sMarketCode)==0)
         return(it->first.c_str());
   }
   return("");  // ʡ���ж��Ƿ�ΪNULL��
}
