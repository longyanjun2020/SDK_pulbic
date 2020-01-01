/**
* @file mmi_mae_util_gles.h
*
* @version $Id$
*/
#ifndef __MMI_MAE_UTIL_GLES_H__
#define __MMI_MAE_UTIL_GLES_H__

#if defined(__FEATURE_MGL__)

#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_graphic_forward.h"

boolean GLESUtil_Get3DFrame(void *pThis, IBITMAP **pDstBmp, Rect_t *pSrcRc);

#endif// defined(__FEATURE_MGL__)

#endif // __MMI_MAE_UTIL_GLES_H__
