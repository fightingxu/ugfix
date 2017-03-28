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
   
   
   /* ���´����������ֽڶ���ʹ�õ� */
   /* ���´����������ֽڶ���ʹ�õ� */
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
   
#define LBYTEID 0x1023   // ������ͨѶЭ��ʶ����
#define RBYTEID 0x2310   // �����ͨѶЭ��ʶ����

   typedef struct _T_FMQSTATUS
   {
      unsigned short byteid;     // �öԷ�ʶ���ļ�����(д)�������е��ֽ���  -- Ŀǰ�Ȳ����ǲ�ͬ�ֽ��� 2011-10-23 11:24:43
      int            status;     // ��������״̬ -1: ��ͣ��0: δ������1: �������У�2: ��������
      unsigned int   lasttime;   // ����д���ʱ���(time(NULL))���Լ������Ƿ����������У���������ʽ
      unsigned int   partnertm;  // ������ȡ���ĶԷ���ʱ���, ���ı�ԭ�����ֽ��򣬼�ʹ��ͬҲ��Ҫ��
      unsigned int   sormsgs;    // ���͸��Է��Ķ�������Ϣ����(���ϴ�EOD��ʼ)
      unsigned int   soemsgs;     // ���͸��Է���ִ������Ϣ����
      unsigned int   smsgs;      // ���͸��Է��ĳ�������Ӧ������Ϣ
      unsigned int   rormsgs;     // ���յ��Է��Ķ�������Ϣ����(���ϴ�EOD��ʼ)
      unsigned int   roemsgs;     // ���յ��Է���ִ������Ϣ����
      unsigned int   rmsgs;      // ���յ��Է��ĳ�������Ӧ������Ϣ
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
   int m_handle;  // �ļ����
//   bool m_bOut;   // �򿪷�ʽ���Ƿ�Ϊд�뷽ʽ
public:
   T_FMQSTATUS status;  // ״̬��Ϣ

private:
   
public:
	int InStatus();
	int OutStatus();
	int Open(const char *path, const char *sid, bool bCreate);
	CFMQStatusFile();
	virtual ~CFMQStatusFile();
};

#endif // !defined(AFX_FMQSTATUSFILE_H__27661ADE_83CF_4123_9576_4352AD26B937__INCLUDED_)
