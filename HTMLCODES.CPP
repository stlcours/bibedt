// HTMLCodes
// Provides different conversions
//
// © 2004 Karl Runmo ,runmo@hotmail.com
//   - Modified 2006 by Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.

#include "stdafx.h"
#include <windows.h>

struct HTMLCODES {
	char szCode[10];
	char Code;
};
static const HTMLCODES g_HTMLCodes[] = {
	{"&quot;",'"'},
	{"&amp;",'&'},
	{"&lt;",'<'},
	{"&gt;",'>'},
	{"&nbsp;",' '},
	{"&iexcl;",'¡'},
	{"&cent;",'¢'},
	{"&pound;",'£'},
	{"&curren;",'¤'},
	{"&yen;",'¥'},
	{"&brvbar;",'¦'},
	{"&sect;",'§'},
	{"&uml;",'¨'},
	{"&copy;",'©'},
	{"&ordf;",'ª'},
	{"&laquo;",'«'},
	{"&not;",'¬'},
	{"&shy;",'­'},
	{"&reg;",'®'},
	{"&macr;",'¯'},
	{"&deg;",'°'},
	{"&plusmn;",'±'},
	{"&sup2;",'²'},
	{"&sup3;",'³'},
	{"&acute;",'´'},
	{"&micro;",'µ'},
	{"&para;",'¶'},
	{"&middot;",'·'},
	{"&cedil;",'¸'},
	{"&sup1;",'¹'},
	{"&ordm;",'º'},
	{"&raquo;",'»'},
	{"&frac14;",'¼'},
	{"&frac12;",'½'},
	{"&frac34;",'¾'},
	{"&iquest;",'¿'},
	{"&Agrave;",'À'},
	{"&Aacute;",'Á'},
	{"&Acirc;",'Â'},
	{"&Atilde;",'Ã'},
	{"&Auml;",'Ä'},
	{"&Aring;",'Å'},
	{"&AElig;",'Æ'},
	{"&Ccedil;",'Ç'},
	{"&Egrave;",'È'},
	{"&Eacute;",'É'},
	{"&Ecirc;",'Ê'},
	{"&Euml;",'Ë'},
	{"&Igrave;",'Ì'},
	{"&Iacute;",'Í'},
	{"&Icirc;",'Î'},
	{"&Iuml;",'Ï'},
	{"&ETH;",'Ð'},
	{"&Ntilde;",'Ñ'},
	{"&Ograve;",'Ò'},
	{"&Oacute;",'Ó'},
	{"&Ocirc;",'Ô'},
	{"&Otilde;",'Õ'},
	{"&Ouml;",'Ö'},
	{"&times;",'×'},
	{"&Oslash;",'Ø'},
	{"&Ugrave;",'Ù'},
	{"&Uacute;",'Ú'},
	{"&Ucirc;",'Û'},
	{"&Uuml;",'Ü'},
	{"&Yacute;",'Ý'},
	{"&THORN;",'Þ'},
	{"&szlig;",'ß'},
	{"&agrave;",'à'},
	{"&aacute;",'á'},
	{"&acirc;",'â'},
	{"&atilde;",'ã'},
	{"&auml;",'ä'},
	{"&aring;",'å'},
	{"&aelig;",'æ'},
	{"&ccedil;",'ç'},
	{"&egrave;",'è'},
	{"&eacute;",'é'},
	{"&ecirc;",'ê'},
	{"&euml;",'ë'},
	{"&igrave;",'ì'},
	{"&iacute;",'í'},
	{"&icirc;",'î'},
	{"&iuml;",'ï'},
	{"&eth;",'ð'},
	{"&ntilde;",'ñ'},
	{"&ograve;",'ò'},
	{"&oacute;",'ó'},
	{"&ocirc;",'ô'},
	{"&otilde;",'õ'},
	{"&ouml;",'ö'},
	{"&divide;",'÷'},
	{"&oslash;",'ø'},
	{"&ugrave;",'ù'},
	{"&uacute;",'ú'},
	{"&ucirc;",'û'},
	{"&uuml;",'ü'},
	{"&yacute;",'ý'},
	{"&thorn;",'þ'},
	{"&yuml;",'ÿ'},
	{"&OElig;",'E'},
	{"&oelig;",'e'},
	{"&Scaron;",'S'},
	{"&scaron;",'s'},
	{"&Yuml;",'ÿ'},
	{"&fnof;",'f'},
	{"&circ;",'^'},
	{"&tilde;",'~'},
	{"&ndash;",'-'},
	{"&mdash;",'-'},
	{"&lsquo;",'‘'},
	{"&rsquo;",'’'},
	{"&sbquo;",','},
	{"&ldquo;",'\"'},
	{"&rdquo;",'\"'},
	{"&bdquo;",'„'},
	{"&dagger;",'†'},
	{"&Dagger;",'‡'},
	{"&bull;",'•'},
	{"&hellip;",'…'},
	{"&permil;",'‰'},
	{"&lsaquo;",'‹'},
	{"&rsaquo;",'›'},
	{"&euro;",'€'},
	{"&trade;",'™'},
//	{{(char)0x96,(char)0x00},'-'},
//	{{(char)0x97,(char)0x00},'-'},
	{{(char)0x11,(char)0x82},'-'},
	{{(char)0x13,(char)0x20},'-'},
	{{(char)0x14,(char)0x20},'-'},
	{{(char)0xA0,(char)0x00},' '},
	{"",0}
};

char *ConvertFromHTMLCodes(char *szText)
{
	int i, j, k;
	for(k=j=0;szText[j];j++){
		for(i=0;g_HTMLCodes[i].Code;i++){
			if(!strncmp(&szText[j],g_HTMLCodes[i].szCode,strlen(g_HTMLCodes[i].szCode))){
				szText[k++] = g_HTMLCodes[i].Code;
				j+=strlen(g_HTMLCodes[i].szCode)-1;
				break;
			}
		}
		if(!g_HTMLCodes[i].Code){
			if(!strnicmp(&szText[j],"&#",2)){
				j+=2;
				szText[k++] = atoi(&szText[j]);
				while(szText[j] && szText[j]!=';' && szText[j]!=' ')
					j++;
				if(!szText[j])
					break;
			}
			else
				szText[k++] = szText[j];
		}
	}
	szText[k]=0;
	return szText;
}
char *ConvertToHTMLCodes(char *szText)
{
	int nLen=0;
	int i, j, k;
	for(i=0;szText[i];i++){
		for(j=0;g_HTMLCodes[j].Code;j++)
			if(szText[i]==g_HTMLCodes[j].Code)
				break;
		if(g_HTMLCodes[j].Code)
			nLen+=strlen(g_HTMLCodes[j].szCode);
		else
			nLen++;
	}
	char *szRet = new char[nLen+1];
	k=0;
	for(i=0;szText[i];i++){
		for(j=0;g_HTMLCodes[j].Code;j++)
			if(szText[i]==g_HTMLCodes[j].Code)
				break;
		if(g_HTMLCodes[j].Code){
			strcpy(&szRet[k],g_HTMLCodes[j].szCode);
			k+=strlen(g_HTMLCodes[j].szCode);
		}
		else
			szRet[k++] = szText[i];
	}
	szRet[k]=0;
	return szRet;
}


struct UTF8{
	unsigned char Code;
	unsigned char szCode[3];
};

static const UTF8 g_Utf8[] = {
	{150,{0xc2,0x96,0}},	   // n-dash
	{151,{0xc2,0x97,0}},	   // m-dash
	{160,{0xc2,0xa0,0}},
	{161,{0xc2,0xa1,0}},
	{162,{0xc2,0xa2,0}},
	{163,{0xc2,0xa3,0}},
	{164,{0xc2,0xa4,0}},
	{165,{0xc2,0xa5,0}},
	{166,{0xc2,0xa6,0}},
	{167,{0xc2,0xa7,0}},
	{168,{0xc2,0xa8,0}},
	{169,{0xc2,0xa9,0}},
	{170,{0xc2,0xaa,0}},
	{171,{0xc2,0xab,0}},
	{172,{0xc2,0xac,0}},
	{173,{0xc2,0xad,0}},
	{174,{0xc2,0xae,0}},
	{175,{0xc2,0xaf,0}},
	{176,{0xc2,0xb0,0}},
	{177,{0xc2,0xb1,0}},
	{178,{0xc2,0xb2,0}},
	{179,{0xc2,0xb3,0}},
	{180,{0xc2,0xb4,0}},
	{181,{0xc2,0xb5,0}},
	{182,{0xc2,0xb6,0}},
	{183,{0xc2,0xb7,0}},
	{184,{0xc2,0xb8,0}},
	{185,{0xc2,0xb9,0}},
	{186,{0xc2,0xba,0}},
	{187,{0xc2,0xbb,0}},
	{188,{0xc2,0xbc,0}},
	{189,{0xc2,0xbd,0}},
	{190,{0xc2,0xbe,0}},
	{191,{0xc2,0xbf,0}},
	{192,{0xc3,0x80,0}},
	{193,{0xc3,0x81,0}},
	{194,{0xc3,0x82,0}},
	{195,{0xc3,0x83,0}},
	{196,{0xc3,0x84,0}},
	{197,{0xc3,0x85,0}},
	{198,{0xc3,0x86,0}},
	{199,{0xc3,0x87,0}},
	{200,{0xc3,0x88,0}},
	{201,{0xc3,0x89,0}},
	{202,{0xc3,0x8a,0}},
	{203,{0xc3,0x8b,0}},
	{204,{0xc3,0x8c,0}},
	{205,{0xc3,0x8d,0}},
	{206,{0xc3,0x8e,0}},
	{207,{0xc3,0x8f,0}},
	{208,{0xc3,0x90,0}},
	{209,{0xc3,0x91,0}},
	{210,{0xc3,0x92,0}},
	{211,{0xc3,0x93,0}},
	{212,{0xc3,0x94,0}},
	{213,{0xc3,0x95,0}},
	{214,{0xc3,0x96,0}},
	{215,{0xc3,0x97,0}},
	{216,{0xc3,0x98,0}},
	{217,{0xc3,0x99,0}},
	{218,{0xc3,0x9a,0}},
	{219,{0xc3,0x9b,0}},
	{220,{0xc3,0x9c,0}},
	{221,{0xc3,0x9d,0}},
	{222,{0xc3,0x9e,0}},
	{223,{0xc3,0x9f,0}},
	{224,{0xc3,0xa0,0}},
	{225,{0xc3,0xa1,0}},
	{226,{0xc3,0xa2,0}},
	{227,{0xc3,0xa3,0}},
	{228,{0xc3,0xa4,0}},
	{229,{0xc3,0xa5,0}},
	{230,{0xc3,0xa6,0}},
	{231,{0xc3,0xa7,0}},
	{232,{0xc3,0xa8,0}},
	{233,{0xc3,0xa9,0}},
	{234,{0xc3,0xaa,0}},
	{235,{0xc3,0xab,0}},
	{236,{0xc3,0xac,0}},
	{237,{0xc3,0xad,0}},
	{238,{0xc3,0xae,0}},
	{239,{0xc3,0xaf,0}},
	{240,{0xc3,0xb0,0}},
	{241,{0xc3,0xb1,0}},
	{242,{0xc3,0xb2,0}},
	{243,{0xc3,0xb3,0}},
	{244,{0xc3,0xb4,0}},
	{245,{0xc3,0xb5,0}},
	{246,{0xc3,0xb6,0}},
	{247,{0xc3,0xb7,0}},
	{248,{0xc3,0xb8,0}},
	{249,{0xc3,0xb9,0}},
	{250,{0xc3,0xba,0}},
	{251,{0xc3,0xbb,0}},
	{252,{0xc3,0xbc,0}},
	{253,{0xc3,0xbd,0}},
	{254,{0xc3,0xbe,0}},
	{255,{0xc3,0xbf,0}},
	{0,{0,0}}
};
char *ConvertFromUtf8Codes(char *szText)
{
	int i, j, k;
	for(k=j=0; szText[j]; j++){
		for(i=0; g_Utf8[i].Code;i++){
			if(!strncmp(&szText[j], (char*)g_Utf8[i].szCode, 2)){
				szText[k++] = g_Utf8[i].Code;
				j++;
				break;
			}
		}
		if(!g_Utf8[i].Code)
			szText[k++] = szText[j];
	}
	szText[k] = 0;
	return szText;
}
char *ConvertToUtfCodes(char *szText)
{
	int nLen=0;
	int i, j, k;
	for(i=0;szText[i];i++){
		for(j=0;g_Utf8[j].Code;j++)
			if((unsigned char)szText[i]==g_Utf8[j].Code)
				break;
		if(g_Utf8[j].Code)
			nLen+=strlen((char*)g_Utf8[j].szCode);
		else
			nLen++;
	}
	char *szRet = new char[nLen+1];
	k=0;
	for(i=0;szText[i];i++){
		for(j=0;g_Utf8[j].Code;j++)
			if((unsigned char)szText[i]==g_Utf8[j].Code)
				break;
		if(g_Utf8[j].Code){
			strcpy(&szRet[k],(char*)g_Utf8[j].szCode);
			k+=strlen((char*)g_Utf8[j].szCode);
		}
		else
			szRet[k++] = szText[i];
	}
	szRet[k]=0;
	return szRet;
}

