Two method to generate test load easily.
The test load will be generated in path .\build\$product\out\testload

1. From cygwin command line
	please type "./tng/ReleaseTestLoadFromOut.pl" in cygwin
	the default product is latest product you setup by configure.pl
	You can press enter to use default or input other product name which you want to generate test load.
	for "Need JTAG data?[n]:", you can press enter if you do not copy *.axf files which are used by JTAG.
	Otherwise, please type y.
	

2. Execute batch file in product out folder
	there are two bat files which will be copied to product out folder by configure.pl
	GenerateTestLoadFromOut_JTAG.bat: it will generate test load which includes *.axf for JTAG usage.
	GenerateTestLoadFromOut_nonJTAG.bat: it will generate test load which does not includes *.axf for JTAG usage.

Please note: .\build\$product\out\testload will be cleared first for each time you generate a new test load.