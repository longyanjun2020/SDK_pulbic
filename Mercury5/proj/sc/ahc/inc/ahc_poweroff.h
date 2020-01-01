//==============================================================================
//
//  File        : ahc_poweroff.h
//  Description : INCLUDE File for the AHC power off function.
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_POWEROFF_H_
#define _AHC_POWEROFF_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"

/*===========================================================================
 * Function Prototype
 *===========================================================================*/

void        AHC_PowerOff_Preprocess(void);
void        AHC_PowerOff_VirtualPath(void);
void        AHC_PowerOff_NormalPath(void);
AHC_BOOL    AHC_PowerOff_ShowPicture(INT8 *charStr);
void        AHC_PowerOff_NormalPathEx(AHC_BOOL bForce, AHC_BOOL bByebye, AHC_BOOL bSound);

#endif // _AHC_POWEROFF_H_
