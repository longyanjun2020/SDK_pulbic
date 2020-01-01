#!/bin/sh

if [ "$1" == "dlm_bin" ]; then

#echo make dlm_bin DLM_KERNEL_LST="$2 $3 $4 $5 $6 $7 $8 $9"
make dlm_bin DLM_KERNEL_LST="$2 $3 $4 $5 $6 $7 $8 $9"

elif [ "$1" == "dpm_bin_8830n" ]; then

#echo make PartialMake_fast RELEASE_PROCESS=0 DPM=$2 L1=$2
make PartialMake_fast RELEASE_PROCESS=0 DPM=$2 L1=$2
#echo make link_dpm DPM=$2
make link_dpm DPM=$2

elif [  "$1" == "ABI_VER" ]; then

make PartialMake_fast  RELEASE_PROCESS=0 $1 \
L1=$2 \
L2=$3 \
L3=$4 \
L4=$5 \
L5=$6 \
L6=$7 \
L7=$8 \
L8=$9

elif [ "$1" == "ap" ]; then
    make PartialMake_fast RELEASE_PROCESS=0 \
        L1=$1 \
        L2=$2 \
        L3=$3 \
        L4=$4 \
        L5=$5 \
        L6=$6 \
        L7=$7 \
        L8=$8 \
        L9=$9

elif [ "$1" == "NO_FB" ]; then

make PartialMake_fast  RELEASE_PROCESS=0 DISABLE_FEEDBACK=1 \
L1=$1 \
L2=$2 \
L3=$3 \
L4=$4 \
L5=$5 \
L6=$6 \
L7=$7 \
L8=$8 \
L9=$9

elif [ "$1" == "DELETE" ]; then

if [ "$2" != "" ]; then 
make clean_lib TARGET=$2
fi
if [ "$3" != "" ]; then 
make clean_lib TARGET=$3
fi
if [ "$4" != "" ]; then 
make clean_lib TARGET=$4
fi
if [ "$5" != "" ]; then 
make clean_lib TARGET=$5
fi
if [ "$6" != "" ]; then 
make clean_lib TARGET=$6
fi
if [ "$7" != "" ]; then 
make clean_lib TARGET=$7
fi
if [ "$8" != "" ]; then 
make clean_lib TARGET=$8
fi
if [ "$9" != "" ]; then 
make clean_lib TARGET=$9
fi

else

make PartialMake_fast  RELEASE_PROCESS=0 \
L1=$1 \
L2=$2 \
L3=$3 \
L4=$4 \
L5=$5 \
L6=$6 \
L7=$7 \
L8=$8 \
L9=$9

fi
