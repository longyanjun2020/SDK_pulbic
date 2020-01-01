FLASH 0x00000000
{
  ; Flash
  ROM_DSP_TEAK_SPAT_SECTION 0x00000000 FIXED
  {
    *(hwldsp_path_info)
  }

  ROM +0x0
  {
    * (+RO)
  }
}

