/**
* @file    mae_motiondetector_priv.h
* @brief
*
*
* @author  mark.yang@mstarsemi.com
* @version $Id: mae_motiondetector_priv.h 291 2009-02-27 13:08:01Z kenny.wu $
*/
#ifndef __MAE_MOTIONDETECTOR_PRIV_H__
#define __MAE_MOTIONDETECTOR_PRIV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_sensormgr_types.h"

typedef enum
{
    DETECTOR_STATUS_PROCESSING = 0,	/**< indicate that the detector need more g-sensor to detector the motion */
    DETECTOR_STATUS_DETECTED		/**< indicate that the detector found a specific motion behavior,
								         the motion is set the the 3rd parameter */
}DETECTOR_STATUS_e;

typedef enum
{
    DETECTOR_TYPE_STATE_ORIENTED = 0,	/**< the motion detector always stay on some state and changes between these states. e.g. the handset must have a orientation state */
    DETECTOR_TYPE_ACTION_ORIENTED		/**< the motion detector only stay on such state in a short time and return to idle state in most time. e.g. before a shake action is done. the state stays on unshakted state */
}DETECTOR_TYPE_e;

struct _MotionDector_s;
typedef struct _MotionDector_s _MotionDector_st;

typedef struct
{
	DETECTOR_TYPE_e eDetectorType;
	SENSOR_NOTIFY_DELAY_e eDelayLevel;
	_MotionDector_st* (*Detector_New)();
	DETECTOR_STATUS_e (*PfnDetector_Analyze)(_MotionDector_st *pDectorHandle, GSensorInfo_t *pGSensorInfo);
	MotionValue_t (*PfnDetector_GetResult)(_MotionDector_st *pDectorHandle);
	void (*PfnDetector_Release)(_MotionDector_st *pDectorHandle);
}_DetectorImpl_t;

#endif //  __MAE_MOTIONDETECTOR_PRIV_H__
