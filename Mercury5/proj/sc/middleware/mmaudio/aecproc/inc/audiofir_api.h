#ifndef _AUDIOFIR_API_H_
#define _AUDIOFIR_API_H_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***************************************************************************
 * Nested Include Files
 ***************************************************************************/
/***************************************************************************
 * Manifest Constants
 **************************************************************************/

#define AUDIO_FIR_LENGTH                32
#define AUDIO_FIR_STATE_SIZE_MONO       192
#define AUDIO_FIR_STATE_SIZE_STEREO    (AUDIO_FIR_STATE_SIZE_MONO+32*sizeof(short))

/***************************************************************************
 * Typed Constants
 **************************************************************************/

/***************************************************************************
 * Type Definitions
 **************************************************************************/
typedef struct audiofir_config_t_
{
    int        channel_mode;                       /* mono : 0, stereo : !=0 */
    short     coef_lin_1b15[AUDIO_FIR_LENGTH-1];
    short     gain_lin_12b4;
}audiofir_config_t;

/***************************************************************************
 *  Macros
 **************************************************************************/

/***************************************************************************
 *  Function Prototypes
 **************************************************************************/

extern void*  audiofir_initialise   (void* audiofir, int*   size, void* config);
extern int    audiofir_configure    (void* audiofir, void*  config);
extern void   audiofir_process      (void* audiofir, short* data);
extern int Audio_FIRProcessWhole(void*   hdle_p,short* pcmbuf, unsigned int u32FrameSz);

#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif/*_AUDIOFIR_API_H_*/
/* END OF FILE */
