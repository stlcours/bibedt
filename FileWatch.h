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

  $Id: FileWatch.h,v 1.3 2006/05/20 14:37:38 stievie Exp $
*/

// FileWatch.h: Schnittstelle für die Klasse CFileWatch.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEWATCH_H__6F139428_29E7_4CA6_A781_BB585A4B39A1__INCLUDED_)
#define AFX_FILEWATCH_H__6F139428_29E7_4CA6_A781_BB585A4B39A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum FILECHANGE {
	FC_NONE, FC_DATE, FC_DELETE
};

class CFileWatch  
{
public:
	void EndUpdate() { m_dwUpdateCount++; }
	void BeginUpdate() { if (m_dwUpdateCount > 0) m_dwUpdateCount--; }
	FILECHANGE GetModified();
	void Update();
	CTime m_LastModified;
	CFileWatch();
	virtual ~CFileWatch();
	void SetFileName(CString fn);
	CString GetFileName() const { return m_FileName; }

protected:
	CString m_FileName;
private:
	DWORD m_dwUpdateCount;
};

#endif // !defined(AFX_FILEWATCH_H__6F139428_29E7_4CA6_A781_BB585A4B39A1__INCLUDED_)
