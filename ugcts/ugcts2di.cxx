// ***************************************************************
//  ugcts2di   version:  1.0   CYH  date: 09/17/2011
//  -------------------------------------------------------------
//  这里是一些UGCTS通过对数据库操作的基本函数
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


// 取KSCTS数据库中的REAL_DONE表中的最大DONE_ID值 （被EOD调用）
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

// 函数名: DBFetchRDRecords
// 编程  : 陈永华 2011-9-20 0:27:41
// 描述  : 从证券交易系统数据库中读取属于FIX委托类型的成交记录和撤单记录
// 返回  : int : 返回读取的记录数
// 参数  : const char *sENTRUST_METHOD [IN]: 即交易系统内部记录在ENTRUST_METHOD的属于FIX委托的类型码 'f'
// 参数  : long *lastdoneid [IN/OUT]: 上次读到的最大DONE_ID序号，当<0的时候，即作为第一次，从头开始读
// 参数  : int cjxhry [IN]: DONE_ID的回退计数，宁可重复处理，防止遗漏
// 参数  : int cjsjry [IN]: RDONE_DATETIME的回退时间间隔，，宁可重复处理，防止遗漏
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
      // 是后续处理了的
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
         /* WITH UR;  ?? 那种好呢 ?? */
      
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
      *lastdoneid = 0;  // 表示后面不再是第一次了
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
   Commit(); // 管它三七二十一
   if (sqlcode!=NOTFOUND)
   {
      SQLDebugLog(40003,"PE:Fail to FETCH REAL_DONE from DONE_ID>%ld, SQLCODE=%d @ %s-%d",
         *lastdoneid,sqlcode,__FILE__,__LINE__);
   }
   return(n);
}

// 函数名: DBInsertFIXEntrust
// 编程  : 陈永华 2011-9-17 23:14:37
// 描述  : 将T_UGDATA内部的数据，插入到UGCTS的数据库FIX_BSORDERS表中
// 返回  : int <0: 插入失败；==0: 插入成功
// 参数  : T_UGDATA *pUGData [IN]: 插入数据
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


// 函数名: DBGetEntrustStatus
// 编程  : 陈永华 2011-9-18 10:18:50
// 描述  : 从KSCTS的ENTRUST表中查指定委托的数据，当返回为1的时候:
//          sSellSide = ENTRUST.MARKET_CODE;
//          sOrderID = ENTRUST.RPT_CONTRACT;
//          sOrdStatus = ENTRUST.ENTRUST_STATUS;
//          sExecInst = ENTRUST.EXCHANGE_ERR_CODE;
//          sAccount = ENTRUST.HOLDER_ACC_NO;
//          sClientID = ENTRUST.CUST_NO;
// 返回  : int -1: 失败，数据库异常(也有可能有多条); 
//             0: 没有找到指定委托记录；
//             1: 找到，并对pUGData中的上述数据进行修改
// 参数  : const char *sENTRUST_METHOD [IN]: KSCTS内部的委托方式，即g_KSCTS.m_WTFSi值
// 参数  : T_UGDATA *pUGData[IN/OUT]: 用pUGData->sOrigClOrdID作为委托合同号来指定委托记录；
//                   当返回1的时候，更改上述几个字段，但采用KSCTS的表示方式
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
      strcpy(ent_bs,"1%");  // 撤单类的BS
      strcpy(ent_method1,"4"); // 似乎是写死的，参见p130105.sql
   }
   else
   {
      strcpy(ent_bs,"0%");  // 原始委托类BS
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