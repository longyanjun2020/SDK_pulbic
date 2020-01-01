////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2012 MStar Semiconductor, Inc.
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


#ifndef MMP_API_H
#define MMP_API_H

#include <stdint.h>
#include "avp_ms_io.h"
#include "avp_mmp_info.h"

struct cb_io_s;

typedef int mmp_notify_cb(void *ctx, int msg);

typedef enum
{
    MMP_USER_CMD,
    MMP_AUTO_CMD,
} MMP_CMD_MODE;

typedef enum
{
    MMP_CMD_NONE,
    MMP_CMD_OPEN,
    MMP_CMD_PLAY,
    MMP_CMD_STOP,
    MMP_CMD_PAUSE,
    MMP_CMD_RESUME,
    MMP_CMD_QUIT,
    MMP_CMD_GET_POS,
    MMP_CMD_SET_NEXT_POS,
    MMP_CMD_SET_PREV_POS,
    MMP_CMD_SET_INIT_POS,
    MMP_CMD_GET_FILE_INFO,
    MMP_CMD_GET_DISP_INFO,
    MMP_CMD_VOL_UP,
    MMP_CMD_VOL_DOWN,
    MMP_CMD_MUTE,
    MMP_CMD_UNMUTE,
    MMP_CMD_EQMODE,
    MMP_CMD_GET_THUMBNAIL,
    MMP_CMD_NEXT_CHANNEL,
    MMP_CMD_PREV_CHANNEL,
    MMP_CMD_DISP_AUDIO_SPECTRUM,
    MMP_CMD_NEXT_AUDIO,
    MMP_CMD_NEXT_VIDEO,
    MMP_CMD_NEXT_SUBTITLE,
    MMP_CMD_FAST_FORWARD,
    MMP_CMD_SPEED_NORMAL,
    MMP_CMD_SEEK_POS,
    MMP_CMD_SEEK_COMPLETE,
} MMP_CMD_ATTRIBUTE;

typedef enum
{
    MMP_APP_FILE,
    MMP_APP_STREAMING,
    MMP_APP_PUSH,
    MMP_APP_HTTP,
} MMP_APP_MODE;

typedef enum
{
    MMP_AUDIO_TRACK,
    MMP_VIDEO_TRACK,
    MMP_SUBTITLE_TRACK,
} MMP_TRACK_TYPE;

enum MMP_OPEN_CAPABILITY
{
    MMP_CAPAPILITY_LOW = 0,
    MMP_CAPAPILITY_MEDIUM,
    MMP_CAPABILITY_HIGH,
};

enum MMP_INFO_VIDEC_TYPE
{
    MMP_INFO_SW_VIDEC=0,
    MMP_INFO_HW_MVD,
    MMP_INFO_HW_MJPD,
};

enum MMP_PRIORITY_TYPE
{
    MMP_PRIORITY_HIGH = 0,
    MMP_PRIORITY_LOW
};

enum
{
    MMP_STATE_CLOSE = 0,
    MMP_STATE_OPENING,
    MMP_STATE_PAUSE,
    MMP_STATE_PLAY,
    MMP_STATE_PLAY_END,
    MMP_STATE_STOP,
    MMP_STATE_SEEKING,
    MMP_STATE_SEEK_COMPLETE,
};

enum
{
    MMP_MSG_EOS = 0,
    MMP_MSG_OPEN_COMPLETE,
    MMP_MSG_OPEN_FAIL,
    MMP_MSG_OPEN_MEM_FAIL,
    MMP_MSG_PLAY_FAIL,
    MMP_MSG_SEEK_COMPLETE,
    MMP_MSG_SEEK_FAIL,
    MMP_MSG_GET_FILE_INFO_COMPLETE,
    MMP_MSG_LOW_PRIORITY,
    MMP_MSG_HIGH_PRIORITY,
};

typedef struct MMP_VO_SETTING_S
{
    uint16_t disp_width;
    uint16_t disp_height;
    uint16_t disp_start_x;
    uint16_t disp_start_y;
    uint8_t  *disp_buffer;
    MMP_ROTATE_MODE rotate_mode;
    int      maced;
} MMP_VO_SETTING;

#define MMP_ENABLE_AUDIO    (1 << 0)
#define MMP_ENABLE_VIDEO    (1 << 1)
#define MMP_ENABLE_SUBTITLE (1 << 2)

#ifdef __cplusplus
extern "C" {
#endif

int MMP_Open(struct cb_io_s *cbio, void **pInst, int volume, int program_id, int appmode, mmp_notify_cb *notify_cb, uint8_t *password, unsigned int password_len, int capability, int enable_track);

int MMP_Play3(struct cb_io_s *cbio, void *ao_handle, void *vo_handle, void *pInst, int enable_track, MMP_VO_SETTING *vo_setting);

int MMP_Pause(void *pInst);

int MMP_Continue(void *pInst);

int MMP_Stop(void *pInst);

int MMP_GetFileInfo3(struct cb_io_s *cbio, mmp_file_info *pInfo, KMV_info *pKmvInfo, int appmode, uint8_t *password, uint32_t password_len);

int MMP_GetInfo_Memory(void **pInst, const void *data, int len, int type_hint, mmp_file_info *pInfo, int appmode);

int MMP_GetActiveFileInfo(void *pInst, mmp_file_info *pInfo, KMV_info *pKmvInfo);

MMP_CMD_ATTRIBUTE MMP_GetUserCommand(int *param, int block);

//for seek function
//pi32Pos: timestamp of the seek point
int MMP_SetPos(void *pInst, int32_t pi32Pos, int flag); /* TODO: define flag */

//*pu32Pos: reported time position
int MMP_GetPos(void *pInst, uint32_t *pu32Pos);

int MMP_CancelSeek(void *pInst);

int MMP_GetDispInfo(void *pInst, void *pInfo);

int MMP_SetSpeed(void *pInst, int speed_percent);

int MMP_GetSpeed(void *pInst, int *speed_percent);

void MMP_SetStatus(void *pInst, uint16_t status, int cause);

int MMP_GetStatus(void *pInst);

int MMP_GetVolume(void *pInst, uint32_t *volume_p);

int MMP_SetVolume(void *pInst, uint32_t volume);

int MMP_MuteVolume(void *pInst);

int MMP_UnmuteVolume(void *pInst);

int MMP_MixSound(void *pInst, const ms_fnchar *filename);

int MMP_SetEQMode(void *pInst, unsigned int EQMode);

int MMP_GetCommandMode(void);

void MMP_SetCommandMode(int mode);

int MMP_AllocateMem(void);

int MMP_SetBufAddr(unsigned char *mmp_addr      , int mmp_size,
                   unsigned char *map_addr      , int map_size,
                   unsigned char *map_info_addr , int map_info_size,
                   unsigned char *mmp_input_addr, int mmp_input_size,
                   unsigned char *mmp_fb_addr   , int mmp_fb_size,
                   unsigned char *audio_out_addr, int audio_out_size);

int MMP_ReleaseMem(void);

int MMP_GetAudSpec(void *pInst, int64_t *pts, short *p16AudSpecLevel);

int MMP_SetAudSpec(int EnableAudSpec);

int MMP_SetTrack(void *pInst, MMP_TRACK_TYPE track_type, int track_id);

int MMP_SetDispInfo(void *pInst, MMP_VO_SETTING *vo_setting);

int MMP_ResetPlayer(void **pInst);

int MMP_SetPriority(void *pInst, int priority_type);

int MMP_StartProfilePlayer(void);

int MMP_EndProfilePlayer(void);

int MMP_GetPlayerProfile(void *pInst, int *cpu_usage);

int MMP_GetSeekTime(void *pInst, int *seek_time);

void MMP_InitPlugins(int speed_page_mode);

extern char *mmp_revision;
extern char *mmp_baseurl;

#ifdef __cplusplus
}
#endif

#endif /* MMP_API_H */
