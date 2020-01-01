#!/bin/sh

BASE=$1
VERSION=$2

ABI_DUMPS="abi_dumps/"
for lib in `ls $ABI_DUMPS`; do
    echo ./tng/abi-compliance-checker.pl -l ${lib} -d1 ${ABI_DUMPS}${lib}/${lib}_${BASE}.abi.tar.gz -d2 ${ABI_DUMPS}${lib}/${lib}_${VERSION}.abi.tar.gz
    ./tng/abi-compliance-checker.pl -l ${lib} -d1 ${ABI_DUMPS}${lib}/${lib}_${BASE}.abi.tar.gz -d2 ${ABI_DUMPS}${lib}/${lib}_${VERSION}.abi.tar.gz
done

echo ABI-CC done!
