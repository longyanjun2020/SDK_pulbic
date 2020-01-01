/**
 *
 * @file    ema_disp_msg.h
 *
 * @brief   This module defines the Camera interface for upper layer (like MMI) using.
 *
 * @author  Pauli Leong
 * @version $Id: ema_disp_msg.h 7742 2008-03-20 03:35:24Z kenny.wu $
 *
 */
#ifndef __EMA_DISP_MSG_H__
#define __EMA_DISP_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "esl_disp_itf.h"




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
typedef struct {
	u16							prim;
	u16             sender;
	ema_TransType_t	TransType;
	ema_ErrCode_e   errorStatus;
} ema_DispRsp_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_DISP_MSG_H__ */


