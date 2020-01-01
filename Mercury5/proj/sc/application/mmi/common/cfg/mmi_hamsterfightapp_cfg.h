
#ifndef __MMI_HAMSTERFIGHTAPP_CFG_H__
#define __MMI_HAMSTERFIGHTAPP_CFG_H__

typedef u8 HF_ProcessState_e;

typedef struct
{
    HF_ProcessState_e e_HF_ProcessState;
    u16 nGameLevel;
    u16 nRemainingHP;
    u16 nComboNumber;
    u16 nRemainingHamsterNum;
    u16 nCountDownMotionNumber;
    u16 nWinGameMotionNumber;
    u16 nLoseGameMotionNumber;
} HAMSTERFIGHT_RECORD_t;

// Allow Mater Reset

//#define CONFIG_DEFINE(cfgId, type, name, value)
//HAMSTERFIGHT
#define CONFIG_AMR_HAMSTERFIGHT_RECORD_LIST  CONFIG_DEFINE(CFGIT_HAMSTERFIGHT_RECORD_LIST, HAMSTERFIGHT_RECORD_t, 1, \
{0/*e_HF_ProcessState*/, 1/*nGameLevel*/, 10/*nRemainingHP*/, 0/*nComboNumber*/, 10/*nRemainingHamsterNum*/, 0/*nCountDownMotionNumber*/, 0/*nWinGameMotionNumber*/, 0/*nLoseGameMotionNumber*/}/*HamsterFightRecordList*/)

#define CONFIG_AMR_HAMSTERFIGHT_SOUND_SWITCH  CONFIG_DEFINE(CFGIT_HAMSTERFIGHT_SOUND_SWITCH, u8, 1, {1/*bIsSoundOn*/}/*HamsterFightSoundSwitch*/)
#define CONFIG_AMR_HAMSTERFIGHT_IMAGE_URL  CONFIG_DEFINE(CFGIT_HAMSTERFIGHT_IMAGE_URL, MAE_WChar, FILEMGR_MAX_FILEPATH_SIZE, {L""}/*HamsterFightImageUrl*/)
//HAMSTERFIGHT end


#define HAMSTERFIGHTAPP_AMR_ALL_CONFIG \
                CONFIG_AMR_HAMSTERFIGHT_RECORD_LIST \
                CONFIG_AMR_HAMSTERFIGHT_SOUND_SWITCH \
                CONFIG_AMR_HAMSTERFIGHT_IMAGE_URL



#endif /* __MMI_HAMSTERFIGHTAPP_CFG_H__ */

