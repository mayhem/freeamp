# Microsoft Developer Studio Generated NMAKE File, Based on netscape.dsp
!IF "$(CFG)" == ""
CFG=netscape - Win32 Debug
!MESSAGE No configuration specified. Defaulting to netscape - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "netscape - Win32 Release" && "$(CFG)" !=\
 "netscape - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "netscape.mak" CFG="netscape - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "netscape - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "netscape - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "netscape - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\..\..\..\..\program files\communicator\program\plugins\NPfreeamp.dll"

!ELSE 

ALL : "..\..\..\..\..\program files\communicator\program\plugins\NPfreeamp.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\npfreeamp.obj"
	-@erase "$(INTDIR)\npfreeamp.res"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\NPfreeamp.exp"
	-@erase "$(OUTDIR)\NPfreeamp.lib"
	-@erase "..\..\..\..\..\program files\communicator\program\plugins\NPfreeamp.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "\PluginSDK\include" /I "..\..\..\config"\
 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\netscape.pch" /YX\
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\npfreeamp.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netscape.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\NPfreeamp.pdb" /machine:I386 /def:"..\src\npfreeamp.def"\
 /out:"d:\program files\communicator\program\plugins\NPfreeamp.dll"\
 /implib:"$(OUTDIR)\NPfreeamp.lib" 
DEF_FILE= \
	"..\src\npfreeamp.def"
LINK32_OBJS= \
	"$(INTDIR)\npfreeamp.obj" \
	"$(INTDIR)\npfreeamp.res" \
	"$(INTDIR)\npwin.obj"

"..\..\..\..\..\program files\communicator\program\plugins\NPfreeamp.dll" : \
"$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "netscape - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : \
"..\..\..\..\..\program files\netscape\communicator\program\plugins\NPfreeamp.dll"

!ELSE 

ALL : \
"..\..\..\..\..\program files\netscape\communicator\program\plugins\NPfreeamp.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\npfreeamp.obj"
	-@erase "$(INTDIR)\npfreeamp.res"
	-@erase "$(INTDIR)\npwin.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\NPfreeamp.exp"
	-@erase "$(OUTDIR)\NPfreeamp.lib"
	-@erase "$(OUTDIR)\NPfreeamp.pdb"
	-@erase "..\..\..\..\..\program files\netscape\communicator\program\plugins\NPfreeamp.dll"
	-@erase "..\..\..\..\..\program files\netscape\communicator\program\plugins\NPfreeamp.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /I "\PluginSDK\include" /I\
 "..\..\..\config" /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\netscape.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\npfreeamp.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\netscape.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\NPfreeamp.pdb" /debug /machine:I386 /def:"..\src\npfreeamp.def"\
 /out:"d:\program files\netscape\communicator\program\plugins\NPfreeamp.dll"\
 /implib:"$(OUTDIR)\NPfreeamp.lib" /pdbtype:sept 
DEF_FILE= \
	"..\src\npfreeamp.def"
LINK32_OBJS= \
	"$(INTDIR)\npfreeamp.obj" \
	"$(INTDIR)\npfreeamp.res" \
	"$(INTDIR)\npwin.obj"

"..\..\..\..\..\program files\netscape\communicator\program\plugins\NPfreeamp.dll"\
 : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "netscape - Win32 Release" || "$(CFG)" ==\
 "netscape - Win32 Debug"
SOURCE=..\src\npfreeamp.c

!IF  "$(CFG)" == "netscape - Win32 Release"

DEP_CPP_NPFRE=\
	"..\..\..\..\..\PluginSDK\include\jri.h"\
	"..\..\..\..\..\PluginSDK\include\jri_md.h"\
	"..\..\..\..\..\PluginSDK\include\jritypes.h"\
	"..\..\..\..\..\PluginSDK\include\npapi.h"\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\npfreeamp.obj" : $(SOURCE) $(DEP_CPP_NPFRE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "netscape - Win32 Debug"

DEP_CPP_NPFRE=\
	"..\..\..\..\..\PluginSDK\include\jri.h"\
	"..\..\..\..\..\PluginSDK\include\jri_md.h"\
	"..\..\..\..\..\PluginSDK\include\jritypes.h"\
	"..\..\..\..\..\PluginSDK\include\npapi.h"\
	"..\..\..\config\config.h"\
	

"$(INTDIR)\npfreeamp.obj" : $(SOURCE) $(DEP_CPP_NPFRE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\npfreeamp.rc
DEP_RSC_NPFREE=\
	"..\src\emusic.bmp"\
	"..\src\freeamp.bmp"\
	

!IF  "$(CFG)" == "netscape - Win32 Release"


"$(INTDIR)\npfreeamp.res" : $(SOURCE) $(DEP_RSC_NPFREE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\npfreeamp.res" /i\
 "\FreeAmp\freeamp\netscape\win32\src" /d "NDEBUG" $(SOURCE)


!ELSEIF  "$(CFG)" == "netscape - Win32 Debug"


"$(INTDIR)\npfreeamp.res" : $(SOURCE) $(DEP_RSC_NPFREE) "$(INTDIR)"
	$(RSC) /l 0x409 /fo"$(INTDIR)\npfreeamp.res" /i\
 "\FreeAmp\freeamp\netscape\win32\src" /d "_DEBUG" $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\..\PluginSDK\Common\npwin.cpp

!IF  "$(CFG)" == "netscape - Win32 Release"

DEP_CPP_NPWIN=\
	"..\..\..\..\..\PluginSDK\include\jri.h"\
	"..\..\..\..\..\PluginSDK\include\jri_md.h"\
	"..\..\..\..\..\PluginSDK\include\jritypes.h"\
	"..\..\..\..\..\PluginSDK\include\npapi.h"\
	"..\..\..\..\..\PluginSDK\include\npupp.h"\
	

"$(INTDIR)\npwin.obj" : $(SOURCE) $(DEP_CPP_NPWIN) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "netscape - Win32 Debug"

DEP_CPP_NPWIN=\
	"..\..\..\..\..\PluginSDK\include\jri.h"\
	"..\..\..\..\..\PluginSDK\include\jri_md.h"\
	"..\..\..\..\..\PluginSDK\include\jritypes.h"\
	"..\..\..\..\..\PluginSDK\include\npapi.h"\
	"..\..\..\..\..\PluginSDK\include\npupp.h"\
	

"$(INTDIR)\npwin.obj" : $(SOURCE) $(DEP_CPP_NPWIN) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

