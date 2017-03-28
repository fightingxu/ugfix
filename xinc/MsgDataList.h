/********************************************************************
	created:	2011/08/24
	created:	24:8:2011   22:10
	filename: 	D:\projects\FIXIII\UGate\xinc\MsgDataList.h
	file path:	D:\projects\FIXIII\UGate\xinc
	file base:	MsgDataList
	file ext:	h
	author:		CHENYH
	
	purpose:	
*********************************************************************/

#ifndef MsgDataList_h__
#define MsgDataList_h__
#include <list>
class CMsgData  
{
public:
   int msglen;
   char *msgbuf;
public:
   CMsgData();
   CMsgData(const CMsgData &msgdata);
   CMsgData(int length,const char *msg);
   virtual ~CMsgData();
};

typedef std::list <CMsgData> L_MSGDATA;

//////////////////////////////////////////////////////////////////////////
// ���¹���ר������Ҫ�ָ���Ϣ��UDL����Open��ʱ�򣬽������ݻָ��õ���Ҫ��ȡƽ̨���ݵĹ��ܺ���
// ���������Ƚ��ʺ�UDL�������Ѿ��������Ϣ����:
// ������: UG_GetSSPendingOrders
// ���  : ������ 2011-8-24 22:14:35
// ����  : UG�ӿ��У����ڴ�FSƽ̨��û�û��OrderID(����֪���Ƿ��Ѿ����͸�SellSide)��New Order Request / Order Cancel Request��Ϣ�б�
// ����  : int ���صõ�����Ϣ����
// ����  : const char *SSPartnerid [IN]: ��SellSide��PartnerID
// ����  : L_MSGDATA &msglist [OUT]: �õ���δ������Ϣ
int UG_GetSSPendingOrders(const char *SSPartnerid, L_MSGDATA &msglist);


// ������: UG_GetBSExecRepts
// ���  : ������ 2011-8-24 22:24:36
// ����  : UG�ӿ��У����ڴ�FSƽ̨������б����
// ����  : int ���صõ�����Ϣ����
// ����  : const char *BSPartnerID [IN]: ��BuySide��PartnerID
// ����  : L_MSGDATA &msglist [OUT]: �õ�����Ϣ
int UG_GetBSExecRepts(const char *BSPartnerID, L_MSGDATA &msglist);

// ������Ϊ��Ҫ�ָ�ԭ�ж���״̬��UDL�ӿ�ʹ�õĺ���
// ������: UG_GetSSAllOrders
// ���  : ������ 2011-9-30 23:02:08
// ����  : UG�ӿ��У����ڴ�FSƽ̨����������ڸ�SellSide��NewOrderRequest��OrderCancelRequest��Ϣ��
//       ���Ѿ��д����صģ��������Ϣ�У�����OrderID���򣬼� 37=<OrderID>����
// ����  : int ���صõ�����Ϣ����
// ����  : const char *sSSPartnerID [IN]: ��SellSide��PartnerID
// ����  : L_MSGDATA &msglist [OUT]: ���ص����ڱ�SellSide��SSOrders��Ϣ�б�
int UG_GetSSAllOrders(const char *sSSPartnerID, L_MSGDATA &msglist);

#endif // MsgDataList_h__