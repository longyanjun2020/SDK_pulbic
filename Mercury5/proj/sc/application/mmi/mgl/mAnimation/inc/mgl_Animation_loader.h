/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Animation_loader.h
 *
 *
 * HISTORY
 *      2009.09.24       Chunwei Wang         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */
#ifndef __M_ANIMATION_LOADER_H__
#define __M_ANIMATION_LOADER_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"
#include "mgl_Utility_file.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define MAX_ANIMATION_COUNT 4
#define NOT_FOUND_ANIMATION -1

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef enum 
{
    MGL_AMT_UNKNOWN = 0,     //! Unknown animated mesh type.
    MGL_AMT_MD2,     //! Quake 2 MD2 model file     
    MGL_AMT_3DS,     //! 3DS model file
}mgl_MeshType_e;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef  __cplusplus
extern "C" {
#endif

mgl_s16 mgl_Animation_FileLoader(const mgl_u16 *pu16Filename);
mgl_s16 mgl_Animation_MemLoader(mgl_u8 *pRawData, mgl_u32 rawDataSize, mgl_MeshType_e aniMeshType);
mgl_void mgl_Animation_CleanUp(mgl_u16 animationID);
mgl_void mgl_Animation_RenderFrame(mgl_u16 animationID, mgl_s32 frameNum);
#ifdef  __cplusplus
}
#endif


#endif /* __M_ANIMATION_LOADER_H__ */
