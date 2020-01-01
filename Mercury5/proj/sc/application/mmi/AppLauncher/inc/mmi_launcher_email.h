#ifndef __EMAIL_APP_H__
#define __EMAIL_APP_H__

#include "mmi_launcher_common.h"

typedef u8 EmailInsertObjectType_e;

typedef struct
{
    MAE_WChar* wStrName;
    MAE_WChar* wStrAddress;
}EmailRecipient_t;

typedef struct
{
	u32 uRecipientNum;
    EmailRecipient_t *psRecipients;
	boolean bNeedToDeleteFile;
	MAE_WChar *pwStrUrl; // for object url full path  and  if object is text type, this means text content
    EmailInsertObjectType_e eObjType;
}EmailEditData_t;

void LaunchAppToCreateNewEmail
(
  AppLaunchMode_e eAppLaunchMode,
  EmailEditData_t *psEditData,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);
#endif

