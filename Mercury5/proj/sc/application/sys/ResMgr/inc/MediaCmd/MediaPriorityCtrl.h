/**
* @file Media_PriorityCtrl.h
*
* This header file defines the APIs of priority controller.
*
*/

#ifndef __MEDIA_PRIORITYCTRL_H__
#define __MEDIA_PRIORITYCTRL_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Common.h"

/*=============================================================*/
// Structure Declarations
/*=============================================================*/
typedef enum ResMgr_PriCtrlCmp_e_
{
	RES_MGR_PRI_CTRL_CMP__HIGHER,
	RES_MGR_PRI_CTRL_CMP__LOWER,
	RES_MGR_PRI_CTRL_CMP__SAME,
	RES_MGR_PRI_CTRL_CMP__NUM
} ResMgr_PriCtrlCmp_e;

/*
    RES_MGR_PRI_COMP__QUEUE means the later commands are queued until the prior command is completed
    RES_MGR_PRI_COMP__INTERRUPT means the later commands will stop the prior command
*/
typedef enum ResMgr_PriHandleType_e_
{
    RES_MGR_PRU_HDL_TYPE__QUEUE,
    RES_MGR_PRU_HDL_TYPE__INTERRUPT,
    RES_MGR_PRU_HDL_TYPE__NUM
} ResMgr_PriHandleType_e;

/*
    RES_MGR_LOW_PRI_HDL__PENDING means the later commands are queued until the prior command is completed
    RES_MGR_LOW_PRI_HDL__DROP means the later commands will be dropped if they have lower priority
*/
typedef enum ResMgr_LowPriHandleType_e_
{
    RES_MGR_LOW_PRI_HDL__PENDING,
    RES_MGR_LOW_PRI_HDL__DROP,
    RES_MGR_LOW_PRI_HDL__NUM
} ResMgr_LowPriHandleType_e;
/*=============================================================*/
// Function Declarations
/*=============================================================*/
ResMgr_PriCtrlCmp_e Media_ComparePriority(ResMgr_AppId_e eApp1Id, ResMgr_AppId_e eApp2Id);
ResMgr_PriHandleType_e Media_GetPriHandleType(ResMgr_AppId_e eApp1Id);
ResMgr_LowPriHandleType_e Media_GetLowPriHandleType(ResMgr_AppId_e eAppId);
#endif //__MEDIA_PRIORITYCTRL_H__

