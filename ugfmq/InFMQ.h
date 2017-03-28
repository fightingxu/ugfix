// InFMQ.h: interface for the CInFMQ class.
// ר�Ŵ�FMQ�����ж�ȡ��Ϣ����
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

   // ������: Recv
   // ���  : ������ 2011-10-24 20:01:59
   // ����  : ���Ѿ��򿪵ı�KSFMQ�У���ȡδ��ȡ������Ϣ
   // ����  : int <0:��ȡʧ�ܣ��ο�KSFMQ�еĴ��󷵻���, ����KSFMQ_ERROR_IO_TIMEOUT����ָ��ʱ����û�ж�������Ϣ;
   //            >0: �ɹ���ȡδ�����չ�����Ϣ;
   // ����  : int msTimeout[IN]: [IN]: �Ժ���Ƶĵȴ����ճ�ʱʱ�䣬<=0: ��������
   // ����  : char *msgBuf[OUT]: ��Ϣ��ȡ��Ż�����
   // ����  : int msgsize[IN]: msgBuf���泤��
	int Recv(int msTimeout, char *msgBuf, int msgsize);

   // ������: Read
   // ���  : ������ 2011-10-24 20:26:02
   // ����  : ���Ѿ��򿪵ı�KSFMQ�У��ӵ�һ����ʼ���¶�ȡ��д�����Ϣ
   // ����  : int <0:��ȡʧ�ܣ��ο�KSFMQ�еĴ��󷵻���, ����KSFMQ_ERROR_IO_TIMEOUT��ʾ��ָ������Ϣ;
   // ����  : int msgno [IN]: ��1��ʼ��ָ����ȡ����Ϣ���
   // ����  : char *msgbuf [OUT]: [OUT]: ��Ϣ��ȡ��Ż�����
   // ����  : unsigned int msgsize[IN]: msgBuf���泤��
   // ����  : char *flag [OUT]: ���ֽڷ��ظ���Ϣ�Ƿ񱻶�ȡ��, ' '��ʾδ��Recv��ȡ����'A'��ʾ�Ѿ���Recv��ȡ�� 
	int Read(int msgno, char *msgbuf, unsigned int msgsize, char *flag);


   // ������: IsReset
   // ���  : ������ 2011-10-24 20:51:49
   // ����  : ��KSFMQ�Ƿ������ˣ�������ˣ�����End Of Day����
   // ����  : bool �����Ƿ����ã�true: ���������ˣ�false: û�б�����
	bool IsReset();

   // ������: Close
   // ���  : ������ 2011-10-24 21:17:22
   // ����  : �ر��Ѿ��򿪵�KSFMQ����
   // ����  : void 
	void Close();

   // ������: Open
   // ���  : ������ 2011-10-24 20:55:14
   // ����  : �Խ��շ�ʽ��ָ����KSFMQ����
   // ����  : int ����0:�ɹ�; ����<0: KSFMQ_ERROR_QUEUE_NOT_FOUND ����ʧ��
   // ����  : const char *path [IN]: KSFMQ������·��
   // ����  : const char *name [IN]: Ҫ�򿪵�KSFMQ�Ķ�����
	int Open(const char *path, const char *name);

	CInFMQ();
	virtual ~CInFMQ();

};

#endif // !defined(AFX_INFMQ_H__DA18AD67_D037_4203_938A_1D974B00E9C7__INCLUDED_)
