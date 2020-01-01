#ifndef HEAAC_COMMON_TYPES_H
#define HEAAC_COMMON_TYPES_H

#include <stdint.h>

#if defined(_MSC_VER)
#include <windows.h> //BOOL
#else
typedef	int8_t             BOOL;
#endif


#if defined(_MSC_VER)
typedef	int8_t             S8;
typedef	uint8_t            U8;
typedef	int16_t            S16;
typedef	uint16_t           U16;
typedef	int32_t            S32;
typedef	uint32_t           U32;
#else

typedef signed char S8;
typedef unsigned char U8;
typedef short S16;
typedef unsigned short U16;
typedef int S32;
typedef unsigned int U32;

#endif
#endif
