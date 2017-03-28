#include "stdafx.h"
#include "LuaFIX.h"
#include "FIXData.h"
#ifdef _MSC_VER
#pragma comment(lib, "lua5.1.lib")
#endif

#define FD_INVALIDHANDLE   -1000
#define FD_SETDATAERR      -1001

//lua_State* CLuaFIX::L = NULL;
const struct luaL_Reg CLuaFIX::FIXLib [] = { 
	{"FIXDataNew", CLuaFIX::Lua_FIXDataNew},
	{"FIXDataDelete", CLuaFIX::Lua_FIXDataDelete},
	{"FIXDataReset", CLuaFIX::Lua_FIXDataReset},
	{"FIXDataSetData", CLuaFIX::Lua_FIXDataSetData},
	{"FIXDataAddTag", CLuaFIX::Lua_FIXDataAddTag},
	{"FIXDataGetTagCount", CLuaFIX::Lua_FIXDataGetTagCount},
	{"FIXDataGetTagNo", CLuaFIX::Lua_FIXDataGetTagNo},
	{"FIXDataGetTag", CLuaFIX::Lua_FIXDataGetTag},
	{"FIXDataGetTagNext", CLuaFIX::Lua_FIXDataGetTagNext},
	{"FIXDataGetGroupTagNext", CLuaFIX::Lua_FIXDataGetGroupTagNext},
	{"FIXDataUpdateTag", CLuaFIX::Lua_FIXDataUpdateTag},
	{"FIXDataGetFIXData", CLuaFIX::Lua_FIXDataGetFIXData},
	{"FIXDataRemoveTagNo", CLuaFIX::Lua_FIXDataRemoveTagNo},
	{"FIXDataRemoveTag", CLuaFIX::Lua_FIXDataRemoveTag},
	{"FIXDataGetStdFIXMessage", CLuaFIX::Lua_GetStdFIXMessage},
	{"FIXDataDebugString", CLuaFIX::Lua_FIXDataDebugString},
	{NULL, NULL}  /* sentinel */ 
};

CLuaFIX::CLuaFIX(void)
{
   L=NULL;
}

CLuaFIX::~CLuaFIX(void)
{
   LuaC_Close();
}

int CLuaFIX::LuaC_Open(const char *partner)
{
   LuaC_Close();
   if (partner==NULL || partner[0]=='\0')
      return(-2);
	L = lua_open();
	luaL_openlibs(L);
	luaL_openlib(L, "FIXLib", FIXLib, 0);

	luaopen_base(L);
	luaopen_table(L);
	lua_pushcfunction(L, luaopen_io);
	lua_pushstring(L, LUA_IOLIBNAME);
	lua_call(L, 1, 0); 
	luaopen_string(L);
	luaopen_math(L);

	if (luaL_dofile(L,partner)!=0)
   {
      LuaC_Close();
      return(-1);
   }
   return(0);
}

int CLuaFIX::Lua_FIXDataNew( lua_State* L )
{
	 CFIXData *pFIXData = new CFIXData;
	 lua_pushinteger(L, (lua_Integer)pFIXData);
	 return 1;
}

int CLuaFIX::Lua_FIXDataDelete( lua_State* L )
{
	int nNumber = lua_gettop(L);
	if (nNumber != 1)
		return 0;

	CFIXData* pFixData = (CFIXData*)lua_tointeger(L, 1);
	if (pFixData != NULL)
		delete pFixData;

	return 0;
}

int CLuaFIX::Lua_FIXDataReset( lua_State* L )
{
	int nNumber = lua_gettop(L);
   const char * sBeginString=NULL;
   const char * sSenderCompID=NULL;
   const char * sTargetCompID=NULL;
	if (nNumber <1 ) // 需要有四个参数 FIXDATAHANDLE h,const char *sBeginString,const char *sSenderCompID,const char *sTargetCompID
		return 0;
   if (nNumber > 1)
      sBeginString = lua_tostring(L, 2);
   if (nNumber > 2)
      sSenderCompID = lua_tostring(L, 3);
   if (nNumber > 3)
      sTargetCompID = lua_tostring(L, 4);


	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	int nResult = pfixdata->Reset(sBeginString, sSenderCompID, sTargetCompID);

	lua_pushinteger(L, nResult);
	return 1;
}

int CLuaFIX::Lua_FIXDataSetData( lua_State* L )
{
	int nNumber = lua_gettop(L);
	if (nNumber < 2) // 需要有三个参数 FIXDATAHANDLE h,const char *fixdata, int length
		return 0;
   int nLength;
   CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
   
   if (pfixdata == NULL)
   {
      lua_pushinteger(L, FD_INVALIDHANDLE);
      return 1;
   }
   
   const char* pstrData = lua_tostring(L, 2);

   if (nNumber < 3)
      nLength = 0;
   else
      nLength = lua_tointeger(L, 3);
   if (nLength <= 0)
      nLength = strlen(pstrData);   

	if (pfixdata->SetData(pstrData, nLength))
		lua_pushinteger(L, 1);
	else lua_pushinteger(L, FD_SETDATAERR);

	return 1;
}

int CLuaFIX::Lua_FIXDataAddTag( lua_State* L )
{
	int nNumber = lua_gettop(L);
	if (nNumber < 3) // 需要四个参数 FIXDATAHANDLE h,int tag, const char *tvalue, int vlen
		return 0;
   int vlen;
   if (nNumber <4)
      vlen = -1;
   else
      vlen = lua_tointeger(L, 4);


	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int nResult = pfixdata->AddTag(lua_tointeger(L, 2), lua_tostring(L, 3), vlen);
	lua_pushinteger(L, nResult);
	return 1;
}

int CLuaFIX::Lua_FIXDataGetTagCount( lua_State* L )
{
	int nNumber = lua_gettop(L);
	if (nNumber != 1) // 需要一个参数FIXDATAHANDLE h
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int nResult = pfixdata->GetTagCount();
	lua_pushinteger(L, nResult);
	return 1;
}

int CLuaFIX::Lua_FIXDataGetTagNo( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 2) // 需要两个参数
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int tag_no = lua_tointeger(L, 2);
	int tag, vlen;
	char buffer[10240] = {0};
	int nResult = pfixdata->GetTag(tag_no, tag, buffer, vlen);

	lua_pushinteger(L, nResult); // 首先返回C函数返回值
	lua_pushinteger(L, tag);
	lua_pushstring(L, buffer);
	lua_pushinteger(L, vlen);
	return 4;
}

int CLuaFIX::Lua_FIXDataGetTag( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 2) // 需要两个参数
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int tag = lua_tointeger(L, 2);
	char buffer[10240] = {0};
	int vlen=sizeof(buffer);
	int nResult = pfixdata->GetTag(tag, buffer, vlen);
	lua_pushinteger(L, nResult); // 首先放个C函数返回值
	lua_pushstring(L, buffer);
	lua_pushinteger(L, vlen);

	return 3;

}

int CLuaFIX::Lua_FIXDataGetTagNext( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 3) // 需要三个参数FIXDATAHANDLE h, int tag_no0, int tag
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int tag_no0 = lua_tointeger(L, 2);
	int tag = lua_tointeger(L, 3);

	char tvalue[10240] = {0};
	int vlen = 0;
	int nResult = pfixdata->GetTagNext(tag_no0, tag, tvalue, vlen);
	lua_pushinteger(L, nResult);
	lua_pushstring(L, tvalue);
	lua_pushinteger(L, vlen);

	return 3;
}

int CLuaFIX::Lua_FIXDataGetGroupTagNext( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 3) // 需要四个参数FIXDATAHANDLE h, int tag_no0, int tag, int no
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}
	int tag_no0 = lua_tointeger(L, 2);
	int tag = lua_tointeger(L, 3);
	int no = lua_tointeger(L, 4);

	char tvalue[10240] = {0};
	int vlen = 0;
	int nResult = pfixdata->GetGroupTagNext(tag_no0, tag, no, tvalue, vlen);
	lua_pushinteger(L, nResult);
	lua_pushstring(L, tvalue);
	lua_pushinteger(L, vlen);
	return 3;
}

int CLuaFIX::Lua_FIXDataUpdateTag( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber < 4) // 需要四个参数FIXDATAHANDLE h, int tag_no, int tag, const char *tvalue, int tvlen
		return 0;  // 无法执行:(
   int tvlen;
   if (nNumber < 5)
      tvlen = -1;
   else
      tvlen = lua_tointeger(L, 5);

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int nResult = pfixdata->UpdateTag(lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tostring(L, 4), tvlen);
	lua_pushinteger(L, nResult);
	return 1;
}

int CLuaFIX::Lua_FIXDataGetFIXData( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 1) // 需要一个参数FIXDATAHANDLE h
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}
	char fixdata[10240] = {0};
	int nResult = pfixdata->GetFIXData(fixdata, sizeof(fixdata) - 1);
	lua_pushinteger(L, nResult);
	lua_pushstring(L, fixdata);
	return 2;
}

int CLuaFIX::Lua_FIXDataRemoveTagNo( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 2) // 需要一个参数FIXDATAHANDLE h, int tag_no
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	int nResult = pfixdata->RemoveTagNo(lua_tointeger(L, 2));
	lua_pushinteger(L, nResult);
	return 1;
}

int CLuaFIX::Lua_FIXDataRemoveTag( lua_State* L )
{
	int nNumber =  lua_gettop(L);
	if (nNumber != 2) // 需要一个参数FIXDATAHANDLE h, int tag
		return 0;

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}
	int nResult = pfixdata->RemoveTag(lua_tointeger(L, 2));
	lua_pushinteger(L, nResult);
	return 1;
}

int CLuaFIX::Lua_GetStdFIXMessage( lua_State* L )
{
	int nNumber = lua_gettop(L);
   const char *sBeginString=NULL;
	if (nNumber < 1) // 需要两个参数FIXDATAHANDLE h, begginString(可选参数)
		return 0;
   if (nNumber > 1)
      sBeginString = lua_tostring(L,2);

	CFIXData* pfixdata = (CFIXData*)lua_tointeger(L, 1);
	if (pfixdata == NULL)
	{
		lua_pushinteger(L, FD_INVALIDHANDLE);
		return 1;
	}

	char fixdata[10240] = {0};
	int nResult = pfixdata->GetStdFIXMessage(fixdata, sizeof(fixdata) - 1, sBeginString);
	lua_pushinteger(L, nResult);
	lua_pushstring(L, fixdata);
	return 2;
}

int CLuaFIX::LuaC_CheckFIXMsg( CFIXData* pfixdata, int iInOut )
{
   if (L==NULL)
      return(0);
   if (iInOut==LUA_INMSG)
   	lua_getglobal(L, "CheckInFIXMsg");
   else
      lua_getglobal(L, "CheckOutFIXMsg");
	lua_pushinteger(L, (lua_Integer)pfixdata);
	int n = lua_pcall(L, 1, 1, 0);

// 	int nNumber = lua_gettop(L);
// 	const char* pBuffer = NULL;
// 	for (int i = 0; i < nNumber; i++)
// 	{
// 		pBuffer = lua_tostring(L, i + 1);
// 	}
// 	if (nNumber >= 1)
// 		return lua_tointeger(L, 1);

	return 0;
}

int CLuaFIX::Lua_FIXDataDebugString( lua_State* L )
{
	printf(lua_tostring(L, 1));
	return 0;
}

void CLuaFIX::LuaC_Close()
{
   if (L!=NULL)
   {
      lua_close(L);
      L = NULL;      
   }
}
