#ifndef FW_STD_H
#define FW_STD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "fw_configure.h"
#include "vm_types.ht"
#include "mmi_log.h" // for ASSERT
#define XMMI_DISABLE_PRINT
#ifdef XMMI
  #ifndef XMMI_DISABLE_PRINT
#include "fw_porting.h"
#include "mmi_mae_common_def.h" // for ASSERT, MALLOC, FREE, STRDUP
  #endif
#endif


#define MF_MAX_FILEPATH_SIZE    516       /* according to FAT32, filename length is 255 */
                                          /* and path length is 260, so 255+260+1=516   */
#define MF_UNICODE_FILE_BOM     0xFEFF    /* byte-order mark(BOM) for unicode file      */

#define MVOID                   void

/* Define the boolean values of TRUE and FALSE */
#define MBOOL_TRUE  1
#define MBOOL_FALSE 0

/* Prototype Aliasing */
typedef int             MBOOL,     *PMBOOL;
typedef long            MLONG,     *PMLONG;     /* In 64-bit architecture, its size is 8 bytes */
typedef unsigned long   MULONG,    *PMULONG;    /* In 64-bit architecture, its size is 8 bytes */
typedef U32             MHANDLE,   *PMHANDLE;    /* HANDLE has defined in WIN32 */

typedef void           *PMVOID;

typedef float           MFLOAT,    *PMFLOAT;
typedef double          MDOUBLE,   *PMDOUBLE;

/* In generally, size_t is type-defined with unsigned long */
#define MSIZET          size_t
typedef size_t         *PMSIZET;

#include "fw_long64.h"

/* data structure of the vertex */
typedef struct Vertex_s
{
    S32 s32X;    /* The x coordinate */
    S32 s32Y;    /* The y coordinate */
} Vertex_st,*pVertex_st;

/* data structure of the bounding box */
typedef struct BBox_s
{
    S32 s32Left;      /* the left x coordinate of the bounding box   */
    S32 s32Bottom;    /* the bottom y coordinate of the bounding box */
    S32 s32Right;     /* the right x coordinate of the bounding box  */
    S32 s32Top;       /* the top y coordinate of the bounding box    */
} BBox_st,*pBBox_st;

/* data structure of the timestamp */
typedef struct Time_s
{
    U16 u16Year;        /* Year. */
    U8 u8Month;         /* Month.       [1-12] */
    U8 u8MDay;          /* Month day.   [1-31] */
    U8 u8Hour;          /* Hour.        [0-23] */
    U8 u8Min;           /* Minute.      [0-59] */
    U8 u8Sec;           /* Second.      [0-59] */
} Time_st, *pTime_st;

#include "fw_mm.h"

#define MF_MEMSET  memset
#define MF_MEMCPY  memcpy
#define MF_MEMCMP  memcmp

#define MF_MMINITIALIZE mfMMInitialize
#define MF_MMFINALIZE   mfMMFinalize
#define MF_MALLOC       mfMMMalloc
#define MF_CALLOC       mfMMCalloc
#define MF_REALLOC      mfMMRealloc
#define MF_STRDUP       mfMMStrdup
#define MF_FREE(x)      {if(x) {mfMMFree(x);x=NULL;}}

#include "fw_file.h"
#include "fw_unicode.h"
#include "fw_profiling.h"

#ifdef linux
    #define UCS2_TEXT(x)    mfUniWcharToUCS2((L##x))
#else    /* !defined(linux) */
    #define UCS2_TEXT(x)    (L##x)
#endif    /* end of #ifdef linux */

#if defined(XMMI)
  #ifdef UNICODE
        #define FILE_DELM     UCS2_TEXT('/')
        #define FILE_DELM_STR UCS2_TEXT("/")
    #else    /* !defined(UNICODE) */
        #define FILE_DELM     '/'
        #define FILE_DELM_STR "/"
    #endif    /* end of #ifdef UNICODE */
#elif defined(WIN32)||defined(WINCE)
    #ifdef UNICODE
        #define FILE_DELM     UCS2_TEXT('\\')
        #define FILE_DELM_STR UCS2_TEXT("\\")
    #else    /* !defined(UNICODE) */
        #define FILE_DELM     '\\'
        #define FILE_DELM_STR "\\"
    #endif    /* end of #ifdef UNICODE */
#else    /* (!defined(WIN32))&&(!defined(WINCE)) */
    #ifdef UNICODE
        #define FILE_DELM     UCS2_TEXT('/')
        #define FILE_DELM_STR UCS2_TEXT("/")
    #else    /* !defined(UNICODE) */
        #define FILE_DELM     '/'
        #define FILE_DELM_STR "/"
    #endif    /* end of #ifdef UNICODE */
#endif    /* end of #if defined(WIN32)||defined(WINCE) */

#ifdef USE_DEBUG
    #if defined(XMMI)
	#ifndef XMMI_DISABLE_PRINT
	  #define PRINTF(x,...)
         #define MF_ASSERT
	  #define printf(x)
	#else
         #define PRINTF(x,...)  fw_printf(x, ##__VA_ARGS__)
         #define MF_ASSERT    ASSERT
	  #define printf(x)
	#endif
    #else
	 #define PRINTF printf
	 #include <assert.h>
         #define MF_ASSERT(x)    assert(x)
    #endif
#else    /* !defined(USE_DEBUG) */
    #ifdef XMMI
	 #define printf(x,...)
	 #define MF_ASSERT(x)
        #ifdef WIN32
        #define PRINTF(x,...) LOG_TRACE(MMI_LEVEL_MAPVIEW, x, ##__VA_ARGS__)
        #else
        #define PRINTF(x,...)  fw_printf(x, ##__VA_ARGS__)
        #endif
    #else // xmmi
        #if defined(WIN32)||defined(WINCE)
          #define PRINTF
        #else    /* (!defined(WIN32))&&(!defined(WINCE)) */
          #define PRINTF(x,...)
        #endif    /* end of #if defined(WIN32)||defined(WINCE) */
	 #define MF_ASSERT(x)
    #endif // xmmi

#endif    /* end of #ifdef DEBUG */

// 20090105 By JL Chuang
#ifdef XMMI
  #define sprintf_s(x,y,z,...) vsprintf(x,z, ##__VA_ARGS__)
//  #define sprintf vsprintf
  #undef SPRINTF
  #define SPRINTF vsprintf
  #define WSPRINTF mae_swprintf
#endif

#define MF_ABS(x)      ((x)>0?(x):-(x))
#define MF_MAX(x,y)    ((x)>(y)?(x):(y))
#define MF_MIN(x,y)    ((x)<(y)?(x):(y))


#define MF_SQRT(x)     sqrt((MDOUBLE)(x))

/* prototype casting */
/* one character */
/* one character to short */
#define MF_ONE_CHAR_TO_INT16(x)            ((S16)(x))
/* one character to unsigned short */
#define MF_ONE_CHAR_TO_UINT16(x)           ((U16)(x))
/* one character to int */
#define MF_ONE_CHAR_TO_INT32(x)            ((S32)(x))
/* one character to unsigned int */
#define MF_ONE_CHAR_TO_UINT32(x)           ((U32)(x))
/* one character to float */
#define MF_ONE_CHAR_TO_FLOAT(x)            ((MFLOAT)(x))
/* one character to double */
#define MF_ONE_CHAR_TO_DOUBLE(x)           ((MDOUBLE)(x))

/* one short integer */
/* one short to int */
#define MF_ONE_INT16_TO_INT32(x)           ((S32)(x))
/* one short to unsigned int */
#define MF_ONE_INT16_TO_UINT32(x)          ((U32)(x))
/* one short to float */
#define MF_ONE_INT16_TO_FLOAT(x)           ((MFLOAT)(x))
/* one short to double */
#define MF_ONE_INT16_TO_DOUBLE(x)          ((MDOUBLE)(x))

/* one int integer */
/* one int to float */
#define MF_ONE_INT32_TO_FLOAT(x)           ((MFLOAT)(x))
/* one int to double */
#define MF_ONE_INT32_TO_DOUBLE(x)          ((MDOUBLE)(x))

/* two characters */
/* two characters to short (big endian): byte(0)~byte(1) */
#define MF_TWO_CHAR_TO_INT16_B(x)          ((S16)(((((U16)((x)[0]))<<8)&0xFF00)|           \
                                                  (((U16)((x)[1]))&0x00FF)))
/* two characters to unsigned short (big endian): byte(0)~byte(1) */
#define MF_TWO_CHAR_TO_UINT16_B(x)         ((U16)(((((U16)((x)[0]))<<8)&0xFF00)|           \
                                                  (((U16)((x)[1]))&0x00FF)))
/* two characters to short (big endian): byte(i)~byte(i+1) */
#define MF_TWO_CHAR_TO_INT16_IB(x,i)       ((S16)(((((U16)((x)[i]))<<8)&0xFF00)|           \
                                                  (((U16)((x)[i+1]))&0x00FF)))
/* two characters to unsigned short (big endian): byte(i)~byte(i+1) */
#define MF_TWO_CHAR_TO_UINT16_IB(x,i)      ((U16)(((((U16)((x)[i]))<<8)&0xFF00)|           \
                                                  (((U16)((x)[i+1]))&0x00FF)))
/* two characters to short (little endian): byte(1)~byte(0) */
#define MF_TWO_CHAR_TO_INT16_L(x)          ((S16)(((((U16)((x)[1]))<<8)&0xFF00)|           \
                                                  (((U16)((x)[0]))&0x00FF)))
/* two characters to unsigned short (little endian): byte(1)~byte(0) */
#define MF_TWO_CHAR_TO_UINT16_L(x)         ((U16)(((((U16)((x)[1]))<<8)&0xFF00)|           \
                                                  (((U16)((x)[0]))&0x00FF)))
/* two characters to short (little endian): byte(i+1)~byte(i) */
#define MF_TWO_CHAR_TO_INT16_IL(x,i)       ((S16)(((((U16)((x)[i+1]))<<8)&0xFF00)|         \
                                                  (((U16)((x)[i]))&0x00FF)))
/* two characters to unsigned short (little endian): byte(i+1)~byte(i) */
#define MF_TWO_CHAR_TO_UINT16_IL(x,i)      ((U16)(((((U16)((x)[i+1]))<<8)&0xFF00)|         \
                                                  (((U16)((x)[i]))&0x00FF)))
/* two characters to int (big endian): byte(0)~byte(1) */
#define MF_TWO_CHAR_TO_INT32_B(x)          ((S32)(((((U32)((x)[0]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[1]))&0x000000FF)))
/* two characters to unsigned int (big endian): byte(0)~byte(1) */
#define MF_TWO_CHAR_TO_UINT32_B(x)         ((U32)(((((U32)((x)[0]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[1]))&0x000000FF)))
/* two characters to int (big endian): byte(i)~byte(i+1) */
#define MF_TWO_CHAR_TO_INT32_IB(x,i)       ((S32)(((((U32)((x)[i]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[i+1]))&0x000000FF)))
/* two characters to unsigned int (big endian): byte(i)~byte(i+1) */
#define MF_TWO_CHAR_TO_UINT32_IB(x,i)      ((U32)(((((U32)((x)[i]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[i+1]))&0x000000FF)))
/* two characters to int (little endian): byte(1)~byte(0) */
#define MF_TWO_CHAR_TO_INT32_L(x)          ((S32)(((((U32)((x)[1]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[0]))&0x000000FF)))
/* two characters to unsigned int (little endian): byte(1)~byte(0) */
#define MF_TWO_CHAR_TO_UINT32_L(x)         ((U32)(((((U32)((x)[1]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[0]))&0x000000FF)))
/* two characters to int (little endian): byte(i+1)~byte(i) */
#define MF_TWO_CHAR_TO_INT32_IL(x,i)       ((S32)(((((U32)((x)[i+1]))<<8)&0x0000FF00)|     \
                                                  (((U32)((x)[i]))&0x000000FF)))
/* two characters to unsigned int (little endian): byte(i+1)~byte(i) */
#define MF_TWO_CHAR_TO_UINT32_IL(x,i)      ((U32)(((((U32)((x)[i+1]))<<8)&0x0000FF00)|     \
                                                  (((U32)((x)[i]))&0x000000FF)))

/* four characters */
/* four characters to int (big endian): byte(0)~byte(3) */
#define MF_FOUR_CHAR_TO_INT32_B(x)         ((S32)(((((U32)((x)[0]))<<24)&0xFF000000)|      \
                                                  ((((U32)((x)[1]))<<16)&0x00FF0000)|      \
                                                  ((((U32)((x)[2]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[3]))&0x000000FF)))
/* four characters to unsigned int (big endian): byte(0)~byte(3) */
#define MF_FOUR_CHAR_TO_UINT32_B(x)        ((U32)(((((U32)((x)[0]))<<24)&0xFF000000)|      \
                                                  ((((U32)((x)[1]))<<16)&0x00FF0000)|      \
                                                  ((((U32)((x)[2]))<<8)&0x0000FF00)|       \
                                                  (((U32)((x)[3]))&0x000000FF)))
/* four characters to int (big endian): byte(i)~byte(i+3) */
#define MF_FOUR_CHAR_TO_INT32_IB(x,i)      ((S32)(((((U32)((x)[i]))<<24)&0xFF000000)|      \
                                                  ((((U32)((x)[i+1]))<<16)&0x00FF0000)|    \
                                                  ((((U32)((x)[i+2]))<<8)&0x0000FF00)|     \
                                                  (((U32)((x)[i+3]))&0x000000FF)))
/* four characters to unsigned int (big endian): byte(i)~byte(i+3) */
#define MF_FOUR_CHAR_TO_UINT32_IB(x,i)     ((U32)(((((U32)((x)[i]))<<24)&0xFF000000)|      \
                                                  ((((U32)((x)[i+1]))<<16)&0x00FF0000)|    \
                                                  ((((U32)((x)[i+2]))<<8)&0x0000FF00)|     \
                                                  (((U32)((x)[i+3]))&0x000000FF)))
/* four characters to int (little endian): byte(3)~byte(0) */
#define MF_FOUR_CHAR_TO_INT32_L(x)         ((S32)(((((S32)((x)[3]))<<24)&0xFF000000)|      \
                                                  ((((S32)((x)[2]))<<16)&0x00FF0000)|      \
                                                  ((((S32)((x)[1]))<<8)&0x0000FF00)|       \
                                                  (((S32)((x)[0]))&0x000000FF)))
/* four characters to unsigned int (little endian): byte(3)~byte(0) */
#define MF_FOUR_CHAR_TO_UINT32_L(x)        ((U32)(((((S32)((x)[3]))<<24)&0xFF000000)|      \
                                                  ((((S32)((x)[2]))<<16)&0x00FF0000)|      \
                                                  ((((S32)((x)[1]))<<8)&0x0000FF00)|       \
                                                  (((S32)((x)[0]))&0x000000FF)))
/* four characters to int (little endian): byte(i+3)~byte(i) */
#define MF_FOUR_CHAR_TO_INT32_IL(x,i)      ((S32)(((((S32)((x)[i+3]))<<24)&0xFF000000)|    \
                                                  ((((S32)((x)[i+2]))<<16)&0x00FF0000)|    \
                                                  ((((S32)((x)[i+1]))<<8)&0x0000FF00)|     \
                                                  (((S32)((x)[i]))&0x000000FF)))
/* four characters to unsigned int (little endian): byte(i+3)~byte(i) */
#define MF_FOUR_CHAR_TO_UINT32_IL(x,i)     ((U32)(((((S32)((x)[i+3]))<<24)&0xFF000000)|    \
                                                  ((((S32)((x)[i+2]))<<16)&0x00FF0000)|    \
                                                  ((((S32)((x)[i+1]))<<8)&0x0000FF00)|     \
                                                  (((S32)((x)[i]))&0x000000FF)))

/* string to char */
#define MF_STRING_TO_INT8(x)               ((S8)atoi((const PS8)(x)))
/* string to unsigned char */
#define MF_STRING_TO_UINT8(x)              ((U8)atoi((const PS8)(x)))
/* string to short */
#define MF_STRING_TO_INT16(x)              ((S16)atoi((const PS8)(x)))
/* string to unsigned short */
#define MF_STRING_TO_UINT16(x)             ((U16)atoi((const PS8)(x)))
/* string to int */
#define MF_STRING_TO_INT32(x)              ((S32)atoi((const PS8)(x)))
/* string to unsigned int */
#define MF_STRING_TO_UINT32(x)             ((U32)atoi((const PS8)(x)))
/* string to double */
#define MF_STRING_TO_DOUBLE(x)             (atof((const PS8)(x)))
/* string to float */
#define MF_STRING_TO_FLOAT(x)              ((MFLOAT)atof((const PS8)(x)))

/* UTF8 */
/* 1-byte UTF8 code to unsigned short */
#define MF_ONE_BYTE_UTF8_TO_UINT16(x)      ((U16)(x))
/* 2-byte UTF8 codes to unsigned short */
#define MF_TWO_BYTE_UTF8_TO_UINT16(x)      ((U16)(((((U16)((x)[0]))<<6)&0x07C0)|          \
                                                  (((U16)((x)[1]))&0x003F)))
/* 3-byte UTF8 codes to unsigned short */
#define MF_THREE_BYTE_UTF8_TO_UINT16(x)    ((U16)(((((U16)((x)[0]))<<12)&0xF000)|         \
                                                  ((((U16)((x)[1]))<<6)&0x0FC0)|          \
                                                  (((U16)((x)[2]))&0x003F)))

#define MF_OFFSETOF(s, f) ((int)((char*)&((s*)0)->f))

#endif    /* end of #ifndef FW_STD_H */
