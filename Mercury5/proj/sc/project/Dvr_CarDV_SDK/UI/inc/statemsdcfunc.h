//==============================================================================
//
//  File        : statemsdcfunc.h
//  Description : INCLUDE File for the StateMSDCFunc function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _STATEMSDCFUNC_H_
#define _STATEMSDCFUNC_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "MenuCommon.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define MSDC_POWEROFF_COUNT 2

/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
void 		StateMSDCMode( UINT32 ulEvent );
AHC_BOOL 	MSDCMode_Start(void);
void 		MSDCTimer_ISR(void *tmr, void *arg);
AHC_BOOL 	MSDCTimer_Start(UINT32 ulTime);
void 		MSDCTimer_ResetCounter(void);

AHC_BOOL MSDCFunc_Init_FromMenu(void* pData);
AHC_BOOL PCCAMFunc_Init_FromMenu(void* pData);
/*
void STATE_MSDC_MODE_EVENT_POWER_OFF(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_USB_REMOVED(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_SD_DETECT(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_SD_REMOVED(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_LCD_COVER_OPEN(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_LCD_COVER_CLOSE(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_LCD_COVER_NORMAL(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_LCD_COVER_ROTATE(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_MSDC_UPDATE_MESSAGE(UINT32 ulEvent);
void STATE_MSDC_MODE_EVENT_ENTER_NET_PLAYBACK(UINT32 ulEvent);
#if defined(MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) && (MSDC_SUPPORT_AIT_CUSTOMER_SCSI_CMD) 
void STATE_MSDC_MODE_EVENT_SCSI_CMD_SWITCH_UVC_MODE(UINT32 ulEvent);
#endif
*/
AHC_BOOL StateSelectFuncUSB_MSDC_PCAM_Mode(void);
#endif  // _STATEMSDCFUNC_H_
