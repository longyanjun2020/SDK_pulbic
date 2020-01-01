/**
 *
 * @file    ema_nrai_msg.h
 *
 * @brief   This module defines the EMA NRAI message struct type for NRAI service
 *
 * @author  Xavier.Fan
 * @version $Id: ema_nrai_msg.h 11919 2008-06-23 06:37:09Z gary.lu $
 *
 */
#ifndef __EMA_NRAI_MSG_H__
#define __EMA_NRAI_MSG_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "isl_nrai_itf.h"
#include "ema.ht"




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


typedef struct
{
  isl_NraiErrCode_e			*	pStatus;
  isl_NraiGetInfoReq_t	*	pGetInfoReq;
} ema_NraiGetInfoCmd_t;


typedef struct
{
  isl_NraiErrCode_e			*	pStatus;
  isl_NraiReadReq_t			*	pReadReq;
} ema_NraiReadCmd_t;


typedef struct
{
  isl_NraiErrCode_e			*	pStatus;
  isl_NraiWriteReq_t		*	pWriteReq;
} ema_NraiWriteCmd_t;


typedef struct
{
	ema_TransType_t							TransType;
	isl_NraiCb_t     					*	pNraiCB;

	union	{
    ema_NraiGetInfoCmd_t			getInfoCmd;
	  ema_NraiReadCmd_t					blockReadCmd;
	  ema_NraiWriteCmd_t				blockWriteCmd;
	} param;
} ema_NraiCmd_t;


typedef struct
{
	u16									prim;
	u16             		sender;
	ema_TransType_t	  	TransType;
	ema_ErrCode_e 			errorStatus;
} ema_NraiRsp_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/




#endif /* __EMA_NRAI_MSG_H__ */


