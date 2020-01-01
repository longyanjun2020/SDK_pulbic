/**
 * @file    mmi_fmradiosrv_def.h
 * @brief   Define FM Radio related enum and structure.
 * @version $Id:
 */

#ifndef __MMI_FMRADIOSRV_DEF_H__
#define __MMI_FMRADIOSRV_DEF_H__

#define     MMI_FMRADIOSRV_FREQ_MAX         10800
#define     MMI_FMRADIOSRV_FREQ_MIN         8750

typedef enum
{
    FMRADIOSRV_STATUS__IDLE,
    FMRADIOSRV_STATUS__PLAY,
    FMRADIOSRV_STATUS__RECORD,
    FMRADIOSRV_STATUS__SUSPEND,
    FMRADIOSRV_STATUS__INVALID
} FmradioSrvStatus_e;


typedef enum FmradioSrvSearchChannelDirection_e_
{
    FMRADIOSRV_SEARCH_CHAN_DIRECTION__DOWN
   ,FMRADIOSRV_SEARCH_CHAN_DIRECTION__UP
} FmradioSrvSearchChannelDirection_e;

typedef enum FmradioSrvVolumeLevel_e_
{
    FMRADIOSRV_VOLUME_LEVEL__MIN
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL0 = FMRADIOSRV_VOLUME_LEVEL__MIN
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL1
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL2
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL3
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL4
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL5
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL6
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL7
   ,FMRADIOSRV_VOLUME_LEVEL__LEVEL8
   ,FMRADIOSRV_VOLUME_LEVEL__MAX = FMRADIOSRV_VOLUME_LEVEL__LEVEL8
   ,FMRADIOSRV_VOLUME_LEVEL__INVALID
} FmradioSrvVolumeLevel_e;

typedef enum FmradioSrvPrefAudPath_e_
{
    FMRADIOSRV_PREF_PATH__HANDSET
   ,FMRADIOSRV_PREF_PATH__HEADSET
   ,FMRADIOSRV_PREF_PATH__SPEAKER
   ,FMRADIOSRV_PREF_PATH__BT_HEADSET
   ,FMRADIOSRV_PREF_PATH__RIGHT_SPEAKER
   ,FMRADIOSRV_PREF_PATH__LEFT_SPEAKER,
} FmradioSrvPrefAudPath_e;

/**
 *  @brief The enumeration defines the area of FM radio
 */
typedef enum FmradioDeEmphasis_e_
{
    FMRADIOSRV_DEEMPHASIS_50US = 0
   ,FMRADIOSRV_DEEMPHASIS_75US
   ,FMRADIOSRV_DEEMPHASIS_INVALID
} FmradioDeEmphasis_e;

typedef enum FmradioStepSpace_e_
{
    FMRADIOSRV_STEP_50KHZ = 0
   ,FMRADIOSRV_STEP_100KHZ
   ,FMRADIOSRV_STEP_200KHZ
   ,FMRADIOSRV_STEP_30KHZ     /* M3 not support yet */
   ,FMRADIOSRV_STEP_300KHZ    /* M3 not support yet */
   ,FMRADIOSRV_STEP_INVALID
} FmradioStepSpace_e;

typedef enum FmradioBpfir_e_
{
    FMRADIOSRV_BPFIR_100KHZ = 0
   ,FMRADIOSRV_BPFIR_120KHZ
   ,FMRADIOSRV_BPFIR_150KHZ
   ,FMRADIOSRV_BPFIR_200KHZ
   ,FMRADIOSRV_BPFIR_INVALID
} FmradioBpfir_e;

typedef enum FmradioBeginRange_e_
{
    FMRADIOSRV_BEGIN_66MHZ = 0  /* M3 not support yet */
   ,FMRADIOSRV_BEGIN_68MHZ      /* M3 not support yet */
   ,FMRADIOSRV_BEGIN_73MHZ      /* M3 not support yet */
   ,FMRADIOSRV_BEGIN_76MHZ
   ,FMRADIOSRV_BEGIN_87_5MHZ
   ,FMRADIOSRV_BEGIN_87_8MHZ
   ,FMRADIOSRV_BEGIN_88MHZ
   ,FMRADIOSRV_BEGIN_100MHZ
   ,FMRADIOSRV_BEGIN_INVALID
} FmradioBeginRange_e;

typedef enum FmradioEndRange_e_
{
    FMRADIOSRV_END_68MHZ = 0  /* M3 not support yet */
   ,FMRADIOSRV_END_73MHZ      /* M3 not support yet */
   ,FMRADIOSRV_END_74MHZ      /* M3 not support yet */
   ,FMRADIOSRV_END_87_5MHZ
   ,FMRADIOSRV_END_90MHZ
   ,FMRADIOSRV_END_100MHZ
   ,FMRADIOSRV_END_108MHZ
   ,FMRADIOSRV_END_INVALID
} FmradioEndRange_e;

typedef struct FmradioSrvAreaConfig_t_
{
    FmradioDeEmphasis_e    eFmrDeEmphasis;
    FmradioStepSpace_e     eFmrStepSpace;
    FmradioBpfir_e         eFmrBpfir;
    FmradioBeginRange_e    eFmrBeginRange;
    FmradioEndRange_e      eFmrEndRange;
    u8                     nCarrierOn;
    u8                     nCarrierOff;
} FmradioSrvAreaConfig_t;

#endif /* __MMI_FMRADIOSRV_DEF_H__ */


