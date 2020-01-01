////////////////////////////////////////////////////////////////////////////////
/// @file   fatfs_wrapper.h
/// @author MStar Semiconductor Inc.
/// @brief  Shell command parser state machine
////////////////////////////////////////////////////////////////////////////////
#ifndef FATFS_WRAPPER_H
#define FATFS_WRAPPER_H

//------------------------------------------------------------------------------
//Include Files
//------------------------------------------------------------------------------

extern const u16 *efat_RT16_NOR;
extern const u16 *efat_RT16_NAND;
extern const u16 *efat_RT16_SD;
extern const u16 *efat_RT16_SD1;
extern const u16 *efat_RT16_SD2;
extern const char              efat_CARD_StorageDir[];
extern const char              efat_SD1_DevName[];
extern const char              efat_SD1_StorageDir[];
extern const char              efat_ND_DevName[];
extern const char              efat_ND_StorageDir[];
extern const char              efat_NOR_DevName[];
extern const char              efat_NOR_StorageDir[];
extern const char              efat_SD2_DevName[];
extern const char              efat_SD2_StorageDir[];
//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
//for mtmgr
#define MTMGR_FS_LIST_MAX_NUM (16) /* 512(sector size)/32(entry size) */
//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
typedef struct _SYSTM_
{
    U16 u16year;   // years since 1980
    U8 u8mon;      // months since January - [0..11]
    U8 u8mday;     // days of the month - [1..31]
    U8 u8hour;     // hours since midnight - [0..23]
    U8 u8min;      // minutes after the hour - [0..59]
    U8 u8sec;      // seconds after the minute - [0..59]
    U8 u8wday;     // days since Sunday - [0..6]
}SYSTM;

typedef struct _MOUNTSTATE_
{
    U8 IsNANDErr           ;
    U8 IsSDErr             ;
    U8 IsSD2Err            ;
    U8 NANDNotExist        ;
    U8 SDNotExist          ;
    U8 SD2NotExist         ;
    U8 NANDFSErr           ;
    U8 SDFSErr             ;
    U8 SD2FSErr            ;
    U32 FSNANDRet;
    U32 FSSDRet;
    U32 FSSD2Ret;
}MOUNT_STATE;


typedef struct
{
    S32 fd;
    U8 device;    
    U8 IsOpen;  
    U8 IsDir;
}EFAT_OPENED_LIST;

//------------------------------------------------------------------------------
//end of fatfs_wrapper.h
//------------------------------------------------------------------------------
#endif // #ifndef FATFS_WRAPPER_H

