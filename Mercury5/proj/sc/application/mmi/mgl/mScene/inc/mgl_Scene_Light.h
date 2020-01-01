/*-----------------------------------------------------------------------------
 *
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Scene_Light.h
 *
 *
 * HISTORY
 *      2009.11.27       Chunwei Wang         Initial Version
 *
 *-----------------------------------------------------------------------------
 */

#ifndef __M_SCENE_LIGHT_H__
#define __M_SCENE_LIGHT_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Core_Types.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define NOT_FOUND_LIGHT -1
//#define ADVANCED_LIGHT_SETTING

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
enum
{
    LIGHT0 = 0,
    LIGHT1,
    LIGHT2,
    LIGHT3,
    LIGHT4,
    LIGHT5,
    LIGHT6,
    LIGHT7,
    LIGHT_NUM
};
typedef mgl_s16 LightId;

#ifdef ADVANCED_LIGHT_SETTING
typedef enum AttenuationType_tag
{
    ATTEN_CONSTANT,
    ATTEN_LINEAR,
    ATTEN_QUADRATIC,
}AttenuationType;

typedef struct AttenuationInfo_tag
{
    AttenuationType type;
    mgl_float factor;
}AttenuationInfo;

typedef struct SpotInfo_tag
{
    mgl_float exp;
    mgl_float cutoff;
    Vertex3D direction;
}SpotInfo;

typedef struct MaterialInfo_tag
{
    Color4f *pAmbientColor;
    Color4f *pDiffuseColor;
    Color4f *pSpecularColor;
    Color4f *pEmissionColor;    
    mgl_float shininess;
}MaterialInfo;
#endif

typedef struct LightInfo_tag
{
    Color4f *pAmbientColor;
    Color4f *pDiffuseColor;    
    Vertex4D *pPosition;
#ifdef ADVANCED_LIGHT_SETTING
	Color4f *pSpecularColor;
    AttenuationInfo *pAttenuation;
    SpotInfo *pSpot;
#endif
}LightInfo;

typedef enum CullFaceType_tag
{
    FRONT,
    BACK,
    FRONT_AND_BACK,
}CullFaceType;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
LightId mgl_Light_AddLight(mgl_void);
mgl_void mgl_Light_RemoveLight(LightId id);
mgl_void mgl_Light_SetLightInfo(LightId id, LightInfo *pLightInfo);
#ifdef ADVANCED_LIGHT_SETTING
mgl_void mgl_Light_SetMaterialInfo(CullFaceType cullFaceType, MaterialInfo *pMaterialInfo);
#endif
#endif /* __M_SCENE_LIGHT_H__ */

