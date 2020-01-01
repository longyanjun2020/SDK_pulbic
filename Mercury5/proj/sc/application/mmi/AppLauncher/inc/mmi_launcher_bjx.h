#ifndef __BJX_APP_H__
#define __BJX_APP_H__
#include "mmi_launcher_common.h"
#include "mmi_launcher_phb.h"

/// 1. Phb App, APM_Mode = APM_LAUNCH_NORMAL, MMI_PHB_BOOK_TYPE_E = xxx, MMI_PHB_GROUP_E = xxx


typedef struct
{
    u16 nContactId;
}BjxAppFindContactIdRspData_t;

typedef void (*BjxAppFindContactIdRspDataFreeCb)(BjxAppFindContactIdRspData_t *pRspData);
typedef void (*BjxAppFindContactIdRspCb)(void *pUserData, MAE_Ret nRspCode, BjxAppFindContactIdRspData_t *pRspData, BjxAppFindContactIdRspDataFreeCb pfnRspDataFreeCb);

typedef struct
{
	void *pUserData;
    CmnLaunchAppRspCb pfnLaunchListenerCb;
	BjxAppFindContactIdRspCb pfnDataRspCb;
}BjxAppFindContactIdCbInfo_t;

/// 1.
/// Launch Bjx to find Contact Id in phonebook
///
/// URL Format: Bjx://FindContactId?APM_Mode=%d?PhoneBookType=%d&PhoneBookGroupType=%d
/// Use data response callback to retrieve data
void LaunchAppToFindContactId
(
  AppLaunchMode_e eAppLaunchMode, 
  PhoneBookType_e eType, 
  PhoneBookGroupType_e eGroupType, 
  LaunchAppTransParam_t *psTransParam,
  BjxAppFindContactIdCbInfo_t *pRspCbInfo
);

#endif/* __BJX_APP_H__ */
