/********************************************************************
	created:	2007/12/11
	created:	11:12:2007   14:43
	filename: 	D:\proj\ksbass\FIX\FIXGateway\profile.h
	file path:	D:\proj\ksbass\FIX\FIXGateway
	file base:	profile
	file ext:	h
	author:		yonghua.chen
	
	purpose:	   为了提高配置文件读取的速度
*********************************************************************/
#ifndef __PROFILE_H
#define __PROFILE_H

typedef void (*FUNC_INI2LOG)(const char *fmt,...);
#include <string>
#include <vector>

typedef struct {
   std::string entry;
   std::string data;
} INI_ENTRY;

typedef std::vector<INI_ENTRY> VINI_ENTRY;
typedef struct 
{
   std::string section;
   VINI_ENTRY  ventries;
} INI_SECTION;
typedef std::vector<INI_SECTION> VINI_SECTION;

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif

BUPUB_API void SetINI2LOGFunc(FUNC_INI2LOG func);

class BUPUB_API TIniFile
{
   VINI_SECTION m_sections;

public:
   // 函数名: TIniFile::ReadTString
   // 编程  : 陈永华 2004-5-7 20:40:18
   // 描述  : 新增的读取定义字段的字符串，且过滤左右空格和'\t'
   // 返回  : char * 
   // 参数  : const char *section
   // 参数  : const char *entry
   // 参数  : const char *defaultString
   // 参数  : char *buffer
   // 参数  : int bufLen
   char * ReadTString(const char *section,const char *entry,const char *defaultString,char *buffer,int   bufLen);
   // 函数名: TIniFile::LRTrim
   // 编程  : 陈永华 2004-5-7 20:41:24
   // 描述  : 从str中将左右空格和'\t'截取掉
   // 返回  : char * 
   // 参数  : char *str
   static char * LRTrim(char *str);
	//打开配置文件
	bool Open(char *filename);
	//读取一个int型entry的值
	int ReadInt( const char *section, const char *entry, int defaultInt);
	//读取一个string型的entry的值
	int ReadString( const char *section, const char *entry,const char *defaultString, char *buffer,int bufLen);
	//写一个string型的entry到指定的section中
	//写一个int型的entry到指定的section中
	//关闭配置文件
	void Close();

   TIniFile();
	~TIniFile();
private:
	char * percolate(char *str);
};

#undef BUPUB_API

#endif
