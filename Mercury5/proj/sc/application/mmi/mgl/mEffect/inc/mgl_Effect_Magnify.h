/*-----------------------------------------------------------------------------
*
* Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mgl_Effect_Magnify.h
*
*
* HISTORY
*      2010.11.02       Sheng Yu         Initial Version
*
*-----------------------------------------------------------------------------
*/

#ifndef __M_EFFECT_MAGNIFY_H__
#define __M_EFFECT_MAGNIFY_H__
/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_Common.h"
#include "mgl_Texture_ImgMgr.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/

/** MagnifyData
*
* @brief    size:   Magnifying glass size.
*           step:   Size of triangle polygons that are composing the magnifying glass.
*           ratio:  Magnify ratio.
*           centX:  X-axis of the center point of magnifying glass to be drawn.
*           centY:  Y-axis of the center point of magnifying glass to be drawn.
*           MaxX:   Width of magnifying glass picture.
*           MaxY:   Height of magnifying glass picture.
*           TexX:   X-axis of position to be magnified.
*           TexY:   Y-axis of position to be magnified.
*
*/
typedef struct MagnifyData_tag
{
	mgl_s32 size;
	mgl_s32 step;
	mgl_float ratio;
	mgl_s32 centX, centY;
	mgl_s32 MaxX, MaxY;
	mgl_s32 TexX, TexY;
}MagnifyData;

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_RenderMagnify
* @brief      Render specified area with magnifying glass effect. User can
*             specify the size, position, and magnifying ratio of the
*             magnifying glass.
*
* @param[in]  pMagnifyData  Include parameters that will apply to the magnify effect.
* @param[in]  pTexAttri     Texture that will be applied to the magnify effect.
*
* @retval     None
*
*/
mgl_void mgl_Effect_RenderMagnify(MagnifyData *pMagnifyData, T_TEXTURE_ATTR_PTR pTexAttri);

/** mgl_Effect_ResetMagnify
* @brief      Reset condition to its inital default.
*
* @param[in]  None
*
* @retval     None
*
*/
mgl_void mgl_Effect_ResetMagnify(mgl_void);

#endif /* __M_EFFECT_MAGNIFY_H__ */

