# Microsoft Developer Studio Generated NMAKE File, Based on zlib.dsp
!IF "$(CFG)" == ""
CFG=zlib - Win32 NASM Debug
!MESSAGE No configuration specified. Defaulting to zlib - Win32 NASM Debug.
!ENDIF 

!IF "$(CFG)" != "zlib - Win32 Release" && "$(CFG)" != "zlib - Win32 Debug" &&\
 "$(CFG)" != "zlib - Win32 NASM Debug" && "$(CFG)" !=\
 "zlib - Win32 NASM Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "zlib.mak" CFG="zlib - Win32 NASM Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "zlib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 NASM Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "zlib - Win32 NASM Release" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe

!IF  "$(CFG)" == "zlib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\zlib.lib"

!ELSE 

ALL : ".\zlib.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\adler32.obj"
	-@erase "$(INTDIR)\compress.obj"
	-@erase "$(INTDIR)\crc32.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\gzio.obj"
	-@erase "$(INTDIR)\infblock.obj"
	-@erase "$(INTDIR)\infcodes.obj"
	-@erase "$(INTDIR)\inffast.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\inftrees.obj"
	-@erase "$(INTDIR)\infutil.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\uncompr.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\zutil.obj"
	-@erase ".\zlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\zlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\zlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"zlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adler32.obj" \
	"$(INTDIR)\compress.obj" \
	"$(INTDIR)\crc32.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\gzio.obj" \
	"$(INTDIR)\infblock.obj" \
	"$(INTDIR)\infcodes.obj" \
	"$(INTDIR)\inffast.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\inftrees.obj" \
	"$(INTDIR)\infutil.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\uncompr.obj" \
	"$(INTDIR)\zutil.obj"

".\zlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\zlib.lib"

!ELSE 

ALL : ".\zlib.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\adler32.obj"
	-@erase "$(INTDIR)\compress.obj"
	-@erase "$(INTDIR)\crc32.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\gzio.obj"
	-@erase "$(INTDIR)\infblock.obj"
	-@erase "$(INTDIR)\infcodes.obj"
	-@erase "$(INTDIR)\inffast.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\inftrees.obj"
	-@erase "$(INTDIR)\infutil.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\uncompr.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\zutil.obj"
	-@erase ".\zlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\zlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\zlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"zlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adler32.obj" \
	"$(INTDIR)\compress.obj" \
	"$(INTDIR)\crc32.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\gzio.obj" \
	"$(INTDIR)\infblock.obj" \
	"$(INTDIR)\infcodes.obj" \
	"$(INTDIR)\inffast.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\inftrees.obj" \
	"$(INTDIR)\infutil.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\uncompr.obj" \
	"$(INTDIR)\zutil.obj"

".\zlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

!IF "$(RECURSE)" == "0" 

ALL : ".\zlib.lib"

!ELSE 

ALL : ".\zlib.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\adler32.obj"
	-@erase "$(INTDIR)\compress.obj"
	-@erase "$(INTDIR)\crc32.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\gzio.obj"
	-@erase "$(INTDIR)\infblock.obj"
	-@erase "$(INTDIR)\infcodes.obj"
	-@erase "$(INTDIR)\inffast.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\inftrees.obj"
	-@erase "$(INTDIR)\infutil.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\uncompr.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\zutil.obj"
	-@erase ".\zlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /GX /Z7 /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /Fp"$(INTDIR)\zlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c\
 
CPP_OBJS=.\Debug/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\zlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"zlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adler32.obj" \
	"$(INTDIR)\compress.obj" \
	"$(INTDIR)\crc32.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\gzio.obj" \
	"$(INTDIR)\infblock.obj" \
	"$(INTDIR)\infcodes.obj" \
	"$(INTDIR)\inffast.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\inftrees.obj" \
	"$(INTDIR)\infutil.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\uncompr.obj" \
	"$(INTDIR)\zutil.obj"

".\zlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

OUTDIR=.\Release
INTDIR=.\Release

!IF "$(RECURSE)" == "0" 

ALL : ".\zlib.lib"

!ELSE 

ALL : ".\zlib.lib"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\adler32.obj"
	-@erase "$(INTDIR)\compress.obj"
	-@erase "$(INTDIR)\crc32.obj"
	-@erase "$(INTDIR)\deflate.obj"
	-@erase "$(INTDIR)\gzio.obj"
	-@erase "$(INTDIR)\infblock.obj"
	-@erase "$(INTDIR)\infcodes.obj"
	-@erase "$(INTDIR)\inffast.obj"
	-@erase "$(INTDIR)\inflate.obj"
	-@erase "$(INTDIR)\inftrees.obj"
	-@erase "$(INTDIR)\infutil.obj"
	-@erase "$(INTDIR)\trees.obj"
	-@erase "$(INTDIR)\uncompr.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\zutil.obj"
	-@erase ".\zlib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\zlib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\zlib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"zlib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\adler32.obj" \
	"$(INTDIR)\compress.obj" \
	"$(INTDIR)\crc32.obj" \
	"$(INTDIR)\deflate.obj" \
	"$(INTDIR)\gzio.obj" \
	"$(INTDIR)\infblock.obj" \
	"$(INTDIR)\infcodes.obj" \
	"$(INTDIR)\inffast.obj" \
	"$(INTDIR)\inflate.obj" \
	"$(INTDIR)\inftrees.obj" \
	"$(INTDIR)\infutil.obj" \
	"$(INTDIR)\trees.obj" \
	"$(INTDIR)\uncompr.obj" \
	"$(INTDIR)\zutil.obj"

".\zlib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
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


!IF "$(CFG)" == "zlib - Win32 Release" || "$(CFG)" == "zlib - Win32 Debug" ||\
 "$(CFG)" == "zlib - Win32 NASM Debug" || "$(CFG)" ==\
 "zlib - Win32 NASM Release"
SOURCE=..\src\adler32.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_ADLER=\
	"..\src\zlib.h"\
	

"$(INTDIR)\adler32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_ADLER=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\adler32.obj" : $(SOURCE) $(DEP_CPP_ADLER) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_ADLER=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\adler32.obj" : $(SOURCE) $(DEP_CPP_ADLER) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_ADLER=\
	"..\src\zlib.h"\
	

"$(INTDIR)\adler32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\compress.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_COMPR=\
	"..\src\zlib.h"\
	

"$(INTDIR)\compress.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_COMPR=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\compress.obj" : $(SOURCE) $(DEP_CPP_COMPR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_COMPR=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\compress.obj" : $(SOURCE) $(DEP_CPP_COMPR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_COMPR=\
	"..\src\zlib.h"\
	

"$(INTDIR)\compress.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\crc32.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_CRC32=\
	"..\src\zlib.h"\
	

"$(INTDIR)\crc32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_CRC32=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\crc32.obj" : $(SOURCE) $(DEP_CPP_CRC32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_CRC32=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\crc32.obj" : $(SOURCE) $(DEP_CPP_CRC32) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_CRC32=\
	"..\src\zlib.h"\
	

"$(INTDIR)\crc32.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\deflate.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_DEFLA=\
	"..\src\deflate.h"\
	

"$(INTDIR)\deflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_DEFLA=\
	"..\include\deflate.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\deflate.obj" : $(SOURCE) $(DEP_CPP_DEFLA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_DEFLA=\
	"..\include\deflate.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\deflate.obj" : $(SOURCE) $(DEP_CPP_DEFLA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_DEFLA=\
	"..\src\deflate.h"\
	

"$(INTDIR)\deflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\gzio.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_GZIO_=\
	"..\src\zutil.h"\
	

"$(INTDIR)\gzio.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_GZIO_=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\gzio.obj" : $(SOURCE) $(DEP_CPP_GZIO_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_GZIO_=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\gzio.obj" : $(SOURCE) $(DEP_CPP_GZIO_) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_GZIO_=\
	"..\src\zutil.h"\
	

"$(INTDIR)\gzio.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\infblock.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_INFBL=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\infblock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_INFBL=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\infblock.obj" : $(SOURCE) $(DEP_CPP_INFBL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_INFBL=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\infblock.obj" : $(SOURCE) $(DEP_CPP_INFBL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_INFBL=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\infblock.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\infcodes.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_INFCO=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inffast.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\infcodes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_INFCO=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inffast.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\infcodes.obj" : $(SOURCE) $(DEP_CPP_INFCO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_INFCO=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inffast.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\infcodes.obj" : $(SOURCE) $(DEP_CPP_INFCO) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_INFCO=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inffast.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\infcodes.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\inffast.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_INFFA=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inffast.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\inffast.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_INFFA=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inffast.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\inffast.obj" : $(SOURCE) $(DEP_CPP_INFFA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_INFFA=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inffast.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\inffast.obj" : $(SOURCE) $(DEP_CPP_INFFA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_INFFA=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inffast.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\inffast.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\inflate.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_INFLA=\
	"..\src\infblock.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\inflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_INFLA=\
	"..\include\infblock.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\inflate.obj" : $(SOURCE) $(DEP_CPP_INFLA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_INFLA=\
	"..\include\infblock.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\inflate.obj" : $(SOURCE) $(DEP_CPP_INFLA) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_INFLA=\
	"..\src\infblock.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\inflate.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\inftrees.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_INFTR=\
	"..\src\inffixed.h"\
	"..\src\inftrees.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\inftrees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_INFTR=\
	"..\include\inffixed.h"\
	"..\include\inftrees.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\inftrees.obj" : $(SOURCE) $(DEP_CPP_INFTR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_INFTR=\
	"..\include\inffixed.h"\
	"..\include\inftrees.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\inftrees.obj" : $(SOURCE) $(DEP_CPP_INFTR) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_INFTR=\
	"..\src\inffixed.h"\
	"..\src\inftrees.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\inftrees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\infutil.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_INFUT=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\infutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_INFUT=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\infutil.obj" : $(SOURCE) $(DEP_CPP_INFUT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_INFUT=\
	"..\include\infblock.h"\
	"..\include\infcodes.h"\
	"..\include\inftrees.h"\
	"..\include\infutil.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\infutil.obj" : $(SOURCE) $(DEP_CPP_INFUT) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_INFUT=\
	"..\src\infblock.h"\
	"..\src\infcodes.h"\
	"..\src\inftrees.h"\
	"..\src\infutil.h"\
	"..\src\zutil.h"\
	

"$(INTDIR)\infutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\trees.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_TREES=\
	"..\src\deflate.h"\
	"..\src\trees.h"\
	

"$(INTDIR)\trees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_TREES=\
	"..\include\deflate.h"\
	"..\include\trees.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\trees.obj" : $(SOURCE) $(DEP_CPP_TREES) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_TREES=\
	"..\include\deflate.h"\
	"..\include\trees.h"\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\trees.obj" : $(SOURCE) $(DEP_CPP_TREES) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_TREES=\
	"..\src\deflate.h"\
	"..\src\trees.h"\
	

"$(INTDIR)\trees.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\uncompr.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_UNCOM=\
	"..\src\zlib.h"\
	

"$(INTDIR)\uncompr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_UNCOM=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\uncompr.obj" : $(SOURCE) $(DEP_CPP_UNCOM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_UNCOM=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	

"$(INTDIR)\uncompr.obj" : $(SOURCE) $(DEP_CPP_UNCOM) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_UNCOM=\
	"..\src\zlib.h"\
	

"$(INTDIR)\uncompr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\src\zutil.c

!IF  "$(CFG)" == "zlib - Win32 Release"

NODEP_CPP_ZUTIL=\
	"..\src\zutil.h"\
	

"$(INTDIR)\zutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 Debug"

DEP_CPP_ZUTIL=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\zutil.obj" : $(SOURCE) $(DEP_CPP_ZUTIL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Debug"

DEP_CPP_ZUTIL=\
	"..\include\zconf.h"\
	"..\include\zlib.h"\
	"..\include\zutil.h"\
	

"$(INTDIR)\zutil.obj" : $(SOURCE) $(DEP_CPP_ZUTIL) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "zlib - Win32 NASM Release"

NODEP_CPP_ZUTIL=\
	"..\src\zutil.h"\
	

"$(INTDIR)\zutil.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

