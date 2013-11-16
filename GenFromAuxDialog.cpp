/*
  BibEdt
  Copyright (C) 2005, Ascher Stefan. All rights reserved.
  stievie@utanet.at, http://bibedt.sourceforge.net/

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

  $Id: GenFromAuxDialog.cpp,v 1.12 2006/07/29 11:33:14 stievie Exp $
*/

// GenFromAuxDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "GenFromAuxDialog.h"
#include "FileDialogEx.h"
#include "BibDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CGenFromAuxDialog 


CGenFromAuxDialog::CGenFromAuxDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CGenFromAuxDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenFromAuxDialog)
	//}}AFX_DATA_INIT
}


void CGenFromAuxDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenFromAuxDialog)
	DDX_Control(pDX, IDC_CHECK_REQFIELDS, m_btnReqFields);
	DDX_Control(pDX, ID_BUTTON_GENERATE, m_btnGenerate);
	DDX_Control(pDX, IDC_EDIT_AUXFILE, m_editAuxFile);
	DDX_Control(pDX, IDC_EDIT_LOG, m_editLog);
	DDX_Control(pDX, IDC_EDIT_TARGETFILE, m_editTargetFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenFromAuxDialog, CDialog)
	//{{AFX_MSG_MAP(CGenFromAuxDialog)
	ON_BN_CLICKED(IDC_BUTTON_AUXBROWSE, OnButtonAuxbrowse)
	ON_BN_CLICKED(IDC_BUTTON_TARGETBROWSE, OnButtonTargetbrowse)
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_BUTTON_GENERATE, OnButtonGenerate)
	ON_EN_CHANGE(IDC_EDIT_AUXFILE, OnChangeEditAuxfile)
	ON_EN_CHANGE(IDC_EDIT_TARGETFILE, OnChangeEditTargetfile)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_ANCHOR_MAP(CGenFromAuxDialog)
	ANCHOR_MAP_ENTRY(ID_BUTTON_GENERATE, ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDCANCEL, ANF_BOTTOM)
	ANCHOR_MAP_ENTRY(IDC_EDIT_AUXFILE, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_TARGETFILE, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_AUXBROWSE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_BUTTON_TARGETBROWSE, ANF_TOP | ANF_RIGHT)
	ANCHOR_MAP_ENTRY(IDC_CHECK_REQFIELDS, ANF_TOP | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(IDC_EDIT_LOG, ANF_TOP | ANF_BOTTOM | ANF_RIGHT | ANF_LEFT)
	ANCHOR_MAP_ENTRY(NULL, ANF_AUTOMATIC)
END_ANCHOR_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CGenFromAuxDialog 

void CGenFromAuxDialog::OnButtonAuxbrowse() 
{
	CString f;
	CString fn;
	m_editAuxFile.GetWindowText(fn);
	f.Format(_T("%s|%s||"), AfxLoadString(IDS_STRING_AUXFILTER), AfxLoadString(IDS_STRING_ALLFILTER));
	CFileDialogEx dlg(TRUE, AfxLoadString(IDS_STRING_EXT_AUX), fn, OFN_HIDEREADONLY | OFN_ENABLESIZING, f, this);	
	if (dlg.DoModal() == IDOK) {
		m_editAuxFile.SetWindowText(dlg.GetPathName());
	}
}

void CGenFromAuxDialog::OnButtonTargetbrowse() 
{
	CString f;
	CString fn;
	m_editTargetFile.GetWindowText(fn);
	f.Format(_T("%s|%s||"), AfxLoadString(IDS_STRING_BIBFILTER), AfxLoadString(IDS_STRING_ALLFILTER));
	CFileDialogEx dlg(FALSE, AfxLoadString(IDS_STRING_EXT_BIB), fn, OFN_HIDEREADONLY | OFN_ENABLESIZING, f, this);	
	if (dlg.DoModal() == IDOK) {
		m_editTargetFile.SetWindowText(dlg.GetPathName());
	}
}

BOOL CGenFromAuxDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HICON icon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(icon, FALSE);
	InitAnchors(ANIF_SIZEGRIP);
	m_btnReqFields.SetCheck(AfxGetApp()->GetProfileInt(SETTINGS_KEY, _T("ReqFieldsOnly"), 0));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CGenFromAuxDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r;
	GetWindowRect(&r);
	HandleAnchors(r);	
}

void CGenFromAuxDialog::OnButtonGenerate() 
{
	DWORD warnings = 0;
	CWaitCursor wait;
	CString str;
	m_editLog.SetWindowText(NULL);
	CString fn;
	CAuxParser AuxParser((DWORD)this);
	m_editAuxFile.GetWindowText(fn);
	AuxParser.m_AuxFile = fn;
	CBibItem * newitem;
	BOOL reqonly = m_btnReqFields.GetCheck() == 1;

	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, curdir);
	int bsp = fn.ReverseFind(_T('\\'));
	if (bsp != -1)
		SetCurrentDirectory(fn.Left(bsp));

	AuxParser.Parse(LogProc);
	if (AuxParser.m_BibData.IsEmpty()) {
		warnings++;
		str.Format(AfxLoadString(IDS_STRING_WARNING), AfxLoadString(IDS_STRING_NOBIBDATA));
		AddLog(str);
	}
	if (AuxParser.m_BibStyle.IsEmpty()) {
		warnings++;
		str.Format(AfxLoadString(IDS_STRING_WARNING), AfxLoadString(IDS_STRING_NOSTYLE));
		AddLog(str);
	}

	CBibFile target;
	DWORD pscount = 0;
	if (!AuxParser.m_AllItems) {
		CBibItem* item;

		// Add preambles and strings
		POSITION p = m_BibList->GetHeadPosition();
		while (p) {
			item = (CBibItem*)m_BibList->GetNext(p);
			if (item->IsType(STR_STRING) || item->IsType(STR_PREAMBLE)) {
				newitem = target.New();
				newitem->Assign(item);
				pscount++;
			}
		}

		// Add extracted items
		p = AuxParser.m_Keys.GetHeadPosition();
		while (p) {
			CString key = AuxParser.m_Keys.GetNext(p);
			item = m_BibList->Find(key);
			if (item) {
				if (!target.Find(item->GetKey())) {
					newitem = target.New();
					newitem->Assign(item);
					RemoveNotRequiredFields(newitem, reqonly);
				}
				// It it has a crossref field we need also the referenced
				CField* cr = item->Find(STR_CROSSREF);
				if (cr) {
					if (!target.Find(cr->GetValue())) {
						item = m_BibList->Find(cr->GetValue());
						if (item) {
							newitem = target.New();
							newitem->Assign(item);
							RemoveNotRequiredFields(newitem, reqonly);
						}
					}
				}
			} else {
				warnings++;
				str.Format(AfxLoadString(IDS_STRING_KEYNOTFOUND), key);
				AddLog(str);
			}
		}	
	} else {
		// \citation{*} means all items
		target.Assign(m_BibList);
	}

	m_editTargetFile.GetWindowText(fn);
	if (target.GetCount() > 0) {
		CFileException ex;
		CFile f;
		if (f.Open(fn, CFile::modeWrite | CFile::shareExclusive | CFile::modeCreate, &ex)) {
			target.Save(&f);
			f.Close();
			str.Format(AfxLoadString(IDS_STRING_AUXSUCC), fn, target.GetCount() - pscount);
			AddLog(str);
		} else
			ex.ReportError();
	}
	SetCurrentDirectory(curdir);

	str.Format(AfxLoadString(IDS_STRING_AUXSTAT), AuxParser.m_Errors, AuxParser.m_Warnings + warnings);
	AddLog(str);
}

BOOL CALLBACK CGenFromAuxDialog::LogProc(CString fn, DWORD pOwner)
{
	CGenFromAuxDialog* dlg = (CGenFromAuxDialog*)pOwner;
	if (dlg) {
		dlg->AddLog(fn);
	}
	return TRUE;
}

void CGenFromAuxDialog::AddLog(CString txt)
{
	int l = m_editLog.GetWindowTextLength();
	m_editLog.SetSel(l, l);
	m_editLog.ReplaceSel(txt + NL);
}

void CGenFromAuxDialog::OnChangeEditAuxfile() 
{
	m_btnGenerate.EnableWindow(m_editAuxFile.GetWindowTextLength() > 0 && m_editTargetFile.GetWindowTextLength() > 0);
}

void CGenFromAuxDialog::OnChangeEditTargetfile() 
{
	OnChangeEditAuxfile();
}

void CGenFromAuxDialog::RemoveNotRequiredFields(CBibItem *item, BOOL remove)
{
	if (!remove)
		return;

	CBibDef* def = ((CBibedtApp*)AfxGetApp())->m_BibDef;
	CString type = item->GetType();
	POSITION p = item->GetTailPosition();
	POSITION cur;
	REQUIRED r;
	while (p) {
		cur = p;
		CField* f = (CField*)item->GetPrev(p);
		ASSERT(f);
		CString field = f->GetName();
		r = def->GetRequired(type, field);
		if (r == R_UNKNOWN || r == R_IGNORED) {
			item->RemoveAt(cur);
			delete f;
		}
	}
}

void CGenFromAuxDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	AfxGetApp()->WriteProfileInt(SETTINGS_KEY, _T("ReqFieldsOnly"), m_btnReqFields.GetCheck());		
}
