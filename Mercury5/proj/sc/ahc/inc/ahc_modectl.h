//==============================================================================
//
//  File        : ahc_modectl.h
//  Description : INCLUDE File for the AHC Mode control function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MODECTL_H_
#define _AHC_MODECTL_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
 
#include "ahc_common.h"

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct _AHC_MODE_DESCP {
    AHC_MODE_ID eModeId;
    UINT8       u8Name[20];
} AHC_MODE_DESCP;

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum {
    PWR_ON_BY_KEY       = 0x01,
    PWR_ON_BY_VBUS      = 0x02,
    PWR_ON_BY_GSENSOR   = 0x04,
    PWR_ON_BY_IR        = 0x08,
    PWR_ON_BY_DC        = 0x10,
} BOOT_UP_SRC;

/*===========================================================================
 * Function Prototype
 *===========================================================================*/

AHC_BOOL    AHC_Initialize(void);
AHC_BOOL    AHC_SetMode(AHC_MODE_ID uiMode);
AHC_BOOL    AHC_GetSystemStatus(UINT32* pwValue);
AHC_MODE_ID AHC_GetAhcSysMode(void);
void        AHC_SetAhcSysMode(AHC_MODE_ID uiMode);
UINT8       AHC_SetBootingSrc(UINT8 bBootupFlag);
AHC_BOOL    AHC_WaitForBootComplete(void);

#endif
