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

  $Id: FindDupOptionsDialog.cpp,v 1.1 2005/09/02 20:08:22 stievie Exp $
*/

// FindDupOptionsDialog.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "bibedt.h"
#include "FindDupOptionsDialog.h"
#include "BibItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CFindDupOptionsDialog 


CFindDupOptionsDialog::CFindDupOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDupOptionsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDupOptionsDialog)
	m_CaseSens = FALSE;
	m_Exact = TRUE;
	//}}AFX_DATA_INIT
}


void CFindDupOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDupOptionsDialog)
	DDX_Control(pDX, IDC_COMBO_FIELDS, m_cboFields);
	DDX_Check(pDX, IDC_CHECK_CASESENS, m_CaseSens);
	DDX_Check(pDX, IDC_CHECK_EXACT, m_Exact);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindDupOptionsDialog, CDialog)
	//{{AFX_MSG_MAP(CFindDupOptionsDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen für Nachrichten CFindDupOptionsDialog 

BOOL CFindDupOptionsDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	ASSERT(m_BibList);
	CStringList fields;
	m_BibList->GetAllFieldNames(&fields);
	int ki = m_cboFields.AddString(STR_KEY);
	POSITION p = fields.GetHeadPosition();
	while (p) {
		m_cboFields.AddString(fields.GetNext(p));
	}
	if (!m_Fields.IsEmpty()) {
		if (m_cboFields.SelectString(0, m_Fields) == CB_ERR) {
			int i = m_cboFields.AddString(m_Fields);
			m_cboFields.SetCurSel(i);
		}
	} else
		m_cboFields.SetCurSel(ki);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}

void CFindDupOptionsDialog::OnOK()
{
	m_cboFields.GetWindowText(m_Fields);
	CDialog::OnOK();
}
