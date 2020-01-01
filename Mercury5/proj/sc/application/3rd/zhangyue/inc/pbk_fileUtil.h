#if defined(__ZYUE_ENGINE__)
#ifndef __VEN_FILEUTIL_H_
#define __VEN_FILEUTIL_H_
/**
 *
 * @file    ven_fileUtil.h
 * @brief   This file defines the file util interface definition.
 *
 * @author  Mingkun.Zhang
 *
 *
 */
#include "ven_sdk.h"
#include "ven_file.h"

// A handle points to an internal structure in MStar system. It uses as search handle. mk
typedef void* pbk_fileUtil_search_handle_t;

// File search structure
typedef struct pbk_fileUtil_search_start_t_
{
	u32                dwNum;     /* total files(folders) */
	u32                dwCurr;    /* current item*/
	ven_dir_handle_t   hDir;      /* folder handle */
    u16				  pFileNameWC[256];      /* WildCard string for match*/
}pbk_fileUtil_search_start_t;

/**
 *  ven_fileUtil_findnext
 *
 *  @brief  find next file
 *
 *  @param  hSearch           [in]ven_fileUtil_search_handle_t
 *  @param  pFileInfo         [out]file info
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR or VEN_FILE_ERR_BAD_PARAM if failed
 *
 */
s32 pbk_fileUtil_findnext(pbk_fileUtil_search_handle_t hSearch, ven_file_info_t *pFileInfo);

/**
 *  ven_fileUtil_findfirst
 *
 *  @brief  start search file
 *
 *  @param  pFilePath       [in] file path
 *  @param  pFileInfo       [out]file info
 *
 *  @retval ven_fileUtil_search_handle_t
 */
pbk_fileUtil_search_handle_t pbk_fileUtil_findfirst(const u16* pFilePath, ven_file_info_t *pFileInfo);

/**
 *  ven_fileUtil_findclose
 *
 *  @brief  stop search file
 *
 *  @param  hSearch           [in]ven_fileUtil_search_handle_t
 *
 *  @retval VEN_FILE_ERR_NO_ERROR if success
 *          VEN_FILE_ERR_INTERNAL_ERROR or VEN_FILE_ERR_BAD_PARAM if failed
 *
 */
s32 pbk_fileUtil_findclose(pbk_fileUtil_search_handle_t hSearch);

#endif
#endif
