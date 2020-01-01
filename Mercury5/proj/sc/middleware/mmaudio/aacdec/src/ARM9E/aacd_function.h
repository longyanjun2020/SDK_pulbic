#ifndef AAC_DECODER_FUNCTION1_INCLUDE
#define AAC_DECODER_FUNCTION1_INCLUDE


void aacd_memset8(void *buf,int len);



void pns_decode_channel(aac_dec *pad,ic_stream *ics, ic_stream *icsr, int *l_spec,
                    int *r_spec, unsigned char *ms_used_ptr);
void pns_decode_mono(aac_dec *pad,ic_stream *ics, int *l_spec);

void is_decode(aac_dec *pad,ic_stream *ics, ic_stream *icsr, int *l_spec, int *r_spec); 

//----------------------------------------------------------------------------------------
void ms_decode(ic_stream *ics, int *l_spec, int *r_spec);
//-------------------------------------------------------------------------------------
int single_lfe_channel_element(aac_dec *pad,int channel);
int channel_pair_element(aac_dec *pad,int channels);
//------------------------------------------------------------------------------------
int dec_spectral_data(aac_dec *pad,ic_stream *ics, int *spectral_data);
void tns_data(aac_dec *pad,ic_stream *ics);
int tns_lpc_frame(ic_stream *ics, int sr_index, int *spec);
int *synthesis(aac_dec *pad,int win_seq,int win_shape, int win_shape_prev, int *freq_in, int *overlap,int **free_buf);
int ReadFillElement(aac_dec *pad,drc_info *drc,int *sbr_ele, int prev_element);
int aac_get_sample_rate(int sr_index);
int aac_get_sample_index(int sr);
int decode_scale_factors(aac_dec *pad,ic_stream *ics);
//------------------------------------------------------------------------------------
unsigned int aac_bit_read(aac_dec *pad,int len);
unsigned int aac_1bit_read(aac_dec *pad);
unsigned int aac_bit_view2(aac_dec *pad,int len);
int ADTSFrameCount(aac_dec *pad,int skipframe, unsigned int *tolsize,unsigned int filelen,int *fbrowser);
int LOASFrameCount(aac_dec *pad,int skipframe, unsigned int *tolsize,unsigned int filelen,int *fbrowser);
unsigned int aac_bit_view32(aac_dec *pad);
void aac_byte_read(aac_dec *pad,unsigned char *buf,int byte_len);
void aac_next_granule(aac_dec *pad);
void aac_byte_skip(aac_dec *pad,int byte_len);
void eng_fill_frame(aac_dec *pad);
//------------------------------------------------------------------------------------
unsigned char program_config_element(aac_dec *pad,program_config *pce);
int adts_fixed_header(void);
unsigned short data_stream_element(aac_dec *pad);
int decode_cpe(aac_dec *pad,int id_syn_ele);
int decode_sce_lfe(aac_dec *pad,int id_syn_ele);




//void AACD_ao_bitstream_callback(unsigned char *buf, int len);
int AAC_ADIF_header(aac_dec *pad,unsigned int file_size,int *srate, int *ch,int *bitrate,int *total_time,int *object_type);
int AAC_ADTS_header(aac_dec *pad,int *ch,int *srate,int *object_type,int sync_flag,int max_size);
int AAC_LOAS_header(aac_dec *pad,int *ch,int *srate,int *object_type,int sync_flag,int max_size);
int OEM_aacd_sram_init(int *sram_ptr,int *heap_ptr,int enable_sbr,aac_dec **pad, int sram_size, int getinfo);





#endif

