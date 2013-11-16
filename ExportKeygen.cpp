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

  $Id: ExportKeygen.cpp,v 1.1 2006/08/14 07:57:24 stievie Exp $
*/

// ExportKeygen.cpp: Implementierung der Klasse CExportKeygen.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "Options.h"
#include "ExportKeygen.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExportKeygen::CExportKeygen()
{

}

CExportKeygen::~CExportKeygen()
{

}

void CExportKeygen::Load(xmlNodePtr node)
{
	UNUSED_ALWAYS(node);
	COptions* pOP = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_Name = _T("Keygeneration");
	m_StyleFile = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Keygen.Export.StyleFile"), pOP->m_KeygenXSL);
	m_Encoding = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Keygen.Export.Encoding"), _T("ISO-8859-1"));
	m_Ext = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Keygen.Export.Ext"), _T(".txt"));
	m_Filter = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Keygen.Export.Filter"), _T("Textfiles (*.txt)|*.txt"));	
	m_Iconv.SetTargetCharset(m_Encoding);
}

void CExportKeygen::Save(xmlNodePtr node)
{
	UNUSED_ALWAYS(node);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Keygen.Export.StyleFile"), m_StyleFile);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Keygen.Export.Encoding"), m_Encoding);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Keygen.Export.Ext"), m_Ext);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Keygen.Export.Filter"), m_Filter);
}

CString CExportKeygen::GetSource()
{
	if (m_Item) {
		// Brrrr, well the whole exporter stuff is a hack!
		CBibFile *lst = new CBibFile;
		CBibFile *old = m_BibList;
		lst->AddTail((CObject*)m_Item);
		m_BibList = lst;
		CString str = CExportGeneric::GetSource();
		lst->RemoveAll();
		delete lst;
		m_BibList = old;
#ifdef _DEBUG
	CFile f;
	try {
		f.Open(_T("C:\\TEMP\\bibedt_test.txt"), CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		f.Write(str, str.GetLength());
		f.Close();
	} catch (...) {	}
#endif
		return str;
	} else
		return _T("");
}

CString CExportKeygen::EncodeString(CString str, BOOL rs)
{
	// encodes &, < and >
	CString ret = str;
	ret.Replace(_T("&"), _T("&#x26;"));
	ret.Replace(_T("<"), _T("&#x3C;"));
	ret.Replace(_T(">"), _T("&#x3E;"));
	if (rs) {
		// Replace some common characters
		ret.Replace(_T("---"), _T("&#x97;"));
		ret.Replace(_T("--"), _T("&#x96;"));
		ret.Replace(_T("~"), _T(" "));
		ret.Replace(_T("\\,"), _T(" "));
		ret.Replace(_T("\"`"), _T("\""));
		ret.Replace(_T("\"'"), _T("\""));
		ret.Replace(_T("``"), _T("\""));
		ret.Replace(_T("''"), _T("\""));
		ret.Replace(_T("`"), _T("'"));
		ret.Replace(_T("'"), _T("'"));
		// TeX et al.
		ret.Replace(_T("\\TeX "), _T("TeX"));
		ret.Replace(_T("\\TeX"), _T("TeX"));
		ret.Replace(_T("\\LaTeX"), _T("LaTeX"));
		ret.Replace(_T("\\BibTeX"), _T("BibTeX"));
		ret.Replace(_T("\\MF"), _T("METAFONT"));
		ret.Replace(_T("\\MP"), _T("METAPOST"));
		ret.Replace(_T("\\ "), _T(" "));
		ret.Replace(_T("{}"), _T(""));
	}

	return m_Iconv.Convert(ret);
}

CExport* CExportKeygen::Clone()
{
	CExport* res = new CExportKeygen();
	res->Assign(this);
	return res;
}
