# Microsoft Developer Studio Generated NMAKE File, Based on musicbrowser.dsp
!IF "$(CFG)" == ""
CFG=musicbrowser - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to musicbrowser - Win32 NASM\
 Debug.
!ENDIF 

!IF "$(CFG)" != "musicbrowser - Win32 Release" && "$(CFG)" !=\
 "musicbrowser - Win32 Debug" && "$(CFG)" != "musicbrowser - Win32 NASM Debug"\
 && "$(CFG)" != "musicbrowser - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "musicbrowser.mak" CFG="musicbrowser - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "musicbrowser - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "musicbrowser - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "musicbrowser - Win32 NASM Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "musicbrowser - Win32 NASM Release" (based on\
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

ALL : "gdbm - Win32 Release" "fabaselib - Win32 Release" ".\musicbrowser.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fabaselib - Win32 ReleaseCLEAN" "gdbm - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\DataIndex.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\musicbrowser.res"
	-@erase "$(INTDIR)\MusicTree.obj"
	-@erase "$(INTDIR)\PlaylistView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\Win32MusicBrowser.obj"
	-@erase "$(OUTDIR)\musicbrowser.exp"
	-@erase "$(OUTDIR)\musicbrowser.lib"
	-@erase ".\musicbrowser.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\res" /I "..\..\..\..\lib\gdbm" /I\
 "..\..\..\..\lmc\include" /I "..\..\..\..\io\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\musicbrowser.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\musicbrowser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\musicbrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib gdbm.lib comctl32.lib version.lib wsock32.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\musicbrowser.pdb"\
 /machine:I386 /def:".\musicbrowser.def" /out:"musicbrowser.ui"\
 /implib:"$(OUTDIR)\musicbrowser.lib" /libpath:"..\..\..\..\lib\gdbm"\
 /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\musicbrowser.def"
LINK32_OBJS= \
	"$(INTDIR)\DataIndex.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\musicbrowser.res" \
	"$(INTDIR)\MusicTree.obj" \
	"$(INTDIR)\PlaylistView.obj" \
	"$(INTDIR)\Win32MusicBrowser.obj" \
	"..\..\..\..\base\win32\fabaselib.lib" \
	"..\..\..\..\lib\gdbm\gdbm.lib"

".\musicbrowser.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "gdbm - Win32 Release" "fabaselib - Win32 Release"\
 ".\musicbrowser.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                                             ..\..\..\..\base\win32\prj\plugins
	copy musicbrowser.ui                                                               ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\musicbrowser.ui"

!ELSE 

ALL : "gdbm - Win32 Debug" "fabaselib - Win32 Debug" ".\musicbrowser.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fabaselib - Win32 DebugCLEAN" "gdbm - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\DataIndex.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\musicbrowser.res"
	-@erase "$(INTDIR)\MusicTree.obj"
	-@erase "$(INTDIR)\PlaylistView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\Win32MusicBrowser.obj"
	-@erase "$(OUTDIR)\musicbrowser.exp"
	-@erase "$(OUTDIR)\musicbrowser.lib"
	-@erase "$(OUTDIR)\musicbrowser.pdb"
	-@erase ".\musicbrowser.ilk"
	-@erase ".\musicbrowser.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\res" /I "..\..\..\..\lib\gdbm" /I\
 "..\..\..\..\lmc\include" /I "..\..\..\..\io\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\musicbrowser.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\musicbrowser.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\musicbrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib gdbm.lib comctl32.lib version.lib wsock32.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\musicbrowser.pdb"\
 /debug /machine:I386 /def:".\musicbrowser.def" /out:"musicbrowser.ui"\
 /implib:"$(OUTDIR)\musicbrowser.lib" /pdbtype:sept\
 /libpath:"..\..\..\..\lib\gdbm" /libpath:"..\..\..\..\base\win32" 
LINK32_OBJS= \
	"$(INTDIR)\DataIndex.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\musicbrowser.res" \
	"$(INTDIR)\MusicTree.obj" \
	"$(INTDIR)\PlaylistView.obj" \
	"$(INTDIR)\Win32MusicBrowser.obj" \
	"..\..\..\..\base\win32\fabaselib.lib" \
	"..\..\..\..\lib\gdbm\gdbm.lib"

".\musicbrowser.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "gdbm - Win32 Debug" "fabaselib - Win32 Debug"\
 ".\musicbrowser.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                                             ..\..\..\..\base\win32\prj\plugins
	copy musicbrowser.ui                                                               ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\musicbrowser.ui"

!ELSE 

ALL : "gdbm - Win32 NASM Debug" "fabaselib - Win32 NASM Debug"\
 ".\musicbrowser.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fabaselib - Win32 NASM DebugCLEAN" "gdbm - Win32 NASM DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\DataIndex.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\musicbrowser.res"
	-@erase "$(INTDIR)\MusicTree.obj"
	-@erase "$(INTDIR)\PlaylistView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\Win32MusicBrowser.obj"
	-@erase "$(OUTDIR)\musicbrowser.exp"
	-@erase "$(OUTDIR)\musicbrowser.lib"
	-@erase "$(OUTDIR)\musicbrowser.pdb"
	-@erase ".\musicbrowser.ilk"
	-@erase ".\musicbrowser.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\res" /I "..\..\..\..\lib\gdbm" /I\
 "..\..\..\..\lmc\include" /I "..\..\..\..\io\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\musicbrowser.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\musicbrowser.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\musicbrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib gdbm.lib comctl32.lib version.lib wsock32.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\musicbrowser.pdb"\
 /debug /machine:I386 /def:".\musicbrowser.def" /out:"musicbrowser.ui"\
 /implib:"$(OUTDIR)\musicbrowser.lib" /pdbtype:sept\
 /libpath:"..\..\..\..\lib\gdbm" /libpath:"..\..\..\..\base\win32" 
LINK32_OBJS= \
	"$(INTDIR)\DataIndex.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\musicbrowser.res" \
	"$(INTDIR)\MusicTree.obj" \
	"$(INTDIR)\PlaylistView.obj" \
	"$(INTDIR)\Win32MusicBrowser.obj" \
	"..\..\..\..\base\win32\fabaselib.lib" \
	"..\..\..\..\lib\gdbm\gdbm.lib"

".\musicbrowser.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "gdbm - Win32 NASM Debug" "fabaselib - Win32 NASM Debug"\
 ".\musicbrowser.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                                             ..\..\..\..\base\win32\prj\plugins
	copy musicbrowser.ui                                                               ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\musicbrowser.ui"

!ELSE 

ALL : "gdbm - Win32 NASM Release" "fabaselib - Win32 NASM Release"\
 ".\musicbrowser.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"fabaselib - Win32 NASM ReleaseCLEAN" "gdbm - Win32 NASM ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\DataIndex.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\Event.obj"
	-@erase "$(INTDIR)\musicbrowser.res"
	-@erase "$(INTDIR)\MusicTree.obj"
	-@erase "$(INTDIR)\PlaylistView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\Win32MusicBrowser.obj"
	-@erase "$(OUTDIR)\musicbrowser.exp"
	-@erase "$(OUTDIR)\musicbrowser.lib"
	-@erase ".\musicbrowser.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\include" /I "..\..\include" /I\
 "..\..\..\include" /I "..\..\..\..\base\include" /I\
 "..\..\..\..\base\win32\include" /I "..\..\..\..\config" /I\
 "..\..\..\..\ui\include" /I "..\res" /I "..\..\..\..\lib\gdbm" /I\
 "..\..\..\..\lmc\include" /I "..\..\..\..\io\include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\musicbrowser.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\musicbrowser.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\musicbrowser.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=fabaselib.lib gdbm.lib comctl32.lib version.lib wsock32.lib\
 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib\
 shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\musicbrowser.pdb"\
 /machine:I386 /def:".\musicbrowser.def" /out:"musicbrowser.ui"\
 /implib:"$(OUTDIR)\musicbrowser.lib" /libpath:"..\..\..\..\lib\gdbm"\
 /libpath:"..\..\..\..\base\win32" 
DEF_FILE= \
	".\musicbrowser.def"
LINK32_OBJS= \
	"$(INTDIR)\DataIndex.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\Event.obj" \
	"$(INTDIR)\musicbrowser.res" \
	"$(INTDIR)\MusicTree.obj" \
	"$(INTDIR)\PlaylistView.obj" \
	"$(INTDIR)\Win32MusicBrowser.obj" \
	"..\..\..\..\base\win32\fabaselib.lib" \
	"..\..\..\..\lib\gdbm\gdbm.lib"

".\musicbrowser.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "gdbm - Win32 NASM Release"\
 "fabaselib - Win32 NASM Release" ".\musicbrowser.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                                                             ..\..\..\..\base\win32\prj\plugins
	copy musicbrowser.ui                                                               ..\..\..\..\base\win32\prj\plugins
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
 "musicbrowser - Win32 Debug" || "$(CFG)" == "musicbrowser - Win32 NASM Debug"\
 || "$(CFG)" == "musicbrowser - Win32 NASM Release"
SOURCE=..\src\DataIndex.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_DATAI=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\DataIndex.obj" : $(SOURCE) $(DEP_CPP_DATAI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_DATAI=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\DataIndex.obj" : $(SOURCE) $(DEP_CPP_DATAI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

DEP_CPP_DATAI=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\DataIndex.obj" : $(SOURCE) $(DEP_CPP_DATAI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

DEP_CPP_DATAI=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\DataIndex.obj" : $(SOURCE) $(DEP_CPP_DATAI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Dialog.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_DIALO=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_DIALO=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

DEP_CPP_DIALO=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

DEP_CPP_DIALO=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\Dialog.obj" : $(SOURCE) $(DEP_CPP_DIALO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Event.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\Event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\Event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\Event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

DEP_CPP_EVENT=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\Event.obj" : $(SOURCE) $(DEP_CPP_EVENT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\MusicTree.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_MUSIC=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\MusicTree.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_MUSIC=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\MusicTree.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

DEP_CPP_MUSIC=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\MusicTree.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

DEP_CPP_MUSIC=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\MusicTree.obj" : $(SOURCE) $(DEP_CPP_MUSIC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\PlaylistView.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_PLAYL=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\PlaylistView.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_PLAYL=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\PlaylistView.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

DEP_CPP_PLAYL=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\PlaylistView.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

DEP_CPP_PLAYL=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\PlaylistView.obj" : $(SOURCE) $(DEP_CPP_PLAYL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Win32MusicBrowser.cpp

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\Win32MusicBrowser.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\Win32MusicBrowser.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	

"$(INTDIR)\Win32MusicBrowser.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\database.h"\
	"..\..\..\..\base\include\debug.h"\
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
	"..\include\dataindex.h"\
	"..\include\win32musicbrowser.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\Win32MusicBrowser.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\res\musicbrowser.rc
DEP_RSC_MUSICB=\
	"..\res\active.ico"\
	"..\res\drag.cur"\
	"..\res\playing.bmp"\
	"..\res\toolbar.bmp"\
	

!IF  "$(CFG)" == "musicbrowser - Win32 Release"


"$(INTDIR)\musicbrowser.res" : $(SOURCE) $(DEP_RSC_MUSICB) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\musicbrowser.res" /i\
 "\Local\src\freeamp\ui\musicbrowser\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"


"$(INTDIR)\musicbrowser.res" : $(SOURCE) $(DEP_RSC_MUSICB) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\musicbrowser.res" /i\
 "\Local\src\freeamp\ui\musicbrowser\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"


"$(INTDIR)\musicbrowser.res" : $(SOURCE) $(DEP_RSC_MUSICB) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\musicbrowser.res" /i\
 "\Local\src\freeamp\ui\musicbrowser\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"


"$(INTDIR)\musicbrowser.res" : $(SOURCE) $(DEP_RSC_MUSICB) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\musicbrowser.res" /i\
 "\Local\src\freeamp\ui\musicbrowser\win32\res" /d "NDEBUG" $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

"fabaselib - Win32 Release" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fabaselib.mak CFG="fabaselib - Win32 Release" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"fabaselib - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fabaselib.mak\
 CFG="fabaselib - Win32 Release" RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

"fabaselib - Win32 Debug" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fabaselib.mak CFG="fabaselib - Win32 Debug" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"fabaselib - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fabaselib.mak CFG="fabaselib - Win32 Debug"\
 RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

"fabaselib - Win32 NASM Debug" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fabaselib.mak CFG="fabaselib - Win32 NASM Debug" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"fabaselib - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fabaselib.mak\
 CFG="fabaselib - Win32 NASM Debug" RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

"fabaselib - Win32 NASM Release" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\fabaselib.mak\
 CFG="fabaselib - Win32 NASM Release" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"fabaselib - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp\base\win32\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\fabaselib.mak\
 CFG="fabaselib - Win32 NASM Release" RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ENDIF 

!IF  "$(CFG)" == "musicbrowser - Win32 Release"

"gdbm - Win32 Release" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 Release" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"gdbm - Win32 ReleaseCLEAN" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 Release"\
 RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 Debug"

"gdbm - Win32 Debug" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 Debug" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"gdbm - Win32 DebugCLEAN" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 Debug" RECURSE=1\
 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Debug"

"gdbm - Win32 NASM Debug" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 NASM Debug" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"gdbm - Win32 NASM DebugCLEAN" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 NASM Debug"\
 RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ELSEIF  "$(CFG)" == "musicbrowser - Win32 NASM Release"

"gdbm - Win32 NASM Release" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\gdbm.mak CFG="gdbm - Win32 NASM Release" 
   cd "..\..\..\ui\musicbrowser\win32\prj"

"gdbm - Win32 NASM ReleaseCLEAN" : 
   cd "\Local\src\freeamp\lib\gdbm\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\gdbm.mak CFG="gdbm - Win32 NASM Release"\
 RECURSE=1 
   cd "..\..\..\ui\musicbrowser\win32\prj"

!ENDIF 


!ENDIF 

