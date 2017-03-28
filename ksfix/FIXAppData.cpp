// FIXAppData.cpp: implementation of the CFIXAppData class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "FIXAppData.h"

bool g_FFSDSync=false;


//#define FIXAppDataTest
#ifdef FIXAppDataTest
const char appdata[]="35=D.115=ML.116=OBOCID.50=UUID1.52=20120522-06:11:00.148.11=0040000088.109=00500045.1=1800000045.21=1.55=000001.207=SZ.54=1.60=20120522-05:44:22.38=1000.40=2.44=13.0100.15=CNY.10101=1337665462.";
#define LOCALID "CYHUG"
#define PARTNER "GL"
int main()
{
   CFIXAppData test;
   char fdata[8000];
   int len;
   int i,sno,ib;
   int isno,osno;
   char sAPMain[20];
   char sAPBack[20];
   isno = osno = 0;
   strcpy(sAPBack,"apback");
   strcpy(sAPMain,"apmain");
   test.Init(sAPMain,sAPBack);
   test.GetLastSeqNo(isno,osno);
   i = isno; 
   if (i<osno) i = osno;
   for (ib=0;ib<2000;++ib)
   {
      ++i;
      test.SetSeqNo(i,i);
      if ((i%3)==1)
      {
         isno = sno = i;
         len = sprintf(fdata,"34=%d\00149=%s\00156=%s\001%s",sno,PARTNER,LOCALID,appdata);
         test.Put(FAD_IN,sno,fdata,len);
      }
      if ((i%3)==2)
      {
         osno = sno = i;
         len = sprintf(fdata,"34=%d\00149=%s\00156=%s\001%s",sno,LOCALID,PARTNER,appdata);
         test.Put(FAD_OUT,sno,fdata,len);
      }
      if (osno>10 && osno<20)
      {
         printf("\n(PutTesting)Enter any key to continue(InSeqNo=%d,OutSeqNo=%d)...",isno,osno);
         getch();
      }
   }
   printf("\n(End of PutTest)Enter any key to continue(InSeqNo=%d,OutSeqNo=%d)...",isno,osno);
   getch();

   printf("\nEnter any key to continue(GetCount(IN)=%d,GetCount(OUT)=%d)",
      test.GetCount(FAD_IN),test.GetCount(FAD_OUT));
   getch();

   osno = sno = osno+10;
   len = sprintf(fdata,"34=%d\00149=%s\00156=%s\001%s",sno,LOCALID,PARTNER,appdata);
   test.Put(FAD_OUT,sno,fdata,len);
   test.SetSeqNo(-1,osno);

   printf("\n(GetCount(IN)=%d,GetCount(OUT)=%d)",
      test.GetCount(FAD_IN),test.GetCount(FAD_OUT));
   i = test.GetCount(FAD_OUT);
   len = test.GetData(FAD_OUT,i-2,&sno,fdata,sizeof(fdata));
   fdata[len]='\0';
   printf("\nOutMsg[%d](SeqNo=%d):'%s'",i-2,sno,fdata);
   printf("\nEnter any key to continue...");
   getch();

   //////////////////////////////////////////////////////////////////////////
   // 测试一下效率:)
   printf("\nNeed FSYNC ?...");
   switch (getch())
   {
   case 'y':
   case 'Y':
      g_FFSDSync = true;
      break;
   }

   TICKUS t1 = GetTickCountUS();
   test.EndOfDay();
   TICKUS t2 = GetTickCountUS();
   printf("\nEndOfDay() took %uUS\nBegin to put 1000 Msgs...",DiffTCUS(t2,t1));

   t1 = GetTickCountUS();
   for (sno=1;sno<=1000;++sno)
   {
      len = sprintf(fdata,"34=%d\00149=%s\00156=%s\001%s",sno,LOCALID,PARTNER,appdata);
      test.Put(FAD_OUT,sno,fdata,len);
      test.SetSeqNo(-1,sno);
   }
   t2 = GetTickCountUS();
   printf("took %uUS\nClose...",DiffTCUS(t2,t1));
   
   t1 = GetTickCountUS();
   test.Close();
   t2 = GetTickCountUS();
   printf("took %uUS\n",DiffTCUS(t2,t1));
   return(0);
}
/*****************************
性能指标测试: 在Windows 7 (64位) - Sony VPCSD
---------------------------------------------
不做SYNC:
EndOfDay() took 4120US  -- 4.12ms
Begin to put 1000 Msgs...took 55947US -- 55.95ms
Close...took 33423US -- 33.42ms
---------------------------------------------
做SYNC: -- 在DELL公司笔记本上，可能由于硬盘加密，导致非常慢: 1000 Msgs: 194.67s / DELL的台式机上 4.74s
EndOfDay() took 10438US -- 10.44ms
Begin to put 1000 Msgs...took 5428148US -- 5.43s
Close...took 33360US -- 33.36ms
*****************************/
#endif


#include <fcntl.h>
#include <sys/stat.h>
#ifdef WIN32
#include <share.h>
#define sh_fopen(a,b,c) _fsopen(a,b,c)
#include <io.h>
#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#else
#define SH_DENYNO    0x40
#define SH_DENYWR    0x20
#define sh_fopen(a,b,c) fopen(a,b)
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif

#ifdef _MSC_VER
#include <direct.h>
#include <process.h>
#define PATH_MARK '\\'
#else
#include <sys/types.h>
#include <dirent.h>
#define PATH_MARK '/'
#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif



void FileSync(FILE *fp)
{
   fflush(fp);
   if (g_FFSDSync)
   {
      int fno = fileno(fp);
#ifdef _MSC_VER
      _commit(fno);
#else
      fsync(fno);
#endif
   }
}

bool UpdateCheckPath(char *path, char *defsub)
{
   char tmp[MAX_PATH];
   int l;
   
   if (path[0]=='\0')
   {
      if (getcwd(tmp,sizeof(tmp))!=NULL)
      {
         if (defsub==NULL)
         {
            sprintf(path,"%s%c%s",tmp,PATH_MARK,"sub");
         }
         else
         {
            sprintf(path,"%s%c%s",tmp,PATH_MARK,defsub);
         }
      }
   }
   if (access(path,0)!=0)
   {
#ifdef _MSC_VER
      if (mkdir(path)!=0)
#else
      if (mkdir(path,0777)!=0)
#endif
      {
         printf("Cannot create direct <%s> - error:%d <%s>!\n",path,errno,strerror(errno));
         return(false);
      }
   }
   l = strlen(path);
   if (path[l-1]!=PATH_MARK)
   {
      //strcat(path,"/");
      //sprintf(path+l,"%c",PATH_MARK);
      path[l++]=PATH_MARK;
      path[l]='\0';
   }
   return(true);
}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIXAppData::CFIXAppData()
{

}

CFIXAppData::~CFIXAppData()
{

}

bool CFIXAppData::SetEODTime(time_t tmEOD)
{
   if (m_Back.IsOpened())
      m_Back.SetEODTime(tmEOD);
   return(m_Main.SetEODTime(tmEOD));
}

bool CFIXAppData::SetSeqNo(int InSeqNo, int OutSeqNo)
{
   if (m_Back.IsOpened())
   {
      m_Back.SetSeqNo(InSeqNo,OutSeqNo);
   }
   return(m_Main.SetSeqNo(InSeqNo,OutSeqNo));
}

// Function name: CFIXAppData::Put
// Author       : CHENYH 2012/5/22 16:50:16
// Description  : 将新的应用消息，进行持久化
// 返回  : int : 返回数据存储的实际长度；
//           0: 数据块存储单元没有正常打开；
//          <0: 写入异常；
// 参数  : int in_out [IN]: FAD_IN / FAD_OUT
// Argument : unsigned int seqno [IN]: 消息序号seqno - key
// Argument : const char *fixdata [IN]: 应用消息具体数据
// Argument : int fdlen [IN]: fixdata中消息的字节数
int CFIXAppData::Put(int in_out, unsigned int seqno, const char *fixdata, int fdlen)
{
   if (m_Back.IsOpened())
   {
      m_Back.Put(in_out,seqno,fixdata,fdlen);
   }
   return(m_Main.Put(in_out,seqno,fixdata,fdlen));
}


bool CFIXAppData::Init(char *path, char *bkpath)
{
   m_Back.Open(bkpath);
   return(m_Main.Open(path));
}


// 函数名: CFIXAppData::EndOfDay
// 编程  : 陈永华 2012-5-24 15:28:55
// 描述  : 将持久化的数据清空，并且将序号置0
// 返回  : bool 
bool CFIXAppData::EndOfDay()
{
   if (m_Back.IsOpened())
   {
      m_Back.EndOfDay();
   }
   return(m_Main.EndOfDay());
}


int CFIXAppData::GetCount(int in_out)
{
   return(m_Main.GetCount(in_out));
}

int CFIXAppData::GetData(int in_out, int number, int *seqno, char *data, int dsize)
{
   T_RECINDEX ridx;
   int rtn;
   *seqno = 0;
   if ((rtn=m_Main.GetIndex(in_out,number,&ridx))>0)
   {
      *seqno = ridx.seqno;
      rtn = m_Main.GetData(in_out,&ridx,data,dsize);
      if (rtn<0)
         rtn -= 2; // 跳过重叠部分
   }
   return(rtn);
}

bool CFIXAppData::GetLastSeqNo(int &InSeqNo, int &OutSeqNo)
{
   return (m_Main.GetLastSeqNo(InSeqNo,OutSeqNo));
}


time_t CFIXAppData::GetLastEODTime()
{
   return(m_Main.m_tmLastEOD);   
}

//////////////////////////////////////////////////////////////////////
// CFIXFileStore Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFIXFileStore::CFIXFileStore()
{
   m_fSeqNo = NULL;
   m_InSeqNo = 0;
   m_OutSeqNo = 0;
   m_tmLastEOD = 0;
}

CFIXFileStore::~CFIXFileStore()
{
   Close();
}

void CFIXFileStore::Close()
{
   m_In.close();
   m_Out.close();

   if (m_fSeqNo!=NULL)
   {
      fclose(m_fSeqNo);
      m_fSeqNo = NULL;
   }
   m_InSeqNo = 0;
   m_OutSeqNo = 0;
}

#define FAD_SEQNO    "STATUS"
#define FAD_INIDX    "IN.idx"
#define FAD_INDAT    "IN.dat"
#define FAD_OUTIDX   "OUT.idx"
#define FAD_OUTDAT   "OUT.dat"
bool CFIXFileStore::Open(char *path)
{
   Close();
   if (path==NULL||path[0]=='\0')
      return(true);
   UpdateCheckPath(path,"ksfd");
   m_path = path;
   m_fSeqNo = fdopen(FAD_SEQNO,"r+b");
   if (m_fSeqNo==NULL)
   {
      m_fSeqNo = fdopen(FAD_SEQNO,"w+b");
      if (m_fSeqNo==NULL)
         return(false);
      SetSeqNo(0,0);
   }
   RestoreSeqNo();

   if (OpenFDFiles(&m_In,FAD_INIDX, FAD_INDAT)
      && OpenFDFiles(&m_Out,FAD_OUTIDX,FAD_OUTDAT))
   {
      return(true);
   }
   Close();
   return(m_fSeqNo!=NULL);
}


bool CFIXFileStore::OpenFDFiles(T_FFSDATA *pfg, const char *idxfile, const char *datfile)
{
   pfg->m_fData = fdopen(datfile,"r+b");
   if (pfg->m_fData==NULL)
   {
      pfg->m_fData = fdopen(datfile,"w+b");
   }
   fseek(pfg->m_fData,0,SEEK_END);
   pfg->m_DatEnd = ftell(pfg->m_fData);

   pfg->m_fIdx = fdopen(idxfile,"r+b");
   if (pfg->m_fIdx==NULL)
   {
      pfg->m_fIdx = fdopen(idxfile,"w+b");
   }
   fseek(pfg->m_fIdx,0,SEEK_END);
   pfg->m_IdxEnd = (ftell(pfg->m_fIdx)/FFSIDXUNITLEN)*FFSIDXUNITLEN;
   fseek(pfg->m_fIdx,pfg->m_IdxEnd,SEEK_SET);

   return(pfg->m_fData!=NULL && pfg->m_fIdx!=NULL);
}


FILE * CFIXFileStore::fdopen(const char *filename, const char *mode)
{
   char file[MAX_PATH];
   sprintf(file,"%s%s",m_path.c_str(),filename);
   return(sh_fopen(file,mode,SH_DENYNO));
}

bool CFIXFileStore::SetSeqNo(int InSeqNo, int OutSeqNo)
{
   if (InSeqNo>=0)
   {
      if (m_InSeqNo>InSeqNo)
      {
         m_In.Truncate(InSeqNo);
      }
      m_InSeqNo = InSeqNo;
   }
   if (OutSeqNo>=0)
   {
      if (m_OutSeqNo>OutSeqNo)
      {
         m_Out.Truncate(OutSeqNo);
      }
      m_OutSeqNo = OutSeqNo;
   }
   if (m_fSeqNo!=NULL)
   {
      if (fseek(m_fSeqNo,0,SEEK_SET)!=0
         || fprintf(m_fSeqNo,"%d\n%d\n%u\n",m_InSeqNo,m_OutSeqNo,(unsigned int)m_tmLastEOD)<0)
      {
         Close();
      }
      else
      {
         chsize(fileno(m_fSeqNo),ftell(m_fSeqNo));
         FileSync(m_fSeqNo);
      }
   }
   return(m_fSeqNo!=NULL);
}

bool CFIXFileStore::RestoreSeqNo()
{
   char buf[40];
   m_InSeqNo = m_OutSeqNo = 0;
   if (m_fSeqNo!=NULL)
   {
      fseek(m_fSeqNo,0,SEEK_SET);
      buf[0]='\0';
      fgets(buf,sizeof(buf),m_fSeqNo);
      m_InSeqNo = atoi(buf);
      buf[0]='\0';
      fgets(buf,sizeof(buf),m_fSeqNo);
      m_OutSeqNo = atoi(buf);
      buf[0]='\0';
      fgets(buf,sizeof(buf),m_fSeqNo);
      m_tmLastEOD = atoui(buf);
   }
   return(m_fSeqNo!=NULL);
}



T_FFSDATA::T_FFSDATA()
{
   m_fData = NULL;
   m_fIdx = NULL;
   m_DatEnd = -2;
   m_IdxEnd = -2;
}

T_FFSDATA::~T_FFSDATA()
{
   close();
}

void T_FFSDATA::close()
{
   if (m_fData!=NULL)
   {
      fclose(m_fData);
      m_fData = NULL;
   }
   m_DatEnd = -1;
   if (m_fIdx!=NULL)
   {
      fclose(m_fIdx);
      m_fIdx = NULL;
   }
   m_IdxEnd = -1;
}


// 函数名: T_FFSDATA::AddData
// 编程  : 陈永华 2012-5-24 0:12:14
// 描述  : 持久化一个数据块单元 - DataUnit
// 返回  : int : 返回数据存储的实际长度；
//           0: 数据块存储单元没有正常打开；
//          <0: 写入异常；
// 参数  : unsigned int seqno [IN]: 数据块的序号
// 参数  : int length [IN]: 数据块的长度
// 参数  : const char *data [IN]: 存放存储的数据块
int T_FFSDATA::AddData(unsigned int seqno, int length, const char *data)
{
   if (m_fData==NULL||m_fIdx==NULL)
      return(0);
   fseek(m_fData,0,SEEK_END);
   m_DatEnd = ftell(m_fData);
   fprintf(m_fData,"%-10u:",seqno);  // 10个字节的seqno区域+':' = 11字节
   int rtn = fwrite(data,1,length,m_fData)+FFSDATHEAD;
   FileSync(m_fData);
   fseek(m_fIdx,m_IdxEnd,SEEK_SET);
   //fseek(m_fIdx,0,SEEK_END);
   fprintf(m_fIdx,"%-10u:%-10u,%-10d",
      seqno,m_DatEnd,rtn);
   FileSync(m_fIdx);
   m_DatEnd += rtn;
   m_IdxEnd += FFSIDXUNITLEN;
   return(rtn-FFSDATHEAD);
}


// 函数名: T_FFSDATA::GetData
// 编程  : 陈永华 2012-5-24 0:06:52
// 描述  : 根据当前数据索引读取指定的数据块
/* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
   0 : 本数据块存储单元没有正常打开；
   -5: 不能定位到指定的数据文件位置；
   -6: 读取数据块seqno检查的数据；
   -7: 索引中的seqno和数据块seqno值不符；
   -8: 索引数据中的长度超过dsize值
   -9: 读取指定长度的数据块失败
*****************************************************/
// 参数  : T_RECINDEX *pIdx [IN]: 即这块数据索引IndexUnit；(length已经扣除了FFSDATHEAD)
// 参数  : char *data [OUT]: 存放数据块的缓存；
// 参数  : int dsize [IN]: data数据块可缓存的最大长度；
int T_FFSDATA::GetData(T_RECINDEX *pIdx, char *data, int dsize)
{
   if (m_fData==NULL||m_fIdx==NULL)
      return(0);
   if (pIdx->length>dsize)
      return(-8);
   if (fseek(m_fData,pIdx->pos,SEEK_SET)!=0)
      return(-5);
   if (fread(data,1,FFSDATHEAD,m_fData)!=FFSDATHEAD)
      return(-6);
   if (pIdx->seqno!=atoi(data))
      return(-7);
   if (fread(data,1,pIdx->length,m_fData)!=pIdx->length)
      return(-9);
   return(pIdx->length);
}

bool CFIXFileStore::IsOpened()
{
   return(m_fSeqNo!=NULL);
}

int CFIXFileStore::Put(int in_out, unsigned int seqno, const char *fixdata, int fdlen)
{
   if (in_out==FAD_IN)
   {
      return(m_In.AddData(seqno,fdlen,fixdata));
   }
   else
   {
      return(m_Out.AddData(seqno,fdlen,fixdata));
   }
}


// 函数名: CFIXFileStore::EndOfDay
// 编程  : 陈永华 2012-5-24 15:28:13
// 描述  : 清空文件持久化数据内容，并将序号置0
// 返回  : bool 
bool CFIXFileStore::EndOfDay()
{
   if (m_fSeqNo!=NULL)
   {
      m_In.EndOfDay();
      m_Out.EndOfDay();
      m_tmLastEOD = time(NULL);
      return(SetSeqNo(0,0));      
   }
   return(false);
}


// 函数名: T_FFSDATA::EndOfDay
// 编程  : 陈永华 2012-5-24 15:22:42
// 描述  : 清空数据索引和数据持久化的内容
// 返回  : bool 
bool T_FFSDATA::EndOfDay()
{
   m_IdxEnd = 0;
   m_DatEnd = 0;
   if (m_fIdx!=NULL)
   {
      chsize(fileno(m_fIdx),0);
      chsize(fileno(m_fData),0);
   }
   return(m_fIdx!=NULL);
}



int T_FFSDATA::GetCount()
{
   int rtn=0;
   if (m_fIdx!=NULL)
   {
      rtn = filelength(fileno(m_fIdx))/FFSIDXUNITLEN;
      assert(rtn==(m_IdxEnd/FFSIDXUNITLEN));
   }
   return(rtn);
}


// 函数名: T_FFSDATA::GetIndex
// 编程  : 陈永华 2012-5-24 15:44:29
// 描述  : 取指定序号的数据索引数据
/* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
   0 : 本数据块存储单元没有正常打开；
   -1: 不能读取完整的Index单元；
   -2: IndexUnit中的seqno异常；
   -3: IndexUnit中数据位置异常；
   -4: IndexUnit中数据长度值异常；
   -5: 指定数据索引序号越界 (0 - GetCount()-1)
   -6: 定位数据索引位置失败
*****************************************************/
// 参数  : int number [IN]: 指定数据索引编号: 0 -- GetCount()-1
// 参数  : T_RECINDEX *pIdx [OUT]: 返回数据索引
int T_FFSDATA::GetIndex(int number, T_RECINDEX *pIdx)
{
   char data[40];
   if (m_fData==NULL||m_fIdx==NULL)
      return(0);
   if (number<0||number>=(m_IdxEnd/FFSIDXUNITLEN))
      return(-5);
   if (fseek(m_fIdx,number*FFSIDXUNITLEN,SEEK_SET)!=0)
      return(-6);
   if (fread(data,1,FFSIDXUNITLEN,m_fIdx)!=FFSIDXUNITLEN)
      return(-1);
   data[FFSIDXUNITLEN]='\0';
   pIdx->seqno = atoi(data);
   pIdx->pos = atoi(data+11);
   pIdx->length = atoi(data+22);
   if (pIdx->seqno<=0)
      return(-2);
   if (pIdx->pos<0)
      return(-3);
   pIdx->length -= FFSDATHEAD;
   if (pIdx->length<=0)
      return(-4);
   return(pIdx->length);
}

int CFIXFileStore::GetIndex(int in_out, int number, T_RECINDEX *pIdx)
{
   if (in_out==FAD_IN)
      return(m_In.GetIndex(number,pIdx));
   else
      return(m_Out.GetIndex(number,pIdx));
}

int CFIXFileStore::GetCount(int in_out)
{
   if (in_out==FAD_IN)
      return(m_In.GetCount());
   else
      return(m_Out.GetCount());
}

int CFIXFileStore::GetData(int in_out, T_RECINDEX *pIdx, char *data, int dsize)
{
   if (in_out==FAD_IN)
      return(m_In.GetData(pIdx,data,dsize));
   else
      return(m_Out.GetData(pIdx,data,dsize));
}

void CFIXAppData::Close()
{
   if (m_Back.IsOpened())
   {
      m_Back.Close();
   }
   m_Main.Close();
}


bool CFIXFileStore::GetLastSeqNo(int &InSeqNo, int &OutSeqNo)
{
   InSeqNo = m_InSeqNo;
   OutSeqNo = m_OutSeqNo;
   return(m_InSeqNo>=0 && m_OutSeqNo>=0);
}

bool CFIXFileStore::SetEODTime(time_t tmEOD)
{
   m_tmLastEOD = tmEOD;
   return(SetSeqNo(-1,-1));
}


int T_FFSDATA::Truncate(int seqno)
{
   int i;
   T_RECINDEX idx;
   for (i=0;;++i)
   {
      if (GetIndex(i,&idx)<=0)
         break;
      if (idx.seqno>seqno)
      {
         m_IdxEnd = i*FFSIDXUNITLEN;
         chsize(fileno(m_fIdx),m_IdxEnd);
         if (m_fData!=NULL)
         {
            m_DatEnd = idx.pos;
            chsize(fileno(m_fData),m_DatEnd);
         }
         break;
      }
   }
   return(i);
}
