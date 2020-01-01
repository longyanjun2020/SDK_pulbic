#ifndef __MDL_AUD_PUB_FORWARD_H__
#define __MDL_AUD_PUB_FORWARD_H__

#include "vm_types.ht"

// mdl_aud_pub_types.h
typedef s8 MdlAudGain_t;
opaque_enum(MdlAudPath_e_);
typedef enum MdlAudPath_e_ MdlAudPath_e;
opaque_enum(MdlAudChannel_e_);
typedef enum MdlAudChannel_e_ MdlAudChannel_e;
opaque_enum(MdlAudDTMF_e_);
typedef enum MdlAudDTMF_e_ MdlAudDTMF_e;
// MdlAudDtmfParam_t moves to mdl_aud_int_types.h
opaque_enum(MdlAudPlayCmd_e_);
typedef enum MdlAudPlayCmd_e_ MdlAudPlayCmd_e;
opaque_enum(MdlAudFormat_e_);
typedef enum MdlAudFormat_e_ MdlAudFormat_e;
opaque_enum(MdlAudSamplingRate_e_);
typedef enum MdlAudSamplingRate_e_ MdlAudSamplingRate_e;
typedef struct MdlAudStreamParam_t_ MdlAudStreamParam_t;
opaque_enum(MdlAudMusicMode_e_);
typedef enum MdlAudMusicMode_e_ MdlAudMusicMode_e;
// MdlAudSetMusicModeParam_t moves to mdl_aud_int_types.h
typedef struct MdlAudInfo_t_ MdlAudInfo_t;
typedef struct MdlAudCb_t_ MdlAudCb_t;
opaque_enum(MdlAudType_e_);
typedef enum MdlAudType_e_ MdlAudType_e;
opaque_enum(MdlAudInput_e_);
typedef enum MdlAudInput_e_ MdlAudInput_e;
opaque_enum(MdlAudOutput_e_);
typedef enum MdlAudOutput_e_ MdlAudOutput_e;
opaque_enum(MdlAudDistortedVoice_e_);
typedef enum MdlAudDistortedVoice_e_ MdlAudDistortedVoice_e;

opaque_enum(MdlAudioTchOutput_e_);
typedef enum MdlAudioTchOutput_e_ MdlAudioTchOutput_e;
opaque_enum(MdlAudioTchInput_e_);
typedef enum MdlAudioTchInput_e_ MdlAudioTchInput_e;
opaque_enum(MdlAudioTchIF_e_);
typedef enum MdlAudioTchIF_e_ MdlAudioTchIF_e;
opaque_enum(MdlAudioTchCfgReq_e_);
typedef enum MdlAudioTchCfgReq_e_ MdlAudioTchCfgReq_e;
opaque_enum(MdlAudioTchRenderType_e_);
typedef enum MdlAudioTchRenderType_e_ MdlAudioTchRenderType_e;
typedef struct MdlAudioManagerParam_t_ MdlAudioManagerParam_t;
typedef struct MdlAudTchConfig_t_ MdlAudTchConfig_t;

// MdlAudSwitchSpeakerAmp_t moves to mdl_aud_int_types.h
// MdlAudOpen_t moves to mdl_aud_int_types.h
// MdlAudClose_t moves to mdl_aud_int_types.h
// MdlAudSetInGain_t moves to mdl_aud_int_types.h
// MdlAudSetInGain_t moves to mdl_aud_int_types.h
// MdlAudGetOutput_t moves to mdl_aud_int_types.h
// MdlAudSetOutput_t moves to mdl_aud_int_types.h
// MdlAudGetOutputGain_t moves to mdl_aud_int_types.h
// MdlAudSetFrequency_t moves to mdl_aud_int_types.h
// MdlAudSetRecFrequency_t moves to mdl_aud_int_types.h
// MdlAudSwitchTchStatus_t moves to mdl_aud_int_types.h
opaque_enum(MdlAudNotifyType_e_);
typedef enum MdlAudNotifyType_e_ MdlAudNotifyType_e;
opaque_enum(MdlAudNotifyErr_e_);
typedef enum MdlAudNotifyErr_e_ MdlAudNotifyErr_e;
typedef struct MdlAudNotifyInfo_t_ MdlAudNotifyInfo_t;
// MdlAudRegNotify_t moves to mdl_aud_int_types.h
typedef struct MdlAudNotifyCb_t_ MdlAudNotifyCb_t;
typedef struct MdlAudConfig_t_ MdlAudConfig_t;
// MdlAudSetMute_t moves to mdl_aud_int_types.h
// MdlAudSetPath_t moves to mdl_aud_int_types.h
// MdlAudSetVol_t moves to mdl_aud_int_types.h
// MdlAudSetBalance_t moves to mdl_aud_int_types.h
// MdlAudEnableLocalTone_t moves to mdl_aud_int_types.h
// MdlAudEnableSpeech_t moves to mdl_aud_int_types.h
// MdlAudRegPcmRecordCb_t moves to mdl_aud_int_types.h
// MdlAudGetInfo_t moves to mdl_aud_int_types.h
// MdlAudSpeakerEnable_t moves to mdl_aud_int_types.h
// MdlAudGainFadeOut_t moves to mdl_aud_int_types.h
// MdlAudGainFadeIn_t moves to mdl_aud_int_types.h
// MdlAudGetPath_t moves to mdl_aud_int_types.h
opaque_enum(MdlAudSpeakerType_e_);
typedef enum MdlAudSpeakerType_e_ MdlAudSpeakerType_e;

typedef struct MdlAudGainInfo_t_ MdlAudGainInfo_t;

#endif // __MDL_AUD_PUB_FORWARD_H__
