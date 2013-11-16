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

  $Id: AuxParser.cpp,v 1.12 2006/08/07 18:39:15 stievie Exp $
*/

// AuxParser.cpp: Implementierung der Klasse CAuxParser.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bibedt.h"
#include "AuxParser.h"
#include "Globals.h"
#include "xString.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

/**
 * \brief Constructor.
 * \param owner A Pointer to the owning object.
 */
CAuxParser::CAuxParser(DWORD owner)
{
	ASSERT(owner);
	m_Owner = owner;
	m_Warnings = 0;
	m_AllItems = FALSE;
}

CAuxParser::~CAuxParser()
{

}

/**
 * \brief Start parsing.
 * \param LogProc A Pointer to the logging procedure.
 */
void CAuxParser::Parse(PFNLOGPROC LogProc)
{
	m_LogProc = LogProc;
	m_Errors = 0;
	m_BibData.Empty();
	m_BibStyle.Empty();
	CString str;
	if (!m_AuxFile.IsEmpty()) {
		CFile f;
		CFileException ex;
		if (f.Open(m_AuxFile, CFile::modeRead | CFile::shareDenyWrite, &ex)) {
			str.Format(AfxLoadString(IDS_STRING_PARSING), m_AuxFile);
			AddLog(str);
			CBibReader reader(&f);
			ParseFile(&reader);
			f.Close();
		} else {
			m_Errors++;
			TCHAR msg[MAX_PATH];
			ex.GetErrorMessage(msg, MAX_PATH);
			str.Format(AfxLoadString(IDS_STRING_ERROR), msg);
			AddLog(str);
		}
	}
}

CMD_TYPE CAuxParser::GetCmdType(xString* token)
{
	if (xsCompareS(token, _T("bibcite")) == 0) {
		return CT_BIBCITE;
	} else if (xsCompareS(token, _T("@input")) == 0) {
		return CT_INPUT;
	} else if (xsCompareS(token, _T("bibdata")) == 0) {
		return CT_BIBDATA;
	} else if (xsCompareS(token, _T("bibstyle")) == 0) {
		return CT_BIBSTYLE;
	} else if (xsCompareS(token, _T("citation")) == 0) {
		return CT_CITATION;
	}
	return CT_UNKNOWN;
}

/**
 * \brief The actual parsing procedure.
 * \param reader A pointer to a CBibReader object with the contents of the .aux file.
 */
void CAuxParser::ParseFile(CBibReader* reader)
{
	_TUCHAR c;
	xString* cmd = xsNew();
	xString* key = xsNew();
	CString str;
	BOOL escape = FALSE;
	BOOL iscite = FALSE;
	BOOL isinput = FALSE;
	BOOL incmd = FALSE;
	BOOL bibdata = FALSE;
	BOOL bibstyle = FALSE;
	BOOL citation = FALSE;
	while (reader->Read(&c, sizeof(_TUCHAR))) {
		switch (c) {
			case _T('\\'):
				if (!escape)
					incmd = TRUE;
				escape = !escape;
				xsClear(cmd);
				break;
			case _T('{'):
				xsTerminate(cmd);
				switch (GetCmdType(cmd)) {
				case CT_BIBCITE:
					iscite = TRUE;
					break;
				case CT_INPUT:
					isinput = TRUE;
					break;
				case CT_BIBDATA:
					bibdata = TRUE;
					break;
				case CT_BIBSTYLE:
					bibstyle = TRUE;
					break;
				case CT_CITATION: 
					citation = TRUE;
					break;
				}
				incmd = FALSE;
				xsClear(cmd);
				break;
			case _T('}'):
				if (iscite) {
					xsTerminate(key);
					m_Keys.AddTail(CString(xsValue(key)));
					str.Format(AfxLoadString(IDS_STRING_FOUNDKEY), xsValue(key));
					AddLog(str);
					xsClear(key);
					iscite = FALSE;
				} else if (citation) {
					xsTerminate(key);
					if (xsCompareS(key, _T("*")) == 0) {
						m_AllItems = TRUE;
						str.Format(AfxLoadString(IDS_STRING_FOUNDKEY), xsValue(key));
						AddLog(str);
					}
					xsClear(key);
					citation = FALSE;
				} else if (isinput) {
					// Recursively parse inputed files and search for \citation{*}
					CAuxParser* parser = new CAuxParser(m_Owner);
					xsTerminate(key);
					parser->m_AuxFile = CString(xsValue(key));
					parser->Parse(m_LogProc);
					m_Keys.AddTail(&parser->m_Keys);
					m_AllItems |= parser->m_AllItems;
					m_Warnings += parser->m_Warnings;
					m_Errors += parser->m_Errors;
					delete parser;
					xsClear(key);
					isinput = FALSE;
				} else if (bibdata) {
					xsTerminate(key);
					m_BibData = CString(xsValue(key));
					str.Format(AfxLoadString(IDS_STRING_BIBDATA), xsValue(key));
					AddLog(str);
					xsClear(key);
					bibdata = FALSE;
				} else if (bibstyle) {
					xsTerminate(key);
					m_BibStyle = CString(xsValue(key));
					str.Format(AfxLoadString(IDS_STRING_BIBSTYLE), xsValue(key));
					AddLog(str);
					xsClear(key);
					bibstyle = FALSE;
				}
				incmd = FALSE;
				break;
			case _T('\r'):
			case _T('\n'):
			case _T('\t'):
			case _T(' '):
				break;
			default:
				if (iscite || isinput || bibdata || bibstyle || citation)
					xsPut(key, c);
				else
					xsPut(cmd, c);
		}
	}
	xsDelete(cmd);
	xsDelete(key);
}

/**
 * \brief Add a log message.
 * \param msg The message string.
 */
void CAuxParser::AddLog(CString msg)
{
	if (m_LogProc)
		m_LogProc(msg, m_Owner);
}

/**
 * \brief Add a warning.
 * \param msg The warning message.
 */
void CAuxParser::Warning(CString msg)
{
	m_Warnings++;
	CString str;
	str.Format(AfxLoadString(IDS_STRING_WARNING), msg);
	AddLog(str);
}
