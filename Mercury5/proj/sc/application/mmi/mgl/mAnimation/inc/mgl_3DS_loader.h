/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *     mgl_3DS_loader.h
 *
 *
 * HISTORY
 *      2011.01.21       Golden Chen         Initial Version ( abstract from Benson Yang )
 *                                          
 *----------------------------------------------------------------------------- 
 */
#ifndef __M_3DS_LOADER_H__
#define __M_3DS_LOADER_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Animation_loader.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_Scene_Environment.h"


/*------------------------------------------------------------------------------
    Marco
-------------------------------------------------------------------------------*/
#define MGL_3DS_OBJ_MAX 30
#define MGL_3DS_NODE_MAX 30

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef struct _3DSObjectImageInfo_t _3DSObjectImageInfo, *_3DSObjectImageInfo_PTR;
struct _3DSObjectImageInfo_t
{
    mgl_s32 id_texture;
    mgl_u16 nImageWidth;
    mgl_u16 nImageHeight;
    mgl_boolean bMirrorVert;
    mgl_boolean bMirrorHorz;
    T_TEXTURE_SOURCE_DATA TexData;
    T_TEXTURE_ATTR_DATA TexAttrData;
};

typedef struct _3DSObjectAlphaInfo_t
{
    mgl_float nStartAlpha;  
    mgl_float nEndAlpha;
    mgl_float nCurrAlpha;		
}_3DSObjectAlphaInfo;

typedef mgl_u8 _3DSObjectPickColorInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

mgl_boolean mgl_Is3DSFileExtension(const mgl_s8 *pFilename);
mgl_s16 mgl_Loader3DSModelFromFile(const mgl_u16 *pu16Filename);
mgl_s16 mgl_Loader3DSModelFromMem(const mgl_u8 *pRawData, const mgl_u32 rawDataSize);
mgl_void mgl_CleanUp3DSModel(mgl_s16 _3dsID);
mgl_s32 mgl_Get3DSFrameNum(mgl_s16 _3dsID);
mgl_void mgl_Render3DSFrame(mgl_s16 _3dsID, mgl_u32 u32FrameIndex);
mgl_s32 mgl_LoaderGetObjectIdx(mgl_s16 _3dsID, mgl_s8 *pName);

mgl_void mgl_PlayerSetSingleKeyFrameMode(mgl_s16 _3dsID, mgl_boolean isKeyFrameMode);
mgl_void mgl_PlayerSetAlignCenter(mgl_s16 _3dsID, mgl_boolean isAlignCenter);

mgl_u8 mgl_Get3DSObjectPickingColor(mgl_s16 _3dsID, mgl_u32 u32ObjIdx);
mgl_void mgl_Set3DSTransformInfo(mgl_s16 _3dsID, TransformOP *pTransform, mgl_u16 transNum);
mgl_void mgl_Set3DSObjTransformInfo(mgl_s16 _3dsID, mgl_u32 u32ObjIdx, TransformOP *pTransform, mgl_u16 transNum);
mgl_void mgl_Set3DSObjectImageInfo(mgl_s16 _3dsID, mgl_u32 u32ObjIdx, _3DSObjectImageInfo *pImageInfo);
mgl_void mgl_Set3DSObjectAlphaInfo(mgl_s16 _3dsID, mgl_u32 u32ObjIdx, _3DSObjectAlphaInfo *pAlphaInfo);
mgl_void mgl_Set3DSObjectTextureInfo(mgl_s16 _3dsID, mgl_u32 u32ObjIdx, T_TEXTURE_ATTR_PTR pTexAttri);
mgl_void mgl_Set3DSHasAnimation(mgl_boolean bHasAnimation);

mgl_u32 mgl_LoaderGetStartFrame(mgl_s16 _3dsID);
mgl_u32 mgl_LoaderGetEndFrame(mgl_s16 _3dsID);
mgl_u32 mgl_LoaderGetObjectNum(mgl_s16 _3dsID);
mgl_s8* mgl_LoaderGetObjectName(mgl_s16 _3dsID, mgl_u32 u32ObjIdx);

mgl_void mgl_LoaderAdjustCameraZ(mgl_float zOffset);

#ifdef  __cplusplus
}
#endif


#endif /* __M_MD2_LOADER_H__ */
