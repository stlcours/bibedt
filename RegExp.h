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

  $Id: RegExp.h,v 1.9 2005/09/07 00:18:36 stievie Exp $
*/

#ifndef _REGEX_H
#define _REGEX_H

extern "C" {
#include "regex.h"
}

/**
 * Structure representing one match.
 */
typedef struct _REMATCH {
	int start;                               /**< Start index of the match. */
	int end;                                 /**< End index of the match. */
	int GetLength() { return end - start; }  /**< Returns the length of the matching string. */
} REMATCH, *PREMATCH;

/**
 * Maximum count of matches.
 */
#define MAX_REMATCHES 10

/**
 * \class CRegExp
 * \brief A class interface for the GNU regular expression library.
 *
 * This class requires the GNU regular expression library.
 *
 * \author Stefan Ascher
 */
class CRegExp
{
public:
	CRegExp(LPCTSTR pszPattern);
	virtual ~CRegExp();

	BOOL Exec(const CString& sMatch);
	REMATCH* GetMatch(int index);
	int GetMatchStart(int index);
	int GetMatchEnd(int index);
	int GetMatchCount() const { return m_Matches.GetCount(); }
	CString GetErrorString() const;
	int m_Error;

protected:
	regex_t* m_Compiled;
	CList <REMATCH, REMATCH&> m_Matches;

private:
	// disable copying
	CRegExp(const CRegExp&);
	CRegExp& operator=(const CRegExp&);
};

#endif // !_REGEX_H