/**
* @file MediaRsp.h
*
* This header file defines the data structures of Media Response
*
*/

#ifndef __MEDIARSP_H__
#define __MEDIARSP_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ResMgr_Rsp.h"
#include "MediaRspItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct Media_GenRsp_t_
{
    s32 sErrCode;
    void *pGenRspData;
} Media_GenRsp_t;

typedef enum Media_RspEvt_e_
{
    MEDIA_RSP_EVT__M2_PLAY_END,
    MEDIA_RSP_EVT__M2_PLAY_ERROR,
    MEDIA_RSP_EVT__BT_PLAY_ERROR
} Media_RspEvt_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__MEDIARSP_H__

