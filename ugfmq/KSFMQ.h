/********************************************************************
	created:	2007/12/13
	created:	13:12:2007   16:03
	filename: 	D:\proj\ksbass\FIX\KSFMQ\KSFMQ.h
	file path:	D:\proj\ksbass\FIX\KSFMQ
	file base:	KSFMQ
	file ext:	h
	author:		Yonghua.Chen
	
	purpose:	 ���ӿ���Ϊ�˷���MQ�����ñ��������ļ�ģʽ��ʵ�ֵı��ڼ��
   ���ٵ�MQ��
         ���ӿڿ��ṩ�����ֽӿ�ģʽ��
         �� C�ӿں������ϣ�ͬʱҲ�ɹ�C#֮�������ʹ��
         �� JAVA�ӿں�������
         ����ģʽ��������ͬ���¶���̼����ݽ�����
         ����Լ��ֻ��һ�����̿��Զ�ȡ���ݣ�2011-10-22 11:51:58
         �����ڱ�ģʽ�£�ÿ��ʵ�ʵĶ��п��Ա�����̻߳���̹��ã���
         ��ʵ��ʹ���У�ÿ���̱߳���ʹ�ø��Զ����Ķ��о�����ڽ���Recv
         ����Send��Ϣ��
         ��һ�����ж��������ܱ�����̹߳��ã���Ҫ�����߳�
         Ҫ����ͬһ������ֻ��ͨ��Open��ʽʹ�á�
         ��ʹʹ����ͬ��ʽ����ͨ���ⲿ���ݱ����ܹ�ȷ����һ���߳�ͬʱ�þ����
         Ҳ���Բ���ʹ����Recvģʽ��(����ʹ��FMQRecvMessageEx��bAutoCommit=1ģʽ)��
         �����ַ�ʽ�����´򿪾������Ч�ʸߡ�
         Recvģʽ��
                  ��ʹ��FMQRecvMessageʱ���JAVA�Ľ��պ���ʱ����Ҫ��Ӧ��
         FMQCommitRecvMessage��
                  ��ʹ��FMQRecvMessageEx��bAutoCommit��Ϊ0��ʱ��������Ҫ
         ��������FMQCommitRecvMessage�ˡ�
         ע��MAX_MQS���������һ�����̿�ͬʱ�����������ĸ������ơ�
*********************************************************************/
#ifndef KSFMQ_H
#define KSFMQ_H
#ifdef KSFMQ_EXPORTS
#ifdef _WINDOWS
#define KSFMQ_API __declspec(dllexport)
#else
#define KSFMQ_API 
#endif
#else
#ifdef _WINDOWS
#define KSFMQ_API __declspec(dllimport)
#else
#define KSFMQ_API 
#endif
#endif

#define MAX_MQS   20  // һ���������򿪵Ķ��и���(IN/OUT)


// General KSFMQ Error codes
#define KSFMQ_OK 0L
#define KSFMQ_ERROR_ACCESS_DENIED -1072824283L
#define KSFMQ_ERROR_ILLEGAL_FORMATNAME -1072824290L
#define KSFMQ_ERROR_INVALID_HANDLE -1072824313L

// Error codes for opening queue
#define KSFMQ_ERROR_QUEUE_NOT_FOUND -1072824317L
#define KSFMQ_ERROR_NO_DS -1072824301L
#define KSFMQ_ERROR_SHARING_VIOLATION -1072824311L
#define KSFMQ_ERROR_ILLEGAL_QUEUE_PATHNAME -1072824300L

// Error codes for sending messages
#define KSFMQ_ERROR_INSUFFICIENT_RESOURCES -1072824281L
#define KSFMQ_ERROR_MESSAGE_STORAGE_FAILED -1072824278L

// Error codes for receiving messages
#define KSFMQ_ERROR_BUFFER_OVERFLOW -1072824294L
#define KSFMQ_ERROR_IO_TIMEOUT -1072824293L
#define KSFMQ_ERROR_OPERATION_CANCELLED -1072824312L
#define KSFMQ_ERROR_QUEUE_DELETED -1072824230L
#define KSFMQ_ERROR_TRANSACTION_USAGE -1072824240L
#define KSFMQ_INFORMATION_OPERATION_PENDING -1074659334L


#define FLAG_SEND  '1'  // Send Flag
#define FLAG_UNCMT 'a'  // Received but not commited
#define FLAG_RECV  'A'  // Received Flag


#ifdef __cplusplus
extern "C" {
#endif


// ������: FMQOpenOutgoing
// ���  : ������ 2007-11-6 13:31:12
// ����  : ��Outgoing����
// ����  : KSFMQ_API int : �ο�KSFMQ_xxxx�Ĵ������
// ����  : const char *queueName [IN]: Outgoing����·��
// ����  : int *OHandle [OUT]: ���ش򿪵�Outgoing���о��
KSFMQ_API int FMQOpenOutgoing(const char *queueName, int *OHandle);


// ������: FMQSendMessage
// ���  : ������ 2007-11-6 13:31:17
// ����  : ��Outgoing���з�����Ϣ
// ����  : KSFMQ_API int   : �ο�KSFMQ_xxxx�Ĵ������
// ����  : int OHandle [IN]: Outgoing���о��
// ����  : int nMsgLen [IN]: ������Ϣ���ֽڳ���
// ����  : char *msgBuf [IN]: ������Ϣ
KSFMQ_API int FMQSendMessage(int OHandle, int nMsgLen, char *msgBuf);


// ������: FMQOpenIncoming
// ���  : ������ 2007-11-6 13:31:20
// ����  : ��Incoming����
// ����  : KSFMQ_API int  : �ο�KSFMQ_xxxx�Ĵ������
// ����  : const char *queueName [IN]: Incoming����·��
// ����  : int *IHandle [OUT]: ���ش򿪵�Incoming���о��
KSFMQ_API int FMQOpenIncoming(const char *queueName, int *IHandle);

// ������: FMQRecvMessage
// ���  : ������ 2007-11-6 13:31:23
// ����  : ��Incoming���н�����Ϣ��������Ϻ���Ҫ����FMQCommitRecvMessage
// ����  : KSFMQ_API int   : �ο�KSFMQ_xxxx�Ĵ������
// ����  : int IHandle [IN]: Incoming���о��
// ����  : int msTimeout [IN]: �Ժ���Ƶĵȴ����ճ�ʱʱ�䣬<=0: �������أ� 
// ����  : int *nMsgLen [IN/OUT]: IN �Ĳ���ΪmsgBuf�Ŀռ��ֽڴ�С��OUT��Ϊ���ؽ��յ�����Ϣ����
// ����  : char *msgBuf [OUT]: ������Ϣ�Ļ���
KSFMQ_API int FMQRecvMessage(int IHandle, int msTimeout, int *nMsgLen, char *msgBuf);


// ������: FMQRecvMessageEx
// ���  : ������ 2007-12-13 15:29:54
// ����  : ��Incoming���н�����Ϣ, ΪFMQRecvMessage��չģʽ������ָ���Ƿ��Զ���ʶ�Ѿ��ύ
// ����  : int    : �ο�KSFMQ_xxxx�Ĵ������
// ����  : int IHandle [IN]: Incoming���о��
// ����  : int msTimeout [IN]: �Ժ���Ƶĵȴ����ճ�ʱʱ�䣬<=0: ��������
// ����  : int *nMsgLen [IN/OUT]: IN �Ĳ���ΪmsgBuf�Ŀռ��ֽڴ�С��OUT��Ϊ���ؽ��յ�����Ϣ����
// ����  : char *msgBuf [OUT]: ������Ϣ�Ļ���
// ����  : int bAutoCommit [IN]: 0 �� ���Զ�commit����Ҫ��������FMQCommitRecvMessage���������Զ��ύ��������Ҫ����FMQCommitRecvMessage
KSFMQ_API int FMQRecvMessageEx(int IHandle, int msTimeout, int *nMsgLen, char *msgBuf,int bAutoCommit);

// ������: FMQCommitRecvMessage
// ���  : ������ 2007-11-6 13:39:59
// ����  : ������Ϣ������ݽ�, ������ֻ������һ��IHandle�����߳���ʹ�õ������ʹ��
// ����  : KSFMQ_API int  : �ο�KSFMQ_xxxx�Ĵ������
// ����  : int IHandle[IN]: Incoming���о��
// ����  : int bCommit [IN]: 0-��ʾ���պ���ʧ�ܣ���������Ϣ��!=0:��ʾ��ɱ��ν��գ���Ϣ�Ѿ�����������
KSFMQ_API int FMQCommitRecvMessage(int IHandle, int bCommit);


// ������: FMQClose
// ���  : ������ 2007-11-6 13:31:26
// ����  : �رմ򿪵Ķ���
// ����  : KSFMQ_API int   : �ο�KSFMQ_xxxx�Ĵ������
// ����  : int Handle [IN]: �򿪶��о��
KSFMQ_API int FMQClose(int Handle);


// ������: FMQCreate
// ���  : ������ 2007-11-6 13:31:29
// ����  : ��������
// ����  : int   : �ο�KSFMQ_xxxx�Ĵ������
// ����  : const char *queueName [IN]: ������Ϣ·��
KSFMQ_API int FMQCreate(const char *queueName);


// ������: FMQReadMessage
// ���  : ������ 2011-10-23 12:10:51
// ����  : ֱ��ɨ��������ݣ����ı��ȡ���
// ����  : int ���سɹ���ȡ��Ϣ�ĳ��ȣ�=0: FMQ����ָ������Ϣ�ţ�<0: �ο�KSFMQ_xxxx�Ĵ������
// ����  : int Handle [IN]: �򿪶��о��
// ����  : int msgno [IN]: ��1��ʼ����Ϣ��
// ����  : char *msgbuf  [OUT]: ������Ϣ�Ļ���
// ����  : unsigned int msgsize [IN]: msgbuf�Ļ��泤��
// ����  : char *flag [OUT]: ���ظ���Ϣ�Ķ�ȡ���
KSFMQ_API int FMQReadMessage(int Handle, int msgno, char *msgbuf, unsigned int msgsize, char *flag);


// ������: FMQIsReset
// ���  : ������ 2011-10-24 16:56:18
// ����  : �����ն����Ƿ����
// ����  : int 0-û�б���գ�1-������ˣ�����ο�KSFMQ_xxxx�Ĵ������
// ����  : int IHandle[IN]: Incoming���о��
KSFMQ_API int FMQIsReset(int IHandle);

// ������: FMQSize
// ���  : ������ 2011-10-26 13:31:26
// ����  : ��ȡ���������е���Ϣ����
// ����  : int   : ���ض��������е���Ϣ������<0: KSFMQ_ERROR_INVALID_HANDLE - ����Ķ��о��;
// ����  : int Handle [IN]: �򿪶��о��
KSFMQ_API int FMQSize(int Handle);


// ������: FMQRSMsgs
// ���  : ������ 2011-10-27 0:05:22
// ����  : ��ȡ�����У����ջ��͵���Ϣ��
// ����  : int : ���ض����У����ջ��͵���Ϣ����<0: KSFMQ_ERROR_INVALID_HANDLE - ����Ķ��о��;
// ����  : int Handle [IN]: �򿪶��о��
KSFMQ_API int FMQRSMsgs(int Handle);
#ifdef __cplusplus
}
#endif

#undef KSFMQ_API

#endif
