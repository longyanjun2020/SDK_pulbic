
#ifndef __MMI_AZANRAPP_CFG__H__
#define __MMI_AZANRAPP_CFG__H__

#include "mmi_common_azan.h"
#include "AzanApp_resource.h"

#define AZAN_USER_DEF_TILTE_MAX_SIZE 40
typedef struct
{
    u32 nCityTextID;
    double fLongitude;
    double fLatitude;
    double fGMT;
    double fUserDefLongitude;
    double fUserDefLatitude;    
    MAE_WChar UserDefTitleName[AZAN_USER_DEF_TILTE_MAX_SIZE+1];
    u8 bDST;
    u8 nCalculationMethod;
    u8 bEnableAzan;
    u8 nUserDefGMTID;
} AzanSettingInfo_t;

typedef struct
{
    u32 nDatetime;
    ALARM_STATUS_e eStatus;
} Azan_Entry_t;

#define AZAN_ALARM_MAX_NUM (6)
//Beijing City
#define CONFIG_NAMR_AZAN_SETTING     CONFIG_DEFINE(CFGIT_AZAN_SETTING, AzanSettingInfo_t, 1, \
        /*  nCityTextID          fLongitude fLatitude fGMT  fUserDefLongitude fUserDefLatitude UserDefTitleName bDST  nCalculationMethod bEnableAzan nUserDefGMTID */ \
         {TXT_LIL_N_AZAN_BEIJING, 116.3883,   39.9289, 8.0,   0.00,              0.00,       {L"UserUnDefined"}, FALSE, EGYPT_SURVEY,      FALSE,        12})
#define CONFIG_NAMR_AZAN_ALARM_DATA  CONFIG_DEFINE(CFGIT_AZAN_ALARM_DATA, Azan_Entry_t, AZAN_ALARM_MAX_NUM, \
       /* nDatetime     eStatus*/ \
          {{ 0, ALARM_STATUS_OFF}, \
           { 0, ALARM_STATUS_OFF}, \
           { 0, ALARM_STATUS_OFF}, \
           { 0, ALARM_STATUS_OFF}, \
           { 0, ALARM_STATUS_OFF}})

#define AZANAPP_NAMR_ALL_CONFIG \
        CONFIG_NAMR_AZAN_SETTING \
        CONFIG_NAMR_AZAN_ALARM_DATA

#endif  //__MMI_AZANRAPP_CFG__H__
