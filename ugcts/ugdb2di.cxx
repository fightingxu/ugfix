
/***********************************************************************************
  编码日志记录
  编码者: 陈永华
  编码日期 2004-2-7 18:13:36
  版本: V1.00 
  说明: 系统数据库部分的基本功能，在正式使用之前必须复制为 .sqc, 
  以便nsqlprep预编译，这里定义为 .cpp是为了用IDE时候编辑方便
 ***********************************************************************************/
#define _IN_SQC_   // 每个SQC源文件必须包括本定义，以激活 gmsqc.h中的 ：EXEC SQL WHENEVER SQLERROR CALL SQLErrorHandler();

#include <stdio.h>
#include <string.h>
#include "busqc.h"
#ifdef __cplusplus
extern "C" {
#endif
//void WriteLog(int level,char *fmt, ...);
#ifdef __cplusplus
}
#endif

#include <sql.h>
EXEC SQL INCLUDE sqlca;

ST_SQLDB *pSqlDB;


/* ****** Updated by CHENYH at 2004-2-7 23:02:02 ****** 
// install Embedded SQL for C error handler
EXEC SQL WHENEVER SQLERROR CALL SQLErrorHandler();
*/

int DbConnect(char *sDBName,char *sUser,char *sPass)
{
   EXEC SQL BEGIN DECLARE SECTION;
   char m_dbname[32];
   char m_user[32];
   char m_pass[32];
   EXEC SQL END DECLARE SECTION;
   
   strcpy(m_dbname,sDBName);
   strcpy(m_user,sUser);
   strcpy(m_pass,sPass);
  
   if(strlen(m_user)==0)
   {
      EXEC SQL CONNECT TO :m_dbname ;
   }
   else
   {
      EXEC SQL CONNECT TO :m_dbname USER :m_user USING :m_pass;
   }

   if(SQLCODE)
   {
      SQLDebugLog(10000, "Connect Database %s User %s Passwd %s Error(%d)!",m_dbname,m_user,m_pass,SQLCODE);
      return SQLCODE;
   }
   
   SQLDebugLog(1, "Connect Database %s success!",m_dbname);
   return 0;
}

int DbDisConnect()
{
	EXEC SQL CONNECT RESET;
	return SQLCODE;
}

int RollBack()
{
	EXEC SQL ROLLBACK;
	return SQLCODE;
}

int Commit()
{
	EXEC SQL COMMIT WORK;
	return SQLCODE;
}

void SQLErrorHandler()
{

/* ****** Updated by CHENYH at 2004-7-1 9:33:33 ****** 
   g_BUnit.m_SqlDB.lErrorCode = SQLCODE;
   g_BUnit.m_SqlDB.lErrorNumber = SQLERRD1;
   strncpy(g_BUnit.m_SqlDB.szErrorMsg,(char *)SQLERRMC,sizeof(g_BUnit.m_SqlDB.szErrorMsg)-1);
   strncpy(g_BUnit.m_SqlDB.szErrorState,SQLSTATE,sizeof(g_BUnit.m_SqlDB.szErrorState));
   if (SQLCODE<=-10000)
      SQLDebugLog(SQLCODE,"SQLERROR DEBUG: SQLSTATE(%s)-msg%ld:'%s'",
         g_BUnit.m_SqlDB.szErrorState,
         g_BUnit.m_SqlDB.lErrorNumber,
         g_BUnit.m_SqlDB.szErrorMsg);
*/
}

void SQLInitialize(ST_SQLDB *psqldb)
{
   pSqlDB = psqldb;
    // set Embedded SQL for C options

/* ****** Updated by CHENYH at 2004-7-1 9:31:59 ****** 
    EXEC SQL SET OPTION LOGINTIME 10;
    EXEC SQL SET OPTION QUERYTIME 100;
    EXEC SQL SET ANSI_DEFAULTS ON;  // Specifies SQL-92 compatibility
    EXEC SQL SET CONCURRENCY READONLY;  // Specifies read-only cursors. Data retrieved by a FETCH statement cannot be modified.
    EXEC SQL SET FETCHBUFFER 1;   
*/
}

void SQLDisconnect1()
{
   if (pSqlDB->bConnected)
   {

/* ****** Updated by CHENYH at 2004-7-1 9:32:06 ****** 
      EXEC SQL DISCONNECT ALL;
*/
		if (DbDisConnect()==0)
			pSqlDB->bConnected = 0;
   }
}

void SQLExit()
{
   SQLDisconnect1(); 
}


// 函数名: SQLConnectToServer
// 编程  : 陈永华 2004-2-7 23:24:49
// 描述  : 根据g_BUnit.m_SqlDB中定义的SQL数据库连接参数，建立连接
// 返回  : int   0: 表示连接成功；其他则连接失败，检查g_BUnit.m_SqlDB中的SQL处理失败信息
int SQLConnectToServer()
{
	int bRet=0;

	bRet=DbConnect(pSqlDB->szDatabase,pSqlDB->szLogin,pSqlDB->szPassword);
	if (bRet==0)
	{
		pSqlDB->bConnected = 1;
	}
	else
	{
		pSqlDB->bConnected = 0;
	}
	return(bRet);

/* ****** Updated by CHENYH at 2004-7-1 9:32:21 ****** 
   EXEC SQL BEGIN DECLARE SECTION;
   // for CONNECT TO statement
   char szConnectToServerDatabase[(SQLID_MAX * 2)+2] = "";
   char szConnectToLoginPassword[(SQLID_MAX * 2)+2] = "";
   EXEC SQL END DECLARE SECTION;

   ST_SQLDB *pSqlDB = &(g_BUnit.m_SqlDB);
   
   // set defaults
   if (strlen(pSqlDB->szDatabase) == 0)
   {
      strcpy(pSqlDB->szDatabase, "pubs");
   }
   
   // build host variables for CONNECT TO
   if (strlen(pSqlDB->szServer) != 0)
   {
      strcat(szConnectToServerDatabase, pSqlDB->szServer);
      strcat(szConnectToServerDatabase, ".");
   }
   if (strlen(pSqlDB->szDatabase) != 0)
   {
      strcat(szConnectToServerDatabase, pSqlDB->szDatabase);
   }
   
   if (strlen(pSqlDB->szLogin) != 0)
   {
      strcat(szConnectToLoginPassword, pSqlDB->szLogin);
   }
   if (strlen(pSqlDB->szPassword) != 0)
   {
      strcat(szConnectToLoginPassword, ".");
      strcat(szConnectToLoginPassword, pSqlDB->szPassword);
   }
   
   // attempt connection to SQL Server
   EXEC SQL CONNECT TO :szConnectToServerDatabase AS MYDB0 USER :szConnectToLoginPassword;
   

   if (SQLCODE == 0)
   {
      pSqlDB->bConnected = 1;
   }
   else
   {
      // problem connecting to SQL Server
      pSqlDB->bConnected = 0;
   }
   return(SQLCODE);
*/
}

int  SQLIsConnectOK()
{
   EXEC SQL BEGIN DECLARE SECTION;
   long sv_tv = 0;
   EXEC SQL END DECLARE SECTION;

   /* 2007-01-29 modified by zhanghao
      EXEC SQL SELECT 1 INTO :sv_tv from ks.system; */
   EXEC SQL VALUES 1 INTO :sv_tv;

   if (SQLCODE==0 && sv_tv==1)
      return(1);
   else
      return(0);
}


void PrintErrMsg(char *appMsg,struct sqlca * pSqlca,int line,char *file)
{
   int   rc = 0;
   char  sqlInfo[1024];
   char  sqlInfoToken[1024];
   char  sqlstateMsg[1024];
   char  errorMsg[1024];
   
   if (pSqlca->sqlcode != 0)
   {
      if( pSqlca->sqlcode < 0)
      {
         strcpy(sqlInfo,"\n---- error report ----\n");
      }
      else
      {
         strcpy(sqlInfo,"\n---- warning report ----\n");
      } /* endif */
      
      sprintf( sqlInfoToken, "  app. message = %s\n", appMsg);
      strcat( sqlInfo, sqlInfoToken);
      sprintf( sqlInfoToken, "  line         = %d\n", line);
      strcat( sqlInfo, sqlInfoToken);
      sprintf( sqlInfoToken, "  file         = %s\n", file);
      strcat( sqlInfo, sqlInfoToken);
      sprintf( sqlInfoToken, "  SQLCODE      = %ld\n", pSqlca->sqlcode);
      strcat( sqlInfo, sqlInfoToken);
      
      /* get error message */
      rc = sqlaintp( errorMsg, 1024, 80, pSqlca);
      /* return code is the length of the errorMsg string */
      if( rc > 0)
      {
         sprintf( sqlInfoToken, "%s\n", errorMsg);
         strcat( sqlInfo, sqlInfoToken);
      }
      
      /* get SQLSTATE message */
      rc = sqlogstt( sqlstateMsg, 1024, 80, pSqlca->sqlstate);
      if (rc == 0)
      {
         sprintf( sqlInfoToken, "%s\n", sqlstateMsg);
         strcat( sqlInfo, sqlInfoToken);
      }
      if( pSqlca->sqlcode < 0)
      {
          SQLDebugLog(0,"%s--- end error report ---",sqlInfo);
/* ****** Updated by CHENYH at 2006-1-18 17:57:52 ****** 
         strcat(sqlInfo, "--- end error report ---\n");
         TextLogOut(80000,sqlInfo);
*******************************************************/
      }
      else
      {
          SQLDebugLog(0,"%s--- end warning report ---",sqlInfo);
/* ****** Updated by CHENYH at 2006-1-18 17:57:54 ****** 
         strcat(sqlInfo, "--- end warning report ---\n");
         TextLogOut(8000,sqlInfo);
*******************************************************/
      } /* endif */
   } /* endif */
   else
   {
      SQLDebugLog(0,"  app. message = %s\n  line         = %d\n  file         = %s\n",
        appMsg, line, file);
   }
   return;
}





















