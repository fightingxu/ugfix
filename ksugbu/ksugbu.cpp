/********************************************************************
	created:	2012/08/25
	created:	25:8:2012   17:57
	filename: 	C:\dd\projects\FIX_OMS\01编码\ugate\ksugbu\ksugbu.cpp
	file path:	C:\dd\projects\FIX_OMS\01编码\ugate\ksugbu
	file base:	ksugbu
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 2012/8/25 18:01:24 前版本中，发现有两点问题：
   1. 在Channel的恢复过程中，对IN/OUT并没有调用消息格式化处理；
   2. 由于FIXEngine不支持中文字符串，因此，需要对FIXEngine的输出消息
   进行中文过滤；
   3. 相对而言，中间的消息处理过程中，有一些几次copy过程，需要改进，
   以提高其性能；

   2013/3/7 17:12:24
   为了避免多个Session同时触发后台做EOD处理，特别在CheckEOD_AllChannel中
   每个Session之间均做了一个延时。

   2013/4/24 17:21:17 
   由于发现原在UGFIX在长时间运行过程中，发现整个UGFIX处于假死状态，
   我怀疑是主线程状态更新411731之前，到FE取状态的时候会因FE接口问题，
   导致Block住，导致整个UGFIX成假死，同时影响到了所有Session，包括
   对Session的控制命令处理等；
   为此，特别将关于fixState从FE那里读取状态的工作移交给FIXSession::OTRun中
   通过ReflushStatus()接口更新;

   2013/5/6 13:22:11 
   在长时间运行过程中，发现了在Close状态下，调用FE的EOD处理，会出现异常；
   修改：CFIXSession::DoEODProcess()
   通过判断m_LastStatus来决定处理方式。

*********************************************************************/
// ***************************************************************
//  ksugbu   version:  1.0   ? date: 08/16/2011
//  -------------------------------------------------------------
//  为UGATE的主程序，通过它、UGate库和相对应的UDL模块，组成UGATE
//  -------------------------------------------------------------
//  Copyright (C) 2011 - All Rights Reserved
// ***************************************************************
//  UGATE使用两个连接与BCC进行工作的，一个是主体连接接收处理来自
//  平台的各类指令和消息；另外一个则为'UGATE'命名的BU组的连接，专门
//  用于向平台发消息和请求。
// ***************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "UDLInterface.h"
#include "ugate.h"


#ifdef _MSC_VER
#include <conio.h>
#include <io.h>

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


void ListChannelStatus()
{
   int i;
   char info[256];
   printf("UGate(%s) ChannelStatus:\n",UG_GetLocalID());
   for (i=0;UGGetChannelInfo(i,info)>=0;++i)
   {
      printf("\t%d - %s\n",i,info);
   }
}

void ReloadKFXFile()
{
   int i,n;
   char info[256];
   n = 0;
   for (i=0;UGGetChannelInfo(i,info)>=0;++i)
   {
      printf("%d - %s\n",i,info);
   }
   n=i;
   if (n<=1)
   {
      i = n-1;
   }
   else
   {
      printf("Enter Channel Number(0..%d) to reload KFX File:",n-1);
      gets(info);
      i = atoi(info);
   }
   UGReloadKFXFile(i);
}

int main(int argc, char *argv[])
{
   if (argc<2)
   {
      printf("Usage:%s <INI File>\n",argv[0]);
      return(0);
   }
   if (UG_LoadIni(argv[1])==0)
   {
      // 配置文件装载错误，属于UG内部错误
      return(-1);
   }

   if (UDLInitialize()<0)  // 读取配置并启动UDL，但不建立连接
   {
      UG_WriteLog(10020,"Fail to Initialize UDL");
      return(-2);
   }
   if (UG_Init()<0) 
   {
      UDLExit();
      return(-3);
   }

#ifndef _MSC_VER
   setnoblockgetch();
#endif

   while (UG_BCCLinkOK()>0)
   {
      // 开始正常工作:
#ifdef WIN32
      switch (mygetch())
      {
      case '?':
      case 'h':
      case 'H':
         printf("\nCommand List:\n");
         printf("\t ? or h: display this Help informations!\n");
         printf("\t l or L: List channel status!\n");
         printf("\t r or R: Reload Channel KFX File!\n");
         printf("\t x: To eXit this business unit.\n");
         printf("Enter command to select:");
         break;
      case 'l':
      case 'L':
         ListChannelStatus();
         break;
      case 'r':
      case 'R':
         ReloadKFXFile();
         break;
      case 'x':
      case 'X':
         UG_ToExit();
         continue;
         break;
      }
#endif
      UG_Processing();  // 在这里，若收到来自FS的消息，则或者进行内部处理（如启动Partner的连接或停止）或者 提交UDL进行消息的处理和发送      
   }

   UG_ToExit();
   UDLExit();
   return(0);
}

