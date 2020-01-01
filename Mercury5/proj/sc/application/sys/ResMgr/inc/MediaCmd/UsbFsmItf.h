/**
* @file UsbFsmItf.h
*
* This header file defines the interfaces of USB States
*
*/

#ifndef __USBFSMITF_H__
#define __USBFSMITF_H__

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
typedef enum UsbStates_e_
{
    USB_STATE__IDLE,
    USB_STATE__INIT,
    USB_STATE__OPEN,
    USB_STATE__NUM
} UsbStates_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
StateMachineHandle_t UsbFSM_Init(void *pCusData);
void UsbFSM_Uninit(StateMachineHandle_t pHandle);
bool Usb_IdleAcceptAct(StateMachineHandle_t pHandle, void *pCusData, u16 uAction);

#endif //__USBFSMITF_H__

