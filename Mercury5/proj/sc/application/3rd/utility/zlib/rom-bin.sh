##!/bin/sh

# binary file turned into header file

./rom_tools/bin2c.exe zlib_rom_final.bin > inc/zlib_rom_final.h
echo -e "\n" >> inc/zlib_rom_final.h

