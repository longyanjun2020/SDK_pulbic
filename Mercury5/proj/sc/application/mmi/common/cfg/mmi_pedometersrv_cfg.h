

#ifndef __MMI_PEDOMETERSRV_CFG__H__
#define __MMI_PEDOMETERSRV_CFG__H__

#define MAX_PEDOMETER_USERNAME_LEN 20
enum
{
    PEDOMETER_SEX_MIN=0,
    PEDOMETER_SEX_MALE=1,
    PEDOMETER_SEX_FEMALE=2,
    PEDOMETER_SEX_MAX=3
};
typedef u8 PedometerSexType_e;
enum
{
    PEDOMETER_RESET_MIN=0,
    PEDOMETER_RESET_TODAY=1,
    PEDOMETER_RESET_ALL=2,
    PEDOMETER_RESET_MAX=3
};
typedef u8 PedometerResetType_e;
enum
{
    PEDOMETER_UNIT_MIN=0,
    PEDOMETER_UNIT_METRIC=1,
    PEDOMETER_UNIT_IMPERIAL=2,
    PEDOMETER_UNIT_MAX=3
};
typedef u8 PedometerUnitType_e;
enum
{
    PEDOMETER_TYPE_MIN=0,
    PEDOMETER_TYPE_AGE=1,
    PEDOMETER_TYPE_HEIGHT=2,
    PEDOMETER_TYPE_WEIGHT=3,
    PEDOMETER_TYPE_GOALSTEPS=4,
    PEDOMETER_TYPE_MAX=5
};
typedef u8 PedometerDataType_e;
typedef struct _PedometerStatItem_t
{
    u16 u16Calorie;
    u32 u32FootSteps;
} PedometerStatItem_t;
typedef struct _PedometerDay_t
{
    u16 u16Year;
    u8 u8Month;
    u8 u8Day;
} PedometerDay_t;

//pedometersrv
#define CONFIG_AMR_PEDOMETERSRV_CNT_ENABLE CONFIG_DEFINE(CFGIT_PEDOMETERSRV_CNT_ENABLE, boolean, 1, TRUE)
#define CONFIG_AMR_PEDOMETERSRV_REMINDER_ENABLE CONFIG_DEFINE(CFGIT_PEDOMETERSRV_REMINDER_ENABLE, boolean, 1, TRUE)
#define CONFIG_AMR_PEDOMETERSRV_TOTAL_STEP CONFIG_DEFINE(CFGIT_PEDOMETERSRV_TOTAL_STEPS, u32, 1, 0)
#define CONFIG_AMR_PEDOMETERSRV_AGE CONFIG_DEFINE(CFGIT_PEDOMETERSRV_AGE, u16, 1, 31)
#define CONFIG_AMR_PEDOMETERSRV_GOAL_STEPS CONFIG_DEFINE(CFGIT_PEDOMETERSRV_GOAL_STEPS, u16, 1, 20)
#define CONFIG_AMR_PEDOMETERSRV_USER_NAME CONFIG_DEFINE(CFGIT_PEDOMETERSRV_USER_NAME, MAE_WChar, 20,{L"Pedo"})
#define CONFIG_AMR_PEDOMETERSRV_SEX CONFIG_DEFINE(CFGIT_PEDOMETERSRV_SEX, PedometerSexType_e, 1,PEDOMETER_SEX_MALE)
#define CONFIG_AMR_PEDOMETERSRV_UNITS CONFIG_DEFINE(CFGIT_PEDOMETERSRV_UNITS, PedometerUnitType_e, 1, PEDOMETER_UNIT_METRIC)
#define CONFIG_AMR_PEDOMETERSRV_CUR_RECORD CONFIG_DEFINE(CFGIT_PEDOMETERSRV_CUR_RECORD, PedometerStatItem_t, 1, {0/*u16Calorie*/, 0/*u32FootSteps*/})
#define CONFIG_AMR_PEDOMETERSRV_YEAR_RECORD CONFIG_DEFINE(CFGIT_PEDOMETERSRV_YEAR_RECORD, PedometerStatItem_t, MAX_DAYS_PER_YEAR, \
  { {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}, \
    {0, 0},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0} })

#define CONFIG_AMR_PEDOMETERSRV_STARTDAY CONFIG_DEFINE(CFGIT_PEDOMETERSRV_STARTDAY, PedometerDay_t, 1, {0/*u16Year*/, 0/*u8Month*/, 0/*u8Day*/})
#define CONFIG_AMR_PEDOMETERSRV_CUR_DAY CONFIG_DEFINE(CFGIT_PEDOMETERSRV_CUR_DAY, PedometerDay_t, 1, {0/*u16Year*/, 0/*u8Month*/, 0/*u8Day*/})
#define CONFIG_AMR_PEDOMETERSRV_CHEIGHT CONFIG_DEFINE(CFGIT_PEDOMETERSRV_CHEIGHT, u8, 8, {0})
#define CONFIG_AMR_PEDOMETERSRV_CWEIGHT CONFIG_DEFINE(CFGIT_PEDOMETERSRV_CWEIGHT, u8, 8, {0})
//pedometersrv end

#ifdef __NATIVE_GAME_MMI_PEDOMETER__
#define PEDOMETERSRV_AMR_ALL_CONFIG \
                              CONFIG_AMR_PEDOMETERSRV_CNT_ENABLE \
                              CONFIG_AMR_PEDOMETERSRV_REMINDER_ENABLE \
                              CONFIG_AMR_PEDOMETERSRV_TOTAL_STEP \
                              CONFIG_AMR_PEDOMETERSRV_AGE \
                              CONFIG_AMR_PEDOMETERSRV_GOAL_STEPS \
                              CONFIG_AMR_PEDOMETERSRV_USER_NAME \
                              CONFIG_AMR_PEDOMETERSRV_SEX \
                              CONFIG_AMR_PEDOMETERSRV_UNITS \
                              CONFIG_AMR_PEDOMETERSRV_CUR_RECORD \
                              CONFIG_AMR_PEDOMETERSRV_YEAR_RECORD \
                              CONFIG_AMR_PEDOMETERSRV_STARTDAY \
                              CONFIG_AMR_PEDOMETERSRV_CUR_DAY \
                              CONFIG_AMR_PEDOMETERSRV_CHEIGHT \
                              CONFIG_AMR_PEDOMETERSRV_CWEIGHT
#else
#define PEDOMETERSRV_AMR_ALL_CONFIG
#endif

#endif //__MMI_PEDOMETERSRV_CFG__H__
