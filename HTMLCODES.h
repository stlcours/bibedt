// HTMLCodes
// Provides different conversions
//
// � 2004 Karl Runmo ,runmo@hotmail.com
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

struct ColTable
{
	char *szName;
	COLORREF colVal;
};
static ColTable g_ColTable[] = 
{
	{"AliceBlue"           ,RGB(240,248,255)},
	{"AntiqueWhite"        ,RGB(250,235,215)},
	{"Aqua"                ,RGB(  0,255,255)},
	{"Aquamarine"          ,RGB(127,255,212)},
	{"Azure"               ,RGB(240,255,255)},
	{"Beige"               ,RGB(245,245,220)},
	{"Bisque"              ,RGB(255,228,196)},
	{"Black"               ,RGB(  0,  0,  0)},
	{"BlanchedAlmond"      ,RGB(255,255,205)},
	{"Blue"                ,RGB(  0,  0,255)},
	{"BlueViolet"          ,RGB(138, 43,226)},
	{"Brown"               ,RGB(165, 42, 42)},
	{"Burlywood"           ,RGB(222,184,135)},
	{"CadetBlue"           ,RGB( 95,158,160)},
	{"Chartreuse"          ,RGB(127,255,  0)},
	{"Chocolate"           ,RGB(210,105, 30)},
	{"Coral"               ,RGB(255,127, 80)},
	{"CornflowerBlue"      ,RGB(100,149,237)},
	{"Cornsilk"            ,RGB(255,248,220)},
	{"Crimson"             ,RGB(220, 20, 60)},
	{"Cyan"                ,RGB(  0,255,255)},
	{"DarkBlue"            ,RGB(  0,  0,139)},
	{"DarkCyan"            ,RGB(  0,139,139)},
	{"DarkGoldenRod"       ,RGB(184,134, 11)},
	{"DarkGray"            ,RGB(169,169,169)},
	{"DarkGreen"           ,RGB(  0,100,  0)},
	{"DarkKhaki"           ,RGB(189,183,107)},
	{"DarkMagenta"         ,RGB(139,  0,139)},
	{"DarkOliveGreen"      ,RGB( 85,107, 47)},
	{"DarkOrange"          ,RGB(255,140,  0)},
	{"DarkOrchid"          ,RGB(153, 50,204)},
	{"DarkRed"             ,RGB(139,  0,  0)},
	{"DarkSalmon"          ,RGB(233,150,122)},
	{"DarkSeaGreen"        ,RGB(143,188,143)},
	{"DarkSlateBlue"       ,RGB( 72, 61,139)},
	{"DarkSlateGray"       ,RGB( 47, 79, 79)},
	{"DarkTurquoise"       ,RGB(  0,206,209)},
	{"DarkViolet"          ,RGB(148,  0,211)},
	{"DeepPink"            ,RGB(255, 20,147)},
	{"DeepSkyBlue"         ,RGB(  0,191,255)},
	{"DimGray"             ,RGB(105,105,105)},
	{"DodgerBlue"          ,RGB( 30,144,255)},
	{"FireBrick"           ,RGB(178, 34, 34)},
	{"FloralWhite"         ,RGB(255,250,240)},
	{"ForestGreen"         ,RGB( 34,139, 34)},
	{"Fuchsia"             ,RGB(255,  0,255)},
	{"Gainsboro"           ,RGB(220,220,220)},
	{"GhostWhite"          ,RGB(248,248,255)},
	{"Gold"                ,RGB(255,215,  0)},
	{"GoldenRod"           ,RGB(218,165, 32)},
	{"Gray"                ,RGB(127,127,127)},
	{"Green"               ,RGB(  0,128,  0)},
	{"GreenYellow"         ,RGB(173,255, 47)},
	{"HoneyDew"            ,RGB(240,255,240)},
	{"HotPink"             ,RGB(255,105,180)},
	{"IndianRed"           ,RGB(205, 92, 92)},
	{"Indigo"              ,RGB( 75,  0,130)},
	{"Ivory"               ,RGB(255,255,240)},
	{"Khaki"               ,RGB(240,230,140)},
	{"Lavender"            ,RGB(230,230,250)},
	{"LavenderBlush"       ,RGB(255,240,245)},
	{"Lawngreen"           ,RGB(124,252,  0)},
	{"LemonChiffon"        ,RGB(255,250,205)},
	{"LightBlue"           ,RGB(173,216,230)},
	{"LightCoral"          ,RGB(240,128,128)},
	{"LightCyan"           ,RGB(224,255,255)},
	{"LightGoldenRodYellow",RGB(250,250,210)},
	{"LightGreen"          ,RGB(144,238,144)},
	{"LightGrey"           ,RGB(211,211,211)},
	{"LightPink"           ,RGB(255,182,193)},
	{"LightSalmon"         ,RGB(255,160,122)},
	{"LightSeaGreen"       ,RGB( 32,178,170)},
	{"LightSkyBlue"        ,RGB(135,206,250)},
	{"LightSlateGray"      ,RGB(119,136,153)},
	{"LightSteelBlue"      ,RGB(176,196,222)},
	{"LightYellow"         ,RGB(255,255,224)},
	{"Lime"                ,RGB(  0,255,  0)},
	{"LimeGreen"           ,RGB( 50,205, 50)},
	{"Linen"               ,RGB(250,240,230)},
	{"Magenta"             ,RGB(255,  0,255)},
	{"Maroon"              ,RGB(128,  0,  0)},
	{"MediumAquamarine"    ,RGB(102,205,170)},
	{"MediumBlue"          ,RGB(  0,  0,205)},
	{"MediumOrchid"        ,RGB(186, 85,211)},
	{"MediumPurple"        ,RGB(147,112,219)},
	{"MediumSeaGreen"      ,RGB( 60,179,113)},
	{"MediumSlateBlue"     ,RGB(123,104,238)},
	{"MediumSpringGreen"   ,RGB(  0,250,154)},
	{"MediumTurquoise"     ,RGB( 72,209,204)},
	{"MediumVioletRed"     ,RGB(199, 21,133)},
	{"MidnightBlue"        ,RGB( 25, 25,112)},
	{"MintCream"           ,RGB(245,255,250)},
	{"MistyRose"           ,RGB(255,228,225)},
	{"Moccasin"            ,RGB(255,228,181)},
	{"NavajoWhite"         ,RGB(255,222,173)},
	{"Navy"                ,RGB(  0,  0,128)},
	{"OldLace"             ,RGB(253,245,230)},
	{"Olive"               ,RGB(128,128,  0)},
	{"OliveDrab"           ,RGB(107,142, 35)},
	{"Orange"              ,RGB(255,165,  0)},
	{"OrangeRed"           ,RGB(255, 69,  0)},
	{"Orchid"              ,RGB(218,112,214)},
	{"PaleGoldenRod"       ,RGB(238,232,170)},
	{"PaleGreen"           ,RGB(152,251,152)},
	{"PaleTurquoise"       ,RGB(175,238,238)},
	{"PaleVioletRed"       ,RGB(219,112,147)},
	{"PapayaWhip"          ,RGB(255,239,213)},
	{"PeachPuff"           ,RGB(255,218,185)},
	{"Peru"                ,RGB(205,133, 63)},
	{"Pink"                ,RGB(255,192,203)},
	{"Plum"                ,RGB(221,160,221)},
	{"PowderBlue"          ,RGB(176,224,230)},
	{"Purple"              ,RGB(128,  0,128)},
	{"Red"                 ,RGB(255,  0,  0)},
	{"RosyBrown"           ,RGB(188,143,143)},
	{"RoyalBlue"           ,RGB( 65,105,225)},
	{"SaddleBrown"         ,RGB(139, 69, 19)},
	{"Salmon"              ,RGB(250,128,114)},
	{"SandyBrown"          ,RGB(244,164, 96)},
	{"SeaGreen"            ,RGB( 46,139, 87)},
	{"SeaShell"            ,RGB(255,245,238)},
	{"Sienna"              ,RGB(160, 82, 45)},
	{"Silver"              ,RGB(192,192,192)},
	{"SkyBlue"             ,RGB(135,206,235)},
	{"SlateBlue"           ,RGB(106, 90,205)},
	{"SlateGray"           ,RGB(112,128,144)},
	{"Snow"                ,RGB(255,250,250)},
	{"SpringGreen"         ,RGB(  0,255,127)},
	{"SteelBlue"           ,RGB( 70,130,180)},
	{"Tan"                 ,RGB(210,180,140)},
	{"Teal"                ,RGB(  0,128,128)},
	{"Thistle"             ,RGB(216,191,216)},
	{"Tomato"              ,RGB(255, 99, 71)},
	{"Turquoise"           ,RGB( 64,224,208)},
	{"Violet"              ,RGB(238,130,238)},
	{"Wheat"               ,RGB(245,222,179)},
	{"White"               ,RGB(255,255,255)},
	{"WhiteSmoke"          ,RGB(245,245,245)},
	{"Yellow"              ,RGB(255,255,  0)},
	{"YellowGreen"         ,RGB(139,205, 50)},
	{NULL,0}
};

char *ConvertFromHTMLCodes(char *szText);
char *ConvertToHTMLCodes(char *szText);
char *ConvertFromUtf8Codes(char *szText);
char *ConvertToUtfCodes(char *szText);
