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

  $Id: RegExp.cpp,v 1.5 2005/08/22 23:32:33 stievie Exp $
*/

#include "stdafx.h"
#include <stddef.h>
#include "RegExp.h"

/**
 * \brief Constructor.
 *
 * \param pszPattern The expression string.
 */
CRegExp::CRegExp(LPCTSTR pszPattern)
{
	m_Compiled = (regex_t*)malloc(sizeof(regex_t));
	memset(m_Compiled, 0, sizeof(regex_t));
	m_Error = regcomp(m_Compiled, pszPattern, REG_EXTENDED);
}

CRegExp::~CRegExp()
{
	if (m_Compiled) {
		regfree(m_Compiled);
		free(m_Compiled);
	}
}

/**
 * \brief Return the error string.
 * 
 * \return CString object holding the error string.
 */
CString CRegExp::GetErrorString() const
{
	char buff[256];
	regerror(m_Error, m_Compiled, buff, sizeof(buff));
	return CString(buff);
}

/**
 * \brief Execute.
 *
 * \param sMatch The string to search for the expression.
 *
 * \return TRUE when found, otherwise FALSE.
 */
BOOL CRegExp::Exec(const CString& sMatch)
{
	int count = 0;
	m_Matches.RemoveAll();
	regmatch_t* match;
	match = (regmatch_t*)malloc(sizeof(regmatch_t) * MAX_REMATCHES);
	memset(match, -1, sizeof(regmatch_t) * MAX_REMATCHES);
	int error = regexec(m_Compiled, sMatch, MAX_REMATCHES, match, 0);
	if (error == 0) {
		while (count < MAX_REMATCHES && match[count].rm_so != -1) {
			REMATCH m;
			m.start = match[count].rm_so;
			m.end = match[count].rm_eo;
			count++;
			m_Matches.AddTail(m);
		}
	}
	free(match);
	return (error == 0);
}

/**
 * \brief Get start index of match.
 *
 * \param index The index of the match.
 *
 * \return The start position.
 */
int CRegExp::GetMatchStart(int index) 
{
	PREMATCH match = GetMatch(index);
	if (match)
		return match->start;
	else
		return -1;
}

/**
 * \brief Get end index of match.
 *
 * \param index The index of the match.
 *
 * \return The end position.
 */
int CRegExp::GetMatchEnd(int index)
{
	PREMATCH match = GetMatch(index);
	if (match)
		return match->end;
	else
		return -1;
}

/**
 * \brief Get match.
 *
 * \param index The index of the match.
 *
 * \return A pointer to a REMATCH structure.
 */
REMATCH* CRegExp::GetMatch(int index)
{
	if (index < m_Matches.GetCount()) {
		POSITION p = m_Matches.FindIndex(index);
		if (p) {
			return &m_Matches.GetAt(p); 
		} else
			return NULL;
	} else
		return NULL;
}
