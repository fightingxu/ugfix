#include "stdafx.h"
#include "xpub.h"
#include "UDLInterface.h"
#include "fixbase.h"
#include "ugate.h"
#include "UGFMQ.h"

CUGFMQ g_UGFMQ;
// ������: UDLInitialize
// ���  : ������ 2011-8-17 14:42:01
// ����  : ��ʼ��UDLģ�飬������Ҫ���������������Ϣ
//       �ڲ�������������������Ϣ
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLInitialize()
{
   //UG_SetOutMode(1); // ���õ���UG_GetOutMsg����
   return(g_UGFMQ.Initialize());
}

// ������: UDLGetStatus
// ���  : ������ 2011-8-21 10:15:51
// ����  : ���UDLģ���ڲ�״̬�����ڲ��쳣���򷵻�<0
//         �������ڲ�����ͨ������ڲ����������ٷ�����״̬��
//         ����ͨ�������������ʱ����UDL�ڲ���״̬��
//         ���������ٻ���һ���쳣��UGate�ᱻǿ���˳� (��Ҫ��������)
// ����  : int <0 : UDL�쳣�������������������ú��ָܻ���>=0:״̬���سɹ�����������
// ����  : char *statusmsg [OUT]: �����¸�ʽ���ظ���Partner��״̬��
//             <PartnerID1>:<status>:<load>:<errmsg>|...|<PartnerID2>:<status>:<load>:<errmsg>
//             status: 0 - û��������1 - �Ѿ���������
//             load: ����ֵ������û�б������OUT��Ϣ����
// ����  : unsigned int smsize [IN]: statusmsg�Ļ����ֽ���(��Ž�4000���ֽ�) 
int UDLGetStatus(char *statusmsg,unsigned int smsize)
{
   return(g_UGFMQ.GetStatus(statusmsg,smsize));
}

// ������: UDLExit
// ���  : ������ 2011-8-18 21:03:38
// ����  : UGateҪ��UDL�˳�
// ����  : int <0: ��ʾ��ʼ��ʧ�ܣ����򣬱�ʾ�ɹ�
int UDLExit()
{
   g_UGFMQ.Exit();
   return(0);
}

// ������: UDLOpen
// ���  : ������ 2011-8-19 23:20:46
// ����  : ��ʽ�������Ự(Session)����Է�ϵͳ�Խ�
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLOpen(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   int rtn;
   rtn = g_UGFMQ.Open(sLocalID,sPartnerID,emsg);
   if (rtn<0)
      g_UGFMQ.Close(sLocalID,sPartnerID,emsg);
   return(rtn);
}


// ������: UDLClose
// ���  : ������ 2011-8-19 23:34:35
// ����  : �ر���Է������ӣ�����Close״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLClose(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   g_UGFMQ.Close(sLocalID,sPartnerID,emsg);
   return(0);
}


// ������: UDLEndOfDay
// ���  : ������ 2011-8-19 23:35:58
// ����  : �Ա�������Reset�������֮ǰ����������ݣ�������ر�״̬
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *sPartnerID [IN]: ָ������Session�� PartnerID
// ����  : char *emsg [OUT]: ������ʧ�ܵ�ʱ�򣬷���ʧ����Ϣ
int UDLEndOfDay(const char *sLocalID, const char *sPartnerID,char *emsg)
{
   return(g_UGFMQ.EndOfDay(sLocalID,sPartnerID,emsg));
}

// ������: UDLOnMessageOut
// ���  : ������ 2011-8-18 20:39:40
// ����  : UG�յ�����FSƽ̨��FIX��Ϣ����Ҫͨ��UDL�������͸����ַ�
// ����  : int <0: ʧ�ܣ����򣬳ɹ�
// ����  : const char *fixmsg [IN]: ҵ����� FIX��ʽ��Message (�ο�Э��)
// ����  : char *eMsg [OUT]: ��ʧ�ܵ�ʱ��(��Э����ʧ��)�����ش�����Ϣ(<80�ֽ�)
int UDLOnMessageOut(const char *fixmsg, char *eMsg)
{
   return(g_UGFMQ.OnMessageOut(fixmsg,eMsg));
}

