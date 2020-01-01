////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MDL_AVP_DEMUXER_H
#define MDL_AVP_DEMUXER_H

/**
 * @file
 */

#include <stdint.h>

/**
 * @defgroup demux_plugin Demuxer Plug-in
 * @ingroup video
 * @brief Demuxer plug-in interface
 *
 * TODO: Detailed description goes here. Explain how to write a plug-in and
 * register to player.
 * @{
 */

/**
 * The maximum number of plug-in
 */
#define MDL_AVP_MAX_DMX_PLUGIN  1

/**
 * Define a number for each new format, the number must be greater than 1023.<br>
 * [NOTE] There is no guarantee that the number will not collide with other
 *        plug-in providers.
 */
#define MDL_AVP_FILE_BASE       (1023)
#define MDL_AVP_FILE_MKV        (MDL_AVP_FILE_BASE + 1)

/**
 * The return codes for demuxer plug-in functions and callbacks
 */
typedef enum MDLAVPDemuxError_e
{
    AvpDmxOK,                   ///< Operation succeeded.
    AvpDmxTryAgain,             ///< Use when parsing a frame failed. Player will
                                ///< retry for several times before fatal error.
    AvpDmxInvalidParam,         ///< Input parameter is invalid.
    AvpDmxNotEnoughMemory,      ///< Memory or resource allocation failed.
    AvpDmxOpenFailed,           ///< File is corrupted or not supported.
    AvpDmxSeekFailed,           ///< Failed to seek to target position.
    AvpDmxEndOfStream,          ///< End of stream reached.
} MDLAVPDemuxError_et;

/**
 * Stream types used by callback functions to specify the intended stream
 */
typedef enum MDLAvpStreamType_e
{
    AVP_STREAM_NONE,            ///< Unused.
    AVP_STREAM_PROG,            ///< Unused for now.
    AVP_STREAM_AUDIO,           ///< This is an audio stream.
    AVP_STREAM_VIDEO,           ///< This is a video stream.
    AVP_STREAM_SUBTITLE,        ///< Unused for now.
} MDLAvpStreamType_et;

struct MDLAvpInput_s;
struct MDLAvpOutput_s;

/**
 * Information to describe a video or audio stream
 */
typedef struct MDLAvpStreamInfo_s
{
    uint32_t    infoSize;       ///< Size of the structure, i.e., sizeof(MDLAvpStreamInfo_st)
    uint32_t    codecType;      ///< FourCC of the codec
    uint8_t    *configData;     ///< Pointer to decoder configuration data
    uint32_t    configLength;   ///< The length of the configuration data
} MDLAvpStreamInfo_st;

/**
 * The demuxer plug-in definition
 */
typedef struct MDLAvpDemuxer_s
{
    /**
     * Probe whether the input is the supported format.
     * @param[in] input The input stream. In general probe function should read
     *            as few bytes (for example, 16 bytes) as possible.
     * @return 1 when format matches, 0 otherwise.
     */
    int (* pfnProbe)(struct MDLAvpInput_s *input);

    /**
     * Create demuxer and parse container header. Demuxer should not parse
     * any frame data in this function. In other words, calling output
     * function in this function may result in unexpected behavior.
     * @param[out] ctx receives allocated demuxer
     * @param[in] input the input stream
     * @param[in] output the output allocator
     * @retval AvpDmxOK open file succeeded
     * @retval AvpDmxNotEnoughMemory memory allocation failed
     * @retval AvpDmxOpenFailed file not valid
     */
    int (* pfnOpenFile)(void **ctx, struct MDLAvpInput_s *input, struct MDLAvpOutput_s *output);

    /**
     * Close demuxer and free any allocated memory.
     * @param[in] ctx demuxer context
     * @retval AvpDmxOK
     */
    int (* pfnCloseFile)(void *ctx);

    /**
     * Get codec and duration information for the input stream.
     * TODO: list valid codec type.
     * @param[in] ctx demuxer context
     * @param[out] aType audio codec type specified as four CC.
     *                   Set to 0 if audio stream does not exist.
     * @param[out] vType video codec type specified as four CC.
     *                   Set to 0 if video stream does not exist.
     * @param[out] duration clip duration specified in us time unit.
     * @warning Do not set both audio and video type to 0.
     * @retval AvpDmxOK
     */
    int (* pfnGetInfo)(void *ctx, struct MDLAvpStreamInfo_s *audioConfig, struct MDLAvpStreamInfo_s *videoConfig, int64_t *duration);

    /**
     * Parse one sample and deliver the sample using output APIs.
     * @param[in] ctx demuxer context
     * @param[out] type stream type of the parsed sample
     * @param[out] pts presentation timestamp of the parsed sample.
     *             Time is specified in us (10^-6 s) unit.
     * @retval AvpDmxOK parse secceeded
     * @retval AvpDmxEndOfStream both audio and video stream ends
     * @retval AvpDmxTryAgain error encountered and demuxer can recover
     */
    int (* pfnParseData)(void *ctx, enum MDLAvpStreamType_e *type, int64_t *pts);

    /**
     * Seek to target time. If seek failed, restore to the state before seek,
     * so that playback can continue at the previous position. Demuxer should
     * output key audio/video frames after a successful seek operation.
     * @param[in] ctx demuxer context
     * @param[in,out] pts On input, pts specifies seek target time. On output,
     *                    pts receives the sought-to position on. In general
     *                    the output pts is the smaller of the first audio
     *                    and video key frame pts.
     * @retval AvpDmxOK seek succeeded
     * @retval AvpDmxEndOfStream seek beyond end of stream
     * @retval AvpDmxSeekFailed seek failed
     */
    int (* pfnSeekTime)(void *ctx, int64_t *pts);

    /**
     * For future extension, unused for now.
     */
    int (* pfnGetExtend)(void *ctx, int type, void *data);
} MDLAvpDemuxer_st;

/**
 * Register the plug-in demuxer with specified file format.
 * @param fileType a user defined file type ID to identify the demuxer format
 * @param demuxer the demuxer callback functions, the demuxer structure must
 *                remain valid after registration finished.
 * @retval AvpDmxOK registration succeeded
 * @retval AvpDmxInvalidParam this file type is already registered
 * @retval AvpDmxNotEnoughMemory the number of registered plug-ins exceeds the
 *                               maximun allowed number
 */
int MDLAvpRegisterDemuxer(int fileType, const struct MDLAvpDemuxer_s *demuxer);

/** @} */

/**
 * @defgroup plugin_input Input Functions
 * @ingroup demux_plugin
 */

/** @{ */
/**
 * Reads \p size bytes from \p input stream to \p buffer.
 * @param[in] input the input stream
 * @param[in] buffer destination buffer to write to
 * @param[in] size number of bytes to read from input stream
 * @return number of bytes read
 */
int32_t MDLAvpInputRead(struct MDLAvpInput_s *input, void *buffer, int32_t size);
/**
 * Sets input read position. The position is determined by \p offset and \p whence.
 * @param[in] input the input stream
 * @param[in] offset offset value to be added to the position specified by \p whence
 * @param[in] whence SEEK_SET, SEEK_CUR, or SEEK_END.
 * @return new poistion if success, -1 otherwise.
 * @warning When seek failed, the resulting position is undefined, and further
 *          read may still succeed instead of EOF. Demuxers expecting EOF after
 *          unsuccessful reads may end up fallen into infinite loops.
 */
int32_t MDLAvpInputSeek(struct MDLAvpInput_s *input, int32_t offset, int whence);
/**
 * Gets the current input stream position.
 * @param[in] input the input stream
 * @return current input stream position
 */
int32_t MDLAvpInputTell(struct MDLAvpInput_s *input);
/**
 * Close input stream
 * @param[in] input the input stream
 */
void MDLAvpInputClose(struct MDLAvpInput_s *input);
/** @} */

/**
 * @defgroup plugin_output Output Functions
 * @ingroup demux_plugin
 */

/** @{ */
/**
 * Allocate output buffer to write parsed sample to. For segmented sample,
 * demuxer can allocated buffer large enough to hold the current segment.
 * If later sample size grows, demuxer can realloc sample buffer. If the
 * output sample size is too large or the specified stream is disabled,
 * allocation may fail. In this case demuxer should skip the current sample
 * and parse the next one.
 * @param[in] output the output stream
 * @param[in] type the stream type of the current sample
 * @param[out] buffer address to a pointer to receive allocated buffer
 * @param[in] size the size of the sample to allocate
 * @retval AvpDmxOK allocation succeeded
 * @retval AvpDmxNotEnoughMemory allocation failed. Output buffer is set to
 *                               NULL in this case.
 */
int MDLAvpOutputAlloc(struct MDLAvpOutput_s *output, enum MDLAvpStreamType_e type, void **buffer, int size);

/**
 * Discard previously allocated sample buffer.
 * @param[in] output the output stream
 * @param[in] type the stream type of the current sample
 * @retval AvpDmxOK
 */
int MDLAvpOutputDiscard(struct MDLAvpOutput_s *output, enum MDLAvpStreamType_e type);

/**
 * Commit the allocated sample buffer. Audio samples must be delivered at frame
 * boundary. For video samples, there must be exactly one frame per sample.
 * @param[in] output the output stream
 * @param[in] type the stream type of the current sample
 * @param[in] size the size of the sample, the value must be smaller than the
 *                 last alloc or realloc call.
 * @param[in] pts the pts of this sample specified in us (10^-6 s) time unit
 * @retval AvpDmxOK
 */
int MDLAvpOutputCommit(struct MDLAvpOutput_s *output, enum MDLAvpStreamType_e type, int size, int64_t pts);

/**
 * Reallocate sample buffer, only required if a larger sample buffer is required.
 * The allocated buffer address may differ from the initial allocated address.
 * The realloc function will help move the previous written content to the new
 * address.
 * @param[in] output the output stream
 * @param[in] type the stream type of the current sample
 * @param[out] buffer address to a pointer to receive allocated buffer
 * @param[in] size the size of the sample to allocate
 * @retval AvpDmxOK allocation succeeded
 * @retval AvpDmxNotEnoughMemory allocation failed. Output buffer is set to
 *                               NULL in this case.
 */
int MDLAvpOutputRealloc(struct MDLAvpOutput_s *output, enum MDLAvpStreamType_e type, void **buffer, int size);

/**
 * Demuxer should call this function for each stream (audio and video) to
 * notify decoder end-of-stream. Since demuxer runs faster than current playback
 * position, it is possible that demuxer receives seek command after sending
 * EOS. Demuxer must handle seek command and continue demuxing in this case.
 * @param[in] output the output stream
 * @param[in] type the stream type which reaches EOS.
 * @retval AvpDmxOK
 */
int MDLAvpOutputEndStream(struct MDLAvpOutput_s *output, enum MDLAvpStreamType_e type);
/** @} */

#endif /* MDL_AVP_DEMUXER_H */
