/********************************************************************
	created:	2011/09/15
	created:	15:9:2011   16:51
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\UGDBFuncs.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	UGDBFuncs
	file ext:	h
	author:		CHENYH
	
	purpose:	这里是用ESQL提供的基本功能清单
      但是由于ESQL不支持线程安全，因此需要经过特别封装后，方可提供
      给具体功能使用。
*********************************************************************/
#ifndef UGDBFuncs_h__
#define UGDBFuncs_h__
#include "busqc.h"
#include "ugate.h"  // 这里需要T_UGDATA结构
#include "ugcts2di.hxx"

#ifndef NOTFOUND
#define NOTFOUND 100
#endif

typedef struct _T_REAL_DONE T_REAL_DONE;

#ifdef __cplusplus
extern "C" {
#endif
   
   // 在CJThread.cpp中实现的，用于缓存，等读取完毕后，由CJThread去逐条处理这些成交记录
   void HaveDBRealDone(T_REAL_DONE *pRealDone);
   
#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
extern "C" {
#endif

   // 取KSCTS数据库中的REAL_DONE表中的最大DONE_ID值 （被EOD调用）
   int DBGetLastMaxDoneID(long *lastdoneid);


   // 函数名: DBInsertFIXEntrust
   // 编程  : 陈永华 2011-9-17 23:14:37
   // 描述  : 将T_UGDATA内部的数据，插入到UGCTS的数据库FIX_BSORDERS表中
   // 返回  : int <0: 失败；否则成功 
   // 参数  : T_UGDATA *pUGData [IN]: 需要插入到FIX_BSORDERS表中的数据
   int DBInsertFIXEntrust(T_UGDATA *pUGData);

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
   int DBGetEntrustStatus(const char *sENTRUST_BRANCH,const char *sENTRUST_METHOD, T_UGDATA *pUGData);

   
   // 函数名: DBFetchRDRecords
   // 编程  : 陈永华 2011-9-20 0:27:41
   // 描述  : 从证券交易系统数据库中读取属于FIX委托类型的成交记录和撤单记录
   // 返回  : int : 返回读取的记录数
   // 参数  : const char *sENTRUST_METHOD [IN]: 即交易系统内部记录在ENTRUST_METHOD的属于FIX委托的类型码 'f'
   // 参数  : long *lastdoneid [IN/OUT]: 上次读到的最大DONE_ID序号，当<0的时候，即作为第一次，从头开始读
   // 参数  : int cjxhry [IN]: DONE_ID的回退计数，宁可重复处理，防止遗漏
   // 参数  : int cjsjry [IN]: RDONE_DATETIME的回退时间间隔，，宁可重复处理，防止遗漏
   int DBFetchRDRecords(const char *sENTRUST_BRANCH,const char *sENTRUST_METHOD, long *lastdoneid, int cjxhry, int cjsjry);

#ifdef __cplusplus
}
#endif

#endif // UGDBFuncs_h__