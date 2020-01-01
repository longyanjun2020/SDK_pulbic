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
* @file    mdl_fms_rai.h
* @version
* @brief
*
*/

#ifndef __MDL_FMS_RAI_H__
#define __MDL_FMS_RAI_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
// opaque iterator for identifier search
#if	defined(_FMS_RAI_HASH_C_)	||	defined(__FMS_RAI_NAND_C__)
#define fms_rai_browse_t fms_rai_browse_opaque_t
#endif // _FMS_RAI_HASH_C_

/*=============================================================*/
// Data type definition
/*=============================================================*/
// random access item identifier
typedef u32 fms_rai_id_t;

// size of a random access item
typedef u16 fms_rai_size_t;

// informations on a random access item
typedef struct {
    fms_rai_size_t size;  // byte size of the object
    } fms_rai_info_t;

typedef int fms_rai_browse_t[5]; // Fixes SCR #32713 was char[16]

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
#ifdef __NAND__
void fms_nraiFreeSectorRecord(void);
u32 fms_nraiFlush(void);
#endif
/* --------------------------------------------------------------------------
   Sorting a to-be-deleted RAI group according to offset, makes the adjacent IDs rearrange in the same cluster.
   Returns id information of each group, NULL if any of the object check in hash table failed.
   NOTE : About the return buffer, the first element means how many subgroup in this group deletion.
          and the following elements mean the last RAI id in each subgroup.
   -------------------------------------------------------------------------- */
fms_rai_id_t * fms_rai_group_delete_init(fms_rai_id_t * identGroup, u32 number); //id group of the object to sorting. number of the id group

/* --------------------------------------------------------------------------
   Delete a group of random access item
   Returns TRUE on success, FALSE if any of the object check in hash table failed.
   -------------------------------------------------------------------------- */
int fms_rai_group_delete(fms_rai_id_t * identGroup, u32 number);// id group of the object to delete. number of the id group



/* --------------------------------------------------------------------------
   Start a search on a given range of identifier values
   The identifiers will be returned in no particular order
   This function has no return value
   -------------------------------------------------------------------------- */
int fms_rai_find_init (fms_rai_id_t        min,       // minimal identifier value
                       fms_rai_id_t        max,       // maximal identifier value
                       fms_rai_browse_t  * iterator); // iterator used for subsequent searches

/* --------------------------------------------------------------------------
   Get the next defined data object identifier in a sequential search

     The iterator must have been initialized with fms_rai_find_init(). Calling
   the function with an unitialized iterator will have unpredictable results.

     Return FMS_RAI_FOUND if another object has been found. The object ID is
   returned in the first parameter.
     Returns FMS_RAI_DONE if no more object have been found. The first parameter
   value is undefined in that case.
     Returns FMS_RAI_ABORT if another operation on the data objects (insertion or
   deletion by another task, garbage collection) has modified the internal
   repartition of the identifiers. In that case, the caller has to abort the
   iteration and start all over again. Sorry about that, it's a design choice
   to allow minimal memory consumption.
   -------------------------------------------------------------------------- */
int fms_rai_find_next (fms_rai_id_t *      ident,     // next object identifier
                       fms_rai_browse_t  * iterator); // iterator used for subsequent searches

/* --------------------------------------------------------------------------
   Delete a random access item
   Returns TRUE on success, FALSE if the object did not exist
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int fms_rai_delete (fms_rai_id_t ident); // id of the object to delete

/* --------------------------------------------------------------------------
   Get informations on a random access item
   Returns TRUE on success, FALSE if the object does not exist
   -------------------------------------------------------------------------- */
int fms_rai_info (fms_rai_id_t     ident, // id of the object to get info on
                  fms_rai_info_t * info); // returned informations

/* --------------------------------------------------------------------------
   Read a range of a random access item's content
   Returns the number of bytes read, 0 if no object was found
   the size parameter will be updated to the actual number of bytes read
   read operations past the object's end of data will be truncated
   -------------------------------------------------------------------------- */
int fms_rai_read (fms_rai_id_t   ident,  // id of the object to read from
                  fms_rai_size_t start,  // read start offset
                  fms_rai_size_t length, // number of bytes to read
                  void *         data);  // object data receive buffer

/* --------------------------------------------------------------------------
   Create or modify a random access item
   Returns TRUE on success, FALSE if there is not enough space left or
   the requested size exceeds the FMS_RAI_SIZE_MAX limit
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int fms_rai_write (fms_rai_id_t   ident, // id of the created / modified object
                   fms_rai_size_t size,  // total size of the object
                   const void *   data); // object contents

#endif //__MDL_FMS_RAI_H__

