/***********************************************************************************
  编码日志记录
  编码者: 陈永华
  编码日期 2004-2-7 15:36:16
  版本: V1.00 
  说明: 与各个sqc程序相关的全局变量和函数定义
  2004-9-9 14:22:26 : 为了能够支持多数据库连接而作的修改，
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
   
   // 最后一次错误时候的错误信息：
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
// 目前只考虑单一数据库连接

void SQLErrorHandler();
void SQLInitialize(ST_SQLDB *pSQLDB);
void SQLExit();

// 函数名: SQLConnectToServer
// 编程  : 陈永华 2004-2-7 23:24:49
// 描述  : 根据g_SqlDB中定义的SQL数据库连接参数，建立连接
// 返回  : long   0: 表示连接成功；其他则连接失败，检查g_SqlDB中的SQL处理失败信息
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
