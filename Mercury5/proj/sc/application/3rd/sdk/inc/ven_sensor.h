#ifndef __VEN_SENSOR_H_
#define __VEN_SENSOR_H_
/***************************************************************************/
/*  File : ven_sensor.h                                                        */
/*-------------------------------------------------------------------------*/
/*  Scope: This file defines the sensor related vendor request API,    */
/*         and MMI response API.                                           */
/*                                                                         */
/***************************************************************************/

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_SEN_RET_SUCCESS        = 0, ///< operation completed successfully
    VEN_SEN_RET_BAD_PARAM      = 1, ///< invalid input parameters
    VEN_SEN_RET_FAILED         = 2, ///< WHAT? every code here is failed
    VEN_SEN_RET_OUT_OF_MEMORY  = 3, ///< memory is not enough to complete the operation
};
typedef u32 ven_sen_ret_t;

#if defined (__G_SENSOR__)
enum
{
	VEN_SEN_GSENSOR_NOTIFY_DELAY_FASTEST, 		//(0.1 Sec) Get notify as soon as possible
	VEN_SEN_GSENSOR_NOTIFY_DELAY_GAME,			//(0.2 Sec) Notify delay suitable for games
	VEN_SEN_GSENSOR_NOTIFY_DELAY_NORMAL,		//(1.0 Sec) Notify delay suitable for screen orientation changes
	VEN_SEN_GSENSOR_NOTIFY_DELAY_UI,			//(0.5 Sec) Notify delay suitable for the user interface
};
typedef u32 ven_sen_gsensor_notify_delay_t;	//for Gsensor notify frequency

enum
{
    VEN_SEN_GSENSOR_MOTION_TYPE_ORIENTATION 	= 0x01,	/**< Orientation detection, only feedback when orientation changes */
    VEN_SEN_GSENSOR_MOTION_TYPE_SIMPLE_ACTION 	= 0x02,
    VEN_SEN_GSENSOR_MOTION_TYPE_TRUN_OVER		= 0x04,  
};
typedef u32 ven_sen_gsensor_motion_type_t;	//for Gsensor motion detector

enum
{
    VEN_SEN_GSENSOR_ORIENTATION_LANDSCAPE = 0,
    VEN_SEN_GSENSOR_ORIENTATION_REVERSE_LANDSCAPE,
    VEN_SEN_GSENSOR_ORIENTATION_PORTRAIT,
    VEN_SEN_GSENSOR_ORIENTATION_REVERSE_PORTRAIT,
    VEN_SEN_GSENSOR_ORIENTATION_FACE_DOWN,
    VEN_SEN_GSENSOR_ORIENTATION_FACE_UP,
};
typedef u32 ven_sen_gsensor_orientation_t;

enum
{
    VEN_SEN_GSENSOR_SIMPLE_ATION_SHAKE = 0,
};
typedef u32 ven_sen_gsensor_simple_ation_t;

enum
{
    VEN_SEN_GSENSOR_TRUNOVER_DETECTED = 0,
};
typedef u32 ven_sen_gsensor_turnover_t;

typedef struct
{
	u16 x;	/**< x-ax accelerometer sensor value */
	u16 y;	/**< y-ax accelerometer sensor value */
	u16 z;	/**< z-ax accelerometer sensor value */
} ven_sen_gsensor_info_t;

typedef struct
{
	u16 nAxisNum;
	u16 nSensitiveLevel;
} ven_sen_gsensor_devInfo_t;

typedef struct
{
	ven_sen_ret_t retCode;
	ven_sen_gsensor_devInfo_t devInfo;
} ven_sen_gsensor_get_devinfo_rsp_t;

typedef struct
{
	ven_sen_ret_t retCode;
	ven_sen_gsensor_motion_type_t type;
	u32 motionInfo;
} ven_sen_gsensor_get_last_motion_rsp_t;

#endif //#if defined (__G_SENSOR__)

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/
#if defined (__G_SENSOR__)
typedef void (*VEN_SEN_GSENSOR_NOTIFY_FUNC)(ven_sen_gsensor_info_t gsensorInfo, u32 usrData);

/**
 *  ven_sen_gsensorRegNotify
 *
 *  @brief  This function will help to register Gsensor notify with a function. 
 *    		The notify function will get notify information per delay time .
 *          	This function only support one notify function for each vendor. 
 *           The new notify function will replace the old one if register again.
 *		The notify function only work during its vendor is alive. 
 *		If pGsensorNotify == NULL, this function will deregister the notify function.
 *
 *  @param  nDelay       [in] To set the frequency of getting notification
 *  @param  bListenOnPowerSavingMode  [in] TRUE means that you want to get notification during power saving mode. But this parameter is not supported for multiple vendors now.  
 *  @param  pGsensorNotify       [in]Added gsensor notify function
 *  @param  usrData  			[in]User data for notify function
 *
 *  @retval VEN_SEN_RET_SUCCESS if success
 *          VEN_SEN_RET_FAILED if failed
 *          VEN_SEN_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_sen_ret_t ven_sen_gsensorRegNotify(ven_sen_gsensor_notify_delay_t nDelay, bool bListenOnPowerSavingMode, VEN_SEN_GSENSOR_NOTIFY_FUNC pGsensorNotify, u32 usrData, ven_req_data_t *ptVenReq);

/**
 *  ven_sen_gsensorGetDevInfo
 *
 *  @brief  This function will help to get the information of the Gsensor, including nAxisNum and nSensitiveLevel.
 *
 *  @param  pDevInfo       [in] The pointer of device information you want to fill with.
 *
 *  @retval VEN_SEN_RET_SUCCESS if success
 *          VEN_SEN_RET_FAILED if failed
 *          VEN_SEN_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_sen_ret_t ven_sen_gsensorGetDevInfo(ven_sen_gsensor_devInfo_t *pDevInfo, ven_req_data_t *ptVenReq);

typedef void (*VEN_SEN_GSENSOR_MOTION_LISTENER_FUNC)(ven_sen_gsensor_motion_type_t type, u32 motionInfo, u32 usrData);

/**
 *  ven_sen_gsensorRegMotionListener
 *
 *  @brief  This function will help to register motion detector with a function. 
 *    		The listener function will get motion information when end user move the phone .
 *          	This function only support one notify function for each vendor. 
 *           The new listener function will replace the old one if register again.
 *		The Listener function only work during its vendor is alive. 
 *		If pMotionListener == NULL, this function will deregister the listener function.
 *
 *  @param  type       [in] To set what kind of motion you want to listen
 *  @param  bListenOnPowerSavingMode  [in] TRUE means that you want to get notification during power saving mode. But this parameter is not supported for multiple vendors now.  
 *  @param  pMotionListener       [in]Added motion listener function
 *  @param  usrData  			[in]User data for motion listener  function
 *
 *  @retval VEN_SEN_RET_SUCCESS if success
 *          VEN_SEN_RET_FAILED if failed
 *          VEN_SEN_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_sen_ret_t ven_sen_gsensorRegMotionListener(ven_sen_gsensor_motion_type_t type, bool bListenOnPowerSavingMode, VEN_SEN_GSENSOR_MOTION_LISTENER_FUNC pMotionListener, u32 usrData, ven_req_data_t *ptVenReq);

/**
 *  ven_sen_gsensorGetLastMotion
 *
 *  @brief  This function will help to get the information of last motion.
 *
 *  @param  type       [in] what kind of last motion you want to get.
 *  @param  pMotionInfo       [out] the pointer to last motion.
 *
 *  @retval VEN_SEN_RET_SUCCESS if success
 *          VEN_SEN_RET_FAILED if failed
 *          VEN_SEN_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_sen_ret_t ven_sen_gsensorGetLastMotion(ven_sen_gsensor_motion_type_t type, u32 *pMotionInfo, ven_req_data_t *ptVenReq);
#endif //#if defined (__G_SENSOR__)

ven_sen_ret_t ven_sen_btAppSendFile(u16 *pFileUrl, bool bIsDelete, ven_req_data_t* ptVenReq);


#endif
