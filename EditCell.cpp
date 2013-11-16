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

  $Id: EditCell.cpp,v 1.10 2006/07/30 20:27:30 stievie Exp $
*/

// EditCell.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"
#include "EditCell.h"
#include "Globals.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditCell

CEditCell::CEditCell (CListCtrlEx* pCtrl, int iItem, int iSubItem, CString sInitText, CStringList* autocomp)
:   m_bEscape (FALSE)
{
	m_AutoComplete = autocomp;
    m_pListCtrl = pCtrl;
    m_Item = iItem;
    m_SubItem = iSubItem;
    m_InitText = sInitText;
	m_DoSuggest = TRUE;
}

CEditCell::~CEditCell()
{
}

BEGIN_MESSAGE_MAP(CEditCell, CEdit)
    //{{AFX_MSG_MAP(CEditCell)
    ON_WM_KILLFOCUS()
    ON_WM_NCDESTROY()
    ON_WM_CHAR()
    ON_WM_CREATE()
    ON_WM_GETDLGCODE()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditCell message handlers

void 
CEditCell::SetListText()
{
    CString Text;
    GetWindowText (Text);

    // Send Notification to parent of ListView ctrl
    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
    dispinfo.hdr.idFrom = GetDlgCtrlID();
    dispinfo.hdr.code = LVN_ENDLABELEDIT;

    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = m_Item;
    dispinfo.item.iSubItem = m_SubItem;
    dispinfo.item.pszText = m_bEscape ? NULL : LPTSTR ((LPCTSTR) Text);
    dispinfo.item.cchTextMax = Text.GetLength();

    GetParent()->GetParent()->SendMessage (WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM) &dispinfo);
}

BOOL 
CEditCell::PreTranslateMessage (MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
	    if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || 
			pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_TAB || 
			pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || GetKeyState (VK_CONTROL))
			{
				::TranslateMessage (pMsg);
				::DispatchMessage (pMsg);
				return TRUE;		    	// DO NOT process further
			}
    }

    return CEdit::PreTranslateMessage (pMsg);
}

void 
CEditCell::OnKillFocus (CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	SetListText();
	if (pNewWnd == m_pListCtrl) {
		// Don't exit edit mode when other toplevel window gets the focus,
		// but save the text, just in case... Saves one click :-)
		DestroyWindow();
	}
}

void 
CEditCell::OnNcDestroy()
{
    CEdit::OnNcDestroy();
    
    delete this;
}

void 
CEditCell::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // Up and down are in the OnKeyDown so that the user can hold down the arrow
    // keys to scroll through the entries.
    BOOL Control = GetKeyState(VK_CONTROL) < 0;
	BOOL Shift = GetKeyState(VK_SHIFT) < 0;
    switch (nChar)
    {
		case VK_UP :
		{
			if (m_Item > 0)
				m_pListCtrl->EditSubItem (m_Item - 1, m_SubItem);
			return;
		}
		case VK_TAB  :
		{
			if (Shift) {
				if (m_Item > 0)
					m_pListCtrl->EditSubItem (m_Item - 1, m_SubItem);
			} else {
				if (m_SubItem == 0)
					m_pListCtrl->EditSubItem (m_Item, 1);
				else
					m_pListCtrl->EditSubItem (m_Item + 1, m_SubItem);
			}
			return;
		}
		case VK_DOWN :
		{
			m_pListCtrl->EditSubItem (m_Item + 1, m_SubItem);
			return;
		}
		case VK_HOME :
		{
			if (!Control)
				break;

			m_pListCtrl->EditSubItem (0, m_SubItem);
			return;
		}
		case VK_END :
		{
			if (!Control)
				break;

			int Count = m_pListCtrl->GetItemCount() - 1;
			m_pListCtrl->EditSubItem (Count, m_SubItem);
			return;
		}
    }
    
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void 
CEditCell::OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    switch (nChar)
    {
		case VK_NEXT :
		{
			int Count = m_pListCtrl->GetItemCount();
			int NewItem = m_Item + m_pListCtrl->GetCountPerPage();
			if (Count > NewItem)
				m_pListCtrl->EditSubItem (NewItem, m_SubItem);
			else
				m_pListCtrl->EditSubItem (Count - 1, m_SubItem);
			return;
		}
		case VK_PRIOR :
		{
			int NewItem = m_Item - m_pListCtrl->GetCountPerPage();
			if (NewItem > 0)
				m_pListCtrl->EditSubItem (NewItem, m_SubItem);
			else
				m_pListCtrl->EditSubItem (0, m_SubItem);
			return;
		}
    }
    
    CEdit::OnKeyUp (nChar, nRepCnt, nFlags);
}

void 
CEditCell::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags)
{
    BOOL Shift = GetKeyState(VK_SHIFT) < 0;
    switch (nChar)
    {
		case VK_ESCAPE :
		{
			if (Shift)
				// Shift+Escape -> disable autocomplete
				m_DoSuggest = FALSE;
			else {
				m_bEscape = TRUE;
				GetParent()->SetFocus();
			}
			return;
		}
		case VK_RETURN :
		{
			SetListText();
			if (m_SubItem == 0)
				m_pListCtrl->EditSubItem (m_Item, 1);
			else
				m_pListCtrl->EditSubItem (m_Item + 1, 0);
			return;
		}
		case VK_TAB :
		{
			if (Shift)
			{
				if (m_SubItem > 0)
					m_pListCtrl->EditSubItem (m_Item, m_SubItem - 1);
				else
				{
					if (m_Item > 0)
						m_pListCtrl->EditSubItem (m_Item - 1, 2);
				}
			}
			else
			{
				if (m_SubItem == 0)
					m_pListCtrl->EditSubItem (m_Item, 1);
				else if (m_SubItem < 2)
					m_pListCtrl->EditSubItem (m_Item, m_SubItem + 1);				
				else
					m_pListCtrl->EditSubItem (m_Item + 1, 0);
			}
			return;
		}
    }

    CEdit::OnChar (nChar, nRepCnt, nFlags);

    // Get text
    CString Text;
    GetWindowText(Text);

	// Make some suggestion
	if (m_DoSuggest && nChar != 8 && m_AutoComplete != NULL) {
		int iSelStart;
		int iSelEnd;
		GetSel(iSelStart, iSelEnd);
		CString sugg = GetSuggestion(Text);
		if (!sugg.IsEmpty()) {
			Text = sugg;
			SetWindowText(Text);
			SetSel(iSelStart, Text.GetLength());
		}
	}

    // Resize edit control if needed

    CWindowDC DC (this);
    CFont *pFont = GetParent()->GetFont();
    CFont *pFontDC = DC.SelectObject (pFont);
    CSize Size = DC.GetTextExtent (Text);
    DC.SelectObject (pFontDC);
    Size.cx += 5;			   	// add some extra buffer

    // Get client rect
    CRect Rect, ParentRect;
    GetClientRect (&Rect);
    GetParent()->GetClientRect (&ParentRect);

    // Transform rect to parent coordinates
    ClientToScreen (&Rect);
    GetParent()->ScreenToClient (&Rect);

    // Check whether control needs to be resized and whether there is space to grow
    if (Size.cx > Rect.Width())
    {
		if (Size.cx + Rect.left < ParentRect.right )
			Rect.right = Rect.left + Size.cx;
		else
			Rect.right = ParentRect.right;
		MoveWindow (&Rect);
    }
}

int 
CEditCell::OnCreate (LPCREATESTRUCT lpCreateStruct)
{
    if (CEdit::OnCreate (lpCreateStruct) == -1)
		return -1;

    // Set the proper font
    CFont* Font = GetParent()->GetFont();
    SetFont (Font);

    SetWindowText (m_InitText);
    SetFocus();
    SetSel (0, -1);
    return 0;
}

UINT 
CEditCell::OnGetDlgCode()
{
    return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTTAB;
}

void CEditCell::SetAutoComplete(CStringList *lst)
{
	m_AutoComplete = lst;
}

CString CEditCell::GetSuggestion(CString txt)
{
	if (m_AutoComplete == NULL || txt.IsEmpty())
		return _T("");

	POSITION p = m_AutoComplete->GetHeadPosition();
	while (p) {
		CString str = m_AutoComplete->GetNext(p);
		if (str.GetLength() != txt.GetLength() && str.Left(txt.GetLength()).Compare(txt) == 0)
			return str;
	}
	return _T("");
}

LRESULT CEditCell::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_PASTE:
		// Remove linebreaks
		CString str = ClipBrdGetData(this, CB_TEXT);
		if (!str.IsEmpty()) {
			str.Replace(_T("\r\n"), _T(" "));
			str.Replace(_T("\r"), _T(" "));
			str.Replace(_T("\n"), _T(" "));
			CEdit::ReplaceSel(str, TRUE);
			return 0;
		}
		break;
	}
	return CEdit::WindowProc(message, wParam, lParam);
}