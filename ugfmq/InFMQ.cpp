// InFMQ.cpp: implementation of the CInFMQ class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "InFMQ.h"
#ifdef _MSC_VER
#define PATHMARK '\\'
#else
#define PATHMARK '/'
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInFMQ::CInFMQ()
{
   m_handle = -1;
}

CInFMQ::~CInFMQ()
{
   Close();
}

int CInFMQ::Open(const char *path, const char *name)
{
   char file[256];
   Close();
   sprintf(file,"%s%c%s",path,PATHMARK,name);
   return(FMQOpenIncoming(file,&m_handle));
}

void CInFMQ::Close()
{
   if (m_handle>=0)
   {
      FMQClose(m_handle);
      m_handle = -1;
   }
}

bool CInFMQ::IsReset()
{
   return(FMQIsReset(m_handle)==1);
}

int CInFMQ::Read(int msgno, char *msgbuf, unsigned int msgsize, char *flag)
{
   return(FMQReadMessage(m_handle,msgno,msgbuf,msgsize,flag));
}

int CInFMQ::Recv(int msTimeout, char *msgBuf, int msgsize)
{
   int rtn;
   if ((rtn=FMQRecvMessageEx(m_handle,msTimeout,&msgsize,msgBuf,1))==KSFMQ_OK)
      return(msgsize);
   else
      return(rtn);
}

int CInFMQ::Size()
{
   return(FMQSize(m_handle));
}

int CInFMQ::RMsgs()
{
   return(FMQRSMsgs(m_handle));
}
