================================================================================
BibEdt ReadMe
Copyright (C) 2005-2006, Stefan Ascher <stievie[at]users[dot]sourceforge[dot]net>
http://bibedt.sourceforge.net/
================================================================================

--------------------------------------------------------------------------------
Contents
--------------------------------------------------------------------------------

  1  Description
  2  License
  3  Installation
     3.1  Uninstall
  4 Building from source

--------------------------------------------------------------------------------
1 Description
--------------------------------------------------------------------------------

A very simple program to edit BibTeX files. For documention see the manual for
this program. You can download it from
http://sourceforge.net/project/showfiles.php?group_id=142263&package_id=161101
and put it into the same directory as the program. Use always one with a matching
version number, or, if there is none, the previous version.

--------------------------------------------------------------------------------
2 License
--------------------------------------------------------------------------------

BibEdt is subject to the GNU General Public License Version 2 (the "License");
you may not use this project except in compliance with the License. You may obtain
a copy of the License at http://www.gnu.org/copyleft/gpl.html.

The BibTeX lexer (lexbib) may alternatively to the GPL also be used under the
same license as Scintilla.

--------------------------------------------------------------------------------
3 Installation
--------------------------------------------------------------------------------

There are two ways to install this software:

  1. Download [1] the Setup program, start it and follow the instructions on the
     screen. This package contains all required files, no additional downloads
     are needed.
  2. Download [1] the binary distribution of the program. Just unzip the file
     bebin-version.zip (binary) or besrc-version.zip (source) to any directory
     and run it from there.
     When you download BibEdt the first time you must also download [2] an additional
     package with some libraries BibEdt uses. This package has the filename
     yazbin-ver.zip. You must download this package and extract the files into
     the directory of BibEdt.

[1] http://sourceforge.net/project/showfiles.php?group_id=142263&package_id=156662
[2] http://sourceforge.net/project/showfiles.php?group_id=142263&package_id=162662

3.2 Uninstall
-------------

  1. If you've used the Setup program then open the Control Panel Applet "Software",
     locate BibEdt XX (XX is the version number) in the list and double click on
     it. Alternatively you can also use the Uninstall icon in the BibEdt program
     group of the Start menu. This will uninstall BibEdt with all files and registry
     keys.
  2. If you didn't use the Setup program but the ZIP package then just delete the
     extracted and created files and the registry key:
     HKEY_CURRENT_USER\Software\Ascher\BibEdt.

--------------------------------------------------------------------------------
4 Building from source
--------------------------------------------------------------------------------

See building.txt in the source distribution for instructions and requirements.

================================================================================
$Id: readme.txt,v 1.73 2006/04/18 21:31:18 stievie Exp $
