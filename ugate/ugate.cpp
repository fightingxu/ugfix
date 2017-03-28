/********************************************************************
	created:	2011/08/17
	created:	17:8:2011   10:39
	filename: 	C:\DD\PROJECTS\FIXIII\UGATE\ugate\ugate.cpp
	file path:	C:\DD\PROJECTS\FIXIII\UGATE\ugate
	file base:	ugate
	file ext:	cpp
	author:		CHENYH
	
	purpose:	������� C �ӿڶ��壬�Թ�UDL�ȵ���
*********************************************************************/
#include "stdafx.h"
#ifdef _MSC_VER
#include <process.h>
#else
#include <pthread.h>
#endif
#include "FIXData.h"
#include "fixbase.h"
#include "XPack.h"
#include "cpack.h"
#include "bdefine.h"
#include "bupub.h"
#include "mypub.h"
#include "logfile.h"
#include "UGateManage.h"
#include "MsgDataList.h"
#include "ugate.h"

CUGateManage g_UGate;
ST_BUNIT g_BUnit;
CSvrLink *g_pSvrLink;  // ��ҵ��������ĵ�����
CLogFile g_LogFile;   // ���Ƶ�SvrLink.cpp�У���Ϊϵͳ��Ҫ������
CXPack *g_pXPack;  //

//////////////////////////////////////////////////////////////////////////
typedef struct {
   char Exchange[8];  // ���������룬XSHG/XSHE etc.
   char Account[40];  // ���ױ��� / �ɶ����� ģʽƥ����ʽ
   char Symbol[40];   // ֤ȯ���� ģʽƥ����ʽ
   char IMarket[8];   // �����ڲ��г�����: 1,2,3,4 etc. 
} T_MARKET;  // ���ڸ���ί�����ݣ����IMarket��Exchange����Ϣ�Ļ�����ṹ

int g_nMarkets=-1;  // �г��б��У�����ĸ���
T_MARKET *g_Markets=NULL;

struct T_INMSGTYPEFUNC 
{
   char MsgType[8];
   int reqtype;
};

T_INMSGTYPEFUNC g_InMsgFuncs[]=
{
   {"D",411701},
   {"8",411705},
   {"9",411705},
   {"F",411702},
   {"G",411702},
   {"H",411704},
   {"",411799}
};


// ������: UG_LoadMarkets
// ���  : ������ 2011-9-15 23:13:06
// ����  : װ�ؽ����г����ڲ�����ƥ���ļ�
// ����  : int >0: �ɹ�װ��ƥ���������
//             <=0: װ��ʧ��  -1:�ļ����쳣; 0:û��׼ȷ�����嵥;
//             -2: �����ڴ�ʧ�ܣ�
// ����  : const char *imarketfile
int UG_LoadMarkets(const char *imarketfile)
{
   FILE *fp;
   char buf[512];
   T_MARKET *pMarket;

   if (g_Markets!=NULL)
   {
      delete []g_Markets;
      g_Markets = NULL;
   }
   g_nMarkets = 0;
   fp = fopen(imarketfile,"rt");
   if (fp==NULL)
   {
      return(-1); // ��ʾ�ļ����쳣
   }
   while (fgets(buf,sizeof(buf),fp))
   {
      ++g_nMarkets;
   }
   if (g_nMarkets<=0)
   {
      fclose(fp);
      return(0);
   }
   g_Markets = new T_MARKET[g_nMarkets];
   if (g_Markets==NULL)
   {
      fclose(fp);
      return(-2); // ��ʾ����ռ��쳣
   }
   fseek(fp,0,SEEK_SET); // ��ͷ��ʼ���¶�ȡ
   g_nMarkets = 0;
   pMarket = g_Markets;
   while (fgets(buf,sizeof(buf),fp))
   {      
      /* 
      //EXCHANGE|ACCOUNT|SYMBOL|IMARKET|NOTE  -- ��һ����Ϊ�����������������ݵĺ�����ӵģ����򽫲����ȡ�����Ķ�!!!!!
      XSHG|!C*|*|1|�Ϻ�A��
      XSHG|C*|*|3|�Ϻ�B��
      XSHE|*|!2*,!4*,!36*|2|����ͶƱ�������A��
      XSHE|*|2*|4|����ͶƱ�������B��
      XSHE|*|40*,43*|5|����A��ת��
      XSHE|*|42*|6|����B��ת��
      XSHE|0*,40*,480*|36*|2|����A��ͶƱ
      XSHE|!0*,!40*,!480*|36*|4|����B��ͶƱ
      */
      mytrim(buf);
      if (buf[0]=='/')
         continue;
      if (GetSubString(buf,'|',0,pMarket->Exchange,sizeof(pMarket->Exchange),NULL)<=0)
         continue;
      mytrim(pMarket->Exchange);
      if (GetSubString(buf,'|',1,pMarket->Account,sizeof(pMarket->Account),NULL)<=0)
         continue;
      mytrim(pMarket->Account);
      if (GetSubString(buf,'|',2,pMarket->Symbol,sizeof(pMarket->Symbol),NULL)<=0)
         continue;
      mytrim(pMarket->Symbol);
      if (GetSubString(buf,'|',3,pMarket->IMarket,sizeof(pMarket->IMarket),NULL)<=0)
         continue;
      mytrim(pMarket->IMarket);
      if (strlen(pMarket->IMarket)>0)
      {
         ++pMarket;
         ++g_nMarkets;
      }
   }
   fclose(fp);
   return(g_nMarkets);
}


// ������: UG_GetIMarket
// ���  : ������ 2011-9-15 23:18:45
// ����  : ��������ĸ����룬�ҳ��ڲ��г����룻����֮ǰ�ɹ�����UG_LoadMarkets
// ����  : const char *: NULL - û���ҵ�; ���򷵻ؽ����г��ڲ�����
// ����  : const char *exchcode[IN]: KSFIXƽ̨�ṩ�Ľ��������룬�� "XSHE"
// ����  : const char *account[IN]: �ɶ������Ͷ�����ʺţ�����Ϊ��(��һ��׼ȷ)
// ����  : const char *symbol[IN]: ֤ȯ������Լ���룬����Ϊ��(��һ��׼ȷ)
const char *UG_GetIMarket(const char *exchcode, const char *account, const char *symbol)
{
   int i;
   for (i=0;i<g_nMarkets;++i)
   {
      if (strcmp(g_Markets[i].Exchange,exchcode))
         continue;
      if (account!=NULL && account[0] 
         && CYHStringMatch(account,g_Markets[i].Account)==0)
         continue;
      if (symbol!=NULL && symbol[0]
         && CYHStringMatch(symbol,g_Markets[i].Symbol)==0)
         continue;
      return(g_Markets[i].IMarket);
   }
   return(NULL);
}


// ������: UG_GetExchange
// ���  : ������ 2011-9-15 23:23:38
// ����  : ��������ĸ����룬�ҳ����������룻����֮ǰ�ɹ�����UG_LoadMarkets
// ����  : const char *: NULL - û���ҵ�; ���򷵻�ƽ̨�Ľ���������
// ����  : const char *imarket[IN]: ����ϵͳ�ڲ����г����룬�� "1"
// ����  : const char *account[IN]: �ɶ������Ͷ�����ʺţ�����Ϊ��(��һ��׼ȷ)
// ����  : const char *symbol[IN]: ֤ȯ������Լ���룬����Ϊ��(��һ��׼ȷ)
const char *UG_GetExchange(const char *imarket, const char *account, const char *symbol)
{
   int i;
   for (i=0;i<g_nMarkets;++i)
   {
      if (strcmp(g_Markets[i].IMarket,imarket))
         continue;
      if (account!=NULL && account[0] 
         && CYHStringMatch(account,g_Markets[i].Account)==0)
         continue;
      if (symbol!=NULL && symbol[0]
         && CYHStringMatch(symbol,g_Markets[i].Symbol)==0)
         continue;
      return(g_Markets[i].Exchange);
   }
   return(NULL);
}



//////////////////////////////////////////////////////////////////////////
// !! ��������������ר����OUTMODE!=0�������£���UDL���õģ��ڲ�����
// ������: UG_GetOutMsg
// ���  : ������ 2011-9-16 22:30:51
// ����  : UDL��ȡ��Ҫ�����OUT��Ϣ
// ����  : int >0: ��ȡ�ɹ���������msgbuf�е���Ϣ���ȣ�
//             0: �ڵȴ�outwaitms*100 (ms)ʱ���ڣ�û����ҪOUT�������Ϣ��
//             -2: �Ƿ���partnerid����UGATEû�ж����������
// ����  : const char *partnerid [IN]: ���ַ���ID����OUT��Ϣ�е� TargetCompID
// ����  : int outwaitms [IN]: �ȴ���Ϣ��ʱ����ƣ�ʵ�ʵȴ����ʱ��Ϊ outwaitms*100 (ms)
// ����  : char *msgbuf [OUT]: ��ŵõ�����ҪOUT�������Ϣ�����泤�ȼ�Ϊϵͳʵ�ʴ�����������ΪMAXFIXMSGLEN
int UG_GetOutMsg(const char *partnerid, int outwaitms, char *msgbuf)
{
   return(g_UGate.GetOutMsg(partnerid,outwaitms,msgbuf));
}

int UG_GetOutMsgSize(const char *partnerid)
{
   return(g_UGate.GetOutMsgSize(partnerid));
}



// ������: UG_HaveOutMsg
// ���  : ������ 2011-9-16 22:30:54
// ����  : ��UDL��ʱ��OUT��Ϣ�����浽UGATE��ܹ����µ�OUT��Ϣ������
// ����  : int : 0/1 - ʵ�ʵ�plevel����ʵ�ʱ���ŵ�OUT��Ϣ�������ȼ���0��1��
//             -2: �Ƿ���partnerid����UGATEû�ж����������
// ����  : const char *parterid [IN]: ���ַ���ID����OUT��Ϣ�е� TargetCompID
// ����  : const char *msg [IN]: Ҫ�����fixmsg����'\0'����
// ����  : int plevel [IN]: ������������ȼ�: 0��1, 0��1��, ����UG_GetOutMsg��ʱ����ȡ0�����е���Ϣ��Ȼ��ȡ1�����е���Ϣ
int UG_HaveOutMsg(const char *parterid, const char *msg, int plevel)
{
   return(g_UGate.HaveOutMsg(parterid,msg,plevel));
}

//////////////////////////////////////////////////////////////////////////


// ������: StartThread
// ���  : ������ 2011-8-17 21:15:38
// ����  : ��ThreadRun������Ϊ�̵߳���ڣ�����һ���߳�
// ����  : int <0: ����ʧ�ܣ�����ɹ�
// ����  : THREADENTRY ThreadRun [IN]: �߳���ں���
// ����  : void *pArv [IN]: ������ʱ��Ĵ���Ĳ���
int StartThread(THREADENTRY ThreadRun,void *pArv)
{
#ifdef _MSC_VER
   if (_beginthread(ThreadRun,0,pArv)==-1)
      return(-1);
   else
      return(1);
#else
   pthread_attr_t attr;
   pthread_t hThread;
   pthread_attr_init (&attr);
   pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
   pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
   if((pthread_create(&hThread,&attr,ThreadRun, pArv))==0)
      return(1);
   else
      return(-1);
#endif
}

// ������: UG_INIReadTString
// ���  : ������ 2011-8-17 14:16:47
// ����  : ���ַ�����ʽ��ȡ�����ļ��е�ָ�������ȥ����ǰ����ַ�����
// ����  : char * : 
// ����  : const char *section [IN]: ���ö�
// ����  : const char *entry [IN]: ������
// ����  : const char *defvalue [IN]: ȱʡֵ
// ����  : char *buffer [OUT]: ��Ŷ�ȡ������ֵ
// ����  : int bufLen [IN]: buffer������ֽڳ���
char *UG_INIReadTString(const char *section, const char *entry, const char *defvalue,char *buffer,int bufLen)
{
   return(g_UGate.m_inifile.ReadTString(section,entry,defvalue,buffer,bufLen));
}


// ������: UG_INIReadInt
// ���  : ������ 2011-8-17 21:13:26
// ����  : �����η�ʽ��ȡ�����ļ��е�ָ����������
// ����  : int :���ض�ȡ������ֵ
// ����  : const char *section [IN]: ���ö�
// ����  : const char *entry [IN]: ������
// ����  : int defvalue [IN]: ȱʡֵ
int UG_INIReadInt(const char *section, const char *entry,int defvalue)
{
   return(g_UGate.m_inifile.ReadInt(section,entry,defvalue));
}



int WriteAppInfo(int bccBaseFuncNo,int bccID)
{
   // �ƺ�û��ɶ�������ģ���û����ҪΪ��BU�鴴��ʲô���ʼ��ʲô�ģ���������Լ������
   return(0);
}

int xProcess(TRUSERID *handle,char *rdata,int rdlen,int *iRetCode, char *szMsg)
{
   return(g_UGate.xProcess(handle,rdata,rdlen,iRetCode,szMsg));
}



// ������: UG_LoadIni
// ���  : ������ 2011-8-17 14:33:40
// ����  : �򿪲�װ��UGate���������ò���
// ����  : int >0: �ɹ���������򽫻��˳�
// ����  : const char *inifile [IN]: �����ļ�
int UG_LoadIni(const char *inifile)
{
   g_pSvrLink = BUPubInitialize(NULL, NULL, WriteAppInfo, &g_LogFile, xProcess);
   g_pXPack = (CXPack *)GetDefaultXPack();
   return(g_UGate.LoadIni(inifile));
}


void UG_ToExit()
{
   g_UGate.ToExit();
}


// ������: UG_BCCLinkOK
// ���  : ������ 2011-8-17 15:13:47
// ����  : UGate��BCC�����Ƿ�������������������˵��Ҫ��ǿ���˳�
// ����  : int >0: ��������
int UG_BCCLinkOK()
{
   if (g_pSvrLink->LinkOK())
      return(1);
   else
      return(-1);
}


// ������: UG_GetLocalID
// ���  : ������ 2011-8-20 15:56:58
// ����  : ȡ��UGate��LocalID
// ����  : const char *
const char *UG_GetLocalID()
{
   return(g_UGate.m_LocalID);
}


// Function name: UGGetChannelInfo
// Author       : CHENYH 2012/5/18 23:39:30
// Description  : ȡUG�ڲ��ĸ���Channel��״̬
// Return type  : int >=0: ��ȡ�ɹ���<0: ʧ�ܣ������iChannel��
// Argument : int iChannel [IN]:��0��ʼ��Channel���
// Argument : char *info256 [OUT]: ��"<PartnerID>:<״̬>:<����>" ��ʽ���ص���Ϣ
int UGGetChannelInfo(int iChannel, char *info256)
{
   info256[0]='\0';
   if (g_UGate.GetChannelInfo(iChannel,info256))
   {
      return(iChannel);
   }
   else
      return(-1);
}

void UGReloadKFXFile(int iChannel)
{
   g_UGate.ReloadKFXFile(iChannel);
}


// ������: UG_Init
// ���  : ������ 2011-8-17 14:49:22
// ����  : ��ʼ��UGate������ģ��
// ����  : int <0: ʧ�ܣ�����ɹ�
int UG_Init()
{
   int rtn;
   // ��ʼ����BCC���ӣ�
   do 
   {
      rtn = g_pSvrLink->ToLink(&g_BUnit);
      if (rtn==1)
      {
         DEBUG_RUNTIME_MSGOUT("��ҵ���������(BCC)�����ӳɹ�!\n");
         break;
      }
      else if (rtn==-100)
      {
         DEBUG_RUNTIME_MSGOUT("����ҵ���������(BCC)��δ��ʽ���������߼�������е�[SERVER]�����\n");
         mysleep(g_BUnit.iHBInterval);
      }
      else
      {
         // Ӧ�����ڹ��ϣ���Է�������BCC
         return(rtn);
      }
   } while (1);

   return (g_UGate.Initialize());  
}

int UG_Processing()
{
   return(g_UGate.Processing());
}

int UG_SendMessageIn(int reqtype, int pmode, const char *inmsg)
{
   return(g_UGate.HaveMessageIn(reqtype,pmode,inmsg));
}

// ������: UG_PickupTagValue
// ���  : ������ 2011-8-22 17:07:51
// ����  : ��fixmsg�п��ٻ��tag��ֵ����ֻ��ȡ��һ��
// ������ʱ��ȡ��������tag����: MsgType; BeginString; SenderCompID; TargetCompID��
// ����  : const char * : ����NULL��ʾû���ҵ�ָ����tag����tvsize����; ����ȡ����
// ����  : const char *fixmsg [IN]: ����ȡ��FIX��ʽ����Ϣ��
// ����  : int tag [IN]: Ҫ�ҵ�ָ��TAG
// ����  : char *tvalue [OUT]: ��д��ȡ��tag��ֵ
// ����  : unsigned int tvsize [IN]: tvalue�Ļ��泤�ȣ�������<=0��
const char *UG_PickupTagValue(const char *fixmsg, int tag, char *tvalue, unsigned int tvsize)
{
   char part[12];
   const char *pc;
   int plen = sprintf(part,"%d=",tag);
   tvalue[0]='\0';
   for (pc=fixmsg;*pc;++pc)
   {
      if (memcmp(pc,part,plen)==0)
      {
         // �ҵ���:
         int i;
         pc += plen;
         for (i=0;i<tvsize;++i)
         {
            switch (pc[i])
            {
            case 0x01:
            case 0:
               tvalue[i]='\0';
               return(tvalue);
            default:
               tvalue[i]=pc[i];
               break;
            }
         }
         return(NULL); // ������
      }
      while (*pc!=0x01 && *pc!='\0') ++pc;
      if (*pc=='\0')
      {
         break;
      }
   }
   return(NULL);
}


int FIXDataGetUGData(FIXDATAHANDLE h, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize)
{
   int ino;
   int n;
   int lXValue = 0;
   char tv453[4];
   memset(tv453,0,sizeof(tv453));
   memset(pUGData,0,sizeof(T_UGDATA));
   
   pUGData->lListSeqNo = -1;
   pUGData->lMsgSeqNum = -1;
   pUGData->lOrdRejReason = -1;
   pUGData->lCxlRejReason = -1;

   pUGData->dOrderQty = -1;
   pUGData->dCashOrderQty = -1;
   pUGData->dPrice = -1;
   pUGData->dAvgPx = -1;
   pUGData->dCumQty = -1;
   pUGData->dLeavesQty = -1;
   pUGData->dCommission = -1;
   pUGData->dLastPx = -1;
   pUGData->dLastQty = -1;

   n = FIXDataGetTagCount(h);
   for (ino=0;ino<n;++ino)
   {
      int tag;
      char tvalue[256];
      int vlen=sizeof(tvalue);
      FIXDataGetTagNo(h,ino,&tag,tvalue,&vlen);
      switch (tag)
      {
      case TAG_Account: // =1,		/*2.TAG1 �ɶ�����*/
         STRNCPY(pUGData->sAccount,tvalue);
         break;
      case TAG_SenderCompID: // =49,		/*6.TAG49 ���ͷ�ID*/
         STRNCPY(pUGData->sSenderCompID,tvalue);
         break;
      case TAG_TargetCompID: // =56,		/*7.TAG56 ���շ�ID*/
         STRNCPY(pUGData->sTargetCompID,tvalue);
         break;
      case TAG_MsgSeqNum: // =34,		/*19.TAG34 FIX ��Ϣ���*/
         pUGData->lMsgSeqNum = atol(tvalue);
         break;
      case TAG_CxlRejReason: // =102,		/*27.TAG102 �����ܾ�ԭ��*/
         pUGData->lCxlRejReason = atol(tvalue);
         break;
      case TAG_OrdRejReason: // =103,		/*28.TAG103�����ܾ�ԭ�� */
         pUGData->lOrdRejReason = atol(tvalue);
         break;
      case TAG_Price: // =44,		/*32.TAG44  ί�м۸�*/
         pUGData->dPrice = atof(tvalue);
         break;
      case TAG_LastPx: // =31,		/*33.TAG31 ���γɽ��۸�*/
         pUGData->dLastPx = atof(tvalue);
         break;
      case TAG_AvgPx: // =6,		/*34.TAG6 ƽ���ɽ��۸�*/
         pUGData->dAvgPx = atof(tvalue);
         break;
      case TAG_Commission: // =12,		/*35.TAG12 �ڻ���������*/
         pUGData->dCommission = atof(tvalue);
         break;
      case TAG_OrderQty: // =38,		/*37.TAG38 ί������*/
         pUGData->dOrderQty = atof(tvalue);
         break;
      case TAG_CashOrderQty: // =152,		/*37.TAG152 ί�н��*/
         pUGData->dCashOrderQty = atof(tvalue);
         break;
      case TAG_LastQty: // =32,		/*38.TAG32 ���γɽ�����*/
         pUGData->dLastQty = atof(tvalue);
         break;
      case TAG_LeavesQty: // =151,		/*39.TAG151 ʣ��δִ������*/
         pUGData->dLeavesQty = atof(tvalue);
         break;
      case TAG_CumQty: // =14,		/*40.TAG14 �ۼƳɽ���*/
         pUGData->dCumQty = atof(tvalue);
         break;
      case TAG_HandlInst: // =21,		/*68.TAG21 �������ͣ�Ŀǰ��1*/
         STRNCPY(pUGData->sHandlInst,tvalue);
         break;
      case TAG_Side: // =54,		/*69.TAG54 �ͻ����2*/
         STRNCPY(pUGData->sSide,tvalue);
         break;
      case TAG_ExecTransType: // =20,		/*70.TAG20 �������ͱ�ʶ��*/
         STRNCPY(pUGData->sExecTransType,tvalue);
         break;
      case TAG_TimeInForce: // =59,		/*72.TAG59  ί����ЧʱЧ*/
         STRNCPY(pUGData->sTimeInForce,tvalue);
         break;
      case TAG_CxlRejResponseTo: // =434,		/*73.TAG434 �����ܾ���Ӧ(1or2)*/
         STRNCPY(pUGData->sCxlRejResponseTo,tvalue);
         break;
      case TAG_ClOrdID: // =11,		/*89.TAG11 �ͻ�������ţ�Ψһ*/
         STRNCPY(pUGData->sClOrdID,tvalue);
         break;
      case TAG_OrigClOrdID: // =41,		/*90.TAG41 �ͻ�ԭʼ�������*/
         STRNCPY(pUGData->sOrigClOrdID,tvalue);
         break;
       case TAG_SvrTime: // =10101,		/*93.TAG10101:Svrʱ�� */
          pUGData->lSvrTime = atol(tvalue);
          break;
      case TAG_MsgType: // =35,		/*95.TAG35 ��Ϣ����*/
         STRNCPY(pUGData->sMsgType,tvalue);
         break;
      case TAG_Symbol: // =55,		/*97.TAG 55 ����Ʒ��(֤ȯ)����*/
         STRNCPY(pUGData->sSymbol,tvalue);
         break;
      case TAG_SecurityID: // =48
         STRNCPY(pUGData->sSecurityID,tvalue);
         break;
      case TAG_IDSource: // =22
         STRNCPY(pUGData->sIDSource,tvalue);
         break;
      case TAG_ClientID: // =109,		/*99.TAG109 �ͻ��˻�(Լ��)*/
         STRNCPY(pUGData->sClientID,tvalue);
         break;
      case TAG_TransactTime: // =60,		/*100.TAG60 UTC ��������ʱ��*/
         STRNCPY(pUGData->sTransactTime,tvalue);
         break;
      case TAG_OrdStatus: // =39,		/*108.TAG39 ����״̬*/
         STRNCPY(pUGData->sOrdStatus,tvalue);
         break;
      case TAG_ExecType: // =150,		/*109.TAG150, ִ������*/
         STRNCPY(pUGData->sExecType,tvalue);
         break;
      case TAG_BeginString: // =8,		/*118.TAG8 ��Ϣͷ��Э��汾��*/
         STRNCPY(pUGData->sBeginString,tvalue);
         break;
      case TAG_OnBehalfOfCompID: // =115,		/*119.TAG115 ��˾���(Buy Side)*/
         STRNCPY(pUGData->sOnBehalfOfCompID,tvalue);
         break;
      case TAG_DeliverToCompID: // =128,		/*120.TAG128 ��˾���(Sell Side)*/
         STRNCPY(pUGData->sDeliverToCompID,tvalue);
         break;
      case TAG_OnBehalfOfSubID: // =116,
         STRNCPY(pUGData->sOnBehalfOfSubID,tvalue);
         break;
      case TAG_DeliverToSubID: // =129,
         STRNCPY(pUGData->sDeliverToSubID,tvalue);
         break;
      case TAG_SenderSubID: // =50,
         STRNCPY(pUGData->sSenderSubID,tvalue);
         break;
      case TAG_TargetSubID: // =57,
         STRNCPY(pUGData->sTargetSubID,tvalue);
         break;
      case TAG_NonTradingOrdType: // =8526,		/*125.TAG8526 �ǽ��׶������� */
         STRNCPY(pUGData->sNonTradingOrdType,tvalue);
         break;
      case TAG_ExecID: // =17,		/*133.TAG17 ִ�б��*/
         STRNCPY(pUGData->sExecID,tvalue);
         break;
      case TAG_OrdType: // =40,		/*139.TAG40 ��������*/
         STRNCPY(pUGData->sOrdType,tvalue);
         break;
      case TAG_OpenClose: // =77,		/*140.TAG77 ��ƽ��־���ڻ���*/
         STRNCPY(pUGData->sOpenClose,tvalue);
         break;
      case TAG_Currency: // =15,		/*141.TAG15 ����*/
         STRNCPY(pUGData->sCurrency,tvalue);
         break;
      case TAG_SecurityExchange: // =207,		/*142.TAG207 ����������, Session��ͬ*/
         STRNCPY(pUGData->sSecurityExchange,tvalue);
         break;
      case TAG_OrderID: // =37,		/*153.TAG37 SellSide���صĶ������*/
         STRNCPY(pUGData->sOrderID,tvalue);
         break;
      case TAG_TEXT: // =58		      /*176.TAG58 TEXT*/
         STRNCPY(pUGData->vsmess,tvalue);
         break;
      case TAG_PossResend: // 97
         pUGData->sPossResend=tvalue[0];  // 'Y' or 'N'
         break;
      case TAG_ExpireDate: // ���ױ���ʱ������ڲ���: Date of Local Market (vs. UTC) in YYYYMMDD format.  Valid values: YYYY = 0000-9999, MM = 01-12, DD = 01-31.
         STRNCPY(pUGData->sExpireDate,tvalue);   
         break;
      case TAG_ExpireTime: // 126  UTCTime YYYYMMDD-HH:MM:SS / YYYYMMDD-HH:MM:SS.sss
         //Strncpy(pUGData->sExpireDate,tvalue,9);
         STRNCPY(pUGData->sExpireTime,tvalue);
         break;
      case TAG_Password: // 554 String:
         STRNCPY(pUGData->sPassword,tvalue);
         break;
      case TAG_ExecInst: // 18 MultiString
         STRNCPY(pUGData->sExecInst,tvalue);
         break;
      case TAG_SecondaryExecID: // 527
         STRNCPY(pUGData->sSecondaryExecID,tvalue);
         break;
      case TAG_PartyRole:  // 453
         STRNCPY(tv453,tvalue);
         break;
      case TAG_PartyID: // 448 PartyID as ClientID when 453=3
         if (strcmp(tv453,"3")==0)
         {
            STRNCPY(pUGData->sClientID,tvalue);
            tv453[0]='\0';  // ����Ͳ�������
         }
         break;
      default:
         if (addfixmsg!=NULL && 7+vlen+lXValue<afmsize-1)
         {
            sprintf(addfixmsg+lXValue,"%d=%s%c",
               tag,tvalue,C_SOH);
            lXValue += strlen(addfixmsg+lXValue);
         }
         break;         
      }
   }
#if 1
   // ExecID: nnnDmmm-XXXXXXXX:
   pUGData->lExecNoCnt = atoi(pUGData->sExecID);
   pUGData->lDays = 0;
   for (ino=0;pUGData->sExecID[ino]!='\0';ino++)
   {
      if (pUGData->sExecID[ino]=='D')
      {
         pUGData->lDays = atoi(pUGData->sExecID+ino+1);
         break;
      }
      if (pUGData->sExecID[ino]<'0'
         || pUGData->sExecID[ino]>'9')
         break; // ����
   }
#else  
   // ԭ���ݸ�ʽ: xxxxxxxNNNNNN
   if (strlen(pUGData->sExecID)<8)
      pUGData->lExecNoCnt = 0;
   else
      pUGData->lExecNoCnt = atoi(pUGData->sExecID+7);
#endif
   return(n);
}


// ������: UG_UGDataReturn
// ���  : ������ 2011-9-17 14:54:09
// ����  : ����pUGData�е�sSenderCompID��sTargetCompID��sOnBehalfOfCompID��sDeliverToCompID
// ����  : void 
// ����  : T_UGDATA *pUGData [IN/OUT]
void UG_UGDataReturn(T_UGDATA *pUGData)
{
   char fvalue[256];
   STRNCPY(fvalue,pUGData->sSenderCompID);
   STRNCPY(pUGData->sSenderCompID,pUGData->sTargetCompID);
   STRNCPY(pUGData->sTargetCompID,fvalue);
   
   STRNCPY(fvalue,pUGData->sOnBehalfOfCompID);
   STRNCPY(pUGData->sOnBehalfOfCompID,pUGData->sDeliverToCompID);
   STRNCPY(pUGData->sDeliverToCompID,fvalue);
   
   STRNCPY(fvalue,pUGData->sOnBehalfOfSubID);
   STRNCPY(pUGData->sOnBehalfOfSubID,pUGData->sDeliverToSubID);
   STRNCPY(pUGData->sDeliverToSubID,fvalue);

   STRNCPY(fvalue,pUGData->sSenderSubID);
   STRNCPY(pUGData->sSenderSubID,pUGData->sTargetSubID);
   STRNCPY(pUGData->sTargetSubID,fvalue);
}



// ������: UG_CancelRejectFIXMsg
// ���  : ������ 2011-9-17 14:58:17
// ����  : ��pUGDataת��ΪCancelReject��FIX��Ϣ��
// ����  : int :�������ɵĴ��ĳ���
// ����  : T_UGDATA *pUGData[IN]: ��������
// ����  : char *fixmsg [OUT]: ���ɵ�FIX��Ϣ���Ļ���
// ����  : unsigned int fmsize[IN]: fixmsg�Ļ��泤��
int UG_CancelRejectFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize)
{
   int fmlen = 0;
   int rtn;
   
   rtn = FVString2FIXMsg(TAG_BeginString,pUGData->sBeginString,fixmsg,fmsize);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_MsgType,"9"/*pUGData->sMsgType*/,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderCompID,pUGData->sSenderCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetCompID,pUGData->sTargetCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfCompID,pUGData->sOnBehalfOfCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToCompID,pUGData->sDeliverToCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfSubID,pUGData->sOnBehalfOfSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToSubID,pUGData->sDeliverToSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderSubID,pUGData->sSenderSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetSubID,pUGData->sTargetSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrderID,pUGData->sOrderID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClOrdID,pUGData->sClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrigClOrdID,pUGData->sOrigClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdStatus,pUGData->sOrdStatus,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ListID,pUGData->sListID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVInt2FIXMsg(TAG_ListSeqNo,pUGData->lListSeqNo,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,pUGData->sAccount,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_CxlRejResponseTo,pUGData->sCxlRejResponseTo,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVInt2FIXMsg(TAG_CxlRejReason,pUGData->lCxlRejReason,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TEXT,pUGData->vsmess,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (strcmp(pUGData->sBeginString,"FIX.4.2")<=0)  // 20110309
   {
      rtn = FVString2FIXMsg(TAG_ClientID,pUGData->sClientID,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }   
         
   return(fmlen);
}


// ������: UG_ExecutionFIXMsg
// ���  : ������ 2011-9-17 15:02:55
// ����  : ��pUGDataת��ΪExecution Report��FIX��Ϣ��
// ����  : int :�������ɵĴ��ĳ���
// ����  : T_UGDATA *pUGData[IN]: ��������
// ����  : char *fixmsg [OUT]: ���ɵ�FIX��Ϣ���Ļ���
// ����  : unsigned int fmsize[IN]: fixmsg�Ļ��泤��
int UG_ExecutionFIXMsg(T_UGDATA *pUGData,char *fixmsg, unsigned int fmsize)
{
   int fmlen = 0;
   int rtn;
   rtn = FVString2FIXMsg(TAG_BeginString,pUGData->sBeginString,fixmsg,fmsize);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_MsgType,"8"/*pUGData->sMsgType*/,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_SenderCompID,pUGData->sSenderCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetCompID,pUGData->sTargetCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfCompID,pUGData->sOnBehalfOfCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToCompID,pUGData->sDeliverToCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfSubID,pUGData->sOnBehalfOfSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToSubID,pUGData->sDeliverToSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderSubID,pUGData->sSenderSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetSubID,pUGData->sTargetSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,pUGData->sAccount,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ListID,pUGData->sListID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVInt2FIXMsg(TAG_ListSeqNo,pUGData->lListSeqNo,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVDouble2FIXMsg(TAG_Price,pUGData->dPrice,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (pUGData->sExecType[0]=='I' || pUGData->sExecTransType[0]=='3')
   {
      // ����PossResend='Y' & ClOrdID duplicated, �򷵻ض���״̬��ѯ�����:
   }
   else
   {
      rtn = FVDouble2FIXMsg(TAG_LastPx,pUGData->dLastPx,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
      
      rtn = FVQty2FIXMsg(TAG_LastQty,pUGData->dLastQty,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;      
   }

   rtn = FVDouble2FIXMsg(TAG_AvgPx,pUGData->dAvgPx,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVQty2FIXMsg(TAG_OrderQty,pUGData->dOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_CashOrderQty,pUGData->dCashOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVQty2FIXMsg(TAG_LeavesQty,pUGData->dLeavesQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_CumQty,pUGData->dCumQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
      
   rtn = FVString2FIXMsg(TAG_OrigClOrdID,pUGData->sOrigClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClOrdID,pUGData->sClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrderID,pUGData->sOrderID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExecID,pUGData->sExecID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_SecondaryExecID,pUGData->sSecondaryExecID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Symbol,pUGData->sSymbol,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityID,pUGData->sSecurityID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_IDSource,pUGData->sIDSource,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_Side,pUGData->sSide,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdStatus,pUGData->sOrdStatus,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (strcmp(pUGData->sBeginString,"FIX.4.2")<=0)
   {
      rtn = FVString2FIXMsg(TAG_ExecTransType,pUGData->sExecTransType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
      
      rtn = FVString2FIXMsg(TAG_ExecType,pUGData->sExecType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }
   else
   {
      if (strcmp(pUGData->sExecType,"1")==0
         ||strcmp(pUGData->sExecType,"2")==0)
         rtn = FVString2FIXMsg(TAG_ExecType,"F",fixmsg+fmlen,fmsize-fmlen);  // F = Trade (partial fill or fill)
      else
         rtn = FVString2FIXMsg(TAG_ExecType,pUGData->sExecType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;         
   }
   
   rtn = FVString2FIXMsg(TAG_SecurityExchange,pUGData->sSecurityExchange,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdType,pUGData->sOrdType,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_TimeInForce,pUGData->sTimeInForce,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;

   rtn = FVString2FIXMsg(TAG_ExpireDate,pUGData->sExpireDate,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExpireTime ,pUGData->sExpireTime,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OpenClose ,pUGData->sOpenClose,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_HandlInst,pUGData->sHandlInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExecInst,pUGData->sExecInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;


   if (strcmp(pUGData->sBeginString,"FIX.4.2")<=0)  // 20110309
   {
      rtn = FVString2FIXMsg(TAG_ClientID,pUGData->sClientID,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }   

   rtn = FVString2FIXMsg(TAG_TEXT,pUGData->vsmess,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   if (pUGData->sOrdStatus[0]=='8')
   {
      // ���������ܾ������,���ܾͻ��и��ֶ�
      rtn = FVInt2FIXMsg(TAG_OrdRejReason,pUGData->lOrdRejReason,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }

   rtn = FVString2FIXMsg(TAG_Currency,pUGData->sCurrency,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   

   return(fmlen);
}


// ������: UG_NewOrderSingle2FIXMsg
// ���  : ������ 2011-9-17 15:14:13
// ����  : ��pUGDataת��ΪNewOrderSingle��FIX��Ϣ��
// ����  : int :�������ɵĴ��ĳ���
// ����  : T_UGDATA *pUGData[IN]: ��������
// ����  : char *fixmsg [OUT]: ���ɵ�FIX��Ϣ���Ļ���
// ����  : unsigned int fmsize[IN]: fixmsg�Ļ��泤��
int UG_NewOrderSingle2FIXMsg(T_UGDATA *pUGData, const char *addfixmsg, char *fixmsg, int fmsize)
{
   int fmlen = 0;
   int rtn;
   fixmsg[0]='\0';
   
   rtn = FVString2FIXMsg(TAG_BeginString,pUGData->sBeginString,fixmsg,fmsize);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_MsgType,"D",fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderCompID,pUGData->sSenderCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetCompID,pUGData->sTargetCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfCompID,pUGData->sOnBehalfOfCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToCompID,pUGData->sDeliverToCompID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OnBehalfOfSubID,pUGData->sOnBehalfOfSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_DeliverToSubID,pUGData->sDeliverToSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SenderSubID,pUGData->sSenderSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TargetSubID,pUGData->sTargetSubID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClOrdID,pUGData->sClOrdID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClientID,pUGData->sClientID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,pUGData->sAccount,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_HandlInst,pUGData->sHandlInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExecInst,pUGData->sExecInst,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Symbol,pUGData->sSymbol,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityID,pUGData->sSecurityID,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_IDSource,pUGData->sIDSource,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityExchange,pUGData->sSecurityExchange,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Side,pUGData->sSide,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_OrderQty,pUGData->dOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVQty2FIXMsg(TAG_CashOrderQty,pUGData->dCashOrderQty,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OrdType,pUGData->sOrdType,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVDouble2FIXMsg(TAG_Price,pUGData->dPrice,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_Currency,pUGData->sCurrency,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   //long	lSvrTime;		/*93.TAG10101:Svrʱ�� */
   rtn = FVInt2FIXMsg(TAG_SvrTime,pUGData->lSvrTime,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   //char	sTimeInForce[4];		/*72.TAG59  ί����ЧʱЧ*/
   rtn = FVString2FIXMsg(TAG_TimeInForce ,pUGData->sTimeInForce,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExpireDate,pUGData->sExpireDate,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_ExpireTime ,pUGData->sExpireTime,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVDouble2FIXMsg(TAG_Commission,pUGData->dCommission,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0) fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_TEXT, pUGData->vsmess,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   rtn = FVString2FIXMsg(TAG_OpenClose ,pUGData->sOpenClose,fixmsg+fmlen,fmsize-fmlen);
   if (rtn>0)  fmlen += rtn;
   
   if (pUGData->sOrdType[0]=='Z')
   {
      rtn = FVString2FIXMsg(TAG_NonTradingOrdType,pUGData->sNonTradingOrdType,fixmsg+fmlen,fmsize-fmlen);
      if (rtn>0) fmlen += rtn;
   }
   
   if (addfixmsg!=NULL)
   {
      rtn = strlen(addfixmsg);
      if (rtn>fmsize-fmlen)
         rtn = fmsize-fmlen;
      while (rtn>0 && addfixmsg[rtn-1]!=C_SOH)
         --rtn;
      if (rtn>0)
      {
         memcpy(fixmsg+fmlen,addfixmsg,rtn);
         fmlen += rtn;
         fixmsg[fmlen]='\0';
      }
   }
   return(fmlen);
}

// ������: UG_FIXMsg2UGData
// ���  : ������ 2011-8-25 16:41:02
// ����  : ��ȡfixmsg�еĹؼ����ݵ�pUGData�У�������ȡ�ģ����ŵ�addfixmsg��
// ����  : int <0: ʧ��,fixmsg���ǺϹ����Ϣ����ϵͳ�쳣��>0: �ɹ������ع��ж��ٸ��ֶ���
// ����  : const char *fixmsg [IN]: ����ȡ��FIX��Ϣ��
// ����  : int fmlen [IN]: fixmsg�Ĵ���
// ����  : T_UGDATA *pUGData [OUT]: Ҫ����д�Ĺؼ��ֶ�ֵ
// ����  : const char *addfixmsg [IN]: û���ܹ�����д��pUGData�еķǹؼ����FIX���Ӵ���NULL-���� 
// ����  : unsigned int afmsize [IN]:  addfixmsg�Ļ����ֽ���
int UG_FIXMsg2UGData(const char *fixmsg, int fmlen, T_UGDATA *pUGData, char *addfixmsg, unsigned int afmsize)
{
   int n;
   FIXDATAHANDLE h;
   h = FIXDataNew();
   if (h==NULL)
      return(-1);
   if (FIXDataSetData(h,fixmsg,fmlen)<0)
      n = -2;
   else
      n = FIXDataGetUGData(h,pUGData,addfixmsg,afmsize);
   FIXDataDelete(h);
   return(n);
}

// UDL��������ͨ��״̬�����Ϣ���Ը���ƽ̨���
// statusinfo��ʽΪ: <LocalID>|<PartnerID1>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>|...|<PartnerIDx>:<status>:<load>:<errmsg>:<InMsgs>:<OutMsgs>
int UDLHaveChannelStatusInfo(const char *statusinfo)
{
   return(g_UGate.HaveMessageIn(RT_UPSTATUS,0,statusinfo));
}

// ������: UDLHaveMessageIn
// ���  : ������ 2011-8-19 23:42:29
// ����  : UDL�ӶԷ��յ���Ϣ����Ҫͨ��UG�ύ��FSƽ̨
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: Ϊ����Ϣ�������Ǹ�Partner��Ҳ����ΪNULL
// ����  : const char *fixmsg [IN]: UDL�ύ��UG���д����FIX��Ϣ����
int UDLHaveMessageIn(const char *PartnerID,const char *infixmsg)
{
   char msgtype[8];
   CFIXData fixdata;
   char fixmsg[MAXFIXDATALENGTH];
   if (fixdata.SetData(infixmsg,strlen(infixmsg)))
   {
      fixdata.UpdateTag(-1,TAG_TargetCompID,g_UGate.m_LocalID);  // TargetCompID updated with LocalID
      if (PartnerID!=NULL)
      {
         fixdata.UpdateTag(-1,TAG_SenderCompID,PartnerID);
      }
      int tvlen = sizeof(msgtype);
      if (fixdata.GetTag(TAG_MsgType,msgtype,tvlen)>=0)
      {
         fixdata.GetFIXData(fixmsg,sizeof(fixmsg));
         int i;
         for (i=0;g_InMsgFuncs[i].MsgType[0];++i)
         {
            if (strcmp(g_InMsgFuncs[i].MsgType,msgtype)==0)
            {
               return(g_UGate.HaveMessageIn(g_InMsgFuncs[i].reqtype,1,&fixdata));
            }
         }
         return(g_UGate.HaveMessageIn(RT_OTHERBUS,1,&fixdata));   
      }
   }
   g_LogFile.WriteLogEx(11556,"Invalid MsgIn:%s",infixmsg);
   return(-1);
}


int FIXTagComp(FIXDATAHANDLE h1, FIXDATAHANDLE h2, int tag)
{
   char tvalue1[256]={0};
   char tvalue2[256]={0};
   int tvlen;

   tvlen=sizeof(tvalue1); FIXDataGetTag(h1,tag,tvalue1,&tvlen);
   tvlen=sizeof(tvalue2); FIXDataGetTag(h2,tag,tvalue2,&tvlen);
   return(strcmp(tvalue1,tvalue2));
}


// ������: UG_FIXMsgKeyTagCmp
// ���  : ������ 2011-8-26 17:35:24
// ����  : �Ƚ�����FIX��Ϣ�е���ؼ���ȷ���Ƿ����Ϊ��ͬ����Ϣ
// ����  : int =0: ��ʾ��ͬ��
//       ����Ϊ��ͬ��-- 1:MsgType; 2: NewOrderSingle; 3:OrderCancel/OrderModification; 
//                      4:Execution Report; 5:Order Cancel Reject; 6:New Order List
// ����  : const char *fixmsg1 [IN]: ���Ƚϵ�FIX��Ϣ1
// ����  : const char *fixmsg2 [IN]: ���Ƚϵ�FIX��Ϣ2
int UG_FIXMsgKeyTagCmp(const char *fixmsg1, const char *fixmsg2)
{
   FIXDATAHANDLE h1,h2;
   char msgtype[8];
   int tvlen;

#define FIXCMPRETURN(a) { FIXDataDelete(h1); FIXDataDelete(h2); return(a); }

   h1 = FIXDataNew(); h2 = FIXDataNew();
   FIXDataSetData(h1,fixmsg1,-1);
   FIXDataSetData(h2,fixmsg2,-1);
   if (FIXTagComp(h1,h2,TAG_MsgType))
      FIXCMPRETURN(1); // �������ͬ���ǾͲ��ñȽ���
   tvlen=sizeof(msgtype); FIXDataGetTag(h1,TAG_MsgType,msgtype,&tvlen);
   switch (msgtype[0])
   {
   case 'D': // New Order Single Request
      // ֻҪ�Ƚ�һ��ClOrdID��Ӧ�þͿ�����
      if (FIXTagComp(h1,h2,TAG_ClOrdID))
         FIXCMPRETURN(2);
      break;
   case 'E': // E = New Order List
      if (FIXTagComp(h1,h2,TAG_ListID)         
         ||FIXTagComp(h1,h2,TAG_ClOrdID))
         FIXCMPRETURN(6);
      break;
   case 'F': // F = Order Cancel Request
   case 'G': // G= Order Cancel/Replace Request
      if (FIXTagComp(h1,h2,TAG_ClOrdID)
         ||FIXTagComp(h1,h2,TAG_OrigClOrdID))
         FIXCMPRETURN(3);
      break;
   case '8': // 8 = Execution Report
      //"8|11|17|39|150",       // Execution|ClOrdID|ExecID|OrdStatus|ExecType
      if (FIXTagComp(h1,h2,TAG_ClOrdID)
         ||FIXTagComp(h1,h2,TAG_ExecID)
         ||FIXTagComp(h1,h2,TAG_OrdStatus)
         ||FIXTagComp(h1,h2,TAG_ExecType))
         FIXCMPRETURN(4);
      break;
   case '9': // 9 = Order Cancel Reject
      //"9|11|41|39|434|102",   // CancelRej|ClOrdID|OrigClOrdID|OrdStatus|CxlRejResponseTo|CxlRejReason
      if (FIXTagComp(h1,h2,TAG_ClOrdID)
         ||FIXTagComp(h1,h2,TAG_OrigClOrdID)
         ||FIXTagComp(h1,h2,TAG_OrdStatus)
         ||FIXTagComp(h1,h2,TAG_CxlRejResponseTo)
         ||FIXTagComp(h1,h2,TAG_CxlRejReason))
         FIXCMPRETURN(5);
      break;
//    default:  // ������ͬ���ǲ�ͬ�أ�
//       FIXCMPRETURN(0); // ����ͬ����ʾ���ûָ�����Ϣ
   }
   FIXCMPRETURN(0); // ����ͬ����ʾ���ûָ�����Ϣ

#undef FIXCMPRETURN
}


// ������: UG_GetSSPendingOrders
// ���  : ������ 2011-8-24 22:14:35
// ����  : UG�ӿ��У����ڴ�FSƽ̨��û�û��OrderID(����֪���Ƿ��Ѿ����͸�SellSide)��New Order Request / Order Cancel Request��Ϣ�б�
// ����  : int ���صõ�����Ϣ����
// ����  : const char *SSPartnerid [IN]: ��SellSide��PartnerID
// ����  : L_MSGDATA &msglist [OUT]: �õ���δ������Ϣ
int UG_GetSSPendingOrders(const char *SSPartnerid, L_MSGDATA &msglist)
{
   // RT_GETSSORD  411769   // IN: Get SSOrders from FS <flag>|<SellSide>...
   //  ��ȡ��UG_SSORDERS��SSORDERIDΪ�յļ�¼����SSCLORDID������
   return(g_UGate.GetSSOrders(0,SSPartnerid,msglist));   
}


// ������: UG_GetBSExecRepts
// ���  : ������ 2011-8-24 22:24:36
// ����  : UG�ӿ��У����ڴ�FSƽ̨������б����
// ����  : int ���صõ�����Ϣ����
// ����  : const char *BSPartnerID [IN]: ��BuySide��PartnerID
// ����  : L_MSGDATA &msglist [OUT]: �õ�����Ϣ
int UG_GetBSExecRepts(const char *BSPartnerID, L_MSGDATA &msglist)
{
   // ���UG_EXEC�еĸ�Partner����Ϣ
   return(g_UGate.GetBSExecRepts(BSPartnerID,msglist));
}

// ������: UG_GetSSAllOrders
// ���  : ������ 2011-9-30 23:02:08
// ����  : UG�ӿ��У����ڴ�FSƽ̨����������ڸ�SellSide��NewOrderRequest��OrderCancelRequest��Ϣ��
//       ���Ѿ��д����صģ��������Ϣ�У�����OrderID���򣬼� 37=<OrderID>����
// ����  : int ���صõ�����Ϣ����
// ����  : const char *sSSPartnerID [IN]: ��SellSide��PartnerID
// ����  : L_MSGDATA &msglist [OUT]: ���ص����ڱ�SellSide��SSOrders��Ϣ�б�
int UG_GetSSAllOrders(const char *sSSPartnerID, L_MSGDATA &msglist)
{
   return(g_UGate.GetSSOrders(1,sSSPartnerID,msglist));
}


// ������: UG_RestoreFIXInMsg
// ���  : ������ 2011-8-28 16:17:02
// ����  : �Իָ��ķ�ʽ��FIX IN����Ϣ�ύ��FS
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *fixmsg [IN]: IN FIX Message
int UG_RestoreFIXInMsg(const char *partnerid, const char *infixmsg)
{
   CFIXData fixdata;
   //char fixmsg[MAXFIXDATALENGTH];
   if (!fixdata.SetData(infixmsg,strlen(infixmsg)))
      return(-1); // ����������Ϣ
   fixdata.UpdateTag(-1,TAG_TargetCompID,g_UGate.m_LocalID);  // TargetCompID updated with LocalID
   if (partnerid!=NULL)
      fixdata.UpdateTag(-1,TAG_SenderCompID,partnerid);
   //fixdata.GetFIXData(fixmsg,sizeof(fixmsg));
   // �Իָ��ķ�ʽ��FIX IN����Ϣ�ύ��FS
   return(g_UGate.HaveMessageIn(RT_RESINMSG,1,&fixdata));
}

// ������: UG_CheckEOD
// ���  : ������ 2011-8-27 21:42:47
// ����  : ���FSƽ̨�������Ƿ���Ҫ��EOD����ͬʱ����FS�Ƿ���ҪDFD
// ����  : int  0 - ��ʾ������EOD�������ʾҪ��EOD����
// ����  : const char *partnerid [IN]: ���ַ���ʶ
// int UG_CheckEOD(const char *partnerid)
// {
//    // RT_CHECKEOD  411756   // IN: Check EOD of Partner <0-UG>|<UGID>|<PARTNERID>
//    return(g_UGate.CheckEOD(partnerid));     
// }



// ������: UG_GetPartners
// ���  : ������ 2011-8-29 23:58:55
// ����  : ȡϵͳ��������ڱ�UG�ĸ���Partner
// ����  : const char * : ������ЧPartnerID����: <PartnerID1>;<PartnerID2>;...;<PartnerIDn>
const char *UG_GetPartners()
{
   return(g_UGate.GetPartners());
}

void UG_SetOutMode(int outmode)
{
   g_UGate.ToSetOutMode(outmode);
}