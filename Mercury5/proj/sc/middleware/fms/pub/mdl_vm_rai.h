////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_vm_rai.h
* @version
* @brief
*
*/

#ifndef __MDL_VM_RAI_H__
#define __MDL_VM_RAI_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
  * \brief	random access item identifier
  *
  */
typedef u32 vm_raiId_t;

/**
  * \brief	size of a random access item
  *
  */
typedef u16 vm_raiSize_t;

/**
  * \brief	information on a random access item
  *
  */
typedef struct {
    vm_raiSize_t size;  // byte size of the object
    } vm_raiInfo_t;

/**
  * \brief	iterator for identifier search
  *
  */
typedef int vm_raiBrowse_t[5];

/**
  * \brief	iterator for garbage collection
  *
  */
typedef int vm_raiGC_t[2];

/**
  * \brief	global statistics on object management
  *
  */
typedef struct {
    int mem_free;            ///< total byte amount of immediately available memory
    int mem_contig;          ///< byte amount of immediately available CONTIGUOUS memory
    int mem_avail;           ///< byte amount of memory available after complete garbage collection
    int mem_limit;           ///< total storage byte space (may be used as a scale factor for the other mem_xxx infos)
    int objects_read;        ///< number of objects read since last reboot
    int objects_created;     ///< number of objects created since last reboot
    int objects_overwritten; ///< number of objects overwritten since last reboot
    int objects_deleted;     ///< number of objects deleted since last reboot

    int sectors_erased;      ///< number of FLASH sectors erased since last reboot
#if 1//DUMPCONTIMEM //shihyu
    int continuousmem[16];
#endif

} vm_raiStats_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
int vm_raiRead (vm_raiId_t ident, vm_raiSize_t start, vm_raiSize_t length, void * data);
bool vm_raiWrite (vm_raiId_t ident, vm_raiSize_t size, const void * data);
bool vm_raiDelete (vm_raiId_t ident);
vm_raiId_t * vm_raiGroupDeleteInit (vm_raiId_t * ident, u32 number);
int vm_raiGroupDelete(vm_raiId_t * ident, u32 number);
bool vm_raiInfo (vm_raiId_t     ident, vm_raiInfo_t * info);
void vm_raiFindInit (vm_raiId_t min, vm_raiId_t max, vm_raiBrowse_t * iterator);
int vm_raiFindNext (vm_raiId_t *ident, vm_raiBrowse_t  * iterator);
int vm_raiFindClose (vm_raiBrowse_t  * iterator);
int vm_raiStats (vm_raiStats_t * info);
int vm_raiGcInit (int item_num, int item_size, vm_raiGC_t * iterator);
int vm_raiGc (vm_raiGC_t * iterator);
/* non-blocking function */
/* if can't get semaphor, return error */
int vm_raiRead_nb (vm_raiId_t ident, vm_raiSize_t start, vm_raiSize_t length, void * data);
bool vm_raiFlush (void);

#endif //__MDL_VM_RAI_H__

