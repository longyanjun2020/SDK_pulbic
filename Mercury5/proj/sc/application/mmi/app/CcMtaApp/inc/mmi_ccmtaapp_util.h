/**
* @file    mmi_ccmtaapp_util.h
* @brief   xxxx
* @version $Id: mmi_ccmta_util.h 1733 2007-09-05 09:27:04Z collin.chiang $
*/
#ifndef __MMI_CCMTAAPP_UTIL_H__
#define __MMI_CCMTAAPP_UTIL_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h"

u16*		CcMtaUtilAsciiToUCS2Len(u16* pUnicode, const u8* pAscii, u16 len);
u32			CcMtaUtilInCallNotificationMap(u32 index);

#ifdef __CCMTA_OPTION_MENU_MMI__
void        CcMtaUtilHideOptionItem(IWidget *pMenu, u32 u32ItemID);
#endif // __CCMTA_OPTION_MENU_MMI__

#ifdef __DISTORTED_VOICE_MMI__
void CcMtaUtilSetDistortedVoiceSettings(IBase* pUser, boolean bStatus, u8 nEffect);
void CcMtaUtilGetDistortedVoiceSettings(IBase* pUser, boolean * bStatus, u8 * nEffect);
#endif // __DISTORTED_VOICE_MMI__

#endif /* __MMI_CCMTAAPP_UTIL_H__ */
