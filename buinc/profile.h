/********************************************************************
	created:	2007/12/11
	created:	11:12:2007   14:43
	filename: 	D:\proj\ksbass\FIX\FIXGateway\profile.h
	file path:	D:\proj\ksbass\FIX\FIXGateway
	file base:	profile
	file ext:	h
	author:		yonghua.chen
	
	purpose:	   Ϊ����������ļ���ȡ���ٶ�
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
   // ������: TIniFile::ReadTString
   // ���  : ������ 2004-5-7 20:40:18
   // ����  : �����Ķ�ȡ�����ֶε��ַ������ҹ������ҿո��'\t'
   // ����  : char * 
   // ����  : const char *section
   // ����  : const char *entry
   // ����  : const char *defaultString
   // ����  : char *buffer
   // ����  : int bufLen
   char * ReadTString(const char *section,const char *entry,const char *defaultString,char *buffer,int   bufLen);
   // ������: TIniFile::LRTrim
   // ���  : ������ 2004-5-7 20:41:24
   // ����  : ��str�н����ҿո��'\t'��ȡ��
   // ����  : char * 
   // ����  : char *str
   static char * LRTrim(char *str);
	//�������ļ�
	bool Open(char *filename);
	//��ȡһ��int��entry��ֵ
	int ReadInt( const char *section, const char *entry, int defaultInt);
	//��ȡһ��string�͵�entry��ֵ
	int ReadString( const char *section, const char *entry,const char *defaultString, char *buffer,int bufLen);
	//дһ��string�͵�entry��ָ����section��
	//дһ��int�͵�entry��ָ����section��
	//�ر������ļ�
	void Close();

   TIniFile();
	~TIniFile();
private:
	char * percolate(char *str);
};

#undef BUPUB_API

#endif
