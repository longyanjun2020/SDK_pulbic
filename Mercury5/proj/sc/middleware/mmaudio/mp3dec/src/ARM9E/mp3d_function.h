# ifndef _MP3_DECODER_FUNCTION_INCLUDE_FILE_ 
# define _MP3_DECODER_FUNCTION_INCLUDE_FILE_

#define min_value(x,y) ((x)>(y))?(y):(x)



void mp3d_memcpy(void *dstp,void *srcp, int size);


void ms_stereo_dec(int *xr[2], short *modes,unsigned char *sfbwidth);
int mp3_interim_init_sync(mp3dec *pmd,int max_size);
int mp3_interim_next_sync(mp3dec *pmd,int max_size);
int mp3_interim_decode(mp3dec *pmd);

void js_stereo_dec(mp3dec *pmd,gr_ch_struct *gr_ch1,int *xr[2], short *modes,unsigned char *sfbwidth);
void js_stereo_ext_dec(mp3dec *pmd,gr_ch_struct *gr_ch1,int *xr[2], short *modes,unsigned char *sfbwidth);
int MP2_decode(mp3dec *pmd);
int MP1_decode(mp3dec *pmd);
mp3dec *mp3_oem_dmem_init1(int *sram_ptr,int *heap_ptr, int sram_size, int getinf);
void mp3_oem_dmem_init2(mp3dec *pmd, int sram_size);
unsigned int hcs_bit_read(mp3dec *pmd,int len);

int decode_header(mp3dec *pmd,unsigned int val);
int verify_header(mp3dec *pmd,unsigned int val);
void mp3_dec_init(mp3dec *pmd);

int III_sideinfo(mp3dec *pmd,unsigned int *data_bitlen);
void III_synth(mp3dec *pmd,int ch, int phase, int *pcm1,int nsb, int (*sbsample)[18][32]);
int III_scalefactors(mp3dec *pmd,struct channel *channel,
                     struct channel *gr0ch, unsigned int scfsi);
unsigned int III_scalefactors_lsf(mp3dec *pmd,struct channel *channel,
              struct channel *gr1ch, int mode_extension);
void III_reorder(int *xr, struct channel *channel,int mixed_l,
       unsigned char sfbwidth[39], int *dst);

void III_freqinver(int sample[18][32], unsigned int sb);

void III_overlap_z(int overlap[18], int sample[18][32], unsigned int sb);
void III_imdct_s(mp3dec *pmd,int X[18], int overlap[18], int sample[18][32], unsigned int sb);
void III_imdct_l(mp3dec *pmd,int X[18], int overlap[18], int sample[18][32], unsigned int sb, unsigned int block_type);
void III_aliasreduce(mp3dec *pmd,int xr[576], int lines);
int III_stereo(mp3dec *pmd,int *xr[2], unsigned char *sfbwidth, int mixed_l,int mixed_s);
int III_huffdecode(mp3dec *pmd,int xr[576], struct channel *channel,
                          unsigned char *sfbwidth, unsigned int part2_length);

void huffman_skip_byte(mp3dec *pmd,int byte_len);
unsigned int mp3_bit_read(mp3dec *pmd,int len);
void III_exponents(mp3dec *pmd,struct channel *channel, unsigned char *sfbwidth, int exponents[39]);
void init_hcs_ptr(mp3dec *pmd,unsigned char *ptr);
void audio_byte_skip(mp3dec *pmd,int byte_len);
unsigned int hcs_bit_read32(mp3dec *pmd);
unsigned short mp3_bit_crc(mp3dec *pmd,int len,unsigned int cache,unsigned short init);
unsigned short l3_crc_check(mp3dec *pmd,int len,unsigned short init);
int III_requantize_count1(mp3dec *pmd,int exp);
int III_dequantize_p1(int exp,int frac);
int III_requantize(mp3dec *pmd,unsigned int value, int exp,int frac);
int III_dequantize_p256(mp3dec *pmd,int value, int exp, int frac);

void fill_mdb(mp3dec *pmd);
unsigned int hcs_byte_read(mp3dec *pmd,int len);
void reset_overlap_data(mp3dec *pmd,int layer);
int search_got_sync(mp3dec *pmd,int *psyn_ind,int flag,int max_size);
int get_syncword_mdb(mp3dec *pmd,int syn_ind,int max_size);
//------------------------------------------------
//------------------------------------------------
static INLINE int huffman_append_cache16(mp3dec *pmd)
{
   if(pmd->mdb_num==0)  //copy bs buffer content to mdb buffer content
      fill_mdb(pmd);
   pmd->ado_cache = (pmd->ado_cache<<8) | ((*pmd->mdbptr++) & 0x00ff);
   pmd->ado_cache_left += 8;  
   pmd->mdb_num--;

   return 1;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static INLINE unsigned int huffman_bit_viewn(mp3dec *pmd,int len)
{
   unsigned int val = 0;
   
   while(pmd->ado_cache_left < len)
      huffman_append_cache16(pmd);

   val = (pmd->ado_cache >> (pmd->ado_cache_left-len)) & ((1<<len)-1);

   return val;
}
//----------------------------------------------------
//mp3_bit_read() is the same with huffman_bit_read()
//----------------------------------------------------

static INLINE unsigned int huffman_bit_read(mp3dec *pmd,int len)
{
   unsigned int val = 0;

   if(pmd->ado_cache_left < len)
      huffman_append_cache16(pmd);
   if(pmd->ado_cache_left < len)
      huffman_append_cache16(pmd);
   pmd->ado_cache_left -= len;
   val = ((pmd->ado_cache >> pmd->ado_cache_left) & ((1<<len)-1));

   return val;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
static INLINE unsigned int huffman_1bit_read(mp3dec *pmd)
{
   unsigned int val = 0;

   if(pmd->ado_cache_left==0)
   {
      huffman_append_cache16(pmd);
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
