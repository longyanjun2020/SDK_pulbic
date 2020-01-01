/// **************************************************************************
/// \file fms_lowl_macros.h
/// \brief Common macro-commands for HW access in low-level functions
///
///
///


#ifndef _098639ccff492debb6dfedc892324b3c_included_fms_lowl_macros_h
#define _098639ccff492debb6dfedc892324b3c_included_fms_lowl_macros_h

/**
  * @brief Loop timing value before erase suspend on WHAT2 for fms_Intel_Erase
  */
#define ERASE_MAX_ITERATIONS_INTEL     350
/**
  * @brief Loop timing value before erase suspend on WHAT2 for fms_Amd_Erase
  */
#define ERASE_MAX_ITERATIONS_AMD       115
/**
  * @brief Loop timing value before erase suspend on WHAT2 for fms_Toshiba_Erase
  */
#define ERASE_MAX_ITERATIONS_TOSHIBA   100


#define FMS_OFFSET_TO_DEVICEID      (0x01<<1)   ///< Offset to device ID in electronic signature
#define FMS_OFFSET_TO_DEVICEID_2    (0x0E<<1)   ///< Offset to device 2nd ID in Spansion electronic signature
#define FMS_OFFSET_TO_DEVICEID_3    (0x0F<<1)   ///< Offset to device 3rd ID in Spansion electronic signature
#define FMS_OFFSET_TO_PROTECTFLAG   (0x02<<1)   ///< Offset to block protection status in electronic signature
/**
  * @brief Offset to protection register (unique device number) in electronic signature
  */
#define FMS_OFFSET_TO_ELECSIGNATURE (0x81<<1)

#define FMS_CFI_OFFSET_TO_QUERYSTR_Q (0x10<<1)  ///< Offset to 'Q' in CFI query result
#define FMS_CFI_OFFSET_TO_QUERYSTR_R (0x11<<1)  ///< Offset to 'R' in CFI query result
#define FMS_CFI_OFFSET_TO_QUERYSTR_Y (0x12<<1)  ///< Offset to 'Y' in CFI query result
#define FMS_CFI_OFFSET_TO_CMDSETID   (0x13<<1)  ///< Offset to command set code in CFI query result


#define FMS_SAMSUNG_2883_PROTECT     (0x02<<1)
#define FMS_SAMSUNG_2883_UNPROTECT (0x42<<1)
#define FMS_SAMSUNG_2883_PROTECT_CMD   0x60


/****************************************************************************/
/* COMMON MACRO FUNCTIONS                                                   */
/****************************************************************************/

/**
  * @brief Common query CFI command
  *
  * The offset is done for AMD command set flash devices
  * and Intel ones don't care
  *
  * @param _ADDR_ Address within the device to query
  */
#define fms_Cmd_CfiQuery( _ADDR_ ) do{\
        *(volatile u8*)( FMS_ADDR_KEEPHIGH(_ADDR_) | (0x555L<<1)) = 0x98;\
    }while(0)


/****************************************************************************/
/* COMMON MACRO FUNCTIONS FOR INTEL                                         */
/****************************************************************************/
/**
  * @brief Issue a "reset" to return in Read Array mode
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Intel_Reset(_ADDR_)       do { *(volatile u8*)(_ADDR_) = 0xFF; } while(0)
/**
  * @brief Get the status register
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Intel_ReadStatus(_ADDR_) ( *(volatile u8*)(_ADDR_) )
/**
  * @brief Clear the status register's errors
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Intel_ClearStatus(_ADDR_) do { *(volatile u8*)(_ADDR_) = 0x50; } while(0)
/**
  * @brief Enter in electronic signature mode
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Intel_AutoSelect( _ADDR_ ) do{\
        *(volatile u8*)(_ADDR_) = 0x90;\
    }while(0)

/****************************************************************************/
/* COMMON CONSTANT DEFINE FOR AMD                                            */
/****************************************************************************/

#define FMS_ADDOFF_555 (0x555L<<1)  ///< Special address 0x555 shifted because of 16-bit access
#define FMS_ADDOFF_AAA (0x2AAL<<1)  ///< Special address 0xAAA shifted because of 16-bit access
#define FMS_DATA_AA    0xAA         ///< Special value '0xAA'
#define FMS_DATA_55    0x55         ///< Special value '0x55'

// yanni add start
#define NOR_WRITE_BUFFER_LOAD_CMD                  0x25
#define NOR_WRITE_BUFFER_PGM_CONFIRM_CMD   0X29
// yanni add end
/****************************************************************************/
/* COMMON MACRO FUNCTIONS FOR AMD                                           */
/****************************************************************************/

/* Unlock write cycles for AMD command set flashs */
/**
  * @brief Flash operation prolog
  *
  * Common flash operations prolog for AMD command set flash devices
  * @param _ADDR_ Address within the flash device
  */
#define fms_InitWriteCmdSeq( _ADDR_ ) do{                     \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555 ) = FMS_DATA_AA; \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_AAA ) = FMS_DATA_55; \
    }while(0)

/**
  * @brief Enter in electronic signature mode
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_AutoSelect( _ADDR_ ) do{           \
        fms_InitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( (_ADDR_) & (~0x7FFUL) ) | FMS_ADDOFF_555) = 0x90; \
    }while(0)

/**
  * @brief Return in read array mode
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_Reset( _ADDR_ ) do{ *(volatile u8*)(_ADDR_) = 0xF0; }while(0)

/**
  * @brief Issue a word program command
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_WordProg( _ADDR_, _DATA_) do{      \
        fms_InitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0xA0; \
        *(volatile u16*)(_ADDR_) = (u16)(_DATA_);          \
    }while(0)
#define fms_Cmd_Auto_Page_Prog( _ADDR_, _DATA_) do{      \
        fms_InitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0xE6; \
    }while(0)


/**
  * @brief Issue a block erase command
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_BlockErase( _ADDR_ ) do{           \
        fms_InitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x80; \
        fms_InitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)(_ADDR_) = 0x30;                    \
    }while(0)

/**
  * @brief Issue an erase suspend command
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_EraseSuspend( _ADDR_ ) do{ *(volatile u8*)(_ADDR_) = 0xB0; }while(0)
/**
  * @brief Issue an erase resume command
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_EraseResume( _ADDR_ )  do{ *(volatile u8*)(_ADDR_) = 0x30; }while(0)

// FIXME (not only for Toshiba)
/**
  * @brief Enter in security block mode (Toshiba)
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_EnterSecSi( _ADDR_ )   do{         \
        fms_InitWriteCmdSeq( (_ADDR_) );                     \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x88; \
    }while(0)

/**
  * @brief Exit the security block mode (Toshiba)
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Amd_ExitSecSi( _ADDR_ )   do{ \
        fms_Cmd_Amd_AutoSelect( (_ADDR_) );          \
        *(volatile u8*)(_ADDR_) = 0x00;           \
    }while(0)

/**
  * @brief Volatie sector protection Entry (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Spansion_Dyb_Entey( _ADDR_ )   do{ \
        fms_InitWriteCmdSeq((_ADDR_));\
        *(volatile u8*)( (_ADDR_ ) | FMS_ADDOFF_555) = 0xE0; \
    }while(0)

/**
  * @brief Volatie sector protection Exit (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Spansion_Dyb_Exit( _ADDR_ )   do{ \
        *(volatile u8*)(_ADDR_) = 0x90;\
        *(volatile u8*)(_ADDR_) = 0x00;\
    }while(0)



/**
  * @brief Volatie sector protection set (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Spansion_Dyb_Set( _ADDR_ )   do{ \
        *(volatile u8*)(_ADDR_) = 0xA0;\
        *(volatile u8*)(_ADDR_ ) = 0x00;\
    }while(0)


/**
  * @brief Volatie sector protection Clear (Spansion)
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Spansion_Dyb_Clear( _ADDR_ )   do{ \
        *(volatile u8*)(_ADDR_) = 0xA0;\
        *(volatile u8*)(_ADDR_ ) = 0x01;\
    }while(0)


// yanni add start
/**
  * @brief Buffer program  (Spansion)
  *
  * @param _ADDR_ Targeted address
  */



#define fms_Cmd_Write_buffer( _ADDR_,_OFFSET_)   do{ \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555 ) = FMS_DATA_AA;\
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_AAA ) = FMS_DATA_55;\
        *(volatile u8*)(_ADDR_+_OFFSET_)=NOR_WRITE_BUFFER_LOAD_CMD;\
    }while(0)




/**
  * @brief Buffer program  (Spansion)
  *
  * @param _ADDR_ Targeted address
  */

#define flash_write( _ADDR_,_OFFSET_,_DATA_)   do{ \
        *(volatile u16*)(_ADDR_+_OFFSET_)=(u16)(_DATA_);\
    }while(0)


#define flash_read( _ADDR_,_OFFSET_)   do{ \
        *(volatile u16*)(_ADDR_+_OFFSET_);\
    }while(0)


/**
  * @brief Buffer program  (Spansion)
  *
  * @param _ADDR_ Targeted address
  */


#define fms_ProgramBufferToFlashCmd( _ADDR_,_OFFSET_)   do{ \
        *(volatile u8*)(_ADDR_+_OFFSET_)=NOR_WRITE_BUFFER_PGM_CONFIRM_CMD;\
    }while(0)


/**
  * @brief Samsung_2833_protect
  *
  * @param _ADDR_ Targeted address
  */
#define fms_Cmd_Samsung_2833_protect( _ADDR_ )   do{ \
        *(volatile u8*)( (_ADDR_ ) ) = FMS_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) ) = FMS_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) | FMS_SAMSUNG_2883_PROTECT) = FMS_SAMSUNG_2883_PROTECT_CMD; \
    }while(0)
/**
  * @brief Samsung_2833_unprotect
  *
  * @param _ADDR_ Targeted address
  */

#define fms_Cmd_Samsung_2833_unprotect( _ADDR_ )   do{ \
        *(volatile u8*)( (_ADDR_ ) ) = FMS_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) ) = FMS_SAMSUNG_2883_PROTECT_CMD; \
        *(volatile u8*)( (_ADDR_ ) | FMS_SAMSUNG_2883_UNPROTECT) = FMS_SAMSUNG_2883_PROTECT_CMD; \
    }while(0)

/****************************************************************************/
/* MACROs for TOSHIBA_TV00570002CDGB                                        */
/****************************************************************************/

#define FMS_TOSHIBA_TV00570002CDGB_OFFSET_TO_MANUFACTURE_CODE    (0x00<<1)   ///< Offset to device Manufacture Code
#define FMS_TOSHIBA_TV00570002CDGB_OFFSET_TO_DEVICE_CODE         (0x01<<1)   ///< Offset to device Device Code
#define FMS_TOSHIBA_TV00570002CDGB_OFFSET_TO_PROTECTFLAG         (0x02<<1)   ///< Offset to block protection status

/**
  * @brief protect a block
  *
  * @param _ADDR_ Targeted address
  */

#define fms_Cmd_TOSHIBA_TV00570002CDGB_ProtectBlock(_ADDR_) do { \
        fms_InitWriteCmdSeq( (_ADDR_) );                        \
        *(volatile u8*)(_ADDR_ | FMS_ADDOFF_555) = 0x60;    \
        *(volatile u8*)(_ADDR_ | FMS_TOSHIBA_TV00570002CDGB_OFFSET_TO_PROTECTFLAG) = 0x68;                \
    } while(0)

/**
  * @brief unprotect a block
  *
  * @param _ADDR_ Targeted address
  */

#define fms_Cmd_TOSHIBA_TV00570002CDGB_UnProtectBlock(_ADDR_) do{ \
        fms_InitWriteCmdSeq( (_ADDR_) );                        \
        *(volatile u8*)( ( FMS_ADDR_KEEPHIGH(_ADDR_) ) | FMS_ADDOFF_555) = 0x60;    \
        *(volatile u8*)(_ADDR_ | FMS_TOSHIBA_TV00570002CDGB_OFFSET_TO_PROTECTFLAG) = 0x60;                \
    } while(0)

#define fms_Cmd_TOSHIBA_TV00570002CDGB_Hidden_Rom_Exit(_ADDR_) do {\
        fms_Cmd_Amd_AutoSelect(_ADDR_); \
        *(volatile u8*)((_ADDR_) | FMS_ADDOFF_555) = 0x00; \
    } while (0)

#define fms_TOSHIBA_TV00570002CDGB_ReadID(value, u32Addr, offset) \
    do { \
        fms_Cmd_Amd_AutoSelect((u32Addr)); \
        (value) = *(volatile u16*)((u32Addr) | (offset)); \
        fms_Cmd_Amd_Reset(u32Addr); \
    } while (0)

#define fms_TOSHIBA_TV00570002CDGB_GetProtectStatus(status, u32Addr) \
    fms_TOSHIBA_TV00570002CDGB_ReadID(status, u32Addr, FMS_TOSHIBA_TV00570002CDGB_OFFSET_TO_PROTECTFLAG)


#endif /* ! _098639ccff492debb6dfedc892324b3c_included_fms_lowl_macros_h */
