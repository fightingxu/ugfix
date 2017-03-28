// FMQStatusFile.h: interface for the CFMQStatusFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FMQSTATUSFILE_H__27661ADE_83CF_4123_9576_4352AD26B937__INCLUDED_)
#define AFX_FMQSTATUSFILE_H__27661ADE_83CF_4123_9576_4352AD26B937__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef __cplusplus
extern "C" {
#endif
   
   
   /* 以下代码是用来字节对齐使用的 */
   /* 以下代码是用来字节对齐使用的 */
#ifdef WIN32
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
   //#pragma pack(push,1)
#else
#ifdef HP_UX
#define __PACKED__
#pragma pack 1
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif
#endif
   
#define LBYTEID 0x1023   // 本机的通讯协议识别码
#define RBYTEID 0x2310   // 反序的通讯协议识别码

   typedef struct _T_FMQSTATUS
   {
      unsigned short byteid;     // 让对方识别本文件主体(写)程序运行的字节序  -- 目前先不考虑不同字节序 2011-10-23 11:24:43
      int            status;     // 主体程序的状态 -1: 暂停；0: 未启动；1: 在启动中；2: 正常启动
      unsigned int   lasttime;   // 最新写入的时间点(time(NULL))，以检查对手是否正常在线中，以心跳方式
      unsigned int   partnertm;  // 本方读取到的对方的时间点, 不改变原来的字节序，即使不同也不要该
      unsigned int   sormsgs;    // 发送给对方的订单类消息总数(从上次EOD开始)
      unsigned int   soemsgs;     // 发送给对方的执行类消息总数
      unsigned int   smsgs;      // 发送给对方的常规请求、应答类消息
      unsigned int   rormsgs;     // 接收到对方的订单类消息总数(从上次EOD开始)
      unsigned int   roemsgs;     // 接收到对方的执行类消息总数
      unsigned int   rmsgs;      // 接收到对方的常规请求、应答类消息
   } __PACKED__ T_FMQSTATUS;


   
#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
#else
#ifdef HP_UX
#pragma pack 0
#else
#pragma options align=reset
#endif
#endif
#endif
#undef __PACKED__
   
#ifdef __cplusplus
}
#endif


class CFMQStatusFile  
{
private:
   int m_handle;  // 文件句柄
//   bool m_bOut;   // 打开方式，是否为写入方式
public:
   T_FMQSTATUS status;  // 状态信息

private:
   
public:
	int InStatus();
	int OutStatus();
	int Open(const char *path, const char *sid, bool bCreate);
	CFMQStatusFile();
	virtual ~CFMQStatusFile();
};

#endif // !defined(AFX_FMQSTATUSFILE_H__27661ADE_83CF_4123_9576_4352AD26B937__INCLUDED_)
