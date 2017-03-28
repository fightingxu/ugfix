// FIXData.cpp: implementation of the CFIXData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FIXData.h"


// 这个函数只是为了能够支持宏定义FIXGETTAG用
int FIXGetTag(CFIXData *pFIXData, int tag, char *tvalue, int tvlen)
{
   return(pFIXData->GetTag(tag,tvalue,tvlen));
}


/*
8	BeginString	Y	FIX.4.4 (Always unencrypted, must be first field in message)
9	BodyLength	Y	(Always unencrypted, must be second field in message)
35	MsgType	Y	(Always unencrypted, must be third field in message)
49	SenderCompID	Y	(Always unencrypted)
56	TargetCompID	Y	(Always unencrypted)
115	OnBehalfOfCompID	N	Trading partner company ID used when sending messages via a third party (Can be embedded within encrypted data section.)
128	DeliverToCompID	N	Trading partner company ID used when sending messages via a third party (Can be embedded within encrypted data section.)
90	SecureDataLen	N	Required to identify length of encrypted section of message. (Always unencrypted)  
91	SecureData	N	Required when message body is encrypted.  Always immediately follows SecureDataLen field.
34	MsgSeqNum	Y	(Can be embedded within encrypted data section.)
50	SenderSubID	N	(Can be embedded within encrypted data section.)
142	SenderLocationID	N	Sender's LocationID (i.e. geographic location and/or desk) (Can be embedded within encrypted data section.)
57	TargetSubID	N	"ADMIN" reserved for administrative messages not intended for a specific user. (Can be embedded within encrypted data section.)
143	TargetLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) (Can be embedded within encrypted data section.)
116	OnBehalfOfSubID	N	Trading partner SubID used when delivering messages via a third party. (Can be embedded within encrypted data section.)
144	OnBehalfOfLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) used when delivering messages via a third party. (Can be embedded within encrypted data section.)
129	DeliverToSubID	N	Trading partner SubID used when delivering messages via a third party. (Can be embedded within encrypted data section.)
145	DeliverToLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) used when delivering messages via a third party. (Can be embedded within encrypted data section.)
43	PossDupFlag	N	Always required for retransmitted messages, whether prompted by the sending system or as the result of a resend request. (Can be embedded within encrypted data section.)
97	PossResend	N	Required when message may be duplicate of another message sent under a different sequence number. (Can be embedded within encrypted data section.)
52	SendingTime	Y	(Can be embedded within encrypted data section.)
122	OrigSendingTime	N	Required for message resent as a result of a ResendRequest.  If data is not available set to same value as SendingTime  (Can be embedded within encrypted data section.)
212	XmlDataLen	N	Required when specifying XmlData to identify the length of a XmlData message block. (Can be embedded within encrypted data section.)
213	XmlData	N	Can contain a XML formatted message block (e.g. FIXML).   Always immediately follows XmlDataLen field. (Can be embedded within encrypted data section.)
See Volume 1: FIXML Support
347	MessageEncoding	N	Type of message encoding (non-ASCII characters) used in a message's "Encoded" fields.  Required if any "Encoding" fields are used.
369	LastMsgSeqNumProcessed	N	The last MsgSeqNum value received by the FIX engine and processed by downstream application, such as trading system or order routing system.  Can be specified on every message sent.  Useful for detecting a backlog with a counterparty.
627	NoHops	N	Number of repeating groups of historical "hop" information.  Only applicable if OnBehalfOfCompID is used, however, its use is optional.  Note that some market regulations or counterparties may require tracking of message hops.
'	628	HopCompID	N	Third party firm which delivered a specific message either from the firm which originated the message or from another third party (if multiple "hops" are performed). It is recommended that this value be the SenderCompID (49) of the third party.
'	629	HopSendingTime	N	Time that HopCompID (628) sent the message. It is recommended that this value be the SendingTime (52) of the message sent by the third party.
'	630	HopRefID	N	Reference identifier assigned by HopCompID (628) associated with the message sent. It is recommended that this value be the MsgSeqNum (34) of the message sent by the third party.
*/


#ifdef FIXDATA_TEST
const char *FIXBasicTestMsg="8=FIX.4.2\0019=0223\00135=D\00134=1264\00152=20090319-06:57:30\00150=SUNGARDHK\00157=SUNGARDSH\00156=SUNGARDSH\00149=SUNGARDHK\00111=000000003801\00155=600000\00138=200\00154=1\0011=A000000111\00140=2\00159=0\00144=11.070000\00121=1\00160=20090319-06:57:30\001109=00240111\001207=SS\00148=600000\00115=RMB\00110=109\001";

void Test1()
{
   CFIXData fd;
   char dFIXMsg[MAXFIXDATALENGTH];
   int msglen;
   printf("SFIXMsg:%s\n",FIXBasicTestMsg);
   msglen = strlen(FIXBasicTestMsg);
   fd.SetData(FIXBasicTestMsg,msglen);
   msglen = fd.GetStdFIXMessage(dFIXMsg,sizeof(dFIXMsg),NULL);
   printf("DFIXMsg:%s\n",dFIXMsg);
}



void Test2()
{
   CFIXData fd;
   char dFIXMsg[MAXFIXDATALENGTH];
   int msglen;
   printf("SFIXMsg:%s\n",FIXBasicTestMsg);
   msglen = strlen(FIXBasicTestMsg);
   fd.SetData(FIXBasicTestMsg,msglen);
   int tagno;
   int flen=-1;
   tagno = fd.GetTag(50,dFIXMsg,flen);
   printf("[50=%s]->SUNGARD\n",dFIXMsg);
   assert(tagno>=0);
   fd.UpdateTag(tagno,50,"SUNGARD");
   fd.UpdateTag(-1,8,"FIX.4.4");
   fd.RemoveTag(109);  // 删除这个在FIX.4.2中使用的值
   fd.AddTag(453,"3");
   fd.AddTag(448,"A123456789");
   fd.AddTag(447,"5");
   fd.AddTag(452,"5");
   fd.AddTag(448,"SYWG");
   fd.AddTag(447,"12");
   fd.AddTag(452,"D");
   fd.AddTag(448,"00J95");
   fd.AddTag(447,"1");
   fd.AddTag(452,"C");
   flen = sizeof(dFIXMsg);
   tagno = fd.GetTag(453,dFIXMsg,flen);
   assert(tagno>=0);
   printf("453=%s\n",dFIXMsg);
   int i,n;
   n = atoi(dFIXMsg);
   int tn448;
   int tn447;
   int tn452;
   tn448=tn447=tn452=tagno;
   for (i=0;i<n;i++)
   {
      flen = sizeof(dFIXMsg);
      tn448 = fd.GetTagNext(tn448,448,dFIXMsg,flen);
      printf("%d 448=%s",i,dFIXMsg);
      flen = sizeof(dFIXMsg);
      tn447 = fd.GetTagNext(tn447,447,dFIXMsg,flen);
      printf(" 447=%s",dFIXMsg);
      flen = sizeof(dFIXMsg);
      tn452 = fd.GetTagNext(tn452,452,dFIXMsg,flen);
      printf(" 452=%s\n",dFIXMsg);
   }
   msglen = fd.GetStdFIXMessage(dFIXMsg,sizeof(dFIXMsg),NULL);
   printf("DFIXMsg:%s\n",dFIXMsg);
}

int main(void)
{
   // 先测试基本的读取各个TAG的方式
   Test1();
   // 测试设置基本数据消息，然后修改几个TAG和添加几个TAG值，最后再获取标准FIX消息串
   Test2();
   return(0);
}

#endif

//#define BLENGTHCHARS 7 // 9=xxxx|
bool IsBodyTag(int tag)
{
   if (tag==8
      ||tag==9
      ||tag==10)
      return(false);
   else
      return(true);
}

unsigned int GetFIXCheckSum(const char *buf, int bufLen)
{
   int idx;
   unsigned int cks;
   
   for(idx=0, cks = 0; idx < bufLen; cks += (unsigned int)buf[idx++] );
   return(cks&0xFF);
}


static struct T_VLTAGPAIR
{
   int lenTag;
   int targetTag;
} g_VLTagPairs[]=
{
   {90,91},      // SecureDataLen, SecureData
   {93,89},      // SignatureLength
   {95,96},      // RawDataLength
   {212,213},     // XmlDataLen
   {348,349},     // EncodedIssuerLen
   {350,351},     // EncodedSecurityDescLen
   {352,353},     // EncodedListExecInstLen
   {354,355},     // EncodedTextLen
   {356,357},	   // EncodedSubjectLen
   {358,359},	   // EncodedHeadlineLen
   {360,361},	   // EncodedAllocTextLen
   {362,363},	   // EncodedUnderlyingIssuerLen
   {364,365},     // EncodedUnderlyingSecurityDescLen
   {445,446},     // EncodedListStatusTextLen
   {618,619},     // EncodedLegIssuerLen
   {621,622},     // EncodedLegSecurityDescLen
   {-1,-1}       // END MARK
};

int IsVLengthTagID(int tagid)
{
   int i;
   for (i=0;g_VLTagPairs[i].targetTag>0;i++)
   {
      if (g_VLTagPairs[i].targetTag==tagid)
         return(i);
   }
   return(-1);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIXData::CFIXData()
{
   m_FIXData = new char [MAXFIXDATALENGTH];
   m_iLastP = 0;
   m_Tags = new ST_FIXTAG [MAXTAGS];
   m_iLastTag = 0;
}

CFIXData::CFIXData(CFIXData const& copyData)
{
   m_FIXData = new char [MAXFIXDATALENGTH];
   memcpy(m_FIXData, copyData.m_FIXData, copyData.m_iLastP);
   m_iLastP = copyData.m_iLastP;
   m_Tags = new ST_FIXTAG [MAXTAGS];
   for (m_iLastTag=0;m_iLastTag<copyData.m_iLastTag;m_iLastTag++)
   {
      memcpy(m_Tags+m_iLastTag,copyData.m_Tags+m_iLastTag,sizeof(ST_FIXTAG));
   }
}

CFIXData::~CFIXData()
{
   if (m_FIXData!=NULL)
   {
      delete []m_FIXData;
   }
   if (m_Tags!=NULL)
   {
      delete []m_Tags;
   }
}

int CFIXData::Reset(const char *sBeginString,const char *sSenderCompID,const char *sTargetCompID)
{
   m_iLastTag = 0;
   m_iLastP = 0;
   if (NULL==m_FIXData)
   {
      m_FIXData = new char [MAXFIXDATALENGTH];
   }
   if (NULL==m_Tags)
   {
      m_Tags = new ST_FIXTAG [MAXTAGS];
   }
   if (NULL==m_Tags||NULL==m_FIXData)
      return(FDE_RESETERR);
   if (sBeginString!=NULL)
   {
      if (AddTag(8,sBeginString)>=0)
      {
         if (sSenderCompID!=NULL && AddTag(49,sSenderCompID)>=0)
         {
            if (sTargetCompID!=NULL)
               AddTag(56,sTargetCompID);
         }
      }
   }
   return(GetTagCount());
}

bool CFIXData::SetData(const char *fixdata, int length, T_REJECTMSG *rejmsg)
{
   Reset();
   return(AddData(fixdata,length,rejmsg));
}


int CFIXData::AddTag(int tag, const char *tvalue, int vlen)
{
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   if (vlen<=0)
   {
      vlen = strlen(tvalue);
   }
   if (vlen<=0)
      return(FDE_INVILIDVALUE); // illegal value of the tag 
   if (MAXFIXDATALENGTH<m_iLastP+vlen)
   {
      return(FDE_OVERFLOW); // FIXData overflow
   }
   if (m_iLastTag>=MAXTAGS)
      return(FDE_TOOMANYTAG);
   int i=m_iLastTag;
   m_Tags[i].tag = tag;
   m_Tags[i].offset = m_iLastP;
   m_Tags[i].length = vlen;
   if (vlen>0)
      memcpy(m_FIXData+m_iLastP,tvalue,vlen);
   m_iLastP += vlen; m_iLastTag++;
   return(i);
}

int CFIXData::GetTagCount()
{
   return(m_iLastTag);
}

int CFIXData::GetTag(int tag_no, int &tag, char *tvalue, int &vlen)
{
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   if (tag_no<0 ||tag_no>=m_iLastTag)
      return(FDE_INVILIDTAGNO);  // error at tag_no
   return(iGetTag(tag_no,tag,tvalue,vlen));
}

int CFIXData::GetTag(int tag, char *tvalue, int &vlen)
{
   int ino;
   int itag;
   int rtn;
   int ivlen;
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   for (ino=0;ino<m_iLastTag;ino++)
   {
      ivlen = 0;
      rtn = iGetTag(ino,itag,NULL,ivlen);
      if (rtn<0)
         return(rtn);
      if (itag==tag)
      {
         return(iGetTag(ino,itag,tvalue,vlen));
      }
   }
   return(FDE_NOTAG);
}

int CFIXData::UpdateTag(int tag_no, int tag, const char *tvalue, int tvlen)
{
   int ivlen;
   int itag;
   if (tag_no<0)
   {
      for (tag_no=0;tag_no<m_iLastTag;tag_no++)
      {
         ivlen = 0;
         int rtn = iGetTag(tag_no,itag,NULL,ivlen);
         if (rtn<0)
         {
            return(rtn);
         }
         if (itag==tag)
            break;
      }
   }
   if (tag_no>=m_iLastTag)
      return(AddTag(tag,tvalue,tvlen));
   else
   {
      // Replace:
      int dof;
      if (tvlen<=0)
      {
         tvlen = strlen(tvalue);
      }
      dof = tvlen-m_Tags[tag_no].length;  // 新缓存和旧缓存之间的长度差异
      if (dof+m_iLastP>MAXFIXDATALENGTH)
         return(FDE_OVERFLOW);
      int i;
      if (dof!=0)
      {
         for (i=tag_no+1;i<m_iLastTag;i++)
         {
            m_Tags[i].offset += dof;   
         }
         i = m_iLastP-1; // old tail
         m_iLastP += dof;
         if (dof>0)
         {
            // move forward:
            int j = i+dof;  // new tail
            dof = m_Tags[tag_no].offset+tvlen; // new head
            for (;j>=dof;)
            {
               m_FIXData[j--]=m_FIXData[i--];
            }
         }
         else //if (tvlen<m_Tags[tag_no].length)
         {
            // move back:
            i = m_Tags[tag_no].offset+tvlen; // new head
            int j = m_Tags[tag_no].offset+m_Tags[tag_no].length; // old head
            for (;i<m_iLastP;)
            {
               m_FIXData[i++]=m_FIXData[j++];
            }
         }
      }
      memcpy(m_FIXData+m_Tags[tag_no].offset,tvalue,tvlen);
      m_Tags[tag_no].length = tvlen;
      m_Tags[tag_no].tag = tag;
      return(tag_no);
   }
}

int FIXGetTagField(char *fixfield, int tag, const char *tvalue, int tvlen)
{
   int l=sprintf(fixfield,"%d=",tag);
   memcpy(fixfield+l,tvalue,tvlen); l+=tvlen;
   fixfield[l++]=C_SOH;
   fixfield[l]='\0';
   return(l);
}

#define NEEDSEQ   
#define HEADTAGS  27
const int g_iHeadTags[HEADTAGS]={
   8	,  //BeginString	Y	FIX.4.2 (Always unencrypted, must be first field in message)
   9	,  //BodyLength	Y	(Always unencrypted, must be second field in message)
   35	,  //MsgType	Y	(Always unencrypted, must be third field in message)
   49	,  //SenderCompID	Y	(Always unencrypted)
   56	,  //TargetCompID	Y	(Always unencrypted)
   115	,  //OnBehalfOfCompID	N	Trading partner company ID used when sending messages via a third party (Can be embedded within encrypted data section.)
   128	,  //DeliverToCompID	N	Trading partner company ID used when sending messages via a third party (Can be embedded within encrypted data section.)
   90	,  //SecureDataLen	N	Required to identify length of encrypted section of message. (Always unencrypted)  
   91	,  //SecureData	N	Required when message body is encrypted.  Always immediately follows SecureDataLen field.
   34	,  //MsgSeqNum	Y	(Can be embedded within encrypted data section.)
   50	,  //SenderSubID	N	(Can be embedded within encrypted data section.)
   142	,  //SenderLocationID	N	Sender's LocationID (i.e. geographic location and/or desk) (Can be embedded within encrypted data section.)
   57	,  //TargetSubID	N	"ADMIN" reserved for administrative messages not intended for a specific user. (Can be embedded within encrypted data section.)
   143	,  //TargetLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) (Can be embedded within encrypted data section.)
   116	,  //OnBehalfOfSubID	N	Trading partner SubID used when delivering messages via a third party. (Can be embedded within encrypted data section.)
   144	,  //OnBehalfOfLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) used when delivering messages via a third party. (Can be embedded within encrypted data section.)
   129	,  //DeliverToSubID	N	Trading partner SubID used when delivering messages via a third party. (Can be embedded within encrypted data section.)
   145	,  //DeliverToLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) used when delivering messages via a third party. (Can be embedded within encrypted data section.)
   43	,  //PossDupFlag	N	Always required for retransmitted messages, whether prompted by the sending system or as the result of a resend request. (Can be embedded within encrypted data section.)
   97	,  //PossResend	N	Required when message may be duplicate of another message sent under a different sequence number. (Can be embedded within encrypted data section.)
   52	,  //SendingTime	Y	(Can be embedded within encrypted data section.)
   122	,  //OrigSendingTime	N	Required for message resent as a result of a ResendRequest.  If data is not available set to same value as SendingTime  (Can be embedded within encrypted data section.)
   212	,  //XmlDataLen	N	Required when specifying XmlData to identify the length of a XmlData message block. (Can be embedded within encrypted data section.)
   213	,  //XmlData	N	Can contain a XML formatted message block (e.g. FIXML).   Always immediately follows XmlDataLen field. (Can be embedded within encrypted data section.)
   347	,  //MessageEncoding	N	Type of message encoding (non-ASCII characters) used in a message's "Encoded" fields.  Required if any "Encoding" fields are used.
   369	,  //LastMsgSeqNumProcessed	N	The last MsgSeqNum value received and processed.  Can be specified on every message sent.  Useful for detecting a backlog with a counterparty.
   370	   //OnBehalfOfSendingTime	N	Used when a message is sent via a "hub" or "service bureau".  If A sends to Q (the hub) who then sends to B via a separate FIX session, then when Q sends to B the value of this field should represent the SendingTime on the message A sent to Q.   (always expressed in UTC (Universal Time Coordinated, also known as "GMT")
}; 

const int g_iTailTags[3]=
{
   93	,  //SignatureLength	N	Required when trailer contains signature.  Note:  Not to be included within SecureData field 
   89	,  //Signature	N	Note:  Not to be included within SecureData field
   10	   //CheckSum	Y	(Always unencrypted, always last field in message)
};
int CFIXData::GetFIXData(char *fixdata, int fdsize)
{
   int fdoff=0;
#ifdef NEEDSEQ   // 需要严格顺序的
   int i;
   // 先取Standard Header
   for (i=0;i<HEADTAGS;++i)
   {
      int tno;
      int vlen=0;
      tno = GetTag(g_iHeadTags[i],NULL,vlen);
      if (tno>=0 && m_Tags[tno].length>0)
      {
         if (fdoff+m_Tags[tno].length+7>fdsize)
            return(FDE_NOENOUGHROOM);
         fdoff += FIXGetTagField(fixdata+fdoff,g_iHeadTags[i],m_FIXData+m_Tags[tno].offset,m_Tags[tno].length);
      }
   }
   for (i=0;i<m_iLastTag;++i)
   {
      int j;
      for (j=0;j<HEADTAGS;++j)
      {
         if (m_Tags[i].tag==g_iHeadTags[j])
            break;
      }
      if (j>=HEADTAGS && m_Tags[i].length>0)
      {
         switch (m_Tags[i].tag)
         {
         case 93	:  //SignatureLength	N	Required when trailer contains signature.  Note:  Not to be included within SecureData field 
         case 89	:  //Signature	N	Note:  Not to be included within SecureData field
         case 10	:  //CheckSum	Y	(Always unencrypted, always last field in message)
            break;
         default:
            if (m_Tags[i].length+7+fdoff>fdsize)
               return(FDE_NOENOUGHROOM);
            fdoff += FIXGetTagField(fixdata+fdoff,m_Tags[i].tag,m_FIXData+m_Tags[i].offset,m_Tags[i].length);
            break;
         }
      }
   }

   // 最后按照规定的顺序，取Standard Tailer:
   for (i=0;i<3;++i)
   {
      int tno;
      int vlen=0;
      tno = GetTag(g_iTailTags[i],NULL,vlen);
      if (tno>=0 && m_Tags[tno].length>0)
      {
         if (fdoff+m_Tags[tno].length+7>fdsize)
            return(FDE_NOENOUGHROOM);
         fdoff += FIXGetTagField(fixdata+fdoff,g_iTailTags[i],m_FIXData+m_Tags[tno].offset,m_Tags[tno].length);
      }      
   }

   /* 由于许多字段值类型为 data，可能含'\0'的，因此不能这样做的
   string htags[HEADTAGS];
   string ttags[3];
   string body;
   for (i=0;i<m_iLastTag;++i)
   {
      if (m_Tags[i].length+5+2>fdsize)
         return(FDE_NOENOUGHROOM);
      if (m_Tags[i].length>0)
      {
         FIXGetTagField(fixdata,m_Tags[i].tag,m_FIXData+m_Tags[i].offset,m_Tags[i].length);
         switch (m_Tags[i].tag)
         {
         case 8  :   //BeginString	Y	FIX.4.4 (Always unencrypted, must be first field in message)
            htags[0]=fixdata;
            break;
         case 9	:  //BodyLength	Y	(Always unencrypted, must be second field in message)
            htags[1]=fixdata;
            break;
         case 35	:  //MsgType	Y	(Always unencrypted, must be third field in message)
            htags[2]=fixdata;
            break;
         case 49	:  //SenderCompID	Y	(Always unencrypted)
            htags[3]=fixdata;
            break;
         case 56	:  //TargetCompID	Y	(Always unencrypted)
            htags[4]=fixdata;
            break;
         case 115	:  //OnBehalfOfCompID	N	Trading partner company ID used when sending messages via a third party (Can be embedded within encrypted data section.)
            htags[5]=fixdata;
            break;
         case 128	:  //DeliverToCompID	N	Trading partner company ID used when sending messages via a third party (Can be embedded within encrypted data section.)
            htags[6]=fixdata;
            break;
         case 90	:  //SecureDataLen	N	Required to identify length of encrypted section of message. (Always unencrypted)  
            htags[7]=fixdata;
            break;
         case 91	:  //SecureData	N	Required when message body is encrypted.  Always immediately follows SecureDataLen field.
            htags[8]=fixdata;
            break;
         case 34	:  //MsgSeqNum	Y	(Can be embedded within encrypted data section.)
            htags[9]=fixdata;
            break;
         case 50	:  //SenderSubID	N	(Can be embedded within encrypted data section.)
            htags[10]=fixdata;
            break;
         case 142	:  //SenderLocationID	N	Sender's LocationID (i.e. geographic location and/or desk) (Can be embedded within encrypted data section.)
            htags[11]=fixdata;
            break;
         case 57	:  //TargetSubID	N	"ADMIN" reserved for administrative messages not intended for a specific user. (Can be embedded within encrypted data section.)
            htags[12]=fixdata;
            break;
         case 143	:  //TargetLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) (Can be embedded within encrypted data section.)
            htags[13]=fixdata;
            break;
         case 116	:  //OnBehalfOfSubID	N	Trading partner SubID used when delivering messages via a third party. (Can be embedded within encrypted data section.)
            htags[14]=fixdata;
            break;
         case 144	:  //OnBehalfOfLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) used when delivering messages via a third party. (Can be embedded within encrypted data section.)
            htags[15]=fixdata;
            break;
         case 129	:  //DeliverToSubID	N	Trading partner SubID used when delivering messages via a third party. (Can be embedded within encrypted data section.)
            htags[16]=fixdata;
            break;
         case 145	:  //DeliverToLocationID	N	Trading partner LocationID (i.e. geographic location and/or desk) used when delivering messages via a third party. (Can be embedded within encrypted data section.)
            htags[17]=fixdata;
            break;
         case 43	:  //PossDupFlag	N	Always required for retransmitted messages, whether prompted by the sending system or as the result of a resend request. (Can be embedded within encrypted data section.)
            htags[18]=fixdata;
            break;
         case 97	:  //PossResend	N	Required when message may be duplicate of another message sent under a different sequence number. (Can be embedded within encrypted data section.)
            htags[19]=fixdata;
            break;
         case 52	:  //SendingTime	Y	(Can be embedded within encrypted data section.)
            htags[20]=fixdata;
            break;
         case 122	:  //OrigSendingTime	N	Required for message resent as a result of a ResendRequest.  If data is not available set to same value as SendingTime  (Can be embedded within encrypted data section.)
            htags[21]=fixdata;
            break;
         case 212	:  //XmlDataLen	N	Required when specifying XmlData to identify the length of a XmlData message block. (Can be embedded within encrypted data section.)
            htags[22]=fixdata;
            break;
         case 213	:  //XmlData	N	Can contain a XML formatted message block (e.g. FIXML).   Always immediately follows XmlDataLen field. (Can be embedded within encrypted data section.)
            htags[23]=fixdata;
            break;
         case 347	:  //MessageEncoding	N	Type of message encoding (non-ASCII characters) used in a message's "Encoded" fields.  Required if any "Encoding" fields are used.
            htags[24]=fixdata;
            break;
         case 369	:  //LastMsgSeqNumProcessed	N	The last MsgSeqNum value received by the FIX engine and processed by downstream application, such as trading system or order routing system.  Can be specified on every message sent.  Useful for detecting a backlog with a counterparty.
            htags[25]=fixdata;
            break;
         case 370	:  //OnBehalfOfSendingTime	N	Used when a message is sent via a "hub" or "service bureau".  If A sends to Q (the hub) who then sends to B via a separate FIX session, then when Q sends to B the value of this field should represent the SendingTime on the message A sent to Q.   (always expressed in UTC (Universal Time Coordinated, also known as "GMT")
            htags[26]=fixdata;
            break;
         case 93	:  //SignatureLength	N	Required when trailer contains signature.  Note:  Not to be included within SecureData field 
            ttags[0]=fixdata;
            break;
         case 89	:  //Signature	N	Note:  Not to be included within SecureData field
            ttags[1]=fixdata;
            break;
         case 10	:  //CheckSum	Y	(Always unencrypted, always last field in message)
            ttags[2]=fixdata;
            break;
         default:
            body += fixdata;
            break;
         }
      }
   }
   for (i=0;i<HEADTAGS;++i)
   {
      if (htags[i].length()>0)
      {
         if (fdoff+htags[i].length()>fdsize)
            return(FDE_NOENOUGHROOM);
         memcpy(fixdata+fdoff,htags[i].c_str(),htags[i].length());
         fdoff += htags[i].length();
      }
   }
   if (fdoff+body.length()>fdsize)
      return(FDE_NOENOUGHROOM);
   memcpy(fixdata+fdoff,body.c_str(),body.length());
   fdoff += body.length();
   for (i=0;i<3;++i)
   {
      if (ttags[i].length()>0)
      {
         if (fdoff+ttags[i].length()>fdsize)
            return(FDE_NOENOUGHROOM);
         memcpy(fixdata+fdoff,ttags[i].c_str(),ttags[i].length());
         fdoff += ttags[i].length();
      }
   }
   ********************************************/
#else
   int it;
   int fdoff=0;  // 已经生成的fixdata的长度
   for (it=0;it<m_iLastTag;it++)
   {
      if (fdsize<fdoff+m_Tags[it].length+5+2)
         return(FDE_NOENOUGHROOM);
      if (m_Tags[it].length>0)
      {
         fdoff += FIXGetTagField(fixdata+fdoff,m_Tags[it].tag,m_FIXData+m_Tags[it].offset,m_Tags[it].length);
         /*         
         sprintf(fixdata+fdoff,"%d=",m_Tags[it].tag);
         fdoff += strlen(fixdata+fdoff);
         memcpy(fixdata+fdoff,m_FIXData+m_Tags[it].offset,m_Tags[it].length);
         fdoff += m_Tags[it].length;
         fixdata[fdoff++]=C_SOH;
         */
      }
   }
#endif
   if (fdoff<fdsize)
      fixdata[fdoff]='\0';
   return(fdoff);
}



int CFIXData::ReverseGetIntValue(int tagid)
{
   int i;
   char tvalue[256];
   int vlen;
   for (i=m_iLastTag-1;i>=0;i--)
   {
      if (m_Tags[i].tag==tagid)
      {
         vlen = m_Tags[i].length;
         if (vlen>255)
            vlen = 255;
         if (vlen>0)
         {
            memcpy(tvalue,m_FIXData+m_Tags[i].offset,vlen);
         }
         tvalue[vlen]='\0';
         return(atoi(tvalue));
      }
   }
   return(-1);
}

int CFIXData::GetTagNext(int tag_no0, int tag, char *tvalue, int &vlen)
{
   int ino;
   int rtn;
   int itag;
   int ivlen=0;
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   for (ino=tag_no0+1;ino<m_iLastTag;ino++)   
   {
      rtn = iGetTag(ino,itag,NULL,ivlen);
      if (rtn<0)
         return(rtn);
      if (itag==tag)
      {
         return(iGetTag(ino,itag,tvalue,vlen));
      }
   }
   return(FDE_NOTAG);
}


int CFIXData::GetStdFIXMessage(char *fixdata, int datasize, const char *sBeginString)
{
#ifdef NEEDSEQ   // 需要严格顺序的
   int fdoff=0;
   int i;
   int tno;
   int vlen;
   // 先取Standard Header
   if (sBeginString!=NULL)
   {
      fdoff = sprintf(fixdata,"8=%s%c",sBeginString,C_SOH);
   }
   else
   {
      vlen=0;
      tno = GetTag(8,NULL,vlen);
      if (tno>=0 && m_Tags[tno].length>0)
      {
         fdoff = FIXGetTagField(fixdata,8,m_FIXData+m_Tags[tno].offset,m_Tags[tno].length);
      }
      else
      {
         fdoff = sprintf(fixdata,"8=FIX.4.4%c",C_SOH);
      }
   }
   int pTag9=fdoff;
   fdoff += 7; // 9=0234<SOH>
   for (i=2;i<HEADTAGS;++i)
   {
      vlen=0;
      tno = GetTag(g_iHeadTags[i],NULL,vlen);
      if (tno>=0 && m_Tags[tno].length>0)
      {
         if (fdoff+m_Tags[tno].length+7>datasize)
            return(FDE_NOENOUGHROOM);
         fdoff += FIXGetTagField(fixdata+fdoff,g_iHeadTags[i],m_FIXData+m_Tags[tno].offset,m_Tags[tno].length);
      }
   }
   // Body:
   for (i=0;i<m_iLastTag;++i)
   {
      int j;
      for (j=0;j<HEADTAGS;++j)
      {
         if (m_Tags[i].tag==g_iHeadTags[j])
            break;
      }
      if (j>=HEADTAGS && m_Tags[i].length>0)
      {
         switch (m_Tags[i].tag)
         {
         case 93	:  //SignatureLength	N	Required when trailer contains signature.  Note:  Not to be included within SecureData field 
         case 89	:  //Signature	N	Note:  Not to be included within SecureData field
         case 10	:  //CheckSum	Y	(Always unencrypted, always last field in message)
            break;
         default:
            if (m_Tags[i].length+7+fdoff>datasize)
               return(FDE_NOENOUGHROOM);
            fdoff += FIXGetTagField(fixdata+fdoff,m_Tags[i].tag,m_FIXData+m_Tags[i].offset,m_Tags[i].length);
            break;
         }
      }
   }
   // 最后按照规定的顺序，取Standard Tailer:
   for (i=0;i<2;++i)
   {
      vlen=0;
      tno = GetTag(g_iTailTags[i],NULL,vlen);
      if (tno>=0 && m_Tags[tno].length>0)
      {
         if (fdoff+m_Tags[tno].length+7>datasize)
            return(FDE_NOENOUGHROOM);
         fdoff += FIXGetTagField(fixdata+fdoff,g_iTailTags[i],m_FIXData+m_Tags[tno].offset,m_Tags[tno].length);
      }      
   }
   sprintf(fixdata+pTag9,"9=%04d",fdoff-pTag9-7);
   fixdata[pTag9+6]=C_SOH;

   unsigned int crc = GetFIXCheckSum(fixdata,fdoff);
   sprintf(fixdata+fdoff,"10=%03u%c",crc,C_SOH);
   return(fdoff+7);
#else
   unsigned int clen=0;
   int it;
   if (sBeginString!=NULL)
   {
      sprintf(fixdata,"8=%s",sBeginString);
      clen = strlen(fixdata);
   }
   else
   {
      for (it=0;it<m_iLastTag;it++)
      {
         if (m_Tags[it].tag==8)
         {
            strcpy(fixdata,"8=");
            memcpy(fixdata+2,m_FIXData+m_Tags[it].offset,m_Tags[it].length);
            clen = 2+m_Tags[it].length;
            break;
         }
      }
      if (it>=m_iLastTag)
      {
         // 使用缺省的FIX.4.4
         strcpy(fixdata,"8=FIX.4.4");
         clen = strlen(fixdata);
      }
   }
   fixdata[clen++]=C_SOH;
   
   // Get the body part...
   char *pfixbody=fixdata+clen+7; // body string start  9=0234<SOH>
   int blen=0; // body length
   for (it=0;it<m_iLastTag;it++)
   {
      if (IsBodyTag(m_Tags[it].tag))
      {
         if (datasize<blen+m_Tags[it].length+10)
            return(FDE_NOENOUGHROOM);
         sprintf(pfixbody+blen,"%d=",m_Tags[it].tag);
         blen += strlen(pfixbody+blen);
         memcpy(pfixbody+blen,m_FIXData+m_Tags[it].offset,m_Tags[it].length);
         blen += m_Tags[it].length;
         pfixbody[blen++]=C_SOH;
      }
   }

   sprintf(fixdata+clen,"9=%04d",blen);
   fixdata[clen+6]=C_SOH;
   blen += clen+7;

   unsigned int crc = GetFIXCheckSum(fixdata,blen);
   sprintf(fixdata+blen,"10=%03u%c",crc,C_SOH);
   return(blen+7);
#endif
}

int CFIXData::RemoveTagNo(int tag_no)
{
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   if (tag_no<0 ||tag_no>=m_iLastTag)
      return(FDE_INVILIDTAGNO);  // error at tag_no
   ST_FIXTAG *pft = m_Tags+tag_no;
   int df = pft->length;
   if (m_iLastP>pft->offset+pft->length)
      memcpy(m_FIXData+pft->offset,m_FIXData+pft->offset+pft->length,m_iLastP-pft->offset-pft->length);
   m_iLastP -= df;
   for (++tag_no;tag_no<m_iLastTag;++tag_no)
   {
      pft->tag = m_Tags[tag_no].tag; 
      pft->length = m_Tags[tag_no].length;
      pft->offset = m_Tags[tag_no].offset-df;
      ++pft;
   }
   return(--m_iLastTag);
}

int CFIXData::RemoveTag(int tag)
{
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   int ino;
   for (ino=0;ino<m_iLastTag;ino++)
   {
      if (m_Tags[ino].tag==tag)
         return(RemoveTagNo(ino));
   }
   return(FDE_NOTAG);
}

int CFIXData::iGetTag(int tag_no, int &tag, char *tvalue, int &vlen)
{
   tag = m_Tags[tag_no].tag;
   if (tvalue!=NULL)
   {
      if (vlen<0||vlen>m_Tags[tag_no].length)
      {
         vlen = m_Tags[tag_no].length;
      }
      else 
         vlen--;
      if (vlen>0)
         memcpy(tvalue,m_FIXData+m_Tags[tag_no].offset,vlen);
      tvalue[vlen]='\0';
   }
   else
      vlen = m_Tags[tag_no].length;
   return(tag_no);
}

int CFIXData::AddTag(int tag, char ctvalue)
{
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   if (MAXFIXDATALENGTH<m_iLastP+1)
      return(FDE_OVERFLOW); // FIXData overflow
   if (m_iLastTag>=MAXTAGS)
      return(FDE_TOOMANYTAG);
   m_Tags[m_iLastTag].tag = tag;
   m_Tags[m_iLastTag].offset = m_iLastP;
   m_Tags[m_iLastTag++].length = 1;
   m_FIXData[m_iLastP++] = ctvalue;
   return(m_iLastTag-1);
}

int CFIXData::AddTag(int tag, double dtvalue, unsigned int dec)
{
   char tmp[256];
   char fmt[10];
   sprintf(fmt,"%%.%ulf",dec);
   return(AddTag(tag,tmp,sprintf(tmp,fmt,dtvalue)));
}

int CFIXData::AddTag(int tag, int itvalue)
{
   char tvalue[12];
   return(AddTag(tag,tvalue,sprintf(tvalue,"%d",itvalue)));
}

int CFIXData::AddTag(int tag, unsigned int utvalue)
{
   char tvalue[12];
   return(AddTag(tag,tvalue,sprintf(tvalue,"%u",utvalue)));
}

int CFIXData::AddTag(int tag, INT8 tvi8)
{
   char tvalue[24];
#ifdef _MSC_VER
   return(AddTag(tag,tvalue,sprintf(tvalue,"%I64d",tvi8)));
#else
   return(AddTag(tag,tvalue,sprintf(tvalue,"%lld",tvi8)));
#endif
}

int CFIXData::AddTag(int tag, long ltvalue)
{
   char tvalue[24];
   return(AddTag(tag,tvalue,sprintf(tvalue,"%ld",ltvalue)));
}

int CFIXData::GetTagI(int tag)
{
   char tvalue[24];
   int rtn;
   int tvlen = sizeof(tvalue);
   if ((rtn=GetTag(tag,tvalue,tvlen))<0)
      return(rtn);
   return(atoi(tvalue));
}

#ifdef _MSC_VER
#define ATOINT8(str) _atoi64(str)
#else
#define ATOINT8(str) atoll(str)
#endif

INT8 CFIXData::GetTagI8(int tag)
{
   char tvalue[24];  // INT8: –9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
   int rtn;
   int tvlen = sizeof(tvalue);
   if ((rtn=GetTag(tag,tvalue,tvlen))<0)
      return(rtn);
   return(ATOINT8(tvalue));
}

bool FIX_bCheckSum=true;

bool CFIXData::Valid(const char *fixmsg, T_REJECTMSG *pRejMsg)
{
   int tvlen;
   char msgtype[8];
   // ValidMsgSeqNum:
   int msgSN = GetTagI(34);
   if (pRejMsg!=NULL)
   {
      // 为了直接导出
      pRejMsg->RefSeqNum = msgSN;
   }
   if (msgSN<=0)
   {
      SETREJMSG(pRejMsg,msgSN,34,"",1,"No Tag 34(MsgSeqNum)");
      return(false);
   }
   // ValidMsgType:
   tvlen = sizeof(msgtype);
   int tag;
   if (GetTag(2,tag,msgtype,tvlen)<0||tag!=35)
   {
      SETREJMSG(pRejMsg,msgSN,35,"",14,"No Tag 35(MsgType)");
      return(false);
   }
   if (pRejMsg!=NULL)
   {
      strncpy(pRejMsg->RefMsgType,msgtype,sizeof(pRejMsg->RefMsgType));
   }
   // ValidBodyLength:
   int bodylength; // = GetTagI(9);
   const char *pcm = strstr(fixmsg,"\0019=");
   if (pcm==NULL)
   {
      SETREJMSG(pRejMsg,msgSN,9,"",1,"No Tag 9(BodyLength)");
      return(false);
   }
   int cs1;
   cs1 = (int)(pcm-fixmsg)+3; // 9=后面这个长度位置
   bodylength = atoi(fixmsg+cs1);
   for (;fixmsg[cs1];++cs1)
   {
      if (fixmsg[cs1]==C_SOH)
         break;
   }
   bodylength += cs1; // body再加上8=...<SOH>9=...<SOH>部分
   //if (FIX_bCheckSum)
   {
      if (memcmp(fixmsg+bodylength,"\00110=",4)!=0)
      {
         SETREJMSG(pRejMsg,msgSN,9,msgtype,10,"Error @ Tag 9");
         return(false);
      }
      cs1 = atoi(fixmsg+bodylength+4);
      int cs2 = GetFIXCheckSum(fixmsg,bodylength+1);
      if (cs1!=cs2)
      {
         if (pRejMsg!=NULL)
         {
            sprintf(pRejMsg->Text,"Invalid Tag 10 (%d!=%d)",cs1,cs2);
            SETREJMSG(pRejMsg,msgSN,10,msgtype,5,pRejMsg->Text);
         }
         return(false);
      }
   }
   return(true);
}

bool CFIXData::AddData(const char *fixdata, int length, T_REJECTMSG *rejmsg)
{
   if (NULL==m_Tags||NULL==m_FIXData)
   {
      SETREJMSG(rejmsg,0,0,"",99,"Fail to reset FIXData");
      return(false);
   }
   if (NULL==fixdata)
   {
      SETREJMSG(rejmsg,0,0,"",99,"fixdata is NULL");
      return(false);
   }
   if (length<=0||length>strlen(fixdata))
      length = strlen(fixdata);
   int i;
   //8=FIX.4.4<SOH>9=158<SOH>35=D<SOH>49=TARGET0<SOH>56=SENDER0<SOH>34=36<SOH>52=20071211-03:17:23.947<SOH>11=ClOrdId<SOH>21=C<SOH>55=symbol<SOH>54=2<SOH>40=3<SOH>60=20020425-09:19:23.063<SOH>10=019<SOH>
   int vltag;
   for (i=0;i<length;)
   {
      if (m_iLastTag>=MAXTAGS)
      {
         SETREJMSG(rejmsg,GetTagI(34),m_Tags[m_iLastTag-1].tag,"",99,"Too much Tags");
         return(false);
      }
      m_Tags[m_iLastTag].tag = atoi(fixdata+i);
      for (;fixdata[i]!='=';i++)
      {
         if ('\0'==fixdata[i]||length<=i)
         {
            SETREJMSG(rejmsg,GetTagI(34),m_Tags[m_iLastTag].tag,"",4,"");
            return(false);
         }
      }
      i++; // '='
      m_Tags[m_iLastTag].offset = m_iLastP;
      vltag = IsVLengthTagID(m_Tags[m_iLastTag].tag);
      if (vltag<0)
      {
         int ip0 = i;
         for (;fixdata[i]!=C_SOH;i++)
         {
            if ('\0'==fixdata[i]||length<=i)
            {
               SETREJMSG(rejmsg,GetTagI(34),m_Tags[m_iLastTag].tag,"",6,"No end with SOH");
               return(false);
            }
            m_FIXData[m_iLastP++]=fixdata[i];  // assign 'value' into m_FIXData
         }
         m_Tags[m_iLastTag].length = i-ip0;
      }
      else
      {
         // is a variable-length tag:
         int vlen = ReverseGetIntValue(g_VLTagPairs[vltag].lenTag);
         if (vlen<0)
         {
            SETREJMSG(rejmsg,GetTagI(34),m_Tags[m_iLastTag].tag,"",1,"Var-length undefined");
            return(false);
         }
         if (length<i+vlen)
         {
            SETREJMSG(rejmsg,GetTagI(34),m_Tags[m_iLastTag].tag,"",5,"Var-length overflow");
            return(false);
         }
         m_Tags[m_iLastTag].length = vlen;
         for (;vlen>0;vlen--)
         {
            m_FIXData[m_iLastP++]=fixdata[i++];
         }
      }
      if (fixdata[i]!=C_SOH)
      {
         SETREJMSG(rejmsg,GetTagI(34),m_Tags[m_iLastTag-1].tag,"",5,"No end with SOH");
         return(false);
      }
      ++i; // C_SOH
      ++m_iLastTag;
   }
   return(true);
}



double CFIXData::GetTagD(int tag)
{
   char tvalue[128];
   int rtn;
   int tvlen = sizeof(tvalue);
   if ((rtn=GetTag(tag,tvalue,tvlen))<0)
      return((double)rtn);
   return(atof(tvalue));
}




int CFIXData::GetGroupTagNext(int tag_no0, int tag, int no, char *tvalue, int &vlen)
{
   int ino;
   int rtn;
   int itag;
   int ivlen=0;
   if (NULL==m_FIXData||NULL==m_Tags)
      return(FDE_RESETERR);
   for (ino=tag_no0+1;ino<m_iLastTag;ino++)   
   {
      rtn = iGetTag(ino,itag,NULL,ivlen);
      if (rtn<0)
         return(rtn);
      if (itag==tag)
      {
         if (no>0) 
            --no;
         else
            return(iGetTag(ino,itag,tvalue,vlen));
      }
   }
   return(FDE_NOTAG);
}

// 目的是为了过滤在常规字段中，包含非ASCII码的字符串部分，由于Sungard FIXEngine会因为消息中含这些字符而异常
int CFIXData::FilterNonASC()
{
   int i;
   int n=0;
   for (i=0;i<m_iLastTag;++i)
   {
      if (IsVLengthTagID(m_Tags[i].tag)<0)  
      {
         int l;
         char *pc=m_FIXData+m_Tags[i].offset;
         int len = m_Tags[i].length;
         for (l=0;l<len;++l)
         {
            if (pc[l]>127||pc[l]<=0)
            {
               ++n;
               break;
            }
         }
         m_Tags[i].length = l;
      }
   }
   return(n);
}
