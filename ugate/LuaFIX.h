#pragma once
#include <lua.hpp>
#include "FIXData.h"
class CLuaFIX
{
public:

	CLuaFIX(void);
	virtual ~CLuaFIX(void);


	// Function name   : LuaInit
	// Description     : 初始化Lua运行环境，并加载相应的文件
	// Return type     : int 0-OK, <0 fail to open pluafile 
	int LuaC_Open(const char *pluafile);


   // Function name: LuaC_Close
   // Author       : CHENYH 2012/5/18 9:25:48
   // Description  : 关闭本Lua运行环境
   // Return type  : void 
	void LuaC_Close();

	// Function name   : Lua_FIXDataNew
	// Description     : new 一个CFIXData，以便调用后续函数的使用
	// Return type     : int ：FIXDATAHANDLE : 返回new CFIXData后返回的指针；NULL - 调用失败
	// Argument        : lua_State* L
	static int Lua_FIXDataNew(lua_State* L);


	// Function name   : Lua_FIXDataDelete
	// Description     : delete 调用FIXDataNew获得的CFIXData类的实例
	// Return type     : int
	// Argument        : lua_State* L
	static int Lua_FIXDataDelete(lua_State* L);


	// Function name   : Lua_FIXDataReset
	// Description     : 重新设置CFixData内容
	// Return type     : int 
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄
	// Argument        : const char *sBeginString [IN] : Tag8, 消息的版本号标识码，空则不处理
	// Argument        : const char *sSenderCompID [IN] : Tag49, 消息发送方，空则不处理
	// Argument        : const char *sTargetCompID [IN] : Tag56, 消息接收方，空则不处理
	static int Lua_FIXDataReset(lua_State* L);


	// Function name   : Lua_FIXDataSetData
	// Description     : 将fix格式的消息数据设置到FIXData的数据值
	// Return type     : int : int >=0: OK; <0: false 
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN/OUT]:  通过FIXDataNew获得的句柄
	// Argument        : const char *fixdata [IN]: fix格式的消息数据 
	// Argument        : int length [IN]: fixdata的消息长度，<=0则表示fixdata是以 '\0'结束的。
	static int Lua_FIXDataSetData(lua_State* L);


	// Function name   : Lua_FIXDataAddTag
	// Description     : 在最后添加一个标签tag和值
	// Return type     : int  返回加入标签的序号tag_no, <0 : 则表示错误：参考FIXDATA_ERRCODES等
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h[IN/OUT]:  通过FIXDataNew获得的句柄
	// Argument        : int tag [IN]: 加入的FIXTag的tag标签
	// Argument        : const char *tvalue[IN]: tag标签的值
	// Argument        : int vlen [IN]: tag标签的值的长度，<=0: 则表示该值为原始字符串
	static int Lua_FIXDataAddTag(lua_State* L);


	// Function name   : Lua_FIXDataGetTagCount
	// Description     : 获取本FIXData中的FIXTag的个数
	// Return type     : int 
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄
	static int Lua_FIXDataGetTagCount(lua_State* L);


	// Function name   : Lua_FIXDataGetTagNo
	// Description     : 获取指定标签序号tag_no的FIXTag的信息
	// Return type     : int : int >=0: 成功，返回tag_no；<0: 失败 参考FIXDATA_ERRCODES
	// Return value    : tag(标签的tag), tvalue(标签值), vlen(tvalue中返回FIXTag值的字节数)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag_no [IN]: 标签序号
	static int Lua_FIXDataGetTagNo(lua_State* L);


	// Function name   : Lua_FIXDataGetTag
	// Description     : 根据标签的tag值获取第一个出现该标签的值
	// Return type     : int : int >=0: 成功，返回标签序号tag_no；<0: 失败 参考FIXDATA_ERRCODES
	// Return value    : tvalue(标签值), vlen(tvalue中返回FIXTag值的字节数)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag [IN]: 标签的tag
	static int Lua_FIXDataGetTag(lua_State* L);


	// Function name   : Lua_FIXDataGetTagNext
	// Description     : 从tag_no0的后面开始查找tag为tag的那个，并获得相关信息
	//                   这个方法可以用于获取Group 的Component Item的Tag值，即基于上面一个同Tag的返回值为tag_no0，获得后面一个同Tag的值
	// Return type     : int :int  >=0: 返回对应的tag序号；<0: 没有找到，参考FIXDATA_ERRCODES
	// Return value    : tvalue(tag值的缓存), vlen(获得的tvalue的有效长度)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag_no0 [IN]: 相对位置，开始从tag_no0+1的tag开始查找; 最小为-1(第一个),...
	// Argument        : int tag [IN]: 要获取的tag
	static int Lua_FIXDataGetTagNext(lua_State* L);


	// Function name   : Lua_FIXDataGetGroupTagNext
	// Description     : 从从tag_no0的后面开始的Component Group中找指定序号no的tag的值
	// Return type     : int : int   >=0: 返回对应的tag序号；<0: 没有找到，参考FIXDATA_ERRCODES
	// Return value    : tvalue(tag值的缓存), vlen(获得的tvalue的有效长度)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag_no0 [IN]: 相对位置，开始从tag_no0+1的tag开始查找; 最小为-1. 在Group类型的时候，本参数常常为NoXXX的组项个数那个tag位置
	// Argument        : int tag [IN]: 要获取的tag
	// Argument        : int no [IN]: 指定的序号，从0(即第一个)开始...
	static int Lua_FIXDataGetGroupTagNext(lua_State* L);


	// Function name   : Lua_FIXDataUpdateTag
	// Description     : 修改指定的标签内容
	// Return type     : int : int 返回加入标签的序号tag_no, <0 : 则表示错误：参考FIXDATA_ERRCODES
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag_no [IN]: 修改的FIXTag的标签序号，当tag_no<0, 则根据tag值替换第一个出现tag的标签内容，或者(无则)追加在最后
	// Argument        : int tag [IN]: 修改的FIXTag的tag标签
	// Argument        : const char *tvalue [IN]: tag标签的值
	// Argument        : int tvlen [IN]: tag标签的值的长度，<=0: 则表示该值为原始字符串，由函数内部根据值得到长度
	static int Lua_FIXDataUpdateTag(lua_State* L);


	// Function name   : Lua_FIXDataGetFIXData
	// Description     : 获取已经设置了的完整的FIXDATA数据串
	// Return type     : int : 返回fixdata返回的串的有效长度
	// Return value    : fixdata(存放FIXDATA返回的格式化的FIX数据串)
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataAddTag或FIXDataUpdateTag等
	static int Lua_FIXDataGetFIXData(lua_State* L);


	// Function name   : Lua_FIXDataRemoveTagNo
	// Description     : 去掉指定的Tag域
	// Return type     : int : int >=0: 成功，返回当前总tag域个数；<0: 参考FIXDATA_ERRCODES
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag_no [IN]: 指定的Tag域编号
	static int Lua_FIXDataRemoveTagNo(lua_State* L);


	// Function name   : Lua_FIXDataRemoveTag
	// Description     : 去掉第一个发现的指定tag域
	// Return type     : int : int >=0: 成功，返回当前总tag域个数；<0: 参考FIXDATA_ERRCODES
	// Argument        : lua_State* L
	// Argument        : FIXDATAHANDLE h [IN]:  通过FIXDataNew获得的句柄, 并做了如FIXDataSetData等操作
	// Argument        : int tag: 指定的Tag域
	static int Lua_FIXDataRemoveTag(lua_State* L);


	// Function name   : Lua_GetStdFIXMessage
	// Description     : 得到标准格式的FIX消息数据
	// Return type     : int 消息数据的长度
	// Return value    : fixdata(消息数据缓存)
	// Argument        : lua_State* L
	// Argument        : int datasize=MAXFIXDATALENGTH [IN]: 消息缓存的长度
	// Argument        : const char *sBeginString=NULL: 指定BeginString(可选)
	static int Lua_GetStdFIXMessage(lua_State* L);

#define LUA_INMSG    0  // Partner发给本方系统的消息
#define LUA_OUTMSG   1  // 本方系统发给Partner的消息

	// Function name   : LuaC_CheckFIXMsg
	// Description     : 通过Lua脚本去检查并更新相应的fix字段
	// Return type     : int ：int > 0 做了修改，否则没有做修改
   // Argument : CFIXData* pfixdata [INOUT]: 被检查的FIX消息体
   // Argument : int iInOut [IN]: LUA_INMSG or LUA_OUTMSG
	int LuaC_CheckFIXMsg(CFIXData* pfixdata, int iInOut);

	static int Lua_FIXDataDebugString(lua_State* L);

private:

	static const struct luaL_Reg FIXLib [];
	lua_State* L;
};
