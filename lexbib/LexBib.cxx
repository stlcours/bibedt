// Scintilla source code edit control
/** @file LexBib.cxx
 ** Lexer for BibTeX
 **/
// Copyright 2005 by Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>

// Based on the LaTeX lexer.
// Copyright 1998-2001 by Neil Hodgson <neilh[at]scintilla[dot]org>
// The License.txt file describes the conditions under which this software may be distributed.

// The external linkage code was taken from LexCamle.cxx
// Copyright 2005 by Robert Roessler <robertr[at]rftp[dot]com>

// $Id: LexBib.cxx,v 1.15 2005/08/19 12:00:35 stievie Exp $

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "KeyWords.h"
#include "Scintilla.h"
#include "SciLexer.h"
#include "LexBib.h"

#ifdef BUILD_AS_EXTERNAL_LEXER
/*
	(actually seems to work!)
*/
#include "WindowAccessor.h"
#include "ExternalLexer.h"


#if PLAT_WIN
#include <windows.h>

#ifdef _DEBUG
void Platform::DebugPrintf(const char *format, ...) {
	char buffer[2000];
	va_list pArguments;
	va_start(pArguments, format);
	vsprintf(buffer,format,pArguments);
	va_end(pArguments);
	OutputDebugString(buffer);
}
#define TRACE Platform::DebugPrintf
#else
void Platform::DebugPrintf(const char *, ...) {
}
#define TRACE
#endif // _DEBUG
#else
#define TRACE
#endif // PLAT_WIN

static void ColouriseBibtexDoc(
	unsigned int startPos, int length,
	int initStyle,
	WordList *keywordlists[],
	Accessor &styler);
static void FoldBibtexDoc(
	unsigned int startPos, int length,
	int initStyle,
	WordList *keywordlists[],
	Accessor &styler);

static void InternalLexOrFold(int lexOrFold, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props);

bool Platform::IsDBCSLeadByte(int codePage, char ch) {
	return ::IsDBCSLeadByteEx(codePage, ch) != 0;
}

long Platform::SendScintilla(WindowID w, unsigned int msg, unsigned long wParam, long lParam) {
	return ::SendMessage(reinterpret_cast<HWND>(w), msg, wParam, lParam);
}

long Platform::SendScintillaPointer(WindowID w, unsigned int msg, unsigned long wParam, void *lParam) {
	return ::SendMessage(reinterpret_cast<HWND>(w), msg, wParam,
		reinterpret_cast<LPARAM>(lParam));
}

void EXT_LEXER_DECL Fold(unsigned int lexer, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props)
{
	// below useless evaluation(s) to supress "not used" warnings
	lexer;
	// build expected data structures and do the Fold
	InternalLexOrFold(1, startPos, length, initStyle, words, window, props);

}

int EXT_LEXER_DECL GetLexerCount()
{
	return 1;	// just this!
}

void EXT_LEXER_DECL GetLexerName(unsigned int Index, char *name, int buflength)
{
	// below useless evaluation(s) to supress "not used" warnings
	Index;
	// return as much of our lexer name as will fit (what's up with Index?)
	if (buflength > 0) {
		buflength--;
		int n = strlen(LEXBIB_NAME);
		if (n > buflength)
			n = buflength;
		memcpy(name, LEXBIB_NAME, n), name[n] = '\0';
	}
}

void EXT_LEXER_DECL Lex(unsigned int lexer, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props)
{
	// below useless evaluation(s) to supress "not used" warnings
	lexer;
	// build expected data structures and do the Lex
	InternalLexOrFold(0, startPos, length, initStyle, words, window, props);
}

static void InternalLexOrFold(int foldOrLex, unsigned int startPos, int length,
	int initStyle, char *words[], WindowID window, char *props)
{
	// create and initialize a WindowAccessor (including contained PropSet)
	PropSet ps;
	ps.SetMultiple(props);
	WindowAccessor wa(window, ps);
	// create and initialize WordList(s)
	int nWL = 0;
	for (; words[nWL]; nWL++) ;	// count # of WordList PTRs needed
	WordList** wl = new WordList* [nWL + 1];// alloc WordList PTRs
	int i = 0;
	for (; i < nWL; i++) {
		wl[i] = new WordList();	// (works or THROWS bad_alloc EXCEPTION)
		wl[i]->Set(words[i]);
	}
	wl[i] = 0;
	// call our "internal" folder/lexer (... then do Flush!)
	if (foldOrLex)
		FoldBibtexDoc(startPos, length, initStyle, wl, wa);
	else
		ColouriseBibtexDoc(startPos, length, initStyle, wl, wa);
	wa.Flush();
	// clean up before leaving
	for (i = nWL - 1; i >= 0; i--)
		delete wl[i];
	delete [] wl;
}

#else
#define TRACE
#endif	/* BUILD_AS_EXTERNAL_LEXER */

/**
 * Find the start of the closest previous bibitem
 */
static int findStart(int pos, Accessor &styler)
{
	int brack = 0;
	int res = 0;
	for (int i = 0; i < pos; i++) {
		char c = styler.SafeGetCharAt(i);
		switch (c) {
		case '{':
			brack++;
			break;
		case '}':
			brack--;
			break;
		case '@':
			if (!brack)
				res = i - 1;
			break;
		}
	}
	return res;
}

static void FoldBibtexDoc(unsigned int startPos, int length, int, WordList*[], Accessor &styler) 
{
	unsigned int endPos = startPos + length;
	bool atEOL = false;
	int lineCurrent = styler.GetLine(startPos);
	int levelCurrent = SC_FOLDLEVELBASE;
	if (lineCurrent > 0)
		levelCurrent = styler.LevelAt(lineCurrent-1) >> 16;
	int levelNext = levelCurrent;
	char chNext = styler[startPos];
	for (unsigned int i = startPos; i < endPos; i++) {
		char ch = chNext;
		chNext = styler.SafeGetCharAt(i + 1);
		atEOL = (ch == '\r' && chNext != '\n') || (ch == '\n');

		switch (styler.StyleAt(i)) {
		case SCE_BIB_START:
			levelNext++;
			break;
		case SCE_BIB_END:
			levelNext--;
			break;
		}

		if (atEOL) {
			int levelUse = levelCurrent;
			int lev = levelUse | levelNext << 16;
			if (levelUse < levelNext)
				lev |= SC_FOLDLEVELHEADERFLAG;
			if (lev != styler.LevelAt(lineCurrent)) {
				styler.SetLevel(lineCurrent, lev);
			}
			lineCurrent++;
			levelCurrent = levelNext;
		}
	}
}

static int isSpecial(char s) {
	return (s == '\\') || (s == ',') || (s == ';') || (s == '\'') || (s == ' ') ||
	       (s == '\"') || (s == '`') || (s == '^') || (s == '~');
}

static int isTag(int start, Accessor &styler) {
	char s[6];
	unsigned int i = 0, e = 1;
	while (i < 5 && e) {
		s[i] = styler[start + i];
		i++;
		e = styler[start + i] != '{';
	}
	s[i] = '\0';
	return (strcmp(s, "begin") == 0) || (strcmp(s, "end") == 0);
}

static bool isStringOrPreamble(int start, Accessor &styler) {
	char s[9];
	unsigned int i = 0, e = 1;
	while (i < 8 && e) {
		s[i] = styler[start + i];
		i++;
		e = styler[start + i] != '{';
	}
	s[i] = '\0';
	return (stricmp(s, "string") == 0) || (stricmp(s, "preamble") == 0 || (stricmp(s, "comment") == 0));
}

static void ColouriseBibtexDoc(unsigned int startPos, int length, int initStyle,
                              WordList *[], Accessor &styler) {

	styler.StartAt(startPos);

	int state = initStyle;
	char chNext = styler[startPos];
	styler.StartSegment(startPos);
	int lengthDoc = startPos + length;
	int brack = 0;
	unsigned int newStartPos;
	// Have we found a bib item
	bool haveitem = false;
	bool isstrorpre = false;

	// We need the start of a bib item
	newStartPos = findStart(startPos, styler);

	for (int i = newStartPos; i < lengthDoc; i++) {
		char ch = chNext;
		chNext = styler.SafeGetCharAt(i + 1);

		if (styler.IsLeadByte(ch)) {
			chNext = styler.SafeGetCharAt(i + 2);
			i++;
			continue;
		}
		switch (state) {
		case SCE_L_DEFAULT :
			switch (ch) {
			case '\\' :
				if (i >= (int)startPos)
					styler.ColourTo(i - 1, state);
				if (isSpecial(styler[i + 1])) {
					if (i >= (int)startPos)
						styler.ColourTo(i + 1, SCE_L_COMMAND);
					i++;
					chNext = styler.SafeGetCharAt(i + 1);
				} else {
					if (isTag(i + 1, styler))
						state = SCE_L_TAG;
					else
						state = SCE_L_COMMAND;
				}
				break;
			case '@' :
				if (i >= (int)startPos)
					styler.ColourTo(i - 1, state);
				if (!brack) {
					state = SCE_BIB_ITEM;
					isstrorpre = isStringOrPreamble(i + 1, styler);
					haveitem = true;
				} else
					state = SCE_L_DEFAULT;
				break;
			case '{' :
				brack++;
				break;
			case '}' :
				if (brack) {
					brack--;
					if (!brack && haveitem) {
						if (i >= (int)startPos)
							styler.ColourTo(i - 1, state);
						state = SCE_BIB_END;
					}
				}
				break;
			case '$' :
				if (i >= (int)startPos)
					styler.ColourTo(i - 1, state);
				state = SCE_L_MATH;
				if (chNext == '$') {
					i++;
					chNext = styler.SafeGetCharAt(i + 1);
				}
				break;
			case '%' :
				if (i >= (int)startPos)
					styler.ColourTo(i - 1, state);
				state = SCE_L_COMMENT;
				break;
			}
			break;
		case SCE_L_COMMAND :
			if (chNext == '[' || chNext == '{' || chNext == '}' ||
			        chNext == ' ' || chNext == '\r' || chNext == '\n' ||
					chNext == '`' || chNext == '´' || chNext == '\'' ||
					chNext == '\"' || chNext == '=') {
				if (i >= (int)startPos)
					styler.ColourTo(i, state);
				state = SCE_L_DEFAULT;
			}
			break;
		case SCE_L_TAG :
			if (ch == '}') {
				if (brack)
					brack--;
				if (i >= (int)startPos)
					styler.ColourTo(i, state);
				state = SCE_L_DEFAULT;
			}
			break;
		case SCE_BIB_ITEM:
			if (chNext == '{') {
				if (i >= (int)startPos)
					styler.ColourTo(i, state);
				state = SCE_BIB_START;
			}
			break;
		case SCE_BIB_START:
		case SCE_BIB_END:
			if (i >= (int)startPos && haveitem)
				styler.ColourTo(i, state);
			if (state == SCE_BIB_START && !isstrorpre)
				state = SCE_BIB_KEY;
			else
				state = SCE_L_DEFAULT;
			if (ch == '{')
				brack++;
			else if (ch == '}') {
				brack--;
				haveitem = false;
			}
			break;
		case SCE_BIB_KEY :
			if (ch == ',' || ch == '}') {
				if (i-1 >= (int)startPos && haveitem)
					styler.ColourTo(i-1, state);
				state = SCE_L_DEFAULT;
			}
			break;
		case SCE_L_MATH :
			if (ch == '$') {
				if (chNext == '$') {
					i++;
					chNext = styler.SafeGetCharAt(i + 1);
				}
				if (i >= (int)startPos)
					styler.ColourTo(i, state);
				state = SCE_L_DEFAULT;
			}
			break;
		case SCE_L_COMMENT :
			if (ch == '\r' || ch == '\n') {
				if (i >= (int)startPos)
					styler.ColourTo(i - 1, state);
				state = SCE_L_DEFAULT;
			}
		}
	}
	if (i >= (int)startPos)
		styler.ColourTo(lengthDoc-1, state);
}

#ifndef BUILD_AS_EXTERNAL_LEXER

LexerModule lmBib(SCLEX_BIBTEX, ColouriseBibtexDoc, LEXBIB_NAME, FoldBibtexDoc, 0);

#endif // !BUILD_AS_EXTERNAL_LEXER

