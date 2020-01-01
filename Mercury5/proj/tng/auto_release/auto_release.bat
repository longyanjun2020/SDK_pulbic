@echo off

SET PATH=%PATH%;C:\cygwin\bin;

if exist C:\Perl (
	rename C:\Perl Perl_tmp
)

if not exist ReleaseConfigurations.txt (
	echo can not find ReleaseConfigurations.txt
	goto END
)

if not exist genCygwinBash.pl (
	echo can not find genCygwinBash.pl
	goto END
)

perl -x -S ./genCygwinBash.pl /CLEAN_ALL C:/cygwin/home/%user_name%/.bashrc ReleaseConfigurations.txt
perl -x -S ./genCygwinBash.pl /RELEASE_SHELL C:/cygwin/home/%user_name%/.bashrc ReleaseConfigurations.txt

if not exist genShellScript.pl (
	echo can not find genShellScript.pl
	goto END
)
perl -x -S ./genShellScript.pl ReleaseConfigurations.txt %1

if not exist auto_release.sh (
	echo can not find auto_release.sh
	goto END
)
if not exist create_customer_project.sh (
	echo can not find create_customer_project.sh
	goto END
)
if not exist delta_release.sh (
	echo can not find delta_release.sh
	goto END
)
if not exist export_code.sh (
	echo can not find export_code.sh
	goto END
)
if not exist full_release.sh (
	echo can not find full_release.sh
	goto END
)
if not exist release.sh (
	echo can not find release.sh
	goto END
)

PUSHD C:
cd\

if not exist cygwin (
	echo can not find cygwin
	goto END
)

cd C:/cygwin

if not exist cygwin.bat (
	echo can not find cygwin.bat
	goto END
)

call "cygwin.bat"

POPD
perl -x -S ./genCygwinBash.pl /CLEAN_ALL C:/cygwin/home/%user_name%/.bashrc ReleaseConfigurations.txt
perl -x -S ./genCygwinBash.pl /CLEAN_SHELL C:/cygwin/home/%user_name%/.bashrc ReleaseConfigurations.txt

if not exist genCusLib.bat (
	echo can not find genCusLib.bat
)

call "genCusLib.bat"

PUSHD C:
cd\

cd C:/cygwin

call "cygwin.bat"

:END

POPD
perl -x -S ./genCygwinBash.pl /CLEAN_ALL C:/cygwin/home/%user_name%/.bashrc ReleaseConfigurations.txt

if exist C:\Perl_tmp (
	rename C:\Perl_tmp Perl
)

echo finished

