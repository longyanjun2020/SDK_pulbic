#! /bin/bash

XRG_OPT_HEADER_FN=option.h
GLOBAL_HEADER_FN=global_config.h
XRG_OPT_Header=../tools/XRG/$XRG_OPT_HEADER_FN
XRG_GLOBAL_HEADER=../tools/XRG/$GLOBAL_HEADER_FN
STRIP_PATH=tng/GenOpt/strip/

$STRIP_PATH/remccoms3.sed < $1> $STRIP_PATH/$GLOBAL_HEADER_FN && \
cp -f $XRG_OPT_Header $STRIP_PATH && \
cd $STRIP_PATH && \
./stripcc.exe -n -c "armcc --preinclude $XRG_OPT_HEADER_FN -E $GLOBAL_HEADER_FN" && \
rm -f $XRG_OPT_HEADER_FN && \
cd - && \
mv $STRIP_PATH/$GLOBAL_HEADER_FN $XRG_GLOBAL_HEADER

