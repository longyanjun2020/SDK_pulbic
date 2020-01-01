//==============================================================================
//
//  File        : mmp_lib.h
//  Description : Top level global definition and configuration.
//  Author      : Jerry Tsao
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_LIB_H_
#define _MMP_LIB_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"
#include "mmp_err.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#ifndef NULL
    #define NULL            (0)
#endif

#define MMP_TRUE                     (1)
#define MMP_FALSE                    (0)

#define FLOOR2(_a)                   ((_a) >> 1 << 1)
#define FLOOR4(_a)                   ((_a) >> 2 << 2)
#define FLOOR8(_a)                   ((_a) >> 3 << 3)
#define FLOOR16(_a)                  ((_a) >> 4 << 4)
#define FLOOR32(_a)                  ((_a) >> 5 << 5)
#define FLOOR256(_a)                 ((_a) >> 8 << 8)
#define FLOOR512(_a)                 ((_a) >> 9 << 9)
#define FLOOR_X(base, x)             ((base) & (-x))

#define ALIGN2(_a)                   (((_a) + 1) >> 1 << 1)
#define ALIGN4(_a)                   (((_a) + 3) >> 2 << 2)
#define ALIGN8(_a)                   (((_a) + 7) >> 3 << 3)
#define ALIGN16(_a)                  (((_a) + 15) >> 4 << 4)
#define ALIGN32(_a)                  (((_a) + 31) >> 5 << 5)
#define ALIGN64(_a)                  (((_a) + 63) >> 6 << 6)
#define ALIGN256(_a)                 (((_a) + 255) >> 8 << 8)
#define ALIGN512(_a)                 (((_a) + 511) >> 9 << 9)
#define ALIGN4K(_a)                  (((_a) + 0xFFF) >> 12 << 12)
#define ALIGN_X(base, x)             ((base + x - 1) & (-x))

#define ALIGN2_ROUND_UP(_a)          (((_a) + 2) >> 1 << 1)
#define ALIGN4_ROUND_UP(_a)          (((_a) + 4) >> 2 << 2)
#define ALIGN8_ROUND_UP(_a)          (((_a) + 8) >> 3 << 3)
#define ALIGN16_ROUND_UP(_a)         (((_a) + 16) >> 4 << 4)
#define ALIGN32_ROUND_UP(_a)         (((_a) + 32) >> 5 << 5)
#define ALIGN64_ROUND_UP(_a)         (((_a) + 64) >> 6 << 6)
#define ALIGN256_ROUND_UP(_a)        (((_a) + 256) >> 8 << 8)
#define ALIGN512_ROUND_UP(_a)        (((_a) + 512) >> 9 << 9)
#define ALIGN4K_ROUND_UP(_a)         (((_a) + 0x1000) >> 12 << 12)
#define ALIGN_X_ROUND_UP(base, x)    ((base + x) & (-x))

#ifndef CEIL 
#define CEIL(_N, _M)                 (((_N%_M)>0)?((_N/_M)+1):(_N/_M))
#endif

#define SHIFT24(_a)		             ((_a) >> 24)
#define MASK24(_a)		             ((_a) & 0x00FFFFFF)

#define SHIFT16(_a)		             ((_a) >> 16)
#define MASK16(_a)		             ((_a) & 0x0000FFFF)

#define SHIFT8(_a)		             ((_a) >> 8)
#define MASK8(_a)		             ((_a) & 0x00FF)

#define MOD_PW2(_a, _b)              ((_a) & (_b-1))

/** @brief Debug break point // Truman 06-Nov-06
 * Usage: Simply add this macro as a statesment.\n
 * If the debug environment can't sync with IDE, you could use this to set an break point for quick debugging.\n
 * You could run to the break point and break the debugger.
 * Then set the real break_point or trace the variables.
 */
#define BREAK_POINT {\
    MMP_BYTE c[2];\
    GETS(&c[0]);\
}

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================


typedef unsigned int        u_int   ;
typedef unsigned short      u_short ;
typedef unsigned char       u_char  ;

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================
/*******************************************************************************
 *
 *   ESCAPE CODE FOR UART COLOR PRINT
 *
*******************************************************************************/
#define ESC_ATR_COLOR_DEFAULT                        "\033[0m"
#define ESC_ATR_COLOR_BRIGHTER                       "\033[1m"
#define ESC_ATR_COLOR_UNDERLINED                     "\033[4m"
#define ESC_ATR_COLOR_FLASHING                       "\033[5m"
#define ESC_FG_COLOR_BLACK                          "\033[30m"
#define ESC_FG_COLOR_RED                            "\033[31m"
#define ESC_FG_COLOR_GREEN                          "\033[32m"
#define ESC_FG_COLOR_YELLOW                         "\033[33m"
#define ESC_FG_COLOR_BLUE                           "\033[34m"
#define ESC_FG_COLOR_PURPLE                         "\033[35m"
#define ESC_FG_COLOR_CYAN                           "\033[36m"
#define ESC_FG_COLOR_GRAY                           "\033[37m"
#define ESC_BG_COLOR_BLACK                          "\033[40m"
#define ESC_BG_COLOR_RED                            "\033[41m"
#define ESC_BG_COLOR_GREEN                          "\033[42m"
#define ESC_BG_COLOR_YELLOW                         "\033[43m"
#define ESC_BG_COLOR_BLUE                           "\033[44m"
#define ESC_BG_COLOR_PURPLE                         "\033[45m"
#define ESC_BG_COLOR_CYAN                           "\033[46m"
#define ESC_BG_COLOR_GRAY                           "\033[47m"

/*******************************************************************************
 *
 *   MARCO OF ESCAPE CODE FOR UART COLOR PRINT
 *
*******************************************************************************/

#define AT_DEFAULT(X)             ESC_ATR_COLOR_DEFAULT        X
#define AT_BRIGHTER (X)           ESC_ATR_COLOR_BRIGHTER       X ESC_ATR_COLOR_DEFAULT
#define AT_UNDERLINED(X)          ESC_ATR_COLOR_UNDERLINED     X ESC_ATR_COLOR_DEFAULT
#define AT_FLASHING(X)            ESC_ATR_COLOR_FLASHING       X ESC_ATR_COLOR_DEFAULT
#define FG_BLACK(X)               ESC_FG_COLOR_BLACK           X ESC_ATR_COLOR_DEFAULT
#define FG_RED(X)                 ESC_FG_COLOR_RED             X ESC_ATR_COLOR_DEFAULT
#define FG_GREEN(X)               ESC_FG_COLOR_GREEN           X ESC_ATR_COLOR_DEFAULT
#define FG_YELLOW(X)              ESC_FG_COLOR_YELLOW          X ESC_ATR_COLOR_DEFAULT
#define FG_BLUE(X)                ESC_FG_COLOR_BLUE            X ESC_ATR_COLOR_DEFAULT
#define FG_PURPLE(X)              ESC_FG_COLOR_PURPLE          X ESC_ATR_COLOR_DEFAULT
#define FG_CYAN(X)                ESC_FG_COLOR_CYAN            X ESC_ATR_COLOR_DEFAULT
#define FG_GRAY(X)                ESC_FG_COLOR_GRAY            X ESC_ATR_COLOR_DEFAULT
#define BG_BLACK(X)               ESC_BG_COLOR_BLACK           X ESC_ATR_COLOR_DEFAULT
#define BG_RED(X)                 ESC_BG_COLOR_RED             X ESC_ATR_COLOR_DEFAULT
#define BG_GREEN(X)               ESC_BG_COLOR_GREEN           X ESC_ATR_COLOR_DEFAULT
#define BG_YELLOW(X)              ESC_BG_COLOR_YELLOW          X ESC_ATR_COLOR_DEFAULT
#define BG_BLUE(X)                ESC_BG_COLOR_BLUE            X ESC_ATR_COLOR_DEFAULT
#define BG_PURPLE(X)              ESC_BG_COLOR_PURPLE          X ESC_ATR_COLOR_DEFAULT
#define BG_CYAN(X)                ESC_BG_COLOR_CYAN            X ESC_ATR_COLOR_DEFAULT
#define BG_GRAY(X)                ESC_BG_COLOR_GRAY            X ESC_ATR_COLOR_DEFAULT

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

void printc( char* szFormat, ... );
void printd( char* szFormat, ... );
void print_dbg( char* szFormat, ... );
void print_static( char* szFormat, ... );

//t for temp debugging only. Use a highlighted color. It should be removed before commit the code
//to ensure it is removed, comment this define
#define printt(str,...) printc(ESC_ATR_COLOR_BRIGHTER FG_PURPLE(str), __VA_ARGS__)
#define printt0(str) printc(ESC_ATR_COLOR_BRIGHTER FG_PURPLE(str))

void printstr( char* szFormat);

#ifdef __RTK_OS__
#define WEAK_FUNC(x) x __attribute__((weak))
#else
#define WEAK_FUNC(x) __weak x
#endif

extern signed char UartSendTrace(const char *strFormat, ...);
#define MMP_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define MMP_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#endif // _MMP_LIB_H_
