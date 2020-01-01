#ifndef __UT_MAIN_H__
#define __UT_MAIN_H__

#include "ut_common.h"

typedef void (*UtTestEndCb)(void *pInstance);

typedef void (*UtDeviceCond_ft)(u32 nCusData);

typedef enum
{
    UT_SOURCE__SRV_BB = 0,
    UT_SOURCE__SRV_WB,
    UT_SOURCE__NUM,
} UtSource_e;

typedef enum
{
    UT_DEVFLAG_RECOVER=0x00000000,    /* Recovr the device flag to the original states */
    /* for Battery */
    UT_DEVFLAG_BAT_CPI=0x00000001,    /* The charger is plugged in                     */
    UT_DEVFLAG_BAT_CPO=0x00000002,    /* The charger is plugged out                    */
    UT_DEVFLAG_BAT_LOW=0x00000004,    /* The low battery level                         */
    UT_DEVFLAG_BAT_FUL=0x00000008,    /* The full battery level                        */
    UT_DEVFLAG_BAT_NOR=0x00000010,    /* The normal battery level                      */
    /* for Audio */
    UT_DEVFLAG_AUD_HPI=0x00000100,    /* The headset is plugged in                     */
    UT_DEVFLAG_AUD_HPO=0x00000200,    /* The headset is plugged out                    */
} eDevFlag;

/* the type to define the underlying device condition, such as low battery, SD full, etc. */
typedef struct DevCondParam_t_
{
    u32               nDevTiming;   /* the timing to trigger the underlying device condition (mini-second) */
    eDevFlag          eDevCond;     /* the flag to depict the underlying device condition (refer to eDevFlag)      */
} DevCondParam_t;

typedef struct DevCondCbParam_t_
{
    u32               nCbTiming;    /* the timing to trigger the callback function after setting device condition (mini-second) */
    UtDeviceCond_ft   fnDevCond;    /* the function pointer to be executed for setting underlying device condition */
    u32               nCusData;
} DevCondCbParam_t;

/* This compiler option is used to depict whether to support the implementation of  */
/* asynchronous architecture for unit test. If it's not defined, the unit test will */
/* only support the older one which did the sequencial test in looping.             */
#define UT_TEST_SUPPORT_ASYNC

/* This defined value depicts the synchronous checking immediately */
#define UT_TEST_PERIOD_IMMEDIATE 0
/* This defined value depicts the synchronous checking in 1 minute */
#define UT_TEST_PERIOD_DEFAULT   100

bool       UtDummyCheck(FILE *flog, int idx);
bool       UtIsAsyncTimeout(void);
bool       UtDoAsynCheck(void);
void       UtExecReturnDirectly(bool bRet);
char      *UtGetTestSuitName(char *);
eDevFlag   UtGetDevCondition(void);
void       UtSetDevCondition(DevCondParam_t *pDevCond, DevCondCbParam_t *pCbParam);

/*The following APIs are only provided for mmi_unitTestApp.c*/
boolean    UtIsSourceExist(UtSource_e eSource);
MAE_Ret    UtInitTCs(UtSource_e eSource, void *pAppInstance, UtTestEndCb pfnTestEndCb);
void       UtTest(u32 nIdx);
void       UtRelease(void);
MAE_WChar *UtGetTestResult(void);
u32        UtGetSuiteNum(void);
u32        UtGetCaseNumByIdx(u32 nSuiteIdx);
MAE_WChar *UtGetTestSuitNameByIdx(u32 nIndex);
MAE_WChar *UtGetTestCaseNameByIdx(u32 nSuiteIdx, u32 nCaseIdx);
void       UtSetTestCaseEnable(u32 nSuiteIdx, u32 nCaseIdx, boolean bEnable);
void       UtSetTestSuiteEnable(u32 nSuiteIdx, boolean bEnable);
void       UtSetTestSuiteRepeatTimes(u32 nSuiteIdx, u32 nTotalRound);
boolean    UtIsTestSuiteEnable(u32 nSuiteIdx);

#endif    /* __UT_MAIN_H__ */
