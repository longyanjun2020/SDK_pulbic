#ifndef __MIDI_DELTA_PORTING_DEFINE_H_
#define __MIDI_DELTA_PORTING_DEFINE_H_


#ifdef FLAG_MIDI_LIB_DATA_TYPE

/* definition in non-G1 platform */

typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#ifdef __GNUC__
 typedef unsigned long long uint64_t;
 typedef long long int64_t;
#if 1
 #define INLINE inline
 #define GINLINE inline
#else
 #define INLINE
 #define GINLINE
#endif
#elif MSVC
 typedef __int64 int64_t;
 typedef unsigned __int64 uint64_t;
 #define INLINE __inline
 #define GINLINE
 #define PSS_STYLE 2
#else
 typedef unsigned long long uint64_t;
 typedef long long int64_t;
 #define INLINE	inline
 #define GINLINE	inline
 #define PSS "PSS"
#endif

// for string.h and mem.h
#include <string.h>
#define MIDI_strcpy strcpy
#define MIDI_strcmp strcmp
#define MIDI_strlen strlen
#define MIDI_memcmp memcmp
#define MIDI_memcpy memcpy
#define MIDI_memset memset
#define MIDI_memmove memmove

// for memory
#define MIDI_malloc malloc
#define MIDI_calloc calloc
#define MIDI_realloc realloc
#define MIDI_free   free

#else

// include original
#include "vm_types.ht"

typedef s8  int8_t;
typedef s16 int16_t;
typedef s32   int32_t;
typedef s64   int64_t;

typedef u8 uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;


// for string.h and mem.h
#ifdef __USE_VM_MEMMGT__
#include "vm_stdio.ho"
#define MIDI_strcpy vm_strcpy
#define MIDI_strcmp vm_strcmp
#define MIDI_strlen vm_strlen
#define MIDI_memcmp vm_memcmp
#define MIDI_memcpy vm_memcpy
#define MIDI_memset vm_memset
#define MIDI_memmove vm_memmove
#else
#include <string.h>
#define MIDI_strcpy strcpy
#define MIDI_strcmp strcmp
#define MIDI_strlen strlen
#define MIDI_memcmp memcmp
#define MIDI_memcpy memcpy
#define MIDI_memset memset
#define MIDI_memmove memmove
#endif


 #define INLINE
 #define GINLINE
 #define PSS "PSS"

#endif


void *mem_malloc(int32_t size);
void mem_free(void *ptr);

#endif
