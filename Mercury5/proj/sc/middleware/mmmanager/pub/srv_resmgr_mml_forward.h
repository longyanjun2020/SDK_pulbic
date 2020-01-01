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
* @file    srv_resmgr_mml_forward.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MML_FORWARD_H__
#define __SRV_RESMGR_MML_FORWARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

/*=============================================================*/
// Forward declarations
/*=============================================================*/
/* srv_resmgr_mmlcommon_types.h */
typedef_opaque_enum(MmlUseCaseGroupId_e_,  MmlUseCaseGroupId_e);
typedef_opaque_enum(MmlFilenameFormat_e_,  MmlFilenameFormat_e);
typedef_opaque_enum(MmlFileOperatingMode_e_, MmlFileOperatingMode_e);
typedef_opaque_enum(MmlApplicationDataId_e_,  MmlApplicationDataId_e);
/* srv_resmgr_mml_api.h */
typedef struct SrvResMgrMmlModule_t          *SrvResMgrMmlModule_h;
typedef_opaque_enum(SrvResMgrMmlDependency_e_, SrvResMgrMmlDependency_e);
/* srv_resmgr_mml_types.h */
typedef struct MmlMultimediaCapability_t_    MmlMultimediaCapability_t;
/* srv_resmgr_mmlaudio_types.h */
typedef_opaque_enum(MmlUseCaseAudioId_e_,    MmlUseCaseAudioId_e);
/* srv_resmgr_mmlvideo_types.h */
typedef_opaque_enum(MmlUseCaseVideoId_e_,    MmlUseCaseVideoId_e);
/* srv_resmgr_mmlimage_types.h */
typedef_opaque_enum(MmlUseCaseImageId_e_,    MmlUseCaseImageId_e);
/* srv_resmgr_mmlgame_types.h */
typedef_opaque_enum(MmlUseCaseGameId_e_,     MmlUseCaseGameId_e);
/* srv_resmgr_mmlusb_types.h */
typedef_opaque_enum(MmlUseCaseUsbId_e_,      MmlUseCaseUsbId_e);
/* srv_resmgr_mmltv_types.h */
typedef_opaque_enum(MmlUseCaseTvId_e_,       MmlUseCaseTvId_e);
/* srv_resmgr_mmlcamera_types.h */
typedef_opaque_enum(MmlUseCaseCameraId_e_,   MmlUseCaseCameraId_e);
/* srv_resmgr_mmlradio_types.h */
typedef_opaque_enum(MmlUseCaseRadioId_e_,    MmlUseCaseRadioId_e);
/* srv_resmgr_mmlgps_types.h */
typedef_opaque_enum(MmlUseCaseGpsId_e_,      MmlUseCaseGpsId_e);
/* srv_resmgr_mmlwlan_types.h */
typedef_opaque_enum(MmlUseCaseWlanId_e_,     MmlUseCaseWlanId_e);
/* srv_resmgr_mmlvideosdk_types.h */
typedef_opaque_enum(MmlUseCaseVideoSdkId_e_, MmlUseCaseVideoSdkId_e);
/* srv_resmgr_mmlrfid_types.h */
typedef_opaque_enum(MmlUseCaseRfidId_e_, MmlUseCaseRfidId_e);
/* srv_resmgr_mmlconcurrent_types.h */
typedef struct MmlPlatformCapability_t_      MmlPlatformCapability_t;
//typedef_opaque_enum(MmlPlatformChipType_e_,  MmlPlatformChipType_e);
typedef_opaque_enum(MmlConcurrentSection_e_, MmlConcurrentSection_e);
/* srv_resmgr_mmlutility_api.h */
typedef_opaque_enum(MmlUtilityResult_e_,     MmlUtilityResult_e);
typedef struct MmlFileNameInfo_t_            MmlFileNameInfo_t;
typedef_opaque_enum(MmlFileGetFileNameType_e_, MmlFileGetFileNameType_e);
typedef struct MmlRingOpen_t_                MmlRingOpen_t;
typedef_opaque_enum(MmlRingOperatingMode_e_, MmlRingOperatingMode_e);
typedef struct MmlRingCallback_t_            MmlRingCallback_t;
typedef struct MmlRingMessage_t_             MmlRingMessage_t;
/* srv_resmgr_mmlcommon_types.h */
typedef_opaque_enum(MmlErrCode_e_,           MmlErrCode_e);
/* MML_Manager.h */
typedef_opaque_enum(MmlCallbackId_e_,        MmlCallbackId_e);
typedef struct MmlMultimediaGroup_t_         MmlMultimediaGroup_t;
typedef struct MmlNotifyCallback_t_       MmlNotifyCallback_t;

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MML_GET_UCGID(nUseCaseId)           ((MmlUseCaseGroupId_e)((nUseCaseId) >> 16))
#define MML_GET_UCGEVENT_BASE(eGroupId)     ( (u32)(eGroupId) << 16)
#define MML_GET_UCID_INIT_BASE(eGroupId)    (((u32)(eGroupId) << 16) | 0x00000000)
#define MML_GET_UCID_GET_BASE(eGroupId)     (((u32)(eGroupId) << 16) | 0x00000100)
#define MML_GET_UCID_SET_BASE(eGroupId)     (((u32)(eGroupId) << 16) | 0x00000200)
#define MML_GET_UCID_EXE_BASE(eGroupId)     (((u32)(eGroupId) << 16) | 0x00000300)

#define MML_DCACHE_ALIGN_SIZE               (32)
#define MML_DCACHE_ALIGN_MASK               (MML_DCACHE_ALIGN_SIZE - 1)
#define MML_DCACHE_ALIGN_CEIL(nSize)        (((u32)(nSize) + MML_DCACHE_ALIGN_MASK) & (~MML_DCACHE_ALIGN_MASK))
#define MML_DCACHE_ALIGN_FLOOR(nSize)       ((u32)(nSize) & (~MML_DCACHE_ALIGN_MASK))
#define MML_DCACHE_ALIGN_CEIL_D(nSize)      ((((u32)(nSize) + MML_DCACHE_ALIGN_MASK) & MML_DCACHE_ALIGN_MASK) ^ (MML_DCACHE_ALIGN_MASK))
#define MML_DCACHE_ALIGN_FLOOR_D(nSize)     ((u32)(nSize) & MML_DCACHE_ALIGN_MASK)

/*=============================================================*/
// Data type definition
/*=============================================================*/
#if !defined(TRUE)
#define TRUE  (1)
#endif

#if !defined(FALSE)
#define FALSE (0)
#endif

#if !defined(NULL)
#define NULL  (0)
#endif

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MML_FORWARD_H__

