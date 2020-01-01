#!/bin/bash

sync


if [ -e tng/genFileList.pl ] && [ -e sc ]; then
	echo generate file list and update make file
	tng/genFileList.pl FileList.xml sc $1
else
	echo can not find tng/genFileList.pl or sc
	exit 1
fi

if [ -e tng/replacePattern.pl ] && [ -e FileList.xml ]; then
	echo replace pattern
	tng/replacePattern.pl FileList.xml /default/ /%product_name%/
else
	echo can not find tng/replacePattern.pl or FileList.xml
	exit 1
fi
		
if [ -e tng/mergeCode.pl ] && [ -e sc/customer/default/profile/$2 ]; then
	echo compare and merge file list
	tng/mergeCode.pl sc/customer/default/profile/$2 FileList.xml fileChangeLog.txt
else
	echo can not find tng/mergeCode.pl or sc/customer/default/profile/$2
	exit 1
fi
		
if [ -e fileChangeLog.txt ]; then
	echo file list changed: fileChangeLog.txt
	echo sc/customer/default/profile/$2 is update!
	exit 1
else
	echo file list no update
fi