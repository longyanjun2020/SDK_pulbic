/**
* @file UsbDevCtrlFsmItf.h
*
* This header file defines the interfaces of USB Device Ctrl States
*
*/

#ifndef __USBDEVCTRLFSMITF_H__
#define __USBDEVCTRLFSMITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "StateMachineItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum UsbDevStates_e_
{
    USB_DEV_STATE__IDLE,
    USB_DEV_STATE__NUM
} UsbDevStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t UsbDevFSM_Init(void *pCusData);
void UsbDevFSM_Uninit(StateMachineHandle_t pHandle);
bool UsbDev_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__USBDEVCTRLFSMITF_H__

