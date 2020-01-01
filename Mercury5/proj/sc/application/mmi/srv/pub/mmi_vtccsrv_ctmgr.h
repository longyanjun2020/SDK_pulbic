/**
 * @file    mmi_vtccsrv_ctmgr.h
 * @brief   xxxx
 * @version $Id: mmi_vtccsrv_ctmgr.h 11970 2008-06-24 12:04:04Z collin.chiang $
 */
#ifndef __MMI_VTCCSRV_CTMGR_H__
#define __MMI_VTCCSRV_CTMGR_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_datamodel.h"

#include "mmi_vtccsrv_def.h"

#ifdef __VT_3G324M__

/******** Call Table Management function *******/

/* Call Table Management interface function for VTCCSRV */
boolean VTCCSRV_CTMgrInsertNew(CallTable_t *pCallTable, CallTableEntry_t *pNewEntry, u8 *pRetIndex);
boolean VTCCSRV_CTMgrUpdatebyIndex(CallTable_t *pCallTable, u8 u8Index, CallTableEntry_t *pUpdateEntry);
boolean VTCCSRV_CTMgrUpdatebyCallID(CallTable_t *pCallTable, u8 u8CallID, CallTableEntry_t *pUpdateEntry);
boolean VTCCSRV_CTMgrDeletebyIndex(CallTable_t *pCallTable, u8 u8Index);
boolean VTCCSRV_CTMgrDeletebyCallID(CallTable_t *pCallTable, u8 u8CallID);
boolean VTCCSRV_CTMgrCleanUp(CallTable_t *pCallTable);

/* Utility function for Call Table Management interface */
void VTCCSRV_CTMgrUtilWriteTable(CallTable_t *pCallTable, u8 u8Index, CallTableEntry_t *pEntry, VTCCSRV_UpdateMode_e eMode);
boolean VTCCSRV_CTMgrUtilRetrieveIndexbyCallID(CallTable_t *pCallTable, u8 u8CallID, u8 *pRetIndex);
boolean VTCCSRV_CTMgrUtilRetrieveCallIDbyIndex(CallTable_t *pCallTable, u8 u8Index, u8 *pRetCallID);
boolean VTCCSRV_CTMgrUtilFindAvailableIndex(CallTable_t *pCallTable, u8 *pRetIndex);
void VTCCSRV_CTMgrUtilDeleteRefreshCallTable(CallTable_t *pCallTable, u8 u8Index);
boolean VTCCSRV_CTMgrUtilUpdateCallStatus(CallTable_t *pCallTable, u8 u8CallID, u8 u8Status);
boolean VTCCSRV_CTMgrUtilUpdateStartTime(CallTable_t *pCallTable, u8 u8CallID, u32 u32Time);
boolean VTCCSRV_CTMgrUtilUpdateMPTYFlag(CallTable_t *pCallTable, u8 u8CallID, boolean bMYPYFlag);
boolean VTCCSRV_CTMgrUtilIsIndexValid(u8 u8Index);
boolean VTCCSRV_CTMgrUtilIsCallIDValid(u8 u8CallID);

#endif //__VT_3G324M__
#endif /* __MMI_VTCCSRV_CTMGR_H__ */

