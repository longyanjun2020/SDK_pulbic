//==============================================================================
//
//  File        : ahc_touchpanel.h
//  Description : INCLUDE File for the AHC gsensor control function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_TOUCHPANEL_H_
#define _AHC_TOUCHPANEL_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"

/*===========================================================================
 * 
 *===========================================================================*/ 

#define AHC_TOUCHPANEL_RET_FALSE 		(AHC_FALSE)
#define AHC_TOUCHPANEL_RET_TRUE 		(AHC_TRUE)
#define AHC_TOUCHPANEL_NO_ERROR 		(MMP_ERR_NONE)

#define AHC_TOUCHPANEL_CHECK_RETURE_VALUE(RET_VAL, NO_ERROR, YES, NO) return (RET_VAL == NO_ERROR) ? YES : NO;

/*===========================================================================
 * Function prototype
 *===========================================================================*/
 
AHC_BOOL AHC_TouchPanel_Module_Attached(void);
AHC_BOOL AHC_TouchPanel_Init(void);
int 	 AHC_TouchPanel_ReadPosition(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir);
AHC_BOOL AHC_TouchPanel_ReadVBAT1(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir);
AHC_BOOL AHC_TouchPanel_IOControl(UINT8 cmd, void* arg);
AHC_BOOL AHC_TouchPanel_CheckUpdate(MMP_ULONG* pulKeyEvent, MMP_ULONG* pulPosition, MMP_UBYTE dir, MMP_UBYTE* finger);
AHC_BOOL AHC_TouchPanel_GetKeyValue(MMP_ULONG* pulKeyEvent, MMP_ULONG* pulPosition, MMP_UBYTE dir, MMP_UBYTE* finger);

#endif //_AHC_TOUCHPANEL_H_
