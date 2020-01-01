/**
 *  @file mmps_system.h
 *  @brief Header file the host system API
 *  @author Jerry Tsao, Truman Yang
 *  @version 1.1
 */
#ifndef _MMPS_SYSTEM_H_
#define _MMPS_SYSTEM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"
#include "config_fw.h"
#include "mmp_gpio_inc.h"
#include "mmpd_system.h"

/** @addtogroup MMPS_System
@{
*/

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPS_SYSTEM_OPMODE
{
    MMPS_SYSTEM_OPMODE_BYPASS = 0,		/**< System Bypass mode, LCD bus is bypassed and controlled by B/B, 
    										Firmware is active. */
    MMPS_SYSTEM_OPMODE_ACTIVE,			/**< System active mode, LCD bus is controlled by AIT chip, Firmware is active */
    MMPS_SYSTEM_OPMODE_SUSPEND,			/**< System suspend mode, LCD bus is bypassed and controlled by B/B,
    										Firmware is sleeping. */
    MMPS_SYSTEM_OPMODE_PWRDN,			/**< System power down. LCD bus is bypassed and controlled by B/B,
    										Firmware is released. */
    MMPS_SYSTEM_OPMODE_SELFSLEEP,       /**< Standalone System enter self sleep mode*/
    MMPS_SYSTEM_OPMODE_MAX
} MMPS_SYSTEM_OPMODE;

typedef enum _MMPS_DRAM_TYPE
{
    MMPS_DRAM_TYPE_NONE = 0,	// no stack memory
    MMPS_DRAM_TYPE_1,			// first used
    MMPS_DRAM_TYPE_2,			// second used
    MMPS_DRAM_TYPE_3,			// third used
    MMPS_DRAM_TYPE_EXT,
    MMPS_DRAM_TYPE_AUTO
} MMPS_DRAM_TYPE;

typedef enum _MMPS_DRAM_MODE
{
    MMPS_DRAM_MODE_SDRAM = 0,	// SD RAM
    MMPS_DRAM_MODE_DDR,			// DDR RAM
    MMPS_DRAM_MODE_DDR2,
    MMPS_DRAM_MODE_DDR3,
    MMPS_DRAM_MODE_NUM
} MMPS_DRAM_MODE;

typedef enum _MMPS_SYSTEM_MEM_DIR
{
    MMPS_SYSTEM_MEM_TOP = 0,           //#define MEM_ALLOC_FROM_TOP
    MMPS_SYSTEM_MEM_BOTTOM             //#define MEM_ALLOC_FROM_BOTTOM 
} MMPS_SYSTEM_MEM_DIR;

typedef enum
{
    MMPS_SYSTEM_WAKEUP_NONE = 0x0,
    MMPS_SYSTEM_WAKEUP_GPIO,
    MMPS_SYSTEM_WAKEUP_TVPLUG_IN,
    MMPS_SYSTEM_WAKEUP_USB_RESUME,
    MMPS_SYSTEM_WAKEUP_HDMI_HPD,
    MMPS_SYSTEM_WAKEUP_RTC_CNT_VALID,
    MMPS_SYSTEM_WAKEUP_RTC_VALID,
    MMPS_SYSTEM_WAKEUP_RTC_INT,
    MMPS_SYSTEM_WAKEUP_MAX
}MMPS_SYSTEM_WAKEUP_EVNET;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

/** @brief Type of by pass pin controller call back function.

The responsibility of this function should set the bypass ping according to the input
@param[in] value Value 1 for high, value 0 for low.
@return If the initalize successful
*/
typedef struct _MMPS_SYSTEM_CONFIG {
    MMPS_DRAM_TYPE		stackMemoryType;		///< Stack memory type inside AIT chip
    MMPS_DRAM_MODE      stackMemoryMode;    	///< DDR or SDRAM
	MMP_ULONG           ulStackMemoryStart;		///< Stack memory start address
	MMP_ULONG           ulStackMemorySize;		///< Stack memory size
    MMP_ULONG           ulMaxReserveBufferSize; ///< Reserve Buffer Size for Audio Operation
    MMP_ULONG           ulMaxReserveChannel; 	///< Reserve Buffer Size for Audio Operation
} MMPS_SYSTEM_CONFIG;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMPS_SYSTEM_CONFIG* MMPS_System_GetConfig(void);
MMP_UBYTE MMPS_System_ReadCoreID(void);
MMP_ERR MMPS_System_ResetSystem(void);
MMP_ERR MMPS_System_SetOperationMode(MMPS_SYSTEM_OPMODE opMode);

MMP_ERR MMPS_System_AllocateFSBuffer(void);
MMP_ERR MMPS_System_SendEchoCommand(void);
MMP_ERR MMPS_System_SetAudioFrameStart(MMP_ULONG *ulFBEndAddr);
MMP_ERR MMPS_System_GetAudioFrameStart(MMP_ULONG audio_id, MMP_ULONG *ulFBEndAddr);
MMP_ERR MMPS_System_GetPreviewFrameStart(MMP_ULONG *ulFBEndAddr);
MMP_ERR MMPS_System_SetWakeUpEvent(MMP_BOOL bEnable, MMPS_SYSTEM_WAKEUP_EVNET event, MMP_GPIO_PIN piopin, MMP_UBYTE polarity);

/* Memory Pool Function */
void MMPS_System_SetMemHeapEnd(MMP_ULONG ulHeapEnd);
MMP_ULONG MMPS_System_GetMemHeapEnd(void);

#if (EN_AUTO_TEST_LOG == 1)
MMP_ERR MMPS_System_ClrAutoTestLog(void);
MMP_ERR MMPS_System_DumpAutoTestLog(void);
MMP_ERR MMPS_System_SetUserDefCmdNum(MMP_LONG ulUserDefNum);
#endif

/// @}

#endif // _MMPS_SYSTEM_H_
