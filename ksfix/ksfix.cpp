#include "stdafx.h"
#include "mypub.h"
#include "FIXSession.h"
#include "FIXLinkThread.h"
#include "ksfix.h"

CFIXLinkThread g_FIXLink;


// Function name: KFLSetLogPath
// Author       : CHENYH 2012/5/28 15:14:00
// Description  : ����FIX��Ϣ��־�Ĵ��·��
// Return type  : void 
// Argument : const char *logpath [IN]: �����־·��
void KFLSetLogPath(const char *logpath)
{
   g_FIXLink.SetLogPath(logpath);
}


// Function name: KFLSetSession
// Author       : CHENYH 2012/5/28 15:14:55
// Description  : ����FIX��SessionID��FIX�汾
// Return type  : void 
// Argument : const char *localid [IN]: ����ID
// Argument : const char *partnerid [IN]: �Է�ID
// Argument : const char *fixversion [IN]: FIX�汾�ţ���"FIX.4.4"
void KFLSetSession(const char *localid, const char *partnerid, const char *fixversion)
{
   g_FIXLink.SetSession(localid,partnerid,fixversion);
}



// Function name: KFLSetHeartBeat
// Author       : CHENYH 2012/5/28 15:16:21
// Description  : ���ñ������е���������ͼ����ʱ���������ٶ����
// Return type  : void 
// Argument : int hbt [IN]: �������ʱ�䣬�� ��30
// Argument : int hbtlatency [IN]: ������ϢԤ����ʱ���� ��5
void KFLSetHeartBeat(int hbt, int hbtlatency)
{
   g_FIXLink.SetHeartBtInt(hbt,hbtlatency);
}


// Function name: KFLSetUserPassword
// Author       : CHENYH 2012/5/28 15:19:05
// Description  : ���õ�½�����������֤�ı����ͶԷ����û���������
// Return type  : void 
// Argument : const char *lusername [IN]: �����û���
// Argument : const char *lpassword [IN]: �����û���
// Argument : const char *pusername [IN]: �Է��û���
// Argument : const char *ppassword [IN]: �Է��û���
void KFLSetUserPassword(const char *lusername, const char *lpassword, const char *pusername, const char *ppassword)
{
   g_FIXLink.SetUserPassword(lusername,lpassword,pusername,ppassword);
}


// Function name: KFLGetStatus
// Author       : CHENYH 2012/5/28 15:20:37
// Description  : ��ȡĿǰFIX����״̬
// Return type  : int 0 - Close��1 - Connecting(����������)��2 - Open(���������ӣ������ڹ�����)
int KFLGetStatus()
{
   return(g_FIXLink.GetStatus());
}


// Function name: KFLSetFIXStorePath
// Author       : CHENYH 2012/5/26 21:28:56
// Description  : ����FIX�����ݳ־û�·��
// Return type  : int 0:�ɹ���-1:ʧ��
// Argument : const char *mpath [IN]: ���洢Ŀ¼·��������Ϊ�У����ҿ��Դ�����·�������򣬽�����ʧ��
// Argument : const char *bkpath [IN]: ���洢Ŀ¼·��������ΪNULL��""����ʾ�ޱ��洢·��
int KFLSetFIXStorePath(const char *mpath, const char *bkpath)
{
   if (g_FIXLink.SetFIXPath(mpath,bkpath))
      return(0);
   else
      return(-1);
}

void KFLSetAutoEOD(int iHHMM)
{
   g_FIXLink.SetEODTime(iHHMM);
}



// Function name: KFLToOpen
// Author       : CHENYH 2012/5/28 15:23:05
// Description  : ��ʽ����FIX���Ӻ͹���
// Return type  : int >=0: ���ӳɹ������������������̣߳�<0: ʧ�ܣ��ɼ����־�е�˵��:
/*                -1: ������Է��������ӣ�
                  -2: �����ݳ־û��ļ�ʧ�ܣ�����KFLSetFIXStorePath�Ĳ�������ȷ��mpath·���±����ܹ������ļ���
                  -3: �������õ�����ʱ���ڣ������յ��Է�Logon��Ϣ��
                      �� �Է�Logon��ϢSessionID����ȷ��
                  -4: �Է���Logon��Ϣ�йؼ���������ȷ��
                  -5: ���Ӻ��յ��ĵ�һ����Ϣ����LOGON��Ϣ��
*/
// Argument : const char *svrip [IN]: �Է���������IP��ַ��
// Argument : int svrport [IN]: �Է��������Ӷ˿ڣ�
int KFLToOpen(const char *svrip, int svrport)
{
   return(g_FIXLink.ToOpen(svrip,svrport));
}


// Function name: KFLGetInMsg
// Author       : CHENYH 2012/5/28 15:51:24
// Description  : ȡ�յ���FIX��Ϣ����
// Return type  : int >0: �����յ�FIX��Ϣ�ĳ��ȣ�0: û���յ���FIX��Ϣ 
// Argument : char *msgbuf [OUT]: �յ���FIX��Ϣ�Ļ��棬��Ҫ�㹻��>=8K, ��ģ��֧���8K�ֽڵ���Ϣ
// Argument : unsigned int waitms [IN]: �ȴ����յ�ʱ�� ���룬����>=100ms
int KFLGetInMsg(char *msgbuf, unsigned int waitms)
{
   return(g_FIXLink.GetInMsg(msgbuf,waitms));
}


// Function name: KFLHaveOutMsg
// Author       : CHENYH 2012/5/28 16:07:07
// Description  : �ύ�跢��FIX��Ϣ����
// Return type  : void 
// Argument : int msglen [IN]: FIX��Ϣ�ĳ���
// Argument : const char *msg [IN]: FIX��Ϣ
// Argument : int plevel [IN]: ���ȼ���0 or 1����Ϊ0
void KFLHaveOutMsg(int msglen, const char *msg, int plevel)
{
   g_FIXLink.HaveOutMsg(msglen,msg,plevel);
}

// Function name: KFLToClose
// Author       : CHENYH 2012/5/28 15:35:20
// Description  : �жϹر�FIX���ӣ���Ҫ���״̬��ȷ���Ƿ���Ľ�������
// Return type  : void 
void KFLToClose()
{
   g_FIXLink.ToCloseSession();
}


// Function name: KFLToDoEOD
// Author       : CHENYH 2012/5/28 15:36:29
// Description  : ִ��EOD����
// Return type  : int >=0: �ɹ�ִ�У�<0: EOD����ʧ��
int KFLToDoEOD()
{
   return(g_FIXLink.ToDoEndOfDay());
}