// BUShm.cpp: implementation of the CBUShm class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifdef _MSC_VER
#include <windows.h>
#include <share.h>
#include <io.h>
#include <sys/locking.h>

#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#define LT_LOCK      _LK_NBLCK
#define LT_UNLOCK    _LK_UNLCK
#else
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/shm.h>

#define SH_DENYNO    0x40
#define SH_DENYRW    0x10
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#define LT_LOCK   F_WRLCK
#define LT_UNLOCK F_UNLCK
#endif

#include "BUShm.h"

#define BUSHM_KID 16
#define BUSHM_FLAG 0
#define SHM_RIGHT 0777

#define LOCK_POSITION 0x40000000L
#define MAX_FILELEN   0x3FFFFFFFL


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBUShm::CBUShm()
{
   m_address = NULL;
   m_fileno = -1;
   m_shmid = INVALID_ID;
   m_size = 0;
}

CBUShm::~CBUShm()
{
   Close();
}


void CBUShm::Close()
{
#ifdef _MSC_VER
   if (m_address!=NULL)
   {
      UnmapViewOfFile(m_address);
      m_address = NULL;
   }
   /* Removed by CHENYH @ 2013/4/24 16:56:02
   if (m_shmid!=INVALID_ID)
   {
      CloseHandle(m_shmid);
      m_shmid = INVALID_ID;
   }
   */
#else
   if (m_address!=NULL)
   {
      // 先detach
      shmdt(m_address);
   }
   m_address = NULL; 
   m_shmid = INVALID_ID;
   m_size = 0;
#endif
   if (m_fileno!=-1)
   {
      close(m_fileno);
      m_fileno = -1;
   }
}



char * CBUShm::GetMessage()
{
   return(m_szmsg);
}

void * CBUShm::GetSHMPtr()
{
   return(m_address);
}



key_t CBUShm::myftok(const char *path, int ID)
{
	int  handle;
/* ****** Updated by CHENYH at 2005-11-21 21:14:21 ****** 
	char buffer[255];
	char current_path[255];
	memset(buffer,0,sizeof(buffer));
	memset(current_path,0,sizeof(current_path));
	if(NULL != getcwd(current_path,sizeof(current_path)))
	{
	    sprintf(buffer,"%s/%s.shm",current_path,path);
	}
	else 
		sprintf(buffer,"/tmp/%s.shm",path);
   sprintf(buffer,"%s.shm",path);
*******************************************************/

	//handle=open(buffer,O_RDWR);
   handle = sh_open(path,O_RDWR,SH_DENYNO);
	if (handle == -1)
	{
      handle = sh_open(path,O_CREAT|O_RDWR,SH_DENYNO);
		if (handle == -1)
		{
			return -2;
		}
		else
		{
			close(handle);
		}
	}
	else
	{
		close(handle);
	}
#ifdef _MSC_VER
   return(1);
#else
	return ftok(path,ID);
#endif
}

void * CBUShm::Open(const char *name, size_t shmsize)
{
   char buf[256];
   Close();
   sprintf(buf,"%s.shm",name);
   m_fileno = sh_open(buf,O_CREAT|O_RDWR,SH_DENYNO);
   if (m_fileno==-1)
   {
      sprintf(m_szmsg,"Cannot open SHM File for '%s' size=%u",name,shmsize);
      return(NULL);
   }
#ifdef _MSC_VER
   int i;
   for (i=0;i<sizeof(buf);i++)
   {
      if ('\\'==buf[i])
         buf[i]='_';
      else if (0==buf[i])
         break;
   }
   if (shmsize>0)
   {
      INT64 lsize=shmsize;  // TMD: 竟然必须要用一个临时变量才能正常执行移位操作 2013/2/5 15:32:57
      unsigned int ssh,ssl;
      ssh = (unsigned int)(lsize>>32);
      ssl = (unsigned int)(lsize&0xFFFFFFFF);
      m_shmid = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,ssh,ssl,(LPCSTR)buf);
      if (m_shmid==NULL)
      {
         // 共享内存创建错误：
         sprintf(m_szmsg,"Cannot open share memory for SHM(%s) size=%u (%u,%u) -errno:%u!",buf,shmsize,ssh,ssl,GetLastError());
         Close();
         return(NULL);
      }
   }
   else
   {
      m_shmid = OpenFileMapping(FILE_MAP_WRITE|FILE_MAP_READ,FALSE,(LPCSTR)buf);
      if (m_shmid==NULL)
      {
         sprintf(m_szmsg,"Cannot open share memory for SHM(%s) - errno:%u!",buf,GetLastError());
         Close();
         return(NULL);
      }
   }
   m_address = MapViewOfFile(m_shmid,FILE_MAP_WRITE|FILE_MAP_READ,0,0,0);
   if (m_address==NULL)
   {
      sprintf(m_szmsg,"MapViewOfFile fail [SHM(%s) size=%u] - errno:%u!",buf,shmsize,GetLastError());
      Close();
      return(NULL);
   }
   BY_HANDLE_FILE_INFORMATION finfo;
   GetFileInformationByHandle(m_shmid,&finfo);
   m_size = ((size_t)finfo.nFileSizeHigh<<32)+finfo.nFileSizeLow;
   return(m_address);
#else
   fchmod(m_fileno,0666);  // 期货: 希望监控服务器能够运行ksmbcc show之类的命令，因此，这里也就需要扩展获得文件ftok的权限等
   bool bcreated = true;
   key_t shmkey = myftok(buf,BUSHM_KID);
   if (shmsize>0)
   {
      m_shmid = shmget(shmkey,shmsize,SHM_RIGHT|IPC_CREAT);
   }
   else
      m_shmid = -1;
   if (m_shmid==-1)
   {
      m_shmid = shmget(shmkey,0,BUSHM_FLAG);
      bcreated = false;
   }
   if (m_shmid==-1)
   {
      // 共享内存创建错误：
      sprintf(m_szmsg,"Cannot open share memory for key:0x%X-errno:%d!",shmkey,errno);
      Close();
      return(NULL);
   }
   m_address = shmat(m_shmid,0,0);
#ifdef SHM_FAILED //11:50 2006-7-4 for HP_UX64 
   if (m_address==SHM_FAILED)
#else
   if (m_address==(void *)-1L)
#endif
   {
      m_address = NULL;
      // 则表示挂接的地址出现问题，可能属于flag不正确的缘故
      sprintf(m_szmsg,"shmkey=%x:shmat(%d,0,0) 返回错误errno=%d!",shmkey,m_shmid,errno);
      Close();
      if (bcreated)
         Remove(name);
   }
   struct shmid_ds info;
   shmctl(m_shmid,IPC_STAT,&info);
   m_size = info.shm_segsz;
   return(m_address);
#endif
}

bool CBUShm::Remove(const char *name)
{
#ifdef _MSC_VER
   return(true);  // Windows下似乎一旦无进程在使用该共享内存块，则就自动消亡，因此，没有必要做删除处理
#else
   char buf[256];
   sprintf(buf,"%s.shm",name);
   key_t shmkey = myftok(buf,BUSHM_KID);
   int shmid = shmget(shmkey,0,BUSHM_FLAG);
   if (shmid!=-1)
   {
      if (shmctl(shmid,IPC_RMID,0)==-1)
         return(false);
   }
   remove(buf);
   return(true);
#endif
}

bool CBUShm::locktype(int ltype, unsigned int offset, unsigned int len)
{
#ifdef _MSC_VER
   _lseek(m_fileno,offset,SEEK_SET);
   return (_locking(m_fileno,ltype,len)==0);
#else
   struct flock lck;
   lck.l_type = ltype;
   lck.l_whence = SEEK_SET;
   lck.l_start = offset;
   lck.l_len = len;
   lck.l_pid = getpid();
   return (fcntl(m_fileno,F_SETLK,&lck)==0);
#endif
}

bool CBUShm::Lock(int offset, int len)
{
   unsigned int loff;
   unsigned int llen;
   if (offset<=0)
      loff = LOCK_POSITION;
   else
      loff = LOCK_POSITION+offset;
   if (len<=0)
   {
      loff = LOCK_POSITION;
      llen = MAX_FILELEN;
   }
   else
      llen = len;
   return(locktype(LT_LOCK,loff,llen));
}

bool CBUShm::Unlock(int offset, int len)
{
   unsigned int loff;
   unsigned int llen;
   if (offset<=0)
      loff = LOCK_POSITION;
   else
      loff = LOCK_POSITION+offset;
   if (len<=0)
   {
      loff = LOCK_POSITION;
      llen = MAX_FILELEN;
   }
   else
      llen = len;
   return(locktype(LT_UNLOCK,loff,llen));
}

// 2007-10-9 11:29:17 added by CHENYH @ Beijing
int CBUShm::GetID()
{
	return((int)m_shmid);
}

size_t CBUShm::GetSize()
{
	return(m_size);
}

int CBUShm::GetNumberAttach()
{
#ifdef _MSC_VER
	if (m_shmid==NULL)
		return(-1);
   BY_HANDLE_FILE_INFORMATION finfo;
   GetFileInformationByHandle(m_shmid,&finfo);
	return((int)finfo.nNumberOfLinks);
#else
	if (m_shmid==-1)
		return(-1);
   struct shmid_ds info;
   shmctl(m_shmid,IPC_STAT,&info);
	return(info.shm_nattch);
#endif
}
