#ifndef AAC_DECODER_FUNCTION1_INCLUDE
#define AAC_DECODER_FUNCTION1_INCLUDE


void aacd_memset8(void *buf,int len);



void pns_decode_channel(ic_stream *ics, ic_stream *icsr, int *l_spec,
                    int *r_spec, unsigned char *ms_used_ptr);
void pns_decode_mono(ic_stream *ics, int *l_spec);

void is_decode(ic_stream *ics, ic_stream *icsr, int *l_spec, int *r_spec); 

//----------------------------------------------------------------------------------------
void ms_decode(ic_stream *ics, int *l_spec, int *r_spec);
//-------------------------------------------------------------------------------------
int single_lfe_channel_element(int channel);
int channel_pair_element(int channels);
//------------------------------------------------------------------------------------
int dec_spectral_data(aac_dec *paacd, ic_stream *ics, int *spectral_data);
void tns_data(ic_stream *ics);
int tns_lpc_frame(ic_stream *ics, int sr_index, int *spec);
int *synthesis(aac_dec *paacd,int win_seq,int win_shape, int win_shape_prev, int *freq_in, int *overlap,int **free_buf);
int ReadFillElement(drc_info *drc,int *sbr_ele, int prev_element);
int aac_get_sample_rate(int sr_index);
int aac_get_sample_index(int sr);
int decode_scale_factors(aac_dec *paacd,ic_stream *ics);
//------------------------------------------------------------------------------------
unsigned int aac_bit_read(int len);
unsigned int aac_1bit_read(void);
unsigned int aac_bit_view2(int len);
int ADTSFrameCount(int skipframe, unsigned int *tolsize,int filelen,int *fbrowser);
int LOASFrameCount(int skipframe, unsigned int *tolsize,int filelen,int *fbrowser);
unsigned int aac_bit_view32(void);
void aac_byte_read(unsigned char *buf,int byte_len);
void aac_next_granule(void);
void aac_byte_skip(int byte_len);
void eng_fill_frame(void);
//------------------------------------------------------------------------------------
unsigned char program_config_element(program_config *pce);
int adts_fixed_header(void);
unsigned short data_stream_element(void);
int decode_cpe(int id_syn_ele);
int decode_sce_lfe(int id_syn_ele);




void AACD_ao_bitstream_callback(unsigned char *buf, int len);
void AAC_ADIF_header(int file_size,int *srate, int *ch,int *bitrate,int *total_time,int *object_type);
int AAC_ADTS_header(int *ch,int *srate,int *object_type,int sync_flag,int max_size);
void OEM_aacd_sram_init(int enable_sbr);





#endif

