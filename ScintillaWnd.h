/* @doc
 * @module ScintillaWnd.h | Definition of a Scintilla syntax coloring edit control for MFC<nl>
 * This program is an example how to use the excellent scintilla edit control of Neil Hodgson.<nl>
 * See www.scintilla.org for details<nl>
 * Author: Horst Brückner, hb@ec-logic.com<nl>
 * Environment: VisualC++ Version 6, static Build of Scintilla, SciLexer.dll as Lexer<nl>
 */

// Extended by Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>

/*
 * $Id: ScintillaWnd.h,v 1.22 2005/08/25 16:20:03 stievie Exp $
 */

#ifndef __SCINTILLAWND_H__
#define __SCINTILLAWND_H__

#include "Platform.h"
#include "scintilla.h"
#include "scilexer.h"

#define BRACE_HIGHLIGHT RGB(255, 255, 128)

/**
 * \brief Class of a GCL Scintilla syntax coloring edit control for MFC.
 *
 * This class encapsulates the Scintilla syntax colouring edititing control.
 */
class CScintillaWnd : public CWnd  
{
public:
	CScintillaWnd();
	virtual ~CScintillaWnd();

public:
	/**
	 * \brief Return linenumber display flag.
	 */
	BOOL GetDisplayLinenumbers (){return m_bLinenumbers;};
	/**
	 * \brief Return selection display flag.
	 */
	BOOL GetDisplaySelection (){return m_bSelection;};
	/**
	 * \brief Return folding margin display flag.
	 */
	BOOL GetDisplayFolding (){return m_bFolding;};
	/**
	 * \brief Set search flags.
	 */
	virtual void SetSearchflags (int nSearchflags){m_nSearchflags = nSearchflags;};   

public:
	BOOL ExpandLine(int line);
	BOOL FoldLine(int line);
	void ExpandAll();
	void FoldAll();
	void Scoll(int col, int line);
	int GetFirstVisibleLine();
	CWnd * SetFocus();
	int GetPositionFromPoint(CPoint point);
	TCHAR GetCharAt(long lPos);
	int GetTextLength();
	long FormatRange(BOOL draw, RangeToFormat* fr);
	void Colourise(int iStartPos, int iEndPos = -1);
	int m_RightEdgePos;
	int GetRightEdge();
	void SetRightEdge(int pos);
	void SetSelectedText(LPSTR lpText);
	void DefineMarker(int marker, int markerType, COLORREF fore, COLORREF back);
	void ToogleBookmark(long lLine);
	void ClearBookmarks();
	int GetStyleAt(long lPos);
	BOOL GetHasText();
	BOOL GetCanCut();
	void SetLexer(LPSTR name);
	void LoadLexerLib(LPCSTR name);
	void SetForeground(COLORREF crForeground);
	void SetBackground(COLORREF crBackground);
	virtual DWORD GetWrap();
	virtual BOOL GetReadOnly();
	virtual void SetReadOnly(BOOL val = TRUE);
	virtual void SetModify(BOOL val);
	virtual BOOL GetModify();
	virtual void SetWrap(DWORD wrap);
	void SetFont(CString name, int size, BOOL bold, BOOL italic, BOOL underline);
	// @cmember register a window class to use scintilla in a dialog
	static BOOL Register(CWinApp *app, UINT id);
	// @cmember try to load Lexer DLL
	static HMODULE LoadScintillaDll (LPCSTR szLexerDll = NULL);
	// @cmember create window
	virtual BOOL Create (LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	// @cmember Set Text to the Scintilla control
	virtual void SetText (LPCSTR szText);
	// @cmember Get Text from the Scintilla control
	virtual void GetText (CString &strText);
	// @cmember Get Text from the Scintilla control
	virtual LPSTR GetText();
	// @cmember Load a file
	virtual BOOL LoadFile (LPCSTR szFile);
	// @cmember Save a file
	virtual BOOL SaveFile (LPCSTR szFile);
	// @cmember calcluate number of chars needed for linenumberdisplay
	virtual int GetLinenumberChars ();
	// @cmember calcluate number of pixels for linenumber display
	virtual int GetLinenumberWidth ();
	// @cmember set display of linenumbers on/off
	virtual void SetDisplayLinenumbers(BOOL bFlag = TRUE);
	// @cmember set display of selection/bookmark margin on/off
	virtual void SetDisplaySelection(BOOL bFlag = TRUE);
	// @cmember set display of source folding margin on/off
	virtual void SetDisplayFolding(BOOL bFlag = TRUE);
	// @cmember cut selection to clipboard
	virtual void Cut();
	// @cmember copy selection to clipboard
	virtual void Copy();
	// @cmember paste from clipboard
	virtual void Paste();
	// @cmember clear selection
	virtual void Clear();
	// @cmember undo last change
	virtual void Undo();
	// @cmember redo last change
	virtual void Redo();
	// @cmember check if we can undo
	virtual BOOL GetCanUndo();
	// @cmember check if we can redo
	virtual BOOL GetCanRedo();
	// @cmember check if we have something to paste from clipboard
	virtual BOOL GetCanPaste();
	// @cmember select complete text
	virtual void SelectAll();
	// @cmember return the current line number
	virtual long GetCurrentLine();
	// @cmember return the current column number
	virtual long GetCurrentColumn();
	// @cmember return the current character position within the file
	virtual long GetCurrentPosition();
	// @cmember return the current style number at the current character position
	virtual int GetCurrentStyle();
	// @cmember return the current folding level at the current character position
	virtual int GetCurrentFoldinglevel();
	// @cmember set the fontname for a style number
	virtual void SetFontname(int nStyle, LPCSTR szFontname);
	// @cmember set the fontname height in points for a style number
	virtual void SetFontheight(int nStyle, int nHeight);
	// @cmember set the foregroundcolor for a style number
	virtual void SetForeground(int nStyle, COLORREF crForeground);
	// @cmember set the backgroundcolor for a style number
	virtual void SetBackground(int nStyle, COLORREF crBackground);
	// @cmember set given style to bold
	virtual void SetBold(int nStyle, BOOL bFlag);
	// @cmember set given style to bold
	virtual void SetItalic(int nStyle, BOOL bFlag);
	// @cmember set given style to bold
	virtual void SetUnderline(int nStyle, BOOL bFlag);
	// @cmember get flag if we are in overstrike mode
	virtual BOOL GetOverstrike();
	// @cmember set flag for overstrike mode
	virtual void SetOverstrike(BOOL bOverstrike);
	// @cmember init the view with reasonable defaults
	virtual void Init();
	// @cmember called whenever the text is changed - we can update any indicators and do brace matching
	virtual void UpdateUI();
	// @cmember do default folding 
	virtual void DoDefaultFolding(int nMargin, long lPosition);
	// @cmember refresh lexer and display after new settings
	virtual void Refresh();
	// @cmember add a bookmark = marker type 0
	virtual void AddBookmark(long lLine);
	// @cmember delete a bookmark = marker type 0
	virtual void DeleteBookmark(long lLine);
	// @cmember check for bookmark = marker type 0
	virtual BOOL HasBookmark(long lLine);
	// @cmember Find next bookmark
	virtual BOOL FindNextBookmark();
	// @cmember Find previous bookmark
	virtual BOOL FindPreviousBookmark();
	// @cmember goto line
	virtual void GotoLine(long lLine);
	// @cmember goto position
	virtual void GotoPosition(long lPos);
	// @cmember search forward for a given text
	virtual BOOL SearchForward(LPCSTR szText);
	// @cmember search backward for a given text
	virtual BOOL SearchBackward(LPCSTR szText);
	// @cmember replace a text found by SearchForward or SearchBackward
	virtual void ReplaceSearchedText(LPCSTR szText);
	// @cmember Set your own lexer
	virtual void SetLexer(int nLexer);
	// @cmember return start position of selection
	virtual long GetSelectionStart();
	// @cmember return end position of selection
	virtual long GetSelectionEnd();
	// @cmember get selected text
	virtual CString GetSelectedText();
	// @cmember replace all in buffer or selection
	virtual int ReplaceAll(LPCSTR szFind, LPCSTR szReplace, BOOL bSelection = TRUE);

protected:
	void Expand(int &line, BOOL doExpand, BOOL force, int visLevels, int level = -1);
	/** 
	 * Flag if we should display line numbers.
	 */
	BOOL m_bLinenumbers;
	/** 
	 * Flag if we should display selection and bookmark margin.
	 */
	BOOL m_bSelection;
	/**
	 * Flag if we should display folding margin.
	 */
	BOOL m_bFolding;
	/**
	 * Search flags.
	 */
	int m_nSearchflags;
};

/**
 * \brief Window name of the Scintilla control.
 */
#define STR_SCINTILLAWND _T("Scintilla")
/**
 * \brief Default filename of Scintilla DLL.
 */
#define STR_LEXERDLL     _T("scilexer.dll")

#endif // !__SCINTILLAWND_H__
