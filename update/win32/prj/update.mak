# Microsoft Developer Studio Generated NMAKE File, Based on update.dsp
!IF "$(CFG)" == ""
CFG=update - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to update - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "update - Win32 Release" && "$(CFG)" != "update - Win32 Debug"\
 && "$(CFG)" != "update - Win32 NASM Debug" && "$(CFG)" !=\
 "update - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "update.mak" CFG="update - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "update - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "update - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "update - Win32 NASM Debug" (based on "Win32 (x86) Application")
!MESSAGE "update - Win32 NASM Release" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "update - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\update.exe"

!ELSE 

ALL : ".\update.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase ".\update.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\\" /I "..\..\include" /I "..\include"\
 /I "..\..\..\io\include" /I "..\..\..\base\include" /I\
 "..\..\..\base\win32\include" /I "..\..\..\config" /I "..\..\..\ui\include" /I\
 "..\..\..\lib\xml\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\update.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\update.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\update.pdb" /machine:I386 /out:"update.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

".\update.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\update.exe"
   copy update.exe  ..\..\..\base\win32\prj
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "update - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\update.exe"

!ELSE 

ALL : ".\update.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\update.pdb"
	-@erase ".\update.exe"
	-@erase ".\update.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\\" /I "..\..\include" /I\
 "..\include" /I "..\..\..\io\include" /I "..\..\..\base\include" /I\
 "..\..\..\base\win32\include" /I "..\..\..\config" /I "..\..\..\ui\include" /I\
 "..\..\..\lib\xml\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\update.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\update.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\update.pdb" /debug /machine:I386 /out:"update.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

".\update.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\update.exe"
   copy update.exe  ..\..\..\base\win32\prj
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "update - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\update.exe"

!ELSE 

ALL : ".\update.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\update.pdb"
	-@erase ".\update.exe"
	-@erase ".\update.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /Zi /Od /I "..\\" /I "..\..\include" /I\
 "..\include" /I "..\..\..\io\include" /I "..\..\..\base\include" /I\
 "..\..\..\base\win32\include" /I "..\..\..\config" /I "..\..\..\ui\include" /I\
 "..\..\..\lib\xml\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\update.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\update.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\update.pdb" /debug /machine:I386 /out:"update.exe"\
 /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

".\update.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\update.exe"
   copy update.exe  ..\..\..\base\win32\prj
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "update - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\update.exe"

!ELSE 

ALL : ".\update.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase ".\update.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "..\\" /I "..\..\include" /I "..\include"\
 /I "..\..\..\io\include" /I "..\..\..\base\include" /I\
 "..\..\..\base\win32\include" /I "..\..\..\config" /I "..\..\..\ui\include" /I\
 "..\..\..\lib\xml\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\update.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\update.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\update.pdb" /machine:I386 /out:"update.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj"

".\update.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\update.exe"
   copy update.exe  ..\..\..\base\win32\prj
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


!IF "$(CFG)" == "update - Win32 Release" || "$(CFG)" == "update - Win32 Debug"\
 || "$(CFG)" == "update - Win32 NASM Debug" || "$(CFG)" ==\
 "update - Win32 NASM Release"
SOURCE=..\main.cpp

!IF  "$(CFG)" == "update - Win32 Release"

DEP_CPP_MAIN_=\
	"..\..\..\base\include\errors.h"\
	"..\..\..\base\include\facontext.h"\
	"..\..\..\base\include\log.h"\
	"..\..\..\base\include\preferences.h"\
	"..\..\..\base\include\thread.h"\
	"..\..\..\base\include\updatemanager.h"\
	"..\..\..\base\win32\include\mutex.h"\
	"..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\config\config.h"\
	"..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "update - Win32 Debug"

DEP_CPP_MAIN_=\
	"..\..\..\base\include\errors.h"\
	"..\..\..\base\include\facontext.h"\
	"..\..\..\base\include\log.h"\
	"..\..\..\base\include\preferences.h"\
	"..\..\..\base\include\thread.h"\
	"..\..\..\base\include\updatemanager.h"\
	"..\..\..\base\win32\include\mutex.h"\
	"..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\config\config.h"\
	"..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "update - Win32 NASM Debug"

DEP_CPP_MAIN_=\
	"..\..\..\base\include\errors.h"\
	"..\..\..\base\include\facontext.h"\
	"..\..\..\base\include\log.h"\
	"..\..\..\base\include\preferences.h"\
	"..\..\..\base\include\thread.h"\
	"..\..\..\base\include\updatemanager.h"\
	"..\..\..\base\win32\include\mutex.h"\
	"..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\lib\xml\include\parse.h"\
	
NODEP_CPP_MAIN_=\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "update - Win32 NASM Release"

DEP_CPP_MAIN_=\
	"..\..\..\base\include\errors.h"\
	"..\..\..\base\include\facontext.h"\
	"..\..\..\base\include\log.h"\
	"..\..\..\base\include\preferences.h"\
	"..\..\..\base\include\thread.h"\
	"..\..\..\base\include\updatemanager.h"\
	"..\..\..\base\win32\include\mutex.h"\
	"..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\config\config.h"\
	"..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\main.obj" : $(SOURCE) $(DEP_CPP_MAIN_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 
