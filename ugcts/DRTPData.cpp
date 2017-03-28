// DRTPData.cpp: implementation of the CDRTPData class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "DRTPData.h"
#include "nbccclt.h"
#include "nbccsvr.h"
#include "xpub.h"
#include "ugate.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDRTPData::CDRTPData()
{
   int i;
   for (i=0;i<MAXDRTPNODES;++i)
      m_CJSvr[i] = -1;
   m_LastOK = -1;
   m_nDRTPs = 0;
   m_bSvrReg = false;
}

CDRTPData::~CDRTPData()
{

}

int CDRTPData::Initialize(char *errMsg)
{
   int i;
   char tmp[80];

   m_nDRTPs = UG_INIReadInt("KSCTS","DRTPNODES",1);
   if (m_nDRTPs>MAXDRTPNODES||m_nDRTPs<1)
   {
      sprintf(errMsg,"Invalid [KSCTS] DRTPNODES=%d defined!",m_nDRTPs);
      return(-1); 
   }

   BCCCLTInit(m_nDRTPs);

   for (i=0;i<m_nDRTPs;++i)
   {
      sprintf(tmp,"DRTP%d",i+1);
      UG_INIReadTString("KSCTS",tmp,"",m_DRTPPara[i],sizeof(m_DRTPPara[i]));
      if ('\0'==m_DRTPPara[i][0])
      {
         sprintf(errMsg,"Undefined [KSCTS] %s!",tmp);
         return(-2);
      }
      if (GetNodeBranch(i)<0 || GetNodeIP(i,tmp,sizeof(tmp))<0)
      {
         sprintf(errMsg,"Invalid [KSCTS] DRTP%d=%s",i+1,m_DRTPPara[i]);
         return(-3);
      }
      m_bcno[i] = BCAddDrtpNode(tmp,GetNodePort(i));
   }
   BCSetDebugSwitch(UG_INIReadInt("KSCTS","BCLOG",1)!=0);
   if (UG_INIReadInt("KSCTS","BSLOG",1)!=0)
   {
      BSKLGOpen("bslog");
   }

   m_CJFuncNo = UG_INIReadInt("KSCTS","CJFUNCNO",0);
   if (m_CJFuncNo<=0)
   {
      sprintf(errMsg,"Invalid [KSCTS] CJFUNCNO=%d!",m_CJFuncNo);
      return(-4);
   }

   m_AckTime = UG_INIReadInt("KSCTS","ACKTIME",1000);
   if (m_AckTime<500)
   {
      m_AckTime = 500;
   }

   return(0);
}

int CDRTPData::GetNodeBranch(int id)
{
   char tmp[32];
   if (id<0 || id>=m_nDRTPs)
      return(-1);
   if(GetSubString(m_DRTPPara[id],':',2,tmp,sizeof(tmp),NULL)<=0)
      return(-2);
   return(atoi(tmp));
}

int CDRTPData::GetNodePort(int id)
{
   char tmp[32];
   if (id<0 || id>=m_nDRTPs)
      return(-1);
   if(GetSubString(m_DRTPPara[id],':',1,tmp,sizeof(tmp),NULL)<=0)
      return(-2);
   return(atoi(tmp));
}

int CDRTPData::GetNodeIP(int id, char *ip, unsigned int ipsize)
{
   if (id<0 || id>=m_nDRTPs)
      return(-1);
   if(GetSubString(m_DRTPPara[id],':',0,ip,ipsize,NULL)<=0)
      return(-2);
   return(strlen(ip));
}

bool CDRTPData::ToStartCJRecv(char *errMsg)
{
   int i;
   for (i=0;i<m_nDRTPs;++i)
   {
      char ip[32];
      GetNodeIP(i,ip,sizeof(ip));
      m_CJSvr[i]=BSAddService(GetNodeBranch(i),ip,GetNodePort(i),
         &m_CJFuncNo,1,true);
      if (m_CJSvr[i]<0)
      {
         sprintf(errMsg,"Fail to start CJ RecvSvr @ DRTP[%d](%s)!",
            i,ip);
         return(false);
      }
   }
   m_bSvrReg = true;
   return(true);
}

void CDRTPData::ToStopCJRecv()
{
   int i;
   m_bSvrReg = false;
   for (i=0;i<m_nDRTPs;++i)
   {
      BSStopService(m_CJSvr[i]);
      m_CJSvr[i] = -1; // 表示没有用了
   }
}

int CDRTPData::isLinkOK(int id)
{
   if (id<0 || id>=m_nDRTPs)
      return(-1);
   if (m_CJSvr[id]<0)
      return(-2);
   if (BSIsServiceOK(m_CJSvr[id]))
      return(1);
   else
      return(0);
}

int CDRTPData::CallSvr(BCHANDLE bch, int destno, int funcno, char *errMsg)
{
   int i0=m_LastOK;
   int id;
   if (i0<0)
      i0=0;
   for (id=i0;;)
   {
      if (!m_bSvrReg || isLinkOK(id)>0)
      {
         if (BCCallRequest(bch,m_bcno[id],destno,funcno,m_AckTime,&i0,errMsg))
         {
            m_LastOK = id;
            return(id);
         }
         else
         {
            m_LastOK = id+1;
            if (m_LastOK>=m_nDRTPs)
               m_LastOK = 0;
            if (i0>0)
               return(-i0);  // 失败了
            else
               return(i0);
         }
      }
      if (++id>=m_nDRTPs)
         id = 0;
      if (id==i0)
      {
         sprintf(errMsg,"No linked DRTP to CallSvr(%d:%d)",destno,funcno);
         return(-1);
      }
   }
}

bool CDRTPData::BindBSCJRecv(BSHANDLE bsh)
{
   int i;
   for (i=0;i<m_nDRTPs;++i)
   {
      BSBindService(bsh,m_CJSvr[i]);
   }
   return(true);
}

int CDRTPData::TryCallSvr(BCHANDLE bch, int destno, int funcno, char *errMsg)
{
   int i0=m_LastOK;
   int id;
   int errcode;
   if (i0<0)
      i0=0;
   for (id=i0;;)
   {
      if (!m_bSvrReg || isLinkOK(id)>0)
      {
         if (BCCallRequest(bch,m_bcno[id],destno,funcno,m_AckTime,&errcode,errMsg))
         {
            m_LastOK = id;
            return(id);
         }
      }
      if (++id>=m_nDRTPs)
         id = 0;
      if (id==i0)
      {
         sprintf(errMsg,"No linked DRTP to CallSvr(%d:%d)",destno,funcno);
         return(-1);
      }
   }
}


int CDRTPData::CallNext(BCHANDLE bch, char *errMsg)
{
	int i0 = m_LastOK;
	int id;
	int errcode;
	if (i0<0)
		i0=0;
	for (id=i0;;)
	{
		if (!m_bSvrReg || isLinkOK(id)>0)
		{
			if (BCCallNext(bch,m_AckTime,&errcode,errMsg))
			{
				m_LastOK = id;
				return(id);
			}
		}
		if (++id>=m_nDRTPs)
			id = 0;
		if (id==i0)
		{
			sprintf(errMsg,"Fail to CallNext:%d!",errcode);
			return(-1);
		}
	}
}