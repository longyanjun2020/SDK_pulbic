#if	!defined(__NAND__)
/****************************************************************************/
/*  $Workfile::   fms_rai.h                                               $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*                                                                          */
/*  Contents: flash random access items - public interface                  */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.4  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   07 Feb 2006 09:27:02 $     */
/****************************************************************************
 *   $Log:   U:/projet/gsm/pvcsarch/archives/fms/itf/fms_rai.h-arc  $
 *
 *   Rev 0.4   07 Feb 2006 09:27:02   kod
 *Resolution for 32713: Cannot write entry in Object Flash memory part
 *Version v1a2c.
 *
 *   Rev 0.3   24 Nov 2004 15:53:00   kod
 *Resolution for 26275: Two allocations with undefined size are allowed
 *Resolution for 26611: [FMS] Xmodem downloader needs some FMS modifications
 *Version v1a18
 *
 *   Rev 0.2   13 Jun 2003 12:00:00   kod
 *Changed FMS_RAI_SIZE_MAX from 16 kiB to 30 kiB
 *Resolution for 10271: RAI entry maximum size change
 *
 *   Rev 0.1   25 Feb 2003 11:42:42   kod
 *Initial release for integration
 ****************************************************************************/



/*****************************************************************************
 File     : fms_rai.h
 Contents : flash random access items - public interface
 Author   : Pierre Berger, Theoris
 Date     : Nov 8 2002
 *****************************************************************************
 note: RAI stands for Random Access Items. It also means "paradise" in Russian
 ******************************************************************************/

#ifndef __FMS_RAI_H__
#define __FMS_RAI_H__

#include "mdl_fms_rai.h"

/* ==========================================================================
   Constants
   ========================================================================== */

// maximal data size for a random access item
#define FMS_RAI_SIZE_MAX ((fms_rai_size_t) (30*1024))

// return codes for fms_rai_find_next
#define FMS_RAI_FOUND 0 // iteration found another identifier
#define FMS_RAI_DONE  1 // end of iteration
#define FMS_RAI_ABORT 2 // iteration is aborted due to GC or other index changes

// return codes for fms_rai_FLASH_gc
#define FMS_RAI_GC_CONT 0 // garbage collection still in progress
#define FMS_RAI_GC_OK   1 // garbage collection successful
#define FMS_RAI_GC_KO   2 // not enough room for the requested items

/* ==========================================================================
   Public types
   ========================================================================== */
// opaque iterator for garbage collection
#if	defined(_FMS_RAI_STORE_C_)	||	defined(__FMS_RAI_NAND_C__)
#define fms_rai_GC_t fms_rai_GC_opaque_t
#endif // _FMS_RAI_HASH_C_
typedef int fms_rai_GC_t[2]; // Fixes SCR #32713 was char[8]

// pseudo-iterator for preventive GC
#ifdef _FMS_RAI_STORE_C_
const fms_rai_GC_t fms_rai_gc_preventive = {0,0};
#else
extern fms_rai_GC_t fms_rai_gc_preventive;
#define FMS_RAI_GC_PREVENTIVE (&fms_rai_gc_preventive)
#endif // _FMS_RAI_HASH_C_

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

    } fms_rai_stats_t;

/* ==========================================================================
   Public functions
   ========================================================================== */

/* non-blocking */
int fms_rai_read_nb (fms_rai_id_t   ident,  // id of the object to read from
                  fms_rai_size_t start,  // read start offset
                  fms_rai_size_t length, // number of bytes to read
                  void *         data);  // object data receive buffer

/* non-blocking */
int fms_rai_write_nb (fms_rai_id_t   ident, // id of the created / modified object
                   fms_rai_size_t size,  // total size of the object
                   const void *   data); // object contents

int fms_rai_find_close (fms_rai_browse_t  * iterator); // iterator used for subsequent searches

/* --------------------------------------------------------------------------
   Get global FLASH objects management statistics
   -------------------------------------------------------------------------- */
int fms_rai_stats (fms_rai_stats_t * info); // returned informations

/* --------------------------------------------------------------------------
   Garbage collector initialization

     This function will reclaim unused FLASh space, trying to free up at least
   the requested amount of memory.

     If room for more than one object is requested, it is not guaranteed that
   all the subsequent allocations will succeed, since the allocation cannot cross
   a FLASH sector boundary and the system is likely to run out of contiguous
   memory.
     If the caller wants to make sure that an allocation will succeed, he has to
   call the garbage collection before each single allocation, and arrange for not
   being interrupted by another task that could perform any other write/delete
   operation. He then has to make sure the garbage collector reported an OK
   status. This could not be the case if there is not enough space left in the
   FLASH.
   -------------------------------------------------------------------------- */
int fms_rai_gc_init (int            item_num,  // number of items to make room for
                     int            item_size, // average size of an item
                     fms_rai_GC_t * iterator); // iterative GC context

/* --------------------------------------------------------------------------
   Garbage collector invokation

     The iterator must have been initialized with fms_rai_gc_init(). Calling the
   function with an unitialized iterator will have unpredictable results.

     The garbage collection algorithm has been split into (relatively) fast
   steps to avoid blocking the caller for a potentially long time (more than 1
   second approximately).

     Therefore, the function is likely to take more than one invokation to
   complete.
     The FMS_RAI_GC_CONT return code signals that the garbage collection is still
   in progress and that the function has to be called again.
     The process is complete when the function returns either a FMS_RAI_GC_OK or
   FMS_RAI_GC_KO result.
     The KO result may occur when the actual remaining space in the FLASH is
   not sufficient to hold the requested number of items.
   -------------------------------------------------------------------------- */
int fms_rai_gc (fms_rai_GC_t * iterator); // iterative GC context

#if 1
int fms_rai_fatObject(u32* fatObject);
int fms_rai_hiddenObject(u32* hidnObject);
#endif

bool fms_rai_flush(void);

#ifdef	__NAND__
/* --------------------------------------------------------------------------
   Read a range of a FLASH object's content
   Returns TRUE on success, FALSE if no object was found
   the size parameter will be updated to the actual number of bytes read
   read operations past the object's end of data will be truncated
   -------------------------------------------------------------------------- */
int	fms_rai_nand_read(fms_rai_id_t		 ident,  // id of the object to read from
											fms_rai_size_t	 start,  // read start offset
                  		fms_rai_size_t	 length, // number of bytes to read
                  		void					 * data);  // object data receive buffer



/* --------------------------------------------------------------------------
   Create or modify a FLASH object
   Returns TRUE on success, FALSE if there is not enough space left or
   the requested size exceeds the FRAI_SIZE_MAX limit
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_write(fms_rai_id_t			ident, // id of the created / modified object
											 fms_rai_size_t		size,  // total size of the object
											 const	void		*	data); // object contents


/* --------------------------------------------------------------------------
   Delete a FLASH object
   Returns TRUE on success, FALSE if the object did not exist
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_delete(fms_rai_id_t ident); // id of the object to delete


/* --------------------------------------------------------------------------
   Get informations on a FLASH object
   Returns TRUE on success, FALSE if the object does not exist
   -------------------------------------------------------------------------- */
int	fms_rai_nand_info(fms_rai_id_t		 ident, // id of the object to get info on
											fms_rai_info_t * info); // returned informations


/* --------------------------------------------------------------------------
   Start a search from a given identifier value.
   No return value
   -------------------------------------------------------------------------- */
int fms_rai_nand_find_init(fms_rai_id_t				min,     // minimal identifier value
													 fms_rai_id_t				max,     // maximal identifier value
													 fms_rai_browse_t * opaque); // iterator used for subsequent searches


/* --------------------------------------------------------------------------
   Get the next defined data object identifier in a sequential search

     The iterator must have been initialized with frai_find_init(). Calling
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
int	fms_rai_nand_find_next(fms_rai_id_t			* ident,   // next object identifier
													 fms_rai_browse_t * opaque); // iterator used for subsequent searches


int	fms_rai_nand_find_close(fms_rai_browse_t * opaque); // iterator used for subsequent searches


/* --------------------------------------------------------------------------
   Get global FLASH objects management statistics
   Always returns 0
   -------------------------------------------------------------------------- */
int fms_rai_nand_stats(fms_rai_stats_t * info); // returned informations


/* --------------------------------------------------------------------------
   Garbage collector initialization

     This function will reclaim unused FLASh space, trying to free up at least
   the requested amount of memory.

     If room for more than one object is requested, it is not guaranteed that
   all the subsequent allocations will succeed, since the allocation cannot cross
   a FLASH sector boundary and the system is likely to run out of contiguous
   memory.
     If the caller wants to make sure that an allocation will succeed, he has to
   call the garbage collection before each single allocation, and arrange for not
   being interrupted by another task that could perform any other write/delete
   operation. He then has to make sure the garbage collector reported an OK
   status. This could not be the case if there is not enough space left in the
   FLASH.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_gc_init(int						item_num,  // number of items to make room for
												 int					  item_size, // average size of an item
												 fms_rai_GC_t * opaque);   // iterative GC context


/* --------------------------------------------------------------------------
   Garbage collector invokation

     The iterator must have been initialized with frai_gc_init(). Calling the
   function with an unitialized iterator will have unpredictable results.

     However, it is possible to use the FMS_RAI_GC_PREVENTIVE pseudo-iterator to
   perform preventive cleanup. In that case, the garbage collection will always
   succeed, and will reclaim only the sectors that contain a significant amount
   of garbage. The invokation should be done in a low-priority task to free up
   FLASH space in anticipation for other operations. It is advisable to couple
   this invokation with a call to frai_recycle().

     The garbage collection algorithm has been split into (relatively) fast
   steps to avoid blocking the caller for a potentially long time (more than 1
   second approximately).

     Therefore, the function is likely to take more than one invokation to
   complete.
     The FMS_RAI_GC_CONT return code signals that the garbage collection is still
   in progress and that the function has to be called again.
     The process is complete when the function returns either a FMS_RAI_GC_OK or
   FMS_RAI_GC_KO result.
     The KO result may occur when the actual remaining space in the FLASH is
   not sufficient to hold the requested number of items.
   -------------------------------------------------------------------------- */
int fms_rai_nand_gc(fms_rai_GC_t * opaque); // iterative GC context
#endif

#endif /* ! __FMS_RAI_H__ */

#else  /* defined(__NAND__) */
/****************************************************************************/
/*  $Workfile::   fms_rai.h                                               $ */
/*--------------------------------------------------------------------------*/
/*  Scope   : Flash Memory Services                                         */
/*                                                                          */
/*  Contents: flash random access items - public interface                  */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  $Revision::   0.4  $                                                    */
/*-------------------------------+------------------------------------------*/
/*  $Author::   kod    $         |     $Date::   07 Feb 2006 09:27:02 $     */
/****************************************************************************
 *   $Log:   U:/projet/gsm/pvcsarch/archives/fms/itf/fms_rai.h-arc  $
 *
 *   Rev 0.4   07 Feb 2006 09:27:02   kod
 *Resolution for 32713: Cannot write entry in Object Flash memory part
 *Version v1a2c.
 *
 *   Rev 0.3   24 Nov 2004 15:53:00   kod
 *Resolution for 26275: Two allocations with undefined size are allowed
 *Resolution for 26611: [FMS] Xmodem downloader needs some FMS modifications
 *Version v1a18
 *
 *   Rev 0.2   13 Jun 2003 12:00:00   kod
 *Changed FMS_RAI_SIZE_MAX from 16 kiB to 30 kiB
 *Resolution for 10271: RAI entry maximum size change
 *
 *   Rev 0.1   25 Feb 2003 11:42:42   kod
 *Initial release for integration
 ****************************************************************************/



/*****************************************************************************
 File     : fms_rai.h
 Contents : flash random access items - public interface
 Author   : Pierre Berger, Theoris
 Date     : Nov 8 2002
 *****************************************************************************
 note: RAI stands for Random Access Items. It also means "paradise" in Russian
 ******************************************************************************/

#ifndef __FMS_RAI_H__
#define __FMS_RAI_H__

#include "mdl_fms_rai.h"

/* ==========================================================================
   Constants
   ========================================================================== */

// maximal data size for a random access item
#define FMS_RAI_SIZE_MAX ((fms_rai_size_t) (60*1024))

// return codes for fms_rai_find_next
#define FMS_RAI_FOUND 0 // iteration found another identifier
#define FMS_RAI_DONE  1 // end of iteration
#define FMS_RAI_ABORT 2 // iteration is aborted due to GC or other index changes

// return codes for fms_rai_FLASH_gc
#define FMS_RAI_GC_CONT 0 // garbage collection still in progress
#define FMS_RAI_GC_OK   1 // garbage collection successful
#define FMS_RAI_GC_KO   2 // not enough room for the requested items

/* ==========================================================================
   Public types
   ========================================================================== */
// opaque iterator for garbage collection
#if	defined(_FMS_RAI_STORE_C_)	||	defined(__FMS_RAI_NAND_C__)
#define fms_rai_GC_t fms_rai_GC_opaque_t
#endif // _FMS_RAI_HASH_C_
typedef int fms_rai_GC_t[2]; // Fixes SCR #32713 was char[8]

// pseudo-iterator for preventive GC
#ifdef _FMS_RAI_STORE_C_
const fms_rai_GC_t fms_rai_gc_preventive = {0,0};
#else
extern fms_rai_GC_t fms_rai_gc_preventive;
#define FMS_RAI_GC_PREVENTIVE (&fms_rai_gc_preventive)
#endif // _FMS_RAI_HASH_C_

#define DUMPCONTIMEM 1


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
#if DUMPCONTIMEM //shihyu
    int continuousmem[16];
#endif

    } fms_rai_stats_t;

/* ==========================================================================
   Public functions
   ========================================================================== */

/* non-blocking */
int fms_rai_read_nb (fms_rai_id_t   ident,  // id of the object to read from
                  fms_rai_size_t start,  // read start offset
                  fms_rai_size_t length, // number of bytes to read
                  void *         data);  // object data receive buffer

/* non-blocking */
int fms_rai_write_nb (fms_rai_id_t   ident, // id of the created / modified object
                   fms_rai_size_t size,  // total size of the object
                   const void *   data); // object contents

int fms_rai_find_close (fms_rai_browse_t  * iterator); // iterator used for subsequent searches

/* --------------------------------------------------------------------------
   Get global FLASH objects management statistics
   -------------------------------------------------------------------------- */
int fms_rai_stats (fms_rai_stats_t * info); // returned informations

/* --------------------------------------------------------------------------
   Garbage collector initialization

     This function will reclaim unused FLASh space, trying to free up at least
   the requested amount of memory.

     If room for more than one object is requested, it is not guaranteed that
   all the subsequent allocations will succeed, since the allocation cannot cross
   a FLASH sector boundary and the system is likely to run out of contiguous
   memory.
     If the caller wants to make sure that an allocation will succeed, he has to
   call the garbage collection before each single allocation, and arrange for not
   being interrupted by another task that could perform any other write/delete
   operation. He then has to make sure the garbage collector reported an OK
   status. This could not be the case if there is not enough space left in the
   FLASH.
   -------------------------------------------------------------------------- */
int fms_rai_gc_init (int            item_num,  // number of items to make room for
                     int            item_size, // average size of an item
                     fms_rai_GC_t * iterator); // iterative GC context

/* --------------------------------------------------------------------------
   Garbage collector invokation

     The iterator must have been initialized with fms_rai_gc_init(). Calling the
   function with an unitialized iterator will have unpredictable results.

     The garbage collection algorithm has been split into (relatively) fast
   steps to avoid blocking the caller for a potentially long time (more than 1
   second approximately).

     Therefore, the function is likely to take more than one invokation to
   complete.
     The FMS_RAI_GC_CONT return code signals that the garbage collection is still
   in progress and that the function has to be called again.
     The process is complete when the function returns either a FMS_RAI_GC_OK or
   FMS_RAI_GC_KO result.
     The KO result may occur when the actual remaining space in the FLASH is
   not sufficient to hold the requested number of items.
   -------------------------------------------------------------------------- */
int fms_rai_gc (fms_rai_GC_t * iterator); // iterative GC context

bool fms_rai_flush(void);

#ifdef	__NAND__
/* --------------------------------------------------------------------------
   Read a range of a FLASH object's content
   Returns TRUE on success, FALSE if no object was found
   the size parameter will be updated to the actual number of bytes read
   read operations past the object's end of data will be truncated
   -------------------------------------------------------------------------- */
int	fms_rai_nand_read(fms_rai_id_t		 ident,  // id of the object to read from
											fms_rai_size_t	 start,  // read start offset
                  		fms_rai_size_t	 length, // number of bytes to read
                  		void					 * data);  // object data receive buffer

#if 0
/* --------------------------------------------------------------------------
   Read a range of a FLASH object's content
   Returns TRUE on success, FALSE if no object was found
   the size parameter will be updated to the actual number of bytes read
   read operations past the object's end of data will be truncated
   -------------------------------------------------------------------------- */
int	fms_rai_nand_read_nb(fms_rai_id_t			ident,  // id of the object to read from
											   fms_rai_size_t		start,  // read start offset
                  		   fms_rai_size_t		length, // number of bytes to read
                  		   void						*	data);  // object data receive buffer
#endif

/* --------------------------------------------------------------------------
   Create or modify a FLASH object
   Returns TRUE on success, FALSE if there is not enough space left or
   the requested size exceeds the FRAI_SIZE_MAX limit
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_write(fms_rai_id_t			ident, // id of the created / modified object
											 fms_rai_size_t		size,  // total size of the object
											 const	void		*	data); // object contents

#if 0
/* --------------------------------------------------------------------------
   Create or modify a FLASH object
   Returns TRUE on success, FALSE if there is not enough space left or
   the requested size exceeds the FRAI_SIZE_MAX limit
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_write_nb(fms_rai_id_t		 ident, // id of the created / modified object
												  fms_rai_size_t	 size,  // total size of the object
												  const	void		 * data); // object contents
#endif

/* --------------------------------------------------------------------------
   Delete a FLASH object
   Returns TRUE on success, FALSE if the object did not exist
   NOTE : this function is likely to trigger garbage collection,
          therefore its response time may be over one second.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_delete(fms_rai_id_t ident); // id of the object to delete


/* --------------------------------------------------------------------------
   Get informations on a FLASH object
   Returns TRUE on success, FALSE if the object does not exist
   -------------------------------------------------------------------------- */
int	fms_rai_nand_info(fms_rai_id_t		 ident, // id of the object to get info on
											fms_rai_info_t * info); // returned informations


/* --------------------------------------------------------------------------
   Start a search from a given identifier value.
   No return value
   -------------------------------------------------------------------------- */
int fms_rai_nand_find_init(fms_rai_id_t				min,     // minimal identifier value
													 fms_rai_id_t				max,     // maximal identifier value
													 fms_rai_browse_t * opaque); // iterator used for subsequent searches


/* --------------------------------------------------------------------------
   Get the next defined data object identifier in a sequential search

     The iterator must have been initialized with frai_find_init(). Calling
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
int	fms_rai_nand_find_next(fms_rai_id_t			* ident,   // next object identifier
													 fms_rai_browse_t * opaque); // iterator used for subsequent searches


int	fms_rai_nand_find_close(fms_rai_browse_t * opaque); // iterator used for subsequent searches


/* --------------------------------------------------------------------------
   Get global FLASH objects management statistics
   Always returns 0
   -------------------------------------------------------------------------- */
int fms_rai_nand_stats(fms_rai_stats_t * info); // returned informations


/* --------------------------------------------------------------------------
   Garbage collector initialization

     This function will reclaim unused FLASh space, trying to free up at least
   the requested amount of memory.

     If room for more than one object is requested, it is not guaranteed that
   all the subsequent allocations will succeed, since the allocation cannot cross
   a FLASH sector boundary and the system is likely to run out of contiguous
   memory.
     If the caller wants to make sure that an allocation will succeed, he has to
   call the garbage collection before each single allocation, and arrange for not
   being interrupted by another task that could perform any other write/delete
   operation. He then has to make sure the garbage collector reported an OK
   status. This could not be the case if there is not enough space left in the
   FLASH.
   -------------------------------------------------------------------------- */
int	fms_rai_nand_gc_init(int						item_num,  // number of items to make room for
												 int					  item_size, // average size of an item
												 fms_rai_GC_t * opaque);   // iterative GC context


/* --------------------------------------------------------------------------
   Garbage collector invokation

     The iterator must have been initialized with frai_gc_init(). Calling the
   function with an unitialized iterator will have unpredictable results.

     However, it is possible to use the FMS_RAI_GC_PREVENTIVE pseudo-iterator to
   perform preventive cleanup. In that case, the garbage collection will always
   succeed, and will reclaim only the sectors that contain a significant amount
   of garbage. The invokation should be done in a low-priority task to free up
   FLASH space in anticipation for other operations. It is advisable to couple
   this invokation with a call to frai_recycle().

     The garbage collection algorithm has been split into (relatively) fast
   steps to avoid blocking the caller for a potentially long time (more than 1
   second approximately).

     Therefore, the function is likely to take more than one invokation to
   complete.
     The FMS_RAI_GC_CONT return code signals that the garbage collection is still
   in progress and that the function has to be called again.
     The process is complete when the function returns either a FMS_RAI_GC_OK or
   FMS_RAI_GC_KO result.
     The KO result may occur when the actual remaining space in the FLASH is
   not sufficient to hold the requested number of items.
   -------------------------------------------------------------------------- */
int fms_rai_nand_gc(fms_rai_GC_t * opaque); // iterative GC context

#endif

#endif /* ! __FMS_RAI_H__ */

#endif	/*	!(defined(__NAND__) */

