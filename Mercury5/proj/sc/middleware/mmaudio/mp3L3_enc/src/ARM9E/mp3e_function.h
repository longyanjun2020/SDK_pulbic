#ifndef __MP3_L3_ENCODER_FUNCTION_INCLUDE_FILE__
#define __MP3_L3_ENCODER_FUNCTION_INCLUDE_FILE__


int     mp3e_l3_format_bitstream(mp3e_global_struct *gfp);
void    mp3e_l3_flush_bitstream(mp3e_global_struct *gfp);
int     mp3e_l3_copy_buffer(mp3e_global_struct * gfp, unsigned char *buffer, int size);


int mp3e_l3_bit_reservoir(mp3e_global_struct *gfp,int *pe, int mean_bits);
void mp3e_l3_inter_channel_bits(mp3e_global_struct *gfp,int *pe, int *used_bit,int max_bits);
void mp3e_l3_decide_ms(mp3e_global_struct *gfp, int *pe_LR,int *pe_MS);
void mp3e_l3_L3psycho(mp3e_global_struct *gfp,int gr_out,int *pe_LR, int *pe_MS);

int mp3e_l3_BitrateIndex(int bRate,int version,int samplerate,int *full_bitrate_index);
void mp3e_l3_init_outer_loop(mp3e_global_struct *gfp, gr_info *cod_info);
void mp3e_l3_iteration_loop(mp3e_global_struct *gfp, gr_info *cod_info, int xrpow[576],int gr,int ch, int desired_bits,int PE);
int mp3e_l3_SmpFrqIndex(int, int *);

int mp3e_l3_ifast_log2(int x,int in_bit, int out_bit);
//int mp3e_l3_ifast_sqrt(int x,int in_bit, int out_bit);
void mp3e_l3_init_scalefac(mp3e_global_struct * gfp,gr_info *cod_info,int ch);
int mp3e_l3_writeMainData(mp3e_global_struct * gfp,int gr,int ch);


void mp3e_l3_init_xrpow(mp3e_global_struct * gfp, gr_info *cod_info, int *xrpow);

int     mp3e_l3_count_bits(mp3e_global_struct *gfp, int *xr,gr_info *cod_info);
int     mp3e_l3_noquant_count_bits(mp3e_global_struct *gfp,gr_info *cod_info);

void    mp3e_l3_best_scalefac_store(mp3e_global_struct * gfp, int gr, int ch,III_side_info_t * l3_side);
int     mp3e_l3_scale_bitcount(mp3e_global_struct * gfp,gr_info *gi);
int     mp3e_l3_scale_bitcount_lsf(mp3e_global_struct * gfp, gr_info *gi);


int     mp3e_l3_ResvFrameBegin(mp3e_global_struct *gfp, int *mean_bits);
void    mp3e_l3_ResvFrameEnd(mp3e_global_struct * gfp, int mean_bits);
void    mp3e_l3_mdct_sub48(mp3e_global_struct * gfp, short *w0, int gr, int ch);
void *mp3e_l3_oem_init(void *sram_ptr,int sram_len,void *heap_ptr,int heap_len);

#endif

