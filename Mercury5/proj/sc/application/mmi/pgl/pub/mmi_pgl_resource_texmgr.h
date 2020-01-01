/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_resource_texmgr.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_RESOURCE_TEXMGR_INC__
#define __MMI_PGL_RESOURCE_TEXMGR_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_utility_types.h"
#include "srv_MGL.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define PGL_TEX_NULL            0
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef pgl_s32 hTexRes;

/** PglhTexResInfo_t
*
* @brief    TexInfo:            texture infos of MGL.
*           fragment:           The fragment numbers of texture.
*
*/
typedef struct PglhTexResInfo_tag
{
	TextureInfo TexInfo;
    pgl_u8 fragment;
}PglhTexResInfo_t;

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
/** pgl_Resource_TexRes_Create
* @brief      Create a Texture Resource and add it into PGL Game Engine.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  pTexResInfo       Pointer to texture parameters to be used for create a texture resource.
*
* @retval     hTexRes           return PGL Texture HandleID.
*
*/
hTexRes pgl_Resource_TexRes_Create(EngineHandleID engineID, PglhTexResInfo_t *pTexResInfo);

/** pgl_Resource_TexRes_Modify
* @brief      Modify parameters of Texture Resource.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  resID             PGL Texture HandleID.
* @param[in]  pTexResInfo       Pointer to texture parameters to be used for modifying a texture resource.
*
* @retval     ePgl_RetCode      return ePGL_RET_SUCCESS if texture res is modified successfully.
*
*/
ePgl_RetCode pgl_Resource_TexRes_Modify(EngineHandleID engineID, hTexRes resID, PglhTexResInfo_t *pTexResInfo);

/** pgl_Resource_TexRes_Destroy
* @brief      Destroy a Texture Resource and remove it from PGL Game Engine.
*
* @param[in]  engineID          PGL Engine HandleID.
* @param[in]  resID             PGL Texture HandleID.
*
* @retval     None.
*
*/
pgl_void pgl_Resource_TexRes_Destroy(EngineHandleID engineID, hTexRes resID);

#endif

