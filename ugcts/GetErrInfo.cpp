#include "stdafx.h"
#include "stdlib.h"
#include "GetErrInfo.h"
#include "xpub.h"

#define MAXMARKETS 20
#define ERRCODEFILE "RejErrorCode.txt"
static int g_nMarkets=-1;

typedef struct{
	int ErrCode;
	char ErrStr_CH[128];
	char ErrStr_ENG[192];
}T_QHERRITEM;

typedef struct{
	char smarket_code;        //内部市场代码
    T_QHERRITEM* ErrCodeItems;   //错误信息
	int iSize;                   //错误信息条数
}T_QHERRINFO;
T_QHERRINFO g_ErrInfo[MAXMARKETS];

//用于qsort()的比较函数
int comp( const void* p, const void* q) 
{ 
	if(p !=NULL && q != NULL)
           return ( ((T_QHERRITEM*)p)->ErrCode - ((T_QHERRITEM*)q)->ErrCode ) ;
        else
           return 0;
} 

//加载中英文错误信息对照表
int LoadErrCodeFile( )
{
	if(g_nMarkets >= 0)
		return 0;
    FILE* fp = NULL;
	char tmp[512];
	short i = 0; //第几个市场A,B,C,G,...
	fp = fopen(ERRCODEFILE,"r");
	if (fp==NULL)
		return(-1); // 不能打开错误代码文件
	g_nMarkets =0;
	while(fgets(tmp,sizeof(tmp),fp)) //先load所有的市场代码
	{
	    if ( tmp[1]!='|')
		   continue;
	    for(i=0; i<g_nMarkets; i++)
		{
		    if(g_ErrInfo[i].smarket_code == tmp[0])
			{
			    g_ErrInfo[i].iSize++;
			    break;
			}
		}
		if(i >=g_nMarkets)
		{
			g_ErrInfo[g_nMarkets].smarket_code = tmp[0];
			g_ErrInfo[g_nMarkets].iSize = 1;
			g_nMarkets++;
		}
	}
	for(i=0; i<g_nMarkets; i++ )
	{
		g_ErrInfo[i].ErrCodeItems = (T_QHERRITEM*)malloc( g_ErrInfo[i].iSize * sizeof(T_QHERRITEM) );
		g_ErrInfo[i].iSize = 0; //为了后面统一处理错误信息的存储，先设为0
	}
	fseek(fp,0,SEEK_SET);
	while(fgets(tmp,sizeof(tmp),fp)) //load各个市场的委托拒绝、撤单拒绝的原因
	{
		if (tmp[1]!='|')
			continue;
		for(i=0;i<g_nMarkets;i++)
		{
			if( tmp[0] == g_ErrInfo[i].smarket_code )
				break;
		}
		if( i>=g_nMarkets) //防止异常情况
			continue;
		T_QHERRITEM *pItem = g_ErrInfo[i].ErrCodeItems + g_ErrInfo[i].iSize;
		memset(pItem,0,sizeof(T_QHERRITEM));
		pItem->ErrCode = atoi(tmp+2);
		GetSubString(tmp, '|', 2 ,pItem->ErrStr_CH , sizeof(pItem->ErrStr_CH),  NULL);
		GetSubString(tmp, '|', 3 ,pItem->ErrStr_ENG, sizeof(pItem->ErrStr_ENG), NULL);
		mytrim(pItem->ErrStr_ENG);
		g_ErrInfo[i].iSize++;
	}
	for(i=0;i<g_nMarkets;i++)
		qsort(g_ErrInfo[i].ErrCodeItems,g_ErrInfo[i].iSize,sizeof(T_QHERRITEM),comp);
	fclose(fp);
	return 0;
}

//折半查找
int BiSearch(int key,T_QHERRINFO ErrInfo)
{
	int low = 0,high = ErrInfo.iSize-1, mid=0;
	while(low<=high)
	{
		mid = (low+high)/2;
		if(key == ErrInfo.ErrCodeItems[mid].ErrCode)
			return mid;
		else if(ErrInfo.ErrCodeItems[mid].ErrCode < key)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

int SetErrCodeInfo(char MarketCode, char* CHErrMsg,char* RejMsgPre, char* MsgOut)
{
	int i =0;
	int iPos=-1;
	int iCode  = 0;
	iCode = atoi(CHErrMsg);//解析错误代码
	if(g_nMarkets<1)
	{
	    if(LoadErrCodeFile() <0) //文件不存在
		{
		   sprintf(MsgOut,"%d(Load %s failed)", iCode, ERRCODEFILE);
		   return -1;
		}
	}
	for(; i<g_nMarkets ;i++)
	{
		if( MarketCode == g_ErrInfo[i].smarket_code )
			break;
	}
	if(i >= g_nMarkets)
	{
		sprintf(MsgOut,"%d:Unknow MarketCode-%c",iCode, MarketCode);
		return -1;
	}
	if(iCode>0)  //存在错误代码
	{
			iPos =BiSearch(iCode, g_ErrInfo[i]);
	}
	else
	{
		for(iPos=0;iPos<g_ErrInfo[i].iSize;iPos++)
		{
			if( strstr(CHErrMsg,g_ErrInfo[i].ErrCodeItems[iPos].ErrStr_CH) )
				break;
		}
	}
	if(iPos >= g_ErrInfo[i].iSize||iPos < 0) //没有找到对应的错误信息
	{
	    sprintf(MsgOut,"%d:Unknow Reason!", iCode);
		return -1;
	}
	sprintf(MsgOut,"%s%d:%s",RejMsgPre,g_ErrInfo[i].ErrCodeItems[iPos].ErrCode,g_ErrInfo[i].ErrCodeItems[iPos].ErrStr_ENG);
	return 0;
}
