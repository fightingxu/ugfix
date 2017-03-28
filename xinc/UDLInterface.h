/********************************************************************
	created:	2011/08/16
	created:	16:8:2011   17:06
	filename: 	C:\dd\projects\FIXIII\UGate\xinc\UDLInterface.h
	file path:	C:\dd\projects\FIXIII\UGate\xinc
	file base:	UDLInterface
	file ext:	h
	author:		CHENYH
	
	purpose:	本头文件，即为UDL模块必须提供的 C 函数接口
      UDL开发要点：
         考虑到本平台上，更多为大订单，即有大批量的成交需要处理
         因此，对IN / OUT 在有可能的情况下，要将成交执行消息处理
         与其他消息处理独立出处理线程。

*********************************************************************/
#ifndef _UDL_I_H
#define _UDL_I_H

#ifdef __cplusplus
extern "C" {
#endif
   
   // 函数名: UDLInitialize
   // 编程  : 陈永华 2011-8-17 14:42:01
   // 描述  : 初始化UDL模块，但还不要建立具体的连接信息
   //       内部包括各参数的配置信息
   // 返回  : int <0: 表示初始化失败；否则，表示成功
   int UDLInitialize();

   // 函数名: UDLGetStatus
   // 编程  : 陈永华 2011-8-21 10:15:51
   // 描述  : 检查UDL模块内部状态，若内部异常，则返回<0
   //         本函数内部必须通过检查内部变量，快速返回其状态，
   //         不可通过大量处理等延时导出UDL内部的状态，
   //         可以有所迟缓，一旦异常，UGate会被强制退出 (需要重新启动)
   // 返回  : int <0 : UDL异常，程序必须重启或改配置后方能恢复；>=0:状态返回成功，继续跟踪
   // 参数  : char *statusmsg [OUT]: 用如下格式返回各个Partner的状态：
   //             <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerID2>:<status>:<load>:<errmsg>
   //             status: 0 - 没有启动；1 - 已经正常启动
   //             load: 负载值，即还没有被处理的OUT消息个数
   // 参数  : unsigned int smsize [IN]: statusmsg的缓存字节数(大概近4000个字节) 
   int UDLGetStatus(char *statusmsg,unsigned int smsize);

   // 函数名: UDLExit
   // 编程  : 陈永华 2011-8-18 21:03:38
   // 描述  : UGate要求UDL退出
   // 返回  : int <0: 表示初始化失败；否则，表示成功
   int UDLExit();

   // 函数名: UDLOpen
   // 编程  : 陈永华 2011-8-19 23:20:46
   // 描述  : 正式启动本会话(Session)，与对方系统对接
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
   // 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
   int UDLOpen(const char *sLocalID, const char *sPartnerID,char *emsg);


   // 函数名: UDLClose
   // 编程  : 陈永华 2011-8-19 23:34:35
   // 描述  : 关闭与对方的连接，进入Close状态
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
   // 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
   int UDLClose(const char *sLocalID, const char *sPartnerID,char *emsg);


   // 函数名: UDLEndOfDay
   // 编程  : 陈永华 2011-8-19 23:35:58
   // 描述  : 对本连接做Reset处理，清除之前处理缓存的数据，并进入关闭状态
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *sPartnerID [IN]: 指定操作Session的 PartnerID
   // 参数  : char *emsg [OUT]: 当返回失败的时候，返回失败信息
   int UDLEndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);

   //////////////////////////////////////////////////////////////////////////
   // !!! 当配置中的OUTMODE==0的时候，UGATE框架才调用本函数
   // 否则，UDL希望UG框架管理OutFIXMsg，并通过调用 UG_GetOutMsg检查和获取需要Out处理的消息
   // 尽管 UDL需要提供本函数入口，但可以为空，或通过SQLDebugLog报警，表示配置错误！
   //////////////////////////////////////////////////////////////////////////
   // 函数名: UDLOnMessageOut
   // 编程  : 陈永华 2011-8-18 20:39:40
   // 描述  : UG收到来自FS平台的FIX消息，需要通过UDL处理，发送给对手方
   //          
   // 返回  : int <0: 失败；否则，成功
   // 参数  : const char *fixmsg [IN]: 业务类的 FIX格式的Message (参考协议)
   // 参数  : char *eMsg [OUT]: 当失败的时候(非协议类失败)，返回错误信息(<80字节)
   int UDLOnMessageOut(const char *fixmsg, char *eMsg);


#ifdef __cplusplus
}
#endif
#endif