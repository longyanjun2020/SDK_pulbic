/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */
/**
 * @file JkFileConnectionStream.h
 *   FileConnection Stream JSI
 */
/**
 * @addtogroup Module_FileConnection_Stream_JSI
 * @{
 */

#ifndef ___JK_FILECONNECTION_STREAM_H
#define ___JK_FILECONNECTION_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "JkFileConnectionCommon.h"


/**
 *
 * Opens a byte input stream.
 *
 * @param *connection
 *	A pointer to the structure holding information about the file connection.
 * @param *id
 *	A pointer to the buffer for putting the stream ID.
 * @param *markSupported
 *	A pointer to the buffer for indicating whether functionality
 *	corresponding to the <code>InputStream</code> class <code>mark</code>
 *	and <code>reset</code> methods is supported.
 *	Put #JK_TRUE if the functionality is supported, else #JK_FALSE.
 * @return
 *	Return one of the following error codes.
 *	- #JK_FILECONNECTION_SUCCESS: <br>
 *     The function succeeded.
 *	- #JK_FILECONNECTION_MEMORY_ERR: <br>
 *     The function failed because of insufficient memory.
 *	- #JK_FILECONNECTION_SECURITY_ERR: <br>
 *     The function failed because the application was denied read access to the file.
 *	- #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *     The function failed because the connection was opened for write access.
 *	- #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *     The function failed because the file does not exist or is not accessible.
 *	- #JK_FILECONNECTION_IO_ERR: <br>
 *     The function failed because of an I/O error.
 *  .
 *
 * Open a byte input stream, and put a stream ID identifying the stream in the buffer designated by <i>id</i>. 
 * The stream ID value must be unique. 
 * The stream ID is designated when requesting stream operations after this function is called. 
 * 
 * Set the file access position to the beginning of the file. 
 * 
 * In no case are multiple input streams open concurrently on a connection to the
 * same file. 
 * But an input stream and an output stream must be able to be opened concurrently for a connection.
 * The file access position must be maintained in each stream.
 * 
 * If the connection is to a directory, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionOpenByteInputStream(JKFileConnectionConnectionInfo* connection,JKSint32* id,JKBool* markSupported);


/**
 * Reads data from a byte input stream.
 * 
 * @param taskId
 *        The task ID.
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() is designated.
 * @param buffer 
 *        A pointer to the buffer for putting the read data. 
 * @param length 
 *        A pointer to the memory location containing the read buffer size (in bytes).
 *        After the read operation is completed, put the size of actually read data in this buffer. 
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_ASYNC_FUNCTION: <br>
 *            The processing of this function was started asynchronously.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *         - #JK_FILECONNECTION_EOF: <br>
 *            The end of the stream was reached.
 *         .
 * 
 * The pointer designated in the <i>buffer</i> parameter is valid only until 
 * this function returns, or until an asynchronous processing result is 
 * notified if this function executes its processing asynchronously.
 * 
 * The pointer designated in the <i>length</i> parameter is valid only until
 * this function returns. 
 * If the function executes asynchronously, this pointer is not used for storage.
 * 
 * Advance the file access position by the number of read bytes. 
 * 
 * The function processing can be executed asynchronously. To do so, pass 
 * #JK_FILECONNECTION_ASYNC_FUNCTION in the return code for this function. 
 * Also AmNotifyFileConnectionAsyncFunctionEvent() must be called as soon 
 * as the asynchronous processing is completed, in order to notify JBlend of 
 * the processing result by an event. The event format is as follows. 
 * <ul>
 * <li> event[0]: Task ID. The value designated in the <i>taskId</i> parameter of this function.
 * <li> event[1]: One of the following error codes.
 *   <ul>
 *     <li> #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *     <li> #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *     <li> #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *     <li> #JK_FILECONNECTION_INTERRUPTED_ERR: <br>
 *            Processing was interrupted (stream closing was requested during processing)
 *     <li> #JK_FILECONNECTION_EOF: <br>
 *            The end of the stream was reached.
 *   </ul>
 * <li> event[2]: The size (in bytes) of actually read data
 * </ul>
 * 
 * When this function is implemented to perform the requested processing asynchronously, it is
 * possible that this function will be called again while processing is executing in another
 * task. The stream that is processed in the subsequent function calls may be the same as or 
 * different from the one passed in the current call.
 */
JKFileConnectionErr JkFileConnectionReadBytes(JKSint32 taskId,JKSint32 id,JKSint8* buffer,JKSint32* length);


/**
 * Closes a byte input stream.
 * 
 * @param id 
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() is designated.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 * 
 * Close the byte input stream designated by <i>id</i> and free resources 
 * associated with the stream. 
 * 
 * If other processing is being executed asynchronously on this byte input stream, either
 * complete that processing immediately or interrupt that processing. 
 */
JKFileConnectionErr JkFileConnectionCloseByteInputStream(JKSint32 id);


/**
 * Skips over data in a byte stream.
 * 
 * @param taskId
 *        The task ID.
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() is designated.
 * @param length
 *        A pointer to the buffer for putting the number of bytes to be skipped over.  
 *        After the processing is completed, store in this buffer the number of bytes actually skipped over.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_ASYNC_FUNCTION: <br>
 *            The processing of this function was started asynchronously.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *         .
 * 
 * Advance the file access position by the number of skipped bytes. 
 * 
 * The pointer designated in the <i>length</i> parameter is valid only until this function 
 * returns. If the function executes asynchronously, this pointer is not used for storage.
 * 
 * The function processing can be executed asynchronously. To do so, pass 
 * #JK_FILECONNECTION_ASYNC_FUNCTION in the return code for this function. 
 * Also AmNotifyFileConnectionAsyncFunctionEvent() must be called as soon 
 * as the asynchronous processing is completed, in order to notify JBlend of 
 * the processing result by an event. The event format is as follows. 
 * <ul>
 * <li> event[0]: Task ID. The value designated in the <i>taskId</i> parameter of this function.
 * <li> event[1]: One of the following error codes.
 *   <ul>
 *     <li> #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *     <li> #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *     <li> #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *     <li> #JK_FILECONNECTION_INTERRUPTED_ERR: <br>
 *            Processing was interrupted (stream closing was requested during processing)
 *   </ul>
   * <li> event[2]: The high 32 bits of the byte length (a 64-bit signed integer) of the data actually skipped.
   * <li> event[3]: The low 32 bits of the byte length (a 64-bit signed integer) of the data actually skipped.
 * </ul>
 * 
 * When this function is implemented to perform the requested processing asynchronously, it is
 * possible that this function will be called again while processing is executing in another
 * task. The stream that is processed in the subsequent function calls may be the same as or 
 * different from the one passed in the current call.
 */
JKFileConnectionErr JkFileConnectionSkipBytes(JKSint32 taskId,JKSint32 id,JKFileConnectionLong* length);


/**
 * 
 * Opens a byte output stream.
 *
 * @param *connection
 *	A pointer to the structure holding information about the file connection.
 * @param *id
 *	A pointer to the buffer for putting the stream ID.
 * @return
 *	Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access to the file.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 *         - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file does not exist or is not accessible.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *         .
 *
 * Open a byte output stream, and put a stream ID identifying the stream in the buffer designated by <i>id</i>. 
 * The stream ID value must be unique within the scope of the file connection. 
 * The stream ID is designated when requesting stream operations after this function is called. 
 * 
 * Set the file access position to the beginning of the file.
 * 
 * In no case are multiple output streams open concurrently on a connection to the
 * same file.
 * But an input stream and an output stream must be able to be opened concurrently for a connection.
 * The file access position must be maintained in each stream.
 *
 * If the connection is to a directory, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionOpenByteOutputStream(JKFileConnectionConnectionInfo* connection,JKSint32* id);


/**
 * 
 * Opens a byte output stream and sets the file access position.
 *
 * @param connection
 *	A pointer to the structure holding information about the file connection.
 * @param offset
 *	The offset value (in bytes) from the beginning of the file.
 * @param id
 *	A pointer to the buffer for putting the stream ID.
 * @return
 *	       Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_SECURITY_ERR: <br>
 *            The function failed because the application was denied write access 
 *            to the file.
 *         - #JK_FILECONNECTION_ILLEGAL_ACCESS_ERR: <br>
 *            The function failed because the connection was opened for read access.
 *         - #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR: <br>
 *            The function failed because the file does not exist or is not accessible.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of an I/O error.
 *  .
 *
 * Open a byte output stream, and put a stream ID identifying the stream in the buffer designated by <i>id</i>. 
 * The stream ID value must be unique. 
 * The stream ID is designated when requesting stream operations after this function is called. 
 * 
 * Advance the file access position by the number of bytes designated in the
 * offset parameter from the beginning of the file. 
 * If the designated offset is larger than the file size, set the access position
 * to the end of the file. 
 * 
 * In no case are multiple output streams open concurrently on a connection to the
 * same file. 
 * But an input stream and an output stream must be able to be opened concurrently for a connection.
 * The file access position must be maintained in each stream.
 *
 * If the connection is to a directory, return #JK_FILECONNECTION_TARGET_NOT_EXIST_ERR.
 */
JKFileConnectionErr JkFileConnectionOpenByteOutputStreamWithOffset(JKFileConnectionConnectionInfo* connection,JKFileConnectionLong* offset,JKSint32* id);


/**
 * Writes data to a byte output stream. 
 * 
 * @param taskId
 *        The task ID.
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() or 
 *        JkFileConnectionOpenByteOutputStreamWithOffset() is designated.
 * @param buffer
 *        A pointer to the structure holding the data to write. 
 * @param length
 *        A pointer to the memory area containing the write buffer size (in bytes).
 *        After the write operation is completed, put the size of actually written data in this buffer. 
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_ASYNC_FUNCTION: <br>
 *            The processing of this function was started asynchronously.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *         .
 * 
 * Advance the file access position by the number of written bytes. 
 * 
 * The pointer designated in the <i>buffer</i> parameter is valid only until 
 * this function returns, or until an asynchronous processing result is 
 * notified if this function executes its processing asynchronously.
 * 
 * The pointer designated in the <i>length</i> parameter is valid only until
 *  this function returns. If the function executes asynchronously, 
 * this pointer is not used for storage.
 * 
 * The function processing can be executed asynchronously. To do so, pass 
 * #JK_FILECONNECTION_ASYNC_FUNCTION in the return code for this function. 
 * Also AmNotifyFileConnectionAsyncFunctionEvent() must be called as soon 
 * as the asynchronous processing is completed, in order to notify JBlend of 
 * the processing result by an event. The event format is as follows. 
 * <ul>
 * <li> event[0]: Task ID. The value designated in the <i>taskId</i> parameter of this function.
 * <li> event[1]: One of the following error codes.
 *   <ul>
 *     <li> #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *     <li> #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *     <li> #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *     <li> #JK_FILECONNECTION_INTERRUPTED_ERR: <br>
 *            Processing was interrupted (stream closing was requested during processing)
 *   </ul>
 * <li> event[2]: The size (in bytes) of actually write data
 * </ul>
 * 
 * When this function is implemented to perform the requested processing asynchronously, it is
 * possible that this function will be called again while processing is executing in another
 * task. It is also possible that this function will be called again while processing is executing
 * in another task for the same stream.
 */
JKFileConnectionErr JkFileConnectionWriteBytes(JKSint32 taskId,JKSint32 id,JKSint8* buffer,JKSint32* length);


/**
 * Closes a byte output stream.
 * 
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() or 
 *        JkFileConnectionOpenByteOutputStreamWithOffset() is designated.
 * @return
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *         .
 * 
 * Flush the write buffer of the byte output stream designated by <i>id</i>, 
 * close the byte output stream and free its associated resources.
 * 
 * If other processing is being executed asynchronously on this byte output stream, either
 * complete that processing immediately or interrupt that processing. 
 */
JKFileConnectionErr JkFileConnectionCloseByteOutputStream(JKSint32 id);


/**
 * Flushes the write buffer of a byte output stream.
 * 
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteOutputStream() or 
 *        JkFileConnectionOpenByteOutputStreamWithOffset() is designated.
 * @return
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The processing of this function was started asynchronously.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *         .
 */
JKFileConnectionErr JkFileConnectionFlushByteOutputStream(JKSint32 id);


/**
 * Gets the number of bytes that can be read or skipped from a byte input stream. 
 * 
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() is designated.
 * @param size 
 *        A pointer to the buffer for putting the number of bytes that can be read or skipped
 * @return
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of I/O error.
 *         .
 * 
 * Return the number of bytes that can be read or skipped from the indicated 
 * stream without blocking when the native system may block subsequent JSI 
 * function call for the same stream. If there is no possibility of blocking, 
 * return the number of bytes from the current file access position to the end 
 * of the file. 
 */
JKFileConnectionErr JkFileConnectionGetAvailableSize(JKSint32 id,JKSint32* size);


/**
 * Sets a mark at the current access position in a byte input stream. 
 * 
 * @param id
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() is designated.
 * @param readlimit
 *        The maximum limit of bytes that can be read before the mark position 
 *        becomes invalid.
 * @return
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_GENERAL_ERR: <br>
 *            The function failed because of other errors.
 *         .
 * 
 * If #JK_FALSE is set in the buffer indicated by the <i>markSupported</i> parameter 
 * passed to JkFileConnectionOpenByteInputStream(), this function cannot is never called.
 *
 * The native system must mark the current position in the input stream.
 * When JkFileConnectionResetByteInputStream() is called hereafter, the 
 * access position must be set back to the position marked by this function.
 * The native system may invalidate the mark when more than 
 * <i>readlimit</i> bytes are read or skipped from the current position.
 */
JKFileConnectionErr JkFileConnectionMarkByteInputStream(JKSint32 id,JKSint32 readlimit);


/**
 * Restores the access position to the last set mark in a byte input stream. 
 * 
 * @param id 
 *        The stream ID.
 *        The ID returned by JkFileConnectionOpenByteInputStream() is designated.
 * @return 
 *         Return one of the following error codes.
 *         - #JK_FILECONNECTION_SUCCESS: <br>
 *            The function succeeded.
 *         - #JK_FILECONNECTION_MEMORY_ERR: <br>
 *            The function failed because of insufficient memory.
 *         - #JK_FILECONNECTION_IO_ERR: <br>
 *            The function failed because of this stream has not been marked 
 *            or the mark has been invalidated.
 *         .
 * 
 * If #JK_FALSE is set in the buffer indicated by the <i>markSupported</i> parameter 
 * passed to JkFileConnectionOpenByteInputStream(), this function is never called.
 */
JKFileConnectionErr JkFileConnectionResetByteInputStream(JKSint32 id);



#ifdef __cplusplus
}
#endif

#endif /* ___JK_FILECONNECTION_STREAM_H */

/**
 * @} end of group
 */
