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

  $Id: OptionsFilePage.h,v 1.10 2006/05/20 18:09:43 stievie Exp $
*/

#if !defined(AFX_OPTIONSFILEPAGE_H__DA04B75D_803A_454A_8ABC_E6791101DC62__INCLUDED_)
#define AFX_OPTIONSFILEPAGE_H__DA04B75D_803A_454A_8ABC_E6791101DC62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsFilePage.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld COptionsFilePage 

class COptionsFilePage : public CPropertyPage
{
	DECLARE_DYNCREATE(COptionsFilePage)

// Konstruktion
public:
	COptions * m_Options;
	COptionsFilePage();
	~COptionsFilePage();

// Dialogfelddaten
	//{{AFX_DATA(COptionsFilePage)
	enum { IDD = IDD_OPTIONSPAGE_FILES };
	CEdit	m_editConfigDir;
	CString	m_strConfigDir;
	//}}AFX_DATA


// Überschreibungen
	// Der Klassen-Assistent generiert virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(COptionsFilePage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(COptionsFilePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEditConfigdir();
	afx_msg void OnButtonConfigdirBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	static int __stdcall BrowseProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_OPTIONSFILEPAGE_H__DA04B75D_803A_454A_8ABC_E6791101DC62__INCLUDED_
