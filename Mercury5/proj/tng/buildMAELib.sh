#!/bin/bash

sync

# To rebuild mae pure lib
echo rebuild mae pure lib
if [ -e sc/application/mmi/MAE/lib/mae.lib ]; then
	echo remove sc/application/mmi/MAE/lib/mae.lib
	rm sc/application/mmi/MAE/lib/mae.lib
fi
echo clean mae
make clean_mae

echo build mae pure lib
make mae_purelib

echo clean mae
make clean_mae

if [ -e sc/application/mmi/MAE/lib/mae.lib ]; then
	echo Great! mae.lib generated.
else
	echo Can NOT find mae.lib
	exit 1
fi


# To checkout the svn which is without MAE source code
echo checkout svn
svn checkout http://svn_tp/svn/MAE/branches/tasks/XMMI_AP/proj/sc/application/mmi/MAE _MAE_BRANCH

if [ -e _MAE_BRANCH ]; then
	echo checkout to _MAE_BRANCH folder successfully!
else
	echo Can NOT checkout to _MAE_BRANCH folder
	exit 1
fi


# To copy all files in _MAE_BRANCH from sc/application/mmi/MAE
echo copy header files
if [ -e tng/copyMAELibHeader.pl  ]; then
	tng/copyMAELibHeader.pl sc/application/mmi/MAE _MAE_BRANCH
else
	echo Can NOT find tng/copyMAELibHeader.pl
	echo remove folder _MAE_BRANCH
	rm -rf _MAE_BRANCH
	exit 1
fi


# To commit the svn
echo commit svn
svn commit _MAE_BRANCH -m "Update mae lib and header files automaitcally"


# To remove the temporary svn files
echo Remove folder _MAE_BRANCH
rm -rf _MAE_BRANCH


echo finish!