//
// drv_stg_platform.h
//

#ifndef _DRV_STG_PLATFORM_H_
#define _DRV_STG_PLATFORM_H_

#include "sys_MsWrapper_cus_os_util.h" // MsGetOsTick()
//#include "sys_sys_arm.h" // B3 B4 sys_Clean_and_flush_data_cache_buffer()
//#include "sys_sys_r2.h"  // G1    sys_Drain_write_buffer()
extern void sys_Clean_and_flush_data_cache_buffer(u32 addr, s32 size);
extern void sys_Drain_write_buffer(void);
//#include "hal_drv_util.h" // HalUtilPHY2MIUAddr()
extern u32 HalUtilPHY2MIUAddr(u32 phyaddr);

typedef enum
{
    L_ASSERT    = 0,
    L_ERROR     = 1,
    L_MSG       = 2,
    L_INFO      = 3,
    L_PRFOMNS   = 4,

} E_LOG_LEVEL;

typedef enum
{
    E_CHIP_UNKNOW   =  0,
    E_CHIP_B_3      =  3,
    E_CHIP_B_4      =  4,
    E_CHIP_B_5      =  5,
    E_CHIP_B_9      =  9,
    E_CHIP_B10      = 10,

} E_CHIP_NAME;

typedef enum
{
    E_IP_FCIE_ONLY  = 0,
    E_IP_SDIO_ONLY  = 1,
    E_IP_FCIE_SDIO  = 2,

} E_STG_IP_CFG;

typedef enum
{
    E_SD_DATA_BUS_NONE   = 0,
    E_SD_DATA_BUS_1_BIT  = 1,
    E_SD_DATA_BUS_4_BITS = 2,

} E_STG_DATA_BUS;

void LOG_SD(E_LOG_LEVEL LogLevel, char *fmt, ...);

#ifdef __ARMCC_VERSION
    #define ARMCC_PACKED __packed
    #define GCC_PACKED
#elif defined __GNUC__
    #define ARMCC_PACKED
    #define GCC_PACKED __attribute__((packed))
#endif

#ifdef __ARMCC_VERSION
    #define ARMCC_ALIGN __align(32)
    #define GCC_ALIGN
#elif defined __GNUC__
    #define ARMCC_ALIGN
    #define GCC_ALIGN __attribute__((aligned(32)))
#endif

void            DrvStg_CardPowerCtrl(U8 u8Disk, U8 u8OnOff);
void            MDrv_CheckCustPmGpioSetting(void);
U8              DrvStg_GetE2PConfigSave2Var(void);
U8              DrvStg_HasCardDetect(U8 u8Disk);
U8              DrvStg_CardInsertIsLow(U8 u8Disk);
E_STG_DATA_BUS  DrvStg_GetDataBusConfig(U8 u8Disk);
U8              DrvStg_DualCard1BitMode(void);
U32             DrvStg_GetDowngradeSdClock(void);
U32             DrvStg_GetFmRxLimitClock(U32 u32Clock);
E_CHIP_NAME     DrvStg_GetChipName(void);
E_STG_IP_CFG    DrvStg_GetIpConfig(void);

#endif // #ifndef _DRV_STG_PLATFORM_H_

