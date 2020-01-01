/**
 * @file    mmi_filemgr_util.h
 *
 * @brief   This file defines the interface of file filemgr utility functions.
 * @version $Id: mmi_common_path.h 41655 2010-02-25 12:00:00Z eddie.chen $
 * @author
 *
 */
#ifndef __MMI_FILEMGR_UTIL_H__
#define __MMI_FILEMGR_UTIL_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_common_content_forward.h"
#include "mmi_mae_helper.h"
#include "mmi_mae_filemgr.h"
#include "mmi_common_mimetype.h"


extern const FileMgr_VolMappingTbl_t _tFileMgr_VolMappingTbl[];
extern MAE_Ret FileMgrGetVolMappingNum(u32 *pNum);

s32 FileListSortingComparatorByName(void *pBase, void* pRef);
s32 FileListSortingComparatorByFileSize(void *pBase, void* pRef);
s32 FileListSortingComparatorByDate(void *pBase, void* pRef);
s32 FileListSortingComparatorByType(void *pBase, void* pRef);

/**
* MMI_Common_GetFilter
* @brief	Utility to get filter by different type
*
* @param	eType                   Input filter type.
* @param	tFilter	                Output filter data structure pointer.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_GetFilter(MAEMIMEFilterID_e eType, VFS_PartialListFilter_t **tFilter);

/**
* MMI_Common_MatchVolumeID
* @brief	Utility to check volumeID
*
* @param	pStrVol	                Input volume name.
* @param	pVol	                Output volume ID.
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Out of memory.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_MatchVolumeID(FileMgr_WChar *pStrVol, u8 *pVol);

/**
* MMI_Common_GetVolumeName
* @brief	Utility to check volumeID
*
* @param	nVol                    Input volume ID.
* @param	pStrVolumeName	        Output volume name.
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Out of memory.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret  MMI_Common_GetVolumeName(FileMgr_WChar *pStrVolumeName, u8 nVol);

/**
* MMI_Common_ProcessFilePathWithBuffer
* @brief	Utility to convert url to path and file name.
*
* @param	pStrDir	                Input URL.
* @param	pStrPath	            Output path.
* @param	pStrFileName	        Output filename
* @param	pVolumeID	            Output volumeID
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal   MAE_RET_OUT_OF_MEMORY   Out of memory.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_Ret MMI_Common_ProcessFilePathWithBuffer(const FileMgr_WChar *pStrDir, FileMgr_WChar *pStrPath, FileMgr_WChar *pStrFileName, u8 *pVolumeID);

/**
* MMI_Common_CreateMediaMgrPath
*  @brief  Convert fs:/PHON/xxxx to /NAND/xxx or /CARD/xxx to fit the format of Montage.
*          It is specially designed for IMedia. This function would allocate a block of memory
*          for output.
*  @param  pSourceURL    A string with format of fs:/xxxx in ucs2 format
*  @param  ppDestPath    A string with format of /xxxx in device string format (0x90 lenth .....)
*
*  @retval MAE_RET_BAD_PARAM The pSourcePath is not in the format of fs:/PHON/xxx or fs:/CARD/....
*  @retval MAE_RET_SUCCESS Convert success
*/
MAE_Ret MMI_Common_CreateMediaMgrPath(FileMgr_WChar *pSourceURL, FileMgr_WChar **ppDestPath);

/**
 *  MMI_Common_CreateFSPath
 *  @brief  Convert /NOR0/xxx or /CARD/xxx to fs:/PHON/xxxx or fs:/CARD/xxxx fit the format of mae File Manager.
 *  @param  pSourcePath  A string with format of /xxxx in ucs2 format
 *  @param  ppDestPath    A string with format of fs:/xxxx in ucs2 format
 *
 *  @retval MAE_RET_BAD_PARAM The pSourcePath is not in the format of /NOR0/xxx or /CARD/xxx
 *  @retval MAE_RET_SUCCESS ppDestPath create success
 */
MAE_Ret MMI_Common_CreateFSURL(FileMgr_WChar *pSourcePath, FileMgr_WChar **ppDestURL);


#endif /* __MMI_FILEMGR_UTIL_H__ */

