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

  $Id: bibedtDoc.cpp,v 1.80 2006/08/12 18:46:55 stievie Exp $
*/

// bibedtDoc.cpp : Implementierung der Klasse CBibedtDoc
//

#include "stdafx.h"
#include "bibedt.h"

#include "bibedtDoc.h"
#include "BibFile.h"
#include "BibDef.h"
#include "Globals.h"
#include "bibedtView.h"
#include "MainFrm.h"
#include "PreambleDialog.h"
#include "StringsDialog.h"
#include "SourceDialog.h"
#include "FilterDialog.h"
#include "GenFromAuxDialog.h"
#include "OnlineSearch.h"
#include "FileDialogEx.h"
#include "ValueListDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBibedtDoc

IMPLEMENT_DYNCREATE(CBibedtDoc, CDocument)

BEGIN_MESSAGE_MAP(CBibedtDoc, CDocument)
	//{{AFX_MSG_MAP(CBibedtDoc)
	ON_COMMAND(ID_FILE_IMPORT, OnFileImport)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PREAMBLE, OnUpdateEditPreamble)
	ON_COMMAND(ID_EDIT_PREAMBLE, OnEditPreamble)
	ON_UPDATE_COMMAND_UI(ID_EDIT_STRINGS, OnUpdateEditStrings)
	ON_COMMAND(ID_EDIT_STRINGS, OnEditStrings)
	ON_COMMAND(ID_RECORD_ADD, OnRecordAdd)
	ON_UPDATE_COMMAND_UI(ID_RECORD_EDIT, OnUpdateRecordEdit)
	ON_COMMAND(ID_RECORD_EDIT, OnRecordEdit)
	ON_UPDATE_COMMAND_UI(ID_RECORD_SORTED, OnUpdateRecordSorted)
	ON_COMMAND(ID_RECORD_SORTED, OnRecordSorted)
	ON_UPDATE_COMMAND_UI(ID_RECORD_SOURCE, OnUpdateRecordSource)
	ON_COMMAND(ID_RECORD_SOURCE, OnRecordSource)
	ON_UPDATE_COMMAND_UI(ID_RECORD_REMOVE, OnUpdateRecordRemove)
	ON_COMMAND(ID_RECORD_REMOVE, OnRecordRemove)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_COMMAND(ID_RECORD_FIRST, OnRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREVIOUS, OnUpdateRecordPrevious)
	ON_COMMAND(ID_RECORD_PREVIOUS, OnRecordPrevious)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_COMMAND(ID_RECORD_NEXT, OnRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND(ID_RECORD_LAST, OnRecordLast)
	ON_UPDATE_COMMAND_UI(ID_RECORD_COPYKEY, OnUpdateRecordCopykey)
	ON_COMMAND(ID_RECORD_COPYKEY, OnRecordCopykey)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_GENERATEFROMAUX, OnUpdateToolsGeneratefromaux)
	ON_COMMAND(ID_TOOLS_GENERATEFROMAUX, OnToolsGeneratefromaux)
	ON_COMMAND(ID_TOOLS_FILTER, OnToolsFilter)
	ON_UPDATE_COMMAND_UI(ID_SEARCH_REGULAREXPRESSION, OnUpdateSearchRegularexpression)
	ON_COMMAND(ID_SEARCH_REGULAREXPRESSION, OnSearchRegularexpression)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ONLINESEARCH, OnUpdateToolsOnlinesearch)
	ON_COMMAND(ID_TOOLS_ONLINESEARCH, OnToolsOnlinesearch)
	ON_UPDATE_COMMAND_UI(ID_EDIT_MODIFIED, OnUpdateEditModified)
	ON_COMMAND(ID_EDIT_MODIFIED, OnEditModified)
	ON_UPDATE_COMMAND_UI(ID_RECORD_INSERTKEY, OnUpdateRecordInsertkey)
	ON_COMMAND(ID_RECORD_INSERTKEY, OnRecordInsertkey)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_GENERATEKEYS, OnUpdateToolsGeneratekeys)
	ON_COMMAND(ID_TOOLS_GENERATEKEYS, OnToolsGeneratekeys)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_VALUELIST, OnUpdateToolsValuelist)
	ON_COMMAND(ID_TOOLS_VALUELIST, OnToolsValuelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBibedtDoc Konstruktion/Destruktion

CBibedtDoc::CBibedtDoc()
{
	m_BibFile = new CBibFile();
	COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_BibFile->m_Backup = o->m_Backup;
	m_Selected = NULL;
	m_CurFilter = NULL;
	m_RegularExpression = FALSE;
	m_OnlineSearchDialog = NULL;
	m_ValueListDialog = NULL;
}

CBibedtDoc::~CBibedtDoc()
{
	delete m_BibFile;
}

BOOL CBibedtDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_FileWatch.SetFileName(_T(""));

	m_BibFile->NewFile();
	CBibList* def = GetBibDef();
	// Add all @strings and @preambles to the new file
	POSITION p = def->GetHeadPosition();
	while (p) {
		CBibItem* item = (CBibItem*)def->GetNext(p);
		if (item->IsType(STR_STRING) || item->IsType(STR_PREAMBLE))
			m_BibFile->New()->Assign(item);
	}
	m_BibFile->SetFilename(_T(""));
	m_BibFile->SetModified(FALSE);

	UpdateAllViews(NULL, UR_NEWFILE);
	SetSelected(NULL);
	SetModifiedFlag(FALSE);
	UpdateFilter();
	CMainFrame *m = (CMainFrame*)AfxGetMainWnd();
	ASSERT(m);
	m->ResetQuicksearch();
	m->UpdateQuicksearchFields(NULL);
	return TRUE;
}

BOOL CBibedtDoc::IsModified()
{
#ifdef _DEBUG
	BOOL docmod = CDocument::IsModified();
	BOOL lstmod = m_BibFile->GetModified();
#if 0
	TRACE1("CBibedtDoc::IsModified(): CDocument::IsModified() == %d\n", docmod);
	TRACE1("CBibedtDoc::IsModified(): m_BibFile->GetModified() == %d\n", lstmod);
#endif
	return docmod || lstmod;
#else
	return CDocument::IsModified() || m_BibFile->GetModified();
#endif
}

void CBibedtDoc::SetModifiedFlag(BOOL bModified)
{
	CDocument::SetModifiedFlag(bModified);
	m_BibFile->SetModified(bModified);
}


/////////////////////////////////////////////////////////////////////////////
// CBibedtDoc Serialisierung

void CBibedtDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		UpdateAllViews(NULL, UR_SAVINGFILE);
		COptions *pOp = ((CBibedtApp*)AfxGetApp())->m_Options;
		if (pOp->m_SortOnSave) {
			m_BibFile->Sort();
			UpdateAllViews(NULL, UR_SORTED);
		}
		m_BibFile->SetFilename(ar.GetFile()->GetFilePath());
		m_BibFile->Save(ar.GetFile());
	}
	else
	{
		DoOpenFile(ar.GetFile());
	}
	m_FileWatch.SetFileName(ar.GetFile()->GetFilePath());
	SetModifiedFlag(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CBibedtDoc Diagnose

#ifdef _DEBUG
void CBibedtDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBibedtDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBibedtDoc Befehle

void CBibedtDoc::OnFileImport() 
{
	CString filter;
	filter.Format(_T("%s|%s||"), AfxLoadString(IDS_STRING_BIBFILTER), AfxLoadString(IDS_STRING_ALLFILTER));
	CFileDialogEx dlg(TRUE, AfxLoadString(IDS_STRING_EXT_BIB), NULL, OFN_HIDEREADONLY | OFN_ENABLESIZING, filter, AfxGetApp()->GetMainWnd());
	if (dlg.DoModal() == IDOK) {
		CBibFile *f = new CBibFile();
		CFile fi;
		try {
			CWaitCursor wait;
			fi.Open(dlg.GetPathName(), CFile::modeRead | CFile::shareDenyWrite);
			f->Load(&fi);
			fi.Close();
			// Apply the current filter
			if (f->GetFilter()) {
				// Do not add filter of this file
				f->Delete(f->GetFilter());
			}
			f->DoFilter(GetFilter());

			POSITION p = m_BibFile->GetTailPosition();
			// Append the imported file
			m_BibFile->Append(f);
			if (p)
				// Not an empty list
				m_BibFile->GetNext(p);
			UpdateAllViews(NULL, UR_APPENDFILE);
		} catch (CFileException ex) {
			ex.ReportError();
		}
		delete f;
	}	
}

void CBibedtDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// Let's check if the file has been modified by another program here,
	// when the program is in idle.
	CheckFileModified();
	COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
	pCmdUI->Enable(o->m_DisableSave ? IsModified() : TRUE);
}

void CBibedtDoc::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsModified() || m_BibFile->GetCanSaveAs());	
}

void CBibedtDoc::SetSource(CString src)
{
	CString sel;
	if (m_Selected)
		sel = m_Selected->GetKey();
	m_BibFile->SetSource(src);
	CBibItem* seli = NULL;
	if (!sel.IsEmpty()) {
		seli = m_BibFile->Find(sel);
	}
	if (!seli)
		seli = m_BibFile->GetFirst();
	SetSelected(seli);
	UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	UpdateFilter();
	CMainFrame *m = (CMainFrame*)AfxGetMainWnd();
	ASSERT(m);
	m->ResetQuicksearch();
}

BOOL CBibedtDoc::ActivateView(DWORD dwID)
{
	return ((CMainFrame*)AfxGetMainWnd())->ActivateView(dwID);
}

void CBibedtDoc::EnableView(DWORD dwID, BOOL enable)
{
	((CMainFrame*)AfxGetMainWnd())->EnableView(dwID, enable);
}

void CBibedtDoc::OnUpdateEditPreamble(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

void CBibedtDoc::OnEditPreamble() 
{
	CPreambleDialog dlg;
	dlg.SetBibList(m_BibFile);
	if (dlg.DoModal() == IDOK) {
		CBibItem * item;
		// Remove all preambles
		POSITION p = m_BibFile->GetTailPosition();
		while (p) {
			item = (CBibItem*)m_BibFile->GetPrev(p);
			ASSERT(item);
			if (item->IsType(STR_PREAMBLE))
				m_BibFile->Delete(item);
		}
		// Add new preambles
		p = dlg.GetBibList()->GetTailPosition();
		while (p) {
			item = (CBibItem*)dlg.GetBibList()->GetPrev(p);
			ASSERT(item);
			CBibItem *newitem = new CBibItem(m_BibFile);
			newitem->Assign(item);
			m_BibFile->AddHead((CObject*)newitem);
		}
		UpdateAllViews(NULL, UR_PREEDITED);
	}
}

void CBibedtDoc::OnUpdateEditStrings(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);	
}

void CBibedtDoc::OnEditStrings() 
{
	CStringsDialog dlg;
	CWaitCursor wait;
	dlg.SetBibList(m_BibFile);
	if (dlg.DoModal() == IDOK) {
		CBibItem * item;
		// Remove all strings
		POSITION p = m_BibFile->GetTailPosition();
		while (p) {
			item = (CBibItem*)m_BibFile->GetPrev(p);
			ASSERT(item);
			if (item->IsType(STR_STRING))
				m_BibFile->Delete(item);
		}
		// Add new strings
		p = dlg.GetBibList()->GetTailPosition();
		while (p) {
			item = (CBibItem*)dlg.GetBibList()->GetPrev(p);
			ASSERT(item);
			CBibItem *newitem = new CBibItem(m_BibFile);
			newitem->Assign(item);
			m_BibFile->AddHead((CObject*)newitem);
		}
		UpdateAllViews(NULL, UR_STREDITED);
	}
}

void CBibedtDoc::OnRecordAdd() 
{
 	CBibItem *def = (CBibItem*)GetBibDef()->GetDefault();
	CString deftype = def->GetType();
	if (m_Selected)
		// Use previous type
		deftype = m_Selected->GetType();
	m_Selected = m_BibFile->New();
	m_Selected->SetType(deftype);
	if (m_CurFilter) {
		// Apply filter
		m_Selected->ApplyFilter(m_CurFilter);
	}
	EnableView(VIEW_RECORD, TRUE);
	UpdateAllViews(NULL, UR_RECADDED, m_Selected);
	// Must be after UR_RECADDED so the item in the list is already added
	UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	// Switch to item view
	ActivateView(VIEW_RECORD);
}

void CBibedtDoc::OnUpdateRecordEdit(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Selected != NULL);	
}

void CBibedtDoc::OnRecordEdit() 
{
	if (m_Selected) {
		ActivateView(VIEW_RECORD);
	}
}

void CBibedtDoc::OnUpdateRecordSorted(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetLoaded());
}

void CBibedtDoc::OnRecordSorted() 
{
	CWaitCursor wait;
	m_BibFile->Sort();
	UpdateAllViews(NULL, UR_SORTED);	
}

void CBibedtDoc::OnUpdateRecordSource(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Selected != NULL);
}

void CBibedtDoc::OnRecordSource() 
{
	if (m_Selected == NULL)
		return;
	// Get updated if any modified
	UpdateAllViews(NULL, UR_SAVEVIEWS);
	CSourceDialog dlg;
	dlg.SetBibItem(m_Selected);
	if (dlg.DoModal() == IDOK && dlg.m_Modified) {
		m_Selected->SetSource(dlg.GetSource());
		UpdateAllViews(NULL, UR_RECSRCEDITED, m_Selected);
	}
}

void CBibedtDoc::OnUpdateRecordRemove(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Selected != NULL);
}

void CBibedtDoc::OnRecordRemove() 
{
	if (m_Selected)
		DeleteItem(m_Selected);
}

void CBibedtDoc::DeleteItem(CBibItem *item)
{
	POSITION p = ((CObList*)m_BibFile)->Find((CObject*)item, NULL);
	BOOL isselected = item == m_Selected;

	if (isselected) {
		POSITION pnext = p;
		if (pnext)
			m_BibFile->GetNext(pnext);
		if (pnext)
			// Next
			m_Selected = (CBibItem*)m_BibFile->GetAt(pnext);
		else {
			// Select first
			if (m_BibFile->GetItemCount()-1)
				m_Selected = (CBibItem*)m_BibFile->GetFirst();
			else
				m_Selected = NULL;
		}
		if (!m_Selected) {
			ActivateView(VIEW_LIST);
			EnableView(VIEW_RECORD, FALSE);
		}
	}

	// Remove it from the list, but don't delete it
	if (p)
		m_BibFile->RemoveAt(p);
	UpdateAllViews(NULL, UR_RECREMOVED, item);
	// Views are updated now we can delete it.
	delete item;
	if (isselected) {
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
		EnableView(VIEW_RECORD, m_Selected != NULL);
	}
}

void CBibedtDoc::SetSelected(CBibItem *item)
{
	if (m_Selected != item) {
		m_Selected = item;
	}
	EnableView(VIEW_RECORD, m_Selected != NULL);
}

void CBibedtDoc::OnUpdateRecordFirst(CCmdUI* pCmdUI) 
{
	if (m_Selected) {
		pCmdUI->Enable(m_BibFile->GetPrevItem(m_Selected) != NULL);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibedtDoc::OnRecordFirst() 
{
	if (m_Selected) {
		m_Selected = m_BibFile->GetFirst();
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	}
}

void CBibedtDoc::OnUpdateRecordPrevious(CCmdUI* pCmdUI) 
{
	if (m_Selected) {
		pCmdUI->Enable(m_BibFile->GetPrevItem(m_Selected) != NULL);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibedtDoc::OnRecordPrevious() 
{
	if (m_Selected) {
		m_Selected = m_BibFile->GetPrevItem(m_Selected);
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	}
}

void CBibedtDoc::OnUpdateRecordNext(CCmdUI* pCmdUI) 
{
	if (m_Selected) {
		pCmdUI->Enable(m_BibFile->GetNextItem(m_Selected) != NULL);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibedtDoc::OnRecordNext() 
{
	if (m_Selected) {
		m_Selected = m_BibFile->GetNextItem(m_Selected);
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	}
}

void CBibedtDoc::OnUpdateRecordLast(CCmdUI* pCmdUI) 
{
	if (m_Selected) {
		pCmdUI->Enable(m_BibFile->GetNextItem(m_Selected) != NULL);
	} else
		pCmdUI->Enable(FALSE);
}

void CBibedtDoc::OnRecordLast() 
{
	if (m_Selected) {
		m_Selected = (CBibItem*)m_BibFile->GetLast();
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	}
}

/**
 * Show the Filter dialog
 */
void CBibedtDoc::EditFilter()
{
	CFilterDialog dlg;
	dlg.SetFilter(m_BibFile->GetFilter());
	if (dlg.DoModal() == IDOK) {
		CBibItem *fi = dlg.GetFilter();
		CBibItem *filter = m_BibFile->GetFilter();
		if (fi->GetCount() > 0) {
			if (!filter) {
				// There is no filter item at the moment -> create one
				filter = m_BibFile->New();
			}
			filter->Assign(dlg.GetFilter());
		} else if (filter)
			// Filter contains no items -> delete it
			m_BibFile->Delete(filter);
		UpdateFilter();
		UpdateAllViews(NULL, UR_FLTEDITED);
	}
}

/**
 * Update filter in the filter combo of the main window
 */
void CBibedtDoc::UpdateFilter()
{
	// Update filter in filter combo of main window
	CMainFrame *m = (CMainFrame*)AfxGetMainWnd();
	ASSERT(m);
	m->UpdateFilter(m_BibFile->GetFilter());
	// Reset filter
	SetFilter(NULL);
}

/**
 * Do filter the file
 */
void CBibedtDoc::DoFilter(CField *filter)
{
	// Filter out all not matching
	m_BibFile->DoFilter(filter);
	UpdateAllViews(NULL, UR_FILTERED);
	if (m_Selected && !m_Selected->IsVisible()) {
		SetSelected(m_BibFile->GetFirst());
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	}
}

void CBibedtDoc::SetFilter(CField *filter)
{
	if (m_CurFilter != filter) {
		m_CurFilter = filter;
		DoFilter(m_CurFilter);
	}
}

void CBibedtDoc::DoQuickSearch(CString str, CString fields, BOOL force)
{
	if (!force && (m_QuicksearchString.CompareNoCase(str) == 0 && m_QuicksearchFields.CompareNoCase(fields) == 0))
		// Only search when something changed
		return;
	m_QuicksearchString = str;
	m_QuicksearchFields = fields;

	COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
	if (!fields.IsEmpty()) {
		// Should we search all fields
		if (fields.CompareNoCase(AfxLoadString(IDS_STRING_ALLFIELDS)) != 0) {
			// If not see if there is a trailing ;
			if (fields.Right(1) != _T(";"))
				fields += _T(";");
		} else
			// If so, empty fields, CBibItem will check that, 
			// i.e. it always searches all fileds if the string is empty.
			fields.Empty();
		m_BibFile->DoQuickSearch(str, fields, m_RegularExpression);
	} else
		m_BibFile->DoQuickSearch(str, o->m_QuickSearchFields, m_RegularExpression);
	UpdateAllViews(NULL, UR_FILTERED);
	if (m_Selected && !m_Selected->IsVisible()) {
		SetSelected(m_BibFile->GetFirst());
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	}
}

void CBibedtDoc::OnUpdateRecordCopykey(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Selected != NULL && !m_Selected->GetKey().IsEmpty());
}

void CBibedtDoc::OnRecordCopykey() 
{
	ASSERT(m_Selected);
	ClipBrdPutData(NULL, m_Selected->GetKey(), CB_TEXT, TRUE);	
}

/**
 * Fill the ComboBox with all field names.
 */
void CBibedtDoc::UpdateQuicksearchFields()
{
	CStringList lst;
	m_BibFile->GetAllFieldNames(&lst);
	CMainFrame *m = (CMainFrame*)AfxGetMainWnd();
	ASSERT(m);
	m->UpdateQuicksearchFields(&lst);
}

void CBibedtDoc::OnUpdateToolsGeneratefromaux(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetLoaded());
}

void CBibedtDoc::OnToolsGeneratefromaux() 
{
	CGenFromAuxDialog dlg;
	dlg.SetBibList(m_BibFile);
	dlg.DoModal();
}

BOOL CBibedtDoc::SetSelected(CString key)
{
	CBibItem* item = m_BibFile->Find(key);
	if (item) {
		SetSelected(item);
		UpdateAllViews(NULL, UR_SELECTED, m_Selected);
		return TRUE;
	}
	return FALSE;
}

void CBibedtDoc::OnToolsFilter() 
{
	EditFilter();
}

void CBibedtDoc::OnCloseDocument() 
{
	UpdateAllViews(NULL, UR_SAVEVIEWS, NULL);
	if (m_OnlineSearchDialog != NULL) {
		COnlineSearch* dlg = m_OnlineSearchDialog;
		m_OnlineSearchDialog = NULL;
		dlg->DestroyWindow();
		delete dlg;
	}
	if (m_ValueListDialog != NULL) {
		CValueListDialog *vdlg = m_ValueListDialog;
		m_ValueListDialog = NULL;
		vdlg->DestroyWindow();
		delete vdlg;
	}
	
	CDocument::OnCloseDocument();
}

void CBibedtDoc::OnUpdateSearchRegularexpression(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_RegularExpression);
}

void CBibedtDoc::OnSearchRegularexpression() 
{
	m_RegularExpression = !m_RegularExpression;
	DoQuickSearch(m_QuicksearchString, m_QuicksearchFields, TRUE); 
}

void CBibedtDoc::CheckFileModified()
{
	if (GetForegroundWindow() != AfxGetMainWnd()->m_hWnd)
		// Only when this is the active app
		return;

	CString msg;
	switch (m_FileWatch.GetModified()) {
	case FC_DATE:
		SetModifiedFlag(TRUE);
		msg.Format(IDS_STRING_FILECHANGED, GetTitle());
		if (AfxMessageBox(msg, MB_ICONQUESTION | MB_YESNO, 0) == IDYES) {
			CFile file;
			CFileException ex;
			if (file.Open(m_BibFile->GetFilename(), CFile::modeRead | CFile::shareDenyWrite, &ex)) {
				DoOpenFile(&file);
				file.Close();
				SetModifiedFlag(FALSE);
				m_FileWatch.Update();
			} else
				ex.ReportError();
		}
		break;
	case FC_DELETE:
		SetModifiedFlag(TRUE);
		msg.Format(IDS_STRING_FILEDELETED, GetTitle());
		AfxMessageBox(msg, MB_ICONINFORMATION, 0);
		break;
	}
}

void CBibedtDoc::DoOpenFile(CFile *file)
{
	m_BibFile->SetFilename(file->GetFilePath());
	if (!m_BibFile->Load(file)) {
		ShowError(AfxLoadString(IDS_STRING_LOADERR));
	}
	UpdateAllViews(NULL, UR_OPENFILE);
	SetSelected(m_BibFile->GetFirst());
	UpdateAllViews(NULL, UR_SELECTED, m_Selected);
	UpdateFilter();
	CMainFrame *m = (CMainFrame*)AfxGetMainWnd();
	ASSERT(m);
	m->ResetQuicksearch();
	UpdateQuicksearchFields();
}

BOOL CBibedtDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	m_FileWatch.BeginUpdate();	
	BOOL ret = CDocument::OnSaveDocument(lpszPathName);
	m_FileWatch.Update();
	m_FileWatch.EndUpdate();
	return ret;
}

CString CBibedtDoc::GenerateKey(CBibItem *item)
{
	return m_BibFile->GenerateKey(item);
}

void CBibedtDoc::OnUpdateToolsOnlinesearch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(TRUE);
}

void CBibedtDoc::OnToolsOnlinesearch() 
{
	if (m_OnlineSearchDialog != NULL)
		m_OnlineSearchDialog->ShowWindow(SW_SHOW);
	else {
		m_OnlineSearchDialog = new COnlineSearch();
		m_OnlineSearchDialog->SetDocument(this);
		m_OnlineSearchDialog->SetBibList(m_BibFile);
		m_OnlineSearchDialog->ShowWindow(SW_NORMAL);
		m_OnlineSearchDialog->UpdateWindow();
	}
}

void CBibedtDoc::OnUpdateEditModified(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(IsModified());
}

void CBibedtDoc::OnEditModified() 
{
	SetModifiedFlag(!IsModified());
}

void CBibedtDoc::OnUpdateRecordInsertkey(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Selected != NULL && !m_Selected->GetKey().IsEmpty());
}

void CBibedtDoc::OnRecordInsertkey() 
{
	COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
	HWND w = o->GetEditorWindow();
	if (w) {
		if (m_Selected != NULL && !m_Selected->GetKey().IsEmpty()) {
			OnRecordCopykey();
			::SendMessage(w, WM_PASTE, 0, 0);
		}
	}

}

void CBibedtDoc::OnUpdateToolsGeneratekeys(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_BibFile->GetCount());
}

void CBibedtDoc::OnToolsGeneratekeys() 
{
	if (AfxMessageBox(IDS_GENERATEKEYS_PROMPT, MB_ICONQUESTION | MB_YESNO, 0) == IDYES) {
		CWaitCursor wait;

		POSITION p = m_BibFile->GetHeadPosition();
		while (p) {
			CBibItem* item = (CBibItem*)m_BibFile->GetNext(p);
			ASSERT(item);
			if (item->IsRegularItem()) {
				CString key = m_BibFile->GenerateKey(item);
//				ASSERT(!key.IsEmpty());
				if (!key.IsEmpty())
					item->SetKey(key);
#ifdef _DEBUG
				else
					TRACE("CBibedtDoc::OnToolsGeneratekeys(): key.IsEmpty == TRUE\n");
#endif
			}
		}
		UpdateAllViews(NULL, UR_SRCEDITED, NULL);
		m_BibFile->SetModified(TRUE);
	}
}

void CBibedtDoc::OnUpdateToolsValuelist(CCmdUI* pCmdUI) 
{
	// TODO: Code für die Befehlsbehandlungsroutine zum Aktualisieren der Benutzeroberfläche hier einfügen
	
}

void CBibedtDoc::OnToolsValuelist() 
{
	if (m_ValueListDialog != NULL)
		m_ValueListDialog->ShowWindow(SW_SHOW);
	else {
		m_ValueListDialog = new CValueListDialog();
		m_ValueListDialog->SetBibList(m_BibFile);
		m_ValueListDialog->ShowWindow(SW_NORMAL);
		m_ValueListDialog->UpdateWindow();
	}
}
