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
* @file    mdl_audio_pub_api.h
* @version
* @brief   Abscontainer middleware audio header file
*
*/

#ifndef __MDL_AUD_PUB_API_H__
#define __MDL_AUD_PUB_API_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_audio_pub_api.h"
#include "mdl_aud_forward.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * @brief Call back function, Application needs to provide the function entry
 *
 * @param pData         : PCM data
 * @param dataLen       : data length
 *
 * @return None
 */
typedef void (*MdlAudPcmRecordCb)(u16 *pnData, u32 nDataLen, u32 nUserData);

/**
 *  @brief Call back function, MMI need to provide the function entity
 *
 * @param ptAudGainInfo    : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*MdlAudGainInfoCbFn_t)(MdlAudGainInfo_t *ptAudGainInfo);

/**
 *  @brief Call back function, MMI need to provide the function entity
 *
 * @param bA2dpEnable    : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*MdlAudA2dpStatusCbFn_t)(bool *pbA2dpEnable);


/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
MdlAudRet_e MdlAudSetMuteReq(bool bMute);

/**
 * @brief  This function is used to set the audio path of related audio path
 *
 * @param  chanId                       : Audio channel to select
 * @param  audPath                      : Audio output/input path to select
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetPathReq(MdlAudChannel_e eChanId, MdlAudPath_e eAudPath);

/**
 * @brief  This function is used to set the volume and range of the output devices
 *
 * @param  chanId                       : Audio channel select to mute
 * @param  range                        : Maximum range of volume
 * @param  volume                       : Input volume level, increasing volume control enabled when the volume level is out of setting range
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetVolReq(MdlAudChannel_e eChanId, u8 nRange, u8 nVolume);

/**
 * @brief  This function is used to set the volume balance of the output devices
 *
 * @param  chanId                       : Audio channel select to mute
 * @param  range                        : Maximum range of volume (5 means -5 ~ +5)
 * @param  level                        : Balance level. Negative value means the volume of right channel is decreased. Positive value means the volume of left channel is decreased.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_AUD_PATH_ERROR           : Incorret request of audio path with related audio function
 * @return ESL_AUD_TIMEOUT              : Request command to MMP is no response
 */
MdlAudRet_e MdlAudSetBalanceReq(MdlAudChannel_e eChanId, s8 nRange, s8 nLevel);

/**
 * @brief This function is used to set music mode
 *
 * @param  mode                         : Music mode
 * @param  ptAudCb                       : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetMusicModeReq(MdlAudMusicMode_e eMode, MdlAudCb_t *ptAudCb);

/**
 * @brief  This function is used to enable local tone
 *
 * @param  enable                       : Enable local tone or not
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_AUD_PATH_ERROR           : Incorret request of audio path with related audio function
 * @return ESL_AUD_TIMEOUT              : Request command to MMP is no response
 */
MdlAudRet_e MdlAudEnableLocalToneReq(bool bEnable);

/**
 * @brief  This function is used to enable/disable speech
 *
 * @param  enable                       : TRUE => enable   FALSE => disable
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 * @return ESL_AUD_PATH_ERROR           : Incorret request of audio path with related audio function
 * @return ESL_AUD_TIMEOUT              : Request command to MMP is no response
 */
MdlAudRet_e MdlAudEnableSpeechReq(bool bEnable);

/**
 * @brief  This function is used to set dtmftone
 *
 * @param  toneID                       : Tony ID indicated which sound effct should be played
 * @param  ptAudCb                      : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetDTMFReq(MdlAudDTMF_e eToneID, MdlAudCb_t *ptAudCb);

/**
 * @brief  This function is used to play a dtmftone
 *
 * @param  toneID                       : Tony ID indicated which sound effct should be played
 * @param  ptAudCb                      : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudPlayDTMFReq(MdlAudDTMF_e eToneID, MdlAudCb_t *ptAudCb);

/**
 * @brief  This function is used to play a dtmftone with volume setting
 *
 * @param  toneID                       : Tony ID indicated which sound effct should be played
 * @param  volRange                     : Volume range
 * @param  volLevel                     : Volume level
 * @param  ptAudCb                      : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudPlayDTMFReqEx(MdlAudDTMF_e eToneId, u8 nVolRange, u8 nVolLevel, MdlAudCb_t *ptAudCb);

/**
 * @brief  This function is used to stop a dtmftone
 *
 * @param  ptAudCb                       : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudStopDTMFReq(MdlAudCb_t *ptAudCb);

/**
 * @brief EMA audio play stream (support only PCM WAVE)
 *
 * @param  streamParam                  : stream buffer and length
 * @param  ptAudCb                      : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudPlayStreamReq(MdlAudStreamParam_t tStreamParam, MdlAudCb_t *ptAudCb);

/**
 * @brief This function is used to set audio play command (Pause/Resume/Stop)
 *
 * @param  playCmd                      : Audio play command including stop, pause, and resume
 * @param  ptAudCb                      : Audio call back function point (It will return date using this call back function)
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudPlayCmdReq(MdlAudPlayCmd_e ePlayCmd, MdlAudCb_t *ptAudCb);

/**
 * @brief Register notification for audio palying and recording
 *
 * @param notifyType                    : Notification selected type to register
 * @param notifyCb                      : Notification call back to info MMI when Multimedia task receivd notification.
 * @param pAudCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudRegNotifyReq(MdlAudNotifyType_e eNotifyType, MdlAudNotifyCb_t tNotifyCb, MdlAudCb_t *ptAudCb);

/**
 * @brief This function is used to register PCM record callback
 *
 * @param  pfnCb                        : Callback function
 * @param  userData                   :  user data for callback function
 * @param  ptAudCb                       : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudRegPcmRecordCbReq(MdlAudPcmRecordCb *ptfnCb, u32 nUserData, MdlAudCb_t *ptAudCb);

/**
 * @brief This function is start PCM record
 *
 * @param  ptAudCb                       : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudStartPcmRecordReq(MdlAudCb_t *ptAudCb);

/**
 * @brief This function is used to stop PCM record
 *
 * @param  ptAudCb                      : Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudStopPcmRecordReq(MdlAudCb_t *ptAudCb);

/**
 * @brief Audio open
 *
 * @param AudioType                     : Audio type
 * @param channel                       : Audio channel
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudOpenReq(MdlAudChannel_e eChannel, MdlAudType_e eAudioType);

/**
 * @brief Audio close
 *
 * @param AudioType                     : Audio type
 * @param channel                       : Audio channel
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudCloseReq(MdlAudChannel_e eChannel, MdlAudType_e eAudioType);

/**
 * @brief Audio config
 *
 * @param channel                       : Audio channel
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudConfigReq(MdlAudChannel_e eChannel, MdlAudioManagerParam_t tParam);

/**
 * @brief Audio set in gain
 *
 * @param channel                       : Audio channel
 * @param inputGain                     : Input gain
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetInGainReq(MdlAudChannel_e eChannel, MdlAudGain_t tInputGain);

/**
 * @brief Audio set input path
 *
 * @param channel                       : Audio channel
 * @param input                         : Input path
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetInputReq(MdlAudChannel_e eChannel, MdlAudInput_e eInput);

/**
 * @brief Audio get output path
 *
 * @param channel                       : Audio channel
 * @param output                        : [out] output path
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetOutputReq(MdlAudChannel_e eChannel, MdlAudOutput_e *peOutput);

/**
 * @brief Audio set output path
 *
 * @param channel                       : Audio channel
 * @param output                        : Output path
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetOutputReq(MdlAudChannel_e eChannel, MdlAudOutput_e eOutput);

/**
 * @brief Audio get output gain
 *
 * @param channel                       : Audio channel
 * @param audioType                     : Audio type
 * @param pOutputGain                   : [out] output gain
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetOutputGainReq(MdlAudChannel_e eChannel, MdlAudType_e eAudioType, MdlAudGain_t *ptOutputGain);

/**
 * @brief Audio set frequency
 *
 * @param channel                       : Audio channel
 * @param frequency                     : Frequency
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetFrequencyReq(MdlAudChannel_e eChannel, MdlAudSamplingRate_e eSamplingRate);

/**
 * @brief Get audio info
 *
 * @param pAudConfig                    : [out] audio configuration
 * @param pAudState                     : [out] music state
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetInfoReq(MdlAudConfig_t *ptAudConfig, MdlAudType_e *peAudState);

/**
 * @brief Set distorted voice
 *
 * @param eMode                         : [out] distorted voice mode
 * @param pAudState                     : [out] Call back struct pointer, include sender task ID, userValue and call back function.
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetDistortedVoiceReq(MdlAudDistortedVoice_e eMode, MdlAudCb_t *ptAudCb);

/**
 * @brief Switch on/off speaker amplifier
 *
 * @param channel                       : Channel
 * @param bOn                           : On / off
 * @param Delay                         : Delay time (ms)
 * @param ExtInfo                       : Extension debug info
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSwitchSpeakerAmplifierReq(MdlAudChannel_e eChannel, bool bOn, u32 nDelay, u32 nExtInfo);

/**
 * @brief Audio speaker enable
 *
 * @param channel                       : Audio channel
 * @param enable                        : Frequency
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSpeakerEnableReq(MdlAudChannel_e eChannel, bool bEnable);

/**
 * @brief Audio gain fade out
 *
 * @param channel                       : Audio channel
 * @param gain                          : Audio gain
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGainFadeOutReq(MdlAudChannel_e eChannel, MdlAudGain_t tGain);

/**
 * @brief Audio gain fade in
 *
 * @param channel                       : Audio channel
 * @param gain                          : Audio gain
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGainFadeInReq(MdlAudChannel_e eChannel, MdlAudGain_t tGain);

/**
 * @brief Get channel path
 *
 * @param channel                       : Audio channel
 * @param audPath                       : Audio path
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetPathReq(MdlAudChannel_e eChannel, MdlAudPath_e *pePath);

/**
 * @brief Set recording sampling rate
 *
 * @param channel                       : Audio channel
 * @param audPath                       : Audio path
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSetRecFrequencyReq(MdlAudSamplingRate_e eSamplingRate);

/**
 * @brief Get speaker capability
 *
 * @param peSpeakerType                 : [out] Speaker type
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetSpeakerTypeReq(MdlAudSpeakerType_e *peSpeakerType);

#if defined(__SPEECH_CTA_CHEATING_MODE__)
/**
 * @brief Set Sidetone mute for CTA CT mode
 *
 * @param peSpeakerType                 : [out] Speaker type
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSpeechSetCTASTMuteReq(void);

/**
 * @brief Restore Sidetone mute for CTA CT mode
 *
 * @param peSpeakerType                 : [out] Speaker type
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudSpeechSetCTASTRestoreReq(void);
#endif /* __SPEECH_CTA_CHEATING_MODE__ */

/**
 * @brief Check 3 segment headset
 *
 * @param None
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudCheck3SegmentHeadsetReq(void);

/**
 * @brief Em Audio Test
 *
 * @param bOn                           : On / off
 * @param eChannel                    : Channel
 * @param eInput                        : Input
 * @param eOutput                      : Output
 * @param tInputGain                  : Input Gain
 * @param tInputGain                  : Output Gain
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudEmAudioTestReq(bool bOn, MdlAudChannel_e eChannel, MdlAudInput_e eInput, MdlAudOutput_e eOutput, MdlAudGain_t tInputGain, MdlAudGain_t tOutputGain);

/**
 * @brief Is Output Ready (Timing Issue)
 *
 * @param *bReady                       : Query for ready, TRUE/FALSE
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudIsOutputReadyReq(bool *bReady);

/**
 * @brief Register notification for audio gain info
 *
 * @param tGainInfoCb                   : Notification call back to info MMI when Multimedia task receivd notification.
 * @param ptAudCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudRegGainInfoCbReq(MdlAudGainInfoCbFn_t tGainInfoCb, MdlAudCb_t *ptAudCb);

/**
 * @brief Deregister notification for audio gain info
 *
 * @param tGainInfoCb                   : Notification call back to info MMI when Multimedia task receivd notification.
 * @param ptAudCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudDeregGainInfoCbReq(MdlAudGainInfoCbFn_t tGainInfoCb, MdlAudCb_t *ptAudCb);

/**
 * @brief Register notification for A2DP status
 *
 * @param tA2dpStatusCb                 : Notification call back to info MMI when Multimedia task receivd notification.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudRegA2dpStatusCbReq(MdlAudA2dpStatusCbFn_t tA2dpStatusCb);

/**
 * @brief Deregister notification for A2DP status
 *
 * @param tGainInfoCb                   : Notification call back to info MMI when Multimedia task receivd notification.
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudDeregA2dpStatusCbReq(MdlAudA2dpStatusCbFn_t tA2dpStatusCb);

/**
 * @brief Get Music Mix Capability
 *
 * @param *bMix                       : Query for Mix Capability, TRUE/FALSE. (B5 do not support call preview music)
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetAudioMixCapabilityReq(bool *bMix);

/**
 * @brief Get External amp gain offset
 *
 * @param *pbExtAmp                     : Query for external amp, TRUE/FALSE.
 * @param *pnGainOffset                 : Query for gain offset
 *
 * @return ISL_VOC_OK                   : Function request success
 * @return ISL_VOC_FAIL                 : Function request fail
 * @return ISL_VOC_PARAM_ERROR          : Incorrect parameter setting
 * @return ISL_VOC_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_VOC_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_VOC_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudGetExtAmpGainOffsetReq(bool *pbExtAmp, s8 *pnGainOffset);

/**
 * @brief  This function is used to enable streaming record
 *
 * @param  bEnable                      : Enable or not
 *
 * @return ESL_AUD_OK                   : function request success
 * @return ESL_AUD_FAIL                 : function request fail
 * @return ESL_AUD_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AUD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @return ESL_AUD_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AUD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlAudRet_e MdlAudEnableStreamRecReq(bool bEnable);

#endif //__MDL_AUD_PUB_API_H__

