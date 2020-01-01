//==============================================================================
//
//  File        : ahc_rotation.h
//  Description : INCLUDE File for the AHC rotation function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_ROTATION_H_
#define _AHC_ROTATION_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
 
#include "ahc_common.h"


/* For Rotate OSD/Sensor Method 
   Note : It's suggested not to combine any of KEY/Hall-SNR/G-SNR Method */
#define CTRL_BY_NONE					(0x00)
#define CTRL_BY_MENU					(0x01)
#define CTRL_BY_KEY						(0x02)
#define CTRL_BY_HALL_SNR				(0x04)
#define CTRL_BY_G_SNR					(0x08)

/* For Rotate OSD/Sensor Selection */
#define FLIP_NONE						(0x00)
#define FLIP_OSD						(0x01)
#define FLIP_SNR						(0x02)

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum{

	SRC_MENU = 0,
	SRC_KEY,
	SRC_HALL_SNR,
	SRC_G_SNR,
	SRC_MAX
} ROTATE_SRC;
/*===========================================================================
 * Function Prototype
 *===========================================================================*/
AHC_BOOL 		AHC_GetFlipSelection(UINT8 ubCtrl,UINT8* pSelection,UINT8* pbLinkMenu);
AHC_BOOL 		AHC_CheckOSDFlipEn(UINT8 ubCheck);
AHC_BOOL 		AHC_CheckSNRFlipEn(UINT8 ubCheck);
AHC_BOOL 		AHC_CheckLinkWithMenu(UINT8 ubCheck);

void 			AHC_SetRotateSrc(UINT8 src);
UINT8 			AHC_GetRotateSrc(void);
AHC_BOOL 		AHC_LinkLCDStatusToPara(UINT32 wValue);
AHC_BOOL 		AHC_DrawRotateEvent(UINT32 Event);
AHC_BOOL 		AHC_SetKitDirection(UINT8 LCDdir, AHC_BOOL bSetLCD, UINT8 SNRdir, AHC_BOOL bSetSnr);
AHC_BOOL 		AHC_PreSetLCDDirection(void);

#endif