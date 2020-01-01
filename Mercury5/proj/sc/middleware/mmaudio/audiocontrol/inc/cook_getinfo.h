#ifndef _RMLBR_GETINFO_LIBRARY_INCLUDE_FILE_
#define _RMLBR_GETINFO_LIBRARY_INCLUDE_FILE_

#include <string.h>
#ifndef _RMLBR_GETINFO_AUDIO_
#define _RMLBR_GETINFO_AUDIO_

#ifndef HELIX_RESULT_H
#define HELIX_RESULT_H


#ifndef HELIX_TYPES_H
#define HELIX_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif  /* #ifdef __cplusplus */
    
/*
 * INT8 Type definition
 *
 * INT8 is a signed 8-bit type
 */
#ifndef INT8

#if defined(_SYMBIAN)
typedef TInt8 INT8;
#else /* #if defined(_SYMBIAN) */
typedef char INT8;
#endif /* #if defined(_SYMBIAN) */

#endif /* #ifndef INT8 */

    
/*
 * CHAR - signed 8-bit value
 */
typedef INT8 CHAR;


/*
 * UINT8 Type definition
 *
 * UINT8 is an unsigned 8-bit type
 */
#ifndef UINT8

#if defined(_SYMBIAN)
typedef TUint8 UINT8;
#else /* #if defined(_SYMBIAN) */
typedef unsigned char UINT8;
#endif /* #if defined(_SYMBIAN) */

#endif /* #ifndef UINT8 */

/*
 * BYTE Type definition
 *
 * BYTE is another name for a UINT8
 */
typedef UINT8 BYTE;

/*
 * UCHAR Unsigned 8 bit value.
 *
 */
typedef UINT8 UCHAR;

/*
 * INT16 Type definition
 *
 * INT16 is a signed 16-bit type
 */
#ifndef INT16

#if defined(_SYMBIAN)
typedef TInt16  INT16;
#else /* #if defined(_SYMBIAN) */
typedef short int INT16;
#endif /* #if defined(_SYMBIAN) */

#endif /* #ifndef INT16 */

/*
 * UINT16 Type definition
 *
 * UINT16 is an unsigned 16-bit type
 */
#ifndef UINT16

#if defined(_SYMBIAN)
typedef TUint16 UINT16;
#else /* #if defined(_SYMBIAN) */
typedef unsigned short int UINT16;
#endif /* #if defined(_SYMBIAN) */

#endif /* #ifndef UINT16 */

/*
 * INT32 Type definition
 *
 * INT32 is a signed 32-bit type
 */
#ifndef INT32

#if defined(_SYMBIAN)
typedef TInt32  INT32;
#elif defined(_UNIX) && defined(_LONG_IS_64)
typedef int INT32;
#elif defined(_VXWORKS)
typedef int INT32;
#else
typedef long int INT32;
#endif

#endif /* #ifndef INT32 */

/*
 * LONG32 Type definition
 *
 * LONG32 is another name for a INT32
 */
typedef INT32 LONG32;

/*
 * UINT32 Type definition
 *
 * UINT32 is an unsigned 32-bit type
 */
#ifndef UINT32

#if defined(_SYMBIAN)
typedef TUint32 UINT32;
#elif defined(_UNIX) && defined(_LONG_IS_64)
typedef unsigned int UINT32;
#elif defined(_VXWORKS)
typedef unsigned int UINT32;
#else
typedef unsigned long int UINT32;
#endif

#endif /* #ifndef UINT32 */

/*
 * UFIXED32 Type definition
 *
 * UFIXED32 is another name for a UINT32
 */
typedef UINT32 UFIXED32;

/*
 * ULONG32 Type definition
 *
 * ULONG32 is another name for a UINT32
 */
typedef UINT32 ULONG32;

/*
 * HX_MOFTAG Type definition
 *
 * HX_MOFTAG is of type UINT32
 */
typedef UINT32 HX_MOFTAG;

/*
 * HXBOOL Type definition
 *
 * HXBOOL is a boolean type
 */
#ifndef HXBOOL

#if defined(_SYMBIAN)
typedef TBool HXBOOL;
#else /* #if defined(_SYMBIAN) */
typedef int HXBOOL;
#endif /* #if defined(_SYMBIAN) */

#endif /* #ifndef HXBOOL */

/*
 * BOOL Type definition
 *
 * BOOL is another name for a HXBOOL
 */
//typedef HXBOOL BOOL;

/*
 * TRUE and FALSE definitions
 */
#ifdef TRUE
#undef TRUE
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifdef FALSE
#undef FALSE
#endif

#ifndef FALSE
#define FALSE 0
#endif

/*
 * HX_BITFIELD Type definition
 *
 * HX_BITFIELD is a bitfield type. It would
 * be used in conjunction with a field width
 * parameter like this:
 *
 * HX_BITFIELD foo:2;
 */
#ifndef HX_BITFIELD

typedef unsigned char HX_BITFIELD;

#endif

/*
 * HXFLOAT Type definition
 *
 * HXFLOAT is a single-precision floating-point type
 */
#ifndef HXFLOAT

typedef float HXFLOAT;

#endif /* #ifndef HXFLOAT */

/*
 * HXDOUBLE Type definition
 *
 * HXDOUBLE is a double-precision floating-point type
 */
#ifndef HXDOUBLE

typedef double HXDOUBLE;

#endif /* #ifndef HXDOUBLE */

/*
 * HXNULL definition
 */
#ifndef HXNULL
#define HXNULL ((void *)0)
#endif

/*
 * Helix DATE type.
 */

#define HX_YEAR_OFFSET 1900

typedef struct system_time
{
    UINT16 second;    /* 0-59 */
    UINT16 minute;    /* 0-59 */
    UINT16 hour;      /* 0-23 */
    UINT16 dayofweek; /* 0-6  (Sunday = 0) */
    UINT16 dayofmonth;/* 1-31 */
    UINT16 dayofyear; /* 1-366 (January 1 = 1) */
    UINT16 month;     /* 1-12 (January = 1) */
    UINT16 year;      /* year - 1900 or (year - HX_YEAR_OFFSET) */
    INT16 gmtDelta;   /* Greenwich Mean Time Delta in +/- hours */
} HX_DATETIME;
    
HX_DATETIME HX_GET_DATETIME(void);

#define HXEXPORT_PTR        *
#define HXEXPORT
#define ENTRYPOINT(func) func


#ifdef __cplusplus
}
#endif  /* #ifdef __cplusplus */

#endif /* #ifndef HELIX_TYPES_H */


#ifdef __cplusplus
extern "C" {
#endif  /* #ifdef __cplusplus */

/* Definition of HX_RESULT */
#ifndef HX_RESULT
typedef INT32 HX_RESULT;
#endif /* #ifndef HX_RESULT */

/* FACILITY_ITF defintion */
#ifndef FACILITY_ITF
#define FACILITY_ITF 4
#endif

/* General error definition macro */
#ifndef MAKE_HX_FACILITY_RESULT
#define MAKE_HX_FACILITY_RESULT(sev,fac,code) \
    ((HX_RESULT) (((UINT32)(sev) << 31) | ((UINT32)(fac)<<16) | ((UINT32)(code))))
#endif /* #ifndef MAKE_HX_FACILITY_RESULT */

/* Error definition macros with fac == FACILITY_ITF */
#ifndef MAKE_HX_RESULT
#define MAKE_HX_RESULT(sev,fac,code) MAKE_HX_FACILITY_RESULT(sev, FACILITY_ITF, ((fac << 6) | (code)))
#endif /* #ifndef MAKE_HX_RESULT */

#define SS_GLO      0  /* General errors                             */
#define SS_NET      1  /* Networking errors                          */
#define SS_FIL      2  /* File errors                                */
#define SS_DEC      8  /* Decoder errors                             */
#define SS_DPR     63  /* Deprecated errors                          */

#define HXR_NOTIMPL                     MAKE_HX_FACILITY_RESULT(1,0,0x4001)   /* 80004001 */
#define HXR_OUTOFMEMORY                 MAKE_HX_FACILITY_RESULT(1,7,0x000e)   /* 8007000e */
#define HXR_INVALID_PARAMETER           MAKE_HX_FACILITY_RESULT(1,7,0x0057)   /* 80070057 */
#define HXR_NOINTERFACE                 MAKE_HX_FACILITY_RESULT(1,0,0x4002)   /* 80004002 */
#define HXR_POINTER                     MAKE_HX_FACILITY_RESULT(1,0,0x4003)   /* 80004003 */
#define HXR_FAIL                        MAKE_HX_FACILITY_RESULT(1,0,0x4005)   /* 80004005 */
#define HXR_ACCESSDENIED                MAKE_HX_FACILITY_RESULT(1,7,0x0005)   /* 80070005 */
#define HXR_OK                          MAKE_HX_FACILITY_RESULT(0,0,0)        /* 00000000 */

#define HXR_INVALID_VERSION             MAKE_HX_RESULT(1,SS_GLO,5)            /* 80040005 */
#define HXR_UNEXPECTED                  MAKE_HX_RESULT(1,SS_GLO,9)            /* 80040009 */
#define HXR_UNSUPPORTED_AUDIO           MAKE_HX_RESULT(1,SS_GLO,15)           /* 8004000f */
#define HXR_NOT_SUPPORTED               MAKE_HX_RESULT(1,SS_GLO,33)           /* 80040021 */

#define HXR_NO_DATA                     MAKE_HX_RESULT(0,SS_NET,2)            /* 00040042 */

#define HXR_AT_END                      MAKE_HX_RESULT(0,SS_FIL,0)            /* 00040080 */
#define HXR_INVALID_FILE                MAKE_HX_RESULT(1,SS_FIL,1)            /* 80040081 */
#define HXR_CORRUPT_FILE                MAKE_HX_RESULT(1,SS_FIL,17)           /* 80040091 */
#define HXR_READ_ERROR                  MAKE_HX_RESULT(1,SS_FIL,18)           /* 80040092 */

#define HXR_BAD_FORMAT                  MAKE_HX_RESULT(1,SS_DPR,1)            /* 80040fc1 */

#define HXR_DEC_NOT_FOUND               MAKE_HX_RESULT(1,SS_DEC,1)            /* 80040201 */

/* Define success and failure macros */
#define HX_SUCCEEDED(status) (((UINT32) (status) >> 31) == 0)
#define HX_FAILED(status)    (((UINT32) (status) >> 31) != 0)

#ifdef __cplusplus
}
#endif  /* #ifdef __cplusplus */

#endif /* #ifndef HELIX_RESULT_H */

#define STRING_LEN_PROTECTION 64

#define RM_PARSER_INITIAL_READ_BUFFER_SIZE_GETINFO 256

#define HX_SEEK_ORIGIN_SET 0
#define HX_SEEK_ORIGIN_CUR 1
#define HX_SEEK_ORIGIN_END 2

#define RM_PROPERTY_TYPE_UINT32  0
#define RM_PROPERTY_TYPE_BUFFER  1
#define RM_PROPERTY_TYPE_CSTRING 2

#define HX_KEYFRAME_FLAG     0x0002
#define HX_KEYFRAME_RULE          0
#define HX_NONKEYFRAME_RULE       1
#define HX_THINNING_RULE          2
#define HX_ASM_SWITCH_ON          1
#define HX_ASM_SWITCH_OFF         2

#define RM_HEADER_OBJECT           0x2E524D46   /* '.RMF' */
#define RM_PROPERTIES_OBJECT       0x50524F50   /* 'PROP' */
#define RM_MEDIA_PROPERTIES_OBJECT 0x4D445052   /* 'MDPR' */
#define RM_CONTENT_OBJECT          0x434F4E54   /* 'CONT' */
#define RM_DATA_OBJECT             0x44415441   /* 'DATA' */
#define RM_INDEX_OBJECT            0x494E4458   /* 'INDX' */
#define RM_MULTIHEADER_OBJECT      0x4D4C5449   /* 'MLTI' */

#define RM_NO_STREAM_SET           0xFFFFFFFF
#define RM_INDEX_MIN_ENTRIES               32
#define RM_INDEX_MAX_ENTRIES             2048    
#define RM_INDEX_MIN_TIME_GRANULARITY      50  /* in milliseconds */
#define RM_INDEX_MAX_TIME_GRANULARITY   15000  /* in milliseconds */

#define RM_PARSER_GENERIC_HDR_SIZE       10
#define RM_PARSER_INDEX_HEADER_SIZE      20
#define RM_PARSER_INDEX_RECORD_SIZE      14
#define RM_PARSER_PACKET_HEADER_SIZE     12
#define RM_PARSER_DATA_CHUNK_HEADER_SIZE 18

#define RM_PARSER_LOGICAL_PREFIX    "logical-"
#define RM_PARSER_LOGICAL_FILEINFO  "logical-fileinfo"
#define RM_PARSER_NUM_RULE_BOOKS          9
#define RM_PARSER_RULE_BOOK_BUFFER_SIZE 320 /* Big enough for format string and args */

#define REALAUDIO_MIME_TYPE		 "audio/x-pn-realaudio"
#define REALAUDIO_ENCRYPTED_MIME_TYPE	 "audio/x-pn-realaudio-encrypted"
#define REALVIDEO_MIME_TYPE		 "video/x-pn-realvideo"
#define REALVIDEO_ENCRYPTED_MIME_TYPE	 "video/x-pn-realvideo-encrypted"
#define REALEVENT_MIME_TYPE		 "application/x-pn-realevent"
#define REALEVENT_ENCRYPTED_MIME_TYPE	 "application/x-pn-realevent-encrypted"
#define REALIMAGEMAP_MIME_TYPE		 "application/x-pn-imagemap"
#define REALIMAGEMAP_ENCRYPTED_MIME_TYPE "application/x-pn-imagemap-encrypted"
#define IMAGEMAP_MIME_TYPE		 "image_map/x-pn-realvideo"
#define IMAGEMAP_ENCRYPTED_MIME_TYPE	 "image_map/x-pn-realvideo-encrypted"
#define SYNCMM_MIME_TYPE		 "syncMM/x-pn-realvideo"
#define SYNCMM_ENCRYPTED_MIME_TYPE	 "syncMM/x-pn-realvideo-encrypted"

/* Audio codec defines */
#define RA_FORMAT_ID        0x2E7261FD  /* RealAudio Stream */
#define RA_NO_INTERLEAVER   0x496E7430  /* 'Int0' (no interleaver) */
#define RA_INTERLEAVER_SIPR 0x73697072  /* interleaver used for SIPRO codec ("sipr") */
#define RA_INTERLEAVER_GENR 0x67656E72  /* interleaver used for ra8lbr and ra8hbr codecs ("genr") */
#define RA_INTERLEAVER_VBRS 0x76627273  /* Simple VBR interleaver ("vbrs") */
#define RA_INTERLEAVER_VBRF 0x76627266  /* Simple VBR interleaver (with possibly fragmenting) ("vbrf") */

#if 0
static const char* g_pszRuleBook[] =
{
    /* VBR Real streams when max_bit_rate != 0 */
    "priority=%lu,AverageBandwidth=%lu,MaximumBandwidth=%lu,"
    "TimeStampDelivery=TRUE,PNMKeyFrameRule=T;"
    "OnDepend=\"0\",priority=%lu,AverageBandwidth=0,MaximumBandwidth=0,"
    "TimeStampDelivery=TRUE,PNMNonKeyFrameRule=T;",
    /* VBR Real streams when max_bit_rate == 0 */
    "priority=%lu,AverageBandwidth=%lu,TimeStampDelivery=TRUE,PNMKeyFrameRule=T;"
    "OnDepend=\"0\",priority=%lu,AverageBandwidth=0,TimeStampDelivery=TRUE,PNMNonKeyFrameRule=T;",
    /* Non-real-datatype VBR streams when max_bit_rate != 0 */
    "Marker=0,AverageBandwidth=%lu,MaximumBandwidth=%lu,TimeStampDelivery=TRUE;"
    "Marker=1,AverageBandwidth=0,MaximumBandwidth=0,TimeStampDelivery=TRUE;",
    /* Non-real-datatype VBR streams when max_bit_rate == 0 && avg_bit_rate != 0 */
    "Marker=0,AverageBandwidth=%lu,TimeStampDelivery=TRUE;"
    "Marker=1,AverageBandwidth=0,TimeStampDelivery=TRUE;",
    /* Non-real-datatype VBR streams when max_bit_rate == 0 && avg_bit_rate == 0 */
    "Marker=0,TimeStampDelivery=TRUE;"
    "Marker=1,TimeStampDelivery=TRUE;",
    /* CBR RealVideo */
    "#($Bandwidth >= %lu),priority=9,averagebandwidth=%lu,PNMKeyFrameRule=T;"
    "#($Bandwidth >= %lu),OnDepend=\"0\",priority=5,averagebandwidth=0,PNMNonKeyFrameRule=T;"
    "#($Bandwidth < %lu),priority=9,timestampdelivery=T,DropByN=T,PNMThinningRule=T;",
    /* RealEvent streams */
    "TimeStampDelivery=T,priority=10,PNMKeyFrameRule=T;"
    "TimeStampDelivery=T,priority=10,PNMNonKeyFrameRule=T;",
    /* CBR RealAudio streams */
    "priority=5,averagebandwidth=%lu,PNMKeyFrameRule=T;"
    "priority=5,averagebandwidth=0,PNMNonKeyFrameRule=T,OnDepend=\"0\",OffDepend=\"0\";",
    /* CBR non-real-datatype streams */
    "Marker=0,priority=5,averagebandwidth=%lu;"
    "Marker=1,priority=5,averagebandwidth=0;"
};
#endif
typedef struct ra_format_info_struct
{
    UINT32 ulSampleRate;
    UINT32 ulActualRate;
    UINT16 usBitsPerSample;
    UINT16 usNumChannels;
    UINT16 usAudioQuality;
    UINT16 usFlavorIndex;
    UINT32 ulBitsPerFrame;
    UINT32 ulGranularity;
    UINT32 ulOpaqueDataSize;
    UINT32 uSampleSize;
    BYTE*  pOpaqueData;
} ra_format_info;

typedef struct ra_block_struct
{
    BYTE*  pData;
    UINT32 ulDataLen;
    UINT32 ulTimestamp;
    UINT32 ulDataFlags;
} ra_block;

typedef void rm_parser;
typedef void ra_depack;
typedef void (*rm_error_func_ptr) (void* pUserError, HX_RESULT err, const char* msg);
typedef void* (*rm_malloc_func_ptr) (void* pUserMem, UINT32 ulSize);
typedef void  (*rm_free_func_ptr)   (void* pUserMem, void* ptr);

typedef HX_RESULT (*ra_block_avail_func_ptr) (void*     pAvail,
                                              UINT32    ulSubStream,
                                              ra_block* block);

/* Function pointer definitions */
typedef UINT32 (*rm_read_func_ptr) (void*   pUserRead,
                                    BYTE*   pBuf, /* Must be at least ulBytesToRead long */
                                    UINT32  ulBytesToRead);
typedef void (*rm_seek_func_ptr) (void*  pUserRead,
                                  UINT32 ulOffset,
                                  UINT32 ulOrigin);

typedef HX_RESULT (*ra_decode_init_func_ptr)(void*              pInitParams,
                                             UINT32             ulInitParamsSize,
                                             ra_format_info*    pStreamInfo,
                                             void**             pDecode,
                                             void*              pUserMem,
                                             rm_malloc_func_ptr fpMalloc,
                                             rm_free_func_ptr   fpFree);
typedef HX_RESULT (*ra_decode_reset_func_ptr)(void*   pDecode,
                                              UINT16* pSamplesOut,
                                              UINT32  ulNumSamplesAvail,
                                              UINT32* pNumSamplesOut);
typedef HX_RESULT (*ra_decode_conceal_func_ptr)(void*  pDecode,
                                                UINT32 ulNumSamples);
typedef HX_RESULT (*ra_decode_decode_func_ptr)(void*       pDecode,
                                               UINT8*      pData,
                                               UINT32      ulNumBytes,
                                               UINT32*     pNumBytesConsumed,
                                               UINT16*     pSamplesOut,
                                               UINT32      ulNumSamplesAvail,
                                               UINT32*     pNumSamplesOut,
                                               UINT32      ulFlags);
typedef HX_RESULT (*ra_decode_getmaxsize_func_ptr)(void*   pDecode,
                                                   UINT32* pNumSamples);
typedef HX_RESULT (*ra_decode_getchannels_func_ptr)(void*   pDecode,
                                                    UINT32* pNumChannels);
typedef HX_RESULT (*ra_decode_getchannelmask_func_ptr)(void*   pDecode,
                                                       UINT32* pChannelMask);
typedef HX_RESULT (*ra_decode_getrate_func_ptr)(void*   pDecode,
                                                UINT32* pSampleRate);
typedef HX_RESULT (*ra_decode_getdelay_func_ptr)(void*   pDecode,
                                                 UINT32* pNumSamples);
typedef HX_RESULT (*ra_decode_close_func_ptr)(void*            pDecode,
                                              void*            pUserMem,
                                              rm_free_func_ptr fpFree);



struct rm_pkt_hdr
{
    UINT16 version;             /* struct version */
    UINT16 length;              /* length of header */
    UINT16 stream_num;          /* stream number */
    UINT32 timestamp;           /* packet timestamp */
    UINT16 flags;               /* keyframe, etc. */
};

typedef struct rm_property_struct
{
    char*  pName;
    UINT32 ulType;
    BYTE*  pValue;
    UINT32 ulValueLen;
} rm_property;

typedef struct ra_decode_struct
{
    void*                               pUserError;
    rm_error_func_ptr                   fpError;
    void*                               pUserMem;
    rm_malloc_func_ptr                  fpMalloc;
    rm_free_func_ptr                    fpFree;

    ra_decode_init_func_ptr             fpInit;
    ra_decode_reset_func_ptr            fpReset;
    ra_decode_conceal_func_ptr          fpConceal;
    ra_decode_decode_func_ptr           fpDecode;
    ra_decode_getmaxsize_func_ptr       fpGetMaxSize;
    ra_decode_getchannels_func_ptr      fpGetChannels;
    ra_decode_getchannelmask_func_ptr   fpGetChannelMask;
    ra_decode_getrate_func_ptr          fpGetSampleRate;
    ra_decode_getdelay_func_ptr         fpMaxSamp;
    ra_decode_close_func_ptr            fpClose;

    void*                               pDecode;
} ra_decode;


typedef struct
{
    ra_depack* pDepack;
    ra_decode* pDecode;
    BYTE*      pOutBuf;
    UINT32     ulOutBufSize;
    UINT32     ulDataBytesWritten;
} rm2wav_info_getinfo;

struct rm_generic_hdr
{
    UINT32 id;          /* unique identifier for this header */
    UINT32 size;        /* size of header in file */
    UINT16 version;     /* struct version */
};

/* rm file header -- all real media files start with this header */
struct rm_file_hdr
{
    UINT32 id;           /* unique identifier for this header */
    UINT32 size;         /* size of header in file */
    UINT16 version;      /* struct version */
    UINT32 file_version; /* revision number for realmedia file */
    UINT32 num_headers;  /* num headers in file (including this one) */
};

/* rm properties header -- summarizes data for entire clip */
struct rm_properties_hdr
{
    UINT32 id;           /* unique identifier for this header */
    UINT32 size;         /* size of header in file */
    UINT16 version;      /* struct version */
    UINT32 max_bit_rate; /* maximum bit rate of clip */
    UINT32 avg_bit_rate; /* average bit rate of clip */
    UINT32 max_pkt_size; /* max length of packet in clip (bytes) */
    UINT32 avg_pkt_size; /* averge length of packet in clip (bytes) */
    UINT32 num_pkts;     /* total packets in clip (all streams) */
    UINT32 duration;     /* duration of clip (milliseconds) */
    UINT32 preroll;      /* preroll time (milliseconds) */
    UINT32 index_offset; /* offset to beginning of index data */
    UINT32 data_offset;  /* offset to beginning of packet data */
    UINT16 num_streams;  /* total number of streams in clip */
    UINT16 flags;        /* various and sundry */
};

/* rm content header -- title, author, copyright */
struct rm_content_hdr
{
    UINT32 id;               /* unique identifier for this header */
    UINT32 size;             /* size of header in file */
    UINT16 version;          /* struct version */
    UINT16 title_sz;         /* length of title field */
    char*  title;            /* title of clip */
    UINT16 author_sz;        /* length of author field */
    char*  author;           /* author of clip */
    UINT16 copyright_sz;     /* length of copyright field */
    char*  copyright;        /* copyright of clip */
    UINT16 comment_sz;       /* length of comment field */
    char*  comment;          /* comment */
};

/* rm media properties header -- stream info, one for each stream */
struct rm_media_props_hdr
{
    UINT32 id;                  /* unique identifier for this header */
    UINT32 size;                /* size of header in file */
    UINT16 version;             /* struct version */
    UINT16 stream_num;          /* stream number */
    UINT32 max_bit_rate;        /* maximum bit rate of stream */
    UINT32 avg_bit_rate;        /* average bit rate of stream */
    UINT32 max_pkt_size;        /* max length of packet in stream (bytes) */
    UINT32 avg_pkt_size;        /* averge length of packet in stream (bytes) */
    UINT32 start_time;          /* start time of stream -- clip relative */
    UINT32 preroll;             /* preroll time (milliseconds) */
    UINT32 duration;            /* duration of stream (milliseconds) */
    BYTE   stream_name_sz;      /* length of stream_name field */
    char*  stream_name;         /* string name of stream */
    BYTE   mime_type_sz;        /* length of mime_type field */
    char*  mime_type;           /* MIME type of stream */
    UINT32 type_spec_sz;        /* length of type_spec field */
    BYTE*  type_spec;           /* type specific data buffer */
};

struct rm_name_value_map
{
    UINT32 size;      /* size of header in file */
    UINT16 version;   /* struct version */
    BYTE   name_sz;   /* length of name field */
    char*  name;      /* name of property */
    UINT32 type;      /* type of property */
    UINT16 value_sz;  /* length of value field */
    BYTE*  value;     /* value of property */
};


/* rm logical stream header -- used for surestream */
struct rm_logical_stream_hdr
{
    UINT32  size;                    /* size of header in file */
    UINT16  version;                 /* struct version */ 
    UINT16  num_physical_streams;    /* number of actual streams */
    UINT16* physical_stream_num;     /* array of stream numbers */
    UINT32* data_offsets;            /* array of offsets to stream packets */
    UINT16  num_rules;               /* number of ASM rules */
    UINT16* rule_stream_map;         /* maps rules to streams */
    UINT16  num_props;               /* number of name value properties */
    struct rm_name_value_map* props; /* array of name value properties */
};

struct rm_seek_table_entry
{
    UINT32 ulTime;
    UINT32 ulOffset;
};

struct rm_seek_table
{
    struct rm_seek_table_entry* pEntry;
    UINT32                      ulMaxEntries;
    UINT32                      ulNumEntries;
    UINT32                      ulLastTime;
    UINT32                      ulRangeTime;
    UINT32                      ulTimeGranularity;
};

struct rm_keyframe_packet
{
    UINT32 ulTimestamp;
    UINT32 ulFileOffset;
    HXBOOL bValid;
};

struct rm_stream_info
{
   UINT32                    ulLastTimeStamp;
   UINT32                    ulLastRule;
   struct rm_keyframe_packet keyFramePacket;
   struct rm_seek_table      seekTable;
   HX_BITFIELD               bIsRealAudio              : 1;
   HX_BITFIELD               bIsRealVideo              : 1;
   HX_BITFIELD               bIsRealEvent              : 1;
   HX_BITFIELD               bStreamDone               : 1;
   HX_BITFIELD               bNeedKeyframe             : 1;
   HX_BITFIELD               bSeenFirstPacketTimeStamp : 1;
};

struct rm_data_hdr
{
    UINT32 id;                  /* unique identifier for this header */
    UINT32 size;                /* size of header in file */
    UINT16 version;             /* struct version */
    UINT32 num_pkts;            /* total number of packets in segment */
    UINT32 next_data_hdr;       /* offset of next segment */
};

typedef struct rm_stream_header_struct
{
    char*        pMimeType;
    char*        pStreamName;
    UINT32       ulStreamNumber;
    UINT32       ulMaxBitRate;
    UINT32       ulAvgBitRate;
    UINT32       ulMaxPacketSize;
    UINT32       ulAvgPacketSize;
    UINT32       ulDuration;
    UINT32       ulPreroll;
    UINT32       ulStartTime;
    UINT32       ulOpaqueDataLen;
    BYTE*        pOpaqueData;
    UINT32       ulNumProperties;
    rm_property* pProperty;
} rm_stream_header;

/*
 * Parser struct
 */
typedef struct rm_parser_internal_struct
{
    rm_error_func_ptr             fpError;
    void*                         pUserError;
    rm_malloc_func_ptr            fpMalloc;
    rm_free_func_ptr              fpFree;
    void*                         pUserMem;
    rm_read_func_ptr              fpRead;
    rm_seek_func_ptr              fpSeek;
    void*                         pUserRead;
    struct rm_file_hdr            fileHdr;
    struct rm_properties_hdr      propHdr;
    struct rm_content_hdr         contHdr;
    UINT32                        ulNumStreams;
    UINT32                        ulNumMediaPropsHdrs;
    UINT32                        ulNumMediaPropsHdrsAlloc;
    struct rm_media_props_hdr*    pMediaPropsHdr;
    UINT32                        ulNumLogicalStreamHdrs;
    struct rm_logical_stream_hdr* pLogicalStreamHdr;
    struct rm_logical_stream_hdr* pLogicalFileInfo;
    BYTE*                         pReadBuffer;            /* Read buffer */
    UINT32                        ulReadBufferSize;       /* Allocated size of the read buffer */
    UINT32                        ulNumBytesRead;         /* Current number of bytes read into the buffer */
    UINT32                        ulCurFileOffset;        /* Current read offset into the file */
    UINT32                        ulStreamNumMapSize;
    UINT32*                       pulStreamNumMap;
    UINT32                        ulMaxDuration;
    struct rm_stream_info*        pStreamInfo;
    struct rm_data_hdr            dataHdr;
    HXBOOL                        bIsRealDataType;
    UINT32                        ulMinFirstPacketTime;
    rm_stream_header*             pStreamHdr;
    UINT32                        ulKeyframesNeeded;
} rm_parser_internal;

/* map an ASM rule to some other property */
typedef struct rm_rule_map_struct
{
    UINT32  ulNumRules;
    UINT32* pulMap;
} rm_rule_map;

/* rm multistream header -- surestream */
typedef struct rm_multistream_hdr_struct
{
    UINT32             ulID;            /* unique identifier for this header */
    rm_rule_map rule2SubStream;  /* mapping of ASM rule number to substream */
    UINT32             ulNumSubStreams; /* number of substreams */
} rm_multistream_hdr;

typedef struct ra_substream_hdr_struct
{
    UINT16      usRAFormatVersion;     /* 3, 4, or 5 */
    UINT16      usRAFormatRevision;    /* should be 0 */
    UINT16      usHeaderBytes;         /* size of raheader info */
    UINT16      usFlavorIndex;         /* compression type */
    UINT32      ulGranularity;         /* size of one block of encoded data */
    UINT32      ulTotalBytes;          /* total bytes of ra data */
    UINT32      ulBytesPerMin;         /* data rate of encoded and interleaved data */
    UINT32      ulBytesPerMin2;        /* data rate of interleaved or non-interleaved data */
    UINT32      ulInterleaveFactor;    /* number of blocks per superblock */
    UINT32      ulInterleaveBlockSize; /* size of each interleave block */
    UINT32      ulCodecFrameSize;      /* size of each audio frame */
    UINT32      ulUserData;            /* extra field for user data */
    UINT32      ulSampleRate;          /* sample rate of decoded audio */
    UINT32      ulActualSampleRate;    /* sample rate of decoded audio */
    UINT32      ulSampleSize;          /* bits per sample in decoded audio */
    UINT32      ulChannels;            /* number of audio channels in decoded audio */
    UINT32      ulInterleaverID;       /* interleaver 4cc */
    UINT32      ulCodecID;             /* codec 4cc */
    BYTE        bIsInterleaved;        /* 1 if file has been interleaved */
    BYTE        bCopyByte;             /* copy enable byte, if 1 allow copies (SelectiveRecord) */
    BYTE        ucStreamType;          /* i.e. LIVE_STREAM, FILE_STREAM */
    BYTE        ucScatterType;         /* the interleave pattern type 0==cyclic,1==pattern */
    UINT32      ulNumCodecFrames;      /* number of codec frames in a superblock */
    UINT32*     pulInterleavePattern;  /* the pattern of interleave if not cyclic */
    UINT32      ulOpaqueDataSize;      /* size of the codec specific data */
    BYTE*       pOpaqueData;           /* codec specific data */
    HXDOUBLE    dBlockDuration;        /* Duration in ms of audio "block" */
    UINT32      ulLastSentEndTime;     /* Ending time of last sent audio frame */
    BYTE*       pFragBuffer;           /* Intermediate buffer for reconstructing VBR packets */
    UINT32      ulFragBufferSize;      /* Size of intermediate buffer */
    UINT32      ulFragBufferAUSize;    /* Size of AU being reconstructed */
    UINT32      ulFragBufferOffset;    /* Current offset within AU */
    UINT32      ulFragBufferTime;      /* Timestamp of AU being reconstructed */
    UINT32      ulSuperBlockSize;      /* ulInterleaveBlockSize * ulInterleaveFactor */
    UINT32      ulSuperBlockTime;      /* dBlockDuration * ulInterleaveFactor */
    UINT32      ulKeyTime;             /* Timestamp of keyframe packet */
    BYTE*       pIBuffer;              /* Buffer holding interleaved blocks    */
    BYTE*       pDBuffer;              /* Buffer holding de-interleaved blocks */
    UINT32*     pIPresentFlags;        /* number of UINT32s: ulInterleaveBlockSize */
    UINT32*     pDPresentFlags;        /* number of UINT32s: ulInterleaveBlockSize */
    UINT32      ulBlockCount;          /* number of blocks currently in superblock */
    UINT32*     pulGENRPattern;        /* Interleave pattern for GENR interleaver */
    UINT32*     pulGENRBlockNum;
    UINT32*     pulGENRBlockOffset;
    HX_BITFIELD bIsVBR : 1;
    HX_BITFIELD bSeeked : 1;
    HX_BITFIELD bLossOccurred : 1;
    HX_BITFIELD bHasKeyTime : 1;       /* Do we have a time for the key slot? */
    HX_BITFIELD bHasFrag : 1;
    HX_BITFIELD bAdjustTimestamps : 1;
    HX_BITFIELD bKnowIfAdjustNeeded : 1;
    HX_BITFIELD bHasLastPacket : 1;
} ra_substream_hdr;

typedef struct ra_depack_internal_struct
{
    void*                   pAvail;
    ra_block_avail_func_ptr fpAvail;
    rm_error_func_ptr       fpError;
    void*                   pUserError;
    rm_malloc_func_ptr      fpMalloc;
    rm_free_func_ptr        fpFree;
    void*                   pUserMem;
    rm_rule_map             rule2Flag;
    rm_multistream_hdr      multiStreamHdr;
    ra_substream_hdr*       pSubStreamHdr;
    UINT32                  ulTrackStartTime;
    UINT32                  ulTrackEndTime;
    UINT32                  ulEndTime;
    UINT32                  ulStreamDuration;
    HX_BITFIELD             bForceTrackStartTime : 1;
    HX_BITFIELD             bForceTrackEndTime : 1;
    HX_BITFIELD             bStreamSwitchable : 1;
    HX_BITFIELD             bAllVBR : 1;
    HX_BITFIELD             bAllNonVBR : 1;
    HX_BITFIELD             bHasEndTime : 1;
} ra_depack_internal;


typedef struct ra8lbr_decode_struct
{
    void*   pDecoder;
    UINT32  ulNumChannels;
    UINT32  ulChannelMask;
    UINT32  ulFrameSize;
    UINT32  ulFramesPerBlock;
    UINT32  ulSamplesPerFrame;
    UINT32  ulSampleRate;
    UINT32  ulDelayFrames;
    UINT32  ulDelayRemaining;
    UINT32  ulFramesToConceal;
    UCHAR*  pFlushData;
} ra8lbr_decode;

#endif

//#include "helix_result.h"

static unsigned char * RMlbr_bufgetinfo_start;
static unsigned char * RMlbr_bufgetinfo_point;
static unsigned char * RMlbr_bufgetinfo_end;

#ifdef _WIN32
#define debug_msg_enable
#endif

#define RMlbr_GetInfo_memory_request 8*1024    //at least 5786 bytes of pattern25.ram

unsigned int reset_mem_use(void);
int Mstar_COOK_aop_bitstream_fseek2(unsigned int offset );
int Mstar_COOK_aop_bitstream_callback2(unsigned char *buf, int len );
int Mstar_COOKD_get_info(unsigned char * cook_buf_start, int *sample_rate, int *ch, int *total_time, int *bitrate, int *BitRateType);
extern int retrieve_COOK_info(void *pFileName, void *pInfo);

#endif
