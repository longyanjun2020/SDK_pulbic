/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Effect_WaterWave.h
 *
 *
 * HISTORY
 *      2009.11.17       Chunwei Wang         Initial Version
 *      2009.11.21       Golden Chen            Change 2-pass rendering to 1-pass
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_EFFECT_WATERWAVE_H__
#define __M_EFFECT_WATERWAVE_H__

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

/** WaterWaveInfo
*
* @brief    pX:         X-axis of the point to be applied with the water wave effect.
*           pY:         Y-axis of the point to be applied with the water wave effect.
*           amplitude:  Amplitude of the water wave.
*           updateWave: Enable/Disable water wave updates.
*           skyFactor:  Opaqueness of the sky color that is reflected on the water surface.
                        (This feature is currently desabled.)
*           watercolor: Set water color.
*
*/
typedef struct WaterWaveInfo_tag
{
    mgl_u32 pX;
    mgl_u32 pY;
    mgl_u32 amplitude;
    mgl_boolean updateWave;
    mgl_float skyFactor;
    Color4f watercolor;
}WaterWaveInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_RenderWaterWave
* @brief      Render water wave effect, with hydraulic computation based on
*             input position and water wave amplitude.
*
* @param[in]  envMap        Sky color map to reflect on the water surface.
*                           (This feature is currently desabled.)
* @param[in]  pTexAttri     Background texture for water wave effect.
* @param[in]  pWaterInfo    Include parameters that will apply to the water wave effect.
*
* @retval     None
*
*/
mgl_void mgl_Effect_RenderWaterWave(T_TEXTURE_ATTR_PTR pEnvMapTexAttri, T_TEXTURE_ATTR_PTR pTexAttri, WaterWaveInfo *pWaterInfo);

/** mgl_Effect_ResetWaterWave
* @brief      Reset condition to its inital default.
*
* @param[in]  None
*
* @retval     None
*
*/
mgl_void mgl_Effect_ResetWaterWave(mgl_void);

#endif /* __M_EFFECT_WATERWAVE_H__ */

