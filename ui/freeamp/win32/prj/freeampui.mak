# Microsoft Developer Studio Generated NMAKE File, Based on freeampui.dsp
!IF "$(CFG)" == ""
CFG=freeampui - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to freeampui - Win32 NASM\
 Debug.
!ENDIF 

!IF "$(CFG)" != "freeampui - Win32 Release" && "$(CFG)" !=\
 "freeampui - Win32 Debug" && "$(CFG)" != "freeampui - Win32 NASM Debug" &&\
 "$(CFG)" != "freeampui - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "freeampui.mak" CFG="freeampui - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "freeampui - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "freeampui - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "freeampui - Win32 NASM Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "freeampui - Win32 NASM Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "freeampui - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\freeamp.ui"

!ELSE 

ALL : "zlib - Win32 Release" ".\freeamp.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"zlib - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Bitmap.obj"
	-@erase "$(INTDIR)\ButtonControl.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\DialControl.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FreeAmpTheme.obj"
	-@erase "$(INTDIR)\freeampui.res"
	-@erase "$(INTDIR)\MultiStateControl.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\SliderControl.obj"
	-@erase "$(INTDIR)\TextControl.obj"
	-@erase "$(INTDIR)\Theme.obj"
	-@erase "$(INTDIR)\ThemeManager.obj"
	-@erase "$(INTDIR)\ThemeZip.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\updatemanager.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\Win32Bitmap.obj"
	-@erase "$(INTDIR)\Win32Canvas.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32MessageDialog.obj"
	-@erase "$(INTDIR)\Win32PreferenceWindow.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\Win32Window.obj"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(OUTDIR)\freeamp.exp"
	-@erase "$(OUTDIR)\freeamp.lib"
	-@erase ".\freeamp.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\res" /I "..\include" /I\
 "..\..\include" /I "..\..\..\include" /I "..\..\..\..\io\include" /I\
 "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I\
 "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include"\
 /I "..\..\..\..\lib\gdbm" /I "..\..\..\..\lib\xml\include" /I\
 "..\..\..\..\lib\zlib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\freeampui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeampui.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeampui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib wsock32.lib winmm.lib comctl32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\freeamp.pdb"\
 /machine:I386 /def:".\freeampui.def" /out:"freeamp.ui"\
 /implib:"$(OUTDIR)\freeamp.lib" /libpath:"..\..\..\..\lib\zlib" 
DEF_FILE= \
	".\freeampui.def"
LINK32_OBJS= \
	"$(INTDIR)\Bitmap.obj" \
	"$(INTDIR)\ButtonControl.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\DialControl.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FreeAmpTheme.obj" \
	"$(INTDIR)\freeampui.res" \
	"$(INTDIR)\MultiStateControl.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\SliderControl.obj" \
	"$(INTDIR)\TextControl.obj" \
	"$(INTDIR)\Theme.obj" \
	"$(INTDIR)\ThemeManager.obj" \
	"$(INTDIR)\ThemeZip.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\updatemanager.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\Win32Bitmap.obj" \
	"$(INTDIR)\Win32Canvas.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32MessageDialog.obj" \
	"$(INTDIR)\Win32PreferenceWindow.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\Win32Window.obj" \
	"$(INTDIR)\Window.obj" \
	"..\..\..\..\lib\zlib\zlib.lib"

".\freeamp.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "zlib - Win32 Release" ".\freeamp.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                           ..\..\..\..\base\win32\prj\plugins
	copy freeamp.ui                          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\freeamp.ui"

!ELSE 

ALL : "zlib - Win32 Debug" ".\freeamp.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"zlib - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Bitmap.obj"
	-@erase "$(INTDIR)\ButtonControl.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\DialControl.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FreeAmpTheme.obj"
	-@erase "$(INTDIR)\freeampui.res"
	-@erase "$(INTDIR)\MultiStateControl.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\SliderControl.obj"
	-@erase "$(INTDIR)\TextControl.obj"
	-@erase "$(INTDIR)\Theme.obj"
	-@erase "$(INTDIR)\ThemeManager.obj"
	-@erase "$(INTDIR)\ThemeZip.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\updatemanager.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\Win32Bitmap.obj"
	-@erase "$(INTDIR)\Win32Canvas.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32MessageDialog.obj"
	-@erase "$(INTDIR)\Win32PreferenceWindow.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\Win32Window.obj"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(OUTDIR)\freeamp.exp"
	-@erase "$(OUTDIR)\freeamp.lib"
	-@erase "$(OUTDIR)\freeamp.pdb"
	-@erase ".\freeamp.ilk"
	-@erase ".\freeamp.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\res" /I "..\include" /I\
 "..\..\include" /I "..\..\..\include" /I "..\..\..\..\io\include" /I\
 "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I\
 "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include"\
 /I "..\..\..\..\lib\gdbm" /I "..\..\..\..\lib\xml\include" /I\
 "..\..\..\..\lib\zlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\freeampui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeampui.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeampui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib wsock32.lib winmm.lib comctl32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\freeamp.pdb" /debug\
 /machine:I386 /def:".\freeampui.def" /out:"freeamp.ui"\
 /implib:"$(OUTDIR)\freeamp.lib" /pdbtype:sept /libpath:"..\..\..\..\lib\zlib" 
DEF_FILE= \
	".\freeampui.def"
LINK32_OBJS= \
	"$(INTDIR)\Bitmap.obj" \
	"$(INTDIR)\ButtonControl.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\DialControl.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FreeAmpTheme.obj" \
	"$(INTDIR)\freeampui.res" \
	"$(INTDIR)\MultiStateControl.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\SliderControl.obj" \
	"$(INTDIR)\TextControl.obj" \
	"$(INTDIR)\Theme.obj" \
	"$(INTDIR)\ThemeManager.obj" \
	"$(INTDIR)\ThemeZip.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\updatemanager.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\Win32Bitmap.obj" \
	"$(INTDIR)\Win32Canvas.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32MessageDialog.obj" \
	"$(INTDIR)\Win32PreferenceWindow.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\Win32Window.obj" \
	"$(INTDIR)\Window.obj" \
	"..\..\..\..\lib\zlib\zlib.lib"

".\freeamp.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "zlib - Win32 Debug" ".\freeamp.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                           ..\..\..\..\base\win32\prj\plugins
	copy freeamp.ui                          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\freeamp.ui"

!ELSE 

ALL : "zlib - Win32 NASM Debug" ".\freeamp.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"zlib - Win32 NASM DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Bitmap.obj"
	-@erase "$(INTDIR)\ButtonControl.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\DialControl.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FreeAmpTheme.obj"
	-@erase "$(INTDIR)\freeampui.res"
	-@erase "$(INTDIR)\MultiStateControl.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\SliderControl.obj"
	-@erase "$(INTDIR)\TextControl.obj"
	-@erase "$(INTDIR)\Theme.obj"
	-@erase "$(INTDIR)\ThemeManager.obj"
	-@erase "$(INTDIR)\ThemeZip.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\updatemanager.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\Win32Bitmap.obj"
	-@erase "$(INTDIR)\Win32Canvas.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32MessageDialog.obj"
	-@erase "$(INTDIR)\Win32PreferenceWindow.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\Win32Window.obj"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(OUTDIR)\freeamp.exp"
	-@erase "$(OUTDIR)\freeamp.lib"
	-@erase "$(OUTDIR)\freeamp.pdb"
	-@erase ".\freeamp.ilk"
	-@erase ".\freeamp.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\res" /I "..\include" /I\
 "..\..\include" /I "..\..\..\include" /I "..\..\..\..\io\include" /I\
 "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I\
 "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include"\
 /I "..\..\..\..\lib\gdbm" /I "..\..\..\..\lib\xml\include" /I\
 "..\..\..\..\lib\zlib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\freeampui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeampui.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeampui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=zlib.lib wsock32.lib winmm.lib comctl32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\freeamp.pdb" /debug\
 /machine:I386 /def:".\freeampui.def" /out:"freeamp.ui"\
 /implib:"$(OUTDIR)\freeamp.lib" /pdbtype:sept /libpath:"..\..\..\..\lib\zlib" 
DEF_FILE= \
	".\freeampui.def"
LINK32_OBJS= \
	"$(INTDIR)\Bitmap.obj" \
	"$(INTDIR)\ButtonControl.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\DialControl.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FreeAmpTheme.obj" \
	"$(INTDIR)\freeampui.res" \
	"$(INTDIR)\MultiStateControl.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\SliderControl.obj" \
	"$(INTDIR)\TextControl.obj" \
	"$(INTDIR)\Theme.obj" \
	"$(INTDIR)\ThemeManager.obj" \
	"$(INTDIR)\ThemeZip.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\updatemanager.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\Win32Bitmap.obj" \
	"$(INTDIR)\Win32Canvas.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32MessageDialog.obj" \
	"$(INTDIR)\Win32PreferenceWindow.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\Win32Window.obj" \
	"$(INTDIR)\Window.obj" \
	"..\..\..\..\lib\zlib\zlib.lib"

".\freeamp.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "zlib - Win32 NASM Debug" ".\freeamp.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                                           ..\..\..\..\base\win32\prj\plugins
	copy freeamp.ui                          ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\freeamp.ui"

!ELSE 

ALL : "zlib - Win32 NASM Release" ".\freeamp.ui"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"zlib - Win32 NASM ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Bitmap.obj"
	-@erase "$(INTDIR)\ButtonControl.obj"
	-@erase "$(INTDIR)\Canvas.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\debug.obj"
	-@erase "$(INTDIR)\DialControl.obj"
	-@erase "$(INTDIR)\Font.obj"
	-@erase "$(INTDIR)\FreeAmpTheme.obj"
	-@erase "$(INTDIR)\freeampui.res"
	-@erase "$(INTDIR)\MultiStateControl.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\Parse.obj"
	-@erase "$(INTDIR)\playlist.obj"
	-@erase "$(INTDIR)\preferences.obj"
	-@erase "$(INTDIR)\registrar.obj"
	-@erase "$(INTDIR)\registry.obj"
	-@erase "$(INTDIR)\semaphore.obj"
	-@erase "$(INTDIR)\SliderControl.obj"
	-@erase "$(INTDIR)\TextControl.obj"
	-@erase "$(INTDIR)\Theme.obj"
	-@erase "$(INTDIR)\ThemeManager.obj"
	-@erase "$(INTDIR)\ThemeZip.obj"
	-@erase "$(INTDIR)\thread.obj"
	-@erase "$(INTDIR)\updatemanager.obj"
	-@erase "$(INTDIR)\utility.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\Win32Bitmap.obj"
	-@erase "$(INTDIR)\Win32Canvas.obj"
	-@erase "$(INTDIR)\Win32Font.obj"
	-@erase "$(INTDIR)\Win32MessageDialog.obj"
	-@erase "$(INTDIR)\Win32PreferenceWindow.obj"
	-@erase "$(INTDIR)\win32prefs.obj"
	-@erase "$(INTDIR)\win32thread.obj"
	-@erase "$(INTDIR)\Win32Window.obj"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(OUTDIR)\freeamp.exp"
	-@erase "$(OUTDIR)\freeamp.lib"
	-@erase ".\freeamp.ui"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /Op /Ob2 /I "..\res" /I "..\include" /I\
 "..\..\include" /I "..\..\..\include" /I "..\..\..\..\io\include" /I\
 "..\..\..\..\base\include" /I "..\..\..\..\base\win32\include" /I\
 "..\..\..\..\config" /I "..\..\..\..\ui\include" /I "..\..\..\..\lmc\include"\
 /I "..\..\..\..\lib\gdbm" /I "..\..\..\..\lib\xml\include" /I\
 "..\..\..\..\lib\zlib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\freeampui.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\freeampui.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\freeampui.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=gdbm.lib wsock32.lib winmm.lib comctl32.lib kernel32.lib\
 user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib\
 ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo\
 /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\freeamp.pdb"\
 /machine:I386 /def:".\freeampui.def" /out:"freeamp.ui"\
 /implib:"$(OUTDIR)\freeamp.lib" /libpath:"..\..\..\..\lib\zlib" 
DEF_FILE= \
	".\freeampui.def"
LINK32_OBJS= \
	"$(INTDIR)\Bitmap.obj" \
	"$(INTDIR)\ButtonControl.obj" \
	"$(INTDIR)\Canvas.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\debug.obj" \
	"$(INTDIR)\DialControl.obj" \
	"$(INTDIR)\Font.obj" \
	"$(INTDIR)\FreeAmpTheme.obj" \
	"$(INTDIR)\freeampui.res" \
	"$(INTDIR)\MultiStateControl.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\Parse.obj" \
	"$(INTDIR)\playlist.obj" \
	"$(INTDIR)\preferences.obj" \
	"$(INTDIR)\registrar.obj" \
	"$(INTDIR)\registry.obj" \
	"$(INTDIR)\semaphore.obj" \
	"$(INTDIR)\SliderControl.obj" \
	"$(INTDIR)\TextControl.obj" \
	"$(INTDIR)\Theme.obj" \
	"$(INTDIR)\ThemeManager.obj" \
	"$(INTDIR)\ThemeZip.obj" \
	"$(INTDIR)\thread.obj" \
	"$(INTDIR)\updatemanager.obj" \
	"$(INTDIR)\utility.obj" \
	"$(INTDIR)\Win32Bitmap.obj" \
	"$(INTDIR)\Win32Canvas.obj" \
	"$(INTDIR)\Win32Font.obj" \
	"$(INTDIR)\Win32MessageDialog.obj" \
	"$(INTDIR)\Win32PreferenceWindow.obj" \
	"$(INTDIR)\win32prefs.obj" \
	"$(INTDIR)\win32thread.obj" \
	"$(INTDIR)\Win32Window.obj" \
	"$(INTDIR)\Window.obj" \
	"..\..\..\..\lib\zlib\zlib.lib"

".\freeamp.ui" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

$(DS_POSTBUILD_DEP) : "zlib - Win32 NASM Release" ".\freeamp.ui"
   IF NOT EXIST ..\..\..\..\base\win32\prj\plugins mkdir                ..\..\..\..\base\win32\prj\plugins
	copy freeamp.ui                ..\..\..\..\base\win32\prj\plugins
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "freeampui - Win32 Release" || "$(CFG)" ==\
 "freeampui - Win32 Debug" || "$(CFG)" == "freeampui - Win32 NASM Debug" ||\
 "$(CFG)" == "freeampui - Win32 NASM Release"
SOURCE=..\..\src\Bitmap.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_BITMA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	

"$(INTDIR)\Bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_BITMA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	

"$(INTDIR)\Bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_BITMA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	

"$(INTDIR)\Bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_BITMA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	

"$(INTDIR)\Bitmap.obj" : $(SOURCE) $(DEP_CPP_BITMA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\ButtonControl.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_BUTTO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\ButtonControl.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_BUTTO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\ButtonControl.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_BUTTO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\ButtonControl.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_BUTTO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\ButtonControl.obj" : $(SOURCE) $(DEP_CPP_BUTTO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\Canvas.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_CANVA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Canvas.obj" : $(SOURCE) $(DEP_CPP_CANVA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_CANVA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Canvas.obj" : $(SOURCE) $(DEP_CPP_CANVA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_CANVA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Canvas.obj" : $(SOURCE) $(DEP_CPP_CANVA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_CANVA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Canvas.obj" : $(SOURCE) $(DEP_CPP_CANVA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\Control.cpp
DEP_CPP_CONTR=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\Control.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\src\DialControl.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_DIALC=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\DialControl.obj" : $(SOURCE) $(DEP_CPP_DIALC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_DIALC=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\DialControl.obj" : $(SOURCE) $(DEP_CPP_DIALC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_DIALC=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\DialControl.obj" : $(SOURCE) $(DEP_CPP_DIALC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_DIALC=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\DialControl.obj" : $(SOURCE) $(DEP_CPP_DIALC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\Font.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_FONT_=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_FONT_=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_FONT_=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_FONT_=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	

"$(INTDIR)\Font.obj" : $(SOURCE) $(DEP_CPP_FONT_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\FreeAmpTheme.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_FREEA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\downloadformat.h"\
	"..\..\..\..\base\include\downloadmanager.h"\
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
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\include\ui.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\freeamptheme.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	
NODEP_CPP_FREEA=\
	"..\..\..\..\base\include\win32impl.h"\
	"..\..\src\BeOSPreferenceWindow.h"\
	"..\..\src\GTKPreferenceWindow.h"\
	"..\..\src\GTKUtility.h"\
	

"$(INTDIR)\FreeAmpTheme.obj" : $(SOURCE) $(DEP_CPP_FREEA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_FREEA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\downloadformat.h"\
	"..\..\..\..\base\include\downloadmanager.h"\
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
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\include\ui.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\freeamptheme.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	

"$(INTDIR)\FreeAmpTheme.obj" : $(SOURCE) $(DEP_CPP_FREEA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_FREEA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\downloadformat.h"\
	"..\..\..\..\base\include\downloadmanager.h"\
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
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\include\ui.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\freeamptheme.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	

"$(INTDIR)\FreeAmpTheme.obj" : $(SOURCE) $(DEP_CPP_FREEA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_FREEA=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\downloadformat.h"\
	"..\..\..\..\base\include\downloadmanager.h"\
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
	"..\..\..\..\base\include\registrar.h"\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\include\ui.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\freeamptheme.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	
NODEP_CPP_FREEA=\
	"..\..\..\..\base\include\win32impl.h"\
	"..\..\src\BeOSPreferenceWindow.h"\
	"..\..\src\GTKPreferenceWindow.h"\
	"..\..\src\GTKUtility.h"\
	

"$(INTDIR)\FreeAmpTheme.obj" : $(SOURCE) $(DEP_CPP_FREEA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\MultiStateControl.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_MULTI=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\MultiStateControl.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_MULTI=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\MultiStateControl.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_MULTI=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\MultiStateControl.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_MULTI=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\MultiStateControl.obj" : $(SOURCE) $(DEP_CPP_MULTI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\lib\xml\src\Parse.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_PARSE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_PARSE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_PARSE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_PARSE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	

"$(INTDIR)\Parse.obj" : $(SOURCE) $(DEP_CPP_PARSE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\SliderControl.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_SLIDE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\SliderControl.obj" : $(SOURCE) $(DEP_CPP_SLIDE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_SLIDE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\SliderControl.obj" : $(SOURCE) $(DEP_CPP_SLIDE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_SLIDE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\SliderControl.obj" : $(SOURCE) $(DEP_CPP_SLIDE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_SLIDE=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\SliderControl.obj" : $(SOURCE) $(DEP_CPP_SLIDE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\TextControl.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_TEXTC=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\TextControl.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_TEXTC=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\TextControl.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_TEXTC=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\TextControl.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_TEXTC=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\TextControl.obj" : $(SOURCE) $(DEP_CPP_TEXTC) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\Theme.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_THEME=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\themezip.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_THEME=\
	"..\..\src\BeOSBitmap.h"\
	"..\..\src\BeOSFont.h"\
	"..\..\src\BeOSWindow.h"\
	"..\..\src\GTKBitmap.h"\
	"..\..\src\GTKFont.h"\
	"..\..\src\GTKUtility.h"\
	"..\..\src\GTKWindow.h"\
	

"$(INTDIR)\Theme.obj" : $(SOURCE) $(DEP_CPP_THEME) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_THEME=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\themezip.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Theme.obj" : $(SOURCE) $(DEP_CPP_THEME) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_THEME=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\themezip.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Theme.obj" : $(SOURCE) $(DEP_CPP_THEME) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_THEME=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\buttoncontrol.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\dialcontrol.h"\
	"..\..\include\font.h"\
	"..\..\include\messagedialog.h"\
	"..\..\include\multistatecontrol.h"\
	"..\..\include\slidercontrol.h"\
	"..\..\include\textcontrol.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\themezip.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_THEME=\
	"..\..\src\BeOSBitmap.h"\
	"..\..\src\BeOSFont.h"\
	"..\..\src\BeOSWindow.h"\
	"..\..\src\GTKBitmap.h"\
	"..\..\src\GTKFont.h"\
	"..\..\src\GTKUtility.h"\
	"..\..\src\GTKWindow.h"\
	

"$(INTDIR)\Theme.obj" : $(SOURCE) $(DEP_CPP_THEME) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\ThemeManager.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_THEMEM=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\thememanager.h"\
	

"$(INTDIR)\ThemeManager.obj" : $(SOURCE) $(DEP_CPP_THEMEM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_THEMEM=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\thememanager.h"\
	

"$(INTDIR)\ThemeManager.obj" : $(SOURCE) $(DEP_CPP_THEMEM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_THEMEM=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\thememanager.h"\
	

"$(INTDIR)\ThemeManager.obj" : $(SOURCE) $(DEP_CPP_THEMEM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_THEMEM=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\thememanager.h"\
	

"$(INTDIR)\ThemeManager.obj" : $(SOURCE) $(DEP_CPP_THEMEM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\ThemeZip.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_THEMEZ=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	"..\..\include\themezip.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\ThemeZip.obj" : $(SOURCE) $(DEP_CPP_THEMEZ) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_THEMEZ=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	"..\..\include\themezip.h"\
	

"$(INTDIR)\ThemeZip.obj" : $(SOURCE) $(DEP_CPP_THEMEZ) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_THEMEZ=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	"..\..\include\themezip.h"\
	

"$(INTDIR)\ThemeZip.obj" : $(SOURCE) $(DEP_CPP_THEMEZ) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_THEMEZ=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	"..\..\include\themezip.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\ThemeZip.obj" : $(SOURCE) $(DEP_CPP_THEMEZ) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Win32Bitmap.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\include\win32bitmap.h"\
	

"$(INTDIR)\Win32Bitmap.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\include\win32bitmap.h"\
	

"$(INTDIR)\Win32Bitmap.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\include\win32bitmap.h"\
	

"$(INTDIR)\Win32Bitmap.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\include\win32bitmap.h"\
	

"$(INTDIR)\Win32Bitmap.obj" : $(SOURCE) $(DEP_CPP_WIN32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Win32Canvas.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32C=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Canvas.obj" : $(SOURCE) $(DEP_CPP_WIN32C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32C=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Canvas.obj" : $(SOURCE) $(DEP_CPP_WIN32C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32C=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Canvas.obj" : $(SOURCE) $(DEP_CPP_WIN32C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32C=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32font.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Canvas.obj" : $(SOURCE) $(DEP_CPP_WIN32C) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Win32Font.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32F=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	"..\include\win32font.h"\
	

"$(INTDIR)\Win32Font.obj" : $(SOURCE) $(DEP_CPP_WIN32F) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32F=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	"..\include\win32font.h"\
	

"$(INTDIR)\Win32Font.obj" : $(SOURCE) $(DEP_CPP_WIN32F) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32F=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	"..\include\win32font.h"\
	

"$(INTDIR)\Win32Font.obj" : $(SOURCE) $(DEP_CPP_WIN32F) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32F=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\config\config.h"\
	"..\..\include\font.h"\
	"..\include\win32font.h"\
	

"$(INTDIR)\Win32Font.obj" : $(SOURCE) $(DEP_CPP_WIN32F) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Win32MessageDialog.cpp
DEP_CPP_WIN32M=\
	"..\..\include\messagedialog.h"\
	

"$(INTDIR)\Win32MessageDialog.obj" : $(SOURCE) $(DEP_CPP_WIN32M) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\src\Win32PreferenceWindow.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32P=\
	"..\..\..\..\base\include\debug.h"\
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
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\base\win32\include\win32updatemanager.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	"..\include\win32window.h"\
	
NODEP_CPP_WIN32P=\
	"..\..\..\..\base\include\win32impl.h"\
	

"$(INTDIR)\Win32PreferenceWindow.obj" : $(SOURCE) $(DEP_CPP_WIN32P) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32P=\
	"..\..\..\..\base\include\debug.h"\
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
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\base\win32\include\win32updatemanager.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32PreferenceWindow.obj" : $(SOURCE) $(DEP_CPP_WIN32P) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32P=\
	"..\..\..\..\base\include\debug.h"\
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
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\base\win32\include\win32updatemanager.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32PreferenceWindow.obj" : $(SOURCE) $(DEP_CPP_WIN32P) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32P=\
	"..\..\..\..\base\include\debug.h"\
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
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\base\win32\include\win32updatemanager.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\preferencewindow.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32preferencewindow.h"\
	"..\include\win32window.h"\
	
NODEP_CPP_WIN32P=\
	"..\..\..\..\base\include\win32impl.h"\
	

"$(INTDIR)\Win32PreferenceWindow.obj" : $(SOURCE) $(DEP_CPP_WIN32P) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\Win32Window.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32W=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Window.obj" : $(SOURCE) $(DEP_CPP_WIN32W) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32W=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Window.obj" : $(SOURCE) $(DEP_CPP_WIN32W) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32W=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Window.obj" : $(SOURCE) $(DEP_CPP_WIN32W) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32W=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	"..\include\win32bitmap.h"\
	"..\include\win32canvas.h"\
	"..\include\win32window.h"\
	

"$(INTDIR)\Win32Window.obj" : $(SOURCE) $(DEP_CPP_WIN32W) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\src\Window.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WINDO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\Window.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WINDO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\Window.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WINDO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\Window.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WINDO=\
	"..\..\..\..\base\include\debug.h"\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\facontext.h"\
	"..\..\..\..\base\include\log.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\include\bitmap.h"\
	"..\..\include\canvas.h"\
	"..\..\include\control.h"\
	"..\..\include\font.h"\
	"..\..\include\theme.h"\
	"..\..\include\thememanager.h"\
	"..\..\include\window.h"\
	

"$(INTDIR)\Window.obj" : $(SOURCE) $(DEP_CPP_WINDO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\debug.cpp
DEP_CPP_DEBUG=\
	"..\..\..\..\base\include\debug.h"\
	

"$(INTDIR)\debug.obj" : $(SOURCE) $(DEP_CPP_DEBUG) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\mutex.cpp
DEP_CPP_MUTEX=\
	"..\..\..\..\base\win32\include\mutex.h"\
	

"$(INTDIR)\mutex.obj" : $(SOURCE) $(DEP_CPP_MUTEX) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\playlist.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

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


!ENDIF 

SOURCE=..\..\..\..\base\src\preferences.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_PREFE=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\preferences.obj" : $(SOURCE) $(DEP_CPP_PREFE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\registrar.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

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


!ENDIF 

SOURCE=..\..\..\..\base\src\registry.cpp
DEP_CPP_REGIST=\
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\registry.obj" : $(SOURCE) $(DEP_CPP_REGIST) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\win32\src\semaphore.cpp
DEP_CPP_SEMAP=\
	"..\..\..\..\base\win32\include\semaphore.h"\
	

"$(INTDIR)\semaphore.obj" : $(SOURCE) $(DEP_CPP_SEMAP) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\..\base\src\thread.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

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


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_THREA=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\thread.obj" : $(SOURCE) $(DEP_CPP_THREA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

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


!ENDIF 

SOURCE=..\..\..\..\base\src\updatemanager.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_UPDAT=\
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
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\updatemanager.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_UPDAT=\
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
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	

"$(INTDIR)\updatemanager.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_UPDAT=\
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
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	

"$(INTDIR)\updatemanager.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_UPDAT=\
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
	"..\..\..\..\base\include\registry.h"\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\include\updatemanager.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\base\win32\include\mutex.h"\
	"..\..\..\..\base\win32\include\semaphore.h"\
	"..\..\..\..\config\config.h"\
	"..\..\..\..\lib\xml\include\parse.h"\
	"..\..\..\..\lib\zlib\include\zconf.h"\
	"..\..\..\..\lib\zlib\include\zlib.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\updatemanager.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\src\utility.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_UTILI=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\config\config.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\utility.obj" : $(SOURCE) $(DEP_CPP_UTILI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_UTILI=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\utility.obj" : $(SOURCE) $(DEP_CPP_UTILI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_UTILI=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\utility.obj" : $(SOURCE) $(DEP_CPP_UTILI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_UTILI=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\include\utility.h"\
	"..\..\..\..\config\config.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	

"$(INTDIR)\utility.obj" : $(SOURCE) $(DEP_CPP_UTILI) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\win32\src\win32prefs.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32PR=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32PR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32PR=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32PR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32PR=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32PR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32PR=\
	"..\..\..\..\base\include\errors.h"\
	"..\..\..\..\base\include\preferences.h"\
	"..\..\..\..\base\win32\include\win32prefs.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32prefs.obj" : $(SOURCE) $(DEP_CPP_WIN32PR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\base\win32\src\win32thread.cpp

!IF  "$(CFG)" == "freeampui - Win32 Release"

DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

DEP_CPP_WIN32T=\
	"..\..\..\..\base\include\thread.h"\
	"..\..\..\..\base\win32\include\win32thread.h"\
	"..\..\..\..\config\config.h"\
	

"$(INTDIR)\win32thread.obj" : $(SOURCE) $(DEP_CPP_WIN32T) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\res\freeampui.rc
DEP_RSC_FREEAM=\
	"..\res\icon1.ico"\
	

!IF  "$(CFG)" == "freeampui - Win32 Release"


"$(INTDIR)\freeampui.res" : $(SOURCE) $(DEP_RSC_FREEAM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeampui.res" /i\
 "\FreeAmp\freeamp\ui\freeamp\win32\res" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"


"$(INTDIR)\freeampui.res" : $(SOURCE) $(DEP_RSC_FREEAM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeampui.res" /i\
 "\FreeAmp\freeamp\ui\freeamp\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"


"$(INTDIR)\freeampui.res" : $(SOURCE) $(DEP_RSC_FREEAM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeampui.res" /i\
 "\FreeAmp\freeamp\ui\freeamp\win32\res" /d "_DEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"


"$(INTDIR)\freeampui.res" : $(SOURCE) $(DEP_RSC_FREEAM) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\freeampui.res" /i\
 "\FreeAmp\freeamp\ui\freeamp\win32\res" /d "NDEBUG" $(SOURCE)


!ENDIF 

!IF  "$(CFG)" == "freeampui - Win32 Release"

"zlib - Win32 Release" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 Release" 
   cd "..\..\..\ui\freeamp\win32\prj"

"zlib - Win32 ReleaseCLEAN" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\zlib.mak CFG="zlib - Win32 Release"\
 RECURSE=1 
   cd "..\..\..\ui\freeamp\win32\prj"

!ELSEIF  "$(CFG)" == "freeampui - Win32 Debug"

"zlib - Win32 Debug" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 Debug" 
   cd "..\..\..\ui\freeamp\win32\prj"

"zlib - Win32 DebugCLEAN" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\zlib.mak CFG="zlib - Win32 Debug" RECURSE=1\
 
   cd "..\..\..\ui\freeamp\win32\prj"

!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Debug"

"zlib - Win32 NASM Debug" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 NASM Debug" 
   cd "..\..\..\ui\freeamp\win32\prj"

"zlib - Win32 NASM DebugCLEAN" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\zlib.mak CFG="zlib - Win32 NASM Debug"\
 RECURSE=1 
   cd "..\..\..\ui\freeamp\win32\prj"

!ELSEIF  "$(CFG)" == "freeampui - Win32 NASM Release"

"zlib - Win32 NASM Release" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) /F .\zlib.mak CFG="zlib - Win32 NASM Release" 
   cd "..\..\..\ui\freeamp\win32\prj"

"zlib - Win32 NASM ReleaseCLEAN" : 
   cd "\FreeAmp\freeamp\lib\zlib\prj"
   $(MAKE) /$(MAKEFLAGS) CLEAN /F .\zlib.mak CFG="zlib - Win32 NASM Release"\
 RECURSE=1 
   cd "..\..\..\ui\freeamp\win32\prj"

!ENDIF 


!ENDIF 

