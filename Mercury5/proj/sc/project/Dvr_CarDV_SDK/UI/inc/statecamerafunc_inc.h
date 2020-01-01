//==============================================================================
//
//  File        : StateCameraFunc_inc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATECAMERAFUNC_INC_H_
#define _STATECAMERAFUNC_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/

UINT32      StateCaptureModeHnadler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

AHC_BOOL    StateCaptureModeInitLCD(void* pData);
AHC_BOOL    StateCaptureModeInitHDMI(void* pData);
AHC_BOOL    StateCaptureModeInitTV(void* pData);
AHC_BOOL    StateCaptureModeShutDown(void* pData);

#endif //_STATECAMERAFUNC_INC_H_
