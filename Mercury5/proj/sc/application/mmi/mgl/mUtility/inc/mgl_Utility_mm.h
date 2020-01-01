#ifndef __M_UTILITY_MM_H__
#define __M_UTILITY_MM_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"

/* extern */
#ifdef __cplusplus
extern "C" {
#endif    /* end of #ifdef __cplusplus */

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
mgl_void* mglMMMallocImpl(mgl_s32 s32Bytes, mgl_s8 *sFileName, mgl_s32 s32LineNo);
mgl_void* mglMMCallocImpl(mgl_s32 s32Elems, mgl_s32 s32ElemSize, mgl_s8 *sFileName, mgl_s32 s32LineNo);
mgl_void* mglMMReallocImpl(mgl_void *pvMem, mgl_s32 s32NewSize, mgl_s8 *sFileName, mgl_s32 s32LineNo);
mgl_s8* mglMMStrdupImpl(const mgl_s8 *sSrc, mgl_s8 *sFileName, mgl_s32 s32LineNo);
mgl_void mglMMFreeImpl(mgl_void *pvMem);

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#ifdef MM_SUPPORT_MALLOC_TRACE
    #define mglMMMalloc(x)       mglMMMallocImpl((x),__FILE__,__LINE__)
    #define mglMMCalloc(x,y)     mglMMCallocImpl((x),(y),__FILE__,__LINE__)
    #define mglMMRealloc(x,y)    mglMMReallocImpl((x),(y),__FILE__,__LINE__)
    #define mglMMStrdup(x)       mglMMStrdupImpl((x),__FILE__,__LINE__)
#else
    #define mglMMMalloc(x)       mglMMMallocImpl((x),NULL,0)
    #define mglMMCalloc(x,y)     mglMMCallocImpl((x),(y),NULL,0)
    #define mglMMRealloc(x,y)    mglMMReallocImpl((x),(y),NULL,0)
    #define mglMMStrdup(x)       mglMMStrdupImpl((x),NULL,0)
#endif    /* end of #ifdef MM_SUPPORT_MALLOC_TRACE */

#define mglMMFree(x)         mglMMFreeImpl((x))

#ifdef __cplusplus
}
#endif    /* end of #ifdef __cplusplus */

#endif    /* end of #ifndef __M_UTILITY_MM_H__ */
