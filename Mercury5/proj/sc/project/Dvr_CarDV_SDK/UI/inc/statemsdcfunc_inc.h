//==============================================================================
//
//  File        : StatemsdcFunc_inc.h
//  Description : INCLUDE File for the StatemsdcFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEMSDCFUNC_INC_H_
#define _STATEMSDCFUNC_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL StateMSDCModeInit(void* pData);
AHC_BOOL StateMSDCModeShutDown(void* pData);
AHC_BOOL StatePCCAMModeInit(void* pData);
AHC_BOOL StatePCCAMModeShutDown(void* pData);
UINT32 StateMSDCModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);

#endif //_STATEMSDCFUNC_INC_H_
