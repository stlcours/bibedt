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

  $Id: ScintillaBibWnd.h,v 1.9 2005/08/25 16:20:03 stievie Exp $
*/

// ScintillaBibWnd.h: Schnittstelle für die Klasse CScintillaBibWnd.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCINTILLABIBWND_H__9550C486_43E2_4CC9_A3FF_B06DF3992CEC__INCLUDED_)
#define AFX_SCINTILLABIBWND_H__9550C486_43E2_4CC9_A3FF_B06DF3992CEC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScintillaWnd.h"

class CScintillaBibWnd : public CScintillaWnd  
{
public:
	BOOL ExpandItem(CString item);
	BOOL FoldItem(CString item);
	CString GetKeyAt(long lPos);
	CString GetCurrentKey();
	BOOL MarkMatches(LPCSTR lpText);
	BOOL m_RegExpr;
	BOOL m_MatchCase;
	BOOL m_WholeWords;
	BOOL FindNext();
	CString m_FindText;
	BOOL m_SearchBackward;
	BOOL SearchText(LPCSTR lpText);
	BOOL GotoItem(CString key);
	int FindItem(CString key);
	virtual void Init();
	CScintillaBibWnd();
	virtual ~CScintillaBibWnd();

};

#endif // !defined(AFX_SCINTILLABIBWND_H__9550C486_43E2_4CC9_A3FF_B06DF3992CEC__INCLUDED_)
