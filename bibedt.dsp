# Microsoft Developer Studio Project File - Name="bibedt" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=bibedt - Win32 Debug Unicode
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "bibedt.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "bibedt.mak" CFG="bibedt - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "bibedt - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "bibedt - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE "bibedt - Win32 Release Unicode" (basierend auf  "Win32 (x86) Application")
!MESSAGE "bibedt - Win32 Debug Unicode" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bibedt - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc07 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 Release\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /machine:I386 /libpath:"Release" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib"

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0xc07 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Debug\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"Debug" /libpath:"xaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib"

!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "bibedt___Win32_Release_Unicode"
# PROP BASE Intermediate_Dir "bibedt___Win32_Release_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release_Unicode"
# PROP Intermediate_Dir "Release_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "_UNICODE" /D "UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Release\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /machine:I386 /libpath:"Release" /libpath:"yaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib"
# ADD LINK32 Release\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /machine:I386 /libpath:"Release" /libpath:"yaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "bibedt___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "bibedt___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_Unicode"
# PROP Intermediate_Dir "Debug_Unicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\scintilla\scintilla\include" /I "lexbib" /I "regex" /I "..\yaz\include" /I "..\libxml2\include" /I "..\iconv\include" /I "..\libxslt\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Debug\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"Debug" /libpath:"xaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib"
# ADD LINK32 Debug\regex.lib comctl32.lib version.lib yaz.lib libxml2.lib iconv.lib libxslt.lib /nologo /subsystem:windows /map /debug /machine:I386 /pdbtype:sept /libpath:"Debug" /libpath:"xaz\bin" /libpath:"..\yaz\bin" /libpath:"..\yaz\lib" /libpath:"..\libxml2\lib" /libpath:"..\iconv\lib" /libpath:"..\libxslt\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "bibedt - Win32 Release"
# Name "bibedt - Win32 Debug"
# Name "bibedt - Win32 Release Unicode"
# Name "bibedt - Win32 Debug Unicode"
# Begin Group "Quellcodedateien"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ApplyFilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\AuxParser.cpp
# End Source File
# Begin Source File

SOURCE=.\BeIconv.cpp
# End Source File
# Begin Source File

SOURCE=.\BibDef.cpp
# End Source File
# Begin Source File

SOURCE=.\bibedt.cpp
# End Source File
# Begin Source File

SOURCE=.\bibedt.rc
# End Source File
# Begin Source File

SOURCE=.\bibedtDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\BibEdtList.cpp
# End Source File
# Begin Source File

SOURCE=.\bibedtView.cpp
# End Source File
# Begin Source File

SOURCE=.\BibFile.cpp
# End Source File
# Begin Source File

SOURCE=.\BibItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BibitemView.cpp
# End Source File
# Begin Source File

SOURCE=.\BibList.cpp
# End Source File
# Begin Source File

SOURCE=.\BibReader.cpp
# End Source File
# Begin Source File

SOURCE=.\BibWriter.cpp
# End Source File
# Begin Source File

SOURCE=.\Coding.cpp
# End Source File
# Begin Source File

SOURCE=.\CodingHTML.cpp
# End Source File
# Begin Source File

SOURCE=.\CodingRTF.cpp
# End Source File
# Begin Source File

SOURCE=.\CodingTeX.cpp
# End Source File
# Begin Source File

SOURCE=.\CodingXML.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CopyCitationDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomizeDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\DocMgrEx.cpp
# End Source File
# Begin Source File

SOURCE=.\EditCell.cpp
# End Source File
# Begin Source File

SOURCE=.\Export.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportBib.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportCopyHtml.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ExporterList.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportGeneric.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportInternal.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportKeygen.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportRTF.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportText.cpp
# End Source File
# Begin Source File

SOURCE=.\ExportXML.cpp
# End Source File
# Begin Source File

SOURCE=.\Field.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldList.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDialogEx.cpp
# End Source File
# Begin Source File

SOURCE=.\FileWatch.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FindDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FindDuplicatesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\FindDupOptionsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\GenFromAuxDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Globals.cpp
# End Source File
# Begin Source File

SOURCE=.\HTMLCODES.CPP
# End Source File
# Begin Source File

SOURCE=.\HTMLView.cpp
# End Source File
# Begin Source File

SOURCE=.\htmlviewer.cpp
# End Source File
# Begin Source File

SOURCE=.\InputBox.cpp
# End Source File
# Begin Source File

SOURCE=.\KeysDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Language.cpp
# End Source File
# Begin Source File

SOURCE=.\LinkStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ListViewPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyBitmapButton.cpp
# End Source File
# Begin Source File

SOURCE=.\OnlineSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\Options.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsEditorPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsExporterPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsFilePage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsGeneralPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsLanguagePage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPreviewPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsPrintPage.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.cpp
# End Source File
# Begin Source File

SOURCE=.\PreambleDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\Print.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintPages.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\RegExp.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplaceDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaBibWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\ScintillaWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchProfile.cpp
# End Source File
# Begin Source File

SOURCE=.\SearchProfilesDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SourceDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\SourceView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StringListEx.cpp
# End Source File
# Begin Source File

SOURCE=.\StringsDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ToolbarEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ValueListDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualFx.cpp
# End Source File
# Begin Source File

SOURCE=.\XSLTransform.cpp
# End Source File
# Begin Source File

SOURCE=.\xString.cpp

!IF  "$(CFG)" == "bibedt - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "bibedt - Win32 Release Unicode"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "bibedt - Win32 Debug Unicode"

# ADD BASE CPP /Yu
# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\YazAbstractXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\YazCCLQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\YazConn.cpp
# End Source File
# Begin Source File

SOURCE=.\YazCQLQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\YazMARCParser.cpp
# End Source File
# Begin Source File

SOURCE=.\YazOPACParser.cpp
# End Source File
# Begin Source File

SOURCE=.\YazOpacXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\YazParser.cpp
# End Source File
# Begin Source File

SOURCE=.\YazPrefixQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\YazQuery.cpp
# End Source File
# Begin Source File

SOURCE=.\YazRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\YazResultSet.cpp
# End Source File
# Begin Source File

SOURCE=.\YazUsMarcXMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\YazXMLParser.cpp
# End Source File
# End Group
# Begin Group "Header-Dateien"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ApplyFilterDialog.h
# End Source File
# Begin Source File

SOURCE=.\AuxParser.h
# End Source File
# Begin Source File

SOURCE=.\BeIconv.h
# End Source File
# Begin Source File

SOURCE=.\BibDef.h
# End Source File
# Begin Source File

SOURCE=.\bibedt.h
# End Source File
# Begin Source File

SOURCE=.\bibedtDoc.h
# End Source File
# Begin Source File

SOURCE=.\BibEdtList.h
# End Source File
# Begin Source File

SOURCE=.\bibedtView.h
# End Source File
# Begin Source File

SOURCE=.\BibFile.h
# End Source File
# Begin Source File

SOURCE=.\BibItem.h
# End Source File
# Begin Source File

SOURCE=.\BibitemView.h
# End Source File
# Begin Source File

SOURCE=.\BibList.h
# End Source File
# Begin Source File

SOURCE=.\BibReader.h
# End Source File
# Begin Source File

SOURCE=.\BibWriter.h
# End Source File
# Begin Source File

SOURCE=.\BPCtrlAnchorMap.h
# End Source File
# Begin Source File

SOURCE=.\Coding.h
# End Source File
# Begin Source File

SOURCE=.\CodingHTML.h
# End Source File
# Begin Source File

SOURCE=.\CodingRTF.h
# End Source File
# Begin Source File

SOURCE=.\CodingTeX.h
# End Source File
# Begin Source File

SOURCE=.\CodingXML.h
# End Source File
# Begin Source File

SOURCE=.\colortable.h
# End Source File
# Begin Source File

SOURCE=.\ColumnsDialog.h
# End Source File
# Begin Source File

SOURCE=.\CopyCitationDialog.h
# End Source File
# Begin Source File

SOURCE=.\CustomizeDialog.h
# End Source File
# Begin Source File

SOURCE=.\DocMgrEx.h
# End Source File
# Begin Source File

SOURCE=.\EditCell.h
# End Source File
# Begin Source File

SOURCE=.\Export.h
# End Source File
# Begin Source File

SOURCE=.\ExportBib.h
# End Source File
# Begin Source File

SOURCE=.\ExportCopyHtml.h
# End Source File
# Begin Source File

SOURCE=.\ExportDialog.h
# End Source File
# Begin Source File

SOURCE=.\ExporterList.h
# End Source File
# Begin Source File

SOURCE=.\ExportGeneric.h
# End Source File
# Begin Source File

SOURCE=.\ExportInternal.h
# End Source File
# Begin Source File

SOURCE=.\ExportKeygen.h
# End Source File
# Begin Source File

SOURCE=.\ExportPreview.h
# End Source File
# Begin Source File

SOURCE=.\ExportRTF.h
# End Source File
# Begin Source File

SOURCE=.\ExportText.h
# End Source File
# Begin Source File

SOURCE=.\ExportXML.h
# End Source File
# Begin Source File

SOURCE=.\Field.h
# End Source File
# Begin Source File

SOURCE=.\FieldList.h
# End Source File
# Begin Source File

SOURCE=.\FileDialogEx.h
# End Source File
# Begin Source File

SOURCE=.\FileWatch.h
# End Source File
# Begin Source File

SOURCE=.\FilterDialog.h
# End Source File
# Begin Source File

SOURCE=.\FindDialog.h
# End Source File
# Begin Source File

SOURCE=.\FindDuplicatesDialog.h
# End Source File
# Begin Source File

SOURCE=.\FindDupOptionsDialog.h
# End Source File
# Begin Source File

SOURCE=.\GenFromAuxDialog.h
# End Source File
# Begin Source File

SOURCE=.\Globals.h
# End Source File
# Begin Source File

SOURCE=.\HTMLCODES.h
# End Source File
# Begin Source File

SOURCE=.\HTMLView.h
# End Source File
# Begin Source File

SOURCE=.\htmlviewer.h
# End Source File
# Begin Source File

SOURCE=.\InputBox.h
# End Source File
# Begin Source File

SOURCE=.\KeysDialog.h
# End Source File
# Begin Source File

SOURCE=.\Language.h
# End Source File
# Begin Source File

SOURCE=.\LinkStatic.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlEx.h
# End Source File
# Begin Source File

SOURCE=.\ListViewPrint.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyBitmapButton.h
# End Source File
# Begin Source File

SOURCE=.\OnlineSearch.h
# End Source File
# Begin Source File

SOURCE=.\Options.h
# End Source File
# Begin Source File

SOURCE=.\OptionsEditorPage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsExporterPage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsFilePage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsLanguagePage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPreviewPage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsPrintPage.h
# End Source File
# Begin Source File

SOURCE=.\OptionsSheet.h
# End Source File
# Begin Source File

SOURCE=.\PreambleDialog.h
# End Source File
# Begin Source File

SOURCE=.\Print.h
# End Source File
# Begin Source File

SOURCE=.\PrintPages.h
# End Source File
# Begin Source File

SOURCE=.\ProgressDialog.h
# End Source File
# Begin Source File

SOURCE=.\RegExp.h
# End Source File
# Begin Source File

SOURCE=.\ReplaceDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaBibWnd.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaPrint.h
# End Source File
# Begin Source File

SOURCE=.\ScintillaWnd.h
# End Source File
# Begin Source File

SOURCE=.\SearchDialog.h
# End Source File
# Begin Source File

SOURCE=.\SearchProfile.h
# End Source File
# Begin Source File

SOURCE=.\SearchProfilesDialog.h
# End Source File
# Begin Source File

SOURCE=.\SourceDialog.h
# End Source File
# Begin Source File

SOURCE=.\SourceView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StringListEx.h
# End Source File
# Begin Source File

SOURCE=.\StringsDialog.h
# End Source File
# Begin Source File

SOURCE=.\ToolbarEx.h
# End Source File
# Begin Source File

SOURCE=.\ValueListDialog.h
# End Source File
# Begin Source File

SOURCE=.\VisualFx.h
# End Source File
# Begin Source File

SOURCE=.\XSLTransform.h
# End Source File
# Begin Source File

SOURCE=.\xString.h
# End Source File
# Begin Source File

SOURCE=.\Yaz.h
# End Source File
# Begin Source File

SOURCE=.\YazAbstractXMLParser.h
# End Source File
# Begin Source File

SOURCE=.\YazCCLQuery.h
# End Source File
# Begin Source File

SOURCE=.\YazConn.h
# End Source File
# Begin Source File

SOURCE=.\YazCQLQuery.h
# End Source File
# Begin Source File

SOURCE=.\YazMARCParser.h
# End Source File
# Begin Source File

SOURCE=.\YazOPACParser.h
# End Source File
# Begin Source File

SOURCE=.\YazOpacXMLParser.h
# End Source File
# Begin Source File

SOURCE=.\YazParser.h
# End Source File
# Begin Source File

SOURCE=.\YazPrefixQuery.h
# End Source File
# Begin Source File

SOURCE=.\YazQuery.h
# End Source File
# Begin Source File

SOURCE=.\YazRecord.h
# End Source File
# Begin Source File

SOURCE=.\YazResultSet.h
# End Source File
# Begin Source File

SOURCE=.\YazUsMarcXMLParser.h
# End Source File
# Begin Source File

SOURCE=.\YazXMLParser.h
# End Source File
# End Group
# Begin Group "Ressourcendateien"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bibedt.exe.manifest
# End Source File
# Begin Source File

SOURCE=.\res\bibedt.ico
# End Source File
# Begin Source File

SOURCE=.\res\bibedt.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_i.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_r.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Book01a.ico
# End Source File
# Begin Source File

SOURCE=.\res\bookmark.bmp
# End Source File
# Begin Source File

SOURCE=.\res\config.bib
# End Source File
# Begin Source File

SOURCE=.\res\donate.bmp
# End Source File
# Begin Source File

SOURCE=.\res\enc_html.txt
# End Source File
# Begin Source File

SOURCE=.\res\enc_rtf.txt
# End Source File
# Begin Source File

SOURCE=.\res\enc_tex.txt
# End Source File
# Begin Source File

SOURCE=.\res\enc_xml.txt
# End Source File
# Begin Source File

SOURCE=.\res\header_sort.bmp
# End Source File
# Begin Source File

SOURCE=.\res\linkhand.cur
# End Source File
# Begin Source File

SOURCE=.\res\listview.bmp
# End Source File
# Begin Source File

SOURCE=.\res\osearch.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_rec.bmp
# End Source File
# End Group
# Begin Group "XSL Styles"

# PROP Default_Filter ".xsl"
# Begin Source File

SOURCE=.\becmn.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\bibtexml.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\copyhtml.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\copyrtf.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\dc.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\keygen.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\marc21.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\plain.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\preview.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\xml2rdf.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\xml2rtf.xsl
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\xml2txt.xsl
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=.\building.txt
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\changelog.txt
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# PROP Exclude_From_Build 1
# End Source File
# End Target
# End Project
