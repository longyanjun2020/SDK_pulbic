# ifndef _MP3_DECODER_FUNCTION_INCLUDE_FILE_ 
# define _MP3_DECODER_FUNCTION_INCLUDE_FILE_

#define min_value(x,y) ((x)>(y))?(y):(x)



void mp3d_memcpy(void *dstp,void *srcp, int size);


void ms_stereo_dec(int *xr[2], short *modes,unsigned char *sfbwidth);
int mp3_interim_init_sync(int max_size);
int mp3_interim_next_sync(int max_size);
int mp3_interim_decode(void);
void Mstar_mp3d_post_process(int mono_stereo,int stereo_reverse,int samples,int ch,int **pcm_buf,short *out_buf);
void js_stereo_dec(gr_ch_struct *gr_ch1,int *xr[2], short *modes,unsigned char *sfbwidth);
void js_stereo_ext_dec(gr_ch_struct *gr_ch1,int *xr[2], short *modes,unsigned char *sfbwidth);
int MP2_decode(void);
int MP1_decode(void);
void mp3_oem_dmem_init1(void);
void mp3_oem_dmem_init2(void);
unsigned int hcs_bit_read(int len);

int decode_header(unsigned int val);
int verify_header(unsigned int val);
void mp3_dec_init(void);
void mp3_stream_init(void);
void mp3_frame_init(void);
void mp3_header_init(void);
//void fill_granule2(void);
void audio_byte_skip2(int byte_len);
unsigned short mp3_bit_crc(int len, unsigned int cache, unsigned short init);
int III_sideinfo(unsigned int *data_bitlen);
void III_synth(int ch, int phase, int *pcm1,int nsb, int (*sbsample)[18][32]);
int III_scalefactors(struct channel *channel,
                     struct channel *gr0ch, unsigned int scfsi);
unsigned int III_scalefactors_lsf(struct channel *channel,
              struct channel *gr1ch, int mode_extension);
void III_reorder(int *xr, struct channel *channel,int mixed_l,
       unsigned char sfbwidth[39], int *dst);

void III_freqinver(int sample[18][32], unsigned int sb);

void III_overlap_z(int overlap[18],
         int sample[18][32], unsigned int sb);
void III_imdct_s(int X[18], int overlap[18], int sample[18][32], unsigned int sb);
void III_imdct_l(int X[18], int overlap[18], int sample[18][32], unsigned int sb, unsigned int block_type);
void III_aliasreduce(int xr[576], int lines);
int III_stereo(int *xr[2], unsigned char *sfbwidth, int mixed_l,int mixed_s);
int III_huffdecode(int xr[576], struct channel *channel,
                          unsigned char *sfbwidth, unsigned int part2_length);



unsigned int audio_huffman_read(unsigned int bitcache, int bits);

int audio_read_cache(void);
void huffman_skip_byte(int byte_len);
int audio_read_16bit(void);
unsigned int mp3_bit_read(int len);
int III_requantize_1(int exp);
int III_requantize_32(unsigned int value, int exp);
int III_requantize_count1_32(int exp);
void III_exponents(struct channel *channel, unsigned char *sfbwidth, int exponents[39]);
//void fill_granule(void);
void init_hcs_ptr(unsigned char *ptr);
void audio_byte_skip(int byte_len);
//void copy_bs_to_mdb(int byte_len,unsigned char **dstptr);
//void mp3_byte_align(void);
unsigned int hcs_bit_read32(void);

unsigned short mp3_bit_crc(int len,unsigned int cache,unsigned short init);
unsigned short l3_crc_check(int len,unsigned short init);
void l3_crc_check_layer3(int len);
int III_requantize_count1(int exp);
int III_dequantize_p1(int exp,int frac);
int III_requantize(unsigned int value, int exp,int frac);
int III_dequantize_p256(int value, int exp, int frac);

void fill_mdb(void);
unsigned int hcs_byte_read(int len);
void reset_overlap_data(int layer);

//------------------------------------------------
//------------------------------------------------
static INLINE int huffman_append_cache16(void)
{
   if(pmd->mdb_num==0)  //copy bs buffer content to mdb buffer content
      fill_mdb();
   pmd->ado_cache = (pmd->ado_cache<<8) | ((*pmd->mdbptr++) & 0x00ff);
   pmd->ado_cache_left += 8;  
   pmd->mdb_num--;

   return 1;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static INLINE unsigned int huffman_bit_viewn(int len)
{
   unsigned int val = 0;
   
   while(pmd->ado_cache_left < len)
      huffman_append_cache16();

   val = (pmd->ado_cache >> (pmd->ado_cache_left-len)) & ((1<<len)-1);

   return val;
}
//----------------------------------------------------
//mp3_bit_read() is the same with huffman_bit_read()
//----------------------------------------------------

static INLINE unsigned int huffman_bit_read(int len)
{
   unsigned int val = 0;

   if(pmd->ado_cache_left < len)
      huffman_append_cache16();
   if(pmd->ado_cache_left < len)
      huffman_append_cache16();
   pmd->ado_cache_left -= len;
   val = ((pmd->ado_cache >> pmd->ado_cache_left) & ((1<<len)-1));

   return val;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static INLINE unsigned int huffman_1bit_read(void)
{
   unsigned int val = 0;

   if(pmd->ado_cache_left==0)
   {
      huffman_append_cache16();
   }

   pmd->ado_cache_left--;
   val = (pmd->ado_cache >> pmd->ado_cache_left) & 0x01;

   return val;
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
#define huffman_syn_bit(len) \
{ \
   pmd->ado_cache_left -= len; \
}


#define GET_UPDATED_PTS \
{ \
   if(pts!=-1) pmd->pts_time = pts; \
}

#endif
