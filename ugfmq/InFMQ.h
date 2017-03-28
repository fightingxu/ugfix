// InFMQ.h: interface for the CInFMQ class.
// 专门从FMQ队列中读取消息的类
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INFMQ_H__DA18AD67_D037_4203_938A_1D974B00E9C7__INCLUDED_)
#define AFX_INFMQ_H__DA18AD67_D037_4203_938A_1D974B00E9C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "KSFMQ.h"

class CInFMQ  
{
private:
   int m_handle;
public:
   
private:
   
public:
	int RMsgs();
	int Size();

   // 函数名: Recv
   // 编程  : 陈永华 2011-10-24 20:01:59
   // 描述  : 从已经打开的本KSFMQ中，读取未读取过的消息
   // 返回  : int <0:读取失败，参考KSFMQ中的错误返回码, 其中KSFMQ_ERROR_IO_TIMEOUT即在指定时间内没有读到新消息;
   //            >0: 成功读取未被接收过的消息;
   // 参数  : int msTimeout[IN]: [IN]: 以毫秒计的等待接收超时时间，<=0: 立即返回
   // 参数  : char *msgBuf[OUT]: 消息读取存放缓存区
   // 参数  : int msgsize[IN]: msgBuf缓存长度
	int Recv(int msTimeout, char *msgBuf, int msgsize);

   // 函数名: Read
   // 编程  : 陈永华 2011-10-24 20:26:02
   // 描述  : 在已经打开的本KSFMQ中，从第一条开始重新读取已写入的消息
   // 返回  : int <0:读取失败，参考KSFMQ中的错误返回码, 其中KSFMQ_ERROR_IO_TIMEOUT表示无指定的消息;
   // 参数  : int msgno [IN]: 从1开始的指定读取的消息编号
   // 参数  : char *msgbuf [OUT]: [OUT]: 消息读取存放缓存区
   // 参数  : unsigned int msgsize[IN]: msgBuf缓存长度
   // 参数  : char *flag [OUT]: 单字节返回该消息是否被读取过, ' '表示未用Recv读取过；'A'表示已经被Recv读取过 
	int Read(int msgno, char *msgbuf, unsigned int msgsize, char *flag);


   // 函数名: IsReset
   // 编程  : 陈永华 2011-10-24 20:51:49
   // 描述  : 本KSFMQ是否被重置了（即清空了，即做End Of Day处理）
   // 返回  : bool 返回是否被重置，true: 即被重置了；false: 没有被重置
	bool IsReset();

   // 函数名: Close
   // 编程  : 陈永华 2011-10-24 21:17:22
   // 描述  : 关闭已经打开的KSFMQ队列
   // 返回  : void 
	void Close();

   // 函数名: Open
   // 编程  : 陈永华 2011-10-24 20:55:14
   // 描述  : 以接收方式打开指定的KSFMQ队列
   // 返回  : int 返回0:成功; 否则<0: KSFMQ_ERROR_QUEUE_NOT_FOUND 即打开失败
   // 参数  : const char *path [IN]: KSFMQ的宿主路径
   // 参数  : const char *name [IN]: 要打开的KSFMQ的队列名
	int Open(const char *path, const char *name);

	CInFMQ();
	virtual ~CInFMQ();

};

#endif // !defined(AFX_INFMQ_H__DA18AD67_D037_4203_938A_1D974B00E9C7__INCLUDED_)
