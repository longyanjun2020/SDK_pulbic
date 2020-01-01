/**
* @file    mmi_srv_tts.h
* @brief   
*          
*/

#ifndef __MMI_SRV_TTS_H__
#define __MMI_SRV_TTS_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_ttssrv.h"

/** SrvTtsOpenSession
@brief  The interface is used to open a session for tts.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_FAILED                   If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
*/
MAE_Ret SrvTtsOpenSession(void);

/** SrvTtsCloseSession
@brief  The interface is used to close the session for tts.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_FAILED                   If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
*/
MAE_Ret SrvTtsCloseSession(void);

/** SrvTtsGetTtsProfile
@brief  The interface is used to get tts profile information.

@param[out]      psProfile              Profile information.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_FAILED                   If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsGetTtsProfile(TTSSetting_t *psProfile);

/** SrvTtsSetTtsProfile
@brief  The interface is used to set tts profile information.

@param[in]      tProfile                Profile information.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_FAILED                   If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsSetTtsProfile(TTSSetting_t tProfile);

/** SrvTtsCreateTextHandle
@brief  The interface is used to create a new handle.

@param[in]      pUcs2                   An unicode string should be played.
@param[in]      uLen                    The length of the unicode string.
@param[in]      eVolume                 Volume information.
@param[in]      TTSStatusUpdateCB       Indication callback function when status is changed.
@param[out]     TTSHdl_t                The handle for the following command.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_FAILED                If fail.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsCreateTextHandle(u16* pUcs2, u16 uLen, TTSSRV_VOLUMESETTING_e eVolume, TTSStatusUpdateCB pfnStatusUpdateCb, TTSHdl_t *phOutTts);

/** SrvTtsSetHandleAttr
@brief  The interface is used to set attributes for some handle.

@param[in]      hTts                    The controlling handle.
@param[in]      tAttrs                  The attribute structure.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NO_FILE                  If tts resource file doesn't exist!
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsSetHandleAttr(TTSHdl_t hTts, TTSSrvAttr_t tAttrs);

/** SrvTtsSetCurVolume
@brief  The interface is used to set current handle's volume as eVolume.

@param[in]      hTts                    The controlling handle.
@param[in]      eVolume                 The volume you want to set.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsSetCurVolume(TTSHdl_t hTts, TTSSRV_VOLUMESETTING_e eVolume);

/** SrvTtsPlayText
@brief  The interface is used to start play for some handle.

@param[in]      hTts                    The controlling handle.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsPlayText(TTSHdl_t hTts);

/** SrvTtsResumePlayText
@brief  The interface is used to resume play for some handle.

@param[in]      hTts                    The controlling handle.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsResumePlayText(TTSHdl_t hTts);

/** SrvTtsStop
@brief  The interface is used to stop play for some handle.

@param[in]      hTts                    The controlling handle.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsStop(TTSHdl_t hTts);

/** SrvTtsDestroyTextHandle
@brief  The interface is used to destroy a handle.

@param[in]      hTts                    The controlling handle.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsDestroyTextHandle(TTSHdl_t hTts);

/** SrvTtsPlayTextNoResume
@brief  The interface is used to do a play without handle. So applications could not control the life cycle of this play after firing this command.

@param[in]      pUcs2                   An unicode string should be played.
@param[in]      uLen                    The length of the unicode string.
@param[in]      eVolume                 Volume information.
@param[in]      TTSStatusUpdateCB       Indication callback function when status is changed.
 
@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_SUPPORTED          Not support TTS functions. 
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error. 
*/
MAE_Ret SrvTtsPlayTextNoResume(u16 *pUcs2, u16 uLen, TTSSRV_VOLUMESETTING_e eVolume, TTSStatusUpdateCB pfnStatusUpdateCb);


/** SrvTtsLock
@brief  The interface is used to lock tts service.
        Lock tts service will do the following steps:

        1. Abort all tts requests
        2. Unint tts resource
        3. Lock tts

        When tts service is locked, it rejects any request.

@retval  MAE_RET_SUCCESS             If successful.
@retval  MAE_RET_NOT_SUPPORTED       Not support TTS functions. 
*/
MAE_Ret SrvTtsLockAsync(TTSLockCB pfnLockCb);

/** SrvTtsUnLock
@brief  The interface is used to unlock tts service.

@retval  MAE_RET_SUCCESS             If successful.
@retval  MAE_RET_NOT_SUPPORTED       Not support TTS functions. 
*/
MAE_Ret SrvTtsUnLockAsync(TTSLockCB pfnUnLockCb);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_TTS_H__
