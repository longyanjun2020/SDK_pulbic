////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
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

#ifndef VFS_API_H
#define VFS_API_H

#include <stdint.h>
#include "mdl_avp_streaming_interface.h"

#ifdef __RTK_OS__
typedef u16Char ms_fnchar;
#endif

enum
{
    MDL_AVP_VFS_FIRST_TIMESTAMP,
    MDL_AVP_VFS_LAST_TIMESTAMP,
};

enum
{
    MDL_AVP_VFS_FILE_NOT_EXIST,
    MDL_AVP_VFS_FILE_COMPLETE_DOWNLOAD,
    MDL_AVP_VFS_FILE_PARTIAL_DOWNLOAD,
};

enum
{
    MDL_AVP_VFS_SEEK_SET,
    MDL_AVP_VFS_SEEK_CUR,
    MDL_AVP_VFS_SEEK_END,
};

enum
{
    MDL_AVP_VFS_OK,
    MDL_AVP_VFS_OPEN_FAILED,
    MDL_AVP_VFS_CLOSE_FAILED,
};

int  MDLAvpVfsClose(uint32_t *read_handle, uint32_t *write_handle);
void MDLAvpVfsClosePlayer(uint32_t read_handle);
int  MDLAvpVfsGetDownloadTimeStamp(uint32_t write_handle, int pos);
int  MDLAvpVfsGetLastDropPacketPts(uint32_t read_handle);
int  MDLAvpVfsGetRebufferStatus(uint32_t write_handle);
int  MDLAvpVfsGetMemFreeSize(uint32_t write_handle);
int  MDLAvpVfsGetMemTotalSize(uint32_t write_handle);
int  MDLAvpVfsGetNetworkType(uint32_t read_handle);
int  MDLAvpVfsGetRebufferInfo(uint32_t read_handle, int *cur_rebuffer_size, int *req_rebuffer_size);
int  MDLAvpVfsGetStatus(uint32_t write_handle);
int  MDLAvpVfsReadInit(uint32_t read_handle);
int  MDLAvpVfsRead(uint32_t read_handle, void *buf, int size);
void MDLAvpVfsRegCB(uint32_t read_handle, avp_vfs_rebuffer_cb *rb_cb, avp_vfs_rebuffer_done_cb *rb_done_cb, avp_vfs_rebuffer_stop_cb *rb_stop_cb, avp_vfs_seek_cb *seek_cb);
int  MDLAvpVfsSeek(uint32_t handle, int offset, int whence);
int  MDLAvpVfsSeekWithID(uint32_t handle, uint32_t id, int offset, int whence);
void MDLAvpVfsSetPlayerInfo(uint32_t read_handle, void *player);
int  MDLAvpVfsStopRebuffer(uint32_t read_handle);
int  MDLAvpVfsNotifyNetworkError(uint32_t read_handle);
int  MDLAvpVfsSetLastDropPacketPts(uint32_t write_handle, uint32_t drop_pts);
int  MDLAvpVfsStreamingFileOpen(void *stm_handle, const ms_fnchar *file_name, int file_size, int *first_download_byte, uint32_t *read_handle, uint32_t *write_handle);
int  MDLAvpVfsStreamingMemOpen(void *stm_handle, int file_size, uint8_t *probe_data, int probe_size, int network_type, uint32_t *read_handle, uint32_t *write_handle);
int  MDLAvpVfsUpdateFileSize(uint32_t write_handle, int file_size);
int  MDLAvpVfsWrite(uint32_t write_handle, void *buf, int size);
void MDLAvpVfsWriteEOF(uint32_t write_handle);
int  MDLAvpVfsWriteWithID(uint32_t write_handle, uint32_t id, uint32_t start_offset, void *buf, int size);
int  MDLAvpVfsSetPlayInfo(uint32_t write_handle, int enable_audio, int enable_video, int start_pos, uint64_t audio_base_pts, uint64_t video_base_pts);
#endif

