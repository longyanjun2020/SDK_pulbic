
#ifndef __MP4_PARSER_DECODER_STRUCT_INCLUDE_FILE__
#define __MP4_PARSER_DECODER_STRUCT_INCLUDE_FILE__





#define MAX_TRACKS 1

#define TRACK_UNKNOWN 0
#define TRACK_AUDIO   1
#define TRACK_VIDEO   2
#define TRACK_SYSTEM  3
#define TRACK_OTHER   3

#define ERROR_FORMAT_SIZE (0x01)
#define ERROR_NO_MEMORY  (0x02)
#define FOURCC(a,b,c,d) ((a<<24)|(b<<16)|(c<<8)|(d))
#define BOX_FTYP FOURCC('f','t','y','p')
#define BOX_MDAT FOURCC('m','d','a','t')
#define BOX_MOOV FOURCC('m','o','o','v')
#define BOX_MVHD FOURCC('m','v','h','d')
#define BOX_TRAK FOURCC('t','r','a','k')
#define BOX_TKHD FOURCC('t','k','h','d')
#define BOX_TREF FOURCC('t','r','e','f')
#define BOX_EDTS FOURCC('e','d','t','s')
#define BOX_MDIA FOURCC('m','d','i','a')
#define BOX_MDHD FOURCC('m','d','h','d')
#define BOX_HDLR FOURCC('h','d','l','r')
#define BOX_MINF FOURCC('m','i','n','f')
#define BOX_VMHD FOURCC('v','m','h','d')
#define BOX_SMHD FOURCC('s','m','h','d')
#define BOX_HMHD FOURCC('h','m','h','d')
#define BOX_NMHD FOURCC('n','m','h','d')
#define BOX_DINF FOURCC('d','i','n','f')
#define BOX_DREF FOURCC('d','r','e','f')
#define BOX_STBL FOURCC('s','t','b','l')
#define BOX_STSD FOURCC('s','t','s','d')
#define BOX_STTS FOURCC('s','t','t','s')
#define BOX_CTTS FOURCC('c','t','t','s')
#define BOX_STSC FOURCC('s','t','s','c')
#define BOX_STSZ FOURCC('s','t','s','z')
#define BOX_STCO FOURCC('s','t','c','o')

#define BOX_MP4A FOURCC('m','p','4','a')
#define BOX_MP4V FOURCC('m','p','4','v')
#define BOX_MP4S FOURCC('m','p','4','s')
#define BOX_DRMS FOURCC('d','r','m','s')
#define BOX_ESDS FOURCC('e','s','d','s')

typedef struct
{
   int stsc_first_chunk;
   int stsc_samples_per_chunk;
}stsc_struct;


typedef struct
{
   uint64_t duration;
   int type;
   int channelCount;
   int sampleSize;
   unsigned int sampleRate;
   int audioType;

   int stsz_sample_size;
   int stsz_sample_count;
   int *stsz_table;
   unsigned int stsz_file_offset;
   int stsz_range_start;
   int stsz_range_end;

   int stts_entry_count;

   int stsc_entry_count;   
   unsigned int stsc_file_offset;
   int stsc_range_start;
   int stsc_range_end;
   stsc_struct *stsc_table;

   unsigned int stco_file_offset;
   int stco_range_start;
   int stco_range_end;
   int stco_entry_count;
   int *stco_table;
   unsigned int last_stco_offset;

   unsigned int maxBitrate;
   unsigned int avgBitrate;
   unsigned int timeScale;   
   unsigned int stsz_sample_byte;
   int tot_sample;
   int cn_srate,cn_ch,cn_header_type,cn_ret;  
   int cn_sbr_present_flag,cn_downSampledSBR,cn_forceUpSampling;   
   int last_chunk_index_on_file;
   unsigned int last_chunk_offset_on_file;
} mp4ff_track_t;

// mp4 main file structure 
typedef struct
{
   uint64_t file_offset;
   int duration;
   int total_tracks;
   mp4ff_track_t track[MAX_TRACKS];
} mp4ff_t;



//#define MP4_BITSTREAM_SIZE 4096
#define MP4_BITSTREAM_SIZE 1024
#define MAX_STCO_ENTRY_FOR_PLAYTIME     0x1000  

//--------------------------------------------

typedef struct
{
   unsigned char mp4_bitstream_buf[MP4_BITSTREAM_SIZE];    // input bitstream buffer 
   int fending;

   int buf_left;
   unsigned char *bsbuf;
   unsigned int file_size;
   int mp4_format;
   int id3_len;
   int (*aop_read)(void *,unsigned char *buf, int len,int *fending);
   void (*aop_seek)(void *,unsigned int file_ptr);
   void *aacd_instance;
   int srate;
   int ch;
   int header_type;   

   mp4ff_t mp4ff;

   int moov_exist;
   int mdat_exist;
   unsigned int mdat_len;

   int sample_size;
   int cur_sample;

   int cur_track;
   unsigned int cur_chunk_offset;

   int cur_chunk_frame_idx;
   int cur_chunk_idx;

   int next_stsc_index;
   int cur_chunk_totframe;
   int next_first_chunk;
   int video_num;
   int chunk_sum;
   //---------------------
   int chunk_size;
   int avg_bitrate;
   int total_time;    

   int mvhd_time_scale;
   int mvhd_duration;
   unsigned int mdat_fpos;
   int max_size;
   int consume_byte_per_frame;
   int updated_total_time;
   int frame_time;
   int enable_sbr;
   int stsc_buf_entry;   
   int stsz_buf_entry;  
   int stco_buf_entry;     
   int *stsc_buf;
   int *stsz_buf;
   int *stco_buf;
   unsigned int bs_file_offset;  //not include ID3
   int seek_back;
   void *cb_instance;
}mp4_data_struct;

#define CURRENT_BITSTREAM_FILE_OFFSET   (pad->bs_file_offset - pad->buf_left)

#define mp4_aop_min(a, b) (((a) < (b)) ? (a) : (b))
#define mp4_aop_max(a, b) (((a) > (b)) ? (a) : (b))
int mp4_fill_read(mp4_data_struct *pad);
void mp4_byte_skip(mp4_data_struct *pad,int byte_len);
uint64_t mp4_8byte_read(mp4_data_struct *pad);
unsigned int mp4_nbyte_read(mp4_data_struct *pad,int len);
unsigned int mp4_1byte_read(mp4_data_struct *pad);
int mp4_read_data(mp4_data_struct *pad,unsigned char * buf, int len);

int mp4_init_decoding(mp4_data_struct *pad);


int mp4_interim_aop_read(void *cb_instance,unsigned char *buf, int len, int *pts, int *chunk_size, int *fending);
int mp4_aop_parse_atoms(mp4_data_struct *pad);
int mp4ff_refill_stsc(mp4_data_struct *pad,mp4ff_track_t * track,int pos, int do_seek);
int mp4ff_refill_stsz(mp4_data_struct *pad,mp4ff_track_t * track,int pos);
int mp4ff_refill_stco(mp4_data_struct *pad,mp4ff_track_t * track,int pos);
void mp4_skip_to_codec(mp4_data_struct *pad,int len);
int mp4_read_to_codec(mp4_data_struct *pad,unsigned char * buf, int len);

#endif
