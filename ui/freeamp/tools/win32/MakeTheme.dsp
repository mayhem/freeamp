# Microsoft Developer Studio Project File - Name="MakeTheme" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=MakeTheme - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MakeTheme.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MakeTheme.mak" CFG="MakeTheme - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MakeTheme - Win32 Release" (based on\
 "Win32 (x86) Console Application")
!MESSAGE "MakeTheme - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MakeTheme - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "MakeTheme - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /I "../../include" /I "../../../../lib/zlib/include" /I "../../../../config" /I "../../../../base/include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MakeTheme - Win32 Release"
# Name "MakeTheme - Win32 Debug"
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\adler32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\compress.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\crc32.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\deflate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\gzio.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\infblock.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\infcodes.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\inffast.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\inflate.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\inftrees.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\infutil.c
# End Source File
# Begin Source File

SOURCE=..\src\MakeTheme.cpp
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\DevStudio\VC\lib\SETARGV.OBJ"
# End Source File
# Begin Source File

SOURCE=..\..\src\ThemeZip.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\trees.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\uncompr.c
# End Source File
# Begin Source File

SOURCE=..\..\..\..\lib\zlib\src\zutil.c
# End Source File
# End Target
# End Project