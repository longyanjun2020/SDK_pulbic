
ROM 0x1c000000 0x00020000 ;256KB
{
	;ZLIB_ROM_EXEC   0x1c0000c0 0x3400 ; = 13kB ; for Simulation, B3
	;ZLIB_ROM_EXEC   0x1c0034c0 0x3400 ; = 13kB ; for refer
	ZLIB_ROM_EXEC   0x04008c00 0x2800 ; = 10kB ; for ROM
	{
		* (+RO)
		* (+RW)
		* (+ZI)
	}
}

