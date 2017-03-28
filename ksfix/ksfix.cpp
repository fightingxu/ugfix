#include "stdafx.h"
#include "mypub.h"
#include "FIXSession.h"
#include "FIXLinkThread.h"
#include "ksfix.h"

CFIXLinkThread g_FIXLink;


// Function name: KFLSetLogPath
// Author       : CHENYH 2012/5/28 15:14:00
// Description  : 设置FIX消息日志的存放路径
// Return type  : void 
// Argument : const char *logpath [IN]: 存放日志路径
void KFLSetLogPath(const char *logpath)
{
   g_FIXLink.SetLogPath(logpath);
}


// Function name: KFLSetSession
// Author       : CHENYH 2012/5/28 15:14:55
// Description  : 设置FIX的SessionID和FIX版本
// Return type  : void 
// Argument : const char *localid [IN]: 本方ID
// Argument : const char *partnerid [IN]: 对方ID
// Argument : const char *fixversion [IN]: FIX版本号，如"FIX.4.4"
void KFLSetSession(const char *localid, const char *partnerid, const char *fixversion)
{
   g_FIXLink.SetSession(localid,partnerid,fixversion);
}



// Function name: KFLSetHeartBeat
// Author       : CHENYH 2012/5/28 15:16:21
// Description  : 设置本链接中的心跳间隔和检测延时，与网络速度相关
// Return type  : void 
// Argument : int hbt [IN]: 心跳间隔时间，秒 如30
// Argument : int hbtlatency [IN]: 心跳消息预计延时，秒 如5
void KFLSetHeartBeat(int hbt, int hbtlatency)
{
   g_FIXLink.SetHeartBtInt(hbt,hbtlatency);
}


// Function name: KFLSetUserPassword
// Author       : CHENYH 2012/5/28 15:19:05
// Description  : 设置登陆中用于身份验证的本方和对方的用户名和密码
// Return type  : void 
// Argument : const char *lusername [IN]: 本方用户名
// Argument : const char *lpassword [IN]: 本方用户名
// Argument : const char *pusername [IN]: 对方用户名
// Argument : const char *ppassword [IN]: 对方用户名
void KFLSetUserPassword(const char *lusername, const char *lpassword, const char *pusername, const char *ppassword)
{
   g_FIXLink.SetUserPassword(lusername,lpassword,pusername,ppassword);
}


// Function name: KFLGetStatus
// Author       : CHENYH 2012/5/28 15:20:37
// Description  : 获取目前FIX工作状态
// Return type  : int 0 - Close；1 - Connecting(正在连接中)；2 - Open(即正常连接，并处于工作中)
int KFLGetStatus()
{
   return(g_FIXLink.GetStatus());
}


// Function name: KFLSetFIXStorePath
// Author       : CHENYH 2012/5/26 21:28:56
// Description  : 设置FIX的数据持久化路径
// Return type  : int 0:成功；-1:失败
// Argument : const char *mpath [IN]: 主存储目录路径，必须为有，并且可以创建的路径；否则，将返回失败
// Argument : const char *bkpath [IN]: 备存储目录路径，可以为NULL或""来表示无备存储路径
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
// Description  : 正式启动FIX连接和工作
// Return type  : int >=0: 连接成功，并正常启动工作线程；<0: 失败，可检查日志中的说明:
/*                -1: 不能与对方建立连接；
                  -2: 打开数据持久化文件失败，可能KFLSetFIXStorePath的参数不正确；mpath路径下必须能够创建文件；
                  -3: 根据设置的心跳时间内，不能收到对方Logon消息；
                      或 对方Logon消息SessionID不正确；
                  -4: 对方的Logon消息中关键参数不正确；
                  -5: 连接后收到的第一个消息不是LOGON消息；
*/
// Argument : const char *svrip [IN]: 对方服务方连接IP地址；
// Argument : int svrport [IN]: 对方服务方连接端口；
int KFLToOpen(const char *svrip, int svrport)
{
   return(g_FIXLink.ToOpen(svrip,svrport));
}


// Function name: KFLGetInMsg
// Author       : CHENYH 2012/5/28 15:51:24
// Description  : 取收到的FIX消息数据
// Return type  : int >0: 返回收到FIX消息的长度；0: 没有收到的FIX消息 
// Argument : char *msgbuf [OUT]: 收到的FIX消息的缓存，需要足够长>=8K, 本模块支持最长8K字节的消息
// Argument : unsigned int waitms [IN]: 等待接收的时间 毫秒，建议>=100ms
int KFLGetInMsg(char *msgbuf, unsigned int waitms)
{
   return(g_FIXLink.GetInMsg(msgbuf,waitms));
}


// Function name: KFLHaveOutMsg
// Author       : CHENYH 2012/5/28 16:07:07
// Description  : 提交需发送FIX消息数据
// Return type  : void 
// Argument : int msglen [IN]: FIX消息的长度
// Argument : const char *msg [IN]: FIX消息
// Argument : int plevel [IN]: 优先级（0 or 1）高为0
void KFLHaveOutMsg(int msglen, const char *msg, int plevel)
{
   g_FIXLink.HaveOutMsg(msglen,msg,plevel);
}

// Function name: KFLToClose
// Author       : CHENYH 2012/5/28 15:35:20
// Description  : 中断关闭FIX连接，需要检查状态来确认是否真的结束工作
// Return type  : void 
void KFLToClose()
{
   g_FIXLink.ToCloseSession();
}


// Function name: KFLToDoEOD
// Author       : CHENYH 2012/5/28 15:36:29
// Description  : 执行EOD操作
// Return type  : int >=0: 成功执行；<0: EOD操作失败
int KFLToDoEOD()
{
   return(g_FIXLink.ToDoEndOfDay());
}