/**
 * @file    mmi_if_java.h
 * @brief   The file handles the java event with java task
 * @author  christine.tai@mstarsemi.com
 *
 */
#ifndef __MMI_IF_JAVA_H__
#define __MMI_IF_JAVA_H__

#ifdef __JAVA_MMI__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "java_ams_itf.h"

#ifdef _MSIM_
//#define __JAVA_SIMULATE__
#endif

// Java error code, refer to java_ams.h
#define MMI_JAVA_OK              0 // OK
#define MMI_JAVA_FAIL            1 // Fail or Error
#define MMI_JAVA_AMSLIST_FULL    2 // AMS list is full
#define MMI_JAVA_LARGE_JAR       3 // JAR size is too large
#define MMI_JAVA_NO_ENOUGH_SPACE 4 // No enough space for AMS operation

#define MMI_JAVA_REINIT_BUSY     7 //

typedef struct
{
	int suiteIndex;
	java_suite_struct suiteInfo;
}mmi_ams_GetSuiteInfoRsp_t;

typedef struct
{
	int suiteIndex;
	java_permission_setting PermissionInfo;
}mmi_ams_GetPermissionRsp_t;

typedef struct
{
	int suiteIndex;
	java_permission_setting PermissionInfo;
}mmi_ams_SetPermissionRsp_t;

typedef struct
{
	int suiteIndex;
	int midletCount;
}mmi_ams_GetMidletCntRsp_t;

typedef struct
{
	int suiteIndex;
	int midletIndex;
	java_midlet_struct MidletInfo;
}mmi_ams_GetMidletInfoRsp_t;

typedef struct
{
	int suiteIndex;
	int midletIndex;
}mmi_ams_LaunchMidletRsp_t;

typedef struct
{
    s32    otaCode;
    s32    update;
    s32    trusted;
    s32    oldId;
} mmi_ams_CheckResult_t;

typedef struct
{
    s32    otaCode;
    s32    suiteIndex;
} mmi_ams_InstallResult_t;

typedef struct
{
    u32 SemID;

    int jamMsgID;
    u16* pMsgString;
    u32 softkey;

    u32 *selected_key;
} mmi_ams_DrawInstallDialogReq_t;

typedef struct
{
    int suiteId;
    int midletId;
    unsigned long TimeH;
    unsigned long TimeL;

    u32 SemID;
    int *retCode;
} mmi_ams_PushAlarmReq_t;

typedef struct
{
    int suiteId;
    int midletId;
    int port;

    u32 SemID;
    int *retCode;
} mmi_ams_PushPortReq_t;

#ifdef __JAVA_OAKMONT_NFC_PUSH_SUPPORT__
typedef struct
{
    int suiteId;
    int midletId;
    //int port;
    unsigned char* protocol;
    unsigned char* filter;    

    u32 SemID;
    int *retCode;
} mmi_ams_PushNDEFReq_t;
#endif

typedef struct
{
    u16 u16FileName[256];
} mmi_ams_HttpDownloadRsp_t;

void mmi_java_msg_parser(IBase* pRecipient, struct vm_msg *pData);

void mmi_java_user_extend_rsp_if(IBase* pRecipient, struct vm_msg *pData);

void mmi_java_clean_suite_info_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_permission_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_midlet_cnt_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_midlet_info_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_launch_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_check_ind(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_install_ind(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_DataModelFree(IBase* pOwner, u32 lParam, u32 dParam);
void mmi_java_clean_http_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_push_alarm_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
void mmi_java_clean_push_port_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);

#ifdef __JAVA_OAKMONT_NFC_PUSH_SUPPORT__
void mmi_java_clean_push_ndef_cnf(IBase* pIssuer, u32 nParam1, u32 nParam2);
#endif    

#endif // __JAVA_MMI__

#endif /* __MMI_IF_JAVA_H__ */
