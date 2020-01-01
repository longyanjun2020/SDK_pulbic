

#ifndef __MMI_BTSRV_CFG__H__
#define __MMI_BTSRV_CFG__H__

#define BTSRV_DEVICE_NAME_LEN (40)
enum
{
    BTSRV_POWER_OFF=0,
    BTSRV_POWER_ON,
    BTSRV_POWER_NUM
};
typedef u8 BTSRV_PowerAction_e;
enum
{
    BTSRV_DISCOVERABLE=0,
    BTSRV_HIDE,
    BTSRV_DISCOVERABLE_NUM
};
typedef u8 BTSRV_Discoverable_e;



// Allow Mater Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)
#define CONFIG_AMR_BTSRV_RECEIVE_FOLDER  CONFIG_DEFINE(CFGIT_BTSRV_RECEIVE_FOLDER, MAE_WChar, 266, {L"fs:/CARD/Received/"})
#define CONFIG_AMR_BTSRV_RECEIVE_STORAGE  CONFIG_DEFINE(CFGIT_BTSRV_RECEIVE_STORAGE, StorageCfg_t, 1, {STORAGE_CARD})

#define CONFIG_AMR_BTSRV_POWER_ON_OFF CONFIG_DEFINE(CFGIT_BTSRV_POWER_ON_OFF, BTSRV_PowerAction_e, 1, BTSRV_POWER_OFF )
#define CONFIG_AMR_BTSRV_DISCOVERABLE CONFIG_DEFINE(CFGIT_BTSRV_DISCOVERABLE, BTSRV_Discoverable_e, 1, BTSRV_DISCOVERABLE )
#define CONFIG_AMR_BTSRV_LOCAL_NAME CONFIG_DEFINE(CFGIT_BTSRV_LOCAL_NAME, MAE_WChar, BTSRV_DEVICE_NAME_LEN, {L"BT Device"} )

#ifdef __BLUETOOTH_MMI__
#define BTSRV_AMR_ALL_CONFIG \
                CONFIG_AMR_BTSRV_RECEIVE_FOLDER \
                CONFIG_AMR_BTSRV_RECEIVE_STORAGE \
                CONFIG_AMR_BTSRV_POWER_ON_OFF \
                CONFIG_AMR_BTSRV_DISCOVERABLE \
                CONFIG_AMR_BTSRV_LOCAL_NAME
#else
#define BTSRV_AMR_ALL_CONFIG
#endif

#endif  //__MMI_BTSRV_CFG__H__