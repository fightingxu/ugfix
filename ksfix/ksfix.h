#ifndef _KSFIX_H
#define _KSFIX_H

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

// Function name: KFLSetLogPath
// Author       : CHENYH 2012/5/28 15:14:00
// Description  : ����FIX��Ϣ��־�Ĵ��·��
// Return type  : void 
// Argument : const char *logpath [IN]: �����־·��
BUPUB_API void KFLSetLogPath(const char *logpath);


// Function name: KFLSetSession
// Author       : CHENYH 2012/5/28 15:14:55
// Description  : ����FIX��SessionID��FIX�汾
// Return type  : void 
// Argument : const char *localid [IN]: ����ID
// Argument : const char *partnerid [IN]: �Է�ID
// Argument : const char *fixversion [IN]: FIX�汾�ţ���"FIX.4.4"
BUPUB_API void KFLSetSession(const char *localid, const char *partnerid, const char *fixversion);



// Function name: KFLSetHeartBeat
// Author       : CHENYH 2012/5/28 15:16:21
// Description  : ���ñ������е���������ͼ����ʱ���������ٶ����
// Return type  : void 
// Argument : int hbt [IN]: �������ʱ�䣬�� ��30
// Argument : int hbtlatency [IN]: ������ϢԤ����ʱ���� ��5
BUPUB_API void KFLSetHeartBeat(int hbt, int hbtlatency);


// Function name: KFLSetUserPassword
// Author       : CHENYH 2012/5/28 15:19:05
// Description  : ���õ�½�����������֤�ı����ͶԷ����û���������
// Return type  : void 
// Argument : const char *lusername [IN]: �����û���
// Argument : const char *lpassword [IN]: �����û���
// Argument : const char *pusername [IN]: �Է��û���
// Argument : const char *ppassword [IN]: �Է��û���
BUPUB_API void KFLSetUserPassword(const char *lusername, const char *lpassword, const char *pusername, const char *ppassword);


// Function name: KFLGetStatus
// Author       : CHENYH 2012/5/28 15:20:37
// Description  : ��ȡĿǰFIX����״̬
// Return type  : int 0 - Close��1 - Connecting(����������)��2 - Open(���������ӣ������ڹ�����)
BUPUB_API int KFLGetStatus();


// Function name: KFLSetFIXStorePath
// Author       : CHENYH 2012/5/26 21:28:56
// Description  : ����FIX�����ݳ־û�·��
// Return type  : int 0:�ɹ���-1:ʧ��
// Argument : const char *mpath [IN]: ���洢Ŀ¼·��������Ϊ�У����ҿ��Դ�����·�������򣬽�����ʧ��
// Argument : const char *bkpath [IN]: ���洢Ŀ¼·��������ΪNULL��""����ʾ�ޱ��洢·��
BUPUB_API int KFLSetFIXStorePath(const char *mpath, const char *bkpath);


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
BUPUB_API int KFLToOpen(const char *svrip, int svrport);

#ifndef MAXFIXDATALENGTH
#define MAXFIXDATALENGTH 8192
#endif

// Function name: KFLGetInMsg
// Author       : CHENYH 2012/5/28 15:51:24
// Description  : ȡ�յ���FIX��Ϣ����
// Return type  : int >0: �����յ�FIX��Ϣ�ĳ��ȣ�0: û���յ���FIX��Ϣ 
// Argument : char *msgbuf [OUT]: �յ���FIX��Ϣ�Ļ��棬��Ҫ�㹻��>=8K, ��ģ��֧���8K�ֽڵ���Ϣ
// Argument : unsigned int waitms [IN]: �ȴ����յ�ʱ�� ���룬����>=100ms
BUPUB_API int KFLGetInMsg(char *msgbuf, unsigned int waitms);


// Function name: KFLHaveOutMsg
// Author       : CHENYH 2012/5/28 16:07:07
// Description  : �ύ�跢��FIX��Ϣ����
// Return type  : void 
// Argument : int msglen [IN]: FIX��Ϣ�ĳ���
// Argument : const char *msg [IN]: FIX��Ϣ
// Argument : int plevel [IN]: ���ȼ���0 or 1����Ϊ0
BUPUB_API void KFLHaveOutMsg(int msglen, const char *msg, int plevel);


// Function name: KFLToClose
// Author       : CHENYH 2012/5/28 15:35:20
// Description  : �жϹر�FIX���ӣ���Ҫ���״̬��ȷ���Ƿ���Ľ�������
// Return type  : void 
BUPUB_API void KFLToClose();

// Function name: KFLToDoEOD
// Author       : CHENYH 2012/5/28 15:36:29
// Description  : ִ��EOD����
// Return type  : int >=0: �ɹ�ִ�У�<0: EOD����ʧ��
BUPUB_API int KFLToDoEOD();


#undef BUPUB_API

#endif