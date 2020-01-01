/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

#include "JkTypes.h"

/**
 * @file AMRms.h
 *   RMS Maintenance JBI
 */
/**
 * @addtogroup RMS_Maintenance_JBI
 * @{
 */

#ifndef ___AMRMS_H
#define ___AMRMS_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 *  Function return code: Succeeded.
 */
#define AM_RMS_RETCODE_SUCCESS			(0)

/**
 *  Function return code: Optimization is discontinued.
 */
#define AM_RMS_RETCODE_ERROR_SAFE		(-1)

/**
 *  Function return code: Optimization was not possible due to insufficient memory.
 */
#define AM_RMS_RETCODE_ERROR_MEMORY		(-2)

/**
 *  Function return code: Optimization was terminated by error.
 */
#define AM_RMS_RETCODE_ERROR_CRITICAL	(-3)


/**
 *  Gets the total size of unused space in a record store file.
 *
 *  @param heapAddress
 *   The pointer to the work memory region. 
 *   It is assumed that the Java heap area used when JBlend is executed is
 *   specified. 
 *  @param heapSize
 *   The number of bytes of the work memory region.
 *  @param vendor
 *   A pointer to the memory area containing the vendor name
 *  @param vendorlen
 *   The number of characters in the vendor name (string designated 
 *   in the vendor parameter)
 *  @param suite
 *   A pointer to the memory area containing the MIDlet suite name.
 *  @param suitelen
 *   The number of characters in the MIDlet suite name (string designated in the
 *   suite parameter).
 *  @return
 *   A value of 0 or more: The total size of the unused area. (Succeeded)<br>
 *   A negative value: Operation failed. Either of the following is returned.<br>
 *   - #AM_RMS_RETCODE_ERROR_SAFE<br>
 *   - #AM_RMS_RETCODE_ERROR_MEMORY
 *   .
 *
 *  This function gets the size of unused space in the record store file used by the designated 
 *  MIDlet suite. 
 *
 *  Three record store files are created for each MIDlet suite; this function
 *  gets the total size of unused space in all the files used by the designated MIDlet
 *  suite.
 *  The value obtained by this function is used in deciding whether to call the file 
 *  optimizing service function #AmRmsOptimize().
 *  
 *  This function can be called when the following two conditions are met.
 *  <ul>
 *   <li> Before calling #AamsVmStartMIDP(), or
 *    after returning from #AamsVmStartMIDP().
 *   <li> The work memory region specified for the argument is not used for other
 *    usages. 
 *  </ul>
 *  Since this function makes use of @ref Storage_File_Access_JSI , it can be used 
 *  only if @ref Storage_File_Access_JSI has been implemented.
 *
 *  The necessary size of the memory area indicated by the <i>heapAddress</i>
 *  parameter is the file name length in bytes of the #JK_FILE_RECORDSTORE-kind file.
 *
 */
JKSint32 AmRmsGetGarbageSize(void *heapAddress, int heapSize,
                             const JKWChar *vendor, JKSint16 vendorlen,
                             const JKWChar *suite, JKSint16 suitelen);

/**
 *  Optimizes a record store file.
 *
 *  @param heapAddress
 *   The pointer to the work memory region. 
 *   It is assumed that the Java heap area used when JBlend is executed is
 *   specified. 
 *  @param heapSize
 *   The number of bytes of the work memory region.
 *  @param vendor
 *   A pointer to the memory area containing the vendor name
 *  @param vendorlen
 *   The number of characters in the vendor name (string designated in the vendor 
 *   parameter)
 *  @param suite
 *   A pointer to the memory area containing the MIDlet suite name
 *  @param suitelen
 *   The number of characters in the MIDlet suite name (string designated in the
 *   suite parameter)
 *  @return
 *   #AM_RMS_RETCODE_SUCCESS: Succeeded<br>
 *   A negative value: Operation failed. One of the following is returned.
 *   - #AM_RMS_RETCODE_ERROR_SAFE
 *   - #AM_RMS_RETCODE_ERROR_MEMORY
 *   - #AM_RMS_RETCODE_ERROR_CRITICAL
 *   .
 *   If #AM_RMS_RETCODE_ERROR_CRITICAL is returned, there is a possibility 
 *   that the RMS data structure is broken.
 *   In this case, take countermeasures such as deleting RMS files or 
 *   restoring them from the backup files.
 *
 *  This function optimizes the record store files used by the designated MIDlet suite.
 *  Three record store files are created for each MIDlet suite; this function
 *  deletes the unused space in all the files used by the designated MIDlet suite.
 *  
 *  This function can be called when the following two conditions are met.
 *  <ul>
 *   <li> Before calling #AamsVmStartMIDP(), or
 *    after returning from #AamsVmStartMIDP().
 *   <li> The work memory region specified for the argument is not used for other
 *    usages. 
 *  </ul>
 *  Since this function makes use of @ref Storage_File_Access_JSI , it can be used 
 *  only if @ref Storage_File_Access_JSI  has been implemented.
 *
 *  The necessary size of the memory area indicated by the <i>heapAddress</i>
 *  parameter is as follows.
 *  @htmlonly<blockquote>@endhtmlonly
 *  <dl>
 *   <p><dt><b> For faster optimization </b><br>
 *   <dd> The total size of the three kind of RMS files.
 *   <p><dt><b> For optimization with less memory </b><br>
 *   <dd> The sum of record store management file ( #JK_FILE_RECORDSTORE ) size
 *        and index file ( #JK_FILE_INDEX ) size + work memory size<br>
 *        <br>
 *        A minimum of 1 byte is required for the work memory.
 *        Note that, if the size of work memory is too small, 
 *        the number of function calls of JkFileSeek(), JkFileRead(), and JkFileWrite() 
 *        increases considerably, thus taking excessive time.
 *  </dl>
 *  @htmlonly</blockquote>@endhtmlonly
 *  If, however, a file name length in bytes of the three kind of RMS files is
 *  greater than the two sizes listed above, that name length is the 
 *  necessary size.
 */
JKSint32 AmRmsOptimize(void *heapAddress, int heapSize,
                       const JKWChar *vendor, JKSint16 vendorlen,
                       const JKWChar *suite, JKSint16 suitelen);
#ifdef __cplusplus
}
#endif
#endif

/**
 * @}
 */
