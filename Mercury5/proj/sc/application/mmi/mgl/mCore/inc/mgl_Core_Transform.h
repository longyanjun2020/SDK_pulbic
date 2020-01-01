/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Core_Transform.h
 *
 *
 * HISTORY
 *      2009.10.04       Golden Chen         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_CORE_TRANSFORM_H__
#define __M_CORE_TRANSFORM_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#ifndef __PC_SIMULATOR__
#define MGL_INLINE /* __attribute__((always_inline)) */
#else
#define MGL_INLINE
#endif

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef enum RotateAxis_tag
{
    ROTATE_X_AXIS,
    ROTATE_Y_AXIS,
    ROTATE_Z_AXIS
}RotateAxis;

typedef struct RotateInfo_tag
{
    RotateAxis axis;
    Vertex3D rotatePivot;    
    mgl_float  rotateFactor;       
}RotateInfo;

typedef struct ScaleInfo_tag
{
  Vertex3D scalePivot;    
  Vertex3D scaleFactor;      
}ScaleInfo;

typedef struct TranslateInfo_tag
{
  Vertex3D translateFactor;    
}TranslateInfo;

typedef struct ArcBallInfo_tag
{
    Vertex3D arcBallPivot;        
    Vertex2D downPt;
    Vertex2D dragPt;
    mgl_u32 boundWidth;
    mgl_u32 boundHeight;
    mgl_boolean *pIsClick;
    mgl_boolean *pIsDrag;
}ArcBallInfo;

typedef enum Transform_tag
{
    TRANSFORM_NONE,
    TRANSFORM_ROTATE,
    TRANSFORM_SCALE,
    TRANSFORM_TRANSLATE,
    TRANSFORM_ARCBALL,
}Transform_e;

typedef struct TransformOP_tag
{
   Transform_e opFun;
   union
   {
        RotateInfo rotate;
        ScaleInfo scale;
        TranslateInfo translate;
        ArcBallInfo arcBall;
   }opData;
}TransformOP;

/*------------------------------------------------------------------------------
    Global inline Function
-------------------------------------------------------------------------------*/
extern MGL_INLINE mgl_void Transform_GLCoordToWindowCoord3D(Vertex3D* p);

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_void mgl_Transform(TransformOP *pTransform); /* internal usage */
mgl_void mgl_TransformBegin(mgl_u32 nodeID, TransformOP *pTransform, mgl_u16 transNum);
mgl_void mgl_TransformEnd(mgl_void);
mgl_void mgl_TransformBegin_Global(mgl_u32 *pNodeID, mgl_u16 nodeNum, TransformOP *pTransform, mgl_u16 transNum);
mgl_void mgl_TransformEnd_Global(mgl_void);

#endif /* __M_CORE_TRANSFORM_H__ */

