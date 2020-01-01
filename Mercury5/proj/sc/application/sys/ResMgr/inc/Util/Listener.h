/**
* @file Listener.h
*
* This header file defines the data structures of Listener
*
*/

#ifndef __LISTENER_H__
#define __LISTENER_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ListenerItf.h"
#include "DListItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct Listener_t_
{
    ListenerType_e eType;
    Listener_Compare Compare;
    void *pCusData;
    DList_t *pRegClients;
} Listener_t;

typedef struct ListenerClient_t_
{
    void *pSettings;
    Listener_CheckEvt CheckEvt;
    Listener_ListenEvt ListenEvt;
} ListenerClient_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__LISTENER_H__
