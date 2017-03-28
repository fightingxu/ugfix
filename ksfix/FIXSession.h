// FIXSession.h: interface for the CFIXSession class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXSESSION_H__094D5AC4_9FA2_4A8F_91D1_59510B42E61E__INCLUDED_)
#define AFX_FIXSESSION_H__094D5AC4_9FA2_4A8F_91D1_59510B42E61E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "tcp.h"
#include <string>
#include "FIXData.h"
#include "logfile.h"
#include "FIXAppData.h"

// ���ڱ��಻������"����(Client)" �� "����(Server)" ���ַ�ʽ���У���ˣ����ﲻ�������ӵĽ����͵�½���̵Ŀ���
class CFIXSession  
{
public: 
   CFIXAppData m_Persistence;
   CLogFile m_LogFile;
   
   char m_FSMPath[260];
   char m_FSBPath[260];

   //////////////////////////////////////////////////////////////////////////
   // ��Ҫ�ⲿ���õĸ������
   char m_FSName[64];
   bool bNeedSendingTime; // ��Session��FIX��Ϣ���Ƿ���ҪSendingTime

   std::string m_localid;
   std::string m_partnerid;
   std::string m_fixversion;
   
   unsigned int m_outHeartBtInt; // = setup.heartbtInt(30);
   unsigned int m_inHeartBtInt;  // = setup.heartbtInt(30) + setup.heartbtLatency(5);
   
   //////////////////////////////////////////////////////////////////////////
   // Serverģʽ��ʱ�����ⲿ�������ӵ�ʱ�����ã�Client���ڽ�������֮ǰ���ã���ʹ������
   char m_partnerip[64];     // �Զ˵�IP��ַ
   int  m_partnerport;       // �Զ˵Ķ˿ں�

   //////////////////////////////////////////////////////////////////////////
   // �������ⲿ���Լ������ݣ�
   CTcpSocket m_sock;
   CFIXData m_recvFIXData;  // ���յ����������ݰ��󣬴�m_datakeep�н�ȡ����Ϣ���ݣ�ת�浽����

   int  m_state;    // ��FIX���ӵ�״̬����
   enum FIXSTATE 
   {
      FIXST_CLOSE,
      FIXST_CONNECTING,    // ������·�Ѿ�����������û�����LOGN֮ǰ
      FIXST_OPEN           // LOGON��Ϣ������ϣ���ʼ������ʽ��FIX���ݽ���״̬
   };
   
   time_t tmLastRecv; // ���һ���յ��Է���Ϣ��ʱ���
   time_t tmLogon;    // ��ʽ��¼ʱ��
   time_t tmLastSent; // ���һ�η�����Ϣ��ʱ��㣬������������
   
   int incomingSeqNumber;  // ���һ���յ���Ϣ�����
   int outgoingSeqNumber;  // ���һ��������Ϣ�����
   
protected:
   int m_GapFillSeqNo;   // <=0: ͬ��״̬��>0: ����Ҫ���Reset��ָ������ţ��Żָ���ͬ��״̬

   T_REJECTMSG m_rejmsg;

   char m_datakeep[MAXFIXDATALENGTH];  // �����Ѿ����յ�����δ���������ݻ���
   int  m_InMsgLen;  // ��CheckDataKeepΪtrueʱ��Ϊ��ǰ������InMsg����
   int  m_dklen;   // �Ѿ����յ���������ʱ���泤��
   
   unsigned int TestReqID;   // MsgType=1��ʱ���ã�������һ��Test��Ϣ�еģ�����ͬ�������Է��÷��͵���Ϣ�Ѿ�ȫ���������յ���
   time_t tmTestReq;        // 0 - ��û�з���TestReq���������յ����˶Է���Ӧ��HeartBeat���� ���򣬱�ʾ�Ѿ�������TestReq������û���յ���Ӧ��HeartBeat��
   
   int  logon;   // Logon��Ϣ����״̬ : 0 û�з��͹���1 �Ѿ�������Logon��Ϣ��2 �Ѿ��յ�Logon����Ҳ�Ѿ�������Logout�����ұ����ӱ��ر��� (ע������EOD����������Ҫ��logon��λ)
   int  logout;   // Logout��Ϣ����״̬ : 0 û�з��͹���1 �Ѿ�������Logout��Ϣ��2 �Ѿ��յ�Logout����Ҳ�Ѿ�������Logout�����ұ����ӱ��ر���
public:
   int GetStatus();
   // ���ñ�Session�������������
   void SetHeartBtInt(int hbt, int hbtlatency);

protected:
	int OnLogout();
	int DoEndOfDay();

	bool SetFIXVersion(const char *fixversion);
	bool IsLinkOK();
	void SetSendingTime(bool bMandatory);
	void ToClose();

	int OnSequenceReset();

   // ip_port - <PartnerIP>:<PartnerPort>
	bool SetPartnerConnect(const char *ip_port);

   // sessionid: <LocalID>-<PartnerID>
	bool SetSessionID(const char *sessionid);
   
   // ������: InitOutFIXData
   // ���  : ������ 2011-4-22 22:54:36
   // ����  : �� pFIXData��ͷ����ʼ��
   // ����  : void 
   // ����  : CFIXData *pFIXData [OUT]: �����õ�CFIXData
   // ����  : const char *MsgType [IN]: MsgType��ֵ
   void InitOutFIXData(CFIXData *pFIXData, const char *MsgType);
   
   // ������: SendFIXMsg
   // ���  : ������ 2011-4-22 22:48:14
   // ����  : ��pfixdata�Ա�׼��FIX�淶��ʽ���͸��Է�
   // ����  : int <0: ���ʹ���>0: �ɹ������ط���ȥ����Ϣ��� outgoingMsgSeqNum
   // ����  : CFIXData *pfixdata [IN]: �Ѿ����úõ�fix��Ϣ����
   int SendFIXMsg(CFIXData *pfixdata);

	CFIXSession();
	virtual ~CFIXSession();

   virtual void OnUndefinedInMsgType();

   int ToCheckTest();

	int SendResendRequest(int beginSeqNo, int endSeqNo=0);
	int CheckInSequenceNumber();
   // Function name: CFIXSession::OpenFIXStorePath
   // Author       : CHENYH 2012/5/26 14:13:13
   // Description  : ��FIX״̬�־û������ָ�InSeq��OutSeq����׼����ʽ���ݽ���
   //  !!! ������Ҫ����ʽȷ��Ϊ���趨��Session֮�󣬲ſɵ��á�
   //  CM_TCP_SERVER: ���ڽ��ܵ��Է����ӣ����õ�Logon��Ϣ��ȷ�ϱ����ӵ�Session֮��׼������Logon��Ϣ֮ǰ���ã�
   //  CM_TCP_CLIENT: �����趨��Session֮��׼������Logon��Ϣ֮ǰ���á�
   // Return type  : bool �����Ƿ�򿪳ɹ�
   // Argument : const char *mpath [IN]: ���洢Ŀ¼·��������Ϊ�У����ҿ��Դ�����·�������򣬽�����ʧ��
   // Argument : const char *bkpath [OUT]: ���洢Ŀ¼·��������ΪNULL��""����ʾ�ޱ��洢·��
   bool OpenFIXStorePath(const char *mpath, const char *bkpath=NULL);
   
	int ResendFIXMsg(char *fixdata, int fdlen);
	bool ValidRecvSessionID();
   // ���յ�Session Level��ResendRequest�ı�׼����
	int OnResendRequest();
   // ����SeqReset�ı�׼FIX Session Level����Ϣ
	int SendSeqReset(int tag34, int NewSeqNum, bool Gap_Fill=true, bool dup=false);
	int SendTestReq();
	int SendLogout(const char *logouttxt=NULL);
	int OnHeartBeat();
	int SendHeartBt(const char *TestReqID,const char *tag10031=NULL);
	int OnTestReq(const char *tag10031=NULL);
	int SendLogon(const char *UserName=NULL, const char *Password=NULL, bool bResetSeqNum=false);
	int SendRejectMsg(T_REJECTMSG *pRejMsg);


   // ������: CheckRecvFIXData
   // ���  : ������ 2011-4-22 22:56:17
   // ����  : ����������Ƿ���������FIX��Ϣ����
   // ����  : bool true - m_recFIXData�м�Ϊ�ո��յ���fix��Ϣ���ݣ�false - ��û���յ�������fix��Ϣ
   // ����  : int timeout [IN]: �������ݽ��յĵȴ�ʱ�� (ms)
	bool CheckRecvFIXData(int timeout);

   // ������: SendFIXMsg
   // ���  : ������ 2011-4-22 22:51:06
   // ����  : ���淶����FIX��Ϣpmsg���͸��Է�
   // ����  : int <0: ���ʹ���>0: �ɹ�
   // ����  : const char *pmsg [IN]: fix��Ϣ�ַ���
   // ����  : int msglen [IN]: fix��Ϣpmsg�ĳ��ȣ����ֽڼ�
	int SendFIXMsg(const char *pmsg, int msglen);

private:
   bool ValidFIXData(const char *fixmsg,int fmlen);
   bool CheckDataKeep();
   
};

char *BuildTag52(char *tag52); // ȡ��ǰUTCDateTime

#endif // !defined(AFX_FIXSESSION_H__094D5AC4_9FA2_4A8F_91D1_59510B42E61E__INCLUDED_)
