/*
   aac encoder interface functions
 */
#ifndef _aacenc_h_
#define _aacenc_h_

#include "mmpf_audio_typedef.h"

/* here we distinguish between stereo and the mono only encoder */
#ifdef MONO_ONLY
#define MAX_CHANNELS        1
#else
#define MAX_CHANNELS        2
#endif

#define AACENC_BLOCKSIZE    1024   /*! encoder only takes BLOCKSIZE samples at a time */
#define AACENC_TRANS_FAC    8      /*! encoder short long ratio */
#define AACENC_PCM_LEVEL    1.0    /*! encoder pcm 0db refernence */


/*-------------------------- defines --------------------------------------*/


/*-------------------- structure definitions ------------------------------*/
struct AAC_ENCODER;

typedef  struct {
  Word32   sampleRate;            /* audio file sample rate */
  Word32   bitRate;               /* encoder bit rate in bits/sec */
  Word16   nChannelsIn;           /* number of channels on input (1,2) */
  Word16   nChannelsOut;          /* number of channels on output (1,2) */
  Word16   bandWidth;             /* targeted audio bandwidth in Hz */
} AACENC_CONFIG;


/*-----------------------------------------------------------------------------

functionname: AacInitDefaultConfig
description:  gives reasonable default configuration
returns:      ---

------------------------------------------------------------------------------*/
void AACEnc_AacInitDefaultConfig(AACENC_CONFIG *config);

/*---------------------------------------------------------------------------

functionname:AacEncOpen
description: allocate and initialize a new encoder instance
returns:     AACENC_OK if success

---------------------------------------------------------------------------*/

Word16  AACEnc_AacEncOpen (AACENC_CONFIG     *config);        /* pre-initialized config struct */


/*---------------------------------------------------------------------------

functionname:AACEnc_AacEncEncode
description: encode one frame
returns:     always 0

---------------------------------------------------------------------------*/
Word16 AACEnc_AacEncEncode(
                    Word16             *timeSignal,	   /*!< BLOCKSIZE*nChannels audio samples, interleaved */
                    const UWord8       *ancBytes,      /*!< pointer to ancillary data bytes */
                    Word16             *numAncBytes,   /*!< number of ancillary Data Bytes, send as fill element  */
                    UWord8             *outBytes,      /*!< pointer to output buffer            */
                    Word32             *numOutBytes    /*!< number of bytes in output buffer */
                    );


/*-----------------------------------------------------------------------------
//20080731 for audio all in one.

functionname: AACEnc_SetWorkingBuf
description:  Set AAC ENCODER working buffer.
returns:      sizeof working buffer.(in bytes)

------------------------------------------------------------------------------*/
int AACEnc_SetWorkingBuf(int *buf);


#endif /* _aacenc_h_ */
