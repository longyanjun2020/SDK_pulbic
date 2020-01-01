/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      pgl_Gui_Render.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __PGL_GUI_RENDER_INC__
#define __PGL_GUI_RENDER_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "pgl_Utility_Types.h"
#include "pgl_Resource_TexMgr.h"
#include "pgl_Engine_Scene.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef struct PglGuiActorRenderInfo_t_tag
{
    EngineHandleID engineID;
    pgl_u16 guiSceneHandleId;
    pgl_u32 guiSceneNodeId;
    pgl_float guiSceneAlpha;
}PglGuiActorRenderInfo_t;

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/
ePgl_RetCode pgl_Gui_RenderMgr_Create(PglGuiActorRenderInfo_t *pRenderInfo);
pgl_void pgl_Gui_RenderMgr_Release(PglGuiActorRenderInfo_t *pRenderInfo);
pgl_void pgl_Gui_Render_World(ePgl_Layer_Type elayer, PglGuiActorRenderInfo_t *pRenderInfo);  

#endif

