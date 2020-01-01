/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkFile.h
 * Storage File Access JSI
 */
/**
 * @addtogroup Storage_File_Access_JSI
 * @{
 */

#ifndef ___FILE_JK_FILE_H
#define ___FILE_JK_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *  File handle type
 */
typedef JKHandle JKFileHandle;

/**
 *  File access mode:Read only (file access position at beginning)
 */
#define JK_FILE_R   0

/**
 *  File access mode:Write only (file access position at beginning)
 */
#define JK_FILE_W   1

/**
 *   File access mode:Read/write (file access position at beginning)
 */
#define JK_FILE_RW  2

/**
 *  The file access position is relative to the beginning of the file.
 */
#define JK_FILE_SEEK_SET    0

/**
 *  The file access position is relative to the current position.
 */
#define JK_FILE_SEEK_CUR    1

/**
 *  The file access position is relative to the end of the file.
 */
#define JK_FILE_SEEK_END    2

/**
 *  File kind: For record store management
 */
#define JK_FILE_RECORDSTORE 0

/**
 *  File kind: For index use
 */
#define JK_FILE_INDEX       1

/**
 *  File kind: For data storage use
 */
#define JK_FILE_DATA        2

/**
 *  Open a file.
 * @param name
 *   The name of the file used as the record store.<br>
 *   This is the name that was passed to JBlend by #JkFileGetNameBySuite().
 * @param namelen
 *   The length of the file name (number of characters)
 * @param mode
 *    File access mode. One of the following is designated.
 *   - #JK_FILE_R
 *   - #JK_FILE_W
 *   - #JK_FILE_RW
 *   .
 * @return
 *   If the operation succeeds, return a file handle indicating the opened 
 *   file. <br>
 *   In case of failure, return #JK_INVALID_HANDLE.
 *
 *  Open the file designated by name in the designated file access mode, and 
 *  return a file handle.<br>
 *  If there is no file of the designated name and the designated access mode 
 *  is #JK_FILE_W, create a new file.<br>
 *  In the native system, the file must not actually be created until 
 *  #JkFileOpen() is issued requesting that the file be opened. <br>
 *  If the designated file exists and #JK_FILE_W is designated as the file 
 *  access mode, discard the file contents.<br>
 *  If the designated file does not exist and #JK_FILE_R or #JK_FILE_RW is 
 *  designated as the file access mode, return #JK_INVALID_HANDLE indicating
 *  failure.
 * @see JkFileGetNameBySuite()
 * @see JkFileClose()
 */
JKFileHandle   JkFileOpen(JKWChar* name, JKSint16 namelen, JKSint8 mode);

/**
 *  Close a file.
 * @param fileHandle
 *   A file handle indicating the file to be closed (the value 
 * returned by  #JkFileOpen()).
 * @return 
 *   If the operation succeeds, return 0.<br>
 *   In case of failure, return a value other than 0.
 *
 *   Close the designated file. <br>
 *   Free the file space reserved for the designated file.
 * @see JkFileOpen()
 */
JKSint8    JkFileClose(JKFileHandle fileHandle);

/**
 *  Read data from a file.
 * @param fileHandle
 *   A file handle indicating the file to be read (the value
 *   returned by  #JkFileOpen()).
 * @param buffer
 *    A pointer to the buffer for storing the read data.
 * @param length 
 *   The number of bytes to be read.
 * @return
 *   If the operation succeeds, return the number of bytes read.<br>
 *   In case of failure, return a negative value.<br>
 *   If the file access position is EOF when this function is called, return 0.
 *
 *  Load the designated number of bytes of data from the designated file to a 
 *  buffer.<br>
 *  After reading, advance the file access position by the number of bytes 
 *  read.<br>
 * @see JkFileOpen()
 * @see JkFileWrite()
 */
JKSint32   JkFileRead(JKFileHandle fileHandle, void *buffer, JKSint32 length);

/**
 *  Write data to a file.
 * @param fileHandle
 *   A file handle indicating the file to be written (the value
 *   returned by  #JkFileOpen()).
 * @param buffer
 *   A pointer to the buffer holding the data to be written.
 * @param length
 *   The size of the data to be written (in bytes). 
 * @return
 *   If the operation succeeds, return 0.<br>
 *   If space is insufficient to write designated number of bytes, return -1
 *   indicating failure.<br>
 *   If the operation fails for other reasons, return -2.
 *
 *  Write to the designated file the designated number of bytes of data from 
 *  the buffer.<br>
 *  After writing, advance the file access position by the number of bytes 
 *  written.<br>
 *  Before writing, check whether there is enough space to write
 *  the designated number of bytes. And when space is insufficient,
 *  return -1 without writing anything. <br>
 * @see JkFileOpen()
 * @see JkFileRead()
 */
JKSint32   JkFileWrite(JKFileHandle fileHandle, const void *buffer, JKSint32 length);

/**
 *  Move the file access position.
 * @param fileHandle 
 *   The file handle of the file to be manipulated (the value returned by  
 *   #JkFileOpen())
 * @param offset 
 *   The offset from the origin from which the file access position is 
 *   calculated.
 * @param whence 
 *   The origin from which file access movement is calculated.
 *   One of the following is designated.
 *   -  #JK_FILE_SEEK_CUR
 *   -  #JK_FILE_SEEK_END
 *   -  #JK_FILE_SEEK_SET
 *   .
 * @return
 *   If the operation succeeds, return the file access position after 
 *   movement.<br>
 *   In case of failure, return a negative value.
 *
 *  Move the file access position of the designated file.<br>
 *  This should be done such that,<br>
 *    JkFileSeek(fileHandle, 0, JKT_File_Seek_SET) == 0<br>
 *    JkFileSeek(fileHandle, 0, JKT_File_Seek_END) == file size
 *
 *  <b>Note:</b><br>
 *  Movement of the file access position as designated by this function
 *  never goes beyond the EOF.
 * @see JkFileOpen()
 */
JKSint32   JkFileSeek(JKFileHandle fileHandle, JKSint32 offset, JKSint8 whence);

/**
 *  Reserve file space in persistent storage.
 * @param fileHandle 
 *   A file handle of the file to be manipulated (the value returned by  #JkFileOpen())
 * @param size
 *   The size of space to be reserved (in bytes). <br>
 *   This is the size of file space to be newly reserved, and is unrelated to 
 *   the file space size already in use or reserved.
 * @return 
 *   If the operation succeeds, return 0.<br>
 *   If space could not be reserved due to lack of space, return -1.<br>
 *   If the operation fails for other reasons, return -2.
 *
 *  Reserve the designated amount of file space in storage. <br>
 *  #JKwriteFile() will be used later to write to the space. <br>
 *  Guarantee that the file size can be increase by the reserved amount at the
 *  time of writing to the file. Even if the same storage is used by a system 
 *  other than JBlend, guarantee that the file size can be increased by 
 *  the amount reserved by this function.<br>
 *  
 *  This function is called once for each kind of record store file (i.e., for 
 *  record store management, index, and data storage files), during the 
 *  interval after #JkFileBeginCommit() has been called and until 
 *  #JkFileEndCommit() is called. Note that there may be some cases in which it 
 *  is not called.
 * 
 *  The file space reserved by #JkFileReserveSpace() must be retained until
 *  #JkFileEndCommit() is called. 
 *  The reserved file space may be discarded after #JkFileEndCommit() has
 *  been called.
 * 
 *  This function is called when JBlend determines that space must be reserved.<br>
 *  Since it will not necessarily be called before every write operation, do not
 *  implement #JkFileWrite() on the assumption that #JkFileReserveSpace() will be called.
 * @see JkFileBeginCommit()
 * @see JkFileEndCommit()
 * @see JkFileWrite()
 * @see JkFileFreeSpace()
 */
JKSint32   JkFileReserveSpace(JKFileHandle fileHandle, JKSint32 size);

/**
 *  Free reserved file space.
 * @param fileHandle 
 *   A file handle of the file to be manipulated (the value returned by  #JkFileOpen())
 * @param size
 *   The size (0 or above) of the space to be freed, given in bytes.
 *
 *  Free the designated amount of space reserved for file use by 
 *  #JkFileReserveSpace().<br>
 *  The reserved file space will all be used by #JkFileWrite almost immediately 
 *  thereafter.
 *  This function is called when a reserved file space was not used for file 
 *  expansion by #JkFileWrite(), such as when an error occurred before  
 *  #JkFileWrite() was called.<br>
 *  If the amount of space that can be freed is less than the designated size, 
 *  free the amount possible. In this case the reserved space size becomes 0.<br>
 *  <br>
 *  <b>Notes:</b><br>
 *  <ul>
 *  <li>If the file space reserved by #JkFileReserveSpace() is not freed when 
 *  the Java application terminates, it must be freed by the native system.<br>
 *  <li>In the case of an RTOS that manages storage in block units, blocks are 
 *  allocated by #JkFileReserveSpace().
 *  Blocks are not taken into account when JBlend calls #JkFileFreeSpace(),
 *  so when a block is no longer needed the native system must free it.
 *  </ul>     
 * @see JkFileReserveSpace()
 */
void       JkFileFreeSpace(JKFileHandle fileHandle, JKSint32 size);

/**
  *  Truncates a file to the designated size.
 *  
 *  @param fileHandle 
 *   The handle of the file to be truncated (the value returned by #JkFileOpen())<br>
 *  @param size 
 *   The length (in bytes) of the file after truncation. A value greater than zero
 *   and less than the file size before truncation is designated in this parameter.<br>
 *  @return
 *   If the operation succeeds, return 0.<br>
 *   If the operation fails, return -1 after restoring the file to the state 
 *   before this function was called.<br>
 *   If restoration is not possible, return -2.<br>
 * 
 *  Truncate the size of the designated file to the size designated in the <i>size</i>
 *  parameter. 
 *  After truncating, delete the data at the end of the file. 
 *  
 *  After this function is called, JBlend calls #JkFileSeek() designating the file
 *  access position before reading and writing data. It therefore does not matter
 *  where the file access position is located right after this function is called.
 *
 *  This function is called after record deletion by JBlend or when unused space 
 *  occurs at the end of a file as a result of optimization by #AMRmsOptimize(). <br>
 *  Regardless of whether this function succeeds or fails, do not change the size of 
 *  file space that has been reserved by #JkFileReserveSpace(). 
 */
JKSint8       JkFileTruncate(JKFileHandle fileHandle, JKSint32 size);

/**
 *  Return the size available to use for file space.
 * @param vendor
 *   A pointer to the memory area containing the vendor name
 * @param vendorlen
 *   The number of characters in the vendor name (string designated in the <i>vendor</i> parameter)
 * @param suite
 *   A pointer to the memory area containing the MIDlet suite name
 * @param suitelen
 *   The number of characters in the MIDlet suite name (string designated in the <i>suite</i> parameter) 
 * @return
 *   Return the size (0 or above) of available space.
 *
 *  Return the file space size available for recored store file use at the time 
 *  this function is called. It is not necessary to guarantee that this amount 
 *  of space can be written to.<br>
 *  Do not include the size of space currently used or that reserved by 
 *  #JkFileReserveSpace().
 * @see JkFileFreeSpace()
 */
JKSint32   JkFileGetAvailSize(const JKWChar* const vendor, const JKSint16 vendorlen,
                              const JKWChar* const suite, const JKSint16 suitelen);

/**
 *  Get the name of the file used for the record store.
 * @param vendor
 *   A pointer to the memory area containing the vendor name
 * @param vendorlen
 *   The number of characters in the vendor name (string designated in the <i>vendor</i> parameter)
 * @param suite
 *   A pointer to the memory area containing the MIDlet suite name
 * @param suitelen
 *   The number of characters in the MIDlet suite name (string designated in the <i>suite</i> parameter) 
 * @param kind
 *   Kind of file. One of the following is designated.
 *   -  #JK_FILE_RECORDSTORE
 *   -  #JK_FILE_INDEX
 *   -  #JK_FILE_DATA
 *   .
 * @param filename 
 *   A pointer to the buffer for storing the obtained file name.
 *   If a value other than #JK_NULL is designated, put the file 
 *   name in the buffer indicated by this pointer. 
 * @return
 *   If the parameter <i>filename</i> is #JK_NULL:<br>
 *   Return the number of characters of the file name if successful. 
 *   In case of failure, return a negative value.<br>
 *   If the parameter <i>filename</i> is not #JK_NULL:<br>
 *   Return 0 if successful. In case of failure (wrong file type, etc.), return 
 *   a negative value.<br>
 *
 *  Return the record store file name for the designated vendor name, MIDlet 
 *  suite name and file type. The file name obtained by this function is used 
 *  when opening the file by calling #JkFileOpen(). 
 *
 *  This function is called twice when JBlend accesses the record store.
 *<dl>
 *<dt>1st time
 *  <dd>JBlend calls this function to get the length of the file name string. 
 *  After calling this function, JBlend allocates a buffer of the length returned
 *  as the return value.
 *  The first time this function is called, #JK_NULL is set in the <i>filename</i> parameter.
 *  <dt>2nd time<br>
 *  <dd>JBlend calls this function designating a pointer to the allocated buffer in the
 *  <i>filename</i> parameter.
 *  In the native system, put the requested file name in the buffer indicated by this pointer. 
 *  The string must not be longer than the value returned the first time this function was called. 
 *  Do not append '@\0' or other string termination.
 *</dl>
 *  The file name returned by this function must be unique with respect to the 
 *  three keys Vendor name, Suite name and File type.
 * @see JkFileOpen()
 */
JKSint32 JkFileGetNameBySuite(const JKWChar* const vendor, JKSint16 vendorlen,
                              const JKWChar* const suite, JKSint16 suitelen,
                              JKSint8 kind, JKWChar* const filename);

/**
 *  Notifies the start of a record store write operation. 
 *  
 *  @param vendor
 *   A pointer to the memory area containing the vendor name
 *  @param vendorlen
 *   The number of characters in the vendor name (string designated in the <i>vendor</i> parameter)
 *  @param suite
 *   A pointer to the memory area containing the MIDlet suite name
 *  @param suitelen
 *   The number of characters in the MIDlet suite name (string designated in the <i>suite</i> parameter) 
 * 
 *  This function is called before the <code>javax.microedition.RecordStore
 * </code> class method that performs record store writing starts 
 * its processing. 
 *
 *  When write processing is complete, #JkFileEndCommit() is called designating
 *  the same MIDlet suite name as that passed to #JkFileBeginCommit().
 *  #JkFileBeginCommit() and #JkFileEndCommit() are called as a pair for the
 *  same MIDlet suite name. In no case is #JkFileBeginCommit() called 
 *  successively for the same MIDlet suite name.
 *  #JkFileEndCommit() is called even if writing did not take
 *  place due to an error.
 *
 *  In case the JVM terminates abnormally or is terminated by #AamsVmKill() after 
 *  #JkFileBeginCommit() is called but before #JkFileEndCommit() is called,
 *  the integrity of the record store data structure may be compromised. In the 
 *  native system, handle such cases as necessary, such as by discarding the 
 *  record store files of the designated MIDlet suite or by restoring from a
 *  backup copy. 
 * 
 * @see JkFileEndCommit()
 */
void JkFileBeginCommit(const JKWChar* const vendor, JKSint16 vendorlen,
                       const JKWChar* const suite, JKSint16 suitelen);

/**
 *  Notifies the end of a record store write operation.
 *
 *  @param vendor
 *   A pointer to the memory area containing the vendor name
 *  @param vendorlen
 *   The number of characters in the vendor name (string designated in the <i>vendor</i> parameter)
 *  @param suite
 *   A pointer to the memory area containing the MIDlet suite name
 *  @param suitelen
 *   The number of characters in the MIDlet suite name (string designated in the <i>suite</i> parameter) 
 *
 * The calling of #JkFileEndCommit() is always paired with #JkFileBeginCommit().
 * See the description of #JkFileBeginCommit() for details. 
 * @see JkFileBeginCommit()
 */
void JkFileEndCommit(const JKWChar* const vendor, JKSint16 vendorlen,
                     const JKWChar* const suite, JKSint16 suitelen);

/**
 * Gets the data size for one read action.
 * @return
 *   Return the size (in bytes) of data to be read from a file at one time. <br>
 *   Return a negative value if data is to be read in record units. <br>
 *   Return 0 if data may be read in the default unit size (1024 bytes). 
 *
 * Return a value that is a suitable size for reading data from a record store
 * file at one time. 
 * 
 * When JBlend calls #JkFileRead() to read from a record store file, reading takes place 
 * in units of the size returned by this function. 
 * 
 * If data is read in large chunks, the time required for a read operation, during which 
 * control of the JVM is not possible, will be correspondingly long. This function 
 * offers a means for avoiding this problem by designating a suitably small read size. 
 * If an appropriate size is notified to JBlend by #JkFileGetPreferredReadSize(),
 * control of the JVM can take place promptly when a function for JVM control (e.g., 
 * #AamsVmSuspend() or #AamsVmStop()) is called during data read. On the other hand,
 * setting the read size too small with this function increases the number of times 
 * #JkFileRead() is called, which can adversely affect performance.
 * 
 * This function is called once only, after the JVM is started and before a Java 
 * application first reads from a record store. In no case is it called more than
 * once while the JVM is running.
 * When this function is called, return a value as appropriate for the situation
 * at the time. For example, return a smaller value if the storage file is located 
 * on a slow medium.
 * 
 * The specification allowing a negative value to be returned is for the sake of
 * compatibility with specifications before #JkFileGetPreferredReadSize() was added.
 * Return a negative value in order to achieve the same behavior as before the 
 * #JkFileGetPreferredReadSize() function was added, assuming such behavior is 
 * acceptable. 
 * 
 */
JKSint32 JkFileGetPreferredReadSize(void);


/**
 * Gets the data size for one write action.
 *
 * @return
 *   Return the size (in bytes) of data to be written to a file at one time. <br>
 *   Return a negative value if data is to be written in record units. <br>
 *   Return 0 if data may be written in the default unit size (1024 bytes). 
 *
 * Return a value that is a suitable size for writing data to a record store 
 * file at one time. 
 * 
 * When JBlend calls #JkFileWrite() to write to a record store file, writing takes 
 * place in units of the size returned by this function.
 * 
 * If data is written in large chunks, the time required for a write operation, during 
 * which control of the JVM is not possible, will be correspondingly long.  
 * This function offers a means for avoiding this problem by designating a suitably 
 * small write size. 
 * If an appropriate size is notified to JBlend by #JkFileGetPreferredWriteSize(),
 * control of the JVM can take place promptly when a function for JVM control is called 
 * during a data write operation. 
 * 
 * This function is called once only, after the JVM is started and before a Java 
 * application first writes to a record store. 
 * In no case is it called more than once while the JVM is running.
 * When this function is called, return a value as appropriate for the situation
 * at the time. For example, return a smaller value if the storage file is located 
 * on a slow medium.
 * 
 * The specification allowing a negative value to be returned is for the sake of
 * compatibility with specifications before #JkFileGetPreferredWriteSize() was added.
 * Return a negative value in order to achieve the same behavior as before the 
 * #JkFileGetPreferredWriteSize() function was added, assuming such behavior is 
 * acceptable. 
 * 
 */
JKSint32 JkFileGetPreferredWriteSize(void);


#ifdef __cplusplus
}
#endif

#endif /* ___FILE_JK_FILE_H */

/** @} end of group */
