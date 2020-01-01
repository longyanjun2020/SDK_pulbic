#ifndef __DUAL_MEM_POOL_H__
#define __DUAL_MEM_POOL_H__

#include "java_head.h"
#include "nemomp.h"

/**************************************************************************
 * Constant Definition
 **************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
 
/**************************************************************************
 * Declaration
 **************************************************************************/

#define MEM_POOL_TRACE 0

int initializeFirstMemoryPool(long*, int);
int finalizeFirstMemoryPool(void);

int initializeSecondMemoryPool(long*, int);
int finalizeSecondMemoryPool(void);

/* Private implementations for memory allocation */
void* dmpMallocImpl(int, char*, int);
void* dmpCallocImpl(int, int, char*, int);
void  dmpFreeImpl(void*, char*, int);

#ifdef MEM_POOL_TRACE
  extern int tracenativememory;
  #define dmpMalloc(x)     dmpMallocImpl((x), __FILE__, __LINE__)
  #define dmpCalloc(x, y)  dmpCallocImpl((x), (y), __FILE__, __LINE__)
#ifdef __JAVA_JTWI__  
  #define dmpStrdup(x)     dmpStrdupImpl((x), __FILE__, __LINE__)  // 20090218: Addded
#endif
  #define dmpFree(x)       dmpFreeImpl((x), __FILE__, __LINE__)
#else
#define dmpMalloc(x)     dmpMallocImpl((x), (char*)NULL, 0)
#define dmpCalloc(x, y)  dmpCallocImpl((x), (y), (char*)NULL, 0)
#ifdef __JAVA_JTWI__  
  #define dmpStrdup(x)     dmpStrdupImpl((x), (char*)NULL, 0)  // 20090218: Addded
#endif  
#define dmpFree(x)       dmpFreeImpl((x), (char*)NULL, 0)		
#endif /* MEM_POOL_TRACE */	

#ifdef __cplusplus
}
#endif

#endif /* __DUAL_MEM_POOL_H__ */


