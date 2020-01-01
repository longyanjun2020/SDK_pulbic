//==============================================================================
//
//  File        : aihc_gui.h
//  Description : INCLUDE File for the AHC GUI function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AIHC_GUI_H_
#define _AIHC_GUI_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_parameter.h"
#include "ahc_gui.h"
//#include "AHC_Config_SDK.h"

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL AIHC_OSDGetParam(AHC_PARAM_ID wParamID,UINT32 *Param);
AHC_BOOL AIHC_DrawReservedOSD(AHC_BOOL bDrawReserved);
AHC_BOOL AIHC_GUI_GetOSDBufAddr(UINT16 uwDisplayID, UINT32 *Addr);

#endif
