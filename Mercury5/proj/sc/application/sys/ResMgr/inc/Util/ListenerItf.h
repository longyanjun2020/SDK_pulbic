/**
* @file ListenerItf.h
*
* This header file defines the interfaces of Listener
*
*/

#ifndef __LISTENERITF_H__
#define __LISTENERITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "PlatformDefines.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef bool (*Listener_CheckEvt) (u16 uEvt, u16 uEvtOwner, void *pEvtParm, void *pOwner, void *pCusData);
typedef void (*Listener_ListenEvt) (u16 uEvt, void *pEvtParm, void *pOwner, void *pCusData);
typedef bool (*Listener_Compare) (void *pCurSettings, void *pRefSettings, void *pCusData);

typedef enum ListenerType_e_
{
    LISTENER_TYPE__NOTIFY_FIRST,
    LISTENER_TYPE__NOTIFY_LAST,
    LISTENER_TYPE__NOTIFY_ALL,
    LISTENER_TYPE__NUM
} ListenerType_e;

typedef void* ListenerHdl_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ListenerHdl_t Listener_Init(ListenerType_e eType, Listener_Compare Compare, void *pCusData);
void Listener_Uninit(ListenerHdl_t pHandle);

void Listener_Register
(
    ListenerHdl_t pHandle,
    void *pSettings,
    Listener_CheckEvt CheckEvt,
    Listener_ListenEvt ListenEvt
);

void* Listener_Deregister(ListenerHdl_t pHandle, void *pSettings);
bool Listener_NotifyEvent(ListenerHdl_t pHandle, u16 uEvt, u16 uEvtOwner, void *pEvtParm);
bool Listener_IsRegister(ListenerHdl_t pHandle, void *pSettings);

#endif //__LISTENERITF_H__
