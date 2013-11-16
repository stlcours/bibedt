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

  $Id: BibReader.h,v 1.5 2006/06/06 18:52:18 stievie Exp $
*/

// BibReader.h: Schnittstelle für die Klasse CBibReader.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIBREADER_H__600673C7_AD7A_428A_877F_869EA0366307__INCLUDED_)
#define AFX_BIBREADER_H__600673C7_AD7A_428A_877F_869EA0366307__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBibReader  
{
public:
	TCHAR GetAt(UINT pos) const;
	UINT GetPosition() const { return m_Position; }
	virtual DWORD GetLength() const { return m_Length; };
	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual LONG Seek(LONG lOff, UINT nFrom);
	CBibReader(CFile *file);
	CBibReader(CString src);
	virtual ~CBibReader();
	TCHAR operator[](UINT pos) const { return GetAt(pos); }

protected:
	TCHAR* m_Buffer;
	UINT m_Position;
private:
	DWORD m_Length;
};

#endif // !defined(AFX_BIBREADER_H__600673C7_AD7A_428A_877F_869EA0366307__INCLUDED_)
