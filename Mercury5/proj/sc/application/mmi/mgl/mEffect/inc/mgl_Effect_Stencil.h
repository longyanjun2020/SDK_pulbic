/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Effect_Stencil.h
 *
 *
 * HISTORY
 *      2009.10.13       Chunwei Wang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_EFFECT_STENCIL_H__
#define __M_EFFECT_STENCIL_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef mgl_void (*DrawMirrorObject)(mgl_void *userData);
typedef mgl_void(*DrawMirrorFloor)(mgl_void *userData);

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_Stencil_DrawMirror
* @brief      Render mirror reflections. It can create physically projected
*             clipping mirror reflection.
*
* @param[in]  pObject       Reflected object.
* @param[in]  pFloor        Floor to be reflected on.
* @param[in]  pUserData     Include parameters that will apply to this effect.
* @param[in]  height        Height of the reflected object.
* @param[in]  alpha         Alpha of the floor.
*
* @retval     None
*
*/
mgl_void mgl_Effect_Stencil_DrawMirror(DrawMirrorObject pObject, DrawMirrorFloor pFloor, mgl_void *pUserData, mgl_u32 height, mgl_float alpha);

#endif /* __M_EFFECT_STENCIL_H__ */

