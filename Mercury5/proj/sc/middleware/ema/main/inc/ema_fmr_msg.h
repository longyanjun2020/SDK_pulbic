/**
 *
 * @file    ema_fmr_msg.h
 *
 * @brief   This module defines the EMA FMR message struct type for FMR interface using.
 *
 * @author  Kevin Chang
 * @version $Id:
 * 
 */
#ifndef __EMA_FMR_MSG_H__
#define __EMA_FMR_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_fmr_itf.h"




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
typedef struct{
  bool              PowerOn;
}ema_FmrAtvSetPower_t;

typedef struct
{
	ema_TransType_t     TransType;
	esl_FmrCb_t         *pFmrDoneCB;
	union
	{
    ema_FmrAtvSetPower_t       fmrAtvSetPowerCmd;
	} cmdType;
} ema_FmrCmd_t;

typedef struct
{
	u16                 prim;
	u16                 sender;
	ema_TransType_t     TransType;
	ema_ErrCode_e       errorStatus;
} ema_FmrRsp_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_FMR_MSG_H__ */




