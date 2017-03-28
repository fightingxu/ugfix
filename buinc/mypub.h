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


//在Windows下，重新定义MAX和MIN宏
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
// Description  : 设置后续的mygetch为非阻塞方式运行
// Return type  : void 
BUPUB_API void setnoblockgetch();


// Function name: mygetch
// Author       : CHENYH 2012/7/10 15:05:29
// Description  : 当有键盘输入的时候，返回键盘的键值
// Return type  : int  0 - 表示当前无键盘输入；否则即返回键盘键值
BUPUB_API int mygetch();


// Function name: MyUpdateCheckPath
// Author       : CHENYH 2012/6/28 0:18:22
// Description  : 检查path目录是否存在，并在最后加上目录分隔符
// Return type  : int 
// Argument : char *path [IN/OUT]: 指定的目录
// Argument : const char *defsub [IN]: 缺省路径
BUPUB_API int MyUpdateCheckPath(char *path, const char *defsub);


// Function name: GetLocalDateTime
// Author       : CHENYH 2012/6/20 15:04:25
// Description  : 将时间转换为本地的 YYYYMMDD 和 HH:MM:SS
// Return type  : void 
// Argument : time_t *tmTime [IN]: 指定的时间点；NULL则为当前时间
// Argument : char *sLocalDate [OUT]: 返回本地日期 YYYYMMDD , NULL 则不赋值
// Argument : char *sLocalTime [OUT]: 返回本地时间 HH:MM:SS , NULL 则不赋值
BUPUB_API void GetLocalDateTime(void *tmTime, char *sLocalDate, char *sLocalTime);


// Function name: GetTimeMillis
// Author       : CHENYH 2012/5/20 8:50:17
// Description  : 取本机的时间(含毫秒部分)
// Return type  : void 
// Argument : time_t *ptm [OUT]
// Argument : int *pmillis [OUT]
BUPUB_API void GetTimeMillis(time_t *ptm, int *pmillis);


// Function name: GetFormatDateTime
// Author       : CHENYH 2012/5/20 8:50:20
// Description  : 将时间转换为YYYYMMDD-hh:mm:ss(.xxx)
// Return type  : void 
// Argument : time_t tm [IN]: 时间
// Argument : char *sFmtTime [OUT]: 存放获取的时间串'YYYYMMDD-HH:MM:SS.xxx',至少有24字节缓存长
// Argument : int millis [IN]: >=0: 需要毫秒部分；<0: 不需要毫秒部分
// Argument : int isUTC [IN]: 0 - 本地时间；1 - UTC时间
BUPUB_API void GetFormatDateTime(time_t tm, char *sFmtTime, int millis, int isUTC);

// Function name: DateTime2TimeT
// Author       : CHENYH 2012/6/19 17:12:53
// Description  : 将YYYYMMDD-hh:mm:ss时间转换为time_t
// Return type  : void 
// Argument : const char *sDateTime [IN]: YYYYMMDD-hh:mm:ss[.xxx]
// Argument : int isUTC [IN]: 0 - 不是UTC的时间；!=0 - 是UTC时间
// Argument : time_t *pTimeT [OUT]: 返回的time_t的值
BUPUB_API void DateTime2TimeT(const char *sDateTime, int isUTC, time_t *pTimeT);


// 函数名: GetFIXUTCDateTime
// 编程  : 陈永华 2011-8-27 10:40:09
// 描述  : 获得符合FIX规范的UTCTime
// 返回  : void 
// 参数  : time_t tm [IN]: 用time(NULL)获得的值
// 参数  : char *sUTCTime[OUT]: 存放获取的时间串'YYYYMMDD-HH:MM:SS.xxx',至少有24字节缓存长
BUPUB_API void GetFIXUTCDateTime(time_t tm, char *sUTCTime, int millis);


BUPUB_API unsigned int atoui(char *pstr);

/* 去除左右空格   */
BUPUB_API char *mytrim(char *s);


// 函数名: *Strncpy
// 编程  : 陈永华 2004-2-21 13:39:08
// 描述  : 从source中最多复制count字符到dest，但是在dest[count-1]被赋值为'\0'字符串结束符
// 返回  : char 
// 参数  : char *dest
// 参数  : char *source
// 参数  : size_t count
BUPUB_API char *Strncpy(char *dest,const char *source,unsigned int count);

#define STRNCPY(d,s) Strncpy(d,s,sizeof(d))

// 函数名: *Strncpy_t
// 编程  : 陈永华 2004-2-21 13:39:12
// 描述  : 从source中最多复制count字符到dest，但是在dest[count-1]被赋值为'\0'字符串结束符
//        同时去除左右空格
// 返回  : char 
// 参数  : char *dest
// 参数  : char *source
// 参数  : size_t count
BUPUB_API char *Strncpy_t(char *dest,const char *source,unsigned int count);

#define STRNCPY_T(d,s) Strncpy_t(d,s,sizeof(d))

// 函数名: mytrim_r
// 编程  : 陈永华 2004-2-21 13:45:29
// 描述  : 清除字符串右边的' '和'\t'
// 返回  : char *
// 参数  : char *dest
BUPUB_API char *mytrim_r(char *dest);

// 函数名: Strncpy_rt
// 编程  : 陈永华 2004-2-21 13:46:22
// 描述  : 复制并清除dest右边的' '和'\t'
// 返回  : char * 就是dest的指针
// 参数  : char *dest
// 参数  : char *source
// 参数  : size_t count
BUPUB_API char *Strncpy_rt(char *dest,char *source,unsigned int count);

#define STRNCPY_RT(d,s) Strncpy_rt(d,s,sizeof(d))

// 描述  : 从用分割符separator分割的大字符串pc中，提取第pid的子字符串到para中
// 返回  : int ：>0:true - 返回获取到的数据串之后的那个位置，即'\0'或separator位置；0 :false－为失败
// 参数  : const char *pc [IN]: 大字符串 如 "000,1,22, 333,4444"
// 参数  : char separator [IN]: 分割符 如','
// 参数  : int pid [IN]: 要提取的子字符串的序号，从0开始
// 参数  : char *para [OUT]: 被提取出来的子字符串，如上述的pid=3的子字符串，则为" 333"
// 参数  : int psize [IN]: para缓存的长度，用字节数表示
// 参数  : char *rtnmsg [OUT]: 返回错误信息 
BUPUB_API int GetSubString(const char *pc, char separator ,int pid, char *para, int psize, char *rtnmsg);

// 函数名: percolate
// 编程  : 陈永华 2003-9-24 13:38:37
// 描述  : 从字符串中将非法字符过滤掉，同时将以//作为后续为注释描述也同//一起过滤掉
// 返回  : int 结束串的长度
// 参数  : char *str In、Out
BUPUB_API int percolate(char *str);

// 函数名: *getfmttime
// 编程  : 陈永华 2003-10-14 11:23:47
// 描述  : 将tm的时间转换为本地时间的格式化字符串，本子系统中non-thread-safe
// 返回  : char * 格式化的字符串指针, NULL 则使用内部静态空间存放格式化的字符串，
// 参数  : time_t *ptm ：需要转换的时间 ==NULL 则为转换时时间点
// 参数  : int fmttype 
/*
            0 : hh:mm:ss
            1 : MM/DD-hh:mm:ss
            2 : YYYY/MM/DD-hh:mm:ss
            3 : YYYYMMDD
            4 : hhmmss
            其他 : YYYYMMDDhhmmss
*/
// 参数  : char *outstr 输出字符串的缓存，=NULL则使用内部的静态缓存，其长度需要视fmttype而定
BUPUB_API char *getfmttime(void *ptm,int fmttype,char *outstr);


// 函数名: mysleep
// 编程  : 陈永华 2004-2-11 12:35:51
// 描述  : 本线程进入睡眠状态milliseconds毫秒
// 返回  : void 
// 参数  : unsigned int milliseconds
BUPUB_API void mysleep(unsigned int milliseconds);

#ifdef _MSC_VER
// 函数名: gettimeofday
// 编程  : 陈永华 2009-5-19 13:04:42
// 描述  : 用高精度计时器获得一个相对时间点的值，以本程序的角度来说的，和标准的不同
// 返回  : void 
// 参数  : struct timeval *pt [OUT]: 获取时间点，以timeval格式返回
// 参数  : void *ptr [没有用的，仅仅为了和Linux等兼容而已]
BUPUB_API void gettimeofday(struct timeval *pt,void *ptr);
#else
// 函数名: GetTickCount
// 编程  : 陈永华 2004-2-11 20:55:11
// 描述  : 为了和WINDOWS平台兼容，获取当前的时间点
// 返回  : unsigned int 
BUPUB_API unsigned int GetTickCount();
#endif


// 函数名: tc2_tc1
// 编程  : 陈永华 2004-2-11 21:06:59
// 描述  : 以GetTickCount()得到的毫秒时间点的差，（毫秒计） t2-t1 ，对于非WINDOWS，时间差实际不能超过1天
// 返回  : unsigned int   tc2-tc1 
// 参数  : unsigned int tc2
// 参数  : unsigned int tc1
BUPUB_API unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1);

typedef unsigned int TICKUS;

// 函数名: GetTickCountUS
// 编程  : 陈永华 2011-5-4 14:54:04
// 描述  : 取以us为单位的时间点
// 返回  : int 最大为: 
// 999.999999 秒 -> 999,999,999 us
BUPUB_API TICKUS GetTickCountUS();

// 这里约定t1一定是t0之后的时间点
BUPUB_API TICKUS DiffTCUS(TICKUS t1,TICKUS t0);

BUPUB_API double TestTimeUS(int ustimeout);

// 函数名: DataDumpFile
// 编程  : 陈永华 2005-3-24 18:19:51
// 描述  : 将数据转储到文件中
// 返回  : void 
// 参数  : char *filename
// 参数  : char *data
// 参数  : int datalen
BUPUB_API void DataDumpFile(const char *filename,const char *data,int datalen);

// 函数名: OutErrorFile
// 编程  : 陈永华 2004-2-7 15:14:33
// 描述  : 将错误信息记录到错误记录文件中
// 返回  : void 
// 参数  : char *efilename
// 参数  : char *msg
// 参数  : char *sourcefile
// 参数  : int lineno
BUPUB_API void OutErrorFile(const char *efilename,const char *msg,const char *sourcefile,int lineno);


// 函数名: DebugFileOut
// 编程  : 陈永华 2004-2-11 14:37:14
// 描述  : 将信息记录到跟踪调试文件中，以方便调试和问题的查询
// 返回  : void 
// 参数  : char *dfilename 跟踪调试文件生成文件名
// 参数  : char *msg 跟踪调试信息
// 参数  : char *sourcefile 源文件名称
// 参数  : int lineno 源文件的行号
BUPUB_API void DebugFileOut(const char *dfilename,const char *msg,const char *sourcefile,int lineno);

// 函数名: RemoveOverdueFile
// 编程  : 陈永华 2004-4-6 9:52:41
// 描述  : 清除在指定的目录path_mark下的修改日期早于overdue的天数的文件
// 返回  : int 删除的文件数
// 参数  : char *path_mark 指定的目录（如果需要应该包括目录分隔符，如MS操作系统的'\\' 或其他的'/'）
// 参数  : char *ext 文件扩展名，包括 '.'
// 参数  : int overdue  指定过期的天数
BUPUB_API int RemoveOverdueFile(const char *path_mark,const char *ext,int overdue);

// 函数名: RemoveOverdueFileInSecond
// 编程  : 陈永华 2008-10-7 13:41:20
// 描述  : 清除在指定的目录path_mark下的修改时间早于overdue的秒数的文件
// 返回  : int 删除的文件数
// 参数  : char *path_mark  指定的目录（如果需要应该包括目录分隔符，如MS操作系统的'\\' 或其他的'/'）
// 参数  : char *ext 文件扩展名，包括 '.'
// 参数  : int overdue  指定过期的秒数
BUPUB_API int RemoveOverdueFileInSecond(const char *path_mark,const char *ext,int overdue);

//抛出一个CDesignError异常
//@参数	msg	char*	指定的错误信息
//@异常	CDesignError	抛出此异常，错误位置在当前文件当前行
#define RAISE_DESIGN_ERROR(msg) { OutErrorFile("DesignError",msg,__FILE__,__LINE__); exit(-1000);}

//抛出一个CRuntimeError
//@参数	msg	char*	指定的错误信息
//@异常	CRuntimeError	抛出此异常，错误位置在当前文件当前行
#define RAISE_RUNTIME_ERROR(msg) { OutErrorFile("RuntimeError",msg,__FILE__,__LINE__); exit(-1001);}

extern int iThisProcID;   // 本程序的ID标识，由应用服务架构分配，可以认为在整个系统中唯一，如用OutErrorFile作为文件名记录跟踪数据用 
//#define DEBUG_RUNTIME_MSGOUT(msg) { DebugFileOut("runtimedebug",msg,__FILE__,__LINE__);}
#if defined(BUPUB_EXPORTS)||defined(BUPUBLIB)
#define DEBUG_RUNTIME_MSGOUT(msg) { g_pLogFile->WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }
#else
#define DEBUG_RUNTIME_MSGOUT(msg) { g_LogFile.WriteLogEx(1111,"FILE:%s LINE:%d Msg:%s",__FILE__,__LINE__,msg); }
#endif

#ifdef __cplusplus
}
#endif

// 下面为推送数据的时候，pushmode选用的参数：
#ifndef PM_INACK 
   #define PM_CLEAR  'X'
   #define PM_INACK  '0'  /* 非可靠推送 */
   #define PM_ACK    '1'  /* 可靠推送,需要对方接收后必须有接收确认回单 */
   #define PM_ANSWER '2'  /* 在特殊情况下使用，作为请求发送给目标点，外部处理结束后应答返回的时候，需要再次提交给原始的BUNIT */
#endif

/* ****** Updated by CHENYH at 2004-3-10 13:02:41 ****** 
// 设置BCC应答数据处理模式，见CBULinkThread/CSvrLink中的iAnswerMode
*/
#ifndef AM_AUTO
   #define AM_AUTO     'A'   // 一旦有数据就打包自动发送给请求客户端
   #define AM_CONFIRM  'C'   // 有数据只有在业务处理要求才发送给请求客户端,需要用AnswerData或AnswerDataPart才发送
#endif

#undef BUPUB_API

#endif

