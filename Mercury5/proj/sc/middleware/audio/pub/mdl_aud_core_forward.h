#ifndef __MDL_AUD_CORE_FORWARD_H__
#define __MDL_AUD_CORE_FORWARD_H__

#include "vm_types.ht"
// mdl_aud_core_api.h
typedef s8 AudioGain_t;
typedef struct MdlAudAudioGainSetting_t_ MdlAudAudioGainSetting_t;
opaque_enum(MdlAudPcmStateMachine_e_);
typedef enum MdlAudPcmStateMachine_e_ MdlAudPcmStateMachine_e;
opaque_enum(MdlAudHandlerStateMachine_e_);
typedef enum MdlAudHandlerStateMachine_e_ MdlAudHandlerStateMachine_e;
typedef struct MdlAudPcmHandle_t_ MdlAudPcmHandle_t;
opaque_enum(MdlAudVoiceType_e_);
typedef enum MdlAudVoiceType_e_ MdlAudVoiceType_e;
opaque_enum(MdlAudProfile_e_);
typedef enum MdlAudProfile_e_ MdlAudProfile_e;
typedef struct MdlAudPcmDataNode_tag MdlAudPcmDataNode_t;
opaque_enum(MdlAudHeadsetType_e_);
typedef enum MdlAudHeadsetType_e_ MdlAudHeadsetType_e;

#endif // __MDL_AUD_CORE_FORWARD_H__
