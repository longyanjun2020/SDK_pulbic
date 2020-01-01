//==============================================================================
//
//  File        : ahc_charger.h
//  Description : INCLUDE File for the AHC charger function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_CHARGER_H_
#define _AHC_CHARGER_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
 
#include "ahc_common.h"

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

/*===========================================================================
 * Enum define
 *===========================================================================*/

/*===========================================================================
 * Function Prototype
 *===========================================================================*/
void        AHC_Charger_InitialIO(void);
void        AHC_Charger_SetEnable(AHC_BOOL bEn);
AHC_BOOL    AHC_Charger_GetEnable(void);
void        AHC_Charger_SetTempCtrlEnable(AHC_BOOL bEn);
AHC_BOOL    AHC_Charger_GetTempCtrlStatus(void);
AHC_BOOL    AHC_Charger_GetStatus(void);

#endif