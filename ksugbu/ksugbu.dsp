# Microsoft Developer Studio Project File - Name="ksugbu" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ksugbu - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ksugbu.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ksugbu.mak" CFG="ksugbu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ksugbu - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ksugbu - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ksugbu - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./" /I "../xinc" /I "../buinc" /I "../FE/inc" /I "C:\Program Files\Java\jdk1.7.0\include\\" /I "C:\Program Files\Java\jdk1.7.0\include\win32" /I "C:\Program Files (x86)\Lua\5.1\include" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"Release/ugate.exe" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "ksugbu - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./" /I "../xinc" /I "../buinc" /I "../FE/inc" /I "C:\Program Files\Java\jdk1.7.0\include\\" /I "C:\Program Files\Java\jdk1.7.0\include\win32" /I "C:\Program Files (x86)\Lua\5.1\include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug/ugate.exe" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "ksugbu - Win32 Release"
# Name "ksugbu - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ksugbu.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
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

SOURCE=..\bupub\dbf.cpp
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

SOURCE=..\bupub\stdafx.cpp
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

SOURCE=..\buinc\dbf.h
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
# Begin Group "FE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\FE\APIListener.cpp
# End Source File
# Begin Source File

SOURCE=..\FE\inc\APIListener.h
# End Source File
# Begin Source File

SOURCE=..\FE\FIXEngine.cpp
# End Source File
# Begin Source File

SOURCE=..\FE\inc\FIXEngine.h
# End Source File
# Begin Source File

SOURCE=..\FE\FIXSession.cpp
# End Source File
# Begin Source File

SOURCE=..\FE\inc\FIXSession.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ugate.ini
# End Source File
# Begin Source File

SOURCE=..\lib\XPack.lib
# End Source File
# Begin Source File

SOURCE=..\FE\fixengineR.lib
# End Source File
# End Target
# End Project
