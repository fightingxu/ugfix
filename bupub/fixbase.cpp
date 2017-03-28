/********************************************************************
	created:	2009/07/03
	created:	3:7:2009   11:17
	filename: 	D:\projects\FIXII\2编码\FIXServer\ksfixbu\fixbase.cpp
	file path:	D:\projects\FIXII\2编码\FIXServer\ksfixbu
	file base:	fixbase
	file ext:	cpp
	author:		Yonghua.Chen
	
	purpose:	这里是用CFIXData实现的一些供具体功能函数调用的基础函数的实现
*********************************************************************/

#include "stdafx.h"
#include "mypub.h"
#include "FIXData.h"
#include "fixbase.h"

#define FIX_MINDBL -0.0001


FIXDATAHANDLE FIXDataNew(void)
{
   CFIXData *pFIXData = new CFIXData;
   return(pFIXData);
}

void FIXDataDelete(FIXDATAHANDLE pFIXDataHandle)
{
   if (pFIXDataHandle!=NULL)
   {
      CFIXData *pfixdata = (CFIXData *)pFIXDataHandle;
      delete pfixdata;
      pFIXDataHandle = NULL;
   }
}

int FIXDataReset(FIXDATAHANDLE h,const char *sBeginString,const char *sSenderCompID,const char *sTargetCompID)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->Reset(sBeginString,sSenderCompID,sTargetCompID));
}

int FIXDataSetData(FIXDATAHANDLE h,const char *fixdata, int length)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   if (length<=0)
      length = strlen(fixdata);
   if (pfixdata->SetData(fixdata,length))
      return(1);
   else
      return(FD_SETDATAERR);
}

int FIXDataAddTag(FIXDATAHANDLE h,int tag, const char *tvalue, int vlen)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->AddTag(tag,tvalue,vlen));
}

int FIXDataGetTagCount(FIXDATAHANDLE h)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->GetTagCount());
}

int FIXDataGetTagNo(FIXDATAHANDLE h, int tag_no, int *tag, char *tvalue, int *vlen)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   if (vlen==NULL)
   {
      int len=-1;
      return(pfixdata->GetTag(tag_no,*tag,tvalue,len));
   }
   return(pfixdata->GetTag(tag_no,*tag,tvalue,*vlen));
}

int FIXDataGetTag(FIXDATAHANDLE h, int tag, char *tvalue, int *vlen)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   if (vlen==NULL)
   {
      int len=-1;
      return(pfixdata->GetTag(tag,tvalue,len));
   }
   return(pfixdata->GetTag(tag,tvalue,*vlen));
}

int FIXDataGetTagNext(FIXDATAHANDLE h, int tag_no0, int tag, char *tvalue, int *vlen)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   if (vlen==NULL)
   {
      int len=-1;
      return(pfixdata->GetTagNext(tag_no0,tag,tvalue,len));
   }
   return(pfixdata->GetTagNext(tag_no0,tag,tvalue,*vlen));
}

int FIXDataGetGroupTagNext(FIXDATAHANDLE h, int tag_no0, int tag, int no, char *tvalue, int *vlen)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   if (vlen==NULL)
   {
      int len = -1;
      return(pfixdata->GetGroupTagNext(tag_no0,tag,no,tvalue,len));
   }
   return(pfixdata->GetGroupTagNext(tag_no0,tag,no,tvalue,*vlen));
}



int FIXDataUpdateTag(FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue, int tvlen)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->UpdateTag(tag_no,tag,tvalue,tvlen));
}

int FIXDataGetFIXData(FIXDATAHANDLE h, char *fixdata, int fdsize)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->GetFIXData(fixdata,fdsize));
}

int FIXDataRemoveTagNo(FIXDATAHANDLE h, int tag_no)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->RemoveTagNo(tag_no));
}

int FIXDataRemoveTag(FIXDATAHANDLE h, int tag)
{
   if (h==NULL)
      return(FD_INVALIDHANDLE);
   CFIXData *pfixdata = (CFIXData *)h;
   return(pfixdata->RemoveTag(tag));
}

int FDUpdateTagString(FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue)
{
   if (tvalue==NULL)
      return(-1);
   int tvlen = strlen(tvalue);
   if (tvlen<=0)
      return(-2);
   return(FIXDataUpdateTag(h,tag_no,tag,tvalue,tvlen));   
}


int FDUpdateTagDouble(FIXDATAHANDLE h, int tag_no, int tag, double tvalue)
{
   char ctv[400];
   if (tvalue<FIX_MINDBL)
      return(-1);
   int tvlen = sprintf(ctv,"%lf",tvalue);
   return(FIXDataUpdateTag(h,tag_no,tag,ctv,tvlen));   
}


int FDUpdateTagQty(FIXDATAHANDLE h, int tag_no, int tag, double qty)
{
   char tvalue[400];
   if (qty<FIX_MINDBL)
      return(-1);
   int tvlen = sprintf(tvalue,"%.4lf",qty);
   if (tvlen>5)
   {
      if (memcmp(tvalue+tvlen-5,".0000",5)==0)
      {
         tvlen -= 5;
         tvalue[tvlen]='\0';
      }
   }
   return(FIXDataUpdateTag(h,tag_no,tag,tvalue,tvlen)); 
}

int FDUpdateTagInt(FIXDATAHANDLE h, int tag_no, int tag, int tvint)
{
   char tvalue[40];
   if (tvint<0)
      return(-1);
   int tvlen = sprintf(tvalue,"%d",tvint);
   return(FIXDataUpdateTag(h,tag_no,tag,tvalue,tvlen)); 
}


int FVString2FIXMsg(int tagid, const char *sFieldValue, char *fmbuf, int fmbsize)
{
   if (sFieldValue[0]=='\0')
      return(0);
   if ((int)strlen(sFieldValue)+7>fmbsize)
   {
      return(-1);
   }
   return(sprintf(fmbuf,"%d=%s%c",tagid,sFieldValue,C_SOH));
}

int FVDouble2FIXMsg(int tagid, double dFieldValue, char *fmbuf, int fmbsize)
{
   if (dFieldValue<FIX_MINDBL)
      return(0); 
   if (fmbsize<27)
      return(-1);
   return(sprintf(fmbuf,"%d=%.4lf%c",tagid,dFieldValue,C_SOH));
}

// 由于申万的BayClay Capital对手不能接收Qty类型的以小数方式表示，为此，我们就做如下处理 @ 2011-06-20
int FVQty2FIXMsg(int tagid, double dFieldValue, char *fmbuf, int fmbsize)
{
   if (dFieldValue<FIX_MINDBL)
      return(0); 
   if (fmbsize<27)
      return(-1);
   int rtn = sprintf(fmbuf,"%d=%.4lf%c",tagid,dFieldValue,C_SOH);
   if (rtn>6)  // ".0000<SOH>"
   {
      if (memcmp(fmbuf+rtn-6,".0000",5)==0)
      {
         fmbuf[rtn-6]=C_SOH;
         rtn -= 5;
         fmbuf[rtn]='\0';
      }
   }
   return(rtn);
}

int FVInt2FIXMsg(int tagid, int iFieldValue, char *fmbuf, int fmbsize)
{
   if (iFieldValue<0)
      return(0);
   if (fmbsize<17)
      return(-1);
   return(sprintf(fmbuf,"%d=%d%c",tagid,iFieldValue,C_SOH));
}

const char *CYHPubKey="Designed by ChenYongHua";
const char *szKey="FIXSERVER";

int PwdEncode(char *Source, const char *Key)
{
   unsigned char *p;
   if (Key==NULL||(*Key)=='\0'||Source==NULL||(*Source)=='\0')
      return(0);
   for (p=(unsigned char *)Source;*p;p++)
   {
      if (*p>=0x80)
         return(0);
   }
   for (p=(unsigned char *)Key;*p;p++)
   {
      if (*p>=0x80)
         return(0);
   }
   unsigned char *k;
   unsigned char *c;
   k = (unsigned char *)Key;
   c = (unsigned char *)CYHPubKey;
   for (p=(unsigned char *)Source;*p;p++,k++,c++)
   {
      if ((*k)==0)
         k = (unsigned char *)Key;
      if ((*c)==0)
         c = (unsigned char *)CYHPubKey;         
      *p ^= ((*k)^(*c)^0x80);
   }
   return(1);
}

int PwdDncode(char *Source, const char *Key)
{
   unsigned char *p;
   if (Key==NULL||(*Key)=='\0'||Source==NULL||(*Source)=='\0')
      return(0);
   for (p=(unsigned char *)Source;*p;p++)
   {
      if (*p<0x80)
         return(0);
   }
   for (p=(unsigned char *)Key;*p;p++)
   {
      if (*p>=0x80)
         return(0);
   }
   unsigned char *k;
   unsigned char *c;
   k = (unsigned char *)Key;
   c = (unsigned char *)CYHPubKey;
   for (p=(unsigned char *)Source;*p;p++,k++,c++)
   {
      if ((*k)==0)
         k = (unsigned char *)Key;
      if ((*c)==0)
         c = (unsigned char *)CYHPubKey;         
      *p ^= ((*k)^(*c)^0x80);
   }
   return(1);
}

