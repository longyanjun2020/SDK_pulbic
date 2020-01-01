/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Scene_Camera.h
 *
 *
 * HISTORY
 *      2009.10.27       Golden Chen         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_SCENE_CAMERA_H__
#define __M_SCENE_CAMERA_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Core_Types.h"
#include "mgl_Core_Transform.h"
#include "mgl_Core_Matrix.h"
#include "mgl_Scene_Environment.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
enum
{
    CAMERA_WORLD=0,
    CAMERA_3DUI,    
};
typedef mgl_s16 CameraEnv;
enum
{
    CAMERA0 = 0,
    CAMERA1,
    CAMERA2,    
    CAMERA3,    
    CAMERA4,    
    CAMERA5,    
    CAMERA6,    
    CAMERA7,    
    CAMERA_NUM,
    CAMERA_ERROR = -1,
};
typedef mgl_s16 CameraId;

typedef struct CameraInfo_tag
{
    Vertex3D CameraPosition;
    Vertex3D CameraTarget;
    Vertex3D CameraUpVector;
    boolean bActive, bNeedUpdate;
    CameraEnv CameraEnvi;
    Matrix4x4 Camera_Mv;
}CameraInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
CameraId mgl_Camera_Create(CameraEnv cameraEnv);
mgl_void mgl_Camera_Release(CameraId cameraID);
mgl_void mgl_Camera_SetCameraPosition(CameraId cameraID, Vertex3D *pFromPos);
mgl_void mgl_Camera_SetTargetPosition(CameraId cameraID, Vertex3D *pToPos);
mgl_void mgl_Camera_SetUpVector(CameraId cameraID, Vertex3D *pUp);
Vertex3D mgl_Camera_GetCameraPosition(CameraId cameraID);
Vertex3D mgl_Camera_GetCameraTargetPosition(CameraId cameraID);
Vertex3D mgl_Camera_GetUpVector(CameraId cameraID);
mgl_void mgl_Camera_Moving(CameraId cameraID, mgl_float speed);
mgl_void mgl_Camera_StrafeMoving(CameraId cameraID, mgl_float speed);
mgl_void mgl_Camera_RotateView(CameraId cameraID, mgl_float angle);
mgl_void mgl_Camera_RotateTarget(CameraId cameraID, mgl_float angle);
mgl_void mgl_Camera_RotateViewBasedOnAxis(CameraId cameraID, mgl_float angle, Vertex3D *paxis);
mgl_void mgl_Camera_RotateViewBasedOnTSDelta(CameraId cameraID, mgl_float angleY, mgl_float angleZ);
mgl_void mgl_CameraBegin_Global(CameraId cameraID);
mgl_void mgl_CameraEnd_Global(mgl_void);
#endif /* __M_SCENE_CAMERA_H__ */

