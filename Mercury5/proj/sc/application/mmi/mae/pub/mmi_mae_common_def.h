/**
 * @file mmi_mae_common_def.h
 *
 * This file is the collection of common definitions.
 *
 * @version $Id: mmi_mae_common_def.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */

#ifndef __MMI_MAE_COMMON_DEF_H__
#define __MMI_MAE_COMMON_DEF_H__

#ifdef __DISP_ML_MMI__
#define __AP_USE_ML__
#define __AP_USE_ML_DEBUG__
#define __AP_USE_ML_TEST__
#endif

/*=============================================================*/
// header files
/*=============================================================*/
#include "stdlib.h"
#include "string.h"
#include "wchar.h"

#include "mmi_mae_features.h"
#include "mmi_mae_retcode.h"

#if defined(__MAE_DEBUG__) && defined(__PC_SIMULATOR__)
    #include <assert.h> ///< included for assert on simulator
#endif

#if defined(__GNUC__) && !defined(_WIN32)
    /**
     * GCC doesn't allow duplicate typedefs even if they are exactly match. And in our target build
     * environment, almost every source file in MAE/MMI implementatoin has actually included
     * "vm_types.ht" via different headers. So we simply include it here and skip typedefs of basic
     * types later to avoid redefinition problems.
     */
    #include "vm_types.ht"
#endif

#if !defined(opaque_enum)
#if defined(__cplusplus) && defined(__GNUC__) && (__GNUC__>=4) && (__GNUC_MINOR__>=6)
#define opaque_enum(e) enum e : int
#else
#define opaque_enum(e) enum e
#endif
#define typedef_opaque_enum(e1, e2) \
    opaque_enum(e1); \
    typedef enum e1 e2
#endif //opaque_enum

/// trace functions used only on simulator;
/// on device the trace functions output only the identifiers instead of entire strings
#if defined(__PC_SIMULATOR__) && !defined(__MAE_INTERNAL_BUILD__)
void mae_dbgPrintf(int nLevel, char *pStrFormat, ...);
void mae_dbgError(int nLevel, char *pStrFormat, ...);
#endif // __PC_SIMULATOR__ && !__MAE_INTERNAL_BUILD__

/*=============================================================*/
// Variable
/*=============================================================*/

/*=============================================================*/
// types and macros
/*=============================================================*/
enum
{
    MAE_MEM_NORMAL = 0,
    MAE_MEM_HISTORY,
};

#ifdef _MSC_VER

typedef unsigned _int8          u8;
typedef unsigned _int16         u16;
typedef unsigned _int32         u32;

typedef _int8                   s8;
typedef _int16                  s16;
typedef _int32                  s32;

#define TRUE  1
#define FALSE 0

#else /* ~_MSC_VER */

// skip typedefs of these basic types to avoid redefinitions when we are using gcc
#if !defined(__GNUC__) || defined(_WIN32)

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef long long s64;
typedef int s32;
typedef short s16;
typedef signed char s8;

#endif // !__GNUC__ || _WIN32

#ifndef TRUE
// it usually causes incompatible redefinition warnings
// #define TRUE (1 == 1)
#define TRUE 1
#endif

#ifndef FALSE
// it usually causes incompatible redefinition warnings
// #define FALSE (1 == 0)
#define FALSE 0
#endif

#endif /* ~_MSC_VER */

#ifndef MAX
    #define  MAX( x, y ) ( ((x) > (y)) ? (x) : (y) )
#endif

#ifndef MIN
    #define  MIN( x, y ) ( ((x) < (y)) ? (x) : (y) )
#endif

#ifndef WIN32
typedef u32 boolean;
#else
#define boolean u32
#endif

/*
 * __SLDPM_FREE__ is used to mark important functions/data so that
 * the compiler would give them a special attribute call .sldpm_free.
 * These function/data are free from DPM (Demand Paging Module)
 * and will not be compressed in the flash.
 * If a function/data is frequently called, then it is better to give
 * it this attribute to speed up the run time performance.
 *
 * Other compiler options are used to group highly related code together
 * to reduce the number page faults.
 *
 * See also:
 *   sc/customer/product/cust/scatter/scatter_8532_64_32_bt_acrux2.dsc
 *   sc/customer/product/cust/scatter/scatter_85xx_emmi_sldpm.dsc
 */
#if defined(__TARGET__) && defined(__arm)
#define __SLDPM_FREE__  __attribute__((section(".sldpm_free")))
#define __SLDPM_AUDIO_SECTION__  __attribute__((section(".audio_section")))
#define __SLDPM_AUDIO_PLAY_SECTION__  __attribute__((section(".audio_play_section")))
#define __SLDPM_AUDIO_STOP_SECTION__  __attribute__((section(".audio_stop_section")))
#define __SLDPM_AUDIO_RODATA_SECTION__  __attribute__((section(".audio_rodata_section")))
#define __SLDPM_BT_RODATA_SECTION__  __attribute__((section(".bt_rodata_section")))
#define __SLDPM_BT_SECTION__  __attribute__((section(".bt_section")))
#define __SLDPM_BT_SEARCH_SECTION__  __attribute__((section(".bt_search_section")))
#define __SLDPM_CALENDAR_SECTION__  __attribute__((section(".calendar_section")))
#define __SLDPM_CALLLOG_SECTION__  __attribute__((section(".callog_section")))
#define __SLDPM_CAM_SECTION__  __attribute__((section(".cam_section")))
#define __SLDPM_CAM_RODATA_SECTION__  __attribute__((section(".cam_rodata_section")))
#define __SLDPM_CC_SECTION__  __attribute__((section(".cc_section")))
#define __SLDPM_CC_RODATA_SECTION__  __attribute__((section(".cc_rodata_section")))
#define __SLDPM_CC_IN_SECTION__  __attribute__((section(".cc_in_section")))
#define __SLDPM_CC_OUT_SECTION__  __attribute__((section(".cc_out_section")))
#define __SLDPM_CFG_SECTION__  __attribute__((section(".cfg_section")))
#define __SLDPM_CHECK_SIGNAL_SECTION__  __attribute__((section(".check_singal_section")))
#define __SLDPM_DIALOG_SECTION__  __attribute__((section(".dialog_section")))
#define __SLDPM_FILEMGR_SECTION__  __attribute__((section(".filemgr_section")))
#define __SLDPM_FILEMGR_RODATA_SECTION__  __attribute__((section(".filemgr_rodata_section")))
#define __SLDPM_KMV_SECTION__  __attribute__((section(".kmv_section")))
#define __SLDPM_MISC_SECTION__  __attribute__((section(".misc_section")))
#define __SLDPM_MOI_SECTION__  __attribute__((section(".moi_section")))
#define __SLDPM_MSG_SECTION__  __attribute__((section(".msg_section")))
#define __SLDPM_MMS_SECTION__  __attribute__((section(".mms_section")))
#define __SLDPM_MPLAYER_SECTION__  __attribute__((section(".mplayer_section")))
#define __SLDPM_NETWORK_SECTION__  __attribute__((section(".network_section")))
#define __SLDPM_PHB_SECTION__  __attribute__((section(".phb_section")))
#define __SLDPM_RADIO_SECTION__  __attribute__((section(".radio_section")))
#define __SLDPM_SIM_SECTION__  __attribute__((section(".sim_section")))
#define __SLDPM_SMS_SECTION__  __attribute__((section(".sms_section")))
#define __SLDPM_STGR_SECTION__  __attribute__((section(".stgr_section")))
#define __SLDPM_STK_SECTION__  __attribute__((section(".stk_section")))
#define __SLDPM_USB_SECTION__  __attribute__((section(".usb_section")))
#define __SLDPM_VOICECALL_SECTION__  __attribute__((section(".voicecall_section")))
#define __SLDPM_VPLAYER_SECTION__  __attribute__((section(".videoplayer_section")))
#define __SLDPM_VTM_SECTION__  __attribute__((section(".vtm_section")))
#define __SLDPM_WAP_SECTION__  __attribute__((section(".wap_section")))
#else
#define __SLDPM_FREE__
#define __SLDPM_AUDIO_SECTION__ 
#define __SLDPM_AUDIO_PLAY_SECTION__ 
#define __SLDPM_AUDIO_STOP_SECTION__  
#define __SLDPM_AUDIO_RODATA_SECTION__  
#define __SLDPM_BT_RODATA_SECTION__  
#define __SLDPM_BT_SECTION__  
#define __SLDPM_BT_SEARCH_SECTION__  
#define __SLDPM_CALLLOG_SECTION__ 
#define __SLDPM_CALENDAR_SECTION__  
#define __SLDPM_CAM_SECTION__  
#define __SLDPM_CAM_RODATA_SECTION__
#define __SLDPM_CC_SECTION__  
#define __SLDPM_CC_RODATA_SECTION__ 
#define __SLDPM_CC_IN_SECTION__  
#define __SLDPM_CC_OUT_SECTION__ 
#define __SLDPM_CFG_SECTION__   
#define __SLDPM_CHECK_SIGNAL_SECTION__  
#define __SLDPM_DIALOG_SECTION__  
#define __SLDPM_FILEMGR_SECTION__  
#define __SLDPM_FILEMGR_RODATA_SECTION__  
#define __SLDPM_KMV_SECTION__  
#define __SLDPM_MISC_SECTION__ 
#define __SLDPM_MMS_SECTION__  
#define __SLDPM_MOI_SECTION__  
#define __SLDPM_MPLAYER_SECTION__ 
#define __SLDPM_MSG_SECTION__  
#define __SLDPM_NETWORK_SECTION__  
#define __SLDPM_PHB_SECTION__  
#define __SLDPM_RADIO_SECTION__  
#define __SLDPM_SIM_SECTION__  
#define __SLDPM_SMS_SECTION__  
#define __SLDPM_STGR_SECTION__  
#define __SLDPM_STK_SECTION__  
#define __SLDPM_USB_SECTION__  
#define __SLDPM_VOICECALL_SECTION__  
#define __SLDPM_VPLAYER_SECTION__ 
#define __SLDPM_VTM_SECTION__  
#define __SLDPM_WAP_SECTION__  
#endif

typedef void (* PfnMAE_Callback)(void * pUser, void* pInfo);
#if defined(__GNUC__)// && defined(_WIN32)
// omits stand alone copies of inline functions when we are using gcc to build
// non-target applications with MAE/MMI header files
#define __INLINE static __inline
#define MAE_INLINE static __inline
#elif defined(__EMMI_SLDPM__) && defined(__TARGET__) && defined(__arm)
#define __INLINE __SLDPM_FREE__ static
#define MAE_INLINE __SLDPM_FREE__ static
#else
#define __INLINE __inline
#define MAE_INLINE __inline
#endif // __GNUC__ && _WIN32

typedef void (* PfnMAE_Notify)(void * pUser);

/// The size of underlying type of MAEClsId_t has special purposes in combining with applet/service
/// specified events. It also compacts shell's instance headers to 8-byte boundaries in default case.
typedef u16 MAE_ClsId; ///< type for class ids
typedef u32 MAE_IId; ///< type for interface ids
typedef u32 MAE_Ret; ///< type for MAE return values
typedef u16 MAE_WChar; ///< type for MAE defined wide characters
typedef u32 MAE_EventId; ///< type for events used in the communication of IHandler objects

/// type aliases
typedef MAE_IId MAEIId_t;
typedef MAE_ClsId MAEClsId_t;
typedef MAE_Ret MAERet_t;
typedef MAE_EventId MAEEvent_t;

/*
 * Replace FREEIF macro with a function for reducing code size
 *
 * #define FREEIF(p) if (p != 0) {FREE((void*)p); p = 0;}
 */
void freeif(void **);
#define FREEIF(p) freeif((void **) &(p));
//#define BREAKIF(a) if (a != MAE_RET_SUCCESS) break


#undef ASSERT

#ifdef __UNIT_TEST_APP__
#define ASSERT(_e_) if(_e_){}      // to prevent lint warning because _e_ is set but not used

#elif defined(__MAE_DEBUG__) && ((defined(__MAE_PLATFORM_DEBUG__) && !defined(__MAE_DISABLE_PLATFORM_ASSERT__)) || (!defined(__MAE_PLATFORM_DEBUG__) && !defined(__MAE_DISABLE_APPLET_ASSERT__)))
#ifdef __PC_SIMULATOR__
#define ASSERT(_e_)  {\
            assert(_e_);              \
    }
#else
/// rtpp doesn't handle preprocessed file so that #_e_ will not be catenated
/// ASSERT(_e_)    (void)((!!(_e_)) || (LOG_FATAL(MMI_LEVEL_COMMON, "assertion failed: " #_e_)))
#define ASSERT(_e_)    {\
        if(!(_e_))                                                          \
        {                                                                   \
            extern void ker_assert_func(u8 * str, u8 * file, u32 line); \
            ker_assert_func( #_e_, __FILE__, __LINE__);                 \
        }                                                               \
    }
#endif /* __PC_SIMULATOR__ */
#else
#define ASSERT(_e_) if(_e_){}      // to prevent lint warning because _e_ is set but not used
#endif

/// macros of the source file name used in memory dump information
#ifdef __SFILE__
#define __MFILE__    __SFILE__
#else
#define __MFILE__    __FILE__
#endif // __SFILE__

/// prototypes of memory management functions
/// there are two versions, release and debug, for the memory allocation functions
/// refer to the header file "sys_rtk_vmrtkho.h" for more information
#ifdef __SDK_SIMULATION__
void *MAE_Malloc(u32 nSize, int __nMline__, char *__nMfile__);
void *MAE_MallocHeap(u32 nSize, int __nMline__, char *__nMfile__);
void *MAE_Realloc(void *ptr, u32 nSize, int __nMline__, char *__nMfile__);
void *MAE_ReallocHeap(void *ptr, u32 nSize, int __nMline__, char *__nMfile__);
void *MAE_Calloc(u32 nNum, u32 nSize, int __nMline__, char *__nMfile__);
#ifdef __SIMULATOR_MEMORY_CHECK_OVERLAY__
void *MAE_MEMCPY(void *s1, const void *s2, size_t  n);
#endif
#else
void *MAE_Malloc(u32 nSize);
void *MAE_MallocHeap(u32 nSize);
void *MAE_Realloc(void *ptr, u32 nSize);
void *MAE_ReallocHeap(void *ptr, u32 nSize);
void *MAE_Calloc(u32 nNum, u32 nSize);
#endif // __SDK_SIMULATION__

s32 MAE_Free(void *ptr);
s32 MAE_FreeLr(void *ptr, u32 nCurrentLr);
boolean MAE_IsHeapMemory(void *ptr);
boolean MAE_IsPoolMemory(void *ptr);
void MAE_SetMemTbl(u8 nType);

#ifdef __DEBUG_POOL__
s32 MAE_FreeAux(void *ptr);
void *MAE_MallocAux(u32 nSize);
void *MAE_ReallocAux(void *ptr, u32 nSize);
#endif /* __DEBUG_POOL__ */

u8 *mae_strdup( const u8 *pStrSource );

#define WCSNCPY(d,s,c) wcsncpy(d,s,c)
#define SWPRINTF mae_swprintf
#define STRNCMP strncmp
#define STRCMP strcmp
#define STRLEN strlen
#define SPRINTF sprintf
#define STRCAT strcat
#define STRCPY strcpy
#define STRNCPY strncpy

#if defined(__MAE_INTERNAL_BUILD__) || defined(VC_MEM_DBG)
#define MALLOC(size)        malloc(size)
#define REALLOC(ptr, size)  realloc(ptr, size)
#define FREE(a)             free(a)
#define FREE_LR(a, b)       free(a)

#define CALLOC(num, size) MAE_Calloc(num, size)

#define MALLOC_HEAP(size) malloc(size)
#define REALLOC_HEAP(ptr, size) realloc(ptr, size)
#define MALLOC_AUX(size) malloc(size)
#define REALLOC_AUX(ptr, size) realloc(ptr, size)
#define FREE_AUX(size) free(size)

#define MEMSET(a,v,n) memset(a,v,n)
#define MEMCMP(s1,s2,size) memcmp(s1,s2,size)
#define MEMMOVE(d,s,c) memmove(d,s,c)
#define MEMCPY(d,s,c) memcpy(d,s,c)
#define STRDUP(X) strdup(X)


#elif (defined __PC_SIMULATOR__)
#ifdef __MMI_CUSVERIFIER_SUPPORT__
#define MALLOC(size)        malloc(size)
#define REALLOC(ptr, size)  realloc(ptr, size)
#define FREE(a)             free(a)
#define FREE_LR(a, b)       free(a)
#else
#define MALLOC(size) MAE_Malloc(size, __LINE__, __MFILE__)
#define REALLOC(ptr, size) MAE_Realloc(ptr, size, __LINE__, __MFILE__)
#define FREE(a) MAE_Free(a)
#define FREE_LR(a, b) MAE_FreeLr(a, b)
#endif
#define CALLOC(num, size) MAE_Calloc(num, size, __LINE__, __MFILE__)


#define MALLOC_HEAP(size) MAE_MallocHeap(size, __LINE__, __MFILE__)
#define REALLOC_HEAP(ptr, size) MAE_ReallocHeap(ptr, size, __LINE__, __MFILE__)

#define MALLOC_AUX(size) malloc(size)
#define REALLOC_AUX(ptr, size) realloc(ptr, size)
#define FREE_AUX(a) free(a)

#define MEMSET(a,v,n) memset(a,v,n)
#define MEMCMP(s1,s2,size) memcmp(s1,s2,size)
#define MEMMOVE(d,s,c) memmove(d,s,c)

#ifdef __SIMULATOR_MEMORY_CHECK_OVERLAY__
#ifdef __MMI_CUSVERIFIER_SUPPORT__
#define MEMCPY(d,s,c) memcpy(d,s,c)
#else
#define MEMCPY(d,s,c) MAE_MEMCPY(d,s,c)
#endif
#else
#define MEMCPY(d,s,c) memcpy(d,s,c)
#endif

#define STRDUP(X) mae_strdup(X)

#else /* target */
#define MALLOC(size) MAE_Malloc(size)
#define REALLOC(ptr, size) MAE_Realloc(ptr, size)
#define FREE(a) MAE_Free(a)
#define FREE_LR(a, b) MAE_FreeLr(a, b)

#define MALLOC_HEAP(size) MAE_MallocHeap(size)
#define REALLOC_HEAP(ptr, size) MAE_ReallocHeap(ptr, size)

#define CALLOC(num,size) MAE_Calloc(num,size)

#ifdef __DEBUG_POOL__
#define MALLOC_AUX(size) MAE_MallocAux(size)
#define REALLOC_AUX(ptr, size) MAE_ReallocAux(ptr, size)
#define FREE_AUX(a) MAE_FreeAux(a)
#else
#define MALLOC_AUX(size) MAE_Malloc(size)
#define REALLOC_AUX(ptr, size) MAE_Realloc(ptr, size)
#define FREE_AUX(a) MAE_Free(a)
#endif /* __DEBUG_POOL__ */

#define MEMSET(a,v,n) memset(a,v,n)
#define MEMCMP(s1,s2,size) memcmp(s1,s2,size)
#define MEMMOVE(d,s,c) memmove(d,s,c)
#define MEMCPY(d,s,c) memcpy(d,s,c)
#define STRDUP(X) mae_strdup(X)
#endif // #ifdef __MAE_INTERNAL_BUILD__ #elif ...

#ifdef __MAE_PLATFORM_DEBUG__
#define BREAK_IF_NULL(p, nRetVar, RetVal, str) \
    {                                          \
        if(NULL == (p))                        \
        {                                      \
            nRetVar = RetVal;                  \
            ASSERT(0); \
            break;\
        }\
    }
#else
#define BREAK_IF_NULL(p, nRetVar, RetVal, str) \
    {\
        if(NULL == (p))\
        {\
            nRetVar = RetVal;\
            LOG_ERROR(MAE_LEVEL_MEM, str);      \
            ASSERT(0);        \
            break;                             \
        }                                      \
    }
#endif //__MAE_PLATFORM_DEBUG__

#ifdef __MAE_PLATFORM_DEBUG__
#define BREAK_IF_FAIL(a, str)                   \
    {                                           \
        if(MAE_RET_SUCCESS != (a))              \
        {                                       \
            ASSERT(0);  \
            break;\
        }\
    }
#else
#define BREAK_IF_FAIL(a, str) \
    {\
        if(MAE_RET_SUCCESS != (a))\
            {                                   \
            LOG_ERROR(MAE_LEVEL_MEM, str, (a)); \
            ASSERT(0);        \
            break;                              \
        }                                       \
    }
#endif //__MAE_PLATFORM_DEBUG__

#ifdef __MAE_PLATFORM_DEBUG__
#define BREAK_IF_WARNING(a, str) \
    {\
        if(MAE_RET_SUCCESS != (a))\
        {\
            break;\
        }\
    }
#else
#define BREAK_IF_WARNING(a, str) \
    {\
    if(MAE_RET_SUCCESS != (a))\
        {\
            LOG_ERROR(MAE_LEVEL_MEM, str, (a));\
            break;\
        }\
    }
#endif

#ifdef __MAE_PLATFORM_DEBUG__
#define RET_IF_FAIL(a, str)                     \
    {                                           \
        if(MAE_RET_SUCCESS != (a))              \
        {                                       \
            ASSERT(0); \
            return;\
        }\
    }
#else
#define RET_IF_FAIL(a, str) \
    {\
        if(MAE_RET_SUCCESS != (a))\
        {                                   \
            LOG_ERROR(MAE_LEVEL_MEM, str, (a));\
            ASSERT(0);       \
            return;                             \
        }                                       \
    }
#endif //__MAE_PLATFORM_DEBUG__

#ifdef __MAE_PLATFORM_DEBUG__
#define RET_VAL_IF_FAIL(a, str)                 \
    {                                           \
        if(MAE_RET_SUCCESS != (a))              \
        {                                       \
            ASSERT(0);                      \
            return (a);\
        }\
    }
#else
#define RET_VAL_IF_FAIL(a, str) \
    {\
        if(MAE_RET_SUCCESS != (a))\
        {\
            LOG_ERROR(MAE_LEVEL_MEM, str, (a)); \
            ASSERT(0);       \
            return (a);                         \
        }                                       \
    }
#endif //__MAE_PLATFORM_DEBUG__

#ifdef __MAE_PLATFORM_DEBUG__
#define RET_IF_NULL(p, str)                \
    {                                      \
        if(NULL == (p))                    \
        {                                  \
            ASSERT(0);\
            return;\
        }\
    }
#else
#define RET_IF_NULL(p, str) \
    {\
        if(NULL == (p))\
        {\
            LOG_ERROR(MAE_LEVEL_MEM, str);\
            ASSERT(0);\
            return;                        \
        }                                  \
    }
#endif //__MAE_PLATFORM_DEBUG__

#ifdef __MAE_PLATFORM_DEBUG__
#define RET_VAL_IF_NULL(p, v, str)         \
    {                                      \
        if(NULL == (p))                    \
        {                                  \
            ASSERT(0); \
            return (v);\
        }\
    }
#else
#define RET_VAL_IF_NULL(p, v, str) \
            {                              \
        if(NULL == (p))\
        {\
            LOG_ERROR(MAE_LEVEL_MEM, str);\
            ASSERT(0);\
            return (v);                    \
        }                                  \
    }
#endif //__MAE_PLATFORM_DEBUG__

#define LOG_IF_FAIL(_level_, a, str) \
    {\
        if(MAE_RET_SUCCESS != (a))\
        {\
            LOG_ERROR((_level_), str, (a));\
        }\
    }

/*
 * _RTPP_DO_LOG is used for macros BREAK_IF_FAIL and its friends
 * that are expanded by the rtpp program in the $(OUT) directory.
 */
#ifdef __MAE_PLATFORM_DEBUG__
#include "mmi_mae_log.h"
#define _RTPP_DO_LOG(...) LOG_ERROR(__VA_ARGS__)
#else
#define _RTPP_DO_LOG(...)
#endif

#ifdef __SDK_SIMULATION__
#include "mmi_mae_unittest_data.h"
#else

typedef enum _HOOKFUNC_DATA_QUERY_RST
{
    HOOKFUNC_DATA_QUERY_FAIL = 0,
    HOOKFUNC_DATA_QUERY_SUCCESS,

} HOOKFUNC_DATA_QUERY_RST;

#define SEND_UT_FUNCTION_NAME(function_name)
#define SEND_UT_FUNCTION_ADDR(func_fp, func_name)
#define SEND_UT_TEXT(text_data, length)
#define SEND_UT_TEMPLATE_NAME(func_name)
#define SEND_UT_POPUP_NAME(func_name)
#define UT_HOOK_FUNCTION(original_func_fp, hook_func_fp)
#define UT_UNHOOK_FUNCTION(original_func_fp)
#define UT_UNHOOK_ALLFUNCTION()
#define QUERY_UT_HOOKFUNC_INT_DATA(original_func_fp, data_name, s32_p, ret_p) {*ret_p = HOOKFUNC_DATA_QUERY_FAIL;}
#define QUERY_UT_HOOKFUNC_STR_DATA(original_func_fp, data_name, u8str_buf, buf_size, str_len, ret_fp) {*ret_p = HOOKFUNC_DATA_QUERY_FAIL;}

#endif

typedef struct
{
    u8  year;            ///< Year value after 1900, value range is 0~255
    u8  month;            ///< Month, value range is 1~12
    u8  day;            ///< Day, value range is 1~31
    u8  dayOfWeek;      ///< [1 = Monday, 7 = Sunday]
    u8  hour;            ///< Hour, value range is 0~23
    u8  minute;            ///< Minute, value range is 0~59
    u8  second;            ///< Second, value range is 0~59
    u16 secondFracPart; ///< Fractionnal part of the second, not used now
}MAE_DateTime_t;     ///<  This structure is identical to vm_rtcTimeFormat_t now

#define    MAE_JULIANDATE_START_YEAR    1900 ///< MAE_DateTime_t.year + MAE_JULIANDATE_START_YEAR should be the real year.

enum
{
    DUAL_MASTER = 0,
    DUAL_SLAVE
};
typedef u8 MAE_DualMode_t;

enum
{
    MAE_DISPID_START = 0,
    MAE_DISPID_MAIN = MAE_DISPID_START,
    MAE_DISPID_SUB,
    MAE_DISPID_SUM
};
typedef u32 MAE_DispId_t;

typedef u8 MAE_Key_t;

enum{
	MAE_SPECIFIED_SCREEN_TYPE_START = 0,
	MAE_SPECIFIED_SCREEN_TYPE_FIRST_OPAQUE_AP = MAE_SPECIFIED_SCREEN_TYPE_START,
	MAE_SPECIFIED_SCREEN_TYPE_CUR_WINDOW_MAINSCR,
	MAE_SPECIFIED_SCREEN_TYPE_END
};
typedef u32 MAE_SpecifiedScreenType_t;

#ifdef __PC_SIMULATOR__
#include "mae_eleak.h"
typedef struct  {
   u16     nParentId;
   u16  nChildId;
   char filename[256];
   int     num;
   int  line;
} LEAK_DATA;
#else
#define SEND_LEAK_INFO(text_data, length)
#define SEND_LEAK_RELEASE(text_data, length)
#endif



//Just for UT test case
extern boolean g_bIgnoreBreakAssert;
#ifdef __PC_SIMULATOR__
#define HOPPER_TEST
#define __SPY__
#endif

#ifdef HOPPER_TEST
typedef struct{
    s16 x;
    s16 y;
    u16 nFlag;
    u16 nCnt;
    u16 nClsId;
}Hit_t;

typedef struct{
    u16 nApId;
    u16 nWinId;
    Hit_t hit;
}HopItem_t;
#endif

#ifdef __SPY__
#define SPY_WND        0
#define SPY_POSTEVT    1
#define SPY_SENDEVT    2
#define SPY_APPLET  3
#define SPY_EVENT    4
#define SPY_SRVCB    5
#define SPY_KEY        6
#define SPY_TOUCH    7

typedef struct{
    u16    nClsId;
    u16 nWndId;
    u32 nAct;
}WinSpy_t;

typedef struct{
    u16 nClsId;
    u32 nEvt;
    u32 nParam1;
    u32 nParam2;
    u32 nAddr;
}EvtSpy_t;

typedef struct{
    u16 nType;
    union{
        WinSpy_t  win;
        EvtSpy_t  evt;
    }body;
}MsgSpy_t;
#endif

#endif //__MAE_COMMON_DEF_H__
/*=============================================================*/
// end of file
