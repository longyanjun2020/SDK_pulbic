/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *     mgl_MD2_loader.h
 *
 *
 * HISTORY
 *      2009.09.24       Chunwei Wang         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */
#ifndef __M_MD2_LOADER_H__
#define __M_MD2_LOADER_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Animation_loader.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Transform.h"

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
enum
{
    MD2ANIM_STAND = 0,
    MD2ANIM_RUN,
    MD2ANIM_ATTACK,
    MD2ANIM_PAIN_A,
    MD2ANIM_PAIN_B,
    MD2ANIM_PAIN_C,
    MD2ANIM_JUMP,
    MD2ANIM_FLIP,
    MD2ANIM_SALUTE,
    MD2ANIM_FALLBACK,
    MD2ANIM_WAVE,
    MD2ANIM_POINT,
    MD2ANIM_CROUCH_STAND,
    MD2ANIM_CROUCH_WALK,
    MD2ANIM_CROUCH_ATTACK,
    MD2ANIM_CROUCH_PAIN,
    MD2ANIM_CROUCH_DEATH,
    MD2ANIM_DEATH_FALLBACK,
    MD2ANIM_DEATH_FALLFORWARD,
    MD2ANIM_DEATH_FALLBACKSLOW,
    MD2ANIM_BOOM,
    MD2ANIM_MAX,
};
typedef mgl_s16 MD2AnimType;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

mgl_boolean mgl_IsMD2FileExtension(const mgl_s8 *pFilename);
mgl_s16 mgl_LoaderMD2ModelFromFile(const mgl_u16 *pu16Filename);
mgl_s16 mgl_LoaderMD2ModelFromMem(const mgl_u8 *pRawData, const mgl_u32 rawDataSize);
mgl_void mgl_CleanUpMD2Model(mgl_s16 md2ID);
mgl_void mgl_RenderMD2Frame(mgl_s16 md2ID, mgl_s32 frameNum);
mgl_s32 mgl_GetMD2FrameNum(mgl_s16 md2ID);
mgl_void mgl_SetMD2TextureInfo(mgl_s16 md2ID, T_TEXTURE_ATTR_PTR pTexAttri);
mgl_void mgl_SetMD2Interpolation(mgl_s16 md2ID, mgl_float interp);
mgl_void mgl_SetMD2TransformInfo(mgl_s16 md2ID, TransformOP *pTransform, mgl_u16 transNum);

#ifdef  __cplusplus
}
#endif


#endif /* __M_MD2_LOADER_H__ */
