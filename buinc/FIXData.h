// FIXData.h: interface for the CFIXData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXDATA_H__4F856A31_3D27_4847_8C9C_0DCE95793F36__INCLUDED_)
#define AFX_FIXDATA_H__4F856A31_3D27_4847_8C9C_0DCE95793F36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef C_SOH
#define C_SOH 0x01
#endif

/* ****** Updated by CHENYH at 2007-12-12 10:18:21 ****** 
Tag	Ftag	FieldName	   Need	Specification
  8	BeginString		      Y	起始串STEP.1.0.0 (不可加密，消息的第一个域)
  9	BodyLength		      Y	消息体长度(不可加密，消息的第二个域)
 35	MsgType		         Y	消息类型(不可加密，消息的第三个域)
 49	SenderCompID		   Y	发送方代码(不可加密，发送方标识符)
 56	TargetCompID		   Y	接收方代码(不可加密，接收方标识符)
115	OnBehalfOfCompID		N	最初发送方标识符（可加密），用于经第三方发送。
128	DeliverToCompID		N	最终接收方标识符（可加密），用于经第三方发送。
 90	SecureDataLen		   N	密文数据长度
 91	SecureData		      N	密文数据（紧跟密文数据长度域）
 34	MsgSeqNum		      Y	消息序号（可加密）
 50	SenderSubID		      N	发送方子标识符（可加密）
142	SenderLocationID		N	发送方方位标识符（可加密）
 57	TargetSubID		      N	接收方子标识符（可加密）
143	TargetLocationID		N	接收方方位标识符（可加密）
116	OnBehalfOfSubID		N	最初发送方子标识符（可加密）
144	OnBehalfOfLocationID		N	最初发送方方位标识符（可加密）
129	DeliverToSubID		      N	最终接收方子标识符（可加密）
145	DeliverToLocationID		N	最终接收方方位标识符（可加密）
 43	PossDupFlag		      N	可能重复标志，重复发送时，作此标记。（可加密）
 97	PossResend		      N	可能重发标志。（可加密）
 52	SendingTime		      Y	发送时间（可加密）
122	OrigSendingTime		N	原始发送时间（可加密）
347	MessageEncoding		N	消息中Encoded域的字符编码类型（非ASCII码）
369	LastMsgSeqNumProcessed		N	最后处理消息序号（可加密）
370	OnBehalfOfSendingTime		N	最初发送时间（用UTC表示时间）
627	NoHops		         N	历史跳跃信息重复组，记录消息经第三方发送的历史，每次经第三方发送为一个跳跃，仅当OnBehalfOfCompID使用时有效，主要用于跟踪消息的路径。
   628	HopCompID	      N	建议取值第三方的SenderCompID
   629	HopSendingTime	   N	建议取值用第三方的SendingTime
   630	HopRefID	         N	建议取值第三方的MsgSeqNum

212 XmlDataLen            N     Required when specifying XmlData to identify the length of a XmlData message block. (Can be embedded within encrypted data section.) 
213 XmlData               N     Can contain a XML formatted message block (e.g. FIXML). Always immediately follows XmlDataLen field. (Can be embedded within encrypted data section.) See Volume 1: FIXML Support 


--------------------------------------------------------------------
Standard Trailer 

Tag Field Name             Req'd Comments 
 93 SignatureLength        N     Required when trailer contains signature. Note: Not to be included within SecureData field 
 89 Signature              N     Note: Not to be included within SecureData field 
 10 CheckSum               Y     (Always unencrypted, always last field in message) 
      
***********************************************************/


enum TAGDATATYPES
{
   TDT_STRING,    // Normal String
/* ****** Updated by CHENYH at 2007-12-12 15:52:44 ****** 
   --  将这部分的格式转换，交给应用服务器部分完成 - 数据库中转换这些太容易了
   TDT_INT,       // Extend: Length, NumInGroup, SeqNum
   TDT_DAYOFMONTH,   // 1-31
   TDT_FLOAT,     // Extend: Qty, Price, PriceOffset, Amt, Percentage
   TDT_CHAR,      // one character
   TDT_BOOLEAN,   // 'Y' or 'N'
   TDT_MONTHYEAR, // YYYYMM或YYYYMMDD或YYYYMMWW，YYYY = 0000-9999, MM = 01-12，DD = 01-31，WW = w1,w2,w3,w4,w5。
   TDT_LMDATE,    // Local Market Date -  YYYYMMDD
   TDT_TZTIME,    // TZTimeOnly - HH:MM:SS[.sss]
   TDT_TZTIMESTAMP,  // TZTimeStamp: YYYYMMDD-HH:MM:SS[.sss]
   TDT_UTCTIME,   // UTCTimeOnly - HH:MM:SS[.sss]
   TDT_UTCDATE,   // UTCDateOnly - YYYYMMDD
   TDT_UTCTIMESTAMP, // UTCTimeStamp - YYYYMMDD-HH:MM:SS[.sss]
   TDT_MVSTRING,  // Multiple Value String: with ' '
   TDT_COUNTRY,   // GB/T 2659   对照表 collate table
   TDT_CURRENCY,  // GB/T 12406  对照表 collate table
   TDT_EXCHANGE,  // ISO 10383   对照表 collate table
*********************************************************/
   TDT_DATA       // Data block.
};

struct T_REJECTMSG
{
   int RefSeqNum;
   int RefTagID;
   char RefMsgType[8];
   int SessionRejectReason;
   char Text[256];
};


extern int g_LengthTags[];

typedef struct _ST_FIXTAG
{
   int tag;
   int length;
   int offset;
} ST_FIXTAG;


//#define MAXFIXDATALENGTH 10240
#define MAXFIXDATALENGTH 8192  


enum FIXDATA_ERRCODES
{
   FDE_INVILIDTAGNO  =-1,
   FDE_NOENOUGHROOM  =-2,
   FDE_NOTAG         =-3,
   FDE_OVERFLOW      =-4,
   FDE_INVILIDVALUE  =-5,
   FDE_TOOMANYTAG    =-6,

   FDE_RESETERR      =-100
};

#define MAXTAGS 1024

#ifdef _MSC_VER
#define INT8 __int64
#else 
#define INT8 long long
#endif

inline void SETREJMSG(T_REJECTMSG *rejmsg,int rseqnum,int rtagid,const char *rmsgtype,int reason,const char *text) 
{
   if (rejmsg==NULL)
      return;
   rejmsg->RefSeqNum = rseqnum;
   rejmsg->RefTagID = rtagid;
   strncpy(rejmsg->RefMsgType,rmsgtype,sizeof(rejmsg->RefMsgType));
   rejmsg->SessionRejectReason = reason;
   if (rejmsg->Text != text)
      strncpy(rejmsg->Text,text,sizeof(rejmsg->Text));
}

class CFIXData  
{
public:
private:
   int   m_iLastTag;
   ST_FIXTAG *m_Tags; // [MAXTAGS];  采用动态申请，以减少全局或堆栈空间占用, 当前有效字段定义索引
   int   m_iLastP;   // 当前可用的最后一个数据位置
   char *m_FIXData;  // [MAXFIXDATALENGTH]; 采用动态申请，以减少全局或堆栈空间占用, 纯粹的tag数据内容，不包括tag和分割符

public:
	int FilterNonASC();


	double GetTagD(int tag);
   // 在原始的FIXData基础上，添加后续的fixdata部分的消息内容，fixdata为 <TAG>=<VALUE><SOH>...的字符串消息，但不用包括TAG10的部分
	bool AddData(const char *fixdata, int length=0, T_REJECTMSG *rejmsg=NULL);

   // 验证本FIXData是否符合FIX基本规范
	bool Valid(const char *fixmsg, T_REJECTMSG *pRejMsg=NULL);

	INT8 GetTagI8(int tag);
	int GetTagI(int tag);
	int AddTag(int tag, long ltvalue);
	int AddTag(int tag, INT8 tvi8);
	int AddTag(int tag, unsigned int utvalue);
	int AddTag(int tag, int itvalue);
	int AddTag(int tag, double dtvalue, unsigned int dec=3);
	int AddTag(int tag, char ctvalue);


   // 函数名: GetGroupTagNext
   // 编程  : 陈永华 2009-7-6 12:11:24
   // 描述  : 从从tag_no0的后面开始的Component Group中找指定序号no的tag的值
   // 返回  : int  >=0: 返回对应的tag序号；<0: 没有找到，参考FIXDATA_ERRCODES
   // 参数  : int tag_no0 [IN]: 相对位置，开始从tag_no0+1的tag开始查找; 最小为-1. 在Group类型的时候，本参数常常为NoXXX的组项个数那个tag位置
   // 参数  : int tag [IN]: 要获取的tag
   // 参数  : int no [IN]: 指定的序号，从0(即第一个)开始...
   // 参数  : char *tvalue [OUT]: tag值的缓存
   // 参数  : int &vlen [IN/OUT]:  IN: tvalue的缓存字节数；OUT: 获得的tvalue的有效长度
	int GetGroupTagNext(int tag_no0, int tag, int no, char *tvalue, int &vlen);

   // 函数名: RemoveTag
   // 编程  : 陈永华 2009-3-24 13:53:17
   // 描述  : 去掉第一个发现的指定tag域
   // 返回  : int >=0: 成功，返回当前总tag域个数；<0: 参考FIXDATA_ERRCODES
   // 参数  : int tag[IN]: 指定的Tag域
	int RemoveTag(int tag);

   // 函数名: RemoveTagNo
   // 编程  : 陈永华 2009-3-24 13:51:22
   // 描述  : 去掉指定的Tag域
   // 返回  : int >=0: 成功，返回当前总tag域个数；<0: 参考FIXDATA_ERRCODES
   // 参数  : int tagno [IN]: 指定的Tag域编号
	int RemoveTagNo(int tagno);


   // 函数名: GetStdFIXMessage
   // 编程  : 陈永华 2009-3-24 13:49:04
   // 描述  : 得到标准格式的FIX消息数据
   // 返回  : int 消息数据的长度
   // 参数  : char *fixdata [OUT]: 消息数据缓存
   // 参数  : int datasize=MAXFIXDATALENGTH [IN]: 消息缓存的长度
   // 参数  : const char *sBeginString=NULL: 指定BeginString
	int GetStdFIXMessage(char *fixdata, int datasize=MAXFIXDATALENGTH,const char *sBeginString=NULL);

   // 函数名: GetTagNext
   // 编程  : 陈永华 2009-3-24 13:43:06
   // 描述  : 从tag_no0的后面开始查找tag为tag的那个，并获得相关信息
   //          这个方法可以用于获取Group 的Component Item的Tag值，即基于上面一个同Tag的返回值为tag_no0，获得后面一个同Tag的值
   // 返回  : int >=0: 返回对应的tag序号；<0: 没有找到，参考FIXDATA_ERRCODES
   // 参数  : int tag_no0 [IN]: 相对位置，开始从tag_no0+1的tag开始查找; 最小为-1,0,...
   // 参数  : int tag [IN]: 要获取的tag
   // 参数  : char *tvalue [OUT]: tag值的缓存
   // 参数  : int &vlen [IN/OUT]:  IN: tvalue的缓存字节数；OUT: 获得的tvalue的有效长度
	int GetTagNext(int tag_no0, int tag, char *tvalue, int &vlen);

   // 函数名: GetFIXData
   // 编程  : 陈永华 2008-1-16 18:43:53
   // 描述  : 获取完整的FIXDATA数据串
   // 返回  : int : 返回fixdata返回的串的有效长度
   // 参数  : char *fixdata [OUT]: 存放FIXDATA返回的格式化的FIX数据串
   // 参数  : int fdsize [IN]: fixdata缓存的长度
	int GetFIXData(char *fixdata, int fdsize);

   // 函数名: GetTag
   // 编程  : 陈永华 2008-1-16 17:09:03
   // 描述  : 根据标签的tag值获取第一个出现该标签的值
   // 返回  : int >=0: 成功，返回标签序号tag_no；<0: 失败 参考FIXDATA_ERRCODES
   //          -1: error at tag_no - tag_no<0 or tag_no>=m_Tags.size()
   //          -2: no enough room of 'tvalue' to load value
   //          -3: no this tag
   // 参数  : int tag [IN]: 标签的tag
   // 参数  : char *tvalue [OUT]: 提供标签值存放空间，返回标签值, 不能为NULL
   // 参数  : int &vlen[IN/OUT]: IN tvalue缓存空间长度，<=0表示足够大；OUT: tvalue中返回FIXTag值的字节数
	int GetTag(int tag, char *tvalue, int &vlen);

   // 函数名: GetTag
   // 编程  : 陈永华 2008-1-16 14:24:37
   // 描述  : 获取指定标签序号tag_no的FIXTag的信息
   // 返回  : int >=0: 成功，返回tag_no；<0: 失败 参考FIXDATA_ERRCODES
   //          -1: error at tag_no - tag_no<0 or tag_no>=m_Tags.size()
   //          -2: no enough room of 'tvalue' to load value
   // 参数  : int tag_no [IN]: 标签序号
   // 参数  : int &tag [OUT]: 标签的tag
   // 参数  : char *tvalue [OUT]: 提供标签值存放空间，返回标签值，tvalue==NULL: 则表示不用返回该值
   // 参数  : int &vlen [IN/OUT]: IN tvalue缓存空间长度，<=0表示足够大；OUT: tvalue中返回FIXTag值的字节数
	int GetTag(int tag_no, int &tag, char *tvalue, int &vlen);

   // 函数名: GetTagCount
   // 编程  : 陈永华 2008-1-16 14:22:07
   // 描述  : 获取本FIXData中的FIXTag的个数
   // 返回  : int 
	int GetTagCount();

   // 函数名: UpdateTag
   // 编程  : 陈永华 2008-1-16 17:14:11
   // 描述  : 修改指定的标签内容
   // 返回  : int 返回加入标签的序号tag_no, <0 : 则表示错误：参考FIXDATA_ERRCODES
   //          // FIXData overflow : -4 
   //          // illegal value of the tag : -5
   // 参数  : int tag_no [IN]: 修改的FIXTag的标签序号，当tag_no<0, 则根据tag值替换第一个出现tag的标签内容，或者(无则)追加在最后
   // 参数  : int tag [IN]: 修改的FIXTag的tag标签
   // 参数  : const char *tvalue [IN]: tag标签的值
   // 参数  : int  tvlen=0 [IN]: tag标签的值的长度，<=0: 则表示该值为原始字符串，由函数内部根据值得到长度
   int UpdateTag(int tag_no, int tag, const char *tvalue, int  tvlen=0);
   
   // 函数名: AddTag
   // 编程  : 陈永华 2008-1-16 14:13:29
   // 描述  : 在最后添加一个标签
   // 返回  : int 返回加入标签的序号tag_no, <0 : 则表示错误：参考FIXDATA_ERRCODES
   //          // FIXData overflow : -4 
   //          // illegal value of the tag : -5
   // 参数  : int tag [IN]: 加入的FIXTag的tag标签
   // 参数  : const char *tvalue [IN]: tag标签的值
   // 参数  : int vlen [IN]: tag标签的值的长度，<=0: 则表示该值为原始字符串，由函数内部根据值得到长度
	int AddTag(int tag, const char *tvalue, int vlen=0);

   // 函数名: SetData
   // 编程  : 陈永华 2008-1-16 14:07:19
   // 描述  : 设置FIXData的数据值
   // 返回  : bool 
   // 参数  : const char *fixdata [IN]: FIXData 的数据值串，
   //          如: 8=FIX.4.4<SOH>9=158<SOH>35=D<SOH>49=TARGET0<SOH>56=SENDER0<SOH>34=36<SOH>52=20071211-03:17:23.947<SOH>11=ClOrdId<SOH>21=C<SOH>55=symbol<SOH>54=2<SOH>40=3<SOH>60=20020425-09:19:23.063<SOH>10=019<SOH>
   // 参数  : int length [IN]: fixdata的字节长度
	bool SetData(const char *fixdata, int length, T_REJECTMSG *rejmsg=NULL);

   // 函数名: Reset
   // 编程  : 陈永华 2008-1-16 14:06:54
   // 描述  : 清空本FIXData内部的数据，并填写作为FIX消息的关键Tag
   // 返回  : int 
   // 参数  : char *sBeginString [IN] : Tag8, 消息的版本号标识码，空则不处理
   // 参数  : char *sSenderCompID [IN] : Tag49, 消息发送方
   // 参数  : char *sTargetCompID [IN] : Tag56, 消息接收方
	int Reset(const char *sBeginString=NULL,const char *sSenderCompID=NULL,const char *sTargetCompID=NULL);
	
	CFIXData();
	CFIXData(CFIXData const& copyData);
	virtual ~CFIXData();

private:
	int iGetTag(int tag_no, int &tag, char *tvalue, int &vlen);
   int ReverseGetIntValue(int tagid);

};

unsigned int GetFIXCheckSum(const char *buf, int bufLen);

int FIXGetTag(CFIXData *pFIXData, int tag, char *tvalue, int tvlen);
#define FIXGETTAG(fixdata,tag,stvalue) FIXGetTag(&fixdata,tag,stvalue,sizeof(stvalue))

#endif // !defined(AFX_FIXDATA_H__4F856A31_3D27_4847_8C9C_0DCE95793F36__INCLUDED_)
