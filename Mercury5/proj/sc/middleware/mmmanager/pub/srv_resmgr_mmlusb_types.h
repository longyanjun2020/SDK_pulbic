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
* @file    srv_resmgr_mmlusb_types.h
* @version
* @brief
*
*/

#ifndef __SRV_RESMGR_MMLUSB_TYPES_H__
#define __SRV_RESMGR_MMLUSB_TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined (__SDK_SIMULATION__)
#define __packed
#endif

/** @defgroup MMLayerUsb USB
    Mass Storage, Virtual COM, Modem, PC-Cam, Picture Bridge
    @{
*/
    /** @defgroup MMLayerUsbMassStorage Mass Storage
        Mass Storage
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbVirtualCom Virtual COM
        Virtual COM
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbModem Modem
        Modem
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbPCCam PC-Cam
        PC-Cam
        @{
    */
    /** @} */

    /** @defgroup MMLayerUsbPicBridge Picture Bridge
        Picture Bridge
        @{
    */
    /** @} */

/** @} */

/*=============================================================*/
// Include files
/*=============================================================*/
#include "srv_resmgr_mml_forward.h"
#include "vm_types.ht"
#include "srv_resmgr_mmlcommon_types.h"
#include "srv_resmgr_mmlimage_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/** @ingroup    MMLayerUsb
    @brief      Use case IDs
*/
opaque_enum(MmlUseCaseUsbId_e_)
{
    /* Usb Init */
    MML_UCID_USB_INIT_BASE = MML_GET_UCID_INIT_BASE(MML_UCGID_USB),
    MML_UCID_USB_REG_NOTIFY_CALLBACK = MML_UCID_USB_INIT_BASE,           ///< 00060000 = Reg notify callback
    MML_UCID_USB_UNREG_NOTIFY_CALLBACK,                                  ///< 00060001 = Unreg notify callback
    MML_UCID_USB_INIT_CATEGORY,

    /* Usb Get */
    MML_UCID_USB_GET_BASE = MML_GET_UCID_GET_BASE(MML_UCGID_USB),
    MML_UCID_USB_GET_USB_STATUS = MML_UCID_USB_GET_BASE,                 ///< 00060100 = Get USB status
    MML_UCID_USB_GET_CATEGORY,

    /* Usb Set */
    MML_UCID_USB_SET_BASE = MML_GET_UCID_SET_BASE(MML_UCGID_USB),
    MML_UCID_USB_SET_CATEGORY,

    /* Usb Execute */
    MML_UCID_USB_EXECUTE_BASE = MML_GET_UCID_EXE_BASE(MML_UCGID_USB),
    MML_UCID_USB_OPEN_USB = MML_UCID_USB_EXECUTE_BASE,                   ///< 00060300 = Open USB
    MML_UCID_USB_CLOSE_USB,                                              ///< 00060301 = Close USB
    MML_UCID_USB_START_PICTURE_BRIDGE_JOB,                               ///< 00060302 = Start picture bridge job
    MML_UCID_USB_ABORT_PICTURE_BRIDGE_JOB,                               ///< 00060303 = Abort picture bridge job
    MML_UCID_USB_CONTINUE_PICTURE_BRIDGE_JOB,                            ///< 00060304 = Continue picture bridge job
    MML_UCID_USB_EXECUTE_CATEGORY,

    /* Force ID to be at least 32-bits */
    MML_UCID_USB_FORCE_U32 = 0x7FFFFFFF
};

/** @ingroup    MMLayerUsb
    @brief      Response results
*/
typedef enum
{
    /* Common */
    USB_ERROR_SUCCESS = 0,
    USB_ERROR_FAIL,
    USB_ERROR_PARAMETER_INVALID,
    USB_ERROR_STATE_CHANGE,
    USB_ERROR_ACCEPT,
    USB_ERROR_IGNORE,
    USB_ERROR_REJECT,
    USB_ERROR_MEMORY_FAILURE,
    /* Mass Storage */
    /* Virtual COM */
    /* Modem */
    /* PC-Cam */
    /* Picture Bridge */
    USB_ERROR_PRINTER_PAPER_ERROR,
    USB_ERROR_PRINTER_INK_ERROR,
    USB_ERROR_PRINTER_HARDWARE_ERROR,
    USB_ERROR_PRINTER_FILE_ERROR,
    USB_ERROR_PRINTER_DISCOVERY_FAIL,
    USB_ERROR_DEVICE_ACCESS_DENIED,
    USB_ERROR_DEVICE_FILE_DENIED,
    /* */
    USB_ERROR_NUM
} MmlUsbResult_e;

/** @ingroup    MMLayerUsb
    @brief      States
*/
typedef enum
{
    /* Common */
    USB_STATE_CLOSED = 0,                 ///< Initial state
    USB_STATE_SUSPENDED,                  ///< Usb device is suspended for power saving. Alternative to USB_STATE_MASSSTORAGE_SUSPENDED,
                                          ///< USB_STATE_VIRTUALCOM_SUSPENDED, USB_STATE_MODEM_SUSPENDED, USB_STATE_PCCAM_SUSPENDED, or
                                          ///< USB_STATE_PICBRIDGE_SUSPENDED.
    /* Mass Storage */
    USB_STATE_MASSSTORAGE,                ///< Mass storage is opened
    USB_STATE_MASSSTORAGE_SUSPENDED,      ///< Mass storage is suspended for power saving
    /* Virtual COM */
    USB_STATE_VIRTUALCOM,                 ///< Virtual COM is opened
    USB_STATE_VIRTUALCOM_SUSPENDED,       ///< Virtual COM is suspended for power saving
    USB_STATE_VIRTUALCOM_READ,            ///< Virtual COM is reading data from PC (optional)
    USB_STATE_VIRTUALCOM_WRITE,           ///< Virtual COM is writing data to PC (optional)
    /* Modem */
    USB_STATE_MODEM,                      ///< Modem is opened
    USB_STATE_MODEM_SUSPENDED,            ///< Modem is suspended for power saving
    /* PC-Cam */
    USB_STATE_PCCAM,                      ///< PC-Cam is opened
    USB_STATE_PCCAM_SUSPENDED,            ///< PC-Cam is suspended for power saving
    /* Picture Bridge */
    USB_STATE_PICBRIDGE_IDLE,             ///< Picture bridge is opened
    USB_STATE_PICBRIDGE_SUSPENDED,        ///< Picture bridge is suspended for power saving
    USB_STATE_PICBRIDGE_PRINTING,         ///< Picture bridge is printing a DPS job
    USB_STATE_PICBRIDGE_PAUSED,           ///< DPS job is paused due to a fatal error
    /* */
	USB_STATE_COMPOSITE,
	/* */
    USB_STATE_DONTCARE,
    USB_STATE_NUM
} MmlUsbState_e;

/** @ingroup    MMLayerUsb
    @brief      Events
*/
typedef enum
{
    /* Common */
    USB_EVENT_STATE_CHANGE = MML_GET_UCGEVENT_BASE(MML_UCGID_USB),
    USB_EVENT_RUNTIME_ERROR,
    USB_EVENT_PC_SUSPEND,
    USB_EVENT_PC_RESUME,
    USB_EVENT_REQUEST,                          ///< Alternative to USB_EVENT_VIRTUALCOM_CONNECTED or USB_EVENT_PCCAM_PREVIEW_ON
    /* Mass Storage */
    /* Virtual COM */
    USB_EVENT_VIRTUALCOM_READ_DONE,             ///< Reading data from PC is completed
    USB_EVENT_VIRTUALCOM_WRITE_DONE,            ///< Writing data to PC is completed
    USB_EVENT_VIRTUALCOM_CONNECTED,             ///< Virtual COM port is connected to PC
    USB_EVENT_VIRTUALCOM_DISCONNECTED,          ///< Virtual COM port is disconnected from PC
    /* Modem */
    /* PC-Cam */
    USB_EVENT_PCCAM_PREVIEW_ON,                 ///< PC-Cam preview on
    USB_EVENT_PCCAM_PREVIEW_OFF,                ///< PC-Cam preview off
    /* Picture Bridge */
    USB_EVENT_PICBRIDGE_RUNTIME_ERROR,
    USB_EVENT_PICBRIDGE_STATUS_UPDATE,          ///< Report the printer status
    USB_EVENT_PICBRIDGE_PRINT_COMPLETED,        ///< Printing DPS job is completed
    USB_EVENT_PICBRIDGE_PRINT_ABORTED,          ///< Printing DPS job is aborted
    /* */
    USB_EVENT_DONTCARE,
    USB_EVENT_ALL,
    USB_EVENT_NUM
} MmlUsbEvent_e;

/** @ingroup    MMLayerUsb
    @brief      Usb device classes
*/
typedef enum
{
    USB_DEVICECLASS_MASSSTORAGE = 0,
    USB_DEVICECLASS_VIRTUALCOM,
    USB_DEVICECLASS_MODEM,
    USB_DEVICECLASS_PCCAM,
    USB_DEVICECLASS_PICBRIDGE,
    USB_DEVICECLASS_COMPOSITE,
    /* */
    USB_DEVICECLASS_NUM
} MmlUsbDeviceClass_e;

/** @ingroup    MMLayerUsb
    @brief      Usb device statuses
*/
typedef enum
{
    USB_DEVICESTATUS_HOST_ATTACHED = 0,
    USB_DEVICESTATUS_CHARGING_ONLY,
    /* */
    USB_DEVICESTATUS_NUM
} MmlUsbDeviceStatus_e;

/** @ingroup    MMLayerUsbPicBridge
    @brief      Picture bridge statuses
*/
typedef enum
{
    /* Picture Bridge */
    USB_PICBRIDGE_STATUS_SERVICEERROR,     ///< Server error
    USB_PICBRIDGE_STATUS_JOBACCEPTABLE,    ///< Job acceptable
    USB_PICBRIDGE_STATUS_JOBPRINTING,      ///< Job printing
    USB_PICBRIDGE_STATUS_JOBWAITING,       ///< Job waiting
    USB_PICBRIDGE_STATUS_JOBFATAL,         ///< Job fatal
    /* */
    USB_PICBRIDGE_STATUS_NUM
} MmlUsbPicBridgeStatus_e;

/** @ingroup    MMLayerUsb
    @brief      Name string (ascii code)
*/
typedef struct
{
    u8          *pNameString;
    u16  	    nNameStringSize;
} MmlUsbNameStringAscii_t;

/** @ingroup    MMLayerUsbPicBridge
    @brief      Picture bridge statuses
*/
typedef	struct
{
    MmlUsbPicBridgeStatus_e    eStatus;     ///< Current status of the printer
    MmlUsbResult_e	           eErrCode;    ///< Error code is only used when picture bridge
                                            ///< returns 'Service Error', 'Job Warning' and 'Job Fatal' status
} MmlUsbPicBridgeStatus_t;

/** @ingroup    MMLayerUsb
    @brief      State change info
*/
typedef	struct
{
    MmlUsbState_e     eState;    ///< The new state after the transition
    MmlUsbEvent_e	  eCause;    ///< The cause of state change, if any
} MmlUsbStateChange_t;

/** @ingroup    MMLayerUsb
    @brief      Notification payload
*/
typedef struct
{
    MmlUsbEvent_e	               eEvent;        ///< Specify the event you want to notify
    u32                            nHandle;       ///< 32-bit device handle

    /// union of MmlUsbNotify_t parameters
    union
    {
        MmlUsbStateChange_t        tStateChange;              ///< Used with USB_EVENT_STATE_CHANGE event
        MmlUsbResult_e             eErrCode;                  ///< Used with USB_EVENT_RUNTIME_ERROR event
        MmlUsbPicBridgeStatus_t    tPicBridgeStatus;          ///< Used with USB_EVENT_PICBRIDGE_STATUS_UPDATE
	} uParam;
} MmlUsbNotify_t;

/** @ingroup    MMLayerUsb
    @brief      Notification callback prototype
    @param      nSenderID     Sender's mailbox ID
    @param      nUserValue    Interface self-reference
    @param      pUsbNotify    Pointer to the accompanying notification payload
*/
typedef void (*PfnMmlUsbNotifyCallback)(u16 nSenderID, u32 nUserValue, MmlUsbNotify_t *pUsbNotify);

/** @ingroup    MMLayerUsb
    @brief      Notification callback registration structure
*/
typedef struct
{
    u16                        nSenderID;           ///< Sender's mailbox ID
    u32                        nUserValue;          ///< Interface self-reference
    PfnMmlUsbNotifyCallback    pfnNotifyCallback;   ///< Callback function your want to register
} MmlUsbNotifyCallback_t;

/** @ingroup    MMLayerUsb
    @brief      Response callback prototype
    @param      nSenderID       Sender's mailbox ID
    @param      nUserValue      Interface self-reference
    @param      eErrCode        Returned result (error code)
    @param      pUsbResponse    Pointer to the returned response payload
*/
struct MmlUsbResponse_t_;
typedef void (*PfnMmlUsbResponseCallback)(u16 nSenderID, u32 nUserValue, MmlUsbResult_e eErrCode, struct MmlUsbResponse_t_ *pUsbResponse);

/** @ingroup    MMLayerUsb
    @brief      Response callback registration structure
*/
typedef struct
{
    u16                          nSenderID;              ///< Sender's mailbox ID
    u32                          nUserValue;             ///< Interface self-reference
    PfnMmlUsbResponseCallback    pfnResponseCallback;    ///< Callback function your want to register
} MmlUsbResponseCallback_t;

/** @ingroup    MMLayerUsb
    @brief      Register notification callback
*/
typedef struct
{
    MmlUsbEvent_e             eEvent;             ///< Specify which event you want to handle
    MmlUsbNotifyCallback_t    tNotifyCallback;    ///< Registration data specifying the callback function' address
} MmlUsbRegNotifyCallback_t;

/** @ingroup    MMLayerUsb
    @brief      Open USB
*/
typedef struct
{
    MmlUsbDeviceClass_e        eDeviceClass;               ///< Used with 'Open USB'
    MmlCameraSensorSource_e    eSensorSource;              ///< Sensor source (pc-cam only)
    MmlCameraFrequency_e       eFrequency;                 ///< Anit-flicker frequency (pc-cam only)	50/60 Hz
    u16                        bXAxisMirrorEnable;         ///< Enable x-axis mirror (pc-cam only)
    u16                        bYAxisMirrorEnable;         ///< Enable y-axis mirror (pc-cam only)
    MmlUsbNameStringAscii_t    tVendorNameStringAscii;     ///< Specify the vendor name characters string
} MmlUsbOpenUsb_t;

/** @ingroup    MMLayerUsbPicBridge
    @brief      Start picture bridge job
*/
typedef struct
{
    MmlImageInputType_e          eInputType;            ///< Input source types
    u32                          nHandle;               ///< 32-bit device handle

    /// union of MmlUsbStartPicBridgeJob_t parameters
    union
    {
        MmlImageFileParam_t      tFileParam;            ///< Print from file-based source
        MmlImageMemoryParam_t    tMemoryParam;          ///< Print from in-memory source
	} uParam;
} MmlUsbStartPicBridgeJob_t;

/** @ingroup    MMLayerUsb
    @brief      Response payload
*/
typedef struct MmlUsbResponse_t_
{
    MmlUsbState_e               eState;          ///< Current state
    u32                         nHandle;         ///< 32-bit device handle

    /// union of MmlUsbResponse_t parameters
	union
	{
        MmlUsbStateChange_t     tStateChange;    ///< Used with 'USB_ERROR_STATE_CHANGE' result
        MmlUsbDeviceStatus_e    eDeviceStatus;   ///< Used with 'Get USB status'
    } uParam;
} MmlUsbResponse_t;

/** @ingroup    MMLayerUsb
    @brief      Usb use case parameters
*/
typedef struct
{
	u32                               nUseCaseID;            ///< Use case ID
	MmlUsbResponseCallback_t          *pResponseCallback;    ///< Pointer to the response callback registration data
	MmlUsbResponse_t                  *pResponse;            ///< Pointer to the response payload

    /// union of MmlUsbUCParam_t parameters
    union
	{
	    /* Get usb status */

        u32                              nHandle;                   ///< Used with 'Close USB, Abort picture bridge job, Continue picture bridge job'
        MmlUsbOpenUsb_t                  tOpenUsb;                  ///< Used with 'Open USB'
        MmlUsbStartPicBridgeJob_t        tStartPicBridgeJob;        ///< Used with 'Start picture bridge job'
	} uParam;
} MmlUsbUCParam_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#ifdef __cplusplus
}
#endif

#endif //__SRV_RESMGR_MMLUSB_TYPES_H__
