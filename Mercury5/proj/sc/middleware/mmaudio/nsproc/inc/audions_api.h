
#define AUDIONS_FRAME_LENGTH    (160)
#define AUDIONS_REALFFT_SIZE    (128)
#define AUDIONS_LAPPING_STEP    (AUDIONS_REALFFT_SIZE/4)

typedef struct
{
    int gamma, kappa, scale;
}
audions_config_t;

extern void*
audions_initialise(
    void*           membuff,     /* allocated buffer for noise suppressor */
    int*            memsize,     /* in : available size, out : needed/used size */
    audions_config_t* config);     /* noise-suppressor configure */

extern int audions_suppress(
    void*   suppr, /* noise suppression handler */
    short*  iopcm); /* output pcm data */

extern void audions_set_config(
    void*               suppressor,/* noise suppression handler */
    audions_config_t*   config);    /* noise-suppressor configure */

