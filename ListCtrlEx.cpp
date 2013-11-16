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

  $Id: ListCtrlEx.cpp,v 1.13 2006/03/29 21:30:29 stievie Exp $
*/

// ListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"
#include "EditCell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define IDC_EDITCELL 1001

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx (CString Text /* = "Some Text" */)
{
    m_DefaultText = Text;
}

CListCtrlEx::~CListCtrlEx()
{
}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
    //{{AFX_MSG_MAP(CListCtrlEx)
    ON_WM_HSCROLL()
    ON_WM_VSCROLL()
    ON_WM_LBUTTONDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

void 
CListCtrlEx::Resize (int cx, int cy)
{
    CRect Rect (0, 0, cx, cy);
    MoveWindow (&Rect);
    InvalidateRect (Rect);
    SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);
}

CEdit* 
CListCtrlEx::EditSubItem (int Item, int Column)
{
    // The returned pointer should not be saved

	CancelEdit(FALSE);

    // Make sure that the item is visible
    if (!EnsureVisible (Item, TRUE)) 
    {
		InsertItemEx (Item);
		if (!EnsureVisible (Item, TRUE)) 
			return NULL;
    }

    // Make sure that nCol is valid
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if (Column >= nColumnCount || GetColumnWidth (Column) < 5)
		return NULL;

    // Get the column offset
    int Offset = 0;
    for (int iColumn = 0; iColumn < Column; iColumn++)
		Offset += GetColumnWidth (iColumn);

    CRect Rect;
    GetItemRect (Item, &Rect, LVIR_BOUNDS);

    // Now scroll if we need to expose the column
    CRect ClientRect;
    GetClientRect (&ClientRect);
    if (Offset + Rect.left < 0 || Offset + Rect.left > ClientRect.right)
    {
		CSize Size;
		if (Offset + Rect.left > 0)
			Size.cx = -(Offset - Rect.left);
		else
			Size.cx = Offset - Rect.left;
		Size.cy = 0;
		Scroll (Size);
		Rect.left -= Size.cx;
    }

    // Get Column alignment
    LV_COLUMN lvCol;
    lvCol.mask = LVCF_FMT;
    GetColumn (Column, &lvCol);
    DWORD dwStyle;
    if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
    else if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
    else dwStyle = ES_CENTER;

    Rect.left += Offset+4;
    Rect.right = Rect.left + GetColumnWidth (Column) - 3;
    if (Rect.right > ClientRect.right)
		Rect.right = ClientRect.right;

    dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

    // Send Notification to parent of ListView ctrl
    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = m_hWnd;
    dispinfo.hdr.idFrom = 0;
    dispinfo.hdr.code = LVN_BEGINLABELEDIT;

    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = Item;
    dispinfo.item.iSubItem = Column;
    dispinfo.item.pszText = NULL;
    dispinfo.item.cchTextMax = 0;

	// Return Values
	// To allow the user to edit the label, return FALSE.
	// To prevent the user from editing the label, return TRUE.
    if (!GetParent()->SendMessage (WM_NOTIFY, GetDlgCtrlID(), (LPARAM) &dispinfo)) {
		CEditCell *pEdit = new CEditCell (this, Item, Column, GetItemText(Item, Column), 
			m_AutoComplete.GetCount() > 0 ? &m_AutoComplete : NULL);
		pEdit->Create (dwStyle, Rect, this, IDC_EDITCELL);
	    return pEdit;
	} else {
		return NULL;
	}
}

int 
CListCtrlEx::HitTestEx (CPoint& Point, int* pColumn)
{
    int ColumnNum = 0;
    int Row = HitTest (Point, NULL);
    
    if (pColumn)
		*pColumn = 0;

    // Make sure that the ListView is in LVS_REPORT
    if ((GetWindowLong (m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
		return Row;

    // Get the top and bottom row visible
    Row = GetTopIndex();
    int Bottom = Row + GetCountPerPage();
    if (Bottom > GetItemCount())
	    Bottom = GetItemCount();
    
    // Get the number of columns
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    // Loop through the visible rows
    for(; Row <= Bottom; Row++)
    {
		// Get bounding rect of item and check whether point falls in it.
		CRect Rect;
		GetItemRect (Row, &Rect, LVIR_BOUNDS);
		if (Rect.PtInRect (Point))
		{
			// Now find the column
			for (ColumnNum = 0; ColumnNum < nColumnCount; ColumnNum++)
			{
				int ColWidth = GetColumnWidth (ColumnNum);
				if (Point.x >= Rect.left && Point.x <= (Rect.left + ColWidth))
				{
					if (pColumn)
						*pColumn = ColumnNum;
					return Row;
				}
				Rect.left += ColWidth;
			}
		}
    }
    return -1;
}

int 
CListCtrlEx::InsertItemEx (int Item)
{
    int Result = InsertItem (Item + 1, m_DefaultText);

    SetColumnWidth (2, LVSCW_AUTOSIZE_USEHEADER);

    return Result;
}

void 
CListCtrlEx::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (GetFocus() != this) 
		SetFocus();
    
    CListCtrl::OnHScroll (nSBCode, nPos, pScrollBar);
}

void 
CListCtrlEx::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (GetFocus() != this) 
		SetFocus();
    
    CListCtrl::OnVScroll (nSBCode, nPos, pScrollBar);
}

void 
CListCtrlEx::OnLButtonDown (UINT nFlags, CPoint Point)
{
    int Index;
    int ColNum;
    if ((Index = HitTestEx (Point, &ColNum)) != -1 && Index == GetSelectionMark()) {
		// This was a slow dbl click
	    CListCtrl::OnLButtonDown (nFlags, Point);
		EditSubItem (Index, ColNum);
    } else
	    CListCtrl::OnLButtonDown (nFlags, Point);
}

void CListCtrlEx::CancelEdit(BOOL cancel)
{
	CEditCell* edit = dynamic_cast<CEditCell*>(GetEditControl());
	if (edit != NULL) {
		if (!cancel)
			edit->SetListText();
		SetFocus();
	}
}


BOOL CALLBACK CListCtrlEx::EnumChildProc(
	HWND hwnd,      // handle to child window
	LPARAM lParam   // application-defined value
)
{
	CListCtrlEx* sender = (CListCtrlEx*)lParam;
	sender->FoundWindow(hwnd);
	return TRUE;
}

CEdit* CListCtrlEx::GetEditControl()
{
	m_Editor = NULL;
	EnumChildWindows(m_hWnd, EnumChildProc, (LPARAM)this);
	return m_Editor;
}

void CListCtrlEx::FoundWindow(HWND hwnd)
{
	if (hwnd)
		m_Editor = dynamic_cast<CEdit*>(CEdit::FromHandle(hwnd));
}

void CListCtrlEx::OnSetFocus(CWnd* pOldWnd) 
{
	CEdit* editor = GetEditControl();
	if (editor)
		editor->SetFocus();
	else
		CListCtrl::OnSetFocus(pOldWnd);
		
}

void CListCtrlEx::ApplyEditText()
{
	CEditCell* edit = dynamic_cast<CEditCell*>(GetEditControl());
	if (edit)
		edit->SetListText();
}

BOOL CListCtrlEx::GetEditPos(int &iItem, int &iSubItem)
{
	CEditCell* edit = dynamic_cast<CEditCell*>(GetEditControl());
	if (edit) {
		iItem = edit->m_Item;
		iSubItem = edit->m_SubItem;
		return TRUE;
	} else
		return FALSE;
}

void CListCtrlEx::UpdateEditor()
{
	CEditCell* edit = dynamic_cast<CEditCell*>(GetEditControl());
	if (edit) {
		CString txt = GetItemText(edit->m_Item, edit->m_SubItem);
		edit->SetWindowText(txt);
	}
}
