////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MDW_VID_HANDLE_H
#define MDW_VID_HANDLE_H

/*=============================================================*/
// Global function definition
/*=============================================================*/

#include "vm_types.ht"
#include "cus_msg.hc"
#include "srv_ResMgr_MmlManager.h"
#include "mdl_avp_interface.h"
#include "srv_resmgr_mmlvideo_types.h"
#include "srv_resmgr_mmlvideosdk_types.h"

typedef enum manager_Type_e
{
    MML_manager = 0,
    VT_manager,
    AVP_manager,
} manager_type_et;

typedef struct
{
    MmlVideoUCParam_t     tVideoUCParam;
    manager_type_et       tManagerType;
} mmp_managerParam_t;

typedef struct
{
    uint32_t session_id;
    uint32_t seek_pos;
} avp_vfs_seek_info_st;

typedef struct
{
    int msg;
    int data_size;
    void *data;
} avp_streaming_info_st;

typedef union
{
    mmp_managerParam_t    tManagerParam;
    int                   tThread_Cmd;
    MmlVideoSdkUCParam_t  tVideoSdkUCParam;
    uint32_t              rebuffer_size; //for AVP_REBUFFER_MSG
    avp_vfs_seek_info_st  seek_info;
    avp_streaming_info_st streaming_info;
} vm_msgBody_t;

#include "vm_msgt.ht"

#define MDL_GET_VIDEO_UCID(pMsg)           (MML_GET_VIDEO_UCID(&pMsg->Body.tManagerParam.tVideoUCParam))
#define MDL_AVP_MANAGER                    (0xAABBCCDD)
#endif
