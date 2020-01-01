//==============================================================================
//
//  File        : statevideofunc_inc.h
//  Description : INCLUDE File for the StateVideo Func function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEVIDEOFUNC_INC_H_
#define _STATEVIDEOFUNC_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL StateVideoRecModeInitLCD(void* pData);
AHC_BOOL StateVideoRecModeInitHDMI(void* pData);
AHC_BOOL StateVideoRecModeInitTV(void* pData);
AHC_BOOL VideoFunc_Init_NoDisplay(void* pData);
AHC_BOOL StateVideoRecModeShutDown(void* pData);
UINT32 StateVideoRecModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );

#endif //_STATEBROWSERFUNC_H_
