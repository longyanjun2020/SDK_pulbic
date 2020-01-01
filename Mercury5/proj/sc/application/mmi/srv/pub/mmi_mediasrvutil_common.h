/**
* @file mmi_mediasrvutil_common.h
*
* @version $Id$
*/
#ifndef __MMI_MEDIASRVUTIL_COMMON_H__
#define __MMI_MEDIASRVUTIL_COMMON_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "ABL_Aud.h"
#include "ABL_Vdo.h"
#include "ABL_Cam.h"
#include "ABL_Fmr.h"
#include "ABL_Gss.h"
#include "mmi_mediasrv_common.h"
#include "srv_ResMgr_Gss.h"
/*================================================
Media Service Common Macros
=================================================*/
#define MSRV_NUM    1
//#define MSRV_CALLOC(size)   MALLOC(size)
#define MSRV_CALLOC(size)   CALLOC(MSRV_NUM, size)

typedef struct MediaSrvRecInfo_t_
{
    MediaSrvAudCodec_e eSrvCodec;
    ABL_AudRecType_e eABLCodec;
    ABL_AudFrequency_e eFrequency;
    u32 nBitRate;
    ABL_AudChannelMode_e eChanMode;
} MediaSrvRecInfo_t;
/*================================================
Media Service Common Utility
=================================================*/
__SLDPM_FREE__ u16 MediaSrvUtilGetAppIdByInstanceId(void *pInstanceID);
__SLDPM_FREE__ u16 MediaSrvUtilGetAppIdByClsId(MAE_ClsId nClsId);
ABL_AudFormat_e MediaSrvUtilGetAudFormatByFileName(MAE_WChar *pFileName);
ABL_AudFormat_e MediaSrvUtilGetAudFormatByMimeType(u16 nAppId, MediaSrvMimeType_e eMimeType);
ABL_VdoMemFormat_e MediaSrvUtilGetVdoMemFormatByMimeType(u16 nAppId, MediaSrvMimeType_e eMimeType);
MediaSrvFileFormat_e MediaSrvUtilRemapAudFormat(ABL_AudFormat_e eAudFormat);
MAE_Ret MediaSrvUtilCheckParam(u32 nParam, u32 nParamBound);
void MediaSrvUtilGetRecParamByCodec(MediaSrvAudCodec_e eSrvCodec, ABL_AudRecType_e *pABLCodec, ABL_AudFrequency_e *pFrequency, u32 *pBitRate,  ABL_AudChannelMode_e *pChanMode);
MAE_Ret MediaSrvUtilGetFreeSpaceInSecond(MediaSrvAudCodec_e eAudCodec, const MAE_WChar *pUrl, u32 *pRemainSecond);
MAE_Ret MediaSrvUtilGetFreeSpaceInSecondEx(const MediaSrvRecInfo_t *pRecInfo, const MAE_WChar *pUrl, u32 *pRemainSecond);
MediaSrvMimeType_e MediaSrvUtilGetSrvMimeByMMIMimeType(MAE_MIME_et eMimeType);
bool MediaSrvUtilGetAudioPlaybackCapability(ABL_AudioGetPlaybackCapability_t *ptAudPlaybackCap, ABL_AudioPlaybackCapability_t *ptAudPlaybackCapInfo);
bool MediaSrvGetFmrCapability(ABL_FmrGetCapabilityParam_t *ptFmrGetCapability, ABL_FmrCapability_t *ptFmrCapability);
bool MediaSrvUtilGetAudioRecordCapability(ABL_AudioGetRecordingCapability_t *ptAudRecCap, ABL_AudioRecordingCapability_t *ptAudRecCapInfo);
bool MediaSrvUtilGetVideoPlaybackCapability(ABL_VideoGetPlaybackCapability_t *ptVdoGetPlaybackCap, ABL_VdoPlaybackCap_t *ptVdoPlaybackCapInfo);
bool MediaSrvUtilGetCamRecordCapability(ABL_CamGetRecordingCapability_t *ptCamGetRecCap, ABL_CamRecordingCap_t *ptCamRecCapInfo);
bool MediaSrvUtilGetImageDecCapability(ABL_GssImageGetDecodingCapability_t *ptImgGetDecCap, ABL_GssImageDecodingCapability_t *ptImgDecCapInfo);
__SLDPM_FREE__ MAE_Ret MediaSrvUtilRemapErrCode(ABL_CmnErrCode_e eErrCode);
bool MediaSrvUtilEmuGameGetCapability(ABL_GameGetGameCapability_t *pEmuGetCap, ABL_GameCapability_t *pEmuCapInfo);
/*-------------------------------------------------------------------------*/
#endif /* __MMI_MEDIASRVUTIL_COMMON_H__ */
