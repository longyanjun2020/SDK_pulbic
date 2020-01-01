#ifndef MAP_API_H
#define MAP_API_H

//#include <stdint.h>
//#include "utility.h"
//#include "ms_io.h"
#include "audioplayer.h"
//#include "mm_manager.h"
//#include "MML_Manager.h"
//#include "srv_ResMgr_Aud.h"
//#include "srv_resmgr_mmlaudio_types.h"
#include "sys_vm_dbg.ho"

#define NEW_AUDPLAYER

    //#define MAP_DBG(fmt, args...)
    #define MAP_DBG //(fmt, args...)  vm_dbgTrace(_CUSAUD,fmt, ##args)
    //#define MAP_DBG diag_printf
    #define MAP_ERR //(fmt, args...) vm_dbgTrace(_CUSAUD,fmt, ##args)


#define cyg_thread_delay MsSleep


extern audio_rbuffer audiorbuffer;
extern audioplayer_s *gpAUDtask;
//extern U8 audio_dynDLOK;

    typedef enum
    {
        AUDIO_PLUGIN_NONE = 0x00,
        AUDIO_PLUGIN_AACDEC = 0x01,
        AUDIO_PLUGIN_WAVDEC = 0x02,
        AUDIO_PLUGIN_AMRDEC = 0x03,
        AUDIO_PLUGIN_MP3DEC = 0x04,
        AUDIO_PLUGIN_AMRWBDEC = 0x05,
        AUDIO_PLUGIN_WMADEC = 0x06,
        AUDIO_PLUGIN_COOKDEC = 0x07,
    }AUDIO_PLUGIN_ID;




int MAP_Continue(void *pInst);
int MAP_GetFileInfo(const ms_fnchar *filename, void *pInfo);
int MAP_GetPos(void *pInst, u32 *pu32Pos);
int MAP_Pause(void *pInst);
int MAP_GetDMATime(void *pInst, u32 *pu32time);
int MAP_Pause_Seek(s32 pause_seek_pos);
s32 MAP_Play(const ms_fnchar *filename, void *pInst);
int MAP_SetPos(void *pInst, u32 *pu32Pos, s8 flag);
int MAP_Stop(void *pInst);

extern u8 fnAUDPlayer_get_audio_status(void);
extern int init_SAMR_decoder2(void *player);

#ifdef __MDL_AUD_PLAY_RINGBUF__
extern s32 MdlAudPlayFillRBuf(audio_rbuffer *b, u32 rbhandle);
extern s32 MdlAudPlayCheckEnd(audio_rbuffer *b, u32 nRBhandle);
extern s32 MdlAudPlayAdvanceRBuf(audio_rbuffer *b, u32 bytes, u32 nRBhandle);
extern int MdlAudPlayCopyRBuf(audio_rbuffer *b, u8 *dest_buf, u32 bytes, u32 nRBhandle);
extern s32 MdlAudPlayResetRBuf(audio_rbuffer *b, u32 rbhandle);
extern s32 MdlAudPlayCheckRemainSize(u32 nRBhandle, u32 *nRemainSize);
#else
extern int _Audio_copy_rbuffer(audio_rbuffer *b, u8 *dest_buf, u32 bytes);
extern s32 _Audio_fill_rbuffer(audio_rbuffer *b);
extern s32 _Audio_advance_rbuffer(audio_rbuffer *b, u32 bytes);
extern s32 _Audio_rbuffer_reset_buf(audio_rbuffer *b,u8 *bufa, u8 *bufb, u32 bufsize);
extern s32 _Audio_rbuffer_init(audio_rbuffer *b, MSFILE rfile,void *pinst);
#endif

u32 MdlAudA2dpGetPosition(void);
extern void MdlAudMAPSendIntMsg(u16 MbxSrc, u16 MbxDst, s16 nInterMSgType, u32 nErrCode);
extern void MAPPrePlayStopHandler(void);

//extern void fnCreatAUDThread(void);
//extern void fnAUDExeCMDHandler(S16 s16Cmdid, S16 s16Attr, U32 u32Setting);
s32 fnAudioPlayer_Play(void *pInst);
void fnMpAudio_thread_init(void *pInst);

#endif
