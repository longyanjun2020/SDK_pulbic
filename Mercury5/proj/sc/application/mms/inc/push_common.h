
/**
 * @file push_common.h
 *
 * API exposed by the common module of PUSH.
 *
 * <!-- #interface list begin -->
 * \section
 * - push_common_checkFileNameValidity()
 * - push_common_initFileNameList()
 * - push_common_insertNode()
 * <!-- #interface list end -->
 */

#ifndef _PUSH_COMMON_H
#define _PUSH_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 *Check filename's validity according to filetype.
 * \param *pfilename Pointer to a null-terminated string that specifies the name of file.
 * \param filetype Long integer that specifies the type of file.
 *
 * \return <ul>
 *  <li>If the filename is valid,then return#TRUE.
 *  <li>If the filename is invalid,then return#FALSE.
 * </ul>
 */
int push_common_checkFileNameValidity(int8_t *pfilename, int32_t filetype);

/**
 *Assign memory for filename list and memset it to zero.
 * \param **plist Pointer to a structure list that specifies all filenames.
 *
 * \return <ul>
 * <li>If the operation is successful,then return#TRUE.
 * <li>Otherwise,return#FALSE.
 * </ul>
 * \sa NCCPush_common_freeFileNameList(T_PUSH_FILENAME_LIST **plist)
 */
int push_common_initFileNameList(T_PUSH_FILENAME_LIST **plist);

/**
 *Insert appointed node into responed structure list.
 * \param *plist Pointer to a T_PUSH_FILENAME_LIST structure list that specifies the names of all files..
 * \param type Long integer that specifies the type of appointed files.
 *
 * \return <ul>
 * <li>If successful,then return#TRUE.
 * <li>Otherwise,return#FALSE.
 * </ul>
 */
 int push_common_insertNode(T_PUSH_FILENAME_LIST *plist, int8_t *filename, int32_t type);

#ifdef __cplusplus
extern "C" {
#endif

#endif
