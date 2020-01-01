/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_engine_scene.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_ENGINE_SCENE_INC__
#define __MMI_PGL_ENGINE_SCENE_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_utility_types.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define PGL_SCENE_NULL          -1
#define SCENEID_2_LAYERID(x)    (1 << (x))
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef pgl_s32 SceneHandleID;

enum
{
    ePGL_SCENE_LAYER_BG = 0,        /*only ImageActor*/
    ePGL_SCENE_LAYER_NOCPLAY,       /*ImageActor*/
    ePGL_SCENE_LAYER_CPLAY,         /*All Physics Actors*/
    ePGL_SCENE_LAYER_GUI_CONTROL,   /*All GUI Actors ex:ImageActor, ButtonActor, TxtActor*/
    ePGL_SCENE_LAYER_MAX,
} ;
typedef pgl_u16 ePgl_Layer_Type;

typedef void (*FPPglSceneUserDefinedDrawBGFuncCB)(pgl_void *pUserData);
typedef void (*FPPglSceneOnFoucsFuncCB)(EngineHandleID engineID, SceneHandleID sceneID, pgl_void *pUserData);
typedef void (*FPPglSceneUnFoucsFuncCB)(EngineHandleID engineID, SceneHandleID sceneID, pgl_void *pUserData);
typedef void (*FPPpglSceneUpdateFuncCB)(EngineHandleID engineID, SceneHandleID sceneID, pgl_void *pUserData);


/** PglSceneFuncTable_t
*
* @brief    fpSceneUserDefinedDrawBGFuncCB:     The User Defined Back-Ground Scene page render call back function.
*           fpSceneOnFoucsFuncCB:               The Scene On-Focus call back function.
*           fpSceneUnFoucsFuncCB:               The Scene Un-Focus call back function.
*           fpSceneUpateFuncCB:                 The Scene Update call back function.
*           pUserData:                          Pointer to userData.
*
*/
typedef struct PglSceneFuncTable_tag
{
    FPPglSceneUserDefinedDrawBGFuncCB   fpSceneUserDefinedDrawBGFuncCB;      //Just for speeding up BG layer by user-defined draw CB.
    FPPglSceneOnFoucsFuncCB             fpSceneOnFoucsFuncCB;
    FPPglSceneUnFoucsFuncCB             fpSceneUnFoucsFuncCB;
    FPPpglSceneUpdateFuncCB             fpSceneUpateFuncCB;
    pgl_void                            *pUserData;
}PglSceneFuncTable_t;


/** PglSceneInfo_t
*
* @brief    sceneFuncTable:                     The scene call back function Table.
*           blayerVisualFlag:                   The valid flag of each scene layer page .
*
*/
typedef struct PglSceneInfo_tag
{
    PglSceneFuncTable_t sceneFuncTable;
    pgl_boolean  blayerVisualFlag[ePGL_SCENE_LAYER_MAX];
}PglSceneInfo_t;


/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
/** pgl_Engine_Scene_Create
* @brief      Create a new scene page and add it to PGL engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  pSceneInfo        Pointer to scene parameters to be used for creating a scene page.
*
* @retval     SceneHandleID     return PGL Scene HandleID.
*
*/
SceneHandleID pgl_Engine_Scene_Create(EngineHandleID engineID, PglSceneInfo_t *pSceneInfo);

/** pgl_Engine_Scene_Clear
* @brief      Clear scene page and reset it at PGL engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID that need to clear.
*
* @retval     None.
*
*/
pgl_void pgl_Engine_Scene_Clear(EngineHandleID engineID, SceneHandleID sceneID);

/** pgl_Engine_Scene_Destroy
* @brief      Destroy scene page and remove it from PGL engine space.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID that need to Destroy.
*
* @retval     None.
*
*/
pgl_void pgl_Engine_Scene_Destroy(EngineHandleID engineID, SceneHandleID sceneID);

/** pgl_Engine_Scene_CheckVaild
* @brief      Check scene page of PGL game engine is valid or not.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if scene page is valid.
*
*/
ePgl_RetCode pgl_Engine_Scene_CheckVaild(EngineHandleID engineID, SceneHandleID sceneID);

/** pgl_Engine_Scene_SetLayerVisual
* @brief      Set scene layer page of PGL game engine is valid or not.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID.
* @param[in]  elayer            PGL layer type.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if scene layer page is set successfully.
*
*/
ePgl_RetCode pgl_Engine_Scene_SetLayerVisual(EngineHandleID engineID, SceneHandleID sceneID, ePgl_Layer_Type elayer, pgl_boolean bVisual);

/** pgl_Engine_Scene_SetLayerVisual
* @brief      Check scene layer page of PGL game engine is valid or not.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID.
* @param[in]  elayer            PGL layer type.
*
* @retval     pgl_boolean       return TURE if scene layer page is valid.
*
*/
pgl_boolean pgl_Engine_Scene_GetLayerVisual(EngineHandleID engineID, SceneHandleID sceneID, ePgl_Layer_Type elayer);

/** pgl_Engine_Scene_Get_UserData
* @brief      Get the user data of PGLscene page.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID.
*
* @retval     pgl_void*         Pointer to scene user data.
*
*/
pgl_void* pgl_Engine_Scene_Get_UserData(EngineHandleID engineID, SceneHandleID nSceneID);
#endif

