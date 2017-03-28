/********************************************************************
	created:	2004/02/11
	created:	11:2:2004   23:39
	filename: 	E:\proj\goldmem\public\mypub.h
	file path:	E:\proj\goldmem\public
	file base:	mypub
	file ext:	h
	author:		CHENYH
	
	purpose:	
*********************************************************************/
#ifndef __MYPUB_H_
#define __MYPUB_H_

#ifndef BUDLL
#define BUPUB_API 
#else
#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _MSC_VER
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif
#endif

#ifdef _MSC_VER
#define SNPRINTF _snprintf
#else
#define SNPRINTF snprintf
#endif


#ifdef __cplusplus
extern "C" {
#endif


#ifndef BYTE
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
#endif
#ifndef INT4
typedef char			INT1;
typedef short			INT2;
typedef int				INT4;
#endif
#ifndef REAL4
typedef float			REAL4;
typedef double			REAL8;
#endif


//��Windows�£����¶���MAX��MIN��
#ifdef _MSC_VER
#define MAX(a,b) _MAX(a,b)
#define MIN(a,b) _MIN(a,b)
#endif

#ifndef ASSERT
#ifdef _DEBUG
#define ASSERT(booleanExpression )					\
	if(!(booleanExpression)){						\
		RAISE_DESIGN_ERROR(#booleanExpression);		\
	}

#define DebugMessageDisplay(msg)   printf("%s:%d <%s>\n",__FILE__,__LINE__,msg)

#else
#define ASSERT(booleanExpression)
#define DebugMessageDisplay(msg)
#endif
#endif

#include <fcntl.h>
#include <sys/stat.h>
#ifdef _MSC_VER
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

#ifndef MAX_PATH
#define MAX_PATH 260
#endif


// Function name: setnoblockgetch
// Author       : CHENYH 2012/7/10 15:04:46
// Description  : ���ú�����mygetchΪ��������ʽ����
// Return type  : void 
BUPUB_API void setnoblockgetch();


// Function name: mygetch
// Author       : CHENYH 2012/7/10 15:05:29
// Description  : ���м��������ʱ�򣬷��ؼ��̵ļ�ֵ
// Return type  : int  0 - ��ʾ��ǰ�޼������룻���򼴷��ؼ��̼�ֵ
BUPUB_API int mygetch();


// Function name: MyUpdateCheckPath
// Author       : CHENYH 2012/6/28 0:18:22
// Description  : ���pathĿ¼�Ƿ���ڣ�����������Ŀ¼�ָ���
// Return type  : int 
// Argument : char *path [IN/OUT]: ָ����Ŀ¼
// Argument : const char *defsub [IN]: ȱʡ·��
BUPUB_API int MyUpdateCheckPath(char *path, const char *defsub);


// Function name: GetLocalDateTime
// Author       : CHENYH 2012/6/20 15:04:25
// Description  : ��ʱ��ת��Ϊ���ص� YYYYMMDD �� HH:MM:SS
// Return type  : void 
// Argument : time_t *tmTime [IN]: ָ����ʱ��㣻NULL��Ϊ��ǰʱ��
// Argument : char *sLocalDate [OUT]: ���ر������� YYYYMMDD , NULL �򲻸�ֵ
// Argument : char *sLocalTime [OUT]: ���ر���ʱ�� HH:MM:SS , NULL �򲻸�ֵ
BUPUB_API void GetLocalDateTime(void *tmTime, char *sLocalDate, char *sLocalTime);


// Function name: GetTimeMillis
// Author       : CHENYH 2012/5/20 8:50:17
// Description  : ȡ������ʱ��(�����벿��)
// Return type  : void 
// Argument : time_t *ptm [OUT]
// Argument : int *pmillis [OUT]
BUPUB_API void GetTimeMillis(time_t *ptm, int *pmillis);


// Function name: GetFormatDateTime
// Author       : CHENYH 2012/5/20 8:50:20
// Description  : ��ʱ��ת��ΪYYYYMMDD-hh:mm:ss(.xxx)
// Return type  : void 
// Argument : time_t tm [IN]: ʱ��
// Argument : char *sFmtTime [OUT]: ��Ż�ȡ��ʱ�䴮'YYYYMMDD-HH:MM:SS.xxx',������24�ֽڻ��泤
// Argument : int millis [IN]: >=0: ��Ҫ���벿�֣�<0: ����Ҫ���벿��
// Argument : int isUTC [IN]: 0 - ����ʱ�䣻1 - UTCʱ��
BUPUB_API void GetFormatDateTime(time_t tm, char *sFmtTime, int millis, int isUTC);

// Function name: DateTime2TimeT
// Author       : CHENYH 2012/6/19 17:12:53
// Description  : ��YYYYMMDD-hh:mm:ssʱ��ת��Ϊtime_t
// Return type  : void 
// Argument : const char *sDateTime [IN]: YYYYMMDD-hh:mm:ss[.xxx]
// Argument : int isUTC [IN]: 0 - ����UTC��ʱ�䣻!=0 - ��UTCʱ��
// Argument : time_t *pTimeT [OUT]: ���ص�time_t��ֵ
BUPUB_API void DateTime2TimeT(const char *sDateTime, int isUTC, time_t *pTimeT);


// ������: GetFIXUTCDateTime
// ���  : ������ 2011-8-27 10:40:09
// ����  : ��÷���FIX�淶��UTCTime
// ����  : void 
// ����  : time_t tm [IN]: ��time(NULL)��õ�ֵ
// ����  : char *sUTCTime[OUT]: ��Ż�ȡ��ʱ�䴮'YYYYMMDD-HH:MM:SS.xxx',������24�ֽڻ��泤
BUPUB_API void GetFIXUTCDateTime(time_t tm, char *sUTCTime, int millis);


BUPUB_API unsigned int atoui(char *pstr);

/* ȥ�����ҿո�   */
BUPUB_API char *mytrim(char *s);


// ������: *Strncpy
// ���  : ������ 2004-2-21 13:39:08
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
BUPUB_API char *Strncpy(char *dest,const char *source,unsigned int count);

#define STRNCPY(d,s) Strncpy(d,s,sizeof(d))

// ������: *Strncpy_t
// ���  : ������ 2004-2-21 13:39:12
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
//        ͬʱȥ�����ҿո�
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
BUPUB_API char *Strncpy_t(char *dest,const char *source,unsigned int count);

#define STRNCPY_T(d,s) Strncpy_t(d,s,sizeof(d))

// ������: mytrim_r
// ���  : ������ 2004-2-21 13:45:29
// ����  : ����ַ����ұߵ�' '��'\t'
// ����  : char *
// ����  : char *dest
BUPUB_API char *mytrim_r(char *dest);

// ������: Strncpy_rt
// ���  : ������ 2004-2-21 13:46:22
// ����  : ���Ʋ����dest�ұߵ�' '��'\t'
// ����  : char * ����dest��ָ��
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
BUPUB_API char *Strncpy_rt(char *dest,char *source,unsigned int count);

#define STRNCPY_RT(d,s) Strncpy_rt(d,s,sizeof(d))

// ����  : ���÷ָ��separator�ָ�Ĵ��ַ���pc�У���ȡ��pid�����ַ�����para��
// ����  : int ��>0:true - ���ػ�ȡ�������ݴ�֮����Ǹ�λ�ã���'\0'��separatorλ�ã�0 :false��Ϊʧ��
// ����  : const char *pc [IN]: ���ַ��� �� "000,1,22, 333,4444"
// ����  : char separator [IN]: �ָ�� ��','
// ����  : int pid [IN]: Ҫ��ȡ�����ַ�������ţ���0��ʼ
// ����  : char *para [OUT]: ����ȡ���������ַ�������������pid=3�����ַ�������Ϊ" 333"
// ����  : int psize [IN]: para����ĳ��ȣ����ֽ�����ʾ
// ����  : char *rtnmsg [OUT]: ���ش�����Ϣ 
BUPUB_API int GetSubString(const char *pc, char separator ,int pid, char *para, int psize, char *rtnmsg);

// ������: percolate
// ���  : ������ 2003-9-24 13:38:37
// ����  : ���ַ����н��Ƿ��ַ����˵���ͬʱ����//��Ϊ����Ϊע������Ҳͬ//һ����˵�
// ����  : int �������ĳ���
// ����  : char *str In��Out
BUPUB_API int percolate(char *str);

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
BUPUB_API char *getfmttime(void *ptm,int fmttype,char *outstr);


// ������: mysleep
// ���  : ������ 2004-2-11 12:35:51
// ����  : ���߳̽���˯��״̬milliseconds����
// ����  : void 
// ����  : unsigned int milliseconds
BUPUB_API void mysleep(unsigned int milliseconds);

#ifdef _MSC_VER
// ������: gettimeofday
// ���  : ������ 2009-5-19 13:04:42
// ����  : �ø߾��ȼ�ʱ�����һ�����ʱ����ֵ���Ա�����ĽǶ���˵�ģ��ͱ�׼�Ĳ�ͬ
// ����  : void 
// ����  : struct timeval *pt [OUT]: ��ȡʱ��㣬��timeval��ʽ����
// ����  : void *ptr [û���õģ�����Ϊ�˺�Linux�ȼ��ݶ���]
BUPUB_API void gettimeofday(struct timeval *pt,void *ptr);
#else
// ������: GetTickCount
// ���  : ������ 2004-2-11 20:55:11
// ����  : Ϊ�˺�WINDOWSƽ̨���ݣ���ȡ��ǰ��ʱ���
// ����  : unsigned int 
BUPUB_API unsigned int GetTickCount();
#endif


// ������: tc2_tc1
// ���  : ������ 2004-2-11 21:06:59
// ����  : ��GetTickCount()�õ��ĺ���ʱ���Ĳ������ƣ� t2-t1 �����ڷ�WINDOWS��ʱ���ʵ�ʲ��ܳ���1��
// ����  : unsigned int   tc2-tc1 
// ����  : unsigned int tc2
// ����  : unsigned int tc1
BUPUB_API unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1);

typedef unsigned int TICKUS;

// ������: GetTickCountUS
// ���  : ������ 2011-5-4 14:54:04
// ����  : ȡ��usΪ��λ��ʱ���
// ����  : int ���Ϊ: 
// 999.999999 �� -> 999,999,999 us
BUPUB_API TICKUS GetTickCountUS();

// ����Լ��t1һ����t0֮���ʱ���
BUPUB_API TICKUS DiffTCUS(TICKUS t1,TICKUS t0);

BUPUB_API double TestTimeUS(int ustimeout);

// ������: DataDumpFile
// ���  : ������ 2005-3-24 18:19:51
// ����  : ������ת�����ļ���
// ����  : void 
// ����  : char *filename
// ����  : char *data
// ����  : int datalen
BUPUB_API void DataDumpFile(const char *filename,const char *data,int datalen);

// ������: OutErrorFile
// ���  : ������ 2004-2-7 15:14:33
// ����  : ��������Ϣ��¼�������¼�ļ���
// ����  : void 
// ����  : char *efilename
// ����  : char *msg
// ����  : char *sourcefile
// ����  : int lineno
BUPUB_API void OutErrorFile(const char *efilename,const char *msg,const char *sourcefile,int lineno);


// ������: DebugFileOut
// ���  : ������ 2004-2-11 14:37:14
// ����  : ����Ϣ��¼�����ٵ����ļ��У��Է�����Ժ�����Ĳ�ѯ
// ����  : void 
// ����  : char *dfilename ���ٵ����ļ������ļ���
// ����  : char *msg ���ٵ�����Ϣ
// ����  : char *sourcefile Դ�ļ�����
// ����  : int lineno Դ�ļ����к�
BUPUB_API void DebugFileOut(const char *dfilename,const char *msg,const char *sourcefile,int lineno);

// ������: RemoveOverdueFile
// ���  : ������ 2004-4-6 9:52:41
// ����  : �����ָ����Ŀ¼path_mark�µ��޸���������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
BUPUB_API int RemoveOverdueFile(const char *path_mark,const char *ext,int overdue);

// ������: RemoveOverdueFileInSecond
// ���  : ������ 2008-10-7 13:41:20
// ����  : �����ָ����Ŀ¼path_mark�µ��޸�ʱ������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark  ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
BUPUB_API int RemoveOverdueFileInSecond(const char *path_mark,const char *ext,int overdue);

//�׳�һ��CDesignError�쳣
//@����	msg	char*	ָ���Ĵ�����Ϣ
//@�쳣	CDesignError	�׳����쳣������λ���ڵ�ǰ�ļ���ǰ��
#define RAISE_DESIGN_ERROR(msg) { OutErrorFile("DesignError",msg,__FILE__,__LINE__); exit(-1000);}

//�׳�һ��CRuntimeError
//@����	msg	char*	ָ���Ĵ�����Ϣ
//@�쳣	CRuntimeError	�׳����쳣������λ���ڵ�ǰ�ļ���ǰ��
#define RAISE_RUNTIME_ERROR(msg) { OutErrorFile("RuntimeError",msg,__FILE__,__LINE__); exit(-1001);}


#ifdef __cplusplus
}
#endif

#undef BUPUB_API

#endif

