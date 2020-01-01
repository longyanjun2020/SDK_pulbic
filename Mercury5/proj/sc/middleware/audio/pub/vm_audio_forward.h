#ifndef __VM_AUDIO_FORWARD_H__
#define __VM_AUDIO_FORWARD_H__

#include "vm_types.ht"
// vm_audio_api.h
opaque_enum(vm_AudioChannel_e_);
typedef enum vm_AudioChannel_e_ vm_AudioChannel_e;
opaque_enum(vm_AudioInput_e_);
typedef enum vm_AudioInput_e_ vm_AudioInput_e;
opaque_enum(vm_AudioOutput_e_);
typedef enum vm_AudioOutput_e_ vm_AudioOutput_e;
opaque_enum(vm_AudioFrequency_e_);
typedef enum vm_AudioFrequency_e_ vm_AudioFrequency_e;
opaque_enum(vm_AudioIF_e_);
typedef enum vm_AudioIF_e_ vm_AudioIF_e;
opaque_enum(vm_AudioCfgReq_e_);
typedef enum vm_AudioCfgReq_e_ vm_AudioCfgReq_e;
opaque_enum(vm_AudioStereoMode_e_);
typedef enum vm_AudioStereoMode_e_ vm_AudioStereoMode_e;
typedef s8 vm_AudioGain_t;
typedef struct vm_AudioManagerParam_t_ vm_AudioManagerParam_t;
opaque_enum(vm_AudioMgrErrorCode_e_);
typedef enum vm_AudioMgrErrorCode_e_ vm_AudioMgrErrorCode_e;
opaque_enum(vm_AudioManagerChannelState_e_);
typedef enum vm_AudioManagerChannelState_e_ vm_AudioManagerChannelState_e;
opaque_enum(vm_AudioManagerMsgType_e_);
typedef enum vm_AudioManagerMsgType_e_ vm_AudioManagerMsgType_e;
typedef struct vm_AudioDtmfParam_t_ vm_AudioDtmfParam_t;
typedef struct vm_AudioSwitchOpAmp_t_ vm_AudioSwitchOpAmp_t;
typedef struct vm_AudioHwlCB_t_ vm_AudioHwlCB_t;
typedef struct vm_AudioManagerPCMParam_t_ vm_AudioManagerPCMParam_t;
opaque_enum(vm_AudioManagerPCMMsgType_e_);
typedef enum vm_AudioManagerPCMMsgType_e_ vm_AudioManagerPCMMsgType_e;
typedef struct vm_AudioManagerPCMMsg_t_ vm_AudioManagerPCMMsg_t;
typedef struct vm_AudioAECStatus_t_ vm_AudioAECStatus_t;

#endif // __VM_AUDIO_FORWARD_H__
