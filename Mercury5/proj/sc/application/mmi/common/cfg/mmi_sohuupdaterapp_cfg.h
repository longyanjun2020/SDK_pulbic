

#ifndef __MMI_SOHUUPDATERAPP_CFG__H__
#define __MMI_SOHUUPDATERAPP_CFG__H__


#define SOHU_SKIN_SYSTEM_FILE_NAME             L""

enum
{
    SOHU_SIM_MASTER = 0,
    SOHU_SIM_SLAVE = 1,
    SOHU_SIM_NO_ACTIVE = 2,
    SOHU_SIM_NO_SIM = 3
};
typedef u8 SohuSimID_e;

enum
{
    SOHU_FREQUENCY_DAILY = 0,
    SOHU_FREQUENCY_WEEKLY,
    SOHU_FREQUENCY_HALFMONTHLY,
    SOHU_FREQUENCY_MONTHLY,
    SOHU_FREQUENCY_NEVER
};
typedef u8 SohuFrequency_e;

typedef struct _SohuUpdaterSettingInfo_t
{
    boolean bConnectPrompt;
    boolean bLibUpdateHint;
    SohuSimID_e eSimId;
    u8 nAccountID;
	MAE_WChar FocusFileName[256];

    SohuFrequency_e eFrequency;
    u8  hour;       // Hour, value range is 0~23
    u8  minute;     // Minute, value range is 0~59    
} SohuUpdaterSettingInfo_t;


// Not Allow Mater Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)

#define CONFIG_AMR_SOHU_UPDATER_SETTING CONFIG_DEFINE(CFGIT_SOHU_UPDATER_SETTING, SohuUpdaterSettingInfo_t, 1, {FALSE, FALSE, SOHU_SIM_MASTER, 0, {SOHU_SKIN_SYSTEM_FILE_NAME}, SOHU_FREQUENCY_NEVER, 0, 0})

#define SOHUUPDATERAPP_AMR_ALL_CONFIG \
                CONFIG_AMR_SOHU_UPDATER_SETTING


#endif  //__MMI_CDWAPAPP_CFG__H__



