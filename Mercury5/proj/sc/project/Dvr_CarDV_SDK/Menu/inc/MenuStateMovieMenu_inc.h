//==============================================================================
//
//  File        : MenuStateMovieMenu_inc.h
//  Description : INCLUDE File for the MenuStateMovieMenu function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MENU_STATE_MOVIE_MENU_INC_H_
#define _MENU_STATE_MOVIE_MENU_INC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

/*===========================================================================
 * Function prototype
 *===========================================================================*/

AHC_BOOL MenuStateVideoModeInit(void* pData);
AHC_BOOL MenuStateVideoModeShutDown(void* pData);

UINT32 	 MenuStateClockSettingsModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
AHC_BOOL MenuStateClockSettingsModeInitLCD(void* pData);         

AHC_BOOL MenuStateClockSettingsModeInitTV(void* pData);

AHC_BOOL MenuStateClockSettingsModeInitHDMI(void* pData);

AHC_BOOL MenuStateClockSettingsModeShutDown(void* pData);
AHC_BOOL MenuStateEditConfirmModeShutDown(void* pData);

UINT32   MenuStateSDUpdateModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam );
AHC_BOOL MenuStateSDUpdateModeInit(void* pData);
AHC_BOOL MenuStateSDUpdateModeShutDown(void* pData);

#endif //_MENU_STATE_CAMERA_MENU_INC_H_
