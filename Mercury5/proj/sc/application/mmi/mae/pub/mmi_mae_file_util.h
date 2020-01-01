/**
 * @file    mmi_mae_filemgr.h
 * @brief   The document describes the interface of IFileMgr
 *
 * File manager supports 3 volumes now, "PHONE", "PHONE_EXT", and "CARD". The usage is to use
 * fs:/(PHON)|(PHONE_EXT)|(CARD)/xxx/xxx .... as filepath for all interfaces of IFILEMgr. The seperator
 * could be both / and \. The first folder maps to different volumes, as a result we cannot make new directories
 * and list files, ... etc, under fs:\.
 *
 * Filename utility definition
 * ----------------------------------
 * Example: fs:/CARD/dev/project/file.txt
 *   the prefix - fs:/
 *   the path - CARD/dev/project/
 *   the full path - fs:/CARD/dev/project/
 *   the name - file.txt
 *   the base name - file
 *   the extension - txt
 *
 * @author  kenny.wu@mstarsemi.com
 * @version $Id: mmi_mae_file_util.h 1045 2009-06-04 12:11:48Z mark.yang $
 */
#ifndef __MMI_MAE_FILE_UTIL_H__
#define __MMI_MAE_FILE_UTIL_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#ifdef __SDK_SIMULATION__
#include "stdio.h"
#endif

/**
 *  MAEUTIL_OpenFile
 *  \brief  open file accroding the pStrDir and set the file position to nOffset
 *
 *  \param  pStrDir                Pointer to the MAE_WChar
 *  \param  nOffset                 number of nOffset from file beginning
 *  \param  nBufSize                number of buffer size
 *  \param  pThis                  the caller's pointer
 *  \retval MAE_Ret                MAE_RET_SUCCESS or MAE_RET_FAILED
 */
MAE_Ret  MAEUTIL_OpenFile (const MAE_WChar* pStrDir, s32 nOffset, u16 nBufSize, IBase* pThis);

/**
 *  MAEUTIL_GetLineEx
 *  \brief  get line according delimiter and return line to caller
 *
 *  \param  pBuffer                Pointer to buffer
 *  \param  nCount                  the number of bytes to read
 *  \param  sizeOfDeleimiter       The length of pDelimiter
 *  \param  pDelimiter              the character set to make line
 *  \retval >=0                    the number of bytes of read
 *          <0					   function occurs error
 */
s32 MAEUTIL_GetLineEx (const void *pBuffer, u32 nCount, u16 sizeOfDeleimiter, u8 *pDelimiter);

/**
 *  MAEUTIL_Tell
 *  \brief  get the current file position
 *
 *  \retval >=0                    the current file position
 *          <0					   function occurs error
 */
s32 MAEUTIL_Tell(void);

/**
 *  MAEUTIL_CloseFile
 *  \brief  close file
 *
 *  \retval MAE_RET_SUCCESS        close file success
 *          MAE_FS_ERROR		   function occurs error
 */
MAE_Ret MAEUTIL_CloseFile(void);

/**
 * Get the pointer of the filename from the fullpath of a file
 *
 * a/b/c.txt --> c.txt
 * a.txt     --> a.txt
 * a/b/c     --> c
 * a/b/c/    --> ""
 *
 * @param pSrc the fullpath of a file
 * @return NULL pStr is NULL
 *         others  the pointer of the filename
 */
MAE_WChar* MAE_FileNameUtil_GetName(const MAE_WChar* pFilename);

/**
 * Get the name of a file without extension, and duplicate it
 * Client need to free the memory address
 *
 * a/b/c.txt	--> c
 * a.txt		--> a
 * a/b/c		--> c
 * a.b/c		--> c
 * a/b/c.d.txt	--> c.d
 * a.			--> a
 * a/b/c/		--> ""
 * .abc			--> ""
 * .			--> ""
 * /			--> ""
 * /.			--> ""
 * ./			--> ""
 * ""			--> ""
 *
 * @param pFilename the full name of a file
 * @return NULL pStr is NULL, or memory insufficient
 *         others the address of the new filename string (without extension part and dot)
 */
MAE_WChar* MAE_FileNameUtil_CopyBaseName(const MAE_WChar* pFilename);

/**
 * Get the extension filename from the file full path
 *
 * @param pFilename the file full path
 * @param bToLowerCase denotes the out string will in lower case or not
 * @return NULL Out of memory
 *         others the string of the extension filename (without dot)
 */
MAE_WChar* MAE_FileNameUtil_GetExtension(const MAE_WChar *pFilename);

/**
 * Get the extension filename from the file full path and duplicate it
 *
 * @param pFilename the file full path
 * @param bToLowerCase denotes the out string will in lower case or not
 * @return NULL Out of memory
 *         others the string of the extension filename (without dot)
 */
MAE_WChar* MAE_FileNameUtil_CopyExtension(const MAE_WChar *pFilename, boolean bToLowerCase);

/**
 * Generate a full path of a file by it's folder path and full filename
 *
 * @param basePath the folder path, without the postfix folder pDelimiter FOLDER_DELIMITER
 * @param fullFilenameToAdd the full name of a file
 * @return NULL any of the the input pointer is NULL, or memory insufficient
 *         others the address of the new full path
 */
MAE_WChar* MAE_FileNameUtil_Concat(const MAE_WChar *pBasePath, const MAE_WChar *pFullFilenameToAdd);

/**
 * Get the folder path of the file and duplicate it
 *
 * @param pFilename the full path of a file
 * @param NULL pFilename is NULL
 *        NULL pFilename is a invalid full path
 *        NULL memory sufficient
 *        others the pointer of the path of the folder (without the postfix:FOLDER_DELIMITER..)
 */
// MAE_WChar* MAE_FileNameUtil_CopyFullPath(const MAE_WChar *pFilename);

/**
 * Removes the extension from a filename.
 *
 * This method returns the textual part of the filename before the last dot.
 *
 * foo.txt    --> foo
 * a\b\c.jpg  --> a\b\c
 * a\b\c      --> a\b\c
 * a.b\c      --> a.b\c
 *
 * @param pFilename the full path of a file
 * @return NULL pFilename is NULL
 *         NULL out of memory
 *         others the pointer of the result
 */
MAE_WChar* MAE_FileNameUtil_RemoveExtension(const MAE_WChar *pFilename);

// MAE_WChar* MAE_FileNameUtil_CopyExtensino(const MAE_WChar *pFilename);
// boolean MAE_FileNameUtil_IsExtension(const MAE_WChar *pFilename, const MAE_WChar *pExt);
// boolean MAE_FileNameUtil_IsExtensions(const MAE_WChar *pFilename, const MAE_WChar *pExt[], int extNum);
// boolean MAE_FileNameUtil_WildcardMatch(const MAE_WChar *pFilename, const MAE_WChar *wildcardMatcher);
// MAE_WChar* MAE_FileNameUtil_Normalize(const MAE_WChar *pFilename);

#endif //  __MAE_FILE_UTIL_H__
