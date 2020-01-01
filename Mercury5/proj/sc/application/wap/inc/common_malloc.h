/*
 * Copyright 2005-2006 NCC Inc. All Rights Reserved.
 * $Id: //depot/dev/base/inc/uapps/common/common_malloc.h#3 $
 */

#ifndef __COMMON_MALLOC_H__
#define __COMMON_MALLOC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <ncc_types.h>

#define MAX_MEM_CONTEXT 10

/** Status codes for heap_extend */
typedef int32_t Boolean;
#define boolean Boolean

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

void common_clean();

/**
 * Init user defining dynamic memory pool.
 * \param startAddress  start address of the block of momery.
 * \param size          size of the block of momery.
 * \param pageSize      align size,'4' is normal.
 * \return              Return the handle of dynamic memory pool if success.otherwise return NULL.
 */
void * common_memCreate(void * startAddress
                           ,uint32_t size
                           ,uint32_t pageSize
                           );

/**
 * Unload user defining dynamic memory pool.
 * \param ctxt          handle of dynamic memory pool.
 * \return              Return TRUE if success;otherwise return FALSE.
 */
int32_t common_memDestroy(void * ctxt);

/**
 * Malloc a memory buffer.
 * \param ctxt          handle of dynamic memory pool.
 * \param nbytes        size of memory buffer to malloc.
 * \return              Return a pointer to memory buffer if success;otherwise return NULL.
 */
void * common_memMalloc(void * ctxt, int32_t nbytes);

/**
 * Free a memory buffer.
 * \param ctxt          handle of dynamic memory pool.
 * \param aptr          pointer to memory buffer.
 * \return              Return size of the block,if return size is 0,fail;otherwise success.
 */
int32_t common_memFree(void * ctxt, void * aptr);

/**
 * Malloc a memory buffer (calloc).
 * \param ctxt          handle of dynamic memory pool.
 * \param num           number of unit.
 * \param size          size of each unit.
 * \return              Return a pointer to memory buffer if success;otherwise return NULL.
 */
void * common_memCalloc(void * ctxt, int32_t num, int32_t size);

/**
 * Get free size.
 * \param ctxt          handle of dynamic memory pool.
 * \return              free size of dynamic memory pool.
 */
uint32_t common_memFreeSize(void * ctxt);

/**
 * Constants used in the size/used field of each heap block to
 * indicate when a block is FREE or in use.
 */

#define CPU_ALIGNMENT      4
#define CPU_HEAP_ALIGNMENT CPU_ALIGNMENT

#define HEAP_BLOCK_USED    1           /**< indicates block is in use */
#define HEAP_BLOCK_FREE    0           /**< indicates block is FREE */

/** The size/used field value for the dummy front and back flags */
#define HEAP_DUMMY_FLAG    (0 + HEAP_BLOCK_USED)

/**
 * The following constants reflect various requirements of the
 * heap data structures which impact the management of a heap.
 *
 * NOTE: Because FREE block overhead is greater than used block
 *       overhead AND a portion of the allocated space is from
 *       the extra FREE block overhead, the absolute lower bound
 *       of the minimum fragment size is equal to the size of
 *       the FREE block overhead.
 */

/** size dummy first and last blocks */
#define HEAP_OVERHEAD   (sizeof( uint32_t ) * 2)

/** num bytes overhead in used block */
#define HEAP_BLOCK_USED_OVERHEAD   (sizeof( void * ) * 2)

/**
 * min number of bytes the user may
 * specify for the heap size
 */
#define HEAP_MINIMUM_SIZE   (HEAP_OVERHEAD + sizeof (Heap_Block))

/**
 * The following defines the data structure used to manage
 * individual blocks in a heap.   When the block is allocated, the
 * next and previous fields are not used by the Heap Handler
 * and thus the address returned for the block starts at
 * the address of the next field.
 *
 * NOTE: The next and previous pointers are only valid when the
 *       block is FREE.  Caution must be exercised to insure that
 *       allocated blocks are large enough to contain them and
 *       that they are not accidentally overwritten when the
 *       block is actually allocated.
 */
typedef struct Heap_Block_struct Heap_Block;

struct Heap_Block_struct {
    uint32_t  back_flag;     /**< size and status of prev block */
    uint32_t  front_flag;    /**< size and status of block */
    Heap_Block * next;       /**< pointer to next block */
    Heap_Block * previous;   /**< pointer to previous block */
};

/**
 * The following defines the control block used to manage each heap.
 *
 * NOTE: This structure is layed out such that it can be used a a dummy
 *       first and last block on the FREE block chain.  The extra padding
 *       insures the dummy last block is the correct size.
 *
 * The first Heap_Block starts at first while the second starts at
 * final.  This is effectively the same trick as is used in the Chain
 * Handler.
 */
typedef struct {
    Heap_Block * start;           /**< first valid block address in heap */
    Heap_Block * final;           /**< last valid block address in heap */

    Heap_Block * first;           /**< pointer to first block in heap */
    Heap_Block * permanent_null;  /**< always NULL pointer */
    Heap_Block * last;            /**< pointer to last block in heap */
    uint32_t page_size;           /**< allocation unit */
    uint32_t reserved;
}   Heap_Control;

typedef struct _MemContext
{
    int32_t _crtl_init_flag;
    int32_t  _crtl_mem_lock;
    uint32_t  _crtl_freesize;
    int32_t Heap_Size;
    void * Heap_Head;
    Heap_Control _crtl_heap_control;
}MemContext;

/**
 * _Crtl_Heap_Initialize
 *
 * DESCRIPTION: This routine initializes the_heap record to manage the
 *              contiguous heap of size bytes which starts at starting_address.
 *              Blocks of memory are allocated from the heap in multiples of
 *              page_size byte units.
 */
uint32_t _Crtl_Heap_Initialize(MemContext * myMemContext,
                               Heap_Control * the_heap,
                               void * starting_address,
                               uint32_t size,
                               uint32_t page_size
                              );

/**
 * _Crtl_Heap_Allocate
 *
 * DESCRIPTION: This function attempts to allocate a block of size bytes from
 *              the_heap. If insufficient memory is FREE in the_heap to allocate
 *              a block of the requested size, then NULL is returned.
 */
void * _Crtl_Heap_Allocate(MemContext * myMemContext,
                           Heap_Control * the_heap,
                           uint32_t size
                          );

/**
 * _Crtl_Heap_Free
 *
 * DESCRIPTION: This routine returns the block of memory which begins
 *              at starting_address to the_heap.  Any coalescing which is
 *              possible with the freeing of this routine is performed.
 */
boolean _Crtl_Heap_Free(MemContext * myMemContext,
                        Heap_Control * the_heap,
                        void * start_address
                       );

/**
 * _Addresses_Add_offset
 *
 * DESCRIPTION: This function is used to add an offset to a base address.
 *              It returns the resulting address.  This address is typically
 *              converted to an access type before being used further.
 */
void * _Addresses_Add_offset(void * base,
                             uint32_t offset
                            );

/**
 * _Addresses_Subtract_offset
 *
 * DESCRIPTION: This function is used to subtract an offset from a base
 *              address.  It returns the resulting address.  This address is
 *              typically converted to an access type before being used further.
 */
void * _Addresses_Subtract_offset(void * base,
                                  uint32_t offset
                                 );

/**
 * _Addresses_Subtract
 *
 * DESCRIPTION: This function is used to subtract two addresses.  It returns the
 *              resulting offset.
 *
 * NOTE: The cast of an address to an uint32_t makes this code
 *       dependent on an addresses being thirty two bits.
 */
uint32_t _Addresses_Subtract(void * left,
                             void * right
                            );

/**
 * _Addresses_Is_aligned
 *
 * DESCRIPTION: This function returns TRUE if the given address is correctly
 *              aligned for this processor and FALSE otherwise.  Proper alignment
 *              is based on correctness and efficiency.
 */
boolean _Addresses_Is_aligned(void * address);

/**
 * _Addresses_Is_in_range
 *
 * DESCRIPTION: This function returns TRUE if the given address is within the
 *              memory range specified and FALSE otherwise.  base is the address
 *              of the first byte in the memory range and limit is the address
 *              of the last byte in the memory range.  The base address is
 *              assumed to be lower than the limit address.
 */
boolean _Addresses_Is_in_range(void * address,
                               void * base,
                               void *limit
                              );

/**
 * _Heap_Head
 *
 * DESCRIPTION: This function returns the head of the specified heap.
 */
Heap_Block * _Heap_Head(Heap_Control * the_heap);

/**
 * _Heap_Tail
 *
 * DESCRIPTION: This function returns the tail of the specified heap.
 */
Heap_Block * _Heap_Tail(Heap_Control * the_heap);

/**
 * _Heap_Previous_block
 *
 * DESCRIPTION: This function returns the address of the block which physically
 *              precedes the_block in memory.
 */
Heap_Block * _Heap_Previous_block(Heap_Block * the_block);

/**
 * _Heap_Next_block
 *
 * DESCRIPTION: This function returns the address of the block which physically
 *              follows the_block in memory.
 *
 * NOTE: Next_block assumes that the block is FREE.
 */
Heap_Block * _Heap_Next_block(Heap_Block * the_block);

/**
 * _Heap_Block_at
 *
 * DESCRIPTION: This function calculates and returns a block's location (address)
 *              in the heap based upon a base address and an offset.
 */
Heap_Block * _Heap_Block_at(void * base,
                            uint32_t offset
                           );

/** _Heap_User_block_at */
Heap_Block * _Heap_User_block_at(void * base);

/**
 * _Heap_Is_previous_block_free
 *
 * DESCRIPTION: This function returns TRUE if the previous block of the_block
 *              is FREE, and FALSE otherwise.
 */
boolean _Heap_Is_previous_block_free(Heap_Block * the_block);

/**
 * _Heap_Is_block_free
 *
 * DESCRIPTION: This function returns TRUE if the block is FREE, and FALSE otherwise.
 */
boolean _Heap_Is_block_free(Heap_Block * the_block);

/**
 * _Heap_Is_block_used
 *
 * DESCRIPTION: This function returns TRUE if the block is currently allocated,
 *              and FALSE otherwise.
 */
boolean _Heap_Is_block_used(Heap_Block * the_block);

/**
 * _Heap_Block_size
 *
 * DESCRIPTION: This function returns the size of the_block in bytes.
 */
uint32_t _Heap_Block_size(Heap_Block * the_block);

/**
 * _Heap_Start_of_user_area
 *
 * DESCRIPTION: This function returns the starting address of the portion of the block
 *              which the user may access.
 */
void * _Heap_Start_of_user_area(Heap_Block * the_block);

/**
 * _Heap_Is_block_in
 *
 * DESCRIPTION: This function returns TRUE if the_block is within the memory area
 *              managed by the_heap, and FALSE otherwise.
 */
boolean _Heap_Is_block_in(Heap_Control * the_heap,
                          Heap_Block * the_block
                         );

/**
 * _Heap_Is_page_size_valid
 *
 * DESCRIPTION: This function validates a specified heap page size.  If the page size
 *              is 0 or if lies outside a page size alignment boundary it is invalid
 *              and FALSE is returned.  Otherwise, the page size is valid and TRUE is
 *              returned.
 */
boolean _Heap_Is_page_size_valid(uint32_t page_size);

/**
 * _Heap_Build_flag
 *
 * DESCRIPTION: This function returns the block flag composed of size and in_use_flag.
 *              The flag returned is suitable for use as a back or front flag in a
 *              heap block.
 */
uint32_t _Heap_Build_flag(uint32_t size,
                          uint32_t in_use_flag
                         );

#undef boolean

#ifdef __cplusplus
}
#endif

#endif /* __COMMON_MALLOC_H__ */
