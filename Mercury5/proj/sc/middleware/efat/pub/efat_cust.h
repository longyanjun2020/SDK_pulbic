///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   efat_cust.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "vm_types.ht"

//------------------------------------------------------------------------------
//Global Variables
//------------------------------------------------------------------------------

extern const u16 *efat_RT16_NOR;    
extern const u16 *efat_RT16_NAND;   
extern const u16 *efat_RT16_SD;     
extern const u16 *efat_RT16_SD1;    
extern const u16 *efat_RT16_SD2;    
extern const u16 *efat_RT16_HIDN;   
extern const char  efat_CARD_StorageDir[];
extern const char  efat_SD1_DevName[];
extern const char  efat_SD1_StorageDir[];
extern const char  efat_ND_DevName[];
extern const char  efat_ND_StorageDir[];
extern const char  efat_NOR_DevName[];
extern const char  efat_NOR_StorageDir[];
extern const char  efat_SD2_DevName[];
extern const char  efat_SD2_StorageDir[];
extern const char  efat_HIDN_DevName[];
extern const char  efat_HIDN_StorageDir[];

extern u16 * efat_u16_vol2dirname(u32 vol);
extern u16 * efat_u16_dev2dirname(u32 u8device);

extern u8 * efat_u8_vol2dirname(u32 vol);
extern u8 * efat_u8_dev2devname(u32 devId);
extern u8 * efat_u8_dev2dirname(u32 devId);



//extern U8 EfatNotCloseFileName[MAX_FILE_NAME_LENGTH+NULL_LENGTH];
//extern U16 EfatNotCloseFileNameIdx;



