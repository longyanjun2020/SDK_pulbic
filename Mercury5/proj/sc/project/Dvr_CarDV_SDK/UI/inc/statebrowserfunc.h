//==============================================================================
//
//  File        : statebrowserfunc.h
//  Description : INCLUDE File for the StateCameraFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEBROWSERFUNC_H_
#define _STATEBROWSERFUNC_H_

/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "MenuCommon.h"

/*===========================================================================
 * Function prototype
 *===========================================================================*/

void 		StateBrowser_LCDMode( UINT32 ulEvent );
void 		BrowserMode_Update(void);
AHC_BOOL 	BrowserMode_Start(void);
void 		BrowserFunc_Thumbnail_Setting(AHC_BOOL bLcdstatus);
void BrowserFunc_DisplaySetting(void);
void 		BrowserFunc_CheckLCDstatus(void);
void 		BrowserFunc_Setting(void);
AHC_BOOL 	BrowserFunc_ThumbnailResetAllEditOp(void);
AHC_BOOL 	BrowserFunc_ThumbnailEditFilelComplete(void);
AHC_BOOL 	BrowserFunc_ThumbnailEditFile(UINT8 Op);
AHC_BOOL 	BrowserFunc_ThumbnailEditCheckFileObj(void);
AHC_BOOL 	BrowserFunc_ThumbnailEditFile_Option(UINT32 ulEvent);

UINT32      BrowserFunc_Touch(UINT16 pt_x,UINT16 pt_y);
UINT32      Browser_FileEdit_Touch(UINT16 pt_x,UINT16 pt_y);

AHC_BOOL StateBrowserModeInitLCD(void* pData);
AHC_BOOL StateBrowserModeInitHDMI(void* pData);
AHC_BOOL StateBrowserModeInitTV(void* pData);
AHC_BOOL StateBrowserModeShutDown(void* pData);
UINT32 StateBrowserModeHandler(UINT32 ulMsgId, UINT32 ulEvent, UINT32 ulParam);
AHC_BOOL StateSelectFuncBrowserMode(void);

#endif //_STATEBROWSERFUNC_H_
