

#ifndef __MMI_CDWAPAPP_CFG__H__
#define __MMI_CDWAPAPP_CFG__H__
#include "mmi_common_cfg.h"
typedef struct _CdwapSettingInfo_t
{
    u8 nActiveSimId;
    boolean bLoadImage;
    boolean bAlreadyShowNotify;
    u8 nFontSize;
} CdwapSettingInfo_t;


// Not Allow Mater Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)

#define CONFIG_AMR_CDWAP_SETTING_INFO CONFIG_DEFINE(CFGIT_CDWAP_SETTING_INFO, CdwapSettingInfo_t, 1, {0, TRUE, FALSE, 2/*CDWAPAPP_FONT_SIZE_NORMAL*/} )

#ifdef __WAP_MMI_CDWAP__ 
#define CDWAPAPP_AMR_ALL_CONFIG \
                CONFIG_AMR_CDWAP_SETTING_INFO
#else
#define CDWAPAPP_AMR_ALL_CONFIG
#endif

#endif  //__MMI_CDWAPAPP_CFG__H__
