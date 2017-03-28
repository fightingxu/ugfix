#pragma once
#include <lua.hpp>
#include "FIXData.h"
class CLuaFIX
{
public:

	CLuaFIX(void);
	virtual ~CLuaFIX(void);


	// Function name   : LuaInit
	// Description     : ��ʼ��Lua���л�������������Ӧ���ļ�
	// Return type     : int 0-OK, <0 fail to open pluafile 
	int LuaC_Open(const char *pluafile);


   // Function name: LuaC_Close
   // Author       : CHENYH 2012/5/18 9:25:48
   // Description  : �رձ�Lua���л���
   // Return type  : void 
	void LuaC_Close();

	// Function name   : Lua_FIXDataNew
	// Description     : new һ��CFIXData���Ա���ú���������ʹ��
	// Return type     : int ��FIXDATAHANDLE : ����new CFIXData�󷵻ص�ָ�룻NULL - ����ʧ��
	// Argument        : lua_State* L
	static int Lua_FIXDataNew(lua_State* L);


	// Function name   : Lua_FIXDataDelete
	// Description     : delete ����FIXDataNew��õ�CFIXData���ʵ��
	// Return type     : int
	// Argument        : lua_State* L
	static int Lua_FIXDataDelete(lua_State* L);


	// Function name   : Lua_FIXDataReset
	// Description     : ��������CFixData����
	// Return type     : int 
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��
	// Argument        : const char *sBeginString [IN] : Tag8, ��Ϣ�İ汾�ű�ʶ�룬���򲻴���
	// Argument        : const char *sSenderCompID [IN] : Tag49, ��Ϣ���ͷ������򲻴���
	// Argument        : const char *sTargetCompID [IN] : Tag56, ��Ϣ���շ������򲻴���
	static int Lua_FIXDataReset(lua_State* L);


	// Function name   : Lua_FIXDataSetData
	// Description     : ��fix��ʽ����Ϣ�������õ�FIXData������ֵ
	// Return type     : int : int >=0: OK; <0: false 
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN/OUT]:  ͨ��FIXDataNew��õľ��
	// Argument        : const char *fixdata [IN]: fix��ʽ����Ϣ���� 
	// Argument        : int length [IN]: fixdata����Ϣ���ȣ�<=0���ʾfixdata���� '\0'�����ġ�
	static int Lua_FIXDataSetData(lua_State* L);


	// Function name   : Lua_FIXDataAddTag
	// Description     : ��������һ����ǩtag��ֵ
	// Return type     : int  ���ؼ����ǩ�����tag_no, <0 : ���ʾ���󣺲ο�FIXDATA_ERRCODES��
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h[IN/OUT]:  ͨ��FIXDataNew��õľ��
	// Argument        : int tag [IN]: �����FIXTag��tag��ǩ
	// Argument        : const char *tvalue[IN]: tag��ǩ��ֵ
	// Argument        : int vlen [IN]: tag��ǩ��ֵ�ĳ��ȣ�<=0: ���ʾ��ֵΪԭʼ�ַ���
	static int Lua_FIXDataAddTag(lua_State* L);


	// Function name   : Lua_FIXDataGetTagCount
	// Description     : ��ȡ��FIXData�е�FIXTag�ĸ���
	// Return type     : int 
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��
	static int Lua_FIXDataGetTagCount(lua_State* L);


	// Function name   : Lua_FIXDataGetTagNo
	// Description     : ��ȡָ����ǩ���tag_no��FIXTag����Ϣ
	// Return type     : int : int >=0: �ɹ�������tag_no��<0: ʧ�� �ο�FIXDATA_ERRCODES
	// Return value    : tag(��ǩ��tag), tvalue(��ǩֵ), vlen(tvalue�з���FIXTagֵ���ֽ���)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag_no [IN]: ��ǩ���
	static int Lua_FIXDataGetTagNo(lua_State* L);


	// Function name   : Lua_FIXDataGetTag
	// Description     : ���ݱ�ǩ��tagֵ��ȡ��һ�����ָñ�ǩ��ֵ
	// Return type     : int : int >=0: �ɹ������ر�ǩ���tag_no��<0: ʧ�� �ο�FIXDATA_ERRCODES
	// Return value    : tvalue(��ǩֵ), vlen(tvalue�з���FIXTagֵ���ֽ���)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag [IN]: ��ǩ��tag
	static int Lua_FIXDataGetTag(lua_State* L);


	// Function name   : Lua_FIXDataGetTagNext
	// Description     : ��tag_no0�ĺ��濪ʼ����tagΪtag���Ǹ�������������Ϣ
	//                   ��������������ڻ�ȡGroup ��Component Item��Tagֵ������������һ��ͬTag�ķ���ֵΪtag_no0����ú���һ��ͬTag��ֵ
	// Return type     : int :int  >=0: ���ض�Ӧ��tag��ţ�<0: û���ҵ����ο�FIXDATA_ERRCODES
	// Return value    : tvalue(tagֵ�Ļ���), vlen(��õ�tvalue����Ч����)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag_no0 [IN]: ���λ�ã���ʼ��tag_no0+1��tag��ʼ����; ��СΪ-1(��һ��),...
	// Argument        : int tag [IN]: Ҫ��ȡ��tag
	static int Lua_FIXDataGetTagNext(lua_State* L);


	// Function name   : Lua_FIXDataGetGroupTagNext
	// Description     : �Ӵ�tag_no0�ĺ��濪ʼ��Component Group����ָ�����no��tag��ֵ
	// Return type     : int : int   >=0: ���ض�Ӧ��tag��ţ�<0: û���ҵ����ο�FIXDATA_ERRCODES
	// Return value    : tvalue(tagֵ�Ļ���), vlen(��õ�tvalue����Ч����)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag_no0 [IN]: ���λ�ã���ʼ��tag_no0+1��tag��ʼ����; ��СΪ-1. ��Group���͵�ʱ�򣬱���������ΪNoXXX����������Ǹ�tagλ��
	// Argument        : int tag [IN]: Ҫ��ȡ��tag
	// Argument        : int no [IN]: ָ������ţ���0(����һ��)��ʼ...
	static int Lua_FIXDataGetGroupTagNext(lua_State* L);


	// Function name   : Lua_FIXDataUpdateTag
	// Description     : �޸�ָ���ı�ǩ����
	// Return type     : int : int ���ؼ����ǩ�����tag_no, <0 : ���ʾ���󣺲ο�FIXDATA_ERRCODES
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag_no [IN]: �޸ĵ�FIXTag�ı�ǩ��ţ���tag_no<0, �����tagֵ�滻��һ������tag�ı�ǩ���ݣ�����(����)׷�������
	// Argument        : int tag [IN]: �޸ĵ�FIXTag��tag��ǩ
	// Argument        : const char *tvalue [IN]: tag��ǩ��ֵ
	// Argument        : int tvlen [IN]: tag��ǩ��ֵ�ĳ��ȣ�<=0: ���ʾ��ֵΪԭʼ�ַ������ɺ����ڲ�����ֵ�õ�����
	static int Lua_FIXDataUpdateTag(lua_State* L);


	// Function name   : Lua_FIXDataGetFIXData
	// Description     : ��ȡ�Ѿ������˵�������FIXDATA���ݴ�
	// Return type     : int : ����fixdata���صĴ�����Ч����
	// Return value    : fixdata(���FIXDATA���صĸ�ʽ����FIX���ݴ�)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataAddTag��FIXDataUpdateTag��
	static int Lua_FIXDataGetFIXData(lua_State* L);


	// Function name   : Lua_FIXDataRemoveTagNo
	// Description     : ȥ��ָ����Tag��
	// Return type     : int : int >=0: �ɹ������ص�ǰ��tag�������<0: �ο�FIXDATA_ERRCODES
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag_no [IN]: ָ����Tag����
	static int Lua_FIXDataRemoveTagNo(lua_State* L);


	// Function name   : Lua_FIXDataRemoveTag
	// Description     : ȥ����һ�����ֵ�ָ��tag��
	// Return type     : int : int >=0: �ɹ������ص�ǰ��tag�������<0: �ο�FIXDATA_ERRCODES
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  ͨ��FIXDataNew��õľ��, ��������FIXDataSetData�Ȳ���
	// Argument        : int tag: ָ����Tag��
	static int Lua_FIXDataRemoveTag(lua_State* L);


	// Function name   : Lua_GetStdFIXMessage
	// Description     : �õ���׼��ʽ��FIX��Ϣ����
	// Return type     : int ��Ϣ���ݵĳ���
	// Return value    : fixdata(��Ϣ���ݻ���)
	// Argument        : lua_State* L
	// Argument        : int datasize=MAXFIXDATALENGTH [IN]: ��Ϣ����ĳ���
	// Argument        : const char *sBeginString=NULL: ָ��BeginString(��ѡ)
	static int Lua_GetStdFIXMessage(lua_State* L);

#define LUA_INMSG    0  // Partner��������ϵͳ����Ϣ
#define LUA_OUTMSG   1  // ����ϵͳ����Partner����Ϣ

	// Function name   : LuaC_CheckFIXMsg
	// Description     : ͨ��Lua�ű�ȥ��鲢������Ӧ��fix�ֶ�
	// Return type     : int ��int > 0 �����޸ģ�����û�����޸�
   // Argument : CFIXData* pfixdata [INOUT]: ������FIX��Ϣ��
   // Argument : int iInOut [IN]: LUA_INMSG or LUA_OUTMSG
	int LuaC_CheckFIXMsg(CFIXData* pfixdata, int iInOut);

	static int Lua_FIXDataDebugString(lua_State* L);

private:

	static const struct luaL_Reg FIXLib [];
	lua_State* L;
};
