#ifndef _mcfcommon_h_
#define _mcfcommon_h_
#ifdef __cplusplus   
extern "C"{   
#endif // __cplusplus

#include "mcr_typedef.h"

#ifndef ALOG_LEVEL_ENUM
typedef enum {
    ALOG_INFO = 1,
    ALOG_WARN,
    ALOG_ERROR,
    ALOG_LEVEL_MAX
}ALogLevelEnum;
#define ALOG_LEVEL_ENUM
#endif

//#define ALOG_APIAUDIO   0
//#define ALOG_APISOCKET  1//todo ...
//#define ALOG_APIMEMORY  2
//#define ALOG_APIGDI		3
//#define ALOG_APIFILE	4


//API LOG控制
#ifdef MCR_DEBUG
//#define MCR_DEBUG_PORTING_APIAUDIO
//#define MCR_DEBUG_PORTING_APISOCKET
//#define MCR_DEBUG_PORTING_APIMEMORY
//#define MCR_DEBUG_PORTING_APIGDI
//#define MCR_DEBUG_PORTING_APIFILE
//#define MCR_DEBUG_PORTING_APIMISC
//#define MCR_DEBUG_PORTING_APISMS
//#define MCR_DEBUG_PORTING_TIMER
#endif


//AUDIO
#ifdef MCR_DEBUG_PORTING_APIAUDIO
#define MCFAPI_AUDIO_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_AUDIO_PRINT
#endif

//SOCKET
#ifdef MCR_DEBUG_PORTING_APISOCKET
#define MCFAPI_SOCKET_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_SOCKET_PRINT
#endif

//MEMORY
#ifdef MCR_DEBUG_PORTING_APIMEMORY
#define MCFAPI_MEMORY_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_MEMORY_PRINT
#endif

//GDI
#ifdef MCR_DEBUG_PORTING_APIGDI
#define MCFAPI_GDI_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_GDI_PRINT
#endif

//FILE
#ifdef MCR_DEBUG_PORTING_APIFILE
#define MCFAPI_FILE_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_FILE_PRINT
#endif

//MISC
#ifdef MCR_DEBUG_PORTING_APIMISC
#define MCFAPI_MISC_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_MISC_PRINT
#endif

//SMS
#ifdef MCR_DEBUG_PORTING_APISMS
#define MCFAPI_SMS_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_SMS_PRINT
#endif

//TIMER
#ifdef MCR_DEBUG_PORTING_TIMER
#define MCFAPI_TIMER_PRINT   McfTrace_LogPrintA
#else
#define MCFAPI_TIMER_PRINT
#endif


//#define MCFAPI_PRINT   McfTrace_LogPrintA //McfCmn_LogPrint


#define  IN
#define  OUT


#ifndef MNULL
#define MFALSE  (0)
#define MTRUE   (1)
#define MNULL   ((void*)0)

typedef unsigned char       MBOOL;
typedef void                MVOID;
typedef char                MCHAR;//
typedef unsigned char       MBYTE;
typedef unsigned short      MWCHAR;
typedef signed short        MSHORT;
typedef unsigned short      MUSHORT;
typedef signed long         MLONG;
typedef unsigned long       MULONG;
typedef signed int          MINT;
typedef unsigned int        MUINT;

#endif
//不具备界面显示能力，具有该属性的应用将不能显示在应用列表里
#define MCR_STR_ABILITY_NOUI                   ("nui")
//具备后台运行能力
#define MCR_STR_ABILITY_BACKGROUNDRUN          ("bac")
//具备处理url的能力
//具备处理文本的能力

typedef unsigned int APPID;

typedef MINT TMCRFD;

#define UNUSED_PARAM(x)     (x)


#define __MFILE_NAME_LEN__  256

MVOID McfCmn_Initialize(MVOID);
MVOID McfCmn_Deinitialize(MVOID);
MVOID *McfCmn_GetGlobalVar(MVOID);

/*
Moving Porting ID into Libarary.
KEL.
*/
MINT Mcf_HelperPortingID(MVOID);

#ifdef __cplusplus   
}   
#endif // __cplusplus
#endif//#ifndef MCRCOMMON_H
