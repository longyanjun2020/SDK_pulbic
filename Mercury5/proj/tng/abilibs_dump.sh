#!/bin/sh

VERSION=$1
OUT=$2
CFLAGS=$3
#PATH_H=$4
PRODUCT=$OUT"/.."

DRV_PUB_H=`ls -aR ./sc/driver/drv | grep "/pub:" | sed "s/\(.*\):/\1/"`
SYS_PUB_H=`ls -aR ./sc/system | grep "/pub:" | sed "s/\(.*\):/\1\//"`
MID_PUB_H=`ls -aR ./sc/middleware | grep "/pub:" | sed "s/\(.*\):/\1/"`
APP_PUB_H=`ls -aR ./sc/application | grep "/pub:" | sed "s/\(.*\):/\1/"`
TSV_PUB_H=`ls -aR ./sc/telserv | grep "/pub:" | sed "s/\(.*\):/\1/"`

PUB_H=$DRV_PUB_H" "$SYS_PUB_H" "$MID_PUB_H" "$APP_PUB_H" "$TSV_PUB_H
for h in $PUB_H; do
    PATH_H+="$h "
done
#echo $PATH_H

GCC_OPTIONS=`echo "$CFLAGS" | sed "s/  */\\\\\\n/g"`
PATH_H=$PATH_H" ./build"
PATH_H=$PATH_H" ./sc/application/mmi/resource"
PATH_H=$PATH_H" ./sc/application/mmi/resource/resourceLib"
PATH_H=$PATH_H" ./sc/application/3rd/mserv/inc"
PATH_H=$PATH_H" ./sc/application/3rd/mserv/itf"
PATH_H=$PATH_H" ./sc/telserv/vml/itf"
PATH_H=$PATH_H" ./sc/telecom/cc/itf_open"
PATH_H=$PATH_H" ./sc/telecom/ip/itf_open"
PATH_H=$PATH_H" ./sc/application/sys/resmgr/inc/socketresmgr"
PATH_H=$PATH_H" ./sc/application/sys/resmgr/inc/socketcore"
PATH_H=$PATH_H" ./sc/application/3rd/java/common/inc"
PATH_H=$PATH_H" ./sc/application/3rd/sdk/inc"
PATH_H=$PATH_H" ./sc/application/3rd/utility/i18n/inc"
PATH_H=$PATH_H" ./sc/application/3rd/wap/itf"
PATH_H=$PATH_H" ./sc/application/email/inc"
PATH_H=$PATH_H" ./sc/application/mms/inc"
PATH_H=$PATH_H" ./sc/application/wap/inc"
PATH_H=$PATH_H" ./sc/application/mmi/AppLauncher/inc"
PATH_H=$PATH_H" ./sc/application/mmi/common/cfg"
PATH_H=$PATH_H" ./sc/application/mmi/mae/src"
PATH_H=$PATH_H" ./sc/application/mmi/widgets/inc"
PATH_H=$PATH_H" ./sc/application/mmi/common/inc"
PATH_H=$PATH_H" ./sc/application/sys/ResMgr/inc/ABL"
PATH_H=$PATH_H" ./sc/application/sys/ResMgr/inc/HAL"
PATH_H=$PATH_H" ./sc/application/sys/ResMgr/inc/MediaCmd"
PATH_H=$PATH_H" ./sc/application/sys/ResMgr/inc/Util"
PATH_H=$PATH_H" ./sc/application/sys/ResMgr/inc"
PATH_H=$PATH_H" ./sc/application/sys/ResMgr/inc/ResMgr"
PATH_H=$PATH_H" ./sc/middleware/mmmanager/inc"
PATH_H=$PATH_H" ./sc/driver/hal/msw8533x/io/pub"
PATH_H=$PATH_H" ./sc/driver/hal/msw8533x/int/pub"
PATH_H=$PATH_H" ./sc/application/cus_app/sc/inc"
# for boot_log_defaut_dimention.txt
PATH_H=$PATH_H" "$PRODUCT
INCLUDE_PATHS=`echo "$PATH_H" | sed "s/\/\//\//g"`
INCLUDE_PATHS=`echo "$INCLUDE_PATHS" | sed "s/  */\\\\\\n/g"`

#echo $INCLUDE_PATHS

XML_FILE=${OUT}abilib_mobile.xml
MOBILE_HEADERS=${OUT}abi_head_mobile.c

echo "" > $MOBILE_HEADERS
cp ./tng/abi_lib_template.xml $XML_FILE 
sed -i "/<\/version>/i $VERSION" "$XML_FILE"
sed -i "/<\/libs>/i $OUT" "$XML_FILE"
sed -i "/<\/include_paths>/i $INCLUDE_PATHS" "$XML_FILE"
sed -i "/<\/gcc_options>/i -std=c++0x" "$XML_FILE"
sed -i "/<\/gcc_options>/i $GCC_OPTIONS" "$XML_FILE"

#echo $PATH_H
INC_PATH=
for path in $PATH_H; do
    INC_PATH=$INC_PATH" -I"$path
done

module=
for headers in `ls ${OUT}abi_headers_*.c`; do
    headers_h=${headers}".h"
    cp ${headers} ${headers_h}
    if [ $VERSION = "test" ]; then
        # to merge this as a sub function of abi-compliance-checker.pl
        echo "i686-unknown-linux-gnu-g++ -std=c++0x -c $headers"
        i686-unknown-linux-gnu-g++ -std=c++0x -c $headers  $INC_PATH $CFLAGS
    fi
    sed -i "/<\/headers>/i $headers_h" "$XML_FILE"
    echo "#include \"$headers_h\"" >> $MOBILE_HEADERS
done

if [ $VERSION = "test" ]; then
    echo "compile $MOBILE_HEADERS with i686-unknown-linux-gnu-g++"
    i686-unknown-linux-gnu-g++ -std=c++0x -c $MOBILE_HEADERS $INC_PATH -I./ $CFLAGS
else
    echo "./tng/abi-compliance-checker.pl -l mobile -dump ${XML_FILE}"
    ./tng/abi-compliance-checker.pl -l mobile -dump ${XML_FILE}
fi
