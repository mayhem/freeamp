# Microsoft Developer Studio Generated NMAKE File, Based on gdbm.dsp
!IF "$(CFG)" == ""
CFG=gdbm - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to gdbm - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "gdbm - Win32 Release" && "$(CFG)" != "gdbm - Win32 Debug" &&\
 "$(CFG)" != "gdbm - Win32 NASM Release" && "$(CFG)" !=\
 "gdbm - Win32 NASM Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "gdbm.mak" CFG="gdbm - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "gdbm - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gdbm - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "gdbm - Win32 NASM Release" (based on "Win32 (x86) Static Library")
!MESSAGE "gdbm - Win32 NASM Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe

!IF  "$(CFG)" == "gdbm - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\gdbm.lib"

!ELSE 

ALL : "..\gdbm.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bucket.obj"
	-@erase "$(INTDIR)\falloc.obj"
	-@erase "$(INTDIR)\findkey.obj"
	-@erase "$(INTDIR)\gdbmclose.obj"
	-@erase "$(INTDIR)\gdbmdelete.obj"
	-@erase "$(INTDIR)\gdbmerrno.obj"
	-@erase "$(INTDIR)\gdbmexists.obj"
	-@erase "$(INTDIR)\gdbmfdesc.obj"
	-@erase "$(INTDIR)\gdbmfetch.obj"
	-@erase "$(INTDIR)\gdbmopen.obj"
	-@erase "$(INTDIR)\gdbmreorg.obj"
	-@erase "$(INTDIR)\gdbmseq.obj"
	-@erase "$(INTDIR)\gdbmsetopt.obj"
	-@erase "$(INTDIR)\gdbmstore.obj"
	-@erase "$(INTDIR)\gdbmsync.obj"
	-@erase "$(INTDIR)\global.obj"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\update.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "..\gdbm.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\\" /I "..\config" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\gdbm.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gdbm.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\gdbm.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bucket.obj" \
	"$(INTDIR)\falloc.obj" \
	"$(INTDIR)\findkey.obj" \
	"$(INTDIR)\gdbmclose.obj" \
	"$(INTDIR)\gdbmdelete.obj" \
	"$(INTDIR)\gdbmerrno.obj" \
	"$(INTDIR)\gdbmexists.obj" \
	"$(INTDIR)\gdbmfdesc.obj" \
	"$(INTDIR)\gdbmfetch.obj" \
	"$(INTDIR)\gdbmopen.obj" \
	"$(INTDIR)\gdbmreorg.obj" \
	"$(INTDIR)\gdbmseq.obj" \
	"$(INTDIR)\gdbmsetopt.obj" \
	"$(INTDIR)\gdbmstore.obj" \
	"$(INTDIR)\gdbmsync.obj" \
	"$(INTDIR)\global.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\update.obj" \
	"$(INTDIR)\version.obj"

"..\gdbm.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\gdbm.lib"

!ELSE 

ALL : "..\gdbm.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bucket.obj"
	-@erase "$(INTDIR)\falloc.obj"
	-@erase "$(INTDIR)\findkey.obj"
	-@erase "$(INTDIR)\gdbmclose.obj"
	-@erase "$(INTDIR)\gdbmdelete.obj"
	-@erase "$(INTDIR)\gdbmerrno.obj"
	-@erase "$(INTDIR)\gdbmexists.obj"
	-@erase "$(INTDIR)\gdbmfdesc.obj"
	-@erase "$(INTDIR)\gdbmfetch.obj"
	-@erase "$(INTDIR)\gdbmopen.obj"
	-@erase "$(INTDIR)\gdbmreorg.obj"
	-@erase "$(INTDIR)\gdbmseq.obj"
	-@erase "$(INTDIR)\gdbmsetopt.obj"
	-@erase "$(INTDIR)\gdbmstore.obj"
	-@erase "$(INTDIR)\gdbmsync.obj"
	-@erase "$(INTDIR)\global.obj"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\update.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "..\gdbm.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I ".\\" /I "..\\" /I "..\config" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\gdbm.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gdbm.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\gdbm.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bucket.obj" \
	"$(INTDIR)\falloc.obj" \
	"$(INTDIR)\findkey.obj" \
	"$(INTDIR)\gdbmclose.obj" \
	"$(INTDIR)\gdbmdelete.obj" \
	"$(INTDIR)\gdbmerrno.obj" \
	"$(INTDIR)\gdbmexists.obj" \
	"$(INTDIR)\gdbmfdesc.obj" \
	"$(INTDIR)\gdbmfetch.obj" \
	"$(INTDIR)\gdbmopen.obj" \
	"$(INTDIR)\gdbmreorg.obj" \
	"$(INTDIR)\gdbmseq.obj" \
	"$(INTDIR)\gdbmsetopt.obj" \
	"$(INTDIR)\gdbmstore.obj" \
	"$(INTDIR)\gdbmsync.obj" \
	"$(INTDIR)\global.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\update.obj" \
	"$(INTDIR)\version.obj"

"..\gdbm.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : "..\gdbm.lib"

!ELSE 

ALL : "..\gdbm.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bucket.obj"
	-@erase "$(INTDIR)\falloc.obj"
	-@erase "$(INTDIR)\findkey.obj"
	-@erase "$(INTDIR)\gdbmclose.obj"
	-@erase "$(INTDIR)\gdbmdelete.obj"
	-@erase "$(INTDIR)\gdbmerrno.obj"
	-@erase "$(INTDIR)\gdbmexists.obj"
	-@erase "$(INTDIR)\gdbmfdesc.obj"
	-@erase "$(INTDIR)\gdbmfetch.obj"
	-@erase "$(INTDIR)\gdbmopen.obj"
	-@erase "$(INTDIR)\gdbmreorg.obj"
	-@erase "$(INTDIR)\gdbmseq.obj"
	-@erase "$(INTDIR)\gdbmsetopt.obj"
	-@erase "$(INTDIR)\gdbmstore.obj"
	-@erase "$(INTDIR)\gdbmsync.obj"
	-@erase "$(INTDIR)\global.obj"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\update.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "..\gdbm.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I ".\\" /I "..\\" /I "..\config" /D "WIN32"\
 /D "NDEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\gdbm.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gdbm.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\gdbm.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bucket.obj" \
	"$(INTDIR)\falloc.obj" \
	"$(INTDIR)\findkey.obj" \
	"$(INTDIR)\gdbmclose.obj" \
	"$(INTDIR)\gdbmdelete.obj" \
	"$(INTDIR)\gdbmerrno.obj" \
	"$(INTDIR)\gdbmexists.obj" \
	"$(INTDIR)\gdbmfdesc.obj" \
	"$(INTDIR)\gdbmfetch.obj" \
	"$(INTDIR)\gdbmopen.obj" \
	"$(INTDIR)\gdbmreorg.obj" \
	"$(INTDIR)\gdbmseq.obj" \
	"$(INTDIR)\gdbmsetopt.obj" \
	"$(INTDIR)\gdbmstore.obj" \
	"$(INTDIR)\gdbmsync.obj" \
	"$(INTDIR)\global.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\update.obj" \
	"$(INTDIR)\version.obj"

"..\gdbm.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : "..\gdbm.lib"

!ELSE 

ALL : "..\gdbm.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\bucket.obj"
	-@erase "$(INTDIR)\falloc.obj"
	-@erase "$(INTDIR)\findkey.obj"
	-@erase "$(INTDIR)\gdbmclose.obj"
	-@erase "$(INTDIR)\gdbmdelete.obj"
	-@erase "$(INTDIR)\gdbmerrno.obj"
	-@erase "$(INTDIR)\gdbmexists.obj"
	-@erase "$(INTDIR)\gdbmfdesc.obj"
	-@erase "$(INTDIR)\gdbmfetch.obj"
	-@erase "$(INTDIR)\gdbmopen.obj"
	-@erase "$(INTDIR)\gdbmreorg.obj"
	-@erase "$(INTDIR)\gdbmseq.obj"
	-@erase "$(INTDIR)\gdbmsetopt.obj"
	-@erase "$(INTDIR)\gdbmstore.obj"
	-@erase "$(INTDIR)\gdbmsync.obj"
	-@erase "$(INTDIR)\global.obj"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\update.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\version.obj"
	-@erase "..\gdbm.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I "..\config" /I ".\\" /I "..\\" /D\
 "WIN32" /D "_DEBUG" /D "_WINDOWS" /Fp"$(INTDIR)\gdbm.pch" /YX /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\gdbm.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"..\gdbm.lib" 
LIB32_OBJS= \
	"$(INTDIR)\bucket.obj" \
	"$(INTDIR)\falloc.obj" \
	"$(INTDIR)\findkey.obj" \
	"$(INTDIR)\gdbmclose.obj" \
	"$(INTDIR)\gdbmdelete.obj" \
	"$(INTDIR)\gdbmerrno.obj" \
	"$(INTDIR)\gdbmexists.obj" \
	"$(INTDIR)\gdbmfdesc.obj" \
	"$(INTDIR)\gdbmfetch.obj" \
	"$(INTDIR)\gdbmopen.obj" \
	"$(INTDIR)\gdbmreorg.obj" \
	"$(INTDIR)\gdbmseq.obj" \
	"$(INTDIR)\gdbmsetopt.obj" \
	"$(INTDIR)\gdbmstore.obj" \
	"$(INTDIR)\gdbmsync.obj" \
	"$(INTDIR)\global.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\update.obj" \
	"$(INTDIR)\version.obj"

"..\gdbm.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

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


!IF "$(CFG)" == "gdbm - Win32 Release" || "$(CFG)" == "gdbm - Win32 Debug" ||\
 "$(CFG)" == "gdbm - Win32 NASM Release" || "$(CFG)" ==\
 "gdbm - Win32 NASM Debug"
SOURCE=..\bucket.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_BUCKE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_BUCKE=\
	"..\config\config.h"\
	

"$(INTDIR)\bucket.obj" : $(SOURCE) $(DEP_CPP_BUCKE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_BUCKE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_BUCKE=\
	"..\config\config.h"\
	

"$(INTDIR)\bucket.obj" : $(SOURCE) $(DEP_CPP_BUCKE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_BUCKE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_BUCKE=\
	"..\config\config.h"\
	

"$(INTDIR)\bucket.obj" : $(SOURCE) $(DEP_CPP_BUCKE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_BUCKE=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\bucket.obj" : $(SOURCE) $(DEP_CPP_BUCKE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\config\config.win32

!IF  "$(CFG)" == "gdbm - Win32 Release"

InputPath=..\config\config.win32

"..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cp ..\config\config.win32 ..\config\config.h

!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

InputPath=..\config\config.win32

"..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cp ..\config\config.win32 ..\config\config.h

!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

InputPath=..\config\config.win32

"..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cp ..\config\config.win32 ..\config\config.h

!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

InputPath=..\config\config.win32

"..\config\config.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cp ..\config\config.win32 ..\config\config.h

!ENDIF 

SOURCE=..\falloc.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_FALLO=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_FALLO=\
	"..\config\config.h"\
	

"$(INTDIR)\falloc.obj" : $(SOURCE) $(DEP_CPP_FALLO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_FALLO=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_FALLO=\
	"..\config\config.h"\
	

"$(INTDIR)\falloc.obj" : $(SOURCE) $(DEP_CPP_FALLO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_FALLO=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_FALLO=\
	"..\config\config.h"\
	

"$(INTDIR)\falloc.obj" : $(SOURCE) $(DEP_CPP_FALLO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_FALLO=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\falloc.obj" : $(SOURCE) $(DEP_CPP_FALLO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\findkey.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_FINDK=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_FINDK=\
	"..\config\config.h"\
	

"$(INTDIR)\findkey.obj" : $(SOURCE) $(DEP_CPP_FINDK) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_FINDK=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_FINDK=\
	"..\config\config.h"\
	

"$(INTDIR)\findkey.obj" : $(SOURCE) $(DEP_CPP_FINDK) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_FINDK=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_FINDK=\
	"..\config\config.h"\
	

"$(INTDIR)\findkey.obj" : $(SOURCE) $(DEP_CPP_FINDK) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_FINDK=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\findkey.obj" : $(SOURCE) $(DEP_CPP_FINDK) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmclose.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMC=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMC=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmclose.obj" : $(SOURCE) $(DEP_CPP_GDBMC) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMC=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMC=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmclose.obj" : $(SOURCE) $(DEP_CPP_GDBMC) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMC=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMC=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmclose.obj" : $(SOURCE) $(DEP_CPP_GDBMC) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMC=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmclose.obj" : $(SOURCE) $(DEP_CPP_GDBMC) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmdelete.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMD=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMD=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmdelete.obj" : $(SOURCE) $(DEP_CPP_GDBMD) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMD=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMD=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmdelete.obj" : $(SOURCE) $(DEP_CPP_GDBMD) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMD=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMD=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmdelete.obj" : $(SOURCE) $(DEP_CPP_GDBMD) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMD=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmdelete.obj" : $(SOURCE) $(DEP_CPP_GDBMD) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmerrno.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBME=\
	"..\gdbmerrno.h"\
	
NODEP_CPP_GDBME=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmerrno.obj" : $(SOURCE) $(DEP_CPP_GDBME) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBME=\
	"..\gdbmerrno.h"\
	
NODEP_CPP_GDBME=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmerrno.obj" : $(SOURCE) $(DEP_CPP_GDBME) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBME=\
	"..\gdbmerrno.h"\
	
NODEP_CPP_GDBME=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmerrno.obj" : $(SOURCE) $(DEP_CPP_GDBME) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBME=\
	"..\config\config.h"\
	"..\gdbmerrno.h"\
	

"$(INTDIR)\gdbmerrno.obj" : $(SOURCE) $(DEP_CPP_GDBME) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmexists.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMEX=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMEX=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmexists.obj" : $(SOURCE) $(DEP_CPP_GDBMEX) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMEX=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMEX=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmexists.obj" : $(SOURCE) $(DEP_CPP_GDBMEX) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMEX=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMEX=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmexists.obj" : $(SOURCE) $(DEP_CPP_GDBMEX) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMEX=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmexists.obj" : $(SOURCE) $(DEP_CPP_GDBMEX) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmfdesc.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMF=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMF=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmfdesc.obj" : $(SOURCE) $(DEP_CPP_GDBMF) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMF=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMF=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmfdesc.obj" : $(SOURCE) $(DEP_CPP_GDBMF) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMF=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMF=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmfdesc.obj" : $(SOURCE) $(DEP_CPP_GDBMF) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMF=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmfdesc.obj" : $(SOURCE) $(DEP_CPP_GDBMF) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmfetch.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMFE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMFE=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmfetch.obj" : $(SOURCE) $(DEP_CPP_GDBMFE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMFE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMFE=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmfetch.obj" : $(SOURCE) $(DEP_CPP_GDBMFE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMFE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMFE=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmfetch.obj" : $(SOURCE) $(DEP_CPP_GDBMFE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMFE=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmfetch.obj" : $(SOURCE) $(DEP_CPP_GDBMFE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmopen.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMO=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMO=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmopen.obj" : $(SOURCE) $(DEP_CPP_GDBMO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMO=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMO=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmopen.obj" : $(SOURCE) $(DEP_CPP_GDBMO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMO=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMO=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmopen.obj" : $(SOURCE) $(DEP_CPP_GDBMO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMO=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmopen.obj" : $(SOURCE) $(DEP_CPP_GDBMO) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmreorg.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMR=\
	"..\extern.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMR=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmreorg.obj" : $(SOURCE) $(DEP_CPP_GDBMR) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMR=\
	"..\extern.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMR=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmreorg.obj" : $(SOURCE) $(DEP_CPP_GDBMR) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMR=\
	"..\extern.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMR=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmreorg.obj" : $(SOURCE) $(DEP_CPP_GDBMR) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMR=\
	"..\config\config.h"\
	"..\extern.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmreorg.obj" : $(SOURCE) $(DEP_CPP_GDBMR) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmseq.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMS=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMS=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmseq.obj" : $(SOURCE) $(DEP_CPP_GDBMS) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMS=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMS=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmseq.obj" : $(SOURCE) $(DEP_CPP_GDBMS) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMS=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMS=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmseq.obj" : $(SOURCE) $(DEP_CPP_GDBMS) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMS=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmseq.obj" : $(SOURCE) $(DEP_CPP_GDBMS) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmsetopt.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMSE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMSE=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmsetopt.obj" : $(SOURCE) $(DEP_CPP_GDBMSE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMSE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMSE=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmsetopt.obj" : $(SOURCE) $(DEP_CPP_GDBMSE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMSE=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMSE=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmsetopt.obj" : $(SOURCE) $(DEP_CPP_GDBMSE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMSE=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmsetopt.obj" : $(SOURCE) $(DEP_CPP_GDBMSE) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmstore.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMST=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMST=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmstore.obj" : $(SOURCE) $(DEP_CPP_GDBMST) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMST=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMST=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmstore.obj" : $(SOURCE) $(DEP_CPP_GDBMST) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMST=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMST=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmstore.obj" : $(SOURCE) $(DEP_CPP_GDBMST) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMST=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmstore.obj" : $(SOURCE) $(DEP_CPP_GDBMST) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\gdbmsync.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GDBMSY=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMSY=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmsync.obj" : $(SOURCE) $(DEP_CPP_GDBMSY) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GDBMSY=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GDBMSY=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmsync.obj" : $(SOURCE) $(DEP_CPP_GDBMSY) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GDBMSY=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GDBMSY=\
	"..\config\config.h"\
	

"$(INTDIR)\gdbmsync.obj" : $(SOURCE) $(DEP_CPP_GDBMSY) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GDBMSY=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\gdbmsync.obj" : $(SOURCE) $(DEP_CPP_GDBMSY) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\global.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_GLOBA=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GLOBA=\
	"..\config\config.h"\
	

"$(INTDIR)\global.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_GLOBA=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_GLOBA=\
	"..\config\config.h"\
	

"$(INTDIR)\global.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_GLOBA=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_GLOBA=\
	"..\config\config.h"\
	

"$(INTDIR)\global.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_GLOBA=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\gdbmerrno.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\global.obj" : $(SOURCE) $(DEP_CPP_GLOBA) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\hash.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_HASH_=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_HASH_=\
	"..\config\config.h"\
	

"$(INTDIR)\hash.obj" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_HASH_=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_HASH_=\
	"..\config\config.h"\
	

"$(INTDIR)\hash.obj" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_HASH_=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_HASH_=\
	"..\config\config.h"\
	

"$(INTDIR)\hash.obj" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_HASH_=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\hash.obj" : $(SOURCE) $(DEP_CPP_HASH_) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\update.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

DEP_CPP_UPDAT=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_UPDAT=\
	"..\config\config.h"\
	

"$(INTDIR)\update.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

DEP_CPP_UPDAT=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	
NODEP_CPP_UPDAT=\
	"..\config\config.h"\
	

"$(INTDIR)\update.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

DEP_CPP_UPDAT=\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	{$(INCLUDE)}"sys\stat.h"\
	{$(INCLUDE)}"sys\types.h"\
	
NODEP_CPP_UPDAT=\
	"..\config\config.h"\
	

"$(INTDIR)\update.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_UPDAT=\
	"..\config\config.h"\
	"..\gdbmconst.h"\
	"..\gdbmdefs.h"\
	"..\proto.h"\
	"..\systems.h"\
	

"$(INTDIR)\update.obj" : $(SOURCE) $(DEP_CPP_UPDAT) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\version.c

!IF  "$(CFG)" == "gdbm - Win32 Release"

NODEP_CPP_VERSI=\
	"..\config\config.h"\
	

"$(INTDIR)\version.obj" : $(SOURCE) "$(INTDIR)" "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 Debug"

NODEP_CPP_VERSI=\
	"..\config\config.h"\
	

"$(INTDIR)\version.obj" : $(SOURCE) "$(INTDIR)" "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Release"

NODEP_CPP_VERSI=\
	"..\config\config.h"\
	

"$(INTDIR)\version.obj" : $(SOURCE) "$(INTDIR)" "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "gdbm - Win32 NASM Debug"

DEP_CPP_VERSI=\
	"..\config\config.h"\
	

"$(INTDIR)\version.obj" : $(SOURCE) $(DEP_CPP_VERSI) "$(INTDIR)"\
 "..\config\config.h"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

