#ifndef FW_MM_H
#define FW_MM_H

#include "fw_configure.h"

#ifdef USE_MM_MALLOC
    #define MM_MAGIC_NUM  0x96A5        /* The magic number of the alloacted memory block                    */
    #define MM_GUARD_BYTE 0x9A          /* The guard byte appended at the tail of the allocated memory block */
    #define MM_GUARD_WORD 0x9A9A9A9A    /* The guard word prior to the exact user-required memory space      */ 

    #ifndef MM_SUPPORT_MALLOC_TRACE
        #define MM_SUPPORT_MALLOC_TRACE
        #define MM_LOG_TO_FILE    /* This macro value defines whether to save the information to the log file */
    #endif    /* end of #ifndef MM_SUPPORT_MALLOC_TRACE */

    #ifdef MM_SUPPORT_MALLOC_TRACE
        #define MM_MALLOC_TRACE_LEVEL 2    /* 0: show the statistic result                                    */
                                           /* 1: show the statistic result and the memory leak and overridden */
                                           /* 2: show complete process and result                             */
        #ifdef MM_LOG_TO_FILE
            #define MM_LOGFILE "MemTrace.log"    /* The name of the log file */
        #endif    /* end of #ifdef MM_LOG_TO_FILE */

    #endif    /* end of #ifdef MM_SUPPORT_MALLOC_TRACE */

    typedef struct MM_s MM_st,*pMM_st;
    struct MM_s
    {
        U16     u16Magic;        /* magic number                            */
        S16     s16GuardSize;    /* size of the tail guard data; in bytes   */
        S32     s32Size;         /* size of memory block; in bytes          */
    #ifdef MM_SUPPORT_MALLOC_TRACE
        PS8     sFileName;       /* filename where allocation took place    */
        S32     s32LineNo;       /* line number where allocation took place */
    #endif    /* end of #ifdef MM_SUPPORT_MALLOC_TRACE */
        pMM_st  psNext;          /* link to the next allocated block        */
        U32     u32GuardWord;    /* guard word                              */
        PU8     pu8Data;         /* allocated blocks with the guard bytes   */
    };

    /* extern */
    #ifdef __cplusplus
    extern "C" {
    #endif    /* end of #ifdef __cplusplus */

        MVOID  mfMMInitialize(MVOID);
        MVOID  mfMMFinalize(MVOID);
    
        PMVOID mfMMMallocImpl(S32 s32Bytes,PS8 sFileName,S32 s32LineNo);
        PMVOID mfMMCallocImpl(S32 s32Elems,S32 s32ElemSize,PS8 sFileName,S32 s32LineNo);
        PMVOID mfMMReallocImpl(PMVOID pvMem,S32 s32NewSize,PS8 sFileName,S32 s32LineNo);
        PS8    mfMMStrdupImpl(const PS8 sSrc,PS8 sFileName,S32 s32LineNo);
        MVOID  mfMMFreeImpl(PMVOID pvMem);
    
        #ifdef MM_SUPPORT_MALLOC_TRACE
            #define mfMMMalloc(x)       mfMMMallocImpl((x),__FILE__,__LINE__)
            #define mfMMCalloc(x,y)     mfMMCallocImpl((x),(y),__FILE__,__LINE__)
            #define mfMMRealloc(x,y)    mfMMReallocImpl((x),(y),__FILE__,__LINE__)
            #define mfMMStrdup(x)       mfMMStrdupImpl((x),__FILE__,__LINE__)
        #else
            #define mfMMMalloc(x)       mfMMMallocImpl((x),NULL,0)
            #define mfMMCalloc(x,y)     mfMMCallocImpl((x),(y),NULL,0)
            #define mfMMRealloc(x,y)    mfMMReallocImpl((x),(y),NULL,0)
            #define mfMMStrdup(x)       mfMMStrdupImpl((x),NULL,0)
        #endif    /* end of #ifdef MM_SUPPORT_MALLOC_TRACE */

        #define mfMMFree(x)         mfMMFreeImpl((x))	
        #if defined(XMMI)
		#define sysMalloc(x)        MALLOC((x))
     	       #define sysFree(x)          FREE((x))
	 #else
	         #define sysMalloc(x)        malloc((x))
	         #define sysFree(x)          free((x))
	 #endif
        
        #define sysMemset(x,y,z)    memset((x),(y),(z))
        #define sysMemcpy(x,y,z)    memcpy((x),(y),(z))
        #define sysStrlen(x)        strlen((x))
        #define sysStrcpy(x,y)      strcpy((x),(y))

    #ifdef __cplusplus
    }
    #endif    /* end of #ifdef __cplusplus */
#elif defined(XMMI)

    /* extern */
    #ifdef __cplusplus
    extern "C" {
    #endif    /* end of #ifdef __cplusplus */
     PMVOID *xmmi_calloc(U32 size);
      /* extern */
    #ifdef __cplusplus
    }	
    #endif    /* end of #ifdef __cplusplus */
	
    #define mfMMInitialize()
    #define mfMMFinalize()
    #define mfMMMalloc(x)       MALLOC((x))
    #define mfMMCalloc(x,y)     xmmi_calloc(((x)*(y)))
    #define mfMMRealloc(x,y)    REALLOC((x),(y))
    #define mfMMStrdup(x)       STRDUP((x))
    #define mfMMFree(x)         FREE((x))
#else
    #ifdef MM_NO_STRDUP
        /* extern */
        #ifdef __cplusplus
        extern "C" {
        #endif    /* end of #ifdef __cplusplus */

            #define sysMalloc(x)        malloc((x))
            #define sysStrlen(x)        strlen((x))
            #define sysStrcpy(x,y)      strcpy((x),(y))

            PS8 strdup(const PS8 sSrc);

        #ifdef __cplusplus
        }
        #endif    /* end of #ifdef __cplusplus */
    #endif    /* end of #ifdef MM_NO_STRDUP */
    #define mfMMInitialize()
    #define mfMMFinalize()
    #define mfMMMalloc(x)       malloc((x))
    #define mfMMCalloc(x,y)     calloc((x),(y)) 
    #define mfMMRealloc(x,y)    realloc((x),(y))
    #define mfMMStrdup(x)       strdup((x))
    #define mfMMFree(x)         free((x))
#endif    /* end of #ifdef USE_MM_MALLOC */

#endif    /* end of #ifndef FW_MM_H */
