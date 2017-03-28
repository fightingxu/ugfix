// OutFMQ.h: interface for the COutFMQ class.
// ר����FMQ�����з�����Ϣ����
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

   // ������: Read
   // ���  : ������ 2011-10-24 20:26:02
   // ����  : ���Ѿ��򿪵ı�KSFMQ�У��ӵ�һ����ʼ���¶�ȡ��д�����Ϣ
   // ����  : int <0:��ȡʧ�ܣ��ο�KSFMQ�еĴ��󷵻���, ����KSFMQ_ERROR_IO_TIMEOUT��ʾ��ָ������Ϣ;
   // ����  : int msgno [IN]: ��1��ʼ��ָ����ȡ����Ϣ���
   // ����  : char *msgbuf [OUT]: [OUT]: ��Ϣ��ȡ��Ż�����
   // ����  : unsigned int msgsize[IN]: msgBuf���泤��
   // ����  : char *flag [OUT]: ���ֽڷ��ظ���Ϣ�Ƿ񱻶�ȡ��, ' '��ʾδ��Recv��ȡ����'A'��ʾ�Ѿ���Recv��ȡ�� 
	int Read(int msgno, char *msgbuf, unsigned int msgsize, char *flag);

   // ������: Reset
   // ���  : ������ 2011-10-24 20:53:50
   // ����  : ���ñ�KSFMQ
   // ����  : int  0: �ɹ�������<0: ʧ��
   // ����  : const char *path
   // ����  : const char *name
	int Reset(const char *path, const char *name);

   // ������: Open
   // ���  : ������ 2011-10-24 20:55:14
   // ����  : �Է��ͷ�ʽ��ָ����KSFMQ����
   // ����  : int ����0:�ɹ�; ����<0: KSFMQ_ERROR_QUEUE_NOT_FOUND ����ʧ��
   // ����  : const char *path [IN]: KSFMQ������·��
   // ����  : const char *name [IN]: Ҫ�򿪵�KSFMQ�Ķ�����
	int Open(const char *path, const char *name);

   // ������: Close
   // ���  : ������ 2011-10-24 21:17:22
   // ����  : �ر��Ѿ��򿪵�KSFMQ����
   // ����  : void 
	void Close();

   COutFMQ();
	virtual ~COutFMQ();

};

#endif // !defined(AFX_OUTFMQ_H__082E73BE_D1F3_47EE_B9AF_EB52A557AA81__INCLUDED_)
