/**
* @file    mmi_srv_stk.h
* @brief   
*          
*
* @author  
* @version $Id: 
*/

#ifndef __MMI_SRV_STK_H__
#define __MMI_SRV_STK_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_stksrv.h"


//Specific Service ListenerCallBack API

// STKSRV_SETUP_IDLE_TEXT
typedef void (*SrvStkSetupIdleTextCB)(void *pThis, MAE_WChar *pText, u32 nDual); //STKSRV_EVT_SetupIdleTextInd

// STKSRV_REFRESH
typedef void (*SrvStkRefreshIndCB)(void *pThis, STKSRV_RefreshType_e eType, u32 nDual); //STKSRV_EVT_RefreshInd

// other 
typedef void (* SrvStkDisplayTextCB)(void *pThis, u32 nDual); //STKSRV_EVT_DisplayTextInd
typedef void (* SrvStkGetInkeyCB)(void *pThis, u32 nDual); //STKSRV_EVT_GetInkeyInd
typedef void (* SrvStkGetInputCB)(void *pThis, u32 nDual); //STKSRV_EVT_GetInputInd
typedef void (* SrvStkSetupCallCB)(void *pThis, u32 nDual); //STKSRV_EVT_SetupCallInd
typedef void (* SrvStkPlayToneCB)(void *pThis, u32 nDual); //STKSRV_EVT_PlayToneInd
typedef void (* SrvStkSelectItemCB)(void *pThis, u32 nDual); //STKSRV_EVT_SelectItemInd
typedef void (* SrvStkSendSSCB)(void *pThis, u32 nDual); //STKSRV_EVT_SendSSInd
typedef void (* SrvStkSendSMSCB)(void *pThis, u32 nDual); //STKSRV_EVT_SendSMSInd
typedef void (* SrvStkSendUSSDCB)(void *pThis, u32 nDual); //STKSRV_EVT_SendUSSDInd
typedef void (* SrvStkSendDTMFCB)(void *pThis, u32 nDual); //STKSRV_EVT_SendDTMFInd
//typedef void (* SrvStkLangNotificationCB)(void *pThis , u32 nDual); //STKSRV_EVT_LangNotificationInd
typedef void (* SrvStkLaunchBrowserCB)(void *pThis, u32 nDual); //STKSRV_EVT_SendDTMFInd
typedef void (* SrvStkErrorIndCB)(void *pThis, STKSRV_Error_e eErrorType, u32 nDual); //STKSRV_EVT_ErrorInd


/** SrvStkSetxxxCB
* @brief  Add a CB to STK.
*
* @param[in]      pfnCallBack             the function which will be called to notify the detection of specific event.
*/
void SrvStkSetChipResetCB(SrvStkSetupIdleTextCB pfnCallBack);

void SrvStkSetRefreshIndCB(SrvStkRefreshIndCB pfnCallBack);

void SrvStkSetDisplayTextCB(SrvStkDisplayTextCB pfnCallBack);

void SrvStkSetGetInkeyCB(SrvStkGetInkeyCB pfnCallBack);

void SrvStkSetGetInputCB(SrvStkGetInputCB pfnCallBack);

void SrvStkSetSetupCallCB(SrvStkSetupCallCB pfnCallBack);

void SrvStkSetPlayToneCB(SrvStkPlayToneCB pfnCallBack);

void SrvStkSetSelectItemCB(SrvStkSelectItemCB pfnCallBack);

void SrvStkSetSendSSCB(SrvStkSendSSCB pfnCallBack);

void SrvStkSetSendSMSCB(SrvStkSendSMSCB pfnCallBack);

void SrvStkSetSendUSSDCB(SrvStkSendUSSDCB pfnCallBack);

void SrvStkSetSendDTMFCB(SrvStkSendDTMFCB pfnCallBack);

void SrvStkSetLaunchBrowserCB(SrvStkLaunchBrowserCB pfnCallBack);

void SrvStkSetErrorIndCB(SrvStkErrorIndCB pfnCallBack);

/** SrvStkRegStkApp
* @brief  To Notify if StkApp is active
* 
* @param[in]    eDualMode      Master or Slave SIM
*/
void SrvStkRegStkApp(MAE_DualMode_t eDualMode) ;

/** SrvStkDeregStkApp
* @brief  To Notify if StkApp is not active
* 
* @param[in]    eDualMode      Master or Slave SIM
*/
void SrvStkDeregStkApp(MAE_DualMode_t eDualMode) ;


/** SrvStkMenuSelectionReq
* @brief  Send Menu Selection Request to RIL.
* 
* @param[in]    eDualMode       Master or Slave SIM
* @param[in]    u8MenuItem      User selected menu item
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkMenuSelectionReq(MAE_DualMode_t eDualMode, u8 u8MenuItem);

/** SrvStkSelectItemRsp
* @brief  Send Select Item Respond to RIL.
* 
* @param[in]    eDualMode       Master or Slave SIM
* @param[in]    rslt            User respond type
* @param[in]    u8MenuItem      User selected menu item
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkSelectItemRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e  rslt, u8  u8MenuItem);

/** SrvStkDisplayTextRsp
* @brief  Send Display Text Respond to RIL.
* 
* @param[in]    eDualMode       Master or Slave SIM
* @param[in]    rslt            User respond type
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkDisplayTextRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e  rslt);

/** SrvStkLaunchBrowserRsp
* @brief  Send Launch Browser Respond to RIL.
* 
* @param[in]    eDualMode       Master or Slave SIM
* @param[in]    rslt            User respond type
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkLaunchBrowserRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e rslt);

/** SrvStkGetInkeyRsp
* @brief  Send Get Inkey Respond to RIL.
* 
* @param[in]    eDualMode       Master or Slave SIM
* @param[in]    rslt            User respond type
* @param[in]    rsltString      User input string
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkGetInkeyRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e     rslt, MAE_WChar *rsltString);

/** SrvStkGetInputRsp
* @brief  Send Get Input Respond to RIL.
* 
* @param[in]      eDualMode           Master or Slave SIM
* @param[in]      rslt                User respond type
* @param[in]      rsltString          User input string
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkGetInputRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e   rslt, MAE_WChar *rsltString);

/** SrvStkSetupCallRsp
* @brief  Send Setup Call Respond to RIL.
* 
* @param[in]      eDualMode           Master or Slave SIM
* @param[in]      rslt                User respond type
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkSetupCallRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e  rslt);

/** SrvStkPlayToneRsp
* @brief  Send Play Tone Respond to RIL.
* 
* @param[in]    eDualMode       Master or Slave SIM
* @param[in]    rslt            User respond type
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If shell wants to terminate service, ignore request. 
*/
MAE_Ret SrvStkPlayToneRsp(MAE_DualMode_t eDualMode, STKSRV_RSP_RSLT_e  rslt);

/** SrvStkSetLanguageReq
* @brief  Send Set Language Request to RIL.
* 
* @param[in]    MAE_LANG_CODE_e maeLangCode
* 
* @retval MAE_RET_SUCCESS       If successful.
* @retval MAE_RET_NOT_SUPPORTED If iso639Code is not supported. 
*/
MAE_Ret SrvStkSetLanguageReq(MAE_LANG_CODE_e maeLangCode);

/** SrvStkGetMainMenuPointer
* @brief  Get STK main Menu Data pointer.
* 
* @param[in]      eDualMode          Master or Slave SIM
* 
* @retval     STK main Menu Data.
*/
STKSRV_SetupMenu_t * SrvStkGetMainMenuPointer(MAE_DualMode_t eDualMode);

/** SrvStkGetIndicationType
* @brief  Get STK Indication Data type.
* 
* @param[in]      eDualMode          Master or Slave SIM
* 
* @retval    STK Indication Data type.
*/
STKSRV_CommandType_e SrvStkGetIndicationType(MAE_DualMode_t eDualMode);

/** SrvStkGetIndicationData
* @brief  Get STK Indication Data pointer.
* 
* @param[in]      eDualMode          Master or Slave SIM
* 
* @retval      STK Indication Data.
*/
STKSRV_Ind_t * SrvStkGetIndicationData(MAE_DualMode_t eDualMode);

/** SrvStkGetIdleTextString
* @brief  Get STK Idle text.
* 
* @param[in]      eDualMode          Master or Slave SIM
* 
* @retval    STK Idle text
*/
MAE_WChar * SrvStkGetIdleTextString(MAE_DualMode_t eDualMode);

/** SrvStkGetMainMenuTitle
* @brief  Get STK main menu title string.
* 
* @param[in]      eDualMode          Master or Slave SIM
* 
* @retval      STK main menu title string.
*/
MAE_WChar * SrvStkGetMainMenuTitle(MAE_DualMode_t eDualMode);

/** SrvStkMSFinishStartupCB
* @brief  when onapp stop , will call the function to do remalloc setup menu memory , avoid heap memory fragment
*/
void SrvStkMSFinishStartupCB(void);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_STK_H__
