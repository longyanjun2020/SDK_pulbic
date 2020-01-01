#ifndef _ADPCMENC_API_H_
#define _ADPCMENC_API_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//#include "adpcmenc_common.h"

/**
 * Identifies the syntax and semantics of the bitstream.
 * The principle is roughly:
 * Two decoders with the same ID can decode the same streams.
 * Two encoders with the same ID can encode compatible streams.
 * There may be slight deviations from the principle due to implementation
 * details.
 *
 * If you add a codec ID to this list, add it so that
 * 1. no value of a existing codec ID changes (that would break ABI),
 * 2. it is as close as possible to similar codecs.
 */
enum CodecID
{
    CODEC_ID_NONE,					/* Microsoft Unknown Wave Format */
	CODEC_ID_ADPCM_MS = 0x0002,		/* Microsoft ADPCM Format */
	CODEC_ID_PCM_ALAW = 0x0006,		/* Microsoft ALAW */
	CODEC_ID_PCM_MULAW = 0x0007,	/* Microsoft MULAW */
	CODEC_ID_ADPCM_IMA_WAV = 0x0011,/* Intel's DVI ADPCM */

    /* various PCM "codecs" */
    CODEC_ID_PCM_S16LE= 0x10000,
    CODEC_ID_PCM_S16BE,
    CODEC_ID_PCM_U16LE,
    CODEC_ID_PCM_U16BE,
    CODEC_ID_PCM_S8,
    CODEC_ID_PCM_U8,
    //CODEC_ID_PCM_MULAW,
    //CODEC_ID_PCM_ALAW,
    CODEC_ID_PCM_S32LE,
    CODEC_ID_PCM_S32BE,
    CODEC_ID_PCM_U32LE,
    CODEC_ID_PCM_U32BE,
    CODEC_ID_PCM_S24LE,
    CODEC_ID_PCM_S24BE,
    CODEC_ID_PCM_U24LE,
    CODEC_ID_PCM_U24BE,
    CODEC_ID_PCM_S24DAUD,
    CODEC_ID_PCM_ZORK,
    CODEC_ID_PCM_S16LE_PLANAR,
    CODEC_ID_PCM_DVD,
    CODEC_ID_PCM_F32BE,
    CODEC_ID_PCM_F32LE,
    CODEC_ID_PCM_F64BE,
    CODEC_ID_PCM_F64LE,
    CODEC_ID_PCM_BLURAY,

    /* various ADPCM codecs */
    CODEC_ID_ADPCM_IMA_QT= 0x11000,
    //CODEC_ID_ADPCM_IMA_WAV,
    CODEC_ID_ADPCM_IMA_DK3,
    CODEC_ID_ADPCM_IMA_DK4,
    CODEC_ID_ADPCM_IMA_WS,
    CODEC_ID_ADPCM_IMA_SMJPEG,
    //CODEC_ID_ADPCM_MS,
    CODEC_ID_ADPCM_4XM,
    CODEC_ID_ADPCM_XA,
    CODEC_ID_ADPCM_ADX,
    CODEC_ID_ADPCM_EA,
    CODEC_ID_ADPCM_G726,
    CODEC_ID_ADPCM_CT,
    CODEC_ID_ADPCM_SWF,
    CODEC_ID_ADPCM_YAMAHA,
    CODEC_ID_ADPCM_SBPRO_4,
    CODEC_ID_ADPCM_SBPRO_3,
    CODEC_ID_ADPCM_SBPRO_2,
    CODEC_ID_ADPCM_THP,
    CODEC_ID_ADPCM_IMA_AMV,
    CODEC_ID_ADPCM_EA_R1,
    CODEC_ID_ADPCM_EA_R3,
    CODEC_ID_ADPCM_EA_R2,
    CODEC_ID_ADPCM_IMA_EA_SEAD,
    CODEC_ID_ADPCM_IMA_EA_EACS,
    CODEC_ID_ADPCM_EA_XAS,
    CODEC_ID_ADPCM_EA_MAXIS_XA,
    CODEC_ID_ADPCM_IMA_ISS
};

/**
 * all in native-endian format
 */
enum SampleFormat {
    SAMPLE_FMT_NONE = -1,
    SAMPLE_FMT_U8,              ///< unsigned 8 bits
    SAMPLE_FMT_S16,             ///< signed 16 bits
    SAMPLE_FMT_S32,             ///< signed 32 bits
    SAMPLE_FMT_FLT,             ///< float
    SAMPLE_FMT_DBL,             ///< double
    SAMPLE_FMT_NB               ///< Number of sample formats. DO NOT USE if dynamically linking to libavcodec
};

typedef struct ADPCMCodecContext{
    /**
     * some codecs need / can use extradata like Huffman tables.
     * mjpeg: Huffman tables
     * rv10: additional flags
     * mpeg4: global headers (they can be in the bitstream or here)
     * The allocated memory should be FF_INPUT_BUFFER_PADDING_SIZE bytes larger
     * than extradata_size to avoid prolems if it is read with the bitstream reader.
     * The bytewise contents of extradata must not depend on the architecture or CPU endianness.
     * - encoding: Set/allocated/freed by libavcodec.
     * - decoding: Set/allocated/freed by user.
     */
	unsigned char *extradata;
    int extradata_size;
    /**
     * the average bitrate
     * - encoding: Set by user; unused for constant quantizer encoding.
     * - decoding: Set by libavcodec. 0 or some bitrate if this info is available in the stream.
     */
    int bit_rate;


    /* audio only */
    int sample_rate; ///< samples per second
    int channels;    ///< number of audio channels

    /**
     * audio sample format
     * - encoding: Set by user.
     * - decoding: Set by libavcodec.
     */
    enum SampleFormat sample_fmt;  ///< sample format

    /* The following data should not be initialized. */
    /**
     * Samples per packet, initialized when calling 'init'.
     */
    int frame_size;
    int frame_number;   ///< audio or video frame number

    void *priv_data;

    enum CodecID id; /* see CODEC_ID_xxx */

    /**
     * fourcc (LSB first, so "ABCD" -> ('D'<<24) + ('C'<<16) + ('B'<<8) + 'A').
     * This is used to work around some encoder bugs.
     * A demuxer should set this to what is stored in the field used to identify the codec.
     * If there are multiple such fields in a container then the demuxer should choose the one
     * which maximizes the information about the used codec.
     * If the codec tag field in a container is larger then 32 bits then the demuxer should
     * remap the longer ID to 32 bits with a table or other structure. Alternatively a new
     * extra_codec_tag + size could be added but for this a clear advantage must be demonstrated
     * first.
     * - encoding: Set by user, if not then the default based on codec_id will be used.
     * - decoding: Set by user, will be converted to uppercase by libavcodec during init.
     */
    unsigned int codec_tag;

    /**
     * number of bytes per packet if constant and known or 0
     * Used by some WAV based audio codecs.
     */
    int block_align;
    int bits_per_coded_sample;
    /**
     * trellis RD quantization
     * - encoding: Set by user.
     * - decoding: unused
     */
    int trellis;
	int FileSize;
	unsigned int ChunkSize;
	unsigned int fact_size;
	unsigned int dwSampleLength;	//TotalSamplesByteSize;

} AVCodecContext;

typedef struct wave_info {
	unsigned int TotalTime;
	unsigned int TotalSamples;
} wave_info;


extern int AIT_ADPCMEnc_adpcm_encode_frame(AVCodecContext *avctx, unsigned char *frame, int buf_size, void *data, int FrameCount);
extern  int AIT_ADPCMEnc_adpcm_encode_init(AVCodecContext *avctx);

#endif	//_ADPCMENC_API_H