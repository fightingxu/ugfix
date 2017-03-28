// KSCTS.cpp: implementation of the CKSCTS class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "xpub.h"
#include "UDLInterface.h"
#include "fixbase.h"
#include "ugate.h"
#include "KSCTS.h"
#include "nbccclt.h"
#include "nbccsvr.h"
#include "UGDBFuncs.h"


CKSCTS g_KSCTS;
// ������: UDLInitialize
// ���  : ������ 2011-8-17 14:42:01
// ����  : ��ʼ��UDLģ�飬������Ҫ���������������Ϣ
//       �ڲ�������������������Ϣ
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLInitialize()
{
   BCCSvrInit("fwd",600);
   UG_SetOutMode(1); // ���õ���UG_GetOutMsg����
   return(g_KSCTS.Initialize());
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
   return(g_KSCTS.GetStatus(statusmsg,smsize));
}

// ������: UDLExit
// ���  : ������ 2011-8-18 21:03:38
// ����  : UGateҪ��UDL�˳�
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLExit()
{
   g_KSCTS.Exit();
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
   rtn = g_KSCTS.Open(sLocalID,sPartnerID,emsg);
   if (rtn<0)
      g_KSCTS.Close();
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
   g_KSCTS.Close();
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
   return(g_KSCTS.EndOfDay(sLocalID,sPartnerID,emsg));
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

//////////////////////////////////////////////////////////////////////////
void HaveDBRealDone(T_REAL_DONE *pRealDone)
{
   g_KSCTS.HaveARealDone(pRealDone);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
ST_SQLDB g_SQLDB;


CKSCTS::CKSCTS()
{
   memset(m_PartnerID,0,sizeof(m_PartnerID));
   memset(m_LocalID,0,sizeof(m_LocalID));
   m_bRunning = false;
   m_pXComp = NULL;
   m_LastDoneID = -1;
   m_LastOutTime = m_LastDoneTime = time(NULL);  // ��һ����û���õ�
   m_DoneCnt = 0;
   m_OutCnt = 0;
}

CKSCTS::~CKSCTS()
{

}


#define IMARKETFILE "imarket.txt"
int CKSCTS::Initialize()
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

   UG_INIReadTString("KSCTS","XPACK","cpack.dat",m_XPackFile,sizeof(m_XPackFile));

   // �ȶ����ݿ������ӳ�ʼ�������Ǳ��������ġ�
   UG_INIReadTString("KSCTS", "DBNAME", "ksdbs", g_SQLDB.szServer, sizeof(g_SQLDB.szServer));
   UG_INIReadTString("KSCTS", "DBSVR", "127.0.0.1", g_SQLDB.szDatabase, sizeof(g_SQLDB.szDatabase));
   UG_INIReadTString("KSCTS", "LOGINUSER", "", g_SQLDB.szLogin, sizeof(g_SQLDB.szLogin));
   UG_INIReadTString("KSCTS", "PASSWORD", "", g_SQLDB.szPassword, sizeof(g_SQLDB.szPassword));

   UG_INIReadTString("KSCTS","KSCTSSVR","0:5800",tmp,sizeof(tmp));
   pc = strstr(tmp,":");
   if (pc==NULL)
   {
      SQLDebugLog(10000,"Invalid [KSCTS] KSCTSSVR=%s defined",tmp);
      return(-1);
   }
   *pc='\0'; ++pc;
   m_SvrDestNo = atoi(tmp);
   m_SvrFuncNo = atoi(pc);

   m_ReDoneIDCnt = UG_INIReadInt("KSCTS","CJXHRY",100);

   m_CJSJRY = UG_INIReadInt("KSCTS","CJSJRY",500);

   SQLInitialize(&g_SQLDB);
   if (SQLConnectToServer()!=0)
      return(-100); // ����ѽ��

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

   // װ�ؽ�����������ڲ��г�����Ķ��ձ�
   rtn = UG_LoadMarkets(IMARKETFILE);
   if (rtn<=0)
   {
      SQLDebugLog(10002,"Fail to load IMARKET(%d):%s",rtn,IMARKETFILE);
      return(rtn-200);
   }

   // ��ʼ���ɽ��ر��߳�
   rtn = m_CJThread.Initialize(tmp);
   if (rtn<0)
   {
      SQLDebugLog(10003,"Fail to Init CJTHREAD(%d):%s",rtn,tmp);
      return(rtn-300);
   }


   // ��ȡ��������:
   m_OThreadCnt = UG_INIReadInt("KSCTS","OUTTHREADS",1);
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

   m_IThreadCnt = UG_INIReadInt("KSCTS","INTHREADS",1);
   if (m_IThreadCnt>MAXINTHREADS)
      m_IThreadCnt = MAXINTHREADS;
   for (i=0;i<m_IThreadCnt;++i)
      m_IThreads[i].m_ID = i;

   UG_INIReadTString("KSCTS","WTYYB","088",m_WTYYB,sizeof(m_WTYYB));
   UG_INIReadTString("KSCTS","WTFSx","FIX",m_WTFSx,sizeof(m_WTFSx));
   UG_INIReadTString("KSCTS","WTFSi","f",m_WTFSi,sizeof(m_WTFSi));

   LoadHWGSDM();

   return(0);
}

void CKSCTS::Exit()
{
   SQLDisconnect1();
}

int CKSCTS::Open(const char *sLocalID, const char *sPartnerID, char *emsg)
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

   // 2012/12/25 22:30:30 Ϊ�������ݿ�������ʱ���ָܻ����ӣ��ر������������
   SQLDisconnect1();
   if (SQLConnectToServer()!=0)
   {
      sprintf(emsg,"Fail to Connect Server(%s:%s)!",g_SQLDB.szDatabase,g_SQLDB.szServer);
      return(-100); // ����ѽ��
   }
   //////////////////////////////////////////////////////////////////////////

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

const char * CKSCTS::GetXPackFile()
{
   return(m_XPackFile);
}

bool CKSCTS::IsRunning()
{
   return(m_bRunning);
}

void CKSCTS::Close()
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

int CKSCTS::LoadHWGSDM()
{
   char tmp[512];
   char *pv;
   int i;
   FILE *fp;
   m_XCompCnt = 0;
   if (m_pXComp!=NULL)
   {
      delete []m_pXComp;
      m_pXComp = NULL;
   }
   fp = fopen("hwgsdm.txt","rt");
   if (fp==NULL)
      return(0);
   i = 0;
   while (fgets(tmp,sizeof(tmp),fp))
      ++i;
   if (i<=0)
   {
      fclose(fp);
      return(0);
   }
   m_pXComp = new T_HWGSDM[i];
   fseek(fp,0,SEEK_SET);
   i = 0;
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
         STRNCPY(m_pXComp[i].onbehalf,tmp);
         STRNCPY(m_pXComp[i].hwgsdm,pv);
         ++i;
      }
   }
   m_XCompCnt = i;
   fclose(fp);
   return(i);
}



char * CKSCTS::GetHWGSDM(const char *onbehalf)
{
   int i;
   for (i=0;i<m_XCompCnt;++i)
   {
      if (strcmp(m_pXComp[i].onbehalf,onbehalf)==0)
         return(m_pXComp[i].hwgsdm);
   }
   return(NULL);
}

int CKSCTS::InsertFIXEntrust(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_DBMutex);
   return(DBInsertFIXEntrust(pUGData));
}


// ������: CKSCTS::GetDBEntrustStatus
// ���  : ������ 2011-9-18 10:39:55
// ����  : ��KSCTS��ENTRUST���в�ָ��ί�е����ݣ�������Ϊ1��ʱ��:
//          sSellSide = ENTRUST.REPORT_SEAT;
//          sOrderID = ENTRUST.RPT_CONTRACT;
//          sOrdStatus = ENTRUST.ENTRUST_STATUS;
//          sExecInst = ENTRUST.EXCHANGE_ERR_CODE
// ����  : int -1: ʧ�ܣ����ݿ��쳣(Ҳ�п����ж���); 
//             0: û���ҵ�ָ��ί�м�¼��
//             1: �ҵ�������pUGData�е��������ݽ����޸�
// ����  : T_UGDATA *pUGData[IN/OUT]: ��pUGData->sClOrdID��Ϊί�к�ͬ����ָ��ί�м�¼��
//                   ������1��ʱ�򣬸������������ֶΣ�������KSCTS�ı�ʾ��ʽ
int CKSCTS::GetDBEntrustStatus(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_DBMutex);
   return(DBGetEntrustStatus(m_WTYYB,m_WTFSi,pUGData));
}


// ������: CKSCTS::CallSvr
// ���  : ������ 2011-9-18 11:26:31
// ����  : ��KSCTS���������ù���
// ����  : int <0: ����ʧ��, �μ�errMsg�������Ϣ��-103:���ڽ���Ӧ��ʱ
//             >=0: ���óɹ������bch�еķ�����Ϣ
// ����  : BCHANDLE bch [IN/OUT]: ���úͷ����õ����ݻ�����
// ����  : char *errMsg [OUT]: �ڷ���ʧ�ܵ�ʱ����д����Ĵ�����Ϣ
int CKSCTS::CallSvr(BCHANDLE bch, char *errMsg)
{
   return(m_DRouters.CallSvr(bch,m_SvrDestNo,m_SvrFuncNo,errMsg));
}

int CKSCTS::FetchCJHBRecords()
{
   CPMUTEX pMutex(&m_DBMutex);
   int dsec = time(NULL)-m_LastDoneTime+2;  // �ϴκͱ��ε�ʱ����(��)+2��
   m_LastDoneTime = time(NULL);
   return(DBFetchRDRecords(m_WTYYB,m_WTFSi,&m_LastDoneID,m_ReDoneIDCnt,dsec));
}


void CKSCTS::HaveARealDone(T_REAL_DONE *pRealDone)
{
   T_UGDATA ugdata;
   char fixmsg[MAXFIXMSGLEN];
   int fmlen;
   if (bDoneProcessed(pRealDone->lDONE_ID))
      return;  // �ȹ����Ѿ�������ĳɽ��򳷵�

   mytrim(pRealDone->sCONTRACT_NO);
   mytrim(pRealDone->sSEC_CODE);

   memset(&ugdata,0,sizeof(ugdata));
   STRNCPY(ugdata.sSenderCompID,m_PartnerID); 
   STRNCPY(ugdata.sOrderID,pRealDone->sCONTRACT_NO);
   strcpy(ugdata.sMsgType,"8");
   STRNCPY(ugdata.sSymbol,pRealDone->sSEC_CODE);
   STRNCPY(ugdata.sOrigClOrdID,pRealDone->sCONTRACT_NO);
   STRNCPY(ugdata.sOrderID,pRealDone->sCONTRACT_NO);  // ��Щ����Լ�����˵ģ��ο�OUTThread�е���Ӧ����

   //PUTLINE(ugdata.sOrigClOrdID);

   switch (pRealDone->sBS[1])
   {
   case '1':
      strcpy(ugdata.sSide,"1"); // buy
      break;
   case '2':
      strcpy(ugdata.sSide,"2");  // sell
      break;
   case 'M':    // D = Subscribe (e.g. ETF)[�깺]
      strcpy(ugdata.sSide,"D");
      break;
   case 'N':    // E = Redeem (e.g. ETF)[���]
      strcpy(ugdata.sSide,"E");
      break;
   default:
      ugdata.sSide[0]=pRealDone->sBS[1];
      break;
   }

   switch (pRealDone->sBS[0])
   {
   case '0': // ���ڳɽ�
      //PUTLINE("Filled");
      strcpy(ugdata.sExecType,"F"); // Trade (filled)
      STRNCPY(ugdata.sClOrdID,pRealDone->sCONTRACT_NO);
      sprintf(fixmsg,"%.0lf-%s",
         pRealDone->dDONE_NO,pRealDone->sCONTRACT_NO); // ������������EXECID��
      STRNCPY(ugdata.sExecID,fixmsg);
      ugdata.dLastPx = pRealDone->dDONE_PRICE;
      ugdata.dLastQty = pRealDone->lDONE_VOL;
      // �������ݣ�FS�в���ô������
      break;
   case '1': // ���ڳ���
      //PUTLINE("Cancelled");
      strcpy(ugdata.sExecType,"4"); // Canceled
      GetCancelClOrdID(&ugdata);
      sprintf(ugdata.sExecID,"CXL-%s",pRealDone->sCONTRACT_NO);
      // �����ɹ�����:
      if (pRealDone->lDONE_VOL<0)
         pRealDone->lDONE_VOL = -pRealDone->lDONE_VOL;
      ugdata.dOrderQty = pRealDone->lDONE_VOL;
      ugdata.dCumQty = 0;
      // ��ugdata.dOrderQty-ugdata.dCumQty�Ĳ�ֵ������ʾ�����ɹ�������
      //////////////////////////////////////////////////////////////////////////
      break;
   default:
      SQLDebugLog(20001,"Unknown BusinessCode:%s of DONEID(%ld)",
         pRealDone->sBS,pRealDone->lDONE_ID);
      return;
   }
   fmlen = UG_ExecutionFIXMsg(&ugdata,fixmsg,sizeof(fixmsg));
   //PUTLINE(fixmsg);
   SendToFIXSvr(fixmsg);
   AddDoneProcessed(pRealDone->lDONE_ID);
   if (strcmp(ugdata.sExecType,"4")==0)
      ClOrderCxlDone(&ugdata); // ��ʾ�������Ѿ�closed
   ++m_DoneCnt;
}

bool CKSCTS::BindCJRecv(BSHANDLE bsh)
{
   return(m_DRouters.BindBSCJRecv(bsh));
}

// ���ݵ�ǰ�����б��еĳ���������ݿ��е�ENTRUST
int CKSCTS::CheckCxlReject()
{
   CPMUTEX pMutex(&m_CCMutex);
   M_CXLCLORDID::iterator it,nt;
   int n=0;
   for (it=m_Cancels.begin();it!=m_Cancels.end();)
   {
      nt = it++;
//      PUTLINE("In CheckCxlReject");
      if (CheckACancelReject(nt->first.c_str(),nt->second.c_str()))
      {
         m_Cancels.erase(nt); // 
         ++n;
      }
   }
   m_DoneCnt += n;
   return(n);
}

// ��ִ����ż�鱾�ɽ��ͳ����Ƿ��Ѿ��������
bool CKSCTS::bDoneProcessed(long done_id)
{
   if (done_id>=0)
   {
      return (m_DoneIDSet.find(done_id)!=m_DoneIDSet.end());
   }
   return(false); // ���򣬾Ͱ�����Ҫ���������� 2012-6-6 22:06:57
}

// ����Ѿ������˵ĳɽ��ͳ���ִ�����(����CJ�̼߳�ӵ���)
void CKSCTS::AddDoneProcessed(long done_id)
{
   if (done_id>=0)
   {
      m_DoneIDSet.insert(done_id);
      if (m_DoneIDSet.size()>m_ReDoneIDCnt)
         m_DoneIDSet.erase(m_DoneIDSet.begin());  // ����һ��ɾ����
   }
}

// ��pUGData->sOrigClOrdID (��pRealDone->sCONTRACT_NO)����鳷������ó��������е�pUGData->sClOrdID
void CKSCTS::GetCancelClOrdID(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_CCMutex);
   M_CXLCLORDID::iterator it;
   it = m_Cancels.find(string(pUGData->sOrigClOrdID));
   if (it!=m_Cancels.end())
   {
      STRNCPY(pUGData->sClOrdID,it->second.c_str());
   }
   else
   {
      STRNCPY(pUGData->sClOrdID,pUGData->sOrigClOrdID);
   }
}

// �ڳ����ڴ���м���һ�ʳ����Ķ�����Ŷԣ�
// ����sOrigClOrdIDΪԭ������ClOrdID��Ҳ����ί�еĺ�ͬ��;
// ��sClOrdIDΪ��sOrigClOrdID���ί�е��ĳ��������ClOrdID��
void CKSCTS::RegisterCancelOrder(const char *sOrigClOrdID, const char *sClOrdID)
{
   CPMUTEX pMutex(&m_CCMutex);
   m_Cancels.insert(make_pair(string(sOrigClOrdID),string(sClOrdID)));
}

// ����pUGData->sOrigClOrdID�ĳ����Ѿ���ɣ��򱻾ܾ��ˣ�
// ʵ�ʾ��ǽ������ڴ���еļ�¼ɾ���ˣ��ó��ռ�����
void CKSCTS::ClOrderCxlDone(T_UGDATA *pUGData)
{
   CPMUTEX pMutex(&m_CCMutex);
   m_Cancels.erase(string(pUGData->sOrigClOrdID));
}



// ������: CKSCTS::CheckACancelReject
// ���  : ������ 2011-9-21 0:08:38
// ����  : ͨ�����KS.ENTRUST�еĳ�����¼���Է����Ƿ񱻾ܾ���
// ����  : bool : true-���������ܾ��ˣ�false-��������û�б��ܾ�
// ����  : const char *origclordid [IN]: ԭʼ������OrigClOrdID, ͬʱҲ��ԭʼ��ί�к�ͬ��: CONTRACT_NO
// ����  : const char *clordid [IN]: ��Ӧ�ĳ�����ClOrdID
bool CKSCTS::CheckACancelReject(const char *origclordid, const char *clordid)
{
   T_UGDATA ugdata;
   char fixmsg[MAXFIXMSGLEN];
   int rtn;

   memset(&ugdata,0,sizeof(ugdata));
   STRNCPY(ugdata.sOrigClOrdID,origclordid);
   STRNCPY(ugdata.sClOrdID,clordid);
   strcpy(ugdata.sMsgType,"F");  // ֻ�ǲ鳷�����Ǳʼ�¼
   if ((rtn=GetDBEntrustStatus(&ugdata))>0)
   {
      if (ugdata.sOrdStatus[0]!='9')
      {
         // ���Ǳ��������ܾ��ķϵ�����ô����FetchCJHBRecords���ﴦ����
         return(false);
      }
      // OK:  '9' - �ϵ�
      ugdata.lCxlRejReason = 2; // 2 = Broker / Exchange Option
      sprintf(ugdata.vsmess,"ErrNo=%s:Rejected by OMS/Exchange",ugdata.sExecInst);
   }
   else
   {
      // û�м�¼����ô�����أ�
      // �ȱ���һ�°�
      SQLDebugLog(20002,"PE:Not found KS.ENTRUST(%s) for Cancel:%d!",origclordid,rtn);
      ugdata.lCxlRejReason = 1; // 1 = Unknown order
      strcpy(ugdata.vsmess,"PE:Not found order");
   }

   STRNCPY(ugdata.sSenderCompID,m_PartnerID); // ��������Ͳ��ô�m_PartnerID��
   strcpy(ugdata.sCxlRejResponseTo,"1");
   rtn = UG_CancelRejectFIXMsg(&ugdata,fixmsg,sizeof(fixmsg));

   SendToFIXSvr(fixmsg);
   return(true);
}

bool CKSCTS::PreOpen(char *emsg)
{
   // 1. �ȼ��CTS�������Ƿ��������
   if (!CheckKSCTSSvr(emsg))
      return(false);
   // 2. �Ȼָ�Out��Ϣ����KSCTS֧�ֵ�ί�кͳ�����Ϣ:
   if (!m_OThreads[0].Restore(m_PartnerID,emsg))
      return(false);

   if (!m_CJThread.Restore(m_PartnerID,emsg))
      return(false);

   return(true);
}

// ����  : char *statusmsg [OUT]: �����¸�ʽ���ظ���Partner��״̬��
//             <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerID2>:<status>:<load>:<errmsg>
//             status: 0 - û��������1 - �Ѿ���������
//             load: ����ֵ������û�б������OUT��Ϣ����
// ����  : unsigned int smsize [IN]: statusmsg�Ļ����ֽ���(��Ž�4000���ֽ�) 
int CKSCTS::GetStatus(char *statusmsg, unsigned int smsize)
{
   char emsg[256];
   if (m_Status>FS_CLOSE)
   {
      if (CheckKSCTSSvr(emsg))
      {
         sprintf(statusmsg,"%s:%d:%d:Last-DoneID=%ld,Time=%ld; Out=%d,Time=%ld",
            m_PartnerID,FS_OPEN,
            UG_GetOutMsgSize(m_PartnerID),
            m_LastDoneID,m_LastDoneTime,m_OutCnt,m_LastOutTime);
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
      sprintf(statusmsg,"%s:%d:%d:Last-DoneID=%ld,Time=%ld; Out=%d,Time=%ld",
         m_PartnerID,m_Status,
         UG_GetOutMsgSize(m_PartnerID),
         m_LastDoneID,m_LastDoneTime,m_OutCnt,m_LastOutTime);
   }
   return(0);  // ����ģʽ�£��������ݿ����Ӳ��л����ô��󣬾͵�������Ҫ����
}

// ����  : �Ա�������Reset�������֮ǰ����������ݣ�������ر�״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int CKSCTS::EndOfDay(const char *sLocalID, const char *sPartnerID, char *emsg)
{
   CPMUTEX pMutex(&m_DBMutex);
   m_LastDoneTime = time(NULL);
   DBGetLastMaxDoneID(&m_LastDoneID);
   SQLDebugLog(500,"EndOfDay(%s): LastDoneID=%ld",sPartnerID,m_LastDoneID);
   m_Cancels.clear();
   return(0);
}

int CKSCTS::GetOutMsg(char *fixmsg)
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

// ���KSCTSӦ�÷�������״̬���Ƿ����������ṩ����
bool CKSCTS::CheckKSCTSSvr(char *emsg)
{
   BCResetHandle(m_bch);
   BCSetRequestType(m_bch,100319);  // ��Ϊ���Թ��ܵ���һ��
//    if (CallSvr(m_bch,emsg)<0)
   if (m_DRouters.TryCallSvr(m_bch,m_SvrDestNo,m_SvrFuncNo,emsg)<0)
      return(false);
   return(true);
}

int CKSCTS::SendToFIXSvr(const char *fixmsg)
{
   if (m_Status==FS_OPEN)  // �Ѿ�������������״̬
      return(UDLHaveMessageIn(m_PartnerID,fixmsg));
   else
      return(UG_RestoreFIXInMsg(m_PartnerID,fixmsg));
}

int CKSCTS::TryCallSvr(BCHANDLE bch, char *errMsg)
{
	return(m_DRouters.TryCallSvr(bch,m_SvrDestNo,m_SvrFuncNo,errMsg));
}

int CKSCTS::CallNext(BCHANDLE bch, char *errMsg)
{
	return(m_DRouters.CallNext(bch,errMsg));
}

/*
 *	fix		fix�ı�׼���Ҵ���
	local	��̨�Ļ��Ҵ���
	iflag	0 fixתlocal  1 localתfix
 */
void CKSCTS::GetCurrcncy(char *fix,char *local,int iflag)
{
	if(iflag == 0)
	{
		if(strcmp(fix,"CNY") == 0 || strcmp(fix,"") == 0)
			strcpy(local,"01");
		else if(strcmp(fix,"USD") == 0)
			strcpy(local,"02");
		else if(strcmp(fix,"HKD") == 0)
			strcpy(local,"03");
	}
	else if(iflag == 1)
	{
		if(strcmp(local,"01") == 0 || strcmp(local,"") == 0)
			strcpy(fix,"CNY");
		else if(strcmp(local,"02") == 0)
			strcpy(fix,"USD");
		else if(strcmp(local,"03") == 0)
			strcpy(fix,"HKD");
	}
}

// 2012-6-6 23:23:08 ���յ��������ܾ���ʱ����д�������CheckCxlReject�Ĺ���
bool CKSCTS::HaveACancelReject(const char *origclordid)
{
   CPMUTEX pMutex(&m_CCMutex);
   M_CXLCLORDID::iterator it;
   char clordid[40];
   it = m_Cancels.find((string)origclordid);
   if (it!=m_Cancels.end())
   {
      STRNCPY(clordid,it->second.c_str());
      if (CheckACancelReject(origclordid,clordid))
      {
         m_Cancels.erase(it);
         return(true);
      }
   }
   return(false);
}
