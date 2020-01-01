@echo off


if not exist genFileList.pl (
	echo can not find genFileList.pl
	goto END
)
cd ..\
if not exist sc (
	echo can not find sc
	goto END
)
echo generate file list and update make file
perl tng\genFileList.pl FileList.xml sc %1


if not exist tng\replacePattern.pl (
	echo can not find replacePattern.pl
	goto END
)
if not exist FileList.xml (
	echo can not find FileList.xml
	goto END
)
echo replace pattern
perl tng\replacePattern.pl FileList.xml /default/ /%product_name%/


if not exist tng\mergeCode.pl (
	echo can not find mergeCode.pl
	goto END
)
if not exist sc\customer\SZ\profile\%2 (
	echo can not find sc\customer\SZ\profile\%2
	goto END
)
echo compare and merge file list
perl tng\mergeCode.pl sc\customer\SZ\profile\%2 FileList.xml fileChangeLog.txt

	
if not exist fileChangeLog.txt (
	echo file list no update
)
if exist fileChangeLog.txt (
	echo file list changed: fileChangeLog.txt
	echo sc\customer\SZ\profile\%2 is update!
)
