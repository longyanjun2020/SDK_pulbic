//==============================================================================
//
//  File        : AHC_MIMF.c
//  Description : INCLUDE File for the Middleware of Index Mapping Functions porting.
//  Author      : Jerry Li
//  Revision    : 1.0
//
//=============================================================================
#ifndef _AHC_MIMF_H_
#define _AHC_MIMF_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "ahc_common.h"
#include "AHC_Config_SDK.h"
//#include "ahc_general.h"
#include "ahc_dcf.h"
#include "ahc_dcfdt.h"
/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum _AHC_MIMF_BROWSER_MASK{
    AHC_MIMF_BROWSER_MASK_DB0       = (0x01 << 0),
    AHC_MIMF_BROWSER_MASK_DB1       = (0x01 << 1),
    AHC_MIMF_BROWSER_MASK_DB2       = (0x01 << 2),
    AHC_MIMF_BROWSER_MASK_DB3       = (0x01 << 3),
    AHC_MIMF_BROWSER_MASK_REAR_CAM  = (0x01 << 4),
    AHC_MIMF_BROWSER_MASK_ALL       = 0x1F
}AHC_MIMF_BROWSER_MASK;
//DCF_DB_TYPE

typedef enum _AHC_MIMF_BROWSER_MASK_TYPE{
    AHC_MIMF_BROWSER_MASK_MOV       = (0x01 << 0),
    AHC_MIMF_BROWSER_MASK_JPG       = (0x01 << 1),
    AHC_MIMF_BROWSER_MASK_TYPE_ALL  = 0x3
}AHC_MIMF_BROWSER_MASK_TYPE;
/*===========================================================================
 * Structure define
 *===========================================================================*/
typedef AHC_BOOL    (AHC_MIMF_CB_NodeOperation)(UINT8 byDBIdx, SFILENAME_INFO  FileNameInfo, UINT8 byOperation);

typedef struct sINDEXMAPNODE{
    struct sINDEXMAPNODE* pPrev;
    struct sINDEXMAPNODE* pNext;
    UINT8  byDB;
    SFILENAME_INFO  FileNameInfo;
} SINDEXMAPNODE, *PSINDEXMAPNODE;

typedef struct sMIMFBROWSEDB{
    struct sINDEXMAPNODE* pFileHead;
    struct sINDEXMAPNODE* pFileTail;
    UINT32 ulUFTotalFileNum;
} SMIMFBROWSEDB, *PSMIMFBROWSEDB;

/*===========================================================================
 * Function prototype
 *===========================================================================*/
void     AHC_MIMF_SetBrowserMask(UINT32 uiBrowserMask);
void     AHC_MIMF_GetBrowserMask(UINT32 *puiBrowserMask);
AHC_BOOL AHC_MIMF_GetTotalFileCount(UINT32 *puiImgIndex);
AHC_BOOL AHC_MIMF_IndexReverseMapping(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam);
AHC_BOOL AHC_MIMF_IndexMapping(UINT32 puiDcfIndex, UINT32 sDB, AHC_BOOL bIsRearCam, UINT32 *uiImgIndex);
AHC_BOOL AHC_MIMF_SetCurrentIndex(UINT32 uiImgIndex);
AHC_BOOL AHC_MIMF_GetCurrentIndex(UINT32 *puiImgIndex);
AHC_BOOL AHC_MIMF_GetFilePathNamebyIndex(UINT32 uiIndex, char* FilePathName);
AHC_BOOL AHC_MIMF_GetFileSizebyIndex(UINT32 uiIndex, UINT32* uiFileSize);
AHC_BOOL AHC_MIMF_GetFileTypebyIndex(UINT32 uiIndex, UINT8 *ubFileType);
AHC_BOOL AHC_MIMF_IsReadOnlybyIndex(UINT32 uiIndex, AHC_BOOL *bReadOnly);
AHC_BOOL AHC_MIMF_GetFileTimebyIndex(UINT32 uiIndex, AHC_RTC_TIME *pRtcTime);
AHC_BOOL AHC_MIMF_IsCharLockbyIndex(UINT32 uiIndex, AHC_BOOL *bCharLock);
AHC_BOOL AHC_MIMF_GetFileNamebyIndex(UINT32 uiIndex, char* FileName);
AHC_BOOL AHC_MIMF_MoveFileByIndex(DCF_DB_TYPE sFromType, DCF_DB_TYPE sToType, UINT32 uiIndex, AHC_BOOL bReadOnly);
AHC_BOOL AHC_MIMF_CheckFileCamStatus(UINT32 uiIndex, UINT8 *status);
void     AHC_MIMF_RegisterCusCallback(void);
#if(MIMF_CUSTOMIZED_SORT_TYPE == MIMF_CUSTOMIZED_SORT_MULTI_DB_DECREASE)
AHC_BOOL AHC_MIMF_MemPoolFSInit(UINT32 uiMaxMemSize);
AHC_BOOL AHC_MIMF_MemPoolFSUninit(void);
void* AHC_MIMF_FileNodeAlloc( void );
AHC_BOOL AHC_MIMF_FileNodeFree( void* pbyBuff );
AHC_BOOL AHC_MIMF_NodeOperation(UINT8 byDB,
                                SFILENAME_INFO FileNameInfo,
                                UINT8 byOperation);
AHC_BOOL AHC_MIMF_GetDBandDCFIndexbyThumbIndex(UINT32 ThumbIndex,UINT8* byDB,UINT32* DCFIndex);
AHC_BOOL AHC_MIMF_IndexReverseMappingMultiDB_De_Sort(UINT32 uiImgIndex, UINT32 *puiDcfIndex, UINT32 *sDB, AHC_BOOL *bIsRearCam);
void AHC_MIMF_SetMultiDBBrowseEnable(AHC_BOOL bSetMultiDBBrowse);
AHC_BOOL AHC_MIMF_GetMultiDBBrowseEnable(void);
void AHC_MIMF_SetMIMFMemStartAddr(UINT32 addr);
void AHC_MIMF_GetMIMFMemStartAddr(UINT32 *addr);
#endif


#endif //end #ifndef _AHC_MIMF_H_

