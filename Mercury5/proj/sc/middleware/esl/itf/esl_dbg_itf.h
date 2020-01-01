/**
 *
 * @file    esl_dbg_itf.h
 *
 * @brief   This file defines the Enahcned Service Layer of debugging interface
 *
 * @author  Gary Lu
 * @version $Id: esl_dbg_itf.h 19811 2009-01-05 08:09:29Z pauli.leong $
 *
 */
#ifndef __ESL_DBG_ITF_H__
#define __ESL_DBG_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"
#include "sys_vm_dbg.ho"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_DBG_ITF__
#define DefExtern
#else
#define DefExtern extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/**
 *  @brief The enumeration defines the return code of the amera interface function.
 */
typedef enum{
  ESL_DBG_OK,               /**< Function complete successfully */ 
  ESL_DBG_FAIL,             /**< Function fail */
  ESL_DBG_PARAM_ERROR,      /**< The input parameter is wrong */
  ESL_DBG_MEM_ALLOC_ERROR,  /**< Can not allocate available memory from OS */
  ESL_DBG_REJECT,           /**< Request reject because of other function's confliction */
  ESL_DBG_ABORT,            /**< Request abort because of incorrect sequence */  
  ESL_DBG_TIMEOUT           /**< Request command to MMP is no response */
} esl_DbgErrCode_e;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Store run-time trace into file for TMT analysis
 *
 * @param pTrcBuf          : the pointer to trace buffer structure.
 *
 * @return ESL_DBG_OK      : store successful
 * @return ESL_DBG_FAIL    : store fail
 */
esl_DbgErrCode_e esl_DbgStoreRuntimeTrace(vm_dbgTrcBuffer_t *pTrcBuf);


/**
 * @brief Store trace lost into file for furthur analysis
 *
 * @param pTrcBuf          : the pointer to trace buffer structure.
 *
 * @return ESL_DBG_OK      : store successful
 * @return ESL_DBG_FAIL    : store fail
 */
esl_DbgErrCode_e esl_DbgStoreTrcLostInfo(vm_dbgTrcLostInfo_t *pInfoBuf);


/** 
 * @brief Store backtrace into file for TMT analysis.
 *   
 * @param device           : type of devices.
 *
 * @return ESL_DBG_OK      : Set attribution success.
 * @return ESL_DBG_FAIL    : Set attribution fail.
 */
esl_DbgErrCode_e esl_DbgStoreBackTrace(void);

#endif


