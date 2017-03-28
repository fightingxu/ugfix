# Microsoft Developer Studio Project File - Name="ugbase" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ugbase - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ugbase.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ugbase.mak" CFG="ugbase - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ugbase - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ugbase - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ugbase - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./" /I "../xinc" /I "../buinc" /I "C:\Program Files\Lua\5.1\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ugbase_r.lib"

!ELSEIF  "$(CFG)" == "ugbase - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./" /I "../xinc" /I "../buinc" /I "C:\Program Files\Lua\5.1\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\lib\ugbase_d.lib"

!ENDIF 

# Begin Target

# Name "ugbase - Win32 Release"
# Name "ugbase - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "buinc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\buinc\bdefine.h
# End Source File
# Begin Source File

SOURCE=..\buinc\bupub.h
# End Source File
# Begin Source File

SOURCE=..\buinc\BUSem.h
# End Source File
# Begin Source File

SOURCE=..\buinc\BUShm.h
# End Source File
# Begin Source File

SOURCE=..\buinc\comstru.h
# End Source File
# Begin Source File

SOURCE=..\buinc\cpack.h
# End Source File
# Begin Source File

SOURCE=..\buinc\cxpack.h
# End Source File
# Begin Source File

SOURCE=..\buinc\FIXData.h
# End Source File
# Begin Source File

SOURCE=..\buinc\logfile.h
# End Source File
# Begin Source File

SOURCE=..\buinc\MemQueue.h
# End Source File
# Begin Source File

SOURCE=..\buinc\MsgQueue.h
# End Source File
# Begin Source File

SOURCE=..\buinc\mutex.h
# End Source File
# Begin Source File

SOURCE=..\buinc\mypub.h
# End Source File
# Begin Source File

SOURCE=..\buinc\PackB.h
# End Source File
# Begin Source File

SOURCE=..\buinc\PackC.h
# End Source File
# Begin Source File

SOURCE=..\buinc\PackHandle.h
# End Source File
# Begin Source File

SOURCE=..\buinc\profile.h
# End Source File
# Begin Source File

SOURCE=..\buinc\rbtr.h
# End Source File
# Begin Source File

SOURCE=..\buinc\slist.h
# End Source File
# Begin Source File

SOURCE=..\buinc\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\buinc\svrlink.h
# End Source File
# Begin Source File

SOURCE=..\buinc\tcp.h
# End Source File
# Begin Source File

SOURCE=..\buinc\WThread.h
# End Source File
# Begin Source File

SOURCE=..\buinc\XPack.h
# End Source File
# End Group
# Begin Group "bupub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bupub\bdefine.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\bupub.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\BUSem.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\BUShm.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\fixbase.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\FIXData.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\logfile.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\MemQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\MsgQueue.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\mypub.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\profile.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\slist.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\svrlink.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\tcp.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\WThread.cpp
# End Source File
# End Group
# Begin Group "ugate"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\ugate\LuaFIX.cpp
# End Source File
# Begin Source File

SOURCE=..\ugate\LuaFIX.h
# End Source File
# Begin Source File

SOURCE=..\ugate\MsgDataList.cpp
# End Source File
# Begin Source File

SOURCE=..\ugate\ugate.cpp
# End Source File
# Begin Source File

SOURCE=..\ugate\UGateManage.cpp
# End Source File
# Begin Source File

SOURCE=..\ugate\UGateManage.h
# End Source File
# Begin Source File

SOURCE=..\ugate\UGChannel.cpp
# End Source File
# Begin Source File

SOURCE=..\ugate\UGChannel.h
# End Source File
# End Group
# Begin Group "xinc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\xinc\fixbase.h
# End Source File
# Begin Source File

SOURCE=..\xinc\MsgDataList.h
# End Source File
# Begin Source File

SOURCE=..\xinc\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\xinc\UDLInterface.h
# End Source File
# Begin Source File

SOURCE=..\xinc\ugate.h
# End Source File
# Begin Source File

SOURCE=..\xinc\xpub.h
# End Source File
# End Group
# End Target
# End Project
