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

  $Id: ExportXML.cpp,v 1.29 2006/08/13 12:19:50 stievie Exp $
*/

// ExportXML.cpp: Implementierung der Klasse CExportXML.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "ExportXML.h"
#include "CodingXML.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExportXML::CExportXML()
{
	m_Name = "XML";
	m_LinkStyle = TRUE;
	m_Encoding = "UTF-8";
	m_Iconv.SetSourceCharset("ISO88591");
	m_Iconv.SetTargetCharset(m_Encoding);
}

CExportXML::~CExportXML()
{
}

CString CExportXML::GetSource()
{
	return GetHeader() + GetBody() + GetFooter();
}

CString CExportXML::GetExt()
{
	return ".xml";
}

CString CExportXML::GetFilter()
{
	return AfxLoadString(IDS_STRING_XMLFILTER);
}

void CExportXML::DoExport(CString filename)
{
	CFile f;
	CString str;
	try {
		f.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		str = GetSource();
		f.Write(str, str.GetLength());
		f.Close();
	} catch (CFileException ex) {
		ex.ReportError();
	}
}

CString CExportXML::GetItemSource(CBibItem* item)
{
	xString* str = xsNew();
	GetItemSource(str, item);
	CString res(xsValue(str));
	xsDelete(str);
	return res;
}

void CExportXML::GetItemSource(xString *const str, CBibItem* item)
{
	Load();

	CString name;

	CString s;
	CBibDef* def = GetBibDef();
	xsCatS(str, _T("  <bibitem>\r\n"));

	xsCatS(str, _T("    <type>"));
	s = item->GetType();
	s.MakeLower();
	xsCatS(str, s);
	xsCatS(str, _T("</type>\r\n"));
	xsCatS(str, _T("    <key>"));
	xsCatS(str, EncodeString(item->GetKey(), TRUE));
	xsCatS(str, _T("</key>\r\n"));
	CField *f;
	POSITION p = item->GetHeadPosition();
	while (p) {
		f = (CField*)item->GetNext(p);
		ASSERT(f);
		if (f->GetValue().IsEmpty())
			// Don't export empty fields
			continue;

		name = f->GetName();
		name.MakeLower();
		xsCatS(str, _T("    <"));
		xsCatS(str, name);
		xsPut(str, _T('>'));

		CString val = RemoveGarbage(f->GetExpandedValue(item->GetOwner()));
		xsCatS(str, EncodeString(val, !def || def->GetConvField(f->GetName())));

		xsCatS(str, _T("</"));
		xsCatS(str, name);
		xsCatS(str, _T(">\r\n"));
	}
	// Resolve crossref
	CFieldList *refed = item->GetCorssRefed();
	if (refed != NULL) {
		p = refed->GetHeadPosition();
		while (p) {
			f = (CField*)item->GetNext(p);
			ASSERT(f);
			if (f->GetValue().IsEmpty() || item->Find(f->GetName()) != NULL)
				// Don't export empty fields or fields that already exist
				continue;

			name = f->GetName();
			name.MakeLower();
			xsCatS(str, _T("    <"));
			xsCatS(str, name);
			xsPut(str, _T('>'));

			CString val = RemoveGarbage(f->GetExpandedValue(item->GetOwner()));
			xsCatS(str, EncodeString(val, !def || def->GetConvField(f->GetName())));

			xsCatS(str, _T("</"));
			xsCatS(str, name);
			xsCatS(str, _T(">\r\n"));
		}
	}

	xsCatS(str, _T("  </bibitem>"));

	xsTerminate(str);
}


CString CExportXML::GetHeader()
{
	CString ret;
	if (m_Encoding.CompareNoCase(_T("RTF")) == 0 || m_Encoding.CompareNoCase(_T("TeX")) == 0 || m_Encoding.CompareNoCase(_T("HTML")) == 0)
		ret.Format(XML_HEAD, XML_VER, _T("ISO-8859-1"));
	else
		ret.Format(XML_HEAD, XML_VER, m_Encoding);

	ret += NL;
	ret += GetDocType();
	CString str;
	if (m_LinkStyle && !m_StyleFile.IsEmpty()) {
		str.Format(_T("<?xml-stylesheet type=\"text/xsl\" href=\"%s\"?>\r\n"), EncodeFilename(m_StyleFile));
		ret += str;
	}
#ifdef _DEBUG
	else if (!m_StyleFile.IsEmpty()) {
		str.Format(_T("<?xml-stylesheet type=\"text/xsl\" href=\"%s\"?>\r\n"), EncodeFilename(m_StyleFile));
		ret += str;
	}
#endif

	str.Format(_T("<%s>\r\n"), XML_ROOTNAME);
	ret += NL + str;
	return ret;
}

CString CExportXML::GetFooter()
{
	CString str;
	str.Format(_T("</%s>\r\n"), XML_ROOTNAME);
	return str;
}

CString CExportXML::GetBody()
{
	xString* res = xsNew();

	CString str;

	DWORD counter = 0;
	POSITION h = m_BibList->GetHeadPosition();

	while (h) {
		CBibItem *bitem = (CBibItem*)m_BibList->GetNext(h);
		if (bitem->IsType(STR_STRING) || bitem->IsType(STR_PREAMBLE) || bitem->IsType(STR_COMMENT))
			continue;

		counter++;
		GetItemSource(res, bitem);
		xsCatS(res, NL);
	}
	xsTerminate(res);
	CString r(xsValue(res));
	xsDelete(res);
	return r;
}

void CExportXML::Load()
{
	if (!m_Loaded) {
		COptions *o = ((CBibedtApp*)AfxGetApp())->m_Options;
		if (m_StyleFile.IsEmpty())
			m_StyleFile = o->m_XSLFilename;

		m_Loaded = TRUE;
	}
}

void CExportXML::Assign(CExport *src)
{
	CExport::Assign(src);
	CExportXML* exp = dynamic_cast<CExportXML*>(src);
	if (exp) {
		m_Encoding = exp->m_Encoding;
		m_StyleFile = exp->m_StyleFile;
	}
}

CExport* CExportXML::Clone()
{
	CExport* res = new CExportXML();
	res->Assign(this);
	return res;
}

CString CExportXML::EncodeString(CString str, BOOL rs)
{
	// encodes &, < and >
//	CString ret = m_Coding->Encode(str);
	CString ret = str;
	ret.Replace(_T("&"), _T("&#x26;"));
	ret.Replace(_T("<"), _T("&#x3C;"));
	ret.Replace(_T(">"), _T("&#x3E;"));
	if (rs) {
		// Replace some common characters
		ret.Replace(_T("---"), _T("&mdash;"));
		ret.Replace(_T("--"), _T("&ndash;"));
		ret.Replace(_T("~"), _T("&nbsp;"));
		ret.Replace(_T("\\,"), _T("&thinsp;"));
		ret.Replace(_T("\"`"), _T("&sdquo;"));
		ret.Replace(_T("\"'"), _T("&ldquo;"));
		ret.Replace(_T("``"), _T("&rdquo;"));
		ret.Replace(_T("''"), _T("&ldquo;"));
		ret.Replace(_T("`"), _T("&lsquo;"));
		ret.Replace(_T("'"), _T("&rsquo;"));
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

CString CExportXML::GetDocType()
{
	return XML_DOCTYPE;
}
