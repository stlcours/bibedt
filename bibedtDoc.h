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

  $Id: bibedtDoc.h,v 1.44 2006/08/12 18:46:55 stievie Exp $
*/

// bibedtDoc.h : Schnittstelle der Klasse CBibedtDoc
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBEDTDOC_H__44C6BE17_6B3A_44DC_BFC0_0F5ECA74271A__INCLUDED_)
#define AFX_BIBEDTDOC_H__44C6BE17_6B3A_44DC_BFC0_0F5ECA74271A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibFile.h"
#include "Coding.h"
#include "FileWatch.h"
#include "ValueListDialog.h"

// Update reasons passed to CView::OnUpdate()
#define UR_RECADDED     1
#define UR_RECREMOVED   2
#define UR_RECEDITED    3
#define UR_RECSRCEDITED 4
#define UR_SORTED       5
#define UR_STREDITED    6
#define UR_PREEDITED    7
#define UR_OPENFILE     8
#define UR_SELECTED     9
#define UR_SRCEDITED   10
#define UR_APPENDFILE  11
#define UR_NEWFILE     12
#define UR_SAVINGFILE  13
#define UR_MODIFIED    14
#define UR_SAVEVIEWS   15
#define UR_FLTEDITED   16
#define UR_FILTERED    17
#define UR_PASTE       18

class COnlineSearch;

class CBibedtDoc : public CDocument
{
protected: // Nur aus Serialisierung erzeugen
	CBibedtDoc();
	DECLARE_DYNCREATE(CBibedtDoc)

// Attribute
public:

// Operationen
public:

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CBibedtDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementierung
public:
	COnlineSearch* m_OnlineSearchDialog;
	CValueListDialog *m_ValueListDialog;
	CString GenerateKey(CBibItem* item);
	void DoOpenFile(CFile* file);
	void CheckFileModified();
	BOOL SetSelected(CString key);
	CString m_QuicksearchFields;
	CString m_QuicksearchString;
	void UpdateQuicksearchFields();
	void EditFilter();
	void DoQuickSearch(CString str, CString fields, BOOL force);
	CField * GetFilter() const { return m_CurFilter; }
	void SetFilter(CField* filter);
	void UpdateFilter();
	void DeleteItem(CBibItem *item);
	void EnableView(DWORD dwID, BOOL enable);
	CBibItem * GetSelected() const { return m_Selected; }
	void SetSelected(CBibItem *item);
	BOOL ActivateView(DWORD dwID);
	void SetSource(CString src);
	bool GetLoaded() const { return m_BibFile->GetCount() > 0; }
	CBibFile* m_BibFile;
	virtual ~CBibedtDoc();
	virtual BOOL IsModified();
	virtual void SetModifiedFlag(BOOL bModified = TRUE);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void DoFilter(CField *filter);

// Generierte Message-Map-Funktionen
protected:
	CBibItem * m_Selected;
	CView * m_ListView;
	//{{AFX_MSG(CBibedtDoc)
	afx_msg void OnFileImport();
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditPreamble(CCmdUI* pCmdUI);
	afx_msg void OnEditPreamble();
	afx_msg void OnUpdateEditStrings(CCmdUI* pCmdUI);
	afx_msg void OnEditStrings();
	afx_msg void OnRecordAdd();
	afx_msg void OnUpdateRecordEdit(CCmdUI* pCmdUI);
	afx_msg void OnRecordEdit();
	afx_msg void OnUpdateRecordSorted(CCmdUI* pCmdUI);
	afx_msg void OnRecordSorted();
	afx_msg void OnUpdateRecordSource(CCmdUI* pCmdUI);
	afx_msg void OnRecordSource();
	afx_msg void OnUpdateRecordRemove(CCmdUI* pCmdUI);
	afx_msg void OnRecordRemove();
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnRecordFirst();
	afx_msg void OnUpdateRecordPrevious(CCmdUI* pCmdUI);
	afx_msg void OnRecordPrevious();
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnRecordNext();
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnRecordLast();
	afx_msg void OnUpdateRecordCopykey(CCmdUI* pCmdUI);
	afx_msg void OnRecordCopykey();
	afx_msg void OnUpdateToolsGeneratefromaux(CCmdUI* pCmdUI);
	afx_msg void OnToolsGeneratefromaux();
	afx_msg void OnToolsFilter();
	afx_msg void OnUpdateSearchRegularexpression(CCmdUI* pCmdUI);
	afx_msg void OnSearchRegularexpression();
	afx_msg void OnUpdateToolsOnlinesearch(CCmdUI* pCmdUI);
	afx_msg void OnToolsOnlinesearch();
	afx_msg void OnUpdateEditModified(CCmdUI* pCmdUI);
	afx_msg void OnEditModified();
	afx_msg void OnUpdateRecordInsertkey(CCmdUI* pCmdUI);
	afx_msg void OnRecordInsertkey();
	afx_msg void OnUpdateToolsGeneratekeys(CCmdUI* pCmdUI);
	afx_msg void OnToolsGeneratekeys();
	afx_msg void OnUpdateToolsValuelist(CCmdUI* pCmdUI);
	afx_msg void OnToolsValuelist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFileWatch m_FileWatch;
	BOOL m_RegularExpression;
	CField * m_CurFilter;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_BIBEDTDOC_H__44C6BE17_6B3A_44DC_BFC0_0F5ECA74271A__INCLUDED_)
