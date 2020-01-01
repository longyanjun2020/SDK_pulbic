#ifndef __JAVA_AMS_ITF_H__
#define __JAVA_AMS_ITF_H__

#include "java_ams.h"

enum
{
    JAVA_AMS_INIT = 0,
    JAVA_AMS_RELEASE,
    JAVA_AMS_GET_SUITE_COUNT,
    JAVA_AMS_GET_SUITE_INFO,
    JAVA_AMS_REMOVE_SUITE,
    JAVA_AMS_GET_PERMISSION,
    JAVA_AMS_SET_PERMISSION,
    JAVA_AMS_GET_MIDLET_COUNT,
    JAVA_AMS_GET_MIDLET_INFO,
    JAVA_AMS_LAUNCH_MIDLET,
    JAVA_AMS_CHECK_MIDLET_SUITE_IND,
    JAVA_AMS_CHECK_MIDLET_SUITE,
    JAVA_AMS_INSTALL_MIDLET_SUITE_IND,
    JAVA_AMS_INSTALL_MIDLET_SUITE,
    JAVA_AMS_SET_INSTALL_PROGRESS,
    JAVA_AMS_DRAW_INSTALL_DIALOG,
    JAVA_AMS_HTTP_DOWNLOAD,
    JAVA_AMS_GET_LOGO_IMAGE,
    JAVA_AMS_CANCEL_INSTALL_MIDLET,

    JAVA_PUSH_REGISTER_ALARM,
    JAVA_PUSH_DEREGISTER_ALARM,
    JAVA_PUSH_REGISTER_PORT,
    JAVA_PUSH_DEREGISTER_PORT,
    JAVA_PUSH_QUERY_INDEX,

    JAVA_ACCESSORY_MEM_CARD_STATUS,
};

typedef u8 Jams_cmd_type;

typedef struct
{
	u32 pad;
}Jams_InitReq_t;

typedef struct
{
	int retCode;
}Jams_InitRsp_t;

typedef struct
{
	u32 pad;
}Jams_ReleaseReq_t;

typedef struct
{
	int retCode;
}Jams_ReleaseRsp_t;

typedef struct
{
	u32 pad;
}Jams_GetSuiteCntReq_t;

typedef struct
{
	int retCode;
	int suiteCount;
}Jams_GetSuiteCntRsp_t;

typedef struct
{
	int suiteIndex;
}Jams_GetSuiteInfoReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
	java_suite_struct suiteInfo;
}Jams_GetSuiteInfoRsp_t;

typedef struct
{
	int suiteIndex;
}Jams_RemoveSuiteReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
}Jams_RemoveSuiteRsp_t;

typedef struct
{
	int suiteIndex;
}Jams_GetPermissionReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
	java_permission_setting PermissionInfo;
}Jams_GetPermissionRsp_t;

typedef struct
{
	int suiteIndex;
   	java_permission_setting PermissionInfo;
}Jams_SetPermissionReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
	java_permission_setting PermissionInfo;
}Jams_SetPermissionRsp_t;

typedef struct
{
	int suiteIndex;
}Jams_GetMidletCntReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
	int midletCount;
}Jams_GetMidletCntRsp_t;

typedef struct
{
	int suiteIndex;
	int midletIndex;
}Jams_GetMidletInfoReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
	int midletIndex;
	java_midlet_struct MidletInfo;
}Jams_GetMidletInfoRsp_t;

typedef struct
{
	int suiteIndex;
	int midletIndex;
	java_LanuchCause cause;
}Jams_LaunchMidletReq_t;

typedef struct
{
	int retCode;
	int suiteIndex;
	int midletIndex;
}Jams_LaunchMidletRsp_t;

typedef struct
{
    u16 *jadPath;
    u16 *jarPath;
    java_install_storage_e storage;
} Jams_CheckMidletSuiteReq_t;

typedef struct
{
    java_CheckResult Result;
    int total;
    int step;
} Jams_checkMidletSuiteInd_t;

typedef struct
{
    int retCode;
} Jams_checkMidletSuiteRsp_t;

typedef struct
{
    u16 *jadPath;
    u16 *jarPath;
    int keepRMS;
    int oldId;
    java_install_storage_e storage;
} Jams_InstallMidletSuiteReq_t;

typedef struct
{
    java_InstallResult Result;
    int total;
    int step;
} Jams_InstallMidletSuiteInd_t;

typedef struct
{
    int retCode;
	int installSuiteId;
} Jams_InstallMidletSuiteRsp_t;

typedef struct
{
    int percentage;
    u32 softkey;
} Jams_SetInstallProgressReq_t;

typedef struct
{
    u32 selected_key;
} Jams_SetInstallProgressRsp_t;


typedef struct
{
    u32 SemID;

    int jamMsgID;
    u16* pMsgString;
    u32 softkey;
    u32 *selected_key;
} Jams_DrawInstallDialogReq_t;

typedef struct
{
	u8  bAbort;
    u16 u16Http[256];
    u16 u16FilePath[256];
} Jams_HttpDownloadReq_t;

typedef struct
{
    int retCode;
    u16 u16FileName[256];
} Jams_HttpDownloadRsp_t;

typedef struct
{
    u32 pad;
} Jams_GetLogoImageReq_t;

typedef struct
{
    int retCode;
    u32 pImageRawData;
    u32 u32DataLen;
} Jams_GetLogoImageRsp_t;

typedef struct
{
    int suiteId;
    int midletId;
    unsigned long TimeH;
    unsigned long TimeL;

    u32 SemID;
    int *retCode;
} Jams_ReqisterAlarmReq_t,Jams_DereqisterAlarmReq_t;

typedef struct
{
    int suiteId;
    int midletId;
    int port;

    u32 SemID;
    int *retCode;
} Jams_ReqisterPortReq_t,Jams_DereqisterPortReq_t;

typedef struct
{
    int suiteId;
} Jams_QueryIndexReq_t;

typedef struct
{
    int suiteId;
    int suiteIndex;
} Jams_QueryIndexRsp_t;

typedef struct
{
    bool bPlugin;
} Jams_AccessoryMemCardStatus_t;

typedef union
{
   Jams_InitReq_t   		amsInitReq;
   Jams_ReleaseReq_t   		amsReleaseReq;
   Jams_GetSuiteCntReq_t	amsGetSuiteCntReq;
   Jams_GetSuiteInfoReq_t	amsGetSuiteInfoReq;
   Jams_RemoveSuiteReq_t	amsRemoveSuiteReq;
   Jams_GetPermissionReq_t	amsGetPermissionReq;
   Jams_SetPermissionReq_t	amsSetPermissionReq;
   Jams_GetMidletCntReq_t	amsGetMidletCntReq;
   Jams_GetMidletInfoReq_t	amsGetMidletInfoReq;
   Jams_LaunchMidletReq_t	amsLaunchMidletReq;
   Jams_CheckMidletSuiteReq_t amsCheckMidletSuiteReq;
   Jams_InstallMidletSuiteReq_t amsInstallMidletSuiteReq;

   Jams_SetInstallProgressRsp_t amsSetProgressRsp;
   Jams_HttpDownloadReq_t	amsHttpDownloadReq;
   Jams_GetLogoImageRsp_t amsGetLogoImgRsp;
   Jams_QueryIndexReq_t	amsQueryIndexReq;
   Jams_AccessoryMemCardStatus_t amsAccMemCardStatus;
} Jams_req_data_t;


typedef union
{
   Jams_InitRsp_t   			amsInitRsp;
   Jams_ReleaseRsp_t   		amsReleaseRsp;
   Jams_GetSuiteCntRsp_t	amsGetSuiteCntRsp;
   Jams_GetSuiteInfoRsp_t	amsGetSuiteInfoRsp;
   Jams_RemoveSuiteRsp_t	amsRemoveSuiteRsp;
   Jams_GetPermissionRsp_t	amsGetPermissionRsp;
   Jams_SetPermissionRsp_t	amsSetPermissionRsp;
   Jams_GetMidletCntRsp_t	amsGetMidletCntRsp;
   Jams_GetMidletInfoRsp_t	amsGetMidletInfoRsp;
   Jams_LaunchMidletRsp_t	amsLaunchMidletRsp;
   Jams_checkMidletSuiteInd_t amsCheckMidletSuiteInd;
   Jams_checkMidletSuiteRsp_t amsCheckMidletSuiteRsp;
   Jams_InstallMidletSuiteInd_t amsInstallMidletSuiteInd;
   Jams_InstallMidletSuiteRsp_t amsInstallMidletSuiteRsp;

   Jams_SetInstallProgressReq_t	amsSetProgressReq;
   Jams_DrawInstallDialogReq_t	amsDrawDialogReq;
   Jams_HttpDownloadRsp_t		amsHttpDownloadRsp;
   Jams_GetLogoImageReq_t		amsGetLogoImgReq;

   Jams_ReqisterAlarmReq_t		amsRegisterAlarmReq;
   Jams_DereqisterAlarmReq_t	amsDeregisterAlarmReq;
   Jams_ReqisterPortReq_t		amsRegisterPortReq;
   Jams_DereqisterPortReq_t		amsDeregisterPortReq;
   Jams_QueryIndexRsp_t		amsQueryIndexRsp;
 } Jams_rsp_data_t;

typedef struct
{
	Jams_cmd_type 	cmdType;
	Jams_req_data_t	cmdData;
}Jams_req_t;

typedef struct
{
	Jams_cmd_type 	cmdType;
	Jams_rsp_data_t	rspData;
}Jams_rsp_t;


#endif /*__JAVA_AMS_ITF_H__*/
