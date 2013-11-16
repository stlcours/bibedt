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

  $Id: BibitemView.h,v 1.28 2006/08/07 15:11:01 stievie Exp $
*/

#if !defined(AFX_BIBITEMVIEW_H__8119A593_5B60_4A6A_8AB1_6F703022CC53__INCLUDED_)
#define AFX_BIBITEMVIEW_H__8119A593_5B60_4A6A_8AB1_6F703022CC53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BibitemView.h : Header-Datei
//

#include "BPCtrlAnchorMap.h"
#include "ScintillaBibWnd.h"
#include "bibedtDoc.h"
#include "ListCtrlEx.h"

/////////////////////////////////////////////////////////////////////////////
// Formularansicht CBibitemView 

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CBibitemView : public CFormView
{
protected:
	CBibitemView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CBibitemView)

// Formulardaten
public:
	//{{AFX_DATA(CBibitemView)
	enum { IDD = IDD_BIBITEMVIEW_FORM };
	CListBox	m_lstMissingFields;
	CEdit	m_EditKey;
	CButton	m_BtnUndo;
	CButton	m_BtnApply;
	CButton	m_BtnRemove;
	CButton	m_BtnEdit;
	CListCtrlEx	m_ListFields;
	CComboBox	m_ComboType;
	//}}AFX_DATA

// Attribute
public:
	CBibedtDoc* GetDocument();

// Operationen
public:

public:
	void UpdateMissing();
	int GetItemIndex(CField* item);
	void DeleteField(int nIndex);
	void AddLocalURL(CString url);
	void EndUpdate() { if (m_Updating > 0) m_Updating--; }
	void BeginUpdate() { m_Updating++; }
	void SetModified(BOOL val = TRUE);
	void Apply();
	BOOL m_Modified;
	int AddField(CString name, CString value, BOOL edit);
	void InitDialog();
	void PopulateFields();
	DECLARE_ANCHOR_MAP();

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CBibitemView)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CEdit* GetFocusEdit();
	void UpdateItem();
	virtual ~CBibitemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	CBibDef* m_BibDef;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CBibitemView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonGeygenerate();
	afx_msg void OnSelchangeComboType();
	afx_msg void OnDblclkListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInsertitemListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	afx_msg void OnChangeEditKey();
	afx_msg void OnDestroy();
	afx_msg void OnFieldlistPopupAdd();
	afx_msg void OnUpdateFieldlistPopupAdd(CCmdUI* pCmdUI);
	afx_msg void OnFieldlistPopupRemove();
	afx_msg void OnUpdateFieldlistPopupRemove(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFieldlistPopupEdit(CCmdUI* pCmdUI);
	afx_msg void OnFieldlistPopupEdit();
	afx_msg void OnUpdatePopupBrowse(CCmdUI* pCmdUI);
	afx_msg void OnPopupBrowse();
	afx_msg void OnUpdatePopupCrossref(CCmdUI* pCmdUI);
	afx_msg void OnPopupCrossref();
	afx_msg void OnBeginlabeleditListFields(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRecordGeneratekey();
	afx_msg void OnDblclkListMissingfields();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPopupFilter();
	afx_msg void OnUpdatePopupFilter(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI* pCmdUI);
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	afx_msg void OnPopupLocalurl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GenerateKey();
	CMenu m_PopupMenu;
	DWORD m_Updating;
	int m_SelField;
	BOOL m_SortAsc;
	static int CALLBACK SortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	CImageList m_ImageList;
	CBibItem* m_BibItem;
	CBibItem* m_TmpItem;
	BOOL m_NewDialog;
};

#ifndef _DEBUG  // Testversion in bibedtView.cpp
inline CBibedtDoc* CBibitemView::GetDocument()
   { return (CBibedtDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_BIBITEMVIEW_H__8119A593_5B60_4A6A_8AB1_6F703022CC53__INCLUDED_
