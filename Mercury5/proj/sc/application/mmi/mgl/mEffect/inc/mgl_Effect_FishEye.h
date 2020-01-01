
#ifndef __M_EFFECT_FISHEYE_H__
#define __M_EFFECT_FISHEYE_H__

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

/** FishEyeInfo
*
* @brief    nPx:        X-axis of the point to be applied with the fish-eye effect.
*           nPy:        Y-axis of the point to be applied with the fish-eye effect.
*           fRadEye:    For moving the fish-eys sphere upward/downward from the surface.
*           fRadSphere: Radius of the sphere that creates the fish-eye effect.
*
*/
typedef struct FishEyeInfo_tag
{
    mgl_u32 nPx;
    mgl_u32 nPy;
    mgl_float fRadEye;
    mgl_float fRadSphere;
}FishEyeInfo;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

/** mgl_Effect_RenderFishEye
* @brief      Render fish-eye hemispherical effect, which has extremely wide and
*             distorted appearance, centered around specified position.
*
* @param[in]  pTexAttri     Texture that will be applied to the fisy-eye effect.
* @param[in]  pFishEyeInfo  Include parameters that will apply to the fisy-eye effect.
*
* @retval     None
*
*/
mgl_void mgl_Effect_RenderFishEye(T_TEXTURE_ATTR_PTR pTexAttri, FishEyeInfo *pFishEyeInfo);

/** mgl_Effect_ResetFishEye
* @brief      Reset condition to its inital default.
*
* @param[in]  None
*
* @retval     None
*
*/
mgl_void mgl_Effect_ResetFishEye(mgl_void);


#endif /* __M_EFFECT_FISHEYE_H__ */

