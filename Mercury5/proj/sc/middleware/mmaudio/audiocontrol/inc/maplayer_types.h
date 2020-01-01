#ifndef _PLAYER_TYPES_H
#define _PLAYER_TYPES_H
#if 0
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
//#include "mmp_common_types.h"


#define false                   0
#define true                    1



#define PLAYER_ASSERT           assert
#define MP_DBG_MSG              //printf

typedef	signed char             _int8_t;
typedef	short int               _int16_t;
typedef	int                     _int32_t;
typedef int64_t                 _int64_t;
typedef unsigned char           byte;


#include "vm_types.ht"

#ifndef TYPE_DEFINITION
#define TYPE_DEFINITION

#if defined(_MSC_VER) //VC compiler
typedef unsigned int            Bool;
typedef unsigned char           uchar;
typedef __int8                  int8;
typedef unsigned __int8         uint8;
typedef __int16                 int16;
typedef unsigned __int16        uint16;
typedef __int32                 int32;
typedef	unsigned int            uint32;
typedef __int64                 int64;
typedef unsigned __int64        uint64;
typedef	unsigned char           u_int8_t;
typedef	unsigned short int      u_int16_t;
typedef	unsigned int            u_int32_t;
typedef uint64_t                u_int64_t;
typedef uint32                  ssize_t;
#elif defined(LINUX)
typedef uint32_t                Bool;
typedef uint8_t                 uchar;
typedef int8_t                  int8;
typedef uint8_t                 uint8;
typedef int16_t                 int16;
typedef uint16_t                uint16;
typedef int32_t                 int32;
typedef	uint32_t                uint32;
typedef int64_t                 int64;
typedef uint64_t                uint64;
typedef	uint32_t                u_int32_t;
typedef uint64_t                u_int64_t;
#endif

#endif

#if 0
typedef int64                   cyg_tick_count_t;
typedef void*                   MP4FileHandle;
typedef u_int32_t               MP4TrackId;
typedef u_int32_t               MP4SampleId;
typedef u_int64_t               MP4Timestamp;
#endif
#include "ms_io.h"
#endif
#endif
