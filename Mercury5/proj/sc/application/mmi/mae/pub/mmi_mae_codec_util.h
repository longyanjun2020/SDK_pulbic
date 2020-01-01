/**
* @file mmi_mae_codec_util.h
*
**/
#ifndef __MMI_MAE_CODEC_UTIL_H__
#define __MMI_MAE_CODEC_UTIL_H__

#include "mmi_mae_common_def.h"
#include "srv_ResMgr_Gss.h"
/************************************************************************/
/* enum type                                             */
/************************************************************************/
typedef enum CodecSrvErrCode_e_
{
	CODEC_SRV_ERR__JPD_RES_NOT_SUPPORT = (s32)-8,       /*IMAGE_JPD_RES_NOT_SUPPORT(-8)*/
	CODEC_SRV_ERR__RE_ENTRY_ABORT = (s32)-7,            /*IMAGE_RE_ENTRY_ABORT*/
	CODEC_SRV_ERR__BAD_PARAMETERS = (s32)-6,            /*IMAGE_BAD_PARAMETERS*/
	CODEC_SRV_ERR__WRONG_HANDLE,                        /*IMAGE_WRONG_HANDLE*/
	CODEC_SRV_ERR__NOT_ENOUGH_MEMORY,                   /*IMAGE_NOT_ENOUGH_MEMORY*/
	CODEC_SRV_ERR__TOO_MUCH_EXECUTING_INSTANCE,         /*IMAGE_TOO_MUCH_EXECUTING_INSTANCE*/
	CODEC_SRV_ERR__DEC_ERR,                             /*IMAGE_DEC_ERR*/
	CODEC_SRV_ERR__FORMAT_UNSUPPORT,                    /*IMAGE_FORMAT_UNSUPPORT*/
	CODEC_SRV_ERR__ERROR,                               /*IMAGE_ERROR:0*/
	CODEC_SRV_ERR__SUCCESS,                             /*IMAGE_SUCCESS:1*/
	CODEC_SRV_ERR__SUCCESS_WAITING,                     /*IMAGE_SUCCESS_WAITING*/
	CODEC_SRV_ERR__SUCCESS_MORE_FRAMES,                 /*IMAGE_SUCCESS_MORE_FRAMES*/
	CODEC_SRV_ERR__SUCCESS_REJECT,						/*IMAGE_REJECT*/
	CODEC_SRV_ERR__SUCCESS_ABORT						/*IMAGE_SUCCESS_ABORTED*/
} CodecSrvErrCode_e;

typedef enum
{
	CODEC_SRV_IMG_QUALITY_LOW
	,CODEC_SRV_IMG_QUALITY_NORMAL
	,CODEC_SRV_IMG_QUALITY_HIGH
	,CODEC_SRV_IMG_QUALITY_NUM
} CodecSrvImgQuality_e;

typedef enum
{
	CODEC_SRV_IMG_COLORFMT_RGB_565
	,CODEC_SRV_IMG_COLORFMT_YUV_420
	,CODEC_SRV_IMG_COLORFMT_UNKNOWN
	,CODEC_SRV_IMG_COLORFMT_NUM
} CodecSrvImgColorFormat_e;

typedef enum
{
	CODEC_SRV_PATH_DIR,
	CODEC_SRV_PATH_PREFIX,
	CODEC_SRV_PATH_ABSOLUTE
} CodecSrvStoragePathOption_e;

/************************************************************************/
/* structure type  define */
/************************************************************************/
typedef ABL_RapidImageInfo_t CodecSrvRapidImageInfo_t;
typedef ABL_ImageInfo_t CodecSrvImageInfo_t;
typedef ABL_GssRotateAngle_e CodecSrvRotateAngle_e;
typedef ABL_GssDecodeParam_t CodecSrvDecodeParam_t;
typedef ABL_GSSPMSSurface_t CodecSrvPMSSurface_t;
typedef ABL_ImageFrameInfo_t CodecSrvFrameInfo_t;

typedef struct
{
	u32 nPosX;
	u32 nPosY;
	u32 nWidth;
	u32 nHeight;
	u32 nStride;
} CodecSrvImageRegion_t;

typedef struct
{
	u8 *pBuffer;
	u32 nBufferLen;
} CodecSrvImgDataBuf_t;

typedef struct
{
	CodecSrvImgQuality_e eQuality;
	CodecSrvImgColorFormat_e eFormat;
	CodecSrvImageRegion_t tRegion;
	CodecSrvImgDataBuf_t tSrcBuf;
} CodecSrvEncodeParm_t;

typedef void (*CodecSrvDecodeCb)(void *pThis, CodecSrvErrCode_e nErrCode);
typedef void (*CodecSrvEncodeCb)(void *pThis, CodecSrvErrCode_e nErrCode, u32 nCusData, CodecSrvImgDataBuf_t *pEncodedImg);

typedef struct CodecSrvCbData_t_
{
	u32 nSrvClientInsId;
	CodecSrvDecodeCb pfnCb;
} CodecSrvCbData_t;

typedef struct CodecSrvEncodeCbData_t_
{
	u32 nSrvClientInsId;
	u32 nCusData;
	CodecSrvEncodeCb pfnCb;
} CodecSrvEncodeCbData_t;

/************************************************************************/
/* Public Interfaces */
/************************************************************************/
s32 CodecSrvOpen(void);
CodecSrvErrCode_e CodecSrvClose(s32 nDecoder);
CodecSrvErrCode_e CodecSrvDecode
(
 u32 nSrvClient,
 s32 nDecoder,
 u8 *pInBuffer,
 u32 nBufferSize,
 ABL_GSSPMSSurface_t pOutSurf,
 ABL_GssRotateAngle_e nRotateAngle,
    ABL_ImageStereoType_e eImgStereoType,
 CodecSrvDecodeCb pfnCb
 );

CodecSrvErrCode_e CodecSrvDecodeRegion
(
 u32 nSrvClient,
 s32 nDecoder,
 u8 *pInBuffer,
 u32 nBufferSize,
 ABL_GssDecodeParam_t *pDecodeParm,
 ABL_GSSPMSSurface_t pOutSurf,
    ABL_ImageStereoType_e eImgStereoType,
 CodecSrvDecodeCb pfnCb
 );

void CodecSrvEncodeToFile
(
 u32 nSrvClient,
 CodecSrvStoragePathOption_e ePathOpt,
 MAE_WChar *pDestPath,
 CodecSrvEncodeParm_t *pEncodeParms,
 u32 nCusData,
 CodecSrvEncodeCb pfnCb
 );

void CodecSrvEncodeToBuffer
(
 u32 nSrvClient,
 CodecSrvImgDataBuf_t *pDestBuf,
 CodecSrvEncodeParm_t *pEncodeParms,
 u32 nCusData,
 CodecSrvEncodeCb pfnCb
 );

CodecSrvErrCode_e CodecSrvGetRapidImageInfo
(
 u32 nSrvClient,
 s32 nDecoder,
 u8 *pInBuffer,
 CodecSrvRapidImageInfo_t *pImageInfo,
 boolean bIsUrl
 );
CodecSrvErrCode_e CodecSrvGetImageInfo
(
 u32 nSrvClient,
 s32 nDecoder,
 u8 *pInBuffer,
 u32 nBufSize,
 CodecSrvImageInfo_t *pImageInfo,
 boolean bIsUrl
 );
CodecSrvErrCode_e CodecSrvDecodeNextFrame(u32 nSrvClient, s32 nDecoder, u32 *pDelayTime);
u32 CodecSrvGetNextFrameDelayTime(u32 nSrvClient, s32 nDecoder);
u8 CodecSrvHasNextFrame(s32 nDecoder);
CodecSrvErrCode_e CodecSrvGetFrameInfo(s32 nDecoder, CodecSrvFrameInfo_t *pFrameInfo);

#endif /* __MMI_MAE_CODEC_UTIL_H__ */
