#!/bin/bash

#datestr=`aeon-elf-gcc -v 2>&1 | grep "^gcc version" | grep -o "(.*)" | grep -o "[^(].*[^)]" | sed 's/ver.*//'`
datestr=`aeon-elf-gcc -v 2>&1 | sed -n '/^gcc version/{s#^.*(\(.*\)).*$#\1#g;s/ver.*//;p}'`

if [ "$datestr"X == X ]
then
    echo "aeon-elf-gcc not found in your path."
    exit 0
fi

datenum=`date -d "$datestr" +%Y%m%d`

if [ $datenum -ge 20100601 ]
then
    echo n
else
    echo y
fi
