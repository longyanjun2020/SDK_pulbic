copy .\tng\GenOpt\MStarStudio_options.cfg .\tng\options.cfg
call .\tng\GenOpt\buildOpt_w32_setenv.bat
make -f .\tng\GenOpt\Makefile_CO_MStarStudio AUTO_CLEAN=2
