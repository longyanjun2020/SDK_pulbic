#!/bin/bash
printHelp() {
	echo -e "\n"
	echo "Usage: . `basename "$BASH_SOURCE"` {lib_name}"
}

if [ -z $1 ]; then printHelp
else

make $1;make log;echo `make log | grep -c warning` "warnings," `make log | grep -c error` errors

fi