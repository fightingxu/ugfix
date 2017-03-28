#include <string.h>
#include "MsgDataList.h"

//////////////////////////////////////////////////////////////////////
// CMsgData Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgData::CMsgData()
{
   msglen = 0;
   msgbuf=NULL;
}

CMsgData::CMsgData(int length,const char *msg)
{
   msglen = length;
   msgbuf=new char[length+1];
   memcpy(msgbuf,msg,length);
   msgbuf[length]='\0';
}

CMsgData::CMsgData(const CMsgData &msgdata)
{
   msglen = msgdata.msglen;
   msgbuf=new char[msglen+1];
   memcpy(msgbuf,msgdata.msgbuf,msglen);
   msgbuf[msglen]='\0';
}


CMsgData::~CMsgData()
{
   if (msgbuf!=NULL)
      delete []msgbuf;
}

