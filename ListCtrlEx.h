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

  $Id: ListCtrlEx.h,v 1.13 2006/03/29 21:30:29 stievie Exp $
*/

#if !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
#define AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrl.h : header file
//

#include "StringListEx.h"

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window

class CListCtrlEx : public CListCtrl
{
public:
	void UpdateEditor();
	BOOL GetEditPos(int &iItem, int &iSubItem);
	void ApplyEditText();
	void FoundWindow(HWND hwnd);
	CEdit* GetEditControl();
	void CancelEdit(BOOL cancel);
	CListCtrlEx (CString Text = "Some Text");
	virtual ~CListCtrlEx();

	CString m_DefaultText;
	CStringListEx m_AutoComplete;

	CEdit*  EditSubItem (int Item, int Column);
	int	    HitTestEx (CPoint& Point, int* Column);
	int	    InsertItemEx (int Item);
	void    Resize (int cx, int cy);

    //{{AFX_VIRTUAL(CListCtrlEx)
    //}}AFX_VIRTUAL

protected:
    //{{AFX_MSG(CListCtrlEx)
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
private:
	CEdit* m_Editor;
	static BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRL_H__2EB671B4_0711_11D3_90AB_00E029355177__INCLUDED_)
