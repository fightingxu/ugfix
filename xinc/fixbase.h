/********************************************************************
	created:	2009/07/03
	created:	3:7:2009   15:06
	filename: 	D:\projects\FIXII\2编码\FIXServer\buinc\fixbase.h
	file path:	D:\projects\FIXII\2编码\FIXServer\buinc
	file base:	fixbase
	file ext:	h
	author:		Yonghua.Chen
	
	purpose:	这里是当采用FIX格式来作为接口的时候，用于让C或者SQC代码调用的
            一些常用函数
*********************************************************************/
#ifndef _FIXBASE_H_
#define _FIXBASE_H_

#ifndef C_SOH
#define C_SOH 0x01
#endif

enum FIX_TAGGROUP {
   TAG_Account=1,		/*2.TAG1 股东代码*/
   TAG_SenderCompID=49,		/*6.TAG49 发送方ID*/
   TAG_TargetCompID=56,		/*7.TAG56 接收方ID*/
   TAG_MsgSeqNum=34,		/*19.TAG34 FIX 消息序号*/
   TAG_CxlRejReason=102,		/*27.TAG102 撤单拒绝原因*/
   TAG_OrdRejReason=103,		/*28.TAG103订单拒绝原因 */
   TAG_Price=44,		/*32.TAG44  委托价格*/
   TAG_LastPx=31,		/*33.TAG31 本次成交价格*/
   TAG_AvgPx=6,		/*34.TAG6 平均成交价格*/
   TAG_Commission=12,		/*35.TAG12 期货的手续费*/
   TAG_OrderQty=38,		/*37.TAG38 委托数量*/
   TAG_LastQty=32,		/*38.TAG32 本次成交数量*/
   TAG_LeavesQty=151,		/*39.TAG151 剩余未执行数量*/
   TAG_CumQty=14,		/*40.TAG14 累计成交量*/
   TAG_HandlInst=21,		/*68.TAG21 定单类型，目前填1*/
   TAG_Side=54,		/*69.TAG54 客户类别2*/
   TAG_ExecTransType=20,		/*70.TAG20 交易类型标识符*/
   TAG_TimeInForce=59,		/*72.TAG59  委托有效时效*/
   TAG_CxlRejResponseTo=434,		/*73.TAG434 撤单拒绝相应(1or2)*/
   TAG_ClOrdID=11,		/*89.TAG11 客户订单编号，唯一*/
   TAG_OrigClOrdID=41,		/*90.TAG41 客户原始订单编号*/
   TAG_OnBehalfOfSubID=116,		/*91.TAG116:Branch/Seat/PBU */
   TAG_DeliverToSubID=129,		/*92.TAG129:Seat/Branch */
   TAG_SvrTime=10101,		/*93.TAG10101:XS时间 */
   TAG_PriorLevel=10100,		/*94.TAG10100:申报优先级 */
   TAG_MsgType=35,		/*95.TAG35 消息类型*/
   TAG_Symbol=55,		/*97.TAG 55 交易品种(证券)代码*/
   TAG_ClientID=109,		/*99.TAG109 客户账户(约定)*/
   TAG_TransactTime=60,		/*100.TAG60 UTC 格林威治时间*/
   TAG_OrdStatus=39,		/*108.TAG39 订单状态*/
   TAG_ExecType=150,		/*109.TAG150, 执行类型*/
   TAG_BeginString=8,		/*118.TAG8 消息头和协议版本号*/
   TAG_OnBehalfOfCompID=115,		/*119.TAG115 公司编号(Buy Side)*/
   TAG_DeliverToCompID=128,		/*120.TAG128 公司编号(Sell Side)*/
   TAG_NonTradingOrdType=8526,		/*125.TAG8526 非交易订单类型 */
   TAG_ExecID=17,		/*133.TAG17 执行编号*/
   TAG_OrdType=40,		/*139.TAG40 订单类型*/
   TAG_OpenClose=77,		/*140.TAG77 开平标志（期货）*/
   TAG_Currency=15,		/*141.TAG15 币种*/
   TAG_SecurityExchange=207,		/*142.TAG207 交易所代码, Session不同*/
   TAG_FgID=10000,		/*144.TAG10000: FIX Gateway 的标识码*/
   TAG_OrderID=37,		/*153.TAG37 SellSide返回的订单序号*/
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
   TAG_GrossTradeAmt=381,  // 2012/8/23 21:52:55 即CumAmt
   //TAG_IOrderPK=10200      // 2012/7/24 0:17:45 在提取TP_IORDER记录的时候需要，如从Saved的记录提取后，正式提交执行的时候需要
   TAG_SecType=10201,      // 为了方便UGATE在处理过程中，能够转换为对应系统的市场类型数据，而在NewOrderSingle中提供
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


   // 函数名: FVString2FIXMsg
   // 编程  : 陈永华 2009-8-19 16:13:16
   // 描述  : 
   // 返回  : int 
   // 参数  : int tagid
   // 参数  : const char *sFieldValue
   // 参数  : char *fmbuf
   // 参数  : int fmbsize
   BUPUB_API int FVString2FIXMsg(int tagid, const char *sFieldValue, char *fmbuf, int fmbsize);
   

   // 函数名: FVDouble2FIXMsg
   // 编程  : 陈永华 2009-8-19 16:13:22
   // 描述  : 
   // 返回  : int 
   // 参数  : int tagid
   // 参数  : double dFieldValue
   // 参数  : char *fmbuf
   // 参数  : int fmbsize
   BUPUB_API int FVDouble2FIXMsg(int tagid, double dFieldValue, char *fmbuf, int fmbsize);
   
   // 由于申万的BayClay Capital对手不能接收Qty类型的以小数方式表示，为此，我们就做如下处理 @ 2011-06-20
   BUPUB_API int FVQty2FIXMsg(int tagid, double dFieldValue, char *fmbuf, int fmbsize);

   // 函数名: FVInt2FIXMsg
   // 编程  : 陈永华 2009-8-19 16:13:28
   // 描述  : 
   // 返回  : int 
   // 参数  : int tagid
   // 参数  : int iFieldValue
   // 参数  : char *fmbuf
   // 参数  : int fmbsize
   BUPUB_API int FVInt2FIXMsg(int tagid, int iFieldValue, char *fmbuf, int fmbsize);


#define FD_INVALIDHANDLE   -1000
#define FD_SETDATAERR      -1001

typedef void * FIXDATAHANDLE;

// 如下是为了让C或SQC代码调用CFIXData类来操作FIX格式的消息数据需要

// 编程  : 陈永华 2009-7-3 15:15:09
// 描述  : new 一个CFIXData，以便调用后续函数的使用
// 返回  : FIXDATAHANDLE : 返回new CFIXData后返回的指针；NULL - 调用失败
// 参数  : void
BUPUB_API FIXDATAHANDLE FIXDataNew(void);


// 编程  : 陈永华 2009-7-3 15:16:59
// 描述  : delete 调用FIXDataNew获得的CFIXData类的实例
// 返回  : void 
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄，需要释放
BUPUB_API void FIXDataDelete(FIXDATAHANDLE h);


// 函数名: FIXDataReset
// 编程  : 陈永华 2009-7-3 15:26:33
// 描述  : 
// 返回  : int 
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄
// 参数  : const char *sBeginString [IN] : Tag8, 消息的版本号标识码，空则不处理
// 参数  : const char *sSenderCompID [IN] : Tag49, 消息发送方，空则不处理
// 参数  : const char *sTargetCompID [IN] : Tag56, 消息接收方，空则不处理
BUPUB_API int FIXDataReset(FIXDATAHANDLE h,const char *sBeginString,const char *sSenderCompID,const char *sTargetCompID);


// 函数名: FIXDataSetData
// 编程  : 陈永华 2009-7-3 15:56:15
// 描述  : 将fix格式的消息数据设置到FIXData的数据值
// 返回  : int >=0: OK; <0: false 
// 参数  : FIXDATAHANDLE h [IN/OUT]:  通过FIXDataNew获得的句柄
// 参数  : const char *fixdata [IN]: fix格式的消息数据 
// 参数  : int length [IN]: fixdata的消息长度，<=0则表示fixdata是以 '\0'结束的。
BUPUB_API int FIXDataSetData(FIXDATAHANDLE h,const char *fixdata, int length);


// 函数名: FIXDataAddTag
// 编程  : 陈永华 2009-7-3 16:22:59
// 描述  : 在最后添加一个标签tag和值
// 返回  : int 返回加入标签的序号tag_no, <0 : 则表示错误：参考FIXDATA_ERRCODES等
// 参数  : FIXDATAHANDLE h[IN/OUT]:  通过FIXDataNew获得的句柄
// 参数  : int tag [IN]: 加入的FIXTag的tag标签
// 参数  : const char *tvalue[IN]: tag标签的值
// 参数  : int vlen [IN]: tag标签的值的长度，<=0: 则表示该值为原始字符串?珊诓扛葜档玫匠ざ?
BUPUB_API int FIXDataAddTag(FIXDATAHANDLE h,int tag, const char *tvalue, int vlen);



// 函数名: FIXDataGetTagCount
// 编程  : 陈永华 2009-7-3 16:26:40
// 描述  : 获取本FIXData中的FIXTag的个数
// 返回  : int 
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄
BUPUB_API int FIXDataGetTagCount(FIXDATAHANDLE h);



// 函数名: FIXDataGetTagNo
// 编程  : 陈永华 2009-7-3 16:52:59
// 描述  : 获取指定标签序号tag_no的FIXTag的信息
// 返回  : int >=0: 成功，返回tag_no；<0: 失败 参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
// 参数  : int tag_no [IN]: 标签序号
// 参数  : int *tag [OUT]: 标签的tag
// 参数  : char *tvalue [OUT]: 提供标签值存放空间，返回标签值，tvalue==NULL: 则表示不用返回该值
// 参数  : int *vlen [IN/OUT]: IN tvalue缓存空间长度，<=0表示足够大；OUT: tvalue中返回FIXTag值的字节数
BUPUB_API int FIXDataGetTagNo(FIXDATAHANDLE h, int tag_no, int *tag, char *tvalue, int *vlen);



// 函数名: FIXDataGetTag
// 编程  : 陈永华 2009-7-3 16:56:26
// 描述  : 根据标签的tag值获取第一个出现该标签的值
// 返回  : int >=0: 成功，返回标签序号tag_no；<0: 失败 参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
// 参数  : int tag [IN]: 标签的tag
// 参数  : char *tvalue [OUT]: 提供标签值存放空间，返回标签值, 不能为NULL
// 参数  : int *vlen[IN/OUT]: IN tvalue缓存空间长度，<=0表示足够大；OUT: tvalue中返回FIXTag值的字节数
BUPUB_API int FIXDataGetTag(FIXDATAHANDLE h, int tag, char *tvalue, int *vlen);


// 函数名: FIXDataGetTagNext
// 编程  : 陈永华 2009-7-6 10:48:28
// 描述  : 从tag_no0的后面开始查找tag为tag的那个，并获得相关信息
//          这个方法可以用于获取Group 的Component Item的Tag值，即基于上面一个同Tag的返回值为tag_no0，获得后面一个同Tag的值
// 返回  : int  >=0: 返回对应的tag序号；<0: 没有找到，参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
// 参数  : int tag_no0 [IN]: 相对位置，开始从tag_no0+1的tag开始查找; 最小为-1(第一个),...
// 参数  : int tag [IN]: 要获取的tag
// 参数  : char *tvalue [OUT]: tag值的缓存
// 参数  : int *vlen [IN/OUT]:  IN: tvalue的缓存字节数；OUT: 获得的tvalue的有效长度
BUPUB_API int FIXDataGetTagNext(FIXDATAHANDLE h, int tag_no0, int tag, char *tvalue, int *vlen);


// 函数名: FIXDataGetGroupTagNext
// 编程  : 陈永华 2009-7-6 12:19:34
// 描述  : 从从tag_no0的后面开始的Component Group中找指定序号no的tag的值
// 返回  : int   >=0: 返回对应的tag序号；<0: 没有找到，参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
// 参数  : int tag_no0 [IN]: 相对位置，开始从tag_no0+1的tag开始查找; 最小为-1. 在Group类型的时候，本参数常常为NoXXX的组项个数那个tag位置
// 参数  : int tag [IN]: 要获取的tag
// 参数  : int no [IN]: 指定的序号，从0(即第一个)开始...
// 参数  : char *tvalue [OUT]: tag值的缓存
// 参数  : int *vlen [IN/OUT]:  IN: tvalue的缓存字节数, 若肯定不会超出则可以直接赋值为-1；OUT: 获得的tvalue的有效长度
BUPUB_API int FIXDataGetGroupTagNext(FIXDATAHANDLE h, int tag_no0, int tag, int no, char *tvalue, int *vlen);


// 函数名: FIXDataUpdateTag
// 编程  : 陈永华 2009-7-3 17:05:52
// 描述  : 修改指定的标签内容
// 返回  : int 返回加入标签的序号tag_no, <0 : 则表示错误：参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
// 参数  : int tag_no [IN]: 修改的FIXTag的标签序号，当tag_no<0, 则根据tag值替换第一个出现tag的标签内容，或者(无则)追加在最后
// 参数  : int tag [IN]: 修改的FIXTag的tag标签
// 参数  : const char *tvalue [IN]: tag标签的值
// 参数  : int tvlen [IN]: tag标签的值的长度，<=0: 则表示该值为原始字符串，由函数内部根据值得到长度
BUPUB_API int FIXDataUpdateTag(FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue, int tvlen);


// 函数名: FIXDataGetFIXData
// 编程  : 陈永华 2009-7-3 17:09:42
// 描述  : 获取已经设置了的完整的FIXDATA数据串
// 返回  : int : 返回fixdata返回的串的有效长度
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataAddTag或FIXDataUpdateTag等?僮?
// 参数  : char *fixdata [OUT]: 存放FIXDATA返回的格式化的FIX数据串
// 参数  : int fdsize [IN]: fixdata缓存的长度
BUPUB_API int FIXDataGetFIXData(FIXDATAHANDLE h, char *fixdata, int fdsize);


// 函数名: FIXDataRemoveTagNo
// 编程  : 陈永华 2009-7-3 17:15:17
// 描述  : 去掉指定的Tag域
// 返回  : int >=0: 成功，返回当前总tag域个数；<0: 参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
// 参数  : int tag_no [IN]: 指定的Tag域编号
BUPUB_API int FIXDataRemoveTagNo(FIXDATAHANDLE h, int tag_no);


// 函数名: FIXDataRemoveTag
// 编程  : 陈永华 2009-7-3 17:15:20
// 描述  : 去掉第一个发现的指定tag域
// 返回  : int >=0: 成功，返回当前总tag域个数；<0: 参考FIXDATA_ERRCODES
// 参数  : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操
// 参数  : int tag: 指定的Tag域
BUPUB_API int FIXDataRemoveTag(FIXDATAHANDLE h, int tag);

/***********************************************************************************
*功能:密码字段加密
*输入:char *Source-数据, char *Key-密钥
*返回：
*     1：成功
*     0：失败
***********************************************************************************/
BUPUB_API int PwdEncode(char *Source, const char *Key);

/***********************************************************************************
*功能:密码字段解密
*输入:char *Source-数据, char *Key-密钥
*返回：
*     1：成功
*     0：失败
***********************************************************************************/
BUPUB_API int PwdDncode(char *Source, const char *Key);


//////////////////////////////////////////////////////////////////////////

// Function name: FDUpdateTagString
// Author       : CHENYH 2012/4/26 16:56:34
// Description  : 
// Return type	: int 
// Argument : FIXDATAHANDLE h : 被更新的FIXData句柄
// Argument : int tag_no: 被更新的tag在FIXData中的序号，<0 - 自动替换第一个属于tag的字段
// Argument : int tag: 指定的tag标签
// Argument : const char *tvalue: 新设置的tag值
BUPUB_API int FDUpdateTagString(FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue);

BUPUB_API int FDUpdateTagDouble(FIXDATAHANDLE h, int tag_no, int tag, double tvalue);

BUPUB_API int FDUpdateTagQty(FIXDATAHANDLE h, int tag_no, int tag, double qty);

BUPUB_API int FDUpdateTagInt(FIXDATAHANDLE h, int tag_no, int tag, int tvalue);

#ifdef __cplusplus
}
#endif

#undef BUPUB_API

#endif
