/**
* @file    mmi_ccapp_util.h
* @brief   xxxx
* @version $Id: mmi_ccapp_util.h 1733 2007-09-05 09:27:04Z collin.chiang $
*/
#ifndef __MMI_CCAPP_UTIL_H__
#define __MMI_CCAPP_UTIL_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_widget.h"
#include "mmi_ccsrv_def.h"
#include "mmi_phbsrv_def.h"


u16*			CcAppUtilAsciiToUCS2Len(u16* pUnicode, const u8* pAscii, u16 len);
boolean			CcAppUtilCheckMPTYCallandStatus(CallTable_t* pCallTable, MMI_CCSRV_Status_e* status);
u8			    CcAppUtilGetMPTYNumber(CallTable_t* pCallTable);
boolean			CcAppUtilFindSingleCallIndex(CallTable_t* pCallTable, u8* CallIndex);
void			CcAppUtilSetData2CallInfo(IWidget *pStatusImage, IWidget *pCallInfo, CallEntry_t *pCallEntry, IBase* pThis);
void			CcAppUtilHideOptionItem(IWidget *pMenu, u32 u32ItemID);
void 			CcAppUtilShowOptionItem(IWidget *pMenu, u32 u32ItemID);
void            CcAppUtilBTHandleforATCHLD(  IBase* pUser, u32 param );
void			CcAppUtilShortStringForPublicMMI(u16 len, u8* pStr, IBase* pUser);
u8				CcAppUtilCheckRedialAttemptLimit(u16 Cause);
void			CcAppUtilSecond2InCallDuration(u32 InCallTick, MAE_WChar* pWStr);
void			CcAppUtilSetImagePosition( IWidget * pContainer, IWidget* pImageWdg, boolean bVisible, s32 x_pos, s32 y_pos );
u32			CcAppUtilCallSetupNotificationMap(u32 index);
u32			CcAppUtilInCallNotificationMap(u32 index);
MAE_Ret CcAppOperationNotAllowScreenCb(void *pApplet, MAEEvent_t eEvt, u32 nParam1, u32 nParam2);


s16 CcAppUtilGetRedialTime(u8 CurrCount);
u8* CcAppUtilFindWChar(u8* pSourStr);
boolean CcAppUtilIsOnlyWChar(const u8* pSourStr);
void CcAppUtilTruncateWChar(u8* pSourStr, u8* pOutStr, u16 nOutLen);
void CcAppUtilTruncateRedundantChar(u8* pSourStr, u8* pOutStr, u16 nOutLen);
#ifndef __MMI_PHBAP_DISABLE_GROUP__
void CcAppUtilGetImageIDFromContactGroup(IBase* pUser, u8 u8OutgoingCallIdx);
#endif

#ifdef __DISTORTED_VOICE_MMI__
void CcAppUtilSetDistortedVoiceSettings(IBase* pUser, boolean bStatus, u8 nEffect);
void CcAppUtilGetDistortedVoiceSettings(IBase* pUser, boolean * bStatus, u8 * nEffect);
#endif // __DISTORTED_VOICE_MMI__

#endif /* __MMI_CCAPP_UTIL_H__ */
