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

  $Id: ScintillaPrint.h,v 1.3 2005/08/22 23:32:33 stievie Exp $
*/

// ScintillaPrint.h: Schnittstelle für die Klasse CScintillaPrint.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCINTILLAPRINT_H__ABF937A8_C64A_4558_B69F_877366269367__INCLUDED_)
#define AFX_SCINTILLAPRINT_H__ABF937A8_C64A_4558_B69F_877366269367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Print.h"
#include "ScintillaWnd.h"

class CScintillaPrint : public CPrint  
{
public:
	CScintillaPrint();
	virtual ~CScintillaPrint();

// Operations
public:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo); 

	void SetScintilla(CScintillaWnd* scin){ m_Scintilla = scin; }
	CScintillaWnd* GetScintilla(){ return m_Scintilla; }

protected:
	CScintillaWnd* m_Scintilla;
	virtual void PrintBody(CDC* pDC, CPrintInfo* pInfo);

private:
	BOOL PaginateTo(CDC *pDC, CPrintInfo *pInfo);
	long PrintPage(CDC *pDC, CPrintInfo *pInfo, long nIndexStart, long nIndexStop);

private:
	CArray<int, int>          m_aPageStart;                       //array of starting pages

};

#endif // !defined(AFX_SCINTILLAPRINT_H__ABF937A8_C64A_4558_B69F_877366269367__INCLUDED_)
