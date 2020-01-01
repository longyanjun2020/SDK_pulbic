/**
* @file ResMgr_Ctrl.h
*
* This header file defines the data structure of resource manager
* control request
*/

#ifndef __RESMGR_CTRL_H__
#define __RESMGR_CTRL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_CtrlItf.h"

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct ResMgr_Ctrl_t_
{
    ResMgr_ResCategory_e eResCategory;
    ResMgr_CtrlType_e eCtrlType;
    ResMgr_CtrlReqHandle_t pReqHdl;
} ResMgr_Ctrl_t;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_CTRL_H__

