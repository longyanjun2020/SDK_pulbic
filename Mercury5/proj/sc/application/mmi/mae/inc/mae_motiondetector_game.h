#ifndef __MAE_MOTIONDETECTOR_GAME_H__
#define __MAE_MOTIONDETECTOR_GAME_H__

#include "mmi_mae_sensormgr_forward.h"
#include "mmi_mae_motiondetector.h"
#include "mae_motiondetector_priv.h"

_MotionDector_st* _MotionDetector_GameAction_New(ISENSORMGR *pISensorMgr);
DETECTOR_STATUS_e _MotionDetector_GameAction_Analyze(_MotionDector_st *pDectorHandle, GSensorInfo_t *pGSensorInfo);
MotionValue_t _MotionDetector_GameAction_GetResult(_MotionDector_st *pDectorHandle);
void _MotionDetector_GameAction_Release(_MotionDector_st *pDectorHandle);

#endif
