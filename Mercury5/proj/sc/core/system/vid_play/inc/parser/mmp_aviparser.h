
//define
#define DEBUG (0)
#define MKTAG(a,b,c,d) (a | (b << 8) | (c << 16) | (d << 24))
#define MKBETAG(a,b,c,d) (d | (c << 8) | (b << 16) | (a << 24))
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))

#define CUR_DEMUXED_AVIVID_FRAME    gAVIVideoMedia[m_ubVideoCurTrack].ulFrameIndex

#define ATOM_RIFF_BE     MKBETAG('R','I','F','F')
#define ATOM_LIST_BE     MKBETAG('L','I','S','T')
#define ATOM_MOVI_BE     MKBETAG('m','o','v','i')

#define ATOM_RIFF        MKTAG('R','I','F','F')
#define ATOM_LIST        MKTAG('L','I','S','T')
#define ATOM_DMLH        MKTAG('d','m','l','h')
#define ATOM_AMVH        MKTAG('a','m','v','h')
#define ATOM_HDRL        MKTAG('h','d','r','l')
#define ATOM_AVIH        MKTAG('a','v','i','h')
#define ATOM_PADS        MKTAG('p','a','d','s')
#define ATOM_STRL        MKTAG('s','t','r','l')
#define ATOM_STRH        MKTAG('s','t','r','h')
#define ATOM_VIDS        MKTAG('v','i','d','s')
#define ATOM_AUDS        MKTAG('a','u','d','s')
#define ATOM_TXTS        MKTAG('t','x','t','s')
#define ATOM_DATS        MKTAG('d','a','t','s')
#define ATOM_STRF        MKTAG('s','t','r','f')
#define ATOM_MOVI        MKTAG('m','o','v','i')
#define ATOM_INDX        MKTAG('i','n','d','x')
#define ATOM_IDX1        MKTAG('i','d','x','1')


typedef struct {
	unsigned int ulRiffEnd;
	unsigned int ulMoviEnd;
	unsigned int ulMoviList;
	int          ulHaveIndex;
} AVIContext;

typedef struct {
	unsigned int frame_period;
	unsigned int bit_rate;
	unsigned int width;
	unsigned int height;
} AVIHeader;

typedef struct{
    MMP_ULONG64 ullOffset;
    MMP_ULONG   ulSize;
    MMP_ULONG   ulDuration;
} MMP_AVI_SPIDX_INFO;

typedef struct{
	MMP_ULONG ulTrackID;
	MMP_ULONG ulIdxOffset;   // table index file offset
	MMP_ULONG ulFrameIndex; // number of current frame
	MMP_ULONG ulTotalFrame;
	MMP_ULONG ulScale;
	MMP_ULONG ulRate;
	MMP_ULONG ulSampleSize;
	MMP_ULONG ulStreamTime;  // Stream time (ms)
	MMP_ULONG ulIndexMoviOffset;
	MMP_ULONG ulMoviOffset;
	MMP_ULONG ulSamplePos;
	MMP_ULONG ulCodecType;
	MMP_ULONG ulFileSize;
	MMP_ULONG ulIdx1start;  //add for AVI1.0(MJPG)
	MMP_ULONG ulMoviEnd;
	MMP_ULONG ulTotalEntry;
	MMP_ULONG ulInitialIndex;
	MMP_ULONG ulInitFrame;
	MMP_ULONG ulDataEnd;
    
    // AVI2.0 used
    MMP_AVI_SPIDX_INFO SpIdxEntry; 
    MMP_ULONG64 ullBaseOffset;
    MMP_ULONG ulSpIdxOffset;
    MMP_ULONG ulReadCount;   // index table read byte count
    MMP_ULONG ulSpIdxNum;
    MMP_ULONG ulSpIdxCount;
    MMP_ULONG ulStdIdxNum;
    MMP_ULONG ulStdIdxCount; 
    
    MMP_BYTE  bIsSuperIdx;
	// index table
	MMP_BOOL  bSeekEnable;
	MMP_BOOL  bPreciseSeek;
	//MMP_ULONG ulChunkOffset;
	//MMP_ULONG ulChunkLength;
} MMP_AVI_MEDIA_INFO;

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
} MMP_IDX_AVITRACK_INFO;

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
    MMP_ULONG ulMaxEntry;
    MMP_ULONG ulDuration;
    MMP_ULONG ulKeyFrameNum;
} MMP_IDX_AVIMEDIA_INFO;
// For background parser

#if 0
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
} MMP_AVIVIDEO_INFO;

typedef struct
{
    MMP_ULONG   format;             ///< audio format, such as AMR, AAC, AACP...etc
    MMP_ULONG   bitrate;            ///< audio bitrate, in Kbps
    MMP_ULONG   sampling_rate;      ///< audio sampling-rate
    MMP_UBYTE   channel_nums;       ///< number of channels
	MMP_ULONG   block_align;
	MMP_ULONG   bits_per_coded_sample;
    MMP_ULONG   total_audio_time;   ///< the duration of the whole audio stream
} MMP_AVIAUDIO_INFO;

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
} MMP_VIDEO_AVICONTAINER_INFO;
#endif

typedef struct MMP_AVI_SAMPLE_INFO
{
    MMP_ULONG ulOffset;    ///< The offset in the file of the sample
    MMP_ULONG ulSize;      ///< The size of the sample
    MMP_LONG lSampleTime; ///< The tick of the sample
    MMP_ULONG ulFlag;
}MMP_AVI_SAMPLE_INFO;

typedef struct AVCodecTag {
    int id;
    unsigned int tag;
} AVCodecTag;

enum CodecType {
    CODEC_TYPE_UNKNOWN = -1,
    CODEC_TYPE_VIDEO,
    CODEC_TYPE_AUDIO,
    CODEC_TYPE_DATA,
    CODEC_TYPE_SUBTITLE,
    CODEC_TYPE_ATTACHMENT,
    CODEC_TYPE_NB
};
#if 0
typedef enum MMP_AVI_VIDEOTYPE {
    MMP_AVI_VIDEO_NONE = 0,     ///< No video
    MMP_AVI_VIDEO_H263 = 0x1,   ///< H.263
    MMP_AVI_VIDEO_MP4V_SP = 0x2,///< MPEG4 Video Simple Profile
    MMP_AVI_VIDEO_MP4V = 0x2,   ///< MPEG4 Video Simple Profile. MP4V is regarded as simple profile when not specified.
    MMP_AVI_VIDEO_MP4V_ASP = 0x4,   ///< MPEG4 Video Advanced Simple Profile
    MMP_AVI_VIDEO_H264 = 0x8,       ///< H.264
    MMP_AVI_VIDEO_WMV = 0x20,
    MMP_AVI_VIDEO_DIVX = 0x40,
    MMP_AVI_VIDEO_UNSUPPORTED = 0x100, /**< Unsupported audio type goes here, including some audio type, which can be played
                                           alone only. e.g. RV */
    MMP_AVI_VIDEOTYPE_MAX
} MMP_AVI_VIDEOTYPE;

typedef enum MMP_AVI_AUDIOTYPE {
    MMP_AVI_AUDIO_NONE = 0,     ///< No audio
    MMP_AVI_AUDIO_AMR_NB = 0x1, ///< AMR-NB
    MMP_AVI_AUDIO_AMR = 0x1,    ///< If not specified, then AMR means AMR-NB
    MMP_AVI_AUDIO_AAC_LC = 0x2, ///< AAC-LC
    MMP_AVI_AUDIO_AAC = 0x2,    ///< If not specified, then AAC means AAC-LC
    MMP_AVI_AUDIO_AAC_PLUS = 0x4,    ///< AAC+
    MMP_AVI_AUDIO_MP3 = 0x8,         ///< MP3
    MMP_AVI_AUDIO_WMA = 0x10,        ///< Microsoft WMA
    MMP_AVI_AUDIO_AC3 = 0x20,        ///< AC3
    MMP_AVI_AUDIO_WAV = 0x40,
    MMP_AVI_AUDIO_RA  = 0x80,        
    MMP_AVI_AUDIO_UNSUPPORTED = 0x100,/**< Unsupported audio type goes here, including some audio type, which can be played
                                          alone only. e.g. AMR-WB */
    MMP_AVI_AUDIOTYPE_MAX
} MMP_AVI_AUDIOTYPE;
#endif
MMP_ERR MMPF_AVIPSR_SeekByTime(const MMP_LONG ulTime, MMP_ULONG ulSeekOption);
