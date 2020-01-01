/**
* @file    mmi_srv_tv.h
* @brief
*
*/

#ifndef __MMI_SRV_CODEC_H__
#define __MMI_SRV_CODEC_H__


/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_codec_util.h"
#include "mmi_mediasrv_common.h"
#include "ABL_Gss.h"

/*=============================================================*/
// Variable Declarations
/*=============================================================*/


/*=============================================================*/
// Private Function Implementations
/*=============================================================*/


/*=============================================================*/
// Public Function Implementations
/*=============================================================*/


MAE_Ret SrvCodecCreate( SrvClient_t *pClient, s32 *pData );
MAE_Ret SrvCodecDestroy( SrvClient_t *pClient, s32 *pData );

/**
SrvCodecOpen
@brief  The interface is used to open codec.

@retval 0           if failed, sequence number = 0.
        !0          if successful, sequence number != 0.
 */
s32 SrvCodecOpen(void);

/**
SrvCodecClose
@brief  The interface is used to close codec.

@param[in]      nDecoder    the sequence number returned from SrvCodecOpen

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
*/
CodecSrvErrCode_e SrvCodecClose(s32 nDecoder);

/**
SrvCodecDecode
@brief  The interface is used to start codec to decode.

@param[in]      nDecoder        the sequence number returned from SrvCodecOpen
@param[in]      pInBuffer       Input buf
@param[in]      nBufferSize     the size of buffer
@param[in]      pOutSurf        output surface
@param[in]      nRotateAngle    rotating angle such as
@param[in]      pfnCb           callback function

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
*/
CodecSrvErrCode_e SrvCodecDecode(s32 nDecoder,
                                 u8 *pInBuffer,
                                 u32 nBufferSize,
                                 ABL_GSSPMSSurface_t pOutSurf,
                                 ABL_GssRotateAngle_e nRotateAngle,
                                 ABL_ImageStereoType_e eImgStereoType,
                                 CodecSrvDecodeCb pfnCb);

/**
SrvCodecDecodeRegion
@brief  The interface is used to define the region to decode.

@param[in]      nDecoder        the sequence number
@param[in]      pInBuffer       input buffer
@param[in]      nBufferSize     the size of buffer
@param[in]      pDecodeParm     decoding parameters
@param[in]      pOutSurf        output surface
@param[in]      pfnCb           callback function

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
*/
CodecSrvErrCode_e SrvCodecDecodeRegion(s32 nDecoder,
                                       u8 *pInBuffer,
                                       u32 nBufferSize,
                                       ABL_GssDecodeParam_t *pDecodeParm,
                                       ABL_GSSPMSSurface_t pOutSurf,
                                       ABL_ImageStereoType_e eImgStereoType,
                                       CodecSrvDecodeCb pfnCb);

/**
SrvCodecGetRapidImageInfo
@brief  The interface is used to get the image info rapidly.

@param[in]      nDecoder        the sequence number
@param[in]      pInBuffer       input buffer
@param[out]     pImageInfo      image info
@param[in]      bIsUrl          pInBuffer is URL or buffer

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
@retval CODEC_SRV_ERR__FORMAT_UNSUPPORT if the image format is not supported.
*/
CodecSrvErrCode_e SrvCodecGetRapidImageInfo(s32 nDecoder,
                                            u8 *pInBuffer,
                                            CodecSrvRapidImageInfo_t *pImageInfo,
                                            boolean bIsUrl);

/**
SrvCodecGetImgInfo
@brief  The interface is used to retrieve the image information.

@param[in]      nDecoder        the sequence number
@param[in]      pInBuffer       input buffer
@param[in]      pImageInfo      image info
@param[in]      bIsUrl          pInBuffer is URL or buffer

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
 */
CodecSrvErrCode_e SrvCodecGetImgInfo(s32 nDecoder,
                                    u8 *pInBuffer,
                                    u32 nBufSize,
                                    CodecSrvImageInfo_t *pImageInfo,
                                    boolean bIsUrl);

/**
SrvCodecDecodeNextFrame
@brief  The interface is used to decode the next frame.

@param[in]      nDecoder        the sequence number
@param[out]     pDelayTime      the delay time

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
*/
CodecSrvErrCode_e SrvCodecDecodeNextFrame(s32 nDecoder, u32 *pDelayTime);

/**
SrvCodecGetNextFrameDelayTime
@brief  The interface is used to get the delay time

@param[in]      nDecoder        the sequence number

@retval CODEC_SRV_ERR__SUCCESS          if successful
@retval CODEC_SRV_ERR__BAD_PARAMETERS   if any of the parameters is NULL.
*/
u32 SrvCodecGetNextFrameDelayTime(s32 nDecoder);

#endif //__MMI_SRV_CODEC_H__
