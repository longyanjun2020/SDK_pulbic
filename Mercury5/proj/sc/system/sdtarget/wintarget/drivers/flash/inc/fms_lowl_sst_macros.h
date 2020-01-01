/// **************************************************************************
/// \file fms_lowl_sst_macros.h
/// \brief Macro definitions for SST command set
///
///
///

#ifndef _0ca84aab365953f58c8ca988c9cdbb47_included_fms_lowl_sst_macros_h
#define _0ca84aab365953f58c8ca988c9cdbb47_included_fms_lowl_sst_macros_h

/**
  * @brief Issue a sector erase command
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_SST36VF16_SectorErase( _ADDR_ ) do{     \
   fms_InitWriteCmdSeq( (_ADDR_) );                     \
   *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x80; \
   fms_InitWriteCmdSeq( (_ADDR_) );                     \
   *(volatile u8*)(_ADDR_) = 0x30;                      \
}while(0)

/**
  * @brief Issue a sector erase command
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_SST36VF32_SectorErase( _ADDR_ ) do{     \
   fms_InitWriteCmdSeq( (_ADDR_) );                     \
   *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x80; \
   fms_InitWriteCmdSeq( (_ADDR_) );                     \
   *(volatile u8*)(_ADDR_) = 0x50;                      \
}while(0)


#define fms_Cmd_SST36VF16_BlockErase(_X_) fms_Cmd_SST36VF32_SectorErase(_X_)
#define fms_Cmd_SST36VF32_BlockErase(_X_) fms_Cmd_SST36VF16_SectorErase(_X_)

/**
  * @brief Enter in Query Sec ID mode
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_SST_QuerySecID( _ADDR_ )   do{         \
   fms_InitWriteCmdSeq( (_ADDR_) );                    \
   *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x88; \
}while(0)

#define FMS_DEVICECODE_SST_SST36VF1601 0x734B
#define FMS_DEVICECODE_SST_SST36VF1602 0x734A
#define FMS_DEVICECODE_SST_SST36VF3203 0x7354
#define FMS_DEVICECODE_SST_SST36VF3204 0x7353

#define FMS_SECID_OFFSET_SST36VF1601 0
#define FMS_SECID_OFFSET_SST36VF1602 0xC0000
#define FMS_SECID_OFFSET_SST36VF3203 0x100000
#define FMS_SECID_OFFSET_SST36VF3204 0

/**
  * @brief Issue a chip erase command
  *
  * @param _ADDR_ Targeted address (should be flash's base)
  */
#define fms_Cmd_SST_ChipErase( _ADDR_ ) do{           \
   fms_InitWriteCmdSeq( (_ADDR_) );                   \
   *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x80; \
   fms_InitWriteCmdSeq( (_ADDR_) );                   \
   *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x10; \
}while(0)

/**
  * @brief Common query CFI command
  * 
  * This one sets a bank in CFI mode, whereas 
  * the other one can still be read.
  *
  * @param _ADDR_ Address within the device to query
  */
#define fms_Cmd_SST_CfiQuery( _ADDR_ ) do{           \
    fms_InitWriteCmdSeq( (_ADDR_) );                 \
    *(volatile u8*)( (_ADDR_) | (0x555L<<1)) = 0x98; \
}while(0)


#endif /* ! _0ca84aab365953f58c8ca988c9cdbb47_included_fms_lowl_sst_macros_h */
