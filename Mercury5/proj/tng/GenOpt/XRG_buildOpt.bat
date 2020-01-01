copy .\tng\GenOpt\XRG_options.cfg .\tng\options.cfg
call .\tng\GenOpt\buildOpt_w32_setenv.bat
make -f .\tng\GenOpt\Makefile_CO_XRG AUTO_CLEAN=2
