// FIXAppData.h: interface for the CFIXAppData class.
// 用于持久化FIX
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIXAPPDATA_H__51DFF822_CE03_49A4_ADF3_84D742CF7C97__INCLUDED_)
#define AFX_FIXAPPDATA_H__51DFF822_CE03_49A4_ADF3_84D742CF7C97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "FIXFileStore.h"

#define FAD_IN    0
#define FAD_OUT   1

class CFIXAppData  
{
private:  
   CFIXFileStore m_Main;   // 主持久化
   CFIXFileStore m_Back;   // 备持久化

public:
	time_t GetLastEODTime();
	bool SetEODTime(time_t tmEOD);
	bool GetLastSeqNo(int &InSeqNo, int &OutSeqNo);
	void Close();

   // 函数名: GetData
   // 编程  : 陈永华 2012-5-24 16:11:35
   // 描述  : 取指定序号的块数据
   /* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
      0 : 本数据块存储单元没有正常打开；
      -1: 不能读取完整的Index单元；
      -2: IndexUnit中的seqno异常；
      -3: IndexUnit中数据位置异常；
      -4: IndexUnit中数据长度值异常；
      -5: 指定数据索引序号越界 (0 - GetCount()-1)
      -6: 定位数据索引位置失败
      -7: 不能定位到指定的数据文件位置；
      -8: 读取数据块seqno检查的数据；
      -9: 索引中的seqno和数据块seqno值不符；
      -10: 索引数据中的长度超过dsize值
      -11: 读取指定长度的数据块失败
   *****************************************************/
   // 参数  : int in_out [IN]: FAD_IN / FAD_OUT
   // 参数  : int number [IN]: 指定数据索引编号: 0 -- GetCount()-1
   // 参数  : int *seqno [OUT]: 返回其序号SeqNo
   // 参数  : char *data [OUT]: 存放数据块的缓存；
   // 参数  : int dsize [IN]: data数据块可缓存的最大长度；
	int GetData(int in_out, int number, int *seqno, char *data, int dsize);


   // 取被持久化数据块数
	int GetCount(int in_out);

   // 函数名: SetSeqNo
   // 编程  : 陈永华 2012-5-24 16:02:44
   // 描述  : 设置序号，并持久化
   // 返回  : bool 
   // 参数  : int InSeqNo=-1 : <0 不变
   // 参数  : int OutSeqNo=-1 : <0 不变
	bool SetSeqNo(int InSeqNo=-1, int OutSeqNo=-1);

   // 函数名: CFIXAppData::EndOfDay
   // 编程  : 陈永华 2012-5-24 15:28:55
   // 描述  : 将持久化的数据清空，并且将序号置0
   // 返回  : bool 
   bool EndOfDay();

   // Function name: CFIXAppData::Put
   // Author       : CHENYH 2012/5/22 16:50:16
   // Description  : 将新的应用消息，进行持久化
   // 返回  : int : 返回数据存储的实际长度；
   //           0: 数据块存储单元没有正常打开；
   //          <0: 写入异常；
   // 参数  : int in_out [IN]: FAD_IN / FAD_OUT
   // Argument : unsigned int seqno [IN]: 消息序号seqno - key
   // Argument : const char *fixdata [IN]: 应用消息具体数据
   // Argument : int fdlen [IN]: fixdata中消息的字节数
   int Put(int in_out, unsigned int seqno, const char *fixdata, int fdlen);

	bool Init(char *path, char *bkpath=NULL);

	CFIXAppData();
	virtual ~CFIXAppData();

private:
};

#endif // !defined(AFX_FIXAPPDATA_H__51DFF822_CE03_49A4_ADF3_84D742CF7C97__INCLUDED_)
