/**
* @file    mmi_srv_pedometer.h
* @brief  A pedometer service for footstep counting with a g-sensor.
*
*/

#ifndef __MMI_SRV_PEDOMETER_H__
#define __MMI_SRV_PEDOMETER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_pedometersrv.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** SrvPedometerSensorStatusChangeCB
* @brief  A callback function type used in SrvPedometerSetSensorStatusChangeCB.
*
* @param[in]       pUserdata                The applet's context (pThis) when calling SrvPedometerSetSensorStatusChangeCB
*                                           to register the callback function.
*/
typedef void ( *SrvPedometerSensorStatusChangeCB )( void *pUserdata );

/** SrvPedometerBatteryStatusChangeCB
* @brief  A callback function type used in SrvPedometerSetBatteryStatusChangeCB.
*
* @param[in]       pUserdata                The applet's context (pThis) when calling SrvPedometerSetBatteryStatusChangeCB
*                                           to register the callback function.
*/
typedef void ( *SrvPedometerBatteryStatusChangeCB )( void *pUserdata );

/** SrvPedometerGoalReachCB
* @brief  A callback function type used in SrvPedometerSetGoalReachCB.
*
* @param[in]       pUserdata                The applet's context (pThis) when calling SrvPedometerSetGoalReachCB
*                                           to register the callback function.
*/
typedef void ( *SrvPedometerGoalReachCB )( void *pUserdata );

/** SrvPedometerResetDoneCB
* @brief  A callback function type used in SrvPedometerSetResetDoneCB.
*
* @param[in]       pUserdata                The applet's context (pThis) when calling SrvPedometerSetResetDoneCB
*                                           to register the callback function.
*/
typedef void ( *SrvPedometerResetDoneCB )( void *pUserdata );



/*=============================================================*/
// functions
/*=============================================================*/
/** SrvPedometerEnablePedometer
* @brief  Enable or disable the pedometer service.
*
* @param[in]       bEnable          TRUE:   Enable
*                                   FALSE:  Disable
*/
void SrvPedometerEnablePedometer( boolean bEnable );

/** SrvPedometerResetPedometer
* @brief  Reset recorded data by type.
*
* @param[in]       eResetType           Reset Type
*                                       PEDOMETER_RESET_TODAY:      Reset today's data only.
*                                       PEDOMETER_RESET_ALL:        Reset all data.
*
* @retval TRUE                          Successful
* @retval FALSE                         Failed
*/
boolean SrvPedometerResetPedometer( PedometerResetType_e eResetType );

/** SrvPedometerIsPedometerEnable
* @brief  Check if pedometer service is enabled.
* 
* @retval  TRUE                     Service is enabled.
* @retval  FALSE                    Service is disabled.
*/
boolean SrvPedometerIsPedometerEnable( void );

/** SrvPedometerGetCurRecord
* @brief  Get current daily recorded data.
*
* @param[out]        ptStatItem         A pointer to a variable which receives current daily recorded data.
*/
void SrvPedometerGetCurRecords( PedometerStatItem_t *ptStatItem );

/** SrvPedometerGetWeekRecord
* @brief   Get current weekly recorded data and the average footsteps.
* 
* @param[out]        ptStatItem         A pointer to a variable which receives current weekly recorded data.
* @param[out]        pAvgSteps          The average daily footsteps calculated from current weekly recorded data.
*/
void SrvPedometerGetWeekRecord( PedometerStatItem_t *ptStatItem, u32 *pAvgSteps );

/** SrvPedometerGetRecordFromNow
* @brief   Get total recorded footsteps and the record starting date.
* 
* @param[out]        ptDateTime         A pointer to a variable which receives record starting date.
* @param[out]        pTotalSteps        A pointer to a variable which receives total recorded footsteps.
*/
void SrvPedometerGetRecordFromNow( PedometerDay_t *ptDateTime, u32 *pTotalSteps );

/** SrvPedometerGetMonthRecord
* @brief   Get the daily recorded data for a specified month and the average footsteps.
* 
* @param[in]         nMonth             The month to get the recorded data. Valid values are 1, 2, 3, ..., 12.
* @param[out]       pDays               A pointer to a variable which receives how many days are there in the specified month.
* @param[out]       pYear               A pointer to a variable which receives which year is for the specified month.
* @param[out]       pAvgSteps           The average daily footsteps calculated from the recorded data for the specified month.
* @param[out]       ptStatItems         A pointer to a buffer which receives a list of daily recorded data for the specified month.
*                                       The buffer size shall be at least 31*sizeof(PedometerStatItem_t) bytes.
*
* @retval MAE_RET_SUCCESS               Successful
* @retval MAE_RET_BAD_PARAM             Invalid parameter(s)
* @retval MAE_RET_OUT_OF_MEMORY         Fail to get srv client
*/
MAE_Ret SrvPedometerGetMonthRecord( u8 nMonth, u8 *pDays, u16 *pYear, u32 *pAvgSteps, PedometerStatItem_t *ptStatItems );

/** SrvPedometerSetUserName
* @brief    Set the user name
* 
* @param[in]         pwName             A user name string which cannot be longer than MAX_PEDOMETER_USERNAME_LEN(20).
* 
* @retval MAE_RET_SUCCESS               Successful
* @retval MAE_RET_BAD_PARAM             Invalid parameter(s)
* @retval MAE_RET_OUT_OF_MEMORY         Fail to get srv client
*/
MAE_Ret SrvPedometerSetUserName( MAE_WChar *pwName );

/** SrvPedometerGetUserName
* @brief    Get the user name which is set with SrvPedometerSetUserName.
* 
* @param[out]        pwName             A string buffer which receives the user name.
*                                       The string buffer size shall be at least MAX_PEDOMETER_USERNAME_LEN(20) * 2 bytes.
*/
void SrvPedometerGetUserName( MAE_WChar *pwName );

/** SrvPedometerSetUserSex
* @brief    Set user's sex
* 
* @param[in]        eSexType            Sex
*                                       PEDOMETER_SEX_MALE:     Male
*                                       PEDOMETER_SEX_FEMALE:   Female
*
* @retval MAE_RET_SUCCESS               Successful
* @retval MAE_RET_BAD_PARAM             Invalid parameter(s)
* @retval MAE_RET_OUT_OF_MEMORY         Fail to get srv client
*/
MAE_Ret SrvPedometerSetUserSex( PedometerSexType_e eSexType );

/** SrvPedometerGetUserSex
* @brief    Get user's sex
* 
* @retval   PEDOMETER_SEX_MIN:      Fail to get srv client
* @retval   PEDOMETER_SEX_MALE:     Male
* @retval   PEDOMETER_SEX_FEMALE:   Female  
*/
PedometerSexType_e SrvPedometerGetUserSex( void );

/** SrvPedometerEnableReminder
* @brief  Enable or disable the reminder. When the reminder is enabled,
*         the callback function (if any) registered with SrvPedometerSetGoalReachCB
*         will be called when the goal footstep count is reached. Otherwise, the
*         callback function will not be called.
* 
* @param[in]     bEnable            TRUE:   Enable
*                                   FALSE:  Disable
*/
void SrvPedometerEnableReminder( boolean bEnable );

/** SrvPedometerIsReminderEnable
* @brief  Check if the reminder is enabled.
* 
* @retval   TRUE:  Enabled
* @retval   FALSE: Disabled or fail to get srv client
*/
boolean SrvPedometerIsReminderEnable( void );

/** SrvPedometerSetMeasureUnits
* @brief    Set measuring units for weight and height.
* 
* @param[in]         eUnitsType             Measuring units
*                                           PEDOMETER_UNIT_METRIC:      Metric units
*                                           PEDOMETER_UNIT_IMPERIAL:    Imperial units
*
* 
* @retval MAE_RET_SUCCESS                    Success
* @retval MAE_RET_OUT_OF_MEMORY              Fail to get srv client
* @retval MAE_RET_BAD_PARAM                  Wrong parameter eSexType
*/
MAE_Ret SrvPedometerSetMeasureUnits( PedometerUnitType_e eUnitsType );

/** SrvPedometerGetMeasureUnits
* @brief    Get the measuring units for weight and height.
* 
* @retval        PEDOMETER_UNIT_MIN:         Fail to get srv client
* @retval        PEDOMETER_UNIT_METRIC:      Metric units
* @retval        PEDOMETER_UNIT_IMPERIAL:    Imperial units
*/
PedometerUnitType_e SrvPedometerGetMeasureUnits( void );

/** SrvPedometerIsIllegalDate
* @brief    If Current Date before Start Date return True(Illegal)
* 
* @retval      boolean with the result
*/
boolean SrvPedometerIsIllegalDate( void );

/** SrvPedometerSetSensorStatusChangeCB
* @brief  Register a callback function which will be called when the G-sensor status changes.
* 
* @param[in]      pfnCallBack            A callback function to be registered.
*                                        If pfnCallBack is NULL, the previously registered callback function (if any)
*                                        is deregistered.
*/
void SrvPedometerSetSensorStatusChangeCB( SrvPedometerSensorStatusChangeCB     pfnCallBack );

/** SrvPedometerSetBatteryStatusChangeCB
* @brief  Register a callback function which will be called when the battery status changes.
* 
* @param[in]      pfnCallBack            A callback function to be registered.
*                                        If pfnCallBack is NULL, the previously registered callback function (if any)
*                                        is deregistered.
*/
void SrvPedometerSetBatteryStatusChangeCB( SrvPedometerBatteryStatusChangeCB    pfnCallBack );

/** SrvPedometerSetGoalReachCB
* @brief  Register a callback function which will be called when the goal footstep count is reached and the reminder is enabled.
* 
* @param[in]      pfnCallBack            A callback function to be registered.
*                                        If pfnCallBack is NULL, the previously registered callback function (if any)
*                                        is deregistered.
*/
void SrvPedometerSetGoalReachCB( SrvPedometerGoalReachCB     pfnCallBack );

/** SrvPedometerSetResetDoneCB
* @brief  Register a callback function which will be called when SrvPedometerResetPedometer is called.
* 
* @param[in]      pfnCallBack            A callback function to be registered.
*                                        If pfnCallBack is NULL, the previously registered callback function (if any)
*                                        is deregistered.
*/
void SrvPedometerSetResetDoneCB( SrvPedometerResetDoneCB     pfnCallBack );


#endif //__MMI_SRV_PEDOMETER_H__

