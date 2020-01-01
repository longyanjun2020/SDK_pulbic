#ifndef _SBC_ENCODER_INCLUDE_LIBRARY_HEADER_FILE_
#define _SBC_ENCODER_INCLUDE_LIBRARY_HEADER_FILE_

#define SBC_MONO            0x00
#define SBC_DUAL_CHANNEL    0x01
#define SBC_STEREO          0x02
#define SBC_JOINT_STEREO    0x03

#define SBC_LOUDNESS    0x00
#define SBC_SNR         0x01


void Mstar_sbce_open(unsigned char *sram_ptr,unsigned char *sdram_ptr);

int Mstar_sbce_encode(short *input_buf, unsigned char *output_buf, unsigned short *output_len);

int Mstar_sbce_init(int channel_mode,int alloc_method,int nrof_blocks,int nrof_subbands,
                    int ch,int sample_freq,int bitrate,int br_flag);

void Mstar_sbce_set_mem(void *sram_ptr,void *sdram_ptr);

void Mstar_sbce_get_mem(int *sram_size,int *sdram_size);
int Mstar_sbce_CalcBitRate(int channel_mode, int nrof_blocks, 
                        int nrof_subbands, int ch,int sample_freq,int bitpool);

int Mstar_sbce_CalcBitPool(int *bitPoolAlt,int *togglePeriod, int channel_mode, int nrof_blocks, 
                        int nrof_subbands, int ch,int sample_freq,int bitrate);
                        
int Mstar_sbce_framelen(int channel_mode,int bitpool,int nrof_blocks,int nrof_subbands,int ch);

#endif
