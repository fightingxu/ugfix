#include "stdafx.h"
#include "mypub.h"

#include <sys/stat.h>

#ifdef _MSC_VER
#include <sys/timeb.h>
#include <direct.h>
#define PATHMARK  '\\'
#define MAKEPATH(a) mkdir(a)
#else
#include <sys/types.h>
#include <dirent.h>
#define PATHMARK  '/'
#define MAKEPATH(a) mkdir(a,0777)
#endif



#ifdef _MSC_VER
#include <conio.h>

void setnoblockgetch()
{
}

int mygetch()
{
   if (kbhit())
      return(getch());
   else return(0);
}
#else
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

void setnoblockgetch()
{
   int oldstatus;
   oldstatus = fcntl(0,F_GETFL);
   fcntl(0,F_SETFL,oldstatus|O_NDELAY);
}

int mygetch()
{
   int rtn;
   char kbuf[2];
   rtn = read(0,kbuf,1);
   if (rtn<=0) return(0);
   else return(kbuf[0]);
}
#endif


int MyUpdateCheckPath(char *path,const char *defsub)
{
   char tmp[MAX_PATH];
   int l;
   
   if (path[0]=='\0')
   {
      if (getcwd(tmp,sizeof(tmp))!=NULL)
      {
         sprintf(path,"%s%c%s",tmp,PATHMARK,defsub);
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
            return(-1);
         }
   }
   l = strlen(path);
   if (path[l-1]!=PATHMARK)
   {
      //strcat(path,"/");
      //sprintf(path+l,"%c",PATH_MARK);
      path[l++]=PATHMARK;
      path[l]='\0';
   }
   return(0);
}



void GetTimeMillis(time_t *ptm, int *pmillis)
{
#ifdef _MSC_VER
   timeb tb;
   ftime (&tb);
   *ptm = tb.time;
   *pmillis = tb.millitm;
#else
   struct timeval tv;
   gettimeofday (&tv, 0);
   *ptm = tv.tv_sec;
   *pmillis = tv.tv_usec/1000;
#endif
}


// Function name: DateTime2TimeT
// Author       : CHENYH 2012/6/19 17:12:53
// Description  : ��YYYYMMDD-hh:mm:ssʱ��ת��Ϊtime_t
// Return type  : void 
// Argument : const char *sDateTime [IN]: YYYYMMDD-hh:mm:ss[.xxx]
// Argument : int isUTC [IN]: 0 - ����UTC��ʱ�䣻!=0 - ��UTCʱ��
// Argument : time_t *pTimeT [OUT]: ���ص�time_t��ֵ
void DateTime2TimeT(const char *sDateTime, int isUTC, time_t *pTimeT)
{
   struct tm tmTime;
   char tmp[20];

   memset(&tmTime,0,sizeof(tmTime));

   memcpy(tmp,sDateTime,4); tmp[4]='\0';
   tmTime.tm_year = atoi(tmp)-1900;
   memcpy(tmp,sDateTime+4,2); tmp[2]='\0';
   tmTime.tm_mon = atoi(tmp)-1;
   memcpy(tmp,sDateTime+6,2); tmp[2]='\0';
   tmTime.tm_mday = atoi(tmp);

   memcpy(tmp,sDateTime+9,2); tmp[2]='\0';
   tmTime.tm_hour = atoi(tmp);
   memcpy(tmp,sDateTime+12,2); tmp[2]='\0';
   tmTime.tm_min = atoi(tmp);
   memcpy(tmp,sDateTime+15,2); tmp[2]='\0';
   tmTime.tm_sec = atoi(tmp);

   *pTimeT = mktime(&tmTime);
   if (isUTC==0)
   {
      // ��sDateTime�Ǳ���ʱ��:
      *pTimeT -= 8*3600;
   }
}

void GetFormatDateTime(time_t tm, char *sFmtTime, int millis, int isUTC)
{
   struct tm gmt;
   if (isUTC)
      gmt = *gmtime(&tm);
   //memcpy(&gmt,gmtime(&tm),sizeof(gmt));
   else
      gmt = *localtime(&tm);
   //memcpy(&gmt,localtime(&tm),sizeof(gmt));
   if (millis<0)
   {
      sprintf(sFmtTime,"%d%02d%02d-%02d:%02d:%02d",
         gmt.tm_year+1900,
         gmt.tm_mon+1,
         gmt.tm_mday,
         gmt.tm_hour,gmt.tm_min,gmt.tm_sec);
   }
   else
   {
      sprintf(sFmtTime,"%d%02d%02d-%02d:%02d:%02d.%03d",
         gmt.tm_year+1900,
         gmt.tm_mon+1,
         gmt.tm_mday,
         gmt.tm_hour,gmt.tm_min,gmt.tm_sec,
         millis);
   }
}

// Function name: GetLocalDateTime
// Author       : CHENYH 2012/6/20 15:04:25
// Description  : ��ʱ��ת��Ϊ���ص� YYYYMMDD �� HH:MM:SS
// Return type  : void 
// Argument : time_t *pTime [IN]: ָ����ʱ��㣻NULL��Ϊ��ǰʱ��
// Argument : char *sLocalDate [OUT]: ���ر������� YYYYMMDD , NULL �򲻸�ֵ
// Argument : char *sLocalTime [OUT]: ���ر���ʱ�� HH:MM:SS , NULL �򲻸�ֵ
void GetLocalDateTime(void *pTime, char *sLocalDate, char *sLocalTime)
{
   struct tm tmTime;
   time_t timet;
   if (pTime==NULL)
   {
      timet = time(NULL);
   }
   else
   {
      timet = *(time_t *)pTime;
   }
   tmTime = *localtime(&timet);
   if (sLocalDate!=NULL)
   {
      strftime(sLocalDate,10,"%Y%m%d",&tmTime);
   }
   if (sLocalTime!=NULL)
   {
      // %H:%M:%S:
      strftime(sLocalTime,10,"%H:%M:%S",&tmTime);
   }
}


void GetFIXUTCDateTime(time_t tm, char *sUTCTime, int millis)
{
   GetFormatDateTime(tm, sUTCTime, millis, 1);
}



unsigned int atoui(char *pstr)
{
   unsigned int ui=0;
   char *pc=pstr;
   for (pc=pstr;*pc;++pc)
   {
      if ((*pc)>='0'&&(*pc)<='9')
      {
         ui = ui*10+(*pc)-'0';
      }
      else
      {
         if (ui>0)
            return(ui);
      }
   }
   return(ui);
}




/* ȥ�����ҿո�   */
char *mytrim(char *s)
{
	int i,len;

	len=strlen(s);
	for (i=len-1;i>=0;i--)
	{
      switch (s[i])
      {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
         s[i]=0;
         break;
      default:
         break;
      }
      if (s[i])
         break;
	}
	for (i=0; i<len; i++)
	{
		if ((s[i] != ' ') && (s[i] != '\t'))
			break;
	}
	if (i != 0)
	{
		strncpy(s,s+i,len-i);
		s[len-i]=0;
	}
	return s;
}

// ������: *Strncpy
// ���  : ������ 2004-2-21 13:39:08
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy(char *dest,const char *source,unsigned int count)
{
   strncpy(dest,source,count);
   dest[count-1]='\0';
   return(dest);
}


// ������: *Strncpy_t
// ���  : ������ 2004-2-21 13:39:12
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
//        ͬʱȥ�����ҿո�
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy_t(char *dest,const char *source,unsigned int count)
{
   mytrim(Strncpy(dest,source,count));
   return(dest);
}


// ������: mytrim_r
// ���  : ������ 2004-2-21 13:45:29
// ����  : ����ַ����ұߵ�' '��'\t'
// ����  : char *
// ����  : char *dest
char *mytrim_r(char *dest)
{
   int i;
   i = strlen(dest)-1;
   for (;i>=0;i--)
   {
      switch (dest[i])
      {
      case ' ':
      case '\t':
      case '\r':
      case '\n':
         dest[i]=0;
         break;
      default:
         break;
      }
      if (dest[i])
         break;
   }
   return(dest);
}


// ������: Strncpy_rt
// ���  : ������ 2004-2-21 13:46:22
// ����  : ���Ʋ����dest�ұߵ�' '��'\t'
// ����  : char * ����dest��ָ��
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy_rt(char *dest,char *source,unsigned int count)
{
   Strncpy(dest,source,count);
   return(mytrim_r(dest));
}

// ����  : ���÷ָ��separator�ָ�Ĵ��ַ���pc�У���ȡ��pid�����ַ�����para��
// ����  : int ��>0:true - ���ػ�ȡ�������ݴ�֮����Ǹ�λ�ã���'\0'��separatorλ�ã�0 :false��Ϊʧ��
// ����  : const char *pc [IN]: ���ַ��� �� "000,1,22, 333,4444"
// ����  : char separator [IN]: �ָ�� ��','
// ����  : int pid [IN]: Ҫ��ȡ�����ַ�������ţ���0��ʼ
// ����  : char *para [OUT]: ����ȡ���������ַ�������������pid=3�����ַ�������Ϊ" 333"
// ����  : int psize [IN]: para����ĳ��ȣ����ֽ�����ʾ
// ����  : char *rtnmsg [OUT]: ���ش�����Ϣ 
int GetSubString(const char *pc, char separator ,int pid, char *para, int psize, char *rtnmsg)
{
   int ip;
   int n=pid;
   // ����ǰ��������ֵ
   for (ip=0; n>0; ip++)
   {
      if (pc[ip]=='\0')
      {
         if (rtnmsg!=NULL)
            sprintf(rtnmsg,"���ַ���<%s>�У�û�е�(%d)������",pc,pid);
         return(0);
      }
      else if (pc[ip]==separator)
      {
         n--;
      }
   }

   /* ****** Updated by CHENYH at 2009-3-25 14:50:15 ****** 
   ��һ�����������Ƿָ�������ô�ö�Ӧ���Ǹ���""
   // �����ָ��
   if (pid>0 && pc[ip]==separator)
      ip++;
   */
   // ȡ�ַ���������
   for (n=0;pc[ip]!=separator && pc[ip]!='\0';ip++)
   {
      para[n++]=pc[ip];
      if (n>=psize)
      {
         if (rtnmsg!=NULL)
            sprintf(rtnmsg,"���ַ���<%s>�У�����[%d]���峬����������%d",pc,pid,psize);
         return(0);
      }
   }
   
   para[n]='\0';
   return(ip);
}


// ������: percolate
// ���  : ������ 2003-9-24 13:38:37
// ����  : ���ַ����н��Ƿ��ַ����˵���ͬʱ����//��Ϊ����Ϊע������Ҳͬ//һ����˵�
// ����  : int �������ĳ���
// ����  : char *str In��Out
int percolate(char *str)
{
   int l,i;
   l = strlen(str)-1;
   for (;l>=0;l--)
   {
      if ((unsigned char)(str[l])<0x20)
         str[l]='\0';
      else break;
   }
   for (i=0;i<=l;i++)
   {
      if (str[i]=='/' && str[i+1]=='/') 
      {
         str[i]='\0';
         break;
      }
   }
   return(i);
}

#define MAXUSLEEPUNIT 500000
// ������: mysleep
// ���  : ������ 2004-2-11 12:35:51
// ����  : ���߳̽���˯��״̬milliseconds����
// ����  : void 
// ����  : unsigned int milliseconds
void mysleep(unsigned int milliseconds)
{
#ifdef WIN32
   Sleep(milliseconds);
#else
//#ifdef AIX
//   struct timespec delay;
//   delay.tv_sec =0;
//   delay.tv_nsec = milliseconds*1000;
//   pthread_delay_np(&delay);
//#else
   /******* Updated by CHENYH at 2005-10-29 0:39:25 ******/
   // ����HP-UX����ʱ�򣬷���usleep��������Ĳ���ֵΪ1000000,
   // ��˲���ֱ����usleep(milliseconds*10000)������
   unsigned int i;
   milliseconds *= 1000;
   do {
   	if (milliseconds>MAXUSLEEPUNIT)
      {
         i = MAXUSLEEPUNIT;
      }
      else
      {
         i = milliseconds;
      }
      milliseconds -= i;
      usleep(i);
   } while(milliseconds>100);
   /*******************************************************/
   //usleep(milliseconds*1000);
//#endif
#endif
}

// ������: *getfmttime
// ���  : ������ 2003-10-14 11:23:47
// ����  : ��tm��ʱ��ת��Ϊ����ʱ��ĸ�ʽ���ַ���������ϵͳ��non-thread-safe
// ����  : char * ��ʽ�����ַ���ָ��, NULL ��ʹ���ڲ���̬�ռ��Ÿ�ʽ�����ַ�����
// ����  : time_t *ptm ����Ҫת����ʱ�� ==NULL ��Ϊת��ʱʱ���
// ����  : int fmttype 
/*
            0 : hh:mm:ss
            1 : MM/DD-hh:mm:ss
            2 : YYYY/MM/DD-hh:mm:ss
            3 : YYYYMMDD
            4 : hhmmss
            ���� : YYYYMMDDhhmmss
*/
// ����  : char *outstr ����ַ����Ļ��棬=NULL��ʹ���ڲ��ľ�̬���棬�䳤����Ҫ��fmttype����
char *getfmttime(void *ptm,int fmttype,char *outstr)
{
   static char tstr[80];
   struct tm tmloc;
   time_t timet;
   
   if (ptm==NULL)
   {
      ptm = &timet;
      time(&timet);
   }
   else
   {
      memcpy(&timet,ptm,sizeof(timet));
   }
   if (outstr==NULL)
   {
      outstr = tstr;
   }
   //localtime_r(&tm,&tmloc);
   memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
   if (fmttype==0)
   {
      // %H:%M:%S:
      strftime(outstr,79,"%H:%M:%S",&tmloc);
   }
   else if (fmttype==1)
   {
      // %m/%d-%H:%M:%S
      strftime(outstr,79,"%m/%d %H:%M:%S",&tmloc);
   }
   else if (fmttype==2)
   {
      strftime(outstr,79,"%Y/%m/%d %H:%M:%S",&tmloc);
   }
   else if (fmttype==3)
   {
      strftime(outstr,79,"%Y%m%d",&tmloc);
   }
   else if (fmttype==4)
   {
      strftime(outstr,79,"%H%M%S",&tmloc);
   }
   else 
   {
      strftime(outstr,79,"%Y%m%d%H%M%S",&tmloc);
   }
   return(outstr);
}


void DataDumpFile(const char *filename,const char *data,int datalen)
{
   FILE *fp;
   fp = fopen(filename,"a+b");
   if (fp!=NULL)
   {
      fwrite(data,1,datalen,fp);
      fclose(fp);
   }
}

void OutErrorFile(const char *efilename,const char *msg,const char *sourcefile,int lineno)
{
   FILE *fp;
   fp = fopen(efilename,"a+t");
   if (fp!=NULL)
   {
      fprintf(fp,
         "%s FILE:%s LINENO:%d -- [%s]\n",
         getfmttime(NULL,1,NULL),
         sourcefile,
         lineno,
         msg
         );      
      fclose(fp);
   }
}

void DebugFileOut(const char *dfilename,const char *msg,const char *sourcefile,int lineno)
{
   const char *pmsg;

/* ****** Updated by CHENYH at 2004-4-28 9:58:39 ****** 
   char szDRMMsg[1025];
   if (strlen(msg)<900) 
   {
      sprintf(szDRMMsg,"BU%d:%s",iThisProcID,msg);
      pmsg = szDRMMsg;
   }
   else
*/
   {
      pmsg = msg;
   }
   OutErrorFile(dfilename,pmsg,sourcefile,lineno);
   if (pmsg[strlen(pmsg)-2]=='\n')
   {
      printf("%s",pmsg);
   }
   else
   {
      printf("%s\n",pmsg);
   }
}

#ifdef WIN32
#include "process.h"
bool bNotGetFrenquecy=true;
LARGE_INTEGER frenquecy;
double TestTimeUS(int ustimeout)
{
	LARGE_INTEGER p1,p2;
	int nms=ustimeout/1000;
   if (nms<1)
      nms = 1;
	if (bNotGetFrenquecy)
	{
		QueryPerformanceFrequency(&frenquecy);
		bNotGetFrenquecy = false;
	}
	LONGLONG dus;
	unsigned int dd=GetTickCount();
	QueryPerformanceCounter(&p1);
	mysleep(nms);
   dd = GetTickCount()-dd;
	QueryPerformanceCounter(&p2);
	dus = p2.QuadPart-p1.QuadPart;
   double dtt = (dus*1000.000/frenquecy.QuadPart);
	printf("mysleep(%d) - Ticks:%ums - pc:%.3lf ms \n",nms,dd,dtt);
   return(dtt-nms);
}

void gettimeofday(struct timeval *pt,void *ptr)
{
	LARGE_INTEGER perfCount;
	if (bNotGetFrenquecy)
	{
		QueryPerformanceFrequency(&frenquecy);
		bNotGetFrenquecy = false;
	}
	QueryPerformanceCounter(&perfCount);
	if (frenquecy.QuadPart>0)
	{
		double dd = (double)perfCount.QuadPart/frenquecy.QuadPart;
		pt->tv_sec = (long)dd;
		pt->tv_usec = ((long)((dd-pt->tv_sec)*1000000.))%1000000;
	}
	else
	{
		pt->tv_sec = perfCount.QuadPart/1000000;
		pt->tv_usec = perfCount.QuadPart%1000000;
	}	
}

unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1)
{
   return(tc2-tc1);
}

TICKUS GetTickCountUS()
{
   LARGE_INTEGER perfCount;
   if (bNotGetFrenquecy)
   {
      QueryPerformanceFrequency(&frenquecy);
      bNotGetFrenquecy = false;
   }
   QueryPerformanceCounter(&perfCount);
   if (frenquecy.QuadPart>0)
   {
      return (1000000.*((double)perfCount.QuadPart/frenquecy.QuadPart)+0.5);
   }
   else
   {
      return(frenquecy.QuadPart);  // ̫�����ˣ���ô�������أ�Windows�쳣�ɣ�
   }
}

TICKUS DiffTCUS(TICKUS t1,TICKUS t0)
{
   return(t1-t0);
}

#else
#ifdef RT_USE
	#ifdef CLOCK_MONOTONIC_HR
		#define CLOCKID CLOCK_MONOTONIC_HR
	#elif defined CLOCK_MONOTONIC
		#define CLOCKID CLOCK_MONOTONIC
	#endif
#endif


double TestTimeUS(int ustimeout)
{
   int nms;
   double tmt;
   double tt;
   nms = ustimeout/1000;
   if (nms<1)
      nms = 1;
#if 1
   TICKUS t1,t2;
   t1 = GetTickCountUS();
   usleep(ustimeout);
   t2 = GetTickCountUS();
   tt = ((double)DiffTCUS(t2,t1));
   tmt = time(NULL);
#ifdef CLOCKID
   printf("Use clock_gettime(0x%X,...)\n",CLOCKID);
#endif
   printf("%.0lf usleep(%d) - t1:%uus t2:%uus, took %lfus\n",
      tmt,ustimeout,t1,t2,tt);
   return((tt-ustimeout)/1000.);
#else
   struct timeval t1,t2;
   gettimeofday(&t1,NULL);
   mysleep(nms);
   gettimeofday(&t2,NULL);
   tt = (t2.tv_usec-t1.tv_usec)/1000.;
   tt += (t2.tv_sec-t1.tv_sec)*1000.;
   tmt = time(NULL);
   printf("%.0lf mysleep(%d) - t1:%ld.%06ldus t2:%ld.%06ldus, took %lf ms\n",
      tmt,
      nms,
      t1.tv_sec,t1.tv_usec,
      t2.tv_sec,t2.tv_usec,
      tt);
   return(tt-nms);
#endif
}

unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1)
{
   return(tc2-tc1);
//    if (tc2<tc1)
//    {
//       return(86400000-tc1+tc2);
//    }
//    else
//    {
//       return(tc2-tc1);
//    }
}
unsigned int GetTickCount()
{
   struct timeval CurrentTime;
   gettimeofday(&CurrentTime, NULL);
   return ((CurrentTime.tv_sec * 1000) + (CurrentTime.tv_usec / 1000));   
}

#ifdef CLOCKID
bool bNotGetFrenquecy=true;
struct timespec NIX_frenquecy;

TICKUS GetTickCountUS()
{
   struct timespec now;
   TICKUS tus;
   if (bNotGetFrenquecy)
   {
      clock_getres(CLOCKID,&NIX_frenquecy);
      bNotGetFrenquecy = false;
   }
   clock_gettime(CLOCKID,&now);
   tus = now.tv_sec*1000000;
   tus += (now.tv_nsec/1000);
   return (tus);
}

TICKUS DiffTCUS(TICKUS t1,TICKUS t0)
{
   return(t1-t0);
}

#else
// 999.999999 �� -> 999,999,999 us
TICKUS GetTickCountUS()
{
   struct timeval CurrentTime;
   gettimeofday(&CurrentTime, NULL);
   return(CurrentTime.tv_usec+(CurrentTime.tv_sec%1000)*1000000);
}

TICKUS DiffTCUS(TICKUS t1,TICKUS t0)
{
   if (t1<t0)
   {
      return(1000000000-t0+t1);
   }
   else
   {
      return(t1-t0);
   }
}
#endif

#endif


void OnRemoveOverdueFile(const char *path_mark,const char *ext, int overdue, char *file)
{
#if 0
   FILE *fp;
   fp = fopen("RMFile.lst","a+t");
   if (fp!=NULL)
   {
      fprintf(fp,
         "%s: rm <%s> where path=<%s> ext=<%s> overdue=%d\n",
         getfmttime(NULL,1,NULL),
         file, path_mark, ext, overdue
         );
      fclose(fp);
   }
#endif
}


// ������: RemoveOverdueFileInSecond
// ���  : ������ 2008-10-7 13:41:20
// ����  : �����ָ����Ŀ¼path_mark�µ��޸�ʱ������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark  ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
int RemoveOverdueFileInSecond(const char *path_mark,const char *ext,int overdue)
{
   int nfs=0;
   char szfile[2048]; 
   time_t odtime;
   if (overdue<1)
      return(0);
   if (ext[0]=='\0'||memcmp(ext,".*",2)==0)
      return(0);
   odtime = time(NULL)-overdue;   
   sprintf(szfile,"%s*%s",path_mark,ext);
#ifdef WIN32
   struct _finddata_t fd;
   int dh;
   dh = _findfirst(szfile,&fd);
   if (dh==-1) 
      return(0);
   do
   {
      if ((odtime>fd.time_write) && strstr(fd.name,ext)!=NULL)
      {
         sprintf(szfile,"%s%s",path_mark,fd.name);
         OnRemoveOverdueFile(path_mark,ext,overdue,szfile);
         remove(szfile);
         nfs++;
      }
   } while (_findnext(dh,&fd)!=-1);
   _findclose(dh);
#else
   DIR *dp;
   struct dirent *dirp;
   struct stat fst;
   dp = opendir(path_mark);
   if (dp==NULL) 
      return(0);
   while ((dirp=readdir(dp))!=NULL)
   {
      sprintf(szfile,"%s%s",path_mark,dirp->d_name);
      if (strstr(dirp->d_name,ext)!=NULL 
         && stat(szfile,&fst)==0 
         && odtime>fst.st_mtime)
      {
         remove(szfile);
         OnRemoveOverdueFile(path_mark,ext,overdue,szfile);
         nfs++;
      }
   }
   closedir(dp);
#endif
   return(nfs);
}


// ������: RemoveOverdueFile
// ���  : ������ 2004-4-6 9:52:41
// ����  : �����ָ����Ŀ¼path_mark�µ��޸���������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
int RemoveOverdueFile(const char *path_mark,const char *ext,int overdue)
{
   return(RemoveOverdueFileInSecond(path_mark,ext,overdue*86400));
}