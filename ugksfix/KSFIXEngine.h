// KSFIXEngine.h: interface for the CKSFIXEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KSFIXENGINE_H__DB827022_2F10_4782_B987_B698842DC4D7__INCLUDED_)
#define AFX_KSFIXENGINE_H__DB827022_2F10_4782_B987_B698842DC4D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
struct T_SESSION
{
   std::string m_localid;
   std::string m_partnerid;
   
   unsigned int m_outHeartBtInt; // = setup.heartbtInt(30);
   unsigned int m_inHeartBtInt;  // = setup.heartbtInt(30) + setup.heartbtLatency(5);
   
   int m_reconnect_count;  // >0: ���Ӳ��ɹ�֮���������Ӵ�����<=0: ����������
   int m_reconnect_delay;  // ����Ƶ�������ʱ����CM_TCP_CLIENT��Ч��
   int m_connectmode;      // CM_TCP_SERVER or CM_TCP_CLIENT
   int m_opentime;         // HHMM
   int m_closetime;        // HHMM
   int m_eodtime;          // HHMM
   
   std::string m_luser;    // ������Է����͵��û��� 
   std::string m_lpass;    // ������Է����͵Ŀ���
   
   std::string m_puser;    // �Է����û���
   std::string m_ppass;    // �Է��Ŀ���
   
   std::string m_logpath;  // ��־·��
};


class CKSFIXEngine  
{
public:
	CKSFIXEngine();
	virtual ~CKSFIXEngine();

};

#endif // !defined(AFX_KSFIXENGINE_H__DB827022_2F10_4782_B987_B698842DC4D7__INCLUDED_)
