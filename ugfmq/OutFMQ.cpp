// OutFMQ.cpp: implementation of the COutFMQ class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include "OutFMQ.h"
#ifdef _MSC_VER
#define PATHMARK '\\'
#else
#define PATHMARK '/'
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutFMQ::COutFMQ()
{
   m_handle = -1;
}

COutFMQ::~COutFMQ()
{
   Close();
}

void COutFMQ::Close()
{
   if (m_handle>=0)
   {
      FMQClose(m_handle);
      m_handle = -1;
   }
}

int COutFMQ::Open(const char *path, const char *name)
{
   char file[256];
   Close();
   sprintf(file,"%s%c%s",path,PATHMARK,name);
   return(FMQOpenOutgoing(file,&m_handle));
}

int COutFMQ::Reset(const char *path, const char *name)
{
   char file[256];
   Close();
   sprintf(file,"%s%c%s",path,PATHMARK,name);
   return(FMQCreate(file));
}

int COutFMQ::Read(int msgno, char *msgbuf, unsigned int msgsize, char *flag)
{
   return(FMQReadMessage(m_handle,msgno,msgbuf,msgsize,flag));
}

int COutFMQ::Send(int nMsgLen, const char *msgBuf)
{
   return(FMQSendMessage(m_handle,nMsgLen,(char *)msgBuf));
}

int COutFMQ::Size()
{
   return(FMQSize(m_handle));
}
