
#ifndef _PUB_MP3_DECODER_LIBRARY_INCLUDE_FILE_
#define _PUB_MP3_DECODER_LIBRARY_INCLUDE_FILE_

/** \addtogroup MMAudioMP3DecMdlApi 
* @{ 
*/
 
#define MP3DEC_SRAM_26K               (26*1024)    // max sram size orig:24064
#define MP3DEC_SRAM_20K               (20*1024)
#define MP3DEC_SRAM_15K               (15*1024)
#define MP3DEC_SRAM_10K               (10*1024)
#define MP3DEC_SRAM_0K                (0)
/**
 * \fn int Mstar_mp3d_init(int AV_flag, int file_size,int *ch,int *srate,int *frame_size,int *bitrate,int *total_time,
                    int *mpeg2,int *layer,int *VBR_flag,int max_size,
                    int (*aop_read)(void *,unsigned char *, int, int *, int *),void (*aop_seek)(void *,unsigned int),void *cb_instance,
                    int *sram_addr,int *heap_addr,void **mp3d_instance,int sram_size, int getinf, int streaming);
 * \brief decode initialize
 * \param[in]  AV_flag 1 for video, 0 for audio
 * \param[in]  file_size file size
 * \param[out] ch channel no 
 * \param[out] srate sample rate
 * \param[out] frame_size frame size 
 * \param[out] bitrate bit rate
 * \param[out] total_time total time   
 * \param[out] mpeg2 mpeg2 present flag 
 * \param[out] layer layer no
 * \param[out] VBR_flag variabl bit present flag
 * \param[in]  max_size max error size
 * \param[in]  aop_read read function pointer
 * \param[in]  aop_seek seek fucntion pointer
 * \param[out]  cb_instance instance pointer
 * \param[in]  sram_addr sram address
 * \param[in]  heap_addr heap address
 * \param[in]  mp3d_instance instance pointer  
 * \param[in]  sram_size sram size  
 * \param[in]  getinf  1: do getinf only, 0, normal 
 * \param[in]  streaming 1 for streaming 
 * \return 0 if the action is successful
 */
int Mstar_mp3d_init(int AV_flag, int file_size,int *ch,int *srate,int *frame_size,int *bitrate,int *total_time,
                    int *mpeg2,int *layer,int *VBR_flag,int max_size,
                    int (*aop_read)(void *,unsigned char *, int, int *, int *),void (*aop_seek)(void *,unsigned int),void *cb_instance,
                    int *sram_addr,int *heap_addr,void **mp3d_instance,int sram_size, int getinf, int streaming);
/**
 * \fn  int Mstar_mp3d_seek(void *mp3d_instance,int AV_flag,int play_time, int max_size);

 * \brief  seek fucntion
 * \param[in] mp3d_instance instance pointer  
 * \param[in] AV_flag 1 for video, 0 for audio  
 * \param[in] play_time seek time  
 * \param[in] max_size max error size    
 * \return 0 if the action is successful
 */
int Mstar_mp3d_seek(void *mp3d_instance,int AV_flag,int play_time, int max_size);

/**
 * \fn  int Mstar_mp3d_decode(void *mp3d_instance,int **pcm_buf,int *play_time,int *ch, int max_size,int *avg_bitrate,int *total_time);
 * \brief  decode input data
 * \param[in] mp3d_instance instance pointer 
 * \param[in] pcm_buf output buffer pointer
 * \param[out] play_time current play time 
 * \param[out] ch channel no
 * \param[in] max_size max error, size  
 * \param[out] avg_bitrate average bit rate  
 * \param[out] total_time duration time  
 * \return 0 if the action is successful
 */
int Mstar_mp3d_decode(void *mp3d_instance,int **pcm_buf,int *play_time,int *ch, int max_size,int *avg_bitrate,int *total_time);

/**
 * \fn  void Mstar_mp3d_post_process(int mono_stereo,int stereo_reverse,int samples,int ch,int **pcm_buf,short *out_buf);
 * \brief  post processing
 * \param[in] mono_stereo stereo or mono
 * \param[in] stereo_reverse stereo reverse  
 * \param[in] samples sample no  
 * \param[in] ch channel no  
 * \param[in] pcm_buf input buffer pointer  
 * \param[in] out_buf output buffer pointer  
 * \return none
 */
void Mstar_mp3d_post_process(int mono_stereo,int stereo_reverse,int samples,int ch,int **pcm_buf,short *out_buf);

/**
 * \fn  void Mstar_mp3d_get_sram_size(int *sram_len,int *heap_len);
 * \brief  get heap size
 * \param[out] sram_len sram size   
 * \param[out] heap_len heap size
 * \return none 
 */
void Mstar_mp3d_get_sram_size(int *sram_len,int *heap_len);

/**
 * \fn  int Mstar_mp3d_getinfo(int AV_flag,unsigned char *buf,int buf_len,int file_size,int *ch,int *srate,int *bitrate,int *total_time,
                    int *mpeg2,int *layer, int max_size,
                    int (*info_read)(unsigned char *, int, int *, int *),void (*info_seek)(unsigned int));
 * \brief get meta
 * \param[in]  AV_flag 1 for video, 0 for audio
 * \param[in]  buf working buffer 
 * \param[in]  buf_len working buffer length
 * \param[in]  file_size file size
 * \param[out]  ch channel no 
 * \param[out]  srate sample rate
 * \param[out]  bitrate bit rate 
 * \param[out]  total_time total time
 * \param[out]  mpeg2 mpeg2 present flag
 * \param[out]  layer layer no
 * \param[in]  max_size max error size
 * \param[in]  info_read read function pointer
 * \param[in]  info_seek seek function pointer 
 * \return 0 if the action is successful
 */
int Mstar_mp3d_getinfo(int AV_flag,unsigned char *buf,int buf_len,int file_size,int *ch,int *srate,int *bitrate,int *total_time,
                    int *mpeg2,int *layer, int max_size,
                    int (*info_read)(unsigned char *, int, int *, int *),void (*info_seek)(unsigned int));


/** @}*/

#endif
