# Microsoft Developer Studio Generated NMAKE File, Based on httpinput.dsp
!IF "$(CFG)" == ""
CFG=httpinput - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to httpinput - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "httpinput - Win32 Release" && "$(CFG)" != "httpinput - Win32 Debug" && "$(CFG)" != "httpinput - Win32 NASM Debug" && "$(CFG)" != "httpinput - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "httpinput.mak" CFG="httpinput - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "httpinput - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "httpinput - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "httpinput - Win32 NASM Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "httpinput - Win32 NASM Release" (based on "Win32 (x86) Dynamic-Link Library")
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

ALL : ".\httpinput.pmi"


CLEAN :
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\http.res"
	-@erase "$(INTDIR)\httpinput.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmi.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\streambuffer.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\httpinput.exp"
	-@erase "$(OUTDIR)\httpinput.lib"
	-@erase ".\httpinput.pmi"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\httpinput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\http.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpinput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10400000" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\httpinput.pdb" /machine:I386 /def:".\httpinput.def" /out:"httpinput.pmi" /implib:"$(OUTDIR)\httpinput.lib" /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\httpinput.def"
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\httpinput.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmi.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\streambuffer.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\http.res"

".\httpinput.pmi" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\httpinput.pmi"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                               ..\..\..\..\base\win32\prj\plugins
	copy httpinput.pmi                          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "httpinput - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\httpinput.pmi"


CLEAN :
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\http.res"
	-@erase "$(INTDIR)\httpinput.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmi.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\streambuffer.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\httpinput.exp"
	-@erase "$(OUTDIR)\httpinput.lib"
	-@erase "$(OUTDIR)\httpinput.pdb"
	-@erase ".\httpinput.ilk"
	-@erase ".\httpinput.pmi"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\httpinput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\http.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpinput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10400000" /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\httpinput.pdb" /debug /machine:I386 /def:".\httpinput.def" /out:"httpinput.pmi" /implib:"$(OUTDIR)\httpinput.lib" /pdbtype:sept /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\httpinput.def"
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\httpinput.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmi.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\streambuffer.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\http.res"

".\httpinput.pmi" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\httpinput.pmi"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                               ..\..\..\..\base\win32\prj\plugins
	copy httpinput.pmi                          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "httpinput - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : ".\httpinput.pmi"


CLEAN :
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\http.res"
	-@erase "$(INTDIR)\httpinput.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmi.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\streambuffer.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\httpinput.exp"
	-@erase "$(OUTDIR)\httpinput.lib"
	-@erase "$(OUTDIR)\httpinput.pdb"
	-@erase ".\httpinput.ilk"
	-@erase ".\httpinput.pmi"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\httpinput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\http.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpinput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10400000" /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\httpinput.pdb" /debug /machine:I386 /def:".\httpinput.def" /out:"httpinput.pmi" /implib:"$(OUTDIR)\httpinput.lib" /pdbtype:sept /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\httpinput.def"
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\httpinput.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmi.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\streambuffer.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\http.res"

".\httpinput.pmi" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\httpinput.pmi"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                               ..\..\..\..\base\win32\prj\plugins
	copy httpinput.pmi                          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "httpinput - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\httpinput.pmi"


CLEAN :
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\http.res"
	-@erase "$(INTDIR)\httpinput.obj"
	-@erase "$(INTDIR)\pipeline.obj"
	-@erase "$(INTDIR)\pmi.obj"
	-@erase "$(INTDIR)\pullbuffer.obj"
	-@erase "$(INTDIR)\streambuffer.obj"
	-@erase "$(INTDIR)\tstream.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\httpinput.exp"
	-@erase "$(OUTDIR)\httpinput.lib"
	-@erase ".\httpinput.pmi"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\..\\" /I "..\..\..\include" /I "..\..\include" /I "..\..\..\..\io\include" /I "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\httpinput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\http.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\httpinput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib wsock32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10400000" /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\httpinput.pdb" /machine:I386 /def:".\httpinput.def" /out:"httpinput.pmi" /implib:"$(OUTDIR)\httpinput.lib" /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\httpinput.def"
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\httpinput.obj" \
	"$(INTDIR)\pipeline.obj" \
	"$(INTDIR)\pmi.obj" \
	"$(INTDIR)\pullbuffer.obj" \
	"$(INTDIR)\streambuffer.obj" \
	"$(INTDIR)\tstream.obj" \
	"$(INTDIR)\http.res"

".\httpinput.pmi" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\httpinput.pmi"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                               ..\..\..\..\base\win32\prj\plugins
	copy httpinput.pmi                          ..\..\..\..\base\win32\prj\plugins
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
!IF EXISTS("httpinput.dep")
!INCLUDE "httpinput.dep"
!ELSE 
!MESSAGE Warning: cannot find "httpinput.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "httpinput - Win32 Release" || "$(CFG)" == "httpinput - Win32 Debug" || "$(CFG)" == "httpinput - Win32 NASM Debug" || "$(CFG)" == "httpinput - Win32 NASM Release"
SOURCE=..\..\..\..\base\src\debug.cpp

"$(INTDIR)\debug.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\httpinput.cpp

"$(INTDIR)\httpinput.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\pipeline.cpp

"$(INTDIR)\pipeline.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\pmi.cpp

"$(INTDIR)\pmi.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\pullbuffer.cpp

"$(INTDIR)\pullbuffer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\streambuffer.cpp

"$(INTDIR)\streambuffer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\tstream.cpp

"$(INTDIR)\tstream.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\res\http.rc

!IF  "$(CFG)" == "httpinput - Win32 Release"


"$(INTDIR)\http.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\http.res" /i "\Local\src\freeamp\io\http\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "httpinput - Win32 Debug"


"$(INTDIR)\http.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\http.res" /i "\Local\src\freeamp\io\http\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "httpinput - Win32 NASM Debug"


"$(INTDIR)\http.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\http.res" /i "\Local\src\freeamp\io\http\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "httpinput - Win32 NASM Release"


"$(INTDIR)\http.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\http.res" /i "\Local\src\freeamp\io\http\win32\res" /d "NDEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

