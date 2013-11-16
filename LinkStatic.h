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

  $Id: LinkStatic.h,v 1.5 2005/08/22 23:32:33 stievie Exp $
*/

#if !defined(AFX_LINKSTATIC_H__A2935141_A5B5_446D_9F5A_ACC4A907723D__INCLUDED_)
#define AFX_LINKSTATIC_H__A2935141_A5B5_446D_9F5A_ACC4A907723D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinkStatic.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CLinkStatic 

class CLinkStatic : public CStatic
{
// Konstruktion
public:
	CLinkStatic();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CLinkStatic)
	public:
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementierung
public:
	BOOL m_Visited;
	CFont m_TextFont;
	COLORREF m_VisitedColor;
	COLORREF m_HoverColor;
	COLORREF m_LinkColor;
	CString GetURL() const { return m_URL; }
	void SetURL(CString url) { m_URL = url; }
	BOOL OpenURL(CString url);
	virtual ~CLinkStatic();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	HCURSOR m_HyperCursor;	
	CString m_URL;
	//{{AFX_MSG(CLinkStatic)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClicked();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_MouseOver;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_LINKSTATIC_H__A2935141_A5B5_446D_9F5A_ACC4A907723D__INCLUDED_
