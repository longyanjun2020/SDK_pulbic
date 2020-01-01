/**
* @file Simu_Vdo.h
*
* This header file defines the interface of lower layer device simulation for video
*
*/
#ifndef __SIMU_VDO_H__
#define __SIMU_VDO_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "Simu_Cmn.h"
#include "ABL_Vdo.h"
// for Video Record WhiteBox test
#include "srv_resmgr_mmlvideo_types.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
// for Video Record WhiteBox test
typedef struct SimuVdrWBUserData_t_
{
    u32 VdrWBId;
    MmlVideoUCParam_t VideoUCParam;         // Video Use Case Parameter
} SimuVdrWBUserData_t;

#if 1 // Sync. with mdl_vdr.c
typedef enum
{
    MDLVDR_WB_FAKE_ERROR_BASE = 0x70F0,     // Avoid fake error mis-use
    MDLVDR_WB_FAKE_PAUSE_RACING,            // Paused command v.s. Run-time Error
    MDLVDR_WB_FAKE_LIMIT_RACING,            // Limit reached v.s. Pause/Stop command
    MDLVDR_WB_FAKE_STOP_RACING,             // Stop command v.s. Run-time error
    MDLVDR_WB_FAKE_INIT_TIMEOUT,            // Init timeout
    MDLVDR_WB_FAKE_PAUSE_TIMEOUT,           // Pause timeout
    MDLVDR_WB_FAKE_STOP_TIMEOUT,            // Stop timeout
    MDLVDR_WB_FAKE_VIDEO_ENCODE_TIMEOUT,    // Video encode timeout
    MDLVDR_WB_FAKE_AUDIO_ENCODE_TIMEOUT,    // Audio encode timeout
    MDLVDR_WB_FAKE_AUDIO_INIT_FAIL,         // Audio init fail
    MDLVDR_WB_FAKE_VIDEO_INIT_FAIL,         // Video init fail
    MDLVDR_WB_FAKE_WRITE_INIT_FAIL,         // Write init fail
    MDLVDR_WB_FAKE_WRITE_PACKET_ERROR,      // Write packet error
    MDLVDR_WB_FAKE_AUDIO_ENCODE_ERROR,      // Audio encode error
    MDLVDR_WB_FAKE_VIDEO_ENCODE_ERROR,      // Video encode error
    MDLVDR_WB_FAKE_DISK_FULL,               // Disk full

} FakeErrorType_e;

typedef struct _MdlVdrFakeErrorParam_t_
{
    FakeErrorType_e eErrorType;

    union {
        u32 nErrorValue;                         // General Error Value
    } uParam;

} MdlVdrFakeErrorParam_t;
#endif
// for Video Record WhiteBox test
typedef struct SimuVdrWBUserError_t_
{
    u32 VdrWBId;
    MdlVdrFakeErrorParam_t tFakeErrParam;   // Fake Error Param
} SimuVdrWBUserError_t;

//for kmv metadata test
#define KMV_MOVIE_IMAGE_SIZE (16*1024)
#define KMV_MOVIE_NAME_LENGTH (120)
#define KMV_MOVIE_STARRING_LENGTH (200)
#define KMV_MOVIE_SYNOPSIS_LENGTH (800)

typedef enum ven_codec_KmvCategoryType_e_
{
    KmvCategoryType_Action = 0,
    KmvCategoryType_Adventure,
    KmvCategoryType_Animation,
    KmvCategoryType_Comedy,
    KmvCategoryType_Documentary,
    KmvCategoryType_Drama,
    KmvCategoryType_FamilyKids,
    KmvCategoryType_Fantasy,
    KmvCategoryType_Horror,
    KmvCategoryType_Music,
    KmvCategoryType_Mystery,
    KmvCategoryType_PerformingArts,
    KmvCategoryType_Romance,
    KmvCategoryType_SciFi,
    KmvCategoryType_Sports,
    KmvCategoryType_Suspense,
    KmvCategoryType_War,
    KmvCategoryType_Western,
    KmvCategoryType_Others,
    KmvCategoryType_NumOfCategory,
    KmvCategoryType_Invalid = 0xFFFF
} ven_codec_KmvCategoryType_e;

typedef struct//four bytes alignment
{
    u8 strMovieName[KMV_MOVIE_NAME_LENGTH];	//utf8 encoding
    u16 nMovieTime;
    u16 nMovieYear;
    u8 strMovieStarring[KMV_MOVIE_STARRING_LENGTH];
    u8 strMovieSynopsis[KMV_MOVIE_SYNOPSIS_LENGTH];
    ven_codec_KmvCategoryType_e eCategory;
    u32 nImageSize; //in bytes
    u8 aryImageData[KMV_MOVIE_IMAGE_SIZE];
} ven_codec_kmvExtInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
void Simu_VdoGetPlaybackCapabilityCb(void *pUserData, void *pParam);
void Simu_VdoGetPositionCb(void *pUserData);
void Simu_VdoGetFileInfoCb(void *pUserData);
void Simu_VdoGetMemInfoCb(void *pUserData);
void Simu_VdoSetPlaySpeedCb(void *pUserData);
void Simu_VdoSetPositionCb(void *pUserData);
void Simu_VdoResetWindowCb(void *pUserData);
#ifdef __MMI_STEREO_VIDEO__
void Simu_VdoSetConfigurationCb(void *pUserData);
#endif
void Simu_VdoStopPlayCb(void *pUserData);
void Simu_VdoPausePlayCb(void *pUserData);
void Simu_VdoResumePlayCb(void *pUserData);
void Simu_VdoOpenCb(void *pUserData);
void Simu_VdoCloseCb(void *pUserData);
void Simu_VdoPlayCb(void *pUserData);
void Simu_VdoGetInfoCb(void *pUserData);
void Simu_VdoDecodeFirstFrameAsyncCb(void *pUserData);
void Simu_VdoCancelDecodeFirstFrameCb(void *pUserData);
void Simu_VdoSeekCb(void *pUserData);
void Simu_VdoCancelSeekCb(void *pUserData);

#endif //__SIMU_VDO_H__
