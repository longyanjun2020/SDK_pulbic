//==============================================================================
//
//  File        : MenuStateModeSelectMeru_inc.h
//  Description : INCLUDE File for the MenuStateModeSelect function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MENU_STATE_MODE_SELECT_MENU_INC_H_
#define _MENU_STATE_MODE_SELECT_MENU_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/

UINT32 MenuStateUSBModeSelectModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
AHC_BOOL MenuStateUSBModeSelectModeInitLCD(void* pData);
AHC_BOOL MenuStateUSBModeSelectModeInitTV(void* pData);
AHC_BOOL MenuStateUSBModeSelectModeInitHDMI(void* pData);
AHC_BOOL MenuStateUSBModeSelectModeShutDown(void* pData);


#endif //_STATEBROWSERFUNC_H_
