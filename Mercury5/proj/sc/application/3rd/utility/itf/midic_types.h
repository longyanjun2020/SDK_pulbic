#ifndef __MIDIC_DELTA_PORTING_DEFINE_H_
#define __MIDIC_DELTA_PORTING_DEFINE_H_

// include original
#include "stdint.h"


// for string.h and mem.h
#include "vm_stdio.ho"
#define MIDIC_strcpy vm_strcpy
#define MIDIC_strcmp vm_strcmp
#define MIDIC_strlen vm_strlen
#define MIDIC_memcmp vm_memcmp
#define MIDIC_memcpy vm_memcpy
#define MIDIC_memset vm_memset
#define MIDIC_memmove vm_memmove

// for memory
#define MIDIC_malloc MsAllocateMem
#define MIDIC_free   MsReleaseMemory 

#define MIDIC_TRACE_LEVEL _MSERV19

#endif
