# Microsoft Developer Studio Generated NMAKE File, Based on musicbrowser.dsp
!IF "$(CFG)" == ""
CFG=musicbrowser - Win32 Debug
!MESSAGE No configuration specified. Defaulting to musicbrowser - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "musicbrowser - Win32 Release" && "$(CFG)" !=\
 "musicbrowser - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "musicbrowser.mak" CFG="musicbrowser - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "musicbrowser - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "musicbrowser - Win32 Debug" (based on\
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

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\musicbrowser.ui"

!ELSE 

ALL : ".\musicbrowser.ui"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\musicbrowser.obj"
	-@erase "$(INTDIR)\musicbrowser.res"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\Win32MusicBrowser.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\musicbrowser.exp"
	-@erase "$(OUTDIR)\musicbrowser.lib"
	-@erase ".\musicbrowser.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\res" /I "..\..\..\..\lib\gdbm" /D "WIN32" /D\
 "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\musicbrowser.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\musicbrowser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\musicbrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\musicbrowser.pdb" /machine:I386 /def:".\musicbrowser.def"\
 /out:"musicbrowser.ui" /implib:"$(OUTDIR)\musicbrowser.lib" 
DEF_FILE= \
	".\musicbrowser.def"
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\musicbrowser.obj" \
	"$(INTDIR)\musicbrowser.res" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\Win32MusicBrowser.obj" \
	"$(INTDIR)\win32thread.obj"

".\musicbrowser.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\musicbrowser.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                      ..\..\..\..\base\win32\prj\plugins
	copy musicbrowser.ui                                        ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\musicbrowser.ui"

!ELSE 

ALL : ".\musicbrowser.ui"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\musicbrowser.obj"
	-@erase "$(INTDIR)\musicbrowser.res"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\Win32MusicBrowser.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(OUTDIR)\musicbrowser.exp"
	-@erase "$(OUTDIR)\musicbrowser.lib"
	-@erase "$(OUTDIR)\musicbrowser.pdb"
	-@erase ".\musicbrowser.ilk"
	-@erase ".\musicbrowser.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\res" /I "..\..\..\..\lib\gdbm" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\musicbrowser.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\musicbrowser.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\musicbrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\musicbrowser.pdb" /debug /machine:I386\
 /def:".\musicbrowser.def" /out:"musicbrowser.ui"\
 /implib:"$(OUTDIR)\musicbrowser.lib" /pdbtype:sept 
DEF_FILE= \
	".\musicbrowser.def"
LINK32_OBJS= \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\musicbrowser.obj" \
	"$(INTDIR)\musicbrowser.res" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\Win32MusicBrowser.obj" \
	"$(INTDIR)\win32thread.obj"

".\musicbrowser.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : ".\musicbrowser.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                      ..\..\..\..\base\win32\prj\plugins
	copy musicbrowser.ui                                        ..\..\..\..\base\win32\prj\plugins
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


!IF "$(CFG)" == "musicbrowser - Win32 Release" || "$(CFG)" ==\
 "musicbrowser - Win32 Debug"
SOURCE=..\..\..\..\base\src\debug.cpp
DEP_CPP_DEBUG=\
	"..\..\..\..\base\include\debug.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\musicbrowser.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_MUSIC=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\musicbrowser.h"\
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
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\gdbm\gdbm_fa.h"\
	"..\..\..\include\ui.h"\
	"..\include\Win32MusicBrowser.h"\
	
NODEP_CPP_MUSIC=\
	"..\..\src\gtkmusicbrowser.h"\
	"..\..\src\infoeditor.h"\
	

"$(INTDIR)\musicbrowser.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_MUSIC=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\eventdata.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\musicbrowser.h"\
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
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\gdbm\gdbm_fa.h"\
	"..\..\..\include\ui.h"\
	"..\include\Win32MusicBrowser.h"\
	

"$(INTDIR)\musicbrowser.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\win32\src\mutex.cpp
DEP_CPP_MUTEX=\
	"..\..\..\..\base\win32\include\mutex.h"\
	

"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\playlist.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_PLAYL=\
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
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\config\config.h"\
	
NODEP_CPP_PLAYL=\
	"..\..\..\..\base\include\win32impl.h"\
	

"$(INTDIR)\playlist.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_PLAYL=\
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
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\playlist.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\preferences.cpp
DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\registrar.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_REGIS=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\hashtable.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\config\config.h"\
	
NODEP_CPP_REGIS=\
	"..\..\..\..\base\include\win32impl.h"\
	

"$(INTDIR)\registrar.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_REGIS=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\hashtable.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\registrar.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\registry.cpp
DEP_CPP_REGIST=\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\registry.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\thread.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	
NODEP_CPP_THREA=\
	"..\..\..\..\base\src\beosthread.h"\
	"..\..\..\..\base\src\linuxthread.h"\
	"..\..\..\..\base\src\solaristhread.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\utility.cpp
DEP_CPP_UTILI=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\config\config.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\utility.obj" : $(SOURCE) $(DEP_CPP_UTILI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\Win32MusicBrowser.cpp
DEP_CPP_WIN32=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\event.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\metadata.h"\
	"..\..\..\..\base\include\musicbrowser.h"\
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
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\gdbm\gdbm_fa.h"\
	"..\..\..\include\ui.h"\
	"..\include\Win32MusicBrowser.h"\
	

"$(INTDIR)\Win32MusicBrowser.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\win32thread.cpp
DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\res\musicbrowser.rc

!IF  "$(CFG)" == "musicbrowser - Win32 Release"


"$(INTDIR)\musicbrowser.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\musicbrowser.res" /i\
 "\FreeAmp\freeamp\ui\musicbrowser\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"


"$(INTDIR)\musicbrowser.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\musicbrowser.res" /i\
 "\FreeAmp\freeamp\ui\musicbrowser\win32\res" /d "_DEBUG" $(SOURCE)


!ENDIF 


!ENDIF 

