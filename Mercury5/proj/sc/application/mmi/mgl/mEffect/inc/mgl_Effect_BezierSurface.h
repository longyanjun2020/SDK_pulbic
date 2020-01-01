/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Effect_BezierSurface.h
 *
 *
 * HISTORY
 *      2009.11.09       Golden Chen         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_EFFECT_BEZIERSURFACE_H__
#define __M_EFFECT_BEZIERSURFACE_H__

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

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/** BEZIER_EFFECT
*
* @brief    Bezier effect style.
*
*/
enum
{
	BEZIER_TWIST_TO_BOTTOM_RIGHT = 0,
	BEZIER_TWIST_TO_MIDDLE_RIGHT,
	BEZIER_TWIST_TO_MIDDLE_BOTTOM,
	BEZIER_TWIST_TO_MIDDLE_TOP,
	BEZIER_TWIST_TO_BOTTOM_LEFT,
	BEZIER_TWIST_TO_MIDDLE_LEFT,
	BEZIER_REMOVE_EFFECT_A,
	BEZIER_REMOVE_EFFECT_B,
	BEZIER_OPTION_MENU,
	BEZIER_SUB_OPTION_MENU,	
	BEZIER_TURNPHOTO_FROM_TOP_HALFWAY,
	BEZIER_TURNPAGE_FROM_LEFT,
	BEZIER_TURNPAGE_FROM_RIGHT,
	BEZIER_TURNPHOTO_FROM_TOP,
	BEZIER_TURNPHOTO_FROM_BOTTOM,
	TOTAL_BEZIER_EFFECT_NUM
};
typedef mgl_u16 BEZIER_EFFECT;

/** BezierInfo
*
* @brief    pos:                Bezier surface position (x,y).
*           size:               Bezier surface size, width and height.
*           effect:             Bezier effect style.
*           u16TheFrameNum:     Set frame number of effect rendering, from 0 to 15.
*           WeightRatio:        For TURNPAGE effect: Turn page between top (0.0f) to bottom (1.0f).
*                               For TURNPHOTO effects: Turn photo between left (0.0f) to right (1.0f).
*
*/
typedef struct BezierInfo_tag
{
    Vertex2D  pos;
    Vertex2D  size;
    BEZIER_EFFECT effect;
    mgl_u16 u16TheFrameNum;
    mgl_float WeightRatio;
}BezierInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_RenderBezier
* @brief      Render cloth modeling effect based on the parameters and conditions
*             provided in ClothModelingInfo.
*
* @param[in]  pBezierInfo       Include parameters that will apply to Bezier effect.
* @param[in]  pTexAttri         Texture that will be applied to the front side of face.
* @param[in]  pTexAttri_Back    Texture that will be applied to the back side of face.
*
* @retval     None
*
*/
mgl_void mgl_Effect_RenderBezier(BezierInfo *pBezierInfo, T_TEXTURE_ATTR_PTR pTexAttri, T_TEXTURE_ATTR_PTR pTexAttri_Back);

/** mgl_Effect_ResetBezier
* @brief      Reset condition to its inital default.
*
* @param[in]  None
*
* @retval     None
*
*/
mgl_void mgl_Effect_ResetBezier(mgl_void);

#endif /* __M_EFFECT_BEZIERSURFACE_H__ */

