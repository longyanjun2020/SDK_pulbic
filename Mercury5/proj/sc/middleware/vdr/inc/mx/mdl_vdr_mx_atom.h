////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
///@file       mdl_vdr_mx_atom.h
///@author  MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#ifndef __MDL_VDR_MX_ATOM_H__
#define __MDL_VDR_MX_ATOM_H__

//-----------------------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------------------
#include "mdl_vdr_mx_def.h"

//-----------------------------------------------------------------------------
// Extern Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//Macros Defines
//-----------------------------------------------------------------------------
#define USE_ATOM_BUFFERRED_READ

//-----------------------------------------------------------------------------
// Data Type Definition
//-----------------------------------------------------------------------------

//
//  ftyp property
//
typedef struct tagftypprop {
	uint32_t   major_brand;
	uint32_t   minor_version;
    char        **compatiable_brands;       // string array
    uint32_t   compatiable_brands_size;
} FTYPPROP, *PFTYPPROP;

//
//  mvhd property
//
typedef struct tagmvhdprop_v0 { // for version 0
    int32_t     version_flag;
    uint32_t    creation_time;
    uint32_t    modification_time;
    uint32_t    timescale;
    uint32_t    duration;
    int32_t     rate;
    int16_t     volume;
    byte        reserved1[70];
    uint32_t   	next_track_id;
} MVHDPROP_V0, *PMVHDPROP_V0;

typedef struct tagmvhdprop_v1 { // for version 1
    int32_t     version_flag;
    uint64_t    creation_time;
    uint64_t    modification_time;
    uint32_t    timescale;
    uint64_t    duration;
    int32_t     rate;
    int16_t     volume;
    byte        reserved1[70];
    uint32_t    next_track_id;
} MVHDPROP_V1, *PMVHDPROP_V1;

typedef struct tagiodsprop {
    int32_t   version_flag;

    union
    {
        // little endian layout
        struct {
            uint16_t reserved : 4;
            uint16_t include_inline_profile_level_flag : 1;
            uint16_t url_flag : 1;
            uint16_t object_desc_id : 10;
        }iods_desc_bits;
        uint16_t iods_desc_16;
    } iods_desc;

    uint8_t od_profile_level_indication;
    uint8_t scene_profile_level_indication;
    uint8_t audio_profile_level_indication;
    uint8_t visual_profile_level_indication;
    uint8_t graphics_profile_level_indication;
}IODSPROP, *PIODSPROP;

//
//  tkhd property
//
typedef struct tagtkhdprop_v0 {
    int32_t     version_flag;
    uint32_t    creation_time;
    uint32_t    modification_time;
    uint32_t    track_id;
    byte        reserved1[4];
    uint32_t    duration;
    byte        reserved2[12];
    uint16_t    volume;
    byte        reserved3[38];
    uint32_t    width;
    uint32_t    height;
} TKHDPROP_V0, *PTKHDPROP_V0;

typedef struct tagtkhdprop_v1 {
    int32_t     version_flag;
    uint64_t    creation_time;
    uint64_t    modification_time;
    uint32_t    track_id;
    uint32_t    reserved1;
    uint64_t    duration;
    byte        reserved2[12];
    uint32_t    volume;
    byte        reserved3[38];
    uint32_t    width;
    uint32_t    height;
} TKHDPROP_V1, *PTKHDPROP_V1;

//
//  mstr property
//
typedef struct tagmstrprop {
    uint8_t mace;
} MSTRPROP, *PMSTRPROP;

//
//  mdhd property
//
typedef struct tagmdhdprop_v0 {
    int32_t     version_flag;
    uint32_t    creation_time;
    uint32_t    modification_time;
    uint32_t    timescale;
    uint32_t    duration;
    uint16_t    language;
    byte        reserved[2];
} MDHDPROP_V0, *PMDHDPROP_V0;

typedef struct tagmdhdprop_v1 {
    int32_t     version_flag;
    uint32_t    creation_time;
    uint32_t    modification_time;
    uint32_t    timescale;
    uint32_t    duration;
    uint16_t    language;
    uint16_t    pre_defined;
} MDHDPROP_V1, *PMDHDPROP_V1;

//
//  hdlr property
//
typedef struct taghdlrprop {
    int32_t     version_flag;
    byte        reserved1[4];
    char        handler_type[5];
    byte        reserved2[12];
    char        *pname;
} HDLRPROP, *PHDLRPROP;

//
//  vmhd property
//
typedef struct tagvmhdprop {
    int32_t     version_flag;
    int16_t     graphicsmode;
    int16_t     opcolor[3];
} VMHDPROP, *PVMHDPROP;

//
//  smhd property
//
typedef struct tagsmhdprop {
    int32_t     version_flag;
    byte        reserved[4];
} SMHDPROP, *PSMHDPROP;

//
//  stts property
//
//
typedef struct tagSTTS_ENTRY {
    uint32_t    sample_count;
    uint32_t    sample_duration;
} STTS_ENTRY;

typedef struct tagsttsprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    *entry_sample;
    FILE_POS    sample_count_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    char        *cache_page;
    int         page_idx;
#endif

    uint32_t    sample_count;   // array [], the size is entry_count
    uint32_t    sample_delta;   // array []

    int32_t     default_uncomress_count;    
    int32_t     fhdl_stts_a;
    int32_t     fhdl_stts_v;
    int32_t     a_v;
} STTSPROP, *PSTTSPROP;

//
//  stsd property
//
typedef struct tagstsdprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    sample_dscription_size;
    char        data_format[5];
    int16_t     stream_width;
    int16_t     stream_height;
    uint8_t     decoder_cfg_len;
    void       *decoder_cfg;
} STSDPROP, *PSTSDPROP;

//
//  ctts property
//
typedef struct tagCTTS_ENTRY {
    uint32_t    sample_count;
    uint32_t    sample_offset;
} CTTS_ENTRY;

typedef struct tagcttsprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    FILE_POS    sample_count_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    char        *cache_page;
    int         page_idx;
#endif

    uint32_t    sample_count;   // array [], the size is entry_count
    uint32_t    sample_offset;   // array []
    int32_t     fhdl_stts_a;
    int32_t     fhdl_stts_v;
    int32_t     a_v;
} CTTSPROP, *PCTTSPROP;

//
//  stsz property
//
typedef struct tagSTSZ_ENTRY {
    uint32_t sample_size;
} STSZ_ENTRY;

typedef struct tagstszprop {
    int32_t     version_flag;
    uint32_t    sample_size;
    uint32_t    sample_count;
    uint32_t    entry_array_size;
    uint32_t    *entry_size;                    // array
    FILE_POS    entry_file_pos;                 // remove malloc array to save dynamic memory space

#ifdef USE_ATOM_BUFFERRED_READ
    char        *cache_page;
    int         page_idx;
#endif

    int32_t     default_uncomress_count;
    int32_t     fhdl_stsz_a;
    int32_t     fhdl_stsz_v;
    int32_t     a_v;
} STSZPROP, *PSTSZPROP;

//
//  stsc property
//
typedef struct tagSTSC_ENTRY {
    uint32_t first_chunk;
    uint32_t samples_per_chunk;
    uint32_t samples_desc_id;
} STSC_ENTRY;

typedef struct tagstscprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    *firstsample;                   // array,  as an optimization we add an implicit property to this table,
                                                // "firstSample" that corresponds to the first sample of the firstChunk
    uint32_t    *first_chunk;                   // array
    uint32_t    *samples_per_chunk;             // array
    uint32_t    *sample_description_index;      // array
    FILE_POS    entry_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    char        *cache_page;
    int         page_idx;
#endif

    int32_t     default_sample_chunk;
    int32_t     fhdl_stsc_a;
    int32_t     fhdl_stsc_v;
    int32_t     a_v;
} STSCPROP, *PSTSCPROP;

//
//  stco property
//
typedef struct tagSTCO_ENTRY {
    uint32_t    chunk_offset_e;
} STCO_ENTRY;

typedef struct tagstcoprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    *chunk_offset;
    FILE_POS    entry_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    char        *cache_page;
    int         page_idx;
#endif

    int32_t     fhdl_stco_a;
    int32_t     fhdl_stco_v;
    int32_t     a_v;
} STCOPROP, *PSTCOPROP;

//
// stss property
//
typedef struct tagSTSS_ENTRY {
    uint32_t sync_sample_id;
} STSS_ENTRY;

typedef struct tagstssprop {
    int32_t     version_flag;
    uint32_t    entry_count;
    uint32_t    *sync_sample;
    FILE_POS    entry_file_pos;

#ifdef USE_ATOM_BUFFERRED_READ
    char        *cache_page;
    int         page_idx;
#endif

    //
    // we read the keyframes in run time, instead of storing them in memory
    //
    //uint32_t  *sample_number;         // array

    int32_t     fhdl_stss_a;
    int32_t     fhdl_stss_v;
    int32_t     a_v;
} STSSPROP, *PSTSSPROP;

//
//  dref property
//
typedef struct tagdrefprop {
    int32_t     version_flag;
    uint32_t    entry_count;
} DREFPROP, *PDREFPROP;

//
//  url property
//
typedef struct tagurlprop {
    int32_t     version_flag;
    char*       location;
} URLPROP, *PURLPROP;

//
// for saving memory space, this is not used for now
//
//the default size is 64, cause we need to handle large boxes...
#define ISOM_BOX            \
    uint32_t type;          \
    uint64_t size;          \

//
// for saving memory space, this is not used for now
//
#define ISOM_SAMPLE_ENTRY_FIELDS        \
    ISOM_BOX                            \
    uint16_t dataReferenceIndex;        \
    char reserved[ 6 ];

//
// for saving memory space, this is not used for now
//
#define ISOM_VISUAL_SAMPLE_ENTRY        \
    ISOM_SAMPLE_ENTRY_FIELDS            \
    uint16_t version;                   \
    uint16_t revision;                  \
    uint32_t vendor;                    \
    uint32_t temporal_quality;          \
    uint32_t spacial_quality;           \
    uint16_t Width, Height;             \
    uint32_t horiz_res, vert_res;       \
    uint32_t entry_data_size;           \
    uint16_t frames_per_sample;         \
    unsigned char compressor_name[33];  \
    uint16_t bit_depth;                 \
    int16_t color_table_index;

//
// for saving memory space, this is not used for now
//
#define ISOM_AUDIO_SAMPLE_ENTRY     \
    ISOM_SAMPLE_ENTRY_FIELDS        \
    uint16_t version;               \
    uint16_t revision;              \
    uint32_t vendor;                \
    uint16_t channel_count;         \
    uint16_t bitspersample;         \
    uint16_t compression_id;        \
    uint16_t packet_size;           \
    uint16_t samplerate_hi;         \
    uint16_t samplerate_lo;

//
// esds property(Elementary stream descriptor)
// You have to parse tag to decide the type of descriptor
typedef struct {
    uint32_t version_flag;

    /* 0x03 ESDescrTag */
    uint16_t es_id;
#define MP4_O_DESCR_TAG                    0x01
#define MP4_IO_DESCR_TAG                   0x02
#define MP4_ES_DESCR_TAG                   0x03
#define MP4_DEC_CONFIG_DESCR_TAG            0x04
#define MP4_DEC_SPECIFIC_DESCR_TAG          0x05
#define MP4_SL_CONFIG_DESCR_TAG             0x06
#define MP4_CONTENT_ID_DESCR_TAG            0x07
#define MP4_SUPPL_CONTENT_ID_DESCR_TAG       0x08
#define MP4_IP_IPTR_DESCR_TAG               0x09
#define MP4_IP_MPPTR_DESCR_TAG              0x0A
#define MP4_IP_MP_DESCR_TAG                 0x0B
#define MP4_REGISTRATION_DESCR_TAG         0x0D
#define MP4_ES_IDINC_DESCR_TAG              0x0E
#define MP4_ES_IDREF_DESCR_TAG              0x0F
#define MP4_FILE_IOD_TAG                                 0x10
#define MP4_FILE_OD_TAG                                  0x11
#define MP4_EXT_PROFILE_LEVEL_DESCR_TAG      0x13
#define MP4_EXT_DESCR_TAGS_START            0x80
#define MP4_EXT_DESCR_TAGS_END              0xFE

#define MP4_STREAM_TYPE_VISUAL          0x04
#define MP4_STREAM_TYPE_AUDIO           0x05

#define MP4_OBJECT_TYPE_ID_ISO14496_2   0x20
#define MP4_OBJECT_TYPE_ID_ISO14496_3   0x40
#define MP4_OBJECT_TYPE_ID_ISO11172_2   0x6A
#define MP4_OBJECT_TYPE_ID_ISO11172_3   0x6B
#define MP4_OBJECT_TYPE_ID_ISO13818_2_SP 0x60
#define MP4_OBJECT_TYPE_ID_ISO13818_2_MP 0x61
#define MP4_OBJECT_TYPE_ID_ISO13818_7_MP 0x66
#define MP4_OBJECT_TYPE_ID_ISO13818_7_LC 0x67

/* Codec type in object_type_id */
#define MP4_OBJECT_TYPE_M4V                MP4_OBJECT_TYPE_ID_ISO14496_2
#define MP4_OBJECT_TYPE_AAC                MP4_OBJECT_TYPE_ID_ISO14496_3
#define MP4_OBJECT_TYPE_MP3                MP4_OBJECT_TYPE_ID_ISO11172_3


    uint8_t  stream_priority;

    /* 0x04 DecConfigDescrTag */
    uint8_t  object_type_id;
#define MP4Visual14496_2Object      0x20
#define MP4Audio14496_3Object       0x40
    uint8_t  stream_type;
    union
    {
        struct {
            uint8_t reserved : 1;
            uint8_t  up_stream : 1;
            uint8_t  stream_type : 6;
        }esds_dcd_bits;
        uint16_t esds_dcd_8;
    } esds_dcd;
#define MP4VisualStream                 0x04
#define MP4AudioStream                  0x05
    /* XXX: really streamType is
     * only 6bit, followed by:
     * 1bit  upStream
     * 1bit  reserved
     */
    uint32_t buffer_size_db; // 24
    uint32_t max_bitrate;
    uint32_t avg_bitrate;

    /* 0x05 DecSpecificDescrTag */
    uint8_t  decoder_cfg_len;
    uint8_t *decoder_cfg;

    /* 0x06 SLConfigDescrTag */
    uint8_t  sl_config_len;
    uint8_t *sl_config;
} MP4AV_ESDS, *PMP4AV_ESDS;

typedef struct
{
    //uint8_t configurationVersion;
    //uint8_t AVCProfileIndication;
    //uint8_t profile_compatibility;
    //uint8_t AVCLevelIndication;
    uint8_t nal_unit_size;

    uint8_t  decoder_cfg_len;
    uint8_t *decoder_cfg;
} AVCConfig;

//
// for saving memory space, this is not used for now
//
typedef struct
{
    ISOM_VISUAL_SAMPLE_ENTRY
    MP4AV_ESDS *esds;
} MP4VPROP, *PMP4VPROP;

//
// for saving memory space, this is not used for now
//
typedef struct
{
    ISOM_AUDIO_SAMPLE_ENTRY
    MP4AV_ESDS *esds;
} MP4APROP, *PMP4APROP;

//
//  samr property
//
typedef struct tagsamrprop {
    byte        reserved1[6];
    uint16_t    dataReferenceIndex;
    byte        reserved2[16];
    uint16_t    timescale;
    byte        reserved3[2];
    // used for version 1
    int16_t     samples_per_packets;
    int16_t     bytes_per_packet;    
} SAMRPROP, *PSAMRPORP;

typedef struct tagsamrprop SOUNPROP;
typedef struct tagsamrprop *PSOUNPROP;

//
//  damr property
//
typedef struct tagdamrprop {
    uint32_t    vendor;
    uint8_t     decoderVersion;
    uint16_t    modeSet;
    uint8_t     modeChangePeriod;
    uint8_t     framesPerSample;
} DAMRPROP, *PDAMRPROP;

//
//  dmp3 property :TODO need to know mp3 property 
//
typedef struct tagdmp3prop {
    uint32_t    vendor;
    uint8_t     decoderVersion;
    uint16_t    modeSet;
    uint8_t     modeChangePeriod;
}DMP3PROP, *PDMP3PROP;

//
//  s263 property
//
typedef struct tags263prop {
    byte        reserved1[6];
    uint16_t    dataReferenceIndex;
    byte        reserved2[16];
    uint16_t    width;
    uint16_t    height;
    byte        reserved3[50];
} S263PROP, *P263PROP;

typedef struct tags263prop VIDEPROP;
typedef struct tags263prop *PVIDEPROP;

//
//  d263 property
//
typedef struct tagd263prop {
    uint32_t    vendor;
    uint8_t     decoderVersion;
    uint8_t     h263Level;
    uint8_t     h263Profile;
} D263PROP, *PD263PROP;

//
//  bitr property
//
typedef struct tagbitrprop {
    uint32_t    avgBitrate;
    uint32_t    maxBitrate;
} BITRPROP, *PBITRPROP;

//-----------------------------------------------------------------------------
// Variable Definition
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Global Function Definition
//-----------------------------------------------------------------------------

#endif // __MDL_VDR_MX_ATOM_H__

