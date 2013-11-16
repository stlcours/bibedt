// Scintilla source code edit control
/** @file LexBib.h
 ** Lexer for BibTeX
 **/
// Copyright 2005 by Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>

// $Id: LexBib.h,v 1.6 2005/08/04 14:04:11 stievie Exp $

#ifndef __LEXBIB_H__
#define __LEXBIB_H__

// Build as external lexer (.dll)
#define BUILD_AS_EXTERNAL_LEXER

#ifdef BUILD_AS_EXTERNAL_LEXER
// The filename of the DLL
#define LEXBIB_LIB "lexbib.dll"
#else
// May be changed on conflict
#define SCLEX_BIBTEX 75
#endif // BUILD_AS_EXTERNAL_LEXER

// The name of the Lexer
#define LEXBIB_NAME "bibtex"

// BibTeX Styles additionally to LaTeX styles
// @foo
#define SCE_BIB_ITEM  5
// First opening {
#define SCE_BIB_START 6
// last closing }
#define SCE_BIB_END   7
// foo=
#define SCE_BIB_FIELD 8
#define SCE_BIB_KEY   9

#endif // !__LEXBIB_H__
