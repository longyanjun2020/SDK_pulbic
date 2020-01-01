
#ifndef _MMP_TSPARSER_H_
#define _MMP_TSPARSER_H_

#include "mmpf_typedef.h"
#include "mmp_err.h"
#include "MsTypes.h"
#include "mmpf_media_core.h"
#include "mmp_vidplay_inc.h"

//define
#define EN_DBG_TS_LOG              (0)
#define EN_TS_SPEED_UP_SEEK_JUMP   (1)
#define EN_TS_LINE_OFFSET_DMA      (1)
#define EN_TS_SPEED_UP_DMX         (1) //Enable this one; Need to enable line offset dma.

#define CUR_DEMUXED_TSVID_FRAME    gTSVideoMedia[m_ubVideoCurTrack].ulFrameIndex

// TS Header flag
#define PID_PAT            0x0000 //Program Association Table (PAT)
//#define PID_CAT            0x0001 //Conditional Access Table (CAT)
#define PID_TSDT           0x0002 //Transport Stream Description (TSDT)
//+++ Customizer:x3~xF:REV
#define PID_SIGMA          0x0008 //Customizer:x3~xF:REV
#define PID_THUMB          0x0009 //VR Thumbnail
#define PID_DUMMY          0x000F //TBD
//#define PID_SDT            0x0011 //Service Description Table (SDT)
//#define PID_EIT            0x0012
//#define PID_RST            0x0013
//#define PID_TDT            0x0014

#define TS_PKT_SYMB        0x47
#define TS_PAT_SYMB        0x00
#define TS_PMT_SYMB        0x02
#define TS_PKT_SIZE        188
#define PKT_HEAD_SZ        0x04
#define PES_DATA_SZ        163    //188-4-21=163
#define PES_PKT_NUM_MAX    356    //65535/184=356(x164)
#define ADTS_HEADER_SIZE   0x07   //7 or 9 bytes (without or with CRC)

#define PRIVATE_SYMB       0x5A

//#define TS_INDEX_BUFFER_SIZE          (256*1024)
//#define TS_MIN_INDEX_DURATION         (500) // 500 ms
#define TS_MAX_SEARCH_SAMPLE_COUNT    (500)

#define TS_MAX_TBL_ENTRY              (16)
#define TS_MAX_WIDTH                  (1920)
#define TS_MAX_HEIGHT                 (1088)
#define TS_MAX_FRM_RATE               (120)
#define TS_STD_FRM_RATE               (30)

#define TS_UNDEFINESAMPLENUM          (0x7fffffff)

#define ALOC_THUMB_SIZE               (64 * 1024) //Equal to MTS_VR_THUMBNAIL_SIZE
#define ALOC_THUMB_TOTAL_PKT          (ALOC_THUMB_SIZE/(TS_PKT_SIZE-PKT_HEAD_SZ)) //356
#define ALOC_THUMB_TOTAL_PKT_SIZE     (ALOC_THUMB_TOTAL_PKT*TS_PKT_SIZE)          //356*188=x1_0570(x1_062C)
#define ALOC_DMX_TBL_SIZE             (2048 * 0x10 * 10) //10min
#define ALOC_COLLECT_VID_SIZE         (2 * TS_MAX_WIDTH * TS_MAX_HEIGHT)
#define ALOC_COLLECT_AUD_SIZE         (2048)

//TS Parser:
#define TSPSR_SEARCH_PKT_RANGE        (4096) //Unit:Packet
#define TSPSR_SEARCH_TAIL_PKT_RANGE   (2048) //Unit:Packet
#define TSPSR_MAXIUM_REC_TIME         (10*60*1000) //Max:10 (Min)


#define STREAM_TYPE_NONE            0x00
#define STREAM_TYPE_VIDEO_MPEG1     0x01
#define STREAM_TYPE_VIDEO_MPEG2     0x02
#define STREAM_TYPE_AUDIO_MP3       0x03
#define STREAM_TYPE_AUDIO_MPEG2     0x04
#define STREAM_TYPE_PRIVATE_SECTION 0x05
#define STREAM_TYPE_PRIVATE_DATA    0x06
#define STREAM_TYPE_AUDIO_AAC       0x0f
#define STREAM_TYPE_AUDIO_AAC_LATM  0x11
#define STREAM_TYPE_VIDEO_MPEG4     0x10
#define STREAM_TYPE_VIDEO_H264      0x1b
#define STREAM_TYPE_VIDEO_VC1       0xea
#define STREAM_TYPE_VIDEO_DIRAC     0xd1
 
#define STREAM_TYPE_AUDIO_AC3       0x81
#define STREAM_TYPE_AUDIO_DTS       0x8a

/** @brief Private data of the TS parser
*/
typedef struct MMPF_TSPSR_PRIVATEDATA
{
    MMP_BOOL                bFilling;               ///< If the parser is filling a frame
    MMP_BOOL                bLargeFrame;            ///< If current frame is a large frame
    MMP_BOOL                bFillBufferDone;        ///< If the demuxer is finished and the parser status is not updated.
    MMPF_M_FRAME_INFO    	pPreWriteHeader;       	///< Previous write buffer header
    MMPF_M_FRAME_INFO    	curWriteHeader;         ///< Current write buffer header
    MMP_USHORT              usEOFPadding;           /**< The padding data after the end of a frame. It might includes ARM padding or
                                                         several 0 bytes for padding */
    MMP_USHORT              usBSOffset;             /**< The offset before the bitstream and the starting address of the header.
                                                         It might include LARGE-DMA SD card 8 byte alignment with 512 bytes offset
                                                         and the header itself.*/
    MMP_VID_AUDIOTYPE       sSupportedAudioFmt; 	///< The audio format supported in current firmware
    MMP_VID_VIDEOTYPE       sSupportedVideoFmt; 	///< The video format supported in current firmware
} MMPF_TSPSR_PRIVATEDATA;

typedef struct {
	MMP_USHORT usStrType; //[H264:AAC:MP3]/[x1B:x0F:x03]
	MMP_ULONG  ulPID;
} PIDSearch;

typedef struct {
	MMP_ULONG frame_period;
	MMP_ULONG bit_rate;
	MMP_ULONG width;
	MMP_ULONG height;
} TSHeader;

typedef struct{
	MMP_ULONG ulTrackID;
	MMP_ULONG ulPID;
	MMP_ULONG ulIdxOffset;   // table index file offset
	MMP_ULONG ulFrameIndex;  // number of current frame
	MMP_ULONG ulTotalFrame;
	MMP_ULONG ulScale;
	MMP_ULONG ulRate;
	MMP_ULONG ulSampleSize;
	MMP_ULONG ulStreamTime;  // Stream time (ms)
	MMP_ULONG ulSamplePos;
	MMP_ULONG ulCodecType;
	MMP_ULONG ulFileSize;
	//MMP_ULONG ulTotalEntry;
	//MMP_ULONG ulInitialIndex;
	//MMP_ULONG ulInitFrame;
	MMP_ULONG ulTotalLength;
	MMP_ULONG ulFrmTime;
	MMP_ULONG ulFrameSize;
	MMP_ULONG ul64PCR_1st;
	MMP_ULONG ul64PTS_1st;
	MMP_ULONG ul64DTS_1st;
	MMP_ULONG ul64PCR_last;
	MMP_ULONG ul64PTS_last;
	MMP_ULONG ul64DTS_last;
    MMP_ULONG ulCollectSize;
    MMP_ULONG ulCollectBufMax;
	MMP_ULONG ulDataEnd;
	// index table
	MMP_BOOL  bSeekEnable;
	MMP_BOOL  bPreciseSeek;
	MMP_ULONG ulFileTotalPkt;
} MMP_TS_MEDIA_INFO;

typedef struct {
	//4B TsHeader;               //01:4B[x04:x00]
	MMP_ULONG ul64VidTotalTime;  //02:8B[x0B:x04]
	MMP_ULONG ulAudTotalTime;    //03:4B[x0F:x0C]
	MMP_ULONG ulAacEncLastTime;  //04:4B[x13:x10]
	MMP_ULONG ulPesDefSkipMax;   //06:4B[x17:x14] 356
	MMP_ULONG ulDivTime90;       //05:4B[x1B:x18]
	MMP_ULONG ulResol;           //07:4B[x1F:x1C]
	MMP_ULONG ulIncr;            //08:4B[x23:x20]
	MMP_ULONG ulIncrx1000;       //09:4B[x27:x24]
} MMP_TS_SIGMA_INFO;

typedef enum _MMP_TS_STREAM_TYPE {
    TS_STREAM_VID,
    TS_STREAM_AUD,
    TS_STREAM_MAX
} MMP_TS_STREAM_TYPE;

typedef enum _MMPF_TSPSR_CACHE_INDEX {
    TS_INIT_CACHE,
    TS_VIDEO_CACHE,
    TS_AUDIO_CACHE
} MMPF_TSPSR_CACHE_INDEX;

typedef enum _MMP_TSPSR_PID {
    TS_PID_NIT,
    TS_PID_PMT,
    TS_PID_VID,
    TS_PID_AUD,
    TS_PID_TYP1,
    TS_PID_MAX
} MMP_TSPSR_PID;

typedef enum _MMP_TS_SAMPLE_STS {
    TS_SAMPLE_STS_NONE,
    TS_SAMPLE_STS_STEP1, //Get the 1st pkt from PES header
    TS_SAMPLE_STS_STEP2, //Get 2nd ~ last pkt from PES data
    TS_SAMPLE_STS_STEP3, //Read total data and contruct frame
    TS_SAMPLE_STS_MAX
} MMP_TS_SAMPLE_STS;

typedef enum _TS_PES_FMT {
    FMT_ONLY_PES = 0,
    FMT_PES_WITH_DATA,
    FMT_PES_MAX
} TS_PES_FMT;

typedef enum _VIDDEC_FRAME_TYPE {
    VIDDEC_I_FRAME = 0x10,
    VIDDEC_P_FRAME = 0x30,
    VIDDEC_B_FRAME = 0x50,
    VIDDEC_FRAME_TYPE_NUM = 0x78
} VIDDEC_FRAME_TYPE;

typedef enum _MMPF_TSPSR_DBG {
    DBG_TS_DISABLE    = 0x0000,
    DBG_TS_HEADER     = 0x0001,
    DBG_TS_PAT        = 0x0002,
    DBG_TS_PMT        = 0x0004,
    DBG_TS_ADP        = 0x0008,
    DBG_TS_PES        = 0x0010,
    DBG_TS_VID_CODEC  = 0x0020,
    DBG_TS_AUD_CODEC  = 0x0040,
    DBG_TS_VID_DATA   = 0x0080,
    DBG_TS_AUD_DATA   = 0x0100,
    DBG_TS_REV_XXX1   = 0x0200,
    DBG_TS_REV_XXX2   = 0x0400,
    DBG_TS_REV_XXX3   = 0x0800,
    DBG_TS_PID_MAX
} MMPF_TSPSR_DBG;

typedef enum _TS_ADP_FIELD_CTRL {
    ADP_CTRL_NONE = 0,
    ADP_CTRL_PAYLOAD_ONLY,
    ADP_CTRL_ADP_FIELD_ONLY,
    ADP_CTRL_ADP_FIELD_WITH_PAYLOAD
} TS_ADP_FIELD_CTRL;

#if 0
// For background parser
typedef struct{
    // file related
    MMP_ULONG ulTrack;
    MMP_ULONG ulSampleSize;
    MMP_ULONG ulFrameNum;
    MMP_ULONG ulScale;
    MMP_ULONG ulRate;
    // index memory table related
    MMP_ULONG ulStoreTime;
    MMP_ULONG ulTableBuffer;
    MMP_ULONG ulTableWptr;
    MMP_ULONG ulLastIdxOffset;
} MMP_IDX_TSTRACK_INFO;

typedef struct{
    // file related
    MMP_ULONG ulFileSize;
    MMP_ULONG ulCurrentOffset;
    MMP_ULONG ulTableEnd;
    MMP_IDX_AVITRACK_INFO VideoTrack[2];
    MMP_IDX_AVITRACK_INFO AudioTrack;
    /*MMP_ULONG ulVideoTrack;
    MMP_ULONG ulAudioTrack;
    MMP_ULONG ulVideoSampleSize;
    MMP_ULONG ulAudioSampleSize;
    MMP_ULONG ulVideoFrameNum;
    MMP_ULONG ulAudioFrameNum;
    MMP_ULONG ulVideoScale;
    MMP_ULONG ulAudioScale;
    MMP_ULONG ulVideoRate;
    MMP_ULONG ulAudioRate;
    // index memory table related
    MMP_ULONG ulVideoStoreTime;
    MMP_ULONG ulAudioStoreTime;    
    MMP_ULONG ulVideoTableBuffer;
    MMP_ULONG ulAudioTableBuffer;
    MMP_ULONG ulVideoTableWptr;
    MMP_ULONG ulAudioTableWptr;*/
    //MMP_ULONG ulMaxEntry;
    //MMP_ULONG ulDuration;
    //MMP_ULONG ulKeyFrameNum;
} MMP_IDX_TSMEDIA_INFO;
// For background parser

typedef struct
{
    MMP_ULONG   format;             ///< video format, such as H263, MPEG4, H264...etc
    MMP_ULONG   bitrate;            ///< video bitrate, in Kbps
    MMP_USHORT  width;              ///< video width
    MMP_USHORT  height;             ///< video height
    MMP_USHORT  fps;                ///< Frame per second, 0 means unknown
    MMP_USHORT	cropping_left;      ///< the distance between the left boundary and video frame
	MMP_USHORT	cropping_right;     ///< the distance between the right boundary and video frame
	MMP_USHORT	cropping_top;       ///< the distance between the top boundary and video frame
	MMP_USHORT	cropping_bottom;    ///< the distance between the bottom boundary and video frame
	MMP_LONG    total_video_time;   ///< the duration of the whole video stream
	MMP_ULONG   total_keyframe_num; ///< total keyframe numbers
} MMP_TSVIDEO_INFO;

typedef struct
{
    MMP_ULONG   format;             ///< audio format, such as AMR, AAC, AACP...etc
    MMP_ULONG   bitrate;            ///< audio bitrate, in Kbps
    MMP_ULONG   sampling_rate;      ///< audio sampling-rate
    MMP_UBYTE   channel_nums;       ///< number of channels
	MMP_ULONG   block_align;
	MMP_ULONG   bits_per_coded_sample;
    MMP_ULONG   total_audio_time;   ///< the duration of the whole audio stream
} MMP_TSAUDIO_INFO;

typedef struct {
    MMP_VIDEO_INFO      video_info;         ///< The video information
    MMP_AUDIO_INFO      audio_info;         ///< The audio information
    MMP_ULONG64         audio_start_time;   ///< The audio start time, time origin for A/V sync if audio timestamps are availabled
    MMP_UBYTE           is_video_available; ///< Does video stream exist or not
    MMP_UBYTE           is_audio_available; ///< Does audio stream exist or not
    MMP_ULONG           file_size;          ///< The file size
    MMP_ULONG           total_file_time;    ///< The total file time in the container
    /*
    !TODO!!
    currently, there is always only one frame in the frame buffer. Therefore, max_frame_num/frame_read_idx/frame_write_idx
    are useless in the current implementation.
    *//*
    MMP_MEDIA_FRAME     **frame_buf;        ///< output frame buffer
    MMP_UBYTE           max_frame_num;      ///< maximun frames in the output buffer
    MMP_UBYTE           frame_read_idx;     ///< reading index for output frame
    MMP_UBYTE           frame_write_idx;    ///< writing index for output frame
    */
} MMP_VIDEO_TSCONTAINER_INFO;
#endif

typedef struct MMP_TS_SAMPLE_INFO
{
    MMP_ULONG ulOffset;    ///< The offset in the file of the sample
    MMP_ULONG ulSize;      ///< The size of the sample
    MMP_LONG lSampleTime; ///< The tick of the sample
    MMP_ULONG ulFlag;
}MMP_TS_SAMPLE_INFO;

typedef struct MMP_TS_PKT_TBL
{
    MMP_ULONG TimeMm;
    MMP_ULONG ulPktStartNo;
    MMP_ULONG ulPktEndNo;
    MMP_USHORT usPktTotalSize;
    MMP_UBYTE ubRev;
    MMP_UBYTE ubTblEntryIsValid;
}MMP_TS_PKT_TBL;

typedef enum _TsCodecType {
    TS_CODEC_UNKNOWN = -1,
    TS_CODEC_VIDEO,
    TS_CODEC_AUDIO,
    //TS_CODEC_DATA,
    //TS_CODEC_SUBTITLE,
    //TS_CODEC_ATTACHMENT,
    //TS_CODEC_NB,
    TS_CODEC_MAX
}TsCodecType;

struct found_packet
{
    struct found_packet *next_ptr; // linked list, pointer to address of next list
    int index;
    MMP_ULONG header_address;
    MMP_ULONG payload_address;
    MMP_UBYTE payload_start_indicator;
    MMP_ULONG PID;
    MMP_UBYTE continuity_counter;
};

typedef struct //SZ:4B
{
    union
    {
        struct
        {
            MMP_UBYTE  sync_byte;
            MMP_UBYTE  transport_error_indicator:1;
            MMP_UBYTE  payload_start_indicator:1;
            MMP_UBYTE  transport_priority:1;
            MMP_USHORT PID:13;
            MMP_UBYTE  transport_scrambling_control:2;
            MMP_UBYTE  adaption_field_control:2;
            MMP_UBYTE  continuity_counter:4;
        } tB00;
        MMP_ULONG nB00;
    } uB00_03;
}TS_header;

typedef struct //SZ:8B+Cycle
{
    union
    {
        struct
        {
            MMP_UBYTE  dummy0;                     //B[x04]      SZ[08b] fix:x00
            MMP_UBYTE  table_id;                   //B[x05]      SZ[08b] fix:x00
            MMP_UBYTE  section_syntax_indicator:1; //B[x06]      SZ[01b] fix:1b
            MMP_UBYTE  zero:1;                     //            SZ[01b] fix:0b
            MMP_UBYTE  rev0:2;                     //            SZ[02b] fix:11b
            MMP_USHORT section_length:12;          //B[x07]      SZ[12b]
        } tB04;
        MMP_ULONG nB04;
    } uB04_07;
    
    union
    {
        struct
        {
            MMP_USHORT transport_stream_id;        //B[x09:x08]  SZ[16b] fix:x0001
            MMP_UBYTE  rev1:2;                     //B[x0A]      SZ[02b] fix:11b
            MMP_UBYTE  version_number:5;           //            SZ[05b] fix:00000b
            MMP_UBYTE  current_next_indicator:1;   //            SZ[01b] fix:1b
            MMP_UBYTE section_number;              //B[x0B]      SZ[08b] fix:x00
        } tB08;
        MMP_ULONG nB08;
    }uB08_0B;

    MMP_UBYTE last_section_number;                 //SZ[08b] fix:x00
    union
    {
        //Cycle St
        struct
        {
            MMP_USHORT program_number;             //SZ[16b] NIT:x0000 PMT:x0001
            //[program_number]
            //When set to 0x0000, then the following PID reference shall be the network PID.
            //For all other cases the value of this field is user defined.
            MMP_UBYTE  rev2:3;                     //SZ[03b] fix:111b
            MMP_USHORT program_map_PID:13;         //SZ[13b]
        } tB0D;
        MMP_ULONG nB0D;
        //Cycle Ed
    }uB0D_0X;
    
    MMP_ULONG CRC32;                              //SZ[32b]
}PAT_inf;
    
typedef struct //SZ:12B+Cycle
{
    union
    {
        struct
        {
            MMP_UBYTE  dummy0;                     //B[x04]      SZ[08b] fix:x00
            MMP_UBYTE  table_id;                   //B[x05]      SZ[08b] fix:x02
            MMP_UBYTE  section_syntax_indicator:1; //B[x06]      SZ[01b] fix:1b
            MMP_UBYTE  zero:1;                     //            SZ[01b] fix:0b
            MMP_UBYTE  rev0:2;                     //            SZ[02b] fix:11b
            MMP_USHORT section_length:12;          //B[x07]      SZ[12b]
        } tB04;
        MMP_ULONG nB04;
    }uB04_07;

    union
    {
        struct
        {
            MMP_USHORT program_number;             //B[x09:x08]  SZ[16b] fix:x0001
            MMP_UBYTE  rev1:2;                     //B[x0A]      SZ[02b]
            MMP_UBYTE  version_number:5;           //            SZ[05b]
            MMP_UBYTE  current_next_indicator:1;   //            SZ[01b]
            MMP_UBYTE  section_number;             //B[x0B]      SZ[08b] fix:x00
        } tB08;
        MMP_ULONG nB08;
    }uB08_0B;

    MMP_UBYTE  last_section_number;                //B[x0C]      SZ[08b] fix:x00
    union
    {
        struct
        {
            MMP_UBYTE  rev2:3;                     //B[x0D]      SZ[03b] fix:111b
            MMP_USHORT PCR_PID:13;                 //B[x0E]      SZ[13b]
            MMP_UBYTE  rev3:4;                     //            SZ[04b]
            MMP_USHORT program_info_length:12;     //B[x0F]      SZ[12b] if=xC;(x10+x0C+1)=0x1D
        } tB0D;
        MMP_ULONG nB0D;
    }uB0D_10;
    
    //Cycle St
    MMP_UBYTE  stream_type;                        //SZ[08b] H264:x1B AAC:x0f MP3:x03
    //[stream_type]
    //This is an 8-bit field specifying the type of program element carried within the packets with the PID
    //whose value is specified by the elementary_PID. The values of stream_type are specified in Table 2-29.
    union
    {
        struct
        {
            MMP_UBYTE  rev4:3;                     //SZ[03b] fix:x111b
            MMP_USHORT elementary_PID:13;          //SZ[13b]
            //[elementary_PID]
            //This is a 13-bit field specifying the PID of the Transport Stream packets 
            //which carry the associated program element.
            
            MMP_UBYTE  rev5:4;                     //SZ[04b] fix:x1111b
            MMP_USHORT ES_info_length:12;          //SZ[12b] if=x6;(x21+x06+1)=0x28
        } tB12;
        MMP_ULONG nB12;
    }uB12_X;
    //Cycle Ed
    
    MMP_ULONG CRC32;                              //SZ[32b]
} PMT_inf;

typedef struct //SZ:8B
{
    MMP_UBYTE   adaptation_field_length;            //B[x04]      SZ[1B]
    union
    {
        struct //SZ:1B
        {
            MMP_UBYTE discontinuity_indicator:1;
            MMP_UBYTE random_access_indicator:1;
            MMP_UBYTE es_priority_indicator:1;
            MMP_UBYTE PCRFlag:1;
            MMP_UBYTE OPCRFlag:1;
            MMP_UBYTE splicing_point_flag:1;
            MMP_UBYTE trasport_private_data_flag:1;
            MMP_UBYTE adaptation_field_ext_flag:1;
        } tFlag;
        MMP_UBYTE nFlag;                            //B[x05]      SZ[1B]
    }uFlag;
    MMP_UBYTE  splice_countdown;                    //B[x06]      SZ[1B]
    MMP_UBYTE  transport_private_dat_length;        //B[x06]      SZ[1B]
    MMP_ULONG  u64PCR;                              //B[x0A:x06]  SZ[5B]
} ADP_inf;

typedef struct //SZ:3B
{
    union
    {
        struct
        {
            MMP_UBYTE ConstTen:2;
            MMP_UBYTE PesScramblingControl:2;
            MMP_UBYTE PesPriority:1;
            MMP_UBYTE DataAlignmentIndicator:1;
            MMP_UBYTE Copyrigh:1;
            MMP_UBYTE OriginalOrCopy:1;
        } tPtsFlag;
        MMP_UBYTE nPtsFlag;
    }uPtsFlag;

    union
    {
        struct
        {
            MMP_UBYTE PtsDtsFlags:2;
            MMP_UBYTE EscrFlag:1;
            MMP_UBYTE EsRateFlag:1;
            MMP_UBYTE DsmTrickModeFlag:1;
            MMP_UBYTE AdditionalCopyInfoFlag:1;
            MMP_UBYTE PesCRCFlag:1;
            MMP_UBYTE PesExtensionFlag:1;
        } tDtsFlag;
        MMP_UBYTE nDtsFlag;
    }uDtsFlag;
    
    MMP_UBYTE pes_data_length;
} PES_Opt_Header;

typedef struct //SZ:19B
{
    MMP_ULONG   pes_start_code;                     //B[x06:x04]  SZ[3B] fix 0x00_0001
    MMP_UBYTE   stream_id;                          //B[x07]      SZ[1B] [AUD:VID]/[xC0:xE0] or 0xBD->ID3?
    MMP_USHORT  pes_packet_length;                  //B[x09:x08]  SZ[2B] 0:No limitation
    MMP_UBYTE   PTS_flag;                           //B[x0A]      SZ[1B] 0x80
    MMP_UBYTE   DTS_flag;                           //B[x0B]      SZ[1B] 0x80; 0xC0
    MMP_UBYTE   pes_data_length;                    //B[x0C]      SZ[1B] x05 or x0A
    MMP_ULONG   u64PTS;                             //B[x11:x0D]  SZ[5B] 33bit
    MMP_ULONG   u64DTS;                             //B[x16:x12]  SZ[5B] 33bit
} PES_inf;

typedef enum _ADTS_PROFILE {
    ADTS_PROFILE_MAIN = 0,
    ADTS_PROFILE_LC,
    ADTS_PROFILE_SSR,
    ADTS_PROFILE_REV,
    ADTS_PROFILE_NON_SUPPORT
} ADTS_PROFILE;

typedef enum _ADTS_SAMPLING_RATE {
    ADTS_RATE_96000 = 0,  //00
    ADTS_RATE_88200,      //01
    ADTS_RATE_64000,      //02
    ADTS_RATE_48000,      //03
    ADTS_RATE_44100,      //04
    ADTS_RATE_32000,      //05
    ADTS_RATE_24000,      //06
    ADTS_RATE_22050,      //07
    ADTS_RATE_16000,      //08
    ADTS_RATE_12000,      //09
    ADTS_RATE_11025,      //10
    ADTS_RATE_8000,       //11
    ADTS_RATE_7350,       //12
    ADTS_RATE_REV1,       //13
    ADTS_RATE_REV2,       //14
    ADTS_RATE_NON_SUPPORT //15
} ADTS_SAMPLING_RATE;

typedef enum _ADTS_CHANNEL {
    ADTS_AOT = 0,
    ADTS_CH_01,
    ADTS_CH_02,
    ADTS_CH_03,
    ADTS_CH_04,
    ADTS_CH_05,
    ADTS_CH_06,
    ADTS_CH_08,
    ADTS_CH_NON_SUPPORT
} ADTS_CHANNEL;

typedef struct //SZ:8B
{
    union
    {
        struct //SZ: 28b
        {
            MMP_USHORT  sync_word:12;                       //x0F_FF
            MMP_UBYTE   ID:1;                               //0:for MPEG-4 1:for MPEG-2
            MMP_UBYTE   layer:2;                            //always x00
            MMP_UBYTE   protection_absent:1;                //0:CRC error detection data IS present
                                                            //1:CRC error detection data IS NOT present
            MMP_UBYTE   profile:2;                          //00:Main 01:LC 02:SSR 03:REV
            MMP_UBYTE   sampling_frequency_idx:4;
            MMP_UBYTE   private_bit:1;                      //set to 0 when encoding, ignore when decoding
            MMP_UBYTE   channel:3;
            MMP_UBYTE   original_copy:1;                    //[0:1]/[not copyright:copyright]
            MMP_UBYTE   home:1;                             //[0:1]/[this is a copy:this is an original]
            MMP_UBYTE   rev:4;
        } tFixHd;
        MMP_ULONG nFixHd;
    }uFixHd;
    
    union
    {
        struct //28b
        {
            MMP_UBYTE   copyright_ident_bit:1;              //0: copyright identification is transferred one bit per frame
                                                            //1:
            MMP_UBYTE   copyright_ident_start:1;            //0: continuation of previous copyright identification, or no copyright
                                                            //1: start of copyright identification
            MMP_USHORT  acc_frame_length:13;                //(ADTS_HEADER_SIZE + size + pce_size);
            MMP_USHORT  adts_buffer_fullness:11;            //x7FF:variable bit stream
            MMP_UBYTE   num_of_raw_data_blocks_in_frame:2;  //00: 1 blocks;
                                                            //number of AAC frames (RDBs) in ADTS frame minus 1,
                                                            //for maximum compatibility always use 1 AAC frame per ADTS frame            
        } tVarHd;
        MMP_ULONG nVarHd;
    }uVarHd;
    
    union
    {
        MMP_USHORT nCRC;                                    //if protection_absent is 0
    }uCrcCheck;
} ADTSCtx;

MMP_ERR MMPF_TSPSR_Init(void);
MMP_ERR MMPF_TSPSR_Deinit(void);
MMP_ERR MMPF_TSPSR_Demux(void);
MMP_ERR MMPF_TSPSR_SeekByTime(const MMP_LONG ulTime, MMP_ULONG ulSeekOption);
void TS_header_decode(MMP_ULONG ulOffset);
void add_found_packet(void);
void find_TS_sync_byte(void);
void display_pid_table(void);
void display_transport_header(void);
void adaption_field(void);

#endif // _MMP_TSPARSER_H_

