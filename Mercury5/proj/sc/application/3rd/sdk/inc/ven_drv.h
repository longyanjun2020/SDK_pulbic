/**
 *
 * @file    ven_drv.h
 * @brief   This file defines accessory interface
 *
 * @author  Ian-Y.Chen
 * @version $Id: ven_drv.h 47407 2009-12-31 09:35:13Z steve.lee $
 *
 */
#ifndef __VEN_DRV_H__
#define __VEN_DRV_H__


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

enum
{
    VEN_DRV_RET_SUCCESS,                 ///< operation completed successfully
    VEN_DRV_RET_BAD_PARAM,               ///< invalid input parameters
    VEN_DRV_RET_OUT_OF_MEMORY,           ///< memory is not enough to complete the operation
    VEN_DRV_RET_OPERATION_CANCELED,      ///< operation is canceled due to interruption
    VEN_DRV_RET_TIMEOUT,                 ///< for dialog with duration assigned
    VEN_DRV_RET_ALL_SLOT_OCCUPIED,       ///< All statusbar icon slot occupied and not available
    VEN_DRV_RET_FAILED,                  ///< unknown error
    VEN_DRV_RET_NOT_SUPPORT,             ///< Not support now
    VEN_DRV_RET_NOT_ALLOWED              ///Operation not allowed
};
typedef u32 ven_drv_ret_t;

enum
{
    VEN_DRV_ACS_TYPE_HEADSET = 0x01,     ///< headset
    VEN_DRV_ACS_TYPE_MEMCARD = 0x02,    ///< memory card
    #if defined(__DUAL_CARD__)
    VEN_DRV_ACS_TYPE_MEMCARD_2 = 0x03,    ///< memory card 2
    #endif
};
typedef u32 ven_DrvAcsType_t;

enum
{
    VEN_DRV_ACS_STATUS_OUT,
    VEN_DRV_ACS_STATUS_IN,
    VEN_DRV_ACS_STATUS_KNOWN
};
typedef u32 ven_DrvAcsStatus_t;

typedef struct
{
    ven_DrvAcsType_t VenAcsType;
    ven_DrvAcsStatus_t VenAcsStatus;
} ven_DrvAcsInfo_t;

enum
{
    VEN_DRV_USB_TYPE_NONE = 0,
    VEN_DRV_USB_TYPE_UNKNOW,
    VEN_DRV_USB_TYPE_CDC,    ///< Communication Device Class (Modem virtual COM port)
    VEN_DRV_USB_TYPE_MSC,    ///< Mass Storage Device Class
    VEN_DRV_USB_TYPE_MTP,    ///< Media Transfer Protocol
    VEN_DRV_USB_TYPE_PBD,    ///< Picture Bridge Device
    VEN_DRV_USB_TYPE_VDC,    ///< Video Class used for PC camera service
    VEN_DRV_USB_TYPE_OTG,    ///< OTG Host
};
typedef u32 ven_DrvUsbType_t;

enum
{
	VEN_DRV_USB_STATUS_OUT = 0,
	VEN_DRV_USB_STATUS_IN,
	VEN_DRV_USB_STATUS_KNOWN,
};
typedef u32 ven_DrvUsbStatus_t;

typedef struct
{
	ven_DrvUsbType_t VenUsbType;
	ven_DrvUsbStatus_t VenUsbStatus;
}ven_DrvUsbInfo_t;

typedef void (*ven_drv_acs_callback)(ven_DrvAcsInfo_t *pAcsInfo);
typedef void (*ven_drv_usb_callback)(ven_DrvUsbInfo_t *pUsbInfo);

typedef enum {
  VEN_DRV_BACKLIGHT_STATUS_OFF,     /**< Device off status */
  VEN_DRV_BACKLIGHT_STATUS_ON,      /**< Device on status */
  VEN_DRV_BACKLIGHT_STATUS_UNKNOWN  /**< Device unknown status */
} ven_DrvDevStatus_e;
typedef u32 ven_DrvBacklightStatus_t;
typedef struct
{
    ven_DrvBacklightStatus_t VenBacklightStatus;
    void *pData;
}ven_DrvBacklightInfo_t;
typedef void (*ven_drv_backlight_callback)(ven_DrvBacklightInfo_t *pBacklightInfo);




#define VEN_DRV_STORAGE_CID_REG_SIZE            (16)      /* 126 bits */
#define VEN_DRV_STORAGE_VFS_NO_ERROR            ( 1)
#define VEN_DRV_STORAGE_VFS_ERROR               ( 0)
typedef enum
{
  VEN_DRV_STG_VOL_NOR = 0,
  VEN_DRV_STG_VOL_SD,
  VEN_DRV_STG_VOL_NAND,
  VEN_DRV_STG_VOL_SD2,
  VEN_DRV_STG_VOL_MAX
} ven_DrvStorageVolType_e;

typedef struct
{
  u8 cidReg[VEN_DRV_STORAGE_CID_REG_SIZE];                /* 128 bits */
}ven_DrvStorageSerial_t;

enum{
    VEN_DRV_BACKLIGHT_CB_TYPE_VENDOR = 0,
    VEN_DRV_BACKLIGHT_CB_TYPE_GPS,
    VEN_DRV_BACKLIGHT_CB_TYPE_SIZE,
};
typedef u32 ven_DrvBacklightCbType_t;

enum
{
    VEN_USB_STATUS_NONE
   ,/**< USB cable not connect. */
    VEN_USB_STATUS_UNKNOWN
   ,/**< USB cable not check yet (but connect). */
    VEN_USB_STATUS_PCHOST
   ,/**< USB cable attached for PC host */
    VEN_USB_STATUS_CHARGING
   ,/**< USB cable is for charging only */
    VEN_USB_STATUS_PCHOST_CDC_MODEM
   ,/**< USB cable is for Communication Modem Device */
    VEN_USB_STATUS_PCHOST_CDC_SYNCTOOL
   ,/**< USB cable is for Communication Sync tool Device */
    VEN_USB_STATUS_PCHOST_CDC_TRACE
   ,/**< USB cable is for Communication Trace Device */
    VEN_USB_STATUS_PCHOST_MSC
   ,/**< USB cable is for Mass Storage */
    VEN_USB_STATUS_PCHOST_VDC
   ,/**< USB cable is for Webcam */
    VEN_USB_STATUS_VBUS_USB_IN
   ,/* For dual charger, to notify USB IN */
    VEN_USB_STATUS_VBUS_USB_OUT
    /* For dual charger, to notify USB IN */
};
typedef u32 ven_usb_status_e;

typedef enum
{
    VEN_DRV_BAT_DUMMY_LEVEL = -3,   ///< dummy value
    VEN_DRV_BAT_TOO_LOW_FOR_COMM,   ///< lowest level
    VEN_DRV_BAT_LOW_BATTERY,        ///< low battery
    VEN_DRV_BAT_LEVEL_0,            ///< level 0
    VEN_DRV_BAT_LEVEL_1,            ///< level 1
    VEN_DRV_BAT_LEVEL_2,            ///< level 2
    VEN_DRV_BAT_LEVEL_3,            ///< level 3
    VEN_DRV_BAT_LEVEL_4,            ///< level 4 (battery full)
} ven_DrvBatLevel_t;

typedef enum
{
    VEN_DRV_BAT_MASTER=1,
    VEN_DRV_BAT_SLAVE,
    VEN_DRV_BAT_BOTH_MASTER_SUPPLY,
    VEN_DRV_BAT_BOTH_SLAVE_SUPPLY=7,
    VEN_DRV_BAT_NULL,
} ven_DrvBatID_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Start backlight flash
 *
 * @param duration      : Flash duration (mini-second)
 *
 * @retval 1            : Success
 * @retval 0            : Fail
 */
extern s32 ven_drv_startBacklightFlash(u32 duration);

/**
 * @brief Stop backlight flash
 *
 * @param None
 *
 * @retval 1            : Success
 * @retval 0            : Fail
 */
extern s32 ven_drv_stopBacklightFlash(void);

/**
 * @brief Set backlight brightness
 *
 * @param range         : range of the brightness
 * @param level         : level of the brightness. If level = 0, it turns off the backlight.
 *
 * @retval 1            : Success
 * @retval 0            : Fail
 */
extern s32 ven_drv_setBacklight(u8 range, u8 level);

/**
 * @brief Start vibration
 *
 * @param duration      : Vibration duration (mini-second)
 *
 * @retval 1            : Success
 * @retval 0            : Fail
 */
extern s32 ven_drv_startVibration(u32 duration);

/**
 * @brief Stop vibration
 *
 * @param None
 *
 * @retval 1            : Success
 * @retval 0            : Fail
 */
extern s32 ven_drv_stopVibration(void);
/**
 * ven_drv_getBacklightStatus
 *
 * @brief get backlight status
 *
 * @param pStatus[out]  : Status On/Off/Unknown
 *
 * @retval 1            : Success
 * @retval 0            : Fail
 */
s32 ven_drv_getBacklightStatus(ven_DrvDevStatus_e *pStatus);

/**
 *  ven_drv_subscribeAcs
 *
 *  @brief  This function subscribes to SDK for accessory changes
 *
 *  @param  SdkHandle   [in]Handle of SDK
 *  @param  AcsTypes   [in]Types of accessory to listen to. use | to combine more than 1 accessory type
 *  @param  pCB   [in]Pointer to ven_drv_acs_callback structure
 *
 *  @retval 1      success
 *  @retval 0      failed
 */
extern s32 ven_drv_subscribeAcs(u32 SdkHandle, ven_DrvAcsType_t AcsTypes, ven_drv_acs_callback pCB);

/**
 *  ven_drv_unsubscribeAcs
 *
 *  @brief  This function unsubscribes accessory changes
 *
 *  @param  SdkHandle   [in]Handle of SDK
 *
 *  @retval 1      success
 *  @retval 0      failed
 */
extern s32 ven_drv_unsubscribeAcs(u32 SdkHandle);

/**
 *  ven_drv_getAcsStatus
 *
 *  @brief  This function gets current accessory status
 *
 *  @param  AcsType   [in]Accessory type
 *  @param  pAcsStatus   [out]Pointer to memory to store status of the given accessory type
 *
 *  @retval 1      success
 *  @retval 0      failed
 */
extern s32 ven_drv_getAcsStatus(ven_DrvAcsType_t AcsType, ven_DrvAcsStatus_t *pAcsStatus);

/**
 *  ven_drv_getBatPercentage
 *
 *  @brief  This function gets current battery capacity in percentage
 *
 *  @param  None
 *
 *  @retval 0~100 (percentage)
 */
extern s8 ven_drv_getBatPercentage(void);

/**
 *  ven_drv_subscribeUsb
 *
 *  @brief  This function subscribes to SDK for USB changes
 *
 *  @param  SdkHandle   [in]Handle of SDK
  *  @param  pCB   [in]Pointer to ven_drv_usb_callback structure
 *
 *  @retval 1      success
 *  @retval 0      failed
 */
extern s32 ven_drv_subscribeUsb(u32 SdkHandle, ven_drv_usb_callback pCB);

/**
 *  ven_drv_unsubscribeUsb
 *
 *  @brief  This function unsubscribes USB changes
 *
 *  @param  SdkHandle   [in]Handle of SDK
 *
 *  @retval 1      success
 *  @retval 0      failed
 */
extern s32 ven_drv_unsubscribeUsb(u32 SdkHandle);



/**
 * @brief Get T Card Serial number form VFS api ,
 * @brief if SerialBufSize is smaller than VEN_DRV_STORAGE_CID_REG_SIZE, bytes of SerialBufSize will be assigned.
 *
 * @param eStorageType  : Storage Type
 * @param pSerialNumBuf : Buffer of SerialNumber
 * @param SerialBufSize : indicate the size of pSerialNumBuf , the size should be VEN_DRV_STORAGE_CID_REG_SIZE
 *
 * @retval 0            : Fail
 * @retval others       : Success
 */
extern s32 ven_drv_getStorageSerialNumber(ven_DrvStorageVolType_e eStorageType, u8* pSerialNumBuf, u32 SerialBufSize );

/**
 *  ven_drv_subscribeBacklight
 *
 *  @brief  This function subscribes to SDK for backlight changes
 *
 *  @param  SdkHandle   [in]Handle of SDK
 *  @param  pCB   [in]Pointer to ven_drv_subscribeBacklight structure
 *
 *  @retval VEN_DRV_RET_SUCCESS      success
 *  @retval others                   failed
 */
extern ven_drv_ret_t ven_drv_subscribeBacklight(u32 SdkHandle, ven_drv_backlight_callback pCB);

/**
 *  ven_drv_unsubscribeBacklight
 *
 *  @brief  This function unsubscribes backlight changes
 *
 *  @param  SdkHandle   [in]Handle of SDK
 *
 *  @retval VEN_DRV_RET_SUCCESS      success
 *  @retval others                   failed
 */
extern ven_drv_ret_t ven_drv_unsubscribeBacklight(u32 SdkHandle);

/**
 *  ven_drv_getUsbStatus
 *
 *  @brief  This function gets usb status.
 *          Only support synchronous now.
 *
 *  @param  SdkHandle       [in]handle of sdk
 *  @param  pUsbStatus      [in]Point to UsbStatus
 *
 *  @retval 0 for failed, 1 for success.
 */
s32 ven_drv_getUsbStatus(u32 SdkHandle, ven_usb_status_e *pUsbStatus);

/**
 *  ven_drv_isBatCharging
 *
 *  @brief  This function checks whether battery is charging.
 *          Only support synchronous now.
 *
 *  @retval TRUE for yes, FALSE for no.
 */
bool ven_drv_isBatCharging(void);

/**
 *  ven_drv_getBatLevel
 *
 *  @brief  This function checks whether battery charger is plugged.
 *          Only support synchronous now.
 *
 *  @retval TRUE for yes, FALSE for no.
 */
bool ven_drv_isBatChargerPlugged(void);

/**
 *  ven_drv_getBatLevel
 *
 *  @brief  This function gets battery level.
 *          Only support synchronous now.
 *
 *  @param  BatID      [in]battery ID
 *
 *  @retval ven_DrvBatLevel_t
 */
s8 ven_drv_getBatLevel(ven_DrvBatID_t BatID);

#endif /*__VEN_DRV_H__*/
