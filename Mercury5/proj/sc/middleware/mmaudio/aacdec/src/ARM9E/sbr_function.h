#ifndef __HE_AAC_DECODER_SBR_FUNCTIONS_H__
#define __HE_AAC_DECODER_SBR_FUNCTIONS_H__


unsigned int sbr_bit_read(buffer_bs *bs,int len);
unsigned int sbr_bit_view(buffer_bs *bs,int len);
static INLINE unsigned int aac_sbr_bit_read(aac_dec *pad,int len)
{
   return sbr_bit_read(&pad->sbr_bs,len);
}

static INLINE unsigned int aac_sbr_1bit_read(aac_dec *pad)
{
   return sbr_bit_read(&pad->sbr_bs,1);
}


static INLINE unsigned int aac_sbr_get_processed_bits(aac_dec *pad)
{
	return pad->sbr_bs.bits_consumed;
}


static INLINE void aac_sbr_bit_flush(aac_dec *pad,int len)
{
   pad->sbr_bs.cache_left -= len;
   pad->sbr_bs.bits_consumed += len;
}


void sbr_buf_stream_init(buffer_bs *bs, unsigned char * bufptr, int len);

int log2_int(unsigned int val);
int pow2_int(int val);
int pow2_fix(int val);
int find_initial_power(unsigned int bands, unsigned int a0, unsigned int a1);

void sbrGetEnvelope(aac_dec *pad,sbr_info *sbr, int ch);
void sbrGetNoiseFloorData(aac_dec *pad,sbr_info *sbr, int ch);
void hf_generation(sbr_info *sbr, qmf_t (*Xlow)[64], sbr_ch_info *sbr_ch,int ch);
void GQ_addr_reset(sbr_info *sbr, int ch);
unsigned int hf_adjustment(sbr_info *sbr, qmf_t (*Xsbr)[64], int ch);
unsigned int estimate_current_envelope(sbr_info *sbr,
                                         qmf_t (*Xsbr)[64], sbr_ch_info *sbr_ch);
void calculate_gain(sbr_info *sbr, sbr_hfadj_info *adj, int ch);
void hf_assembly(sbr_info *sbr, sbr_hfadj_info *adj, qmf_t (*Xsbr)[64], sbr_ch_info *sbr_ch);
void patch_construction(sbr_info *sbr);
int qmf_start_channel(unsigned int bs_start_freq, 
                           unsigned int sr_index);
int qmf_stop_channel(unsigned int bs_stop_freq, unsigned int sr_index,
                          unsigned int k0);
int master_frequency_table_fs0(sbr_info *sbr, int k0, int k2, int bs_alter_scale);
int master_frequency_table(sbr_info *sbr, int k0, int k2, int bs_freq_scale);
int derived_frequency_table(sbr_info *sbr, int bs_xover_band, int k2);
void limiter_frequency_table(sbr_info *sbr);

void dct4_kernel(int * in_real, int * out_real);

void DCT4_32(int *y, int *x);
void DST4_32(int *y, int *x);


void qmfa_init(aac_dec *pad,qmfa_info *qmfa, int qmfa_index);

void qmfs_init(aac_dec *pad,qmfs_info *qmfs, int channels, int index);

void qmfs_end(qmfs_info *qmfs);

void sbr_qmf_analysis_32(sbr_info *sbr, qmfa_info *qmfa, const int *input,
                         qmf_t (*X)[64], int offset, int kx);
void sbr_qmf_synthesis_32(sbr_info *sbr, qmfs_info *qmfs, qmf_t (*X)[64],
                          int *output);
void sbr_qmf_synthesis_64(sbr_info *sbr, qmfs_info *qmfs, qmf_t (*X)[64],
                          int *output);

//int envelope_time_border_vector(sbr_info *sbr, sbr_ch_info *sbr_ch);
void noise_floor_time_border_vector(sbr_info *sbr, sbr_ch_info *sbr_ch);

sbr_info *sbrDecodeInit(aac_dec *pad,int elementID, unsigned int sample_rate, int downSampledSBR,int ele);
void sbrDecodeEnd(sbr_info *sbr);
void sbrReset(sbr_info *sbr);
unsigned int sbr_extension_data(aac_dec *pad,sbr_info *sbr, int cnt, int psResetFlag, int elementID,int extensionType);

unsigned int sbrDecodeCoupleFrame(sbr_info *sbr, int *left_chan, int *right_chan, 
                             int just_seeked, int downSampledSBR);
unsigned int sbrDecodeSingleFrame(sbr_info *sbr, int *pcm_in,
                             int just_seeked, int downSampledSBR);
#if defined(PS_DEC)
unsigned int sbrDecodeSingleFramePS(aac_dec *pad,sbr_info *sbr, int *left_channel, int *right_channel,
                               int just_seeked, int downSampledSBR);


int ReadPsData(aac_dec *pad,ps_info *ps, int *header, int *nr_bits);


ps_info *ps_init(aac_dec *pad,unsigned char sr_index);
void ps_decode(ps_info *ps, qmf_t (*X_left)[64], qmf_t (*X_right)[64], int *stack1,int *stack2);
void channel_filter2(hyb_info *hyb, const int *filter, qmf_t *buffer, qmf_t (*X_hybrid)[12]);
void channel_filter4(hyb_info *hyb, const int *filter, qmf_t *buffer, qmf_t (*X_hybrid)[12]);
void channel_filter8(hyb_info *hyb, const int *filter, qmf_t *buffer, qmf_t (*X_hybrid)[12]);
void channel_filter12(hyb_info *hyb, const short *filter, qmf_t *buffer, qmf_t (*X_hybrid)[12]);
void ps_decorrelate(ps_info *ps, qmf_t (*X_left)[64], qmf_t (*X_right)[64],
                           qmf_t (*X_hybrid_left)[32], qmf_t (*X_hybrid_right)[32]);
void ps_mix_phase(ps_info *ps, qmf_t (*X_left)[64], qmf_t (*X_right)[64],
                         qmf_t (*X_hybrid_left)[32], qmf_t (*X_hybrid_right)[32]);
#endif

void memcpy32(void *dest, void *src, int cnt);

int applySBR(aac_dec *pad,sbr_info *sbr, sbr_bitstream *sbr_bs_info, int ch, int *numChannels,int SbrFrameOK);
void decodeSbrData(sbr_info *sbr, int nrElements,int elementID);
void leanSbrConcealment(sbr_info *sbr, int ch);
void extract_envelope_data_env(sbr_info *sbr, sbr_ch_info *sbr_ch, int l, short *iEnvelope, int f_l);
void timeCompensateFirstEnvelope (sbr_info *sbr, int ch);
int checkEnvelopeData(sbr_info *sbr, int ch);
int checkFrameInfo (sbr_info *sbr, int ch);
int calc_sbr_crc(aac_dec *pad,int crc_check,int len);

#endif


