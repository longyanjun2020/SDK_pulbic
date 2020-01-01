////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_gpd_pub.h
* @version
* @brief   This module defines the export interfaces of General Peripheral Device service
*
*/

#ifndef __MDL_GPD_PUB_H__
#define __MDL_GPD_PUB_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#define MDL_GPD_VER_SW_MAX_LEN            100
#define MDL_GPD_VER_M2_CHIP_ID_MAX_LEN    16
#define MDL_GPD_VER_M2_ROM_CODE_MAX_LEM   32

#ifdef __SMALL_ROM_32__
#define DRV_SECONDARY_TRACE(x)
#else
#define DRV_SECONDARY_TRACE(x)  _TRACE(x)
#endif



#ifdef __SMALL_ROM_32__
#define SECONDARY_TRACE(x)
#else
#define SECONDARY_TRACE(x)  _TRACE(x)
#endif


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The structure defines the device information
 */
typedef enum {
  MDL_GPD_LCD_DEVICE     = 0x00000001,
  MDL_GPD_LED_DEVICE     = 0x00000002,
  MDL_GPD_BL_DEVICE      = 0x00000004,
  MDL_GPD_KEYPADL_DEVICE = 0x00000008,
  MDL_GPD_MMP_DEVICE     = 0x00000010,
  MDL_GPD_AUD_DEVICE     = 0x00000020,
#ifdef __SUBBACKLIGHT_DRV__
  MDL_GPD_SUBBL_DEVICE   = 0x00000040,
#endif
  MDL_GPD_FS_DEVICE      = 0x00000080,
#ifdef __G_SENSOR_DRV__
  MDL_GPD_GSENSOR_DEVICE = 0x00000100,
#endif
  MDL_GPD_CHG_DEVICE = 0x00000200,
  MDL_GPD_BLUETOOTH_DEVICE = 0x00000400,
#ifdef __BREATHLIGHT_DRV__
  MDL_GPD_BREATHLIGHT_DEVICE = 0x00000800,
#endif
#if defined(__WLAN__)
  MDL_GPD_WIFI_DEVICE    = 0x00001000,
#endif
}MdlGpdDevice_e;


/**
 *  @brief The enumeration defines the return code of the General Peripheral Device interface
 */
typedef enum
{
    MDL_GPD_OK,                 /**< Function complete successfully */
    MDL_GPD_FAIL,               /**< Function common fail */
    MDL_GPD_PARAM_ERROR,        /**< The input parameter is wrong */
    MDL_GPD_MEM_ALLOC_ERROR,    /**< Can not allocate memory from OS */
    MDL_GPD_REJECT,             /**< Request rejected because of other function's confliction */
    MDL_GPD_ABORT,              /**< Request aborted because of incorrect sequence */
    MDL_GPD_TIMEOUT             /**< Request no response timeout, this error is returned by call back function */
} MdlGpdErrCode_e;

/**
 * @brief The enumeration defines the LED id.
 */
typedef enum
{
    MDL_GPD_LED_RED       = 1,    /**< RED    LED index (Depends on hardware connection) */
    MDL_GPD_LED_GREEN     = 2,    /**< GREEN  LED index (Depends on hardware connection) */
    MDL_GPD_LED_CYAN      = 3,    /**< CYAN   LED index (Depends on hardware connection) */
    MDL_GPD_LED_BLUE      = 4,    /**< BLUE   LED index (Depends on hardware connection) */
    MDL_GPD_LED_YELLOW    = 5,    /**< YELLOW LED index (Depends on hardware connection) */
    MDL_GPD_LED_PURPLE    = 6,    /**< PURPLE LED index (Depends on hardware connection) */
    MDL_GPD_LED_WHITE     = 7,    /**< WHITE  LED index (Depends on hardware connection) */
    MDL_GPD_LED_FUN_LIGHT = 8,    /**< FUN LIGHT  index (Depends on hardware connection) */
    MDL_GPD_LED_MAX       = 9,
} MdlGpdLedId_e;

/**
 * @brief The enumeration defines the backlight id.
 */
typedef enum
{
    MDL_GPD_BL_0        = 0, /**< Main Backlight Index */
    MDL_GPD_KPD_LIGHT   , /**< Keypad light index */
    MDL_GPD_FLASH_LIGHT , /**< Flash light index */
#ifdef __SUBBACKLIGHT_DRV__
    MDL_GPD_SUB_BL      , /**< Sub Backlight Index */
#endif
#ifdef __HALL_SWITCH_DRV__
    MDL_GPD_SUB_KPD_LIGHT    , /**< Sub keypad light index */
#endif
#ifdef __BREATHLIGHT_DRV__
    MDL_GPD_BREATHLIGHT ,    /**< breatlight index */
#endif
    MDL_GPD_BL_MAX           /**< Maximum Backlight index */
} MdlGpdBlId_e;

/**
 * @brief The enumeration defines the operations of vibrator, led, and backlight.
 */
typedef enum
{
    MDL_GPD_OP_OFF = 0,   /**< Turn off the device */
    MDL_GPD_OP_ON,        /**< Turn on the device */
    MDL_GPD_OP_DURATION,  /**< Switch device state in a duration */
    MDL_GPD_OP_MAX        /**< Invalid opration index */
} MdlGpdOp_e;

/**
 * @brief The enumeration defines the operations of G-sensor.
 */
typedef enum
{
    MDL_GPD_GSENSOR_OP_OFF = 0,        /**< Turn off G-sensor */
    MDL_GPD_GSENSOR_OP_ON,             /**< Turn on G-sensor */
    MDL_GPD_GSENSOR_OP_POLLING_TIME,   /**< Change G-sensor polling time */
    MDL_GPD_GSENSOR_OP_MAX             /**< Invalid opration index */
} MdlGpdGsensorOp_e;

/**
 * @brief The enumeration defines the plug accessory device type.
 */
typedef enum
{
    MDL_GPD_ACS_TYPE_HEADSET = 0,  /**< Headset accessory */
    MDL_GPD_ACS_TYPE_DATACABLE,    /**< USB Data cable */
    MDL_GPD_ACS_TYPE_MEMCARD,      /**< External memory card */
    #if defined(__DUAL_CARD__)
    MDL_GPD_ACS_TYPE_MEMCARD_2,    /**< External memory card 2 */
    #endif
    #if defined(__HALL_SWITCH_DRV__)
    MDL_GPD_ACS_TYPE_HALLSWITCH,   /**< Hall switch */
    #endif
    MDL_GPD_ACS_TYPE_FLIP,         /**< Flip / Slider */
    MDL_GPD_ACS_TYPE_MAX           /**< Number of accessory definition */
} MdlGpdAcsType_e;

/**
 * @brief The enumeration defines the service type.
 */
typedef enum
{
    MDL_GPD_SRV_TYPE_NAND = 0,  /**< NAND driver */
    MDL_GPD_SRV_TYPE_MAX        /**< Number of service definition */
} MdlGpdSrvType_e;

/**
 * @brief The enumeration defines the plug device status.
 */
typedef enum
{
    //MDL_GPD_DEV_POWER_TOUCHSCREEN = 0,    /**< Touch screen */
    MDL_GPD_DEV_POWER_FLIGHTMODE = 0,         /**< Flight mode */
    MDL_GPD_DEV_POWER_MAX                 /**< Number of device definition */
} MdlGpdDevPowerType_e;

/**
 * @brief The enumeration defines the plug device status.
 */
typedef enum
{
    MDL_GPD_DEV_VIBRATOR = 0,   /**< Vibrator */
    MDL_GPD_DEV_RGB_LED,        /**< RGB led */
    MDL_GPD_DEV_BACKLIGHT,      /**< LCD backlight */
    MDL_GPD_DEV_KPD_LIGHT,      /**< Keypad light */
#ifdef __FLASHLIGHT_DRV__
    MDL_GPD_DEV_FLASHLIGHT,     /**< Flashlight */
#endif
#ifdef __SUBBACKLIGHT_DRV__
    MDL_GPD_DEV_SUB_BACKLIGHT,
#endif
#ifdef __FILLLIGHT_DRV__
    MDL_GPD_DEV_FILL_LIGHT,     /**< Fill light */
#endif
#ifdef __HALL_SWITCH_DRV__
    MDL_GPD_DEV_SUB_KPD_LIGHT,    /**< Sub Keypad light */
#endif
#ifdef __BREATHLIGHT_DRV__
    MDL_GPD_DEV_BREATHLIGHT,    /**< breath light index */
#endif
    MDL_GPD_DEV_MAX             /**< Number of device definition */
} MdlGpdDevType_e;

/**
 * @brief The enumeration defines the plug device status.
 */
typedef enum
{
    MDL_GPD_ACS_STATUS_OUT,     /**< Accessory plug-out Status */
    MDL_GPD_ACS_STATUS_IN,      /**< Accessory plug-in Status */
    MDL_GPD_ACS_STATUS_UNKNOWN  /**< Accessory unknown Status */
} MdlGpdAcsStatus_e;


/**
 * @brief The enumeration defines the plug device status.
 */
typedef enum
{
    MDL_GPD_DEV_STATUS_OFF,     /**< Device off status */
    MDL_GPD_DEV_STATUS_ON,      /**< Device on status */
    MDL_GPD_DEV_STATUS_UNKNOWN  /**< Device unknown status */
} MdlGpdDevStatus_e;


/**
 * @brief The structure define the accessory info.
 */
typedef struct
{
    MdlGpdAcsType_e    eAcsType;     /**< Accessory type */
    MdlGpdAcsStatus_e  eAcsStatus;   /**< Accessory Status */
} MdlGpdAcsInfo_t;

/**
 * @brief The enumeration defines the power on cause.
 */
typedef enum
{
    MDL_GPD_PWR_ON_NONE = 0,            /**< #0 No power on cause */
    MDL_GPD_PWR_ON_NORMAL,              /**< #1 Normal power on */
    MDL_GPD_PWR_ON_CHARGER,             /**< #2 Charger power on */
    MDL_GPD_PWR_ON_ALARM,               /**< #3 Alarm power on */
    MDL_GPD_PWR_ON_RESET,               /**< #4 Watch dog reset */
    MDL_GPD_PWR_ON_TIMEEVT,             /**< #5 Minute event power on */
    MDL_GPD_PWR_ON_POWERCUT,            /**< #6 Power cut power on */
    MDL_GPD_PWR_ON_SWRESET,             /**< #7 Power cut power on */
    MDL_GPD_PWR_ON_NORMAL_KEY_RELEASE,  /**< #8 KEYON power on but not long press */
    MDL_GPD_PWR_ON_SIMRESET,            /**< #9 SIM reset (Sepcial Case)*/
    MDL_GPD_PWR_ON_MAX,                 /**< #10 Others */
} MdlGpdPwrOnCause_e;

/**
 * @brief The enumeration defines the system debug information type.
 */
typedef enum
{
    MDL_GPD_SYS_DBG_INFO_BACKTRACE = 0,
    MDL_GPD_SYS_DBG_INFO_STACK_PROFILE,
} MdlGpdSysDbgType_e;

/**
 * @brief The enumeration defines the version type.
 */
typedef enum
{
    MDL_GPD_VER_SW = 0,         /**< MStar software version */
    MDL_GPD_VER_CUST_SW,        /**< Customer software version */
    MDL_GPD_VER_M2_CHIP_ID,     /**< M2 chip id */
    MDL_GPD_VER_M2_ROM_CODE,    /**< M2 rom code version */
    MDL_GPD_VER_MAX
} MdlGpdVerType_e;

#ifndef __EXTEND_BREATHLIGHT_LED_DRV__
typedef struct
{
  u16  Time;  //ms
  u16  Level; // for RGBLED: 0xfff to 0x000, codeing in B:bit11:bit8 G:bit7:bit4 R:bit3:bit0, for KPD LED, DEV_LED_OFF or DEV_LED_ON, for BL DEV_ACC_BL_LEVEL0 to DEV_ACC_BL_LEVEL6
} MdlGpdLedPattern_t;
#else
/**
 * @brief The sturcture defines the pattern setting of vibrator, led, and backlight
 */
typedef struct
{
  u16  Time;  //ms
  u32  Level; // for external LED: 0xffff ffff to 0x0000 0000, there are 4 bits for each LED,  codeing in LED7:bit[31]:bit[28] ~ LED0:bit[3]:bit[0]
  u32  Level2; // for external LED: 0xffff ffff to 0x0000 0000, there are 4 bits for each LED,  codeing in LED15:bit[31]:bit[28] ~ LED8:bit[3]:bit[0]
} MdlGpdLedPattern_t;
#endif

/**
 * @brief The sturcture defines the return information of the vibrator
 */
typedef struct
{
    MdlGpdOp_e eOp;        /**< Vibration ON/OFF status */
} MdlGpdVibInfo_t;

/**
 * @brief The sturcture defines the return information of the LED
 */
typedef struct
{
    MdlGpdLedId_e    eLedId; /**< LED ID */
    MdlGpdOp_e       eOp;    /**< LED operation status */
} MdlGpdLedInfo_t;

/**
 * @brief The sturcture defines the return information of the backlight
 */
typedef struct
{
    MdlGpdBlId_e     eBlId;    /**< Main Backlight ID */
    u8               nBlLevel; /**< Backlight level */
} MdlGpdBlInfo_t;

/**
 * @brief The sturcture defines the duration setting of vibrator, led, and backlight
 */
typedef struct
{
    u32   nOnTime;     /**< Duration of the ON status */
    u32   nOffTime;    /**< Duration of the OFF status */
    u32   nCycle;      /**< Total cycles of the operation */
} MdlGpdDuration_t;

/**
 * @brief The sturcture defines the X-axis and Y-axis polling from G-sensor
 */
typedef struct
{
    u16   nPosX;        /**< X-axis data */
    u16   nPosY;        /**< Y-axis data */
    u16   nPosZ;        /**< Z-axis data, reserved */
} MdlGsensorNotifyInfo_t;

typedef struct
{
    u16 nAxisNum;         /**< Number of axis which g-sensor supported. */
    u16 nSensitiveLevel;  /**< G-sensor sensitive level. */
} MdlGsensorCapability_t;

/**
 * @brief The sturcture defines the return information of G-sensor
 */
typedef struct
{
    MdlGpdGsensorOp_e       eGsensorOp;           /**< G-sensor ON/OFF */
    u32                     nGsensorPollingTime;  /**< G-sensor polling time */
    MdlGsensorCapability_t  tGsensorCapability;   /**< G-sensor capability */
} MdlGpdGsensorInfo_t;


#ifdef __UPGRADE_NVRAM__
//#ifndef __SDK_SIMULATION__
/**
 *  @brief The structure defines the device information
 */
typedef enum {
  MDL_GPD_NVRAM_UPDATE_RO = 0,
  MDL_GPD_NVRAM_UPDATE_RW,
  MDL_GPD_NVRAM_BACKUP_RO,
  MDL_GPD_NVRAM_RESTORE_RO,
  MDL_GPD_NVRAM_RW_RESTORE_NAND_FLASH,
  MDL_GPD_NVRAM_RW_RESTORE_CIS,
  MDL_GPD_NVRAM_UPDATE_INVAID =0xFFFF
}MdlGpdNvramType_e;

typedef enum {
  MDL_GPD_NVRAM_RW_RESTORE_OK = 0,
  MDL_GPD_NVRAM_RW_RESTORE_FAIL,
  MDL_GPD_NVRAM_RW_RESTORE_MEMORY_ALLOCATION_FAIL,
  MDL_GPD_NVRAM_CAUSE_INVAID =0xFFFF
}MdlGpdNvramCause_e;

/**
 * @brief The structure defines the return information of Nvram
 */
typedef struct
{
    MdlGpdNvramType_e       eNvramType;
    u8                     	*pAddr;
    u16                     nLen;
} MdlGpdNvramInfo_t;


/**
 * @brief The structure defines the IT test content of Nvram
 */
#ifdef __UPGRADE_NVRAM_ENHANCED_TEST_ONLY__
typedef struct
{
    u16 type;  /* 0 for RO, 1 for RW */
    u16 backup; /* 0 for NAND, 1 for CIS */
    u32 offset; /*the offset from the top of NAND/CIS paritition*/
    u32 length; /*the length of data*/
    u8  data[16]; /*new data to overwirte*/
} MdlGpdNvramITContent_t;
#endif  // __UPGRADE_NVRAM_ENHANCED_TEST_ONLY__
//#endif
#endif  // __UPGRADE_NVRAM__

/**
 * @brief The structure defines the return information of per task stack profile information
 */
typedef enum
{
	// Normal task stack
	MDL_GPD_TASK_TYPE_SYS,
	MDL_GPD_TASK_TYPE_CUS,
	MDL_GPD_TASK_TYPE_DYNA,
	// Specail task stack
	MDL_GPD_TASK_TYPE_FIQ,
	MDL_GPD_TASK_TYPE_IRQ,
	MDL_GPD_TASK_TYPE_MARKER,
} MdlGpdTaskType_e;

typedef struct
{
	u8					Id;
    char 				TaskName[8];
	MdlGpdTaskType_e	Type;
	void*				TopOfStack;
 	u16					StackSize;
	u32					MaxUsage;
} MdlGpdTaskStkUsag_t;

typedef struct
{
    u32                     nMax;
    u32                     nTotalQueried;
    MdlGpdTaskStkUsag_t     *pInfo;
} MdlGpdSysStkUsgInfo_t;

/**
 * @brief The sturcture defines the return information of General Peripheral Device service
 */
typedef struct
{
    union
    {
        MdlGpdVibInfo_t      tVibInfo;    /**< Vibrator return information */
        MdlGpdLedInfo_t      tLedInfo;    /**< LED return information */
        MdlGpdBlInfo_t       tBlInfo;     /**< Main backlight return information */
        MdlGpdGsensorInfo_t  tGsensorInfo;  /**< G-sensor return information */
#ifdef __UPGRADE_NVRAM__
#ifdef __UPGRADE_NVRAM_ENHANCED__
        MdlGpdNvramInfo_t    tNvramInfo;  /**< Nvram return information */
#endif  // __UPGRADE_NVRAM_ENHANCED__
#endif  // __UPGRADE_NVRAM__
		MdlGpdSysStkUsgInfo_t tSysStkUsg;
    } param;
} MdlGpdInfo_t;

/**
 * @brief Call back function, Application needs to provide the function entry
 *
 * @param senderID      : Sender task ID
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param errCode       : The error return by Multimedia task to know process success or fail.
 * @param pGpdInfo      : Callback information return by General Peripheral Device
 *
 * @return None
 */
typedef void (*PfnMdlGpdCb)(u16 nSenderID, u32 nUserValue, MdlGpdErrCode_e eErrCode, MdlGpdInfo_t *ptGpdInfo);

/**
 * @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID      : Sender task id.
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param pPlugInfo     : Notification value return by General Peripheral Device.
 *
 * @return None
 */
typedef void (*PfnMdlGpdAcsNotifyCb)(u16 nSenderID, u32 nUserValue, MdlGpdAcsInfo_t *ptAcsInfo);

/**
 * @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID               : Sender task id.
 * @param userValue              : Reference value for indicating different sender in same task or check msg response.
 * @param pGpdGsensorNotifyInfo  : Notification value return by G-sensor.
 *
 * @return None
 */
typedef void (*PfnMdlGsensorNotifyCb)(u16 nSenderID, u32 nUserValue, MdlGsensorNotifyInfo_t *ptGsensorNotifyInfo);

/**
 * @brief Call back function, Service need to provide the function entity and return service ON/OFF status.
 *
 * @param none
 *
 * @return TRUE  : Service ON status
 *         FALSE : Service OFF status
 */
typedef bool (*PfnMdlGpdSrvCb)(void);

/**
 * @brief The General Peripheral Device call back function structure definition
 */
typedef struct
{
    u16        senderID;    /**< Sender task ID */
    u32        userValue;   /**< Reference value for indicating different sender in same task or check msg response. */
    PfnMdlGpdCb  pfnCb;       /**< Call back function that called by GPD task after process finished. */
} MdlGpdCb_t;

/**
 *  @brief Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct
{
    u16                   senderID;    /**< Sender ID */
    u32                   userValue;   /**< Reference value for indicating different sender in same task or check msg response. */
    PfnMdlGpdAcsNotifyCb  pfnNotifyCb; /**< Notification call back function that called by Media task after receiving the notification. */
} MdlGpdAcsNotifyCb_t;

/**
 *  @brief G-sensor Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct
{
    u16                    senderID;    /**< Sender ID */
    u32                    userValue;   /**< Reference value for indicating different sender in same task or check msg response. */
    PfnMdlGsensorNotifyCb  pfnNotifyCb; /**< Notification call back function that called by Media task after receiving the notification. */
} MdlGsensorNotifyCb_t;

/**
 *  @brief Callback informatoin structure for service ON/OFF status.
 */
typedef struct
{
    u16                   senderID;    /**< Sender ID */
    u32                   userValue;   /**< Reference value for indicating different sender in same task or check msg response. */
    PfnMdlGpdSrvCb        pfnCb;       /**< Call back function that called when system want to sleep. */
} MdlGpdSrvCb_t;

#ifdef __PROXIMITY_SENSOR_DRV__

/**
 * @brief The enumeration defines proximity sensor status.
 */
typedef enum
{
    MDL_PROXIMITY_SENSOR_STATUS_OFF,         /**< Proximity sensor OFF Status */
    MDL_PROXIMITY_SENSOR_STATUS_EMMITER_ON,  /**< Proximity sensor emmiter ON Status */
    MDL_PROXIMITY_SENSOR_STATUS_ON,          /**< Proximity sensor ON Status */
    MDL_PROXIMITY_SENSOR_STATUS_UNKNOWN      /**< G-sensor unknown Status */
} MdlProximitySensorStatus_e;

/**
 * @brief The enumeration defines the operations of Proximity sensor.
 */
typedef enum
{
    MDL_PROXIMITY_SENSOR_OP_OFF = 0,        /**< Turn off Proximity sensor */
    MDL_PROXIMITY_SENSOR_OP_ON,             /**< Turn on Proximity sensor */
    MDL_PROXIMITY_SENSOR_OP_POLLING_TIME,   /**< Change Proximity sensor polling time */
    MDL_PROXIMITY_SENSOR_OP_MAX             /**< Invalid opration index */
} MdlProximitySensorOp_e;

/**
 * @brief The sturcture defines the indicator from Proximity sensor
 */
typedef struct
{
    u16 nIndicator;
    u16 dataL;      /**< data--L thro */
    u16 dataH;      /**< data--H thro */
    u16 op_flag;    /*1:intp on; 0:intp off*/
} MdlProximitySensorNotifyInfo_t;

/**
 * @brief Notification Call back function, MMI need to provide the function entity
 *
 * @param senderID               : Sender task id.
 * @param userValue              : Reference value for indicating different sender in same task or check msg response.
 * @param pGpdGsensorNotifyInfo  : Notification value return by G-sensor.
 *
 * @return None
 */
typedef void (*PfnMdlProximitySensorNotifyCb)(u16 nSenderID, u32 nUserValue, MdlProximitySensorNotifyInfo_t *ptNotifyInfo);

/**
 *  @brief Proximity Sensor Notification callback informatoin structure supported for application layer (MMI)
 */
typedef struct
{
    u16                            senderID;    /**< Sender ID */
    u32                            userValue;   /**< Reference value for indicating different sender in same task or check msg response. */
    PfnMdlProximitySensorNotifyCb  pfnNotifyCb; /**< Notification call back function that called by Media task after receiving the notification. */
} MdlProximitySensorNotifyCb_t;
#endif

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Set vibrator level, called before switch on vibrator (MdlGpdVibratorSwitchReq).
 *
 * @param nLevel                        : Level of vibrator level(level: 1-12, 0xFF means use default setting in cust_pwm_xxxx.c)
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdVibratorSetLevelReq(u8 nLevel, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Switch vibrator
 *
 * @param eOperation                    : Switch on, off, or periodically
 * @param ptDurSetting                  : If Operation is MDL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdVibratorSwitchReq(MdlGpdOp_e eOperation, MdlGpdDuration_t *ptDurSetting, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Switch led
 *
 * @param eLedId                        : LED ID
 * @param eOperation                    : Switch on, off, or periodically
 * @param ptDurSetting                  : If Operation is MDL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdLedSwitchReq(MdlGpdLedId_e eLedId, MdlGpdOp_e eOperation, MdlGpdDuration_t *ptDurSetting, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Switch backlight
 *
 * @param eBlId                         : Backlight ID
 * @param nRange                        : Maximum range of the brightness
 * @param nLevel                        : nLevel of the brightness
 * @param ptDurSetting                  : If user want to switch brightness periodically, user should provide the duration setting. Otherwise, it shell be NULL.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdBacklightSwitchReq(MdlGpdBlId_e eBlId, u8 nRange, u8 nLevel, MdlGpdDuration_t *ptDurSetting, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Start backlight flash
 *
 * @param eBlId                         : Backlight ID
 * @param nRange                        : Maximum range of the brightness
 * @param nUpLevel                      : Up level of the backlight flash
 * @param nDownLevel                    : Down level of the backlight flash
 * @param ptDurSetting                  : If user want to switch brightness periodically, user should provide the duration setting. Otherwise, it shell be NULL.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdStartBacklightFlashReq(MdlGpdBlId_e eBlId, u8 nRange, u8 nUpLevel, u8 nDownLevel, MdlGpdDuration_t *ptDurSetting, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Stop backlight flash
 *
 * @param eBlId                         : Backlight ID
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdStopBacklightFlashReq(MdlGpdBlId_e eBlId, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Switch G-sensor
 *
 * @param eOperation                    : Switch on, off
 * @param nPollingTime                  : Set the polling speed for G-sensor data. It should not less than 100 ms.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdGsensorSwitchReq(MdlGpdGsensorOp_e eOperation, u32 nPollingTime, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Get plug device status
 *
 * @param eAcsType                      : Device type
 * @param peAcsStatus                   : [out] Current status of the accessory
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdGetAcsStatusReq(MdlGpdAcsType_e eAcsType, MdlGpdAcsStatus_e *peAcsStatus);


/**
 * @brief Get device status
 *
 * @param eDevType                      : Device type
 * @param peDevStatus                   : [out] Current status of the device
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdGetDevStatusReq(MdlGpdDevType_e eDevType, MdlGpdDevStatus_e *peDevStatus);


/**
 * @brief Register notification for plug device. MMI will receive the notification if device status change.
 *
 * @param eAcsType                      : Device type
 * @param tNotifyCb                     : Notification for device status change
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdRegAcsNodifyReq(MdlGpdAcsType_e eAcsType, MdlGpdAcsNotifyCb_t tNotifyCb, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Register notification for G-sensor. MMI will receive the notification when polling timer time's up.
 *
 * @param tNotifyCb                     : Notification for G-sensor status change
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdRegGsensorNodifyReq(MdlGsensorNotifyCb_t tNotifyCb, MdlGpdCb_t *ptGpdCb);


/**
 * @brief Get the power on cause.
 *
 * @param  pePwrOnCause                 : [out] Power on cause
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdPowerOnCauseReq(MdlGpdPwrOnCause_e *pePwrOnCause);


/**
 * @brief Get the version.
 *
 * @param  eVerType                     : Version type
 * @param  pVersion                     : [out] Version string
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdGetVersionReq(MdlGpdVerType_e eVerType, char *pVersion);

/**
 * @brief  switch flashlight
 *
 * @param eOperation                    : on/off
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
#ifdef __FLASHLIGHT_DRV__
MdlGpdErrCode_e MdlGpdFlashlightSwitchReq(MdlGpdOp_e eOperation);
#endif

#ifdef __FILLLIGHT_DRV__
/**
 * @brief  switch Fill light
 *
 * @param eOperation                    : on/off
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdFilllightSwitchReq(MdlGpdOp_e eOperation);
#endif

/**
 * @brief Switch device power for MMI use case.
 *
 * @param eDevPowerType                 : Device power which need to switch for MMI use case.
 * @param eOperation                    : Switch on, off device power. Not periodically.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdDevicePowerSwitchReq(MdlGpdDevPowerType_e eDevPowerType, MdlGpdOp_e eOperation, MdlGpdCb_t *ptGpdCb);



/**
 * @brief  This function is used to set backlight flash
 *
 * @param  eBlId                        : Backlight id
 * @param  nRange                       : Backlight range
 * @param  Level_1                      : Backlight level 1
 * @param  nLevel_2                     : Backlight level 2
 * @param  ptDurSetting                 : Duration setting
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdBacklightFlashReq(MdlGpdBlId_e eBlId, u8 nRange, u8 nLevel_1, u8 nLevel_2, MdlGpdDuration_t *ptDurSetting);


/**
 * @brief  This function is used to restore backlight
 *
 * @param  eBlId                        : Backlight id
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdBacklightRestoreReq(MdlGpdBlId_e eBlId);


/**
 * @brief  This function is used to indicate GPD the accessory status
 *
 * @param  eAcsType                     : Accessory type
 * @param  eAcsStatus                   : Accessory status
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdAcsIndicationReq(MdlGpdAcsType_e eAcsType, MdlGpdAcsStatus_e eAcsStatus);


/**
 * @brief  This function is used to indicate GPD the hook key status change
 *
 * @param                               : NONE
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdHeadsetHookIndicationReq(void);


/**
 * @brief  This function is used to request backtrace
 *
 * @param                               : NONE
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdRequestBacktraceReq(void);

/**
 * @brief  This function is used to request stack profile result
 *
 * @param pInfo                         : [OUT]return per stack profile info
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return MDL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdRequestStackProfileInfoReq(MdlGpdSysStkUsgInfo_t* pInfo);

/**
 * @brief  This function is used to request lcd info
 *
 * @param                               : NONE
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdInfoLcdReq(u32 Port);


/**
 * @brief  This function is used to set device on/off flag and enable/diable sleep mode
 *
 * @param                               : NONE
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdSetDeviceOnOffReq(MdlGpdDevice_e eDevice, bool bIsON, bool bIsSync);


/**
 * @brief  This function is used to indicate GPD the memory card status
 *
 * @param  bIsIN : Memory card status. TRUE - IN,   FALSE - OUT
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdMemCardIndicationReq(bool bIsIN);


/**
 * @brief  This function is used to indicate GPD the data cable status
 *
 * @param  bIsIN : Data cable status. TRUE - IN,   FALSE - OUT
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdDataCableIndicationReq(bool bIsIN);


/**
 * @brief  This function is used to get memory card status
 *
 * @param  pbIsIN : [OUT] Memory card status. TRUE - IN,   FALSE - OUT
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdIsMemCardInReq(bool *pbIsIN);


#ifndef __SDK_SIMULATION__
#ifdef __UPGRADE_NVRAM__
/**
 * @brief  This function is used to update NVRAM data
 *
 * @param
 *
 * @return MDL_GPD_OK                   : Function request success
 * @return ISL_GPD_FAIL                 : Function request fail
 * @return MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @return MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @return ISL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @return ISL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 */
MdlGpdErrCode_e MdlGpdNvramUpdateReq(MdlGpdNvramType_e eNvramType, u8 *pAddr, u32 nLen, MdlGpdCb_t *ptGpdCb);
#ifdef __UPGRADE_NVRAM_ENHANCED__
MdlGpdErrCode_e MdlGpdNvramRWRestoreReq(MdlGpdNvramType_e eNvramType, MdlGpdCb_t *ptGpdCb);
MdlGpdErrCode_e MdlGpdNvramRWRestoreCmp(MdlGpdNvramType_e eNvramType, MdlGpdNvramCause_e causeValue, u16 nLen, u8* pAddr, u16 nUpdateLen, u8* pUpdateAddr, MdlGpdCb_t *ptGpdCb);

#ifdef __UPGRADE_NVRAM_ENHANCED_TEST_ONLY__
MdlGpdErrCode_e MdlGpdNvramITModifyReq(MdlGpdNvramITContent_t *tNvramITContent, MdlGpdCb_t *ptGpdCb);
#endif //__UPGRADE_NVRAM_ENHANCED_TEST_ONLY__

#endif //__UPGRADE_NVRAM_ENHANCED__
MdlGpdErrCode_e MdlGpdNvramBackupReq(MdlGpdNvramType_e eNvramType, u8 *pAddr, u32 nLen, MdlGpdCb_t *ptGpdCb);
#endif  // __UPGRADE_NVRAM__
#endif  // !__SDK_SIMULATION__


#if defined(__BREATHLIGHT_DRV__)
/**
 * @brief Device ctrl with pattern
 *
 * @param DevType                       : Device type
 * @param Operation                     : Switch on, off, or periodically
 * @param pLedPattern                   : Switch pattern
 * @param Cycle                         : Repeate times
 * @param pGpdCb                        : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval ESL_GPD_OK                   : Function open request success
 * @retval ESL_GPD_FAIL                 : Function open request fail
 * @retval ESL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval ESL_GPD_MEM_ALLOC_ERROR	    : Can't allocate available memory from OS
 * @retval ESL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval ESL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval ESL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlGpdDevPatternSwitcReq(MdlGpdDevType_e DevType, MdlGpdOp_e Operation, MdlGpdLedPattern_t *pLedPattern, u16 Cycle, MdlGpdCb_t *ptGpdCb);
#endif

#ifdef __PROXIMITY_SENSOR_DRV__
/**
 * @brief Register notification for proximity sensor. MMI will receive the notification when polling timer time's up.
 *
 * @param tNotifyCb                     : Notification for G-sensor status change
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlProximitySensorRegNodifyReq(MdlProximitySensorNotifyCb_t tNotifyCb, MdlGpdCb_t *ptGpdCb);

/**
 * @brief Switch proximity sensosor
 *
 * @param eOperation                    : Switch on, off
 * @param nPollingTime                  : Set the polling speed for G-sensor data. It should not less than 100 ms.
 * @param ptGpdCb                       : Call back struct pointer, include sender ID, userValue and call back function.
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 * @retval MDL_GPD_PARAM_ERROR          : Incorrect parameter setting
 * @retval MDL_GPD_MEM_ALLOC_ERROR      : Can't allocate available memory from OS
 * @retval MDL_GPD_REJECT               : Request rejected becuase of other function's confliction
 * @retval MDL_GPD_ABORT                : Request aborted becuase of incorrect sequence
 * @retval MDL_GPD_TIMEOUT              : Request no response timeout, this error is returned by call back function
 */
MdlGpdErrCode_e MdlProximitySensorSwitchReq(MdlProximitySensorOp_e eOperation, u32 nPollingTime, MdlGpdCb_t *ptGpdCb);

/**
 * @brief Probe proximity sensosor
 *
 * @param NONE
 *
 * @retval MDL_GPD_OK                   : Function open request success
 * @retval MDL_GPD_FAIL                 : Function open request fail
 */
MdlGpdErrCode_e MdlPaiSensorProbe(void);


#endif

#endif /* __MDL_GPD_PUB_H__ */

