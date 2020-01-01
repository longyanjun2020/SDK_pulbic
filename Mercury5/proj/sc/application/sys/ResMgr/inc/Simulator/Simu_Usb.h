/**
* @file Simu_Usb.h
*
* This header file defines the interface of lower layer device simulation for USB
*
*/
#ifndef __SIMU_USB_H__
#define __SIMU_USB_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_UsbOpenCb(void *pUserData);
void Simu_UsbCloseCb(void *pUserData);
void Simu_UsbAttachCb(void *pUserData);
void Simu_UsbAttachAndPollingCb(void *pUserData);
void Simu_UsbStopPollingCb(void *pUserData);
#endif //__SIMU_USB_H__
