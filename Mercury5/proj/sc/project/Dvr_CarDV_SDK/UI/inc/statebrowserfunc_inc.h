//==============================================================================
//
//  File        : statebrowserfunc_inc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEBROWSERFUNC_INC_H_
#define _STATEBROWSERFUNC_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/
AHC_BOOL StateBrowserModeInitLCD(void* pData);
AHC_BOOL StateBrowserModeInitHDMI(void* pData);
AHC_BOOL StateBrowserModeInitTV(void* pData);
AHC_BOOL StateBrowserModeShutDown(void* pData);
UINT32 	 StateBrowserModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
AHC_BOOL StateSelectFuncBrowserMode(void);

#endif //_STATEBROWSERFUNC_H_
