# Microsoft Developer Studio Generated NMAKE File, Based on freeamp.dsp
!IF "$(CFG)" == ""
CFG=freeamp - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to freeamp - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "freeamp - Win32 Release" && "$(CFG)" !=\
 "freeamp - Win32 Debug" && "$(CFG)" != "freeamp - Win32 NASM Release" &&\
 "$(CFG)" != "freeamp - Win32 NASM Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "freeamp.mak" CFG="freeamp - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "freeamp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "freeamp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "freeamp - Win32 NASM Release" (based on "Win32 (x86) Application")
!MESSAGE "freeamp - Win32 NASM Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "freeamp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\portio.sys" "..\..\..\ReadMe.txt" "..\..\..\Copying.txt"\
 "..\..\..\Changes.txt" "..\..\..\Authors.txt" ".\freeamp.exe"

!ELSE 

ALL : "gdbm - Win32 Release" "dsoundcard - Win32 Release"\
 "simple - Win32 Release" "obsinput - Win32 Release" "httpinput - Win32 Release"\
 "freeampui - Win32 Release" "xing - Win32 Release" "soundcard - Win32 Release"\
 "fileinput - Win32 Release" ".\portio.sys" "..\..\..\ReadMe.txt"\
 "..\..\..\Copying.txt" "..\..\..\Changes.txt" "..\..\..\Authors.txt"\
 ".\freeamp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fileinput - Win32 ReleaseCLEAN" "soundcard - Win32 ReleaseCLEAN"\
 "xing - Win32 ReleaseCLEAN" "freeampui - Win32 ReleaseCLEAN"\
 "httpinput - Win32 ReleaseCLEAN" "obsinput - Win32 ReleaseCLEAN"\
 "simple - Win32 ReleaseCLEAN" "dsoundcard - Win32 ReleaseCLEAN"\
 "gdbm - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\freeamp.res"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\musicsearch.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\player.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\propimpl.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\rio.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase ".\freeamp.exe"
	-@erase "..\..\..\Authors.txt"
	-@erase "..\..\..\Changes.txt"
	-@erase "..\..\..\Copying.txt"
	-@erase "..\..\..\ReadMe.txt"
	-@erase ".\portio.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\..\lib\gdbm" /I\
 "..\include" /I "..\..\include" /I "..\..\..\config" /I\
 "..\..\..\ui\win32Test\include" /I "..\..\..\ui\win32Test\res" /I\
 "..\..\..\io\include" /I "..\..\..\ui\include" /I "..\..\..\lmc\include" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\freeamp.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeamp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib winmm.lib wsock32.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\freeamp.pdb" /machine:I386 /out:"freeamp.exe"\
 /libpath:"..\..\..\lib\gdbm" 
LINK32_OBJS= \
	"$(INTDIR)\freeamp.res" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\musicsearch.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\player.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\propimpl.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\rio.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"..\..\..\io\dsound\win32\prj\Release\dsoundcard.lib" \
	"..\..\..\io\http\win32\prj\Release\httpinput.lib" \
	"..\..\..\io\local\win32\prj\Release\fileinput.lib" \
	"..\..\..\io\obs\win32\prj\Release\obsinput.lib" \
	"..\..\..\io\soundcard\win32\prj\Release\soundcard.lib" \
	"..\..\..\lib\gdbm\gdbm.lib" \
	"..\..\..\lmc\xingmp3\win32\prj\Release\xing.lib" \
	"..\..\..\ui\freeamp\win32\prj\Release\freeamp.lib" \
	"..\..\..\ui\simple\win32\prj\Release\simple.lib"

".\freeamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\portio.sys" "..\..\..\ReadMe.txt" "..\..\..\Copying.txt"\
 "..\..\..\Changes.txt" "..\..\..\Authors.txt" ".\freeamp.exe"

!ELSE 

ALL : "gdbm - Win32 Debug" "dsoundcard - Win32 Debug" "simple - Win32 Debug"\
 "obsinput - Win32 Debug" "httpinput - Win32 Debug" "freeampui - Win32 Debug"\
 "xing - Win32 Debug" "soundcard - Win32 Debug" "fileinput - Win32 Debug"\
 ".\portio.sys" "..\..\..\ReadMe.txt" "..\..\..\Copying.txt"\
 "..\..\..\Changes.txt" "..\..\..\Authors.txt" ".\freeamp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fileinput - Win32 DebugCLEAN" "soundcard - Win32 DebugCLEAN"\
 "xing - Win32 DebugCLEAN" "freeampui - Win32 DebugCLEAN"\
 "httpinput - Win32 DebugCLEAN" "obsinput - Win32 DebugCLEAN"\
 "simple - Win32 DebugCLEAN" "dsoundcard - Win32 DebugCLEAN"\
 "gdbm - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\freeamp.res"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\musicsearch.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\player.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\propimpl.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\rio.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\freeamp.pdb"
	-@erase ".\freeamp.exe"
	-@erase ".\freeamp.ilk"
	-@erase "..\..\..\Authors.txt"
	-@erase "..\..\..\Changes.txt"
	-@erase "..\..\..\Copying.txt"
	-@erase "..\..\..\ReadMe.txt"
	-@erase ".\portio.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\lib\gdbm" /I\
 "..\include" /I "..\..\include" /I "..\..\..\config" /I\
 "..\..\..\ui\win32Test\include" /I "..\..\..\ui\win32Test\res" /I\
 "..\..\..\io\include" /I "..\..\..\ui\include" /I "..\..\..\lmc\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\freeamp.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeamp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib winmm.lib wsock32.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\freeamp.pdb" /debug /machine:I386 /out:"freeamp.exe"\
 /pdbtype:sept /libpath:"..\..\..\lib\gdbm" 
LINK32_OBJS= \
	"$(INTDIR)\freeamp.res" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\musicsearch.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\player.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\propimpl.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\rio.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"..\..\..\io\dsound\win32\prj\Debug\dsoundcard.lib" \
	"..\..\..\io\http\win32\prj\Debug\httpinput.lib" \
	"..\..\..\io\local\win32\prj\Debug\fileinput.lib" \
	"..\..\..\io\obs\win32\prj\Debug\obsinput.lib" \
	"..\..\..\io\soundcard\win32\prj\Debug\soundcard.lib" \
	"..\..\..\lib\gdbm\gdbm.lib" \
	"..\..\..\lmc\xingmp3\win32\prj\Debug\xing.lib" \
	"..\..\..\ui\freeamp\win32\prj\Debug\freeamp.lib" \
	"..\..\..\ui\simple\win32\prj\Debug\simple.lib"

".\freeamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\portio.sys" "..\..\..\ReadMe.txt" "..\..\..\Copying.txt"\
 "..\..\..\Changes.txt" "..\..\..\Authors.txt" ".\freeamp.exe"

!ELSE 

ALL : "gdbm - Win32 NASM Release" "dsoundcard - Win32 NASM Release"\
 "simple - Win32 NASM Release" "obsinput - Win32 NASM Release"\
 "httpinput - Win32 NASM Release" "freeampui - Win32 NASM Release"\
 "xing - Win32 NASM Release" "soundcard - Win32 NASM Release"\
 "fileinput - Win32 NASM Release" ".\portio.sys" "..\..\..\ReadMe.txt"\
 "..\..\..\Copying.txt" "..\..\..\Changes.txt" "..\..\..\Authors.txt"\
 ".\freeamp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fileinput - Win32 NASM ReleaseCLEAN"\
 "soundcard - Win32 NASM ReleaseCLEAN" "xing - Win32 NASM ReleaseCLEAN"\
 "freeampui - Win32 NASM ReleaseCLEAN" "httpinput - Win32 NASM ReleaseCLEAN"\
 "obsinput - Win32 NASM ReleaseCLEAN" "simple - Win32 NASM ReleaseCLEAN"\
 "dsoundcard - Win32 NASM ReleaseCLEAN" "gdbm - Win32 NASM ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\freeamp.res"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\musicsearch.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\player.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\propimpl.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\rio.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase ".\freeamp.exe"
	-@erase "..\..\..\Authors.txt"
	-@erase "..\..\..\Changes.txt"
	-@erase "..\..\..\Copying.txt"
	-@erase "..\..\..\ReadMe.txt"
	-@erase ".\portio.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\..\lib\gdbm" /I\
 "..\include" /I "..\..\include" /I "..\..\..\config" /I\
 "..\..\..\ui\win32Test\include" /I "..\..\..\ui\win32Test\res" /I\
 "..\..\..\io\include" /I "..\..\..\ui\include" /I "..\..\..\lmc\include" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\freeamp.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeamp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib winmm.lib wsock32.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\freeamp.pdb" /machine:I386 /out:"freeamp.exe"\
 /libpath:"..\..\..\lib\gdbm" 
LINK32_OBJS= \
	"$(INTDIR)\freeamp.res" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\musicsearch.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\player.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\propimpl.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\rio.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"..\..\..\io\dsound\win32\prj\Release\dsoundcard.lib" \
	"..\..\..\io\http\win32\prj\Release\httpinput.lib" \
	"..\..\..\io\local\win32\prj\Release\fileinput.lib" \
	"..\..\..\io\obs\win32\prj\Release\obsinput.lib" \
	"..\..\..\io\soundcard\win32\prj\Release\soundcard.lib" \
	"..\..\..\lib\gdbm\gdbm.lib" \
	"..\..\..\lmc\xingmp3\win32\prj\Release\xing.lib" \
	"..\..\..\ui\freeamp\win32\prj\Release\freeamp.lib" \
	"..\..\..\ui\simple\win32\prj\Release\simple.lib"

".\freeamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\portio.sys" "..\..\..\ReadMe.txt" "..\..\..\Copying.txt"\
 "..\..\..\Changes.txt" "..\..\..\Authors.txt" ".\freeamp.exe"

!ELSE 

ALL : "gdbm - Win32 NASM Debug" "dsoundcard - Win32 NASM Debug"\
 "simple - Win32 NASM Debug" "obsinput - Win32 NASM Debug"\
 "httpinput - Win32 NASM Debug" "freeampui - Win32 NASM Debug"\
 "xing - Win32 NASM Debug" "soundcard - Win32 NASM Debug"\
 "fileinput - Win32 NASM Debug" ".\portio.sys" "..\..\..\ReadMe.txt"\
 "..\..\..\Copying.txt" "..\..\..\Changes.txt" "..\..\..\Authors.txt"\
 ".\freeamp.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fileinput - Win32 NASM DebugCLEAN" "soundcard - Win32 NASM DebugCLEAN"\
 "xing - Win32 NASM DebugCLEAN" "freeampui - Win32 NASM DebugCLEAN"\
 "httpinput - Win32 NASM DebugCLEAN" "obsinput - Win32 NASM DebugCLEAN"\
 "simple - Win32 NASM DebugCLEAN" "dsoundcard - Win32 NASM DebugCLEAN"\
 "gdbm - Win32 NASM DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\freeamp.res"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\musicsearch.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\player.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\propimpl.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\rio.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\freeamp.pdb"
	-@erase ".\freeamp.exe"
	-@erase ".\freeamp.ilk"
	-@erase "..\..\..\Authors.txt"
	-@erase "..\..\..\Changes.txt"
	-@erase "..\..\..\Copying.txt"
	-@erase "..\..\..\ReadMe.txt"
	-@erase ".\portio.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\..\lib\gdbm" /I\
 "..\include" /I "..\..\include" /I "..\..\..\config" /I\
 "..\..\..\ui\win32Test\include" /I "..\..\..\ui\win32Test\res" /I\
 "..\..\..\io\include" /I "..\..\..\ui\include" /I "..\..\..\lmc\include" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\freeamp.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeamp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeamp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib winmm.lib wsock32.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\freeamp.pdb" /debug /machine:I386 /out:"freeamp.exe"\
 /pdbtype:sept /libpath:"..\..\..\lib\gdbm" 
LINK32_OBJS= \
	"$(INTDIR)\freeamp.res" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\musicsearch.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\player.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\propimpl.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\rio.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"..\..\..\io\dsound\win32\prj\Debug\dsoundcard.lib" \
	"..\..\..\io\http\win32\prj\Debug\httpinput.lib" \
	"..\..\..\io\local\win32\prj\Debug\fileinput.lib" \
	"..\..\..\io\obs\win32\prj\Debug\obsinput.lib" \
	"..\..\..\io\soundcard\win32\prj\Debug\soundcard.lib" \
	"..\..\..\lib\gdbm\gdbm.lib" \
	"..\..\..\lmc\xingmp3\win32\prj\Debug\xing.lib" \
	"..\..\..\ui\freeamp\win32\prj\Debug\freeamp.lib" \
	"..\..\..\ui\simple\win32\prj\Debug\simple.lib"

".\freeamp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "freeamp - Win32 Release" || "$(CFG)" ==\
 "freeamp - Win32 Debug" || "$(CFG)" == "freeamp - Win32 NASM Release" ||\
 "$(CFG)" == "freeamp - Win32 NASM Debug"
SOURCE=..\..\src\log.cpp
DEP_CPP_LOG_C=\
	"..\..\include\log.h"\
	

"$(INTDIR)\log.obj" : $(SOURCE) $(DEP_CPP_LOG_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\main.cpp
DEP_CPP_MAIN_=\
	"..\..\..\io\include\pipeline.h"\
	"..\..\..\io\include\pullbuffer.h"\
	"..\..\..\lib\gdbm\gdbm.h"\
	"..\..\..\lmc\include\lmc.h"\
	"..\..\..\ui\include\ui.h"\
	"..\..\include\database.h"\
	"..\..\include\errors.h"\
	"..\..\include\event.h"\
	"..\..\include\eventdata.h"\
	"..\..\include\facontext.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\id3v1.h"\
	"..\..\include\log.h"\
	"..\..\include\metadata.h"\
	"..\..\include\musicsearch.h"\
	"..\..\include\player.h"\
	"..\..\include\playlist.h"\
	"..\..\include\playlistformat.h"\
	"..\..\include\portabledevice.h"\
	"..\..\include\preferences.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\..\include\queue.h"\
	"..\..\include\registrar.h"\
	"..\..\include\registry.h"\
	"..\..\include\thread.h"\
	"..\include\mutex.h"\
	"..\include\semaphore.h"\
	"..\include\win32prefs.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_MAIN_=\
	"..\..\..\config\config.h"\
	"..\..\include\win32impl.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\musicsearch.cpp
DEP_CPP_MUSIC=\
	"..\..\..\io\include\pipeline.h"\
	"..\..\..\io\include\pullbuffer.h"\
	"..\..\..\lib\gdbm\gdbm.h"\
	"..\..\..\lmc\include\lmc.h"\
	"..\..\..\ui\include\ui.h"\
	"..\..\include\database.h"\
	"..\..\include\errors.h"\
	"..\..\include\event.h"\
	"..\..\include\eventdata.h"\
	"..\..\include\facontext.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\id3v1.h"\
	"..\..\include\log.h"\
	"..\..\include\metadata.h"\
	"..\..\include\musicsearch.h"\
	"..\..\include\player.h"\
	"..\..\include\playlist.h"\
	"..\..\include\playlistformat.h"\
	"..\..\include\portabledevice.h"\
	"..\..\include\preferences.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\..\include\queue.h"\
	"..\..\include\registry.h"\
	"..\..\include\thread.h"\
	"..\include\mutex.h"\
	"..\include\semaphore.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_MUSIC=\
	"..\..\..\config\config.h"\
	"..\..\src\win32impl.h"\
	

"$(INTDIR)\musicsearch.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\player.cpp
DEP_CPP_PLAYE=\
	"..\..\..\io\include\pipeline.h"\
	"..\..\..\io\include\pmi.h"\
	"..\..\..\io\include\pmo.h"\
	"..\..\..\io\include\pullbuffer.h"\
	"..\..\..\lib\gdbm\gdbm.h"\
	"..\..\..\lmc\include\lmc.h"\
	"..\..\..\ui\include\ui.h"\
	"..\..\include\database.h"\
	"..\..\include\debug.h"\
	"..\..\include\errors.h"\
	"..\..\include\event.h"\
	"..\..\include\eventdata.h"\
	"..\..\include\facontext.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\id3v1.h"\
	"..\..\include\log.h"\
	"..\..\include\metadata.h"\
	"..\..\include\musicsearch.h"\
	"..\..\include\player.h"\
	"..\..\include\playlist.h"\
	"..\..\include\playlistformat.h"\
	"..\..\include\portabledevice.h"\
	"..\..\include\preferences.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\..\include\queue.h"\
	"..\..\include\registrar.h"\
	"..\..\include\registry.h"\
	"..\..\include\thread.h"\
	"..\include\mutex.h"\
	"..\include\semaphore.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_PLAYE=\
	"..\..\..\config\config.h"\
	"..\..\include\win32impl.h"\
	

"$(INTDIR)\player.obj" : $(SOURCE) $(DEP_CPP_PLAYE) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\playlist.cpp
DEP_CPP_PLAYL=\
	"..\..\include\errors.h"\
	"..\..\include\facontext.h"\
	"..\..\include\log.h"\
	"..\..\include\metadata.h"\
	"..\..\include\playlist.h"\
	"..\..\include\playlistformat.h"\
	"..\..\include\portabledevice.h"\
	"..\..\include\preferences.h"\
	"..\..\include\registrar.h"\
	"..\..\include\registry.h"\
	"..\..\include\thread.h"\
	"..\include\mutex.h"\
	
NODEP_CPP_PLAYL=\
	"..\..\..\config\config.h"\
	"..\..\include\win32impl.h"\
	

"$(INTDIR)\playlist.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\propimpl.cpp

!IF  "$(CFG)" == "freeamp - Win32 Release"

DEP_CPP_PROPI=\
	"..\..\include\errors.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\include\mutex.h"\
	
NODEP_CPP_PROPI=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\propimpl.obj" : $(SOURCE) $(DEP_CPP_PROPI) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

DEP_CPP_PROPI=\
	"..\..\include\errors.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\include\mutex.h"\
	
NODEP_CPP_PROPI=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\propimpl.obj" : $(SOURCE) $(DEP_CPP_PROPI) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

DEP_CPP_PROPI=\
	"..\..\include\errors.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\include\mutex.h"\
	
NODEP_CPP_PROPI=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\propimpl.obj" : $(SOURCE) $(DEP_CPP_PROPI) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

DEP_CPP_PROPI=\
	"..\..\include\errors.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\properties.h"\
	"..\..\include\propimpl.h"\
	"..\include\mutex.h"\
	
NODEP_CPP_PROPI=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\propimpl.obj" : $(SOURCE) $(DEP_CPP_PROPI) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\io\rio\rio.cpp
DEP_CPP_RIO_C=\
	"..\..\..\io\include\binary.h"\
	"..\..\..\io\include\rio.h"\
	"..\..\..\io\include\rioioctl.h"\
	"..\..\..\io\include\std.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_RIO_C=\
	"..\..\..\io\rio\iopl32.h"\
	

"$(INTDIR)\rio.obj" : $(SOURCE) $(DEP_CPP_RIO_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\thread.cpp
DEP_CPP_THREA=\
	"..\..\include\thread.h"\
	"..\include\win32thread.h"\
	
NODEP_CPP_THREA=\
	"..\..\..\config\config.h"\
	"..\..\src\beosthread.h"\
	"..\..\src\linuxthread.h"\
	"..\..\src\solaristhread.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\config\config.win32

!IF  "$(CFG)" == "freeamp - Win32 Release"

InputPath=..\..\..\config\config.win32

"..\..\..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\config\config.win32 ..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

InputPath=..\..\..\config\config.win32

"..\..\..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\config\config.win32 ..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

InputPath=..\..\..\config\config.win32

"..\..\..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\config\config.win32 ..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

InputPath=..\..\..\config\config.win32

"..\..\..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\config\config.win32 ..\..\..\config\config.h

!ENDIF 

SOURCE=..\src\mutex.cpp
DEP_CPP_MUTEX=\
	"..\include\mutex.h"\
	

"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\preferences.cpp
DEP_CPP_PREFE=\
	"..\..\include\errors.h"\
	"..\..\include\preferences.h"\
	
NODEP_CPP_PREFE=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\semaphore.cpp
DEP_CPP_SEMAP=\
	"..\include\semaphore.h"\
	

"$(INTDIR)\semaphore.obj" : $(SOURCE) $(DEP_CPP_SEMAP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\win32prefs.cpp

!IF  "$(CFG)" == "freeamp - Win32 Release"

DEP_CPP_WIN32=\
	"..\..\include\errors.h"\
	"..\..\include\preferences.h"\
	"..\include\win32prefs.h"\
	
NODEP_CPP_WIN32=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

DEP_CPP_WIN32=\
	"..\..\include\errors.h"\
	"..\..\include\preferences.h"\
	"..\include\win32prefs.h"\
	
NODEP_CPP_WIN32=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

DEP_CPP_WIN32=\
	"..\..\include\errors.h"\
	"..\..\include\preferences.h"\
	"..\include\win32prefs.h"\
	
NODEP_CPP_WIN32=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

DEP_CPP_WIN32=\
	"..\..\include\errors.h"\
	"..\..\include\preferences.h"\
	"..\include\win32prefs.h"\
	
NODEP_CPP_WIN32=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\win32thread.cpp
DEP_CPP_WIN32T=\
	"..\..\include\thread.h"\
	"..\include\win32thread.h"\
	
NODEP_CPP_WIN32T=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\registrar.cpp
DEP_CPP_REGIS=\
	"..\..\include\errors.h"\
	"..\..\include\hashtable.h"\
	"..\..\include\preferences.h"\
	"..\..\include\registrar.h"\
	"..\..\include\registry.h"\
	
NODEP_CPP_REGIS=\
	"..\..\..\config\config.h"\
	"..\..\include\win32impl.h"\
	

"$(INTDIR)\registrar.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\registry.cpp
DEP_CPP_REGIST=\
	"..\..\include\registry.h"\
	
NODEP_CPP_REGIST=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\registry.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"\
 "..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\AUTHORS

!IF  "$(CFG)" == "freeamp - Win32 Release"

InputPath=..\..\..\AUTHORS

"..\..\..\Authors.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\AUTHORS ..\..\..\Authors.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

InputPath=..\..\..\AUTHORS

"..\..\..\Authors.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\AUTHORS ..\..\..\Authors.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

InputPath=..\..\..\AUTHORS

"..\..\..\Authors.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\AUTHORS ..\..\..\Authors.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

InputPath=..\..\..\AUTHORS

"..\..\..\Authors.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\AUTHORS ..\..\..\Authors.txt

!ENDIF 

SOURCE=..\..\..\CHANGES

!IF  "$(CFG)" == "freeamp - Win32 Release"

InputPath=..\..\..\CHANGES

"..\..\..\Changes.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\CHANGES ..\..\..\Changes.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

InputPath=..\..\..\CHANGES

"..\..\..\Changes.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\CHANGES ..\..\..\Changes.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

InputPath=..\..\..\CHANGES

"..\..\..\Changes.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\CHANGES ..\..\..\Changes.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

InputPath=..\..\..\CHANGES

"..\..\..\Changes.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\CHANGES ..\..\..\Changes.txt

!ENDIF 

SOURCE=..\..\..\COPYING

!IF  "$(CFG)" == "freeamp - Win32 Release"

InputPath=..\..\..\COPYING

"..\..\..\Copying.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\COPYING ..\..\..\Copying.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

InputPath=..\..\..\COPYING

"..\..\..\Copying.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\COPYING ..\..\..\Copying.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

InputPath=..\..\..\COPYING

"..\..\..\Copying.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\COPYING ..\..\..\Copying.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

InputPath=..\..\..\COPYING

"..\..\..\Copying.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\COPYING ..\..\..\Copying.txt

!ENDIF 

SOURCE=..\..\..\README

!IF  "$(CFG)" == "freeamp - Win32 Release"

InputPath=..\..\..\README

"..\..\..\ReadMe.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\README ..\..\..\ReadMe.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

InputPath=..\..\..\README

"..\..\..\ReadMe.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\README ..\..\..\ReadMe.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

InputPath=..\..\..\README

"..\..\..\ReadMe.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\README ..\..\..\ReadMe.txt

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

InputPath=..\..\..\README

"..\..\..\ReadMe.txt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\README ..\..\..\ReadMe.txt

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"fileinput - Win32 Release" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fileinput.mak CFG="fileinput - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"fileinput - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fileinput.mak\
 CFG="fileinput - Win32 Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"fileinput - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fileinput.mak CFG="fileinput - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"fileinput - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fileinput.mak CFG="fileinput - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"fileinput - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fileinput.mak\
 CFG="fileinput - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"fileinput - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fileinput.mak\
 CFG="fileinput - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"fileinput - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fileinput.mak CFG="fileinput - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"fileinput - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\local\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fileinput.mak\
 CFG="fileinput - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"soundcard - Win32 Release" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\soundcard.mak CFG="soundcard - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"soundcard - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\soundcard.mak\
 CFG="soundcard - Win32 Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"soundcard - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\soundcard.mak CFG="soundcard - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"soundcard - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\soundcard.mak CFG="soundcard - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"soundcard - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\soundcard.mak\
 CFG="soundcard - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"soundcard - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\soundcard.mak\
 CFG="soundcard - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"soundcard - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\soundcard.mak CFG="soundcard - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"soundcard - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\soundcard\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\soundcard.mak\
 CFG="soundcard - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"xing - Win32 Release" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\xing.mak CFG="xing - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"xing - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\xing.mak CFG="xing - Win32 Release"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"xing - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\xing.mak CFG="xing - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"xing - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\xing.mak CFG="xing - Win32 Debug" RECURSE=1\
 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"xing - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\xing.mak CFG="xing - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"xing - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\xing.mak CFG="xing - Win32 NASM Release"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"xing - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\xing.mak CFG="xing - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"xing - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\lmc\xingmp3\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\xing.mak CFG="xing - Win32 NASM Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"freeampui - Win32 Release" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\freeampui.mak CFG="freeampui - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"freeampui - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\freeampui.mak\
 CFG="freeampui - Win32 Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"freeampui - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\freeampui.mak CFG="freeampui - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"freeampui - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\freeampui.mak CFG="freeampui - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"freeampui - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\freeampui.mak\
 CFG="freeampui - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"freeampui - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\freeampui.mak\
 CFG="freeampui - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"freeampui - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\freeampui.mak CFG="freeampui - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"freeampui - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\freeamp\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\freeampui.mak\
 CFG="freeampui - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"httpinput - Win32 Release" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\httpinput.mak CFG="httpinput - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"httpinput - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\httpinput.mak\
 CFG="httpinput - Win32 Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"httpinput - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\httpinput.mak CFG="httpinput - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"httpinput - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\httpinput.mak CFG="httpinput - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"httpinput - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\httpinput.mak\
 CFG="httpinput - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"httpinput - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\httpinput.mak\
 CFG="httpinput - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"httpinput - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\httpinput.mak CFG="httpinput - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"httpinput - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\http\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\httpinput.mak\
 CFG="httpinput - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"obsinput - Win32 Release" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\obsinput.mak CFG="obsinput - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"obsinput - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\obsinput.mak CFG="obsinput - Win32 Release"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"obsinput - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\obsinput.mak CFG="obsinput - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"obsinput - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\obsinput.mak CFG="obsinput - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"obsinput - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\obsinput.mak CFG="obsinput - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"obsinput - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\obsinput.mak\
 CFG="obsinput - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"obsinput - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\obsinput.mak CFG="obsinput - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"obsinput - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\obs\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\obsinput.mak\
 CFG="obsinput - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"simple - Win32 Release" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\simple.mak CFG="simple - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"simple - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\simple.mak CFG="simple - Win32 Release"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"simple - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\simple.mak CFG="simple - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"simple - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\simple.mak CFG="simple - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"simple - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\simple.mak CFG="simple - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"simple - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\simple.mak\
 CFG="simple - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"simple - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\simple.mak CFG="simple - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"simple - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\ui\simple\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\simple.mak CFG="simple - Win32 NASM Debug"\
 RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"dsoundcard - Win32 Release" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\dsoundcard.mak CFG="dsoundcard - Win32 Release" 
   cd "..\..\..\..\base\win32\prj"

"dsoundcard - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\dsoundcard.mak\
 CFG="dsoundcard - Win32 Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"dsoundcard - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\dsoundcard.mak CFG="dsoundcard - Win32 Debug" 
   cd "..\..\..\..\base\win32\prj"

"dsoundcard - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\dsoundcard.mak\
 CFG="dsoundcard - Win32 Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"dsoundcard - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\dsoundcard.mak\
 CFG="dsoundcard - Win32 NASM Release" 
   cd "..\..\..\..\base\win32\prj"

"dsoundcard - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\dsoundcard.mak\
 CFG="dsoundcard - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"dsoundcard - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\dsoundcard.mak\
 CFG="dsoundcard - Win32 NASM Debug" 
   cd "..\..\..\..\base\win32\prj"

"dsoundcard - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\io\dsound\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\dsoundcard.mak\
 CFG="dsoundcard - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\..\base\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "freeamp - Win32 Release"

"gdbm - Win32 Release" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 Release" 
   cd "..\..\..\base\win32\prj"

"gdbm - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 Release"\
 RECURSE=1 
   cd "..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

"gdbm - Win32 Debug" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 Debug" 
   cd "..\..\..\base\win32\prj"

"gdbm - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 Debug" RECURSE=1\
 
   cd "..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

"gdbm - Win32 NASM Release" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 NASM Release" 
   cd "..\..\..\base\win32\prj"

"gdbm - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 NASM Release"\
 RECURSE=1 
   cd "..\..\..\base\win32\prj"

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

"gdbm - Win32 NASM Debug" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 NASM Debug" 
   cd "..\..\..\base\win32\prj"

"gdbm - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp1.5\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 NASM Debug"\
 RECURSE=1 
   cd "..\..\..\base\win32\prj"

!ENDIF 

SOURCE=..\res\freeamp.rc
DEP_RSC_FREEA=\
	"..\res\icon1.ico"\
	

!IF  "$(CFG)" == "freeamp - Win32 Release"


"$(INTDIR)\freeamp.res" : $(SOURCE) $(DEP_RSC_FREEA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeamp.res" /i\
 "\Local\src\freeamp1.5\base\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"


"$(INTDIR)\freeamp.res" : $(SOURCE) $(DEP_RSC_FREEA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeamp.res" /i\
 "\Local\src\freeamp1.5\base\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"


"$(INTDIR)\freeamp.res" : $(SOURCE) $(DEP_RSC_FREEA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeamp.res" /i\
 "\Local\src\freeamp1.5\base\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"


"$(INTDIR)\freeamp.res" : $(SOURCE) $(DEP_RSC_FREEA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeamp.res" /i\
 "\Local\src\freeamp1.5\base\win32\res" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=..\..\..\io\rio\win32\i386\free\portio.sys

!IF  "$(CFG)" == "freeamp - Win32 Release"

InputPath=..\..\..\io\rio\win32\i386\free\portio.sys

".\portio.sys" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\io\rio\win32\i386\free\portio.sys .\portio.sys

!ELSEIF  "$(CFG)" == "freeamp - Win32 Debug"

InputPath=..\..\..\io\rio\win32\i386\free\portio.sys

".\portio.sys" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\io\rio\win32\i386\free\portio.sys .\portio.sys

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Release"

InputPath=..\..\..\io\rio\win32\i386\free\portio.sys

".\portio.sys" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\io\rio\win32\i386\free\portio.sys .\portio.sys

!ELSEIF  "$(CFG)" == "freeamp - Win32 NASM Debug"

InputPath=..\..\..\io\rio\win32\i386\free\portio.sys

".\portio.sys" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\io\rio\win32\i386\free\portio.sys .\portio.sys

!ENDIF 


!ENDIF 

