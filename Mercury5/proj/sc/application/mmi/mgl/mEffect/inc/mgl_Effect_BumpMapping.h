/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Effect_BumpMapping.h
 *
 *
 * HISTORY
 *      2010.01.07       Golden Chen         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_EFFECT_BUMPMAPPING_H__
#define __M_EFFECT_BUMPMAPPING_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_Common.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/** BumpMappingInfo
*
* @brief    bFlyingLight:   TRUE to enable moving light, and rotate around
*                           the mapping object.
*           ScreenPosition: Mapping object position.
*
*/
typedef struct BumpMappingInfo_tag
{
    mgl_boolean bFlyingLight;
    Vertex2D ScreenPosition;
}BumpMappingInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_RenderBumpMapping
* @brief      Apply bump mapping effect to the base texture with
*             perturbed normal texture.
*
* @param[in]  pTexAttriBaseMap      Base texture to be applied with bump mapping effect.
* @param[in]  pTexAttriNormalMap    Perturbed normal texture, or bump map.
* @param[in]  pBumpMappingInfo      Include parameters that will apply to the bump mapping effect.
*
* @retval     None
*
*/
mgl_void mgl_Effect_RenderBumpMapping(T_TEXTURE_ATTR_PTR pTexAttriBaseMap, T_TEXTURE_ATTR_PTR pTexAttriNormalMap, BumpMappingInfo *pBumpMappingInfo);

/** mgl_Effect_ResetBumpMapping
* @brief      Reset condition to its inital default.
*
* @param[in]  None
*
* @retval     None
*
*/
mgl_void mgl_Effect_ResetBumpMapping(mgl_void);

#endif /* __M_EFFECT_BUMPMAPPING_H__ */

