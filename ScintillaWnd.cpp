/* @doc
 * @module ScintillaWnd.cpp | Implementation of a Scintilla syntax coloring edit control for MFC
 * This program is an example how to use the excellent scintilla edit control of Neil Hodgson.<nl>
 * See www.scintilla.org for details<nl>
 * Author: Horst Brückner, hb@ec-logic.com<nl>
 * Environment: VisualC++ Version 6, static Build of Scintilla, SciLexer.dll as Lexer<nl>
 */

// Extended by Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>

/*
 * $Id: ScintillaWnd.cpp,v 1.29 2005/08/25 16:20:03 stievie Exp $
 */

#include "stdafx.h"
#include "ScintillaWnd.h"
#include "scintilla.h"
#include "SciLexer.h"
#include "Accessor.h"
#include "Propset.h"
#include "keywords.h"
#include <fstream.h>
#include <io.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// the next 2 arrays are used to determine lexer format from file extensions
static TCHAR *szExtensions[] = 
{
	"py",                                                                // SCLEX_PYTHON
	"c|cc|cpp|cxx|cs|h|hh|hpp|hxx|sma|dlg|rc|rc2|idl|odl|mak|js|java",   // SCLEX_CPP
	"htm|html|shtml|htt|cfm|tpl|hta",         // SCLEX_HTML
	"xml|gcl|xsl|svg|xul|xsd|dtd|xslt|axl",   // SCLEX_XML
	"pl|pm|cgi|pod",                          // SCLEX_PERL
	"sql|spec|body|sps|spb|sf|sp",            // SCLEX_SQL
	"vb|bas|frm|cls|ctl|pag|dsr|dob",         // SCLEX_VB
	"properties",                             // SCLEX_PROPERTIES
	"err",                                    // SCLEX_ERRORLIST
	"iface|mak",                              // SCLEX_MAKEFILE
	"bat|cmd|nt",                             // SCLEX_BATCH
	"xcode",                                  // SCLEX_XCODE
	"tex|sty",                                // SCLEX_LATEX
	"lua",                                    // SCLEX_LUA
	"diff",                                   // SCLEX_DIFF
	"conf",                                   // SCLEX_CONF
	"pas|inc|pp",                             // SCLEX_PASCAL
	"ave",                                    // SCLEX_AVE
	"ada|ads|adb",                            // SCLEX_ADA
	"lsp|lisp|scm|smd|ss",                    // SCLEX_LISP
	"rb",                                     // SCLEX_RUBY
	"e",                                      // SCLEX_EIFFEL
	"e",                                      // SCLEX_EIFFELKW
	"tcl",                                    // SCLEX_TCL
	"tab|spf",                                // SCLEX_NNCRONTAB
	"ant",                                    // SCLEX_BULLANT
	"vbs|dsm",                                // SCLEX_VBSCRIPT
	"asp|aspx",                               // SCLEX_ASP
	"php|php3|php4",                          // SCLEX_PHP
	"bc|cln",                                 // SCLEX_BAAN
	"m",                                      // SCLEX_MATLAB
	"sol",                                    // SCLEX_SCRIPTOL
	"asm",                                    // SCLEX_ASM
	"cpp",                                    // SCLEX_CPPNOCASE
	"f|for|f90|f95",                          // SCLEX_FORTRAN
	"f77",                                    // SCLEX_F77
	"css",                                    // SCLEX_CSS
	"pov",                                    // SCLEX_POV
	"lt|lot",                                 // SCLEX_LOUT
	"src|em",                                 // SCLEX_ESCRIPT
	0,
};

static int nFormats[] = {
	SCLEX_PYTHON,
	SCLEX_CPP,
	SCLEX_HTML,
	SCLEX_XML,
	SCLEX_PERL,
	SCLEX_SQL,
	SCLEX_VB,
	SCLEX_PROPERTIES,
	SCLEX_ERRORLIST,
	SCLEX_MAKEFILE,
	SCLEX_BATCH,
	SCLEX_XCODE,
	SCLEX_LATEX,
	SCLEX_LUA,
	SCLEX_DIFF,
	SCLEX_CONF,
	SCLEX_PASCAL,
	SCLEX_AVE,
	SCLEX_ADA,
	SCLEX_LISP,
	SCLEX_RUBY,
	SCLEX_EIFFEL,
	SCLEX_EIFFELKW,
	SCLEX_TCL,
	SCLEX_NNCRONTAB,
	SCLEX_BULLANT,
	SCLEX_VBSCRIPT,
	SCLEX_ASP,
	SCLEX_PHP,
	SCLEX_BAAN,
	SCLEX_MATLAB,
	SCLEX_SCRIPTOL,
	SCLEX_ASM,
	SCLEX_CPPNOCASE,
	SCLEX_FORTRAN,
	SCLEX_F77,
	SCLEX_CSS,
	SCLEX_POV,
	SCLEX_LOUT,
	SCLEX_ESCRIPT,
	0,
};

/**
 * \brief This is an empty constructor.
 */
CScintillaWnd::CScintillaWnd()
{
	m_bLinenumbers = FALSE;
	m_bSelection = TRUE;
	m_bFolding = FALSE;
	m_nSearchflags = 0;
	m_RightEdgePos = -1;
}

/**
 * \brief This is a destructor.
 */
CScintillaWnd::~CScintillaWnd()
{

}

/**
 * \brief Create the window.
 *
 * Basically calls CWnd::CreateEx with the supplied parameters.
 *
 * \param lpszWindowName The name of the window.
 * \param dwStyle The style of the window.
 * \param rect The window position and size.
 * \param pParentWnd The parent window.
 * \param nID The ID.
 *
 * \return TRUE on success else FALSE on error.
 */
BOOL CScintillaWnd::Create (LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (!CWnd::CreateEx(WS_EX_CLIENTEDGE, STR_SCINTILLAWND, lpszWindowName, dwStyle, rect, pParentWnd, (UINT)nID))
   {   
      LPVOID lpMsgBuf;
      ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
               NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL);
      // Write to stderr
      TRACE (_T("%s\n"), (LPCTSTR)lpMsgBuf);
      // Free the buffer.
      LocalFree( lpMsgBuf );
      return FALSE;
   }
   return TRUE;
}

/**
 * \brief Load Scintilla DLL.
 *
 * Try to load the Scintilla dll - usually named "SciLexer.dll" or "Scintilla.dll".
 * We try to locate the dll in  the current dirtectory and along the path environment.
 * Call this function in your CWinApp derived application in the InitInstance function 
 * by calling:
 * \code CScintillaWnd::LoadScintillaDll()\endcode
 *
 * \param szDllFile The file of the DLL, if NULL it uses the default name "SciLexer.dll".
 *
 * \return NULL on error or the module handle of the loaded DLL on success.
 */
HMODULE CScintillaWnd::LoadScintillaDll (
                                         LPCSTR szDllFile)
{
   CString strLexer = STR_LEXERDLL;
   if (szDllFile != NULL)
      strLexer = szDllFile;
// this call to LoadLibrary searches in:
// 1.) current directory
// 2.) wint
// 3.) winnt/system32
// 4.) path
	HMODULE hModule = ::LoadLibrary(strLexer);
// if load fails get an extended error message 
	if (hModule == NULL)
	{
      LPVOID lpMsgBuf;
      ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
               NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf,0,NULL);
      // Write to stderr
      TRACE (_T("%s: %s\n"), (LPCSTR)strLexer, (LPCTSTR)lpMsgBuf);
      // Free the buffer.
      LocalFree( lpMsgBuf );
      return NULL;
	}
   return hModule;
}

/**
 * \brief Set the text of the editor.
 *
 * Clear the current Text and add new Text.
 *
 * \param szText Pointer to the new text.
 */
void CScintillaWnd::SetText (
                             LPCSTR szText)
{
   BOOL read = GetReadOnly();
	// Can't set text in read only mode
	SetReadOnly(FALSE);
   if (szText != NULL) {
	   SendMessage(SCI_SETTEXT, 0, (LPARAM)szText);
   } else {
	   SendMessage(SCI_CLEARALL, 0, 0);
   }
   SetReadOnly(read);
   GotoPosition(0);
}

/**
 * \brief Return the text.
 *
 * Get the text from the control.
 * 
 * \param strText Points to a CString object to receive the text.
 */
void CScintillaWnd::GetText (
                             CString &strText)
{
   LPSTR szText = GetText();
   if (szText != NULL)
   {
      strText = szText;
      delete [] szText;
   }
}

/**
 * \brief Return the text.
 *
 * Get the text from the control.
 * 
 * \return A character string with text from the control or NULL on error. 
 * The caller has to free the memory with: \code delete [] szText;\endcode
 */
LPSTR CScintillaWnd::GetText ()
{
   long lLen = SendMessage(SCI_GETLENGTH, 0, 0) + 1;
   if (lLen > 0)
   {
      TCHAR *pReturn = new TCHAR[lLen];
      if (pReturn != NULL)
      {
         *pReturn = '\0';
         SendMessage(SCI_GETTEXT, lLen, (long)pReturn);
         return pReturn;
      }
   }
   return NULL;
}

/**
 * \brief Load a file.
 * 
 * Try to load the file.
 *
 * \param szPath The filename to load.
 *
 * \return FALSE on error or TRUE on success.
 */
BOOL CScintillaWnd::LoadFile (
                              LPCSTR szPath)
{
// if pathname is empty do nothing
   if (szPath == NULL || *szPath == '\0')
      return TRUE;

   BOOL bReturn = TRUE;
// ty to open file in sharing mode
   ::ifstream file;
   long len = 0L;
   long nTotal;
   TCHAR *szBuffer = NULL;
   file.open(szPath, ios::in, filebuf::sh_read);
// ok success - try to get length of file
   if (file.is_open())
   {
      len = _filelength(file.fd());
      if (len > 0)
      {
//       alloc new buffer of sie = filesize+1 for termination NULL
         szBuffer = new TCHAR[len+1];
         if (szBuffer != NULL)
         {
            file.read(szBuffer, len);
            nTotal = file.gcount();
            if (nTotal > 0 && nTotal <= len)
               szBuffer[nTotal] = '\0';
//          read error
            if (file.bad())
            {
               file.close();
               bReturn = FALSE;
            }
         }
         else
         {
            file.close();
            bReturn = FALSE;
         }
      }
      file.close();
//    set text to control
      SetText (szBuffer);
//    tell scintilla that we have an unmodified document
      SendMessage(SCI_SETSAVEPOINT, 0, 0);
      GotoPosition(0);

   }
// file open error - return
   else
      bReturn = FALSE;
// clean up
   if (szBuffer != NULL)
      delete [] szBuffer;
   return bReturn;
}

/**
 * \brief Save the file
 *
 * \param szPath The filename.
 *
 * \return TRUE on success otherwise FALSE.
 */
BOOL CScintillaWnd::SaveFile (
                              LPCSTR szPath) //@parm filename to save to
{
   ::ofstream file;
   file.open(szPath);
   if (file.fail())
   {
     return FALSE;
   }
	int buflen = SendMessage(SCI_GETLENGTH)+1; //last NULL
	TCHAR *pBuffer = new TCHAR[buflen];
   if (pBuffer != NULL)
   {
	   SendMessage(SCI_GETTEXT, buflen,(long)pBuffer);
      file.write(pBuffer, buflen-1);
      delete [] pBuffer;
   }
   file << ends;
   file.close();
   return TRUE;
}

/**
 * \brief Calculate number of characters needed for linenumbers.
 *
 * Try to calculate the number of characters needed for the display 
 * of the linenumbers. This function returns 3 for 10-99 lines in file, 
 * 4 for 100-999 lines and so on.
 *
 * \return Number of characters needed to display linenumbers.
 */
int CScintillaWnd::GetLinenumberChars ()
{
// try to get number of lines in control
   LRESULT lLines = SendMessage(SCI_GETLINECOUNT, 0, 0);

   int nChars = 1;
   while (lLines > 0)
   {
      lLines = lLines / 10;
      nChars++;
   }
   return nChars; // allow an extra char for safety
}

/**
 * \brief Calculate a reasonable width for Linenumberdisplay.
 *
 * \return Number of pixels for the margin width of margin (0).
 */
int CScintillaWnd::GetLinenumberWidth ()
{
	// get number of chars needed to display highest linenumber
	int nChars = GetLinenumberChars();
	// get width of character '9' in pixels
	LRESULT lWidth = SendMessage(SCI_TEXTWIDTH, STYLE_LINENUMBER, (long)_T("9"));
	return nChars * lWidth;
}

/**
 * \brief Set the display of line numbers on or off.
 *
 * Scintilla uses 3 "Margin" at the left of the edit window. The Margin (0)
 * is used to display the linenumbers. If set to 0 no numbers are displayed. If
 * set to a width > 0 - linenumbers are displayed. We use a helper function to 
 * calculate the size of this margin.
 *
 * \param bFlag TRUE to show linenumber, FALSE to turn it off.
 */
void CScintillaWnd::SetDisplayLinenumbers(
                                          BOOL bFlag)
{
// if nothing changes just return
   if (GetDisplayLinenumbers() == bFlag)
      return;
// if display is turned off we set margin 0 to 0
   if (!bFlag)
   {
	   SendMessage(SCI_SETMARGINWIDTHN, 0, 0);
   }
// if display is turned o we set margin 0 to the calculated width
   else
   {
      int nWidth = GetLinenumberWidth();
	   SendMessage(SCI_SETMARGINWIDTHN, 0, nWidth);
   }
   m_bLinenumbers = bFlag;
}

/**
 * \brief Cut the selected text to the clipboard.
 */
void CScintillaWnd::Cut()
{
	SendMessage(SCI_CUT, 0, 0);
}

/**
 * \brief Copy the selected text to the clipboard.
 */
void CScintillaWnd::Copy()
{
	SendMessage(SCI_COPY, 0, 0);
}

/**
 * \brief Paste the text from the clipboard to the control.
 */
void CScintillaWnd::Paste()
{
	SendMessage(SCI_PASTE, 0, 0);
}

/**
 * \brief Delete the selected text.
 */
void CScintillaWnd::Clear()
{
	SendMessage(SCI_CLEAR, 0, 0);
}

/**
 * \brief Select the complete text.
 */
void CScintillaWnd::SelectAll()
{
	SendMessage(SCI_SELECTALL, 0, 0);
}

/**
 * \brief Undo the last action.
 */
void CScintillaWnd::Undo()
{
	SendMessage(SCI_UNDO, 0, 0);
}
/////////////////////////////////////
// @mfunc Redo the last undone action
// @rvalue void | not used
//
void CScintillaWnd::Redo()
{
	SendMessage(SCI_REDO, 0, 0);
}

/** 
 * \brief Returns a flag if we can undo the last action.
 *
 * \return TRUE if we can undo - else FALSE.
 */
BOOL CScintillaWnd::GetCanUndo()
{
	return SendMessage(SCI_CANUNDO, 0, 0) != 0;
}

/**
 * \brief Returns a flag if we can redo the last undone action.
 *
 * \return TRUE if we can redo - else FALSE.
 */
BOOL CScintillaWnd::GetCanRedo()
{
	return SendMessage(SCI_CANREDO, 0, 0) != 0;
}

/**
 * \brief Returns a flag if there is text in the clipboard which we can paste.
 *
 * \return TRUE if the clipboard contains text to paste - else FALSE.
 */
BOOL CScintillaWnd::GetCanPaste()
{
	return SendMessage(SCI_CANPASTE, 0, 0) != 0;
}

/**
 * \brief Get the current line number - this the with the caret in it.
 *
 * \return Line number with the caret in it - starts with 1.
 */
long CScintillaWnd::GetCurrentLine()
{
	long lPos = SendMessage(SCI_GETCURRENTPOS, 0, 0);
	return SendMessage(SCI_LINEFROMPOSITION, lPos, 0) + 1;
}

/**
 * \brief Get the current column number = position of the caret within the line.
 *
 * This return value my be affected by the TAB setting! Starts with 1.
 *
 * \return Current column number.
 */
long CScintillaWnd::GetCurrentColumn()
{
	long lPos = SendMessage(SCI_GETCURRENTPOS, 0, 0);
	return SendMessage(SCI_GETCOLUMN, lPos, 0) + 1;
}
/////////////////////////////////////
// @mfunc Return the current character position within the file.
// @rvalue long | current character position
//
long CScintillaWnd::GetCurrentPosition()
{
	return SendMessage(SCI_GETCURRENTPOS, 0, 0);
}
/////////////////////////////////////
// @mfunc Return the current style at the caret
// @rvalue int | the current style index (0...127)
//
int CScintillaWnd::GetCurrentStyle()
{
	long lPos = SendMessage(SCI_GETCURRENTPOS, 0, 0);
	return SendMessage(SCI_GETSTYLEAT, lPos, 0);
}
/////////////////////////////////////
// @mfunc Return the current folding level at the caret line
// @rvalue int | the current folding level (0...n)
//
int CScintillaWnd::GetCurrentFoldinglevel()
{
	long lLine = GetCurrentLine();
	int level = (SendMessage(SCI_GETFOLDLEVEL, lLine, 0)) & SC_FOLDLEVELNUMBERMASK;
	return level - 1024;
}
/////////////////////////////////////
// @mfunc set the fontname e.g. "Arial"
// @rvalue void | not used
//
void CScintillaWnd::SetFontname(int nStyle, LPCSTR szFontname)
{
	SendMessage(SCI_STYLESETFONT, nStyle, (long)szFontname);
}
/////////////////////////////////////
// @mfunc Set the font height in points
// @rvalue void | not used
//
void CScintillaWnd::SetFontheight(int nStyle, int nHeight)
{
	SendMessage(SCI_STYLESETSIZE, nStyle, (long)nHeight);
}

/**
 * \brief Set foreground color for one style.
 *
 * \param nStyle The style to set the color.
 * \param crForeground The color.
 */
void CScintillaWnd::SetForeground(int nStyle, COLORREF crForeground)
{
	SendMessage(SCI_STYLESETFORE, nStyle, (long)crForeground);
}

/**
 * \brief Set foreground color for all styles.
 *
 * \param crForeground The color.
 */
void CScintillaWnd::SetForeground(COLORREF crForeground)
{
	for (int style = 0; style <= STYLE_MAX; style++) {
		if (style != STYLE_LINENUMBER) {
			SetForeground(style, crForeground);
		}
	}
}

/**
 * \brief Set background color for one style.
 *
 * \param nStyle The style to set the color.
 * \param crBackground The color.
 */
void CScintillaWnd::SetBackground(int nStyle, COLORREF crBackground)
{
	SendMessage(SCI_STYLESETBACK, nStyle, (long)crBackground);
}

/**
 * \brief Set background color for all styles.
 *
 * \param crBackground The color.
 */
void CScintillaWnd::SetBackground(COLORREF crBackground)
{
	for (int style = 0; style <= STYLE_MAX; style++) {
		if (style != STYLE_LINENUMBER) {
			SetBackground(style, crBackground);
		}
	}
}

/////////////////////////////////////
// @mfunc set given style to bold
// @rvalue void | not used
//
void CScintillaWnd::SetBold(int nStyle, BOOL bBold)
{
	SendMessage(SCI_STYLESETBOLD, nStyle, (long)bBold);
}
/////////////////////////////////////
// @mfunc set given style to bold
// @rvalue void | not used
//
void CScintillaWnd::SetItalic(int nStyle, BOOL bItalic)
{
   SendMessage(SCI_STYLESETITALIC, nStyle, (long)bItalic);
}
/////////////////////////////////////
// @mfunc set given style to bold
// @rvalue void | not used
//
void CScintillaWnd::SetUnderline(int nStyle, BOOL bUnderline)
{
   SendMessage(SCI_STYLESETUNDERLINE, nStyle, (long)bUnderline);
}

/**
 * \brief Return flag if we are in overstrike mode.
 *
 * \return TRUE for overstrike otherwise FALSE.
 */
BOOL CScintillaWnd::GetOverstrike()
{
   return SendMessage(SCI_GETOVERTYPE , 0, 0);
}

/**
 * \brief Set set overstrike mode.
 *
 * \param bOverstrike TRUE for overstrike mode or FALSE for insert mode.
 */
void CScintillaWnd::SetOverstrike(BOOL bOverstrike)
{
   SendMessage(SCI_SETOVERTYPE, bOverstrike, 0);
}

/**
 * \brief Toggle the display of the selection bookmark margin.
 *
 * \param bFlag TRUE to show selection margin, FALSE to hide it.
 */
void CScintillaWnd::SetDisplaySelection(BOOL bFlag)
{
   m_bSelection = bFlag;
   if (bFlag)
	   SendMessage(SCI_SETMARGINWIDTHN, 1, 16);
   else
	   SendMessage(SCI_SETMARGINWIDTHN, 1, 0);
}

/**
 * \brief Toggle the display of the folding margin.
 *
 * \param bFlag TRUE to show folding margin, FALSE to hide it.
 */
void CScintillaWnd::SetDisplayFolding(BOOL bFlag)
{
   m_bFolding = bFlag;
   if (bFlag)
	   SendMessage(SCI_SETMARGINWIDTHN, 2, 16);
   else
	   SendMessage(SCI_SETMARGINWIDTHN, 2, 0);
}

/**
 * \brief Set some reasonable defaults.
 */
void CScintillaWnd::Init()
{
	// Default font is courier new 10 pt
	SetFont("Courier New", 10, FALSE, FALSE, FALSE);
	// Use default window background color instead of white
	DWORD col = GetSysColor(COLOR_WINDOW);
	SetBackground(col);

	// clear all text styles
	SendMessage(SCI_CLEARDOCUMENTSTYLE, 0, 0);
	// set the number of styling bits to 7 - the asp/html views need a lot of styling - default is 5
	// If you leave the default you will see twiggle lines instead of ASP code
	SendMessage(SCI_SETSTYLEBITS, 7, 0);
	// set the display for indetation guides to on - this displays virtical dotted lines from the beginning of 
	// a code block to the end of the block
	SendMessage(SCI_SETINDENTATIONGUIDES, TRUE, 0);
	// set tabwidth to 2
	SendMessage(SCI_SETTABWIDTH, 2, 0);
	// set indention to 2
	SendMessage(SCI_SETINDENT, 2, 0);
	// set the caret blinking time to systems default
	SendMessage(SCI_SETCARETPERIOD, GetCaretBlinkTime(), 0);
	// Caret width is two pixels
	SendMessage(SCI_SETCARETWIDTH, 2, 0);
	// source folding section
	// tell the lexer that we want folding information - the lexer supplies "folding levels"
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold.html"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold.html.preprocessor"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold.comment"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold.at.else"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold.flags"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("fold.preprocessor"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("styling.within.preprocessor"), (LPARAM)_T("1"));
	SendMessage(SCI_SETPROPERTY, (WPARAM)_T("asp.default.language"), (LPARAM)_T("1"));
	// Tell scintilla to draw folding lines UNDER the folded line
	SendMessage(SCI_SETFOLDFLAGS, 16, 0);
	// Set margin 2 = folding margin to display folding symbols
	SendMessage(SCI_SETMARGINMASKN, 2, SC_MASK_FOLDERS);
	// allow notifications for folding actions
	SendMessage(SCI_SETMODEVENTMASK, SC_MOD_INSERTTEXT | SC_MOD_DELETETEXT, 0);
	// make the folding margin sensitive to folding events = if you click into the margin you get a notification event
	SendMessage(SCI_SETMARGINSENSITIVEN, 2, TRUE);
	// define a set of markers to displa folding symbols
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	// set the backgroundcolor of brace highlights
	SendMessage(SCI_STYLESETBACK, STYLE_BRACELIGHT, BRACE_HIGHLIGHT);
	// Selection colors, use system default
	SendMessage(SCI_SETSELFORE, TRUE, GetSysColor(COLOR_HIGHLIGHTTEXT));
	SendMessage(SCI_SETSELBACK, TRUE, GetSysColor(COLOR_HIGHLIGHT));

	// set end of line mode to CRLF
	SendMessage(SCI_CONVERTEOLS, 2, 0);
	SendMessage(SCI_SETEOLMODE, 2, 0);
	// Allow to scoll bellow last line
	SendMessage(SCI_SETENDATLASTLINE, FALSE, 0);
	// Don't use tabs
	SendMessage(SCI_SETUSETABS, FALSE, 0);
	// Use Tab ident
	SendMessage(SCI_SETTABINDENTS, TRUE, 0);
	SendMessage(SCI_SETBACKSPACEUNINDENTS, TRUE, 0);
	// set markersymbol for marker type 0 - bookmark
	SendMessage(SCI_MARKERDEFINE, 0, SC_MARK_CIRCLE);
	// Printing
	SendMessage(SCI_SETPRINTCOLOURMODE, SC_PRINT_COLOURONWHITE, 0);
	SendMessage(SCI_SETPRINTWRAPMODE, SC_WRAP_WORD, 0);
}

/** 
 * \brief Update UI and do brace matching.
 */
void CScintillaWnd::UpdateUI()
{
	// do brace matching
	long lStart = SendMessage(SCI_GETCURRENTPOS, 0, 0);
	long lEnd = SendMessage(SCI_BRACEMATCH, lStart - 1, 0);
	if (lEnd >= 0)
		// if there is a matching brace highlight it
		SendMessage(SCI_BRACEHIGHLIGHT, lStart-1, lEnd);
	else
		// if there is NO matching brace erase old highlight
		SendMessage(SCI_BRACEHIGHLIGHT, -1, -1);

	// update linenumber margin	width
	if (m_bLinenumbers) {
		int nWidth = GetLinenumberWidth();
		int curwidth = SendMessage(SCI_GETMARGINWIDTHN, 0, 0);
		if (curwidth != nWidth)
			SendMessage(SCI_SETMARGINWIDTHN, 0, nWidth);
	}
}

/**
 * \brief Do default folding for given margin and position - 
 * usually called from notification handler.
 *
 * \param nMargin Maring we want to handle - normally (2).
 * \param lPosition Character position where user clicked margin.
 */
void CScintillaWnd::DoDefaultFolding(
                                     int nMargin,
                                     long lPosition)
{
// simply toggle fold
   if (nMargin == 2)
   {
      long lLine = SendMessage(SCI_LINEFROMPOSITION, lPosition, 0);
      SendMessage(SCI_TOGGLEFOLD, lLine, 0);
   }
}
/////////////////////////////////////
// @mfunc Do default folding for given margin and position - usually called from notification handler
// @rvalue void | not used
//
void CScintillaWnd::Refresh()
{
   SendMessage(SCI_COLOURISE, 0, -1);
}
/////////////////////////////////////
// @mfunc Add a bookmark at given line
// @rvalue void | not used
//
void CScintillaWnd::AddBookmark(
                                long lLine) //@parm line where to add bookmark - lines start at 1
{
   SendMessage(SCI_MARKERADD, lLine-1, 0);
}

void CScintillaWnd::ToogleBookmark(long lLine)
{
	if (HasBookmark(lLine))
		DeleteBookmark(lLine);
	else
		AddBookmark(lLine);
}

/////////////////////////////////////
// @mfunc Delete a bookmark at given line
// @rvalue void | not used
//
void CScintillaWnd::DeleteBookmark(
                                   long lLine) //@parm line where to delete bookmark - lines start at 1
{
   if (HasBookmark(lLine))
   {
      SendMessage(SCI_MARKERDELETE, lLine-1, 0);
   }
}

void CScintillaWnd::ClearBookmarks()
{
	SendMessage(SCI_MARKERDELETEALL, -1, 0);
}

/////////////////////////////////////
// @mfunc Check if given line has a bookmark
// @rvalue BOOL | TRUE if given line has a bookmark - else FALSE
//
BOOL CScintillaWnd::HasBookmark(
                                long lLine) //@parm line where to add bookmark - lines start at 1
{
   int n = SendMessage(SCI_MARKERGET, lLine-1, 0);
// check mask for markerbit 0
   if (n & 0x1)
      return TRUE;
   return FALSE;
}
/////////////////////////////////////
// @mfunc Find next bookmark from current line
// @rvalue void | not used
//
BOOL CScintillaWnd::FindNextBookmark()
{
	long lLine = SendMessage(SCI_MARKERNEXT, GetCurrentLine(), 1);
	if (lLine >= 0) {
		SendMessage(SCI_GOTOLINE, lLine, 0);
		return TRUE;
	} else
		return FALSE;
}
/////////////////////////////////////
// @mfunc Find previous bookmark from current line
// @rvalue void | not used
//
BOOL CScintillaWnd::FindPreviousBookmark()
{
	long lLine = SendMessage(SCI_MARKERPREVIOUS, GetCurrentLine() - 2, 1);
	if (lLine >= 0) {
		SendMessage(SCI_GOTOLINE, lLine, 0);
		return TRUE;
	} else
		return FALSE;
}
/////////////////////////////////////
// @mfunc Goto givven character position
// @rvalue void | not used
//
void CScintillaWnd::GotoPosition(
                                 long lPos) //@parm new character position
{
	SendMessage(SCI_GOTOPOS, lPos, 0);
}
/////////////////////////////////////
// @mfunc Goto given line position
// @rvalue void | not used
//
void CScintillaWnd::GotoLine(
                             long lLine) //@parm new line - lines start at 1
{
	SendMessage(SCI_GOTOLINE, lLine-1, 0);
}

/**
 * \brief  Search forward for a given string and select it if found. 
 * You may use regular expressions on the text.
 *
 * \param szText Text to search.
 *
 * \return TRUE if text is found else FALSE.
 */
BOOL CScintillaWnd::SearchForward(
                                  LPCSTR szText)
{
   if (szText == NULL)
      return FALSE;
   long lPos = GetCurrentPosition();
   TextToFind tf;
   char* txt = new char[strlen(szText)+1];
   strcpy(txt, szText);
   tf.lpstrText = txt;
   tf.chrg.cpMin = lPos+1;
   tf.chrg.cpMax = SendMessage(SCI_GETLENGTH, 0, 0);
   lPos = SendMessage(SCI_FINDTEXT, m_nSearchflags, (long)&tf);
   delete [] txt;
   if (lPos >= 0)
   {
      SetFocus();
      GotoPosition(lPos);
      SendMessage(SCI_SETSEL, tf.chrgText.cpMin, tf.chrgText.cpMax);
      SendMessage(SCI_FINDTEXT, m_nSearchflags, (long)&tf);
      return TRUE;
   }
   return FALSE;
}

/**
 * \brief Search backward for a given string and select it if found.
 *
 *  You may use regular expressions on the text.
 *
 * \param szText The text to search.
 *
 * \return TRUE if text is ffound else FALSE.
 */
BOOL CScintillaWnd::SearchBackward(
                                  LPCSTR szText)
{
   if (szText == NULL)
      return FALSE;
   long lPos = GetCurrentPosition();
   long lMinSel = GetSelectionStart();
   char* txt = new char[strlen(szText)+1];
   strcpy(txt, szText);
   TextToFind tf;
   tf.lpstrText = txt;
   if (lMinSel >= 0)
      tf.chrg.cpMin = lMinSel-1;
   else
      tf.chrg.cpMin = lPos-1;
   tf.chrg.cpMax = 0;
   lPos = SendMessage(SCI_FINDTEXT, m_nSearchflags, (long)&tf);
   delete [] txt;
   if (lPos >= 0)
   {
      SetFocus();
      GotoPosition(lPos);
      SendMessage(SCI_SETSEL, tf.chrgText.cpMin, tf.chrgText.cpMax);
      SendMessage(SCI_FINDTEXT, m_nSearchflags, (long)&tf);
      return TRUE;
   }
   return FALSE;
}

/**
 * \brief Replace a text with a new text.
 * 
 * Replace a text with a new text. You can use regular expression with tagging on the replacement text.
 *
 * \param szText The new text.
 */
void CScintillaWnd::ReplaceSearchedText(
                                        LPCSTR szText)
{
   if (szText == NULL)
      return;
	SendMessage(SCI_TARGETFROMSELECTION, 0, 0);
   if (m_nSearchflags & SCFIND_REGEXP)
      SendMessage(SCI_REPLACETARGETRE, strlen(szText), (long)szText);
   else
      SendMessage(SCI_REPLACETARGET, strlen(szText), (long)szText);
}

/**
 * \brief Set lexer format - see scintilla.h.
 */
void CScintillaWnd::SetLexer(
                             int nLexer) //@parm lexer code e.g. 
{
   SendMessage(SCI_SETLEXER, nLexer, 0);
}

/**
 * \brief Get start of selection (anchor) as character position.
 *
 * \return Character position of selection start (anchor) - -1 on error.
 */
long CScintillaWnd::GetSelectionStart()
{
   return SendMessage(SCI_GETSELECTIONSTART, 0, 0);
}

/**
 * \brief Get end of selection as character position.
 *
 * \return Character position of selection end - -1 on error.
 */
long CScintillaWnd::GetSelectionEnd()
{
   return SendMessage(SCI_GETSELECTIONEND, 0, 0);
}

/**
 * \brief Get selected string.
 *
 * \return The currently selected text.
 */
CString CScintillaWnd::GetSelectedText()
{
   long lLen = (GetSelectionEnd() - GetSelectionStart()) + 1;
   if (lLen > 0)
   {
      TCHAR *p = new TCHAR[lLen+1];
      if (p != NULL)
      {
         *p = '\0';
         SendMessage(SCI_GETSELTEXT, 0, (long)p);
         CString strReturn = p;
         delete [] p;
         return strReturn;
      }
   }
   return _T("");
}

/**
 * \brief Replace a text.
 *
 * Replace a text in a selection or in the complete file multiple times.
 *
 * \param szFind Text to replace.
 * \param szReplace The new Text.
 * \param bUseSelection Replace only in current selection.
 *
 * \return Number of replacements.
 */
int CScintillaWnd::ReplaceAll(
                              LPCSTR szFind, 
                              LPCSTR szReplace, 
                              BOOL bUseSelection)
{
   int nCount = 0;
// different branches for replace in selection or total file
   if (bUseSelection)
   {
//    get starting selection range
      long lLen = 0;
      long lStart = GetSelectionStart();
      long lEnd = GetSelectionEnd();
//    set target to selection
      SendMessage(SCI_SETTARGETSTART, lStart);
      SendMessage(SCI_SETTARGETEND, lEnd);
//    try to find text in target for the first time
	   long lPos = SendMessage(SCI_SEARCHINTARGET, strlen(szFind), (long)szFind);
//    loop over selection until end of selection reached - moving the target start each time
      while (lPos < lEnd && lPos >= 0)
      {
         if (m_nSearchflags & SCFIND_REGEXP) // check for regular expression flag
            lLen = SendMessage(SCI_REPLACETARGETRE, strlen(szReplace), (long)szReplace);
         else
            lLen = SendMessage(SCI_REPLACETARGET, strlen(szReplace), (long)szReplace);
//       the end of the selection was changed - recalc the end
         lEnd = GetSelectionEnd();
//       move start of target behind last change and end of target to new end of selection
         SendMessage(SCI_SETTARGETSTART, lPos+lLen);
         SendMessage(SCI_SETTARGETEND, lEnd);
//       find again - if nothing found loop exits
	      lPos = SendMessage(SCI_SEARCHINTARGET, strlen(szFind), (long)szFind);
         nCount++;
      }
   }
   else
   {
//    start with first and last char in buffer
      long lLen = 0;
      long lStart = 0;
      long lEnd = SendMessage(SCI_GETTEXTLENGTH, 0, 0);
//    set target to selection
      SendMessage(SCI_SETTARGETSTART, lStart, 0);
      SendMessage(SCI_SETTARGETEND, lEnd, 0);
//    try to find text in target for the first time
	   long lPos = SendMessage(SCI_SEARCHINTARGET, strlen(szFind), (long)szFind);
//    loop over selection until end of selection reached - moving the target start each time
      while (lPos < lEnd && lPos >= 0)
      {
         if (m_nSearchflags & SCFIND_REGEXP) // check for regular expression flag
            lLen = SendMessage(SCI_REPLACETARGETRE, strlen(szReplace), (long)szReplace);
         else
            lLen = SendMessage(SCI_REPLACETARGET, strlen(szReplace), (long)szReplace);
//       the end of the selection was changed - recalc the end
         lEnd = SendMessage(SCI_GETTEXTLENGTH, 0, 0);;
//       move start of target behind last change and end of target to new end of buffer
         SendMessage(SCI_SETTARGETSTART, lPos+lLen);
         SendMessage(SCI_SETTARGETEND, lEnd);
//       find again - if nothing found loop exits
	      lPos = SendMessage(SCI_SEARCHINTARGET, strlen(szFind), (long)szFind);
         nCount++;
      }
   }
   return nCount;
}

/**
 * \brief Set Font for all styles.
 *
 * Use this to set the feault font.
 *
 * \param name The name of the font.
 * \param size The size of the font.
 * \param bold Should the font be bold.
 * \param italic Should the font be italic.
 * \param underline Should the font be underlined.
 */
void CScintillaWnd::SetFont(CString name, int size, BOOL bold, BOOL italic, BOOL underline)
{
	for (int style = 0; style <= STYLE_MAX; style++) {
		SetFontname(style, name);
		SetFontheight(style, size);
		SetItalic(style, italic);
		SetBold(style, bold);
		SetUnderline(style, underline);			
	}
}

/**
 * \brief Set wrap mode.
 *
 * \param wrap Can be:
 * - SC_WRAP_NONE: Disable line wrapping.
 * - SC_WRAP_WORD: To enable wrapping on word boundaries.
 * - SC_WRAP_CHAR: To enable wrapping between any characters.
 */
void CScintillaWnd::SetWrap(DWORD wrap)
{
	SendMessage(SCI_SETWRAPMODE, wrap, 0);
}

/**
 * \brief Returns the current wrap mode.
 *
 * \return The wrap mode currently used, it can be one of the following:
 * - SC_WRAP_NONE: Line wrapping is disabled.
 * - SC_WRAP_WORD: Wrapping on word boundaries.
 * - SC_WRAP_CHAR: Wrapping between any characters.
 */
DWORD CScintillaWnd::GetWrap()
{
	return SendMessage(SCI_GETWRAPMODE, 0, 0);
}

/**
 * \brief Returns the modified flag.
 *
 * \return TRUE when the buffer has been modified otherwise FALSE.
 */
BOOL CScintillaWnd::GetModify()
{
	return SendMessage(SCI_GETMODIFY, 0, 0);
}

/**
 * \brief Set modified flag.
 *
 * \param val TRUE to clear the flag.
 */
void CScintillaWnd::SetModify(BOOL val)
{
	SendMessage(SCI_SETSAVEPOINT, 0, 0);
}

/**
 * \brief Set Read-only state.
 *
 * Sets the read-only state.
 *
 * \param val If TRUE the text may not be edited.
 */
void CScintillaWnd::SetReadOnly(BOOL val)
{
	SendMessage(SCI_SETREADONLY, val, 0);
}

/**
 * \brief Return Read-only state.
 *
 * \return TRUE if the buffer can not be edited otherwise FALSE:
 */
BOOL CScintillaWnd::GetReadOnly()
{
	return SendMessage(SCI_GETREADONLY, 0, 0);
}

void CScintillaWnd::LoadLexerLib(LPCSTR name)
{
	SendMessage(SCI_LOADLEXERLIBRARY, 0, (long)name);
}

void CScintillaWnd::SetLexer(LPSTR name)
{
	SendMessage(SCI_SETLEXERLANGUAGE, 0, (long)name);
}

BOOL CScintillaWnd::GetCanCut()
{
	return SendMessage(SCI_GETSELECTIONSTART, 0, 0) - SendMessage(SCI_GETSELECTIONEND, 0, 0);
}

BOOL CScintillaWnd::GetHasText()
{
	return SendMessage(SCI_GETLENGTH, 0, 0);
}

int CScintillaWnd::GetStyleAt(long lPos)
{
	return SendMessage(SCI_GETSTYLEAT, lPos, 0);
}

void CScintillaWnd::DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back)
{
	SendMessage(SCI_MARKERDEFINE, (WPARAM)marker, (LPARAM)markerType);
	SetForeground(marker, fore);
	SetBackground(marker, back);
}

void CScintillaWnd::SetSelectedText(LPSTR lpText)
{
  SendMessage(SCI_REPLACESEL, 0, (LPARAM)lpText);
}

void CScintillaWnd::SetRightEdge(int pos)
{
	if (m_RightEdgePos != pos) {
		m_RightEdgePos = pos;
		if (m_RightEdgePos != -1) {
			SendMessage(SCI_SETEDGEMODE, 1, 0);
			SendMessage(SCI_SETEDGECOLUMN, m_RightEdgePos, 0);
			SendMessage(SCI_SETEDGECOLOUR, GetSysColor(COLOR_BTNFACE), 0);
		} else {
			SendMessage(SCI_SETEDGEMODE, 0, 0);
		}
	}
}

int CScintillaWnd::GetRightEdge()
{
	return m_RightEdgePos;
}

void CScintillaWnd::Colourise(int iStartPos, int iEndPos)
{
	SendMessage(SCI_COLOURISE, iStartPos, iEndPos);
}

long CScintillaWnd::FormatRange(BOOL draw, RangeToFormat *fr)
{
	return SendMessage(SCI_FORMATRANGE, (WPARAM)draw, (LPARAM)fr);
}

int CScintillaWnd::GetTextLength()
{
	return SendMessage(SCI_GETTEXTLENGTH, 0, 0);
}

TCHAR CScintillaWnd::GetCharAt(long lPos)
{
	return SendMessage(SCI_GETCHARAT, lPos, 0);
}

int CScintillaWnd::GetPositionFromPoint(CPoint point)
{
	return SendMessage(SCI_POSITIONFROMPOINT, point.x, point.y);
}

CWnd * CScintillaWnd::SetFocus()
{
	SendMessage(SCI_SETFOCUS, TRUE, 0);
	return CWnd::SetFocus();
}

int CScintillaWnd::GetFirstVisibleLine()
{
	return SendMessage(SCI_GETFIRSTVISIBLELINE, 0, 0);
}

void CScintillaWnd::Scoll(int col, int line)
{
	SendMessage(SCI_LINESCROLL, col ,line);
}

BOOL CScintillaWnd::FoldLine(int line)
{
	int level = SendMessage(SCI_GETFOLDLEVEL, line);
	if ((level & SC_FOLDLEVELHEADERFLAG)) {
		int lineMaxSubord = SendMessage(SCI_GETLASTCHILD, line, -1);
		SendMessage(SCI_SETFOLDEXPANDED, line, 0);
		if (lineMaxSubord > line) {
			SendMessage(SCI_HIDELINES, line + 1, lineMaxSubord);
			return TRUE;
		}
	}
	return FALSE;
}

void CScintillaWnd::FoldAll()
{
	int maxLine = SendMessage(SCI_GETLINECOUNT, 0, 0);
	for (int line = 0; line < maxLine; line++) {
		int level = SendMessage(SCI_GETFOLDLEVEL, line);
		if ((level & SC_FOLDLEVELHEADERFLAG)) {
			int lineMaxSubord = SendMessage(SCI_GETLASTCHILD, line, -1);
			SendMessage(SCI_SETFOLDEXPANDED, line, 0);
			if (lineMaxSubord > line)
				SendMessage(SCI_HIDELINES, line + 1, lineMaxSubord);
		}
	}
}

BOOL CScintillaWnd::ExpandLine(int line)
{
	int level = SendMessage(SCI_GETFOLDLEVEL, line);
	if ((level & SC_FOLDLEVELHEADERFLAG)) {
		SendMessage(SCI_SETFOLDEXPANDED, line, 1);
		Expand(line, TRUE, FALSE, 0, level);
		return TRUE;
	}
	return FALSE;
}

void CScintillaWnd::ExpandAll()
{
	int maxLine = SendMessage(SCI_GETLINECOUNT, 0, 0);
	for (int line = 0; line < maxLine; line++) {
		int level = SendMessage(SCI_GETFOLDLEVEL, line);
		if ((level & SC_FOLDLEVELHEADERFLAG)) {
			SendMessage(SCI_SETFOLDEXPANDED, line, 1);
			Expand(line, TRUE, FALSE, 0, level);
			line--;
		}
	}
}

void CScintillaWnd::Expand(int &line, BOOL doExpand, BOOL force, int visLevels, int level)
{
	int lineMaxSubord = SendMessage(SCI_GETLASTCHILD, line, level & SC_FOLDLEVELNUMBERMASK);
	line++;
	while (line <= lineMaxSubord) {
		if (force) {
			if (visLevels > 0)
				SendMessage(SCI_SHOWLINES, line, line);
			else
				SendMessage(SCI_HIDELINES, line, line);
		} else {
			if (doExpand)
				SendMessage(SCI_SHOWLINES, line, line);
		}
		int levelLine = level;
		if (levelLine == -1)
			levelLine = SendMessage(SCI_GETFOLDLEVEL, line);
		if (levelLine & SC_FOLDLEVELHEADERFLAG) {
			if (force) {
				if (visLevels > 1)
					SendMessage(SCI_SETFOLDEXPANDED, line, 1);
				else
					SendMessage(SCI_SETFOLDEXPANDED, line, 0);
				Expand(line, doExpand, force, visLevels - 1);
			} else {
				if (doExpand) {
					if (!SendMessage(SCI_GETFOLDEXPANDED, line))
						SendMessage(SCI_SETFOLDEXPANDED, line, 1);
					Expand(line, true, force, visLevels - 1);
				} else {
					Expand(line, false, force, visLevels - 1);
				}
			}
		} else {
			line++;
		}
	}
}
