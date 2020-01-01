////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
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
* @file    mdl_fms_backtrace.h
* @version
* @brief
*
*/

#ifndef __MDL_FMS_BACKTRACE_H__
#define __MDL_FMS_BACKTRACE_H__

/*=============================================================*/
// Include files
/*=============================================================*/

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
 *  @brief The enumeration defines the return code of the E2P interface
 */
typedef enum
{
	FMS_TRC_OK,                 /**< Function complete successfully */
	FMS_TRC_FAIL,               /**< Function common fail */
	FMS_TRC_PARAM_ERROR,        /**< The input parameter is wrong */
	FMS_TRC_MEM_ALLOC_ERROR,    /**< Can not allocate memory from OS */
	FMS_TRC_REJECT,             /**< Request rejected because of other function's confliction */
	FMS_TRC_ABORT,              /**< Request aborted because of incorrect sequence */
	FMS_TRC_VOLUME_FULL,				/**< Request fail because volume full */
	FMS_TRC_TIMEOUT,            /**< Request no response timeout, this error is returned by call back function */
	FMS_TRC_BAD_BLOCK           /**< Bad Block */
} fms_TrcErrCode_e;

/**
 *	@brief	The structure of backtrace statistic information
 */
typedef	struct
{
	u32		totalMem;
	u32		freeMem;
	u32		numRecoed;
}	fms_TrcStatInfo_t;

/**
 *	@brief	The structure of record information
 */
typedef	struct
{
	u32		handle;
	u32		dataSize;
	u32		allocatSize;
	bool	isFinalized;
}	fms_TrcRecordInfo_t;

/**
 *	@brief	The structure of record information
 */
typedef	struct
{
	u8		dummy;
}	fms_TrcInfor_t;

/**
 * @brief Call back function, Application needs to provide the function entry 
 *
 * @param senderID      : Sender task ID 
 * @param userValue     : Reference value for indicating different sender in same task or check msg response.
 * @param errCode       : The error return by Multimedia task to know process success or fail.
 * @param pE2pInfo      : Callback information return by E2P multi-media driver
 *
 * @return None
 */
typedef void (*fms_TrcCb)(u16 senderID, u32 userValue, fms_TrcErrCode_e errCode, fms_TrcInfor_t *pTrcInfo);

/**
 * @brief The Backtrace service call back function structure definition
 */
typedef struct
{
  u16        senderID;    /**< Sender task ID */     
  u32        userValue;   /**< Reference value for indicating different sender in same task or check msg response. */
  fms_TrcCb  pfnCb;       /**< Call back function that called by Media task after process finished. */
} fms_TrcCb_t;

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/
/****************************************************************************/
/*  Function: fms_TrcEraseAll                                               */
/*--------------------------------------------------------------------------*/
/*  Scope   : Nuke off all stored information.                              */
/*            Cannot be invoked while an entry is being created.            */
/*                                                                          */
/*  Return    : void                                                        */
/*                                                                          */
/*  Interface : n/a                                                         */
/****************************************************************************/
void fms_TrcEraseAll(void);

/**
 *	@brief	Used to indicate the following backtrace operation is in exception mode
 */
fms_TrcErrCode_e	fms_TrcSetSrvModeInNormal(void);


/**
 *	@brief	Used to indicate the following backtrace operation is in exception mode
 */
fms_TrcErrCode_e	fms_TrcSetSrvModeInException(void);


/**
 *	@brief	Used to initial Backtrace Service
 */
fms_TrcErrCode_e	fms_TrcInitialService(void);


/**
 *	@brief	Used to terminal Backtrace Service
 */
fms_TrcErrCode_e	fms_TrcTerminalService(void);


/**
 *	@brief	Used to initial Backtrace Service
 */
fms_TrcErrCode_e	fms_TrcGetStatics(fms_TrcStatInfo_t * pInfo);


/**
 *	@brief	Used to terminal Backtrace Service
 */
fms_TrcErrCode_e	fms_TrcClearAllRecord(void);


/**
 *	@brief	Used to add record
 */
fms_TrcErrCode_e	fms_TrcAddRecord(u32 maxRecordSize);


/**
 *	@brief	Used to write record
 */
fms_TrcErrCode_e	fms_TrcWriteRecord(u8* pData, u32 dataSize);


/**
 *	@brief	Used to close record
 */
fms_TrcErrCode_e	fms_TrcCloseRecord(void);


/**
 *	@brief	Used to initial lookup-record service
 */
fms_TrcErrCode_e	fms_TrcInitialLookupService(void);


/**
 *	@brief	Used to terminal lookup-record service
 */
fms_TrcErrCode_e	fms_TrcTerminalLookupService(void);


/**
 *	@brief	Used to lookup next record
 */
fms_TrcErrCode_e	fms_TrcLookupNextRecord(fms_TrcRecordInfo_t * pInfo);


/**
 *	@brief	Used to read record
 */
fms_TrcErrCode_e	fms_TrcReadRecord(u32 handle, u32 offset, u32 length, u8* pBuffer, u32* pReadSize);


/**
 *	@brief	Used to store data to NAND backtrace without blocking
 */
fms_TrcErrCode_e	fms_TrcStoreRecordReq(u8* pData, u32 dataSize, fms_TrcCb_t* pCbInfo);

#endif //__MDL_FMS_BACKTRACE_H__

