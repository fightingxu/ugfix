# Microsoft Developer Studio Project File - Name="ugcts" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ugcts - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ugcts.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ugcts.mak" CFG="ugcts - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ugcts - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ugcts - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ugcts - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I "./" /I "../xinc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 ugbase_r.lib bccsvr.lib bccclt.lib XPack.lib ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "ugcts - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "./" /I "../xinc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ugbase_d.lib bccsvr.lib bccclt.lib XPack.lib ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "ugcts - Win32 Release"
# Name "ugcts - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\ksugbu\ksugbu.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
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
# Begin Group "kscts"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\busqc.h
# End Source File
# Begin Source File

SOURCE=.\CJThread.cpp
# End Source File
# Begin Source File

SOURCE=.\CJThread.h
# End Source File
# Begin Source File

SOURCE=.\DRTPData.cpp
# End Source File
# Begin Source File

SOURCE=.\DRTPData.h
# End Source File
# Begin Source File

SOURCE=.\InThread.cpp
# End Source File
# Begin Source File

SOURCE=.\InThread.h
# End Source File
# Begin Source File

SOURCE=.\KSCTS.cpp
# End Source File
# Begin Source File

SOURCE=.\KSCTS.h
# End Source File
# Begin Source File

SOURCE=.\nbccclt.h
# End Source File
# Begin Source File

SOURCE=.\nbccsvr.h
# End Source File
# Begin Source File

SOURCE=.\OutThread.cpp
# End Source File
# Begin Source File

SOURCE=.\OutThread.h
# End Source File
# Begin Source File

SOURCE=.\ugcts2di.cxx
# End Source File
# Begin Source File

SOURCE=.\ugcts2di.hxx
# End Source File
# Begin Source File

SOURCE=.\ugdb2di.cxx
# End Source File
# Begin Source File

SOURCE=.\UGDBFuncs.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\hwgsdm.txt
# End Source File
# Begin Source File

SOURCE=.\ugate.ini
# End Source File
# Begin Source File

SOURCE=.\ugcts.txt
# End Source File
# End Target
# End Project
