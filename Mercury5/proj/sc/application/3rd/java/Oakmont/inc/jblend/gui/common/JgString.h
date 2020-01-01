/*
 * Copyright 2002 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 * API functions for GUI Toolkit character string operations.
 */

#ifndef ___GUI_COMMON_STRING_H
#define ___GUI_COMMON_STRING_H

#include <JkTypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @addtogroup GUI_String
 * @{
 */

/**
 * The string handle
 * 
 * A string handle is data identifying the string.
 */
typedef JKHandle    JGString;

/**
 * Creates a character string.
 * 
 * @param text
 *        The character string. It does not have to be null ('\0') terminated.
 *        If #JK_NULL is designated, it is handled as a string of length 0.
 * @param length
 *        The number of elements in the character string (not the byte size).
 * 
 * @return
 *        If creation succeeds, the string handle is returned. In case of a 
 *        memory shortage, #JK_INVALID_HANDLE is returned.
 * 
 * <p>
 * The character string designated in the text parameter is processed up to the 
 * number of characters in the length parameter, even if it contains null 
 * termination ('\0').
 * The string will be an uneditable character string.
 * </p>
 * <p>
 * In the following cases @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When length is negative.</li>
 * <li>When text is JK_NULL and length is not 0.</li>
 * </ul>
 * </p>
 */
JGString JgStringCreate(const JKWChar text[], JKSint32 length);

/**
 * Deletes a string.
 * 
 * @param string
 *        The string handle. Designate the value returned by JgStringCreate().
 * 
 * In the following cases @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When the string handle is locked.</li>
 * <li>When string is an illegal handle.</li>
 * @if DOJA_OE_RTL
 * <li>When the embedding levels array of the string is locked</li>
 * @endif
 * </ul>
 */
void JgStringDelete(JGString string);

/**
 * Locks the string handle and gets the character string.
 * 
 * @param string
 *        The string handle. Designate the value returned by JgStringCreate().
 * 
 * @return
 *        The character string is returned. It is not null ('\0') terminated.
 * 
 * <p>
 * When using a string text, use this function to lock the string handle.<br>
 * Be sure to unlock the string handle, using JgStringUnlock(), when it is no 
 * longer in use. If a string handle remains locked, memory can become 
 * fragmented or run short. 
 * A record is kept of the lock count in a lock counter, and if a string is 
 * locked multiple times it must be unlocked the same number of times.
 * </p>
 * <p>
 * In the following cases @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When string is an illegal handle.</li>
 * <li>When the lock counter (unsigned 32-bit) overflows</li>
 * </ul>
 * </p>
 */
const JKWChar *JgStringLock(JGString string);

/**
 * Unlocks a string handle.
 * 
 * @param string
 *        The string handle. Designate the value returned by JgStringCreate().
 * 
 * When use of the character string ends, be sure to use this function to 
 * unlock the string handle that was called.
 * An unlocked character string cannot be used. The behavior when trying to
 * use a character string after it is unlocked cannot be guaranteed.

 * In the following cases @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When string is an illegal handle.</li>
 * <li>When the string handle was not locked.</li>
 * </ul>
 */
void JgStringUnlock(JGString string);

/**
 * Gets the string length from the string handle.
 * 
 * @param string
 *        The string handle. Designate the value returned by JgStringCreate().
 * 
 * @return
 *        The number of string elements is returned (not the byte size).
 * 
 * In the following case @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When string is an illegal handle.</li>
 * </ul>
 */
JKSint32 JgStringGetLength(JGString string);


/** @} */

/**
 * @addtogroup GUI_StringBuffer
 * @{
 */

/**
 * The string buffer handle.
 * 
 * A string buffer handle is data identifying the string buffer.
 * The string buffer handle can be used as a string handle.
 * 
 * @see JGString
 */
typedef JGString    JGStrBuf;

/**
 * Creates a string buffer.
 * 
 * @param length
 *        The maximum number of string buffer elements is returned
 *        (not the byte size).
 * 
 * @return
 *        When the string buffer creation succeeded, the string buffer handle 
 *        is returned; if memory is short, JK_INVALID_HANDLE is returned.
 * 
 * <p>
 * The string buffer is created as an editable character string.
 * The created string buffer is deleted using #JgStringDelete.
 * </p>
 * <p>
 * In the following case @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When length is a negative value.</li>
 * </ul>
 * </p>
 */
JGStrBuf JgStrBufCreate(JKSint32 length);

/**
 * Gets the string buffer length from the string buffer handle.
 * 
 * @param strbuf
 *        The string buffer handle. The value returned by JgStrBufCreate() is 
 *        returned.
 * 
 * @return
 *        The number of string buffer elements is returned (not the byte size).
 * 
 * In the following case @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When strbuf is an illegal handle.</li>
 * </ul>
 */
JKSint32 JgStrBufGetBufLength(JGStrBuf strbuf);

/**
 * Sets a character string in the string buffer.
 * 
 * @param strbuf
 *        The string buffer handle. The value returned by JgStrBufCreate() is 
 *        returned.
 * @param text
 *        The character string. It does not need to be null ('\0') terminated. 
 *        When JK_NULL is designated, it is handled as a string of length 0.
 * @param length
 *        The number of string elements (not the buffer size)
 * 
 * In the following cases @ref page_gui_trouble_shooting "Error" results.
 * <ul>
 * <li>When strbuf is an illegal handle.</li>
 * <li>When the designated string buffer is locked.</li>
 * <li>When length is a negative value.</li>
 * <li>When length is larger than the buffer size.</li>
 * <li>When text is JK_NULL and length is not 0.</li>
 * </ul>
 */
void JgStrBufSetText(JGStrBuf strbuf, const JKWChar text[], JKSint32 length);

/**
 *   Inserts a character string in the string buffer.
 *   
 *   @param strbuf  The string buffer handle. The value returned by JgStrBufCreate() 
 *                  is returned.
 *   @param text The character string for insertion. It does not need to be null 
 *               ('\0') terminated. When JK_NULL is designated, it is handled as a 
 *               string of length 0.
 *   @param length The number of string elements (not the buffer size)
 *   @param position The position for character string insertion. Values between 0 
 *                   and the existing character string length are valid.
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *   <li>When strbuf is an illegal handle.</li>
 *   <li>When the designated string buffer is locked.</li>
 *   <li>When length is a negative value.</li>
 *   <li>When length+existing string length is larger than the buffer size.</li>
 *   <li>When text is JK_NULL and length is not 0.</li>
 *   <li>When position is outside the range of (0 to existing string length).</li>
 *   </ul>
 */
void JgStrBufInsertText(JGStrBuf strbuf, const JKWChar text[], JKSint32 length, JKSint32 position);

/**
 *   Deletes part of a string buffer character string.
 *   
 *   @param strbuf  The string buffer handle. The value returned by JgStrBufCreate() 
 *                  is returned.
 *   @param offset The position of the string for deletion. Values between 0 
 *                   and the existing character string length are valid.
 *   @param length The length of the string to be deleted (number of characters).
 *   
 *   In the following cases @ref page_gui_trouble_shooting "Error" results.
 *   <ul>
 *   <li>When strbuf is an illegal handle.</li>
 *   <li>When the designated string buffer is locked.</li>
 *   <li>When offset is outside the range of (0 to existing string length).</li>
 *   <li>When length is a negative value.</li>
 *   <li>When offset+length is larger than the existing string length.</li>
 *   </ul>
 */
void JgStrBufDeleteText(JGStrBuf strbuf, JKSint32 offset, JKSint32 length);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !___GUI_COMMON_STRING_H */
