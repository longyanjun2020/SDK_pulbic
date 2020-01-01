//==============================================================================
//
//  File        : ahc_protection_inc.h
//  Description : INCLUDE File for the aihc_protection function porting.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AIHC_PROTECTION_INC_H_
#define _AIHC_PROTECTION_INC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
//Do not include other files in xxx_inc.h.

/*===========================================================================
 * Macro define
 *===========================================================================*/

/*===========================================================================
 * Enum define
 *===========================================================================*/

// Note that these enumerates must be group in video, audio and movie order.
// leave the naming such as AHC_CLIP for better comparison with CarDV code base.
typedef enum _AHC_PROTECTION_OP{
    AHC_PROTECTION_PRE_FILE = 0x01,// previous
    AHC_PROTECTION_CUR_FILE = 0x02,// current
    AHC_PROTECTION_BOTH_FILE = AHC_PROTECTION_PRE_FILE|AHC_PROTECTION_CUR_FILE// previous + current
}AHC_PROTECTION_OP;

typedef enum _AHC_PROTECT_TYPE {
    AHC_PROTECT_NONE    = 0x00,
    AHC_PROTECT_G       = 0x01, //GSensor Lock
    AHC_PROTECT_MENU    = 0x02, //Menu lock
    AHC_PROTECT_D       = AHC_PROTECT_G|AHC_PROTECT_MENU,   //GSensor+Menu Lock
    AHC_PROTECT_MOVE    = 0x04,  //Move File to another DIR
    AHC_PROTECT_NEXT    = 0x08  //Move next File to another DIR
}AHC_PROTECT_TYPE;

/*===========================================================================
 * Structure define
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/
#define AHC_IsFileProtect           AHC_Thumb_IsFileProtect
#define AHC_GetDCFObjNumPerPage     AHC_Thumb_GetMaxNumPerPage

AHC_BOOL    AHC_Protect_SpellFileName(char* FilePathName, INT8* pchDirName, INT8* pchFileName);
AHC_PROTECT_TYPE AHC_Protect_GetType(void);
void        AHC_Protect_SetType(AHC_PROTECT_TYPE Type);
AHC_BOOL    AHC_Protect_SetVRFile(AHC_PROTECTION_OP Op, AHC_PROTECT_TYPE Type);

#endif //_AIHC_PROTECTION_INC_H_
