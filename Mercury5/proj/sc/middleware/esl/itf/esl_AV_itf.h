/**
 *
 * @file    esl_AV_itf.h
 *
 * @brief   This module defines the Enhanced Service Layer interafce of AV (Audio/Video) media service
 *
 * @author  Pauli Leong
 * @version $Id: esl_AV_itf.h 15238 2008-10-16 09:40:41Z jack.hsieh $
 *
 */
#ifndef __ESL_AV_ITF_H__
#define __ESL_AV_ITF_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_vdo_itf.h"
#include "esl_aud_itf.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __ESL_AV_ITF__
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
 *  @brief AV error code
 */
typedef enum {
  ESL_AV_OK,                /**< Function complete successfully */
  ESL_AV_FAIL,              /**< Function common error */
  ESL_AV_PARAM_ERROR,       /**< The input parameter is wrong */
  ESL_AV_MEM_ALLOC_ERROR,   /**< Can't allocate memory from OS */
  ESL_AV_REJECT,            /**< Request reject because of other function's confliction */
  ESL_AV_ABORT,             /**< Request abort because of incorrect sequence */    
  ESL_AV_TIMEOUT            /**< Request no response timeout,this error is returned by call back function  */    
} esl_AV_ErrCode_e;

/**
 *  @brief Media File type
 */
typedef enum {
    ESL_AV_TYPE_AUD = 0,       /**< Video type */ 
    ESL_AV_TYPE_VDO,           /**< Audio type */ 
    ESL_AV_TYPE_UNKNOWN        /**< Unknown media type */
} esl_AV_Type_e;

/**
 *  @brief Media file structure
 */
typedef struct {
  u16   *pFileName;    /**< AV Media file name in UCS2 format  */
  u16   fileNameLen;   /**< AV Media file name length (UCS2)  */
} esl_AV_FileParam_t;

/**
 *  @brief AV media file information structure
 */
typedef struct {
  u16             typMsg;         /**< Primitive/Message requested ID */
  esl_AV_Type_e   type;           /**< AV media type */
  union {
    esl_AudFormat_e  audFormat;   /**< Audio media format */        
    esl_VdoFormat_e  vdoFormat;   /**< Video media format */      
  } param;   
} esl_AV_Info_t;

/**
 * @brief Call back function, MMI need to provide the function entity 
 *
 * @param senderID     : Sender task id. 
 * @param userValue    : Reference value for indicating different sender in same task or check msg response.
 * @param errCode      : The error code return by Multimedia task to know process success or fail.
 * @param pAVInfo      : Query data return by Multimedia task.
 *
 * @return None
 */
typedef void (*esl_AV_Cb)(u16 senderID, u32 userValue, esl_AV_ErrCode_e errCode, esl_AV_Info_t *pAVInfo);

/**
 *  @brief Esl call back function structure definition
 */
typedef struct {
  u16           senderID;     /**< Task id of sender */    
  u32           userValue;    /**< User vlue of sender for checking msg response */
  esl_AV_Cb     pfnCb;        /**< Done call back function that called by EMA */
} esl_AV_Cb_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/** 
 * @brief This function is used to get AV media file information.
 *   
 * @param  fileParam                   : AV filename / file length information
 * @param  pAVCb                       : AV call back function pointer
 *
 * @return ESL_AV_OK       				     : function request success
 * @return ESL_AV_FAIL                 : function request fail
 * @return ESL_AV_PARAM_ERROR          : Incorrect parameter setting
 * @return ESL_AV_MEM_ALLOC_ERROR	     : Can't allocate available memory from OS
 * @return ESL_AV_REJECT               : Request rejected becuase of other function's confliction
 * @return ESL_AV_ABORT                : Request aborted becuase of incorrect sequence 
 * @return ESL_AV_TIMEOUT              : Request no response timeout, this error is returned by call back function  
 */
esl_AV_ErrCode_e esl_AV_GetMediaFileFormat(esl_AV_FileParam_t fileParam, esl_AV_Cb_t *pAVCb);


#endif /* __ESL_AV_ITF_H__ */

