/********************************************************************
	created:	2011/10/24
	created:	24:10:2011   21:46
	filename: 	C:\dd\projects\FIXIII\UGate\ugfmq\UGFMQ.h
	file path:	C:\dd\projects\FIXIII\UGate\ugfmq
	file base:	UGFMQ
	file ext:	h
	author:		CHENYH
	
	purpose:	��UGate����Ʒ�����
      Ϊ���ܹ���UGate��֧�ֵ������ӿںͱ�UGate�������̷�ʽ������Ϣ������
      �ر�������ֿɸ��ٵ��ļ�������Ϣ����ģʽ��������Ϣ������ֻҪ�ں�
      һ��KSFMQģ�飬�������¼���KSFMQ��Ϣ��������
         (����UGate�˵�ID��Ϊ<LocalID>; �Զ˵�ID��Ϊ<PartnerID>)
         1. UGate������ΪBuySide, ���Զ�����ΪSellSide ��Զ�Ϊ��ϵͳ��ĳ�ཻ���г��Ľ���ϵͳ������ϵͳ
            OR2<PartnerID>:   <LocalID> -> <PartnerID> 
                           UGate���Ͷ�����������Ϣ����MsgType='D','E','F' etc,
                           �Զ����Խ��շ�ʽ�򿪸���Ϣ���У���������Ӧ�Ĵ���
            OE2<LocalID>:     <LocalID> <- <LocalID>
                           UGate�������ԶԶ˵Ķ���ִ�������Ϣ��
                           �Զ��򽫶���ִ�е���Ϣ��ͨ���ö��з��͸�UGate��
            R2<PartnerID>:    <LocalID> -> <PartnerID>
                           UGate���Ƕ����������࣬���Զ�������-Ӧ������Ϣ
                           ͨ�������з��͸��Զˣ�
            A2<LocalID>:      <LocalID> <- <PartnerID>
                           UGateͨ�������н������ԶԶ˶�������Ϣ�����Ӧ����Ϣ��

          2. UGate��ԶԶ�ΪSellSide���������ԶԶ˵���������Ϣ�����Զ����ΪBuySide��
            OR2<LocalID>:     <LocalID> <- <PartnerID>
            OE2<PartnerID>:   <LocalID> -> <PartnerID>
            R2<LocalID>:      <LocalID> <- <PartnerID>
            A2<PartnerID>:    <LocalID> -> <PartnerID>

         ���������������Ӧ����Ϊ�˽�����������ж�������
         �������ڱ�ƽ̨����Ķ������Ƚϴ�����ִ�������Ϣ���ȳ���ϵͳҪ��
         ��ˣ��ر���������Ӧ������Ϣ��Ϊ��������С�
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
   CFMQStatusFile hLocal;  // ������״̬(����)�ļ����
   CFMQStatusFile hPartner; // �Է���״̬

   // ������ΪBuySide��:
   COutFMQ  m_OR2Partner;
   CInFMQ   m_OE2Local;

   // ������ΪSellSide��:
   CInFMQ   m_OR2Local;
   COutFMQ  m_OE2Partner;

   CInFMQ   m_2Local;      // ����ӶԷ����յ�������Ϣ
   COutFMQ  m_2Partner;    // �����ύ���Է���������Ϣ

   int m_InRunStatus;
   
public:
   char m_LocalID[12];    // ���ӿڵı��ض�ID���������ʱ����Ҫ!
   char m_PartnerID[12];  // ���ӿڵĶ��ֶ�ID���������ʱ����Ҫ!
   char m_FMQPath[80];    // Ϊ���ӿڵ���Ŀ¼·���������½������FMQ�Խ������ݽ���   
   int m_Status;   // ��ǰ״̬: -1:��ͣ��0:��û��������1:���������У�2: ��Զ����ӳɹ������ڹ�����

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
