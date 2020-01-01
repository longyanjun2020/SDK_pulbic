////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mdl_aud_cp_pub_api.h
* @version
* @brief   Abscontainer middleware audio header file
*
*/

#ifndef __MDL_AUD_CP_PUB_API_H__
#define __MDL_AUD_CP_PUB_API_H__


/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_audio_pub_api.h"
#include "mdl_aud_pub_api.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * \brief Audio Cut point callback
 */
typedef void (*MdlAudCPCbFn_t)(u8 bufferID);

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/**
 * @brief This function is used to Clear Bach internal RAM
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpResetReq(void);


/**
 * @brief This function is used to start video telephony
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpStartReq(void);


/**
 * @brief This function is used to pause video telephony
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpPauseReq(void);


/**
 * @brief This function is used to resume video telephony
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpResumeReq(void);


/**
 * @brief This function is used to stop video telephony
 *
 * @param                               : None
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpStopReq(void);


/**
 * @brief This function is used to register callback function
 *
 * @param  MdlAudCPCbFn_t               : video telephony callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpRegCallbackReq(MdlAudCPCbFn_t tCpCbFn);


/**
 * @brief This function is used to register callback function from uplink raw data
 *
 * @param  MdlAudCPCbFn_t               : video telephony callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpReadUlRawDataInfoReq(u8 bufferID, MdlAudCpData_t *tCpDataInfo);


/**
 * @brief This function is used to read data which is came from downlink raw data
 *
 * @param  MdlAudCPCbFn_t               : video telephony callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpReadDlRawDataInfoReq(u8 bufferID, MdlAudCpData_t *tCpDataInfo);


/**
 * @brief This function is used to write data which is sent to uplink
 *
 * @param  bufferID                     : bufferId is decided to which 
 * @param  tCpDataInfo                  : video telephony callback function
 *
 * @return MDL_AUD_RET_OK               : function request success
 * @return MDL_AUD_RET_FAIL             : function request fail
 * @return MDL_AUD_RET_PARAM_ERROR      : Incorrect parameter setting
 * @return MDL_AUD_RET_MEM_ALLOC_ERROR  : Can't allocate available memory from OS
 * @return MDL_AUD_RET_REJECT           : Request rejected becuase of other function's confliction
 */
MdlAudRet_e MdlAudCpWriteAECDataReq(u8 bufferID, MdlAudCpData_t tCpDataInfo);

#endif // END __MDL_AUD_CP_PUB_API_H__
