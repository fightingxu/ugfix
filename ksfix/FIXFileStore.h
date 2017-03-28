#ifndef _FILESTORE_H
#define _FILESTORE_H

struct T_RECINDEX
{
   int seqno;
   int pos;
   int length;
};

#define FFSIDXUNITLEN   32  // 10(seqno)+':'+10(offset)+','+10(11+length)
#define FFSDATHEAD      11  // 10(seqno)+':'  +MsgData
struct T_FFSDATA 
{
   FILE *m_fIdx;
   long m_IdxEnd;
   FILE *m_fData;
   long m_DatEnd;
public:
	int Truncate(int seqno);

   // 函数名: T_FFSDATA::GetIndex
   // 编程  : 陈永华 2012-5-24 15:44:29
   // 描述  : 取指定序号的数据索引数据
   /* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
      0 : 本数据块存储单元没有正常打开；
      -1: 不能读取完整的Index单元；
      -2: IndexUnit中的seqno异常；
      -3: IndexUnit中数据位置异常；
      -4: IndexUnit中数据长度值异常；
      -5: 指定数据索引序号越界 (0 - GetCount()-1)
      -6: 定位数据索引位置失败
   *****************************************************/
   // 参数  : int number [IN]: 指定数据索引编号: 0 -- GetCount()-1
   // 参数  : T_RECINDEX *pIdx [OUT]: 返回数据索引
   int GetIndex(int number, T_RECINDEX *pIdx);

   // 取本FFS中存放的数据块个数
	int GetCount();
   
   // 函数名: T_FFSDATA::EndOfDay
   // 编程  : 陈永华 2012-5-24 15:22:42
   // 描述  : 清空数据索引和数据持久化的内容
   // 返回  : bool 
   bool EndOfDay();

   // 函数名: T_FFSDATA::GetData
   // 编程  : 陈永华 2012-5-24 0:06:52
   // 描述  : 根据当前数据索引读取指定的数据块
   /* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
      0 : 本数据块存储单元没有正常打开；
      -5: 不能定位到指定的数据文件位置；
      -6: 读取数据块seqno检查的数据；
      -7: 索引中的seqno和数据块seqno值不符；
      -8: 索引数据中的长度超过dsize值
      -9: 读取指定长度的数据块失败
   *****************************************************/
   // 参数  : T_RECINDEX *pIdx [IN]: 即这块数据索引IndexUnit；(length已经扣除了FFSDATHEAD)
   // 参数  : char *data [OUT]: 存放数据块的缓存；
   // 参数  : int dsize [IN]: data数据块可缓存的最大长度；
	int GetData(T_RECINDEX *pIdx, char *data, int dsize);

   // 函数名: T_FFSDATA::AddData
   // 编程  : 陈永华 2012-5-24 0:12:14
   // 描述  : 持久化一个数据块单元 - DataUnit
   // 返回  : int : 返回数据存储的实际长度；
   //           0: 数据块存储单元没有正常打开；
   //          <0: 写入异常；
   // 参数  : unsigned int seqno [IN]: 数据块的序号
   // 参数  : int length [IN]: 数据块的长度
   // 参数  : const char *data [IN]: 存放存储的数据块
	int AddData(unsigned int seqno, int length, const char *data);

   T_FFSDATA();
   virtual ~T_FFSDATA();
	void close();
};


class CFIXFileStore  
{
public:
   string m_path;
   int m_InSeqNo;
   int m_OutSeqNo;
   time_t m_tmLastEOD;
private:
   FILE *m_fSeqNo;
   
   T_FFSDATA m_In;

   T_FFSDATA m_Out;

public:
	bool SetEODTime(time_t tmEOD);
	bool GetLastSeqNo(int &InSeqNo, int &OutSeqNo);

   // 函数名: GetData
   // 编程  : 陈永华 2012-5-24 15:58:36
   // 描述  : 根据当前数据索引读取指定的数据块
   /* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
      0 : 本数据块存储单元没有正常打开；
      -5: 不能定位到指定的数据文件位置；
      -6: 读取数据块seqno检查的数据；
      -7: 索引中的seqno和数据块seqno值不符；
      -8: 索引数据中的长度超过dsize值
      -9: 读取指定长度的数据块失败
   *****************************************************/
   // 参数  : int in_out [IN]: FAD_IN / FAD_OUT
   // 参数  : T_RECINDEX *pIdx [IN]: 即这块数据索引IndexUnit；(length已经扣除了FFSDATHEAD)
   // 参数  : char *data [OUT]: 存放数据块的缓存；
   // 参数  : int dsize [IN]: data数据块可缓存的最大长度；
	int GetData(int in_out, T_RECINDEX *pIdx, char *data, int dsize);

   // 取存放的数据块个数
	int GetCount(int in_out);

   // 函数名: GetIndex
   // 编程  : 陈永华 2012-5-24 15:53:13
   // 描述  : 取指定序号的数据索引数据
   /* 返回  : int >0: 返回成功读取的数据块长度；<=0: 失败
      0 : 本数据块存储单元没有正常打开；
      -1: 不能读取完整的Index单元；
      -2: IndexUnit中的seqno异常；
      -3: IndexUnit中数据位置异常；
      -4: IndexUnit中数据长度值异常；
      -5: 指定数据索引序号越界 (0 - GetCount()-1)
      -6: 定位数据索引位置失败
   *****************************************************/
   // 参数  : int in_out [IN]: FAD_IN / FAD_OUT
   // 参数  : int number [IN]: 指定数据索引编号: 0 -- GetCount()-1
   // 参数  : T_RECINDEX *pIdx [OUT]: 返回数据索引
	int GetIndex(int in_out, int number, T_RECINDEX *pIdx);

   // 描述  : 清空数据索引和数据持久化的内容
	bool EndOfDay();

   // 函数名: Put
   // 编程  : 陈永华 2012-5-24 15:59:57
   // 描述  : 持久化一个数据块单元 - DataUnit
   // 返回  : int : 返回数据存储的实际长度；
   //           0: 数据块存储单元没有正常打开；
   //          <0: 写入异常；
   // 参数  : int in_out [IN]: FAD_IN / FAD_OUT
   // 参数  : unsigned int seqno [IN]: 数据块的序号
   // 参数  : const char *fixdata [IN]: 存放存储的数据块
   // 参数  : int fdlen [IN]: 数据块的长度
	int Put(int in_out, unsigned int seqno, const char *fixdata, int fdlen);

   bool IsOpened();


   // 函数名: SetSeqNo
   // 编程  : 陈永华 2012-5-24 16:02:44
   // 描述  : 设置序号，并持久化
   // 返回  : bool 
   // 参数  : int InSeqNo=-1 : <0 不变
   // 参数  : int OutSeqNo=-1 : <0 不变
	bool SetSeqNo(int InSeqNo=-1, int OutSeqNo=-1);

	bool Open(char *path);
	void Close();
   CFIXFileStore();
   virtual ~CFIXFileStore();   
private:
	bool OpenFDFiles(T_FFSDATA *pfg, const char *idxfile, const char *datfile);
	bool RestoreSeqNo();
	FILE * fdopen(const char *file, const char *mode);
};
#endif