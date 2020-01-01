#ifndef __CHECKDISKAPP_H__
#define __CHECKDISKAPP_H__

#include "mmi_launcher_common.h"

typedef enum
{
	CHECKDISK_LAUNCH_MODE_CHECK_DISK = 0,
	CHECKDISK_LAUNCH_MODE_FORMAT,
	CHECKDISK_LAUNCH_MODE_INVALID,
}CheckDiskAppLauchMode_e;

#define CHECKDISKAPP_NOTIFY_STOP_AP	0x10000000

typedef enum
{
	CHECKDISK_LAUNCH_TYPE_UNKNOWN = 0,
	CHECKDISK_LAUNCH_TYPE_ALL,
	CHECKDISK_LAUNCH_TYPE_PHONE,
	CHECKDISK_LAUNCH_TYPE_SD1,
	CHECKDISK_LAUNCH_TYPE_SD2,
} CheckDiskAppLauchType_e;

void LaunchCheckDiskAP
(
	 AppLaunchMode_e eAppLaunchMode,
	 u32 nStartMode,
	 u32 nStartType,
	 LaunchAppTransParam_t *psTransParam,
	 CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

#endif/* __CHECKDISKAPP_H__ */
