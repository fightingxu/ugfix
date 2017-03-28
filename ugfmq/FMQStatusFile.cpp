// FMQStatusFile.cpp: implementation of the CFMQStatusFile class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "xpub.h"
#include "FMQStatusFile.h"

#include <sys/stat.h>

#ifdef _MSC_VER
#include <direct.h>
#define PATHMARK '\\'
#else
#include <sys/types.h>
#include <dirent.h>
#define PATHMARK '/'
#endif

#include <fcntl.h>
#include <sys/stat.h>
#ifdef _MSC_VER
#include <share.h>
#define sh_fopen(a,b,c) _fsopen(a,b,c)
#include <io.h>
#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#else
#include <unistd.h>
#define SH_DENYNO    0x40
#define SH_DENYWR    0x20
#define sh_fopen(a,b,c) fopen(a,b)
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFMQStatusFile::CFMQStatusFile()
{
   m_handle = -1;
   memset(&status,0,sizeof(status));
}

CFMQStatusFile::~CFMQStatusFile()
{
   if (m_handle!=-1)
   {
      close(m_handle);
      m_handle = -1;
   }
}

int CFMQStatusFile::Open(const char *path, const char *sid, bool bOut)
{
   char file[256];
   if (m_handle!=-1)
      return(m_handle); // 表示已经打开了的
   memset(&status,0,sizeof(status));
   sprintf(file,"%s%c%s",path,PATHMARK,sid);
   m_handle = sh_open(file,O_CREAT|O_RDWR,SH_DENYNO);
   if (m_handle!=-1)
   {
//      m_bOut = bOut;
      if (bOut)
      {
         status.byteid = LBYTEID;
         status.lasttime = time(NULL);
         write(m_handle,&status,sizeof(status));
      }
      else
      {
         read(m_handle,&status,sizeof(status));
      }
   }
   return(m_handle);
}



int CFMQStatusFile::OutStatus()
{
   if (m_handle==-1)
      return(-1);
//   if (m_bOut)
   {
      status.lasttime = time(NULL);
      lseek(m_handle,0,SEEK_SET);
      return(write(m_handle,&status,sizeof(status)));
   }
//    else
//       return(-2); // 错误的调用
}

int CFMQStatusFile::InStatus()
{
   if (m_handle==-1)
      return(-1);
//    if (m_bOut)
//    {
//       return(-2); // 错误的调用
//    }
   lseek(m_handle,0,SEEK_SET);
   if (read(m_handle,&status,sizeof(status))==sizeof(status))
   {
      return(sizeof(status));
   }
   return(-3);
}
