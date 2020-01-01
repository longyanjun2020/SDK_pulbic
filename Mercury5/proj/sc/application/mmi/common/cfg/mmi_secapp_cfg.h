
#ifndef __MMI_SECURITY_CFG__H__
#define __MMI_SECURITY_CFG__H__

#define FOUR_DIGITS_PASSWORD_LEN (4)
#define EIGHT_DIGITS_PASSWORD_LEN (8)
#define MAX_IMSI_LEN (15)
#define MAX_SIM_IMSI_LIST_NUM (3)
#define MAX_MCC_LEN (3)
#define MAX_MNC_LEN (3)
#define MAX_MCC_MNC_NUM (3)
#define MAX_NETWORK_SUBSET_LEN (2)
#define MAX_NETWORK_SUBSET_NUM (3)
#define MAX_GID1_AND_GID2_LEN (15)
#define MAX_GID1_AND_GID2_NUM (3)
#define MAX_SIM_USIM_LOCK_LEN (8)
#define MAX_SIM_USIM_LOCK_NUM (3)
enum
{
    AutoKeypadLock_Off=0,
    AutoKeypadLock_5_Sec=1,
    AutoKeypadLock_15_Sec=2,
    AutoKeypadLock_30_Sec=3,
    AutoKeypadLock_1_Min=4,
    AutoKeypadLock_3_Mins=5,
    AutoKeypadLock_5_Mins=6
};
typedef u8 AutoKeypadLock_e;
enum
{
    SecurityLockStatus_Off=0/*Off*/,
    SecurityLockStatus_On=1/*On*/
};
typedef u8 SecurityLockStatus_e;
enum
{
    SecurityCheckCnt_Forever=0,
    SecurityCheckCnt_MaxCnt=1,
    SecurityCheckCnt_Default = SecurityCheckCnt_Forever
};
typedef u8 SecurityCheckCount_e;
enum
{
    NetworkLockMode_none=0, /*Check NP code again if MS is restart.*/
    NetworkLockMode_unique=1, /*Once NP code is pass, network lock is unlocked forever.*/
    NetworkLockMode_universal,
    NetworkLockMode_default = NetworkLockMode_none
};
typedef u8 NetworkLockMode_e;
typedef struct _NetworkLockModeInfo_t
{
    NetworkLockMode_e eNetworkLockMode;
    u8 u8MaxNumofCode;
}NetworkLockModeInfo_t;
typedef struct _SIMLockIMSIList_t
{
    u8 au8IMSIList[MAX_SIM_IMSI_LIST_NUM][MAX_IMSI_LEN+1];
} SIMLockIMSIList_t;
typedef struct _NetworkLockInfo_t
{
    u8 bSIMUSIMLockEnable;
    u8 bNetworkLockEnable;
    u8 bNetworkSubsetLockEnable;
    u8 bServiceProviderLockEnable;
    u8 bCorporateLockEnable;
    u8 dummy[3];
} NetworkLockInfo_t;
typedef struct _NetworkLockCusSetting_t
{
    SecurityCheckCount_e eSecCheckCnt;
    NetworkLockModeInfo_t tNetworkLockModeInfo;
}NetworkLockCusSetting_t;
typedef struct _MccMnc_t
{
    u8 MCC[MAX_MCC_LEN+1];
    u8 MNC[MAX_MNC_LEN+1];
} MccMnc_t;
typedef struct _NetworkLock_t
{
    MccMnc_t aryMccMncTable[MAX_MCC_MNC_NUM];
} NetworkLock_t;
typedef struct _NetworkSubsetLock_t
{
    u8 aryIMSI6thAnd7th[MAX_NETWORK_SUBSET_NUM][MAX_NETWORK_SUBSET_LEN+1];
    u8 dummy[3];
} NetworkSubsetLock_t;
typedef struct _ServiceProviderLock_t
{
    u8 aryGID1[MAX_GID1_AND_GID2_NUM][MAX_GID1_AND_GID2_LEN+1];
} ServiceProviderLock_t;
typedef struct _Gid1Gid2_t
{
    u8 GID1[MAX_GID1_AND_GID2_LEN+1];
    u8 GID2[MAX_GID1_AND_GID2_LEN+1];
} Gid1Gid2_t;
typedef struct _CorporateLock_t
{
    Gid1Gid2_t aryGID1Gid2[MAX_GID1_AND_GID2_NUM];
} CorporateLock_t;
typedef struct _SIMUSIMLock_t
{
    u8 aryIMSI8thTo15th[MAX_SIM_USIM_LOCK_NUM][MAX_SIM_USIM_LOCK_LEN+1];
    u8 dummy;
} SIMUSIMLock_t;
typedef struct _NetworkLockTable_t
{
    SIMUSIMLock_t SIMUSIMLock;
    NetworkLock_t NetworkLock;
    NetworkSubsetLock_t NetworkSubsetLock;
    ServiceProviderLock_t ServiceProviderLock;
    CorporateLock_t CorporateLock;
} NetworkLockTable_t;

// Not Allow Mater Reset

#define CONFIG_NAMR_SECURITY_CUSTOMER_KEY CONFIG_DEFINE(CFGIT_SECURITY_CUSTOMER_KEY, u8, EIGHT_DIGITS_PASSWORD_LEN+1, {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x00})
#define CONFIG_NAMR_SECURITY_PHONE_LOCK_STATUS CONFIG_DEFINE(CFGIT_SECURITY_PHONE_LOCK_STATUS, SecurityLockStatus_e, 1, SecurityLockStatus_Off)
#define CONFIG_NAMR_SECURITY_PHONEBOOK_LOCK_STATUS CONFIG_DEFINE(CFGIT_SECURITY_PHONEBOOK_LOCK_STATUS, SecurityLockStatus_e, 1, SecurityLockStatus_Off)
#define CONFIG_NAMR_SECURITY_CALLCENTER_LOCK_STATUS CONFIG_DEFINE(CFGIT_SECURITY_CALLCENTER_LOCK_STATUS, SecurityLockStatus_e, 1, SecurityLockStatus_Off)
#define CONFIG_NAMR_SECURITY_MESSAGE_LOCK_STATUS CONFIG_DEFINE(CFGIT_SECURITY_MESSAGE_LOCK_STATUS, SecurityLockStatus_e, 1, SecurityLockStatus_Off)

#define CONFIG_NAMR_SECURITY_SIM_LOCK_STATUS CONFIG_DEFINE(CFGIT_SECURITY_SIM_LOCK_STATUS, SecurityLockStatus_e,1, SecurityLockStatus_Off)

#define CONFIG_NAMR_SECURITY_PHONE_CODE CONFIG_DEFINE(CFGIT_SECURITY_PHONE_CODE, u8, FOUR_DIGITS_PASSWORD_LEN+1, {7,14,21,28,0})
#define CONFIG_NAMR_SECURITY_PIN_CODE_MASTER CONFIG_DEFINE(CFGIT_SECURITY_PIN_CODE_MASTER, u8, EIGHT_DIGITS_PASSWORD_LEN+1, {7,14,21,28,35,42,49,56,0})
#define CONFIG_NAMR_SECURITY_PIN_CODE_SLAVE CONFIG_DEFINE(CFGIT_SECURITY_PIN_CODE_SLAVE, u8, EIGHT_DIGITS_PASSWORD_LEN+1, {7,14,21,28,35,42,49,56,0})
#define CONFIG_NAMR_SECURITY_SIM_CODE CONFIG_DEFINE(CFGIT_SECURITY_SIM_CODE, u8, FOUR_DIGITS_PASSWORD_LEN+1, {7,14,21,28,0})
#define CONFIG_NAMR_SECURITY_SIM_LOCK_IMSI_LIST CONFIG_DEFINE(CFGIT_SECURITY_SIM_LOCK_IMSI_LIST, SIMLockIMSIList_t, 1, {{ {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}} }} )

#define SECURITY_NAMR_ALL_CONFIG \
            CONFIG_NAMR_SECURITY_CUSTOMER_KEY \
            CONFIG_NAMR_SECURITY_PHONE_LOCK_STATUS \
            CONFIG_NAMR_SECURITY_PHONEBOOK_LOCK_STATUS\
            CONFIG_NAMR_SECURITY_CALLCENTER_LOCK_STATUS\
            CONFIG_NAMR_SECURITY_MESSAGE_LOCK_STATUS\
            CONFIG_NAMR_SECURITY_SIM_LOCK_STATUS \
            CONFIG_NAMR_SECURITY_PHONE_CODE \
            CONFIG_NAMR_SECURITY_PIN_CODE_MASTER \
            CONFIG_NAMR_SECURITY_PIN_CODE_SLAVE \
            CONFIG_NAMR_SECURITY_SIM_CODE \
            CONFIG_NAMR_SECURITY_SIM_LOCK_IMSI_LIST

#endif //__MMI_SECURITY_CFG__H__





