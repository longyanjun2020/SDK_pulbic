/**
 * \file    mmi_cfgsrv.h
 * \brief   The document describes the interface of Configuration Service
 * \author  eric.chen@mstarsemi.com
 *
 * \page    Configuration Service
 * @version $Id: mmi_cfgsrv.h 28082 2009-04-12 12:48:34Z eric.chen $
 */

#ifndef __MMI_CFGSRV_H__
#define __MMI_CFGSRV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_model.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_class.h"

#include "mmi_cfgsrv_citem_file_itemid.h"
#include "mmi_cfgsrv_mitem_allow_mr_itemid.h"
#include "mmi_cfgsrv_mitem_notallow_mr_itemid.h"
#include "mmi_cfgsrv_sitem_itemid.h"
#include "mmi_cfgsrv_mitem_info_itemid.h"
#include "mmi_cfgsrv_common_table.h"

#ifdef __NAND__

#define CFGSRV_SUPPORT_MAX_FILES_IN_CACHE_CLASS     (100)
#define CFGSRV_SUPPORT_MAX_FILES_IN_NMR_CLASS       (100)
#define CFGSRV_SUPPORT_MAX_FILES_IN_MR_CLASS        (200)
#define CFGSRV_SUPPORT_MAX_FILES_IN_INFO_CLASS      (100)

#else

#define CFGSRV_SUPPORT_MAX_FILES_IN_CACHE_CLASS     (100)
#define CFGSRV_SUPPORT_MAX_FILES_IN_NMR_CLASS       (300)
#define CFGSRV_SUPPORT_MAX_FILES_IN_MR_CLASS        (2000)
#define CFGSRV_SUPPORT_MAX_FILES_IN_INFO_CLASS      (300)

#endif


//
// ICFGSrv Model Event
//

// Used to indicate that a CFG item has been updated.
#define ICFGSrv_EVT_ITEM_UPDATE (CLSID_CFGSRV <<16  | 1)
#define ICFGSrv_EVT_ITEM_RESTORE_START (CLSID_CFGSRV <<16  | 2)
#define ICFGSrv_EVT_ITEM_RESTORE_END (CLSID_CFGSRV <<16  | 3)
#define ICFGSrv_EVT_RESTORE_ITEM_RESULT (CLSID_CFGSRV <<16  | 4)//Just post event to caller.

enum
{
    RESTORE_ITEM_RESULT_SUCCESS
   ,RESTORE_ITEM_RESULT_RESULT_LIMITATION
   ,RESTORE_ITEM_RESULT_ERROR
#ifdef __3G_RIL_MMI__
   ,RESTORE_ITEM_RESULT_NVRAM_FAIL
#endif //__3G_RIL_MMI__
};

typedef struct
{
    CFGItemID_e id;
    void *pItemBuffer;
    u32 BufferSize;
}CFGSetItemInfo;


#define INHERIT_ICFGSrv(IName) \
    INHERIT_IHandler(IName); \
    MAE_Ret (*GetItem) (IName *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize);\
    MAE_Ret (*SetItem) (IName *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 BufferSize);\
    MAE_Ret (*SetItemsByBatch)(IName *pICFGSrv, CFGSetItemInfo *pCFGItemInfo, u32 nNumItemInfo);\
    MAE_Ret (*GetDefaultItem) (IName *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 ItemSize);\
    MAE_Ret (*SetDefaultItem) (IName *pICFGSrv, CFGItemID_e id, void *pItemBuffer, u32 ItemSize);\
    MAE_Ret (*GetSize) (IName *pICFGSrv, CFGItemID_e id, u32 *pItemSize);\
    MAE_Ret (*DisableEvent) (IName *pICFGSrv, boolean bDisable);\
    MAE_Ret (*AddListener) (IName *pICFGSrv, ModelListener_t *pModelListener);\
    MAE_Ret (*CancelListener) (IName *pICFGSrv, ModelListener_t *pModelListener);\
    MAE_Ret (*RestoreCFGItem) (IName *pICFGSrv, void *pCaller)



DEFINE_INTERFACE(ICFGSrv);

/**
 *  ICFGSRV_QueryInterface
 *  @brief  Inherit  from IBase to query interface. It only support the interface of ICFGSrv.
 *
 *  @param[in]   pICFGSrv            Pointer to the IPLAYLISTSRV interface
 *  @param[in]   id                  Interface ID. In this function, only IID_PLAYLISTSRV is supported.
 *  @param[out]  ppObj               Reference to a pointer to a function table if this interface is supported
 *  @param[in]   pOwner              Pointer to the object which want to get ICFGSRV interface.
 *
 *  @return MAE_RET_SUCCESS     If successful.
 *  @return MAE_RET_NOT_SUPPORTED  If class id error.
 *  @return MAE_RET_BAD_PARAM    If input parameter error.
 */
#define ICFGSRV_QueryInterface(pICFGSrv, id, pp, po)         GET_FUNCTBL((pICFGSrv),ICFGSrv)->QueryInterface(pICFGSrv, id, pp, po)

/**
 *  ICFGSRV_GetItem
 *  @brief  Use to get configuration item value.
 *
 *  @param[in]   pICFGSrv            Pointer to the IPLAYLISTSRV interface.
 *  @param[in]   id                  Configuration item id.
 *  @param[out]  pItemBuffer         Pointer to the memory buffer which will store Configuration item value.
 *                                   Buffer have to be prepared by user.
 *  @param[in]   BufferSize          configuration item size.
 *
 *  @return MAE_RET_SUCCESS          If successful.
 *  @return MAE_RET_NOT_FOUND         If no file in file system
 *  @return MAE_RET_BAD_PARAM        If input parameter error.
 *  @return MAE_RET_FAILED           If an error happen.
 *
 */
#define ICFGSRV_GetItem(pICFGSrv, id, pItemBuffer, BufferSize)                    GET_FUNCTBL((pICFGSrv),ICFGSrv)->GetItem(pICFGSrv,id, pItemBuffer, BufferSize)

/**
*  ICFGSRV_SetItem
*  @brief  Use to set configuration item value.
*
*  @param[in]   pICFGSrv            Pointer to the IPLAYLISTSRV interface.
*  @param[in]   id                  Configuration item id.
*  @param[in]   pItemBuffer         Pointer to the memory buffer which will store Configuration item value.
*                                   Buffer have to be prepared by user.
*  @param[in]   BufferSize          configuration item size.
*
*  @return MAE_RET_SUCCESS          If successful.
*  @return MAE_RET_NOT_FOUND         If no file in file system
*  @return MAE_RET_BAD_PARAM         If input parameter error.
*  @return MAE_RET_FAILED           If an error happen.
*/
#define ICFGSRV_SetItem(pICFGSrv, id, pItemBuffer, BufferSize)                    GET_FUNCTBL((pICFGSrv),ICFGSrv)->SetItem(pICFGSrv,id, pItemBuffer, BufferSize)





#define ICFGSRV_SetItemsByBatch(pICFGSrv, pCFGItemInfo, nNumItemInfo)             GET_FUNCTBL((pICFGSrv),ICFGSrv)->SetItemsByBatch(pICFGSrv, pCFGItemInfo, nNumItemInfo)
/**
*  ICFGSRV_GetDefaultItem
*  @brief  Use to get configuration item default value.
*
*  @param[in]   pICFGSrv            Pointer to the IPLAYLISTSRV interface.
*  @param[in]   id                  Configuration item id.
*  @param[out]  pItemBuffer         Pointer to the memory buffer which will store configuration item value.
*                                   Buffer have to be prepared by user.
*  @param[in]   BufferSize          configuration item size.
*
*  @return MAE_RET_SUCCESS          If successful.
*  @return MAE_RET_NOT_FOUND         If no file in file system
*  @return MAE_RET_BAD_PARAM         If input parameter error.
*  @return MAE_RET_FAILED           If an error happen.
*/
#define ICFGSRV_GetDefaultItem(pICFGSrv, id, pItemBuffer, BufferSize)              GET_FUNCTBL((pICFGSrv),ICFGSrv)->GetDefaultItem(pICFGSrv,id, pItemBuffer, BufferSize)

/**
 *  ICFGSRV_SetDefaultItem
 *  @brief  Use to set configuration item default value.
 *
 *  @param[in]   pICFGSrv            Pointer to the IPLAYLISTSRV interface.
 *  @param[in]   id                  Configuration item id.
 *  @param[in]   pItemBuffer         Pointer to the memory buffer which will store configuration item value.
 *                                   Buffer have to be prepared by user.
 *  @param[in]   BufferSize          configuration item size.
 *
 *  @return MAE_RET_SUCCESS          If successful.
 *  @return MAE_RET_NOT_FOUND         If no file in file system
 *  @return MAE_RET_BAD_PARAM        If input parameter error.
 *  @return MAE_RET_FAILED           If an error happen.
 */
#define ICFGSRV_SetDefaultItem(pICFGSrv, id, pItemBuffer, BufferSize)              GET_FUNCTBL((pICFGSrv),ICFGSrv)->SetDefaultItem(pICFGSrv,id, pItemBuffer, BufferSize)


/**
 *   ICFGSRV_GetSize
 *  @brief  to get configuration item size
 *  @param[in]   pICFGSrv       Pointer to the ICFGSrv interface
 *  @param[in]   id             Identity of configuration item
 *  @param[out]  pItemSize      Configuration Service will return Configuration Item Size
 *
 *  @return MAE_RET_SUCCESS          If successful.
 *  @return MAE_RET_NOT_FOUND         If no file in file system
 *  @return MAE_RET_BAD_PARAM        If input parameter error.
 *  @return MAE_RET_FAILED           If an error happen.
 */
#define ICFGSRV_GetSize(pICFGSrv, id, pItemSize)                                GET_FUNCTBL((pICFGSrv),ICFGSrv)->GetSize(pICFGSrv, id, pItemSize)



/**
 *  ICFGSRV_DisableEvent
 *  \brief  disable or enable event notify
 *
 *  @param[in]  pICFGSrv       Pointer to the ICFGSrv interface
 *  @param[in]  bDisable       Set TRUE means disable event notify.
 *
 *  @return MAE_RET_SUCCESS          If successful.
 *  @return MAE_RET_BAD_PARAM        If input parameter error.
 *  @return MAE_RET_FAILED           If an error happen.
 */
#define ICFGSRV_DisableEvent(pICFGSrv, bDisable)                                GET_FUNCTBL((pICFGSrv), ICFGSrv)->DisableEvent(pICFGSrv, bDisable)



/**
 *  ICFGSRV_AddListener
 *  \brief  Add listener to get model notify
 *
 *  @param[in]  pICFGSrv       Pointer to the ICFGSrv interface
 *  @param[in]  pModelListener       Set TRUE means disable event notify.
 *
 *  @return MAE_RET_SUCCESS          If successful.
 *  @return MAE_RET_BAD_PARAM        If input parameter error.
 *  @return MAE_RET_FAILED           If an error happen.
 */
#define ICFGSRV_AddListener(pICFGSrv, pModelListener)                                GET_FUNCTBL((pICFGSrv), ICFGSrv)->AddListener(pICFGSrv, pModelListener)


/**
 *  ICFGSRV_CancelListener
 *  \brief  Cancel model notify
 *
 *  @param[in] pICFGSrv             Pointer to the ICFGSrv interface
 *  @param[in] pModelListener       Set TRUE means disable event notify.
 *
 *  @return MAE_RET_SUCCESS          If successful.
 *  @return MAE_RET_BAD_PARAM        If input parameter error.
  *  @return MAE_RET_FAILED           If an error happen.
 */
#define ICFGSRV_CancelListener(pICFGSrv, pModelListener)                                GET_FUNCTBL((pICFGSrv), ICFGSrv)->CancelListener(pICFGSrv, pModelListener)



#define ICFGSRV_RestoreCFGItem(pICFGSrv, pCaller)                                       GET_FUNCTBL((pICFGSrv), ICFGSrv)->RestoreCFGItem(pICFGSrv, pCaller)

__SLDPM_FREE__ MAE_Ret CFGSrv_New(MAE_ClsId ClsID, void **ppObj);

#endif //  __MMI_CFGSRV_H__
