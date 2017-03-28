/***********************************************************************************
  ������־��¼
  ������: ������
  �������� 2004-2-7 15:36:16
  �汾: V1.00 
  ˵��: �����sqc������ص�ȫ�ֱ����ͺ�������
  2004-9-9 14:22:26 : Ϊ���ܹ�֧�ֶ����ݿ����Ӷ������޸ģ�
 ***********************************************************************************/
#ifndef _DB2SQC_H
#define _DB2SQC_H

#define  SC_OK       0
#define  SC_NOTFOUND 100  // No data found 

// maximum SQL Server identifier length
//#define SQLID_MAX 30

typedef struct 
{
   char szLogin[32];     // SQL Server login ID
   char szPassword[32];  // SQL Server password
   char szServer[32];    // SQL Server name
   char szDatabase[32];  // SQL Server database to use
      
   int bConnected;            // are we connected to SQL Server?  1 as Connected, 0 as Disconnected
   
   // ���һ�δ���ʱ��Ĵ�����Ϣ��
   long lErrorCode;        // = SQLCODE  The SQLCODE field contains the negative SQL Server error code (the ESQL/C standard requires that error codes be negative). 
   long lErrorNumber;      // = SQLERRD1 The SQLERRD1 field contains the error number
   char szErrorMsg[80];    // The SQLERRMC field contains the text of the error message. 
   char szErrorState[6];   // SQLSTATE codes return values that are error, warning, or "no data found" messages. 
} ST_SQLDB;


//extern ST_SQLDB g_SQLDB;

#ifdef __cplusplus
extern "C" {
#endif
//////////////////////////////////////////////////////////////////////
// Ŀǰֻ���ǵ�һ���ݿ�����

void SQLErrorHandler();
void SQLInitialize(ST_SQLDB *pSQLDB);
void SQLExit();

// ������: SQLConnectToServer
// ���  : ������ 2004-2-7 23:24:49
// ����  : ����g_SqlDB�ж����SQL���ݿ����Ӳ�������������
// ����  : long   0: ��ʾ���ӳɹ�������������ʧ�ܣ����g_SqlDB�е�SQL����ʧ����Ϣ
int SQLConnectToServer();
int  SQLIsConnectOK();
void SQLDisconnect1();

int RollBack();
int Commit();


#ifdef _IN_SQC_
// install Embedded SQL for C error handler

#endif

#ifdef __cplusplus
}
#endif

#endif
