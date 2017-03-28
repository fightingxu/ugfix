/********************************************************************
	created:	2007/12/11
	created:	11:12:2007   17:20
	filename: 	D:\proj\ksbass\FIX\FIXGateway\profile.cpp
	file path:	D:\proj\ksbass\FIX\FIXGateway
	file base:	profile
	file ext:	cpp
	author:		yonghua.chen
	
	purpose:	为了能够快速读取INI文件，而整个翻了个底
*********************************************************************/
/********************************************************
	读取配置文件类实现
	文件名: profile.cpp
	说明: 
	创建: 
	修改: 吴舸 2001-04-20
	修改原因: 规范编码
**********************************************************/
#include "stdafx.h"
#include <ctype.h>
#include "mypub.h"
#include "profile.h"

static FUNC_INI2LOG pFuncIni2Log=NULL;


void SetINI2LOGFunc(FUNC_INI2LOG func)
{
   pFuncIni2Log = func;
}

TIniFile::TIniFile()
{
   m_sections.clear();
}

TIniFile::~TIniFile()
{
/*
	功能：关闭输入输出流
	参数：无
	返回值：无
	修改者：吴舸 2001-04-20
	修改原因：规范编码
*/
   Close();   
}
void TIniFile::Close()
{
   m_sections.clear();
}

bool TIniFile::Open(char *filename)
{
/*
	功能：打开配置文件
	参数：
		filename[IN]：配置文件名
	返回值：
		成功返回true
		失败返回false
	修改者：吴舸 2001-04-20
	修改原因：规范编码
*/
   Close();

   FILE *fin;
   fin=fopen(filename,"rt");
   if (fin==NULL)
      return false;
   bool rtn = true;
   char tmp[1024];
   INI_SECTION sect;
   INI_ENTRY entry;
   bool insect=false;
   int nline=0;
   while (rtn)
   {
      if (!fgets(tmp,1023,fin))
         break;
      ++nline;
      tmp[1023]='\0';
      char *pc = percolate(tmp);
      int i;
      for (i=0;pc[i]!='=';i++)
      {
         if (pc[i]=='\0')
            break;
      }
      if (pc[i]!='\0')
      {
         if (insect)
         {
            pc[i]='\0'; ++i;
            char *ent = percolate(pc);
            if (ent[0]!='\0')
            {
               // ENTRY=DATA
               entry.entry = ent;  // ENTRY
               entry.data = pc+i;  // DATA
               sect.ventries.push_back(entry);
            }
            else
            {
               printf("INI READER: INVALID LINE @%d (=%s)\n",nline,pc+i);
               rtn = false;

            }
         }
         else
         {
            printf("INI READER: INVALID LINE @%d (Entry not in SECTION)\n",nline);
            rtn = false;
         }
      }
      else if (pc[0]=='[')
      {
         for (i=1;pc[i]!='\0';i++)
         {
            if (pc[i]==']') break;
         }
         if (pc[i]==']')
         {
            if (insect && sect.ventries.size()>0)
            {
               m_sections.push_back(sect);
               sect.ventries.clear();
            }
            pc[i]='\0';
            sect.section = pc+1;   // SECTION : [xxxx]
            insect = true;
         }
         else
         {
            printf("INI READER: INVALID LINE @%d (Invalid SECTION)\n",nline);
            rtn = false;
         }
      }      
   }
   if (insect && sect.ventries.size()>0)
   {
      m_sections.push_back(sect);
      sect.ventries.clear();
   }
   fclose(fin);
   return(rtn);
}

int TIniFile::ReadString( const char *section,const char *entry,const char *defaultString,char *buffer,int   bufLen)
{
/*
	功能：读取指定的section的指定entry的值到buffer中，未找到则使用缺省配置
	参数：
		section[IN]：指定的section
		entry[IN]：指定的entry
		defaultstring[IN]：缺省配置
		buffer[IN]：存放entry值的缓冲区
		bufLen[IN]：缓冲区长度
	返回值：
		成功返回buffer中的值的长度
		失败返回-1
	修改者：吴舸 2001-04-20
	修改原因：规范编码
*/
   VINI_SECTION::iterator vsit;
   VINI_ENTRY::iterator veit;
   for (vsit=m_sections.begin();vsit!=m_sections.end();vsit++)
   {
      if (vsit->section.compare(section)==0)
      {
         for (veit=vsit->ventries.begin();veit!=vsit->ventries.end();veit++)
         {
            if (veit->entry.compare(entry)==0)
            {
               strncpy(buffer,veit->data.c_str(),bufLen-1);
               buffer[bufLen-1]=0;
               // 2006-3-17 17:46:22 用于记录到一个日志文件或独立文件中
               if (pFuncIni2Log!=NULL)
               {
                  (*pFuncIni2Log)("INI:[%s] %s=%s",section,entry,buffer);
               }
               return(0);
            }
         }
      }
   }
   strncpy(buffer,defaultString,bufLen-1);
   buffer[bufLen-1]=0;
   // 2006-3-17 17:46:22 用于记录到一个日志文件或独立文件中
   if (pFuncIni2Log!=NULL)
   {
      (*pFuncIni2Log)("INI:[%s] %s=%s",section,entry,buffer);
   }
	return -1;
}

int TIniFile::ReadInt( const char *section,const char *entry,int defaultInt)
{
/*
	功能：读取指定的section的指定entry的值以整数形式返回，未找到则使用缺省配置
	参数：
		section[IN]：指定的section
		entry[IN]：指定的entry
		defaultInt[IN]：缺省配置
	返回值：
		没有找到指定entry则返回缺省值
		否则返回相应的配置值
	修改者：吴舸 2001-04-20
	修改原因：规范编码
*/
	char buf[1024];
   char buf2[12];
   sprintf(buf2,"%d",defaultInt);  // -2100000000
   ReadString(section,entry,buf2,buf,1024);
   defaultInt = atoi(buf);
	return defaultInt;
}


char * TIniFile::percolate(char *str)
{
	int i;
   char *pc;
   for (i=0;str[i]!=0;i++)
   {
      if (str[i]=='/' && str[i+1]=='/')
      {
         str[i]=0;
         break;
      }
   }
   for (i--;i>=0;i--)
   {
      if (str[i]<=0x20)
         str[i]=0;
      //////////////////////////////////////////////////////////////////////////
      // 新加下面两行，目的是为了能够处理 "ENTRY    =  DATA   ", 以获得 "ENTRY    =  DATA"
      else  
         break;
      //////////////////////////////////////////////////////////////////////////
   }
   for (pc=str;*pc!=0;pc++)
   {
      if (*pc>0x20)
         break;
   }
	return pc;
}



// 函数名: TIniFile::LRTrim
// 编程  : 陈永华 2004-5-7 20:41:24
// 描述  : 从str中将左右空格和'\t'截取掉
// 返回  : char * 
// 参数  : char *str
char * TIniFile::LRTrim(char *str)
{
   char * tmp;
   char * tmp2;
   if(str==NULL)
   {
      return NULL;
   }
   tmp = str;
   while (*tmp)	tmp++;
   if(*str) tmp--;
   while (*tmp == ' '||*tmp=='\t') tmp--;
   *(tmp+1) = 0;
   tmp = str;
   tmp2 = str;
   while ( *tmp2 == ' '||*tmp2=='\t') tmp2 ++ ;
   while ( *tmp2 != 0 ) {
      *tmp = *tmp2; tmp ++; tmp2 ++;
   }
   *tmp = 0;
   return str;   
}


// 函数名: TIniFile::ReadTString
// 编程  : 陈永华 2004-5-7 20:40:18
// 描述  : 新增的读取定义字段的字符串，且过滤左右空格和'\t'
// 返回  : char * 
// 参数  : const char *section
// 参数  : const char *entry
// 参数  : const char *defaultString
// 参数  : char *buffer
// 参数  : int bufLen
char * TIniFile::ReadTString(const char *section, const char *entry, const char *defaultString, char *buffer, int bufLen)
{
   ReadString(section,entry,defaultString,buffer,bufLen);
   return (LRTrim(buffer));
}
