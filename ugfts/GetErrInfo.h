#ifndef _GETERRINFO_H
#define _GETERRINFO_H

//��˾Ϊ������ָ���ڲ��г����룬���е��г�������A,B,C,G.
//�����̵ľܵ���Ϣʱ��Ҫ�õ��г����룬
//Ϊͳһ����OMS�ľܵ�ԭ�򣬹涨FIXϵͳ��֤ȯҵ����г�����Ϊs,�ڻ�Ϊf.
#define STOCK_MCODE 's'
#define FUTURE_MCODE 'f'

#ifdef __cplusplus
extern "C" {
#endif

// ������: SetErrCodeInfo
// ���  : shijubo 2011-08-24
// ����  : ����������Ĵ�����Ϣת��ΪӢ�ĵ�
// ����  : �Ƿ�鵽��Ӧ��Ӣ����Ϣ��0���ɹ����ҵ�������Ϣ��-1��δ�ҵ�
// ����  : char MarketCode  [IN]: �ڲ��г�����
// ����  : char* CHErrMsg [IN]: ���ĵĴ�����Ϣ,[<xxxx-->]<*********>.����260--ί�е��޸Ķ������
// ����  : char* RejMsgPre [IN]: �涨���������Ϣ��ǰ׺
// ����  : char* MsgOut [OUT]: ת�����Ӣ�Ĵ�����Ϣ
int SetErrCodeInfo(char MarketCode, char* CHErrMsg,char* RejMsgPre, char* MsgOut);

#ifdef __cplusplus
}
#endif
#endif
