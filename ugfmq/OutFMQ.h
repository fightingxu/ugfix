// OutFMQ.h: interface for the COutFMQ class.
// 专门向FMQ队列中发送消息的类
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTFMQ_H__082E73BE_D1F3_47EE_B9AF_EB52A557AA81__INCLUDED_)
#define AFX_OUTFMQ_H__082E73BE_D1F3_47EE_B9AF_EB52A557AA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "KSFMQ.h"
class COutFMQ  
{
private:
   int m_handle;
public:

private:

public:
	int Size();
   int Send(int nMsgLen, const char *msgBuf);

   // 函数名: Read
   // 编程  : 陈永华 2011-10-24 20:26:02
   // 描述  : 在已经打开的本KSFMQ中，从第一条开始重新读取已写入的消息
   // 返回  : int <0:读取失败，参考KSFMQ中的错误返回码, 其中KSFMQ_ERROR_IO_TIMEOUT表示无指定的消息;
   // 参数  : int msgno [IN]: 从1开始的指定读取的消息编号
   // 参数  : char *msgbuf [OUT]: [OUT]: 消息读取存放缓存区
   // 参数  : unsigned int msgsize[IN]: msgBuf缓存长度
   // 参数  : char *flag [OUT]: 单字节返回该消息是否被读取过, ' '表示未用Recv读取过；'A'表示已经被Recv读取过 
	int Read(int msgno, char *msgbuf, unsigned int msgsize, char *flag);

   // 函数名: Reset
   // 编程  : 陈永华 2011-10-24 20:53:50
   // 描述  : 重置本KSFMQ
   // 返回  : int  0: 成功；否则<0: 失败
   // 参数  : const char *path
   // 参数  : const char *name
	int Reset(const char *path, const char *name);

   // 函数名: Open
   // 编程  : 陈永华 2011-10-24 20:55:14
   // 描述  : 以发送方式打开指定的KSFMQ队列
   // 返回  : int 返回0:成功; 否则<0: KSFMQ_ERROR_QUEUE_NOT_FOUND 即打开失败
   // 参数  : const char *path [IN]: KSFMQ的宿主路径
   // 参数  : const char *name [IN]: 要打开的KSFMQ的队列名
	int Open(const char *path, const char *name);

   // 函数名: Close
   // 编程  : 陈永华 2011-10-24 21:17:22
   // 描述  : 关闭已经打开的KSFMQ队列
   // 返回  : void 
	void Close();

   COutFMQ();
	virtual ~COutFMQ();

};

#endif // !defined(AFX_OUTFMQ_H__082E73BE_D1F3_47EE_B9AF_EB52A557AA81__INCLUDED_)
