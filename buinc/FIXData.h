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
  8	BeginString		      Y	��ʼ��STEP.1.0.0 (���ɼ��ܣ���Ϣ�ĵ�һ����)
  9	BodyLength		      Y	��Ϣ�峤��(���ɼ��ܣ���Ϣ�ĵڶ�����)
 35	MsgType		         Y	��Ϣ����(���ɼ��ܣ���Ϣ�ĵ�������)
 49	SenderCompID		   Y	���ͷ�����(���ɼ��ܣ����ͷ���ʶ��)
 56	TargetCompID		   Y	���շ�����(���ɼ��ܣ����շ���ʶ��)
115	OnBehalfOfCompID		N	������ͷ���ʶ�����ɼ��ܣ������ھ����������͡�
128	DeliverToCompID		N	���ս��շ���ʶ�����ɼ��ܣ������ھ����������͡�
 90	SecureDataLen		   N	�������ݳ���
 91	SecureData		      N	�������ݣ������������ݳ�����
 34	MsgSeqNum		      Y	��Ϣ��ţ��ɼ��ܣ�
 50	SenderSubID		      N	���ͷ��ӱ�ʶ�����ɼ��ܣ�
142	SenderLocationID		N	���ͷ���λ��ʶ�����ɼ��ܣ�
 57	TargetSubID		      N	���շ��ӱ�ʶ�����ɼ��ܣ�
143	TargetLocationID		N	���շ���λ��ʶ�����ɼ��ܣ�
116	OnBehalfOfSubID		N	������ͷ��ӱ�ʶ�����ɼ��ܣ�
144	OnBehalfOfLocationID		N	������ͷ���λ��ʶ�����ɼ��ܣ�
129	DeliverToSubID		      N	���ս��շ��ӱ�ʶ�����ɼ��ܣ�
145	DeliverToLocationID		N	���ս��շ���λ��ʶ�����ɼ��ܣ�
 43	PossDupFlag		      N	�����ظ���־���ظ�����ʱ�����˱�ǡ����ɼ��ܣ�
 97	PossResend		      N	�����ط���־�����ɼ��ܣ�
 52	SendingTime		      Y	����ʱ�䣨�ɼ��ܣ�
122	OrigSendingTime		N	ԭʼ����ʱ�䣨�ɼ��ܣ�
347	MessageEncoding		N	��Ϣ��Encoded����ַ��������ͣ���ASCII�룩
369	LastMsgSeqNumProcessed		N	�������Ϣ��ţ��ɼ��ܣ�
370	OnBehalfOfSendingTime		N	�������ʱ�䣨��UTC��ʾʱ�䣩
627	NoHops		         N	��ʷ��Ծ��Ϣ�ظ��飬��¼��Ϣ�����������͵���ʷ��ÿ�ξ�����������Ϊһ����Ծ������OnBehalfOfCompIDʹ��ʱ��Ч����Ҫ���ڸ�����Ϣ��·����
   628	HopCompID	      N	����ȡֵ��������SenderCompID
   629	HopSendingTime	   N	����ȡֵ�õ�������SendingTime
   630	HopRefID	         N	����ȡֵ��������MsgSeqNum

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
   --  ���ⲿ�ֵĸ�ʽת��������Ӧ�÷������������ - ���ݿ���ת����Щ̫������
   TDT_INT,       // Extend: Length, NumInGroup, SeqNum
   TDT_DAYOFMONTH,   // 1-31
   TDT_FLOAT,     // Extend: Qty, Price, PriceOffset, Amt, Percentage
   TDT_CHAR,      // one character
   TDT_BOOLEAN,   // 'Y' or 'N'
   TDT_MONTHYEAR, // YYYYMM��YYYYMMDD��YYYYMMWW��YYYY = 0000-9999, MM = 01-12��DD = 01-31��WW = w1,w2,w3,w4,w5��
   TDT_LMDATE,    // Local Market Date -  YYYYMMDD
   TDT_TZTIME,    // TZTimeOnly - HH:MM:SS[.sss]
   TDT_TZTIMESTAMP,  // TZTimeStamp: YYYYMMDD-HH:MM:SS[.sss]
   TDT_UTCTIME,   // UTCTimeOnly - HH:MM:SS[.sss]
   TDT_UTCDATE,   // UTCDateOnly - YYYYMMDD
   TDT_UTCTIMESTAMP, // UTCTimeStamp - YYYYMMDD-HH:MM:SS[.sss]
   TDT_MVSTRING,  // Multiple Value String: with ' '
   TDT_COUNTRY,   // GB/T 2659   ���ձ� collate table
   TDT_CURRENCY,  // GB/T 12406  ���ձ� collate table
   TDT_EXCHANGE,  // ISO 10383   ���ձ� collate table
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
   ST_FIXTAG *m_Tags; // [MAXTAGS];  ���ö�̬���룬�Լ���ȫ�ֻ��ջ�ռ�ռ��, ��ǰ��Ч�ֶζ�������
   int   m_iLastP;   // ��ǰ���õ����һ������λ��
   char *m_FIXData;  // [MAXFIXDATALENGTH]; ���ö�̬���룬�Լ���ȫ�ֻ��ջ�ռ�ռ��, �����tag�������ݣ�������tag�ͷָ��

public:
	int FilterNonASC();


	double GetTagD(int tag);
   // ��ԭʼ��FIXData�����ϣ���Ӻ�����fixdata���ֵ���Ϣ���ݣ�fixdataΪ <TAG>=<VALUE><SOH>...���ַ�����Ϣ�������ð���TAG10�Ĳ���
	bool AddData(const char *fixdata, int length=0, T_REJECTMSG *rejmsg=NULL);

   // ��֤��FIXData�Ƿ����FIX�����淶
	bool Valid(const char *fixmsg, T_REJECTMSG *pRejMsg=NULL);

	INT8 GetTagI8(int tag);
	int GetTagI(int tag);
	int AddTag(int tag, long ltvalue);
	int AddTag(int tag, INT8 tvi8);
	int AddTag(int tag, unsigned int utvalue);
	int AddTag(int tag, int itvalue);
	int AddTag(int tag, double dtvalue, unsigned int dec=3);
	int AddTag(int tag, char ctvalue);


   // ������: GetGroupTagNext
   // ���  : ������ 2009-7-6 12:11:24
   // ����  : �Ӵ�tag_no0�ĺ��濪ʼ��Component Group����ָ�����no��tag��ֵ
   // ����  : int  >=0: ���ض�Ӧ��tag��ţ�<0: û���ҵ����ο�FIXDATA_ERRCODES
   // ����  : int tag_no0 [IN]: ���λ�ã���ʼ��tag_no0+1��tag��ʼ����; ��СΪ-1. ��Group���͵�ʱ�򣬱���������ΪNoXXX����������Ǹ�tagλ��
   // ����  : int tag [IN]: Ҫ��ȡ��tag
   // ����  : int no [IN]: ָ������ţ���0(����һ��)��ʼ...
   // ����  : char *tvalue [OUT]: tagֵ�Ļ���
   // ����  : int &vlen [IN/OUT]:  IN: tvalue�Ļ����ֽ�����OUT: ��õ�tvalue����Ч����
	int GetGroupTagNext(int tag_no0, int tag, int no, char *tvalue, int &vlen);

   // ������: RemoveTag
   // ���  : ������ 2009-3-24 13:53:17
   // ����  : ȥ����һ�����ֵ�ָ��tag��
   // ����  : int >=0: �ɹ������ص�ǰ��tag�������<0: �ο�FIXDATA_ERRCODES
   // ����  : int tag[IN]: ָ����Tag��
	int RemoveTag(int tag);

   // ������: RemoveTagNo
   // ���  : ������ 2009-3-24 13:51:22
   // ����  : ȥ��ָ����Tag��
   // ����  : int >=0: �ɹ������ص�ǰ��tag�������<0: �ο�FIXDATA_ERRCODES
   // ����  : int tagno [IN]: ָ����Tag����
	int RemoveTagNo(int tagno);


   // ������: GetStdFIXMessage
   // ���  : ������ 2009-3-24 13:49:04
   // ����  : �õ���׼��ʽ��FIX��Ϣ����
   // ����  : int ��Ϣ���ݵĳ���
   // ����  : char *fixdata [OUT]: ��Ϣ���ݻ���
   // ����  : int datasize=MAXFIXDATALENGTH [IN]: ��Ϣ����ĳ���
   // ����  : const char *sBeginString=NULL: ָ��BeginString
	int GetStdFIXMessage(char *fixdata, int datasize=MAXFIXDATALENGTH,const char *sBeginString=NULL);

   // ������: GetTagNext
   // ���  : ������ 2009-3-24 13:43:06
   // ����  : ��tag_no0�ĺ��濪ʼ����tagΪtag���Ǹ�������������Ϣ
   //          ��������������ڻ�ȡGroup ��Component Item��Tagֵ������������һ��ͬTag�ķ���ֵΪtag_no0����ú���һ��ͬTag��ֵ
   // ����  : int >=0: ���ض�Ӧ��tag��ţ�<0: û���ҵ����ο�FIXDATA_ERRCODES
   // ����  : int tag_no0 [IN]: ���λ�ã���ʼ��tag_no0+1��tag��ʼ����; ��СΪ-1,0,...
   // ����  : int tag [IN]: Ҫ��ȡ��tag
   // ����  : char *tvalue [OUT]: tagֵ�Ļ���
   // ����  : int &vlen [IN/OUT]:  IN: tvalue�Ļ����ֽ�����OUT: ��õ�tvalue����Ч����
	int GetTagNext(int tag_no0, int tag, char *tvalue, int &vlen);

   // ������: GetFIXData
   // ���  : ������ 2008-1-16 18:43:53
   // ����  : ��ȡ������FIXDATA���ݴ�
   // ����  : int : ����fixdata���صĴ�����Ч����
   // ����  : char *fixdata [OUT]: ���FIXDATA���صĸ�ʽ����FIX���ݴ�
   // ����  : int fdsize [IN]: fixdata����ĳ���
	int GetFIXData(char *fixdata, int fdsize);

   // ������: GetTag
   // ���  : ������ 2008-1-16 17:09:03
   // ����  : ���ݱ�ǩ��tagֵ��ȡ��һ�����ָñ�ǩ��ֵ
   // ����  : int >=0: �ɹ������ر�ǩ���tag_no��<0: ʧ�� �ο�FIXDATA_ERRCODES
   //          -1: error at tag_no - tag_no<0 or tag_no>=m_Tags.size()
   //          -2: no enough room of 'tvalue' to load value
   //          -3: no this tag
   // ����  : int tag [IN]: ��ǩ��tag
   // ����  : char *tvalue [OUT]: �ṩ��ǩֵ��ſռ䣬���ر�ǩֵ, ����ΪNULL
   // ����  : int &vlen[IN/OUT]: IN tvalue����ռ䳤�ȣ�<=0��ʾ�㹻��OUT: tvalue�з���FIXTagֵ���ֽ���
	int GetTag(int tag, char *tvalue, int &vlen);

   // ������: GetTag
   // ���  : ������ 2008-1-16 14:24:37
   // ����  : ��ȡָ����ǩ���tag_no��FIXTag����Ϣ
   // ����  : int >=0: �ɹ�������tag_no��<0: ʧ�� �ο�FIXDATA_ERRCODES
   //          -1: error at tag_no - tag_no<0 or tag_no>=m_Tags.size()
   //          -2: no enough room of 'tvalue' to load value
   // ����  : int tag_no [IN]: ��ǩ���
   // ����  : int &tag [OUT]: ��ǩ��tag
   // ����  : char *tvalue [OUT]: �ṩ��ǩֵ��ſռ䣬���ر�ǩֵ��tvalue==NULL: ���ʾ���÷��ظ�ֵ
   // ����  : int &vlen [IN/OUT]: IN tvalue����ռ䳤�ȣ�<=0��ʾ�㹻��OUT: tvalue�з���FIXTagֵ���ֽ���
	int GetTag(int tag_no, int &tag, char *tvalue, int &vlen);

   // ������: GetTagCount
   // ���  : ������ 2008-1-16 14:22:07
   // ����  : ��ȡ��FIXData�е�FIXTag�ĸ���
   // ����  : int 
	int GetTagCount();

   // ������: UpdateTag
   // ���  : ������ 2008-1-16 17:14:11
   // ����  : �޸�ָ���ı�ǩ����
   // ����  : int ���ؼ����ǩ�����tag_no, <0 : ���ʾ���󣺲ο�FIXDATA_ERRCODES
   //          // FIXData overflow : -4 
   //          // illegal value of the tag : -5
   // ����  : int tag_no [IN]: �޸ĵ�FIXTag�ı�ǩ��ţ���tag_no<0, �����tagֵ�滻��һ������tag�ı�ǩ���ݣ�����(����)׷�������
   // ����  : int tag [IN]: �޸ĵ�FIXTag��tag��ǩ
   // ����  : const char *tvalue [IN]: tag��ǩ��ֵ
   // ����  : int  tvlen=0 [IN]: tag��ǩ��ֵ�ĳ��ȣ�<=0: ���ʾ��ֵΪԭʼ�ַ������ɺ����ڲ�����ֵ�õ�����
   int UpdateTag(int tag_no, int tag, const char *tvalue, int  tvlen=0);
   
   // ������: AddTag
   // ���  : ������ 2008-1-16 14:13:29
   // ����  : ��������һ����ǩ
   // ����  : int ���ؼ����ǩ�����tag_no, <0 : ���ʾ���󣺲ο�FIXDATA_ERRCODES
   //          // FIXData overflow : -4 
   //          // illegal value of the tag : -5
   // ����  : int tag [IN]: �����FIXTag��tag��ǩ
   // ����  : const char *tvalue [IN]: tag��ǩ��ֵ
   // ����  : int vlen [IN]: tag��ǩ��ֵ�ĳ��ȣ�<=0: ���ʾ��ֵΪԭʼ�ַ������ɺ����ڲ�����ֵ�õ�����
	int AddTag(int tag, const char *tvalue, int vlen=0);

   // ������: SetData
   // ���  : ������ 2008-1-16 14:07:19
   // ����  : ����FIXData������ֵ
   // ����  : bool 
   // ����  : const char *fixdata [IN]: FIXData ������ֵ����
   //          ��: 8=FIX.4.4<SOH>9=158<SOH>35=D<SOH>49=TARGET0<SOH>56=SENDER0<SOH>34=36<SOH>52=20071211-03:17:23.947<SOH>11=ClOrdId<SOH>21=C<SOH>55=symbol<SOH>54=2<SOH>40=3<SOH>60=20020425-09:19:23.063<SOH>10=019<SOH>
   // ����  : int length [IN]: fixdata���ֽڳ���
	bool SetData(const char *fixdata, int length, T_REJECTMSG *rejmsg=NULL);

   // ������: Reset
   // ���  : ������ 2008-1-16 14:06:54
   // ����  : ��ձ�FIXData�ڲ������ݣ�����д��ΪFIX��Ϣ�Ĺؼ�Tag
   // ����  : int 
   // ����  : char *sBeginString [IN] : Tag8, ��Ϣ�İ汾�ű�ʶ�룬���򲻴���
   // ����  : char *sSenderCompID [IN] : Tag49, ��Ϣ���ͷ�
   // ����  : char *sTargetCompID [IN] : Tag56, ��Ϣ���շ�
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
