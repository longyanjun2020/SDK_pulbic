/**
 @file AHC_Debug.c
 @brief AHC debug control Function
 @author 
 @version 1.0
*/

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_debug.h"

/** @addtogroup AHC_DEBUG
@{

*/
/*===========================================================================
 * Global variable
 *===========================================================================*/

AHC_BOOL gbAhcDbgBrk = AHC_FALSE;

/*===========================================================================
 * Main body
 *===========================================================================*/ 

/**
 @brief Get version

 Get the information about component versions.
 Parameters:
 @param[out] *pwHwVersion AIT chip series version.
 @param[out] *pwFwVersion  Firmware version.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_GetAITVersion(UINT16 *pwHwVersion, UINT16 *pwFwVersion)
{
    return AHC_TRUE;
}

AHC_BOOL AHC_SetDbgBreak(UINT8 ubSetDbgBrkEn)
{
    gbAhcDbgBrk = ubSetDbgBrkEn;
    return AHC_TRUE;
}

AHC_BOOL AHC_GetDbgBreak(UINT8 *ubDbgBrkFg)
{
    *ubDbgBrkFg = gbAhcDbgBrk;
    return AHC_TRUE;
}
/// @}
