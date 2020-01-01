@rem Setting VS2005 environment in Cygwin is quite trouble.
@rem Call this batch file directly in makefile instead.

@echo off
if "%VS80COMNTOOLS%" == "" goto end

:build
echo.
call "%VS80COMNTOOLS%\vsvars32.bat"
if errorlevel 1 goto end

vcbuild enum.vcproj Debug
echo.

:end
