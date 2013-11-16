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

  $Id: AuxParser.h,v 1.8 2005/10/10 00:18:45 stievie Exp $
*/

// AuxParser.h: Schnittstelle für die Klasse CAuxParser.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUXPARSER_H__0F6A188E_5E27_419E_8226_48BBAB42D067__INCLUDED_)
#define AFX_AUXPARSER_H__0F6A188E_5E27_419E_8226_48BBAB42D067__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibReader.h"

typedef BOOL (CALLBACK *PFNLOGPROC)(CString, DWORD);

enum CMD_TYPE {
	CT_UNKNOWN, CT_BIBCITE, CT_INPUT, CT_BIBDATA, CT_BIBSTYLE, CT_CITATION
};

/**
 * \class CAuxParser
 * \brief Parser for .aux files.
 *
 * Also parses all \c \\\@input ed files.
 *
 * \author Stefan Ascher
 */
class CAuxParser  
{
public:
	BOOL m_AllItems;			   /**< Is \c TRUE when a \c \\citation{*} has been found. */
	void Warning(CString msg);	   /**< Yield a warning. */
	CString m_BibStyle;			   /**< The bibstyle file. */
	CString m_BibData;			   /**< The database file(s). */
	DWORD m_Errors;				   /**< Number of errors. */
	DWORD m_Warnings;			   /**< Number of warnings. */
	CStringList m_Keys;			   /**< The list of found keys. */
	DWORD m_Owner;				   /**< The owner of this class with the callback procedure. */
	PFNLOGPROC m_LogProc;		   /**< Pointer to a callback procedure. */
	void Parse(PFNLOGPROC LogProc);
	CString m_AuxFile;			   /**< The name of the file to parse. */
	CAuxParser(DWORD owner);
	virtual ~CAuxParser();

protected:
	void AddLog(CString msg);
	void ParseFile(CBibReader* reader);
	static CMD_TYPE GetCmdType(xString* token);
};

#endif // !defined(AFX_AUXPARSER_H__0F6A188E_5E27_419E_8226_48BBAB42D067__INCLUDED_)
