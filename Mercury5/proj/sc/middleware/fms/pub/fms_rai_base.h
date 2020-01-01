#if	!defined(__NAND__)

/****************************************************************************/
/*  $Workfile::   fms_rai_base.h                                          $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*                                                                          */
/*  Contents: FLASH random access items base internal definitions           */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.2  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   26 Mar 2003 10:23:32 $     */
/****************************************************************************
 *   $Log:   G:/projet/flash/pvcsarch/archives/FMS/inc/fms_rai_base.h-arc  $
 *
 *   Rev 0.2   26 Mar 2003 10:23:32   kod
 *Second release.
 *Works with DwlWin.
 *
 *   Rev 0.1   25 Feb 2003 11:44:34   kod
 *Initial release for integration
 ****************************************************************************/


/*****************************************************************************
 File     : fms_rai_base.h
 Contents : FLASH random access items base internal definitions
 Author   : Pierre Berger, Theoris
 Date     : Nov 8 2002
 ******************************************************************************/


#ifndef _2d83dd2b5f5e3c2219df1dbafe7dd333_INCLUDED_FMS_RAI_BASE_H
#define _2d83dd2b5f5e3c2219df1dbafe7dd333_INCLUDED_FMS_RAI_BASE_H

/* ==========================================================================
   TEMPORARY
   ========================================================================== */
//#include <stdio.h>

/* ==========================================================================
   Compile option
  ========================================================================== */
#define __FMS_ENLARGE_RAI_SIZE__

/* ==========================================================================
   Macros
   ========================================================================== */
// protected code sections
#define LOCK()          FMS_LOCK(OBJ_SEM)
#define LOCK_TEST()     FMS_LTEST(OBJ_SEM)
#define LOCK_DELAY(MS)  FMS_LDELAY(OBJ_SEM,MS)
#define UNLOCK()        FMS_UNLOCK(OBJ_SEM)

/* ==========================================================================
   Constants
   ========================================================================== */
// flash offset
#define FRAI_SECTOR_MAX 32 // max. nr of addressable sectors

/*
 *   Taking advantage of 4 bytes alignment, ve can use only 14 bits instead of
 * 16 to address a 64K sector.
 *   Limiting the number of sectors to 32 allows to handle 2Mb of 64K sectors
 * FLASH.
 *   This gives a pointer size of 19 bits, for a total address space of 2^21
 * bytes.
 *   Of course the 2Mb address space is the limiting factor : for instance, we
 * will not be able to handle more than 8 256K sectors.
 */

#ifdef __FMS_ENLARGE_RAI_SIZE__
#define FRAI_ADDR_BITS 31 // number of bits to code an internal hash table pointer
#define FRAI_ADDR_PADDING_BITS (32-FRAI_ADDR_BITS)
#else
#define FRAI_ADDR_BITS 19 // number of bits to code an internal hash table pointer
#endif
typedef u32 frai_offset_t; // actually limited to FRAI_ADDR_BITS

// the NULL value is chosen as the highest FLASH offset
/*
 * FRAI_NULL cannot point to a valid object since the size of the pointed object
 * would be 4 and the minimal size of an object is 8
 */
#define FRAI_NULL ((frai_offset_t)((1UL<<FRAI_ADDR_BITS)-1))

// value of hardware flash bits
#define FRAI_FALSE ((int) 0)
#define FRAI_TRUE  ((int)-1)

/*
 * Values defining the safety of the contents of an item data structure.
 * The idea is to write the header first, then the data, and have the system
 * recognize which parts have been properly written even in case of a power
 * failure during the write operation.
 *   These values are then conditioned by the STRATA FLASH write mechanism :
 * increasing state number must correspond to an increasing programmation state
 * here the following transition order shall be enforced :
 * NONE -> HEAD -> DATA
 *  Since the programmation energy levels go down from 11 to 00, we use
 * 11 for NONE and 00 for DATA, the two other possible values meaning HEAD.
 *
 *  Same principle goes for garbage collection status
 *  ORPHAN -> ACTIVE -> TRASH
 */
#define FRAI_WRITE_NONE 3 // nothing has been safely written
#define FRAI_WRITE_HEAD 2 // item header has been safely written
/////// FRAI_WRITE_HEAD 1
#define FRAI_WRITE_DATA 0 // item header and data have been safely written

#define FRAI_STATE_ORPHAN 3 // the item has not been completely activated
#define FRAI_STATE_ACTIVE 2 // the item is valid and active
/////// FRAI_STATE_ACTIVE 1
#define FRAI_STATE_DELETE 0 // the item is available for garbage collection

#define FRAI_COPY 3 // copy of an item being moved out of a reclaimed sector
#define FRAI_UNIQ 0 // unique instance of an item

/* ==========================================================================
   Types
   ========================================================================== */
/*
 * IMPORTANT NOTE
 * ==============
 *   In order to be able to get rid of partially initialized blocks, the size
 * of an item has been defined as the data size (header size not counted).
 *   Thus it is always possible to overwrite the size to zero, turning an
 * incompletely written item into a single deleted header containing no data.
 *   This makes sure that, during the power-up scan of the FLASH, we can
 * invalidate any data block that could not be written due to power failure
 * during the last software activation.
 */

// common flash items header
typedef struct {
    unsigned int chk_state : 2; // not yet confirmed active, active, or available for garbage collection
    unsigned int chk_write : 2; // tells which parts of the item have been safely written
    unsigned int chk_copy  : 2; // temporarily set during garbage collection
    unsigned int signature :10; // to enease consistency check
    unsigned int size      :16; // item total size (max. 16 Kb)
    } frai_header_t;

// additional signature inside item header for consistency check
#define FRAI_ITEM_SIGNATURE(item) (FRAI_OFS(item) & 0x3F)

// object data contents
typedef struct {
    fms_rai_id_t    id;      // unique identifier
    u8           data[1]; // variable amount of data
    } frai_data_t;

// global FLASH object item
typedef struct frai_item_s {
    frai_header_t h; // header
    frai_data_t   b; // object data
    } frai_item_t;

// item WORD size computation
#define FRAI_W_SIZEOF(item) ((sizeof (((frai_item_t*)(item))->h) + ((frai_item_t*)(item))->h.size + 3)>>2)

// compute the size of a FLASH data block
#define FLASH_DATA_TO_ITEM_SIZE(size) ((fms_rai_size_t)((size) + offsetof (frai_item_t, b.data[0]) - sizeof (frai_header_t)))
#define FLASH_ITEM_TO_DATA_SIZE(size) ((fms_rai_size_t)((size) - offsetof (frai_item_t, b.data[0]) + sizeof (frai_header_t)))

/* ==========================================================================
   Module procedures
   ========================================================================== */

/* --------------------------------------------------------------------------
   Items handling layer initialization
   To be called once during system boot, before any random access item access attempt
   If it does not return TRUE, the random access item storage is deep in trouble
   -------------------------------------------------------------------------- */
int frai_items_init (void * base); // FLASH range base address

/* --------------------------------------------------------------------------
   Get an object identifier from a FLASH offset
   -------------------------------------------------------------------------- */
fms_rai_id_t frai_index_id (frai_offset_t offset); // FLASH offset pointing to a data item

/* --------------------------------------------------------------------------
   Duplicates items in a reclaimed sector in the first step of the garbage
   collection.
   -------------------------------------------------------------------------- */

void frai_gc_duplicate (frai_item_t * item,frai_item_t * addr); // direct pointer to a FLASH item

/* --------------------------------------------------------------------------
   Replaces items in a reclaimed sector with their copies in the second step
   of the garbage collection.
   -------------------------------------------------------------------------- */

void frai_gc_replace (frai_item_t * item, u32 addr); // copy of the displaced item

/* --------------------------------------------------------------------------
   Analyze and correct the state of an item during initial flash scan
   The pointer is passed as a void* to be nice with the scanning pointers
   -------------------------------------------------------------------------- */
typedef enum {
    FRAI_STATUS_ACTIVE,   // valid and active item
    FRAI_STATUS_DELETED,  // deleted item
    FRAI_STATUS_COPY,     // item copy for garbage collection
    FRAI_STATUS_ORPHAN,   // new version of an item not yet validated
    FRAI_STATUS_FREE      // blank area
    } frai_item_status_t;

frai_item_status_t frai_scan_item (void * scan, u32 addr);

/* --------------------------------------------------------------------------
   Invalidate an item
   Only used for fixing corrupted sectors during initial scan
   The pointer is passed as a void* to be nice with the scanning pointers
   -------------------------------------------------------------------------- */
void frai_scan_invalidate (void *   item,  // item to invalidate
                           unsigned size); // new item total size

s32 fms_rai_gc_write(frai_item_t *copy, frai_item_t * item, frai_item_t * addr);

frai_item_t * fms_object_read(void * base_addr);

void fms_get_item(void * base_addr, frai_item_t **item);

frai_item_t *fms_Ptr2Offset(frai_item_t * offset);

void fms_m18_release(void* obj);

frai_item_t * fms_object_read(void * base_addr);


/* --------------------------------------------------------------------------
   Anticipated recycling of dirty sectors

     This procedure should typically be called from a low-priority task.
     It will erase and reformat one sector at a time (and do nothing if no
   dirty sectors are present).
     Calling this procedure is in no way mandatory ; however, it will
   anticipate the cleanup of sectors, and thus possibly speed up the other
   operations of this module.
   -------------------------------------------------------------------------- */
void frai_recycle (void);

#ifdef FMS_DEBUG
/* --------------------------------------------------------------------------
   print an item
   -------------------------------------------------------------------------- */
void DEBUG_item (frai_item_t * item); // item to be dumped
#else
#define DEBUG_item(x)
#endif // FMS_DEBUG

#endif /* ! _2d83dd2b5f5e3c2219df1dbafe7dd333_INCLUDED_FMS_RAI_BASE_H */

#else	/*	defined(__NAND__)	*/

/****************************************************************************/
/*  $Workfile::   fms_rai_base.h                                          $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*                                                                          */
/*  Contents: FLASH random access items base internal definitions           */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.2  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   26 Mar 2003 10:23:32 $     */
/****************************************************************************
 *   $Log:   G:/projet/flash/pvcsarch/archives/FMS/inc/fms_rai_base.h-arc  $
 *
 *   Rev 0.2   26 Mar 2003 10:23:32   kod
 *Second release.
 *Works with DwlWin.
 *
 *   Rev 0.1   25 Feb 2003 11:44:34   kod
 *Initial release for integration
 ****************************************************************************/


/*****************************************************************************
 File     : fms_rai_base.h
 Contents : FLASH random access items base internal definitions
 Author   : Pierre Berger, Theoris
 Date     : Nov 8 2002
 ******************************************************************************/


#ifndef _2d83dd2b5f5e3c2219df1dbafe7dd333_INCLUDED_FMS_RAI_BASE_H
#define _2d83dd2b5f5e3c2219df1dbafe7dd333_INCLUDED_FMS_RAI_BASE_H

/* ==========================================================================
   TEMPORARY
   ========================================================================== */
#include "fms_rai.h"


/* ==========================================================================
   Compile option
  ========================================================================== */
#define __FMS_ENLARGE_RAI_SIZE__


/* ==========================================================================
   Macros
   ========================================================================== */
// protected code sections
#define LOCK()      FMS_LOCK(OBJ_SEM)
#define LOCK_TEST() FMS_LTEST(OBJ_SEM)
#define UNLOCK()    FMS_UNLOCK(OBJ_SEM)





/* ==========================================================================
   Constants
   ========================================================================== */
// flash offset
#define FRAI_SECTOR_MAX 32 // max. nr of addressable sectors

/*
 *   Taking advantage of 4 bytes alignment, ve can use only 14 bits instead of
 * 16 to address a 64K sector.
 *   Limiting the number of sectors to 32 allows to handle 2Mb of 64K sectors
 * FLASH.
 *   This gives a pointer size of 19 bits, for a total address space of 2^21
 * bytes.
 *   Of course the 2Mb address space is the limiting factor : for instance, we
 * will not be able to handle more than 8 256K sectors.
 */
#if defined(__FMS_ENLARGE_RAI_SIZE__)
#define FRAI_ADDR_BITS          (31) // number of bits to code an internal hash table pointer
#define FRAI_ADDR_PADDING_BITS  (32 - FRAI_ADDR_BITS)
#else
#define FRAI_ADDR_BITS          (24) // number of bits to code an internal hash table pointer
#endif

typedef u32 frai_offset_t; // actually limited to FRAI_ADDR_BITS

// the NULL value is chosen as the highest FLASH offset
/*
 * FRAI_NULL cannot point to a valid object since the size of the pointed object
 * would be 4 and the minimal size of an object is 8
 */
#define FRAI_NULL ((frai_offset_t)((1UL<<FRAI_ADDR_BITS)-1))

// value of hardware flash bits
#define FRAI_FALSE ((int) 0)
#define FRAI_TRUE  ((int)-1)

/*
 * Values defining the safety of the contents of an item data structure.
 * The idea is to write the header first, then the data, and have the system
 * recognize which parts have been properly written even in case of a power
 * failure during the write operation.
 *   These values are then conditioned by the STRATA FLASH write mechanism :
 * increasing state number must correspond to an increasing programmation state
 * here the following transition order shall be enforced :
 * NONE -> HEAD -> DATA
 *  Since the programmation energy levels go down from 11 to 00, we use
 * 11 for NONE and 00 for DATA, the two other possible values meaning HEAD.
 *
 *  Same principle goes for garbage collection status
 *  ORPHAN -> ACTIVE -> TRASH
 */
#define FRAI_WRITE_NONE 3 // nothing has been safely written
#define FRAI_WRITE_HEAD 2 // item header has been safely written
/////// FRAI_WRITE_HEAD 1
#define FRAI_WRITE_DATA 0 // item header and data have been safely written

#define FRAI_STATE_ORPHAN 3 // the item has not been completely activated
#define FRAI_STATE_ACTIVE 2 // the item is valid and active
/////// FRAI_STATE_ACTIVE 1
#define FRAI_STATE_DELETE 0 // the item is available for garbage collection

#define FRAI_COPY 1 // copy of an item being moved out of a reclaimed sector
#define FRAI_UNIQ 0 // unique instance of an item

/* ==========================================================================
   Types
   ========================================================================== */
/*
 * IMPORTANT NOTE
 * ==============
 *   In order to be able to get rid of partially initialized blocks, the size
 * of an item has been defined as the data size (header size not counted).
 *   Thus it is always possible to overwrite the size to zero, turning an
 * incompletely written item into a single deleted header containing no data.
 *   This makes sure that, during the power-up scan of the FLASH, we can
 * invalidate any data block that could not be written due to power failure
 * during the last software activation.
 */

// common flash items header
typedef struct {
    unsigned int chk_state : 2; // not yet confirmed active, active, or available for garbage collection
    unsigned int chk_write : 2; // tells which parts of the item have been safely written
    unsigned int chk_copy  : 2; // temporarily set during garbage collection
    unsigned int signature :10; // to enease consistency check
    unsigned int size      :16; // item total size (max. 16 Kb)
    } frai_header_t;

// additional signature inside item header for consistency check
#define FRAI_ITEM_SIGNATURE(item) ((item) & 0x3F)

// object data contents
typedef struct {
    fms_rai_id_t    id;      // unique identifier
    u8           data[1]; // variable amount of data
    } frai_data_t;

// global FLASH object item
typedef struct frai_item_s {
    frai_header_t h; // header
    frai_data_t   b; // object data
    } frai_item_t;

// item WORD size computation
#define FRAI_W_SIZEOF(item) ((sizeof (((frai_item_t*)(item))->h) + ((frai_item_t*)(item))->h.size + 3)>>2)

// compute the size of a FLASH data block
#define FLASH_DATA_TO_ITEM_SIZE(size) ((fms_rai_size_t)((size) + offsetof (frai_item_t, b.data[0]) - sizeof (frai_header_t)))
#define FLASH_ITEM_TO_DATA_SIZE(size) ((fms_rai_size_t)((size) - offsetof (frai_item_t, b.data[0]) + sizeof (frai_header_t)))

/* ==========================================================================
   Module procedures
   ========================================================================== */

/* --------------------------------------------------------------------------
   Items handling layer initialization
   To be called once during system boot, before any random access item access attempt
   If it does not return TRUE, the random access item storage is deep in trouble
   -------------------------------------------------------------------------- */
int frai_items_init (void * base); // FLASH range base address

/* --------------------------------------------------------------------------
   Get an object identifier from a FLASH offset
   -------------------------------------------------------------------------- */
fms_rai_id_t frai_index_id (frai_offset_t offset); // FLASH offset pointing to a data item

/* --------------------------------------------------------------------------
   Duplicates items in a reclaimed sector in the first step of the garbage
   collection.
   -------------------------------------------------------------------------- */
void frai_gc_duplicate (frai_item_t * item); // direct pointer to a FLASH item

/* --------------------------------------------------------------------------
   Replaces items in a reclaimed sector with their copies in the second step
   of the garbage collection.
   -------------------------------------------------------------------------- */
void frai_gc_replace (frai_item_t * item); // copy of the displaced item

typedef enum
{
    FRAI_CACHE_READ,
    FRAI_CACHE_WRITE,
    FRAI_CACHE_READ2,
    FRAI_CACHE_WRITE2,
    FRAI_CHKSUM_FAIL1,
    FRAI_CHKSUM_FAIL2,
    FRAI_CHKSUM_FAIL3
} frai_cache_scan_t;

/* --------------------------------------------------------------------------
   Analyze and correct the state of an item during initial flash scan
   The pointer is passed as a void* to be nice with the scanning pointers
   -------------------------------------------------------------------------- */
typedef enum {
    FRAI_STATUS_ACTIVE,   // valid and active item
    FRAI_STATUS_DELETED,  // deleted item
    FRAI_STATUS_COPY,     // item copy for garbage collection
    FRAI_STATUS_ORPHAN,   // new version of an item not yet validated
    FRAI_STATUS_FREE,      // blank area
    FRAI_STATUS_ERROR     // error handling
    } frai_item_status_t;

frai_item_status_t frai_scan_item (frai_offset_t  offset,
                                   frai_offset_t * duplicate_item_offset,
                                   frai_offset_t * uniq_item_offset,
                                   u32           * MarkfreeNo,
                                   u32           * ScanOffsetChanged);

#if 0
/* --------------------------------------------------------------------------
   Invalidate an item
   Only used for fixing corrupted sectors during initial scan
   The pointer is passed as a void* to be nice with the scanning pointers
   -------------------------------------------------------------------------- */
void frai_scan_invalidate (frai_offset_t off,  // item to invalidate
                           unsigned size); // new item total size
#endif

/* --------------------------------------------------------------------------
   Anticipated recycling of dirty sectors

     This procedure should typically be called from a low-priority task.
     It will erase and reformat one sector at a time (and do nothing if no
   dirty sectors are present).
     Calling this procedure is in no way mandatory ; however, it will
   anticipate the cleanup of sectors, and thus possibly speed up the other
   operations of this module.
   -------------------------------------------------------------------------- */
void frai_recycle (void);



#define	ARM_CACHE_LINE_ALIGN		            (32)

#define FRAI_B_SIZEOF(item) (((sizeof (((frai_item_t*)(item))->h) + ((frai_item_t*)(item))->h.size + 3)>>2)<<2)
#define OFFSET_OF_B         (sizeof(frai_header_t))
#define OFFSET_OF_DATA      (sizeof(frai_header_t) + sizeof(fms_rai_id_t))

#if defined(USE_GET_NRAI_INFO)
extern u32 NRAI_SPACE;
#else //USE_GET_NRAI_INFO
#if defined(__FMS_ENLARGE_RAI_SIZE__)
#define	NRAI_SPACE                  (8 * 1024 * 1024)                           //Real NAND Size
#else
#define	NRAI_SPACE                  (1 * 1024 * 1024)                           //Real NAND Size
#endif
#endif //USE_GET_NRAI_INFO
#define	NRAI_BLOCK_SIZE             (64 * 1024)                                 //NAND Block Size
#define NRAI_OFFSET_MAX             NRAI_SPACE


#ifdef FMS_DEBUG
/* --------------------------------------------------------------------------
   print an item
   -------------------------------------------------------------------------- */
void DEBUG_item (frai_item_t * item); // item to be dumped
#else
#define DEBUG_item(x)
#endif // FMS_DEBUG

#endif /* ! _2d83dd2b5f5e3c2219df1dbafe7dd333_INCLUDED_FMS_RAI_BASE_H */

#endif /* !defined(__NAND__) */

