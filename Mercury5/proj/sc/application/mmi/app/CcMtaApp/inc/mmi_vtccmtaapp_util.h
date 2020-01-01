/**
* @file    mmi_vtccmtaapp_util.h
* @brief   xxxx
* @version $Id: mmi_vtccmtaapp_util.h
*/
#ifndef __MMI_VTCCMTAAPP_UTIL_H__
#define __MMI_VTCCMTAAPP_UTIL_H__

#include "mmi_mae_common_def.h"

#ifdef __APP_VIDEO_TELEPHONY__
u16*	 VtCcMtaUtilAsciiToUCS2Len(u16* pUnicode, const u8* pAscii, u16 len);
u32 VtCcMtaUtilInCallNotificationMap(u32 index);
#endif
#endif /* __MMI_VTCCMTAAPP_UTIL_H__ */
