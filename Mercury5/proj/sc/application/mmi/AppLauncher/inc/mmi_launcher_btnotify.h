#ifndef __BTNOTIFY_APP_H__
#define __BTNOTIFY_APP_H__

#include "mmi_btsrv_def.h"
#include "mmi_launcher_common.h"


/// URL Format: BtNotify://Launch?APM_Mode=%d&IndMsg=%d
void LaunchBtNotify
( 
    AppLaunchMode_e eAppLaunchMode, 
    BTSRV_IndMsg_t *pIndMsg,
	LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *pRspCbInfo 
);

#endif/* __BTNOTIFY_APP_H__ */
