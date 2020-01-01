#! /bin/bash
#:;;
#:;;

branchRoot=/cygdrive/r/proj
echo $branchRoot

product=$1
echo $product

if ( [[ "$?" != "0" ]] ); then
  exit 1
fi

cd $branchRoot
./tng/configure.pl $product

echo ==================================================================
echo Start build code 
echo ==================================================================
make clean
if [ -e sc/lib ]; then
  make release_speed
elif [ -e lib ]; then
  make quick
else
  make speed
fi