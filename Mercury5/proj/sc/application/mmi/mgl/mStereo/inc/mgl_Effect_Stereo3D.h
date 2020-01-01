/*-----------------------------------------------------------------------------
*
* Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*		mgl_Effect_Stereo3D.h     
*
*
* HISTORY
*      
*
*-----------------------------------------------------------------------------
*/

#ifndef __M_EFFECT_STEREO3D_H__
#define __M_EFFECT_STEREO3D_H__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_Common.h"
#include "mgl_Scene_Environment.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef enum mgl_StereoType_e
{
	MGL_STEREO_REDBLUE = 0,
	MGL_STEREO_3D_PANEL,
}mgl_StereoType;

typedef enum mSteroFrustumMode_Tag
{
    STEREO_FRUSTUM_LEFT,
    STEREO_FRUSTUM_RIGHT,
    STEREO_NOT_DEFINE,
}mSteroFrustumMode;

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
mgl_void mgl_Effect_Stereo_Begin(mgl_StereoType eStereoType);
mgl_void mgl_Effect_Stereo_End(mgl_void);
mgl_void mgl_Effect_Stereo_Set3DStereoMode(mSteroFrustumMode FrustumMode);

#endif /* __M_EFFECT_STEREO3D_H__ */

