// FIXAppData.h: interface for the CFIXAppData class.
// ���ڳ־û�FIX
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXAPPDATA_H__51DFF822_CE03_49A4_ADF3_84D742CF7C97__INCLUDED_)
#define AFX_FIXAPPDATA_H__51DFF822_CE03_49A4_ADF3_84D742CF7C97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FIXFileStore.h"

#define FAD_IN    0
#define FAD_OUT   1

class CFIXAppData  
{
private:  
   CFIXFileStore m_Main;   // ���־û�
   CFIXFileStore m_Back;   // ���־û�

public:
	time_t GetLastEODTime();
	bool SetEODTime(time_t tmEOD);
	bool GetLastSeqNo(int &InSeqNo, int &OutSeqNo);
	void Close();

   // ������: GetData
   // ���  : ������ 2012-5-24 16:11:35
   // ����  : ȡָ����ŵĿ�����
   /* ����  : int >0: ���سɹ���ȡ�����ݿ鳤�ȣ�<=0: ʧ��
      0 : �����ݿ�洢��Ԫû�������򿪣�
      -1: ���ܶ�ȡ������Index��Ԫ��
      -2: IndexUnit�е�seqno�쳣��
      -3: IndexUnit������λ���쳣��
      -4: IndexUnit�����ݳ���ֵ�쳣��
      -5: ָ�������������Խ�� (0 - GetCount()-1)
      -6: ��λ��������λ��ʧ��
      -7: ���ܶ�λ��ָ���������ļ�λ�ã�
      -8: ��ȡ���ݿ�seqno�������ݣ�
      -9: �����е�seqno�����ݿ�seqnoֵ������
      -10: ���������еĳ��ȳ���dsizeֵ
      -11: ��ȡָ�����ȵ����ݿ�ʧ��
   *****************************************************/
   // ����  : int in_out [IN]: FAD_IN / FAD_OUT
   // ����  : int number [IN]: ָ�������������: 0 -- GetCount()-1
   // ����  : int *seqno [OUT]: ���������SeqNo
   // ����  : char *data [OUT]: ������ݿ�Ļ��棻
   // ����  : int dsize [IN]: data���ݿ�ɻ������󳤶ȣ�
	int GetData(int in_out, int number, int *seqno, char *data, int dsize);


   // ȡ���־û����ݿ���
	int GetCount(int in_out);

   // ������: SetSeqNo
   // ���  : ������ 2012-5-24 16:02:44
   // ����  : ������ţ����־û�
   // ����  : bool 
   // ����  : int InSeqNo=-1 : <0 ����
   // ����  : int OutSeqNo=-1 : <0 ����
	bool SetSeqNo(int InSeqNo=-1, int OutSeqNo=-1);

   // ������: CFIXAppData::EndOfDay
   // ���  : ������ 2012-5-24 15:28:55
   // ����  : ���־û���������գ����ҽ������0
   // ����  : bool 
   bool EndOfDay();

   // Function name: CFIXAppData::Put
   // Author       : CHENYH 2012/5/22 16:50:16
   // Description  : ���µ�Ӧ����Ϣ�����г־û�
   // ����  : int : �������ݴ洢��ʵ�ʳ��ȣ�
   //           0: ���ݿ�洢��Ԫû�������򿪣�
   //          <0: д���쳣��
   // ����  : int in_out [IN]: FAD_IN / FAD_OUT
   // Argument : unsigned int seqno [IN]: ��Ϣ���seqno - key
   // Argument : const char *fixdata [IN]: Ӧ����Ϣ��������
   // Argument : int fdlen [IN]: fixdata����Ϣ���ֽ���
   int Put(int in_out, unsigned int seqno, const char *fixdata, int fdlen);

	bool Init(char *path, char *bkpath=NULL);

	CFIXAppData();
	virtual ~CFIXAppData();

private:
};

#endif // !defined(AFX_FIXAPPDATA_H__51DFF822_CE03_49A4_ADF3_84D742CF7C97__INCLUDED_)
