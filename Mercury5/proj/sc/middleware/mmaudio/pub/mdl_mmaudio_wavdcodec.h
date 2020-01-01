#ifndef _PUB_WAVDEC_H
#define _PUB_WAVDEC_H
#ifdef __cplusplus
extern "C"{
#endif

#ifdef PIONEER_PLAYER
#include "mmp_common_types.h"
#else
//#include "shellmgr.h"
#endif
//#include "ms_io.h"
#include "vm_types.ht"


extern u32 WAVHeaderParser(void *pInst, u32 *data_pos, void *aPCMWaveHeader, void *aIMAADPCMHeader, void *aMSADPCMHeader);

extern void  wav_decoder_funcinit(void *pInst);

extern s32 wav_decoder_open(void *player,
                            u32 *bits_per_sample,
                            u32 *sample_rate,
                            u16 *frame_length,
                            u8 *channels,
                            u32 *para);
extern u32 wav_decoder_close(void *pInst);
extern s32 wav_decoder_decode_data(void *player,
                         u8 **out_buf, u32 *out_size, u32 *iisthreshold,u32 *consume_size);
extern s32 wav_decoder_seek_data(void *player, u32 *seektime);
extern s32 wav_decoder_get_timestamp(void *player, u32 *pu32Pos);
extern void wav_decoder_engine_clock(void *pinst, u8 onoff);



#if 1
extern u32 WAVPCMFormat_Init_MMP( void* WavPCMHeader);
extern s32 WAVPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);


extern s32 WAVIMAADPCMFormat_Init_MMP(void* IMAADPCMAudBlkHeader);
extern s32 WAVIMAADPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);


extern s32 WAVMSADPCMFormat_Init_MMP(void* WavPCMHeader);
extern s32 WAVMSADPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);

extern u32 WAVALawADPCMFormat_Init_MMP(void* ALawADPCMAudBlkHeader);
extern s32 WAVALawADPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);

extern u32 WAVMuLawADPCMFormat_Init_MMP(void* MuLawADPCMAudBlkHeader);
extern s32 WAVMuLawADPCMFormat_Proc_MMP(u8 *out_buf, u32 *out_size, u8 *wavstreambuf, u32 *consumed_size, u32 residual_size);

#endif



#ifdef __cplusplus
}
#endif
#endif

