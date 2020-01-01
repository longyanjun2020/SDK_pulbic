#ifndef __SENDVIA_APP_H__
#define __SENDVIA_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_mae_vectormodel.h"

/// 1. Calendar App,        APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_VCALENDAR,   Id=EventId
/// 2. File Manager App,    APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_GENERAL,     Id=MarkHandleId
/// 3. Map App,             APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_VGPSINFO,    Content=GpsInfo
/// 4. Phb App,             APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_VCARD,       Id=SoringIdx,       Type=PhbActionBookType,     Group=PhbActionGroup
/// 5. Message Viewer App,  APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_GENERAL,     Url=FileUrl
/// 6. Pic Viewer App,      APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_GENERAL,     Url=FileUrl
/// 7. Video Player App,    APM_Mode=APM_LAUNCH_EMBEDDED, ContentType=SENDVIA_CONTENT_TYPE_GENERAL,     Url=FileUrl

typedef enum
{
    SENDVIA_CONTENT_TYPE_MIN = 0,
    SENDVIA_CONTENT_TYPE_MIN_DUMMY = SENDVIA_CONTENT_TYPE_MIN - 1,

	SENDVIA_CONTENT_TYPE_VCALENDAR,
#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
	SENDVIA_CONTENT_TYPE_VCARD,
#endif // __MMI_PHB_DISABLE_IMPORT_EXPORT__
	SENDVIA_CONTENT_TYPE_VTODO,
	SENDVIA_CONTENT_TYPE_GENERAL,
	SENDVIA_CONTENT_TYPE_VGPSINFO,

	SENDVIA_CONTENT_TYPE_MAX,
	SENDVIA_CONTENT_TYPE_MAX_DUMMY = SENDVIA_CONTENT_TYPE_MAX - 1,

	SENDVIA_CONTENT_TYPE_NUM,
	SENDVIA_CONTENT_TYPE_INVALID,

} SendViaContentType_e;

typedef struct
{
    MAE_WChar *pwszContent; 
	boolean bNeedToDeleteFile; 
}SendViaSendData_t;

/// URL Format: SendVia://Content?APM_Mode=%d&ContentType=%d&Content=%s&Content=%s
/// No Response Data Callback
void LaunchSendViaByContent(AppLaunchMode_e eAppLaunchMode, SendViaContentType_e eContentType, MAE_WChar *pwszContent, LaunchAppTransParam_t *psTransParam, CmnAppLaunchRspCbInfo_t *psRspCbInfo);

/// URL Format: SendVia://Content?APM_Mode=%d&ContentType=%d&Content=%s&Url=%s
/// No Response Data Callback
void LaunchSendViaByUrl(AppLaunchMode_e eAppLaunchMode, SendViaContentType_e eContentType, SendViaSendData_t *pSendData,  LaunchAppTransParam_t *psTransParam, CmnAppLaunchRspCbInfo_t *psRspCbInfo);

/// URL Format: SendVia://Content?APM_Mode=%d&ContentType=%d&Content=%s&Id=%d
/// No Response Data Callback
void LaunchSendViaByMarkHandleId(AppLaunchMode_e eAppLaunchMode, SendViaContentType_e eContentType, u32 nMarkHandleId,  LaunchAppTransParam_t *psTransParam, CmnAppLaunchRspCbInfo_t *psRspCbInfo);

/// Plz fill your URL Format
void LaunchSendViaByPhbSortingIdx(AppLaunchMode_e eAppLaunchMode, SendViaContentType_e eContentType, u32 nPhbSortingIdx, u32 nType, u32 nGroup,  LaunchAppTransParam_t *psTransParam, CmnAppLaunchRspCbInfo_t *psRspCbInfo);

/// Plz fill your URL Format
void LaunchSendViaByEventId(AppLaunchMode_e eAppLaunchMode, SendViaContentType_e eContentType, u32 nEventId,  LaunchAppTransParam_t *psTransParam, CmnAppLaunchRspCbInfo_t *psRspCbInfo);

#endif
