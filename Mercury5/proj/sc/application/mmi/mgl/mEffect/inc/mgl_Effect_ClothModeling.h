/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Effect_ClothModeling.h
 *
 *
 * HISTORY
 *      2011.02.21       Evan Chang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_EFFECT_CLOTHMODELING_H__
#define __M_EFFECT_CLOTHMODELING_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Core_Types.h"
#include "mgl_Texture_ImgMgr.h"
#include "mgl_Utility_Common.h"
#include "mgl_Scene_NodeMgr.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define MAX_CURTAIN_RATIO	1.0f 
#define MIN_CURTAIN_RATIO	0.5f    

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/** CLOTH_MODELING_EFFECT
*
* @brief    Cloth modeling effect style.
*
*/
enum
{
	CLOTH_CURTAIN_STEER_FROM_RIGHT_SIDE = 0,
	CLOTH_CURTAIN_STEER_FROM_LEFT_SIDE,
	CLOTH_DROP_HANG_ON_TOP_LEFT,
	CLOTH_DROP_HANG_ON_TOP_RIGHT,
	CLOTH_DROP_NO_HANG,
	TOTAL_CLOTH_MODELING_EFFECT_NUM
};
typedef mgl_u16 CLOTH_MODELING_EFFECT;

/** ClothCurtainEffect
*
* @brief    fCurtainExpandRatio: For curtain effect, to expand or shrink
*                                curtain from MIN_CURTAIN_RATIO to 1.0f.
*
*/
typedef struct ClothCurtainEffect_tag
{
    mgl_float fCurtainExpandRatio;
}ClothCurtainEffect;

/** ClothDropEffect
*
* @brief    bDropCloth: For cloth drop effect. TRUE to drop the cloth.
*
*/
typedef struct ClothDropEffect_tag
{
    mgl_boolean bDropCloth;
}ClothDropEffect;

/** ClothModelingInfo
*
* @brief    vClothSize:         Cloth size, width and height.
*           vInitPosition:      Cloth initial position (x,y).
*           vMovement:          Cloth movement in x-axis and y-axis.
*           vForceGravityFold:  To use default gravity fold, set x, y, and z to 1.
*           vForceWind:         Apply wind force in x and z direction. Not recommend y direction (same as earth gravity).
*           eEffectType:        Cloth modeling effect.
*           CurtainEffect:      Settings for curtain effect.
*           DropEffect:         Settings for cloth drop effect.
*
*/
typedef struct ClothModelingInfo_tag
{
    Vertex2D                vClothSize;
    Vertex2D                vInitPosition;
    Vertex2D                vMovement;
    Vertex3D                vForceGravityFold;
    Vertex3D                vForceWind;
    CLOTH_MODELING_EFFECT   eEffectType;
    union{
        ClothCurtainEffect      CurtainEffect;
        ClothDropEffect         DropEffect;
    }ClothEffect;
}ClothModelingInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_RenderClothModeling
* @brief      Render cloth modeling effect based on the parameters and conditions
*             provided in ClothModelingInfo.
*
* @param[in]  pClothModelingInfo    Include parameters that will apply to the cloth modeling effect.
* @param[in]  pTexAttri             Texture that will be applied to the cloth.
*
* @retval     None
*
*/
mgl_void mgl_Effect_RenderClothModeling(ClothModelingInfo *pClothModelingInfo, mgl_float alpha, T_TEXTURE_ATTR_PTR pTexAttri);

/** mgl_Effect_ResetClothModeling
* @brief      Reset condition to its inital default.
*
* @param[in]  None
*
* @retval     None
*
*/
mgl_void mgl_Effect_ResetClothModeling(mgl_void);

#endif /* __M_EFFECT_CLOTHMODELING_H__ */

