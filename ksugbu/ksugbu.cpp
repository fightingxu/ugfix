/********************************************************************
	created:	2012/08/25
	created:	25:8:2012   17:57
	filename: 	C:\dd\projects\FIX_OMS\01����\ugate\ksugbu\ksugbu.cpp
	file path:	C:\dd\projects\FIX_OMS\01����\ugate\ksugbu
	file base:	ksugbu
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 2012/8/25 18:01:24 ǰ�汾�У��������������⣺
   1. ��Channel�Ļָ������У���IN/OUT��û�е�����Ϣ��ʽ������
   2. ����FIXEngine��֧�������ַ�������ˣ���Ҫ��FIXEngine�������Ϣ
   �������Ĺ��ˣ�
   3. ��Զ��ԣ��м����Ϣ��������У���һЩ����copy���̣���Ҫ�Ľ���
   ����������ܣ�

   2013/3/7 17:12:24
   Ϊ�˱�����Sessionͬʱ������̨��EOD�����ر���CheckEOD_AllChannel��
   ÿ��Session֮�������һ����ʱ��

   2013/4/24 17:21:17 
   ���ڷ���ԭ��UGFIX�ڳ�ʱ�����й����У���������UGFIX���ڼ���״̬��
   �һ��������߳�״̬����411731֮ǰ����FEȡ״̬��ʱ�����FE�ӿ����⣬
   ����Blockס����������UGFIX�ɼ�����ͬʱӰ�쵽������Session������
   ��Session�Ŀ��������ȣ�
   Ϊ�ˣ��ر𽫹���fixState��FE�����ȡ״̬�Ĺ����ƽ���FIXSession::OTRun��
   ͨ��ReflushStatus()�ӿڸ���;

   2013/5/6 13:22:11 
   �ڳ�ʱ�����й����У���������Close״̬�£�����FE��EOD����������쳣��
   �޸ģ�CFIXSession::DoEODProcess()
   ͨ���ж�m_LastStatus����������ʽ��

*********************************************************************/
// ***************************************************************
//  ksugbu   version:  1.0   ? date: 08/16/2011
//  -------------------------------------------------------------
//  ΪUGATE��������ͨ������UGate������Ӧ��UDLģ�飬���UGATE
//  -------------------------------------------------------------
//  Copyright (C) 2011 - All Rights Reserved
// ***************************************************************
//  UGATEʹ������������BCC���й����ģ�һ�����������ӽ��մ�������
//  ƽ̨�ĸ���ָ�����Ϣ������һ����Ϊ'UGATE'������BU������ӣ�ר��
//  ������ƽ̨����Ϣ������
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
      // �����ļ�װ�ش�������UG�ڲ�����
      return(-1);
   }

   if (UDLInitialize()<0)  // ��ȡ���ò�����UDL��������������
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
      // ��ʼ��������:
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
      UG_Processing();  // ��������յ�����FS����Ϣ������߽����ڲ�����������Partner�����ӻ�ֹͣ������ �ύUDL������Ϣ�Ĵ���ͷ���      
   }

   UG_ToExit();
   UDLExit();
   return(0);
}

