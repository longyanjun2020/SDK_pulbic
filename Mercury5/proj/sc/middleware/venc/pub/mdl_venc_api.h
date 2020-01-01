////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MDL_VENC_API_H_
#define _MDL_VENC_API_H_

#define SW263E_FAIL     0
#define SW263E_SUCCESS  1

#define SW263E_BUFFULL  0
#define SW263E_FRMDONE  1

// <<< Calling sequences >>>
//
//      MApi_H263_Create
//      (suggested) MApi_H263_GetMemReq
//      MApi_H263_MMAPInit
//      MApi_H263_Initialize
//          (optional) MApi_H263_SetFramerate
//          (optional) MApi_H263_SetIntraUpdate
//          (optional) MApi_H263_SetAdvBitrateMode
//      (optional) MApi_H263_StartEncode
//
//      MApi_H263_CompressOnePicture                  L
//          (optional) MApi_H263_GetBits              O
//      (if necessary) MApi_H263_ContinueOnePicture   O
//          (optional) MApi_H263_GetBits              P
//
//      (optional) MApi_H263_StopEncode
//      MApi_H263_Destroy


/*!
 * \brief
 *  Create a video encoder instance and load default settings.
 *
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note
 * \warning Currently only one instance is supported. Calling this API will overwrite all settings.
 */
int MApi_H263_Create(void);

/*!
 * \brief
 *  Destroy the video encoder instance.
 *
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note
 * \warning
 */
int MApi_H263_Destroy(void);

/*!
 * \brief
 *  Query the minimal buffer pool size (in bytes).
 *
 * \param[in] width The image width.
 * \param[in] height The image height.
 * \param[in] format The encoding format (0: H263).
 * \param[out] pReqSize To receive the required buffer pool size.
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note
 * \warning
 */
int MApi_H263_GetMemReq(int width, int height, int format, int* pReqSize);

/*!
 * \brief
 *  Set buffer pool to video encoder.
 *  The caller is responsible to allocate the buffer and maintain its validity;
 *  the caller is responsible to de-allocate the buffer after calling MApi_H263_StopEncode().
 *
 * \param[in] buf The buffer pool logical (CPU-side) address.
 * \param[in] buf_pa The buffer pool physical (IP-side) address; must be continuous.
 * \param[in] buf_size The size of the buffer pool.
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note There is no size checking here. The caller is suggested to call XXX first to know the miminal buffer size to allocate.
 * \warning If the buffer pool size is not enough, calling MApi_H263_Initialize() may not success.
 */
int MApi_H263_MMAPInit(unsigned char *buf, unsigned int buf_pa, unsigned int buf_size);

/*!
 * \brief
 *  This API is used to initialize the video encoder.
 *  If the returned value is SW263E_SUCCESS, the video encoder is ready to encode.
 *
 * \param[in] in_width Image width (must be multiple of 16).
 * \param[in] in_height Image height (must be multiple of 16).
 * \param[in] in_sq Speed-Quality indicator; the valid range is [0, 4], lower means faster, lower CPU usage, lower quality.
 * \param[in] in_bitrate The target average bitrate, in unit of "bits per second". If the value is 0, in_qp is used for constant quality encoding.
 * \param[in] in_qp The constant qp used in constant quality mode; the valid range is [2, 30]. Lower means better quality, larger bitstream size.
 * \return SW263E_SUCCESS if success. SW263E_FAIL if buffer pool is not enough, or input parameter is not valid.
 * \sa
 * \note in_qp is of useless when in_bitrate is not 0.
 * \warning
 */
int MApi_H263_Initialize(int in_width, int in_height, int in_sq, int in_bitrate, int in_qp);

/*!
 * \brief
 *  Change default framerate (=15).
 *  This function must be called after MApi_H263_Initialize().
 *
 * \param[in] nFramerate The input framerate; also the maximal framerate achivable by the video encoder.
 * \param[in] nMinFramerate The minimal framerate achieved by the video encoder.
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note If nMinFramerate is smaller than nFramerate, the video encoder will, when necessary, lower effecitve output framerate to trade off image quality.
 * \warning The nFramerate must match the input framerate (by frontend sensor, ICP...); otherwise the output bitrate will not match.
 */
int MApi_H263_SetFramerate(int nFramerate, int nMinFramerate);

/*!
 * \brief
 *  Set advanced bitrate mode.
 *
 * \param[in] nBitrate The target average bitrate, in unit of "bits per second". Must>0 (can be 0 only if nQP>0).
 * \param[in] nQP The constant qp used in constant quality mode; the valid range is [2, 30]. Lower means better quality, larger bitstream size.
 * \param[in] nBitrateMode The bitrate control mode: Valid modes are:
 *            2--constant bitrate, 3--variable bitrate, 5--strict constant bitrate.
 * \param[in] nGOPSize GOPSize = 1 + Number_of_PFrame_Between_IFrame. The value must >= 1.
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note For storage, bitrate mode 2 or 3 is suggested.
 * \note For storage, GOPSize is typically set to framerate.
 * \note When nBitrate>0, nQP is of no use.
 * \note When nBitrate=0 (i.e, nQP>0), nBitrateMode is of no use.
 * \warning
 */
int MApi_H263_SetAdvBitrateMode(int nBitrate, int nQP, int nBitrateMode, int nGOPSize);

/*!
 * \brief
 *  Set IntraUpdate modes.
 *
 * \param[in] bFIR 1 to enable Forced-Intra-Refresh (H263: When GOP length is larger than 132, must enable this.)
 * \param[in] bAIR 1 to enable Adaptive-Intra-Refresh
 * \param[in] bCIR 1 to enable Cyclic-Intra-Refresh
 * \param[in] nAIRCount How many MB's are intra-updated when AIR mode. (>0)
 * \param[in] nCIRDuration How many frames before the next row-by-row MB intra-updating. (> height_in_mb)
 * \return SW263E_SUCCESS if success.
 * \sa
 * \note This API can be used when error-prone video transmission; for local storage, don't use it.
 *       The default H263 GOP length is smaller than 132.
 * \warning
 */
int MApi_H263_SetIntraUpdate(int bFIR, int bAIR, int bCIR, int nAIRCount, int nCIRDuration);

/*!
 * \brief
 * Get the video sequence header (i.e, any bytes before the very first frame header of this video).
 *
 * \param[in,out] pOutBuf The caller-allocated bitstream buffer to receive bytes.
 * \param[in] nOutBufSize The bitstream buffer size.
 * \param[out] pByteCount To receive the byte count.
 * \return SW263E_SUCCESS
 * \sa
 * \note When H.263 encoding, the returned byte count will be 0.
 * \warning
 */
int MApi_H263_StartEncode(unsigned char* pOutBuf, unsigned int nOutBufSize, unsigned int* pByteCount);

// Indicating the previous frame is dirty so was discarded by the caller.
// Inside video encoder, the previous reconstruction frame will not be taken as reference frame.
#define FLAG_PRV_FRAME_DIRTY        0x1
// Indiacting the caller explicitly wants video encoer to encode curent frame as I-frame.
#define FLAG_CUR_FRAME_FASTUPDATE   0x2

/*!
 * \brief
 *  Encode one new input frame.
 *
 * \param[in] pRawBuf The input frame buffer, in I420 (planar) format.
 * \param[in,out] pOutBuf The caller-allocated bitstream buffer to receive bytes.
 * \param[in] nOutBufSize The bitstream buffer size.
 * \param[out] pByteCount To receive the byte count.
 * \param[in] nFlags Bit-field flags to indicate special handling of previous or current frame.
 *            Refer to above definitions "FLAG_XXX"
 * \return SW263E_FRMDONE if the whole frame is encoded; SW263E_BUFFULL if not.
 * \sa
 * \note If SW263E_BUFFULL, the caller must call MApi_H263_ContinueOnePicture() to receive following bitstream.
 * \warning This is a blocking API.
 * \warning SW263E_BUFFULL does not imply *pByteCount equals to nOutBufSize.
 */
int MApi_H263_CompressOnePicture(unsigned char* pRawBuf, unsigned char* pOutBuf, unsigned int nOutBufSize, unsigned int* pByteCount, unsigned int nFlags);

/*!
 * \brief
 *  Re-get the status of the latest MApi_H263_CompressOnePicture() or MApi_H263_ContinueOnePicture().
 *
 * \param[out] ppOutBuf To receive the pointer of the bitstream buffer.
               This is exactly pOutBuf of previous MApi_H263_CompressOnePicture() or MApi_H263_ContinueOnePicture() calling.
 * \param[out] pByteCount To receive the byte count.
 * \param[out] FrameType To receive the encoded frame type: 'I' or 'P'
 * \return SW263E_FRMDONE if the whole frame is encoded; SW263E_BUFFULL if not.
 * \sa
 * \note This API is for some scenario that the caller won't handle MApi_H263_CompressOnePicture() or MApi_H263_ContinueOnePicture immediately.
 * \warning
 */
int MApi_H263_GetBits(unsigned char** ppOutBuf, unsigned int* pByteCount,char* FrameType);

/*!
* \brief
*  Continue encoding one input frame.
*  This must be the continuation of MApi_H263_CompressOnePicture() or MApi_H263_ContinueOnePicture() with return value SW263E_BUFFULL.
*
* \param[in,out] pOutBuf The caller-allocated bitstream buffer to receive bytes.
* \param[in] nOutBufSize The bitstream buffer size.
* \param[out] pByteCount To receive the byte count.
* \param[in] nFlags Bit-field flags to indicate special handling of previous or current frame.
*            Refer to above definitions "FLAG_XXX"
* \return SW263E_FRMDONE if the whole frame is encoded; SW263E_BUFFULL if not.
* \sa
* \note If SW263E_BUFFULL, the caller must call MApi_H263_ContinueOnePicture() again to receive following bitstream.
* \warning This is a blocking API.
* \warning SW263E_BUFFULL does not imply *pByteCount equals to nOutBufSize.
*/
int MApi_H263_ContinueOnePicture(unsigned char* pOutBuf, unsigned int nOutBufSize, unsigned int* pByteCount, unsigned int nFlags);

/*!
 * \brief
 *  Stop and get the final end-of-stream bytes.
 *
 * \param[in,out] pOutBuf The caller-allocated bitstream buffer to receive bytes.
 * \param[in] nOutBufSize The bitstream buffer size.
 * \param[out] pByteCount To receive the byte count.
 * \return SW263E_SUCCESS
 * \sa
 * \note When H.263 encoding, the returned byte count will be 0.
 * \warning
 */
int MApi_H263_StopEncode(unsigned char* pOutBuf, unsigned int nOutBufSize, unsigned int* pByteCount);

#endif
