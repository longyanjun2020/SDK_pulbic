/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_utility_types.h
*
*
* HISTORY
*      2011.10.04       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_UTILITY_TYPES_H__
#define __MMI_PGL_UTILITY_TYPES_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmi_mae_common_def.h"

#include "srv_MGL.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/* Prototype Aliasing */
#ifdef _MSC_VER
typedef _int64          mgl_s64;
#else
typedef long            mgl_s64;
#endif /* ~_MSC_VER */

typedef int             pgl_s32;
typedef short           pgl_s16;
typedef char            pgl_s8;
typedef unsigned int    pgl_u32;
typedef unsigned short  pgl_u16;
typedef unsigned char   pgl_u8;
typedef unsigned char   pgl_boolean;
typedef float           pgl_float;
#define pgl_void        void


enum
{
	ePGL_RET_SUCCESS				= 0,
	ePGL_RET_FAILED	                =-1,
};
typedef pgl_s32 ePgl_RetCode;


enum
{
    PGL_TRANSFORM_NONE,
    PGL_TRANSFORM_SCALE,
    PGL_TRANSFORM_TRANSLATE,
};
typedef pgl_s32 ePgl_TransformType;

typedef struct PglScaleInfo_tag
{
    pgl_float scaleFactor_w;
    pgl_float scaleFactor_h;
}PglScaleInfo;

typedef struct PglTranslateInfo_tag
{
    pgl_float translateFactor_x;
    pgl_float translateFactor_y;
}PglTranslateInfo;


typedef struct PglTransformOP_tag
{
   ePgl_TransformType opTransformFun;
   union
   {
        PglScaleInfo scale;
        PglTranslateInfo translate;
   }TransformOpData;
}PglTransformOP;


typedef pgl_s32 EngineHandleID;

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define PGL_MEMSET  MEMSET
#define PGL_MEMCPY  MEMCPY

#define PGL_MALLOC  MALLOC
#define PGL_FREE(x)    {if((x)) {FREE((x));(x)=NULL;}}

#ifdef C_MODEL
#define PGL_ASSERT(x) assert((x))
#define PGL_PRINTF(x,...) printf( x, ##__VA_ARGS__)
#else
#define PGL_ASSERT(x)   ASSERT((x))
#define PGL_PRINTF(x,...) LOG_TRACE(MAE_LEVEL_PGL, x, ##__VA_ARGS__)
#endif


#define PGL_SPRITE_FIX_FRAME        0xffffffff
#define PGL_SPRITE_INFINITY_LOOP    0xffffffff
#define PGL_MAX_CONTEXT             0x3
#define PGL_ENGINE_NULL            -1
/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/

#endif
