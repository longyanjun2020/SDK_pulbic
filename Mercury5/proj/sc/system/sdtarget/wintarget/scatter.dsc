;
; Scatter description file for V2751/B1 downloader
;
;

; Let's try in internal RAM external RAM, with MEM0 chip select
DOWNLOADER 0x00000000 
{
	RO 0x0                  ; load address in remapped area
	{
	    dwl_boot.o (AAA_vectors, +First)
		* (+RO)                      ; can be partially in ITCM because of +0 use (mandatory, root region)
		* (Veneer$$Code)
	}
	RW +0         ; 512 kB data in external RAM (in fact internal)
	{
		* (+RW)
	}
	RW_STATICBOOT +0x0 UNINIT
	{
		* (STATICBOOT)
	}

	TTB    +0 UNINIT 0x4000  ; level 1 translation table, must be aligned on 16 KB boundary 
	{
		* (TTB)
	}

	ZI +0         ; 512 kB data in external RAM (in fact internal)
	{
		* (+ZI)
	}
	HEAP +0x0 UNINIT
	{
		dwl_malloc.o (+ZI)		; Uninitialised ZI byte
	}					; from dwl_malloc.c
						; to mark heap's start
  VERSION +0
  {
    *(SWVERSION)
  }
  ; internal ram
  IRAM_SECTION 0x08000100  UNINIT 0x2000 ; = 8 kB = 1 bank of 8 kB
  {
    dwl_frame.o (inflatebuffer) ; memory bloc for inflate buffer
  }
}


