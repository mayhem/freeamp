# Microsoft Developer Studio Generated NMAKE File, Based on dsoundcard.dsp
!IF "$(CFG)" == ""
CFG=dsoundcard - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to dsoundcard - Win32 NASM\
 Debug.
!ENDIF 

!IF "$(CFG)" != "dsoundcard - Win32 Release" && "$(CFG)" !=\
 "dsoundcard - Win32 Debug" && "$(CFG)" != "dsoundcard - Win32 NASM Debug" &&\
 "$(CFG)" != "dsoundcard - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dsoundcard.mak" CFG="dsoundcard - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dsoundcard - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsoundcard - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsoundcard - Win32 NASM Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "dsoundcard - Win32 NASM Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "dsoundcard - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\dsoundcard.pmo"

!ELSE 

ALL : ".\dsoundcard.pmo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dsound.res"
	-@erase "$(INTDIR)\dsoundcardpmo.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmo.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\dsoundcard.exp"
	-@erase "$(OUTDIR)\dsoundcard.lib"
	-@erase ".\dsoundcard.pmo"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Ob2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\dsoundcard.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dsound.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dsoundcard.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\dsoundcard.pdb" /machine:I386\
 /def:".\dsoundcard.def" /out:"dsoundcard.pmo"\
 /implib:"$(OUTDIR)\dsoundcard.lib" 
DEF_FILE= \
	".\dsoundcard.def"
LINK32_OBJS= \
	"$(INTDIR)\dsound.res" \
	"$(INTDIR)\dsoundcardpmo.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmo.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj"

".\dsoundcard.pmo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\dsoundcard.pmo"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                 ..\..\..\..\base\win32\prj\plugins
	copy dsoundcard.pmo                            ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "dsoundcard - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\dsoundcard.pmo"

!ELSE 

ALL : ".\dsoundcard.pmo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dsound.res"
	-@erase "$(INTDIR)\dsoundcardpmo.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmo.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\dsoundcard.exp"
	-@erase "$(OUTDIR)\dsoundcard.lib"
	-@erase "$(OUTDIR)\dsoundcard.pdb"
	-@erase ".\dsoundcard.ilk"
	-@erase ".\dsoundcard.pmo"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\dsoundcard.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dsound.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dsoundcard.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\dsoundcard.pdb" /debug /machine:I386\
 /def:".\dsoundcard.def" /out:"dsoundcard.pmo"\
 /implib:"$(OUTDIR)\dsoundcard.lib" /pdbtype:sept 
DEF_FILE= \
	".\dsoundcard.def"
LINK32_OBJS= \
	"$(INTDIR)\dsound.res" \
	"$(INTDIR)\dsoundcardpmo.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmo.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj"

".\dsoundcard.pmo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\dsoundcard.pmo"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                     ..\..\..\..\base\win32\prj\plugins
	copy dsoundcard.pmo            ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "dsoundcard - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\dsoundcard.pmo"

!ELSE 

ALL : ".\dsoundcard.pmo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dsound.res"
	-@erase "$(INTDIR)\dsoundcardpmo.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmo.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\dsoundcard.exp"
	-@erase "$(OUTDIR)\dsoundcard.lib"
	-@erase "$(OUTDIR)\dsoundcard.pdb"
	-@erase ".\dsoundcard.ilk"
	-@erase ".\dsoundcard.pmo"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /GX /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\dsoundcard.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dsound.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dsoundcard.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:yes /pdb:"$(OUTDIR)\dsoundcard.pdb" /debug /machine:I386\
 /def:".\dsoundcard.def" /out:"dsoundcard.pmo"\
 /implib:"$(OUTDIR)\dsoundcard.lib" /pdbtype:sept 
DEF_FILE= \
	".\dsoundcard.def"
LINK32_OBJS= \
	"$(INTDIR)\dsound.res" \
	"$(INTDIR)\dsoundcardpmo.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmo.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj"

".\dsoundcard.pmo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\dsoundcard.pmo"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                     ..\..\..\..\base\win32\prj\plugins
	copy dsoundcard.pmo            ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "dsoundcard - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\dsoundcard.pmo"

!ELSE 

ALL : ".\dsoundcard.pmo"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dsound.res"
	-@erase "$(INTDIR)\dsoundcardpmo.obj"
	-@erase "$(INTDIR)\eventbuffer.obj"
	-@erase "$(INTDIR)\log.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmo.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\dsoundcard.exp"
	-@erase "$(OUTDIR)\dsoundcard.lib"
	-@erase ".\dsoundcard.pmo"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Ob2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\dsoundcard.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
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
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o /win32 "NUL" 
RSC=rc.exe
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dsound.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dsoundcard.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=dsound.lib winmm.lib kernel32.lib user32.lib gdi32.lib\
 winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib\
 uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll\
 /incremental:no /pdb:"$(OUTDIR)\dsoundcard.pdb" /machine:I386\
 /def:".\dsoundcard.def" /out:"dsoundcard.pmo"\
 /implib:"$(OUTDIR)\dsoundcard.lib" 
DEF_FILE= \
	".\dsoundcard.def"
LINK32_OBJS= \
	"$(INTDIR)\dsound.res" \
	"$(INTDIR)\dsoundcardpmo.obj" \
	"$(INTDIR)\eventbuffer.obj" \
	"$(INTDIR)\log.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmo.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj"

".\dsoundcard.pmo" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\dsoundcard.pmo"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                 ..\..\..\..\base\win32\prj\plugins
	copy dsoundcard.pmo                            ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "dsoundcard - Win32 Release" || "$(CFG)" ==\
 "dsoundcard - Win32 Debug" || "$(CFG)" == "dsoundcard - Win32 NASM Debug" ||\
 "$(CFG)" == "dsoundcard - Win32 NASM Release"
SOURCE=..\..\..\..\config\config.win32

!IF  "$(CFG)" == "dsoundcard - Win32 Release"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "dsoundcard - Win32 Debug"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "dsoundcard - Win32 NASM Debug"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ELSEIF  "$(CFG)" == "dsoundcard - Win32 NASM Release"

InputPath=..\..\..\..\config\config.win32

"..\..\..\..\config\config.h"	 : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy ..\..\..\..\config\config.win32 ..\..\..\..\config\config.h

!ENDIF 

SOURCE=..\res\dsound.rc

!IF  "$(CFG)" == "dsoundcard - Win32 Release"


"$(INTDIR)\dsound.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\dsound.res" /i\
 "\FreeAmp\freeamp\io\dsound\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "dsoundcard - Win32 Debug"


"$(INTDIR)\dsound.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\dsound.res" /i\
 "\FreeAmp\freeamp\io\dsound\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "dsoundcard - Win32 NASM Debug"


"$(INTDIR)\dsound.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\dsound.res" /i\
 "\FreeAmp\freeamp\io\dsound\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "dsoundcard - Win32 NASM Release"


"$(INTDIR)\dsound.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\dsound.res" /i\
 "\FreeAmp\freeamp\io\dsound\win32\res" /d "NDEBUG" $(SOURCE)


!ENDIF 

SOURCE=..\src\dsoundcardpmo.cpp
DEP_CPP_DSOUN=\
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
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\lmc\include\lmc.h"\
	"..\..\..\include\eventbuffer.h"\
	"..\..\..\include\pipeline.h"\
	"..\..\..\include\pmi.h"\
	"..\..\..\include\pmo.h"\
	"..\..\..\include\pmoevent.h"\
	"..\..\..\include\pullbuffer.h"\
	"..\include\dsoundcardpmo.h"\
	
NODEP_CPP_DSOUN=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\dsoundcardpmo.obj" : $(SOURCE) $(DEP_CPP_DSOUN) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\eventbuffer.cpp
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
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\lmc\include\lmc.h"\
	"..\..\..\include\eventbuffer.h"\
	"..\..\..\include\pipeline.h"\
	"..\..\..\include\pmi.h"\
	"..\..\..\include\pmo.h"\
	"..\..\..\include\pmoevent.h"\
	"..\..\..\include\pullbuffer.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_EVENT=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\eventbuffer.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"\
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


SOURCE=..\..\..\src\pipeline.cpp
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
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\lmc\include\lmc.h"\
	"..\..\..\include\eventbuffer.h"\
	"..\..\..\include\pipeline.h"\
	"..\..\..\include\pmi.h"\
	"..\..\..\include\pmo.h"\
	"..\..\..\include\pmoevent.h"\
	"..\..\..\include\pullbuffer.h"\
	
NODEP_CPP_PIPEL=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\pipeline.obj" : $(SOURCE) $(DEP_CPP_PIPEL) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\pmo.cpp
DEP_CPP_PMO_C=\
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
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\lmc\include\lmc.h"\
	"..\..\..\include\eventbuffer.h"\
	"..\..\..\include\pipeline.h"\
	"..\..\..\include\pmi.h"\
	"..\..\..\include\pmo.h"\
	"..\..\..\include\pmoevent.h"\
	"..\..\..\include\pullbuffer.h"\
	
NODEP_CPP_PMO_C=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\pmo.obj" : $(SOURCE) $(DEP_CPP_PMO_C) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\preferences.cpp
DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	
NODEP_CPP_PREFE=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\pullbuffer.cpp
DEP_CPP_PULLB=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\include\pullbuffer.h"\
	
NODEP_CPP_PULLB=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) $(DEP_CPP_PULLB) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\semaphore.cpp
DEP_CPP_SEMAP=\
	"..\..\..\..\base\win32\include\semaphore.h"\
	

"$(INTDIR)\semaphore.obj" : $(SOURCE) $(DEP_CPP_SEMAP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\thread.cpp
DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	
NODEP_CPP_THREA=\
	"..\..\..\..\base\src\beosthread.h"\
	"..\..\..\..\base\src\linuxthread.h"\
	"..\..\..\..\base\src\solaristhread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\win32prefs.cpp
DEP_CPP_WIN32=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	
NODEP_CPP_WIN32=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\win32thread.cpp
DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	
NODEP_CPP_WIN32T=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"\
 "..\..\..\..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

