/// @ait_only
/**
 @file mmpd_mp4vdec.h
 @brief Header File for the MPEG4 decoder Driver.
 @author Truman Yang
 @version 
    - 2.0 Seperate the playing file from parser
    - 1.1 [08-Jun-06] Updates the comments and change API to align with the System Software Architecture
*/

#ifndef _MMPD_MP4VDEC_H_
#define _MMPD_MP4VDEC_H_

#include "mmp_lib.h"
//#include "mmpd_display.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/** @addtogroup MMPD_3GPPLAY
 *  @{
 */

    /** There are too many parameters. Use this type to enumerate the types that are seldom used and
    not listed in another group. By this type, all parameters with long can simply use MMPS_VIDPLAY_GetParameter
    and MMPS_VIDPLAY_SetParameter to access. This can also reduce the MMPD layer interface.
    */
    typedef enum MMPD_VIDPLAY_PARAMETER {
        MMPD_VIDPLAY_PARAMETER_GROUP = 0xF000,///< The mask used to classify the parameter group
        MMPD_VIDPLAY_PARAMETER_PARSER_BASE = 0x0000,
        MMPD_VIDPLAY_PARAMETER_STORAGE_PATH, /**< The storage path. MMP_FALSE: memory mode, MMP_TRUE:card mode, 
                                                 2:host-parser memory mode*/
        MMPD_VIDPLAY_PARAMETER_SEEK_MODE,///< Current video player packback seek mode
        MMPD_VIDPLAY_PARAMETER_CACHE, ///< The addresses of cache buffers [1]FSCache [2]FS Cache size [3]Depack Buffer
        MMPD_VIDPLAY_PARAMETER_BITSTREAM, /**< The addresses of the bitstream [1]Video bitstream
                                              [2]Video bitstream size [3]Audio bitstream [4]Audio bitstrem size*/
        MMPD_VIDPLAY_PARAMETER_VIDEO_BITSTREAM,
        MMPD_VIDPLAY_PARAMETER_AUDIO_BITSTREAM,
        MMPD_VIDPLAY_PARAMETER_BITSTREAM_PTR, ///< The addresses of the video bitstream pointer
        MMPD_VIDPLAY_PARAMETER_AUDIO_BITSTREAM_PTR, ///< The addresses of the audio bitstream pointer
        MMPD_VIDPLAY_PARAMETER_MUTEX, ///< The mutex state.
        MMPD_VIDPLAY_PARAMETER_DECODE_DONE, ///< Return if it is decode done or not
        MMPD_VIDPLAY_PARAMETER_INT_THRESHOLD, /**< The data move interrupt threshold in bytes.
                                                   0 for triggering per frame.*/
        MMPD_VIDPLAY_PARAMETER_SEEK_DIR,
        MMPD_VIDPLAY_PARAMETER_VIDEO_FRAMENUM,

        MMPD_VIDPLAY_PARAMETER_DECODER_BASE = 0x2000,
        MMPD_VIDPLAY_PARAMETER_AUXILIARY, /**< The addresses of the video auxiliary buffers
                                              [1]VLD_MVPred [2]DataPartition [3]Pred_H [4]Pred_V*/
        MMPD_VIDPLAY_PARAMETER_DECODER_CONFIG, ///< The decoder config parameters
        
        
        MMPD_VIDPLAY_PARAMETER_POSTPROCESSOR_BASE = 0x3000,
        MMPD_VIDPLAY_PARAMETER_DEBLOCK,///< The deblock value, see @ref MMPD_3GPPLAY_DEBLOCK_TYPE for information

        MMPD_VIDPLAY_PARAMETER_RENDERER_BASE = 0x4000,
        MMPD_VIDPLAY_PARAMETER_FRAME, ///< The addresses of the video frame buffers [1]Y [2]Cb[3]Cr[4]CbCr Size in bytes
        MMPD_VIDPLAY_PARAMETER_VIDEO_BUFFER, /**< The properties of the video frame buffers
                                                 [1]Number of buffers used [2]Use external or not,
                                                 1 for external, 0 for internal.*/
        MMPD_VIDPLAY_PARAMETER_SCALER_BUFFER,
        
        MMPD_VIDPLAY_PARAMETER_FRAME_RESOLUTION,
        
        MMPD_VIDPLAY_PARAMETER_CTRL_FRAME_BUFFER, ///< Allocate video frame buffer for video decode ctrl
        
        MMPD_VIDPLAY_PARAMETER_TV, ///< 1 for on and 0 for off.

        MMPD_VIDPLAY_PARAMETER_CLOCK_BASE = 0x5000,
        MMPD_VIDPLAY_PARAMETER_CURRENT_TIME, ///< The current playing time in millisecond
        MMPD_VIDPLAY_PARAMETER_REFERENCE_CLOCK,///< Current reference clock
        MMPD_VIDPLAY_PARAMETER_SPEED,///< Current video player packback speed
        MMPD_VIDPLAY_PARAMETER_SEEK_BY_FRAME,
        MMPD_VIDPLAY_PARAMETER_SEEK_BY_TIME,

        MMPD_VIDPLAY_PARAMETER_INFO_BASE = 0x6000,
        MMPD_VIDPLAY_PARAMETER_FILE_SIZE, ///< The file size of current parsed file
        MMPD_VIDPLAY_PARAMETER_AUDIO_TOTAL_TIME, ///< The current audio totoal time in millisecond
        MMPD_VIDPLAY_PARAMETER_VIDEO_TOTAL_TIME, ///< The current video totoal time in millisecond
        MMPD_VIDPLAY_PARAMETER_AUDIO_BITRATE, ///< The current audio bit-rate
        MMPD_VIDPLAY_PARAMETER_VIDEO_BITRATE, ///< The current video bit-rate
        MMPD_VIDPLAY_PARAMETER_AUDIO_FORMAT, ///< The current audio format
        MMPD_VIDPLAY_PARAMETER_VIDEO_FORMAT, ///< The current video format
        MMPD_VIDPLAY_PARAMETER_SUPPORTED_AUDIO,///< The supported audio type by the firmware
        MMPD_VIDPLAY_PARAMETER_FPS, ///< Frame per second in the 3GP file
        MMPD_VIDPLAY_PARAMETER_AUDIO_CHANNEL, ///< Number of Audio Channel
        MMPD_VIDPLAY_PARAMETER_AUDIO_SAMPLING_RATE, ///< Audio sampling rate
        MMPD_VIDPLAY_PARAMETER_AUDIO_LENGTH, ///< Audio length in bytes, write only
        MMPD_VIDPLAY_PARAMETER_AUDIO_TIME_BASE, ///< Audio time base
        MMPD_VIDPLAY_PARAMETER_VIDEO_WIDTH, ///< Video width
        MMPD_VIDPLAY_PARAMETER_VIDEO_HEIGHT,///< Video height
        MMPD_VIDPLAY_PARAMETER_OSD_ADDRESS, ///< OSD Starting Address. It's an 8-bytes alignment address.
        MMPD_VIDPLAY_PARAMETER_PLAYER_STATE, ///< Player state.
        MMPD_VIDPLAY_PARAMETER_VIDEO_AVAILABLE, ///< video available or not.
        MMPD_VIDPLAY_PARAMETER_AUDIO_AVAILABLE, ///< video available or not.
        MMPD_VIDPLAY_PARAMETER_DEBUG, ///< Debug information.
        MMPD_VIDPLAY_PARAMETER_AUDIO_OBJINDEX, ///< for aacplus, mp4ASC object index value 
        MMPD_VIDPLAY_PARAMETER_SBCTIME, ///< Set SBC Time
        MMPD_VIDPLAY_PARAMETER_DECODE_AUDIO,
        MMPD_VIDPLAY_PARAMETER_CURRENTTRACK,
        MMPD_VIDPLAY_PARAMETER_MAX
    } MMPD_VIDPLAY_PARAMETER;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
/** @brief The config required in MP4V and H.263 decoder

Used in host-parsed memory mode
*/
typedef struct MMPF_M_MP4V_CONFIG{
	MMP_USHORT	usHMB; ///< The number of horizontal macro blocks
	MMP_USHORT	usVMB; ///< The number of vertical macro blocks
	MMP_USHORT  usHWConfig;///< The attribute of VLD, including H263/MPEG4 format. RVLC and data partition.
	MMP_USHORT  usTimeIncRes;///< The video time increament resolution
}MMPF_M_MP4V_CONFIG;

typedef void* AVC_DEC_HANDLE;

/**
 *  @brief this structure is used to indicate the decoder where the bitstream is,
 *         and then put the decoded picture in this struct
 */
typedef struct
{
    AVC_DEC_HANDLE  *h_dec;
	MMP_UBYTE       *bs_buf;        ///< bitstream buffer
	MMP_UBYTE	    *bitstream;		///< bitstream buffer pointer
	MMP_UBYTE	    *bmp;			///< decoded picture
    MMP_UBYTE       is_init_ready;
	MMP_LONG		bitstream_len;	///< current compressed frame's length
	MMP_LONG		bs_start_pos;
	MMP_LONG		buf_length;		///< the bistream buffer length
	MMP_LONG		width;			///< decoded picture width
	MMP_LONG		height;			///< decoded picture height
	MMP_USHORT	    cropping_left;	// ue(v)
	MMP_USHORT	    cropping_right;	// ue(v)
	MMP_USHORT	    cropping_top;	// ue(v)
	MMP_USHORT	    cropping_bottom;// ue(v)
	MMP_ULONG       is_nalu_to_rbsp_done;
	
    MMP_LONG        is_output_ready;
	//aspect ratio
	MMP_LONG    	is_aspect_ratio_present;
	MMP_LONG		sar_width;
	MMP_LONG		sar_height;
	//time info
	MMP_LONG		is_time_info_present;
	MMP_LONG		num_units_in_tick;
	MMP_LONG		time_scale;
	MMP_ULONG64     input_time;
	MMP_ULONG64     display_time;
	
	MMP_ULONG       current_mem_addr;
	MMP_ULONG       end_mem_addr;
	MMP_ULONG       state;
	MMP_UBYTE       log_en;
} AVC_DATA_BUF;

typedef void* MMP_HANDLE;

/// The functions used for verication
typedef struct MMPD_MP4VDEC_MV_CALLBACK {
    /** @brief Parse the MP4V video header

    This is mainly used when parsing the 3GP file.
    @param[in] pStartAddress The starting address of current frame
    @param[out] pWidth The video width. It maybe not a multiple of 16
    @param[out] pHeight The video height. It maybe not a multiple of 16
    @return The parsing status
    @retval MMP_M_ERR_STREAM_CORRUPT Could not find the header for a certain times.
    */
    MMP_ERR (*DecodeHeader)(MMP_UBYTE* pStartAddress, MMP_USHORT *pWidth, MMP_USHORT *pHeight);

    /** @brief Decode one video frame

    This function also maintain the vld buffer index
    Currently it's used in timer, precode, and FF
    @param[in] h The video codec instance
    @param[in] ulFrameAddr The buffer to be decoded, including VO header
    @return The error status of the function call
    */
    MMP_ERR (*DecodeData)(MMP_HANDLE *h, MMP_ULONG ulFrameAddr);

    /** @brief Post setting for HW video decoder.

    @pre The player should know the resolution of this video.
    @param[in] pConfig MPEG4 video configuration. Set NULL to use default internal config
    */
    MMP_ERR (*SetConfig)(const MMPF_M_MP4V_CONFIG *pConfig);
}MMPD_MP4VDEC_MV_CALLBACK;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
	
MMP_ERR MMPD_MP4VDEC_SetDeblockBuffers(const MMP_ULONG ulY, const MMP_ULONG ulU, const MMP_ULONG ulV,
                                     const MMP_USHORT usWidth, const MMP_USHORT usHeight);
            
MMP_ERR MMPD_MP4VDEC_SetAuxiliaryBuffers(const MMP_ULONG ulMVPred, const MMP_ULONG ulDataPartition, 
            const MMP_ULONG ulHPredict, const MMP_ULONG ulVPredict);
            
MMP_ERR MMPD_MP4VDEC_SetVideoOutBuffers(const MMP_ULONG ulY, const MMP_ULONG ulU, const MMP_ULONG ulV,
                                        const MMP_USHORT usWidth, const MMP_USHORT usHeight,
                                        const MMP_USHORT usBufferUsed);
                                        
MMP_ERR MMPD_MP4VDEC_Init(void);
MMP_ERR MMPD_MP4VDEC_SetBitstreamAddr(const MMP_ULONG ulVideoBSAddr, const MMP_ULONG ulVideoBSSize);

#endif // _INCLUDES_H_
/// @end_ait_only
