/**
* @file    mmi_srv_java.h
* @brief   
*          
*
* @author  
* @version $Id:
*/

#ifndef __MMI_SRV_JAVA_H__
#define __MMI_SRV_JAVA_H__


/*-----------------------------------------------------*/

#include "mmi_srv_client_commondefine.h"

#ifdef __JAVA_MMI__
#include "mmi_javasrv.h"

/** SRV_JAVA EV and Callback Function description
* @brief  The interface of Service Client is used to set the indicator-callback to CB module
* 
* JAVASRV_MASK_AMS
* Group
* JAVASRV_EVT_Set_Install_Progress_Req
* JAVASRV_EVT_Draw_Install_Dialog_Req
* JAVASRV_EVT_Check_Midlet_Ind
* JAVASRV_EVT_Install_Midlet_Ind
*/

typedef void (* SrvJavaInstallProgressReqNotify_CB)(void *pThis, u32 param1, u32 param2); 
/** SrvJavaSetInstallProgressReqNotifyCB
* @brief  The interface of Service Client is used to set CB to listen the request of the install progress
* 
* @param[in]      pfnCallBack             "JAVASRV_EVT_Set_Install_Progress_Req" CB func point
*/
void SrvJavaSetInstallProgressReqNotifyCB(SrvJavaInstallProgressReqNotify_CB pfnCallBack);

typedef void (* SrvJavaDrawInstallDialogReqNotify_CB)(void *pThis, u32 param1, u32 param2); 
/** SrvJavaSetDrawInstallDialogReqNotifyCB
* @brief  The interface of Service Client is used to set CB to listen the request of the draw install dialog
* 
* @param[in]      pfnCallBack             "JAVASRV_EVT_Draw_Install_Dialog_Req" CB func point
*/
void SrvJavaSetDrawInstallDialogReqNotifyCB(SrvJavaDrawInstallDialogReqNotify_CB pfnCallBack);

typedef void (* SrvJavaCheckMidletInd_CB)(void *pThis, u32 param1, u32 param2); 
/** SrvJavaSetCheckMidletIndCB
* @brief  The interface of Service Client is used to set CB to listen the indication of the midlet check
* 
* @param[in]      pfnCallBack             "JAVASRV_EVT_Check_Midlet_Ind" CB func point
*/
void SrvJavaSetCheckMidletIndCB(SrvJavaCheckMidletInd_CB pfnCallBack);

typedef void (* SrvJavaInstallMidletInd_CB)(void *pThis, u32 param1, u32 param2); 
/** SrvJavaSetInstallMidletIndCB
* @brief  The interface of Service Client is used to set CB to listen the indication of the midlet install
* 
* @param[in]      pfnCallBack             "JAVASRV_EVT_Install_Midlet_Ind" CB func point
*/
void SrvJavaSetInstallMidletIndCB(SrvJavaInstallMidletInd_CB pfnCallBack);

typedef void (* SrvJavaAmsInitCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Init_Cnf"
/** SrvJavaAmsInitReq
* @brief  The interface of Service Client is used to init AMS.
* 
* @param[in]      pfnCallBack             JAVASRV_EVT_Init_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsInitReq(SrvJavaAmsInitCB pfnCallBack);

typedef void (* SrvJavaAmsReleaseCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Release_Cnf"
/** SrvJavaAmsReleaseReq
* @brief  The interface of Service Client is used to release AMS.
* 
* @param[in]      pfnCallBack             JAVASRV_EVT_Release_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsReleaseReq(SrvJavaAmsReleaseCB pfnCallBack);

typedef void (* SrvJavaAmsGetSuiteCountCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Get_Suite_Count_Cnf"
/** SrvJavaAmsGetSuiteCountReq
* @brief  The interface of Service Client is used to get midlet suite count.
* 
* @param[in]      pfnCallBack             JAVASRV_EVT_Get_Suite_Count_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsGetSuiteCountReq(SrvJavaAmsGetSuiteCountCB pfnCallBack);

typedef void (* SrvJavaAmsGetSuiteInfoCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Get_Suite_Info_Cnf"
/** SrvJavaAmsGetSuiteInfoReq
* @brief  The interface of Service Client is used to get the midlet suite info for the specific suite index.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      pfnCallBack             JAVASRV_EVT_Get_Suite_Info_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsGetSuiteInfoReq(int nSuiteIndex, SrvJavaAmsGetSuiteInfoCB pfnCallBack);

typedef void (* SrvJavaAmsRemoveSuiteCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Remove_Suite_Cnf"
/** SrvJavaAmsRemoveSuiteReq
* @brief  The interface of Service Client is used to remove the midlet suite for the specific suite index.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      pfnCallBack             JAVASRV_EVT_Remove_Suite_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsRemoveSuiteReq(int nSuiteIndex, SrvJavaAmsRemoveSuiteCB pfnCallBack);

typedef void (* SrvJavaAmsGetPermissionCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Get_Permission_Cnf"
/** SrvJavaAmsGetPermissionReq
* @brief  The interface of Service Client is used to get the midlet permission for the specific suite index.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      pfnCallBack             JAVASRV_EVT_Get_Permission_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsGetPermissionReq(int nSuiteIndex, SrvJavaAmsGetPermissionCB pfnCallBack);

typedef void (* SrvJavaAmsSetPermissionCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Set_Permission_Cnf"
/** SrvJavaAmsSetPermissionReq
* @brief  The interface of Service Client is used to set the midlet permission for the specific suite index.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      ps                      Pointer to the permission setting.
* @param[in]      pfnCallBack             JAVASRV_EVT_Set_Permission_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsSetPermissionReq(int nSuiteIndex,
                                   java_permission_setting *ps,
                                   SrvJavaAmsSetPermissionCB pfnCallBack);

typedef void (* SrvJavaAmsGetMidletCountCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Get_Midlet_Count_Cnf"
/** SrvJavaAmsGetMidletCountReq
* @brief  The interface of Service Client is used to get the midlet count.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      pfnCallBack             JAVASRV_EVT_Get_Midlet_Count_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsGetMidletCountReq(int nSuiteIndex, SrvJavaAmsGetMidletCountCB pfnCallBack);

typedef void (* SrvJavaAmsGetMidletInfoCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Get_Midlet_Info_Cnf"
/** SrvJavaAmsGetMidletInfoReq
* @brief  The interface of Service Client is used to get the midlet info for the specific suite index and the midlet index.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      nMidletIndex            The midlet index of the request.
* @param[in]      pfnCallBack             JAVASRV_EVT_Get_Midlet_Info_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsGetMidletInfoReq(int nSuiteIndex,
                                   int nMidletIndex,
                                   SrvJavaAmsGetMidletInfoCB pfnCallBack);

#ifdef __NCC_3RD_JAVA_PORTING_LAYER__
typedef void (* SrvJavaAmsSetJavaNetProfileCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Set_Java_Net_Profile_Cnf"
/** SrvJavaAmsSetJavaNetProfileReq
* @brief
*
* @param[in]      pfnCallBack             JAVASRV_EVT_Set_Java_Net_Profile_Cnf CB func point.
*
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvJavaAmsSetJavaNetProfileReq(int nCurSimCard);

typedef void (* SrvJavaAmsRstPreinstallReqCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Set_Java_Net_Profile_Cnf"
/** SrvJavaAmsSetJavaNetProfileReq
* @brief
*
* @param[in]      pfnCallBack             JAVASRV_EVT_Set_Java_Net_Profile_Cnf CB func point.
*
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvJavaAmsRstPreinstallReq(SrvJavaAmsRstPreinstallReqCB pfnRstPreinstallCnfCallBack);

typedef void (* SrvJavaAmsRstNetProfileReqCB)(void *pThis, u32 param1, u32 param2);
/** SrvJavaAmsRstNetProfileReq
* @brief
*
* @param[in]      pfnCallBack             JAVASRV_EVT_RST_Java_NetProfile_Cnf CB func point.
*
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request.
*/
MAE_Ret SrvJavaAmsRstNetProfileReq(SrvJavaAmsRstNetProfileReqCB pfnRstNetProfileCnfCallBack); ////refer to post "JAVASRV_EVT_RST_Java_NetProfile_Cnf"
#endif

typedef void (* SrvJavaAmsLaunchMidletCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Launch_Midlet_Cnf"
/** SrvJavaAmsLaunchMidletReq
* @brief  The interface of Service Client is used to launch the midlet for the specific suite index and the midlet index.
* 
* @param[in]      nSuiteIndex             The suite index of the request.
* @param[in]      nMidletIndex            The midlet index of the request.
* @param[in]      pfnCallBack             JAVASRV_EVT_Launch_Midlet_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsLaunchMidletReq(int nSuiteIndex,
                                     int nMidletIndex,
                                     SrvJavaAmsLaunchMidletCB pfnCallBack);

typedef void (* SrvJavaAmsCheckMidletCnfCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Check_Midlet_Cnf"
typedef void (* SrvJavaAmsCheckMidletIndCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Check_Midlet_Ind"
/** SrvJavaAmsCheckMidletReq
* @brief  The interface of Service Client is used to check the midlet.
* 
* @param[in]      pJadPath                            The URL path of JAD.
* @param[in]      pJarPath                            The URL path of JAR.
* @param[in]      pfnChkMidletCnfCallBack             JAVASRV_EVT_Check_Midlet_Cnf CB func point.
* @param[in]      pfnChkMidletIndCallBack             JAVASRV_EVT_Check_Midlet_Ind CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsCheckMidletReq(u16 *pJadPath,
                                 u16 *pJarPath,
                                 SrvJavaAmsCheckMidletCnfCB pfnChkMidletCnfCallBack,
                                 SrvJavaAmsCheckMidletIndCB pfnChkMidletIndCallBack);
/** SrvJavaAmsCheckMidletReqEx
* @brief  The interface of Service Client is used to check the midlet with storage.
* 
* @param[in]      pJadPath                            The URL path of JAD.
* @param[in]      pJarPath                            The URL path of JAR.
* @param[in]      nStorage                            The Storage that user wanna install.
* @param[in]      pfnChkMidletCnfCallBack             JAVASRV_EVT_Check_Midlet_Cnf CB func point.
* @param[in]      pfnChkMidletIndCallBack             JAVASRV_EVT_Check_Midlet_Ind CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsCheckMidletReqEx(u16 *pJadPath,
                                 u16 *pJarPath,
                                 u8 nStorage,
                                 SrvJavaAmsCheckMidletCnfCB pfnChkMidletCnfCallBack,
                                 SrvJavaAmsCheckMidletIndCB pfnChkMidletIndCallBack);

typedef void (* SrvJavaAmsInstallMidletCnfCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Install_Midlet_Cnf"
typedef void (* SrvJavaAmsInstallMidletIndCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Install_Midlet_Ind"
/** SrvJavaAmsInstallMidletReq
* @brief  The interface of Service Client is used to install the midlet.
* 
* @param[in]      pJadPath                                The URL path of JAD.
* @param[in]      pJarPath                                The URL path of JAR.
* @param[in]      nKeepRMS                                if keep RMS data or not.
* @param[in]      nOldId                                  The old id of the request.
* @param[in]      pfnInstMidletCnfCallBack                JAVASRV_EVT_Install_Midlet_Cnf CB func point.
* @param[in]      pfnInstMidletIndCallBack                JAVASRV_EVT_Install_Midlet_Ind CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsInstallMidletReq(u16 *pJadPath,
                                      u16 *pJarPath,
                                      int nKeepRMS,
                                      s32 nOldId,
                                      u8 nStorage,
                                      SrvJavaAmsInstallMidletCnfCB pfnInstMidletCnfCallBack,
                                      SrvJavaAmsInstallMidletIndCB pfnInstMidletIndCallBack);

typedef void (* SrvJavaAmsCancelInstallMidetCB)(void *pThis, u32 param1, u32 param2); //refer to post "JAVASRV_EVT_Cancel_Install_Cnf"
/** SrvJavaAmsCancelInstallMidetReq
* @brief  The interface of Service Client is used to cancel installing AMS midlet.
* 
* @param[in]      pfnCallBack             JAVASRV_EVT_Cancel_Install_Cnf CB func point.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsCancelInstallMidetReq(SrvJavaAmsCancelInstallMidetCB pfnCallBack);

/** SrvJavaAmsSetInstallProgressRsp
* @brief  The interface of Service Client is used to reponse the AMS install progress for the "JAVASRV_EVT_Set_Install_Progress_Req".
* 
* @param[in]      nSelect_key             The key id of the request.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsSetInstallProgressRsp(u32 nSelect_key);

/** SrvJavaAmsDrawInstallDialogRsp
* @brief  The interface of Service Client is used to reponse AMS draw dialog for the "JAVASRV_EVT_Draw_Install_Dialog_Req".
* 
* @param[in]      nSelect_key             The key id of the request.
* @param[in]      pData                   Pointer to the response data;it's the same as the request data for the identification.
* 
* @retval MAE_RET_SUCCESS                 If successful.
* @retval MAE_RET_NOT_SUPPORTED           If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvJavaAmsDrawInstallDialogRsp(u32 nSelect_key,
                                          mmi_ams_DrawInstallDialogReq_t *pData);


/*-----------------------------------------------------*/
#endif // __JAVA_MMI__

#endif /* __MMI_SRV_JAVA_H__ */
