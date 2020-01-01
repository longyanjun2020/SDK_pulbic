/****************************************************************************/
/*  $Workfile::   fms_rai_hash.h                                          $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*                                                                          */
/*  Contents: flash random access items - hash-coding indexation            */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.2  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   Jun 07 2004 10:18:44 $     */
/****************************************************************************
 *   $Log:   U:/projet/gsm/pvcsarch/archives/fms/inc/fms_rai_hash.h-arc  $
 *
 *   Rev 0.2   Jun 07 2004 10:18:44   kod
 *Version v1a13.
 *Resolution for 21973: ARM exception on double scratch memory close
 *Resolution for 23016: [FMS] Disabling ST flash devices permanent lock feature
 *
 *   Rev 0.1   25 Feb 2003 11:44:34   kod
 *Initial release for integration
 ****************************************************************************/


/***************************************************************************** 
 File     : fms_rai_hash.h
 Contents : flash random access items - hash-coding indexation
 Author   : Pierre Berger, Theoris
 Date     : Jan 3 2003
 ******************************************************************************/

#ifndef _ff895d4cb455439d6733bc80dcf8750e_INCLUDED_FMS_RAI_HASH_H
#define _ff895d4cb455439d6733bc80dcf8750e_INCLUDED_FMS_RAI_HASH_H

/* ========================================================================== 
   Constants
   ========================================================================== */

/* ========================================================================== 
   Types
   ========================================================================== */

/* ========================================================================== 
   Module procedures
   ========================================================================== */

/* --------------------------------------------------------------------------
   Get the amount of memory needed for a hash table of a given size
     The application should call this function and use its result to allocate
   the required amount of memory, then pass the same number of elements to the
   frai_hash_init() function, along with the allocated buffer.
   -------------------------------------------------------------------------- */
int frai_hash_query_size (unsigned int num_elem); // desired number of elements

/* --------------------------------------------------------------------------
   Initialize the hash table handling
   -------------------------------------------------------------------------- */
void frai_hash_init (unsigned int num_elem,   // desired number of elements
                     void *       data);      // hash table buffer

/* --------------------------------------------------------------------------
   Retrieve an item's FLASH offset from its identifier
   Returns FRAI_NULL if the identifier was not found
   -------------------------------------------------------------------------- */
frai_offset_t frai_hash_get (fms_rai_id_t id); // id of the object to get

/* --------------------------------------------------------------------------
   Insert an element into the hash table
   Returns FALSE if the table is full, or TRUE on success
   -------------------------------------------------------------------------- */
bool frai_hash_put (fms_rai_id_t  id,      // item identifier
                    frai_offset_t offset); // FLASH offset of the item

/* --------------------------------------------------------------------------
   Remove a hash entry
   Returns FALSE if the entry did not exist, or succeeds returning TRUE
   -------------------------------------------------------------------------- */
bool frai_hash_remove (fms_rai_id_t id); // id of the object to remove


#endif /* ! _ff895d4cb455439d6733bc80dcf8750e_INCLUDED_FMS_RAI_HASH_H */
