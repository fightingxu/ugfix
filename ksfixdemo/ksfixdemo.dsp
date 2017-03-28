# Microsoft Developer Studio Project File - Name="ksfixdemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ksfixdemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ksfixdemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ksfixdemo.mak" CFG="ksfixdemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ksfixdemo - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ksfixdemo - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ksfixdemo - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../buinc" /I "../ksfix" /I "../xinc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ksfixdemo - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../buinc" /I "../ksfix" /I "../xinc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib  kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ksfixdemo - Win32 Release"
# Name "ksfixdemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\ksfix\FIXAppData.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\fixbase.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\FIXData.cpp
# End Source File
# Begin Source File

SOURCE=..\ksfix\FIXLinkThread.cpp
# End Source File
# Begin Source File

SOURCE=..\ksfix\FIXSession.cpp
# End Source File
# Begin Source File

SOURCE=..\ksfix\ksfix.cpp
# End Source File
# Begin Source File

SOURCE=.\ksfixdemo.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\logfile.cpp
# End Source File
# Begin Source File

SOURCE=..\ugate\MsgDataList.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\mypub.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\tcp.cpp
# End Source File
# Begin Source File

SOURCE=..\bupub\WThread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\ksfix\FIXAppData.h
# End Source File
# Begin Source File

SOURCE=..\buinc\fixbase.h
# End Source File
# Begin Source File

SOURCE=..\buinc\FIXData.h
# End Source File
# Begin Source File

SOURCE=..\ksfix\FIXFileStore.h
# End Source File
# Begin Source File

SOURCE=..\ksfix\FIXLinkThread.h
# End Source File
# Begin Source File

SOURCE=..\ksfix\FIXSession.h
# End Source File
# Begin Source File

SOURCE=..\ksfix\ksfix.h
# End Source File
# Begin Source File

SOURCE=..\buinc\logfile.h
# End Source File
# Begin Source File

SOURCE=..\buinc\mutex.h
# End Source File
# Begin Source File

SOURCE=..\buinc\mypub.h
# End Source File
# Begin Source File

SOURCE=..\buinc\stdafx.h
# End Source File
# Begin Source File

SOURCE=..\buinc\tcp.h
# End Source File
# Begin Source File

SOURCE=..\buinc\WThread.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
