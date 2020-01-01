/**
 * @file    mmi_mmsrv_crunch.h
 * @brief   xxxx
 * @version $Id: mmi_mmsrv_crunch.h 21130 2009-01-22 12:19:45Z lih.wang $
 */
#ifndef MMI_MMSRV_CRUNCH_H
#define MMI_MMSRV_CRUNCH_H

#include "mmi_mmsrv_priv.h"


void MMSRV_CrunchForSearchNetworkCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForNetworkRegCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForNetworkRegInd(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForAbortCnf(MMI_MMSRV *pThis, void *pSM);
#ifdef __GPRS_MMI__
void MMSRV_CrunchForGprsAttachCnf(MMI_MMSRV *pThis, void *pSM);
#endif //__GPRS_MMI__
void MMSRV_CrunchForUpdatePreferredListCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForQueryPreferredListCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForChangeBandCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForQueryBandCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForChangeLineCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForQueryLineCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForSignalStrengthInd(MMI_MMSRV *pThis, void *pSM);
#ifdef __GPRS_MMI__
void MMSRV_CrunchForGPRSRegInd(MMI_MMSRV *pThis, void *pSM);
#endif //__GPRS_MMI__
void MMSRV_CrunchDivertCallStatusInd(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchDivertCallStatusCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForNITZInd(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForRegisteredPlmnInfoCnf(MMI_MMSRV *pThis, void *pSM);
#ifdef __GPRS_MMI__
void MMSRV_CrunchForSetWgprsCnf(MMI_MMSRV *pThis, void *pSM);
void MMSRV_CrunchForQueryWgprsCnf(MMI_MMSRV *pThis, void *pSM);
#endif //__GPRS_MMI__
void MMSRV_NetworkInfoQueryTimerCB(void *data, void *pUserData);
void MMSRV_CFUStatusQueryTimerCB(void *data, void *pUserData);

#endif /* MMI_MMSRV_CRUNCH_H */
