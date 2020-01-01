#ifndef __M_SCENE_NODEMGR_H__
#define __M_SCENE_NODEMGR_H__
/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Scene_NodeMgr.h
 *
 *
 * HISTORY
 *      2009.10.16       Chunwei Wang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */


/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"
#include "mgl_Utility_unicode.h"
#include "mgl_Utility_hash.h"
#include "mgl_Core_Transform.h"
#include "mgl_Core_Types.h"
#include "mgl_Core_Matrix.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_ErrCode.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define MAX_SCENE_COUNT (10)
#define NOT_FOUND_SCENE (MAX_SCENE_COUNT + 1)
#define NOT_FOUND_NODE (0)

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef mgl_void (*DrawObject)(mgl_u32 nodeID, mgl_void *pUserData);
typedef mgl_void (*PickObject)(mgl_u32 nodeID, mgl_void *pUserData);
typedef mgl_void (*ReleaseObject)(mgl_u32 nodeID, mgl_void *pUserData);

typedef struct T_NODE_TEXTURE_TAG T_NODE_TEXTURE_DATA, *T_NODE_TEXTURE_PTR;
struct T_NODE_TEXTURE_TAG
{
    T_TEXTURE_SOURCE_DATA TexSrcData;
    T_NODE_TEXTURE_PTR       pTexSrcPrev;
    T_NODE_TEXTURE_PTR       pTexSrcNext;
};

typedef struct T_NODE_ELEMENT_TAG T_NODE_ELEMENT_DATA, *T_NODE_ELEMENT_PTR;
struct T_NODE_ELEMENT_TAG
{
    mgl_u32     nodeID;
    DrawObject    pDraw;
    PickObject      pPick;
    ReleaseObject    pRelease;
    mgl_void         *pUserData;
    mgl_boolean isVisible;
    mgl_boolean isUpdateBBox;
    mgl_boolean isUpdateLocalMatrix;
    AABBox3D  aabox;
    Matrix4x4     globalTransformation;
    Matrix4x4     localTransformation;
    Matrix4x4    absolutionTransformation;
    mgl_u16      textureHandleID;
    mgl_u32       texSourceIndex;
    T_NODE_TEXTURE_PTR       pTexSrcFirst;
    T_NODE_TEXTURE_PTR       pTexSrcLast;
};

typedef struct T_NODE_TAG T_NODE_DATA, *T_NODE_PTR;
struct T_NODE_TAG
{
    T_NODE_PTR       ptHashNext;
    T_NODE_ELEMENT_DATA element;
    T_NODE_PTR       ptPrev;
    T_NODE_PTR       ptNext;
};

typedef struct T_NODE_HASH_TAG T_NODE_HASH_DATA, *T_NODE_HASH_PTR;
struct T_NODE_HASH_TAG
{
    pMGL_Hash_st         ptHash;
    T_NODE_PTR        ptFirst;
    T_NODE_PTR        ptLast;
};

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_ErrCode mgl_SceneMgr_Create(mgl_u16 *pHandleID);
mgl_ErrCode mgl_SceneMgr_AddNode(mgl_u16 handleID, mgl_u32 *pNodeId, DrawObject pDraw, PickObject pPick, ReleaseObject pRelease, mgl_void *pUserData);
mgl_ErrCode mgl_SceneMgr_SetVisible(mgl_u32 *pNodeID, mgl_u16 nodeNum, mgl_boolean isVisible);
mgl_ErrCode mgl_SceneMgr_RenderSceneNode(mgl_u32 *pNodeID, mgl_u16 nodeNum);
mgl_ErrCode mgl_SceneMgr_ReleaseSceneNode(mgl_u32 *pNodeID, mgl_u16 nodeNum);
mgl_ErrCode mgl_SceneMgr_ReleaseSceneNodeTexture(mgl_u32 nodeID, T_TEXTURE_SOURCE_DATA TexSoureData);
mgl_ErrCode mgl_SceneMgr_ReleaseSceneNodeAllTexture(mgl_u32 nodeID);
mgl_ErrCode mgl_SceneMgr_GetSceneNodeTexture(mgl_u32 nodeID, T_TEXTURE_SOURCE_DATA TexSoureData, T_TEXTURE_ATTR_PTR ptIconAttr, mgl_void *pRawData);
mgl_ErrCode mgl_SceneMgr_TraversePickedNode(mgl_u16 handleID, mgl_s32 x, mgl_s32 y);
mgl_ErrCode mgl_SceneMgr_Release(mgl_u16 handleID);
mgl_ErrCode mgl_SceneMgr_ReleaseAllTexture(mgl_u16 handleID);
mgl_ErrCode mgl_SceneMgr_GetNodeElement(mgl_u32 nodeID, T_NODE_ELEMENT_DATA **ppNodeElement);
mgl_void mgl_NodeTextureList_PushEnd(T_NODE_ELEMENT_PTR pNodeElement, T_TEXTURE_SOURCE_PTR pTexSourceData);

#endif /* __M_SCENE_NODEMGR_H__ */

