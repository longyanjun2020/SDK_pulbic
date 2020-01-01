/**
 *
 * @file    ema_trc_msg.h
 *
 * @brief   This module defines the EMA TRC message struct type for TRC interface using.
 *
 * @author  Xavier Fan
 * @version $Id: ema_trc_msg.h 14361 2008-09-24 10:56:18Z arthur.cheng $
 * 
 */
#ifndef __EMA_TRC_MSG_H__
#define __EMA_TRC_MSG_H__




/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "isl_trc_itf.h"




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
	u32										recordSize;
}ema_TrcAddRecord_t;


typedef struct
{
	u8	*									pData;
	u32										dataSize;
}ema_TrcWriteData_t;


typedef struct
{
	u8	*									pData;
	u32										dataSize;
}ema_TrcStoreData_t;


typedef struct
{
	isl_TrcStatInfo_t	*		pStats;
}ema_TrcGetStats_t;


typedef struct
{
	isl_TrcRecordInfo_t	*	pInfo;
}ema_TrcFindRecord_t;

typedef struct
{
	u32										handle;
	u32										offset;
	u32										length;
	u8	*									pBuffer;
	u32	*									pReadSize;
}ema_TrcReadRecord_t;

typedef struct
{
	ema_TransType_t				TransType;
	isl_TrcCb_t	*					pTrcDoneCB;
	isl_TrcErrCode_e	*		pErrCode;
	union
	{
		ema_TrcAddRecord_t	trcAddRecord;
		ema_TrcWriteData_t	trcWriteData;
		ema_TrcGetStats_t		trcGetStats;
		ema_TrcFindRecord_t	trcFindRecord;
		ema_TrcReadRecord_t	trcReadRecord;
		ema_TrcStoreData_t	trcStoreRecord;
	} cmdType;
} ema_TrcCmd_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif /* __EMA_TRC_MSG_H__ */





