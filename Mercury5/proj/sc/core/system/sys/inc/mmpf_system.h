/**
 @file mmpf_system.h
 @brief Header File for the mmpf system.
 @author Truman Yang
 @version 1.0
*/

/** @addtogroup MMPF_SYS
@{
*/

#ifndef _MMPF_SYSTEM_H_
#define _MMPF_SYSTEM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 

#include "mmpf_pll.h"
#include "mmpf_timer.h"
#include "mmp_gpio_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMPILER_DATE_LEN   (12) /// "mmm dd yyyy"
#define COMPILER_TIME_LEN   (10) /// "hh:mm:ss" 9 bytes but word alignment

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_SYS_MDL
{
    MMPF_SYS_MDL_VIF0       = 0,
    MMPF_SYS_MDL_VIF1       = 1,
    MMPF_SYS_MDL_VIF2       = 2,
    MMPF_SYS_MDL_RAW_S0     = 3,
    MMPF_SYS_MDL_RAW_S1     = 4,
    MMPF_SYS_MDL_RAW_S2     = 5,
    MMPF_SYS_MDL_RAW_F      = 6,
    MMPF_SYS_MDL_ISP        = 7,

    MMPF_SYS_MDL_SCAL0      = 8,
    MMPF_SYS_MDL_SCAL1      = 9,
    MMPF_SYS_MDL_SCAL2      = 10,
    MMPF_SYS_MDL_SCAL3      = 11,
    MMPF_SYS_MDL_ICON0      = 12,
    MMPF_SYS_MDL_ICON1      = 13,
    MMPF_SYS_MDL_ICON2      = 14,
    MMPF_SYS_MDL_ICON3      = 15,

    MMPF_SYS_MDL_IBC0       = 16,
    MMPF_SYS_MDL_IBC1       = 17,
    MMPF_SYS_MDL_IBC2       = 18,
    MMPF_SYS_MDL_IBC3       = 19,
    MMPF_SYS_MDL_CCIR       = 20,
    MMPF_SYS_MDL_HDMI       = 21,
    MMPF_SYS_MDL_DSPY       = 22,
    MMPF_SYS_MDL_TV         = 23,

    MMPF_SYS_MDL_MCI        = 24,
    MMPF_SYS_MDL_DRAM       = 25,
    MMPF_SYS_MDL_H264       = 26,
    MMPF_SYS_MDL_JPG        = 27,
    MMPF_SYS_MDL_SD0        = 28,
    MMPF_SYS_MDL_SD1        = 29,
    MMPF_SYS_MDL_SD2        = 30,
    MMPF_SYS_MDL_SD3        = 31,

    MMPF_SYS_MDL_CPU_PHL    = 32,
    MMPF_SYS_MDL_PHL        = 33,
    MMPF_SYS_MDL_AUD        = 34,
    MMPF_SYS_MDL_GRA        = 35,
    MMPF_SYS_MDL_DMA_M0     = 36,
    MMPF_SYS_MDL_DMA_M1     = 37,
    MMPF_SYS_MDL_DMA_R0     = 38,
    MMPF_SYS_MDL_DMA_R1     = 39,

    MMPF_SYS_MDL_GPIO       = 40,
    MMPF_SYS_MDL_PWM        = 41,
    MMPF_SYS_MDL_PSPI       = 42,
    MMPF_SYS_MDL_DBIST      = 43,
    MMPF_SYS_MDL_IRDA       = 44,
    MMPF_SYS_MDL_RTC        = 45,
    MMPF_SYS_MDL_USB        = 46,
    MMPF_SYS_MDL_USBPHY     = 47,

    MMPF_SYS_MDL_I2CS       = 48,
    MMPF_SYS_MDL_SM         = 49,
    MMPF_SYS_MDL_LDC        = 50,
    MMPF_SYS_MDL_PLL_JITTER = 51,
    MMPF_SYS_MDL_SCAL4      = 52,
    MMPF_SYS_MDL_ICON4      = 53,
    MMPF_SYS_MDL_IBC4       = 54,
    MMPF_SYS_MDL_SCAL_RS    = 55,
    MMPF_SYS_MDL_NUM        = 56
} MMPF_SYS_MDL;

typedef enum _MMPF_SYS_CLK
{
    MMPF_SYS_CLK_CPU_A          = 0,
    MMPF_SYS_CLK_CPU_A_PHL      = 1,
    MMPF_SYS_CLK_CPU_B          = 2,
    MMPF_SYS_CLK_CPU_B_PHL      = 3,
    MMPF_SYS_CLK_MCI            = 4,
    MMPF_SYS_CLK_DRAM           = 5,
    MMPF_SYS_CLK_VIF            = 6,
    MMPF_SYS_CLK_RAW_F          = 7,

    MMPF_SYS_CLK_RAW_S0         = 8,
    MMPF_SYS_CLK_RAW_S1         = 9,
    MMPF_SYS_CLK_RAW_S2         = 10,
    MMPF_SYS_CLK_ISP            = 11,
    MMPF_SYS_CLK_COLOR_MCI      = 12,
    MMPF_SYS_CLK_GNR            = 13,
    MMPF_SYS_CLK_SCALE          = 14,
    MMPF_SYS_CLK_ICON           = 15,

    MMPF_SYS_CLK_IBC            = 16,
    MMPF_SYS_CLK_CCIR           = 17,
    MMPF_SYS_CLK_DSPY           = 18,
    MMPF_SYS_CLK_HDMI           = 19,
    MMPF_SYS_CLK_TV             = 20,
    MMPF_SYS_CLK_JPG            = 21,
    MMPF_SYS_CLK_H264           = 22,
    MMPF_SYS_CLK_GRA            = 23,

    MMPF_SYS_CLK_DMA            = 24,
    MMPF_SYS_CLK_PWM            = 25,
    MMPF_SYS_CLK_PSPI           = 26,
    MMPF_SYS_CLK_SM             = 27,
    MMPF_SYS_CLK_SD0            = 28,
    MMPF_SYS_CLK_SD1            = 29,
    MMPF_SYS_CLK_SD2            = 30,
    MMPF_SYS_CLK_SD3            = 31,
    #define MMPF_SYS_CLK_SD(x)  (x + MMPF_SYS_CLK_SD0)
    MMPF_SYS_CLK_GRP0_NUM       = 32,
    
    MMPF_SYS_CLK_USB            = 32,
    MMPF_SYS_CLK_I2CM           = 33,
    MMPF_SYS_CLK_BS_SPI         = 34,
    MMPF_SYS_CLK_GPIO           = 35,
    MMPF_SYS_CLK_AUD            = 36,
    MMPF_SYS_CLK_ADC            = 37,
    MMPF_SYS_CLK_DAC            = 38,
    MMPF_SYS_CLK_IRDA           = 39,

    MMPF_SYS_CLK_LDC            = 40,
    MMPF_SYS_CLK_BAYER          = 41,
    MMPF_SYS_CLK_MDL_NUM        = 42
} MMPF_SYS_CLK;

typedef enum _MMPF_WAKEUP_EVNET
{
	MMPF_WAKEUP_NONE = 0x0,
	MMPF_WAKEUP_GPIO,
	MMPF_WAKEUP_TVPLUG_IN,
	MMPF_WAKEUP_USB_RESUME,
	MMPF_WAKEUP_HDMI_HPD,
	MMPF_WAKEUP_RTC_CNT_VALID,
	MMPF_WAKEUP_RTC_VALID,
	MMPF_WAKEUP_RTC_INT,
	MMPF_WAKEUP_MAX
} MMPF_WAKEUP_EVNET;

typedef enum _MMPF_SYS_ALOC_MEM_TYPE
{
    MMPF_SYS_ALOC_VID = 0,
    MMPF_SYS_ALOC_NUM 
} MMPF_SYS_ALOC_MEM_TYPE;

#if (DBG_ISR_EXE_TIME)
typedef enum __MMPF_SYS_ISR_TYPE {
  MMP_SYS_VIF_ISR = 0,
  MMP_SYS_DMA_ISR,
  MMP_SYS_IBC_ISR,
  MMP_SYS_AUD_ISR,
  MMP_SYS_USB_ISR,
  MMP_SYS_JPG_ISR,
  MMP_SYS_H264_ISR,
  MMP_SYS_TIMER_ISR,
  MMP_SYS_DSPY_ISR,
  MMP_SYS_ISP_ISR,
  MMP_SYS_SD_ISR,
  MMP_SYS_GRA_ISR,
  MMP_SYS_ISR_MAX
} MMPF_SYS_ISR_TYPE;
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct MMP_SYS_BUILD_TIME {
    MMP_UBYTE 	szDate[COMPILER_DATE_LEN]; /// "mmm dd yyyy"
    MMP_UBYTE 	szTime[COMPILER_TIME_LEN]; /// "hh:mm:ss" 9 bytes
} MMP_SYSTEM_BUILD_TIME;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

typedef MMP_BOOL PollingCallBackFunc(void);

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_SYS_ResetSinglePipe(MMP_UBYTE ubPipe);
MMP_ERR	MMPF_SYS_ResetHModule(MMPF_SYS_MDL moduletype, MMP_BOOL bResetRegister);
MMP_ERR MMPF_SYS_ResetVariables(void);
MMP_UBYTE MMPF_SYS_ReadCoreID(void);
MMP_ERR MMPF_SYS_EnterPSMode(MMP_BOOL bEnterPSMode);
MMP_ERR MMPF_SYS_EnterBypassMode(MMP_BOOL bEnterBypassMode);
MMP_ERR MMPF_SYS_EnterSelfSleepMode(void);
MMP_ERR MMPF_SYS_GetFWEndAddr(MMP_ULONG *ulEndAddr);
MMP_ERR MMPF_SYS_GetFWFBEndAddr(MMP_ULONG *ulEndAddr);
MMP_ERR MMPF_SYS_SetWakeUpEvent(MMP_BOOL bEnable, MMPF_WAKEUP_EVNET event, MMP_GPIO_PIN piopin, MMP_UBYTE polarity);
MMP_ERR MMPF_SYS_EnableClock(MMPF_SYS_CLK clockTypeIdx, MMP_BOOL bEnableclock);
MMP_BOOL MMPF_SYS_CheckClockEnable(MMPF_SYS_CLK clockTypeIdx);

MMP_ERR MMPF_SYS_StartTimerCount(void);
MMP_ERR MMPF_SYS_WaitUs(MMP_ULONG ulus, MMP_BOOL *bPollingDone, PollingCallBackFunc *Func);
MMP_ERR MMPF_SYS_GetTimerCount(MMP_ULONG *ulTick, MMP_ULONG *ulTickPerUs);
#if (EN_AUTO_TEST_LOG == 1)
MMP_ERR MMPF_SYS_ClrAutoTestLog(void);
MMP_ERR MMPF_SYS_DumpAutoTestLog(void);
MMP_ERR MMPF_SYS_SetUserDefCmdNum(MMP_USHORT uwUserDefNum);
MMP_UBYTE MMPF_SYS_IsAutoTestCmdLFull(MMP_ULONG ulAhcSysMode);
#endif

#if (DBG_ISR_EXE_TIME)
MMP_ERR MMPF_SYS_GetISRExeTime(MMPF_SYS_ISR_TYPE ISRType, MMP_BOOL bStartExeTime, MMP_ULONG ulExeTimeLimit);
#endif


#endif	//_MMPF_SYSTEM_H_

/** @}*/ //end of MMPF_SYS
