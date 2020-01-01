#ifndef FW_CONFIGURE_H
#define FW_CONFIGURE_H

/*************************************************/
/* Please do some modification for your platform */
/*************************************************/
/* Decide whether to use buffer I/O for file access */
/* #define WIN32 */
/* #define WINCE */
/* #define linux*/

#define XMMI

/* Decide whether to support unicode-encoded file or path names */
/* The option will be decided by Makefile so the below two lines are commented */
/* #define UNICODE */
/* #undef UNICODE */

/* Decide whether to use buffer I/O for file access */
/* The option will be decided by Makefile so the below two lines are commented */
/* #define USE_BUFFER_IO */
/* #undef USE_BUFFER_IO */

/* Decide whether to use memory management to track the usage of memory space */
/* The option will be decided by Makefile so the below two lines are commented */
/* #define USE_MM_MALLOC */
/* #undef USE_MM_MALLOC */

/* Decide whether to use 64-bit long integer */
/* The option will be decided by Makefile so the below two lines are commented */
#define USE_LONG64
/* #undef USE_LONG64 */

/* Decide whether the compiler supports 64-bit long integer prototype */
/* The option will be decided by Makefile so the below two lines are commented */
#define SUPPORT_LONG64
/* #undef SUPPORT_LONG64 */

/* Decide whether to use big-endian data format to implement 64-bit long integer */
/* #define LONG64_BIG_ENDIAN */
#undef LONG64_BIG_ENDIAN

/* Decide whether to support standard output for the display of the debugging messages */
/* The option will be decided by Makefile so the below two lines are commented */
/* #define USE_DEBUG */
/* #undef USE_DEBUG */

/* Decide the basic factor of a degree for LOD0 DB */
#define DB_BASIC_DEGREE_FACTOR 80    /* 100, 80, 50 */

/* Decide whether to keep the previous involved grid raw data instead of re-construction of the relation */
#define KEEP_INVOLVED_GRID_RAW
/* #undef KEEP_INVOLVED_GRID_RAW */

/* Decide whether to do profiling */
/* #define SUPPORT_PROFILING */
/* #undef SUPPORT_PROFILING */

/* Decide whether to record all of detailed profiling flows */
#ifdef SUPPORT_PROFILING
#define PROFILING_DETAIL
/* #undef PROFILING_DETAIL */
#endif    /* end of #ifdef SUPPORT_PROFILING */

/* Decide whether to do profiling for routing and file access only */
/* #define PROFILING_ROUTE_FILE */
/* #undef PROFILING_ROUTE_FILE */

/* Decide whether to support the twice road drawing to draw the road with border */
#ifndef SUPPORT_TWICE_RD_DRAWING
#define SUPPORT_TWICE_RD_DRAWING
/* #undef SUPPORT_TWICE_RD_DRAWING */
#endif    /* end of #ifndef SUPPORT_TWICE_RD_DRAWING */

/*********************************************************/
/* Please DON'T do any modification for below definition */
/*********************************************************/

/* Here're the dependencies among various compilation options. */
/* DON'T do any modification.                                  */
/* It needs to consider whether to support 64-bit long integer when trying to use 64-bit long integer */
#ifndef USE_LONG64
    #undef SUPPORT_LONG64
#endif    /* end of #ifndef USE_LONG64 */

/* Define the all of interface in unicode for filenames and strings */
#ifndef UNICODE
    #define UNICODE
#endif    /* end of #ifndef UNICODE */

/* Only do profiling for routing and file access so it's also necessary to turn on SUPPORT_PROFILING and PROFILING_DETAIL */
#ifdef PROFILING_ROUTE_FILE
#define SUPPORT_PROFILING
#endif    /* end of #ifdef PROFILING_ROUTE_FILE */

/* Define screen width, height here */
#ifndef EXCALIBUR_SCREEN_WIDTH
    #define EXCALIBUR_SCREEN_WIDTH     320
#endif    /* end of #ifndef EXCALIBUR_SCREEN_WIDTH */

#ifndef EXCALIBUR_SCREEN_HEIGHT
    #define EXCALIBUR_SCREEN_HEIGHT    240
#endif    /* end of #ifndef EXCALIBUR_SCREEN_HEIGHT */

#ifndef EXCALIBUR_ORIGION_SHIFT
    #define EXCALIBUR_ORIGION_SHIFT    0
#endif    /* end of #ifndef EXCALIBUR_ORIGION_SHIFT */

#endif    /* end of #ifndef FW_CONFIGURE_H */
