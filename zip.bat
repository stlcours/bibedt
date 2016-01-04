@echo off

rem $Id: zip.bat,v 1.9 2006/07/30 20:27:30 stievie Exp $

rem We use 7-Zip to compress the files, because it's Free, mainly for this reason.
rem It may be downloaded from http://www.7-zip.org/.

if not exist output mkdir output

rem Binary
cd Release
if exist ..\output\bebin%1.zip del ..\output\bebin%1.zip
"%PROGRAMFILES%\7-Zip\7z.exe" a -tzip -mx ..\output\bebin%1.zip @..\zipbin
if errorlevel 1 goto nozip

rem Source
cd ..
if exist output\besrc%1.zip del output\besrc%1.zip
"%PROGRAMFILES%\7-Zip\7z.exe" a -tzip -mx output\besrc%1.zip @zipsrc

rem Documentation
cd doc
if exist ..\output\bedoc%1.zip del ..\output\bedoc%1.zip
"%PROGRAMFILES%\7-Zip\7z.exe" a -tzip -mx ..\output\bedoc%1.zip .\bibedt.pdf
goto exit

:nozip
echo 7-Zip not found, get it from http://www.7-zip.org/
pause

:exit
