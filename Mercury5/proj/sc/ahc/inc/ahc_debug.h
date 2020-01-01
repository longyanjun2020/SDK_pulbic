/**
 @file ahc_debug.h
 @brief Header File for the AHC debug API.
 @author 
 @version 1.0
*/

#ifndef _AHC_DEBUG_H_
#define _AHC_DEBUG_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_common.h"

/** @addtogroup AHC_DEBUG
@{
*/
/// @}

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

AHC_BOOL AHC_GetAITVersion(UINT16 *pwHwVersion, UINT16 *pwFwVersion);
AHC_BOOL AHC_SetDbgBreak(UINT8 ubSetDbgBrkEn);
AHC_BOOL AHC_GetDbgBreak(UINT8 *ubDbgBrkFg);
#endif //_AHC_DEBUG_H_