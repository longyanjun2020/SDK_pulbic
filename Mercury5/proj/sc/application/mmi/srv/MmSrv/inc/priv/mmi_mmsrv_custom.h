/**
* @file mmi_mmsrv_custom.h
*
* MMSrv customization file
*
* @version $Id: mmi_mmsrv_custom.h $
*/
#ifndef __MMI_MMSRV_CUSTOM_H__
#define __MMI_MMSRV_CUSTOM_H__

#include "mmi_mae_common_def.h"

/***
This timer is used to keep searching state.
MM service will back to no service or emergency only state when timer expired.
***/
#define MMSRV_NET_SEARCH_TIMER      30000
#define MMSRV_RSSI_UNKNOWN          99

extern const u8 RssiLevelTable[];

u8 _MMSRV_GetRssiLevel(u16 nRssi);

#endif /* __MMI_MMSRV_CUSTOM_H__ */
