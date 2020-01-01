/**
 * @file ven_stc.h
 *
 * @brief This file defines the app state control related functions.
 *
 * @version $Id: ven_stc.h 15633 2008-10-28 03:55:31Z steve.lee $
 *
 */
#ifndef __VEN_STC_H__
#define __VEN_STC_H__

#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_STC_SUCCESS,
    VEN_STC_BAD_PARAMS,
    VEN_STC_FAILED,
    VEN_STC_SUSPENDED, // The given AP is already started, but it is suspended now
};

typedef u32 ven_stc_ret_t;

enum
{
    VEN_STC_STATUS_FOREGROUND,
    VEN_STC_STATUS_BACKGROUND,
    VEN_STC_STATUS_STOP,
};

typedef u8 ven_stc_status_t;

typedef struct
{
    ven_stc_status_t type;
    void *pData;
    u32 len;
} ven_stc_status_param_t;

typedef void (*VEN_STC_START_FUNC_PTR)(void *pData, u32 len);
typedef void (*VEN_STC_STOP_FUNC_PTR)(void);
typedef void (*VEN_STC_SUSPEND_FUNC_PTR)(void);
typedef void (*VEN_STC_RESUME_FUNC_PTR)(void);
typedef void (*VEN_STC_STATUS_IND_FUNC_PTR)(ven_stc_status_param_t *pParam);

typedef struct ven_stc_life_control_func_tag
{
    VEN_STC_START_FUNC_PTR    pfnStart;
    VEN_STC_STOP_FUNC_PTR     pfnStop;
    VEN_STC_SUSPEND_FUNC_PTR  pfnSuspend;
    VEN_STC_RESUME_FUNC_PTR   pfnResume;
    VEN_STC_STATUS_IND_FUNC_PTR pfnStatusInd;
} ven_stc_ctrl_func_t;

/*--------------------------------------------------------------------------*/
/* Public Function Definition                                               */
/*--------------------------------------------------------------------------*/

/**
 *  ven_stc_regFuncs
 *
 *  @brief  Register life control functions of the APP to SDK.
 *
 *  @param  SdkHandle   [in] The handle of SDK get from ven_handle_open()
 *  @param  ptFuncs     [in] Pointer to the structure containing control functions.
 *
 *  @retval VEN_STC_SUCCESS   register successfully
 *          VEN_STC_FAILED    register failed
 */
ven_stc_ret_t ven_stc_regFuncs(u32 SdkHandle, ven_stc_ctrl_func_t *ptFuncs);

/**
 *  ven_stc_startRsp
 *
 *  @brief  Response the result of start request to SDK.
 *
 *  @param  ptVenRsp   [in] Pointer to the structure containing the result
 *
 *  @retval VEN_STC_SUCCESS   Response successfully
 *          VEN_STC_FAILED    Response failed
 */
ven_stc_ret_t ven_stc_startRsp(ven_rsp_data_t* ptVenRsp);

/**
 *  ven_stc_stopRsp
 *
 *  @brief  Response the result of stop request to SDK.
 *
 *  @param  ptVenRsp   [in] Pointer to the structure containing the result
 *
 *  @retval VEN_STC_SUCCESS   Response successfully
 *          VEN_STC_FAILED    Response failed
 */
ven_stc_ret_t ven_stc_stopRsp(ven_rsp_data_t* ptVenRsp);

/**
 *  ven_stc_suspendRsp
 *
 *  @brief  Response the result of suspend request to SDK.
 *
 *  @param  ptVenRsp   [in] Pointer to the structure containing the result
 *
 *  @retval VEN_STC_SUCCESS   Response successfully
 *          VEN_STC_FAILED    Response failed
 */
ven_stc_ret_t ven_stc_suspendRsp(ven_rsp_data_t* ptVenRsp);

/**
 *  ven_stc_resumeRsp
 *
 *  @brief  Response the result of resume request to SDK.
 *
 *  @param  ptVenRsp   [in] Pointer to the structure containing the result
 *
 *  @retval VEN_STC_SUCCESS   Response successfully
 *          VEN_STC_FAILED    Response failed
 */
ven_stc_ret_t ven_stc_resumeRsp(ven_rsp_data_t* ptVenRsp);

/**
 *  ven_stc_statusRsp
 *
 *  @brief  Response the result of status indication to SDK.
 *
 *  @param  ptVenRsp   [in] Pointer to the structure containing the result
 *
 *  @retval VEN_STC_SUCCESS   Response successfully
 *          VEN_STC_FAILED    Response failed
 */
ven_stc_ret_t ven_stc_statusRsp(ven_stc_status_t status, ven_rsp_data_t* ptVenRsp);

/**
 *  ven_stc_notifyStop
 *
 *  @brief  Stop notification
 *
 *  @param  Handle   [in] The handle of SDK get from ven_handle_open()
 *
 *  @retval VEN_STC_SUCCESS   Notify successfully
 *          VEN_STC_FAILED    Notify failed
 */
ven_stc_ret_t ven_stc_notifyStop(u32 SdkHandle);

/**
 *  ven_stc_notifyStart
 *
 *  @brief  Start notification
 *
 *  @param  ptVenReq   [in] Pointer of vendor request data.
 *
 *  @retval VEN_STC_SUCCESS   Notify successfully
 *          VEN_STC_FAILED    Notify failed
 *          VEN_STC_SUSPENDED The given AP is already started, but it is suspended now
 */
ven_stc_ret_t ven_stc_notifyStart(ven_req_data_t* ptVenReq);

/**
 *  ven_stc_notifyStatusChange
 *
 *  @brief  Status change notification
 *
 *  @param  Handle   [in] The handle of SDK get from ven_handle_open()
 *  @param  Handle   [in] The status that vendor want to change to (VEN_STC_STATUS_FOREGROUND / VEN_STC_STATUS_BACKGROUND)
 *
 *  @retval VEN_STC_SUCCESS   Notify successfully
 *          VEN_STC_FAILED    Notify failed
 */
ven_stc_ret_t ven_stc_notifyStatusChange(ven_stc_status_t status, ven_req_data_t* ptVenReq);

#endif /* __VEN_STC_H__ */


