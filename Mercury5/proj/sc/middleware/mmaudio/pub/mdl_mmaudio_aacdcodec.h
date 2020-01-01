
#ifndef _PUB_AAC_DECODER_LIB_INCLUDE_FILE_
#define _PUB_AAC_DECODER_LIB_INCLUDE_FILE_

#define AACD_CONTENT_INVALID       0x40000
#define AACD_FORMAT_NOT_SUPPORT    0x10000
#define AACD_RESYNC_EOF            0x30000  
#define AACD_Decode_ERR            0x9807 
#define AACD_RESYNC_MAX_SIZE       0x20000  
#define AACD_FORMAT_MP4            0x00002
#define AACD_OK             0

#define MP4_RESYNC_EOF            0x30000  
#define MP4_CONTENT_INVALID       0x40000
#define MP4_OK                    0


#define AACDEC_SRAM_28K 27136 //26.5k for AAC LC   
#define AACDEC_SRAM_20K 20*1024                    
#define AACDEC_SRAM_16K 16*1024                    
#define AACDEC_SRAM_12K 12*1024                    
#define AACDEC_SRAM_0K  0  
//-----------------------------------------------------------
//for old AO API

/** \addtogroup MMAudioAACDecMdlApi 
* @{ 
*/

/**
 * \fn  int Mstar_AACD_aop_decode(void *aacd_instance,int **pcm_buf,int *play_time,int *ch,int *frame_size,int *sbr_flag,int max_size,int *avg_bitrate,int *total_time);
 * \brief  decode input data
 * \param[in] aacd_instance instance pointer 
 * \param[in] pcm_buf output buffer pointer
 * \param[in] play_time current play time 
 * \param[in] ch channel no
 * \param[out] frame_size frame size
 * \param[out] sbr_flag sbr present flag
 * \param[in] max_size max error, size  
 * \param[out] avg_bitrate average bit rate  
 * \param[out] total_time duration time  
 * \return 0 if the action is successful
 */
int Mstar_AACD_aop_decode(void *aacd_instance,int **pcm_buf,int *play_time,int *ch,int *frame_size,int *sbr_flag,int max_size,int *avg_bitrate,int *total_time);


/**
 * \fn  int Mstar_AACD_aop_seek(void *aacd_instance,int play_time,int fbrowser,int enable_sbr,int max_size);
 * \brief  seek fucntion
 * \param[in] aacd_instance instance pointer  
 * \param[in] play_time seek time 
 * \param[in] fbrowser seek mode
 * \param[in] enable_sbr enable sbr mode
 * \param[in] max_size max error size    
 * \return 0 if the action is successful
 */
int Mstar_AACD_aop_seek(void *aacd_instance,int play_time,int fbrowser,int enable_sbr,int max_size);

/**
 * \fn int Mstar_AACD_aop_init(unsigned int filelen, int *srate, int *ch,int *bitrate,int *total_time,
                        int *header_type,int max_frame,int fbrowser,int *sbr_flag, int enable_sbr,int max_size,
                        int (*aop_read)(void *,unsigned char *, int ,int *),void (*aop_seek)(void *,unsigned int),void *cb_instance,
                        int *sram_ptr,int *heap_ptr,void **aacd_instance,int sram_size, int getinfo,int streaming);
 * \brief decode initialize 
 * \param[in]  filelen file size
 * \param[out] srate sample rate
 * \param[out] ch channel no 
 * \param[out] bitrate bit rate
 * \param[out] total_time total time     
 * \param[out] header_type header type 
 * \param[out] max_frame max frame 
 * \param[out] fbrowser seek mode
 * \param[out] sbr_flag sbr present flag
 * \param[out] enable_sbr enable sbr mode
 * \param[in]  max_size max error size
 * \param[in]  aop_read read function pointer
 * \param[in]  aop_seek seek fucntion pointer
 * \param[out]  cb_instance instance pointer
 * \param[in]  sram_ptr sram address
 * \param[in]  heap_ptr heap address
 * \param[in]  aacd_instance instance pointer  
 * \param[in]  sram_size sram size  
 * \param[in]  getinfo  get information mode 
 * \param[in]  streaming 1 for streaming
 * \return 0 if the action is successful
 */
int Mstar_AACD_aop_init(unsigned int filelen, int *srate, int *ch,int *bitrate,int *total_time,
                        int *header_type,int max_frame,int fbrowser,int *sbr_flag, int enable_sbr,int max_size,
                        int (*aop_read)(void *,unsigned char *, int ,int *),void (*aop_seek)(void *,unsigned int),void *cb_instance,
                        int *sram_ptr,int *heap_ptr,void **aacd_instance, int sram_size, int getinfo, int streaming);
//-----------------------------------------------------------
//for new AO API
/**
 * \fn  void Mstar_MP4D_aop_get_sram_size(int *sram_size,int *heap_size,int enable_sbr)
 * \brief  get heap size
 * \param[out] sram_size sram size   
 * \param[out] heap_size heap size
 * \param[in] enable_sbr enable sbr mode  
 * \return none 
 */
void Mstar_MP4D_aop_get_sram_size(int *sram_size,int *heap_size,int enable_sbr);

/**
 * \fn int Mstar_MP4D_aop_init(unsigned int filelen, int *srate, int *ch, int *bitrate,int *total_time,
                        int *header_type,int max_frame,int fbrowser,int *sbr_flag, int enable_sbr,int max_size,
                        int (*aop_read)(void *,unsigned char *, int ,int *),void (*aop_seek)(void *,unsigned int),void *cb_instance,
                        int *sram_ptr,int *heap_ptr,void **aacd_instance,int sram_size, int getinfo, int streaming);
 * \brief decode initialize for MPA 
 * \param[in]  filelen file size
 * \param[out] srate sample rate
 * \param[out] ch channel no 
 * \param[out] bitrate bit rate
 * \param[out] total_time total time     
 * \param[out] header_type header type 
 * \param[out] max_frame max frame 
 * \param[out] fbrowser seek mode
 * \param[out] sbr_flag sbr present flag
 * \param[out] enable_sbr enable sbr mode
 * \param[in]  max_size max error size
 * \param[in]  aop_read read function pointer
 * \param[in]  aop_seek seek fucntion pointer
 * \param[out]  cb_instance instance pointer
 * \param[in]  sram_ptr sram address
 * \param[in]  heap_ptr heap address
 * \param[in]  aacd_instance instance pointer  
 * \param[in]  sram_size sram size
 * \param[in]  getinfo get information mode  
 * \param[in]  streaming 1 for streaming 
 * \return 0 if the action is successful
 */
int Mstar_MP4D_aop_init(unsigned int filelen, int *srate, int *ch, int *bitrate,int *total_time,
                        int *header_type,int max_frame,int fbrowser,int *sbr_flag, int enable_sbr,int max_size,
                        int (*aop_read)(void *,unsigned char *, int ,int *),void (*aop_seek)(void *,unsigned int),void *cb_instance,
                        int *sram_ptr,int *heap_ptr,void **aacd_instance,int sram_size, int getinfo, int streaming);
/**
 * \fn  int Mstar_MP4D_aop_seek(void *aacd_instance,int play_time,int fbrowser,int enable_sbr,int max_size);
 * \brief  seek fucntion
 * \param[in] aacd_instance instance pointer  
 * \param[in] play_time seek time 
 * \param[in] fbrowser seek mode
 * \param[in] enable_sbr enable sbr mode
 * \param[in] max_size max error size    
 * \return 0 if the action is successful
 */
int Mstar_MP4D_aop_seek(void *aacd_instance,int play_time,int fbrowser,int enable_sbr,int max_size);                        
                     
/**
 * \fn  int Mstar_MP4D_aop_decode(void *aacd_instance,int **pcm_buf,int *play_time,int *ch,int *frame_size,int *sbr_flag,int max_size,int *avg_bitrate,int *total_time);
 * \brief  decode input data for MPA
 * \param[in] aacd_instance instance pointer 
 * \param[in] pcm_buf output buffer pointer
 * \param[in] play_time current play time 
 * \param[in] ch channel no
 * \param[out] frame_size frame size
 * \param[out] sbr_flag sbr present flag
 * \param[in] max_size max error, size  
 * \param[out] avg_bitrate average bit rate  
 * \param[out] total_time duration time  
 * \return 0 if the action is successful
 */
int Mstar_MP4D_aop_decode(void *aacd_instance,int **pcm_buf,int *play_time,int *ch,int *frame_size,int *sbr_flag,int max_size,int *avg_bitrate,int *total_time);

//-----------------------------------------------------------
//for AV API
/**
 * \fn  void Mstar_AACD_get_sram_size(int *sram_size,int *heap_size,int enable_sbr);
 * \brief  get heap size
 * \param[out] sram_size sram size   
 * \param[out] heap_size heap size
 * \param[in] enable_sbr enable sbr mode  
 * \return none 
 */
void Mstar_AACD_get_sram_size(int *sram_size,int *heap_size,int enable_sbr);

/**
 * \fn int Mstar_AACD_avp_init(int samplerate,int sbr_present_flag,int downSampledSBR,int forceUpSampling, int header_type,int enable_sbr,
                        int (*avp_read)(void *,unsigned char *, int, int *, int *, int *),void *cb_instance,
                        int *sram_ptr,int *heap_ptr,void **aacd_instance, int sram_size, int getinfo);
 * \brief decode initialize for video 
 * \param[out] samplerate sample rate
 * \param[out] sbr_present_flag sbr_present_flag   
 * \param[out] downSampledSBR  down sample flag
 * \param[out] forceUpSampling force up sample flag
 * \param[out] header_type header type  
 * \param[out] enable_sbr enable sbr mode 
 * \param[in]  avp_read read function pointer
 * \param[out]  cb_instance instance pointer
 * \param[in]  sram_ptr sram address
 * \param[in]  heap_ptr heap address
 * \param[in]  aacd_instance instance pointer
 * \param[in]  sram_size sram size
 * \param[in]  getinfo getinfomaiton mode
 * \return 0 if the action is successful
 */
int Mstar_AACD_avp_init(int samplerate,int sbr_present_flag,int downSampledSBR,int forceUpSampling, int header_type,int enable_sbr,
                        int (*avp_read)(void *,unsigned char *, int, int *, int *, int *),void *cb_instance,
                        int *sram_ptr,int *heap_ptr,void **aacd_instance, int sram_size, int getinfo);

/**
 * \fn  void Mstar_AACD_avp_seek(void *aacd_instance,int play_time);
 * \brief  seek fucntion
 * \param[in] aacd_instance instance pointer   
 * \param[in] play_time seek time 
 * \return none
 */                        
void Mstar_AACD_avp_seek(void *aacd_instance,int play_time);

/**
 * \fn  int Mstar_AACD_avp_decode(void *aacd_instance,int **pcm_buf,int *ch,int *frame_size, int *play_time,int *sbr_flag,int max_size);
 * \brief  decode input data
 * \param[in] aacd_instance instance pointer 
 * \param[in] pcm_buf output buffer pointer
 * \param[in] ch channel no
 * \param[out] frame_size frame size  
 * \param[in] play_time current play time 
 * \param[in] sbr_flag sbr present flag
 * \param[in] max_size max error size   
 * \return 0 if the action is successful
 */
int Mstar_AACD_avp_decode(void *aacd_instance,int **pcm_buf,int *ch,int *frame_size, int *play_time,int *sbr_flag,int max_size);

/**
 * \fn  int Mstar_AACD_avp_config(unsigned char *buf,int size,int *sample_rate,int *ch_num,
                                int *sbr_present_flag,int *downSampledSBR,int *forceUpSampling, int *header_type,int enable_sbr)
 * \brief  config audio formate
 * \param[in] buf buffer pointer
 * \param[in] size buffer size  
 * \param[out] sample_rate sample rate
 * \param[out] ch_num channel no
 * \param[out] sbr_present_flag sbr present flag
 * \param[out] downSampledSBR down sample flag
 * \param[out] forceUpSampling forceupsampling flag
 * \param[in] header_type aac header type
 * \param[in] enable_sbr sbr present flag
 * \return none
 */
int Mstar_AACD_avp_config(unsigned char *buf,int size,int *sample_rate,int *ch_num,
                                int *sbr_present_flag,int *downSampledSBR,int *forceUpSampling, int *header_type,int enable_sbr);


//-----------------------------------------------------------
//for AO and AV
/**
 * \fn  void Mstar_AACD_eng_post_process(int mono_stereo,int stereo_reverse,int samples,int ch,int **pcm_buf,short *out_buf,int sbr_flag);
 * \brief  post processing
 * \param[in] mono_stereo stereo or mono
 * \param[in] stereo_reverse stereo reverse  
 * \param[in] samples sample no  
 * \param[in] ch channel no  
 * \param[in] pcm_buf input buffer pointer  
 * \param[in] out_buf output buffer pointer  
 * \param[in] sbr_flag enable sbr flag 
 * \return none
 */
void Mstar_AACD_eng_post_process(int mono_stereo,int stereo_reverse,int samples,int ch,int **pcm_buf,short *out_buf,int sbr_flag);

//-----------------------------------------------------------
//getinfo
/**
 * \fn int Mstar_MP4D_get_inform(unsigned int file_size, unsigned char *buf_mem, int buf_size,int *srate, int *ch, int *bitrate,int *bitrate_type,
                          int *total_time,int max_frame, int *header_type,int fbrowser,int enable_sbr,int max_size,
                          int (*info_read)(unsigned char *, int),void (*info_seek)(unsigned int) );
 * \brief decode initialize for MPA 
 * \param[in]  file_size file size
 * \param[in]  buf_mem buffer pointer
 * \param[in]  buf_size buffer size  
 * \param[out] srate sample rate
 * \param[out] ch channel no 
 * \param[out] bitrate bit rate
 * \param[out] bitrate_type bit rate type
 * \param[out] total_time total time     
 * \param[out] max_frame max frame
  * \param[out] header_type header type 
 * \param[out] fbrowser seek mode
 * \param[out] enable_sbr enable sbr mode
 * \param[in]  max_size max error size
 * \param[in]  info_read read function pointer
 * \param[in]  info_seek seek fucntion pointer 
 * \return 0 if the action is successful
 */
int Mstar_MP4D_get_inform(unsigned int file_size, unsigned char *buf_mem, int buf_size,int *srate, int *ch, int *bitrate,int *bitrate_type,
                          int *total_time,int max_frame, int *header_type,int fbrowser,int enable_sbr,int max_size,
                          int (*info_read)(unsigned char *, int),void (*info_seek)(unsigned int) );
/**
 * \fn  void Mstar_AACD_get_sram_size_getinfo(int *sram_size,int *heap_size); 
 * \brief  get aac information heap size
 * \param[in] sram_size sram size
 * \param[in] heap_size heap size
 * \return none
 */                          
void Mstar_AACD_get_sram_size_getinfo(int *sram_size,int *heap_size);                          
/**
 * \fn  void Mstar_MP4D_aop_get_sram_size_getinfo(int *sram_size,int *heap_size);
 * \brief  get m4a information heap size
 * \param[in] sram_size sram size
 * \param[in] heap_size heap size
 * \return none
 */        
void Mstar_MP4D_aop_get_sram_size_getinfo(int *sram_size,int *heap_size);

/** @}*/

#endif
