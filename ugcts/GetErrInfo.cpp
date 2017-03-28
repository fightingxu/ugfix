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
	char smarket_code;        //�ڲ��г�����
    T_QHERRITEM* ErrCodeItems;   //������Ϣ
	int iSize;                   //������Ϣ����
}T_QHERRINFO;
T_QHERRINFO g_ErrInfo[MAXMARKETS];

//����qsort()�ıȽϺ���
int comp( const void* p, const void* q) 
{ 
	if(p !=NULL && q != NULL)
           return ( ((T_QHERRITEM*)p)->ErrCode - ((T_QHERRITEM*)q)->ErrCode ) ;
        else
           return 0;
} 

//������Ӣ�Ĵ�����Ϣ���ձ�
int LoadErrCodeFile( )
{
	if(g_nMarkets >= 0)
		return 0;
    FILE* fp = NULL;
	char tmp[512];
	short i = 0; //�ڼ����г�A,B,C,G,...
	fp = fopen(ERRCODEFILE,"r");
	if (fp==NULL)
		return(-1); // ���ܴ򿪴�������ļ�
	g_nMarkets =0;
	while(fgets(tmp,sizeof(tmp),fp)) //��load���е��г�����
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
		g_ErrInfo[i].iSize = 0; //Ϊ�˺���ͳһ���������Ϣ�Ĵ洢������Ϊ0
	}
	fseek(fp,0,SEEK_SET);
	while(fgets(tmp,sizeof(tmp),fp)) //load�����г���ί�оܾ��������ܾ���ԭ��
	{
		if (tmp[1]!='|')
			continue;
		for(i=0;i<g_nMarkets;i++)
		{
			if( tmp[0] == g_ErrInfo[i].smarket_code )
				break;
		}
		if( i>=g_nMarkets) //��ֹ�쳣���
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

//�۰����
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
	iCode = atoi(CHErrMsg);//�����������
	if(g_nMarkets<1)
	{
	    if(LoadErrCodeFile() <0) //�ļ�������
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
	if(iCode>0)  //���ڴ������
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
	if(iPos >= g_ErrInfo[i].iSize||iPos < 0) //û���ҵ���Ӧ�Ĵ�����Ϣ
	{
	    sprintf(MsgOut,"%d:Unknow Reason!", iCode);
		return -1;
	}
	sprintf(MsgOut,"%s%d:%s",RejMsgPre,g_ErrInfo[i].ErrCodeItems[iPos].ErrCode,g_ErrInfo[i].ErrCodeItems[iPos].ErrStr_ENG);
	return 0;
}
