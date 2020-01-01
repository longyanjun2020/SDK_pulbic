
#ifndef __AUD_MIXER_H__
#define __AUD_MIXER_H__

typedef struct _swmixer_s_
{    
    int scale1;
    int scale2;
}  swmixer_s;


extern int mstar_initmixer(
    void*   mixer_handler,    /* allocated memory for echo-cnaceller use */
    int    scale1,      /*  input pcm data1 scale factor  (1~9)*/
    int   scale2);    /*  input pcm data2 scale factor  (1~9)*/


extern int mstar_mixer_proc(
    void* mixer_handler,  /* mixer handle */
    short*  outpcm,     /* output pcm data */
    short*  inpcm1,     /* input pcm data1 */
    short*  inpcm2,     /* input pcm data2 */
    int    length);     /* sample size */

#endif // __AUD_MIXER_H__

