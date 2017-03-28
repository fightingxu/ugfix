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
// 以下功能专用于需要恢复消息的UDL，在Open的时候，进行数据恢复用的需要获取平台数据的功能函数
// 下面两个比较适合UDL那里有已经处理的消息基础:
// 函数名: UG_GetSSPendingOrders
// 编程  : 陈永华 2011-8-24 22:14:35
// 描述  : UG接口中，用于从FS平台获得还没有OrderID(即不知道是否已经发送给SellSide)的New Order Request / Order Cancel Request消息列表
// 返回  : int 返回得到的消息个数
// 参数  : const char *SSPartnerid [IN]: 即SellSide的PartnerID
// 参数  : L_MSGDATA &msglist [OUT]: 得到的未决的消息
int UG_GetSSPendingOrders(const char *SSPartnerid, L_MSGDATA &msglist);


// 函数名: UG_GetBSExecRepts
// 编程  : 陈永华 2011-8-24 22:24:36
// 描述  : UG接口中，用于从FS平台获得所有保存的
// 返回  : int 返回得到的消息个数
// 参数  : const char *BSPartnerID [IN]: 即BuySide的PartnerID
// 参数  : L_MSGDATA &msglist [OUT]: 得到的消息
int UG_GetBSExecRepts(const char *BSPartnerID, L_MSGDATA &msglist);

// 下面则为需要恢复原有订单状态的UDL接口使用的函数
// 函数名: UG_GetSSAllOrders
// 编程  : 陈永华 2011-9-30 23:02:08
// 描述  : UG接口中，用于从FS平台获得所有属于该SellSide的NewOrderRequest和OrderCancelRequest消息，
//       若已经有处理返回的，则会在消息中，带有OrderID的域，即 37=<OrderID>的域。
// 返回  : int 返回得到的消息个数
// 参数  : const char *sSSPartnerID [IN]: 即SellSide的PartnerID
// 参数  : L_MSGDATA &msglist [OUT]: 返回的属于本SellSide的SSOrders消息列表
int UG_GetSSAllOrders(const char *sSSPartnerID, L_MSGDATA &msglist);

#endif // MsgDataList_h__