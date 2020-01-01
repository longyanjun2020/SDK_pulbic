/**
* @file    mmi_srv_motiondetector.h
* @brief
*
*/

#ifndef __MMI_SRV_MOTIONDETECTOR_H__
#define __MMI_SRV_MOTIONDETECTOR_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_motiondetector.h"

//Specific Service ListenerCallBack API
typedef void (*SrvMotionDetectorOrientationCB)(void *pThis, ORIENTATION_e eResult); //MOTION_TYPE_ORIENTATION
typedef void (*SrvMotionDetectorSimpleActionCB)(void *pThis, SIMPLE_ACTINO_e eResult); //MOTION_TYPE_SIMPLE_ACTION
typedef void (*SrvMotionDetectorTurnOverCB)(void *pThis, TURNOVER_e eResult); //MOTION_TYPE_TRUN_OVER

/** SrvMotionDetectorSetxxxCB
* @brief  Add a motion change CB to motion detector.
*
* @param[out]     pfnCallBack             the function which will be called to notify the detection of specific motion.
*
* @retval  MAE_RET_SUCCESS                If successful.
* @retval  MAE_RET_NOT_SUPPORTED          If exceed the max number of supported listeners for register.
* @retval  MAE_RET_NOT_FOUND              If can not found the listener for deregister.
*/
MAE_Ret SrvMotionDetectorSetOrientationCB(SrvMotionDetectorOrientationCB pfnCallBack);

MAE_Ret SrvMotionDetectorSetSimpleActionCB(SrvMotionDetectorSimpleActionCB pfnCallBack);

MAE_Ret SrvMotionDetectorSetTurnOverCB(SrvMotionDetectorTurnOverCB pfnCallBack);

/** SrvMotionDetectorGetLastStatus
* @brief  Get the last recognized motion.
*
* @param[in]      eType                   Type of motion, the enum value comes from MOTION_TYPE_et
* @param[out]     pOutLastValue           the result, the enum value comes from ORIENTATION_et or SIMPLE_ACTINO_et or etc.
*/
void SrvMotionDetectorGetLastStatus(MOTION_TYPE_e eType, MotionValue_t *pOutLastValue);


#endif /*__MMI_SRV_MOTIONDETECTOR_H__*/
