/**
* @file MediaCmdListener.h
*
* This header file defines the interfaces of media proactive event
* for running command
*/

#ifndef __MEDIACMDLISTENERr_H__
#define __MEDIACMDLISTENERr_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "MediaCmdListenerItf.h"
#include "MediaCmd.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef struct MediaProEvts_t_
{
    u16 uProEvtNum;
    const u16 *pProEvts;
    ResMgr_CmdHdl_t pEvtOwnerCmd;
} MediaProEvts_t;

typedef struct MediaProEvtInfo_t_
{
    u16 uResNum;
    MediaProEvts_t *pMediaReqProEvts;
} MediaProEvtInfo_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif //__MEDIACMDLISTENERr_H__

