/********************************************************************
	created:	2007/12/13
	created:	13:12:2007   16:03
	filename: 	D:\proj\ksbass\FIX\KSFMQ\KSFMQ.h
	file path:	D:\proj\ksbass\FIX\KSFMQ
	file base:	KSFMQ
	file ext:	h
	author:		Yonghua.Chen
	
	purpose:	 本接口是为了仿真MQ，采用本地数据文件模式来实现的便于检查
   跟踪的MQ。
         本接口库提供了两种接口模式：
         · C接口函数集合，同时也可供C#之类的语言使用
         · JAVA接口函数集合
         这种模式仅适用于同机下多进程间数据交换。
         但是约定只有一个进程可以读取数据；2011-10-22 11:51:58
         尽管在本模式下，每个实际的队列可以被多个线程或进程公用，但
         在实际使用中，每个线程必须使用各自独立的队列句柄用于接收Recv
         或发送Send消息。
         即一个队列对象句柄不能被多个线程公用，若要各个线程
         要操作同一个对象，只能通过Open方式使用。
         即使使用相同方式，并通过外部数据保护能够确保仅一个线程同时该句柄，
         也绝对不能使用在Recv模式上(除非使用FMQRecvMessageEx的bAutoCommit=1模式)。
         且这种方式不如新打开句柄来得效率高。
         Recv模式：
                  当使用FMQRecvMessage时候或JAVA的接收函数时候，需要对应的
         FMQCommitRecvMessage；
                  若使用FMQRecvMessageEx的bAutoCommit不为0的时候，则不再需要
         后续调用FMQCommitRecvMessage了。
         注意MAX_MQS参数定义的一个进程可同时最多打开这类句柄的个数限制。
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

#define MAX_MQS   20  // 一个进程最多打开的队列个数(IN/OUT)


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


// 函数名: FMQOpenOutgoing
// 编程  : 陈永华 2007-11-6 13:31:12
// 描述  : 打开Outgoing队列
// 返回  : KSFMQ_API int : 参考KSFMQ_xxxx的错误代码
// 参数  : const char *queueName [IN]: Outgoing队列路径
// 参数  : int *OHandle [OUT]: 返回打开的Outgoing队列句柄
KSFMQ_API int FMQOpenOutgoing(const char *queueName, int *OHandle);


// 函数名: FMQSendMessage
// 编程  : 陈永华 2007-11-6 13:31:17
// 描述  : 向Outgoing队列发送消息
// 返回  : KSFMQ_API int   : 参考KSFMQ_xxxx的错误代码
// 参数  : int OHandle [IN]: Outgoing队列句柄
// 参数  : int nMsgLen [IN]: 发送消息的字节长度
// 参数  : char *msgBuf [IN]: 发送消息
KSFMQ_API int FMQSendMessage(int OHandle, int nMsgLen, char *msgBuf);


// 函数名: FMQOpenIncoming
// 编程  : 陈永华 2007-11-6 13:31:20
// 描述  : 打开Incoming队列
// 返回  : KSFMQ_API int  : 参考KSFMQ_xxxx的错误代码
// 参数  : const char *queueName [IN]: Incoming队列路径
// 参数  : int *IHandle [OUT]: 返回打开的Incoming队列句柄
KSFMQ_API int FMQOpenIncoming(const char *queueName, int *IHandle);

// 函数名: FMQRecvMessage
// 编程  : 陈永华 2007-11-6 13:31:23
// 描述  : 从Incoming队列接收消息，处理完毕后需要调用FMQCommitRecvMessage
// 返回  : KSFMQ_API int   : 参考KSFMQ_xxxx的错误代码
// 参数  : int IHandle [IN]: Incoming队列句柄
// 参数  : int msTimeout [IN]: 以毫秒计的等待接收超时时间，<=0: 立即返回； 
// 参数  : int *nMsgLen [IN/OUT]: IN 的参数为msgBuf的空间字节大小；OUT的为返回接收到的消息长度
// 参数  : char *msgBuf [OUT]: 接收消息的缓存
KSFMQ_API int FMQRecvMessage(int IHandle, int msTimeout, int *nMsgLen, char *msgBuf);


// 函数名: FMQRecvMessageEx
// 编程  : 陈永华 2007-12-13 15:29:54
// 描述  : 从Incoming队列接收消息, 为FMQRecvMessage扩展模式，可以指定是否自动标识已经提交
// 返回  : int    : 参考KSFMQ_xxxx的错误代码
// 参数  : int IHandle [IN]: Incoming队列句柄
// 参数  : int msTimeout [IN]: 以毫秒计的等待接收超时时间，<=0: 立即返回
// 参数  : int *nMsgLen [IN/OUT]: IN 的参数为msgBuf的空间字节大小；OUT的为返回接收到的消息长度
// 参数  : char *msgBuf [OUT]: 接收消息的缓存
// 参数  : int bAutoCommit [IN]: 0 － 非自动commit，需要后续调用FMQCommitRecvMessage；其他则自动提交，不再需要调用FMQCommitRecvMessage
KSFMQ_API int FMQRecvMessageEx(int IHandle, int msTimeout, int *nMsgLen, char *msgBuf,int bAutoCommit);

// 函数名: FMQCommitRecvMessage
// 编程  : 陈永华 2007-11-6 13:39:59
// 描述  : 接收消息的事务递交, 本函数只能用于一个IHandle独立线程在使用的情况下使用
// 返回  : KSFMQ_API int  : 参考KSFMQ_xxxx的错误代码
// 参数  : int IHandle[IN]: Incoming队列句柄
// 参数  : int bCommit [IN]: 0-表示接收后处理失败，保留本消息；!=0:表示完成本次接收，消息已经被正常处理
KSFMQ_API int FMQCommitRecvMessage(int IHandle, int bCommit);


// 函数名: FMQClose
// 编程  : 陈永华 2007-11-6 13:31:26
// 描述  : 关闭打开的队列
// 返回  : KSFMQ_API int   : 参考KSFMQ_xxxx的错误代码
// 参数  : int Handle [IN]: 打开队列句柄
KSFMQ_API int FMQClose(int Handle);


// 函数名: FMQCreate
// 编程  : 陈永华 2007-11-6 13:31:29
// 描述  : 创建队列
// 返回  : int   : 参考KSFMQ_xxxx的错误代码
// 参数  : const char *queueName [IN]: 队列消息路径
KSFMQ_API int FMQCreate(const char *queueName);


// 函数名: FMQReadMessage
// 编程  : 陈永华 2011-10-23 12:10:51
// 描述  : 直接扫描队列数据，不改变读取标记
// 返回  : int 返回成功读取消息的长度，=0: FMQ中无指定的消息号；<0: 参考KSFMQ_xxxx的错误代码
// 参数  : int Handle [IN]: 打开队列句柄
// 参数  : int msgno [IN]: 从1开始的消息号
// 参数  : char *msgbuf  [OUT]: 接收消息的缓存
// 参数  : unsigned int msgsize [IN]: msgbuf的缓存长度
// 参数  : char *flag [OUT]: 返回该消息的读取标记
KSFMQ_API int FMQReadMessage(int Handle, int msgno, char *msgbuf, unsigned int msgsize, char *flag);


// 函数名: FMQIsReset
// 编程  : 陈永华 2011-10-24 16:56:18
// 描述  : 检查接收队列是否被清空
// 返回  : int 0-没有被清空；1-被清空了；否则参考KSFMQ_xxxx的错误代码
// 参数  : int IHandle[IN]: Incoming队列句柄
KSFMQ_API int FMQIsReset(int IHandle);

// 函数名: FMQSize
// 编程  : 陈永华 2011-10-26 13:31:26
// 描述  : 获取队列中已有的消息总数
// 返回  : int   : 返回队列中已有的消息总数；<0: KSFMQ_ERROR_INVALID_HANDLE - 错误的队列句柄;
// 参数  : int Handle [IN]: 打开队列句柄
KSFMQ_API int FMQSize(int Handle);


// 函数名: FMQRSMsgs
// 编程  : 陈永华 2011-10-27 0:05:22
// 描述  : 读取队列中，接收或发送的消息数
// 返回  : int : 返回队列中，接收或发送的消息数；<0: KSFMQ_ERROR_INVALID_HANDLE - 错误的队列句柄;
// 参数  : int Handle [IN]: 打开队列句柄
KSFMQ_API int FMQRSMsgs(int Handle);
#ifdef __cplusplus
}
#endif

#undef KSFMQ_API

#endif
