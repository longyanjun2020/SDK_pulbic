#!/bin/sh

# String filter tools, just keep need
# keep exter function list

sed -n -e '/D extr_/p' zlib_rom.sym > zlib_extr_fun.h
sed -e 's/^..................//' zlib_extr_fun.h > a.sym
sed -e 's/$/,/' a.sym > zlib_extr_fun.h
rm -f a.sym
mv -f zlib_extr_fun.h inc/

sed -n -e '/D extr_/p' zlib_rom.sym > zlib_extr_fun_d.h
sed -e 's/^..................//' zlib_extr_fun_d.h > a.sym
sed -e 's/^/extern void /' a.sym > zlib_extr_fun_d.h
sed -e 's/$/(void);/' zlib_extr_fun_d.h > a.sym
rm -f zlib_extr_fun_d.h
mv a.sym inc/zlib_extr_fun_d.h

