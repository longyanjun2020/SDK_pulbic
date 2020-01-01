/**
 * @file    mmi_ccsrv_ctmgr.h
 * @brief   xxxx
 * @version $Id: mmi_ccsrv_ctmgr.h 11970 2008-06-24 12:04:04Z collin.chiang $
 */
#ifndef __MMI_CCSRV_CTMGR_H__
#define __MMI_CCSRV_CTMGR_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_datamodel.h"

#include "mmi_ccsrv_def.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Local function prototype declaration and definition
/*=============================================================*/

/******** Call Table Management function *******/

/* Call Table Management interface function for CCSRV */
boolean CCSRV_CTMgrInsertNew(CallTable_t *pCallTable, CallTableEntry_t *pNewEntry);
boolean CCSRV_CTMgrUpdatebyIndex(CallTable_t *pCallTable, u8 u8Index, CallTableEntry_t *pUpdateEntry);
boolean CCSRV_CTMgrUpdatebyCallID(CallTable_t *pCallTable, u8 u8CallID, CallTableEntry_t *pUpdateEntry);
boolean CCSRV_CTMgrDeletebyIndex(CallTable_t *pCallTable, u8 u8Index);
boolean CCSRV_CTMgrDeletebyCallID(CallTable_t *pCallTable, u8 u8CallID);
boolean CCSRV_CTMgrCleanUp(CallTable_t *pCallTable);

/* Utility function for Call Table Management interface */
void CCSRV_CTMgrUtilWriteTable(CallTable_t *pCallTable, u8 u8Index, CallTableEntry_t *pEntry, CCSRV_UpdateMode_e eMode);
boolean CCSRV_CTMgrUtilRetrieveIndexbyCallID(CallTable_t *pCallTable, u8 u8CallID, u8 *pRetIndex);
boolean CCSRV_CTMgrUtilRetrieveIndexbyCallStatus(CallTable_t *pCallTable, MMI_CCSRV_Status_e eCallStatus, u8 *pRetIndex);
boolean CCSRV_CTMgrUtilRetrieveCallIDbyIndex(CallTable_t *pCallTable, u8 u8Index, u8 *pRetCallID);
boolean CCSRV_CTMgrUtilFindAvailableIndex(CallTable_t *pCallTable, u8 *pRetIndex);
void CCSRV_CTMgrUtilDeleteRefreshCallTable(CallTable_t *pCallTable, u8 u8Index);
boolean CCSRV_CTMgrUtilUpdateCallStatus(CallTable_t *pCallTable, u8 u8CallID, u8 u8Status);
boolean CCSRV_CTMgrUtilUpdateStartTime(CallTable_t *pCallTable, u8 u8CallID, u32 u32Time);
boolean CCSRV_CTMgrUtilUpdateMPTYFlag(CallTable_t *pCallTable, u8 u8CallID, boolean bMYPYFlag);
boolean CCSRV_CTMgrUtilIsIndexValid(u8 u8Index);
boolean CCSRV_CTMgrUtilIsCallIDValid(u8 u8CallID);

#endif /* __MMI_CCSRV_CTMGR_H__ */
