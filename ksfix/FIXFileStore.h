#ifndef _FILESTORE_H
#define _FILESTORE_H

struct T_RECINDEX
{
   int seqno;
   int pos;
   int length;
};

#define FFSIDXUNITLEN   32  // 10(seqno)+':'+10(offset)+','+10(11+length)
#define FFSDATHEAD      11  // 10(seqno)+':'  +MsgData
struct T_FFSDATA 
{
   FILE *m_fIdx;
   long m_IdxEnd;
   FILE *m_fData;
   long m_DatEnd;
public:
	int Truncate(int seqno);

   // ������: T_FFSDATA::GetIndex
   // ���  : ������ 2012-5-24 15:44:29
   // ����  : ȡָ����ŵ�������������
   /* ����  : int >0: ���سɹ���ȡ�����ݿ鳤�ȣ�<=0: ʧ��
      0 : �����ݿ�洢��Ԫû�������򿪣�
      -1: ���ܶ�ȡ������Index��Ԫ��
      -2: IndexUnit�е�seqno�쳣��
      -3: IndexUnit������λ���쳣��
      -4: IndexUnit�����ݳ���ֵ�쳣��
      -5: ָ�������������Խ�� (0 - GetCount()-1)
      -6: ��λ��������λ��ʧ��
   *****************************************************/
   // ����  : int number [IN]: ָ�������������: 0 -- GetCount()-1
   // ����  : T_RECINDEX *pIdx [OUT]: ������������
   int GetIndex(int number, T_RECINDEX *pIdx);

   // ȡ��FFS�д�ŵ����ݿ����
	int GetCount();
   
   // ������: T_FFSDATA::EndOfDay
   // ���  : ������ 2012-5-24 15:22:42
   // ����  : ����������������ݳ־û�������
   // ����  : bool 
   bool EndOfDay();

   // ������: T_FFSDATA::GetData
   // ���  : ������ 2012-5-24 0:06:52
   // ����  : ���ݵ�ǰ����������ȡָ�������ݿ�
   /* ����  : int >0: ���سɹ���ȡ�����ݿ鳤�ȣ�<=0: ʧ��
      0 : �����ݿ�洢��Ԫû�������򿪣�
      -5: ���ܶ�λ��ָ���������ļ�λ�ã�
      -6: ��ȡ���ݿ�seqno�������ݣ�
      -7: �����е�seqno�����ݿ�seqnoֵ������
      -8: ���������еĳ��ȳ���dsizeֵ
      -9: ��ȡָ�����ȵ����ݿ�ʧ��
   *****************************************************/
   // ����  : T_RECINDEX *pIdx [IN]: �������������IndexUnit��(length�Ѿ��۳���FFSDATHEAD)
   // ����  : char *data [OUT]: ������ݿ�Ļ��棻
   // ����  : int dsize [IN]: data���ݿ�ɻ������󳤶ȣ�
	int GetData(T_RECINDEX *pIdx, char *data, int dsize);

   // ������: T_FFSDATA::AddData
   // ���  : ������ 2012-5-24 0:12:14
   // ����  : �־û�һ�����ݿ鵥Ԫ - DataUnit
   // ����  : int : �������ݴ洢��ʵ�ʳ��ȣ�
   //           0: ���ݿ�洢��Ԫû�������򿪣�
   //          <0: д���쳣��
   // ����  : unsigned int seqno [IN]: ���ݿ�����
   // ����  : int length [IN]: ���ݿ�ĳ���
   // ����  : const char *data [IN]: ��Ŵ洢�����ݿ�
	int AddData(unsigned int seqno, int length, const char *data);

   T_FFSDATA();
   virtual ~T_FFSDATA();
	void close();
};


class CFIXFileStore  
{
public:
   string m_path;
   int m_InSeqNo;
   int m_OutSeqNo;
   time_t m_tmLastEOD;
private:
   FILE *m_fSeqNo;
   
   T_FFSDATA m_In;

   T_FFSDATA m_Out;

public:
	bool SetEODTime(time_t tmEOD);
	bool GetLastSeqNo(int &InSeqNo, int &OutSeqNo);

   // ������: GetData
   // ���  : ������ 2012-5-24 15:58:36
   // ����  : ���ݵ�ǰ����������ȡָ�������ݿ�
   /* ����  : int >0: ���سɹ���ȡ�����ݿ鳤�ȣ�<=0: ʧ��
      0 : �����ݿ�洢��Ԫû�������򿪣�
      -5: ���ܶ�λ��ָ���������ļ�λ�ã�
      -6: ��ȡ���ݿ�seqno�������ݣ�
      -7: �����е�seqno�����ݿ�seqnoֵ������
      -8: ���������еĳ��ȳ���dsizeֵ
      -9: ��ȡָ�����ȵ����ݿ�ʧ��
   *****************************************************/
   // ����  : int in_out [IN]: FAD_IN / FAD_OUT
   // ����  : T_RECINDEX *pIdx [IN]: �������������IndexUnit��(length�Ѿ��۳���FFSDATHEAD)
   // ����  : char *data [OUT]: ������ݿ�Ļ��棻
   // ����  : int dsize [IN]: data���ݿ�ɻ������󳤶ȣ�
	int GetData(int in_out, T_RECINDEX *pIdx, char *data, int dsize);

   // ȡ��ŵ����ݿ����
	int GetCount(int in_out);

   // ������: GetIndex
   // ���  : ������ 2012-5-24 15:53:13
   // ����  : ȡָ����ŵ�������������
   /* ����  : int >0: ���سɹ���ȡ�����ݿ鳤�ȣ�<=0: ʧ��
      0 : �����ݿ�洢��Ԫû�������򿪣�
      -1: ���ܶ�ȡ������Index��Ԫ��
      -2: IndexUnit�е�seqno�쳣��
      -3: IndexUnit������λ���쳣��
      -4: IndexUnit�����ݳ���ֵ�쳣��
      -5: ָ�������������Խ�� (0 - GetCount()-1)
      -6: ��λ��������λ��ʧ��
   *****************************************************/
   // ����  : int in_out [IN]: FAD_IN / FAD_OUT
   // ����  : int number [IN]: ָ�������������: 0 -- GetCount()-1
   // ����  : T_RECINDEX *pIdx [OUT]: ������������
	int GetIndex(int in_out, int number, T_RECINDEX *pIdx);

   // ����  : ����������������ݳ־û�������
	bool EndOfDay();

   // ������: Put
   // ���  : ������ 2012-5-24 15:59:57
   // ����  : �־û�һ�����ݿ鵥Ԫ - DataUnit
   // ����  : int : �������ݴ洢��ʵ�ʳ��ȣ�
   //           0: ���ݿ�洢��Ԫû�������򿪣�
   //          <0: д���쳣��
   // ����  : int in_out [IN]: FAD_IN / FAD_OUT
   // ����  : unsigned int seqno [IN]: ���ݿ�����
   // ����  : const char *fixdata [IN]: ��Ŵ洢�����ݿ�
   // ����  : int fdlen [IN]: ���ݿ�ĳ���
	int Put(int in_out, unsigned int seqno, const char *fixdata, int fdlen);

   bool IsOpened();


   // ������: SetSeqNo
   // ���  : ������ 2012-5-24 16:02:44
   // ����  : ������ţ����־û�
   // ����  : bool 
   // ����  : int InSeqNo=-1 : <0 ����
   // ����  : int OutSeqNo=-1 : <0 ����
	bool SetSeqNo(int InSeqNo=-1, int OutSeqNo=-1);

	bool Open(char *path);
	void Close();
   CFIXFileStore();
   virtual ~CFIXFileStore();   
private:
	bool OpenFDFiles(T_FFSDATA *pfg, const char *idxfile, const char *datfile);
	bool RestoreSeqNo();
	FILE * fdopen(const char *file, const char *mode);
};
#endif