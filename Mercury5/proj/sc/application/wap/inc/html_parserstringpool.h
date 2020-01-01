
#ifndef __HTML_PARSERSTRINGPOOL_H__
#define __HTML_PARSERSTRINGPOOL_H__

#include <ncc_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * implement include as less methods as possible
 */
#define MINI_STRING_POOL     1

typedef struct __string_block {
    struct __string_block *next;
    int32_t size;
    uint8_t s[4];
} STRING_BLOCK;

typedef struct __string_pool {
    STRING_BLOCK *blocks;
    STRING_BLOCK *freeBlocks;
    const uint8_t *end;
    uint8_t *ptr;
    uint8_t *start;
    T_Html_Parser_Memory_Handling_Suite mem;
} STRING_POOL;

typedef struct __pool_node {
    uint16_t mask;
    uint16_t size;
    void   *buffer;
} POOL_NODE;

#define poolStart(pool) ((pool)->start)
#define poolEnd(pool) ((pool)->ptr)
#define poolLength(pool) ((pool)->ptr - (pool)->start)
#define poolChop(pool) ((void)--(pool->ptr))
#define poolLastChar(pool) (((pool)->ptr)[-1])
#define poolDiscard(pool) ((pool)->ptr = (pool)->start)
#define poolFinish(pool) ((pool)->start = (pool)->ptr)
#define poolAppendChar(pool, c) \
    (((pool)->ptr == (pool)->end && !poolGrow(pool)) \
    ? 0 \
: ((*((pool)->ptr)++ = c), 1))

#define poolEndString(pool)                                  \
    (((pool)->ptr == (pool)->end && !poolGrowByLen(pool, 1)) \
    ? 0 : ((*((pool)->ptr)++ = '\0'), 1))

void
poolInit(STRING_POOL *pool, const T_Html_Parser_Memory_Handling_Suite *ms);

void
poolClear(STRING_POOL *pool);

void
poolDestroy(STRING_POOL *pool);

uint8_t *
poolAppendStringN(STRING_POOL *pool, const uint8_t *ptr, int32_t len);

uint8_t *
poolAppendByLen(STRING_POOL *pool, const uint8_t *ptr, int32_t len);

uint8_t *
poolAppend(STRING_POOL *pool, const int8_t *ptr, const int8_t *end);

const uint8_t *
poolCopyString(STRING_POOL *pool, const uint8_t *s);

const uint8_t *
poolCopyStringN(STRING_POOL *pool, const uint8_t *s, int32_t n);

const uint8_t *
poolAppendString(STRING_POOL *pool, const uint8_t *s);

uint8_t *
poolStoreString(STRING_POOL *pool, const int8_t *ptr, const int8_t *end);

int32_t
poolGrowByLen(STRING_POOL *pool, int32_t growLen);

void *
poolMalloc(STRING_POOL *pool, uint16_t size, uint16_t align);

void *
poolRealloc(STRING_POOL *pool, void *ptr, uint16_t size, uint16_t align);

#ifdef __cplusplus
}
#endif

#endif /*__HTML_PARSERSTRINGPOOL_H__*/
