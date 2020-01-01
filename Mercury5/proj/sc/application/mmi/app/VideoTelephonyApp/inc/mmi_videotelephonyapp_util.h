/**
* @file    mmi_videotelephonyapp_util.h
* @brief   xxxx
* @version $Id: mmi_videotelephonyapp_util.h$
*/
#ifndef __MMI_VIDEOTELEPHONYAPP_UTIL_H__
#define __MMI_VIDEOTELEPHONYAPP_UTIL_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h"
#include "mmi_ccsrv_def.h"
#include "mmi_phbsrv_def.h"

#include "mmi_vtccsrv_def.h"

u16*		VideoTelephonyAppUtilAsciiToUCS2Len(u16* pUnicode, const u8* pAscii, u16 len);
boolean	VideoTelephonyAppUtilCheckMPTYCallandStatus(CallTable_t* pCallTable, MMI_VTCCSRV_Status_e* status);
u8		VideoTelephonyAppUtilGetMPTYNumber(CallTable_t* pCallTable);
boolean	VideoTelephonyAppUtilFindSingleCallIndex(CallTable_t* pCallTable, u8* CallIndex);
void		VideoTelephonyAppUtilSetData2CallInfo(IWidget *pStatusImage, IWidget *pCallInfo, CallEntry_t *pCallEntry, IBase* pThis);
void		VideoTelephonyAppUtilHideOptionItem(IWidget *pMenu, u32 u32ItemID);
void 		VideoTelephonyAppUtilShowOptionItem(IWidget *pMenu, u32 u32ItemID);
void 		VideoTelephonyAppUtilBTHandleforATCHLD(  IBase* pUser, u32 param );
void		VideoTelephonyAppUtilShortStringForPublicMMI(u16 len, u8* pStr, IBase* pUser);
u8		VideoTelephonyAppUtilCheckRedialAttemptLimit(u16 Cause);
void		VideoTelephonyAppUtilSecond2InCallDuration(u32 InCallTick, MAE_WChar* pWStr);
void		VideoTelephonyAppUtilSetImagePosition( IWidget * pContainer, IWidget* pImageWdg, boolean bVisible, s32 x_pos, s32 y_pos );
u32		VideoTelephonyAppUtilCallSetupNotificationMap(u32 index);
u32		VideoTelephonyAppUtilInCallNotificationMap(u32 index);
s16		VideoTelephonyAppUtilGetRedialTime(u8 CurrCount);
u8*		VideoTelephonyAppUtilFindWChar(u8* pSourStr);
boolean	VideoTelephonyAppUtilIsOnlyWChar(const u8* pSourStr);
void		VideoTelephonyAppUtilTruncateWChar(u8* pSourStr, u8* pOutStr, u16 nOutLen);
void		VideoTelephonyAppUtilTruncateRedundantChar(u8* pSourStr, u8* pOutStr, u16 nOutLen);
#ifndef __MMI_PHBAP_DISABLE_GROUP__
void		VideoTelephonyAppUtilGetImageIDFromContactGroup(IBase* pUser, u8 u8OutgoingCallIdx);
#endif // #ifndef __MMI_PHBAP_DISABLE_GROUP__
#endif /* __MMI_VIDEOTELEPHONYAPP_UTIL_H__ */
