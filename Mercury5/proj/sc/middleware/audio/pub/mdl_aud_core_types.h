#ifndef __MDL_AUD_CORE_TYPES_H__
#define __MDL_AUD_CORE_TYPES_H__

#include "mdl_aud_forward.h"
// mdl_aud_core_api.h
struct MdlAudAudioGainSetting_t_
{
    bool         bFixGain;
    AudioGain_t  tDefaultGain;
    AudioGain_t  tMinGain;
    AudioGain_t  tMaxGain;
};

opaque_enum(MdlAudPcmStateMachine_e_)
{
  MDL_AUD_PCM_STATE_PLAY_OPEN = 0,
  MDL_AUD_PCM_STATE_PLAY_RUN,
  MDL_AUD_PCM_STATE_PLAY_IDLE,
  MDL_AUD_PCM_STATE_PLAY_PAUSE
};


opaque_enum(MdlAudHandlerStateMachine_e_)
{
  MDL_AUD_STATE_IDLE,
  MDL_AUD_STATE_RUN,
  MDL_AUD_STATE_CNF,
  MDL_AUD_STATE_TIMEOUT,
  MDL_AUD_PCM_STATE_RUN,
  MDL_AUD_DTMF_STATE_RUN,
  MDL_AUD_AUD_STATE_RUN,
};


struct MdlAudPcmDataNode_tag
{
    u8                           *pData;       /* all data */
    u8                           *pNextData;   /* next data which is not added into FIFO */
    bool                          bLast;       /* Last data ? */
    u32                           nSampleSize; /* Sample size */
    u32                           nSample;     /* sample count */
    u32                           nSampleLeft; /* sample count which is not added into FIFO */
    u32                           nBlock;      /* block count */
    u32                           nBlockLeft;  /* remain block */
    MdlAudCb_t                   *pAudCb;      /* callback */
    struct MdlAudPcmDataNode_tag *next;
};


struct MdlAudPcmHandle_t_
{
    s32  nI2sSessionId;
    u32 *pnI2sBuffer;   /* data start address */
    u32  nI2sSamples;
    u32  nI2sNbDataPerBlock;
    u16  nI2sBitsPerSample;
    u16  nI2sNbChannels;
    MdlAudPcmDataNode_t *ptI2sDataListHead;
    MdlAudPcmDataNode_t *ptI2sDataListRear;
    MdlAudPcmDataNode_t *ptI2sDataUsedListHead;
    MdlAudPcmDataNode_t *ptI2sDataUsedListRear;
} ;


opaque_enum(MdlAudVoiceType_e_)
{
    MDL_AUD_VOICE_CALL = 0,
    MDL_AUD_VOICE_TONE,
    MDL_AUD_VOICE_PCM,
    MDL_AUD_VOICE_MAX_NUM
};


opaque_enum(MdlAudProfile_e_)
{
    MDL_AUD_PROFILE_HANDSFREE = 0,   //Loud speaker
    MDL_AUD_PROFILE_HANDSET,
    MDL_AUD_PROFILE_HEADSET,             //Earpiece
    MDL_AUD_PROFILE_BT,

    MDL_AUD_PROFILE_MAX
};


/**
 *  @brief The enumeration defines the headset type.
 */
opaque_enum(MdlAudHeadsetType_e_)
{
    MDL_AUD_THREE_SEGMENT_HEADSET,       /**< Three segment headset */
    MDL_AUD_FOUR_SEGMENT_HEADSET,        /**< Four segment headset */
    MDL_AUD_UNKNOWN_SEGMENT_HEADSET      /**< Unknown segment headset */
};

// end mdl_aud_core_api.h
#endif // __MDL_AUD_CORE_TYPES_H__

