@perl -v > NUL
@@IF ERRORLEVEL 1  GOTO L_no_perl

@CD sc\core\system\net
@perl bin\cfg-compile.pl -o lib/inc/auto_syscfg.h cfg/amn_system.ucos.conf
@ECHO "Check the auto_syscfg.h is generated automatically"
@SET OUTPUT_SYSCFG=lib\inc\auto_syscfg.h

@ECHO.
@REM @ECHO "Check the %OUTPUT_SYSCFG% is generated automatically"
@IF EXIST %OUTPUT_SYSCFG% ( @echo %OUTPUT_SYSCFG% is generated.
) else (
	@echo ERROR on generating %OUTPUT_SYSCFG%
)
@ECHO.

@REM @mkdir http\chp_C
@REM @perl bin\chp-compile.pl -o http/chp_C/ http/chp/
@REM @ECHO "Check the CHP files are generated automatically"
@REM @DIR http\chp_C

@GOTO End


:L_no_perl
@ECHO "No PERL executable exists in your PATH, please install it first"
@ECHO "You may download from here: http://www.activestate.com/activeperl/downloads"

GOTO End


:End
@PAUSE
