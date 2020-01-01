//==============================================================================
//
//  File        : StateAudiopbFunc_inc.h
//  Description : INCLUDE File for the StateAudiopb Func function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEAUDIOPBFUNC_INC_H_
#define _STATEAUDIOPBFUNC_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL  StateAudioPlaybackModeInit(void* pData);
AHC_BOOL  StateAudioPlaybackModeShutDown(void* pData);
UINT32 	  StateAudioPlaybackModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);


#endif //_STATEBROWSERFUNC_H_
