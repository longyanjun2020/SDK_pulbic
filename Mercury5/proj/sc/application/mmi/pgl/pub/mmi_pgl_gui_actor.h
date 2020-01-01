/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_gui_actor.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_GUI_ACTOR_INC__
#define __MMI_PGL_GUI_ACTOR_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_utility_types.h"
#include "mmi_pgl_resource_texmgr.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define PGL_GUIACTOR_NULL          0
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
enum
{
    ePGL_GUI_IMAGE = 0,
    ePGL_GUI_BUTTON,
    ePGL_GUI_LINE,
} ;
typedef pgl_u16 ePgl_Gui_Type;
typedef pgl_s32 hGuiActor;          /*User-Defined Collision type of input-Actor*/
typedef void (*FPGuiActorTouchPressCB)(hGuiActor hGuiActorNode, pgl_void *pUserData);
typedef void (*FPGuiActorTouchMoveCB)(hGuiActor hGuiActorNode, pgl_u32 Touches_x, pgl_u32 Touches_y, pgl_void *pUserData);
typedef void (*FPGuiActorTouchReleaseCB)(hGuiActor hGuiActorNode, pgl_void *pUserData);

/** GuiActorTouchesCBFunc_t
*
* @brief    fpGuiTouchPressfunCb:       The Touch press call back functiom for Gui button actor.
*           fpGuiTouchMovefunCb:        The Touch move call back functiom for Gui button actor.
*           fpGuiTouchReleasefunCb:     The Touch release call back functiom for Gui button actor.
*           pUserData:                  Pointer to userData of Gui button actor.
*
*/
typedef struct GuiActorTouchesCBFunc_tag
{
    FPGuiActorTouchPressCB      fpGuiTouchPressfunCb;
    FPGuiActorTouchMoveCB       fpGuiTouchMovefunCb;
    FPGuiActorTouchReleaseCB    fpGuiTouchReleasefunCb;
    pgl_void                    *pUserData;
}GuiActorTouchesCBFunc_t;

/** PglGuiButton_t
*
* @brief    touchesCBFunc:      The Touch call back functiom table of Gui button actor.
*
*/
typedef struct PglGuiButton_tag
{
    hTexRes                 nPressID;
    hTexRes                 nReleaseID;   
	GuiActorTouchesCBFunc_t touchesCBFunc;
}PglGuiButton_t;

/** PglGuiLine_tag
*
* @brief    p2:                 End position of Gui line segment.
*           lineWidth:          Line width.
*
*/
typedef struct PglGuiLine_tag
{
    Vertex2D p2;
    int lineWidth;
}PglGuiLine_t;

/** PglGuiImage_t
*
* @brief    curTimerStep:       Current frame step of Gui sprite image.
*           curFragment:        Current frame index of Gui sprite image.
*           curLoopCycle:       Current repeat cycle index of Gui sprite image.
*           fragmentStep:       User-defined frame step of Gui sprite image.
*           spriteLoopCycle:    User-defined repeat cycle index of Gui sprite image.
*
*/
typedef struct PglGuiImage_tag
{
    pgl_u32             curTimerStep;
    pgl_u8              curFragment;
    pgl_u32             curLoopCycle;
    pgl_u32             fragmentStep;
    pgl_u32             spriteLoopCycle;
}PglGuiImage_t;

/** GuiActorInfo_t
*
* @brief    engineID:           Engine HandleID of Gui actor.
*           sceneID:            Scene HandleID of Gui actor.
*           layerType:          Layer type of Gui actor.
*           p:                  Position of Gui actor.
*           size:               Size of Gui actor.
*           engineID:           Engine HandleID of Gui actor.
*           sceneID:            Scene HandleID of Gui actor.
*           layerType:          Layer type of Gui actor.
*           guiItemType:        Shape type of Gui actor.
*           resID:              Texture res hangleID of Gui actor.
*           angle:              Angle of Gui actor.
*           color:              Color of Gui actor.
*           status:             Status of Gui actor.
*           button:             Settings for Gui button actor.
*           line:               Settings for Gui line actor.
*           image:              Settings for Gui image actor.
*
*/
typedef struct GuiActorInfo_tag
{
    EngineHandleID      engineID;
    SceneHandleID       sceneID;
    ePgl_Layer_Type     layerType;
    Vertex2D            p;
    Vertex2D            size;
    ePgl_Gui_Type       guiItemType;
    hTexRes             resID;
    pgl_float           angle;
    Color4f             color;
    pgl_s32             status;

    union
    {
        PglGuiButton_t  button;                /* for button */
        PglGuiLine_t    line;
        PglGuiImage_t   image;
    }uGuiInfos;
}GuiActorInfo_t;

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
/*Gui Actor APIs*/

/** pgl_Gui_Actor_Add
* @brief      Add a gui Actor into PGL game engine space.
*
* @param[in]  pGuiInfo          Pointer to Gui actor parameters to be used for creating a Gui actor.
*
* @retval     hGuiActor         return Gui actor handleID.
*
*/
hGuiActor pgl_Gui_Actor_Add(GuiActorInfo_t *pGuiInfo);

/** pgl_Gui_Actor_Modify
* @brief      Modify a gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  pGuiInfo          Pointer to Gui actor parameters to be used for modifying a Gui actor.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if Gui actor is modified successfully.
*
*/
ePgl_RetCode pgl_Gui_Actor_Modify(hGuiActor guiActor, GuiActorInfo_t *pGuiInfo);

/** pgl_Gui_Actor_ModifyTexResID
* @brief      Modify texture res handleID of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  TexReID           Texture resource handleID.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if Gui actor resID is modified successfully.
*
*/
ePgl_RetCode pgl_Gui_Actor_ModifyTexResID(hGuiActor guiActor,hTexRes TexReID);

/** pgl_Gui_Actor_GetTexResID
* @brief      Get texture res handleID of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
*
* @retval     hTexRes           return Texture resource handleID.
*
*/
hTexRes pgl_Gui_Actor_GetTexResID(hGuiActor guiActor);

/** pgl_Gui_Actor_Destroy
* @brief      Destroy a gui Actor from PGL game engine space.
*
* @param[in]  sceneID           PGL Scene HandleID.
* @param[in]  elayer            PGL layer type.
* @param[in]  guiActor          Gui actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_Destroy(SceneHandleID sceneID, ePgl_Layer_Type elayer, hGuiActor guiActor);

/** pgl_Gui_Actor_SetSize
* @brief      Set size of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  width             Width value.
* @param[in]  height            Height value.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_SetSize(hGuiActor guiActor,pgl_float width, pgl_float height);

/** pgl_Gui_Actor_SetPosition
* @brief      Set Position of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  x                 X position.
* @param[in]  y                 Y Position
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_SetPosition(hGuiActor guiActor, pgl_float pos_x, pgl_float pox_y);

/** pgl_Gui_Actor_GetPositionX
* @brief      Get X Position of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
*
* @retval     pgl_float         X position.
*
*/
pgl_float pgl_Gui_Actor_GetPositionX(hGuiActor guiActor);

/** pgl_Gui_Actor_GetPositionY
* @brief      Get Y Position of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
*
* @retval     pgl_float         Y position.
*
*/
pgl_float pgl_Gui_Actor_GetPositionY(hGuiActor guiActor);

/** pgl_Gui_Actor_GetStatus
* @brief      Get status of gui Actor.
*
* @param[in]  guiActor          Gui actor handleID.
*
* @retval     pgl_float         Gui actor's status.
*
*/
pgl_s32 pgl_Gui_Actor_GetStatus(hGuiActor guiActor);

/** pgl_Gui_Actor_SetTouchMove
* @brief      Move Gui actor based on touch move infos.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  Touches_x         Touch X position.
* @param[in]  Touches_y         Touch Y position.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_SetTouchMove(hGuiActor guiActor, pgl_u32 Touches_x, pgl_u32 Touches_y);

/** pgl_Gui_Actor_SetRotation
* @brief      Set Rotation of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  rot_angle         Rotation Angle.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_SetRotation(hGuiActor guiActor, pgl_float rot_angle);

/** pgl_Gui_Actor_SetStatus
* @brief      Set status of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  status            Status of Gui actor.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_SetStatus(hGuiActor guiActor, pgl_s32 status);

/** pgl_Gui_Actor_SetColor
* @brief      Set color of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  r                 Red channel.
* @param[in]  g                 Green channel.
* @param[in]  b                 Blue channel.
* @param[in]  a                 Alpha channel.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_SetColor(hGuiActor guiActor, pgl_float r, pgl_float g, pgl_float b, pgl_float a);

/*Gui Actor Action APIs*/
typedef pgl_void (*FPPglActorDelayCBFunc)(hGuiActor hActorNode, pgl_void *pUserData);
/** pgl_Gui_Actor_Delay
* @brief      Apply Delay action of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  duration          Animation time.
* @param[in]  fpDelayCBFunc     The delay call back function .
* @param[in]  pUserData         Pointer to userData.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_Delay(hGuiActor guiActor, pgl_s32 duration, FPPglActorDelayCBFunc fpDelayCBFunc, pgl_void *pUserData);

/** pgl_Gui_Actor_MoveTo
* @brief      Apply MoveTo action of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  newPosition       The last animation position of Gui actor.
* @param[in]  duration          Animation time.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_MoveTo(hGuiActor guiActor,Vertex2D newPosition, pgl_s32 duration);

/** pgl_Gui_Actor_RotateTo
* @brief      Apply RotateTo action of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  newRotation       The last animation rotation angle of Gui actor.
* @param[in]  duration          Animation time.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_RotateTo(hGuiActor guiActor, pgl_float newRotation, pgl_s32 duration);

/** pgl_Gui_Actor_JumpTo
* @brief      Apply JumpTo action of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
* @param[in]  jumpheight        The last animation height of Gui actor.
* @param[in]  duration          Animation time.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_JumpTo(hGuiActor guiActor,Vertex2D jumpheight, pgl_s32 duration);

/** pgl_Gui_Actor_Remove_Action
* @brief      Remove action of Gui actor.
*
* @param[in]  guiActor          Gui actor handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Gui_Actor_Remove_Action(hGuiActor guiActor);

#endif

