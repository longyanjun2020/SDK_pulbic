/**
* @file ResMgr_RspItf.h
*
* This header file defines the interface of resource manager response.
*
*/

#ifndef __RESMGR_RSPITF_H__
#define __RESMGR_RSPITF_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"
#include "ResMgr_RspEvtItf.h"
/*=============================================================*/
// Macro Declarations
/*=============================================================*/
#define RES_MGR__RSP_START(_CATEGORY_)                  (_CATEGORY_ << 12)
#define RES_MGR__RSP_CATEGORY(_EVT_)                    (_EVT_ >> 12)

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ResMgrRspType_e_
{
    RES_MGR_RSP_TYPE__GENERIC,
    RES_MGR_RSP_TYPE__PROACTIVE,
    RES_MGR_RSP_TYPE__NUM
} ResMgrRspType_e;

/*=============================================================*/
// Function Declaration
/*=============================================================*/

#endif //__RESMGR_RSPITF_H__

