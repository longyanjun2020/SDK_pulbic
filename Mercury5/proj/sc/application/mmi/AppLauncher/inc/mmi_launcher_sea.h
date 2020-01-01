#ifndef __SEA_APP_H__
#define __SEA_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_common_sms_master.h"


/// Message Cenetr 
/// 1. Edit New SMS from text template
/// 2. Edit New MMS from text template

typedef enum
{
    MSG_SEA_TYPE_MIN = 0,
    MSG_SEA_TYPE_SMS = MSG_SEA_TYPE_MIN,  
	MSG_SEA_TYPE_MMS,
    MSG_SEA_TYPE_MAX = MSG_SEA_TYPE_MMS,
	MSG_SEA_TYPE_INVALID,
}SeaMsgType_e;


/// "Sms://Edit?APM_Mode=%d&RecipientNum=%d&RecipientName[0]=%d&RecipientPhbNum[0]=%d&...&Content=%s"
void LaunchAppToCreateMsg // for  template, 
(
  AppLaunchMode_e eAppLaunchMode,
  SeaMsgType_e eMsgType,
  MAE_WChar *pContent,
#ifdef __SMS_REJECT_CALL__
  MAE_WChar *pNumber,
#endif  
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif
