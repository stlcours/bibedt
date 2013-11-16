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

  $Id: BibWriter.h,v 1.5 2006/06/06 18:52:18 stievie Exp $
*/

// BibWriter.h: Schnittstelle für die Klasse CBibWriter.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBWRITER_H__6214F73C_5C6A_47DE_98E4_95DB59DF3FC0__INCLUDED_)
#define AFX_BIBWRITER_H__6214F73C_5C6A_47DE_98E4_95DB59DF3FC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BUFFER_SIZE 4096   // 4 KB

class CBibWriter 
{
public:
	virtual void Flush();
	virtual void WriteLn(LPCTSTR str);
	CBibWriter(CFile *file);
	virtual ~CBibWriter();
	virtual void Write(LPCTSTR str);

protected:
	DWORD m_Written;
	CFile * m_File;
private:
	TCHAR m_Buffer[BUFFER_SIZE];
};

#endif // !defined(AFX_BIBWRITER_H__6214F73C_5C6A_47DE_98E4_95DB59DF3FC0__INCLUDED_)
