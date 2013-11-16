# Microsoft Developer Studio Generated NMAKE File, Based on regex.dsp
!IF "$(CFG)" == ""
CFG=regex - Win32 Release
!MESSAGE Keine Konfiguration angegeben. regex - Win32 Release wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "regex - Win32 Release" && "$(CFG)" != "regex - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "regex.mak" CFG="regex - Win32 Release"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "regex - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "regex - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungÅltige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "regex - Win32 Release"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

ALL : "$(OUTDIR)\regex.dll"


CLEAN :
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regex.res"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\regex.dll"
	-@erase "$(OUTDIR)\regex.exp"
	-@erase "$(OUTDIR)\regex.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MT /w /W0 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "REGEX_MALLOC" /D "STDC_HEADERS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\regex.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\regex.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\regex.pdb" /machine:I386 /def:".\regex.def" /out:"$(OUTDIR)\regex.dll" /implib:"$(OUTDIR)\regex.lib" 
DEF_FILE= \
	".\regex.def"
LINK32_OBJS= \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\regex.res"

"$(OUTDIR)\regex.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "regex - Win32 Debug"

OUTDIR=.\..\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Debug
# End Custom Macros

ALL : "$(OUTDIR)\regex.dll" "$(OUTDIR)\regex.bsc"


CLEAN :
	-@erase "$(INTDIR)\regex.obj"
	-@erase "$(INTDIR)\regex.res"
	-@erase "$(INTDIR)\regex.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\regex.bsc"
	-@erase "$(OUTDIR)\regex.dll"
	-@erase "$(OUTDIR)\regex.exp"
	-@erase "$(OUTDIR)\regex.ilk"
	-@erase "$(OUTDIR)\regex.lib"
	-@erase "$(OUTDIR)\regex.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "REGEX_MALLOC" /D "STDC_HEADERS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\regex.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\regex.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\regex.sbr"

"$(OUTDIR)\regex.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\regex.pdb" /debug /machine:I386 /def:".\regex.def" /out:"$(OUTDIR)\regex.dll" /implib:"$(OUTDIR)\regex.lib" 
DEF_FILE= \
	".\regex.def"
LINK32_OBJS= \
	"$(INTDIR)\regex.obj" \
	"$(INTDIR)\regex.res"

"$(OUTDIR)\regex.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

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
!IF EXISTS("regex.dep")
!INCLUDE "regex.dep"
!ELSE 
!MESSAGE Warning: cannot find "regex.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "regex - Win32 Release" || "$(CFG)" == "regex - Win32 Debug"
SOURCE=.\regex.c

!IF  "$(CFG)" == "regex - Win32 Release"


"$(INTDIR)\regex.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "regex - Win32 Debug"


"$(INTDIR)\regex.obj"	"$(INTDIR)\regex.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\regex.rc

"$(INTDIR)\regex.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

