#ifndef _WMA_GETINFO_LIBRARY_INCLUDE_FILE_
#define _WMA_GETINFO_LIBRARY_INCLUDE_FILE_

#include <string.h>
#include "vm_types.ht"

/*lint --e{550} */

//typedef unsigned char    BYTE;
typedef unsigned short   WORD;
typedef unsigned int    DWORD;

typedef void * tHWMAFileState;
#define MIN_OBJECT_SIZE     24
#define DATA_OBJECT_SIZE    50
#define WMA_MAX_DATA_REQUESTED  128
#define WMA_MAX_METADATA_LEN    512     // Max length (in bytes) of any metadata field - note that metadata is WCHAR, so use even numbers
                                    // We will truncate incoming metadata to this length (and skip past the remaining data).
                                    // If you want to support max allowable size, set this to 65535 (0xFFFF).

#define MAX_BUFSIZE 128

/* Bool */
#ifndef _WMABool_DEFINED
#define _WMABool_DEFINED
typedef int tWMA_Bool;
#endif /* _WMABool_DEFINED */

/* 64-bit signed type  */
#ifndef _WMAI64_DEFINED
#define _WMAI64_DEFINED
#if !defined _MSC_VER || defined(__aeon__) 
typedef long long  tWMA_I64;
#else
typedef __int64    tWMA_I64;
#endif
#endif /* _WMAI64_DEFINED */

/* 64-bit unsigned type  */
#ifndef _WMAU64_DEFINED
#define _WMAU64_DEFINED
#if !defined _MSC_VER || defined(__aeon__) 
typedef unsigned long long  tWMA_U64;
#else
typedef unsigned __int64    tWMA_U64;
#endif
#endif /* _WMAU64_DEFINED */

#ifndef _QWORD_DEFINED
#define _QWORD_DEFINED
typedef struct tQWORD
{
    unsigned int   dwLo;
    unsigned int   dwHi;

}   QWORD;
#endif /* _QWORD_DEFINED */


/* versions */
#ifndef _WMAFILEVERSION_DEFINED
#define _WMAFILEVERSION_DEFINED
typedef enum tagWMAFileVersion
{
    cWMA_V1 = 1,
    cWMA_V2 = 2
} tWMAFileVersion;
#endif /* _WMAFILEVERSION_DEFINED */

/* channels */
#ifndef _WMAFILECHANNELS_DEFINED
#define _WMAFILECHANNELS_DEFINED
typedef enum tagWMAFileChannels
{
    cWMA_C_Mono = 1,
    cWMA_C_Stereo = 2

} tWMAFileChannels;
#endif /* _WMAFILECHANNELS_DEFINED */


#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct tGUID
{
    unsigned int   Data1;
    unsigned short  Data2;
    unsigned short  Data3;
    unsigned char   Data4[ 8 ];
}GUID;
#endif

/****************************************************************************/
#ifndef _WAVEFORMATEX_
#define _WAVEFORMATEX_
typedef struct tWAVEFORMATEX
{
    unsigned short    wFormatTag;         /* format type */
    unsigned short    nChannels;          /* number of channels (i.e. mono, stereo...) */
    unsigned int   nSamplesPerSec;     /* sample rate */
    unsigned int   nAvgBytesPerSec;    /* for buffer estimation */
    unsigned short    nBlockAlign;        /* block size of data */
    unsigned short    wBitsPerSample;     /* number of bits per sample of mono data */
    unsigned short    cbSize;             /* the count in bytes of the size of */

}   WAVEFORMATEX;
#endif // _WAVEFORMATEX_



#define WAVE_FORMAT_MSAUDIO1  0x0160
#define WAVE_FORMAT_WMAUDIO2  0x0161

#if !defined (WAVE_FORMAT_WMAUDIO_LOSSLESS)
#define WAVE_FORMAT_WMAUDIO_LOSSLESS  0x0163
#endif

#ifndef WAVE_FORMAT_PCM
#define WAVE_FORMAT_PCM 1
#endif

#ifndef WAVE_FORMAT_EXTENSIBLE
#define WAVE_FORMAT_EXTENSIBLE 65534
#endif

#if !defined (WAVE_FORMAT_WMAUDIO3)
#define WAVE_FORMAT_WMAUDIO3  0x0162

typedef struct wmaudio3waveformat_tag {
  WAVEFORMATEX wfx;
  unsigned short         wValidBitsPerSample; // bits of precision 
  unsigned int        dwChannelMask;       // which channels are present in stream 
  unsigned int        dwReserved1;
  unsigned int        dwReserved2;
  unsigned short         wEncodeOptions;
  unsigned short         wReserved3;
} WMAUDIO3WAVEFORMAT;

//typedef WMAUDIO3WAVEFORMAT FAR *LPWMAUDIO3WAVEFORMAT;
#define WMAUDIO3_WFX_EXTRA_BYTES    (sizeof(WMAUDIO3WAVEFORMAT) - sizeof(WAVEFORMATEX))
#endif // WAVE_FORMAT_WMAUDIO3

typedef struct tAsfXAcmAudioErrorMaskingData
{
    unsigned char    span;
//    unsigned short    virtualPacketLen;
//    unsigned short    virtualChunkLen;
//    unsigned short    silenceLen;
//    unsigned char    silence[1];

}   AsfXAcmAudioErrorMaskingData;

typedef struct tAsfXSignatureAudioErrorMaskingData
{
    unsigned int maxObjectSize;
 //   unsigned short  chunkLen;
 //   unsigned short  signatureLen;
 //   unsigned char  signature[1];

}   AsfXSignatureAudioErrorMaskingData;

#define COPY_KSDATAFORMAT_SUBTYPE_PCM(guid)\
     (guid)->Data1       = 0x01;\
     (guid)->Data2       = 0x00;\
     (guid)->Data3       = 0x10;\
     (guid)->Data4[0] = 0x80;\
     (guid)->Data4[1] = 0x00;\
     (guid)->Data4[2] = 0x00;\
     (guid)->Data4[3] = 0xaa;\
     (guid)->Data4[4] = 0x00;\
     (guid)->Data4[5] = 0x38;\
     (guid)->Data4[6] = 0x9b;\
     (guid)->Data4[7] = 0x71;

#ifndef _SPEAKER_POSITIONS_
#define _SPEAKER_POSITIONS_

#define SPEAKER_FRONT_LEFT              0x1
#define SPEAKER_FRONT_RIGHT             0x2
#define SPEAKER_FRONT_CENTER            0x4
#define SPEAKER_LOW_FREQUENCY           0x8
#define SPEAKER_BACK_LEFT               0x10
#define SPEAKER_BACK_RIGHT              0x20
#define SPEAKER_FRONT_LEFT_OF_CENTER    0x40
#define SPEAKER_FRONT_RIGHT_OF_CENTER   0x80
#define SPEAKER_BACK_CENTER             0x100
#define SPEAKER_SIDE_LEFT               0x200
#define SPEAKER_SIDE_RIGHT              0x400
#define SPEAKER_TOP_CENTER              0x800
#define SPEAKER_TOP_FRONT_LEFT          0x1000
#define SPEAKER_TOP_FRONT_CENTER        0x2000
#define SPEAKER_TOP_FRONT_RIGHT         0x4000
#define SPEAKER_TOP_BACK_LEFT           0x8000
#define SPEAKER_TOP_BACK_CENTER         0x10000
#define SPEAKER_TOP_BACK_RIGHT          0x20000
#endif


#ifndef _WMAFILEHEADER_DEFINED
#define _WMAFILEHEADER_DEFINED
typedef struct tagWMAFileHeader
{
    tWMAFileVersion version;         /* version of the codec */
    unsigned int sample_rate;  /* sampling rate */
    tWMAFileChannels num_channels;   /* number of audio channels */
    unsigned int duration;               /* of the file in milliseconds */
    unsigned int bitrate;                /* bit-rate of the WMA bitstream */
} tWMAFileHeader;
#endif /* _WMAFILEHEADER_DEFINED */

/* status */
#ifndef _WMAFILESTATUS_DEFINED
#define _WMAFILESTATUS_DEFINED
typedef enum tagWMAFileStatus
{
    cWMA_NoErr,                 /* -> always first entry */
                                /* remaining entry order is not guaranteed */
    cWMA_Failed,
    cWMA_BadArgument,
    cWMA_BadAsfHeader,
    cWMA_BadPacketHeader,
    cWMA_BrokenFrame,
    cWMA_NoMoreFrames,
    cWMA_BadSamplingRate,
    cWMA_BadNumberOfChannels,
    cWMA_BadVersionNumber,
    cWMA_BadWeightingMode,
    cWMA_BadPacketization,

    cWMA_BadDRMType,
    cWMA_DRMFailed,
    cWMA_DRMUnsupported,

    cWMA_DemoExpired,

    cWMA_BadState,
    cWMA_Internal,               /* really bad */
    cWMA_NoMoreDataThisTime
} tWMAFileStatus;
#endif /* _WMAFILESTATUS_DEFINED */

typedef struct tagWMAFileContDesc
{
    /* *_len: as [in], they specify how large the corresponding
     *        buffers below are.
     *        as [out], they specify how large the returned
     *        buffers actually are.
     */

    unsigned short title_len;
    unsigned short author_len;
    unsigned short copyright_len;
    unsigned short description_len;   /* rarely used */
    unsigned short rating_len;        /* rarely used */

    /* these are two-byte strings
     *   for ASCII-type character set, to convert these
     *   into a single-byte characters, simply skip
     *   over every other bytes.
     */

    unsigned char *pTitle;
    unsigned char *pAuthor;
    unsigned char *pCopyright;
    unsigned char *pDescription;
    unsigned char *pRating;

} tWMAFileContDesc;



#ifndef _ECD_DEFINED_
#define _ECD_DEFINED_
enum {
    ECD_STRING = 0,
    ECD_BINARY = 1,
    ECD_BOOL = 2,
    ECD_DWORD = 3,
    ECD_QWORD = 4,
    ECD_WORD = 5
};

typedef struct _ECD_DESCRIPTOR {
    unsigned short         cbName;
    unsigned short     *pwszName;
    unsigned short         data_type;
    unsigned short         cbValue;
    union {
        unsigned short *pwszString;
        unsigned char *pbBinary;
        tWMA_Bool *pfBool;
        unsigned int *pdwDword;
        tWMA_U64 *pqwQword;
        unsigned short  *pwWord;
    } uValue;
} ECD_DESCRIPTOR;
#endif // _ECD_DEFINED_

typedef struct tagWMAExtendedContentDescription
{
    unsigned short cDescriptors;             // number of descriptors
    ECD_DESCRIPTOR *pDescriptors;  // pointer to all the descriptors
} tWMAExtendedContentDesc;

#define DESC_NAME_MAX_LENGTH   64
typedef struct _MarkerEntry {
    QWORD   m_qOffset;
    QWORD   m_qtime;
    unsigned short    m_wEntryLen;
    unsigned int   m_dwSendTime;
    unsigned int   m_dwFlags;
    unsigned int   m_dwDescLen;
    unsigned short   m_pwDescName[DESC_NAME_MAX_LENGTH];
} MarkerEntry;


typedef struct tagWMA_MetaDataDescRecords 
{
    unsigned short     wLangIdIndex;   // Specifies the index of the language ID in the Language List Object
    unsigned short     wStreamNumber;  // Specifies whether the entry applies to a specific media stream or 
                                // whether it applies to the whole file. A value of 0 in this field 
                                // indicates that it applies to the whole file; otherwise, the entry 
                                // applies only to the indicated stream number.
    unsigned short     wNameLenth;     // Specifies the number of valid bytes stored in the Name field.
    unsigned short     wDataType;      // Specifies the type of information being stored. The following values are recognized:
                                // Value Type   Description
                                //  0x0000      Unicode string. The data consists of a sequence of Unicode characters.
                                //  0x0001      unsigned char array. The type of the data is implementation-specific.
                                //  0x0002      tWMA_Bool. The data is 2 bytes int and should be interpreted as a 16-bit unsigned integer. Only 0x0000 or 0x0001 are permitted values.
                                //  0x0003      unsigned int. The data is 4 bytes int and should be interpreted as a 32-bit unsigned integer.
                                //  0x0004      QWORD. The data is 8 bytes int and should be interpreted as a 64-bit unsigned integer.
                                //  0x0005      unsigned short. The data is 2 bytes int and should be interpreted as a 16-bit unsigned integer.
                                //  0x0006      GUID. The data is 8 bytes int and should be interpreted as a 128-bit GUID.
                                //  0x8000      Extended Unicode string. The data consists of a sequence of Unicode characters.
                                //  0x8001      Extended unsigned char array. The type of the data is implementation-specific.
                                //  0x8002      Extended tWMA_Bool. The data is 2 bytes int and should be interpreted as a 16-bit unsigned integer.  Only 0x0000 or 0x0001 are permitted values.
                                //  0x8003      Extended unsigned int. The data is 4 bytes int and should be interpreted as a 32-bit unsigned integer.
                                //  0x8004      Extended QWORD. The data is 8 bytes int and should be interpreted as a 64-bit unsigned integer.
                                //  0x8005      Extended unsigned short. The data is 2 bytes int and should be interpreted as a 16-bit unsigned integer.
                                //  0x8006      Extended GUID. The data is 8 bytes int and should be interpreted as a 128-bit GUID.
    unsigned int     dwDataLength;    // Specifies the length in bytes of the Data field.
    unsigned short    *pwName;        // Specifies the name that uniquely identifies the attribute being described. Names are case-sensitive.
    unsigned char     *pData;         // Specifies the actual metadata being stored. The Data field should be interpreted according to the value 
                                // stored in the Data Type field. If the Data Type is one of the extended values, this field may not contain 
                                //any data if the file is being streamed over the wire.
} WMA_MetaDataDescRecords;

typedef struct tagWMA_MetaDataEntry 
{
    unsigned short    m_wDescRecordsCount;
    WMA_MetaDataDescRecords *pDescRec;
} WMA_MetaDataEntry;


/* internal structure for the ASF header parsing */
typedef struct tagWMAFileHdrStateInternal
{
    tWMA_U64     currPacketOffset;     /* not just for packets */
    tWMA_U64     nextPacketOffset;

    /* ASF header */
    unsigned int   cbHeader;
    unsigned int   cbPacketSize;
    unsigned int   cbAudioSize;
    unsigned int   cPackets;
    unsigned int   msDuration;
    unsigned int   msPreroll;
    tWMA_U64     cbFirstPacketOffset;
    tWMA_U64     cbLastPacketOffset;
    unsigned int   dwFilePropertiesFlags;

    /* audio prop */
    unsigned short    nVersion;
    unsigned short    wFormatTag;
    unsigned int   nSamplesPerSec;
    unsigned int   nAvgBytesPerSec;
    unsigned int   nBlockAlign;
    unsigned short    nChannels;
    unsigned int   nSamplesPerBlock;
    unsigned short    nEncodeOpt;
    unsigned short    nAdvancedEncodeOpt;
    unsigned int   nAdvancedEncodeOpt2;
    
    // Added in V9
    unsigned short    wPCMFormatTag;
    unsigned short    wBitsPerSample; // container size
    unsigned short    wValidBitsPerSample; // actual valid data depth in the decoded stream
    unsigned int   dwChannelMask;
    GUID    SubFormat;
    unsigned short    wOriginalBitDepth; // actual valid data depth in the original source (informational)
    
    /* DRM */
    
    unsigned char    pbSecretData[32];
    unsigned int   cbSecretData;
    unsigned char    pbType[16];
    unsigned char    pbKeyID[32];

    /* Content Description */
   tWMAFileContDesc     *m_pDesc;

    /* Extended Content Description */

    tWMAExtendedContentDesc *m_pECDesc;

    /* Marker */
    unsigned int   m_dwMarkerNum;
    MarkerEntry *m_pMarker;

    /* License Store */
    //unsigned int   m_dwLicenseLen;
    unsigned char   *m_pLicData;


// Members added by Amit 
    unsigned short    wAudioStreamId;
    WMA_MetaDataEntry *ptMetaDataEntry;

    // Members added by Naveen for MBR support
    unsigned short    wTargetAudioStreamNumber;
    unsigned short    cAudioStreams;

} tWMAFileHdrStateInternal;

/* parser state  */
typedef enum
{
  //  csWMA_NotValid = 0,

    csWMA_HeaderStart,
 //   csWMA_HeaderError,

    csWMA_NewAsfPacket,

    /* packet parsing states */

    csWMA_DecodePayloadStart,
    csWMA_DecodePayload,
    csWMA_DecodeAudioData,
    csWMA_DecodePayloadEnd,
    csWMA_DecodeCompressedPayload,

    csWMA_End_

} tWMAParseState;

/****************************************************************************/
//typedef struct tWMAPlayerInfo
//{
//    unsigned short nPlayerOpt;        // Bit fields based on above defines
//    int *rgiMixDownMatrix; // Can be null to invoke defaults
//    int iPeakAmplitudeRef;
//    int iRmsAmplitudeRef;
//    int iPeakAmplitudeTarget;
//    int iRmsAmplitudeTarget;
//    short nDRCSetting;       // Dynamic range control setting
//    int iLtRtBufsize;
//    int iLtRtQuality;
//} WMAPlayerInfo;

/****************************************************************************/
typedef struct tPACKET_PARSE_INFO_EX
{
    tWMA_Bool fParityPacket;
    unsigned int cbParseOffset;

    tWMA_Bool fEccPresent;
    unsigned char bECLen;

    unsigned char bPacketLenType;
    unsigned int cbPacketLenTypeOffset;

    unsigned char bPadLenType;
    unsigned char bSequenceLenType;

    tWMA_Bool fMultiPayloads;
    unsigned char bOffsetBytes;
    unsigned char bOffsetLenType;
    unsigned int cbPacketLenOffset;
    unsigned int cbExplicitPacketLength; 
    unsigned int cbSequenceOffset;
    unsigned int dwSequenceNum; 
    unsigned int cbPadLenOffset;
    unsigned int cbPadding;
    unsigned int dwSCR;
    unsigned short wDuration;

    unsigned char bPayLenType;
    unsigned char bPayBytes;
    unsigned int cbPayLenTypeOffset;

    unsigned int cPayloads;

}   PACKET_PARSE_INFO_EX;

/****************************************************************************/
typedef struct tPAYLOAD_MAP_ENTRY_EX
{
    unsigned short cbPacketOffset;
    unsigned short cbTotalSize;
    unsigned char bStreamId;
    unsigned char bObjectId;
    unsigned int cbObjectOffset;
    unsigned int cbObjectSize;
    unsigned int msObjectPres;
    unsigned char cbRepData;
    unsigned char bJunk;
    unsigned short cbPayloadSize;
    unsigned short wBytesRead;
    unsigned short wTotalDataBytes;
    unsigned char bSubPayloadState;
    unsigned char bIsCompressedPayload;
    unsigned char bNextSubPayloadSize;
    unsigned short wSubpayloadLeft;
    unsigned int dwDeltaTime;
    unsigned short  wSubCount;    

}   PAYLOAD_MAP_ENTRY_EX;

typedef enum _audecState {
  audecStateDone = 0,
  audecStateInput,
  audecStateDecode,
  audecStateGetPCM
} audecState;

/* internal structure for the WMAudio library state */
typedef struct tagWMAFileStateInternal
{
    tWMAFileHdrStateInternal hdr_parse;
    /* parse_state */
    tWMAParseState parse_state;
    /* payload parsing */
    tWMA_U64   cbPayloadOffset;
    tWMA_U64   cbPayloadLeft;
    tWMA_Bool  bBlockStart;
    unsigned int cbBlockLeft;

    /* packet parsing */

    PACKET_PARSE_INFO_EX ppex;

    PAYLOAD_MAP_ENTRY_EX payload;
    unsigned int iPayload;
    unsigned short wPayStart;

    /* other states */
    tWMA_Bool    bHasDRM;
    unsigned int   nSampleCount;

    /* objects */
    void* hSPDTX;   // handle to spdif transmitter state machine
    char* szmdata;  // content descriptor metadata for spdif transmitter
    unsigned char* pbIn;     // used only by spdif transmitter ( for input buffer )
    unsigned int cbIn;     // used only by spdif transmitter ( for input buffer )
    unsigned int nLeadingBursts;     // leading empty spdif bursts
    unsigned int nTrailingBursts;    // trailing empty spdif bursts

    void* hWMA;     // handle to audio decoder
    audecState audecState; // audio decoder state

    unsigned char *pCallBackBuffer;
   void *pPlayerInfo;
} tWMAFileStateInternal;



#define WMA_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

#define WMA_IsEqualGUID(rguid1, rguid2) (!memcmp((void *)rguid1, (void *)rguid2, sizeof(GUID)))


#ifndef _WMAERR_DEFINED
#define _WMAERR_DEFINED
typedef int WMAERR;
#endif /* _WMAERR_DEFINED */

#define WMAERR_OK               0
#define WMAERR_FAIL             1
#define WMAERR_INVALIDARG       2
#define WMAERR_BUFFERTOOSMALL   3
#define WMAERR_INVALIDHEADER    4
#define WMAERR_OUTOFMEMORY      5
#define WMAERR_CORRUPTDATA      6
#define WMAERR_NOTDONE          7 /* need more data to finish the work */
#define WMAERR_INVALIDSTATE     8

#define WMA_memory_request 8*1024 //at least 6k

int Mstar_WMA_aop_bitstream_fseek2(unsigned int offset );
int Mstar_WMA_aop_bitstream_callback2(unsigned char *buf, int len );
int Mstar_WMAD_get_info(unsigned char * wma_buf_start, int *sample_rate, int *ch, int *total_time, int *bitrate, int *BitRateType, int *version, int *frame_size);

#define GetUnalignedWordEx( pb, w )     GetUnalignedWord( pb, w ); (pb) += sizeof(WORD);
#define GetUnalignedDwordEx( pb, dw )   GetUnalignedDword( pb, dw ); (pb) += sizeof(DWORD);
#define GetUnalignedQwordEx( pb, qw )   GetUnalignedQword( pb, qw ); (pb) += sizeof(QWORD);
//#define GetUnalignedDoubleEx( pb, d )   GetUnalignedDouble( pb, d ); (pb) += sizeof(double);

#define LoadBYTE( b, p )    b = *(unsigned char *)(p);  (p) += sizeof( unsigned char )

#define LoadWORD( w, p )    GetUnalignedWordEx( p, w )
#define LoadDWORD( dw, p )  GetUnalignedDwordEx( p, dw )
#define LoadQWORD( qw, p )  GetUnalignedQwordEx( p, qw )

#define LoadGUID( g, p ) \
        { \
            LoadDWORD( (g).Data1, p ); \
            LoadWORD( (g).Data2, p ); \
            LoadWORD( (g).Data3, p ); \
            LoadBYTE( (g).Data4[0], p ); \
            LoadBYTE( (g).Data4[1], p ); \
            LoadBYTE( (g).Data4[2], p ); \
            LoadBYTE( (g).Data4[3], p ); \
            LoadBYTE( (g).Data4[4], p ); \
            LoadBYTE( (g).Data4[5], p ); \
            LoadBYTE( (g).Data4[6], p ); \
            LoadBYTE( (g).Data4[7], p ); \
        }



#define GetUnalignedWord( pb, w ) \
            (w) = ((WORD) *(pb + 1) << 8) + *pb;

#define GetUnalignedDword( pb, dw ) \
            (dw) = ((DWORD) *(pb + 3) << 24) + \
                   ((DWORD) *(pb + 2) << 16) + \
                   ((DWORD) *(pb + 1) << 8) + *pb;

#define GetUnalignedQword( pb, qw ) \
            GetUnalignedDword( pb, (qw).dwLo ); \
            GetUnalignedDword( (pb + 4), (qw).dwHi );

//#define GetUnalignedDouble( pb, d ) (d) = *(UNALIGNED double*)(pb);
extern int retrieve_WMA_info(void *pFileName, void *pInfo);
//s32 retrieve_WAV_info2(void *aud_player, void *pInfo);
#endif
