#ifndef __M_UTILITY_COMMON_H__
#define __M_UTILITY_COMMON_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mmi_mae_log.h"
#include "mmi_mae_common_def.h"
#include "mmi_mae_porting.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/* Prototype Aliasing */
typedef int             mgl_s32;       
typedef short           mgl_s16;     
typedef char            mgl_s8;       
typedef unsigned int    mgl_u32;
typedef unsigned short  mgl_u16;
typedef unsigned char   mgl_u8;
typedef unsigned char    mgl_boolean;
typedef float  mgl_float;
typedef mgl_s32 mgl_fixed;
#define mgl_void void

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
extern mgl_u32 g_mglLCMWidth;
extern mgl_u32 g_mglLCMHeight;

#define MGL_LCM_WIDTH    (g_mglLCMWidth)
#define MGL_LCM_HEIGHT   (g_mglLCMHeight)

#ifndef XMMI
#define XMMI
#endif

#include "mgl_Utility_mm.h"
#define MGL_MEMSET  memset
#define MGL_MEMCPY  memcpy
#define MGL_MEMCMP  memcmp

#define MGL_MALLOC      MALLOC//mglMMMalloc
#define MGL_CALLOC      //mglMMCalloc
#define MGL_REALLOC     //mglMMRealloc
#define MGL_STRDUP       //mglMMStrdup
#define MGL_FREE(x)      {if((x)) {FREE((x));(x)=NULL;}}//{if(x) {mglMMFree(x);x=NULL;}}
#ifdef XMMI
#define MGL_ASSERT(x)   ASSERT((x))
#define MGL_PRINTF(x,...) //LOG_TRACE(MAE_LEVEL_MGL, x, ##__VA_ARGS__)
#else
#define MGL_ASSERT(x)   
#define MGL_PRINTF(x,...) 
#endif

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_u32 mgl_VersionQuery(mgl_void);

#endif    /* __M_UTILITY_COMMON_H__ */
