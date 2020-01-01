/**
* @file ABL_Usb.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of USB.
*
*/

#ifndef __ABL_USB_H__
#define __ABL_USB_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_usb_itf.h"
#include "MediaRspItf.h"
#include "srv_ResMgr_Usb.h"
//#include "MML_Manager.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_ExecRes_e ABL_UsbParseExecRes(s16 sResult);
void ABL_UsbInformApp(void *pCusData, void *pRspData, ResMgr_InformType_e eInformType);
void ABL_UsbFreeCusData(void *pCusData);
void ABL_UsbGetCusData(void *pSrcCusData, void *pRspData, void **ppDestCusData);
ResMgr_ExecRes_e ABL_MmlUsbParseExecRes(s16 sResult);
#endif //__ABL_USB_H__

