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

  $Id: ExportBib.cpp,v 1.12 2006/07/08 11:23:44 stievie Exp $
*/

// ExportBib.cpp: Implementierung der Klasse CExportBib.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "ExportBib.h"
#include "BibFile.h"
#include "Globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExportBib::CExportBib()
{
	m_Name = "BibTeX";
}

CExportBib::~CExportBib()
{

}

void CExportBib::DoExport(CString filename)
{
	CFile f;
	try {
		f.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive); 
		m_BibList->Save(&f);
		f.Close();
	} catch (CFileException ex) {
		ex.ReportError();
	}
}

CString CExportBib::GetFilter()
{
	return AfxLoadString(IDS_STRING_BIBFILTER);
}

CString CExportBib::GetExt()
{
	return AfxLoadString(IDS_STRING_EXT_BIB);
}

CString CExportBib::GetItemSource(CBibItem* item)
{
	return item->GetSource();
}

CString CExportBib::GetSource()
{
	return m_BibList->GetSource();
}

/**
 * The caller is responsible to delete the object
 */
CExport* CExportBib::Clone()
{
	CExport* res = new CExportBib();
	res->Assign(this);
	return res;
}

