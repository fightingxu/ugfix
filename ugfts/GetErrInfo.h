#ifndef _GETERRINFO_H
#define _GETERRINFO_H

//公司为交易所指定内部市场代码，现有的市场代码有A,B,C,G.
//处理报盘的拒单信息时需要用到市场代码，
//为统一处理OMS的拒单原因，规定FIX系统中证券业务的市场代码为s,期货为f.
#define STOCK_MCODE 's'
#define FUTURE_MCODE 'f'

#ifdef __cplusplus
extern "C" {
#endif

// 函数名: SetErrCodeInfo
// 编程  : shijubo 2011-08-24
// 描述  : 将输入的中文错误信息转换为英文的
// 返回  : 是否查到相应的英文信息，0：成功查找到错误信息；-1：未找到
// 参数  : char MarketCode  [IN]: 内部市场代码
// 参数  : char* CHErrMsg [IN]: 中文的错误信息,[<xxxx-->]<*********>.例：260--委托单修改定义错误
// 参数  : char* RejMsgPre [IN]: 规定输出错误信息的前缀
// 参数  : char* MsgOut [OUT]: 转换后的英文错误信息
int SetErrCodeInfo(char MarketCode, char* CHErrMsg,char* RejMsgPre, char* MsgOut);

#ifdef __cplusplus
}
#endif
#endif
