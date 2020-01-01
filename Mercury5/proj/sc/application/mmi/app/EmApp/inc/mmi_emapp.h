////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file mmi_emapp.h
*
* Class Id: CLSID_EMAPP
*
* @version $Id: mmi_em.h 33312 2009-06-14 11:50:12Z eric.chen $
*/
#ifndef __MMI_EMAPP_H__
#define __MMI_EMAPP_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_em.h"
#include "mmi_common_em_type.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define EM_EVT_SendSMSCompleted	(CLSID_EMAPP << 16 | 12)
#define EM_IEVT_DetectAccStatus (CLSID_EMAPP << 16 | 20)
#define EM_IEVT_ATV	(CLSID_EMAPP << 16 | 27)
#define EM_IEVT_ATVSwitchRegion (CLSID_EMAPP << 16 | 32)
#define EM_IEVT_ATVPollingTimerExpire (CLSID_EMAPP << 16 | 33)
#define EM_IEVT_ATVSwitchTimerExpire (CLSID_EMAPP << 16 | 35)
#define EM_IEVT_GPSCmdCnf       (CLSID_EMAPP << 16 | 40)
#define EM_IEVT_RAIDumpStatus       (CLSID_EMAPP << 16 | 41)
#define EM_IEVT_WIFIDeleteFifo (CLSID_EMAPP << 16 | 42)
#define EM_IEVT_WIFIOff (CLSID_EMAPP << 16 | 43)
#define EM_IEVT_WIFIInitFifo (CLSID_EMAPP << 16 | 44)
#define EM_IEVT_WIFIAirplaneOn (CLSID_EMAPP << 16 | 45)
#define EM_IEVT_WIFIAirplaneOff (CLSID_EMAPP << 16 | 46)
#define EM_IEVT_WIFICreateDataLink (CLSID_EMAPP << 16 | 47)
#define EM_IEVT_WIFIDestroyDataLink (CLSID_EMAPP << 16 | 48)
#define EM_IEVT_WIFISetFwTest (CLSID_EMAPP << 16 | 53)
#define EM_IEVT_WIFITurnOnWifi (CLSID_EMAPP << 16 | 54)
#define EM_IEVT_BackHistory (CLSID_EMAPP << 16 | 55)
#define EM_IEVT_FMRSetAreaConfigCnf (CLSID_EMAPP << 16 | 56)
#define EM_IEVT_UpdateTSFirmware (CLSID_EMAPP << 16 | 57)
#define EM_IEVT_WIFIGetDeviceCnf (CLSID_EMAPP << 16 | 58)
#define EM_IEVT_WIFISocketConnectCnf (CLSID_EMAPP << 16 | 59)
#define EM_IEVT_WIFISendDataCnf (CLSID_EMAPP << 16 | 60)
#define EM_IEVT_WIFIReceiveDataCb (CLSID_EMAPP << 16 | 61)
#define EM_IEVT_WIFISocketDestroyCb (CLSID_EMAPP << 16 | 62)

typedef enum FmradioSrvEvent_e_
{
    FMRADIOSRV_EVT_PlayCnf = (CLSID_FMRADIOSRV << 16 | 1)
   ,FMRADIOSRV_EVT_StopCnf
   ,FMRADIOSRV_EVT_SetFrequencyCnf
   ,FMRADIOSRV_EVT_SearchChannelCnf
   ,FMRADIOSRV_EVT_SetAreaCnf
   ,FMRADIOSRV_EVT_GetChannelInfoCnf
   ,FMRADIOSRV_EVT_StatusChangeInd
   ,FMRADIOSRV_EVT_AsycSearchChannelInd
   ,FMRADIOSRV_EVT_RecStatusChangeInd
   ,FMRADIOSRV_EVT_PreemptInd
   ,FMRADIOSRV_EVT_SuspendInd
   ,FMRADIOSRV_EVT_ResumeInd
   ,FMRADIOSRV_EVT_Invalid
   ,FMRADIOSRV_EVT_Num
} FmradioSrvEvent_e;

/*
 * When EmApp is built as a sldlm (static load, dynamic link module), 
 * some functions/variables should be set as exception so that
 * the sldlm module can be loaded successfully.
 * The functions/variables associated with loading/unloading the sldlm
 * cannot be put into the sldm.
 * They should be given the __DLM_EMAPP_FREE__ attribute so that
 * they are free from being compressed by the sldlm mechanism.
 *
 * To reduce the number of veneers, the attribute is set to be the same
 * with dpm.
 *
 * Principle: assign __DLM_EMAPP_FREE__ to functions/data that are used
 * before the EmAppNew()
 * */
#if defined(__DLM_EMAPP_MMI__) && defined(__arm) && defined(__TARGET__)
#define __DLM_EMAPP_FREE__ __attribute__((section(".sldpm_free")))
#else
#define __DLM_EMAPP_FREE__
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/


 /*=============================================================*/
 // Global function definition
 /*=============================================================*/
__DLM_EMAPP_FREE__ void EmPreNew(void);
__DLM_EMAPP_FREE__ MAE_Ret EmAppNew(MAE_ClsId id, void **ppObj);
#endif /* __MMI_EMAPP_H__ */
