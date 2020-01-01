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
* @file    mdl_touch_screen_pub.h
* @version
* @brief   MDL header file of ouch screen
*
*/

#ifndef __TOUCHSCREEN_PUB_H__
#define __TOUCHSCREEN_PUB_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"
#include "drv_touchscreen_pub_types.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#ifdef __SMALL_ROM_32__
#define SECOND_TRACE(x)
#else
#define SECOND_TRACE(x)  _TRACE(x)
#endif

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines error codes of touch screen drivers .
 */
typedef enum
{
    MDL_TOUCH_SCREEN_OK = 0,                                         ///< Function complete successfully
    MDL_TOUCH_SCREEN_FAIL,                                           ///< Function common fail
    MDL_TOUCH_SCREEN_INVALID_PARAM,                        ///< Function fail by invalid parameter
    MDL_TOUCH_SCREEN_INVALID_FIRMWARE,                  ///< Function fail by incorrect firmware
    MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION,  ///< Function fail by invalid firmware version

}MdlTsRetCode_e;

/**
 * @brief The enumeration defines the touch screen type.
 */
typedef enum
{
    MDL_TOUCH_SCREEN_R_TYPE,         ///< R type touch screen
    MDL_TOUCH_SCREEN_C_TYPE,         ///< C type touch screen
    MDL_TOUCH_SCREEN_UNKNOWN      ///< Unknown type touch screen
} MdlTscrType_e;

/**
 * @brief The enumeration defines the touch screen power swtich on/off request.
 */
typedef enum
{
    MDL_TOUCH_SCREEN_POWER_SWITCH_OFF,      ///< Switch off touch screen power
    MDL_TOUCH_SCREEN_POWER_SWITCH_ON        ///< Switch on touch screen power
} MdlTscrPowerSwitch_e;

/**
 *  @brief The structure defines touch panel coordination.
 */
typedef struct
{
   u8       Mode;    ///< Touch screen press or release mode
   u16      Row;    ///< Touch screen row data
   u16      Col;     ///< Touch screen column data
}MdlTouchScreenCoord_t;

/**
 *  @brief The structure defines calibration object structure.
 */
typedef struct
{
    Calib_t Xoffset;    ///< Touch screen x offset
    Calib_t Xslope;    ///< Touch screen x slope
    Calib_t Yoffset;    ///< Touch screen y offset
    Calib_t Yslope;    ///< Touch screen y slope
}MdlTscCalibObj_t;

/**
 *  @brief The structure defines calibration structure.
 */
typedef struct
{
   MdlTscCalibObj_t TscCalib;    ///< Touch screen calibration data
#ifdef __MULTI_TOUCH_SLIM__
   u16       TscResistance[2];
#endif
   u16       ScreenWidth;          ///< Touch screen width
   u16       ScreenHeight;         ///< Touch screen height

}MdlTouchScreenCalibration_t;

/**
 *  @brief The structure defines subscribed mailbox structure.
 */
typedef struct
{
	u16 dstMbx;    ///< Touch screen subscribed mailbox
	u8 enable;      ///< Touch screen enable to send massage to subscribed mailbox
}MdlTouchScreenSusbribeData_t;

/**
 *  @brief The structure defines edge tune value structure.
 */
typedef struct
{
    s32 XExpRightBtmTune;    ///< Touch screen expected x right bottom calibration point.
    s32 XExpLeftTopTune;      ///< Touch screen expected x left top calibration point.
    s32 YExpRightBtmTune;    ///< Touch screen expected y right bottom calibration point.
    s32 YExpLeftTopTune;      ///< Touch screen expected y left top calibration point.
}MdlTscEdgeTuneValue_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
* \fn void MdlTouchScreenPowerSwitchMMIRequest(MdlTscrPowerSwitch_e eTscrPowerSwitch)
* \brief Function for MMI to send request of switching touch screen power.
* \param[in] eTscrPowerSwitch Request of switching touch screen power
* \retval None
*/
void MdlTouchScreenPowerSwitchMMIRequest(MdlTscrPowerSwitch_e eTscrPowerSwitch);


/**
* \fn MdlTsRetCode_e MdlTouchScreenSubscribe(u16 nDstMbx, u8 nEnable)
* \brief Function to subscribe TS service
* \param[in] nDstMbx Destination mail box that position data is sent to
* \param[in] nEnable 1-enable,   0-disable
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenSubscribe(u16 nDstMbx, u8 nEnable);

/**
* \fn MdlTsRetCode_e MdlTouchScreenProbe(void)
* \brief Function to probe and select the corresponding touch screen driver
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenProbe(void);

/**
* \fn MdlTsRetCode_e MdlTouchScreenEnable(void)
* \brief Enable touch screen function (Driver to enable touch and interrupt when task init.)
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenEnable(void);

/**
* \fn MdlTsRetCode_e MdlTouchScreenDisable(void)
* \brief Disable touch screen function (not used)
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenDisable(void);


/**
* \fn MdlTsRetCode_e MdlTouchScreenCheckIntpDynamicReportRate(void)
* \brief Check if CTP support interrupt dynamic report rate
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenCheckIntpDynamicReportRate(void);

/** MdlTouchScreenConfigure
* @brief        interface to set TS parameters
* @param[in]    ScreenWidth: LCM panel width
* @param[in]    ScreenHeight: LCM panel height
* @param[in]    delay: interval to get position data
* @retval[out]  MdlTsRetCode_e error code
*
*/
MdlTsRetCode_e MdlTouchScreenConfigure(u16 nScreenWidth, u16 nScreenHeight, u16 nDelay);


#if defined (__TOUCH_SCREEN_FILTERING_DRV__)
/**
* \fn MdlTsRetCode_e MdlTouchScreenFiltering(u16 nfilter)
* \brief Function to set TS filtering
* \param[in] nfilter Filter setting
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenFiltering(u16 nfilter);
#endif


/**
* \fn MdlTsRetCode_e MdlTouchscreenSetCalibration(MdlTouchScreenCalibration_t* pCalibration)
* \brief Function to set calibration parameters
* \param[in] pCalibration Pointer to calibration parameters
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchscreenSetCalibration(MdlTouchScreenCalibration_t* pCalibration);


/**
* \fn MdlTsRetCode_e MdlTouchscreenSetCalibrationMode(bool nMode)
* \brief Function to set calibration mode
* \param[in] nMode True-calibation mode, False-not calibration mode
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchscreenSetCalibrationMode(bool nMode);

/**
* \fn MdlTsRetCode_e MdlTouchscreenGetEdgeTuneValue(MdlTscEdgeTuneValue_t* pEdgeTuneValue)
* \brief Function to get edge tune value (Modify calibration parameter and make lcd edge could reached easier.)
* \param[out] pEdgeTuneValue Pointer to edge tune parameters
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchscreenGetEdgeTuneValue(MdlTscEdgeTuneValue_t* pEdgeTuneValue);

/**
* \fn MdlTsRetCode_e MdlTouchScreenPollingTimer(u8 nMmode)
* \brief Function to start/stop TS polling timer
* \param[in] nMmode 1-start, 0-stop
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenPollingTimer(u8 nMmode);

/**
* \fn MdlTsRetCode_e MdlTouchScreenPenDetect(bool *pbRetValue)
* \brief Function to entry function of pen detection event
* \param[out] pbRetValue Pointer of flag if pen detect valid
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenPenDetect(bool *pbRetValue);

/**
* \fn MdlTsRetCode_e MdlTouchscreenGetADCData(u32 nWhichjob, vm_msg_t *ptMsg)
* \brief Function to receive ADC result from Drv
* \param[in] nWhichjob Current ADC job type
* \param[in] ptMsg Message from Drv layer
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchscreenGetADCData(u32 nWhichjob, vm_msg_t *ptMsg);

/**
* \fn MdlTsRetCode_e MdlTouchScreenEventProcessed(void)
* \brief Function to minus number of pending tscr message when touch event processed.
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenEventProcessed(void);

/**
* \fn MdlTsRetCode_e MdlTouchscreenGetCalibrationMode(bool *pbCaliMode)
* \brief Function to get calibration mode
* \param[out] pbCaliMode Pointer to get calibration mode
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchscreenGetCalibrationMode(bool *pbCaliMode);

/**
* \fn MdlTsRetCode_e MdlTouchscreenGetTscrType(MdlTscrType_e *peTscrType)
* \brief Function to get touch screen type
* \param[out] peTscrType Pointer of touch screen type enum
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchscreenGetTscrType(MdlTscrType_e *peTscrType);

/**
* \fn u32 MdlTouchScreenGetProcessedCnt(void)
* \brief Function to get number of pending tscr message which not processed yet.
* \return Number of pending message
*
*/
void MdlTouchscreenPowerSwitch(bool bOn);

u32 MdlTouchScreenGetProcessedCnt(void);

/**
* \fn void MdlTouchScreenSetProcessedCnt(void)
* \brief Function to add number of pending tscr message which need to process.
* \retval None
*
*/
void MdlTouchScreenSetProcessedCnt(void);

/**
* \fn void MdlTouchScreenIntDelayTime(u8 *delayCnt)
* \brief Function to set  ADC polling period
* \param[in] delayCnt Pointer of delay count
* \retval None
*
*/
void MdlTouchScreenIntDelayTime(u8 *delayCnt);

/**
* \fn MdlTsRetCode_e MdlTouchScreenFwUpdate(void)
* \brief Function to update CTP firmware
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenFwUpdate(void);

/**
* \fn MdlTsRetCode_e MdlTouchScreenReadFwId(u32 *FwId)
* \brief Function to read CTP firmware ID
* \param[out] FwId Pointer of CTP firmware ID
* \retval MDL_TOUCH_SCREEN_OK                         Function complete successfully
* \retval MDL_TOUCH_SCREEN_FAIL                       Function common fail
* \retval MDL_TOUCH_SCREEN_INVALID_PARAM              Function fail by invalid parameter
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE           Function fail by incorrect firmware
* \retval MDL_TOUCH_SCREEN_INVALID_FIRMWARE_VERSION   Function fail by invalid firmware version
*
*/
MdlTsRetCode_e MdlTouchScreenReadFwId(u32 *FwId);
/**
* \fn void MdlTouchScreenChangePointId(u8 PId)
* \brief Function to change point ID if first point id larger than the other point
* \param[in] PId Point ID
* \retval None
*
*/
void MdlTouchScreenChangePointId(u8 PId);

/**
* \fn void MdlTouchscreenGetResistance(u32 *xResistance, u32 *yResistance)
* \brief Function to get resistance
* \param[in] xResistance Pointer to x resistance
* \param[in] yResistance Pointer to y resistance
* \retval None
*
*/
void MdlTouchscreenGetResistance(u32 *xResistance, u32 *yResistance);

#endif  /* __TOUCHSCREEN_PUB_H__ */


