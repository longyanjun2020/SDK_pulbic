@echo on
echo %~dp0
echo %1
echo %2
cd %~dp0\..\..\proj
call buildCus_w32_setenv.bat
set CUS_LP_NAME=%2
make -f Makefile_cus mmi_cus_addition