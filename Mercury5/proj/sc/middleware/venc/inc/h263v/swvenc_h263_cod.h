#ifndef _H263_CODE_
#define _H263_CODE_

/* define H263 start code */
#define PACK_START          0x000001ba
#define SYSTEM_HEADER_START 0x000001bb
#define PACKET_START_LOW    0x000001bc
#define PACKET_START_HIGH   0x000001ff
#define SYNCWORD            0x00000fff
#define PICTURE_START       0x000020 // 22bit: b'00 0000 0000 0000 0010 0000
#define GROUP_START         0x00001 // 17bit: b'0 0000 0000 0000 0001
#define ESCAPE_CODE         0x00000001

/*
#define SLICE_BASE       0x00000101
#define USER_DATA_START  0x000001b2
#define SEQUENCE_START   0x000001b3
#define SEQUENCE_ERROR   0x000001b4
#define EXTENSION_START  0x000001b5
#define SEQUENCE_END     0x000001b7
#define GROUP_START      0x000001b8
#define SYSTEM_END       0x000001b9
#define PACKET_START_CODE_PREFIX    0x00000100
#define AUDIO_STREAM_ID_START   0xc0
#define VIDEO_STREAM_ID_START   0xe0
#define PADDING_STREAM_ID_START 0xbe
*/
#define AUDIO_PACKET_START_CODE_PREFIX  (PACKET_START_CODE_PREFIX | AUDIO_STREAM_ID_START)
#define VIDEO_PACKET_START_CODE_PREFIX  (PACKET_START_CODE_PREFIX | VIDEO_STREAM_ID_START)
#define PADDING_PACKET_START_CODE_PREFIX  (PACKET_START_CODE_PREFIX | PADDING_STREAM_ID_START)


#define SEQUENCE_EXTENSION_ID                  1
#define SEQUENCE_DISPLAY_EXTENSION_ID          2
#define QUANT_MATRIX_EXTENSION_ID              3
#define COPYRIGHT_EXTENSION_ID                 4
#define SEQUENCE_SCALABLE_EXTENSION_ID         5
#define PICTURE_DISPLAY_EXTENSION_ID           7
#define PICTURE_CODING_EXTENSION_ID            8
#define PICTURE_SPATIAL_SCALABLE_EXTENSION_ID  9
#define PICTURE_TEMPORAL_SCALABLE_EXTENSION_ID 10

#define    PROFILE_HIGH                1
#define    PROFILE_SPATIALLY_SCALABLE    2
#define    PROFILE_SNR_SCALABLE        3
#define    PROFILE_MAIN                4
#define    PROFILE_SIMPLE                5

#define LEVEL_HIGH                    4
#define LEVEL_HIGH1440                6
#define LEVEL_MAIN                    8
#define LEVEL_LOW                    10

#define CHROMA_FORMAT_420           1
#define CHROMA_FORMAT_422           2
#define CHROMA_FORMAT_444           3

#define VIDEO_FORMAT_PAL            1
#define VIDEO_FORMAT_NTSC           2
#define VIDEO_FORMAT_SECAM          3
#define VIDEO_FORMAT_MAC            4
#define VIDEO_FORMAT_UNSPECIFIED    5


#define COLOR_PRIMARIES_BT709             1
#define COLOR_PRIMARIES_UNSPECIFIED       2
#define COLOR_PRIMARIES_BT470_2System_M   4
#define COLOR_PRIMARIES_BT470_2System_BG  5
#define COLOR_PRIMARIES_SMPTE170M         6
#define COLOR_PRIMARIES_SMPTE240M         7

#define TRANSFER_CHARACTERISTICS_BT709         1
#define TRANSFER_CHARACTERISTICS_UNSPECIFIED   2
#define TRANSFER_CHARACTERISTICS_BT470SystemM  4
#define TRANSFER_CHARACTERISTICS_BT470SystemBG 5
#define TRANSFER_CHARACTERISTICS_SMPTE170M     6
#define TRANSFER_CHARACTERISTICS_SMPTE240M     7
#define TRANSFER_CHARACTERISTICS_LINEAR        8

#define MATRIX_COEFFICIENTS_BT709                1
#define MATRIX_COEFFICIENTS_UNSPECIFIED            2
#define MATRIX_COEFFICIENTS_FCC                    4
#define MATRIX_COEFFICIENTS_BT470SystemBG        5
#define MATRIX_COEFFICIENTS_SMPTE170M            6
#define MATRIX_COEFFICIENTS_SMPTE240M            7

#define INTRA_DC_PRECISION_8     0
#define INTRA_DC_PRECISION_9     1
#define INTRA_DC_PRECISION_10    2
#define INTRA_DC_PRECISION_11    3

#define PICTURE_STRUCTURE_TOP_FIELD        1
#define PICTURE_STRUCTURE_BOTTOM_FIELD     2
#define PICTURE_STRUCTURE_FRAME_PICTURE    3

// 14496-2
#define M4V_VOS_START           0x000001B0  // Visual Object Sequence start code, 32 bits
#define M4V_VOS_END             0x000001B1  // Visual Object Sequence end code, 32 bits
#define M4V_VO_START            0x000001B5  // Visual Object start code, 32 bits
#define M4V_VOBJ_START_BASE     0x00000100  // 0x00~0x1F
                                            // Video Object start code is (VOBJ_START_BASE | v)
                                            // where v is 5-bit atom, range from 0 to 0x1f
#define M4V_VOL_START_BASE      0x00000120  // 0x20~0x2F
                                            // video object layer start code is (VOL_START_BASE | v)
                                            // where v is 4-bit atom, range from 0 to 15
                                            // 0x30~0xAF    reserved

#define M4V_VOP_START           0x000001B6    // video object plane start code, 32 bits

// std annex G : table G-1
/* Profile and Level Indication */
// PDAM4 : annex C : table 8-16
typedef enum PLIndication {        // profile and level indication
    Simple_L1               = 0x01,
    Simple_L2               = 0x02,
    Simple_L3               = 0x03,
    PLIndication_MAX        = 0xff,
} PLIndication;

#endif
