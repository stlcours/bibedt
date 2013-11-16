# Microsoft Developer Studio Generated NMAKE File, Based on bibedt.dsp
!IF "$(CFG)" == ""
CFG=bibedt - Win32 Debug Unicode
!MESSAGE Keine Konfiguration angegeben. bibedt - Win32 Debug Unicode wird als Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "bibedt - Win32 Release" && "$(CFG)" != "bibedt - Win32 Debug" && "$(CFG)" != "bibedt - Win32 Release Unicode" && "$(CFG)" != "bibedt - Win32 Debug Unicode"
!MESSAGE UngÅltige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie kînnen beim AusfÅhren von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "bibedt.mak" CFG="bibedt - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE FÅr die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "bibedt - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "bibedt - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "bibedt - Win32 Release Unicode" (basierend auf  "Win32 (x86) Application")
!MESSAGE "bibedt - Win32 Debug Unicode" (basierend auf  "Win32 (x86) Application")
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

!IF  "$(CFG)" == "bibedt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\bibedt.exe"

!ELSE 

ALL : "regex - Win32 Release" "lexbib - Win32 Release" "$(OUTDIR)\bibedt.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"lexbib - Win32 ReleaseCLEAN" "regex - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ApplyFilterDialog.obj"
	-@erase "$(INTDIR)\AuxParser.obj"
	-@erase "$(INTDIR)\BeIconv.obj"
	-@erase "$(INTDIR)\BibDef.obj"
	-@erase "$(INTDIR)\bibedt.obj"
	-@erase "$(INTDIR)\bibedt.pch"
	-@erase "$(INTDIR)\bibedt.res"
	-@erase "$(INTDIR)\bibedtDoc.obj"
	-@erase "$(INTDIR)\BibEdtList.obj"
	-@erase "$(INTDIR)\bibedtView.obj"
	-@erase "$(INTDIR)\BibFile.obj"
	-@erase "$(INTDIR)\BibItem.obj"
	-@erase "$(INTDIR)\BibitemView.obj"
	-@erase "$(INTDIR)\BibList.obj"
	-@erase "$(INTDIR)\BibReader.obj"
	-@erase "$(INTDIR)\BibWriter.obj"
	-@erase "$(INTDIR)\Coding.obj"
	-@erase "$(INTDIR)\CodingHTML.obj"
	-@erase "$(INTDIR)\CodingRTF.obj"
	-@erase "$(INTDIR)\CodingTeX.obj"
	-@erase "$(INTDIR)\CodingXML.obj"
	-@erase "$(INTDIR)\ColumnsDialog.obj"
	-@erase "$(INTDIR)\CopyCitationDialog.obj"
	-@erase "$(INTDIR)\CustomizeDialog.obj"
	-@erase "$(INTDIR)\DocMgrEx.obj"
	-@erase "$(INTDIR)\EditCell.obj"
	-@erase "$(INTDIR)\Export.obj"
	-@erase "$(INTDIR)\ExportBib.obj"
	-@erase "$(INTDIR)\ExportCopyHtml.obj"
	-@erase "$(INTDIR)\ExportDialog.obj"
	-@erase "$(INTDIR)\ExporterList.obj"
	-@erase "$(INTDIR)\ExportGeneric.obj"
	-@erase "$(INTDIR)\ExportInternal.obj"
	-@erase "$(INTDIR)\ExportKeygen.obj"
	-@erase "$(INTDIR)\ExportPreview.obj"
	-@erase "$(INTDIR)\ExportRTF.obj"
	-@erase "$(INTDIR)\ExportText.obj"
	-@erase "$(INTDIR)\ExportXML.obj"
	-@erase "$(INTDIR)\Field.obj"
	-@erase "$(INTDIR)\FieldList.obj"
	-@erase "$(INTDIR)\FileDialogEx.obj"
	-@erase "$(INTDIR)\FileWatch.obj"
	-@erase "$(INTDIR)\FilterDialog.obj"
	-@erase "$(INTDIR)\FindDialog.obj"
	-@erase "$(INTDIR)\FindDuplicatesDialog.obj"
	-@erase "$(INTDIR)\FindDupOptionsDialog.obj"
	-@erase "$(INTDIR)\GenFromAuxDialog.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\HTMLCODES.OBJ"
	-@erase "$(INTDIR)\HTMLView.obj"
	-@erase "$(INTDIR)\htmlviewer.obj"
	-@erase "$(INTDIR)\InputBox.obj"
	-@erase "$(INTDIR)\KeysDialog.obj"
	-@erase "$(INTDIR)\Language.obj"
	-@erase "$(INTDIR)\LinkStatic.obj"
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ListViewPrint.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MyBitmapButton.obj"
	-@erase "$(INTDIR)\OnlineSearch.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\OptionsEditorPage.obj"
	-@erase "$(INTDIR)\OptionsExporterPage.obj"
	-@erase "$(INTDIR)\OptionsFilePage.obj"
	-@erase "$(INTDIR)\OptionsGeneralPage.obj"
	-@erase "$(INTDIR)\OptionsLanguagePage.obj"
	-@erase "$(INTDIR)\OptionsPreviewPage.obj"
	-@erase "$(INTDIR)\OptionsPrintPage.obj"
	-@erase "$(INTDIR)\OptionsSheet.obj"
	-@erase "$(INTDIR)\PreambleDialog.obj"
	-@erase "$(INTDIR)\Print.obj"
	-@erase "$(INTDIR)\PrintPages.obj"
	-@erase "$(INTDIR)\ProgressDialog.obj"
	-@erase "$(INTDIR)\RegExp.obj"
	-@erase "$(INTDIR)\ReplaceDialog.obj"
	-@erase "$(INTDIR)\ScintillaBibWnd.obj"
	-@erase "$(INTDIR)\ScintillaPrint.obj"
	-@erase "$(INTDIR)\ScintillaWnd.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\SearchProfile.obj"
	-@erase "$(INTDIR)\SearchProfilesDialog.obj"
	-@erase "$(INTDIR)\SourceDialog.obj"
	-@erase "$(INTDIR)\SourceView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringListEx.obj"
	-@erase "$(INTDIR)\StringsDialog.obj"
	-@erase "$(INTDIR)\ToolbarEx.obj"
	-@erase "$(INTDIR)\ValueListDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VisualFx.obj"
	-@erase "$(INTDIR)\XSLTransform.obj"
	-@erase "$(INTDIR)\xString.obj"
	-@erase "$(INTDIR)\YazAbstractXMLParser.obj"
	-@erase "$(INTDIR)\YazCCLQuery.obj"
	-@erase "$(INTDIR)\YazConn.obj"
	-@erase "$(INTDIR)\YazCQLQuery.obj"
	-@erase "$(INTDIR)\YazMARCParser.obj"
	-@erase "$(INTDIR)\YazOPACParser.obj"
	-@erase "$(INTDIR)\YazOpacXMLParser.obj"
	-@erase "$(INTDIR)\YazParser.obj"
	-@erase "$(INTDIR)\YazPrefixQuery.obj"
	-@erase "$(INTDIR)\YazQuery.obj"
	-@erase "$(INTDIR)\YazRecord.obj"
	-@erase "$(INTDIR)\YazResultSet.obj"
	-@erase "$(INTDIR)\YazUsMarcXMLParser.obj"
	-@erase "$(INTDIR)\YazXMLParser.obj"
	-@erase "$(OUTDIR)\bibedt.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\bibedt.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\bibedt.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bibedt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Release\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\bibedt.pdb" /machine:I386 /out:"$(OUTDIR)\bibedt.exe" /libpath:"Release" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ApplyFilterDialog.obj" \
	"$(INTDIR)\AuxParser.obj" \
	"$(INTDIR)\BeIconv.obj" \
	"$(INTDIR)\BibDef.obj" \
	"$(INTDIR)\bibedt.obj" \
	"$(INTDIR)\bibedtDoc.obj" \
	"$(INTDIR)\BibEdtList.obj" \
	"$(INTDIR)\bibedtView.obj" \
	"$(INTDIR)\BibFile.obj" \
	"$(INTDIR)\BibItem.obj" \
	"$(INTDIR)\BibitemView.obj" \
	"$(INTDIR)\BibList.obj" \
	"$(INTDIR)\BibReader.obj" \
	"$(INTDIR)\BibWriter.obj" \
	"$(INTDIR)\Coding.obj" \
	"$(INTDIR)\CodingHTML.obj" \
	"$(INTDIR)\CodingRTF.obj" \
	"$(INTDIR)\CodingTeX.obj" \
	"$(INTDIR)\CodingXML.obj" \
	"$(INTDIR)\ColumnsDialog.obj" \
	"$(INTDIR)\CopyCitationDialog.obj" \
	"$(INTDIR)\CustomizeDialog.obj" \
	"$(INTDIR)\DocMgrEx.obj" \
	"$(INTDIR)\EditCell.obj" \
	"$(INTDIR)\Export.obj" \
	"$(INTDIR)\ExportBib.obj" \
	"$(INTDIR)\ExportCopyHtml.obj" \
	"$(INTDIR)\ExportDialog.obj" \
	"$(INTDIR)\ExporterList.obj" \
	"$(INTDIR)\ExportGeneric.obj" \
	"$(INTDIR)\ExportInternal.obj" \
	"$(INTDIR)\ExportKeygen.obj" \
	"$(INTDIR)\ExportPreview.obj" \
	"$(INTDIR)\ExportRTF.obj" \
	"$(INTDIR)\ExportText.obj" \
	"$(INTDIR)\ExportXML.obj" \
	"$(INTDIR)\Field.obj" \
	"$(INTDIR)\FieldList.obj" \
	"$(INTDIR)\FileDialogEx.obj" \
	"$(INTDIR)\FileWatch.obj" \
	"$(INTDIR)\FilterDialog.obj" \
	"$(INTDIR)\FindDialog.obj" \
	"$(INTDIR)\FindDuplicatesDialog.obj" \
	"$(INTDIR)\FindDupOptionsDialog.obj" \
	"$(INTDIR)\GenFromAuxDialog.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HTMLCODES.OBJ" \
	"$(INTDIR)\HTMLView.obj" \
	"$(INTDIR)\htmlviewer.obj" \
	"$(INTDIR)\InputBox.obj" \
	"$(INTDIR)\KeysDialog.obj" \
	"$(INTDIR)\Language.obj" \
	"$(INTDIR)\LinkStatic.obj" \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\ListViewPrint.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MyBitmapButton.obj" \
	"$(INTDIR)\OnlineSearch.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\OptionsEditorPage.obj" \
	"$(INTDIR)\OptionsExporterPage.obj" \
	"$(INTDIR)\OptionsFilePage.obj" \
	"$(INTDIR)\OptionsGeneralPage.obj" \
	"$(INTDIR)\OptionsLanguagePage.obj" \
	"$(INTDIR)\OptionsPreviewPage.obj" \
	"$(INTDIR)\OptionsPrintPage.obj" \
	"$(INTDIR)\OptionsSheet.obj" \
	"$(INTDIR)\PreambleDialog.obj" \
	"$(INTDIR)\Print.obj" \
	"$(INTDIR)\PrintPages.obj" \
	"$(INTDIR)\ProgressDialog.obj" \
	"$(INTDIR)\RegExp.obj" \
	"$(INTDIR)\ReplaceDialog.obj" \
	"$(INTDIR)\ScintillaBibWnd.obj" \
	"$(INTDIR)\ScintillaPrint.obj" \
	"$(INTDIR)\ScintillaWnd.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\SearchProfile.obj" \
	"$(INTDIR)\SearchProfilesDialog.obj" \
	"$(INTDIR)\SourceDialog.obj" \
	"$(INTDIR)\SourceView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringListEx.obj" \
	"$(INTDIR)\StringsDialog.obj" \
	"$(INTDIR)\ToolbarEx.obj" \
	"$(INTDIR)\VisualFx.obj" \
	"$(INTDIR)\XSLTransform.obj" \
	"$(INTDIR)\xString.obj" \
	"$(INTDIR)\YazAbstractXMLParser.obj" \
	"$(INTDIR)\YazCCLQuery.obj" \
	"$(INTDIR)\YazConn.obj" \
	"$(INTDIR)\YazCQLQuery.obj" \
	"$(INTDIR)\YazMARCParser.obj" \
	"$(INTDIR)\YazOPACParser.obj" \
	"$(INTDIR)\YazOpacXMLParser.obj" \
	"$(INTDIR)\YazParser.obj" \
	"$(INTDIR)\YazPrefixQuery.obj" \
	"$(INTDIR)\YazQuery.obj" \
	"$(INTDIR)\YazRecord.obj" \
	"$(INTDIR)\YazResultSet.obj" \
	"$(INTDIR)\YazUsMarcXMLParser.obj" \
	"$(INTDIR)\YazXMLParser.obj" \
	"$(INTDIR)\bibedt.res" \
	"$(INTDIR)\ValueListDialog.obj" \
	".\lexbib\Release\lexbib.lib" \
	"$(OUTDIR)\regex.lib"

"$(OUTDIR)\bibedt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\bibedt.exe" "$(OUTDIR)\bibedt.bsc"

!ELSE 

ALL : "regex - Win32 Debug" "lexbib - Win32 Debug" "$(OUTDIR)\bibedt.exe" "$(OUTDIR)\bibedt.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"lexbib - Win32 DebugCLEAN" "regex - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ApplyFilterDialog.obj"
	-@erase "$(INTDIR)\ApplyFilterDialog.sbr"
	-@erase "$(INTDIR)\AuxParser.obj"
	-@erase "$(INTDIR)\AuxParser.sbr"
	-@erase "$(INTDIR)\BeIconv.obj"
	-@erase "$(INTDIR)\BeIconv.sbr"
	-@erase "$(INTDIR)\BibDef.obj"
	-@erase "$(INTDIR)\BibDef.sbr"
	-@erase "$(INTDIR)\bibedt.obj"
	-@erase "$(INTDIR)\bibedt.pch"
	-@erase "$(INTDIR)\bibedt.res"
	-@erase "$(INTDIR)\bibedt.sbr"
	-@erase "$(INTDIR)\bibedtDoc.obj"
	-@erase "$(INTDIR)\bibedtDoc.sbr"
	-@erase "$(INTDIR)\BibEdtList.obj"
	-@erase "$(INTDIR)\BibEdtList.sbr"
	-@erase "$(INTDIR)\bibedtView.obj"
	-@erase "$(INTDIR)\bibedtView.sbr"
	-@erase "$(INTDIR)\BibFile.obj"
	-@erase "$(INTDIR)\BibFile.sbr"
	-@erase "$(INTDIR)\BibItem.obj"
	-@erase "$(INTDIR)\BibItem.sbr"
	-@erase "$(INTDIR)\BibitemView.obj"
	-@erase "$(INTDIR)\BibitemView.sbr"
	-@erase "$(INTDIR)\BibList.obj"
	-@erase "$(INTDIR)\BibList.sbr"
	-@erase "$(INTDIR)\BibReader.obj"
	-@erase "$(INTDIR)\BibReader.sbr"
	-@erase "$(INTDIR)\BibWriter.obj"
	-@erase "$(INTDIR)\BibWriter.sbr"
	-@erase "$(INTDIR)\Coding.obj"
	-@erase "$(INTDIR)\Coding.sbr"
	-@erase "$(INTDIR)\CodingHTML.obj"
	-@erase "$(INTDIR)\CodingHTML.sbr"
	-@erase "$(INTDIR)\CodingRTF.obj"
	-@erase "$(INTDIR)\CodingRTF.sbr"
	-@erase "$(INTDIR)\CodingTeX.obj"
	-@erase "$(INTDIR)\CodingTeX.sbr"
	-@erase "$(INTDIR)\CodingXML.obj"
	-@erase "$(INTDIR)\CodingXML.sbr"
	-@erase "$(INTDIR)\ColumnsDialog.obj"
	-@erase "$(INTDIR)\ColumnsDialog.sbr"
	-@erase "$(INTDIR)\CopyCitationDialog.obj"
	-@erase "$(INTDIR)\CopyCitationDialog.sbr"
	-@erase "$(INTDIR)\CustomizeDialog.obj"
	-@erase "$(INTDIR)\CustomizeDialog.sbr"
	-@erase "$(INTDIR)\DocMgrEx.obj"
	-@erase "$(INTDIR)\DocMgrEx.sbr"
	-@erase "$(INTDIR)\EditCell.obj"
	-@erase "$(INTDIR)\EditCell.sbr"
	-@erase "$(INTDIR)\Export.obj"
	-@erase "$(INTDIR)\Export.sbr"
	-@erase "$(INTDIR)\ExportBib.obj"
	-@erase "$(INTDIR)\ExportBib.sbr"
	-@erase "$(INTDIR)\ExportCopyHtml.obj"
	-@erase "$(INTDIR)\ExportCopyHtml.sbr"
	-@erase "$(INTDIR)\ExportDialog.obj"
	-@erase "$(INTDIR)\ExportDialog.sbr"
	-@erase "$(INTDIR)\ExporterList.obj"
	-@erase "$(INTDIR)\ExporterList.sbr"
	-@erase "$(INTDIR)\ExportGeneric.obj"
	-@erase "$(INTDIR)\ExportGeneric.sbr"
	-@erase "$(INTDIR)\ExportInternal.obj"
	-@erase "$(INTDIR)\ExportInternal.sbr"
	-@erase "$(INTDIR)\ExportKeygen.obj"
	-@erase "$(INTDIR)\ExportKeygen.sbr"
	-@erase "$(INTDIR)\ExportPreview.obj"
	-@erase "$(INTDIR)\ExportPreview.sbr"
	-@erase "$(INTDIR)\ExportRTF.obj"
	-@erase "$(INTDIR)\ExportRTF.sbr"
	-@erase "$(INTDIR)\ExportText.obj"
	-@erase "$(INTDIR)\ExportText.sbr"
	-@erase "$(INTDIR)\ExportXML.obj"
	-@erase "$(INTDIR)\ExportXML.sbr"
	-@erase "$(INTDIR)\Field.obj"
	-@erase "$(INTDIR)\Field.sbr"
	-@erase "$(INTDIR)\FieldList.obj"
	-@erase "$(INTDIR)\FieldList.sbr"
	-@erase "$(INTDIR)\FileDialogEx.obj"
	-@erase "$(INTDIR)\FileDialogEx.sbr"
	-@erase "$(INTDIR)\FileWatch.obj"
	-@erase "$(INTDIR)\FileWatch.sbr"
	-@erase "$(INTDIR)\FilterDialog.obj"
	-@erase "$(INTDIR)\FilterDialog.sbr"
	-@erase "$(INTDIR)\FindDialog.obj"
	-@erase "$(INTDIR)\FindDialog.sbr"
	-@erase "$(INTDIR)\FindDuplicatesDialog.obj"
	-@erase "$(INTDIR)\FindDuplicatesDialog.sbr"
	-@erase "$(INTDIR)\FindDupOptionsDialog.obj"
	-@erase "$(INTDIR)\FindDupOptionsDialog.sbr"
	-@erase "$(INTDIR)\GenFromAuxDialog.obj"
	-@erase "$(INTDIR)\GenFromAuxDialog.sbr"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Globals.sbr"
	-@erase "$(INTDIR)\HTMLCODES.OBJ"
	-@erase "$(INTDIR)\HTMLCODES.SBR"
	-@erase "$(INTDIR)\HTMLView.obj"
	-@erase "$(INTDIR)\HTMLView.sbr"
	-@erase "$(INTDIR)\htmlviewer.obj"
	-@erase "$(INTDIR)\htmlviewer.sbr"
	-@erase "$(INTDIR)\InputBox.obj"
	-@erase "$(INTDIR)\InputBox.sbr"
	-@erase "$(INTDIR)\KeysDialog.obj"
	-@erase "$(INTDIR)\KeysDialog.sbr"
	-@erase "$(INTDIR)\Language.obj"
	-@erase "$(INTDIR)\Language.sbr"
	-@erase "$(INTDIR)\LinkStatic.obj"
	-@erase "$(INTDIR)\LinkStatic.sbr"
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ListCtrlEx.sbr"
	-@erase "$(INTDIR)\ListViewPrint.obj"
	-@erase "$(INTDIR)\ListViewPrint.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MyBitmapButton.obj"
	-@erase "$(INTDIR)\MyBitmapButton.sbr"
	-@erase "$(INTDIR)\OnlineSearch.obj"
	-@erase "$(INTDIR)\OnlineSearch.sbr"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Options.sbr"
	-@erase "$(INTDIR)\OptionsEditorPage.obj"
	-@erase "$(INTDIR)\OptionsEditorPage.sbr"
	-@erase "$(INTDIR)\OptionsExporterPage.obj"
	-@erase "$(INTDIR)\OptionsExporterPage.sbr"
	-@erase "$(INTDIR)\OptionsFilePage.obj"
	-@erase "$(INTDIR)\OptionsFilePage.sbr"
	-@erase "$(INTDIR)\OptionsGeneralPage.obj"
	-@erase "$(INTDIR)\OptionsGeneralPage.sbr"
	-@erase "$(INTDIR)\OptionsLanguagePage.obj"
	-@erase "$(INTDIR)\OptionsLanguagePage.sbr"
	-@erase "$(INTDIR)\OptionsPreviewPage.obj"
	-@erase "$(INTDIR)\OptionsPreviewPage.sbr"
	-@erase "$(INTDIR)\OptionsPrintPage.obj"
	-@erase "$(INTDIR)\OptionsPrintPage.sbr"
	-@erase "$(INTDIR)\OptionsSheet.obj"
	-@erase "$(INTDIR)\OptionsSheet.sbr"
	-@erase "$(INTDIR)\PreambleDialog.obj"
	-@erase "$(INTDIR)\PreambleDialog.sbr"
	-@erase "$(INTDIR)\Print.obj"
	-@erase "$(INTDIR)\Print.sbr"
	-@erase "$(INTDIR)\PrintPages.obj"
	-@erase "$(INTDIR)\PrintPages.sbr"
	-@erase "$(INTDIR)\ProgressDialog.obj"
	-@erase "$(INTDIR)\ProgressDialog.sbr"
	-@erase "$(INTDIR)\RegExp.obj"
	-@erase "$(INTDIR)\RegExp.sbr"
	-@erase "$(INTDIR)\ReplaceDialog.obj"
	-@erase "$(INTDIR)\ReplaceDialog.sbr"
	-@erase "$(INTDIR)\ScintillaBibWnd.obj"
	-@erase "$(INTDIR)\ScintillaBibWnd.sbr"
	-@erase "$(INTDIR)\ScintillaPrint.obj"
	-@erase "$(INTDIR)\ScintillaPrint.sbr"
	-@erase "$(INTDIR)\ScintillaWnd.obj"
	-@erase "$(INTDIR)\ScintillaWnd.sbr"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\SearchDialog.sbr"
	-@erase "$(INTDIR)\SearchProfile.obj"
	-@erase "$(INTDIR)\SearchProfile.sbr"
	-@erase "$(INTDIR)\SearchProfilesDialog.obj"
	-@erase "$(INTDIR)\SearchProfilesDialog.sbr"
	-@erase "$(INTDIR)\SourceDialog.obj"
	-@erase "$(INTDIR)\SourceDialog.sbr"
	-@erase "$(INTDIR)\SourceView.obj"
	-@erase "$(INTDIR)\SourceView.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StringListEx.obj"
	-@erase "$(INTDIR)\StringListEx.sbr"
	-@erase "$(INTDIR)\StringsDialog.obj"
	-@erase "$(INTDIR)\StringsDialog.sbr"
	-@erase "$(INTDIR)\ToolbarEx.obj"
	-@erase "$(INTDIR)\ToolbarEx.sbr"
	-@erase "$(INTDIR)\ValueListDialog.obj"
	-@erase "$(INTDIR)\ValueListDialog.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VisualFx.obj"
	-@erase "$(INTDIR)\VisualFx.sbr"
	-@erase "$(INTDIR)\XSLTransform.obj"
	-@erase "$(INTDIR)\XSLTransform.sbr"
	-@erase "$(INTDIR)\xString.obj"
	-@erase "$(INTDIR)\xString.sbr"
	-@erase "$(INTDIR)\YazAbstractXMLParser.obj"
	-@erase "$(INTDIR)\YazAbstractXMLParser.sbr"
	-@erase "$(INTDIR)\YazCCLQuery.obj"
	-@erase "$(INTDIR)\YazCCLQuery.sbr"
	-@erase "$(INTDIR)\YazConn.obj"
	-@erase "$(INTDIR)\YazConn.sbr"
	-@erase "$(INTDIR)\YazCQLQuery.obj"
	-@erase "$(INTDIR)\YazCQLQuery.sbr"
	-@erase "$(INTDIR)\YazMARCParser.obj"
	-@erase "$(INTDIR)\YazMARCParser.sbr"
	-@erase "$(INTDIR)\YazOPACParser.obj"
	-@erase "$(INTDIR)\YazOPACParser.sbr"
	-@erase "$(INTDIR)\YazOpacXMLParser.obj"
	-@erase "$(INTDIR)\YazOpacXMLParser.sbr"
	-@erase "$(INTDIR)\YazParser.obj"
	-@erase "$(INTDIR)\YazParser.sbr"
	-@erase "$(INTDIR)\YazPrefixQuery.obj"
	-@erase "$(INTDIR)\YazPrefixQuery.sbr"
	-@erase "$(INTDIR)\YazQuery.obj"
	-@erase "$(INTDIR)\YazQuery.sbr"
	-@erase "$(INTDIR)\YazRecord.obj"
	-@erase "$(INTDIR)\YazRecord.sbr"
	-@erase "$(INTDIR)\YazResultSet.obj"
	-@erase "$(INTDIR)\YazResultSet.sbr"
	-@erase "$(INTDIR)\YazUsMarcXMLParser.obj"
	-@erase "$(INTDIR)\YazUsMarcXMLParser.sbr"
	-@erase "$(INTDIR)\YazXMLParser.obj"
	-@erase "$(INTDIR)\YazXMLParser.sbr"
	-@erase "$(OUTDIR)\bibedt.bsc"
	-@erase "$(OUTDIR)\bibedt.exe"
	-@erase "$(OUTDIR)\bibedt.ilk"
	-@erase "$(OUTDIR)\bibedt.map"
	-@erase "$(OUTDIR)\bibedt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bibedt.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\bibedt.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bibedt.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ApplyFilterDialog.sbr" \
	"$(INTDIR)\AuxParser.sbr" \
	"$(INTDIR)\BeIconv.sbr" \
	"$(INTDIR)\BibDef.sbr" \
	"$(INTDIR)\bibedt.sbr" \
	"$(INTDIR)\bibedtDoc.sbr" \
	"$(INTDIR)\BibEdtList.sbr" \
	"$(INTDIR)\bibedtView.sbr" \
	"$(INTDIR)\BibFile.sbr" \
	"$(INTDIR)\BibItem.sbr" \
	"$(INTDIR)\BibitemView.sbr" \
	"$(INTDIR)\BibList.sbr" \
	"$(INTDIR)\BibReader.sbr" \
	"$(INTDIR)\BibWriter.sbr" \
	"$(INTDIR)\Coding.sbr" \
	"$(INTDIR)\CodingHTML.sbr" \
	"$(INTDIR)\CodingRTF.sbr" \
	"$(INTDIR)\CodingTeX.sbr" \
	"$(INTDIR)\CodingXML.sbr" \
	"$(INTDIR)\ColumnsDialog.sbr" \
	"$(INTDIR)\CopyCitationDialog.sbr" \
	"$(INTDIR)\CustomizeDialog.sbr" \
	"$(INTDIR)\DocMgrEx.sbr" \
	"$(INTDIR)\EditCell.sbr" \
	"$(INTDIR)\Export.sbr" \
	"$(INTDIR)\ExportBib.sbr" \
	"$(INTDIR)\ExportCopyHtml.sbr" \
	"$(INTDIR)\ExportDialog.sbr" \
	"$(INTDIR)\ExporterList.sbr" \
	"$(INTDIR)\ExportGeneric.sbr" \
	"$(INTDIR)\ExportInternal.sbr" \
	"$(INTDIR)\ExportKeygen.sbr" \
	"$(INTDIR)\ExportPreview.sbr" \
	"$(INTDIR)\ExportRTF.sbr" \
	"$(INTDIR)\ExportText.sbr" \
	"$(INTDIR)\ExportXML.sbr" \
	"$(INTDIR)\Field.sbr" \
	"$(INTDIR)\FieldList.sbr" \
	"$(INTDIR)\FileDialogEx.sbr" \
	"$(INTDIR)\FileWatch.sbr" \
	"$(INTDIR)\FilterDialog.sbr" \
	"$(INTDIR)\FindDialog.sbr" \
	"$(INTDIR)\FindDuplicatesDialog.sbr" \
	"$(INTDIR)\FindDupOptionsDialog.sbr" \
	"$(INTDIR)\GenFromAuxDialog.sbr" \
	"$(INTDIR)\Globals.sbr" \
	"$(INTDIR)\HTMLCODES.SBR" \
	"$(INTDIR)\HTMLView.sbr" \
	"$(INTDIR)\htmlviewer.sbr" \
	"$(INTDIR)\InputBox.sbr" \
	"$(INTDIR)\KeysDialog.sbr" \
	"$(INTDIR)\Language.sbr" \
	"$(INTDIR)\LinkStatic.sbr" \
	"$(INTDIR)\ListCtrlEx.sbr" \
	"$(INTDIR)\ListViewPrint.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MyBitmapButton.sbr" \
	"$(INTDIR)\OnlineSearch.sbr" \
	"$(INTDIR)\Options.sbr" \
	"$(INTDIR)\OptionsEditorPage.sbr" \
	"$(INTDIR)\OptionsExporterPage.sbr" \
	"$(INTDIR)\OptionsFilePage.sbr" \
	"$(INTDIR)\OptionsGeneralPage.sbr" \
	"$(INTDIR)\OptionsLanguagePage.sbr" \
	"$(INTDIR)\OptionsPreviewPage.sbr" \
	"$(INTDIR)\OptionsPrintPage.sbr" \
	"$(INTDIR)\OptionsSheet.sbr" \
	"$(INTDIR)\PreambleDialog.sbr" \
	"$(INTDIR)\Print.sbr" \
	"$(INTDIR)\PrintPages.sbr" \
	"$(INTDIR)\ProgressDialog.sbr" \
	"$(INTDIR)\RegExp.sbr" \
	"$(INTDIR)\ReplaceDialog.sbr" \
	"$(INTDIR)\ScintillaBibWnd.sbr" \
	"$(INTDIR)\ScintillaPrint.sbr" \
	"$(INTDIR)\ScintillaWnd.sbr" \
	"$(INTDIR)\SearchDialog.sbr" \
	"$(INTDIR)\SearchProfile.sbr" \
	"$(INTDIR)\SearchProfilesDialog.sbr" \
	"$(INTDIR)\SourceDialog.sbr" \
	"$(INTDIR)\SourceView.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StringListEx.sbr" \
	"$(INTDIR)\StringsDialog.sbr" \
	"$(INTDIR)\ToolbarEx.sbr" \
	"$(INTDIR)\VisualFx.sbr" \
	"$(INTDIR)\XSLTransform.sbr" \
	"$(INTDIR)\xString.sbr" \
	"$(INTDIR)\YazAbstractXMLParser.sbr" \
	"$(INTDIR)\YazCCLQuery.sbr" \
	"$(INTDIR)\YazConn.sbr" \
	"$(INTDIR)\YazCQLQuery.sbr" \
	"$(INTDIR)\YazMARCParser.sbr" \
	"$(INTDIR)\YazOPACParser.sbr" \
	"$(INTDIR)\YazOpacXMLParser.sbr" \
	"$(INTDIR)\YazParser.sbr" \
	"$(INTDIR)\YazPrefixQuery.sbr" \
	"$(INTDIR)\YazQuery.sbr" \
	"$(INTDIR)\YazRecord.sbr" \
	"$(INTDIR)\YazResultSet.sbr" \
	"$(INTDIR)\YazUsMarcXMLParser.sbr" \
	"$(INTDIR)\YazXMLParser.sbr" \
	"$(INTDIR)\ValueListDialog.sbr"

"$(OUTDIR)\bibedt.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Debug\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\bibedt.pdb" /map:"$(INTDIR)\bibedt.map" /debug /machine:I386 /out:"$(OUTDIR)\bibedt.exe" /pdbtype:sept /libpath:"Debug" /libpath:"xaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ApplyFilterDialog.obj" \
	"$(INTDIR)\AuxParser.obj" \
	"$(INTDIR)\BeIconv.obj" \
	"$(INTDIR)\BibDef.obj" \
	"$(INTDIR)\bibedt.obj" \
	"$(INTDIR)\bibedtDoc.obj" \
	"$(INTDIR)\BibEdtList.obj" \
	"$(INTDIR)\bibedtView.obj" \
	"$(INTDIR)\BibFile.obj" \
	"$(INTDIR)\BibItem.obj" \
	"$(INTDIR)\BibitemView.obj" \
	"$(INTDIR)\BibList.obj" \
	"$(INTDIR)\BibReader.obj" \
	"$(INTDIR)\BibWriter.obj" \
	"$(INTDIR)\Coding.obj" \
	"$(INTDIR)\CodingHTML.obj" \
	"$(INTDIR)\CodingRTF.obj" \
	"$(INTDIR)\CodingTeX.obj" \
	"$(INTDIR)\CodingXML.obj" \
	"$(INTDIR)\ColumnsDialog.obj" \
	"$(INTDIR)\CopyCitationDialog.obj" \
	"$(INTDIR)\CustomizeDialog.obj" \
	"$(INTDIR)\DocMgrEx.obj" \
	"$(INTDIR)\EditCell.obj" \
	"$(INTDIR)\Export.obj" \
	"$(INTDIR)\ExportBib.obj" \
	"$(INTDIR)\ExportCopyHtml.obj" \
	"$(INTDIR)\ExportDialog.obj" \
	"$(INTDIR)\ExporterList.obj" \
	"$(INTDIR)\ExportGeneric.obj" \
	"$(INTDIR)\ExportInternal.obj" \
	"$(INTDIR)\ExportKeygen.obj" \
	"$(INTDIR)\ExportPreview.obj" \
	"$(INTDIR)\ExportRTF.obj" \
	"$(INTDIR)\ExportText.obj" \
	"$(INTDIR)\ExportXML.obj" \
	"$(INTDIR)\Field.obj" \
	"$(INTDIR)\FieldList.obj" \
	"$(INTDIR)\FileDialogEx.obj" \
	"$(INTDIR)\FileWatch.obj" \
	"$(INTDIR)\FilterDialog.obj" \
	"$(INTDIR)\FindDialog.obj" \
	"$(INTDIR)\FindDuplicatesDialog.obj" \
	"$(INTDIR)\FindDupOptionsDialog.obj" \
	"$(INTDIR)\GenFromAuxDialog.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HTMLCODES.OBJ" \
	"$(INTDIR)\HTMLView.obj" \
	"$(INTDIR)\htmlviewer.obj" \
	"$(INTDIR)\InputBox.obj" \
	"$(INTDIR)\KeysDialog.obj" \
	"$(INTDIR)\Language.obj" \
	"$(INTDIR)\LinkStatic.obj" \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\ListViewPrint.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MyBitmapButton.obj" \
	"$(INTDIR)\OnlineSearch.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\OptionsEditorPage.obj" \
	"$(INTDIR)\OptionsExporterPage.obj" \
	"$(INTDIR)\OptionsFilePage.obj" \
	"$(INTDIR)\OptionsGeneralPage.obj" \
	"$(INTDIR)\OptionsLanguagePage.obj" \
	"$(INTDIR)\OptionsPreviewPage.obj" \
	"$(INTDIR)\OptionsPrintPage.obj" \
	"$(INTDIR)\OptionsSheet.obj" \
	"$(INTDIR)\PreambleDialog.obj" \
	"$(INTDIR)\Print.obj" \
	"$(INTDIR)\PrintPages.obj" \
	"$(INTDIR)\ProgressDialog.obj" \
	"$(INTDIR)\RegExp.obj" \
	"$(INTDIR)\ReplaceDialog.obj" \
	"$(INTDIR)\ScintillaBibWnd.obj" \
	"$(INTDIR)\ScintillaPrint.obj" \
	"$(INTDIR)\ScintillaWnd.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\SearchProfile.obj" \
	"$(INTDIR)\SearchProfilesDialog.obj" \
	"$(INTDIR)\SourceDialog.obj" \
	"$(INTDIR)\SourceView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringListEx.obj" \
	"$(INTDIR)\StringsDialog.obj" \
	"$(INTDIR)\ToolbarEx.obj" \
	"$(INTDIR)\VisualFx.obj" \
	"$(INTDIR)\XSLTransform.obj" \
	"$(INTDIR)\xString.obj" \
	"$(INTDIR)\YazAbstractXMLParser.obj" \
	"$(INTDIR)\YazCCLQuery.obj" \
	"$(INTDIR)\YazConn.obj" \
	"$(INTDIR)\YazCQLQuery.obj" \
	"$(INTDIR)\YazMARCParser.obj" \
	"$(INTDIR)\YazOPACParser.obj" \
	"$(INTDIR)\YazOpacXMLParser.obj" \
	"$(INTDIR)\YazParser.obj" \
	"$(INTDIR)\YazPrefixQuery.obj" \
	"$(INTDIR)\YazQuery.obj" \
	"$(INTDIR)\YazRecord.obj" \
	"$(INTDIR)\YazResultSet.obj" \
	"$(INTDIR)\YazUsMarcXMLParser.obj" \
	"$(INTDIR)\YazXMLParser.obj" \
	"$(INTDIR)\bibedt.res" \
	"$(INTDIR)\ValueListDialog.obj" \
	".\lexbib\Debug\lexbib.lib" \
	"$(OUTDIR)\regex.lib"

"$(OUTDIR)\bibedt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

OUTDIR=.\Release_Unicode
INTDIR=.\Release_Unicode
# Begin Custom Macros
OutDir=.\Release_Unicode
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\bibedt.exe"

!ELSE 

ALL : "$(OUTDIR)\bibedt.exe"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ApplyFilterDialog.obj"
	-@erase "$(INTDIR)\AuxParser.obj"
	-@erase "$(INTDIR)\BeIconv.obj"
	-@erase "$(INTDIR)\BibDef.obj"
	-@erase "$(INTDIR)\bibedt.obj"
	-@erase "$(INTDIR)\bibedt.pch"
	-@erase "$(INTDIR)\bibedt.res"
	-@erase "$(INTDIR)\bibedtDoc.obj"
	-@erase "$(INTDIR)\BibEdtList.obj"
	-@erase "$(INTDIR)\bibedtView.obj"
	-@erase "$(INTDIR)\BibFile.obj"
	-@erase "$(INTDIR)\BibItem.obj"
	-@erase "$(INTDIR)\BibitemView.obj"
	-@erase "$(INTDIR)\BibList.obj"
	-@erase "$(INTDIR)\BibReader.obj"
	-@erase "$(INTDIR)\BibWriter.obj"
	-@erase "$(INTDIR)\Coding.obj"
	-@erase "$(INTDIR)\CodingHTML.obj"
	-@erase "$(INTDIR)\CodingRTF.obj"
	-@erase "$(INTDIR)\CodingTeX.obj"
	-@erase "$(INTDIR)\CodingXML.obj"
	-@erase "$(INTDIR)\ColumnsDialog.obj"
	-@erase "$(INTDIR)\CopyCitationDialog.obj"
	-@erase "$(INTDIR)\CustomizeDialog.obj"
	-@erase "$(INTDIR)\DocMgrEx.obj"
	-@erase "$(INTDIR)\EditCell.obj"
	-@erase "$(INTDIR)\Export.obj"
	-@erase "$(INTDIR)\ExportBib.obj"
	-@erase "$(INTDIR)\ExportCopyHtml.obj"
	-@erase "$(INTDIR)\ExportDialog.obj"
	-@erase "$(INTDIR)\ExporterList.obj"
	-@erase "$(INTDIR)\ExportGeneric.obj"
	-@erase "$(INTDIR)\ExportInternal.obj"
	-@erase "$(INTDIR)\ExportKeygen.obj"
	-@erase "$(INTDIR)\ExportPreview.obj"
	-@erase "$(INTDIR)\ExportRTF.obj"
	-@erase "$(INTDIR)\ExportText.obj"
	-@erase "$(INTDIR)\ExportXML.obj"
	-@erase "$(INTDIR)\Field.obj"
	-@erase "$(INTDIR)\FieldList.obj"
	-@erase "$(INTDIR)\FileDialogEx.obj"
	-@erase "$(INTDIR)\FileWatch.obj"
	-@erase "$(INTDIR)\FilterDialog.obj"
	-@erase "$(INTDIR)\FindDialog.obj"
	-@erase "$(INTDIR)\FindDuplicatesDialog.obj"
	-@erase "$(INTDIR)\FindDupOptionsDialog.obj"
	-@erase "$(INTDIR)\GenFromAuxDialog.obj"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\HTMLCODES.OBJ"
	-@erase "$(INTDIR)\HTMLView.obj"
	-@erase "$(INTDIR)\htmlviewer.obj"
	-@erase "$(INTDIR)\InputBox.obj"
	-@erase "$(INTDIR)\KeysDialog.obj"
	-@erase "$(INTDIR)\Language.obj"
	-@erase "$(INTDIR)\LinkStatic.obj"
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ListViewPrint.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MyBitmapButton.obj"
	-@erase "$(INTDIR)\OnlineSearch.obj"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\OptionsEditorPage.obj"
	-@erase "$(INTDIR)\OptionsExporterPage.obj"
	-@erase "$(INTDIR)\OptionsFilePage.obj"
	-@erase "$(INTDIR)\OptionsGeneralPage.obj"
	-@erase "$(INTDIR)\OptionsLanguagePage.obj"
	-@erase "$(INTDIR)\OptionsPreviewPage.obj"
	-@erase "$(INTDIR)\OptionsPrintPage.obj"
	-@erase "$(INTDIR)\OptionsSheet.obj"
	-@erase "$(INTDIR)\PreambleDialog.obj"
	-@erase "$(INTDIR)\Print.obj"
	-@erase "$(INTDIR)\PrintPages.obj"
	-@erase "$(INTDIR)\ProgressDialog.obj"
	-@erase "$(INTDIR)\RegExp.obj"
	-@erase "$(INTDIR)\ReplaceDialog.obj"
	-@erase "$(INTDIR)\ScintillaBibWnd.obj"
	-@erase "$(INTDIR)\ScintillaPrint.obj"
	-@erase "$(INTDIR)\ScintillaWnd.obj"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\SearchProfile.obj"
	-@erase "$(INTDIR)\SearchProfilesDialog.obj"
	-@erase "$(INTDIR)\SourceDialog.obj"
	-@erase "$(INTDIR)\SourceView.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StringListEx.obj"
	-@erase "$(INTDIR)\StringsDialog.obj"
	-@erase "$(INTDIR)\ToolbarEx.obj"
	-@erase "$(INTDIR)\ValueListDialog.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VisualFx.obj"
	-@erase "$(INTDIR)\XSLTransform.obj"
	-@erase "$(INTDIR)\xString.obj"
	-@erase "$(INTDIR)\YazAbstractXMLParser.obj"
	-@erase "$(INTDIR)\YazCCLQuery.obj"
	-@erase "$(INTDIR)\YazConn.obj"
	-@erase "$(INTDIR)\YazCQLQuery.obj"
	-@erase "$(INTDIR)\YazMARCParser.obj"
	-@erase "$(INTDIR)\YazOPACParser.obj"
	-@erase "$(INTDIR)\YazOpacXMLParser.obj"
	-@erase "$(INTDIR)\YazParser.obj"
	-@erase "$(INTDIR)\YazPrefixQuery.obj"
	-@erase "$(INTDIR)\YazQuery.obj"
	-@erase "$(INTDIR)\YazRecord.obj"
	-@erase "$(INTDIR)\YazResultSet.obj"
	-@erase "$(INTDIR)\YazUsMarcXMLParser.obj"
	-@erase "$(INTDIR)\YazXMLParser.obj"
	-@erase "$(OUTDIR)\bibedt.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\bibedt.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\bibedt.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bibedt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Release\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\bibedt.pdb" /machine:I386 /out:"$(OUTDIR)\bibedt.exe" /libpath:"Release" /libpath:"yaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ApplyFilterDialog.obj" \
	"$(INTDIR)\AuxParser.obj" \
	"$(INTDIR)\BeIconv.obj" \
	"$(INTDIR)\BibDef.obj" \
	"$(INTDIR)\bibedt.obj" \
	"$(INTDIR)\bibedtDoc.obj" \
	"$(INTDIR)\BibEdtList.obj" \
	"$(INTDIR)\bibedtView.obj" \
	"$(INTDIR)\BibFile.obj" \
	"$(INTDIR)\BibItem.obj" \
	"$(INTDIR)\BibitemView.obj" \
	"$(INTDIR)\BibList.obj" \
	"$(INTDIR)\BibReader.obj" \
	"$(INTDIR)\BibWriter.obj" \
	"$(INTDIR)\Coding.obj" \
	"$(INTDIR)\CodingHTML.obj" \
	"$(INTDIR)\CodingRTF.obj" \
	"$(INTDIR)\CodingTeX.obj" \
	"$(INTDIR)\CodingXML.obj" \
	"$(INTDIR)\ColumnsDialog.obj" \
	"$(INTDIR)\CopyCitationDialog.obj" \
	"$(INTDIR)\CustomizeDialog.obj" \
	"$(INTDIR)\DocMgrEx.obj" \
	"$(INTDIR)\EditCell.obj" \
	"$(INTDIR)\Export.obj" \
	"$(INTDIR)\ExportBib.obj" \
	"$(INTDIR)\ExportCopyHtml.obj" \
	"$(INTDIR)\ExportDialog.obj" \
	"$(INTDIR)\ExporterList.obj" \
	"$(INTDIR)\ExportGeneric.obj" \
	"$(INTDIR)\ExportInternal.obj" \
	"$(INTDIR)\ExportKeygen.obj" \
	"$(INTDIR)\ExportPreview.obj" \
	"$(INTDIR)\ExportRTF.obj" \
	"$(INTDIR)\ExportText.obj" \
	"$(INTDIR)\ExportXML.obj" \
	"$(INTDIR)\Field.obj" \
	"$(INTDIR)\FieldList.obj" \
	"$(INTDIR)\FileDialogEx.obj" \
	"$(INTDIR)\FileWatch.obj" \
	"$(INTDIR)\FilterDialog.obj" \
	"$(INTDIR)\FindDialog.obj" \
	"$(INTDIR)\FindDuplicatesDialog.obj" \
	"$(INTDIR)\FindDupOptionsDialog.obj" \
	"$(INTDIR)\GenFromAuxDialog.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HTMLCODES.OBJ" \
	"$(INTDIR)\HTMLView.obj" \
	"$(INTDIR)\htmlviewer.obj" \
	"$(INTDIR)\InputBox.obj" \
	"$(INTDIR)\KeysDialog.obj" \
	"$(INTDIR)\Language.obj" \
	"$(INTDIR)\LinkStatic.obj" \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\ListViewPrint.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MyBitmapButton.obj" \
	"$(INTDIR)\OnlineSearch.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\OptionsEditorPage.obj" \
	"$(INTDIR)\OptionsExporterPage.obj" \
	"$(INTDIR)\OptionsFilePage.obj" \
	"$(INTDIR)\OptionsGeneralPage.obj" \
	"$(INTDIR)\OptionsLanguagePage.obj" \
	"$(INTDIR)\OptionsPreviewPage.obj" \
	"$(INTDIR)\OptionsPrintPage.obj" \
	"$(INTDIR)\OptionsSheet.obj" \
	"$(INTDIR)\PreambleDialog.obj" \
	"$(INTDIR)\Print.obj" \
	"$(INTDIR)\PrintPages.obj" \
	"$(INTDIR)\ProgressDialog.obj" \
	"$(INTDIR)\RegExp.obj" \
	"$(INTDIR)\ReplaceDialog.obj" \
	"$(INTDIR)\ScintillaBibWnd.obj" \
	"$(INTDIR)\ScintillaPrint.obj" \
	"$(INTDIR)\ScintillaWnd.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\SearchProfile.obj" \
	"$(INTDIR)\SearchProfilesDialog.obj" \
	"$(INTDIR)\SourceDialog.obj" \
	"$(INTDIR)\SourceView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringListEx.obj" \
	"$(INTDIR)\StringsDialog.obj" \
	"$(INTDIR)\ToolbarEx.obj" \
	"$(INTDIR)\VisualFx.obj" \
	"$(INTDIR)\XSLTransform.obj" \
	"$(INTDIR)\xString.obj" \
	"$(INTDIR)\YazAbstractXMLParser.obj" \
	"$(INTDIR)\YazCCLQuery.obj" \
	"$(INTDIR)\YazConn.obj" \
	"$(INTDIR)\YazCQLQuery.obj" \
	"$(INTDIR)\YazMARCParser.obj" \
	"$(INTDIR)\YazOPACParser.obj" \
	"$(INTDIR)\YazOpacXMLParser.obj" \
	"$(INTDIR)\YazParser.obj" \
	"$(INTDIR)\YazPrefixQuery.obj" \
	"$(INTDIR)\YazQuery.obj" \
	"$(INTDIR)\YazRecord.obj" \
	"$(INTDIR)\YazResultSet.obj" \
	"$(INTDIR)\YazUsMarcXMLParser.obj" \
	"$(INTDIR)\YazXMLParser.obj" \
	"$(INTDIR)\bibedt.res" \
	"$(INTDIR)\ValueListDialog.obj"

"$(OUTDIR)\bibedt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

OUTDIR=.\Debug_Unicode
INTDIR=.\Debug_Unicode
# Begin Custom Macros
OutDir=.\Debug_Unicode
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\bibedt.exe" "$(OUTDIR)\bibedt.bsc"

!ELSE 

ALL : "$(OUTDIR)\bibedt.exe" "$(OUTDIR)\bibedt.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\ApplyFilterDialog.obj"
	-@erase "$(INTDIR)\ApplyFilterDialog.sbr"
	-@erase "$(INTDIR)\AuxParser.obj"
	-@erase "$(INTDIR)\AuxParser.sbr"
	-@erase "$(INTDIR)\BeIconv.obj"
	-@erase "$(INTDIR)\BeIconv.sbr"
	-@erase "$(INTDIR)\BibDef.obj"
	-@erase "$(INTDIR)\BibDef.sbr"
	-@erase "$(INTDIR)\bibedt.obj"
	-@erase "$(INTDIR)\bibedt.pch"
	-@erase "$(INTDIR)\bibedt.res"
	-@erase "$(INTDIR)\bibedt.sbr"
	-@erase "$(INTDIR)\bibedtDoc.obj"
	-@erase "$(INTDIR)\bibedtDoc.sbr"
	-@erase "$(INTDIR)\BibEdtList.obj"
	-@erase "$(INTDIR)\BibEdtList.sbr"
	-@erase "$(INTDIR)\bibedtView.obj"
	-@erase "$(INTDIR)\bibedtView.sbr"
	-@erase "$(INTDIR)\BibFile.obj"
	-@erase "$(INTDIR)\BibFile.sbr"
	-@erase "$(INTDIR)\BibItem.obj"
	-@erase "$(INTDIR)\BibItem.sbr"
	-@erase "$(INTDIR)\BibitemView.obj"
	-@erase "$(INTDIR)\BibitemView.sbr"
	-@erase "$(INTDIR)\BibList.obj"
	-@erase "$(INTDIR)\BibList.sbr"
	-@erase "$(INTDIR)\BibReader.obj"
	-@erase "$(INTDIR)\BibReader.sbr"
	-@erase "$(INTDIR)\BibWriter.obj"
	-@erase "$(INTDIR)\BibWriter.sbr"
	-@erase "$(INTDIR)\Coding.obj"
	-@erase "$(INTDIR)\Coding.sbr"
	-@erase "$(INTDIR)\CodingHTML.obj"
	-@erase "$(INTDIR)\CodingHTML.sbr"
	-@erase "$(INTDIR)\CodingRTF.obj"
	-@erase "$(INTDIR)\CodingRTF.sbr"
	-@erase "$(INTDIR)\CodingTeX.obj"
	-@erase "$(INTDIR)\CodingTeX.sbr"
	-@erase "$(INTDIR)\CodingXML.obj"
	-@erase "$(INTDIR)\CodingXML.sbr"
	-@erase "$(INTDIR)\ColumnsDialog.obj"
	-@erase "$(INTDIR)\ColumnsDialog.sbr"
	-@erase "$(INTDIR)\CopyCitationDialog.obj"
	-@erase "$(INTDIR)\CopyCitationDialog.sbr"
	-@erase "$(INTDIR)\CustomizeDialog.obj"
	-@erase "$(INTDIR)\CustomizeDialog.sbr"
	-@erase "$(INTDIR)\DocMgrEx.obj"
	-@erase "$(INTDIR)\DocMgrEx.sbr"
	-@erase "$(INTDIR)\EditCell.obj"
	-@erase "$(INTDIR)\EditCell.sbr"
	-@erase "$(INTDIR)\Export.obj"
	-@erase "$(INTDIR)\Export.sbr"
	-@erase "$(INTDIR)\ExportBib.obj"
	-@erase "$(INTDIR)\ExportBib.sbr"
	-@erase "$(INTDIR)\ExportCopyHtml.obj"
	-@erase "$(INTDIR)\ExportCopyHtml.sbr"
	-@erase "$(INTDIR)\ExportDialog.obj"
	-@erase "$(INTDIR)\ExportDialog.sbr"
	-@erase "$(INTDIR)\ExporterList.obj"
	-@erase "$(INTDIR)\ExporterList.sbr"
	-@erase "$(INTDIR)\ExportGeneric.obj"
	-@erase "$(INTDIR)\ExportGeneric.sbr"
	-@erase "$(INTDIR)\ExportInternal.obj"
	-@erase "$(INTDIR)\ExportInternal.sbr"
	-@erase "$(INTDIR)\ExportKeygen.obj"
	-@erase "$(INTDIR)\ExportKeygen.sbr"
	-@erase "$(INTDIR)\ExportPreview.obj"
	-@erase "$(INTDIR)\ExportPreview.sbr"
	-@erase "$(INTDIR)\ExportRTF.obj"
	-@erase "$(INTDIR)\ExportRTF.sbr"
	-@erase "$(INTDIR)\ExportText.obj"
	-@erase "$(INTDIR)\ExportText.sbr"
	-@erase "$(INTDIR)\ExportXML.obj"
	-@erase "$(INTDIR)\ExportXML.sbr"
	-@erase "$(INTDIR)\Field.obj"
	-@erase "$(INTDIR)\Field.sbr"
	-@erase "$(INTDIR)\FieldList.obj"
	-@erase "$(INTDIR)\FieldList.sbr"
	-@erase "$(INTDIR)\FileDialogEx.obj"
	-@erase "$(INTDIR)\FileDialogEx.sbr"
	-@erase "$(INTDIR)\FileWatch.obj"
	-@erase "$(INTDIR)\FileWatch.sbr"
	-@erase "$(INTDIR)\FilterDialog.obj"
	-@erase "$(INTDIR)\FilterDialog.sbr"
	-@erase "$(INTDIR)\FindDialog.obj"
	-@erase "$(INTDIR)\FindDialog.sbr"
	-@erase "$(INTDIR)\FindDuplicatesDialog.obj"
	-@erase "$(INTDIR)\FindDuplicatesDialog.sbr"
	-@erase "$(INTDIR)\FindDupOptionsDialog.obj"
	-@erase "$(INTDIR)\FindDupOptionsDialog.sbr"
	-@erase "$(INTDIR)\GenFromAuxDialog.obj"
	-@erase "$(INTDIR)\GenFromAuxDialog.sbr"
	-@erase "$(INTDIR)\Globals.obj"
	-@erase "$(INTDIR)\Globals.sbr"
	-@erase "$(INTDIR)\HTMLCODES.OBJ"
	-@erase "$(INTDIR)\HTMLCODES.SBR"
	-@erase "$(INTDIR)\HTMLView.obj"
	-@erase "$(INTDIR)\HTMLView.sbr"
	-@erase "$(INTDIR)\htmlviewer.obj"
	-@erase "$(INTDIR)\htmlviewer.sbr"
	-@erase "$(INTDIR)\InputBox.obj"
	-@erase "$(INTDIR)\InputBox.sbr"
	-@erase "$(INTDIR)\KeysDialog.obj"
	-@erase "$(INTDIR)\KeysDialog.sbr"
	-@erase "$(INTDIR)\Language.obj"
	-@erase "$(INTDIR)\Language.sbr"
	-@erase "$(INTDIR)\LinkStatic.obj"
	-@erase "$(INTDIR)\LinkStatic.sbr"
	-@erase "$(INTDIR)\ListCtrlEx.obj"
	-@erase "$(INTDIR)\ListCtrlEx.sbr"
	-@erase "$(INTDIR)\ListViewPrint.obj"
	-@erase "$(INTDIR)\ListViewPrint.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\MyBitmapButton.obj"
	-@erase "$(INTDIR)\MyBitmapButton.sbr"
	-@erase "$(INTDIR)\OnlineSearch.obj"
	-@erase "$(INTDIR)\OnlineSearch.sbr"
	-@erase "$(INTDIR)\Options.obj"
	-@erase "$(INTDIR)\Options.sbr"
	-@erase "$(INTDIR)\OptionsEditorPage.obj"
	-@erase "$(INTDIR)\OptionsEditorPage.sbr"
	-@erase "$(INTDIR)\OptionsExporterPage.obj"
	-@erase "$(INTDIR)\OptionsExporterPage.sbr"
	-@erase "$(INTDIR)\OptionsFilePage.obj"
	-@erase "$(INTDIR)\OptionsFilePage.sbr"
	-@erase "$(INTDIR)\OptionsGeneralPage.obj"
	-@erase "$(INTDIR)\OptionsGeneralPage.sbr"
	-@erase "$(INTDIR)\OptionsLanguagePage.obj"
	-@erase "$(INTDIR)\OptionsLanguagePage.sbr"
	-@erase "$(INTDIR)\OptionsPreviewPage.obj"
	-@erase "$(INTDIR)\OptionsPreviewPage.sbr"
	-@erase "$(INTDIR)\OptionsPrintPage.obj"
	-@erase "$(INTDIR)\OptionsPrintPage.sbr"
	-@erase "$(INTDIR)\OptionsSheet.obj"
	-@erase "$(INTDIR)\OptionsSheet.sbr"
	-@erase "$(INTDIR)\PreambleDialog.obj"
	-@erase "$(INTDIR)\PreambleDialog.sbr"
	-@erase "$(INTDIR)\Print.obj"
	-@erase "$(INTDIR)\Print.sbr"
	-@erase "$(INTDIR)\PrintPages.obj"
	-@erase "$(INTDIR)\PrintPages.sbr"
	-@erase "$(INTDIR)\ProgressDialog.obj"
	-@erase "$(INTDIR)\ProgressDialog.sbr"
	-@erase "$(INTDIR)\RegExp.obj"
	-@erase "$(INTDIR)\RegExp.sbr"
	-@erase "$(INTDIR)\ReplaceDialog.obj"
	-@erase "$(INTDIR)\ReplaceDialog.sbr"
	-@erase "$(INTDIR)\ScintillaBibWnd.obj"
	-@erase "$(INTDIR)\ScintillaBibWnd.sbr"
	-@erase "$(INTDIR)\ScintillaPrint.obj"
	-@erase "$(INTDIR)\ScintillaPrint.sbr"
	-@erase "$(INTDIR)\ScintillaWnd.obj"
	-@erase "$(INTDIR)\ScintillaWnd.sbr"
	-@erase "$(INTDIR)\SearchDialog.obj"
	-@erase "$(INTDIR)\SearchDialog.sbr"
	-@erase "$(INTDIR)\SearchProfile.obj"
	-@erase "$(INTDIR)\SearchProfile.sbr"
	-@erase "$(INTDIR)\SearchProfilesDialog.obj"
	-@erase "$(INTDIR)\SearchProfilesDialog.sbr"
	-@erase "$(INTDIR)\SourceDialog.obj"
	-@erase "$(INTDIR)\SourceDialog.sbr"
	-@erase "$(INTDIR)\SourceView.obj"
	-@erase "$(INTDIR)\SourceView.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StringListEx.obj"
	-@erase "$(INTDIR)\StringListEx.sbr"
	-@erase "$(INTDIR)\StringsDialog.obj"
	-@erase "$(INTDIR)\StringsDialog.sbr"
	-@erase "$(INTDIR)\ToolbarEx.obj"
	-@erase "$(INTDIR)\ToolbarEx.sbr"
	-@erase "$(INTDIR)\ValueListDialog.obj"
	-@erase "$(INTDIR)\ValueListDialog.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VisualFx.obj"
	-@erase "$(INTDIR)\VisualFx.sbr"
	-@erase "$(INTDIR)\XSLTransform.obj"
	-@erase "$(INTDIR)\XSLTransform.sbr"
	-@erase "$(INTDIR)\xString.obj"
	-@erase "$(INTDIR)\xString.sbr"
	-@erase "$(INTDIR)\YazAbstractXMLParser.obj"
	-@erase "$(INTDIR)\YazAbstractXMLParser.sbr"
	-@erase "$(INTDIR)\YazCCLQuery.obj"
	-@erase "$(INTDIR)\YazCCLQuery.sbr"
	-@erase "$(INTDIR)\YazConn.obj"
	-@erase "$(INTDIR)\YazConn.sbr"
	-@erase "$(INTDIR)\YazCQLQuery.obj"
	-@erase "$(INTDIR)\YazCQLQuery.sbr"
	-@erase "$(INTDIR)\YazMARCParser.obj"
	-@erase "$(INTDIR)\YazMARCParser.sbr"
	-@erase "$(INTDIR)\YazOPACParser.obj"
	-@erase "$(INTDIR)\YazOPACParser.sbr"
	-@erase "$(INTDIR)\YazOpacXMLParser.obj"
	-@erase "$(INTDIR)\YazOpacXMLParser.sbr"
	-@erase "$(INTDIR)\YazParser.obj"
	-@erase "$(INTDIR)\YazParser.sbr"
	-@erase "$(INTDIR)\YazPrefixQuery.obj"
	-@erase "$(INTDIR)\YazPrefixQuery.sbr"
	-@erase "$(INTDIR)\YazQuery.obj"
	-@erase "$(INTDIR)\YazQuery.sbr"
	-@erase "$(INTDIR)\YazRecord.obj"
	-@erase "$(INTDIR)\YazRecord.sbr"
	-@erase "$(INTDIR)\YazResultSet.obj"
	-@erase "$(INTDIR)\YazResultSet.sbr"
	-@erase "$(INTDIR)\YazUsMarcXMLParser.obj"
	-@erase "$(INTDIR)\YazUsMarcXMLParser.sbr"
	-@erase "$(INTDIR)\YazXMLParser.obj"
	-@erase "$(INTDIR)\YazXMLParser.sbr"
	-@erase "$(OUTDIR)\bibedt.bsc"
	-@erase "$(OUTDIR)\bibedt.exe"
	-@erase "$(OUTDIR)\bibedt.ilk"
	-@erase "$(OUTDIR)\bibedt.map"
	-@erase "$(OUTDIR)\bibedt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bibedt.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\bibedt.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bibedt.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ApplyFilterDialog.sbr" \
	"$(INTDIR)\AuxParser.sbr" \
	"$(INTDIR)\BeIconv.sbr" \
	"$(INTDIR)\BibDef.sbr" \
	"$(INTDIR)\bibedt.sbr" \
	"$(INTDIR)\bibedtDoc.sbr" \
	"$(INTDIR)\BibEdtList.sbr" \
	"$(INTDIR)\bibedtView.sbr" \
	"$(INTDIR)\BibFile.sbr" \
	"$(INTDIR)\BibItem.sbr" \
	"$(INTDIR)\BibitemView.sbr" \
	"$(INTDIR)\BibList.sbr" \
	"$(INTDIR)\BibReader.sbr" \
	"$(INTDIR)\BibWriter.sbr" \
	"$(INTDIR)\Coding.sbr" \
	"$(INTDIR)\CodingHTML.sbr" \
	"$(INTDIR)\CodingRTF.sbr" \
	"$(INTDIR)\CodingTeX.sbr" \
	"$(INTDIR)\CodingXML.sbr" \
	"$(INTDIR)\ColumnsDialog.sbr" \
	"$(INTDIR)\CopyCitationDialog.sbr" \
	"$(INTDIR)\CustomizeDialog.sbr" \
	"$(INTDIR)\DocMgrEx.sbr" \
	"$(INTDIR)\EditCell.sbr" \
	"$(INTDIR)\Export.sbr" \
	"$(INTDIR)\ExportBib.sbr" \
	"$(INTDIR)\ExportCopyHtml.sbr" \
	"$(INTDIR)\ExportDialog.sbr" \
	"$(INTDIR)\ExporterList.sbr" \
	"$(INTDIR)\ExportGeneric.sbr" \
	"$(INTDIR)\ExportInternal.sbr" \
	"$(INTDIR)\ExportKeygen.sbr" \
	"$(INTDIR)\ExportPreview.sbr" \
	"$(INTDIR)\ExportRTF.sbr" \
	"$(INTDIR)\ExportText.sbr" \
	"$(INTDIR)\ExportXML.sbr" \
	"$(INTDIR)\Field.sbr" \
	"$(INTDIR)\FieldList.sbr" \
	"$(INTDIR)\FileDialogEx.sbr" \
	"$(INTDIR)\FileWatch.sbr" \
	"$(INTDIR)\FilterDialog.sbr" \
	"$(INTDIR)\FindDialog.sbr" \
	"$(INTDIR)\FindDuplicatesDialog.sbr" \
	"$(INTDIR)\FindDupOptionsDialog.sbr" \
	"$(INTDIR)\GenFromAuxDialog.sbr" \
	"$(INTDIR)\Globals.sbr" \
	"$(INTDIR)\HTMLCODES.SBR" \
	"$(INTDIR)\HTMLView.sbr" \
	"$(INTDIR)\htmlviewer.sbr" \
	"$(INTDIR)\InputBox.sbr" \
	"$(INTDIR)\KeysDialog.sbr" \
	"$(INTDIR)\Language.sbr" \
	"$(INTDIR)\LinkStatic.sbr" \
	"$(INTDIR)\ListCtrlEx.sbr" \
	"$(INTDIR)\ListViewPrint.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\MyBitmapButton.sbr" \
	"$(INTDIR)\OnlineSearch.sbr" \
	"$(INTDIR)\Options.sbr" \
	"$(INTDIR)\OptionsEditorPage.sbr" \
	"$(INTDIR)\OptionsExporterPage.sbr" \
	"$(INTDIR)\OptionsFilePage.sbr" \
	"$(INTDIR)\OptionsGeneralPage.sbr" \
	"$(INTDIR)\OptionsLanguagePage.sbr" \
	"$(INTDIR)\OptionsPreviewPage.sbr" \
	"$(INTDIR)\OptionsPrintPage.sbr" \
	"$(INTDIR)\OptionsSheet.sbr" \
	"$(INTDIR)\PreambleDialog.sbr" \
	"$(INTDIR)\Print.sbr" \
	"$(INTDIR)\PrintPages.sbr" \
	"$(INTDIR)\ProgressDialog.sbr" \
	"$(INTDIR)\RegExp.sbr" \
	"$(INTDIR)\ReplaceDialog.sbr" \
	"$(INTDIR)\ScintillaBibWnd.sbr" \
	"$(INTDIR)\ScintillaPrint.sbr" \
	"$(INTDIR)\ScintillaWnd.sbr" \
	"$(INTDIR)\SearchDialog.sbr" \
	"$(INTDIR)\SearchProfile.sbr" \
	"$(INTDIR)\SearchProfilesDialog.sbr" \
	"$(INTDIR)\SourceDialog.sbr" \
	"$(INTDIR)\SourceView.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StringListEx.sbr" \
	"$(INTDIR)\StringsDialog.sbr" \
	"$(INTDIR)\ToolbarEx.sbr" \
	"$(INTDIR)\VisualFx.sbr" \
	"$(INTDIR)\XSLTransform.sbr" \
	"$(INTDIR)\xString.sbr" \
	"$(INTDIR)\YazAbstractXMLParser.sbr" \
	"$(INTDIR)\YazCCLQuery.sbr" \
	"$(INTDIR)\YazConn.sbr" \
	"$(INTDIR)\YazCQLQuery.sbr" \
	"$(INTDIR)\YazMARCParser.sbr" \
	"$(INTDIR)\YazOPACParser.sbr" \
	"$(INTDIR)\YazOpacXMLParser.sbr" \
	"$(INTDIR)\YazParser.sbr" \
	"$(INTDIR)\YazPrefixQuery.sbr" \
	"$(INTDIR)\YazQuery.sbr" \
	"$(INTDIR)\YazRecord.sbr" \
	"$(INTDIR)\YazResultSet.sbr" \
	"$(INTDIR)\YazUsMarcXMLParser.sbr" \
	"$(INTDIR)\YazXMLParser.sbr" \
	"$(INTDIR)\ValueListDialog.sbr"

"$(OUTDIR)\bibedt.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=Debug\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\bibedt.pdb" /map:"$(INTDIR)\bibedt.map" /debug /machine:I386 /out:"$(OUTDIR)\bibedt.exe" /pdbtype:sept /libpath:"Debug" /libpath:"xaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib" 
LINK32_OBJS= \
	"$(INTDIR)\ApplyFilterDialog.obj" \
	"$(INTDIR)\AuxParser.obj" \
	"$(INTDIR)\BeIconv.obj" \
	"$(INTDIR)\BibDef.obj" \
	"$(INTDIR)\bibedt.obj" \
	"$(INTDIR)\bibedtDoc.obj" \
	"$(INTDIR)\BibEdtList.obj" \
	"$(INTDIR)\bibedtView.obj" \
	"$(INTDIR)\BibFile.obj" \
	"$(INTDIR)\BibItem.obj" \
	"$(INTDIR)\BibitemView.obj" \
	"$(INTDIR)\BibList.obj" \
	"$(INTDIR)\BibReader.obj" \
	"$(INTDIR)\BibWriter.obj" \
	"$(INTDIR)\Coding.obj" \
	"$(INTDIR)\CodingHTML.obj" \
	"$(INTDIR)\CodingRTF.obj" \
	"$(INTDIR)\CodingTeX.obj" \
	"$(INTDIR)\CodingXML.obj" \
	"$(INTDIR)\ColumnsDialog.obj" \
	"$(INTDIR)\CopyCitationDialog.obj" \
	"$(INTDIR)\CustomizeDialog.obj" \
	"$(INTDIR)\DocMgrEx.obj" \
	"$(INTDIR)\EditCell.obj" \
	"$(INTDIR)\Export.obj" \
	"$(INTDIR)\ExportBib.obj" \
	"$(INTDIR)\ExportCopyHtml.obj" \
	"$(INTDIR)\ExportDialog.obj" \
	"$(INTDIR)\ExporterList.obj" \
	"$(INTDIR)\ExportGeneric.obj" \
	"$(INTDIR)\ExportInternal.obj" \
	"$(INTDIR)\ExportKeygen.obj" \
	"$(INTDIR)\ExportPreview.obj" \
	"$(INTDIR)\ExportRTF.obj" \
	"$(INTDIR)\ExportText.obj" \
	"$(INTDIR)\ExportXML.obj" \
	"$(INTDIR)\Field.obj" \
	"$(INTDIR)\FieldList.obj" \
	"$(INTDIR)\FileDialogEx.obj" \
	"$(INTDIR)\FileWatch.obj" \
	"$(INTDIR)\FilterDialog.obj" \
	"$(INTDIR)\FindDialog.obj" \
	"$(INTDIR)\FindDuplicatesDialog.obj" \
	"$(INTDIR)\FindDupOptionsDialog.obj" \
	"$(INTDIR)\GenFromAuxDialog.obj" \
	"$(INTDIR)\Globals.obj" \
	"$(INTDIR)\HTMLCODES.OBJ" \
	"$(INTDIR)\HTMLView.obj" \
	"$(INTDIR)\htmlviewer.obj" \
	"$(INTDIR)\InputBox.obj" \
	"$(INTDIR)\KeysDialog.obj" \
	"$(INTDIR)\Language.obj" \
	"$(INTDIR)\LinkStatic.obj" \
	"$(INTDIR)\ListCtrlEx.obj" \
	"$(INTDIR)\ListViewPrint.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\MyBitmapButton.obj" \
	"$(INTDIR)\OnlineSearch.obj" \
	"$(INTDIR)\Options.obj" \
	"$(INTDIR)\OptionsEditorPage.obj" \
	"$(INTDIR)\OptionsExporterPage.obj" \
	"$(INTDIR)\OptionsFilePage.obj" \
	"$(INTDIR)\OptionsGeneralPage.obj" \
	"$(INTDIR)\OptionsLanguagePage.obj" \
	"$(INTDIR)\OptionsPreviewPage.obj" \
	"$(INTDIR)\OptionsPrintPage.obj" \
	"$(INTDIR)\OptionsSheet.obj" \
	"$(INTDIR)\PreambleDialog.obj" \
	"$(INTDIR)\Print.obj" \
	"$(INTDIR)\PrintPages.obj" \
	"$(INTDIR)\ProgressDialog.obj" \
	"$(INTDIR)\RegExp.obj" \
	"$(INTDIR)\ReplaceDialog.obj" \
	"$(INTDIR)\ScintillaBibWnd.obj" \
	"$(INTDIR)\ScintillaPrint.obj" \
	"$(INTDIR)\ScintillaWnd.obj" \
	"$(INTDIR)\SearchDialog.obj" \
	"$(INTDIR)\SearchProfile.obj" \
	"$(INTDIR)\SearchProfilesDialog.obj" \
	"$(INTDIR)\SourceDialog.obj" \
	"$(INTDIR)\SourceView.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StringListEx.obj" \
	"$(INTDIR)\StringsDialog.obj" \
	"$(INTDIR)\ToolbarEx.obj" \
	"$(INTDIR)\VisualFx.obj" \
	"$(INTDIR)\XSLTransform.obj" \
	"$(INTDIR)\xString.obj" \
	"$(INTDIR)\YazAbstractXMLParser.obj" \
	"$(INTDIR)\YazCCLQuery.obj" \
	"$(INTDIR)\YazConn.obj" \
	"$(INTDIR)\YazCQLQuery.obj" \
	"$(INTDIR)\YazMARCParser.obj" \
	"$(INTDIR)\YazOPACParser.obj" \
	"$(INTDIR)\YazOpacXMLParser.obj" \
	"$(INTDIR)\YazParser.obj" \
	"$(INTDIR)\YazPrefixQuery.obj" \
	"$(INTDIR)\YazQuery.obj" \
	"$(INTDIR)\YazRecord.obj" \
	"$(INTDIR)\YazResultSet.obj" \
	"$(INTDIR)\YazUsMarcXMLParser.obj" \
	"$(INTDIR)\YazXMLParser.obj" \
	"$(INTDIR)\bibedt.res" \
	"$(INTDIR)\ValueListDialog.obj"

"$(OUTDIR)\bibedt.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("bibedt.dep")
!INCLUDE "bibedt.dep"
!ELSE 
!MESSAGE Warning: cannot find "bibedt.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "bibedt - Win32 Release" || "$(CFG)" == "bibedt - Win32 Debug" || "$(CFG)" == "bibedt - Win32 Release Unicode" || "$(CFG)" == "bibedt - Win32 Debug Unicode"
SOURCE=.\ApplyFilterDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ApplyFilterDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ApplyFilterDialog.obj"	"$(INTDIR)\ApplyFilterDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ApplyFilterDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ApplyFilterDialog.obj"	"$(INTDIR)\ApplyFilterDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\AuxParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\AuxParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\AuxParser.obj"	"$(INTDIR)\AuxParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\AuxParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\AuxParser.obj"	"$(INTDIR)\AuxParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BeIconv.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BeIconv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BeIconv.obj"	"$(INTDIR)\BeIconv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BeIconv.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BeIconv.obj"	"$(INTDIR)\BeIconv.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibDef.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibDef.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibDef.obj"	"$(INTDIR)\BibDef.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibDef.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibDef.obj"	"$(INTDIR)\BibDef.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\bibedt.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\bibedt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\bibedt.obj"	"$(INTDIR)\bibedt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\bibedt.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\bibedt.obj"	"$(INTDIR)\bibedt.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\bibedt.rc

"$(INTDIR)\bibedt.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\bibedtDoc.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\bibedtDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\bibedtDoc.obj"	"$(INTDIR)\bibedtDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\bibedtDoc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\bibedtDoc.obj"	"$(INTDIR)\bibedtDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibEdtList.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibEdtList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibEdtList.obj"	"$(INTDIR)\BibEdtList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibEdtList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibEdtList.obj"	"$(INTDIR)\BibEdtList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\bibedtView.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\bibedtView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\bibedtView.obj"	"$(INTDIR)\bibedtView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\bibedtView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\bibedtView.obj"	"$(INTDIR)\bibedtView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibFile.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibFile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibFile.obj"	"$(INTDIR)\BibFile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibFile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibFile.obj"	"$(INTDIR)\BibFile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibItem.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibItem.obj"	"$(INTDIR)\BibItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibItem.obj"	"$(INTDIR)\BibItem.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibitemView.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibitemView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibitemView.obj"	"$(INTDIR)\BibitemView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibitemView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibitemView.obj"	"$(INTDIR)\BibitemView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibList.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibList.obj"	"$(INTDIR)\BibList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibList.obj"	"$(INTDIR)\BibList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibReader.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibReader.obj"	"$(INTDIR)\BibReader.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibReader.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibReader.obj"	"$(INTDIR)\BibReader.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\BibWriter.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\BibWriter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\BibWriter.obj"	"$(INTDIR)\BibWriter.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\BibWriter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\BibWriter.obj"	"$(INTDIR)\BibWriter.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Coding.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Coding.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Coding.obj"	"$(INTDIR)\Coding.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Coding.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Coding.obj"	"$(INTDIR)\Coding.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\CodingHTML.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\CodingHTML.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\CodingHTML.obj"	"$(INTDIR)\CodingHTML.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\CodingHTML.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\CodingHTML.obj"	"$(INTDIR)\CodingHTML.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\CodingRTF.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\CodingRTF.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\CodingRTF.obj"	"$(INTDIR)\CodingRTF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\CodingRTF.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\CodingRTF.obj"	"$(INTDIR)\CodingRTF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\CodingTeX.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\CodingTeX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\CodingTeX.obj"	"$(INTDIR)\CodingTeX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\CodingTeX.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\CodingTeX.obj"	"$(INTDIR)\CodingTeX.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\CodingXML.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\CodingXML.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\CodingXML.obj"	"$(INTDIR)\CodingXML.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\CodingXML.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\CodingXML.obj"	"$(INTDIR)\CodingXML.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ColumnsDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ColumnsDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ColumnsDialog.obj"	"$(INTDIR)\ColumnsDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ColumnsDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ColumnsDialog.obj"	"$(INTDIR)\ColumnsDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\CopyCitationDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\CopyCitationDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\CopyCitationDialog.obj"	"$(INTDIR)\CopyCitationDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\CopyCitationDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\CopyCitationDialog.obj"	"$(INTDIR)\CopyCitationDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\CustomizeDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\CustomizeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\CustomizeDialog.obj"	"$(INTDIR)\CustomizeDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\CustomizeDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\CustomizeDialog.obj"	"$(INTDIR)\CustomizeDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\DocMgrEx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\DocMgrEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\DocMgrEx.obj"	"$(INTDIR)\DocMgrEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\DocMgrEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\DocMgrEx.obj"	"$(INTDIR)\DocMgrEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\EditCell.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\EditCell.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\EditCell.obj"	"$(INTDIR)\EditCell.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\EditCell.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\EditCell.obj"	"$(INTDIR)\EditCell.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Export.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Export.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Export.obj"	"$(INTDIR)\Export.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Export.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Export.obj"	"$(INTDIR)\Export.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportBib.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportBib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportBib.obj"	"$(INTDIR)\ExportBib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportBib.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportBib.obj"	"$(INTDIR)\ExportBib.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportCopyHtml.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportCopyHtml.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportCopyHtml.obj"	"$(INTDIR)\ExportCopyHtml.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportCopyHtml.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportCopyHtml.obj"	"$(INTDIR)\ExportCopyHtml.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportDialog.obj"	"$(INTDIR)\ExportDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportDialog.obj"	"$(INTDIR)\ExportDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExporterList.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExporterList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExporterList.obj"	"$(INTDIR)\ExporterList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExporterList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExporterList.obj"	"$(INTDIR)\ExporterList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportGeneric.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportGeneric.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportGeneric.obj"	"$(INTDIR)\ExportGeneric.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportGeneric.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportGeneric.obj"	"$(INTDIR)\ExportGeneric.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportInternal.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportInternal.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportInternal.obj"	"$(INTDIR)\ExportInternal.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportInternal.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportInternal.obj"	"$(INTDIR)\ExportInternal.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportKeygen.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportKeygen.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportKeygen.obj"	"$(INTDIR)\ExportKeygen.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportKeygen.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportKeygen.obj"	"$(INTDIR)\ExportKeygen.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportPreview.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportPreview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportPreview.obj"	"$(INTDIR)\ExportPreview.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportPreview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportPreview.obj"	"$(INTDIR)\ExportPreview.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportRTF.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportRTF.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportRTF.obj"	"$(INTDIR)\ExportRTF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportRTF.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportRTF.obj"	"$(INTDIR)\ExportRTF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportText.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportText.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportText.obj"	"$(INTDIR)\ExportText.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportText.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportText.obj"	"$(INTDIR)\ExportText.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ExportXML.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ExportXML.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ExportXML.obj"	"$(INTDIR)\ExportXML.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ExportXML.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ExportXML.obj"	"$(INTDIR)\ExportXML.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Field.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Field.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Field.obj"	"$(INTDIR)\Field.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Field.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Field.obj"	"$(INTDIR)\Field.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FieldList.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FieldList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FieldList.obj"	"$(INTDIR)\FieldList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FieldList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FieldList.obj"	"$(INTDIR)\FieldList.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FileDialogEx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FileDialogEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FileDialogEx.obj"	"$(INTDIR)\FileDialogEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FileDialogEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FileDialogEx.obj"	"$(INTDIR)\FileDialogEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FileWatch.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FileWatch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FileWatch.obj"	"$(INTDIR)\FileWatch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FileWatch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FileWatch.obj"	"$(INTDIR)\FileWatch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FilterDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FilterDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FilterDialog.obj"	"$(INTDIR)\FilterDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FilterDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FilterDialog.obj"	"$(INTDIR)\FilterDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FindDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FindDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FindDialog.obj"	"$(INTDIR)\FindDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FindDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FindDialog.obj"	"$(INTDIR)\FindDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FindDuplicatesDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FindDuplicatesDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FindDuplicatesDialog.obj"	"$(INTDIR)\FindDuplicatesDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FindDuplicatesDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FindDuplicatesDialog.obj"	"$(INTDIR)\FindDuplicatesDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\FindDupOptionsDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\FindDupOptionsDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\FindDupOptionsDialog.obj"	"$(INTDIR)\FindDupOptionsDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\FindDupOptionsDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\FindDupOptionsDialog.obj"	"$(INTDIR)\FindDupOptionsDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\GenFromAuxDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\GenFromAuxDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\GenFromAuxDialog.obj"	"$(INTDIR)\GenFromAuxDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\GenFromAuxDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\GenFromAuxDialog.obj"	"$(INTDIR)\GenFromAuxDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Globals.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Globals.obj"	"$(INTDIR)\Globals.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Globals.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Globals.obj"	"$(INTDIR)\Globals.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\HTMLCODES.CPP

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\HTMLCODES.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\HTMLCODES.OBJ"	"$(INTDIR)\HTMLCODES.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\HTMLCODES.OBJ" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\HTMLCODES.OBJ"	"$(INTDIR)\HTMLCODES.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\HTMLView.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\HTMLView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\HTMLView.obj"	"$(INTDIR)\HTMLView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\HTMLView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\HTMLView.obj"	"$(INTDIR)\HTMLView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\htmlviewer.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\htmlviewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\htmlviewer.obj"	"$(INTDIR)\htmlviewer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\htmlviewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\htmlviewer.obj"	"$(INTDIR)\htmlviewer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\InputBox.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\InputBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\InputBox.obj"	"$(INTDIR)\InputBox.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\InputBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\InputBox.obj"	"$(INTDIR)\InputBox.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\KeysDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\KeysDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\KeysDialog.obj"	"$(INTDIR)\KeysDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\KeysDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\KeysDialog.obj"	"$(INTDIR)\KeysDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Language.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Language.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Language.obj"	"$(INTDIR)\Language.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Language.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Language.obj"	"$(INTDIR)\Language.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\LinkStatic.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\LinkStatic.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\LinkStatic.obj"	"$(INTDIR)\LinkStatic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\LinkStatic.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\LinkStatic.obj"	"$(INTDIR)\LinkStatic.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ListCtrlEx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ListCtrlEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ListCtrlEx.obj"	"$(INTDIR)\ListCtrlEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ListCtrlEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ListCtrlEx.obj"	"$(INTDIR)\ListCtrlEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ListViewPrint.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ListViewPrint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ListViewPrint.obj"	"$(INTDIR)\ListViewPrint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ListViewPrint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ListViewPrint.obj"	"$(INTDIR)\ListViewPrint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\MainFrm.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\MyBitmapButton.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\MyBitmapButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\MyBitmapButton.obj"	"$(INTDIR)\MyBitmapButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\MyBitmapButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\MyBitmapButton.obj"	"$(INTDIR)\MyBitmapButton.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OnlineSearch.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OnlineSearch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OnlineSearch.obj"	"$(INTDIR)\OnlineSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OnlineSearch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OnlineSearch.obj"	"$(INTDIR)\OnlineSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Options.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Options.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Options.obj"	"$(INTDIR)\Options.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Options.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Options.obj"	"$(INTDIR)\Options.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsEditorPage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsEditorPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsEditorPage.obj"	"$(INTDIR)\OptionsEditorPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsEditorPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsEditorPage.obj"	"$(INTDIR)\OptionsEditorPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsExporterPage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsExporterPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsExporterPage.obj"	"$(INTDIR)\OptionsExporterPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsExporterPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsExporterPage.obj"	"$(INTDIR)\OptionsExporterPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsFilePage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsFilePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsFilePage.obj"	"$(INTDIR)\OptionsFilePage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsFilePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsFilePage.obj"	"$(INTDIR)\OptionsFilePage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsGeneralPage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsGeneralPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsGeneralPage.obj"	"$(INTDIR)\OptionsGeneralPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsGeneralPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsGeneralPage.obj"	"$(INTDIR)\OptionsGeneralPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsLanguagePage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsLanguagePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsLanguagePage.obj"	"$(INTDIR)\OptionsLanguagePage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsLanguagePage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsLanguagePage.obj"	"$(INTDIR)\OptionsLanguagePage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsPreviewPage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsPreviewPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsPreviewPage.obj"	"$(INTDIR)\OptionsPreviewPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsPreviewPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsPreviewPage.obj"	"$(INTDIR)\OptionsPreviewPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsPrintPage.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsPrintPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsPrintPage.obj"	"$(INTDIR)\OptionsPrintPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsPrintPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsPrintPage.obj"	"$(INTDIR)\OptionsPrintPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\OptionsSheet.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\OptionsSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\OptionsSheet.obj"	"$(INTDIR)\OptionsSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\OptionsSheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\OptionsSheet.obj"	"$(INTDIR)\OptionsSheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\PreambleDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\PreambleDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\PreambleDialog.obj"	"$(INTDIR)\PreambleDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\PreambleDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\PreambleDialog.obj"	"$(INTDIR)\PreambleDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\Print.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\Print.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\Print.obj"	"$(INTDIR)\Print.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\Print.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\Print.obj"	"$(INTDIR)\Print.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\PrintPages.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\PrintPages.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\PrintPages.obj"	"$(INTDIR)\PrintPages.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\PrintPages.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\PrintPages.obj"	"$(INTDIR)\PrintPages.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ProgressDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ProgressDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ProgressDialog.obj"	"$(INTDIR)\ProgressDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ProgressDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ProgressDialog.obj"	"$(INTDIR)\ProgressDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\RegExp.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\RegExp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\RegExp.obj"	"$(INTDIR)\RegExp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\RegExp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\RegExp.obj"	"$(INTDIR)\RegExp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ReplaceDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ReplaceDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ReplaceDialog.obj"	"$(INTDIR)\ReplaceDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ReplaceDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ReplaceDialog.obj"	"$(INTDIR)\ReplaceDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ScintillaBibWnd.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ScintillaBibWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ScintillaBibWnd.obj"	"$(INTDIR)\ScintillaBibWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ScintillaBibWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ScintillaBibWnd.obj"	"$(INTDIR)\ScintillaBibWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ScintillaPrint.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ScintillaPrint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ScintillaPrint.obj"	"$(INTDIR)\ScintillaPrint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ScintillaPrint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ScintillaPrint.obj"	"$(INTDIR)\ScintillaPrint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ScintillaWnd.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ScintillaWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ScintillaWnd.obj"	"$(INTDIR)\ScintillaWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ScintillaWnd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ScintillaWnd.obj"	"$(INTDIR)\ScintillaWnd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\SearchDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\SearchDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\SearchDialog.obj"	"$(INTDIR)\SearchDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\SearchDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\SearchDialog.obj"	"$(INTDIR)\SearchDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\SearchProfile.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\SearchProfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\SearchProfile.obj"	"$(INTDIR)\SearchProfile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\SearchProfile.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\SearchProfile.obj"	"$(INTDIR)\SearchProfile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\SearchProfilesDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\SearchProfilesDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\SearchProfilesDialog.obj"	"$(INTDIR)\SearchProfilesDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\SearchProfilesDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\SearchProfilesDialog.obj"	"$(INTDIR)\SearchProfilesDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\SourceDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\SourceDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\SourceDialog.obj"	"$(INTDIR)\SourceDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\SourceDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\SourceDialog.obj"	"$(INTDIR)\SourceDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\SourceView.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\SourceView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\SourceView.obj"	"$(INTDIR)\SourceView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\SourceView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\SourceView.obj"	"$(INTDIR)\SourceView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\bibedt.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bibedt.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bibedt.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\bibedt.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Fp"$(INTDIR)\bibedt.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\bibedt.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bibedt.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\bibedt.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StringListEx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\StringListEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\StringListEx.obj"	"$(INTDIR)\StringListEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\StringListEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\StringListEx.obj"	"$(INTDIR)\StringListEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\StringsDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\StringsDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\StringsDialog.obj"	"$(INTDIR)\StringsDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\StringsDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\StringsDialog.obj"	"$(INTDIR)\StringsDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ToolbarEx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ToolbarEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ToolbarEx.obj"	"$(INTDIR)\ToolbarEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ToolbarEx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ToolbarEx.obj"	"$(INTDIR)\ToolbarEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\ValueListDialog.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\ValueListDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\ValueListDialog.obj"	"$(INTDIR)\ValueListDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\ValueListDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\ValueListDialog.obj"	"$(INTDIR)\ValueListDialog.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\VisualFx.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\VisualFx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\VisualFx.obj"	"$(INTDIR)\VisualFx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\VisualFx.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\VisualFx.obj"	"$(INTDIR)\VisualFx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\XSLTransform.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\XSLTransform.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\XSLTransform.obj"	"$(INTDIR)\XSLTransform.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\XSLTransform.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\XSLTransform.obj"	"$(INTDIR)\XSLTransform.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\xString.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\xString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bibedt.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\xString.obj"	"$(INTDIR)\xString.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\xString.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\bibedt.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\xString.obj"	"$(INTDIR)\xString.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\YazAbstractXMLParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazAbstractXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazAbstractXMLParser.obj"	"$(INTDIR)\YazAbstractXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazAbstractXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazAbstractXMLParser.obj"	"$(INTDIR)\YazAbstractXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazCCLQuery.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazCCLQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazCCLQuery.obj"	"$(INTDIR)\YazCCLQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazCCLQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazCCLQuery.obj"	"$(INTDIR)\YazCCLQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazConn.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazConn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazConn.obj"	"$(INTDIR)\YazConn.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazConn.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazConn.obj"	"$(INTDIR)\YazConn.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazCQLQuery.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazCQLQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazCQLQuery.obj"	"$(INTDIR)\YazCQLQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazCQLQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazCQLQuery.obj"	"$(INTDIR)\YazCQLQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazMARCParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazMARCParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazMARCParser.obj"	"$(INTDIR)\YazMARCParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazMARCParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazMARCParser.obj"	"$(INTDIR)\YazMARCParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazOPACParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazOPACParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazOPACParser.obj"	"$(INTDIR)\YazOPACParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazOPACParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazOPACParser.obj"	"$(INTDIR)\YazOPACParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazOpacXMLParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazOpacXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazOpacXMLParser.obj"	"$(INTDIR)\YazOpacXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazOpacXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazOpacXMLParser.obj"	"$(INTDIR)\YazOpacXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazParser.obj"	"$(INTDIR)\YazParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazParser.obj"	"$(INTDIR)\YazParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazPrefixQuery.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazPrefixQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazPrefixQuery.obj"	"$(INTDIR)\YazPrefixQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazPrefixQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazPrefixQuery.obj"	"$(INTDIR)\YazPrefixQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazQuery.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazQuery.obj"	"$(INTDIR)\YazQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazQuery.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazQuery.obj"	"$(INTDIR)\YazQuery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazRecord.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazRecord.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazRecord.obj"	"$(INTDIR)\YazRecord.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazRecord.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazRecord.obj"	"$(INTDIR)\YazRecord.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazResultSet.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazResultSet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazResultSet.obj"	"$(INTDIR)\YazResultSet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazResultSet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazResultSet.obj"	"$(INTDIR)\YazResultSet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazUsMarcXMLParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazUsMarcXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazUsMarcXMLParser.obj"	"$(INTDIR)\YazUsMarcXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazUsMarcXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazUsMarcXMLParser.obj"	"$(INTDIR)\YazUsMarcXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

SOURCE=.\YazXMLParser.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"


"$(INTDIR)\YazXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"


"$(INTDIR)\YazXMLParser.obj"	"$(INTDIR)\YazXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"


"$(INTDIR)\YazXMLParser.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"


"$(INTDIR)\YazXMLParser.obj"	"$(INTDIR)\YazXMLParser.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\bibedt.pch"


!ENDIF 

!IF  "$(CFG)" == "bibedt - Win32 Release"

"lexbib - Win32 Release" : 
   cd ".\lexbib"
   $(MAKE) /$(MAKEFLAGS) /F ".\lexbib.mak" CFG="lexbib - Win32 Release" 
   cd ".."

"lexbib - Win32 ReleaseCLEAN" : 
   cd ".\lexbib"
   $(MAKE) /$(MAKEFLAGS) /F ".\lexbib.mak" CFG="lexbib - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

"lexbib - Win32 Debug" : 
   cd ".\lexbib"
   $(MAKE) /$(MAKEFLAGS) /F ".\lexbib.mak" CFG="lexbib - Win32 Debug" 
   cd ".."

"lexbib - Win32 DebugCLEAN" : 
   cd ".\lexbib"
   $(MAKE) /$(MAKEFLAGS) /F ".\lexbib.mak" CFG="lexbib - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

!ENDIF 

!IF  "$(CFG)" == "bibedt - Win32 Release"

"regex - Win32 Release" : 
   cd ".\regex"
   $(MAKE) /$(MAKEFLAGS) /F ".\regex.mak" CFG="regex - Win32 Release" 
   cd ".."

"regex - Win32 ReleaseCLEAN" : 
   cd ".\regex"
   $(MAKE) /$(MAKEFLAGS) /F ".\regex.mak" CFG="regex - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

"regex - Win32 Debug" : 
   cd ".\regex"
   $(MAKE) /$(MAKEFLAGS) /F ".\regex.mak" CFG="regex - Win32 Debug" 
   cd ".."

"regex - Win32 DebugCLEAN" : 
   cd ".\regex"
   $(MAKE) /$(MAKEFLAGS) /F ".\regex.mak" CFG="regex - Win32 Debug" RECURSE=1 CLEAN 
   cd ".."

!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

!ENDIF 


!ENDIF 

