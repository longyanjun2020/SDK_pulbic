/**
 * \file rai_fs.h
 * \brief: RAI (Random Access Interface) object access through File System
 */

#ifndef __RAI_FS_H__
#define __RAI_FS_H__

#include "vm_types.ht"

// random access item identifier
typedef u32 rai_id_t;

// size of a random access item
typedef u16 rai_size_t;

// informations on a random access item
typedef struct {
    rai_size_t size;  // byte size of the object
    } rai_info_t;

typedef char rai_browse_t[16];

typedef char rai_GC_t[8];

// global statistics on object management
typedef struct {
    int mem_free;            // total byte amount of immediately available memory
    int mem_contig;          // byte amount of immediately available CONTIGUOUS memory
    int mem_avail;           // byte amount of memory available after complete garbage collection
    int mem_limit;           // total storage byte space
                             // (may be used as a scale factor for the other mem_xxx infos)
    int objects_read;        // number of objects read since last reboot
    int objects_created;     // number of objects created since last reboot
    int objects_overwritten; // number of objects overwritten since last reboot
    int objects_deleted;     // number of objects deleted since last reboot

    int sectors_erased;      // number of FLASH sectors erased since last reboot

    } rai_stats_t;

s32 rai_fs_Init(void);
s32 rai_fs_info (rai_id_t     ident, rai_info_t * info) ;
s32 rai_fs_read (rai_id_t   ident,  rai_size_t start,  rai_size_t length, void *         data) ;
s32 rai_fs_write (rai_id_t    ident,   rai_size_t  size,  const void *    data) ;
s32 rai_fs_delete (rai_id_t ident) ;
s32 rai_fs_find_init (rai_id_t min, rai_id_t max, rai_browse_t  *browse) ;
s32 rai_fs_find_next (rai_id_t *ident, rai_browse_t  *browse) ;
s32 rai_fs_find_close (rai_browse_t  * browse) ;
s32 rai_fs_stats (rai_stats_t * info) ;

s32 rai_fs_gc_init (s32            item_num,  // number of items to make room for
                     s32            item_size, // average size of an item
                     rai_GC_t * iterator); // iterative GC context
s32 rai_fs_gc (rai_GC_t * iterator); // iterative GC context

#endif // __RAI_FS_H__
