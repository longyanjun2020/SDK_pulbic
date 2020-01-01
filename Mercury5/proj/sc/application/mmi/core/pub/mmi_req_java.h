/**
 * @file    mmi_req_java.h
 * @brief   The file handles the java event with java task
 * @author  christine.tai@mstarsemi.com
 *
 * $Id: mmi_req_java.h 28839 2009-04-17 14:15:49Z code.lin $
 */
#ifndef __MMI_REQ_JAVA_H__
#define __MMI_REQ_JAVA_H__

#ifdef __JAVA_MMI__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "java_ams_itf.h"
#include "mmi_if_java.h"

enum
{
    MMI_JAVA_STORAGE_NAND = 0,
    MMI_JAVA_STORAGE_NOR,
    MMI_JAVA_STORAGE_MEMCARD,
    MMI_JAVA_STORAGE_MEMCARD2,
    MMI_JAVA_STORAGE_PREINSTALL,
    MMI_JAVA_STORAGE_NUM,
};
typedef u8 mmi_java_storage_e;

#ifdef _MSIM_
void mmi_java_set_CallerPtr(void * ptr);
#endif

void mmi_java_init_req(void);
void mmi_java_release_req(void);
void mmi_java_getSuiteCount_req(void);
void mmi_java_getSuiteInfo_req(int SuiteIndex);
void mmi_java_removeSuite_req(int SuiteIndex);
void mmi_java_getPermission_req(int SuiteIndex);
void mmi_java_setPermission_req(int SuiteIndex, java_permission_setting *ps);
void mmi_java_getMidletCount_req(int SuiteIndex);
void mmi_java_getMidletInfo_req(int SuiteIndex, int MidletIndex);
void mmi_java_launchMidlet_req(int SuiteIndex, int MidletIndex, java_LanuchCause cause);

void mmi_java_checkMidletSuite_req(u16 *jadPath, u16 *jarPath, u8 nStorage);
void mmi_java_installMidletSuite_req(u16 *jadPath, u16 *jarPath, int KeepRMS, s32 oldId, mmi_java_storage_e storage);
void mmi_java_cancelInstallMidletSuite_req(void);

void mmi_java_setInstallProgress_rsp(u32 select_key);
void mmi_java_drawInstallDialog_rsp(u32 select_key, mmi_ams_DrawInstallDialogReq_t *pData);

void mmi_java_httpDonwload_req(u16 *u16Http, u16 *u16FileName);

void mmi_java_registerAlarm_rsp(int retCode, mmi_ams_PushAlarmReq_t *pData);
void mmi_java_deregisterAlarm_rsp(int retCode, mmi_ams_PushAlarmReq_t *pData);
void mmi_java_registerPort_rsp(int retCode, mmi_ams_PushPortReq_t *pData);
void mmi_java_deregisterPort_rsp(int retCode, mmi_ams_PushPortReq_t *pData);

#ifdef __JAVA_OAKMONT_NFC_PUSH_SUPPORT__
void mmi_java_registerNDEF_rsp(int retCode, mmi_ams_PushNDEFReq_t *pData);
void mmi_java_DeregisterNDEF_rsp(int retCode, mmi_ams_PushNDEFReq_t *pData);
#endif

void mmi_java_queryIndex_req(int SuiteId);
#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
void mmi_java_setNetProfile_req(int nCurSimCard);
void mmi_java_rstNetProfile_req(void);
#ifdef __NCC_3RD_JAVA_WITH_PREINSTALL__
void mmi_java_rstPreinstall_req(void);
#endif
#endif
#ifdef __JAVA_OAKMONT__
void mmi_java_set_mem_card_status_req(boolean bPlugin);
#endif
#endif /* __JAVA_MMI__ */
#endif /* __MMI_REQ_JAVA_H__ */
