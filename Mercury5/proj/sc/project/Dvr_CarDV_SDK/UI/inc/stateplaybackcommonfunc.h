//==============================================================================
//
//  File        : stateplaybackcommon.h
//  Description : INCLUDE File for the stateplaybackcommon function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEPLAYBACKCOMMONFUNC_H_
#define _STATEPLAYBACKCOMMONFUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "ahc_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

/*===========================================================================
 * Function prototype
 *===========================================================================*/
UINT32 		StateCommonPBModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
AHC_BOOL 	StateCommonPBModeInit(void* pData);
AHC_BOOL 	StateCommonPBModeShutDown(void* pData);
AHC_BOOL 	StateSelectPBFunc(UINT8 ubUIMode);
AHC_BOOL 	StateSelectFuncPlaybackMode(void);


#endif //_STATEPLAYBACKCOMMONFUNC_H_
