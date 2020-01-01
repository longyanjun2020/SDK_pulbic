/**
* @file    mmi_mae_motiondetector.h
* @brief   The document describes the interface of IMotionDetector
* IMotionDetector defines a set of interface to track the motion or gesture made by user
*
* The implementation of IMotionDetector MAY need hardware support of some kind of sensor
* such as accelerometer sensor or compass sensor or orientation sensor.
*
* Several motion are defined in MAE:
* 1. Orientation
* 2. Simple action(shake)
*
* @author  mark.yang@mstarsemi.com
* @version $Id: mmi_mae_motiondetector.h 540 2009-03-31 11:04:04Z mark.yang $
*/
#ifndef __MMI_MAE_MOTIONDETECTOR_H__
#define __MMI_MAE_MOTIONDETECTOR_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"


// G-Sensor Cfg Start ------------------------------------------------------------------

/* Sensor Notify Delay Speed
 *   SENSOR_NOTIFY_DELAY_FASTEST -- (0.1 Sec) Get notify as soon as possible
 *   SENSOR_NOTIFY_DELAY_GAME	 -- (0.2 Sec) Notify delay suitable for games
 *   SENSOR_NOTIFY_DELAY_NORMAL	 -- (1.0 Sec) Notify delay suitable for screen orientation changes
 *   SENSOR_NOTIFY_DELAY_UI		 -- (0.5 Sec) Notify delay suitable for the user interface
 */

#define SENSOR_NOTIFY_DELAY_ORIENTATION     SENSOR_NOTIFY_DELAY_GAME
#define SENSOR_NOTIFY_DELAY_SIMPLE_ACTION   SENSOR_NOTIFY_DELAY_FASTEST
#define SENSOR_NOTIFY_DELAY_TRUN_OVER       SENSOR_NOTIFY_DELAY_FASTEST

/* G-Sensor Axis Value Offsets
 */
#define SENSOR_X_AXIS_OFFSET     0
#define SENSOR_Y_AXIS_OFFSET     0
#define SENSOR_Z_AXIS_OFFSET     0

/* Turnover Sensivity Boundary
 *
 * #define GSENSOR_GVALUE_DEGREE_00 (32768)
 * #define GSENSOR_GVALUE_DEGREE_05 (32856)
 * #define GSENSOR_GVALUE_DEGREE_10 (32946)
 * #define GSENSOR_GVALUE_DEGREE_20 (33118)
 * #define GSENSOR_GVALUE_DEGREE_30 (33280)
 * #define GSENSOR_GVALUE_DEGREE_45 (33492)
 * #define GSENSOR_GVALUE_DEGREE_60 (33654)
 * #define GSENSOR_GVALUE_DEGREE_70 (33730)
 * #define GSENSOR_GVALUE_DEGREE_80 (33776)
 * #define GSENSOR_GVALUE_DEGREE_85 (33788)
 * #define GSENSOR_GVALUE_DEGREE_90 (33792)
 */

#define TURNOVER_SENSITIVITY_BOUNDARY		(GSENSOR_GVALUE_DEGREE_45 - GSENSOR_GVALUE_DEGREE_00)	/* 45 degree */

// G-Sensor Cfg End  ------------------------------------------------------------------


typedef enum
{
    MOTION_TYPE_ORIENTATION = 0,	/**< Orientation detection, only feedback when orientation changes */
    MOTION_TYPE_SIMPLE_ACTION,
    MOTION_TYPE_TRUN_OVER,
    MOTION_TYPE_GAME_ACTION,
    MOTION_TYPE_MAX					/**< Number of motion types */
}MOTION_TYPE_e;
#define MOTION_TYPE_MSK(_id)	(1 << (_id&0xFF))//((u32)1<<_id)
#define MOTION_TYPE_MSK_ALL		0xFFFF
typedef u32 MOTION_TYPES_t;			/**< Collection of motion types, value ORed by using MOTION_TYPE_MSK macro.
									e.g. (MOTION_TYPE_MSK(MOTION_TYPE_ORIENTATION) | MOTION_TYPE_ORIENTATION(MOTION_TYPE_SIMPLE_ACTION))
									*/

/**
* Orientation changed notification value
*/
typedef enum
{
    ORIENTATION_LANDSCAPE = 0,
    ORIENTATION_REVERSE_LANDSCAPE,
    ORIENTATION_PORTRAIT,
    ORIENTATION_REVERSE_PORTRAIT,
    ORIENTATION_FACE_DOWN,
    ORIENTATION_FACE_UP,
    ORIENTATION_UNKNOWN
}ORIENTATION_e;

typedef enum
{
SIMPLE_ACTION_SHAKE = 0,
SIMPLE_ACTION_GAME_LEFT,
SIMPLE_ACTION_GAME_RIGHT,
SIMPLE_ACTION_UNKNOWN
}SIMPLE_ACTINO_e;

typedef enum
{
    TRUNOVER_DETECTED = 0,
    TRUNOVER_UNKNOWN
}TURNOVER_e;

typedef enum
{
    TILT_ROLL_LEFT = 0,
    TILT_ROLL_RIGHT,
    TILT_PITCH_UP,
    TILT_PITCH_DOWN,
    TILT_YAW_LEFT,
    TILT_YAW_RIGHT
}TILT_e;

typedef s32 MotionValue_t;	/**< The value is the result of the motion detector and depends on motion type,
							If motion type is MOTION_TYPE_ORIENTATION, the value comes from ORIENTATION_et;
							if motion type is MOTION_TYPE_SIMPLE_ACTION, the value comes from SIMPLE_ACTINO_et;
							if motion type is MOTION_TYPE_TILT, the value comes from TILT_et
							*/

/* Notify callback function prototype */
typedef void (*PfnMAE_MotionChangedCb)(MOTION_TYPE_e type, MotionValue_t motionValue, IBase *pListener);

#define INHERIT_IMotionDetector(IName) \
	INHERIT_IBase(IName);\
	MAE_Ret (*GetLastStatus)(IName *pThis, MOTION_TYPE_e type, MotionValue_t *pOutLastValue);\
	MAE_Ret (*AddChangeListener)(IName *pThis, MOTION_TYPES_t types, boolean isActiveListen, boolean isListenOnPowerSavingMode, PfnMAE_MotionChangedCb pMotionChangedCb, IBase *pListener);\
	MAE_Ret (*RemoveChangeListener)(IName *pThis, IBase *pListener)

DEFINE_INTERFACE(IMotionDetector);

/**
 * Query if this implementation support such interface
 *
 * @param pThis Pointer to the object supporting IMotion interface
 * @param id Interface ID.
 * @param pp Reference to a pointer to a function table if this interface is supported
 * @return number of reference count
 */
#define IMOTIONDETECTOR_QueryInterface(pThis,id,pp,pOwner)							GET_FUNCTBL(pThis,IMotionDetector)->QueryInterface(pThis,id,pp,pOwner)

/**
 * Get the last recognized motion.
 *
 * The motion detector will keep the last recognized motion and overwrite it when new motion is detected.
 * This interface can be used to get the last motion detected in this type of motion detector.
 * If there do not have any recognized motion, this will return the UNKNOWN motion enum value.
 *
 * @param pThis Pointer to the object supporting IMotion interface
 * @param type Type of motion, the enum value comes from MOTION_TYPE_et
 * @param pOutLastValue the result, the enum value comes from ORIENTATION_et or SIMPLE_ACTINO_et or etc.
 */
#define IMOTIONDETECTOR_GetLastStatus(pThis,type,pOutLastValue)						GET_FUNCTBL(pThis,IMotionDetector)->GetLastStatus(pThis,type,pOutLastValue)

/**
 * Add a motion change listener to motion detector for one or more type of motions.
 *
 * The type parameter should be the motion types you are interesting to listen.
 * You should use MOTION_TYPE_MSK macro to enclose the MOTION_TYPE_et and use a bit or operation to concatenate all the motion types.
 * For example, if you are interested in MOTION_TYPE_ORIENTATION, use
 *    MOTION_TYPE_MSK(MOTION_TYPE_ORIENTATION)
 *
 * if you are interested in both MOTION_TYPE_SIMPLE_ACTION and MOTION_TYPE_TILT, use
 *    (MOTION_TYPE_MSK(MOTION_TYPE_SIMPLE_ACTION) | MOTION_TYPE_MSK(MOTION_TYPE_TILT))
 *
 * One object can add only one listener, that is, you remove the listener by using the same object instance.
 *
 * isActiveListen parameter indicate if this listener drive the motion detector to register sensor manager for
 * g-sensor events. This parameter is used for listener which just want to listen to what motion are detected
 * because other active listener. For example, a object can do a passive listen on the background to see if
 * there exist other listener interested in some motion events and will not cause the g-sensor to turn-on all
 * the times if there do not exist any active listener.
 *
 * isListenOnPowerSavingMode indicate that the listener need to detect motion even in power saving mode
 * If there exist any client set this flag to TURE will cause the sensor turned on in power saving mode
 * and will consume more energy. Note that in some product, there may have problem if we do not turn-off
 * the sensor before going into power saving mode.
 *
 * @param pThis Pointer to the object supporting IMotion interface
 * @param type motion type
 * @param isActiveListen will this listener trigger g-sensor to run or just listen to current status according to the other listener's result
 * @param isListenOnPowerSavingMode indicate that the listener need to detect motion even in power saving mode
 * @param pMotionChangedCb the function which will be called to notify the detection of specific motion
 * @param pListener user object
 */
#define IMOTIONDETECTOR_AddChangeListener(pThis, types, isActiveListen, pMotionChangedCb, pListener)	GET_FUNCTBL(pThis,IMotionDetector)->AddChangeListener(pThis, types, isActiveListen, FALSE, pMotionChangedCb, pListener)
#define IMOTIONDETECTOR_AddChangeListenerEx(pThis, types, isActiveListen, isListenOnPowerSavingMode, pMotionChangedCb, pListener)	GET_FUNCTBL(pThis,IMotionDetector)->AddChangeListener(pThis, types, isActiveListen, isListenOnPowerSavingMode, pMotionChangedCb, pListener)

/**
 * Remove a motion change listener from motion detector.
 *
 * @param pThis Pointer to the object supporting IMotion interface
 * @param pListener user object
 */
#define IMOTIONDETECTOR_RemoveChangeListener(pThis, pListener)							GET_FUNCTBL(pThis,IMotionDetector)->RemoveChangeListener(pThis, pListener)


MAE_Ret MAEMotionDetector_New(MAE_ClsId nClsID, void **ppObj);

#endif //  __MAE_MOTIONDETECTOR_H__
