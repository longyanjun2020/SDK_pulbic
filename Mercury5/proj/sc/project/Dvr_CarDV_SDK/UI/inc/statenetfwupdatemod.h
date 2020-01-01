//==============================================================================
//
//  File        : StateNetFwUpdateFunc.h
//  Description : INCLUDE File for the StateNetFwUpdateMod function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATE_NET_FWUPDATE_FUNC_H_
#define _STATE_NET_FWUPDATE_FUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "MenuCommon.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 


/*===========================================================================
 * Function prototype
 *===========================================================================*/ 

AHC_BOOL NetFwUpdateFunc_Init(void* pData);
AHC_BOOL NetFwUpdateFunc_ShutDown(void* pData);
AHC_BOOL NetFwUpdateMode_Start(void);
void StateNetFwUpdateMode( UINT32 ulEvent );

#endif  // _STATE_NET_FWUPDATE_FUNC_H_