@echo off
rem $Id: 0build.bat,v 1.7 2006/05/23 19:24:20 stievie Exp $

rem This batch file assumes that
rem   * vcvars32.bat
rem   * nmake.exe
rem is somewhere in you PATH environment

rem Set required environment variables
call vcvars32.bat
if errorlevel 1 goto novars

rem Build BibEdt and all dependent files
call nmake.exe /f bibedt.mak CFG="bibedt - Win32 Release"
if errorlevel 1 goto cerr

goto exit

:novars
echo vcvars32.bat not found
pause
goto exit

:cerr
echo Some error occurred while compiling
pause

:exit
