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

  $Id: EditCell.h,v 1.7 2006/07/30 19:36:55 stievie Exp $
*/

#if !defined(AFX_EDITCELL_H__2EB671B5_0711_11D3_90AB_00E029355177__INCLUDED_)
#define AFX_EDITCELL_H__2EB671B5_0711_11D3_90AB_00E029355177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditCell.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditCell window
class CEditCell : public CEdit
{
public:
	BOOL m_DoSuggest;
	CString GetSuggestion(CString txt);
	void SetAutoComplete(CStringList* lst);
	CEditCell (CListCtrlEx* pCtrl, int iItem, int iSubItem, CString sInitText, CStringList* autocomp);
    virtual ~CEditCell();
    void    SetListText();
    int			m_Item;
    int			m_SubItem;

    //{{AFX_VIRTUAL(CEditCell)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CStringList* m_AutoComplete;
    CListCtrlEx* m_pListCtrl;
    CString		m_InitText;
    BOOL		m_bEscape;
    
    //{{AFX_MSG(CEditCell)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnNcDestroy();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

    DECLARE_MESSAGE_MAP()
private:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITCELL_H__2EB671B5_0711_11D3_90AB_00E029355177__INCLUDED_)
