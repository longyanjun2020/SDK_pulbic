/**
 *
 * @file    ema_e2p_msg.h
 *
 * @brief   This module defines the EMA E2P message struct type for E2P interface using.
 *
 * @author  Arthur Cheng
 * @version $Id: ema_e2p_msg.h 14361 2008-09-24 10:56:18Z arthur.cheng $
 *
 */
#ifdef __NAND__

#ifndef __EMA_E2P_MSG_H__
#define __EMA_E2P_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/


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
  u32  e2pAddr;
  u32  e2pSize;
  u8   *pBuffer;
}ema_E2pSave_t;

typedef struct
{
  u32  e2pAddr;
  u32  e2pSize;
  u8   *pBuffer;
}ema_E2pLoad_t;

/* Async flush e2p feature {Patrick Yang */
typedef struct
{
  ema_E2pSave_t e2pRo;
  ema_E2pSave_t e2pRw;
}ema_E2pSaveRoRw_t;
/* Async flush e2p feature Patrick Yang} */

typedef struct
{
  ema_E2pLoad_t e2pRo;
  ema_E2pLoad_t e2pRw;
}ema_E2pLoadRoRw_t;


typedef struct
{
	ema_TransType_t     TransType;
	isl_E2pCb_t         *pE2pDoneCB;
	union
	{
		ema_E2pSave_t     e2pSaveCmd;
		ema_E2pLoad_t     e2pLoadCmd;
		ema_E2pSaveRoRw_t e2pSaveRoRwCmd;
		ema_E2pLoadRoRw_t e2pLoadRoRwCmd;
	} cmdType;
} ema_E2pCmd_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_E2P_MSG_H__ */

#endif


