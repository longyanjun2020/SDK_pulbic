/**
* @file    mmi_calllogsrv_hsmgr.h
* @version
* @brief   Call log service headset storage manager header file
*
*/
#ifndef __MMI_CALLLOGSRV_HSMGR_H__
#define __MMI_CALLLOGSRV_HSMGR_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_filemgr.h"
#include "mmi_util_fs.h"
#include "mmi_calllogsrv_def.h"
#include "mmi_calllogsrv.h"
#include "mmi_common_rai_id.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

#define MMI_CALLLOG_FILE_NAME L"callhistory.dat"
#define MMI_CALLLOG_FILE_PATH L"fs:/PHON/CALLHISTORY/"
#define MMI_CALLLOG_FULLPATH_FILENAME MMI_CALLLOG_FILE_PATH MMI_CALLLOG_FILE_NAME

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/

u32 Mmi_CallLog_HSMgr_GetRaiIdByType(MMI_CALLLOG_TYPE_E iType);

MAE_Ret Mmi_CallLog_HSMgr_CheckDirFile(IBase *pThis);
MAE_Ret Mmi_CallLog_HSMgr_DeleteFile(IBase *pThis);

MAE_Ret Mmi_CallLog_HSMgr_InitLogBuf(IBase *pThis, MMI_CALLLOG_TYPE_E iType, Mmi_CallLogSimpRecord_t *pBuf, const u8 *pu8IdxToFile, u8 *pu8Size);
MAE_Ret Mmi_CallLog_HSMgr_InitHeaderFile(IBase *pThis);
MAE_Ret Mmi_CallLog_HSMgr_InitLogFileByType(IBase *pThis, MMI_CALLLOG_TYPE_E iType);

MAE_Ret Mmi_CallLog_HSMgr_ReadHeader(IBase *pThis, Mmi_CallLogFileHeader_t *pHeader);
MAE_Ret Mmi_CallLog_HSMgr_WriteHeader(IBase *pThis, const Mmi_CallLogFileHeader_t *pHeader);
MAE_Ret Mmi_CallLog_HSMgr_WriteLog(IBase *pThis, const Mmi_CallLogFullRecord_t *pFullRecord, MMI_CALLLOG_TYPE_E iType, u32 *u32Filter, u8 *pu8Idx, u8 u8OldestLogIdx);

MAE_Ret Mmi_CallLog_HSMgr_ReadLog(IBase *pThis, Mmi_CallLogFullRecord_t *pFullRecord, MMI_CALLLOG_TYPE_E iType, u8 u8Idx);

MAE_Ret Mmi_CallLog_HSMgr_DeleteOneLog(IBase *pThis, MMI_CALLLOG_TYPE_E iType, u32 *pu32Filter, u8 u8Idx);
MAE_Ret Mmi_CallLog_HSMgr_DeleteAllLogs(IBase *pThis, MMI_CALLLOG_TYPE_E iType, MMI_CALLLOG_SIM_TYPE_E iSimType, u8 *pau8IMSI, u32 *pu32Filter, u8 *pu8IdxToFile);

static void Mmi_CallLog_QuickSort(Mmi_CallLogSimpRecord_t list[], u32 left, u32 right);
static void Mmi_CallLog_TransFilterToSize(u32 u32Filter, u8 *pu8Size);
static u32 Mmi_CallLog_HSMgr_GenEmptyFilter(void);

#endif /* __MMI_CALLLOGSRV_HSMGR_H__ */
