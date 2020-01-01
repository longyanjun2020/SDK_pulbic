/**
 *
 * @file    ema_rfid_msg.h
 *
 * @brief   This file defines the message related type of RFID service
 *
 * @author  Ian-Y Chen
 * @version $Id: ema_rfid_msg.h 6010 2009-08-26 09:48:36Z ian-y.chen $
 *
 */
#ifndef __EMA_RFID_MSG_H__
#define __EMA_RFID_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_rfid_itf.h"
#include "ema.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#ifdef DefExtern
#undef DefExtern
#endif
#ifdef __EMA_PARSE__
#define	DefExtern
#else
#define	DefExtern	extern
#endif


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/

/**
 *  @brief The structure defines the RFID message body for RFID operation message
 */
typedef struct {
  ema_TransType_t   transType;
  esl_RFID_Cb_t    *pRfidCb;
  union
  {
    esl_RFID_StartConfig_t   rfidOpenCmd;
    esl_RFID_ReadParam_t     rfidReadCmd;
    esl_RFID_WriteParam_t    rfidWriteCmd;
    esl_RFID_EncryptParam_t  rfidEncryptCmd;
    esl_RFID_DecryptParam_t  rfidDecryptCmd;
  } cmdType;
} ema_RfidCmd_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_RFID_MSG_H__ */




