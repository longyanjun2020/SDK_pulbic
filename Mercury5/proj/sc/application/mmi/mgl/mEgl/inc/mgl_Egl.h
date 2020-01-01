/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Egl.h
 *
 *
 * HISTORY
 *      2010.01.22       Chunwei.Wang         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_MGL_EGL_H__
#define __M_MGL_EGL_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"
#include "mmi_mae_graphic.h" 
#include "mmi_mae_dib_types.h"
#include "mmi_mae_dib.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define EGL_USE_PIXEL_BUFFER 1

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
typedef struct mgl_G3D_Window_tag
{
	Rect_t region;
	mgl_u32 pitch;
	mgl_void *data;
}mgl_G3D_Window;

typedef enum mgl_PixelFormat_e
{
	PIXEL_FORMAT_R5G6B5,
	PIXEL_FORMAT_A8R8G8B8,
}mgl_PixelFormat;

typedef enum {
	MGL3DPOWER_CLIENT_MMI = 0,
	MGL3DPOWER_CLIENT_DALVIK,
	MGL3DPOWER_CLIENT_MAX
} mgl_3DPowerClientIdx_e;

typedef enum mgl_LCMType_e
{
    LCM_P_QVGA = 0,
    LCM_P_WQVGA,
    LCM_P_HVGA,
    LCM_P_WVGA,
    LCM_L_QVGA,
    LCM_L_WQVGA,
    LCM_L_HVGA,    
    LCM_L_WVGA,
}mgl_LCMType;

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_boolean mgl_EGL_Enable3D (mgl_u32 x, mgl_u32 y, mgl_u32 width, mgl_u32 height);  /* colorBuffer + zBuffer */
mgl_boolean mgl_EGL_Disable3D (mgl_void);

mgl_void mgl_EGL_EnableDepthBuffer(mgl_boolean isEnable);   /* whether or not to allocate zbuffer when mgl_EGL_Enable3D(). */

#ifdef EGL_USE_PIXEL_BUFFER
mgl_boolean mgl_EGL_UserPBufferBegin(mgl_void);
mgl_boolean mgl_EGL_UserPBufferEnd(mgl_void);
#endif

mgl_boolean mgl_EGL_Query3DWindow(mgl_G3D_Window *pInfo);
mgl_boolean mgl_EGL_QueryDepthWindow(mgl_G3D_Window *pDepthInfo);

mgl_void mgl_EGL_ReadPixel(mgl_s32 x, mgl_s32 y, mgl_PixelFormat pixelFormat, mgl_void *pPixel);
mgl_boolean mgl_EGL_ReadRegion(Rect_t *pRect, mgl_u32 pitch, u16 *pOut); /* dummy if MGLS */
mgl_boolean mgl_EGL_Flush3D(mgl_void);
mgl_boolean mgl_EGL_Swap3DBuffer(mgl_void);
mgl_boolean mgl_EGL_IsEnable3D(mgl_void);

mgl_void mgl_EGL_SetBufferContext(DIB_t *pDib1, DIB_t *pDib2); /* dummy if G3D */
mgl_void mgl_EGL_SwapBufferAddr(DIB_t *pDib); /* dummy if G3D */

mgl_boolean mgl_EGL_3DPowerOn( mgl_3DPowerClientIdx_e eClient, mgl_boolean b3DPowerOn);/* dummy if MGLS */
mgl_LCMType mgl_EGL_QueryLCMType(mgl_void); /* internal usage */

#endif /* __M_MGL_EGL_H__ */

