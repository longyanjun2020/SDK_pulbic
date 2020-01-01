/**
* @file ResMgr_Evt.h
*
* This header file defines the data structure of resource manager
* control request
*/

#ifndef __RESMGR_EVT_H__
#define __RESMGR_EVT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_EvtItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_Evt_t_
{
    ResMgr_ResCategory_e eResCategory;
    ResMgr_EvtType_e eEvt;
    u32 uParams;
} ResMgr_Evt_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_EVT_H__

