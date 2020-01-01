@echo off
c:
cd\
@for /F "delims=" %%I in ("%~dp0") do @set INSTALL_ROOT=%%~fI
set INSTALL_ROOT=c:\
set WD=%INSTALL_ROOT%\CygwinPortable\App\Cygwin
set SHELL=/bin/bash
set DISPLAY=:0
%WD%\bin\mount -bfu %WD%\ /
%WD%\bin\mount -bfu %WD%\bin /usr/bin
%WD%\bin\mount -bfu %WD%\lib /usr/lib


set SDEROOT=%INSTALL_ROOT%MIPSsde
set ARMROOT=%INSTALL_ROOT%ARM

set ARMBIN_ARMSD=%ARMROOT%\RDI\armsd\1.3.1\66\win_32-pentium\armsd.exe
set ARMBIN_AXD=%ARMROOT%\RDI\AXD\1.3.1\98\win_32-pentium\axd.exe
set ARMBIN_PRJ2XML=%ARMROOT%\IDEs\CodeWarrior\RVPlugins\1.0\86\win_32-pentium\converters\RVD\prj2xml.exe
set ARMCONF=%ARMROOT%\RDI\armperip\1.3\50;%ARMROOT%\RVARMulator\ARMulator\1.4.1\206\win_32-pentium;%ARMROOT%\RVARMulator\v6ARMulator\1.4.1\238\win_32-pentium
set ARMDLL=%ARMROOT%\RDI\rdimsvr\1.3.1\91\win_32-pentium;%ARMROOT%\RVARMulator\ARMulator\1.4.1\206\win_32-pentium;%ARMROOT%\RDI\Targets\Remote_A\1.3.1\98\win_32-pentium;%ARMROOT%\RVARMulator\v6ARMulator\1.4.1\238\win_32-pentium
set ARMLMD_LICENSE_FILE=%ARMROOT%\Licenses\license.dat

set RVCT22BIN=%ARMROOT%\RVCT\Programs\2.2\349\win_32-pentium
set RVCT22INC=%ARMROOT%\RVCT\Data\2.2\349\include\windows
set RVCT22LIB=%ARMROOT%\RVCT\Data\2.2\349\lib

set path=%WD%\bin;%WD%\usr\X11R6\bin;%ARMROOT%\RVCT\Programs\2.2\349\win_32-pentium;%path%
set CYGWIN=title ntea
set HOME=%INSTALL_ROOT%\CygwinPortable\home
cd %HOME%
subst r: %1
bash --login -i -c '/cygdrive/r/build_emmi.sh %2'
