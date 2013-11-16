# Microsoft Developer Studio Generated NMAKE File, Based on lexbib.dsp
!IF "$(CFG)" == ""
CFG=lexbib - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. lexbib - Win32 Debug wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "lexbib - Win32 Release" && "$(CFG)" != "lexbib - Win32 Debug"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "lexbib.mak" CFG="lexbib - Win32 Debug"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "lexbib - Win32 Release" (basierend auf  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "lexbib - Win32 Debug" (basierend auf  "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "lexbib - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\lexbib.dll"


CLEAN :
	-@erase "$(INTDIR)\LexBib.obj"
	-@erase "$(INTDIR)\lexbib.res"
	-@erase "$(INTDIR)\PropSet.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WindowAccessor.obj"
	-@erase "$(OUTDIR)\lexbib.dll"
	-@erase "$(OUTDIR)\lexbib.exp"
	-@erase "$(OUTDIR)\lexbib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\scintilla\scintilla\include" /I "..\..\scintilla\scintilla\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LEXBIB_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0xc07 /fo"$(INTDIR)\lexbib.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\lexbib.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\scintilla\scintilla\bin\SciLexer.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\lexbib.pdb" /machine:I386 /def:".\lexbib.def" /out:"$(OUTDIR)\lexbib.dll" /implib:"$(OUTDIR)\lexbib.lib" 
DEF_FILE= \
	".\lexbib.def"
LINK32_OBJS= \
	"$(INTDIR)\LexBib.obj" \
	"$(INTDIR)\PropSet.obj" \
	"$(INTDIR)\WindowAccessor.obj" \
	"$(INTDIR)\lexbib.res"

"$(OUTDIR)\lexbib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
PostBuild_Desc=copy lexbib.dll
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\lexbib.dll"
   copyrel.bat
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "lexbib - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\lexbib.dll" "$(OUTDIR)\lexbib.bsc"


CLEAN :
	-@erase "$(INTDIR)\LexBib.obj"
	-@erase "$(INTDIR)\lexbib.res"
	-@erase "$(INTDIR)\LexBib.sbr"
	-@erase "$(INTDIR)\PropSet.obj"
	-@erase "$(INTDIR)\PropSet.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WindowAccessor.obj"
	-@erase "$(INTDIR)\WindowAccessor.sbr"
	-@erase "$(OUTDIR)\lexbib.bsc"
	-@erase "$(OUTDIR)\lexbib.dll"
	-@erase "$(OUTDIR)\lexbib.exp"
	-@erase "$(OUTDIR)\lexbib.ilk"
	-@erase "$(OUTDIR)\lexbib.lib"
	-@erase "$(OUTDIR)\lexbib.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\scintilla\scintilla\include" /I "..\..\scintilla\scintilla\src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LEXBIB_EXPORTS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0xc07 /fo"$(INTDIR)\lexbib.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\lexbib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\LexBib.sbr" \
	"$(INTDIR)\PropSet.sbr" \
	"$(INTDIR)\WindowAccessor.sbr"

"$(OUTDIR)\lexbib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\..\scintilla\scintilla\bin\SciLexer.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\lexbib.pdb" /debug /machine:I386 /def:".\lexbib.def" /out:"$(OUTDIR)\lexbib.dll" /implib:"$(OUTDIR)\lexbib.lib" /pdbtype:sept 
DEF_FILE= \
	".\lexbib.def"
LINK32_OBJS= \
	"$(INTDIR)\LexBib.obj" \
	"$(INTDIR)\PropSet.obj" \
	"$(INTDIR)\WindowAccessor.obj" \
	"$(INTDIR)\lexbib.res"

"$(OUTDIR)\lexbib.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE="$(InputPath)"
PostBuild_Desc=copy lexbib.dll
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\lexbib.dll" "$(OUTDIR)\lexbib.bsc"
   copydbg.bat
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
!IF EXISTS("lexbib.dep")
!INCLUDE "lexbib.dep"
!ELSE 
!MESSAGE Warning: cannot find "lexbib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "lexbib - Win32 Release" || "$(CFG)" == "lexbib - Win32 Debug"
SOURCE=.\LexBib.cxx

!IF  "$(CFG)" == "lexbib - Win32 Release"


"$(INTDIR)\LexBib.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "lexbib - Win32 Debug"


"$(INTDIR)\LexBib.obj"	"$(INTDIR)\LexBib.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\scintilla\scintilla\src\PropSet.cxx

!IF  "$(CFG)" == "lexbib - Win32 Release"


"$(INTDIR)\PropSet.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "lexbib - Win32 Debug"


"$(INTDIR)\PropSet.obj"	"$(INTDIR)\PropSet.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\scintilla\scintilla\src\WindowAccessor.cxx

!IF  "$(CFG)" == "lexbib - Win32 Release"


"$(INTDIR)\WindowAccessor.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "lexbib - Win32 Debug"


"$(INTDIR)\WindowAccessor.obj"	"$(INTDIR)\WindowAccessor.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\lexbib.rc

"$(INTDIR)\lexbib.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

