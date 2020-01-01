#ifndef __MAE_MOTIONDETECTOR_TURNOVER_H__
#define __MAE_MOTIONDETECTOR_TURNOVER_H__
#include "mmi_mae_sensormgr_forward.h"
#include "mmi_mae_motiondetector.h"
#include "mae_motiondetector_priv.h"

/**
 * Create the turnover detector 
 */
_MotionDector_st* _MotionDetector_Turnover_New(ISENSORMGR *pISensorMgr);

/**
 * Analyze the g-sensor value 
 */
DETECTOR_STATUS_e _MotionDetector_Turnover_Analyze(_MotionDector_st *pDectorHandle, GSensorInfo_t *pGSensorInfo);

/**
 * Release the turnover detector instance
 */
void _MotionDetector_Turnover_Release(_MotionDector_st *pDectorHandle);


MotionValue_t _MotionDetector_Turnover_GetResult(_MotionDector_st *pDectorHandle);

#endif
