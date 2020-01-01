#ifndef __M_SCENE_ENVIRONMENT_H__
#define __M_SCENE_ENVIRONMENT_H__
/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Scene_Environment.h
 *
 *
 * HISTORY
 *      2009.09.24       Chunwei Wang         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Core_Types.h"
#include "mgl_Core_Matrix.h"
#include "mgl_Scene_NodeMgr.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef enum mSceneMode_Tag
{
    SCENE_3D_UI,
    SCENE_2D_UI,
    SCENE_NATIVE_3D,
    SCENE_AR,
    SCENE_NOT_DEFINE,
}mSceneMode;

enum 
{
    SCENE_DEPTH = 0x01,
    SCENE_CULLFACE = 0x02,
    SCENE_NICE_PERSPECTIVE = 0x04,
    SCENE_AAPLANE = 0x08,
};
typedef mgl_u16 mSceneCap;

enum
{
    SCENE_DEPTH_BUFFER = 0x01,
    SCENE_COLOR_BUFFER = 0x02,	
};
typedef mgl_u16 mSceneBuffer;

typedef enum mSceneBlendingOP_Tag
{
    SRC_ALPHA_with_ONE_MINUS_SRC_ALPHA,
    ONE_with_ONE,    
    SRC_ONE_with_ONE_MINUS_SRC_ALPHA,
    SRC_ALPHA_with_ONE,
}mSceneBlendingOP;  
	  	
typedef enum mSceneFogOP_Tag
{
    FOG_LINEAR,
    FOG_EXP,
    FOG_EXP2,   
}mSceneFogOP; 

enum
{
    TEXTURE_FILTER_LINEAR = 0x01,
    TEXTURE_FILTER_NEAREST = 0x02,	
    TEXTURE_FILTER_BILINEAR = 0x04,
};
typedef mgl_u16 TextureFilter;

enum
{
    TEXTURE_WRAP_CLAMP = 0x01,
    TEXTURE_WRAP_REPEAT = 0x02,	
};
typedef mgl_u16 TextureWrap;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_void mgl_Scene_SetViewPort(mgl_s32 x, mgl_s32 y, mgl_s32 width, mgl_s32 height);
mgl_void mgl_Scene_SetBGColor(mgl_float r, mgl_float g, mgl_float b, mgl_float a);
mgl_void mgl_Scene_SetColorMask(mgl_boolean redChannel, mgl_boolean greenChannel, mgl_boolean blueChannel);
mgl_void mgl_Scene_ClearBuffer(mSceneBuffer bufferEum);
mgl_void mgl_Scene_SetMode(mSceneMode mode);
mSceneMode mgl_Scene_QueryMode(mgl_void);
mgl_void mgl_Scene_SetCap(mSceneCap cap, mgl_boolean enable);
mgl_boolean mgl_Scene_QueryCap(mSceneCap cap);
mgl_void mgl_Scene_SetClientAreaBegin(mgl_s32 x, mgl_s32 y, mgl_s32 width, mgl_s32 height);
mgl_void mgl_Scene_SetClientAreaEnd(mgl_void);
mgl_void mgl_Scene_SetSceneAttribute(mgl_boolean IsConsiderDepthOrder, mgl_boolean IsDrawBackFace, mgl_boolean IsNicePerspective);
mgl_void mgl_Scene_SetBlendingFunc(mSceneBlendingOP BlendingOP);
mgl_boolean mgl_Scene_Picking_RayIntersection(mgl_s32 x2D, mgl_s32 y2D, AABBox3D bbox, Matrix4x4 matrix);
mgl_void mgl_Scene_SetTextureFilter(TextureFilter filter);
TextureFilter mgl_Scene_GetTextureFilter(mgl_void);
mgl_void mgl_Scene_SetTextureWrap(TextureWrap wrap);
TextureFilter mgl_Scene_GetTextureWrap(mgl_void);
mgl_void mgl_Scene_SetFogFunc(mSceneFogOP fog_op, Color4f* fog_color, mgl_u32 fog_start, mgl_u32 fog_end, mgl_u32 fog_density); /* dummy if MGLS */
mgl_void mgl_Scene_SetOrientation(mgl_u8 platform_orientation);
mgl_u8 mgl_Scene_GetOrientation(mgl_void);
mgl_void mgl_Scene_SetARMatrix(Matrix4x4 *pModelView, Matrix4x4 *pProjection);
#endif /* __M_SCENE_ENVIRONMENT_H__ */

