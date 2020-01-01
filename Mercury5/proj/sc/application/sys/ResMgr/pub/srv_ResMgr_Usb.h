/**
* @file srv_ResMgr_Usb.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of USB.
*
*/

#ifndef __SRV_RESMGR_USB_H__
#define __SRV_RESMGR_USB_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_Common.h"
#include "esl_usb_itf.h"
#include "MediaRspItf.h"
#include "MML_Manager.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef esl_UsbInfo_t ABL_UsbInfo_t;

/**
 *  @brief The structure defines the notification value for application layer.
 *			should sync. with esl_UsbNotifyInfo_t
 */
typedef struct {
	MediaRspId_e	usbNotifyType;  /**< Type of USB notification */
} ABL_UsbNotifyInfo_t;

typedef struct ABL_UsbOpen_t_
{
    esl_UsbDev_e usbDev;
    esl_UsbDevConfig_t usbDevConfig;
} ABL_UsbOpen_t;

typedef esl_UsbDevConfig_t ABL_UsbDevConfig_t;

typedef enum ABL_UsbErrCode_e_
{
    ABL_USB_OK,               //ESL_USB_OK
    ABL_USB_FAIL,             //ESL_USB_FAIL
    ABL_USB_PARAM_ERROR,      //ESL_USB_PARAM_ERROR
    ABL_USB_MEM_ALLOC_ERROR,  //ESL_USB_MEM_ALLOC_ERROR
    ABL_USB_REJECT,           //ESL_USB_REJECT
    ABL_USB_ABORT,            //ESL_USB_ABORT
    ABL_USB_TIMEOUT,          //ESL_USB_TIMEOUT
    ABL_USB_DENY,
    ABL_USB_MERGE
} ABL_UsbErrCode_e;

typedef struct DBLUsbRemapErrCode_t_
{
    ABL_UsbErrCode_e eResMgrErrCode;
    ResMgr_ExecRes_e eExecRes;
} DBLUsbRemapErrCode_t;

typedef struct ABL_UsbRspInfo_t_
{
    ABL_UsbErrCode_e eErrCode;
    ABL_UsbInfo_t tUsbInfo;
    u32 uExtInfo;
} ABL_UsbRspInfo_t;

typedef enum ABL_UsbDev_e_
{
    ABL_USB_NONE,       //ESL_USB_NONE
    ABL_USB_CDC,        //ESL_USB_CDC
    ABL_USB_MSC,        //ESL_USB_MSC
    ABL_USB_MTP,        //ESL_USB_MTP
    ABL_USB_PBD,        //ESL_USB_PBD
    ABL_USB_VDC_MAIN,   //ESL_USB_VDC_MAIN
    ABL_USB_VDC_SUB,    //ESL_USB_VDC_SUB
    ABL_USB_OTG,        //ESL_USB_OTG
#ifdef __3G_RIL_MMI__
    ABL_USB_ATSYNC,
#endif // __3G_RIL_MMI__
    ABL_USB_COMPOSITE,
} ABL_UsbDev_e;

typedef enum ABL_UsbAttach_e{
    ABL_USB_PCHOST,     //ESL_USB_PCHOST
    ABL_USB_CHARGING    //ESL_USB_CHARGING
} ABL_UsbAttach_e;

typedef enum {
    ABL_USB_WEBCAM_ANTIFLICKER_OFF,     //ESL_USB_WEBCAM_ANTIFLICKER_OFF
    ABL_USB_WEBCAM_ANTIFLICKER_ON_60HZ, //ESL_USB_WEBCAM_ANTIFLICKER_ON_60HZ
    ABL_USB_WEBCAM_ANTIFLICKER_ON_50HZ  //ESL_USB_WEBCAM_ANTIFLICKER_ON_50HZ
} ABL_UsbWebcamFlicker_e;

typedef void (*ABL_UsbCb)(u16 uSenderId, u32 uUserValue, ABL_UsbErrCode_e eErrCode, ABL_UsbInfo_t *pUsbInfo);

typedef struct {
    u16 uSenderId;     /**< Task id of sender */
    u32 uUserValue;    /**< userValue of sender for checking msg response to realted applicatoin */
    ABL_UsbCb pfnCb;        /**< Done call back function that called by EMA */
} ABL_UsbCb_t;

typedef MmlUsbStartPicBridgeJob_t   ABL_UsbStartPicBridgeJob_t;
typedef MmlUsbOpenUsb_t             ABL_UsbOpenUsb_t;

typedef struct UsbCmd_t_
{
    ABL_UsbCb_t *pCbParams;
	u32 uHandle;
    union
    {
        ABL_UsbOpenUsb_t            tUsbOpenUsb;
        ABL_UsbStartPicBridgeJob_t  tUsbStartPicBridgeJob;
        ABL_UsbOpen_t tUsbOpenParams;
    } tParams;
} UsbCmd_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
ABL_CmnErrCode_e ABL_UsbOpenSessionReq(ResMgr_AppId_e eAppId, ABL_UsbDev_e eUsbDev, ABL_UsbCb_t *pUsbCb);
ABL_CmnErrCode_e ABL_UsbCloseSessionReq(ResMgr_AppId_e eAppId, ABL_UsbDev_e eUsbDev, ABL_UsbCb_t *pUsbCb);
void ABL_UsbOpenReq(ResMgr_AppId_e eAppId, ABL_UsbDev_e eUsbDev, ABL_UsbDevConfig_t *pUsbDevConfig, ABL_UsbCb_t *pUsbCb);
void ABL_UsbCloseReq(ResMgr_AppId_e eAppId, ABL_UsbDev_e eUsbDev, ABL_UsbCb_t *pUsbCb);
void ABL_UsbAttachReq(ResMgr_AppId_e eAppId, ABL_UsbCb_t *pUsbCb);
void ABL_UsbAttachAndPollingReq(ResMgr_AppId_e eAppId, ABL_UsbCb_t *pUsbCb);
void ABL_UsbStopPollingReq(ResMgr_AppId_e eAppId, ABL_UsbCb_t *pUsbCb);
#endif

