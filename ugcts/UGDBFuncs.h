/********************************************************************
	created:	2011/09/15
	created:	15:9:2011   16:51
	filename: 	C:\dd\projects\FIXIII\UGate\ugcts\UGDBFuncs.h
	file path:	C:\dd\projects\FIXIII\UGate\ugcts
	file base:	UGDBFuncs
	file ext:	h
	author:		CHENYH
	
	purpose:	��������ESQL�ṩ�Ļ��������嵥
      ��������ESQL��֧���̰߳�ȫ�������Ҫ�����ر��װ�󣬷����ṩ
      �����幦��ʹ�á�
*********************************************************************/
#ifndef UGDBFuncs_h__
#define UGDBFuncs_h__
#include "busqc.h"
#include "ugate.h"  // ������ҪT_UGDATA�ṹ
#include "ugcts2di.hxx"

#ifndef NOTFOUND
#define NOTFOUND 100
#endif

typedef struct _T_REAL_DONE T_REAL_DONE;

#ifdef __cplusplus
extern "C" {
#endif
   
   // ��CJThread.cpp��ʵ�ֵģ����ڻ��棬�ȶ�ȡ��Ϻ���CJThreadȥ����������Щ�ɽ���¼
   void HaveDBRealDone(T_REAL_DONE *pRealDone);
   
#ifdef __cplusplus
}
#endif



#ifdef __cplusplus
extern "C" {
#endif

   // ȡKSCTS���ݿ��е�REAL_DONE���е����DONE_IDֵ ����EOD���ã�
   int DBGetLastMaxDoneID(long *lastdoneid);


   // ������: DBInsertFIXEntrust
   // ���  : ������ 2011-9-17 23:14:37
   // ����  : ��T_UGDATA�ڲ������ݣ����뵽UGCTS�����ݿ�FIX_BSORDERS����
   // ����  : int <0: ʧ�ܣ�����ɹ� 
   // ����  : T_UGDATA *pUGData [IN]: ��Ҫ���뵽FIX_BSORDERS���е�����
   int DBInsertFIXEntrust(T_UGDATA *pUGData);

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
   int DBGetEntrustStatus(const char *sENTRUST_BRANCH,const char *sENTRUST_METHOD, T_UGDATA *pUGData);

   
   // ������: DBFetchRDRecords
   // ���  : ������ 2011-9-20 0:27:41
   // ����  : ��֤ȯ����ϵͳ���ݿ��ж�ȡ����FIXί�����͵ĳɽ���¼�ͳ�����¼
   // ����  : int : ���ض�ȡ�ļ�¼��
   // ����  : const char *sENTRUST_METHOD [IN]: ������ϵͳ�ڲ���¼��ENTRUST_METHOD������FIXί�е������� 'f'
   // ����  : long *lastdoneid [IN/OUT]: �ϴζ��������DONE_ID��ţ���<0��ʱ�򣬼���Ϊ��һ�Σ���ͷ��ʼ��
   // ����  : int cjxhry [IN]: DONE_ID�Ļ��˼����������ظ�������ֹ��©
   // ����  : int cjsjry [IN]: RDONE_DATETIME�Ļ���ʱ�������������ظ�������ֹ��©
   int DBFetchRDRecords(const char *sENTRUST_BRANCH,const char *sENTRUST_METHOD, long *lastdoneid, int cjxhry, int cjsjry);

#ifdef __cplusplus
}
#endif

#endif // UGDBFuncs_h__