move customer\src\mcp_drv.c MStarLib\mcp_drv.tmp
move mak\customer.mak MStarLib\customer.tmp
move mak\common.mak MStarLib\common.tmp
del /f/s *.c *.asm *.mak
del /f/q .dependencies_b2\*.*
del /f/q out_b2\*.* 
move MStarLib\mcp_drv.tmp customer\src\mcp_drv.c
move MStarLib\customer.tmp mak\customer.mak
move MStarLib\common.tmp mak\common.mak
