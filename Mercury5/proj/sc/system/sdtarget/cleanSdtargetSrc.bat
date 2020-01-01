ren wintarget\src\dwl_version.c dwl_version.ctmp
ren wintarget\customer\src\mcp_drv.c mcp_drv.ctmp
ren backlight\drv\src\*.c *.ctmp
ren backlight\hal_b5\src\*.c *.ctmp
ren backlight\hal_b9\src\*.c *.ctmp
ren lcd\drv\src\*.c *.ctmp
ren lcd\hal_b5\src\*.c *.ctmp
ren lcd\hal_b9\src\*.c *.ctmp

ren wintarget\mak\customer.mak customer.mtmp
ren wintarget\version*.mak version*.mtmp
ren wintarget\mak\swversion.mak swversion.mtmp
ren lcd\*.mak *.mtmp
ren backlight\*.mak *.mtmp

ren lib_b5\Inc.mak Inc.mtmp
ren lib_b9\Inc.mak Inc.mtmp

mkdir temp
copy Makefile temp\Makefile
copy Makefile.opt temp\Makefile.opt
copy Makefile_b5 temp\Makefile_msw853xb
copy Makefile_b5_cus temp\Makefile_msw853xb_cus
copy Makefile_b9 temp\Makefile_msw8556x
copy Makefile_b9_cus temp\Makefile_msw8556x_cus
copy scatter-emi_nor.desc temp\scatter-emi_nor.desc

del /f/s *.c *.asm *.mak *.s *.i *.S *.I
del /f /Q Makefile* Makefile*.* *.txt *.desc *.bin *.axf *.pl *.sh *.ini cleanSrc.bat

rmdir /S /Q bootldr bootstrap bootrom release_binaries
rmdir /S /Q dep_b5 out_b5 dep_msw853xb out_msw853xb dep_b9 out_b9 dep_msw8556x out_msw8556x

copy temp\*.* .\
rmdir /S /Q temp

ren wintarget\src\dwl_version.ctmp dwl_version.c
ren wintarget\customer\src\mcp_drv.ctmp mcp_drv.c
ren backlight\drv\src\*.ctmp *.c
ren backlight\hal_b5\src\*.ctmp *.c
ren backlight\hal_b9\src\*.ctmp *.c
ren lcd\drv\src\*.ctmp *.c
ren lcd\hal_b5\src\*.ctmp *.c
ren lcd\hal_b9\src\*.ctmp *.c

ren wintarget\mak\customer.mtmp customer.mak
ren wintarget\version*.mtmp version*.mak
ren wintarget\mak\swversion.mtmp swversion.mak
ren lcd\*.mtmp *.mak
ren backlight\*.mtmp *.mak

ren lib_b5\Inc.mtmp Inc.mak
ren lib_b9\Inc.mtmp Inc.mak

ren lib_b5 lib_msw853xb
ren lib_b9 lib_msw8556x