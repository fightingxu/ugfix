#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "fixbase.h"
#include "ksfix.h"

//////////////////////////////////////////////////////////////////////////
// 利用fixbase库中的FVxxxxxx, 快速创建基础消息:
char g_BaseMsg[MAXFIXDATALENGTH];

int BuildBaseOrderMsg()
{
   int len=0;
   int rtn;
   rtn = FVString2FIXMsg(TAG_MsgType,"D",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;   

   rtn = FVString2FIXMsg(TAG_ClOrdID,"0528-1",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;

   rtn = FVString2FIXMsg(TAG_OrdType,"2",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;

   rtn = FVString2FIXMsg(TAG_Side,"1",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVString2FIXMsg(TAG_HandlInst,"1",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVString2FIXMsg(TAG_Symbol,"600036",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVString2FIXMsg(TAG_Account,"A123456789",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVString2FIXMsg(TAG_ClientID,"12345678",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVString2FIXMsg(TAG_SecurityExchange,"XSHG",g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVQty2FIXMsg(TAG_OrderQty,1200,g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   rtn = FVDouble2FIXMsg(TAG_Price,12.45,g_BaseMsg+len,sizeof(g_BaseMsg)-len);
   if (rtn>0) len += rtn;
   
   return(len);  // 已经构成了基本上交所一笔Order的基础FIX消息（但不是完全符合FIX规范的完整消息）
}

int UpdateOrderMsg(const char *baseorder, const char *clordid, char *neworder)
{
   FIXDATAHANDLE hfix = FIXDataNew();
   if (hfix==NULL)
      return(-1); // 正常环境下，不可能出现的，除非没有了内存空间
   FIXDataSetData(hfix,baseorder,0);
   // 修改TAG11的ClOrdID值
   FIXDataUpdateTag(hfix,-1,TAG_ClOrdID,clordid,strlen(clordid));
   // 导出新的订单消息
   int rtn = FIXDataGetFIXData(hfix,neworder,MAXFIXDATALENGTH);
   FIXDataDelete(hfix);  // 注意要delete这个新生产的FIXDATAHANDLE
   return(rtn);
}


const char *FIXP_IP="127.0.0.1";
const int FIXP_Port=13011;
const char *FIXLocalID="test";
const char *FIXPartnerID="cyh";
const char *FIXVersion="FIX.4.2";
const char *FIXLogPath="FIXLOG";
const char *FIXPATH="FIXDATA";


int main(void)
{
   char fixmsg[MAXFIXDATALENGTH];
   KFLSetLogPath(FIXLogPath);
   KFLSetSession(FIXLocalID,FIXPartnerID,FIXVersion);
   KFLSetHeartBeat(30,5);
   //KFLSetUserPassword(); FIX.4.2标准中是没有username等检验的
   KFLSetFIXStorePath(FIXPATH,NULL); // 不要备份

   int rtn = KFLToOpen(FIXP_IP,FIXP_Port);
   if (rtn>=0)
   {
      char clordid[20];
      printf("FIXLink started...");
      BuildBaseOrderMsg();
      int i=1;
      while (KFLGetStatus()==2)
      {
         int j;
         rtn = KFLGetInMsg(fixmsg,100);
         if (rtn>0)
         {
            printf("\nInMsg:%s\n",fixmsg);
         }
         if (kbhit())
         {
            switch(getch())
            {
            case '?':
               printf("\n? -- List this help\n");
               printf("n,N -- Send New Order\n");
               printf("m,M -- Send Multi - New Order\n");
               printf("E -- Do EOD\n");
               printf("x,X -- To Close, and eXit\n");
               break;
            case 'n':
            case 'N':
               sprintf(clordid,"528-%d",i++);
               rtn = UpdateOrderMsg(g_BaseMsg,clordid,fixmsg);
               printf("Sending:%s\n",fixmsg);
               KFLHaveOutMsg(rtn,fixmsg,0);
               break;
            case 'm':
            case 'M':
               for (j=0;j<100;++j)
               {
                  sprintf(clordid,"528-%d",i++);
                  rtn = UpdateOrderMsg(g_BaseMsg,clordid,fixmsg);
                  //printf("Sending:%s\n",fixmsg);
                  KFLHaveOutMsg(rtn,fixmsg,0);
               }
               printf("Sending:%s\n",fixmsg);
               break;
            case 'E':
               KFLToDoEOD();
               break;
            case 'x':
            case 'X':
               KFLToClose();
               break;
            }
         }
      }
   }
   else
   {
      printf("Fail to Open(%s,%d):%d\n",FIXP_IP,FIXP_Port,rtn);
   }
   return(0);
}
