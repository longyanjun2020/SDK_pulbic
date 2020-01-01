/**
 * @file    mmi_mmsrv_util.h
 * @brief   xxxx
 * @version $Id: mmi_mmsrv_util.h 38890 2009-08-29 16:22:38Z zinc.chen $
 */
#ifndef MMI_MMSRV_UTIL_H
#define MMI_MMSRV_UTIL_H

#include "mmi_mae_common_def.h"
#include "mmi_mae_sm_defs.h"
#include "mmi_mae_datamodel.h"

#include "mmi_mae_datamodel.h"
#include "mmi_mae_notifier.h"
#include "mmi_event.h"
#include "mmi_mae_clock.h"

#include "mmi_mmsrv_def.h"

#include "mmi_mmsrv_util.h"

//#include "mmi_mmsrv_priv.h"
//#include "mmi_if_mm.h"

//MMI_MMSRV_RSSI_Level_e MMSRV_UtilGetRSSILevel(u16 rssi);
//u8  MMSRV_UtilGetRSSILevelNew(u16 rssi, u16 ber, boolean bIsCheckErr);
void MMSRV_UtilPostExternalEvent(MAE_Notifier_t *pNotifier, MAE_EventId evt, u32 mask, u32 param1, u32 param2);
void MMSRV_UtilPostExternalEventEx(MAE_Notifier_t *pNotifier, MAE_EventId evt, u32 mask, u32 param1, u32 param2, PfnEventCleanup fnClean);

void MMSRV_UtilFreeMsgDataModel(IBase *pOwner, u32 lParam, u32 dParam);
void MMSRV_UtilCreateZeroRSSIData(IBase *pRecipient, u8 DualID);
//void MMSRV_UtilCreateAirplaneModeInd(IBase* pRecipient);
void MMSRV_UtilCreateNetworkInd(IBase *pRecipient, u32 u32NetStatus, u8 DualID);
void MMSRV_UtilCreateNetworkSearchCnf(IBase *pThis, IBase *pRecipient, u8 DualID);
MAE_Ret MMSRV_UtilGetDateTime(IBase *pThis, MMSRV_NITZInd_t *pData, MAE_DateTime_t *pDate);
s8 MMSRV_UtilGetTimeZone(MMSRV_NITZInd_t *pData);
u32 MMSRV_UtilGetWeekDay(MAE_DateTime_t *pDate);
MAE_Ret MMSRV_UtilGetLocalDateTime(MAE_DateTime_t *pUTCDateTime, MAE_DateTime_t *pOutDateTime, s8 s8TimeZoneOffset);
MAE_TimeZone_e MMSRV_UtilGetUTCTimeZone(s8 s8TimeZone, u8 dst);
#ifdef __3G_RIL_MMI__
MMI_MMSRV_NetworkType_e MMSRV_UtilGetNetworkType(MMSRV_NetworkRegInd_t NetWorkInfo, MMI_MMSRV_NetworkType_e currNetType);
#else //#ifdef __3G_RIL_MMI__
MMI_MMSRV_NetworkType_e MMSRV_UtilGetNetworkType(MMI_MMSRV_RegStat_e stat, MMI_MMSRV_NetworkType_e currNetType);
#endif //#ifdef __3G_RIL_MMI__
MAE_Ret MMSRV_UtilSendCFUReq(IBase *pThis, u8 DualMode);
MAE_WChar *MMSrv_GetErrorCause(u16 errorCode);
#endif /* MMI_MMSRV_UTIL_H */
