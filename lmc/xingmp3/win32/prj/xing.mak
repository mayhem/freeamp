# Microsoft Developer Studio Generated NMAKE File, Based on xing.dsp
!IF "$(CFG)" == ""
CFG=xing - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to xing - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "xing - Win32 Release" && "$(CFG)" != "xing - Win32 Debug" &&\
 "$(CFG)" != "xing - Win32 NASM Release" && "$(CFG)" !=\
 "xing - Win32 NASM Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "xing.mak" CFG="xing - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "xing - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xing - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xing - Win32 NASM Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "xing - Win32 NASM Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "xing - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\xing.lmc"

!ELSE 

ALL : ".\xing.lmc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cdct.obj"
	-@erase "$(INTDIR)\csbt.obj"
	-@erase "$(INTDIR)\cup.obj"
	-@erase "$(INTDIR)\cupl3.obj"
	-@erase "$(INTDIR)\cwinm.obj"
	-@erase "$(INTDIR)\dec8.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\hwin.obj"
	-@erase "$(INTDIR)\icdct.obj"
	-@erase "$(INTDIR)\isbt.obj"
	-@erase "$(INTDIR)\iup.obj"
	-@erase "$(INTDIR)\iwinm.obj"
	-@erase "$(INTDIR)\l3dq.obj"
	-@erase "$(INTDIR)\l3init.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mdct.obj"
	-@erase "$(INTDIR)\mhead.obj"
	-@erase "$(INTDIR)\msis.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\uph.obj"
	-@erase "$(INTDIR)\upsf.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\wavep.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\xing.res"
	-@erase "$(INTDIR)\xinglmc.obj"
	-@erase "$(OUTDIR)\xing.exp"
	-@erase "$(OUTDIR)\xing.lib"
	-@erase ".\xing.lmc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\\" /I "..\..\..\include" /I\
 "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\xing.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\xing.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xing.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\xing.pdb" /machine:I386 /def:".\xing.def" /out:"xing.lmc"\
 /implib:"$(OUTDIR)\xing.lib" 
DEF_FILE= \
	".\xing.def"
LINK32_OBJS= \
	"$(INTDIR)\cdct.obj" \
	"$(INTDIR)\csbt.obj" \
	"$(INTDIR)\cup.obj" \
	"$(INTDIR)\cupl3.obj" \
	"$(INTDIR)\cwinm.obj" \
	"$(INTDIR)\dec8.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\hwin.obj" \
	"$(INTDIR)\icdct.obj" \
	"$(INTDIR)\isbt.obj" \
	"$(INTDIR)\iup.obj" \
	"$(INTDIR)\iwinm.obj" \
	"$(INTDIR)\l3dq.obj" \
	"$(INTDIR)\l3init.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mdct.obj" \
	"$(INTDIR)\mhead.obj" \
	"$(INTDIR)\msis.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\uph.obj" \
	"$(INTDIR)\upsf.obj" \
	"$(INTDIR)\wavep.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\xing.res" \
	"$(INTDIR)\xinglmc.obj"

".\xing.lmc" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\xing.lmc"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                ..\..\..\..\base\win32\prj\plugins
	copy xing.lmc                        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\xing.lmc"

!ELSE 

ALL : ".\xing.lmc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cdct.obj"
	-@erase "$(INTDIR)\csbt.obj"
	-@erase "$(INTDIR)\cup.obj"
	-@erase "$(INTDIR)\cupl3.obj"
	-@erase "$(INTDIR)\cwinm.obj"
	-@erase "$(INTDIR)\dec8.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\hwin.obj"
	-@erase "$(INTDIR)\icdct.obj"
	-@erase "$(INTDIR)\isbt.obj"
	-@erase "$(INTDIR)\iup.obj"
	-@erase "$(INTDIR)\iwinm.obj"
	-@erase "$(INTDIR)\l3dq.obj"
	-@erase "$(INTDIR)\l3init.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mdct.obj"
	-@erase "$(INTDIR)\mhead.obj"
	-@erase "$(INTDIR)\msis.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\uph.obj"
	-@erase "$(INTDIR)\upsf.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wavep.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\xing.res"
	-@erase "$(INTDIR)\xinglmc.obj"
	-@erase "$(OUTDIR)\xing.exp"
	-@erase "$(OUTDIR)\xing.lib"
	-@erase "$(OUTDIR)\xing.pdb"
	-@erase ".\xing.ilk"
	-@erase ".\xing.lmc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\\" /I "..\..\..\include" /I\
 "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\xing.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\xing.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xing.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\xing.pdb" /debug /machine:I386 /def:".\xing.def"\
 /out:"xing.lmc" /implib:"$(OUTDIR)\xing.lib" /pdbtype:sept 
DEF_FILE= \
	".\xing.def"
LINK32_OBJS= \
	"$(INTDIR)\cdct.obj" \
	"$(INTDIR)\csbt.obj" \
	"$(INTDIR)\cup.obj" \
	"$(INTDIR)\cupl3.obj" \
	"$(INTDIR)\cwinm.obj" \
	"$(INTDIR)\dec8.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\hwin.obj" \
	"$(INTDIR)\icdct.obj" \
	"$(INTDIR)\isbt.obj" \
	"$(INTDIR)\iup.obj" \
	"$(INTDIR)\iwinm.obj" \
	"$(INTDIR)\l3dq.obj" \
	"$(INTDIR)\l3init.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mdct.obj" \
	"$(INTDIR)\mhead.obj" \
	"$(INTDIR)\msis.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\uph.obj" \
	"$(INTDIR)\upsf.obj" \
	"$(INTDIR)\wavep.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\xing.res" \
	"$(INTDIR)\xinglmc.obj"

".\xing.lmc" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\xing.lmc"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                ..\..\..\..\base\win32\prj\plugins
	copy xing.lmc                        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\xing.lmc"

!ELSE 

ALL : ".\xing.lmc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cdct.obj"
	-@erase "$(INTDIR)\csbt.obj"
	-@erase "$(INTDIR)\cup.obj"
	-@erase "$(INTDIR)\cupl3.obj"
	-@erase "$(INTDIR)\cwinm.obj"
	-@erase "$(INTDIR)\dec8.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\hwin.obj"
	-@erase "$(INTDIR)\icdct.obj"
	-@erase "$(INTDIR)\isbt.obj"
	-@erase "$(INTDIR)\iup.obj"
	-@erase "$(INTDIR)\iwinm.obj"
	-@erase "$(INTDIR)\l3dq.obj"
	-@erase "$(INTDIR)\l3init.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mdct.obj"
	-@erase "$(INTDIR)\mhead.obj"
	-@erase "$(INTDIR)\msis.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\uph.obj"
	-@erase "$(INTDIR)\upsf.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\wavep.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\xing.res"
	-@erase "$(INTDIR)\xinglmc.obj"
	-@erase "$(OUTDIR)\xing.exp"
	-@erase "$(OUTDIR)\xing.lib"
	-@erase ".\xing.lmc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\\" /I "..\..\..\include" /I\
 "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "ASM_X86"\
 /Fp"$(INTDIR)\xing.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\xing.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xing.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\xing.pdb" /machine:I386 /def:".\xing.def" /out:"xing.lmc"\
 /implib:"$(OUTDIR)\xing.lib" 
DEF_FILE= \
	".\xing.def"
LINK32_OBJS= \
	"$(INTDIR)\cdct.obj" \
	"$(INTDIR)\cdctasm.obj" \
	"$(INTDIR)\csbt.obj" \
	"$(INTDIR)\cup.obj" \
	"$(INTDIR)\cupl3.obj" \
	"$(INTDIR)\cwin8asm.obj" \
	"$(INTDIR)\cwinasm.obj" \
	"$(INTDIR)\cwinm.obj" \
	"$(INTDIR)\dec8.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\hwin.obj" \
	"$(INTDIR)\icdct.obj" \
	"$(INTDIR)\isbt.obj" \
	"$(INTDIR)\iup.obj" \
	"$(INTDIR)\iwinm.obj" \
	"$(INTDIR)\l3dq.obj" \
	"$(INTDIR)\l3init.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mdct.obj" \
	"$(INTDIR)\mdctasm.obj" \
	"$(INTDIR)\mhead.obj" \
	"$(INTDIR)\msis.obj" \
	"$(INTDIR)\msisasm.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\uph.obj" \
	"$(INTDIR)\upsf.obj" \
	"$(INTDIR)\wavep.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\xing.res" \
	"$(INTDIR)\xinglmc.obj"

".\xing.lmc" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\xing.lmc"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                ..\..\..\..\base\win32\prj\plugins
	copy xing.lmc                        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\xing.lmc"

!ELSE 

ALL : ".\xing.lmc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\cdct.obj"
	-@erase "$(INTDIR)\csbt.obj"
	-@erase "$(INTDIR)\cup.obj"
	-@erase "$(INTDIR)\cupl3.obj"
	-@erase "$(INTDIR)\cwinm.obj"
	-@erase "$(INTDIR)\dec8.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\hwin.obj"
	-@erase "$(INTDIR)\icdct.obj"
	-@erase "$(INTDIR)\isbt.obj"
	-@erase "$(INTDIR)\iup.obj"
	-@erase "$(INTDIR)\iwinm.obj"
	-@erase "$(INTDIR)\l3dq.obj"
	-@erase "$(INTDIR)\l3init.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mdct.obj"
	-@erase "$(INTDIR)\mhead.obj"
	-@erase "$(INTDIR)\msis.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\uph.obj"
	-@erase "$(INTDIR)\upsf.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\wavep.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\xing.res"
	-@erase "$(INTDIR)\xinglmc.obj"
	-@erase "$(OUTDIR)\xing.exp"
	-@erase "$(OUTDIR)\xing.lib"
	-@erase "$(OUTDIR)\xing.pdb"
	-@erase ".\xing.ilk"
	-@erase ".\xing.lmc"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\..\\" /I "..\..\..\include" /I\
 "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "ASM_X86"\
 /Fp"$(INTDIR)\xing.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

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

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\xing.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\xing.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\xing.pdb" /debug /machine:I386 /def:".\xing.def"\
 /out:"xing.lmc" /implib:"$(OUTDIR)\xing.lib" /pdbtype:sept 
DEF_FILE= \
	".\xing.def"
LINK32_OBJS= \
	"$(INTDIR)\cdct.obj" \
	"$(INTDIR)\cdctasm.obj" \
	"$(INTDIR)\csbt.obj" \
	"$(INTDIR)\cup.obj" \
	"$(INTDIR)\cupl3.obj" \
	"$(INTDIR)\cwin8asm.obj" \
	"$(INTDIR)\cwinasm.obj" \
	"$(INTDIR)\cwinm.obj" \
	"$(INTDIR)\dec8.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\hwin.obj" \
	"$(INTDIR)\icdct.obj" \
	"$(INTDIR)\isbt.obj" \
	"$(INTDIR)\iup.obj" \
	"$(INTDIR)\iwinm.obj" \
	"$(INTDIR)\l3dq.obj" \
	"$(INTDIR)\l3init.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mdct.obj" \
	"$(INTDIR)\mdctasm.obj" \
	"$(INTDIR)\mhead.obj" \
	"$(INTDIR)\msis.obj" \
	"$(INTDIR)\msisasm.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\uph.obj" \
	"$(INTDIR)\upsf.obj" \
	"$(INTDIR)\wavep.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\xing.res" \
	"$(INTDIR)\xinglmc.obj"

".\xing.lmc" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\xing.lmc"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                ..\..\..\..\base\win32\prj\plugins
	copy xing.lmc                        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "xing - Win32 Release" || "$(CFG)" == "xing - Win32 Debug" ||\
 "$(CFG)" == "xing - Win32 NASM Release" || "$(CFG)" ==\
 "xing - Win32 NASM Debug"
SOURCE=..\..\..\..\config\config.win32

!IF  "$(CFG)" == "xing - Win32 Release"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ENDIF 

SOURCE=..\..\..\..\io\src\eventbuffer.cpp

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\eventbuffer.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	

"$(INTDIR)\eventbuffer.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\eventbuffer.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	

"$(INTDIR)\eventbuffer.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

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


SOURCE=..\..\..\..\io\src\pipeline.cpp

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_PIPEL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	

"$(INTDIR)\pipeline.obj" : $(SOURCE) $(DEP_CPP_PIPEL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_PIPEL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	

"$(INTDIR)\pipeline.obj" : $(SOURCE) $(DEP_CPP_PIPEL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_PIPEL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	

"$(INTDIR)\pipeline.obj" : $(SOURCE) $(DEP_CPP_PIPEL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_PIPEL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	

"$(INTDIR)\pipeline.obj" : $(SOURCE) $(DEP_CPP_PIPEL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\preferences.cpp

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\io\src\pullbuffer.cpp

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) $(DEP_CPP_PULLB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) $(DEP_CPP_PULLB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) $(DEP_CPP_PULLB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	

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

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	
NODEP_CPP_THREA=\
	"..\..\..\..\base\src\beosthread.h"\
	"..\..\..\..\base\src\linuxthread.h"\
	"..\..\..\..\base\src\solaristhread.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	
NODEP_CPP_THREA=\
	"..\..\..\..\base\src\beosthread.h"\
	"..\..\..\..\base\src\linuxthread.h"\
	"..\..\..\..\base\src\solaristhread.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\win32\src\win32prefs.cpp

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\win32\src\win32thread.cpp
DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\res\xing.rc

!IF  "$(CFG)" == "xing - Win32 Release"


"$(INTDIR)\xing.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\xing.res" /i\
 "\FreeAmp\freeamp\lmc\xingmp3\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"


"$(INTDIR)\xing.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\xing.res" /i\
 "\FreeAmp\freeamp\lmc\xingmp3\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"


"$(INTDIR)\xing.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\xing.res" /i\
 "\FreeAmp\freeamp\lmc\xingmp3\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"


"$(INTDIR)\xing.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\xing.res" /i\
 "\FreeAmp\freeamp\lmc\xingmp3\win32\res" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=..\..\src\cdct.c
DEP_CPP_CDCT_=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\cdct.obj" : $(SOURCE) $(DEP_CPP_CDCT_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\csbt.c
DEP_CPP_CSBT_=\
	"..\..\src\csbtb.c"\
	"..\..\src\csbtL3.c"\
	

"$(INTDIR)\csbt.obj" : $(SOURCE) $(DEP_CPP_CSBT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\cup.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_CUP_C=\
	"..\..\include\mhead.h"\
	"..\..\src\cupini.c"\
	"..\..\src\cupL1.c"\
	

"$(INTDIR)\cup.obj" : $(SOURCE) $(DEP_CPP_CUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_CUP_C=\
	"..\..\include\mhead.h"\
	"..\..\src\cupini.c"\
	"..\..\src\cupL1.c"\
	

"$(INTDIR)\cup.obj" : $(SOURCE) $(DEP_CPP_CUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_CUP_C=\
	"..\..\include\mhead.h"\
	"..\..\src\cupini.c"\
	"..\..\src\cupL1.c"\
	

"$(INTDIR)\cup.obj" : $(SOURCE) $(DEP_CPP_CUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_CUP_C=\
	"..\..\include\mhead.h"\
	"..\..\src\cupini.c"\
	"..\..\src\cupL1.c"\
	

"$(INTDIR)\cup.obj" : $(SOURCE) $(DEP_CPP_CUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\cupl3.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_CUPL3=\
	"..\..\..\..\config\config.h"\
	"..\..\include\jdw.h"\
	"..\..\include\L3.h"\
	"..\..\include\mhead.h"\
	

"$(INTDIR)\cupl3.obj" : $(SOURCE) $(DEP_CPP_CUPL3) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_CUPL3=\
	"..\..\..\..\config\config.h"\
	"..\..\include\jdw.h"\
	"..\..\include\L3.h"\
	"..\..\include\mhead.h"\
	

"$(INTDIR)\cupl3.obj" : $(SOURCE) $(DEP_CPP_CUPL3) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_CUPL3=\
	"..\..\..\..\config\config.h"\
	"..\..\include\jdw.h"\
	"..\..\include\L3.h"\
	"..\..\include\mhead.h"\
	

"$(INTDIR)\cupl3.obj" : $(SOURCE) $(DEP_CPP_CUPL3) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_CUPL3=\
	"..\..\..\..\config\config.h"\
	"..\..\include\jdw.h"\
	"..\..\include\L3.h"\
	"..\..\include\mhead.h"\
	

"$(INTDIR)\cupl3.obj" : $(SOURCE) $(DEP_CPP_CUPL3) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\cwinm.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_CWINM=\
	"..\..\..\..\config\config.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\cwin.c"\
	"..\..\src\cwinb.c"\
	
NODEP_CPP_CWINM=\
	"..\..\src\cwinbq.c"\
	"..\..\src\cwinq.c"\
	

"$(INTDIR)\cwinm.obj" : $(SOURCE) $(DEP_CPP_CWINM) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_CWINM=\
	"..\..\..\..\config\config.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\cwin.c"\
	"..\..\src\cwinb.c"\
	

"$(INTDIR)\cwinm.obj" : $(SOURCE) $(DEP_CPP_CWINM) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_CWINM=\
	"..\..\..\..\config\config.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\cwin.c"\
	"..\..\src\cwinb.c"\
	
NODEP_CPP_CWINM=\
	"..\..\src\cwinbq.c"\
	"..\..\src\cwinq.c"\
	

"$(INTDIR)\cwinm.obj" : $(SOURCE) $(DEP_CPP_CWINM) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_CWINM=\
	"..\..\..\..\config\config.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\cwin.c"\
	"..\..\src\cwinb.c"\
	

"$(INTDIR)\cwinm.obj" : $(SOURCE) $(DEP_CPP_CWINM) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\dec8.c
DEP_CPP_DEC8_=\
	"..\..\include\mhead.h"\
	

"$(INTDIR)\dec8.obj" : $(SOURCE) $(DEP_CPP_DEC8_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\hwin.c

"$(INTDIR)\hwin.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\icdct.c
DEP_CPP_ICDCT=\
	"..\..\include\itype.h"\
	

"$(INTDIR)\icdct.obj" : $(SOURCE) $(DEP_CPP_ICDCT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\isbt.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_ISBT_=\
	"..\..\include\itype.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\isbtb.c"\
	

"$(INTDIR)\isbt.obj" : $(SOURCE) $(DEP_CPP_ISBT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_ISBT_=\
	"..\..\include\itype.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\isbtb.c"\
	

"$(INTDIR)\isbt.obj" : $(SOURCE) $(DEP_CPP_ISBT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_ISBT_=\
	"..\..\include\itype.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\isbtb.c"\
	

"$(INTDIR)\isbt.obj" : $(SOURCE) $(DEP_CPP_ISBT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_ISBT_=\
	"..\..\include\itype.h"\
	"..\..\include\tableawd.h"\
	"..\..\src\isbtb.c"\
	

"$(INTDIR)\isbt.obj" : $(SOURCE) $(DEP_CPP_ISBT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\iup.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_IUP_C=\
	"..\..\include\itype.h"\
	"..\..\include\jdw.h"\
	"..\..\include\mhead.h"\
	"..\..\src\iupini.c"\
	"..\..\src\iupL1.c"\
	

"$(INTDIR)\iup.obj" : $(SOURCE) $(DEP_CPP_IUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_IUP_C=\
	"..\..\include\itype.h"\
	"..\..\include\jdw.h"\
	"..\..\include\mhead.h"\
	"..\..\src\iupini.c"\
	"..\..\src\iupL1.c"\
	

"$(INTDIR)\iup.obj" : $(SOURCE) $(DEP_CPP_IUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_IUP_C=\
	"..\..\include\itype.h"\
	"..\..\include\jdw.h"\
	"..\..\include\mhead.h"\
	"..\..\src\iupini.c"\
	"..\..\src\iupL1.c"\
	

"$(INTDIR)\iup.obj" : $(SOURCE) $(DEP_CPP_IUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_IUP_C=\
	"..\..\include\itype.h"\
	"..\..\include\jdw.h"\
	"..\..\include\mhead.h"\
	"..\..\src\iupini.c"\
	"..\..\src\iupL1.c"\
	

"$(INTDIR)\iup.obj" : $(SOURCE) $(DEP_CPP_IUP_C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\iwinm.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_IWINM=\
	"..\..\include\itype.h"\
	"..\..\src\iwinbQ.c"\
	"..\..\src\iwinQ.c"\
	
NODEP_CPP_IWINM=\
	"..\..\src\iwin.c"\
	"..\..\src\iwinb.c"\
	

"$(INTDIR)\iwinm.obj" : $(SOURCE) $(DEP_CPP_IWINM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_IWINM=\
	"..\..\include\itype.h"\
	"..\..\src\iwinbQ.c"\
	"..\..\src\iwinQ.c"\
	

"$(INTDIR)\iwinm.obj" : $(SOURCE) $(DEP_CPP_IWINM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_IWINM=\
	"..\..\include\itype.h"\
	"..\..\src\iwinbQ.c"\
	"..\..\src\iwinQ.c"\
	
NODEP_CPP_IWINM=\
	"..\..\src\iwin.c"\
	"..\..\src\iwinb.c"\
	

"$(INTDIR)\iwinm.obj" : $(SOURCE) $(DEP_CPP_IWINM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_IWINM=\
	"..\..\include\itype.h"\
	"..\..\src\iwinbQ.c"\
	"..\..\src\iwinQ.c"\
	

"$(INTDIR)\iwinm.obj" : $(SOURCE) $(DEP_CPP_IWINM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\l3dq.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_L3DQ_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3dq.obj" : $(SOURCE) $(DEP_CPP_L3DQ_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_L3DQ_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3dq.obj" : $(SOURCE) $(DEP_CPP_L3DQ_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_L3DQ_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3dq.obj" : $(SOURCE) $(DEP_CPP_L3DQ_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_L3DQ_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3dq.obj" : $(SOURCE) $(DEP_CPP_L3DQ_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\l3init.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_L3INI=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3init.obj" : $(SOURCE) $(DEP_CPP_L3INI) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_L3INI=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3init.obj" : $(SOURCE) $(DEP_CPP_L3INI) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_L3INI=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3init.obj" : $(SOURCE) $(DEP_CPP_L3INI) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_L3INI=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\l3init.obj" : $(SOURCE) $(DEP_CPP_L3INI) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\mdct.c

"$(INTDIR)\mdct.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\mhead.c
DEP_CPP_MHEAD=\
	"..\..\include\mhead.h"\
	

"$(INTDIR)\mhead.obj" : $(SOURCE) $(DEP_CPP_MHEAD) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\msis.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_MSIS_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\msis.obj" : $(SOURCE) $(DEP_CPP_MSIS_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_MSIS_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\msis.obj" : $(SOURCE) $(DEP_CPP_MSIS_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_MSIS_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\msis.obj" : $(SOURCE) $(DEP_CPP_MSIS_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_MSIS_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\msis.obj" : $(SOURCE) $(DEP_CPP_MSIS_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\uph.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_UPH_C=\
	"..\..\..\..\config\config.h"\
	"..\..\include\htable.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\uph.obj" : $(SOURCE) $(DEP_CPP_UPH_C) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_UPH_C=\
	"..\..\..\..\config\config.h"\
	"..\..\include\htable.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\uph.obj" : $(SOURCE) $(DEP_CPP_UPH_C) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_UPH_C=\
	"..\..\..\..\config\config.h"\
	"..\..\include\htable.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\uph.obj" : $(SOURCE) $(DEP_CPP_UPH_C) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_UPH_C=\
	"..\..\..\..\config\config.h"\
	"..\..\include\htable.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\uph.obj" : $(SOURCE) $(DEP_CPP_UPH_C) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\upsf.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_UPSF_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\upsf.obj" : $(SOURCE) $(DEP_CPP_UPSF_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_UPSF_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\upsf.obj" : $(SOURCE) $(DEP_CPP_UPSF_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_UPSF_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\upsf.obj" : $(SOURCE) $(DEP_CPP_UPSF_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_UPSF_=\
	"..\..\..\..\config\config.h"\
	"..\..\include\L3.h"\
	

"$(INTDIR)\upsf.obj" : $(SOURCE) $(DEP_CPP_UPSF_) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\wavep.c

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_WAVEP=\
	"..\..\include\port.h"\
	"..\..\src\wcvt.c"\
	

"$(INTDIR)\wavep.obj" : $(SOURCE) $(DEP_CPP_WAVEP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_WAVEP=\
	"..\..\include\port.h"\
	

"$(INTDIR)\wavep.obj" : $(SOURCE) $(DEP_CPP_WAVEP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_WAVEP=\
	"..\..\include\port.h"\
	"..\..\src\wcvt.c"\
	

"$(INTDIR)\wavep.obj" : $(SOURCE) $(DEP_CPP_WAVEP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_WAVEP=\
	"..\..\include\port.h"\
	

"$(INTDIR)\wavep.obj" : $(SOURCE) $(DEP_CPP_WAVEP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\xinglmc.cpp

!IF  "$(CFG)" == "xing - Win32 Release"

DEP_CPP_XINGL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	"..\..\include\mhead.h"\
	"..\..\include\port.h"\
	"..\..\include\xinglmc.h"\
	

"$(INTDIR)\xinglmc.obj" : $(SOURCE) $(DEP_CPP_XINGL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

DEP_CPP_XINGL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	"..\..\include\mhead.h"\
	"..\..\include\port.h"\
	"..\..\include\xinglmc.h"\
	

"$(INTDIR)\xinglmc.obj" : $(SOURCE) $(DEP_CPP_XINGL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

DEP_CPP_XINGL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	"..\..\include\mhead.h"\
	"..\..\include\port.h"\
	"..\..\include\xinglmc.h"\
	

"$(INTDIR)\xinglmc.obj" : $(SOURCE) $(DEP_CPP_XINGL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

DEP_CPP_XINGL=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\playlist.h"\
	"..\..\..\..\base\include\playlistformat.h"\
	"..\..\..\..\base\include\plmevent.h"\
	"..\..\..\..\base\include\portabledevice.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\properties.h"\
	"..\..\..\..\base\include\queue.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\io\include\eventbuffer.h"\
	"..\..\..\..\io\include\pipeline.h"\
	"..\..\..\..\io\include\pmi.h"\
	"..\..\..\..\io\include\pmo.h"\
	"..\..\..\..\io\include\pmoevent.h"\
	"..\..\..\..\io\include\pullbuffer.h"\
	"..\..\..\include\lmc.h"\
	"..\..\include\mhead.h"\
	"..\..\include\port.h"\
	"..\..\include\xinglmc.h"\
	

"$(INTDIR)\xinglmc.obj" : $(SOURCE) $(DEP_CPP_XINGL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\cdctasm.asm

!IF  "$(CFG)" == "xing - Win32 Release"

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

IntDir=.\Release
InputPath=..\..\src\cdctasm.asm
InputName=cdctasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

IntDir=.\Debug
InputPath=..\..\src\cdctasm.asm
InputName=cdctasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ENDIF 

SOURCE=..\..\src\cwin8asm.asm

!IF  "$(CFG)" == "xing - Win32 Release"

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

IntDir=.\Release
InputPath=..\..\src\cwin8asm.asm
InputName=cwin8asm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

IntDir=.\Debug
InputPath=..\..\src\cwin8asm.asm
InputName=cwin8asm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ENDIF 

SOURCE=..\..\src\cwinasm.asm

!IF  "$(CFG)" == "xing - Win32 Release"

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

IntDir=.\Release
InputPath=..\..\src\cwinasm.asm
InputName=cwinasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

IntDir=.\Debug
InputPath=..\..\src\cwinasm.asm
InputName=cwinasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ENDIF 

SOURCE=..\..\src\mdctasm.asm

!IF  "$(CFG)" == "xing - Win32 Release"

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

IntDir=.\Release
InputPath=..\..\src\mdctasm.asm
InputName=mdctasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

IntDir=.\Debug
InputPath=..\..\src\mdctasm.asm
InputName=mdctasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ENDIF 

SOURCE=..\..\src\msisasm.asm

!IF  "$(CFG)" == "xing - Win32 Release"

!ELSEIF  "$(CFG)" == "xing - Win32 Debug"

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Release"

IntDir=.\Release
InputPath=..\..\src\msisasm.asm
InputName=msisasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	c:\local\bin\nasm.exe -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ELSEIF  "$(CFG)" == "xing - Win32 NASM Debug"

IntDir=.\Debug
InputPath=..\..\src\msisasm.asm
InputName=msisasm

"$(IntDir)\$(InputName).obj"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	nasm.exe -f win32 -o $(IntDir)\$(InputName).obj $(InputPath)

!ENDIF 


!ENDIF 

