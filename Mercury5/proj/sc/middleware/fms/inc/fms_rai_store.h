#if !defined(__NAND__)
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
   Macros
   ========================================================================== */
/*
 * just to avoid annoying compiler warnings
 * equivalent to val += var or var -= val, but does the proper cast to convert
 * back from integer promotion
 */
#define U16_INCREMENT(var,val) (var) = (u16)((var)+(val))
#define U16_DECREMENT(var,val) (var) = (u16)((var)-(val))

/* ==========================================================================
   Constants
   ========================================================================== */
// signature of an object sector
#define FRAI_SECTOR_SIGNATURE 0xF0B // 12 bits

/*
 * note that the 16 bits sizes are just enough to address 256K sectors
 * (taking advantage of the 4 bytes alignment)
 */
typedef struct frai_sector_s
{
    struct frai_sector_s * next;      // link to various sector lists
    u32 *                  w_base;    // word address of the first item in the sector
    u16                    w_alloc;   // current allocation word offset
    u16                    w_gc_base; // allocation word offest before GC first pass
    u16                    w_free;    // free  space word size
    u16                    w_trash;   // trash space word size
} frai_sector_t;

typedef struct
{
    frai_sector_t * sector;     // array of sector descriptors, allocated externally
    u32 *           mem_w_base; // base address of the sectors area

    frai_sector_t * alloc;   // current allocation sectors list
    frai_sector_t * free;    // free sectors list
    frai_sector_t * dirty;   // list of sectors that must be cleaned
    frai_sector_t * reserve; // single sector reserved for garbage collection
    frai_sector_t * garbage; // current sector undergoing garbage collection (NULL if no GC in progres)

    int             num_sectors;   // total number of sectors
    u16             sector_w_size; // word size of the sector's item storage

    u16             max_trash;

    /* ArthurCheng 20090217 { */
    int             reserve_for_trash; //
    /* ArthurCheng 20090217 } */
    int             contig_free; // maximal amount of contiguous free memory
    int             total_free;  // total amount of free memory (including the reserved sector)
    int             total_trash; // total amount of trash piled up in the whole set of sectors
    int             total_mem;   // total amount of memory in all the sectors

    int            erased;  // total number of erased sectors
} frai_store_context_t;


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
#if !defined(__FILE_PROSPECTOR__)
                      void * private_mem); // externally allocated storage
#else
					  void * private_mem,  // externally allocated storage
					  void * pHandle);     // Handle for output RAI information
#endif

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

/* --------------------------------------------------------------------------
   lock sectors
   -------------------------------------------------------------------------- */
void frai_SetProtection(void);

/* --------------------------------------------------------------------------
   unlock sectors
   -------------------------------------------------------------------------- */
void frai_UnsetProtection(void);

/* --------------------------------------------------------------------------
   Prints memory stats
   -------------------------------------------------------------------------- */
#ifdef FMS_DEBUG
void DEBUG_mem (void);
#else
#define DEBUG_mem()
#endif // FMS_DEBUG

#endif /* ! _7651b920196500b812f04cd107b6460e_INCLUDED_FMS_RAI_STORE_H */

#else /* defined(__NAND__) */
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
#if !defined(__FILE_PROSPECTOR__)
                      void * private_mem); // externally allocated storage
#else
					  void * private_mem,  // externally allocated storage
					  void * pHandle);     // Handle for output RAI information
#endif

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
                      u32   address); // object address

/* --------------------------------------------------------------------------
   Get global flash management statistics
   -------------------------------------------------------------------------- */
void frai_store_stats (fms_rai_stats_t * stats); // returned information

/* --------------------------------------------------------------------------
   lock sectors
   -------------------------------------------------------------------------- */
void frai_SetProtection(void);

/* --------------------------------------------------------------------------
   unlock sectors
   -------------------------------------------------------------------------- */
void frai_UnsetProtection(void);

/* --------------------------------------------------------------------------
   Prints memory stats
   -------------------------------------------------------------------------- */
#ifdef FMS_DEBUG
void DEBUG_mem (void);
#else
#define DEBUG_mem()
#endif // FMS_DEBUG

#endif /* ! _7651b920196500b812f04cd107b6460e_INCLUDED_FMS_RAI_STORE_H */


#endif	/*	!defined(__NAND__)	*/

