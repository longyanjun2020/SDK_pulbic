
#ifndef __MMI_FMRADIOAPP_CFG__H__
#define __MMI_FMRADIOAPP_CFG__H__

#include "mmi_common_custom.h"
#include "mmi_CusDefine.h"

/*
The maximum of the numeric icon of menu wdg is 20.
If you want to extend the CUS_FMR_CHANNEL_NUM_MAX, you need to add numeric icon in Cus_NumericIconTbl.
*/
#define FMR_CHANNEL_NUM_MAX CUS_FMR_CHANNEL_NUM_MAX
#define FMR_CHANNEL_NAME_EMPTY L""
#define FMR_CHANNEL_FREQ_EMPTY (0)
#define FMR_CHANNEL_NAME_EMPTY_DISP L"---"
#define FMR_NAME_MAX_BYTE_SIZE (30)
#define FMR_NAME_MAX_WORD_SIZE (FMR_NAME_MAX_BYTE_SIZE/2)
enum
{
    FMR_CHANNEL_1=0,
    FMR_CHANNEL_2=1,
    FMR_CHANNEL_3=2,
    FMR_CHANNEL_4=3,
    FMR_CHANNEL_5=4,
    FMR_CHANNEL_6=5,
    FMR_CHANNEL_7=6,
    FMR_CHANNEL_8=7,
    FMR_CHANNEL_9=8
};
typedef u8 MMI_FMR_CHANNEL_NO_e;
enum
{
    FMR_SETTING_OFF=0,
    FMR_SETTING_ON=1
};
typedef u8 MMI_FMR_SETTING_e;
enum
{
    FMRArea_TW=0/*FMRArea_TW*/,
    FMRArea_CN=1/*FMRArea_CN*/
};
typedef u8 FMRArea_e;
typedef struct FMR_CHANNEL_RECORD_TAG
{
    MAE_WChar ChannelName[FMR_NAME_MAX_WORD_SIZE+1];
    u32 u32ChannelFreq;
} FMR_CHANNEL_RECORD_t;

enum
{
    VOICE_RECORD_LOW_QUALITY=0/*Low quality - AMR*/, 
    VOICE_RECORD_NORMAL_QUALITY/*Normal quality - AWB*/, 
    VOICE_RECORD_HIGH_QUALITY/*High quality - MP3*/, 
    VOICE_RECORD_HIGH_QUALITY_2/*High quality_2 - WAV*/, 
    VOICE_RECORD_NUM_QUALITY/*Number of voice record type*/
};
typedef u8 VOICE_RECORD_Type_e;
enum
{
    FM_RECORD_STORAGE_PHONE/*Storage Phone*/, 
    FM_RECORD_STORAGE_CARD/*Storage Card*/,
    FM_RECORD_STORAGE_CARD2/*Storage Card2*/,     
    FM_RECORD_STORAGE_NUM/*Number of storage*/
};
typedef u8 FM_Record_Storage_e;

// Allow Mater Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)
//FM Radio AP
#define CONFIG_AMR_FMR_BACKGROUND_PLAY                  CONFIG_DEFINE(CFGIT_FMR_BACKGROUND_PLAY, MMI_FMR_SETTING_e, 1, FMR_SETTING_OFF )
#define CONFIG_AMR_FMR_SPEAKER                          CONFIG_DEFINE(CFGIT_FMR_SPEAKER, MMI_FMR_SETTING_e, 1, FMR_SETTING_OFF )
#define CONFIG_AMR_FMR_AREA                             CONFIG_DEFINE(CFGIT_FMR_AREA, FMRArea_e, 1, FMRArea_CN )

#define FMRADIOAPP_AMR_ALL_CONFIG \
                CONFIG_AMR_FMR_BACKGROUND_PLAY \
                CONFIG_AMR_FMR_SPEAKER \
                CONFIG_AMR_FMR_AREA


// Not Allow Mater Reset
#define CONFIG_NAMR_FMR_FREQUENCY CONFIG_DEFINE(CFGIT_FMR_FREQUENCY, u32, 1, MMI_FMRADIOSRV_DEFAULT_FREQ)
#define CONFIG_NAMR_FMR_MY_CHANNEL_LIST CONFIG_DEFINE(CFGIT_FMR_MY_CHANNEL_LIST, FMR_CHANNEL_RECORD_t, FMR_CHANNEL_NUM_MAX, \
{{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/},\
{{L""}/*ChannelName*/, 0/*u32ChannelFreq*/}}/*MyChannelList*/)
#ifdef __APP_MMI_FM_RADIO_REC__
#define CONFIG_AMR_FMR_RECORD_TYPE                      CONFIG_DEFINE(CFGIT_FMR_RECORD_TYPE, VOICE_RECORD_Type_e, 1, VOICE_RECORD_NORMAL_QUALITY )
#define CONFIG_AMR_FMR_RECORD_STORAGE                   CONFIG_DEFINE(CFGIT_FMR_RECORD_STORAGE, StorageCfg_t, 1, {STORAGE_CARD} )
#define CONFIG_AMR_FMR_SCH_RECORD_STORAGE                   CONFIG_DEFINE(CFGIT_FMR_SCH_RECORD_STORAGE, StorageCfg_t, 1, {STORAGE_CARD} )
#else
#define CONFIG_AMR_FMR_RECORD_TYPE
#define CONFIG_AMR_FMR_RECORD_STORAGE
#define CONFIG_AMR_FMR_SCH_RECORD_STORAGE                   
#endif

#define FMRADIOAPP_NAMR_ALL_CONFIG \
                CONFIG_NAMR_FMR_FREQUENCY \
                CONFIG_NAMR_FMR_MY_CHANNEL_LIST \
                CONFIG_AMR_FMR_RECORD_TYPE \
                CONFIG_AMR_FMR_RECORD_STORAGE \
				CONFIG_AMR_FMR_SCH_RECORD_STORAGE


#endif  //__MMI_FMRADIOAPP_CFG__H__




