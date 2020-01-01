#ifndef __MAE_MOTIONDETECTOR_ORIENTATION_H__
#define __MAE_MOTIONDETECTOR_ORIENTATION_H__
#include "mmi_mae_sensormgr_forward.h"
#include "mmi_mae_motiondetector.h"
#include "mae_motiondetector_priv.h"

/**
 * Create the orientation detector 
 */
_MotionDector_st* _MotionDetector_Orientation_New(ISENSORMGR *pISensorMgr);

/**
 * Analyze the g-sensor value 
 */
DETECTOR_STATUS_e _MotionDetector_Orientation_Analyze(_MotionDector_st *pDectorHandle, GSensorInfo_t *pGSensorInfo);

/**
 * Release the orientation detector instance
 */
void _MotionDetector_Orientation_Release(_MotionDector_st *pDectorHandle);


MotionValue_t _MotionDetector_Orientation_GetResult(_MotionDector_st *pDectorHandle);

#endif
