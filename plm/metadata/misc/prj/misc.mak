# Microsoft Developer Studio Generated NMAKE File, Based on misc.dsp
!IF "$(CFG)" == ""
CFG=misc - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to misc - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "misc - Win32 Release" && "$(CFG)" != "misc - Win32 Debug" && "$(CFG)" != "misc - Win32 NASM Release" && "$(CFG)" != "misc - Win32 NASM Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "misc.mak" CFG="misc - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "misc - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "misc - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "misc - Win32 NASM Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "misc - Win32 NASM Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "misc - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\misc.mdf"


CLEAN :
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\misc.exp"
	-@erase "$(OUTDIR)\misc.lib"
	-@erase ".\misc.mdf"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\misc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\misc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\misc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib version.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10800000" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\misc.pdb" /machine:I386 /def:".\misc.def" /out:"misc.mdf" /implib:"$(OUTDIR)\misc.lib" /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\misc.def"
LINK32_OBJS= \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\misc.res"

".\misc.mdf" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\misc.mdf"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                   ..\..\..\..\base\win32\prj\plugins
	copy misc.mdf          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "misc - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\misc.mdf"


CLEAN :
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\misc.exp"
	-@erase "$(OUTDIR)\misc.lib"
	-@erase "$(OUTDIR)\misc.pdb"
	-@erase ".\misc.ilk"
	-@erase ".\misc.mdf"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\misc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\misc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\misc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib version.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10800000" /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\misc.pdb" /debug /machine:I386 /def:".\misc.def" /out:"misc.mdf" /implib:"$(OUTDIR)\misc.lib" /pdbtype:sept /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\misc.def"
LINK32_OBJS= \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\misc.res"

".\misc.mdf" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\misc.mdf"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                   ..\..\..\..\base\win32\prj\plugins
	copy misc.mdf          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "misc - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\misc.mdf"


CLEAN :
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\misc.exp"
	-@erase "$(OUTDIR)\misc.lib"
	-@erase ".\misc.mdf"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\misc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\misc.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\misc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib version.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10800000" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\misc.pdb" /machine:I386 /def:".\misc.def" /out:"misc.mdf" /implib:"$(OUTDIR)\misc.lib" /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\misc.def"
LINK32_OBJS= \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\misc.res"

".\misc.mdf" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\misc.mdf"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                   ..\..\..\..\base\win32\prj\plugins
	copy misc.mdf          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "misc - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\misc.mdf"


CLEAN :
	-@erase "$(INTDIR)\misc.obj"
	-@erase "$(INTDIR)\misc.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\misc.exp"
	-@erase "$(OUTDIR)\misc.lib"
	-@erase "$(OUTDIR)\misc.pdb"
	-@erase ".\misc.ilk"
	-@erase ".\misc.mdf"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\misc.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\misc.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\misc.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib version.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10800000" /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\misc.pdb" /debug /machine:I386 /def:".\misc.def" /out:"misc.mdf" /implib:"$(OUTDIR)\misc.lib" /pdbtype:sept /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\misc.def"
LINK32_OBJS= \
	"$(INTDIR)\misc.obj" \
	"$(INTDIR)\misc.res"

".\misc.mdf" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\misc.mdf"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                   ..\..\..\..\base\win32\prj\plugins
	copy misc.mdf          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("misc.dep")
!INCLUDE "misc.dep"
!ELSE 
!MESSAGE Warning: cannot find "misc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "misc - Win32 Release" || "$(CFG)" == "misc - Win32 Debug" || "$(CFG)" == "misc - Win32 NASM Release" || "$(CFG)" == "misc - Win32 NASM Debug"
SOURCE=..\misc.cpp

"$(INTDIR)\misc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\res\misc.rc

!IF  "$(CFG)" == "misc - Win32 Release"


"$(INTDIR)\misc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\misc.res" /i "\Local\src\freeamp-2-0-6\plm\metadata\misc\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "misc - Win32 Debug"


"$(INTDIR)\misc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\misc.res" /i "\Local\src\freeamp-2-0-6\plm\metadata\misc\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "misc - Win32 NASM Release"


"$(INTDIR)\misc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\misc.res" /i "\Local\src\freeamp-2-0-6\plm\metadata\misc\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "misc - Win32 NASM Debug"


"$(INTDIR)\misc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\misc.res" /i "\Local\src\freeamp-2-0-6\plm\metadata\misc\res" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

