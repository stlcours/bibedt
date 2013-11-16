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

  $Id: ExportRTF.h,v 1.14 2006/04/08 19:34:26 stievie Exp $
*/

// ExportRTF.h: Schnittstelle für die Klasse CExportRTF.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPORTRTF_H__123A0DA4_345F_4B20_BAAB_6007E072E7B8__INCLUDED_)
#define AFX_EXPORTRTF_H__123A0DA4_345F_4B20_BAAB_6007E072E7B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Export.h"
#include "xString.h"

/**
 * \brief The RTF exporter.
 * 
 * The class to export a subset of the loaded file to a RTF file.
 */
class CExportRTF : public CExport  
{
public:
	virtual CExport* Clone();
	virtual CString GetBody();
	virtual CString GetFooter();
	virtual CString GetHeader();
	virtual CString GetSource();
	virtual CString GetExt();
	virtual CString GetFilter();
	virtual CString GetItemSource(CBibItem* item);
	virtual void GetItemSource(xString *const str, CBibItem* item);
	virtual void DoExport(CString filename);
	CExportRTF();
	virtual ~CExportRTF();

protected:
	void Load();
	CString GetFontTable();
private:
	CString GetColorTable();
};

#endif // !defined(AFX_EXPORTRTF_H__123A0DA4_345F_4B20_BAAB_6007E072E7B8__INCLUDED_)
