# Microsoft Developer Studio Generated NMAKE File, Based on httpinput.dsp
!IF "$(CFG)" == ""
CFG=httpinput - Win32 Debug
!MESSAGE No configuration specified. Defaulting to httpinput - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "httpinput - Win32 Release" && "$(CFG)" !=\
 "httpinput - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "httpinput.mak" CFG="httpinput - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "httpinput - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "httpinput - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "httpinput - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\httpinput.pmi"

!ELSE 

ALL : ".\httpinput.pmi"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\httpbuffer.obj"
	-@erase "$(INTDIR)\httpinput.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\httpinput.exp"
	-@erase "$(OUTDIR)\httpinput.lib"
	-@erase ".\httpinput.pmi"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\\" /I "..\..\..\include" /I\
 "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\httpinput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpinput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\httpinput.pdb" /machine:I386 /def:".\httpinput.def"\
 /out:"httpinput.pmi" /implib:"$(OUTDIR)\httpinput.lib" 
DEF_FILE= \
	".\httpinput.def"
LINK32_OBJS= \
	"$(INTDIR)\httpbuffer.obj" \
	"$(INTDIR)\httpinput.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32thread.obj"

".\httpinput.pmi" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\httpinput.pmi"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir             ..\..\..\..\base\win32\prj\plugins
	copy httpinput.pmi        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "httpinput - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\httpinput.pmi"

!ELSE 

ALL : ".\httpinput.pmi"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\httpbuffer.obj"
	-@erase "$(INTDIR)\httpinput.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\httpinput.exp"
	-@erase "$(OUTDIR)\httpinput.lib"
	-@erase "$(OUTDIR)\httpinput.pdb"
	-@erase ".\httpinput.ilk"
	-@erase ".\httpinput.pmi"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\\" /I "..\..\..\include" /I\
 "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\httpinput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpinput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib\
 odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\httpinput.pdb" /debug /machine:I386 /def:".\httpinput.def"\
 /out:"httpinput.pmi" /implib:"$(OUTDIR)\httpinput.lib" /pdbtype:sept 
DEF_FILE= \
	".\httpinput.def"
LINK32_OBJS= \
	"$(INTDIR)\httpbuffer.obj" \
	"$(INTDIR)\httpinput.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32thread.obj"

".\httpinput.pmi" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\httpinput.pmi"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir             ..\..\..\..\base\win32\prj\plugins
	copy httpinput.pmi        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

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


!IF "$(CFG)" == "httpinput - Win32 Release" || "$(CFG)" ==\
 "httpinput - Win32 Debug"
SOURCE=..\..\..\..\config\config.win32

!IF  "$(CFG)" == "httpinput - Win32 Release"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "httpinput - Win32 Debug"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ENDIF 

SOURCE=..\..\httpbuffer.cpp
DEP_CPP_HTTPB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\include\pullbuffer.h"\
	"..\..\..\include\streambuffer.h"\
	"..\..\httpbuffer.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\httpbuffer.obj" : $(SOURCE) $(DEP_CPP_HTTPB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\httpinput.cpp
DEP_CPP_HTTPI=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\include\pmi.h"\
	"..\..\..\include\pullbuffer.h"\
	"..\..\..\include\streambuffer.h"\
	"..\..\httpbuffer.h"\
	"..\..\httpinput.h"\
	

"$(INTDIR)\httpinput.obj" : $(SOURCE) $(DEP_CPP_HTTPI) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\log.cpp
DEP_CPP_LOG_C=\
	"..\..\..\..\base\include\log.h"\
	

"$(INTDIR)\log.obj" : $(SOURCE) $(DEP_CPP_LOG_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\mutex.cpp
DEP_CPP_MUTEX=\
	"..\..\..\..\base\win32\include\mutex.h"\
	

"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\pullbuffer.cpp

!IF  "$(CFG)" == "httpinput - Win32 Release"

DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\include\pullbuffer.h"\
	

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) $(DEP_CPP_PULLB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "httpinput - Win32 Debug"

DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\include\pullbuffer.h"\
	

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) $(DEP_CPP_PULLB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\win32\src\semaphore.cpp
DEP_CPP_SEMAP=\
	"..\..\..\..\base\win32\include\semaphore.h"\
	

"$(INTDIR)\semaphore.obj" : $(SOURCE) $(DEP_CPP_SEMAP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\thread.cpp
DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	
NODEP_CPP_THREA=\
	"..\..\..\..\base\src\linuxthread.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\win32thread.cpp

!IF  "$(CFG)" == "httpinput - Win32 Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "httpinput - Win32 Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 
