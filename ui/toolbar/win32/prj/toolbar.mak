# Microsoft Developer Studio Generated NMAKE File, Based on toolbar.dsp
!IF "$(CFG)" == ""
CFG=toolbar - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to toolbar - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "toolbar - Win32 Release" && "$(CFG)" !=\
 "toolbar - Win32 Debug" && "$(CFG)" != "toolbar - Win32 NASM Debug" && "$(CFG)"\
 != "toolbar - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "toolbar.mak" CFG="toolbar - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "toolbar - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "toolbar - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "toolbar - Win32 NASM Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "toolbar - Win32 NASM Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "toolbar - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\toolbar.ui"

!ELSE 

ALL : ".\toolbar.ui"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\toolbar.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\toolbar.exp"
	-@erase "$(OUTDIR)\toolbar.lib"
	-@erase ".\toolbar.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lib\xml\include" /I "..\res" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\toolbar.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\toolbar.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\toolbar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\toolbar.pdb" /machine:I386 /def:".\toolbar.def"\
 /out:"toolbar.ui" /implib:"$(OUTDIR)\toolbar.lib" 
DEF_FILE= \
	".\toolbar.def"
LINK32_OBJS= \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\toolbar.res"

".\toolbar.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\toolbar.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                    ..\..\..\..\base\win32\prj\plugins
	copy toolbar.ui                                      ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "toolbar - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\toolbar.ui"

!ELSE 

ALL : ".\toolbar.ui"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\toolbar.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\toolbar.exp"
	-@erase "$(OUTDIR)\toolbar.lib"
	-@erase "$(OUTDIR)\toolbar.pdb"
	-@erase ".\toolbar.ilk"
	-@erase ".\toolbar.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lib\xml\include" /I "..\res" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\toolbar.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\toolbar.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\toolbar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\toolbar.pdb" /debug /machine:I386 /def:".\toolbar.def"\
 /out:"toolbar.ui" /implib:"$(OUTDIR)\toolbar.lib" /pdbtype:sept 
DEF_FILE= \
	".\toolbar.def"
LINK32_OBJS= \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\toolbar.res"

".\toolbar.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\toolbar.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                    ..\..\..\..\base\win32\prj\plugins
	copy toolbar.ui                                      ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "toolbar - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\toolbar.ui"

!ELSE 

ALL : ".\toolbar.ui"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\toolbar.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\toolbar.exp"
	-@erase "$(OUTDIR)\toolbar.lib"
	-@erase "$(OUTDIR)\toolbar.pdb"
	-@erase ".\toolbar.ilk"
	-@erase ".\toolbar.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lib\xml\include" /I "..\res" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\toolbar.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\toolbar.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\toolbar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\toolbar.pdb" /debug /machine:I386 /def:".\toolbar.def"\
 /out:"toolbar.ui" /implib:"$(OUTDIR)\toolbar.lib" /pdbtype:sept 
DEF_FILE= \
	".\toolbar.def"
LINK32_OBJS= \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\toolbar.res"

".\toolbar.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\toolbar.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                    ..\..\..\..\base\win32\prj\plugins
	copy toolbar.ui                                      ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "toolbar - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\toolbar.ui"

!ELSE 

ALL : ".\toolbar.ui"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\toolbar.res"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\toolbar.exp"
	-@erase "$(OUTDIR)\toolbar.lib"
	-@erase ".\toolbar.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\..\..\..\lib\xml\include" /I "..\res" /D\
 "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\toolbar.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\toolbar.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\toolbar.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\toolbar.pdb" /machine:I386 /def:".\toolbar.def"\
 /out:"toolbar.ui" /implib:"$(OUTDIR)\toolbar.lib" 
DEF_FILE= \
	".\toolbar.def"
LINK32_OBJS= \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\toolbar.res"

".\toolbar.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\toolbar.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                    ..\..\..\..\base\win32\prj\plugins
	copy toolbar.ui                                      ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "toolbar - Win32 Release" || "$(CFG)" ==\
 "toolbar - Win32 Debug" || "$(CFG)" == "toolbar - Win32 NASM Debug" || "$(CFG)"\
 == "toolbar - Win32 NASM Release"
SOURCE=..\Toolbar.cpp
DEP_CPP_TOOLB=\
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
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\include\ui.h"\
	"..\Toolbar.h"\
	
NODEP_CPP_TOOLB=\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\Toolbar.obj" : $(SOURCE) $(DEP_CPP_TOOLB) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\toolbar.rc
DEP_RSC_TOOLBA=\
	"..\icon1.ico"\
	

!IF  "$(CFG)" == "toolbar - Win32 Release"


"$(INTDIR)\toolbar.res" : $(SOURCE) $(DEP_RSC_TOOLBA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\toolbar.res" /i\
 "\FreeAmp\freeamp\ui\toolbar\win32" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "toolbar - Win32 Debug"


"$(INTDIR)\toolbar.res" : $(SOURCE) $(DEP_RSC_TOOLBA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\toolbar.res" /i\
 "\FreeAmp\freeamp\ui\toolbar\win32" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "toolbar - Win32 NASM Debug"


"$(INTDIR)\toolbar.res" : $(SOURCE) $(DEP_RSC_TOOLBA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\toolbar.res" /i\
 "\FreeAmp\freeamp\ui\toolbar\win32" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "toolbar - Win32 NASM Release"


"$(INTDIR)\toolbar.res" : $(SOURCE) $(DEP_RSC_TOOLBA) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\toolbar.res" /i\
 "\FreeAmp\freeamp\ui\toolbar\win32" /d "NDEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

