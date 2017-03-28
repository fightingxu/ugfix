/********************************************************************
	created:	2011/10/24
	created:	24:10:2011   21:46
	filename: 	C:\dd\projects\FIXIII\UGate\ugfmq\UGFMQ.h
	file path:	C:\dd\projects\FIXIII\UGate\ugfmq
	file base:	UGFMQ
	file ext:	h
	author:		CHENYH
	
	purpose:	本UGate的设计方案：
      为了能够让UGate的支持第三方接口和本UGate独立进程方式进行消息交换，
      特别采用这种可跟踪的文件仿真消息交换模式，进行消息交换，只要内含
      一个KSFMQ模块，利用如下几个KSFMQ消息队列名：
         (假设UGate端的ID，为<LocalID>; 对端的ID，为<PartnerID>)
         1. UGate本方作为BuySide, 而对端则作为SellSide 如对端为本系统的某类交易市场的交易系统或交易所系统
            OR2<PartnerID>:   <LocalID> -> <PartnerID> 
                           UGate发送订单类请求消息，如MsgType='D','E','F' etc,
                           对端则以接收方式打开该消息队列，并进行相应的处理；
            OE2<LocalID>:     <LocalID> <- <LocalID>
                           UGate接收来自对端的订单执行类的消息，
                           对端则将订单执行的消息，通过该队列发送给UGate；
            R2<PartnerID>:    <LocalID> -> <PartnerID>
                           UGate将非订单的请求类，如自定义请求-应答类消息
                           通过本队列发送给对端；
            A2<LocalID>:      <LocalID> <- <PartnerID>
                           UGate通过本队列接收来自对端对请求消息处理的应答消息；

          2. UGate相对对端为SellSide，接收来自对端的请求类消息，即对端相对为BuySide：
            OR2<LocalID>:     <LocalID> <- <PartnerID>
            OE2<PartnerID>:   <LocalID> -> <PartnerID>
            R2<LocalID>:      <LocalID> <- <PartnerID>
            A2<PartnerID>:    <LocalID> -> <PartnerID>

         独立订单类请求和应答是为了将该类请求进行独立处理；
         另外由于本平台处理的订单量比较大，尤其执行类的消息量比常规系统要大，
         因此，特别单列了请求应答类消息，为其独立队列。
*********************************************************************/
// UGFMQ.h: interface for the CUGFMQ class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGFMQ_H__1D7031F3_C198_4C56_8D6E_34FCADA06CD4__INCLUDED_)
#define AFX_UGFMQ_H__1D7031F3_C198_4C56_8D6E_34FCADA06CD4__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InFMQ.h"
#include "OutFMQ.h"
#include "FMQStatusFile.h"

class CUGFMQ  
{
private:
   CFMQStatusFile hLocal;  // 本方的状态(心跳)文件句柄
   CFMQStatusFile hPartner; // 对方的状态

   // 本端作为BuySide的:
   COutFMQ  m_OR2Partner;
   CInFMQ   m_OE2Local;

   // 本端作为SellSide的:
   CInFMQ   m_OR2Local;
   COutFMQ  m_OE2Partner;

   CInFMQ   m_2Local;      // 各类从对方接收的其他消息
   COutFMQ  m_2Partner;    // 各类提交给对方的其他消息

   int m_InRunStatus;
   
public:
   char m_LocalID[12];    // 本接口的本地端ID，在组包的时候需要!
   char m_PartnerID[12];  // 本接口的对手端ID，在组包的时候需要!
   char m_FMQPath[80];    // 为本接口的主目录路径，并在下建立多个FMQ以进行数据交换   
   int m_Status;   // 当前状态: -1:暂停；0:还没有启动；1:正在启动中；2: 与对端连接成功，正在工作中

private:
	bool RestoreIn(char *emsg);
	bool RestoreOut(char *emsg);
	bool PreOpen(char *emsg);
	int OpenAllFMQ();
	int CheckPartnerStatus();
	int ResetAllFMQ();
   

public:
	int Run();
	int Exit();
	int OnMessageOut(const char *fixmsg, char *eMsg);
	int EndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg);
	int Close(const char *sLocalID, const char *sPartnerID,char *emsg);
	int Open(const char *sLocalID, const char *sPartnerID,char *emsg);
	int GetStatus(char *statusmsg,unsigned int smsize);
	int Initialize();
	CUGFMQ();
	virtual ~CUGFMQ();

};

extern CUGFMQ g_UGFMQ;
#endif // !defined(AFX_UGFMQ_H__1D7031F3_C198_4C56_8D6E_34FCADA06CD4__INCLUDED_)
