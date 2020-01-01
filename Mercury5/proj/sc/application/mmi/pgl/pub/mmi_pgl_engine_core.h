/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_Engine_Core.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_ENGINE_CORE_INC__
#define __MMI_PGL_ENGINE_CORE_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_utility_types.h"
#include "mmi_pgl_engine_scene.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
enum
{
    ePGL_ENGINE_SCENE_SWITCH_NO_ANIM = 0,
    ePGL_ENGINE_SCENE_SWITCH_ALPHA_ANIM,
    ePGL_ENGINE_SCENE_SWITCH_MOVE_ANIM,
    ePGL_ENGINE_SCENE_SWITCH_NULL,
} ;
typedef pgl_u16 ePgl_Scene_SwitchType;


/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
/*Physics World Space APIs*/

/** pgl_Engine_Create
* @brief      Create a PGL Game Engine.
*
* @param[in]  iterations        Number of iterations to use in the impulse solver of PGL to solve contacts.
* @param[in]  space_gravity     Apply Gravity to affect rigid bodies when integrating velocity.
*
* @retval     EngineHandleID   return PGL Engine HandleID.
*
*/
EngineHandleID pgl_Engine_Create(pgl_s32 iterations, Vertex2D space_gravity);

/** pgl_Engine_Reset
* @brief      Reset a PGL Game Engine.
*
* @param[in]  iterations        Reset Number of iterations to use in the impulse solver of PGL to solve contacts.
* @param[in]  space_gravity     Reset Gravity to affect rigid bodies when integrating velocity.
*
* @retval     None.
*
*/
pgl_void pgl_Engine_Reset(EngineHandleID engineID, pgl_s32 iterations, Vertex2D space_gravity);

/** pgl_Engine_Destroy
* @brief      Destroy a PGL Game Engine.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     None.
*
*/
pgl_void pgl_Engine_Destroy(EngineHandleID engineID);

/** pgl_Engine_Render
* @brief      Render all valid Actors of a PGL Game Engine.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     None.
*
*/
pgl_void pgl_Engine_Render(EngineHandleID engineID);

/** pgl_Engine_Update
* @brief      Update the PGL physics space forward based on fps.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  nfps              frames per second.
* @retval     None.
*
*/
pgl_void pgl_Engine_Update(EngineHandleID engineID, pgl_u16 nfps);

/** pgl_Engine_DirectorScene
* @brief      Director to other scene of PGL engine.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  sceneID           PGL Scene HandleID
* @param[in]  sceneSwitchType   Set Scene animation type for scene switch.
* @param[in]  animFrame         Set animation frame for scene switch.
*
* @retval     None.
*
*/
pgl_void pgl_Engine_DirectorScene(EngineHandleID engineID, SceneHandleID sceneID, ePgl_Scene_SwitchType sceneSwitchType, pgl_u16 animFrame);

/** pgl_Engine_CheckVaild
* @brief      Check PGL game engine is valid or not.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     pgl_boolean       return TRUE if PGL game engine is valid.
*
*/
pgl_boolean pgl_Engine_CheckVaild(EngineHandleID engineID);

/** pgl_Engine_isPause
* @brief      Check PGL game engine was paused or not.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     pgl_boolean       return TRUE if PGL game engine was paused.
*
*/
pgl_boolean pgl_Engine_isPause(EngineHandleID engineID);

/** pgl_Engine_isSceneSwitch
* @brief      Check PGL game engine is switch scene page or not.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     pgl_boolean       return TRUE if PGL game engine is switch scene page.
*
*/
pgl_boolean  pgl_Engine_isSceneSwitch(EngineHandleID engineID);

/** pgl_Engine_GetCurrentScene
* @brief      Get current scene page handleID.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     SceneHandleID     return current scene page handleID.
*
*/
SceneHandleID pgl_Engine_GetCurrentScene(EngineHandleID engineID);

/** pgl_ShiftCamera
* @brief      To shift camera position .
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  val               Camera shift value.
*
* @retval     None.
*
*/
pgl_void pgl_ShiftCamera(EngineHandleID engineID, Vertex3D val);

/** pgl_ResetCamera
* @brief      Reset Camera position into initial conditon.
*
* @param[in]  engineID          PGL Engine HandleID.
*
* @retval     None.
*
*/
pgl_void pgl_ResetCamera(EngineHandleID engineID);

/** pgl_SetCameraEnable
* @brief      Enable camera operation or not for PGL game engine.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  val               enable flag.

* @retval     None.
*
*/
pgl_void pgl_SetCameraEnable(EngineHandleID engineID, pgl_boolean val);


#endif

