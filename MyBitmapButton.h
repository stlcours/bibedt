//	WinDjView
//	Copyright (C) 2004-2006 Andrew Zhezherun
//
//  Adapted for BibEdt by Stefan Ascher
//
//	This program is free software; you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation; either version 2 of the License, or
//	(at your option) any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//	http://www.gnu.org/copyleft/gpl.html

// $Id: MyBitmapButton.h,v 1.1 2006/05/07 20:45:23 stievie Exp $

#pragma once


// CMyBitmapButton

class CMyBitmapButton : public CBitmapButton
{
	DECLARE_DYNAMIC(CMyBitmapButton)

public:
	CMyBitmapButton();
	virtual ~CMyBitmapButton();

protected:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
};
