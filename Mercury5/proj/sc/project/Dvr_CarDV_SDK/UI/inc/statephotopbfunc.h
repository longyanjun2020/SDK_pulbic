//==============================================================================
//
//  File        : statephotopbfunc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEPHOTOPBFUNC_H_
#define _STATEPHOTOPBFUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "MenuCommon.h"

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL 	PhotoPBMode_Start(void);
void 		PhotoPBFunc_SetOSDShowStatus(AHC_BOOL state);
AHC_BOOL 	PhotoPBFunc_GetOSDShowStatus(void);
void 		StatePhotoPlaybackMode(UINT32 ulEvent);
AHC_BOOL 	PhotoPBTimer_Start(UINT32 ulTime);
AHC_BOOL 	PhotoPBTimer_Stop(void);
void 		PhotoPB_SDMMC_Change(void);



#endif //_STATEPHOTOPBFUNC_H_
