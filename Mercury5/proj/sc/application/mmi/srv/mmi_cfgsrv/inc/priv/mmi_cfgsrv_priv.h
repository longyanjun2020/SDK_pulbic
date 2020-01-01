/**
 * \file    mmi_cfgsrv_priv.h
 * \brief   The document describes the interface of Configuration Service
 * \author  eric.chen@mstarsemi.com
 * \page    Configuration Service
 *
 *  @version $Id: mmi_cfgsrv_priv.h 15682 2008-10-29 08:10:41Z eric.chen $
 */
#ifndef __MMI_CFGSRV_PRIV_H__
#define __MMI_CFGSRV_PRIV_H__

#include "mmi_cfgsrv.h"
#include "mmi_cfgsrv_common_table.h"
#include "mmi_cfgsrv_common_table_priv.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_filemgr.h"
#include "mmi_cfgsrv_info.h"

#define __USE_RAI_STORAGE__
//#define _SUPPORT_OPEN_FILE_MODE_RPLUS_
#define __UCS2_FILEMANAGER__
//#define __USE_CACHE_POLICY__



#define CFG_KBYTES (1024)
#define CFG_30KBYTES (30720)
#define MITEMFILE_MAX_RESTORE_SIZE (256)
#define CFG_ITEM_MAX_RESTORE_NUM   (5)

#define ICFGSrv_IEVT_SEND_NOTIFY (CLSID_CFGSRV <<16  | 0x100)




#ifdef __USE_RAI_STORAGE__

typedef struct
{
    const char *pFileName;
    u32 RAIId;
}MMI_CFGSRV_FILE_NAME_MAP_TAB_t;

#if defined(__NAND__)
#define CFG_MAX_RAI_SIZE	(1024)
#define MMI_CFG_TIME_TO_KICK_WATCHDOG (50)
#elif defined(__RAI_COMPRESSION_MMI__)
//NOR products and enable the RAI compression feature
#define CFG_MAX_RAI_SIZE	(256)
#else
//regular NOR products
#define CFG_MAX_RAI_SIZE	(64)
#endif


#endif//__USE_RAI_STORAGE__

#define __STATIC_ASSERT_MSG(cond, MSG)   typedef char __staticAssert_##MSG[(cond)?1:0] 
#define __STATIC_ASSERT_FL(X, F, L)     __STATIC_ASSERT_MSG(X, assert_##F_##L)
#define __STATIC_ASSERT2(X, F, L)       __STATIC_ASSERT_FL(X, F, L)
#define __STATIC_ASSERT(X)              __STATIC_ASSERT2(X, __FILE__, __LINE__)


typedef struct
{
    FileMgr_Stream_t *pIFStream;
    u32 FileStartPOS;
    u32 BufferSize;
    u32 WholeFileSize;
    void *pItemBuffer;
}MMI_CFGSrv_FileInfo;


typedef struct
{
    u8 *pCacheBuffer;       //cache buffer is used for batch processing.
    u32 CacheBufferSize;
}MMI_CFGSrv_CacheBufferInfo;



/*  Declarations */
typedef struct
{
    DECLARE_FUNCTBL(ICFGSrv);     /* struct of interface function pointers */
    u32 nRefCnt;                            /* Reference count */
    IModel *pCFGModel;                         /* CFGSrv Model */
    boolean bDisableModelNotify;                /* Indicate model notify is enable or disable */
    u8 *pCacheItemFileBuffer;
    SET_MASTER_RESET_FLAG_e eRsetCFGItemFlag;
    boolean bRestedMItem;
    boolean bRestedCItem;
    u32 u32RestoredSingleItemIndex;
    //boolean bRenameFail;
    boolean bTerminated;
    void *pCaller;

    MMI_CFGSrv_CacheBufferInfo stCacheBufferInfo[LAST_ITEM_TYPE];
}MMI_CFGSrv;

typedef MAE_Ret (*CFG_PFGETITEM)(ICFGSrv *, CFGItemID_e, void *, u32, boolean, CFGSrvItemType_e);
typedef MAE_Ret (*CFG_PFSETITEM)(ICFGSrv *, CFGItemID_e, void *, u32, boolean, boolean, CFGSrvItemType_e);

/*  Declarations */
typedef struct
{
    CFG_PFGETITEM pGetItemFn;
}MMI_CFGSrv_GetFunElmnts;

typedef struct
{
    CFG_PFSETITEM pSetItemFn;
}MMI_CFGSrv_SetFunElmnts;


//Private function
static MAE_Ret CFGSRV_GetCItem(ICFGSrv *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize, boolean bGetDefaultItem, CFGSrvItemType_e ItemType);
__SLDPM_FREE__ static MAE_Ret CFGSRV_GetMItem(ICFGSrv *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize, boolean bGetDefaultItem, CFGSrvItemType_e ItemType);

#ifdef __USE_CFG_SITEM__
static MAE_Ret CFGSRV_GetSItem(ICFGSrv *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize, boolean bGetDefaultItem, CFGSrvItemType_e ItemType);
#endif

static MAE_Ret CFGSRV_SetCItem(ICFGSrv *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize, boolean bSetDefaultItem, boolean bBatchProcessing, CFGSrvItemType_e ItemType);
static MAE_Ret CFGSRV_SetMItem(ICFGSrv *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize, boolean bSetDefaultItem, boolean bBatchProcessing, CFGSrvItemType_e ItemType);

#ifdef __USE_CFG_SITEM__
static MAE_Ret CFGSRV_SetSItem(ICFGSrv *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize, boolean bSetDefaultItem, CFGSrvItemType_e ItemType);
#endif

//Write data to cache buffer.
static MAE_Ret CFGSRV_SetDataToCacheBuffer(MMI_CFGSrv *pThis, MMI_CFGSrv_FileInfo *pFileInfo, u8 *pCacheBuffer, u32 CacheSize);

//Read & write data to file system
static MAE_Ret CFGSRV_SetDataToFile(ICFGSrv *pICFGSrv, const u8 *pFilePath, MMI_CFGSrv_FileInfo *pFileInfo);
__SLDPM_FREE__ static MAE_Ret CFGSRV_GetDataFromFile(ICFGSrv *pICFGSrv, const u8 *pFilePath, MMI_CFGSrv_FileInfo *pFileInfo);
static MAE_Ret CFGSRV_GetCFGItemFileSize(ICFGSrv *pICFGSrv, const u8 *pFilePath, u32 nWholeFileSize, u32 *pFileSize);

//Check item validity
#ifdef __USE_CFG_SITEM__
static MMI_CFGSRV_SINGLE_ITEM_FILE_ENTITY const * CFGSRV_GetSItemEntity(CFGItemID_e ItemID);
#endif
__SLDPM_FREE__ static MMI_CFGSRV_MULTIPLE_ITEM_FILE_ENTITY const * CFGSRV_GetMItemEntity(CFGItemID_e ItemID, CFGSrvItemType_e ItemType);

#ifdef __USE_CFG_SITEM__
static MAE_Ret CFGSRV_RestoreSingleItem(MMI_CFGSrv *pThis);
#endif//__USE_CFG_SITEM__

__SLDPM_FREE__ static MAE_Ret CFGSRV_SendNotify(ICFGSrv *pICFGSrv, u32 dwParam, u32 nEventCode);

static MAE_Ret CFGSRV_CheckCFGItem(MMI_CFGSrv *pICFGSrv);
static MAE_Ret CFGSRV_CheckCFGItemInFS(ICFGSrv *pICFGSrv, CFGSrvItemType_e ItemFileType, const u8 *pFilePath);
static MAE_Ret CFGSRV_GetCFGItemFileHeader(ICFGSrv *pICFGSrv, void *pItemFileHeader, const u8 *pFilePath, u32 nWholeFileSize);
__SLDPM_FREE__ static MAE_Ret CFGSRV_SetDefaultCFGItemFileToFS(ICFGSrv *pICFGSrv, CFGSrvItemType_e ItemFileType, const u8 *pFilePath);
static MAE_Ret CFGSRV_GetDefaultCFGItemFile(ICFGSrv *pICFGSrv, CFGSrvItemType_e ItemType, void **ppBuffer, u32 *pBufferSize);



__SLDPM_FREE__ static void MMI_CFGSRV_NotifyItemUpdateCB(IBase *pObj, u32 Param);

#endif //__MMI_CFGSRV_PRIV_H__
