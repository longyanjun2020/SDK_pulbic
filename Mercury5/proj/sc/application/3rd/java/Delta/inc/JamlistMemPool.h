#ifndef _JAM_LIST_MALLOC_H
#define _JAM_LIST_MALLOC_H

#include "java_head.h"

/**************************************************************************
 * Constant Definition
 **************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
 
/**************************************************************************
 * Declaration
 **************************************************************************/

#define JAM_LIST_MALLOC_TRACE	1 // Note: Turn-off when production

int initializeJamlistMemoryPool(void);
int finalizeJamlistMemoryPool(void);

/* Private implementations for memory allocation */
void* jamlistMallocImpl(int, char*, int);
void  jamlistFreeImpl(void*, char*, int);

#ifdef JAM_LIST_MALLOC_TRACE
extern int tracenativememory;
  #define jamlistMalloc(x)     jamlistMallocImpl((x), __FILE__, __LINE__)
  #define jamlistFree(x)       jamlistFreeImpl((x), __FILE__, __LINE__)
#else
  #define jamlistMalloc(x)     jamlistMallocImpl((x), (char*)NULL, 0)
  #define jamlistFree(x)       jamlistFreeImpl((x), (char*)NULL, 0)		
#endif /* JAM_LIST_MALLOC_TRACE */	


#ifdef __cplusplus
}
#endif

#endif /* _JAM_LIST_MALLOC_H */


