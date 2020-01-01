#ifndef __VEN_CC_H_
#define __VEN_CC_H_
/********************************************************************************/
/*  File : ven_cc.h                                                            */
/*  Scope: The definition of the data structure or enum for phb related messages*/
/********************************************************************************/

#include "ven_sdk.h"

enum
{
    VEN_CC_RET_SUCCESS,                 ///< operation completed successfully
    VEN_CC_RET_BAD_PARAM,               ///< invalid input parameters
    VEN_CC_RET_OUT_OF_MEMORY,           ///< memory is not enough to complete the operation
    VEN_CC_RET_OPERATION_CANCELED,      ///< operation is canceled due to interruption
    VEN_CC_RET_TIMEOUT,                 ///< for dialog with duration assigned
    VEN_CC_RET_ALL_SLOT_OCCUPIED,       ///< All statusbar icon slot occupied and not available
    VEN_CC_RET_FAILED,                  ///< unknown error
    VEN_CC_RET_NOT_SUPPORT,             ///< Not support now
    VEN_CC_RET_NOT_ALLOWED              ///Operation not allowed
};
typedef u32 ven_cc_ret_t;

enum
{
    VEN_CC_CALL_MODE_IDLE = 0,                ///< there is no call 
    VEN_CC_CALL_MODE_ACTIVE_CALL = 0x1,       ///< call mode contains active call flag              
    VEN_CC_CALL_MODE_HOLD_CALL = 0x2,         ///< call mode contains hold call flag                        
    VEN_CC_CALL_MODE_WAITING_CALL = 0x4,      ///< call mode contains waiting call flag                        
    VEN_CC_CALL_MODE_DIALING_CALL = 0x8,      ///< call mode contains dialing call flag                        
    VEN_CC_CALL_MODE_OUTGOING_CALL = 0x10,    ///< call mode contains out going call flag                         
    VEN_CC_CALL_MODE_INCOMING_CALL = 0x20,    ///< call mode contains in comming call flag
};
typedef u32 iVen_cc_call_mode_t;

enum
{
	VEN_CC_INCOMING_HANDLER = 0,
};
typedef u8 ven_cc_incoming_ind_type_t;

enum
{
	VEN_CC_FILTER_NORNAL = 0,	//handled by mmi
	VEN_CC_FILTER_REJECT,				//reject this incoming call, with calllog
	VEN_CC_FILTER_REJECT_NO_CALLLOG,	//reject this incoming call, without calllog
};
typedef u8 ven_cc_filter_t; //must be same with VenSrv_Cc_Filter_t

typedef struct iVen_cc_call_status
{
    iVen_cc_call_mode_t nCallMode;          ///< the status of call service, may bitwise or by mutiple call mode flags.
    void *pData;
}iVen_cc_call_status_t;

#ifdef __SDK_API_01_SMS_MMS_CC__
typedef enum{

	VEN_CC_CALL_START = 1, 	///<  means CC App is starting(launching)
	VEN_CC_CALL_GO_THROUGH,	///< means the connection get established

}ven_cc_call_state_e;

// define ven_cc_makeCall_getCall_ID() callback response data
typedef struct
{
	ven_cc_ret_t 		retCode;
	ven_cc_call_state_e state;
	s32 				callID;		///<  only available when state == VEN_CC_CALL_START
} ven_cc_call_get_id_rsp_t;
#endif //#ifdef __SDK_API_01_SMS_MMS_CC__

enum
{
    VEN_CC_CALLLOG_TYPE_MISSED = 0,
	VEN_CC_CALLLOG_TYPE_RECEIVED = 1,
	VEN_CC_CALLLOG_TYPE_DIALED = 2,
   	VEN_CC_CALLLOG_TYPE_BLOCK = 3,
} ;
typedef u8 ven_cc_calllog_type_e;

enum
{
    VEN_CC_CALL_TYPE_VOICE = 0,
	VEN_CC_CALL_TYPE_VIDEO = 1,
} ;
typedef u8 ven_cc_call_type_e;

typedef struct
{
    u8 au8Number[40]; //MMI_PHB_NUMBER_LEN
    u32 u32LatestTime;
	u32 au32TimeDuration;
    u8 u8NumberLen;
    ven_common_sim_id_t simId;
    ven_cc_calllog_type_e callLogType;
    ven_cc_call_type_e callType;////
} ven_cc_calllog_t;

/**
 *  ven_cc_makeCall
 *
 *  @brief  This function will make a call with call ui , only async
 *
 *  @param  ptTelNo    [in] wchar format of tel number
 *  @param  telNoLen   [in] number of wchars in ptTelNo
 *  @param  simId      [in] the sim card to make a call
 *
 *  @retval TRUE  if success
 *          FALSE if failed
 */
bool ven_cc_makeCall(u16 *ptTelNo, u8 telNoLen, ven_common_sim_id_t simId, ven_req_data_t* ptVenReq);

/**
 *  ven_cc_makeCall_getCall_ID
 *
 *  @brief  This function will make a call with call ui , only async
 *			As opposed to ven_cc_makeCall(), it acts as suspend/resume model, 
 *			and its callback function will be invoked just after launching CC App successfully, instead of ending of CC APP
 *
 *  @param  ptTelNo    [in] wchar format of tel number
 *  @param  telNoLen   [in] number of wchars in ptTelNo
 *  @param  simId      [in] the sim card to make a call
 *
 *  @retval TRUE  if success
 *          FALSE if failed
 */
bool ven_cc_makeCall_getCall_ID(u16 *ptTelNo, u8 telNoLen, ven_common_sim_id_t simId, ven_req_data_t* ptVenReq);

/**
 *  ven_cc_releaseCall
 *
 *  @brief  This function will release a on-going call
 *	 Note: This function supports synchronous only
 *
 *  @param  callID    [in] CC APP call ID. From the callback function of ven_cc_makeCall_getCall_ID()
 * 
 *  @retval VEN_CC_RET_SUCCESS if success
 *          VEN_CC_RET_FAILED if failed
 */
ven_cc_ret_t ven_cc_releaseCall(s32 callID, ven_req_data_t* ptVenReq);

/**
 *  ven_cc_getCallStatus
 *
 *  @brief  This function will get current call status
 *
 *  @param  pCallStatus  [out] call status structure
 *
 *  @retval VEN_CC_RET_SUCCESS if success
 *          VEN_CC_RET_FAILED if failed
 *          VEN_CC_RET_BAD_PARAM if input parameter is invalid
 *
 *  @note For asynchronous using, call back function in ptVenReq will be called after user interaction and pRetCode will be ignore.
 */
ven_cc_ret_t ven_cc_getCallStatus(iVen_cc_call_status_t *pCallStatus, ven_req_data_t* ptVenReq);

/**
 *  ven_cc_queryCallMode
 *
 *  @brief  check the iVen_cc_call_mode_t queried from iVen_cc_call_status_t
 *
 *  @param  iVen_cc_call_status_t    [in] Queried call status from ven_cc_getCallStatus(...)
 *  @param  eStatus                  [in] The target status that wants to be confirmed
 *  @param  pAnswer                  [out] Answer of the status, true : the applet contains the given status. false : otherwise
 *
 *  @retval VEN_UI_RET_SUCCESS        Successfully
 *          VEN_UI_RET_BAD_PARAM      Given null parameter(s)
 *
 */
ven_cc_ret_t ven_cc_queryCallMode(iVen_cc_call_status_t *pCallStatus, iVen_cc_call_mode_t eStatus, bool *pAnswer);

/**
    This function is used in ven_cc_registerIncomingCall,
    3rd will filter incoming call by this function with simple rule.
    This function must be thread safe because it runs on MMI task.
    If 3rd want to handle this incoming call, return > 0. Otherwise, return 0.
*/
typedef ven_cc_filter_t (*VEN_INCOMINGCALL_FILTER_FUNC)(u8 *pCallNumber, u32 usrData);

/**
    This function is used in ven_cc_registerIncomingCall,
    3rd will handle incoming call by other API in this function, it is not supported now.
    This function could execute other commands to handle the incoming call because it runs on 3rd task.
*/
typedef void (*VEN_INCOMINGCALL_HANDLER_FUNC)(ven_cc_incoming_ind_type_t indType, u8 *pCallNumber, u32 callID, u32 usrData);

/**
 *  ven_cc_registerIncomingCall
 *
 *  @brief  This function will help to register all incoming call with a filter function and a handler function. 
 *    		The filter function will get call number and call Id to judge the call handled normally or rejected (or handled by 3rd party).
 *		The handler function must be NULL, because (handled by 3rd party) is not supported now.
 *          	This function only support sync mode. 
 *          	This function only support one vendor, new register will replace the old one.
 *		If pCallFilter == NULL, this function will deregister the incoming call listener.
 *
 *  @param  pCallFilter       	[in]Incoming call filter function
 *  @param  pCallHandler  	[in]Incoming call handler function
 *  @param  usrData  		[in]User data
 *  @param  ptVenReq        	[in]Vendor req data
 *
 *  @retval VEN_CC_RET_SUCCESS if success
 *          VEN_CC_RET_FAILED if failed
 *          VEN_CC_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_cc_ret_t ven_cc_registerIncomingCall(VEN_INCOMINGCALL_FILTER_FUNC pCallFilter, VEN_INCOMINGCALL_HANDLER_FUNC pCallHandler, u32 usrData, ven_req_data_t *ptVenReq);


typedef void (*VEN_CALLLOG_LISTENER_FUNC)(ven_cc_calllog_t* pCallLog, u32 usrData);

/**
 *  ven_cc_registerAddCallLog
 *
 *  @brief  This function will help to register added call logs with a listener function. 
 *    		The listener function will get a call log information after finishing a call .
 *          	This function only support sync mode. 
 *          	This function only support one listener for each vendor. 
 *		The Listener function only work during its vendor is alive. 
 *		If pCallLogListener == NULL, this function will deregister the incoming call listener.
 *		Compile option __MMI_CALLLOG_SUPPORT_LOG_CHANGED_NOTIFY__ must be define.
 *
 *  @param  venHandle        		[in]Vendor handle
 *  @param  pCallLogListener       [in]Added call log listener function
 *  @param  usrData  			[in]User data
 *
 *  @retval VEN_CC_RET_SUCCESS if success
 *          VEN_CC_RET_FAILED if failed
 *          VEN_CC_RET_BAD_PARAMETERS if input parameter is invalid
 */
ven_cc_ret_t ven_cc_registerAddCallLog(u32 venHandle, VEN_CALLLOG_LISTENER_FUNC pCallLogListener, u32 usrData);

typedef enum
{
    VEN_CC_DTMF_STOP,
    VEN_CC_DTMF_START,
    VEN_CC_DTMF_NONE
} VEN_CC_DTMF_OP;

typedef struct
{
    u16 struct_size;        //sizeof the struct, to make backward compatibility possible
    u8 u8KeyCode;           //The key user pressd, in the format of ASCII code. ex: '1' => 0x31
    u8 u8Duration;          //1~254*100ms if DTMFOper is Start
                            //      255 is infinite DTMF playing
                            //      Don't care if DTMFOper is Stop
    u8 u8OperationMode;     //Start to send or Stop to send the DTMF
} ven_cc_DTMF_req_t;

/**
 *  ven_cc_abortDTMF
 *
 *  @brief  abort DTMF in sync mode
 *
 *  @param  ven_req_data_t          [in] parameters for vendor
 *
 *  @retval VEN_UI_RET_SUCCESS        Successful
 *          VEN_UI_RET_BAD_PARAM      Given incorrect parameter(s)
 *
 */
ven_cc_ret_t ven_cc_abortDTMF(ven_req_data_t* ptVenReq);

/**
 *  ven_cc_startDTMFAsync
 *
 *  @brief  start DTMF in async mode
 *
 *  @param  ven_cc_DTMF_req_t       [in] parameters for DTMF
 *  @param  ven_req_data_t          [in] parameters for vendor
 *
 *  @retval VEN_UI_RET_SUCCESS        Successful
 *          VEN_UI_RET_BAD_PARAM      Given incorrect parameter(s)
 *
 */
ven_cc_ret_t ven_cc_sendDTMFAsync(ven_cc_DTMF_req_t *pDTMFReq, ven_req_data_t* ptVenReq);


/**
 *  ven_cc_EnableDLVoice
 *
 *  @brief  Enable/Disable downlink voice during a call
 *
 *  @param  ven_req_data_t          [in] parameters for vendor
 *  @param  bEnable                 [in] enable/disable downlink voice
 *
 *  @retval VEN_UI_RET_SUCCESS        Successful
 *          VEN_UI_RET_BAD_PARAM      Given incorrect parameter(s)
 *
 */
ven_cc_ret_t ven_cc_EnableDLVoice(ven_req_data_t* ptVenReq, bool bEnable);

#endif //__VEN_CC_H_
