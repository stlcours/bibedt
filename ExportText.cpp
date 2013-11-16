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

  $Id: ExportText.cpp,v 1.22 2006/07/29 11:33:14 stievie Exp $
*/

// ExportText.cpp: Implementierung der Klasse CExportText.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "ExportText.h"
#include "Globals.h"
#include "BibList.h"
#include "BibItem.h"
#include "Field.h"
#include "xString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CExportText::CExportText()
{
	m_Name = _T("Text");
}

CExportText::~CExportText()
{

}

/**
 * \brief Does the export.
 *
 * Builds the text and saves it as file.
 * \param filename The filename for the file.
 */
void CExportText::DoExport(CString filename)
{
	CFile f;
	CString str;
	try {
		f.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive);
		str = GetSource() + NL;
		f.Write(str, str.GetLength());
		f.Close();
	} catch (CFileException ex) {
		ex.ReportError();
	}
}

/**
 * \brief Returns the filter string for CFileDialog.
 */
CString CExportText::GetFilter()
{
	return AfxLoadString(IDS_STRING_TXTFILTER);
}

/**
 * \brief Return the extension for CFileDialog.
 */
CString CExportText::GetExt()
{
	return ".txt";
}

CString CExportText::GetItemSource(CBibItem* item)
{
	return item->GetPrettyString();
}

/**
 * \brief Builds the resulting string.
 */
CString CExportText::GetSource()
{
	// It does not interpret TeX expressions!

	xString* res = xsNew();

	CString str;
	DWORD count = 0;
	
	CBibDef *def = GetBibDef();
	BOOL printnum = def->GetBoolOption(OP_PRINT_NUM, TRUE);
	CString numformat = def->GetStrOption(OP_NUM_FORMAT, _T("[%d] "));
	POSITION h = m_BibList->GetHeadPosition();
	while (h) {
		CBibItem *bitem = (CBibItem*)m_BibList->GetNext(h);
		if (bitem->IsType(STR_STRING) || bitem->IsType(STR_PREAMBLE) || bitem->IsType(STR_COMMENT))
			continue;

		count++;
		if (printnum)
			str.Format(numformat + _T("%s\r\n"), count, bitem->GetPrettyString());
		else
			str.Format(_T("%s\r\n"), bitem->GetPrettyString());

		DWORD pos = 0;
		_TUCHAR c;
		_TUCHAR prev = 0;
		str.Replace(_T("\\,"), _T(" "));

		for (int i = 0; i < str.GetLength(); i++) {
			c = str.GetAt(i);
			pos++;
			if (pos >= m_LineLength-5 && (c == _T(' ') || (c == _T('-') && prev != _T('-')) || c == _T('~')) && i < str.GetLength()-1) {
				if (c != _T(' ') || c == _T('~'))
					// don't write a space at the end of the line
					xsPut(res, c);
				xsCatS(res, _T("\r\n  "));
				pos = 4;
			} else {
				if (c != _T('~'))
					xsPut(res, c);
				else
					xsPut(res, _T(' '));
			}
			prev = c;
		}
	}
	xsTerminate(res);
	CString r(xsValue(res));
	xsDelete(res);
	return r;
}

CExport* CExportText::Clone()
{
	CExport* res = new CExportText();
	res->Assign(this);
	return res;
}
