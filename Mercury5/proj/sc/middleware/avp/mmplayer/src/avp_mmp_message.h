////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2010 MStar Semiconductor, Inc.
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


#ifndef MMP_MESSAGE_H
#define MMP_MESSAGE_H

/* AVP control message */
#define AVP_CONTROL_MSG                                  0

enum mmp_control_e {
    MMP_THREAD_CMD_NONE,
    MMP_THREAD_CMD_PAUSE,
    MMP_THREAD_CMD_RESUME,
    MMP_THREAD_CMD_STOP,
    MMP_THREAD_CMD_SEEK,
    MMP_THREAD_CMD_FLUSH,
    MMP_THREAD_CMD_RESYNC,
};

enum {
    CMD_NONE,
    CMD_PAUSE,
    CMD_RESUME,
    CMD_SEEK,
    CMD_STOP,
    CMD_SWITCH_CHA,
    CMD_SEL_TRACK,
    CMD_FLUSH,
    CMD_DECODE,
    CMD_DMX,
    CMD_WAIT_RBUF,
    CMD_RESYNC,
};

enum {
    VD_CMD_NONE,
    VD_CMD_STOP
};

enum MMP_THREAD_TYPE
{
    MMP_THREAD_VD,
    MMP_THREAD_AD,
    MMP_THREAD_DX,
    MMP_THREAD_VO,
};

int dx_get_cmd(void *pInst);
int vo_get_cmd(void *pInst, int paused, int flushing);
int ad_get_cmd(void *pInst, int paused, int flushing);
int vd_get_cmd(void *pInst);
int send_control_cmd(void *pInst, int thread_id, int cmd);
#endif
