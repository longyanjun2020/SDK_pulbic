#ifndef _AUDEC_API_H_
#define _AUDEC_API_H_

#include <stdint.h>


//#define FAAD_DECODER //Andrew AAC
#define MSTAR_AAC_DECODER //Jacky AAC

#ifdef FAAD_DECODER
#ifdef __cplusplus
extern "C" {
#endif
#include "avp_structs.h"
#include "avp_decoder.h"
#include "avp_mp4.h"
#ifdef __cplusplus
}
#endif
#endif

#ifdef MSTAR_AAC_DECODER

#ifdef __cplusplus
extern "C" {
#endif

#include "avp_aacd_lib.h"

#ifdef __cplusplus
}
#endif

#endif

typedef struct _audio_decoder_s_ audio_decoder_t;
typedef struct _buf_element_s_ buf_element_t;

struct _buf_element_s_
{
    uint32_t buff_size;          /* read video compressed buff size */

    int64_t pts;                 /* pts time */

    uint32_t duration;           /* duration of video or audio buffer */

    uint32_t index;              /* read video frame index */

    uint32_t flag;               /* status flag for this buffer */

    uint8_t *buffer;             /* compressed buff */
};

struct _audio_decoder_s_
{
    uint32_t (*open)(audio_decoder_t *a_decoder,
                uint32_t *bits_per_sample,
                uint32_t *sample_rate,
                uint16_t *frame_length,
                uint8_t *channels,
                uint32_t mode);

    void (*decode_data) (audio_decoder_t *a_decoder,
                         buf_element_t *buf, uint32_t *u32remaining,
                         uint8_t **out_buf, uint32_t *out_size);

    /*
    * reset decoder after engine flush (prepare for new
    * audio data not related to recently decoded data)
    */
    void (*reset) (audio_decoder_t *a_decoder);

    /*
    * inform decoder that a time reference discontinuity has happened.
    * that is, it must forget any currently held pts value
    */
    void (*discontinuity) (audio_decoder_t *a_decoder);

    uint32_t (*close)(audio_decoder_t *a_decoder);


    /*get continuing audio frame num*/

    uint32_t (*getframe_counts)(audio_decoder_t *a_decoder,
                           buf_element_t *buf, uint32_t u32remaining,uint32_t *cuter);

    //mp4player *player;

    //U32 audio_sram_spare_start;
    //int audio_sram_spare_size;

    int frame_counts;

    unsigned char *m_decoderConfigDesc;
    unsigned int m_decoderConfigDesc_len;

#ifdef FAAD_DECODER
    NeAACDecHandle hDecoder;
    NeAACDecFrameInfo frameInfo;
    NeAACDecConfigurationPtr config;
#endif

};

#ifdef __cplusplus
extern "C" {
#endif

void init_audec(audio_decoder_t *a_decoder);
void audec_decode_data(audio_decoder_t *a_decoder, uint8_t *buf, int32_t frame_size);

#ifdef __cplusplus
}
#endif

#endif
