/**
* @file    mmi_srv_vendor.h
* @brief
*
*/

#ifndef __MMI_SRV_VENDOR_H__
#define __MMI_SRV_VENDOR_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_vendorsrv.h"

//Specific Service ListenerCallBack API
typedef void (*SrvVendorCB)(void *pThis, u32 *pNotifier);

/** SrvVendorSetVideoStreamPlayCB
* @brief  Set the callback function to execute when VENSRV_EVT_VIDEOSTREAM_PLAY event happen
*
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetVideoStreamPlayCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetVideoStreamStopCB
* @brief  Set the callback function to execute when VENSRV_EVT_VIDEOSTREAM_STOP event happen
*
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetVideoStreamStopCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetVideoSeekOnOffCB
* @brief  Set the callback function to execute when VENSRV_EVT_VIDEOSEEK_ONOFF event happen
*
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetVideoSeekOnOffCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetVideoPlayCB
* @brief  Set the callback function to execute when VENSRV_EVT_VIDEO_PLAY event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetVideoPlayCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetPHBBroseCB
* @brief  Set the callback function to execute when VENSRV_EVT_PHB_BROWSE event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetPHBBroseCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetFileBroseCB
* @brief   Set the callback function to execute when VENSRV_EVT_FILE_BROWSE event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetFileBroseCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetFileBrowseExCB
* @brief   Set the callback function to execute when VENSRV_EVT_FILE_BROWSE_EX event happen
*
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetFileBrowseExCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetFileSelectFolderCB
* @brief   Set the callback function to execute when VENSRV_EVT_FILE_SELECT_FOLDER event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetFileSelectFolderCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetSenBtAppSendFileCB
* @brief   Set the callback function to execute when VENSRV_EVT_SEN_BTAPP_SEND_FILE event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetSenBtAppSendFileCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetCamLaunchAppCB
* @brief   Set the callback function to execute when VENSRV_EVT_CAM_LAUNCH_APP event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetCamLaunchAppCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetCCMakeCallCB
* @brief  Set the callback function to execute when VENSRV_EVT_CC_MAKECALL event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetCCMakeCallCB(SrvVendorCB pfnCallBack);

#ifdef __SDK_API_01_SMS_MMS_CC__
/** SrvVendorSetCCMakeCallGetCallIDCB
* @brief  Set the callback function to execute when VENSRV_EVT_CC_MAKECALL_GET_CALL_ID event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetCCMakeCallGetCallIDCB(SrvVendorCB pfnCallBack);


/** SrvVendorSetCCReleaseCallCB
* @brief  Set the callback function to execute when VENSRV_EVT_CC_RELEASECALL event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetCCReleaseCallCB(SrvVendorCB pfnCallBack);
#endif //#ifdef __SDK_API_01_SMS_MMS_CC__

/** SrvVendorSetEditorEditCB
* @brief  Set the callback function to execute when VENSRV_EVT_EDITOR_EDIT event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetEditorEditCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetEditorCloseCB
* @brief  Set the callback function to execute when VENSRV_EVT_EDITOR_CLOSE event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetEditorCloseCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetEditorDateCB
* @brief  Set the callback function to execute when VENSRV_EVT_EDITOR_DATE event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetEditorDateCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetEditorEditCB
* @brief  Set the callback function to execute when VENSRV_EVT_EDITOR_TIME event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetEditorTimeCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetSelectSIMCB
* @brief  Set the callback function to execute when VENSRV_EVT_SELECT_SIM event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetSelectSIMCB(SrvVendorCB pfnCallBack);

/** SrvVendorMsgEditorEditCB
* @brief    Set the callback function to execute when VENSRV_EVT_MSG_EDITOR_EDIT event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetMsgEditorEditCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetOpenBrowserCB
* @brief   Set the callback function to execute when VENSRV_EVT_OPEN_BROWSER event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetOpenBrowserCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetStartRspCB
* @brief    Set the callback function to execute when VENSRV_EVT_START_RSP event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetStartRspCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetExitRspCB
* @brief   Set the callback function to execute when VENSRV_EVT_EXIT_RSP event happen
* 
* @param[in]      pfnCallBack             Callback function 
*/
void SrvVendorSetExitRspCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetSuspendRspCB
* @brief    Set the callback function to execute when VENSRV_EVT_SUSPEND_RSP event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetSuspendRspCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetResumeRspCB
* @brief    Set the callback function to execute when VENSRV_EVT_RESUME_RSP event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetResumeRspCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetBackgroundRspCB
* @brief    Set the callback function to execute when VENSRV_EVT_BACKGROUND_RSP event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetBackgroundRspCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetForegroundRspCB
* @brief    Set the callback function to execute when VENSRV_EVT_FOREGROUND_RSP event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetForegroundRspCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetStopCB
* @brief    Set the callback function to execute when VENSRV_EVT_STOP_IND event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetStopCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetStartCB
* @brief    Set the callback function to execute when VENSRV_EVT_START_IND event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetStartCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetItemVISSetCB
* @brief    Set the callback function to execute when VENSRV_EVT_SET_ITEM_VIS event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetItemVISSetCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetItemVISGetCB
* @brief    Set the callback function to execute when VENSRV_EVT_GET_ITEM_VIS event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetItemVISGetCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetDisplayModeSetCB
* @brief    Set the callback function to execute when VENSRV_EVT_SET_DISPLAY_MODE event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetDisplayModeSetCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetShowUICB
* @brief   Set the callback function to execute when VENSRV_EVT_SHOW_UI event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetShowUICB(SrvVendorCB pfnCallBack);

/** SrvVendorSetShowUICB
* @brief   Set the callback function to execute when VENSRV_EVT_CLOSE_UI event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetCloseUICB(SrvVendorCB pfnCallBack);

/** SrvVendorSetUpdateUICB
* @brief   Set the callback function to execute when VENSRV_EVT_UPDATE_UI event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetUpdateUICB(SrvVendorCB pfnCallBack);

/** SrvVendorSetUIIntLevelCB
* @brief   Set the callback function to execute when VENSRV_EVT_SET_UI_INT_LEVEL event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetUIIntLevelCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetUIBlkCB
* @brief   Set the callback function to execute when VENSRV_EVT_SET_UI_BLK event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetUIBlkCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetKillIndCB
* @brief   Set the callback function to execute when VENSRV_EVT_KILL_IND event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetKillIndCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetBackgroundIndCB
* @brief   Set the callback function to execute when VENSRV_EVT_BACKGROUND_IND event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetBackgroundIndCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetForegroundIndCB
* @brief   Set the callback function to execute when VENSRV_EVT_FOREGROUND_IND event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetForegroundIndCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetUIStatusBarDrawIconCB
* @brief   Set the callback function to execute when VENSRV_EVT_UI_STATUSBAR_DRAW_ICON event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetUIStatusBarDrawIconCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetRestUIBlkCB
* @brief   Set the callback function to execute when VENSRV_EVT_RESET_UI_BLK event happen
* 
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetRestUIBlkCB(SrvVendorCB pfnCallBack);

/** SrvVendorSetEnableLaunchKeyguardCB
* @brief   Set the callback function to execute when VENSRV_EVT_ENABLE_LAUNCH_KEYGUARD event happen
*
* @param[in]      pfnCallBack             Callback function
*/
void SrvVendorSetEnableLaunchKeyguardCB(SrvVendorCB pfnCallBack);

/** SrvVendorStartVen
* @brief
* 
* @param[in]      nAppID
* @param[in]      pHandle
* @param[in]      pStartParam
*/
void SrvVendorStartVen(Mmi_VenAppID_t nAppID, u32 *pHandle, mmi_ven_start_param_t *pStartParam);


/** SrvVendorExitVen
* @brief
* 
* @param[in]      handle
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_FAILED        If Cannot find user handle.
*/
MAE_Ret SrvVendorExitVen(u32 handle);

/** SrvVendorSuspendVen
* @brief
* 
* @param[in]      handle
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_FAILED        If Cannot find user handle.
*/
MAE_Ret SrvVendorSuspendVen(u32 handle);

/** SrvVendorResumeVen
* @brief
* 
* @param[in]      handle
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_FAILED        If Cannot find user handle.
*/
MAE_Ret SrvVendorResumeVen(u32 handle);

/** SrvVendorTouchInd
* @brief
* 
* @param[in]      handle
* @param[in]      nEvt            value like MAE_EVT_TS_PRESS (defined in mae_event.h)
* @param[in]      nX
* @param[in]      nY
* 
* @retval MAE_RET_SUCCESS         If successful.
* @retval MAE_RET_FAILED          If Cannot find user handle.
*/
MAE_Ret SrvVendorTouchInd(u32 handle, u32 nEvt, u32 nX, u32 nY);

/** SrvVendorMakeCallEnd
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]	retCode, execute status, sucessful or failed
*/
void SrvVendorMakeCallEnd(u32 handle, u32 session, MAE_Ret retCode);

/** SrvVendorMakeCallGetCallIDEnd
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]	retCode, execute status, sucessful or failed
* @param[in]	state, the calling state, such as start making a call or call get through
* @param[in]      callID, as a represent ID of a successful call, can be used as a parameter to release(hang up) an on-going call.
*/
void SrvVendorMakeCallGetCallIDEnd(u32 handle, u32 session, MAE_Ret retCode, s32 state, s32 callID);

/** SrvVendorReleaseCallRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      nResult
*/
void SrvVendorReleaseCallRsp(u32 handle, u32 session, MAE_Ret nResult);

/** SrvVendorVideoPlayRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      nResult
*/
void SrvVendorVideoPlayRsp(u32 handle, u32 session, MAE_Ret nResult);

/** SrvVendorVideoPlayRsp
* @brief
*
* @param[in]      param1
* @param[in]      param2
*/
void SrvVendorVideoUpdateStatus(u32 handle, u32 session, mmi_ven_video_status_e eStatus, u32 nStatusData);

/** SrvVendorEditorRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      pContent
* @param[in]      nStrLen
* @param[in]      nResult
*/
void SrvVendorEditorRsp(u32 handle, u32 session, MAE_WChar *pContent, u16 nStrLen, editor_reult_t nResult);

/** SrvVendorEditorRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      pContent
* @param[in]      nStrLen
* @param[in]      nResult
*/
void SrvVendorDateEditorRsp(u32 handle, u32 session, u16 nYear, u8 nMonth, u8 nDay, editor_reult_t nResult);

/** SrvVendorEditorRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      pContent
* @param[in]      nStrLen
* @param[in]      nResult
*/
void SrvVendorTimeEditorRsp(u32 handle, u32 session, u8 nHour, u8 nMinute, u8 nSecond, editor_reult_t nResult);

/** SrvVendorPhbBrowseRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      pData
* @param[in]      nStrLen
* @param[in]      nMarkedSize
*/
void SrvVendorPhbBrowseRsp(u32 handle, u32 session, MAE_WChar *pData, u16 nStrLen, u8 nMarkedSize);

/** SrvVendorFileBrowseRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      pData
* @param[in]      nStrLen
* @param[in]      nMarkedSize
*/
void SrvVendorFileBrowseRsp(u32 handle, u32 session, MAE_WChar *pData, u16 nStrLen, u8 nMarkedSize);

/** SrvVendorFileBrowseExRsp
* @brief
*
* @param[in]      handle
* @param[in]      session
* @param[in]      pData
* @param[in]      nStrLen
* @param[in]      nMarkedSize
*/
void SrvVendorFileBrowseExRsp(u32 handle, u32 session, MAE_WChar *pData, u16 nStrLen, u8 nMarkedSize);

void SrvVendorFileSelectFolderRsp(u32 handle, u32 session, MAE_WChar *pData, u16 nStrLen);

void SrvVendorSenBtAppSendFileRsp(u32 handle, u32 session, MAE_Ret retCode);

/** SrvVendorCamLaunchAppRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      nResult
*/
void SrvVendorCamLaunchAppRsp(u32 handle, u32 session, void *pData);

/** SrvVendorSelectSIMRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      nSelectSIM
* @param[in]      nSelectRet
*/
void SrvVendorSelectSIMRsp(u32 handle, u32 session, mmi_ven_select_sim_t nSelectSIM, MAE_Ret nSelectRet);

/** SrvVendorOpenBrowserRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      nResult
*/
void SrvVendorOpenBrowserRsp(u32 handle, u32 session, MAE_Ret nResult);

/** SrvVendorBackgroundVen
* @brief			Put vendor into background execution
* 
* @param[in]      handle
* @param[in]      pData
* @param[in]      dataLen
*/
MAE_Ret SrvVendorBackgroundVen(u32 handle, void * pData, u32 dataLen);

/** SrvVendorForegroundVen
* @brief			Bring vendor to foreground execution
* 
* @param[in]      handle
* @param[in]      pData
* @param[in]      dataLen
*/
MAE_Ret SrvVendorForegroundVen(u32 handle, void * pData, u32 dataLen);

/** SrvVendorGetVenFrameBuffer
* @brief			Get vendor's display frame buffer from SDK display manager
* 
* @param[in]      handle
* @param[in]      ppBitmapBase
*/
MAE_Ret SrvVendorGetVenFrameBuffer(u32 handle, BitmapBase_t **ppBitmapBase);

/** SrvVendorKillVenByID
* @brief			Request VendorSrv to kill a given VendorApp
* 
* @param[in]      apID
* @param[in]      pIssuer
* @param[in]      pFnCB
*/
MAE_Ret SrvVendorKillVenByID(Mmi_VenAppID_t apID, IBase * pIssuer, fnVenSrvKillCBPtr pFnCB, u32 usrData);

/** SrvVendorKillVenByPriority
* @brief			Request VendorSrv to kill a given VendorApp
* 
* @param[in]      apID
* @param[in]      pIssuer
* @param[in]      pFnCB
*/
MAE_Ret SrvVendorKillVenByPriority(IBase * pIssuer, fnVenSrvKillCBPtr pFnCB, u32 usrData);

/** SrvVendorGetVenNameByID
* @brief			Get vendor's display name by id.
* 
* @param[in]      apID
* @param[in]      ppName
*/
MAE_Ret SrvVendorGetVenNameByID(Mmi_VenAppID_t apID, MAE_WChar **ppName);

/** SrvVendorMsgEditorRsp
* @brief
* 
* @param[in]      handle
* @param[in]      session
* @param[in]      nResult
*/
void SrvVendorMsgEditorRsp(u32 handle, u32 session, MAE_Ret nResult);

#endif /*__MMI_SRV_VENDOR_H__*/
