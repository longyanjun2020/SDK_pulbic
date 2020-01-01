/****************************************************************************/
/*  $Workfile::   fms_rai_store.h                                         $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*                                                                          */
/*  Contents: FLASH random access items - low level storage                 */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.2  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   26 Mar 2003 10:23:32 $     */
/****************************************************************************
 *   $Log:   G:/projet/flash/pvcsarch/archives/FMS/inc/fms_rai_store.h-arc  $
 *
 *   Rev 0.2   26 Mar 2003 10:23:32   kod
 *Second release.
 *Works with DwlWin.
 *
 *   Rev 0.1   25 Feb 2003 11:44:34   kod
 *Initial release for integration
 ****************************************************************************/


/*****************************************************************************
 File     : fms_rai_store.h
 Contents : FLASH random access items - low level storage
 Author   : Pierre Berger, Theoris
 Date     : Nov 12 2002
 ******************************************************************************/

#ifndef _7651b920196500b812f04cd107b6460e_INCLUDED_FMS_RAI_STORE_H
#define _7651b920196500b812f04cd107b6460e_INCLUDED_FMS_RAI_STORE_H

/* ==========================================================================
   Public functions
   ========================================================================== */

/* --------------------------------------------------------------------------
   Get the amount of memory needed for handling storage across a given number
   of sectors
   -------------------------------------------------------------------------- */
int frai_store_query_size (unsigned int num_sectors); // total number of sectors

/* --------------------------------------------------------------------------
   Initialize the random access items storage
   External buffer must be provided for sector descriptors storage
   -------------------------------------------------------------------------- */
void frai_store_init (void * base_addr,    // base address of the sectors
                      int    sector_size,  // size of a sector
                      int    num_sectors,  // number of sectors
                      void * private_mem); // externally allocated storage

/* --------------------------------------------------------------------------
    Allocate a chunk of flash storage
    Returns the new storage address, or NULL if no storage available
   ======================================
   BEWARE : it takes WORD sizes for input
   ======================================
   -------------------------------------------------------------------------- */
void * frai_store_alloc (int w_size); // total word size of the object

/* --------------------------------------------------------------------------
   Free a chunk of FLASH storage
   ======================================
   BEWARE : it takes WORD sizes for input
   ======================================
   -------------------------------------------------------------------------- */
void frai_store_free (int    w_size,   // total word size of the object
                      void * address); // object address

/* --------------------------------------------------------------------------
   Get global flash management statistics
   -------------------------------------------------------------------------- */
void frai_store_stats (fms_rai_stats_t * stats); // returned information

#if 1
#define frai_SetProtection()
#define frai_UnsetProtection()
#else
/* --------------------------------------------------------------------------
   lock sectors
   -------------------------------------------------------------------------- */
void frai_SetProtection(void);

/* --------------------------------------------------------------------------
   unlock sectors
   -------------------------------------------------------------------------- */
void frai_UnsetProtection(void);
#endif

/* --------------------------------------------------------------------------
   Prints memory stats
   -------------------------------------------------------------------------- */
#ifdef FMS_DEBUG
void DEBUG_mem (void);
#else
#define DEBUG_mem()
#endif // FMS_DEBUG

#endif /* ! _7651b920196500b812f04cd107b6460e_INCLUDED_FMS_RAI_STORE_H */
