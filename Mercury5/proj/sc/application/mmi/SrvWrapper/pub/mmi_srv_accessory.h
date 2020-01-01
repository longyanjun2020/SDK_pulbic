/**
* @file    mmi_srv_accessory.h
* @brief   Accesscory service wrapper header file
*          Accessory service provides other services or applications an interface to get accessory device status or notification when device status changed.
*
*/

#ifndef __MMI_SRV_ACCESSORY_H__
#define __MMI_SRV_ACCESSORY_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_client_commondefine.h"
#include "mmi_accessorysrv.h"

/*=============================================================*/
// Type definition of callBack function
/*=============================================================*/

/** SrvAccessoryPlugStatusCB
@brief  The interface is the CB definition for plug status changes.

@param[out]     pThis           The pointer of Applet
@param[out]     eDevice         General peripheral device. Please reference ACCDeviceType_e.
                                ACCSRV_DEVICE_HEADSET,
                                ACCSRV_DEVICE_DATACABLE,
                                ACCSRV_DEVICE_EXTCARD,
                                ACCSRV_DEVICE_EXTCARD2,
                                ACCSRV_DEVICE_HALL,
@param[out]     pPlugIn         The device status is plug-in or not.
                                TRUE is plug-in while FALSE is plug-out.
@param[out]     eCardinfo       The external memory card status.
                                Please reference ExtCardAccInfo_e(ACCSRV_EXT_CARD_ACCESSING or ACCSRV_EXT_CARD_NON_ACCESS).
*/
typedef void (*SrvAccessoryPlugStatusCB)(void *pThis, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

/*=============================================================*/
// Global function definition
/*=============================================================*/

/** SrvAccessorySetPlugStatusChangeCB
@brief  The interface is used to set CB which will be triggered when accessory device status change(Headset, data cable and memory card).

@param[in]      pfnPlugStatusCb         SrvAccessoryPlugStatusCB callback function point to info owner with accessory status change data

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              AccessorySrv is already terminated.
@retval  MAE_RET_FAILED                 If an error occurs.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
*/
__SLDPM_FREE__ MAE_Ret SrvAccessorySetPlugStatusChangeCB(SrvAccessoryPlugStatusCB pfnPlugStatusCb);

/** SrvAccessoryGetDeviceStatus
@brief  The interface is used to get accessory device status(Headset, data cable and memory card).

@param[in]      eDevice                 General peripheral device. Please reference ACCDeviceType_e.
                                        ACCSRV_DEVICE_HEADSET,
                                        ACCSRV_DEVICE_DATACABLE,
                                        ACCSRV_DEVICE_EXTCARD,
                                        ACCSRV_DEVICE_EXTCARD2,
                                        ACCSRV_DEVICE_HALL,
@param[out]     pPlugIn                 The device status is plug-in or not.
                                        TRUE is plug-in while FALSE is plug-out.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              AccessorySrv is already terminated.
@retval  MAE_RET_BAD_PARAM              If input parameter eDevice error.
@retval  MAE_RET_NOT_SUPPORTED          The device is not supported.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
*/
//Query Device API
__SLDPM_FREE__ MAE_Ret SrvAccessoryGetDeviceStatus(ACCDeviceType_e eDevice, boolean *pPlugIn);

/** SrvAccessoryFormatExtCard
@brief  The interface is used to format memory card.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              AccessorySrv is already terminated.
@retval  MAE_RET_NOT_FOUND              The memory card is not found.
@retval  MAE_RET_FAILED                 Fat partition format error.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
*/
MAE_Ret SrvAccessoryFormatExtCard(void);

/** SrvAccessoryVibrateOn
@brief  The interface of Service Client is used to set vibrate on request.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              AccessorySrv is already terminated.
@retval  MAE_RET_FAILED                 If an error occurs.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
*/
//Action Vibrate API
MAE_Ret SrvAccessoryVibrateOn(void);

/** SrvAccessoryVibrateOff
@brief  The interface of Service Client is used to set vibrate off request.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              AccessorySrv is already terminated.
@retval  MAE_RET_FAILED                 If an error occurs.
@retval  MAE_RET_OUT_OF_MEMORY          Memory is not enough to complete the operation.
*/
//Action Vibrate API
MAE_Ret SrvAccessoryVibrateOff(void);

/**
 SrvAccessoryGetStateInfo
@brief  The interface is use to get Accessory information(Handset, Data Cable and Ext Card).

@param[in]    DeviceType                            Device. please reference ACCDeviceType_e.
@param[out]  pStatusInfo                             Information about this device. please reference ACCStatusInfo_Union.


@return MAE_RET_SUCCESS          If successful.
@return MAE_RET_FAILED             If an error happen.
@return MAE_RET_BAD_PARAM   If input parameter error.


 */

/** SrvAccessoryAutoRotateOnOff
@brief  The interface of Service Client is used to set AutoRotate on/off request.

@retval  MAE_RET_SUCCESS                If successful.
@retval  MAE_RET_NOT_READY              AccessorySrv is already terminated.
@retval  MAE_RET_FAILED                     If an error occurs.
@retval  MAE_RET_OUT_OF_MEMORY      Memory is not enough to complete the operation.
@return MAE_RET_NOT_SUPPORTED       if not support
*/
//Action AutoRotate API
MAE_Ret SrvAccessoryAutoRotateOnOff(SetOnOff_e eGSensorWndAutorotateOnOff);

/**
 SrvAccessoryGetStateInfo
@brief  The interface is use to get Accessory information(Handset, Data Cable and Ext Card).

@param[in]    DeviceType                            Device. please reference ACCDeviceType_e.
@param[out]  pStatusInfo                             Information about this device. please reference ACCStatusInfo_Union.


@return MAE_RET_SUCCESS          If successful.
@return MAE_RET_FAILED             If an error happen.
@return MAE_RET_BAD_PARAM   If input parameter error.


 */

MAE_Ret SrvAccessoryGetStateInfo(ACCDeviceType_e DeviceType, ACCStatusInfo_Union *pStatusInfo);


/**
 SrvAccessoryGetCardStatus
@brief  The interface is use to get latest card status.

@param[in]    DeviceType                  Device. please reference ACCDeviceType_e.
@param[out]   pStatusInfo                 Information about this device. please reference ACCStatusInfo_Union.


@return MAE_RET_SUCCESS          If successful.
@return MAE_RET_FAILED           If an error happen.
@return MAE_RET_BAD_PARAM        If input parameter error.

*/
MAE_Ret SrvAccessoryGetCardStatus(ACCDeviceType_e DeviceType, ACCStatusInfo_Union *pStatusInfo);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_ACCESSORY_H__
