/**
* @file    mmi_srv_videoplayer.h
* @brief
*
*
* @author
* @version $Id: mmi_srv_videoplayer.h
*/

#ifndef __MMI_SRV_VIDEOPLAYER_H__
#define __MMI_SRV_VIDEOPLAYER_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_videoplayersrv.h"

//Video Service Wrapper interface.
/*=============================================================*/
// Register Callback Operations (Sync.)
/*=============================================================*/
/**
SrvVideoPlayerSetErrorCb
@brief  Set a callback to be invoked when an error was happened.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetErrorCb(VideoPlayerSrvErrorCb pfnErrorCb, u32 nCusData);

/**
SrvVideoPlayerSetPlayStatusCb
@brief  Set a callback to be invoked when playback status was changed.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetPlayStatusCb(VideoPlayerSrvPlayStatusCb pfnPlayStatusCb, u32 nCusData);

/**
SrvVideoPlayerSetPlayProgressCb
@brief  Set a callback to be invoked when playback/download progress was updated.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetPlayProgressCb(VideoPlayerSrvPlayProgressCb pfnPlayProgressCb, u32 nCusData);

/**
SrvVideoPlayerSetBufferingStatusCb
@brief  Set a callback to be invoked when buffering status was updated.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetBufferingStatusCb(VideoPlayerSrvBufferingStatusCb pfnBufferingStatusCb, u32 nCusData);

/**
SrvVideoPlayerSetInterruptCb
@brief  Set a callback to be invoked when interrupt was happened.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetInterruptCb(VideoPlayerSrvInterruptCb pfnInterruptCb, u32 nCusData);

/**
SrvVideoPlayerSetSeekStatusCb
@brief  Set a callback to be invoked when seek status was updated.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetSeekStatusCb(VideoPlayerSrvSeekStatusCb pfnSeekStatusCb, u32 nCusData);

/**
SrvVideoPlayerSetWindowSizeCb
@brief  Set a callback to be invoked when the window size was changed.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetWindowSizeCb(VideoPlayerSrvWindowSizeCb pfnWindowChangeCb, u32 nCusData);

/**
SrvVideoPlayerSetDataFirstFrameCb
@brief  Set a callback to be invoked when the first frame was retrieved.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDataFirstFrameCb(VideoPlayerSrvFirstFrameCb pfnDataFirstFrameCb, u32 nCusData);

/**
SrvVideoPlayerSetDataInfoCb
@brief  Set a callback to be invoked when the video info was updated.

@param[in]      pfnErrorCb  Callback function pointer
@param[in]      nCusData    User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDataInfoCb(VideoPlayerSrvDataInfoCb pfnDataInfoCb, u32 nCusData);

#ifdef __MMI_STEREO_VIDEO__
/**
SrvVideoPlayerSetStereoTypeCb
@brief  Set a callback to be invoked when the stereo configuration was updated.

@param[in]      pfnSetStereoCb  Callback function pointer
@param[in]      nCusData        User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetStereoTypeCb(VideoPlayerSrvSetStereoConfigCmnCb pfnSetStereoCb, u32 nCusData);

/**
SrvVideoPlayerSetDepthCb
@brief  Set a callback to be invoked when the stereo configuration was updated.

@param[in]      pfnSetDepthCb  Callback function pointer
@param[in]      nCusData        User data

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDepthCb(VideoPlayerSrvSetStereoConfigCmnCb pfnSetDepthCb, u32 nCusData);
#endif
/*=============================================================*/
// Set Variable Operations (Sync.)
/*=============================================================*/
/**
SrvVideoPlayerSetDataByUrl
@brief  Set data source by URL.

@param[in]      pURL        Data source URL.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDataByUrl (MAE_WChar *pURL);

/**
SrvVideoPlayerSetDataByBuffer
@brief  Set data source by buffer.

@param[in]      pDataBuffer        Data buffer.
@param[in]      nBufferSize        Data buffer size.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDataByBuffer (void *pDataBuffer, u32 nBufferSize);

/**
SrvVideoPlayerSetDataFormat
@brief  Set the format of data source.

@param[in]      eMimeType        Data format.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDataFormat (MediaSrvMimeType_e eMimeType);

/**
SrvVideoPlayerSetExtInfoBuffer
@brief  Set the buffer for retrieving ext info(KMV).

@param[in]      pInfoBuffer        Buffer pointer.
@param[in]      nBufferSize        Buffer size.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetExtInfoBuffer (void *pInfoBuffer, u32 nBufferSize);

/**
SrvVideoPlayerSetDownloadInterface
@brief  Set the interface of download module for streaming playback.

@param[in]      pfnDownloadItf    Pointer to the interface of download module.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDownloadInterface(VideoPlayerSrvDownloadModuleCb pfnDownloadItf);

/**
SrvVideoPlayerSetSeekMode
@brief  Set the seek mode.

@param[in]      eSeekMode   Seek mode.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetSeekMode(VideoPlayerSrvSeekMode_e eSeekMode);

/**
SrvVideoPlayerSetSeekMode
@brief  Set maximum seek duration.

@param[in]      nSeekDuration   Seek duration.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetSeekDuration(u32 nSeekDuration);

/**
SrvVideoPlayerSetPosition
@brief  Set the playback or seek position.

@param[in]      nPosition   Playback/Seek position.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetPosition(u32 nPosition);

/**
SrvVideoPlayerSetWindowRegion
@brief  Set the window region.

@param[in]      tRegion             The location and size of playing screen

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetWindowRegion(Rect_t tRegion);

/**
SrvVideoPlayerSetWindowAngle
@brief  Set the window angle.

@param[in]      eWindowAngle        The angle of playing screen

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetWindowAngle(MediaSrvAngle_e eWindowAngle);

/**
SrvVideoPlayerSetWindowMode
@brief  Set the window mode.

@param[in]      eWindowAngle        The angle of playing screen

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetWindowMode(VideoPlayerSrvWindMode_e eWindowMode);

#ifdef __MMI_STEREO_VIDEO__
/**
SrvVideoPlayerSetStereoType
@brief  The interface is used to set stereo parameter.

@param[in]      eStereoType Stereo Type

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerSetStereoType(VideoPlayerImageStereoType_e eStereoType);

/**
SrvVideoPlayerSetDepth
@brief  The interface is used to set stereo parameter.

@param[in]      nDepth      Level of depth

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerSetDepth(u32 nDepth);

/**
SrvVideoPlayerUpdateStereoType
@brief  The interface is used to only set stereo parameter of video player service.

@param[in]      eStereoType Stereo Type

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerUpdateStereoType(VideoPlayerImageStereoType_e eStereoType);
#endif

/**
SrvVideoPlayerSetVolume
@brief  Set the volume of playback.

@param[in]      nVolume     The range of volume is from 0 to 8.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetVolume(u8 nVolume);

/**
SrvVideoPlayerSetTempVolume
@brief  The interface is used to set the temp volume of video player.
 */
MAE_Ret SrvVideoPlayerSetTempVolume(u8 nVolume);

/**
SrvVideoPlayerSetDolby

@brief	Set the Dolby mode of playback.

@param[in]	eDolbyMode		Indicate a Dolby mode.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerSetDolby(VideoPlayerSrvDolby_e eDolbyMode);

/**
SrvVideoPlayerSetPassword
@brief    The interface is used to set the password for encrypted videos.

@param[in] pPassword    the set password

@retval MAE_RET_SUCCESS    if set the password successfully
@retval MAE_RET_NOT_SUPPORTED    do not support passsword input
*/
MAE_Ret SrvVideoPlayerSetPassword(const char *pPassword);

/**
SrvVideoPlayerSetConnectionType
@brief    The interface is used to set the connection type in steaming mode.

@retval MAE_RET_SUCCESS    if set the connection type successfully
@retval MAE_RET_NOT_SUPPORTED    do not support the setting
*/
MAE_Ret SrvVideoPlayerSetConnectionType(VideoPlayerSrvConnectionType_e eConnectionType);

/**
SrvVideoPlayerSetStreamingMode
@brief    The interface is used to set the streaming mode.

@retval MAE_RET_SUCCESS    if set the streaming mode successfully
@retval MAE_RET_NOT_SUPPORTED    do not support the setting
*/
MAE_Ret SrvVideoPlayerSetStreamingMode(VideoPlayerSrvStreamingMode_e eStreamingMode);
/*=============================================================*/
// Get Variable Operations (Sync.)
/*=============================================================*/
/**
SrvVideoPlayerGetDolby
@brief	Get the Dolby mode of playback.

@param[out] 	pDolbyMode			Pointer to the Dolby mode variable.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerGetDolby(VideoPlayerSrvDolby_e *pDolbyMode);

/**
SrvVideoPlayerGetStatus
@brief	Get the playback status.

@param[out] 	pStatus			Pointer to the playback status variable.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
*/
MAE_Ret SrvVideoPlayerGetStatus (VideoPlayerSrvState_e *pStatus);

/**
* SrvVideoPlayerQueryA2DPSupport
* @brief        Users can query whether platform support a2dp setting.
*
* @param[in]    pUserA2dpSupported       TRUE:support, False:Not support
*
* @retval       MAE_RET_SUCCESS          If it succeeds to accept the query.
* @retval       MAE_RET_BAD_PARAM        If *pUserA2dpSupported is NULL pointer.
* @retavl       MAE_RET_OUT_OF_MEMORY    If there's no enough memory to do allocation for service instance.
* @retval       MAE_RET_NOT_SUPPORTED    If this function is not supported.
* @retval       MAE_RET_FAILED           If it fail to accept the query.
*/
MAE_Ret SrvVideoPlayerQueryA2DPSupport(boolean *pUserA2dpSupported);

/**
SrvVideoPlayerGetDataInfoSync
@brief  Retrieve the information of video file(Sync.).

@param[out] 	pDataInfo	Pointer to the video information.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
@retval MAE_RET_FAILED      if an error happen

***Essential setting***
1.1 SrvVideoPlayerSetDataByUrl
1.2 SrvVideoPlayerSetDataByBuffer + SrvVideoPlayerSetDataFormat
***Optional setting***
1. SrvVideoPlayerSetExtInfoBuffer

*/
MAE_Ret SrvVideoPlayerGetDataInfoSync (VideoPlayerSrvDataInfo_t *pDataInfo);
/*=============================================================*/
// Playback Operations (Async.)
/*=============================================================*/
/**
SrvVideoPlayerOpenSession
@brief  Open video playback session

@retval MAE_RET_SUCCESS     if successful.
 */
MAE_Ret SrvVideoPlayerOpenSession(void);

/**
SrvVideoPlayerCloseSession
@brief  Close video playback session

@retval MAE_RET_SUCCESS     if successful.
 */
MAE_Ret SrvVideoPlayerCloseSession(void);

/**
SrvVideoPlayerPlay
@brief  Start or resume video playback

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
@retval MAE_RET_FAILED      if an error happen

***Essential setting***
1. SrvVideoPlayerSetWindowRegion
2. SrvVideoPlayerSetWindowAngle
3. SrvVideoPlayerSetWindowMode
4.1 SrvVideoPlayerSetDataByUrl
4.2 SrvVideoPlayerSetDataByBuffer + SrvVideoPlayerSetDataFormat
***Optional setting***
1. VideoPlayerSrvSetPosition
2. VideoPlayerSrvSetLoopPlay
3. VideoPlayerSrvSetExtInfoBuffer
*/
MAE_Ret SrvVideoPlayerPlay (void);

/**
SrvVideoPlayerStop
@brief  Stop playing video file

@retval MAE_RET_SUCCESS     if successful.
        MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerStop(void);

/**
SrvVideoPlayerResume
@brief    resume the paused video file

@retval    MAE_RET_SUCCESS    if the result of executing the command is successful
           MAE_RET_BAD_PARAM    if the parameters are out of the boundary
           MAE_RET_OUT_OF_MEMORY    if the memory is not enough
*/
MAE_Ret SrvVideoPlayerResume(void);

/**
SrvVideoPlayerPause
@brief  Pause playing video file

@retval MAE_RET_SUCCESS     if successful.
        MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerPause(void);

/**
SrvVideoPlayerStartSeek
@brief  Seek the playing position

@retval MAE_RET_SUCCESS     if successful.
@retavl MAE_RET_BAD_PARAM   if any of the parameters is NULL.

***Essential setting***
1. SrvVideoPlayerSetPosition
***Optional setting***
1. SrvVideoPlayerSetSeekMode
2. SrvVideoPlayerSetSeekDuration
*/
MAE_Ret SrvVideoPlayerStartSeek(void);

/**
SrvVideoPlayerStopSeek
@brief  Stop seeking

@retval MAE_RET_SUCCESS     if successful.
@retavl MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerStopSeek(void);

/**
SrvVideoPlayerStartSetWindow
@brief  Set the location and rotating angle of playing screen.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.

***Essential setting***
1. SrvVideoPlayerSetWindowRegion
2. SrvVideoPlayerSetWindowAngle
3. SrvVideoPlayerSetWindowMode
 */
MAE_Ret SrvVideoPlayerStartSetWindow(void);

/**
SrvVideoPlayerStartGetDataFirstFrame
@brief  Retrieve the first frame from the video file.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.

***Essential setting***
1. SrvVideoPlayerSetWindowRegion
2. SrvVideoPlayerSetWindowAngle
3. SrvVideoPlayerSetWindowMode
4.1 SrvVideoPlayerSetDataByUrl
4.2 SrvVideoPlayerSetDataByBuffer + SrvVideoPlayerSetDataFormat
***Optional setting***
1. SrvVideoPlayerSetExtInfoBuffer
*/
MAE_Ret SrvVideoPlayerStartGetDataFirstFrame (void);

/**
SrvVideoPlayerStopGetDataFirstFrame
@brief  Stop retrieving the first frame from the video file.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
 */
MAE_Ret SrvVideoPlayerStopGetDataFirstFrame (void);

/**
SrvVideoPlayerStartGetDataInfo
@brief  Retrieve the information of video file.

@retval MAE_RET_SUCCESS     if successful.
@retval MAE_RET_BAD_PARAM   if any of the parameters is NULL.
@retval MAE_RET_FAILED      if an error happen

***Essential setting***
1.1 SrvVideoPlayerSetDataByUrl
1.2 SrvVideoPlayerSetDataByBuffer + SrvVideoPlayerSetDataFormat
***Optional setting***
1. SrvVideoPlayerSetExtInfoBuffer

*/
MAE_Ret SrvVideoPlayerStartGetDataInfo (void);

/**
SrvVideoPlayerInitAudio
@brief    decide if decode audio part of video

@param[in] bIsInitAudio    indicate if decode audio part

@retval MAE_RET_SUCCESS    if execute successfully.
@retval MAE_RET_ILLEGAL_OPERATION    if the state of videoplayer service is wrong
 */
MAE_Ret SrvVideoPlayerInitAudio(boolean bIsInitAudio);
/*-----------------------------------------------------*/
#endif //__MMI_SRV_VIDEOPLAYER_H__
