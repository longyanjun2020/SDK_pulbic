@echo off

@rem set MAKEFLAGS=-w --debug=v --debug=m --debug=j
set MAKEFLAGS=-w
set RCVT22PATH=C:\ARM
set RCVT22INCPATH=%RCVT22PATH%\RVCT\Data\2.2\349\include\windows
set RCVT22BINPATH=%RCVT22PATH%\RVCT\Programs\2.2\349\win_32-pentium
set ARMINC=%RCVT22INCPATH%
set ARMCONF=%RCVT22BINPATH%
set OSTYPE=Win32
rem if NOT EXIST %RCVT22BINPATH%\armcc.exe goto WrongPath

set _MSTARMOBILE_SRCROOT_DIR_=%1
if NOT DEFINED _MSTARMOBILE_SRCROOT_DIR_ set _MSTARMOBILE_SRCROOT_DIR_=%cd%
set _MSTARMOBILE_BUILDTNG_DIR_=%_MSTARMOBILE_SRCROOT_DIR_%\tng
set _MSTARMOBILE_BUILDTOOL_DIR_=%_MSTARMOBILE_SRCROOT_DIR_%\tng\win32
if NOT EXIST %_MSTARMOBILE_BUILDTNG_DIR_% goto Error
if NOT EXIST %_MSTARMOBILE_BUILDTOOL_DIR_% goto Error1

echo Add Envoronment variable
set PATH=%_MSTARMOBILE_SRCROOT_DIR_%;%_MSTARMOBILE_BUILDKIT_DIR_%;%_MSTARMOBILE_BUILDTOOL_DIR_%;%PATH%
echo Finished.
goto Done

:Error
echo Envoronment variable _MSTARMOBILE_BUILDTNG_DIR_ was not defined or the Directory %_MSTARMOBILE_BUILDTNG_DIR_% does not exist !
goto Done

:Error1
echo Envoronment variable _MSTARMOBILE_BUILDTOOL_DIR_ was not defined or the Directory %_MSTARMOBILE_BUILDTOOL_DIR_% does not exist !
goto Done

:WrongPath
echo Can not find "%RCVT22BINPATH%\armcc.exe"!
echo Please check the path setting for ARM compiler
echo RCVT22PATH=%RCVT22PATH%
echo RCVT22INCPATH=%RCVT22INCPATH%
echo RCVT22BINPATH=%RCVT22INCPATH%
echo ARMINC=%RCVT22INCPATH%
echo ARMCONF=%RCVT22BINPATH%
goto Done

:Done
echo on
