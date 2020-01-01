#ifndef __MP3_ENC_FUNCTION_INCLUDE_FILE__
#define __MP3_ENC_FUNCTION_INCLUDE_FILE__

FLOAT ath_db(FLOAT f, FLOAT value);
int available_bits ( mp3e_data_struct * glopts );
void buffer_init(bit_stream* bs, unsigned char *buffer); //, int buffer_size );
void mp3e_oem_init(void);


void scalefactor_calc (int *sb_sample,
                  unsigned char sf_index[][SB_SIZE][3], int nch,
                  int sblimit);


void sf_transmission_pattern (mp3e_data_struct *glopts,
         unsigned char sf_index[2][SB_SIZE][3],
         unsigned char scfsi[2][SB_SIZE]);

void write_header_bit_alloc_scalefactors (mp3e_data_struct *glopts, unsigned char bit_alloc[2][SB_SIZE], 
      unsigned char scfsi[2][SB_SIZE],
      unsigned char sf_index[2][SB_SIZE][3],
      bit_stream * bs);
ATTR_NOMIPS16 void write_quan_samples ( mp3e_data_struct *glopts, bit_stream * bs);


void main_bit_allocation (mp3e_data_struct * glopts, int SMR[2][SB_SIZE],
         unsigned char scfsi[2][SB_SIZE],
         unsigned char bit_alloc[2][SB_SIZE], int *adb );

int a_bit_allocation (mp3e_data_struct * glopts, int SMR[2][SB_SIZE],
         unsigned char scfsi[2][SB_SIZE],
         unsigned char bit_alloc[2][SB_SIZE], int *adb );


ATTR_NOMIPS16 void window_subband(short * x1, int *ao);


void psycho_init (mp3e_data_struct *glopts);
void psycho_enc (mp3e_data_struct *glopts);


/*write N bits into the bit stream */
//ㄧ次最多的bit 數目是16, the max of N = 16
static inline void buffer_putbits (bit_stream * bs, unsigned int val, int len)
{
   bs->ado_cache_left += len;
   bs->ado_cache |= val << (32-bs->ado_cache_left);
   if(bs->ado_cache_left >= 16)
   {
      bs->ado_cache_ptr[0] = (bs->ado_cache >> 24);
      bs->ado_cache_ptr[1] = (bs->ado_cache >> 16);
      bs->ado_cache_ptr += 2;
      bs->ado_cache <<= 16;
      bs->ado_cache_left -= 16;
   }
}

static inline int buffer_flush_pad(bit_stream * bs, int len)
{
   bs->ado_cache_left += len;
   while(bs->ado_cache_left)
   {
      *bs->ado_cache_ptr++ = (bs->ado_cache >> 24);
      bs->ado_cache <<= 8;
      bs->ado_cache_left -= 8;
   }
   return (int)(bs->ado_cache_ptr-bs->buf);
}


#endif


