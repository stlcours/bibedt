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

  $Id: BibDef.h,v 1.15 2006/06/06 18:52:18 stievie Exp $
*/

// BibDef.h: Schnittstelle für die Klasse CBibDef.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBDEF_H__8F9B5979_33B3_411C_8DF2_F6EB4A87CB93__INCLUDED_)
#define AFX_BIBDEF_H__8F9B5979_33B3_411C_8DF2_F6EB4A87CB93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BibFile.h"

// Option field names
const TCHAR OP_PRINT_NUM[] = _T("print_number");
const TCHAR OP_NUM_FORMAT[] = _T("number_format");

enum REQUIRED
{
	R_UNKNOWN,
	R_REQUIRED,
	R_OPTIONAL,
	R_IGNORED
};

// Fonst style flags
#define FS_BOLD      1 << 0
#define FS_ITALIC    1 << 1
#define FS_UNDERLINE 1 << 2
#define FS_STRIKE    1 << 3

/**
 * \brief The template file
 *
 * This class loads the template file.
 * This file may also provide some options.
 */
class CBibDef : public CBibFile  
{
public:
	REQUIRED IsRequired(CBibItem* item, CField* field);
	DWORD GetRequiredFields(CString type, CStringList* lst);
	BOOL GetConvField(CString name);
	DWORD GetFontStyle(CString type, CString field);
	int GetIntOption(CString name, int def);
	CString GetStrOption(CString name, CString def);
	BOOL GetBoolOption(CString name, BOOL def);
	CBibItem * GetDefault() const;
	CBibItem * GetOptionsItem() const;
	CString GetFormat(CString type, CString field);
	CString GetOrder(CString type, int field);
	int GetImage(CString type);
	BOOL Load();
	REQUIRED GetRequired(CString type, CString field);
	CBibDef();
	virtual ~CBibDef();

private:
	BOOL SaveRes(CString name);
};

#endif // !defined(AFX_BIBDEF_H__8F9B5979_33B3_411C_8DF2_F6EB4A87CB93__INCLUDED_)
