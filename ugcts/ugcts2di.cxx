// ***************************************************************
//  ugcts2di   version:  1.0   CYH  date: 09/17/2011
//  -------------------------------------------------------------
//  ������һЩUGCTSͨ�������ݿ�����Ļ�������
//  -------------------------------------------------------------
//  Copyright (C) 2011 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "xpub.h"
EXEC SQL INCLUDE sqlca;

EXEC SQL BEGIN DECLARE SECTION;
EXEC SQL INCLUDE 'ugcts2di.hxx';
EXEC SQL END DECLARE SECTION;
struct _DB_UGDATA DB_UGData;
struct _T_REAL_DONE tRealDone;

#include "UGDBFuncs.h"


// ȡKSCTS���ݿ��е�REAL_DONE���е����DONE_IDֵ ����EOD���ã�
int DBGetLastMaxDoneID(long *lastdoneid)
{
   EXEC SQL BEGIN DECLARE SECTION;
   long lmaxdoneid;
   EXEC SQL END DECLARE SECTION;
   EXEC SQL SELECT max(done_id) INTO :lmaxdoneid FROM KS.REAL_DONE;
   if (SQLCODE)
   {
      SQLDebugLog(40010,"DBGetLastMaxDoneID - SQLCODE=%d @ %s-%d",
         SQLCODE,__FILE__,__LINE__);
      *lastdoneid = 0;
   }
   else
      *lastdoneid = lmaxdoneid;
   return(SQLCODE);
}

// ������: DBFetchRDRecords
// ���  : ������ 2011-9-20 0:27:41
// ����  : ��֤ȯ����ϵͳ���ݿ��ж�ȡ����FIXί�����͵ĳɽ���¼�ͳ�����¼
// ����  : int : ���ض�ȡ�ļ�¼��
// ����  : const char *sENTRUST_METHOD [IN]: ������ϵͳ�ڲ���¼��ENTRUST_METHOD������FIXί�е������� 'f'
// ����  : long *lastdoneid [IN/OUT]: �ϴζ��������DONE_ID��ţ���<0��ʱ�򣬼���Ϊ��һ�Σ���ͷ��ʼ��
// ����  : int cjxhry [IN]: DONE_ID�Ļ��˼����������ظ�������ֹ��©
// ����  : int cjsjry [IN]: RDONE_DATETIME�Ļ���ʱ�������������ظ�������ֹ��©
int DBFetchRDRecords(const char *sENTRUST_BRANCH,const char *sENTRUST_METHOD, long *lastdoneid, int cjxhry, int cjsjry)
{
   EXEC SQL BEGIN DECLARE SECTION;
   char ent_mothed2[2];
   long ldoneid;
   long ltmus;
   char ent_branch2[8];
   EXEC SQL END DECLARE SECTION;
   int n=0;
   int sqlcode;

   STRNCPY(ent_branch2,sENTRUST_BRANCH);
   STRNCPY(ent_mothed2,sENTRUST_METHOD);
   ldoneid = *lastdoneid;
   if (ldoneid>=0)
   {
      // �Ǻ��������˵�
      ltmus = cjsjry;
      ldoneid -= cjxhry;
      EXEC SQL DECLARE C_RDONE1 CURSOR FOR 
         SELECT DONE_ID,CONTRACT_NO,DONE_NO,
         SEC_TYPE,SEC_CODE,DONE_VOL,
         DONE_TIME,RPT_CONTRACT_NO,
         BS,DONE_PRICE,OCCUR_TIME
         FROM KS.REAL_DONE
         WHERE DONE_ID>:ldoneid
         /*AND ENTRUST_METHOD=:ent_mothed2*/
         AND ENTRUST_BRANCH=:ent_branch2
         AND RDONE_DATETIME>(CURRENT TIMESTAMP - :ltmus SECONDS)
         FOR FETCH ONLY;  
         /* WITH UR;  ?? ���ֺ��� ?? */
      
      EXEC SQL OPEN C_RDONE1;
      while (SQLCODE==0)
      {
         EXEC SQL FETCH C_RDONE1
            INTO :tRealDone.lDONE_ID,:tRealDone.sCONTRACT_NO,:tRealDone.dDONE_NO,
                  :tRealDone.sSEC_TYPE,:tRealDone.sSEC_CODE,:tRealDone.lDONE_VOL,
                  :tRealDone.sDONE_TIME,:tRealDone.sRPT_CONTRACT_NO,
                  :tRealDone.sBS,:tRealDone.dDONE_PRICE,:tRealDone.sOCCUR_TIME;
         if (SQLCODE)
            break;
         if ((*lastdoneid)<tRealDone.lDONE_ID)
            *lastdoneid = tRealDone.lDONE_ID;
         HaveDBRealDone(&tRealDone);
         ++n;
      }
      sqlcode = SQLCODE;
      EXEC SQL CLOSE C_RDONE1;
   }
   else
   {
      *lastdoneid = 0;  // ��ʾ���治���ǵ�һ����
      EXEC SQL DECLARE C_RDONE2 CURSOR FOR 
         SELECT DONE_ID,CONTRACT_NO,DONE_NO,
         SEC_TYPE,SEC_CODE,DONE_VOL,DONE_TIME,
         RPT_CONTRACT_NO,BS,DONE_PRICE,OCCUR_TIME
         FROM KS.REAL_DONE
         WHERE /*ENTRUST_METHOD=:ent_mothed2;*/
         ENTRUST_BRANCH=:ent_branch2
         FOR FETCH ONLY;
      EXEC SQL OPEN C_RDONE2;
      while (SQLCODE==0)
      {
         EXEC SQL FETCH C_RDONE2
            INTO :tRealDone.lDONE_ID,:tRealDone.sCONTRACT_NO,:tRealDone.dDONE_NO,
            :tRealDone.sSEC_TYPE,:tRealDone.sSEC_CODE,:tRealDone.lDONE_VOL,
            :tRealDone.sDONE_TIME,:tRealDone.sRPT_CONTRACT_NO,
            :tRealDone.sBS,:tRealDone.dDONE_PRICE,:tRealDone.sOCCUR_TIME;
         if (SQLCODE)
            break;
         if ((*lastdoneid)<tRealDone.lDONE_ID)
            *lastdoneid = tRealDone.lDONE_ID;
         HaveDBRealDone(&tRealDone);
         ++n;
      }
      sqlcode = SQLCODE;
      EXEC SQL CLOSE C_RDONE2;
   }
   Commit(); // �������߶�ʮһ
   if (sqlcode!=NOTFOUND)
   {
      SQLDebugLog(40003,"PE:Fail to FETCH REAL_DONE from DONE_ID>%ld, SQLCODE=%d @ %s-%d",
         *lastdoneid,sqlcode,__FILE__,__LINE__);
   }
   return(n);
}

// ������: DBInsertFIXEntrust
// ���  : ������ 2011-9-17 23:14:37
// ����  : ��T_UGDATA�ڲ������ݣ����뵽UGCTS�����ݿ�FIX_BSORDERS����
// ����  : int <0: ����ʧ�ܣ�==0: ����ɹ�
// ����  : T_UGDATA *pUGData [IN]: ��������
int DBInsertFIXEntrust(T_UGDATA *pUGData)
{
   /*
   memcpy(&DB_UGData,pUGData,sizeof(DB_UGData));

   EXEC SQL INSERT INTO FIX_BSORDERS
      (ORIGCLORDID,CLORDID,
      SELLSIDE,SSCLORDID,BEGINSTRING,
      ONBEHALFCOMPID,DELIVERCOMPID,
      PCXLCLORDID,MSGSEQNUM,MSGTYPE,
      LISTID,LISTSEQNO,ORDERID,
      ORDTYPE,NONTRADINGORDTYPE,
      TIMEINFORCE,SIDE,
      OPENCLOSE,HANDLINST,
      TRANSACTTIME,SYMBOL,
      ORDERQTY,CURRENCY,
      PRICE,ACCOUNT,
      CLIENTID,SECURITYEXCHANGE,
      ORDSTATUS,EXECTYPE,
      CANCELEDQTY,LOCALDATE,
      LOCALTIME,AVGPX,CUMQTY,
      LEAVESQTY,EXECNOCNT,CASHORDERQTY,
      EXPIREDATE,EXPIRETIME
      )
      VALUES
      (:DB_UGData.sOrigClOrdID,:DB_UGData.sClOrdID,
      '','',:DB_UGData.sBeginString,
      :DB_UGData.sOnBehalfOfCompID,:DB_UGData.sDeliverToCompID,
      '',:DB_UGData.lMsgSeqNum,:DB_UGData.sMsgType,
      :DB_UGData.sListID,:DB_UGData.lListSeqNo,:DB_UGData.sOrderID,
      :DB_UGData.sOrdType,:DB_UGData.sNonTradingOrdType,
      :DB_UGData.sTimeInForce,:DB_UGData.sSide,
      :DB_UGData.sOpenClose,:DB_UGData.sHandlInst,
      :DB_UGData.sTransactTime,:DB_UGData.sSymbol,
      :DB_UGData.dOrderQty,:DB_UGData.sCurrency,
      :DB_UGData.dPrice,:DB_UGData.sAccount,
      :DB_UGData.sClientID,:DB_UGData.sSecurityExchange,
      :DB_UGData.sOrdStatus,:DB_UGData.sExecType,
      0,:DB_UGData.sLocalDate,
      :DB_UGData.sLocalTime,0,0,
      0,1,:DB_UGData.dCashOrderQty,
      :DB_UGData.sExpireDate,:DB_UGData.sExpireTime
      );
   if (SQLCODE)
   {
      SQLDebugLog(40001,"Fail to INSERT FIX_BSORDERS(%s), SQLCODE=%d @ %s-%d",
         DB_UGData.sClOrdID,SQLCODE,__FILE__,__LINE__);
      return(-1);
   }
   Commit();
   */
   return(0);
}


// ������: DBGetEntrustStatus
// ���  : ������ 2011-9-18 10:18:50
// ����  : ��KSCTS��ENTRUST���в�ָ��ί�е����ݣ�������Ϊ1��ʱ��:
//          sSellSide = ENTRUST.MARKET_CODE;
//          sOrderID = ENTRUST.RPT_CONTRACT;
//          sOrdStatus = ENTRUST.ENTRUST_STATUS;
//          sExecInst = ENTRUST.EXCHANGE_ERR_CODE;
//          sAccount = ENTRUST.HOLDER_ACC_NO;
//          sClientID = ENTRUST.CUST_NO;
// ����  : int -1: ʧ�ܣ����ݿ��쳣(Ҳ�п����ж���); 
//             0: û���ҵ�ָ��ί�м�¼��
//             1: �ҵ�������pUGData�е��������ݽ����޸�
// ����  : const char *sENTRUST_METHOD [IN]: KSCTS�ڲ���ί�з�ʽ����g_KSCTS.m_WTFSiֵ
// ����  : T_UGDATA *pUGData[IN/OUT]: ��pUGData->sOrigClOrdID��Ϊί�к�ͬ����ָ��ί�м�¼��
//                   ������1��ʱ�򣬸������������ֶΣ�������KSCTS�ı�ʾ��ʽ
int DBGetEntrustStatus(const char *sENTRUST_BRANCH,const char *sENTRUST_METHOD, T_UGDATA *pUGData)
{
   EXEC SQL BEGIN DECLARE SECTION;
   char ent_method1[2];
   long ent_vol;
   char ent_bs[4];
   char ent_branch1[8];
   EXEC SQL END DECLARE SECTION;
   int sqlcode;
   STRNCPY(ent_method1,sENTRUST_METHOD);
   STRNCPY(ent_branch1,sENTRUST_BRANCH);
   memcpy(&DB_UGData,pUGData,sizeof(DB_UGData));
   if (strcmp(pUGData->sMsgType,"F")==0)
   {
      strcpy(ent_bs,"1%");  // �������BS
      strcpy(ent_method1,"4"); // �ƺ���д���ģ��μ�p130105.sql
   }
   else
   {
      strcpy(ent_bs,"0%");  // ԭʼί����BS
   }
   EXEC SQL SELECT 
      MARKET_CODE,RPT_CONTRACT,
      ENTRUST_STATUS,EXCHANGE_ERR_CODE,
      ENTRUST_VOL,HOLDER_ACC_NO,
      CUST_NO
      INTO
      :DB_UGData.sSellSide,:DB_UGData.sOrderID,
      :DB_UGData.sOrdStatus,:DB_UGData.sExecInst,
      :ent_vol,:DB_UGData.sAccount,
      :DB_UGData.sClientID
      FROM KS.ENTRUST
      WHERE CONTRACT_NO=:DB_UGData.sOrigClOrdID
      AND ENTRUST_METHOD=:ent_method1
      AND ENTRUST_BRANCH=:ent_branch1
      AND BS LIKE :ent_bs WITH UR;
   sqlcode = SQLCODE;
   Commit();
   if (sqlcode==NOTFOUND)
      return(0);
   if (sqlcode)
   {
      SQLDebugLog(40002,"Fail to SELECT KS.ENTRUST(%s,%s), SQLCODE=%d @ %s-%d",
         DB_UGData.sOrigClOrdID,ent_method1,
         sqlcode,__FILE__,__LINE__);
      return(-1);
   }
   mytrim(DB_UGData.sSellSide);
   mytrim(DB_UGData.sOrderID);
   mytrim(DB_UGData.sOrdStatus);
   mytrim(DB_UGData.sExecInst);
   mytrim(DB_UGData.sAccount);
   mytrim(DB_UGData.sClientID);
   STRNCPY(pUGData->sSellSide,DB_UGData.sSellSide); 
   STRNCPY(pUGData->sOrderID,DB_UGData.sOrderID);
   STRNCPY(pUGData->sOrdStatus,DB_UGData.sOrdStatus);
   STRNCPY(pUGData->sExecInst,DB_UGData.sExecInst);
   STRNCPY(pUGData->sAccount,DB_UGData.sAccount);
   STRNCPY(pUGData->sClientID,DB_UGData.sClientID);
   pUGData->dOrderQty = ent_vol;
   return(1);
}