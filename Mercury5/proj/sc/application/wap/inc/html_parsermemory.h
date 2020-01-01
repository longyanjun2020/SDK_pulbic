
#ifndef __HTML_PARSERMEMORY_H__
#define __HTML_PARSERMEMORY_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/** malloc function declaration used by parser */
typedef void*(*htmlParserMalloc)(uint32_t size);

/** free function declaration used by parser */
typedef void(*htmlParserFree)(void *ptr);

/** realloc function declaration used by parser */
typedef void*(*htmlParserRealloc)(void *ptr, uint32_t size);

/** memory manage handler suite structure, include malloc, free, realloc */
typedef struct {
  htmlParserMalloc  malloc_fcn;  /**<malloc function pointer*/
  htmlParserFree    free_fcn;     /**<free function pointer*/
  htmlParserRealloc realloc_fcn; /**<realloc function pointer*/
} T_Html_Parser_Memory_Handling_Suite;

typedef struct __common_freelist_node {
    struct __common_freelist_node *next;
} T_Common_Freelist_Node;

typedef struct __fixedSizeUnitsBlock {
    struct __fixedSizeUnitsBlock *next;
    uint8_t *unitsArray;
} T_Common_FixedSizeUnitsBlock;

typedef struct __fixedSizeUnitsPool {
    T_Common_FixedSizeUnitsBlock *blocks;
    T_Common_Freelist_Node *freelist;
    uint8_t *ptr;
    uint8_t *end;
    uint16_t firstNr;
    uint16_t secondNr;
    uint32_t unitSize;
    T_Html_Parser_Memory_Handling_Suite mem;
} T_Common_FixedSizeUnitsPool;

void
fixedSizeUnitPoolInit( T_Common_FixedSizeUnitsPool *pool,
                       uint32_t unitSize,
                       uint16_t firstNr,
                       uint16_t secondNr,
                       const T_Html_Parser_Memory_Handling_Suite *ms );

void *
getFixedSizeUnit(T_Common_FixedSizeUnitsPool *pool);

void
freeFixedSizeUnit(T_Common_FixedSizeUnitsPool *pool, void *ptr);

void
destroyFixedSizeUnitPool(T_Common_FixedSizeUnitsPool *pool);

#ifdef __cplusplus
}
#endif

#endif /* __HTML_PARSERMEMORY_H__ */
