//==============================================================================
//
//  File        : mmp_exif_inc.h
//  Description : INCLUDE File for the EXIF Driver Function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMP_EXIF_INC_H_
#define _MMP_EXIF_INC_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

/**
@bref   the header structure of JPEG

0xFF:   Maker prefix

0xFFD8: SOI, Start of Image, Start of compressed data
0xFFDB: DQT, Define Quantization Table, Quantization table definition
0xFFC4: DHT, Define Huffman Table, Huffman table definition
0xFFDD: DRI, Define Restart Interoperability, Restart Interoperability definition
0xFFC0: SOF, Start of Frame, Frame header
0xFFCC: DAC
0xFFDA: SOS, Start of Scan, Scan header
0xFFDC: DNL
0xFFDE: DHP
0xFFDF: EXP
0xFFD9: EOI, End of Image, End of compressed data
0xFFFE: COM, comment
0xFF01: TEM,

RES         => 0xFF02~0xFFBF
SOF range   => 0xFFC0~0xFFC3, 0xFFC5~0xFFC7, 0xFFCD~0xFFCF
RST0~RST7   => 0xFFD0~0xFFD7
JPG0~JPG13  => 0xFFF0~0xFFFD
*/

#define JPG_EXIF_PREFIX             0xFF

#define JPG_EXIF_TEM                0xFF01
#define JPG_EXIF_SOF                0xFFC0
#define JPG_EXIF_SOF1               0xFFC1
#define JPG_EXIF_SOF2               0xFFC2
#define JPG_EXIF_SOF3               0xFFC3
#define JPG_EXIF_DHT                0xFFC4
#define JPG_EXIF_SOF5               0xFFC5
#define JPG_EXIF_SOF6               0xFFC6
#define JPG_EXIF_SOF7               0xFFC7
#define JPG_EXIF_JPG                0xFFC8
#define JPG_EXIF_SOF9               0xFFC9
#define JPG_EXIF_SOF10              0xFFCA
#define JPG_EXIF_SOF11              0xFFCB
#define JPG_EXIF_DAC                0xFFCC
#define JPG_EXIF_SOF13              0xFFCD
#define JPG_EXIF_SOF14              0xFFCE
#define JPG_EXIF_SOF15              0xFFCF
#define JPG_EXIF_RST0               0xFFD0
#define JPG_EXIF_RST1               0xFFD1
#define JPG_EXIF_RST2               0xFFD2
#define JPG_EXIF_RST3               0xFFD3
#define JPG_EXIF_RST4               0xFFD4
#define JPG_EXIF_RST5               0xFFD5
#define JPG_EXIF_RST6               0xFFD6
#define JPG_EXIF_RST7               0xFFD7
#define JPG_EXIF_SOI                0xFFD8
#define JPG_EXIF_EOI                0xFFD9
#define JPG_EXIF_SOS                0xFFDA
#define JPG_EXIF_DQT                0xFFDB
#define JPG_EXIF_DNL                0xFFDC
#define JPG_EXIF_DRI                0xFFDD
#define JPG_EXIF_DHP                0xFFDE
#define JPG_EXIF_EXP                0xFFDF
#define JPG_EXIF_APP0               0xFFE0
#define JPG_EXIF_APP1               0xFFE1
#define JPG_EXIF_APP2               0xFFE2
#define JPG_EXIF_APP3               0xFFE3
#define JPG_EXIF_APP4               0xFFE4
#define JPG_EXIF_APP5               0xFFE5
#define JPG_EXIF_APP6               0xFFE6
#define JPG_EXIF_APP7               0xFFE7
#define JPG_EXIF_APP8               0xFFE8
#define JPG_EXIF_APP9               0xFFE9
#define JPG_EXIF_APP10              0xFFEA
#define JPG_EXIF_APP11              0xFFEB
#define JPG_EXIF_APP12              0xFFEC
#define JPG_EXIF_APP13              0xFFED
#define JPG_EXIF_APP14              0xFFEE
#define JPG_EXIF_APP15              0xFFEF
#define JPG_EXIF_JPG0               0xFFF0
#define JPG_EXIF_JPG1               0xFFF1
#define JPG_EXIF_JPG2               0xFFF2
#define JPG_EXIF_JPG3               0xFFF3
#define JPG_EXIF_JPG4               0xFFF4
#define JPG_EXIF_JPG5               0xFFF5
#define JPG_EXIF_JPG6               0xFFF6
#define JPG_EXIF_JPG7               0xFFF7
#define JPG_EXIF_JPG8               0xFFF8
#define JPG_EXIF_JPG9               0xFFF9
#define JPG_EXIF_JPG10              0xFFFA
#define JPG_EXIF_JPG11              0xFFFB
#define JPG_EXIF_JPG12              0xFFFC
#define JPG_EXIF_JPG13              0xFFFD
#define JPG_EXIF_COM                0xFFFE

/* Exif Tag ID */

// IFD0 for Primary JPEG
#define IFD0_IMAGE_WIDTH            0x0100
#define IFD0_IMAGE_HEIGHT           0x0101
#define IFD0_MAKE                   0x010F
#define IFD0_MODEL                  0x0110
#define IFD0_ORIENTATION            0x0112
#define IFD0_X_RESOLUTION           0x011A
#define IFD0_Y_RESOLUTION           0x011B
#define IFD0_RESOLUTION_UNIT        0x0128
#define IFD0_SOFTWARE               0x0131
#define IFD0_DATE_TIME              0x0132
#define IFD0_ARTIST                 0x013B
#define IFD0_YCBCR_POSITION         0x0213
#define IFD0_COPYRIGHT              0x8298
#define IFD0_SEMINFO                0x8546
#define IFD0_EXIF_OFFSET            0x8769
#define IFD0_GPS_OFFSET             0x8825
#define IFD0_SENSINGMETHOD          0x9217
#define IFD0_XPTITLE                0x9C9B
#define IFD0_MAKERNOTESAFETY        0xC635

// GPS IFD Tag
#define GPS_VERSION                 0x0000
#define GPS_LATITUDE_REF            0x0001
#define GPS_LATITUDE                0x0002
#define GPS_LONGITUDE_REF           0x0003
#define GPS_LONGITUDE               0x0004
#define GPS_ALTITUDE_REF            0x0005
#define GPS_ALTITUDE                0x0006
#define GPS_TIME_STAMP              0x0007
#define GPS_SPEED_REF               0x000C
#define GPS_SPEED                   0x000D

// Exif IFD Tag
#define EXIFIFD_EXPOSURETIME        0x829A
#define EXIFIFD_FNUMBER             0x829D
#define EXIFIFD_EXPO_PROGRAM        0x8822
#define EXIFIFD_GPSINFO             0x8825
#define EXIFIFD_ISOSPEEDRATINGS     0x8827
#define EXIFIFD_VERSION             0x9000
#define EXIFIFD_DATETIMEORIGINAL    0x9003
#define EXIFIFD_DATETIMECREATE      0x9004
#define EXIFIFD_COMPONENTS          0x9101
#define EXIFIFD_SHUTTER_SPEED       0x9201
#define EXIFIFD_APERTURE            0x9202
#define EXIFIFD_BRIGHTNESS          0x9203
#define EXIFIFD_EXPOSUREBIAS        0x9204
#define EXIFIFD_MAX_APERTURE        0x9205
#define EXIFIFD_METERINGMODE        0x9207
#define EXIFIFD_LIGHTSOURCE         0x9208
#define EXIFIFD_FLASH               0x9209
#define EXIFIFD_FOCAL_LENGTH        0x920A
#define EXIFIFD_COLORSPACE          0xA001
#define EXIFIFD_PIXL_X_DIMENSION    0xA002
#define EXIFIFD_PIXL_Y_DIMENSION    0xA003
#define EXIFIFD_INTEROP_OFFSET      0xA005
#define EXIFIFD_SCENETYPE           0xA301
#define EXIFIFD_WHITEBLANCE         0xA403
#define EXIFIFD_SCENE_CAP_TYPE      0xA406
#define EXIFIFD_GAINCONTROL         0xA407
#define EXIFIFD_CONTRAST            0xA408
#define EXIFIFD_SATURATION          0xA409
#define EXIFIFD_SHARPNESS           0xA40A

// Interoperability IFD Tag
#define INTEROP_INDEX               0x0001
#define INTEROP_VERSION             0x0002
#define INTEROP_RELAIMG_FILEFMT     0x1000
#define INTEROP_RELAIMG_WIDTH       0x1001
#define INTEROP_RELAIMG_HEIGHT      0x1002

// IFD1 for Thumbnail
#define IFD1_IMAGE_WIDTH            0x0100
#define IFD1_IMAGE_HEIGHT           0x0101
#define IFD1_COMPRESSION            0x0103
#define IFD1_THUMBNAIL_OFFSET       0x0201
#define IFD1_THUMBNAIL_LENGTH       0x0202

#if (DSC_SUPPORT_BASELINE_MP_FILE)
// Index IFD for MPF
#define MPF_IDXIFD_MPF_VERSION      0xB000
#define MPF_IDXIFD_IMG_NUM          0xB001
#define MPF_IDXIFD_MP_ENTRY         0xB002
#define MPF_IDXIFD_IND_UNIQUE_ID_LIST   0xB003
#define MPF_IDXIFD_CAP_FRAME_NUM        0xB004

// MPF Entry ID
#define MPF_ENTRY_ID_PRIMARY_IMG    0
#define MPF_ENTRY_ID_LARGE_THUMB1   1
#define MPF_ENTRY_ID_LARGE_THUMB2   2
#endif

// IFD Index
#define IFD_IDX_IFD0                0
#define IFD_IDX_IFD1                1
#define IFD_IDX_GPSIFD              2
#define IFD_IDX_EXIFIFD             3
#define IFD_IDX_INTEROPIFD          4
#define IFD_IDX_MPF_INDEX_IFD       5
#define IFD_IDX_MPF_ATTR_IFD        6

// Exif Node Index
#define EXIF_NODE_ID_PRIMARY        0
#define EXIF_NODE_ID_LARGE_THUMB1   1
#define EXIF_NODE_ID_LARGE_THUMB2   2

#define DSC_MAX_EXIF_NODE_NUM       (3)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMP_EXIF_TIF_TAG_TYPE
{
    EXIF_TYPE_UNKNOWN    = 0,
    EXIF_TYPE_BYTE       = 1,
    EXIF_TYPE_ASCII      = 2,
    EXIF_TYPE_SHORT      = 3,
    EXIF_TYPE_LONG       = 4,
    EXIF_TYPE_RATIONAL   = 5,
    EXIF_TYPE_SBYTE      = 6,
    EXIF_TYPE_UNDEFINED  = 7,
    EXIF_TYPE_SSHORT     = 8,
    EXIF_TYPE_SLONG      = 9,
    EXIF_TYPE_SRATIONAL  = 10,
    EXIF_TYPE_FLOAT      = 11,
    EXIF_TYPE_DOUBLE     = 12
} MMP_EXIF_TIF_TAG_TYPE;

#endif //_MMP_EXIF_INC_H_
