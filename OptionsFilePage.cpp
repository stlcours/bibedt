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

  $Id: OptionsFilePage.cpp,v 1.11 2006/06/06 18:52:18 stievie Exp $
*/

// OptionsFilePage.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "OptionsFilePage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Eigenschaftenseite COptionsFilePage 

IMPLEMENT_DYNCREATE(COptionsFilePage, CPropertyPage)

COptionsFilePage::COptionsFilePage() : CPropertyPage(COptionsFilePage::IDD)
{
	//{{AFX_DATA_INIT(COptionsFilePage)
	m_strConfigDir = _T("");
	//}}AFX_DATA_INIT
}

COptionsFilePage::~COptionsFilePage()
{
}

void COptionsFilePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsFilePage)
	DDX_Control(pDX, IDC_EDIT_CONFIGDIR, m_editConfigDir);
	DDX_Text(pDX, IDC_EDIT_CONFIGDIR, m_strConfigDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionsFilePage, CPropertyPage)
	//{{AFX_MSG_MAP(COptionsFilePage)
	ON_EN_CHANGE(IDC_EDIT_CONFIGDIR, OnChangeEditConfigdir)
	ON_BN_CLICKED(IDC_BUTTON_CONFIGDIR_BROWSE, OnButtonConfigdirBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten COptionsFilePage 

BOOL COptionsFilePage::OnApply() 
{
	m_Options->m_ConfigDir = m_strConfigDir;
	m_Options->UpdateFiles();

	return CPropertyPage::OnApply();
}

BOOL COptionsFilePage::OnInitDialog() 
{
	m_strConfigDir = m_Options->m_ConfigDir;

	CPropertyPage::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void COptionsFilePage::OnChangeEditConfigdir() 
{
	SetModified();
}

void COptionsFilePage::OnButtonConfigdirBrowse() 
{
	LPITEMIDLIST pidl;
	BROWSEINFO bi;
	TCHAR buffer[MAX_PATH] = {_T('\0')};
	CString dir;
	memset(&bi, 0, sizeof(bi));
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	if (IsXP())
		bi.ulFlags |= BIF_USENEWUI;
	bi.hwndOwner = this->m_hWnd;
	bi.lpfn = BrowseProc;
	m_editConfigDir.GetWindowText(dir);
	bi.lParam = (LPARAM)(LPCTSTR)dir;

	::CoInitialize(NULL);

	pidl = ::SHBrowseForFolder(&bi);
	if (pidl != NULL) {
		if (::SHGetPathFromIDList(pidl, buffer) != 0)
			m_editConfigDir.SetWindowText(buffer);
		CoTaskMemFree(pidl);		
	}

	::CoUninitialize();
}

int __stdcall COptionsFilePage::BrowseProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg) {
	case BFFM_INITIALIZED:
		::SendMessage(hwnd, BFFM_SETSELECTION, 1, lpData);
		break;
	}

	return 0;
}
