#ifndef _DEFTYPES_H_
#define _DEFTYPES_H_

#define _SMALLER_CODESIZE_
//#define _SUPPORT_DUMP_        // Support reconstructed YUV dumping. For debug usage.


#if (defined(_MIPS_) || defined(ARM9) ||defined(__RTK_OS__))&&!defined(__AEON__)
#define swenc_assert(x)
#else
    #include <assert.h>
#define swenc_assert(x) assert(x)
#endif

#if (defined(_MIPS_) || defined(ARM9) ||defined(__RTK_OS__))&&!defined(__AEON__)
//    #define assert(x)
    #define TRUE			1
    #define FALSE			1
    #define NULL			0
	#define OK              0
	#define ERROR          -1
#else
//    #include <assert.h>
#endif

#if defined(WIN32)
    #if _MSC_VER >= 1310 // VC2003 and above
        #define __align16 __declspec(align(16))
    #else
        #define __align16
    #endif
    #define MEMALLOC(Param) VirtualAlloc(NULL, Param, MEM_COMMIT, PAGE_READWRITE)
    #define MEMFREE(Param) VirtualFree(Param, 0, MEM_RELEASE)
    #define ALWAYSINLINE __forceinline
#elif defined(WINCE)
    #define __align16
    #define MEMALLOC(Param) malloc(Param)
    #define MEMFREE(Param) free(Param)
    #define ALWAYSINLINE __forceinline
#elif defined(ARM9)
    #define __align16 __attribute__ ((aligned (16)))
    #define MEMALLOC(Param) //malloc(Param)
    #define MEMFREE(Param) //free(Param)
    #define ALWAYSINLINE __forceinline
#elif defined(__AEON__)
    #define __align16 __attribute__ ((aligned (16)))
    #define MEMALLOC(Param) //malloc(Param)
    #define MEMFREE(Param) //free(Param)
    #define ALWAYSINLINE inline
#else
    #define __align16 __attribute__ ((aligned (16)))
    #define MEMALLOC(Param) malloc(Param)
    #define MEMFREE(Param) free(Param)
    #define ALWAYSINLINE __attribute__((always_inline))
#endif

/**************************************************************************
*  Use 'int' and 'unsigned' ('unsigned int') for signed and unsigned
*    integer if you do not care whether they are 16 or 32 bits.
*  Use int16, int32, uint16 and uint32 instead if you do care
**************************************************************************/


#if defined(__RTK_OS__)&&!defined(__AEON__)
typedef unsigned int u32;
#endif

#ifdef WIN32
typedef unsigned char       uchar;
typedef unsigned char       uint8;
typedef unsigned __int16    uint16;
typedef unsigned __int32    uint32;
typedef unsigned __int64    uint64;
typedef signed char         int8;
typedef __int16             int16;
typedef __int32             int32;
typedef __int64             int64;

#elif defined(__RTK_OS__)
#include "vm_types.ht"
typedef u8 uchar;
typedef u8 uint8;
typedef s8 int8;
typedef u16 uint16;
typedef s16 int16;
typedef u32 uint32;
typedef s32 int32;
typedef u64 uint64;
typedef s64 int64;
#else
#include <stdint.h>
typedef uint8_t  uchar;
typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;
#endif
/********** Type Definition for Non-Windows System **********/

#ifdef _MIPS_
#define __stdcall
#endif

typedef enum Bool {
	E_FALSE = 0,
	E_TRUE = 1,
} Bool;

// -----------------------------------------------------
//	Point structure for 2D coordinate
// -----------------------------------------------------
typedef struct _point_t
{
    int16 x;
    int16 y;
} point_t;

typedef struct {
	int16 level;
	uint16 run;
} RunLevelPair;

#define MAX_WIDTH               352
#define MAX_HEIGHT              288
#define BUF_ALIGN               16
#define FRAME_Y_START_ALIGN     16
#define FRAME_C_START_ALIGN     16
#define FRAME_Y_STRIDE_ALIGN    16
#define FRAME_C_STRIDE_ALIGN    16
#define MV_ALIGN                32
#define BLOCKSIZE		16
#define PIXELINBLOCK    64   // 8*8
#define MACROBLOCKSIZE  384  // 8*8*6


#define MAX_BLOCKNUMX       (MAX_WIDTH/16)
#define MAX_BLOCKNUMY       (MAX_HEIGHT/16)
#define MAX_PIXELS          (MAX_WIDTH*MAX_HEIGHT)
#define MAX_FRMSIZE         (MAX_WIDTH*MAX_HEIGHT*3/2)
#define MAX_BLKSIZE         (MAX_WIDTH*MAX_HEIGHT/256)
#define ALLOCATED_BUF       (2*MAX_FRMSIZE + sizeof(point_t)*MAX_BLKSIZE + sizeof(int16)*384 + 64)

#endif
