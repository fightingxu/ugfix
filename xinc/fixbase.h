/********************************************************************
	created:	2009/07/03
	created:	3:7:2009   15:06
	filename: 	D:\projects\FIXII\2����\FIXServer\buinc\fixbase.h
	file path:	D:\projects\FIXII\2����\FIXServer\buinc
	file base:	fixbase
	file ext:	h
	author:		Yonghua.Chen
	
	purpose:	�����ǵ�����FIX��ʽ����Ϊ�ӿڵ�ʱ��������C����SQC������õ�
            һЩ���ú���
*********************************************************************/
#ifndef _FIXBASE_H_
#define _FIXBASE_H_

#ifndef C_SOH
#define C_SOH 0x01
#endif

enum FIX_TAGGROUP {
   TAG_Account=1,		/*2.TAG1 �ɶ�����*/
   TAG_SenderCompID=49,		/*6.TAG49 ���ͷ�ID*/
   TAG_TargetCompID=56,		/*7.TAG56 ���շ�ID*/
   TAG_MsgSeqNum=34,		/*19.TAG34 FIX ��Ϣ���*/
   TAG_CxlRejReason=102,		/*27.TAG102 �����ܾ�ԭ��*/
   TAG_OrdRejReason=103,		/*28.TAG103�����ܾ�ԭ�� */
   TAG_Price=44,		/*32.TAG44  ί�м۸�*/
   TAG_LastPx=31,		/*33.TAG31 ���γɽ��۸�*/
   TAG_AvgPx=6,		/*34.TAG6 ƽ���ɽ��۸�*/
   TAG_Commission=12,		/*35.TAG12 �ڻ���������*/
   TAG_OrderQty=38,		/*37.TAG38 ί������*/
   TAG_LastQty=32,		/*38.TAG32 ���γɽ�����*/
   TAG_LeavesQty=151,		/*39.TAG151 ʣ��δִ������*/
   TAG_CumQty=14,		/*40.TAG14 �ۼƳɽ���*/
   TAG_HandlInst=21,		/*68.TAG21 �������ͣ�Ŀǰ��1*/
   TAG_Side=54,		/*69.TAG54 �ͻ����2*/
   TAG_ExecTransType=20,		/*70.TAG20 �������ͱ�ʶ��*/
   TAG_TimeInForce=59,		/*72.TAG59  ί����ЧʱЧ*/
   TAG_CxlRejResponseTo=434,		/*73.TAG434 �����ܾ���Ӧ(1or2)*/
   TAG_ClOrdID=11,		/*89.TAG11 �ͻ�������ţ�Ψһ*/
   TAG_OrigClOrdID=41,		/*90.TAG41 �ͻ�ԭʼ�������*/
   TAG_OnBehalfOfSubID=116,		/*91.TAG116:Branch/Seat/PBU */
   TAG_DeliverToSubID=129,		/*92.TAG129:Seat/Branch */
   TAG_SvrTime=10101,		/*93.TAG10101:XSʱ�� */
   TAG_PriorLevel=10100,		/*94.TAG10100:�걨���ȼ� */
   TAG_MsgType=35,		/*95.TAG35 ��Ϣ����*/
   TAG_Symbol=55,		/*97.TAG 55 ����Ʒ��(֤ȯ)����*/
   TAG_ClientID=109,		/*99.TAG109 �ͻ��˻�(Լ��)*/
   TAG_TransactTime=60,		/*100.TAG60 UTC ��������ʱ��*/
   TAG_OrdStatus=39,		/*108.TAG39 ����״̬*/
   TAG_ExecType=150,		/*109.TAG150, ִ������*/
   TAG_BeginString=8,		/*118.TAG8 ��Ϣͷ��Э��汾��*/
   TAG_OnBehalfOfCompID=115,		/*119.TAG115 ��˾���(Buy Side)*/
   TAG_DeliverToCompID=128,		/*120.TAG128 ��˾���(Sell Side)*/
   TAG_NonTradingOrdType=8526,		/*125.TAG8526 �ǽ��׶������� */
   TAG_ExecID=17,		/*133.TAG17 ִ�б��*/
   TAG_OrdType=40,		/*139.TAG40 ��������*/
   TAG_OpenClose=77,		/*140.TAG77 ��ƽ��־���ڻ���*/
   TAG_Currency=15,		/*141.TAG15 ����*/
   TAG_SecurityExchange=207,		/*142.TAG207 ����������, Session��ͬ*/
   TAG_FgID=10000,		/*144.TAG10000: FIX Gateway �ı�ʶ��*/
   TAG_OrderID=37,		/*153.TAG37 SellSide���صĶ������*/
   TAG_TEXT=58,		      /*176.TAG58 TEXT*/
   TAG_PartyRole=453,
   TAG_PartyID=448,
   TAG_ListID=66,
   TAG_TotNoOrders=68,
   TAG_NoOrders=73,
   TAG_ListSeqNo=67,
   TAG_PossResend=97,
   TAG_ExpireTime=126,
   TAG_ExpireDate=432,
   TAG_Password=554,
   TAG_ExecInst=18,
   TAG_SecondaryExecID=527,
   TAG_CashOrderQty=152,
   TAG_SenderSubID=50,
   TAG_TargetSubID=57,
   TAG_SecurityID=48,
   TAG_IDSource=22,
   TAG_TargetStrategy=847,
   TAG_TargetStrategyParameters=848,
   TAG_SecondaryClOrdID=526,
   TAG_GrossTradeAmt=381,  // 2012/8/23 21:52:55 ��CumAmt
   //TAG_IOrderPK=10200      // 2012/7/24 0:17:45 ����ȡTP_IORDER��¼��ʱ����Ҫ�����Saved�ļ�¼��ȡ����ʽ�ύִ�е�ʱ����Ҫ
   TAG_SecType=10201,      // Ϊ�˷���UGATE�ڴ�������У��ܹ�ת��Ϊ��Ӧϵͳ���г��������ݣ�����NewOrderSingle���ṩ
};

#define MIN_QTY 0.00001

#ifndef BUDLL
#define BUPUB_API 
#else
#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _MSC_VER
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif
#endif

#ifdef _MSC_VER
#define SNPRINTF _snprintf
#else
#define SNPRINTF snprintf
#endif


#ifdef __cplusplus
extern "C" {
#endif


   // ������: FVString2FIXMsg
   // ���  : ������ 2009-8-19 16:13:16
   // ����  : 
   // ����  : int 
   // ����  : int tagid
   // ����  : const char *sFieldValue
   // ����  : char *fmbuf
   // ����  : int fmbsize
   BUPUB_API int FVString2FIXMsg(int tagid, const char *sFieldValue, char *fmbuf, int fmbsize);
   

   // ������: FVDouble2FIXMsg
   // ���  : ������ 2009-8-19 16:13:22
   // ����  : 
   // ����  : int 
   // ����  : int tagid
   // ����  : double dFieldValue
   // ����  : char *fmbuf
   // ����  : int fmbsize
   BUPUB_API int FVDouble2FIXMsg(int tagid, double dFieldValue, char *fmbuf, int fmbsize);
   
   // ���������BayClay Capital���ֲ��ܽ���Qty���͵���С����ʽ��ʾ��Ϊ�ˣ����Ǿ������´��� @ 2011-06-20
   BUPUB_API int FVQty2FIXMsg(int tagid, double dFieldValue, char *fmbuf, int fmbsize);

   // ������: FVInt2FIXMsg
   // ���  : ������ 2009-8-19 16:13:28
   // ����  : 
   // ����  : int 
   // ����  : int tagid
   // ����  : int iFieldValue
   // ����  : char *fmbuf
   // ����  : int fmbsize
   BUPUB_API int FVInt2FIXMsg(int tagid, int iFieldValue, char *fmbuf, int fmbsize);


#define FD_INVALIDHANDLE   -1000
#define FD_SETDATAERR      -1001

typedef void * FIXDATAHANDLE;

// ������Ϊ����C��SQC�������CFIXData��������FIX��ʽ����Ϣ������Ҫ

// ���  : ������ 2009-7-3 15:15:09
// ����  : new һ��CFIXData���Ա���ú���������ʹ��
// ����  : FIXDATAHANDLE : ����new CFIXData�󷵻ص�ָ�룻NULL - ����ʧ��
// ����  : void
BUPUB_API FIXDATAHANDLE FIXDataNew(void);


// ���  : ������ 2009-7-3 15:16:59
// ����  : delete ����FIXDataNew��õ�CFIXData���ʵ��
// ����  : void 
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ������Ҫ�ͷ�
BUPUB_API void FIXDataDelete(FIXDATAHANDLE h);


// ������: FIXDataReset
// ���  : ������ 2009-7-3 15:26:33
// ����  : 
// ����  : int 
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��
// ����  : const char *sBeginString [IN] : Tag8, ��Ϣ�İ汾�ű�ʶ�룬���򲻴���
// ����  : const char *sSenderCompID [IN] : Tag49, ��Ϣ���ͷ������򲻴���
// ����  : const char *sTargetCompID [IN] : Tag56, ��Ϣ���շ������򲻴���
BUPUB_API int FIXDataReset(FIXDATAHANDLE h,const char *sBeginString,const char *sSenderCompID,const char *sTargetCompID);


// ������: FIXDataSetData
// ���  : ������ 2009-7-3 15:56:15
// ����  : ��fix��ʽ����Ϣ�������õ�FIXData������ֵ
// ����  : int >=0: OK; <0: false 
// ����  : FIXDATAHANDLE h [IN/OUT]:  ͨ��FIXDataNew��õľ��
// ����  : const char *fixdata [IN]: fix��ʽ����Ϣ���� 
// ����  : int length [IN]: fixdata����Ϣ���ȣ�<=0���ʾfixdata���� '\0'�����ġ�
BUPUB_API int FIXDataSetData(FIXDATAHANDLE h,const char *fixdata, int length);


// ������: FIXDataAddTag
// ���  : ������ 2009-7-3 16:22:59
// ����  : ��������һ����ǩtag��ֵ
// ����  : int ���ؼ����ǩ�����tag_no, <0 : ���ʾ���󣺲ο�FIXDATA_ERRCODES��
// ����  : FIXDATAHANDLE h[IN/OUT]:  ͨ��FIXDataNew��õľ��
// ����  : int tag [IN]: �����FIXTag��tag��ǩ
// ����  : const char *tvalue[IN]: tag��ǩ��ֵ
// ����  : int vlen [IN]: tag��ǩ��ֵ�ĳ��ȣ�<=0: ���ʾ��ֵΪԭʼ�ַ���?��ɺ����ڲ�����ֵ�õ����?
BUPUB_API int FIXDataAddTag(FIXDATAHANDLE h,int tag, const char *tvalue, int vlen);



// ������: FIXDataGetTagCount
// ���  : ������ 2009-7-3 16:26:40
// ����  : ��ȡ��FIXData�е�FIXTag�ĸ���
// ����  : int 
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��
BUPUB_API int FIXDataGetTagCount(FIXDATAHANDLE h);



// ������: FIXDataGetTagNo
// ���  : ������ 2009-7-3 16:52:59
// ����  : ��ȡָ����ǩ���tag_no��FIXTag����Ϣ
// ����  : int >=0: �ɹ�������tag_no��<0: ʧ�� �ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
// ����  : int tag_no [IN]: ��ǩ���
// ����  : int *tag [OUT]: ��ǩ��tag
// ����  : char *tvalue [OUT]: �ṩ��ǩֵ��ſռ䣬���ر�ǩֵ��tvalue==NULL: ���ʾ���÷��ظ�ֵ
// ����  : int *vlen [IN/OUT]: IN tvalue����ռ䳤�ȣ�<=0��ʾ�㹻��OUT: tvalue�з���FIXTagֵ���ֽ���
BUPUB_API int FIXDataGetTagNo(FIXDATAHANDLE h, int tag_no, int *tag, char *tvalue, int *vlen);



// ������: FIXDataGetTag
// ���  : ������ 2009-7-3 16:56:26
// ����  : ���ݱ�ǩ��tagֵ��ȡ��һ�����ָñ�ǩ��ֵ
// ����  : int >=0: �ɹ������ر�ǩ���tag_no��<0: ʧ�� �ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
// ����  : int tag [IN]: ��ǩ��tag
// ����  : char *tvalue [OUT]: �ṩ��ǩֵ��ſռ䣬���ر�ǩֵ, ����ΪNULL
// ����  : int *vlen[IN/OUT]: IN tvalue����ռ䳤�ȣ�<=0��ʾ�㹻��OUT: tvalue�з���FIXTagֵ���ֽ���
BUPUB_API int FIXDataGetTag(FIXDATAHANDLE h, int tag, char *tvalue, int *vlen);


// ������: FIXDataGetTagNext
// ���  : ������ 2009-7-6 10:48:28
// ����  : ��tag_no0�ĺ��濪ʼ����tagΪtag���Ǹ�������������Ϣ
//          ��������������ڻ�ȡGroup ��Component Item��Tagֵ������������һ��ͬTag�ķ���ֵΪtag_no0����ú���һ��ͬTag��ֵ
// ����  : int  >=0: ���ض�Ӧ��tag��ţ�<0: û���ҵ����ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
// ����  : int tag_no0 [IN]: ���λ�ã���ʼ��tag_no0+1��tag��ʼ����; ��СΪ-1(��һ��),...
// ����  : int tag [IN]: Ҫ��ȡ��tag
// ����  : char *tvalue [OUT]: tagֵ�Ļ���
// ����  : int *vlen [IN/OUT]:  IN: tvalue�Ļ����ֽ�����OUT: ��õ�tvalue����Ч����
BUPUB_API int FIXDataGetTagNext(FIXDATAHANDLE h, int tag_no0, int tag, char *tvalue, int *vlen);


// ������: FIXDataGetGroupTagNext
// ���  : ������ 2009-7-6 12:19:34
// ����  : �Ӵ�tag_no0�ĺ��濪ʼ��Component Group����ָ�����no��tag��ֵ
// ����  : int   >=0: ���ض�Ӧ��tag��ţ�<0: û���ҵ����ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
// ����  : int tag_no0 [IN]: ���λ�ã���ʼ��tag_no0+1��tag��ʼ����; ��СΪ-1. ��Group���͵�ʱ�򣬱���������ΪNoXXX����������Ǹ�tagλ��
// ����  : int tag [IN]: Ҫ��ȡ��tag
// ����  : int no [IN]: ָ������ţ���0(����һ��)��ʼ...
// ����  : char *tvalue [OUT]: tagֵ�Ļ���
// ����  : int *vlen [IN/OUT]:  IN: tvalue�Ļ����ֽ���, ���϶����ᳬ�������ֱ�Ӹ�ֵΪ-1��OUT: ��õ�tvalue����Ч����
BUPUB_API int FIXDataGetGroupTagNext(FIXDATAHANDLE h, int tag_no0, int tag, int no, char *tvalue, int *vlen);


// ������: FIXDataUpdateTag
// ���  : ������ 2009-7-3 17:05:52
// ����  : �޸�ָ���ı�ǩ����
// ����  : int ���ؼ����ǩ�����tag_no, <0 : ���ʾ���󣺲ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
// ����  : int tag_no [IN]: �޸ĵ�FIXTag�ı�ǩ��ţ���tag_no<0, �����tagֵ�滻��һ������tag�ı�ǩ���ݣ�����(����)׷�������
// ����  : int tag [IN]: �޸ĵ�FIXTag��tag��ǩ
// ����  : const char *tvalue [IN]: tag��ǩ��ֵ
// ����  : int tvlen [IN]: tag��ǩ��ֵ�ĳ��ȣ�<=0: ���ʾ��ֵΪԭʼ�ַ������ɺ����ڲ�����ֵ�õ�����
BUPUB_API int FIXDataUpdateTag(FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue, int tvlen);


// ������: FIXDataGetFIXData
// ���  : ������ 2009-7-3 17:09:42
// ����  : ��ȡ�Ѿ������˵�������FIXDATA���ݴ�
// ����  : int : ����fixdata���صĴ�����Ч����
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataAddTag��FIXDataUpdateTag��?��?
// ����  : char *fixdata [OUT]: ���FIXDATA���صĸ�ʽ����FIX���ݴ�
// ����  : int fdsize [IN]: fixdata����ĳ���
BUPUB_API int FIXDataGetFIXData(FIXDATAHANDLE h, char *fixdata, int fdsize);


// ������: FIXDataRemoveTagNo
// ���  : ������ 2009-7-3 17:15:17
// ����  : ȥ��ָ����Tag��
// ����  : int >=0: �ɹ������ص�ǰ��tag�������<0: �ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
// ����  : int tag_no [IN]: ָ����Tag����
BUPUB_API int FIXDataRemoveTagNo(FIXDATAHANDLE h, int tag_no);


// ������: FIXDataRemoveTag
// ���  : ������ 2009-7-3 17:15:20
// ����  : ȥ����һ�����ֵ�ָ��tag��
// ����  : int >=0: �ɹ������ص�ǰ��tag�������<0: �ο�FIXDATA_ERRCODES
// ����  : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ�
// ����  : int tag: ָ����Tag��
BUPUB_API int FIXDataRemoveTag(FIXDATAHANDLE h, int tag);

/***********************************************************************************
*����:�����ֶμ���
*����:char *Source-����, char *Key-��Կ
*���أ�
*     1���ɹ�
*     0��ʧ��
***********************************************************************************/
BUPUB_API int PwdEncode(char *Source, const char *Key);

/***********************************************************************************
*����:�����ֶν���
*����:char *Source-����, char *Key-��Կ
*���أ�
*     1���ɹ�
*     0��ʧ��
***********************************************************************************/
BUPUB_API int PwdDncode(char *Source, const char *Key);


//////////////////////////////////////////////////////////////////////////

// Function name: FDUpdateTagString
// Author       : CHENYH 2012/4/26 16:56:34
// Description  : 
// Return type	: int 
// Argument : FIXDATAHANDLE h : �����µ�FIXData���
// Argument : int tag_no: �����µ�tag��FIXData�е���ţ�<0 - �Զ��滻��һ������tag���ֶ�
// Argument : int tag: ָ����tag��ǩ
// Argument : const char *tvalue: �����õ�tagֵ
BUPUB_API int FDUpdateTagString(FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue);

BUPUB_API int FDUpdateTagDouble(FIXDATAHANDLE h, int tag_no, int tag, double tvalue);

BUPUB_API int FDUpdateTagQty(FIXDATAHANDLE h, int tag_no, int tag, double qty);

BUPUB_API int FDUpdateTagInt(FIXDATAHANDLE h, int tag_no, int tag, int tvalue);

#ifdef __cplusplus
}
#endif

#undef BUPUB_API

#endif
