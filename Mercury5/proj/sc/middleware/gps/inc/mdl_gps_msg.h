////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_GPS_MSG_H__
#define __MDL_GPS_MSG_H__

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
#if 0
//#include "mml_gps.h"


typedef union
{
  MmlGpsUCParam_t   tGpsUCParam;
} vm_msgBody_t;
#else
//#include "srv_MmManager_Gps.h"
#include "drv_gps_pub.h"

typedef struct
{
    u32                             nUseCaseID;      /* open,close,start,stop..*/
    MdlErrCode_e                    tResult;         /* Result for execution command */
    MdlGpsState_e                   eState;        ///< Current state

} MdlGpsReponseParam_t;

typedef struct
{
    union
    {
   	    MdlGpsReponseParam_t   MdlResponse;
    } uParam;
} MdlGpsUCParam_t;

typedef union
{
  MdlGpsUCParam_t   tMdlGpsUCParam;
  GPSDrvMsgBody_U   tDrvGpsMsgBody;
} vm_msgBody_t;

#endif

#include "vm_msgt.ht"

/*=============================================================*/
// Variable definition
/*=============================================================*/




/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif // __MDL_GPS_MSG_H__

