/********************************************************************
	created:	2005/06/27
	created:	27:6:2005   19:25
	filename: 	D:\proj\ksbass\ksbu\bupub.cpp
	file path:	D:\proj\ksbass\ksbu
	file base:	bupub
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 �����г��˿��Թ�ҵ��ģ�飨C/C++�����ԣ����õ�������BCC����
   �Ŀ��ƺ�������SetCol��PutRow�Ⱥ�����
*********************************************************************/

#include "stdafx.h"
#include "mypub.h"
#include "cxpack.h"
#include "svrlink.h"
#include "logfile.h"
#include "bdefine.h"

struct T_TICKLOG
{
   TICKUS tickus;
   char file[256];
   int  line;
};

class CBUTL
{
public:
   FILE *fp;
   int m_maxtls;
   int m_itl;
   T_TICKLOG *pLog;
public:
	int Dump();
	int Push(const char *file, int lineno,const char *desc);
	int Begin();
	int Set(int tlnum=0);
   CBUTL() { fp=NULL; m_maxtls=0; m_itl=0; pLog=NULL; }
   virtual ~CBUTL() { Close(); }
private:
	void Close();
};

CSvrLink g_SvrLink;  // ��ҵ��������ĵ�����
extern CLogFile *g_pLogFile;

CBUTL g_BUTL;


// ����BUTL������¼����<=0: �رգ�>0: ������¼
int BUTLSet(int tlnum)
{
   return(g_BUTL.Set(tlnum));
}

// ��ʼ����ʱ�����¼
int BUTLBegin()
{
   return(g_BUTL.Begin());
}

// ʱ�����¼
int BUTLPush(const char *file, int lineno,const char *desc)
{
   return(g_BUTL.Push(file,lineno,desc));
}

// ��ʱ�����¼dump���ļ���
int BUTLDump()
{
   return(g_BUTL.Dump());
}


/* ****** Updated by CHENYH at 2004-3-10 22:17:31 ****** 
// ������: SetCol
// ���  : ������ 2004-2-8 23:26:38
// ����  : ����CPACK����λͼ�����Ѿ���PutRow��������ݼ�¼�����ϴ����ݴ�����͸�ԭ�����
// ����  : int 0:�ɹ�����BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : void *handle �� ��ʱ�Ͷ�Ӧ�� TRUSERID *, �ڱ�ϵͳû�����壬��Ϊ���̵߳�Ե��
// ����  : ...  �� F_XXXXX ���������ֶ��б���END_FIELD��ʾ��������handle��ΪEND_FIELD�������λͼ��������λͼ
*/
int SetCol(TRUSERID *handle,...)
{
	va_list ap;
	int arg;
   ST_PACKHEAD head;
   memset(&head,0,sizeof(head));
	va_start(ap, handle);

/* ****** Updated by CHENYH at 2005-1-25 14:27:25 ****** 
	while ((arg = va_arg(ap, int)) != 0)
*/
   while ((arg=va_arg(ap,int))>=0)
//////////////////////////////////////////////////////////////////////////
	{
		SetParmBit( &head, arg);
	}
	va_end(ap);
   return(g_SvrLink.SetCol(handle,head.ParmBits));
}



/* ****** Updated by CHENYH at 2005-6-27 19:45:04 ****** 
��������Ϊ��PutRow�����Բ�����Ҫ�ˡ�
// ������: PutRowData
// ���  : ������ 2004-2-8 23:30:07
// ����  : �������CPACK����������һ��ST_PACK�����¼��ʵ�ʶ�֮ǰ��SetCol������ֶ���Ч��û�ж������Ч
// ����  : int 0:�ɹ�����BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : ST_PACK *pdata  �� ���ӵ�ST_PACK�������
int PutRowData(ST_PACK *pdata)
{
   return(g_SvrLink.PutRowData(pdata));
}
*******************************************************/

// ������: AnswerData
// ���  : ������ 2004-2-8 23:32:42
// ����  : ��ruserid�Ŀͻ��ˣ�������SetCol��PutRowData���õ�Ӧ�𷵻ص�����
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,0));
}


// ������: AnswerDataPart
// ���  : ������ 2004-2-12 12:12:09
// ����  : ��AnswerData���ƣ���������֪ͨ�ͻ��ˣ����и�������ݷ���
//         �����ڽ��д��������ݷ��أ�������������ͬ����Ϊ�˲��ÿͻ��˳�ʱ��ȴ�
//         �ȷ��Ͳ������ݡ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *ruserid
// ����  : int retcode
// ����  : char *szmsg
int AnswerDataPart(TRUSERID *ruserid,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerData(ruserid,retcode,szmsg,1));
}

// ������: AnswerDataEx
// ���  : ������ 2004-2-8 23:37:00
// ����  : ��ruserid�Ŀͻ��ˣ�����apack��pArrays���Ӧ�𷵻ص�����
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : ST_CPACK *apack  Ӧ������ͷ���ױ���
// ����  : ST_PACK *pArrays �������ݱ��壬��apack->head.RetCount<=1ʱ����Ч ������дΪNULL
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg)
{
   return(g_SvrLink.AnswerDataEx(ruserid,apack,pArrays,retcode,szmsg));
}

// ������: PushData
// ���  : ������ 2004-2-8 23:43:01
// ����  : ��һ����Ϊ����ʽע���Ŀ��㣬��������
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int sourceno  ��������ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    �������ݵ�Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ը�Ŀ���Ự���κ�
// ����  : ST_CPACK *ppack  ���͵����ݰ���ppack->head.RetCount<=1�����������ݲ��ܳ���1�������¼
// ����  : char pushmode  ����ģʽ�������������PM_xxx
// ����  : int acktime   ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime)
{
   return(g_SvrLink.PushData(sourceno,destno,funcno,batchno,ppack,pushmode,acktime));
}



// ������: ExtCall
// ���  : ������ 2004-3-6 17:47:14
// ����  : ������һ������㷢������Ҫ��Է�����Ӧ�𷵻أ������ܳ������ڲ�ͬϵͳ֮��ĶԽӣ���Ҫ��������Χϵͳ����
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����
// ����  : int sourceno  ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ŀ���Ự���κ� (���ȷ����Ը�Ŀ��㣬����������������ģʽ�������ֱ����дΪ0)
// ����  : int acktime   ���������Чʱ�䣬�����
// ����  : ST_CPACK *rpack  ���������
// ����  : ST_CPACK *apack  Ŀ���Ӧ������ݷ���
// ����  : ST_PACK *pArrays Ӧ�����ݺ���������
int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays)
{
   return(g_SvrLink.ExtCall(sourceno,destno,funcno,batchno,acktime,rpack,apack,pArrays));
}

int ExtTransfer(unsigned short destno, unsigned short funcno, ST_CPACK *rpack, ST_PACK *pArrays)
{
   return(g_SvrLink.ExtTransfer(destno,funcno,rpack,pArrays));
}

// ������: GetRequestHead
// ���  : �� 2008-3-6 09:38:11
// ����  : ��ԭʼ�������ͷ���Ƶ�phead
// ����  : void 
// ����  : ST_PACKHEAD *phead[OUT]: ��Ÿ��Ƶİ�ͷ
void GetRequestHead(ST_PACKHEAD *phead)
{
   g_SvrLink.GetRequestHead(phead);
}

// ������: GetAnswerHead
// ���  : �� 2008-3-6 09:43:29
// ����  : ����ǰӦ���ͷ���Ƶ�phead
// ����  : void 
// ����  : ST_PACKHEAD *phead[OUT]: ��Ÿ��Ƶİ�ͷ
void GetAnswerHead(ST_PACKHEAD *phead)
{
   g_SvrLink.GetAnswerHead(phead);
}

// ������: SetAnswerHead
// ���  : �� 2008-3-13 16:07:29
// ����  : ��phead���Ƶ�Ӧ���
// ����  : void
// ����  : TRUSERID *handle[IN]: ��ʱ��ʹ�ã�Ϊ�Ժ���չ���� 
// ����  : ST_PACKHEAD *phead[OUT]: ��Ÿ��Ƶİ�ͷ
void SetAnswerHead(TRUSERID *handle, ST_PACKHEAD *phead)
{
   g_SvrLink.SetAnswerHead(handle, phead);
}



// ������: ExtCallNext
// ���  : ������ 2004-3-8 17:31:47
// ����  : �ڵ���ExtCall֮�󣬷��ֶԷ��������ݻ�û��ȡ���������ñ����ܻ�ȡ��������
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����-3:�Ѿ�ȡ���˺�������
// ����  : int acktime
// ����  : ST_CPACK *apack
// ����  : ST_PACK *pArrays
int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays)
{
   return(g_SvrLink.ExtCallNext(acktime,apack,pArrays));
}


// ������: PushDataEx
// ���  : ������ 2004-2-9 0:10:53
// ����  : ��pushdests�������Ϊ����ʽע��Ŀ�����������
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TPUSHDEST *pushdests �����Ŀ����б�
// ����  : int pdcount  Ŀ���ĸ���
// ����  : ST_CPACK *ppack ���͵Ĳ�����һ����¼�����ݰ�
// ����  : char pushmode ����ģʽ�������������PM_xxx
// ����  : int acktime  ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime)
{
   return(g_SvrLink.PushDataEx(pushdests,pdcount,ppack,pushmode,acktime));
}



// ������: PutRow
// ���  : ������ 2004-2-20 10:03:04
// ����  : һ�������PutRowData �� AnswerData, ���ǲ������Ϸ��� ��Ϊ������а汾���ݣ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : TRUSERID *handle
// ����  : ST_PACK *pdata
// ����  : int *pRetCode
// ����  : char *rtnMsg
int PutRow(TRUSERID *handle,ST_PACK *pdata,int *pRetCode,char *rtnMsg)
{
   return(g_SvrLink.PutRow(handle,pdata,*pRetCode,rtnMsg));
}



// ������: CT_ERR_DEAL
// ���  : ������ 2004-2-22 16:39:51
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ��Ϊ���뼯�н��׼��ݣ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : char *msg
// ����  : int retcode
int CT_ERR_DEAL(char *msg,int retcode)
{
   return(g_SvrLink.Err_Deal(msg,retcode));
}


// ������: Error_Deal
// ���  : ������ 2004-2-22 16:43:34
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ ������ϵͳʹ�ñ��������ԭ����ERR_DEAL
//         �ϲ���ԭ����Ҫ��sprintf����omsg
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int retcode
// ����  : char *omsg  OUT
// ����  : char *pFormat IN
// ����  : ... IN
int Error_Deal(int retcode,char *omsg,char *pFormat,...)
{
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(CT_ERR_DEAL(omsg,retcode));
}


// ������: SQLDebugLog
// ���  : ������ 2004-3-4 17:45:16
// ����  : ר��Ϊ��SQCʹ�ã���C��ʹ�õģ���¼��Ϣ��LOG��־��
// ����  : void 
// ����  : int errorcode
// ����  : char *pFormat
// ����  : ...
void SQLDebugLog(int errorcode,char *pFormat,...)
{
   char omsg[8192];
   va_list pArg;
   if (g_pLogFile==NULL)
      return;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   g_pLogFile->WriteLogEx(errorcode,"%s",omsg);   
}

void TextLogOut(int errorcode, char *textlog)
{
   g_pLogFile->WriteLogEx(errorcode,"%s",textlog);
}


// ������: CheckProcCancel
// ���  : ������ 2004-3-10 15:44:20
// ����  : ����Ƿ񱾴�������ǰ̨�Ƿ�Ҫ��ֹͣ��ע�⣺�������Ҫ����������Ƿ��и�ֹͣ������ᵼ�µ�1���룬��ʹ�ô���Ч�ʽ���
// ����  : int 1:��ʾǰ̨��Ҫ��ֹͣ�����0:û��
int CheckProcCancel()
{
   if (g_SvrLink.CheckProcCancel())
      return(1);
   else 
      return(0);
}

// ������: SetAnswerMode
// ���  : ������ 2004-3-10 18:48:18
// ����  : ����Ӧ��ģʽ����AM_xxxx�Ķ���
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : char iAnswerMode ��AM_xxxx�Ķ���
int SetAnswerMode(char iAnswerMode)
{
   return(g_SvrLink.SetAnswerMode(iAnswerMode));
}


// ������: BCCMsgLogOut
// ���  : ������ 2004-3-10 19:31:25
// ����  : ��BCC���������BU���ı���־��Ϣ
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int logid ������־��ID��
// ����  : char *pFormat ���ı���־�ĸ�ʽ����
// ����  : ... ����pFormat������������
int BCCMsgLogOut(int logid,char *pFormat,...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(g_SvrLink.BCCLogOut(LT_MSG,logid,strlen(omsg),omsg));
}


// ������: ResetNormalCPack
// ���  : ������ 2004-3-11 20:30:59
// ����  : ���ݱ�ҵ�������������һ��CPACK��ͷ��λͼ�����ݶ��������
// ����  : void 
// ����  : ST_CPACK *pack
void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount)
{
   g_SvrLink.ResetNormalCPack(pack,nextflag,recCount);
}


// ������: SetMaxRow
// ���  : ������ 2004-3-22 11:41:26
// ����  : ���ñ��ι��ܴ���ʱ��ÿ��Ӧ������ص�����¼����ֻ�Ա��ι��ܴ�����Ч
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int maxrows
int SetMaxRow(int maxrows)
{
   return(g_SvrLink.SetMaxRow(maxrows));
}


// ������: SetBUError
// ���  : ������ 2004-3-22 11:42:37
// ����  : ���ñ�BU������Ϣ�������ṩ��ǰ�˳���
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : int errcode
// ����  : char *pFormat
// ����  : ...
int SetBUError(int errcode,char *pFormat,...)
{
   char omsg[1024];
   va_list pArg;
   va_start(pArg,pFormat);
   vsprintf(omsg,pFormat,pArg);
   va_end(pArg);
   return(g_SvrLink.SetBUError(errcode,omsg));   
}


// ������: SetAnswerTimeout
// ���  : ������ 2004-3-22 12:49:02
// ����  : �趨��ҵ��ÿ��Ӧ����ĳ�ʱʱ�䣬�Ժ���ƣ���������������ʱ������Ĵ���
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : unsigned int atimeout  ָ���ĳ�ʱʱ�䣨�Ժ���ƣ�
int SetAnswerTimeout(unsigned int atimeout)
{
   return(g_SvrLink.SetAnswerTimeout(atimeout));
}




// ������: ResetAnswerData
// ���  : ������ 2004-3-24 22:16:17
// ����  : ��������Ѿ��ύ��Ӧ�����ݣ�����������ִ��һ������������Ϊ����������Retry
// ����  : int 
int ResetAnswerData()
{
   return(g_SvrLink.ResetAnswerData());
}

// ������: GetDRTPSvrRegStatus
// ���  : ������ 2010-1-15 17:11:16
// ����  : ��ȡͨѶƽ̨��ָ�������ܺ�ע���״̬ (ֻ�ܲ�DRTP4����Ϊ�°汾)
// ����  : int 0 �����ڣ�1���ش��ڣ�2 �����ط����ڣ�3���غ������ط�������; -1δ֪; -1001��-1002: BCC/BU֮�����ݽ����쳣
// ����  : int sourceno [IN]: ͨ��DRTP�ı�ţ���ʹ��TRUSERID::SourceNo����0
// ����  : int svrfuncno [IN]: ָ����ѯ��ע������ܺ�
int GetDRTPSvrRegStatus(int sourceno, int svrfuncno)
{
   return(g_SvrLink.GetSvrFuncRegister(sourceno,svrfuncno));
}



// ������: GetReqUserID
// ���  : ������ 2010-1-15 18:14:52
// ����  : ��TRUSERIDת��Ϊ������Ϣ�����ı�ʶ�ַ���
// ����  : int :���صı�ʶ�ַ�������
// ����  : TRUSERID *handle [IN]: ��ΪNULL��ʱ�򣬼�Ϊ��ǰ����
// ����  : char *sRUserID [OUT]: ��ʶ�ַ����Ļ��棬����Ӧ��100�ֽ�����
int GetReqUserID(TRUSERID *handle, char *sRUserID)
{
   return(g_SvrLink.GetReqUserID(handle,sRUserID));
}



// ������: BookPostData
// ���  : ������ 2010-1-18 15:32:32
// ����  : ���Ͷ��������ۺϺ���
// ����  : int 0: �ɹ��ύ����<0: �����ʧ�ܡ����У� -3: sRUserID�ڲ����ݴ���-1000: pdlen����(����<0��>MAXMSG); 
// ����  : unsigned int postdno [IN]: ����Դ�ı�ʶֵ
// ����  : const char *sRUserID[IN]: ����Դ���µ�·�����ݣ�����GetReqUserID���
// ����  : void *pdata [IN]: ��Ϣ���ݣ��������pushmode�¿���ΪNULL
// ����  : int pdlen [IN]: ��Ϣ���ݳ��ȣ��������pushmode�¿���Ϊ0�������ܴ���8000
// ����  : char pushmode [IN]: ���Ͷ���ģʽ:PM_CLEAR���������жԸõ����������PM_INACK-����ȷ�ϵ�����ģʽ��PM_ACK-�ɿ�����ģʽ
// ����  : int acktime [IN]: ��PM_ACK��Ч���������Ͷ�����Ϣ����Чʱ�䣬��ƣ����ܻ��1������
int BookPostData(unsigned int postdno, const char *sRUserID, void *pdata, int pdlen, char pushmode, int acktime)
{
   return(g_SvrLink.PostBookData(postdno,sRUserID,pdata,pdlen,pushmode,acktime));
}


// ������: BookUpdatePost
// ���  : ������ 2010-1-19 10:10:45
// ����  : ���¶���Ŀ����·����Ϣ
// ����  : int 0: �ɹ��ύ����<0: �����ʧ�ܡ����У� -3: sRUserID�ڲ����ݴ���
// ����  : unsigned int postdno
// ����  : const char *sRUserID
int BookUpdatePost(unsigned int postdno, const char *sRUserID)
{
   return(g_SvrLink.PostBookData(postdno,sRUserID,NULL,0,'1',0));  // PM_ACK:'1'
}


// ������: GetBaseFuncNo
// ���  : ������ 2010-8-19 9:44:25
// ����  : ȡBCC�Ĺ������ܺţ�����KSMBCC.INI�е�BASEFUNCNO=��������
//          ֻ����BU��������������BCC���ӳɹ����ܻ����ȷֵ
// ����  : int BCC��ͨѶƽ̨��ע��Ĺ���ͨѶ���ܺ�
int GetBaseFuncNo()
{
   return(g_SvrLink.bccBFuncNo);
}


// ������: GetBCCID
// ���  : ������ 2010-8-19 9:47:59
// ����  : ȡBCC��ID�ţ�����KSMBCC.INI�е�ID=������
//          ֻ����BU��������������BCC���ӳɹ����ܻ����ȷֵ
// ����  : int 
int GetBCCID()
{
   return(g_SvrLink.bccID);
}

// ������: CheckPushPack
// ���  : ������ 2010-12-2 12:20:55
// ����  : ������������Ƿ����������͹����������
// ����  : int : 1 - PM1, 1���������ݰ���2 - �����ܵ�������Ϣ��3 - Ӧ���ܵ�������Ϣ��0 - ��������
// ����  : char *oQueueID16 [OUT]: 16�ֽ����ϵĻ��棬���ڻ�ȡ���������QueueID���������ƥ��ԭʼ�����Ӧ���ID
int CheckPushPack(char *oQueueID16)
{
   return(g_SvrLink.CheckPushPack(oQueueID16));
}

int CBUTL::Set(int tlnum)
{
   Close();
   if (tlnum>0)
   {
      if (tlnum<50)
         tlnum = 50;
      pLog = new T_TICKLOG[tlnum];
      if (pLog!=NULL)
      {
         fp = sh_fopen("cyhbuticks.txt","at",SH_DENYNO);
         m_maxtls = tlnum;
      }
      else
      {
         tlnum = 0;
      }
   }
   return(tlnum);
}

void CBUTL::Close()
{
   m_itl = 0;
   if (m_maxtls>0)
   {
      if (pLog!=NULL)
         delete [] pLog;
      pLog = NULL;
      if (fp!=NULL)
         fclose(fp);
      fp = NULL;
      m_maxtls = 0;
   }
}

int CBUTL::Begin()
{
   if (m_maxtls<=0)
      return(0);
   m_itl = 0;
   return(1);
}

int CBUTL::Push(const char *file, int lineno, const char *desc)
{
   if (m_maxtls<=0)
      return(0);
   if (m_maxtls<=m_itl)
      return(m_itl);
   if (file!=NULL)
   {
      STRNCPY(pLog[m_itl].file,file);
      pLog[m_itl].line = lineno;
      pLog[m_itl++].tickus = GetTickCountUS();
      return(m_itl);
   }
   else
      return(0);
}

int CBUTL::Dump()
{
   int i=-1;
   if (fp!=NULL)
   {
      for (i=0;i<m_itl;++i)
      {
         fprintf(fp,"%d\t%u\t%d\t%s\n",
            i+1,pLog[i].tickus,pLog[i].line,pLog[i].file);
      }
      m_itl = 0;
   }
   return(i);
}
