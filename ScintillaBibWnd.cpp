/*
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie[at]users[dot]sourceforge[dot]net, http://bibedt.sourceforge.net/

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  $Id: ScintillaBibWnd.cpp,v 1.19 2006/06/06 18:52:18 stievie Exp $
*/

// ScintillaBibWnd.cpp: Implementierung der Klasse CScintillaBibWnd.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "stdafx.h"
#include "ScintillaBibWnd.h"
#include "LexBib.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CScintillaBibWnd::CScintillaBibWnd()
{
	m_RegExpr = FALSE;
	m_MatchCase = FALSE;
	m_WholeWords = FALSE;
	m_SearchBackward = FALSE;
}

CScintillaBibWnd::~CScintillaBibWnd()
{

}

/**
 * Init some default values
 */
void CScintillaBibWnd::Init()
{
	CScintillaWnd::Init();

	SetDisplayFolding(TRUE);
	SetDisplayLinenumbers(TRUE);
	SetDisplaySelection(FALSE);

	// BibTeX
	LoadLexerLib(LEXBIB_LIB);
	SetLexer(LEXBIB_NAME);
	SetWrap(SC_WRAP_WORD);
	// Setup some BibTeX styles
	SetForeground(SCE_L_COMMAND, RGB(0, 0, 160));
	SetForeground(SCE_L_MATH, RGB(150, 150, 40));
	SetForeground(SCE_L_COMMENT, RGB(0, 128, 0));
	SetForeground(SCE_L_TAG, RGB(0, 0, 255));
	SetItalic(SCE_L_COMMENT, TRUE);
	SetBold(SCE_BIB_ITEM, TRUE);
	SetBold(SCE_BIB_END, TRUE);
	SetForeground(SCE_BIB_END, RGB(255, 0, 0));
	SetBold(SCE_BIB_START, TRUE);
	SetForeground(SCE_BIB_START, RGB(255, 0, 0));
	SetForeground(SCE_BIB_FIELD, RGB(140, 0, 70));
	SetForeground(SCE_BIB_KEY, RGB(140, 0, 0));
	SetBold(SCE_BIB_KEY, TRUE);
	// We also need HTML
	SetBold(SCE_H_ATTRIBUTEUNKNOWN, FALSE);
	SetBold(SCE_H_ATTRIBUTE, FALSE);
	SetBold(SCE_H_SINGLESTRING, FALSE);
	SetBold(SCE_H_DOUBLESTRING, FALSE);
	SetBold(SCE_H_TAG, TRUE);
	SetBold(SCE_H_TAGUNKNOWN, TRUE);
	SetForeground(SCE_H_TAGUNKNOWN, RGB(255, 0, 0));
//	SetItalic(SCE_H_COMMENT, TRUE);

	// Marker
	DefineMarker(SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0xFF));
	DefineMarker(SC_MARKNUM_FOLDER, SC_MARK_PLUS, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
	DefineMarker(SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY, RGB(0xff, 0xff, 0xff), RGB(0, 0, 0));
}

/**
 * Returns the position of a bib item.
 */
int CScintillaBibWnd::FindItem(CString key)
{
	// Finds nothing when short before the text was set
	// Well, the style is not yet set. Now it calls CScintillaWnd::Colourise
	// in CSourceView if needed.
	if (key.IsEmpty())
		return -1;
	TextToFind tf;
	int lPos = -1;
	tf.lpstrText = key.GetBuffer(key.GetLength()+1);
	tf.chrg.cpMax = SendMessage(SCI_GETLENGTH, 0, 0);
	do {
		tf.chrg.cpMin = lPos+1;
		lPos = SendMessage(SCI_FINDTEXT, SCFIND_WHOLEWORD | SCFIND_MATCHCASE, (long)&tf);
	} while (lPos > -1 && GetStyleAt(lPos) != SCE_BIB_KEY);
	return lPos;
}

/**
 * Places the caret to a bib item.
 */
BOOL CScintillaBibWnd::GotoItem(CString key)
{
	int p = FindItem(key);
	if (p != -1) {
		int l = SendMessage(SCI_LINEFROMPOSITION, p, 0) + 1;
		SendMessage(SCI_SETYCARETPOLICY, CARET_STRICT, 0);
		CScintillaWnd::GotoLine(l);
		SendMessage(SCI_SETYCARETPOLICY, 0, 0);
		return TRUE;
	} else
		return FALSE;
}

BOOL CScintillaBibWnd::SearchText(LPCSTR lpText)
{
	m_FindText = lpText;
	m_nSearchflags = 0;
	if (m_WholeWords)
		m_nSearchflags |= SCFIND_WHOLEWORD;
	if (m_MatchCase)
		m_nSearchflags |= SCFIND_MATCHCASE;
	if (m_RegExpr)
		m_nSearchflags |= SCFIND_REGEXP;

	if (!m_SearchBackward)
		return SearchForward(lpText);
	else
		return SearchBackward(lpText);
}

BOOL CScintillaBibWnd::FindNext()
{
	return SearchText(m_FindText.GetBuffer(m_FindText.GetLength()+1));
}

BOOL CScintillaBibWnd::MarkMatches(LPCSTR lpText)
{
	if (lpText == NULL)
		return FALSE;

	ClearBookmarks();
	DWORD matches = 0;

	m_nSearchflags = 0;
	if (m_WholeWords)
		m_nSearchflags |= SCFIND_WHOLEWORD;
	if (m_MatchCase)
		m_nSearchflags |= SCFIND_MATCHCASE;
	if (m_RegExpr)
		m_nSearchflags |= SCFIND_REGEXP;

	TextToFind tf;
	int lPos = -1;
	char* txt = new char[strlen(lpText)+1];
	strcpy(txt, lpText);
	tf.lpstrText = txt;
	tf.chrg.cpMax = SendMessage(SCI_GETLENGTH, 0, 0);
	do {
		tf.chrg.cpMin = lPos+1;
		lPos = SendMessage(SCI_FINDTEXT, m_nSearchflags, (long)&tf);
		if (lPos > -1) {
			int l = SendMessage(SCI_LINEFROMPOSITION, lPos, 0) + 1;
			AddBookmark(l);
			matches++;
		}
	} while (lPos > -1);
	delete [] txt;

	return matches;
}

/**
 * Return the key at the current position
 */
CString CScintillaBibWnd::GetCurrentKey()
{
	long lPos = SendMessage(SCI_GETCURRENTPOS, 0, 0);
	return GetKeyAt(lPos);
}

/**
 * Return the key at position lPos
 */
CString CScintillaBibWnd::GetKeyAt(long lPos)
{
	if (GetStyleAt(lPos) != SCE_BIB_KEY)
		return _T("");

	DWORD start = lPos;
	DWORD end = lPos;
	while (start > 0 && GetStyleAt(start) == SCE_BIB_KEY)
		start--;
	start++;
	while (GetStyleAt(end) == SCE_BIB_KEY)
		end++;
	TextRange tr;
	tr.chrg.cpMin = start;
	tr.chrg.cpMax = end;
	TCHAR *buff = new TCHAR[(end - start) + 1];
	tr.lpstrText = buff;

	SendMessage(SCI_GETTEXTRANGE, 0, (long)&tr);
	CString key(buff);

	delete [] buff;

	return key;
}

/**
 * Folds an item with key item
 */
BOOL CScintillaBibWnd::FoldItem(CString item)
{
	int iPos = FindItem(item);
	if (iPos == -1)
		return FALSE;
	int l = SendMessage(SCI_LINEFROMPOSITION, iPos, 0);
	return CScintillaWnd::FoldLine(l);
}

/**
 * Expand an item with key item
 */
BOOL CScintillaBibWnd::ExpandItem(CString item)
{
	int iPos = FindItem(item);
	if (iPos == -1)
		return FALSE;
	int l = SendMessage(SCI_LINEFROMPOSITION, iPos, 0);
	return CScintillaWnd::ExpandLine(l);
}
