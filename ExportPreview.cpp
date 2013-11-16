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

  $Id: ExportPreview.cpp,v 1.10 2006/07/19 20:32:39 stievie Exp $
*/

// ExportPreview.cpp: Implementierung der Klasse CExportPreview.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "ExportPreview.h"
#include "Options.h"
#include "BibList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExportPreview::CExportPreview()
{

}

CExportPreview::~CExportPreview()
{

}

void CExportPreview::Load(xmlNodePtr node)
{
	UNUSED_ALWAYS(node);
	COptions* pOP = ((CBibedtApp*)AfxGetApp())->m_Options;
	m_Name = _T("Preview");
	m_StyleFile = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Preview.Export.StyleFile"), pOP->m_DefPreviewXSL);
	m_Encoding = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Preview.Export.Encoding"), _T("UTF-8"));
	m_Ext = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Preview.Export.Ext"), _T(".html"));
	m_Filter = AfxGetApp()->GetProfileString(SETTINGS_KEY, _T("Preview.Export.Filter"), _T("HTML files (*.html)|*.html"));	
	m_Iconv.SetTargetCharset(m_Encoding);
}

void CExportPreview::Save(xmlNodePtr node)
{
	UNUSED_ALWAYS(node);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Preview.Export.StyleFile"), m_StyleFile);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Preview.Export.Encoding"), m_Encoding);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Preview.Export.Ext"), m_Ext);
	AfxGetApp()->WriteProfileString(SETTINGS_KEY, _T("Preview.Export.Filter"), m_Filter);
}

CString CExportPreview::GetSource()
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
		f.Open(_T("C:\\TEMP\\bibedt_test.html"), CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		f.Write(str, str.GetLength());
		f.Close();
	} catch (...) {	}
#endif
		return str;
	} else
		return _T("");
}

CString CExportPreview::EncodeString(CString str, BOOL rs)
{
//	return CExportXML::EncodeString(str, rs);

	// encodes &, < and >
//	CString ret = m_Coding->Encode(str);
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

CExport* CExportPreview::Clone()
{
	CExport* res = new CExportPreview();
	res->Assign(this);
	return res;
}
