///////////////////////////////////////////////////////////////////////////////////////////////////
// @file   drvJPG_AddHeader.h
// @author MStar Semiconductor Inc.
// @brief  header file of drvJPG_AddHeader.c
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVJPG_ADDHEADER_H
#define _DRVJPG_ADDHEADER_H

#include "mdl_imgcapture_main.h"
//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------

// definition of DQT
#define QT_Y 0
#define QT_C 1
#define PRECISION_8BITS 0

// definition of DHT
#define HT_Y 0
#define HT_C 1
#define DC_TAB 0
#define AC_TAB 1

#define TIFF_HEADER_SIZE     8
#define FIELD_NUM_SIZE       2
#define FIELD_SIZE           12
#define NEXT_IFD_OFFSET_SIZE 4

// type
#define BYTE_TYPE       0x0001
#define ASCII_TYPE      0x0002
#define SHORT_TYPE      0x0003
#define LONG_TYPE       0x0004
#define RATIONAL_TYPE   0x0005
#define CUSTOM_TYPE     0x0007
#define SLONG_TYPE      0x0009
#define SRATIONAL_TYPE  0x000A

//TagID of 0th IFD (Main data)
#define MAKE  0x010F
#define MODEL 0x0110
#define ORIENTATION 0x0112
#define X_RESOLUTION 0x011A
#define Y_RESOLUTION 0x011B
#define RESOLUTION_UNIT   0x0128
#define YCBCR_POSITIONING 0x0213
#define EXIF_IFD_POINTER 0x8769
#define GPS_IFD_POINTER 0x8825

//TagID of Exif IFD
#define EXPOSURE_TIME 0x829A
#define F_NUMBER 0x829D
#define ISO_SPEED_RATINGS 0x8827
#define EXIF_VERSION 0x9000
#define DATE_TIME_ORIGINAL 0x9003
#define DATE_TIME_DIGITIZED 0x9004
#define COMPONENT_CONFIGURATION 0x9101
#define SHUTTER_SPEED_VALUE 0x9201
#define APERTURE_VALUE 0x9202
#define EXPOSURE_BIAS_VALUE 0x9204
#define METERING_MODE 0x9207
#define LIGHT_SOURCE 0x9208
#define FLASH 0x9209
#define FOCAL_LENGTH 0x920A
#define FLASHPIX_VERSION 0xA000
#define COLOR_SPACE 0xA001
#define PIXEL_X_DIMENSION 0xA002
#define PIXEL_Y_DIMENSION 0xA003
#define CUSTOM_RENDERED 0xA401
#define EXPOSURE_MODE 0xA402
#define WHITE_BALANCE 0xA403
#define DIGITAL_ZOOM_RATIO 0xA404
#define SCENE_CAPTURE_TYPE 0xA406
#define GAIN_CONTROL 0xA407
#define MAKER_NOTE 0x927C

//TagID of GPS IFD
#define GPS_VERSION_ID      0x00
#define GPS_LATITUDE_REF    0x01
#define GPS_LATITUDE        0x02
#define GPS_LONGITUDE_REF   0x03
#define GPS_LONGITUDE       0x04
#define GPS_ALTITUDE_REF    0x05
#define GPS_ALTITUDE        0x06
#define GPS_TIMESTAMP       0x07
#define GPS_SATELLITES      0x08
#define GPS_STATUS          0x09
#define GPS_MEASURE_MODE    0x0A
#define GPS_DOP             0x0B
#define GPS_SPEED_REF       0x0C
#define GPS_SPEED           0x0D
#define GPS_TRACK_REF       0x0E
#define GPS_TRACK           0x0F
#define GPS_MAPDATUM        0x12
#define GPS_DATESTAMP       0x1D

//TagID of 1th IFD (thumbnail data)
#define COMPRESSION 0x0103
#define JPEG_INTERCHANGEFORMAT 0x0201
#define JPEG_INTERCHANGEFORMAT_LENGTH 0x0202

#if 0
typedef enum {
  MS_SOF0  = 0xc0,
  MS_SOF1  = 0xc1,
  MS_SOF2  = 0xc2,
  MS_SOF3  = 0xc3,
  MS_SOF5  = 0xc5,
  MS_SOF6  = 0xc6,
  MS_SOF7  = 0xc7,

  MS_JPG   = 0xc8,
  MS_SOF9  = 0xc9,
  MS_SOF10 = 0xca,
  MS_SOF11 = 0xcb,

  MS_SOF13 = 0xcd,
  MS_SOF14 = 0xce,
  MS_SOF15 = 0xcf,

  MS_DHT   = 0xc4,

  MS_DAC   = 0xcc,

  MS_RST0  = 0xd0,
  MS_RST1  = 0xd1,
  MS_RST2  = 0xd2,
  MS_RST3  = 0xd3,
  MS_RST4  = 0xd4,
  MS_RST5  = 0xd5,
  MS_RST6  = 0xd6,
  MS_RST7  = 0xd7,

  MS_SOI   = 0xd8,
  MS_EOI   = 0xd9,
  MS_SOS   = 0xda,
  MS_DQT   = 0xdb,
  MS_DNL   = 0xdc,
  MS_DRI   = 0xdd,
  MS_DHP   = 0xde,
  MS_EXP   = 0xdf,

  MS_APP0  = 0xe0,
  MS_APP1  = 0xe1,
  MS_APP2  = 0xe2,
  MS_APP3  = 0xe3,
  MS_APP4  = 0xe4,
  MS_APP5  = 0xe5,
  MS_APP6  = 0xe6,
  MS_APP7  = 0xe7,
  MS_APP8  = 0xe8,
  MS_APP9  = 0xe9,
  MS_APP10 = 0xea,
  MS_APP11 = 0xeb,
  MS_APP12 = 0xec,
  MS_APP13 = 0xed,
  MS_APP14 = 0xee,
  MS_APP15 = 0xef,

  MS_JPG0  = 0xf0,
  MS_JPG13 = 0xfd,
  MS_COM   = 0xfe,
  MS_START = 0xff,

  MS_TEM   = 0x01,

  MS_ERROR = 0x100
}MDLJPE_MARKER;
#endif

typedef struct _FIELD_ENTRY
{
    u16 u16Tag;
    u16 u16Type;
    u32 u32Count;
    u32 u32ValueorOffset;
}FIELD_ENTRY;

typedef struct
{
	u8  year;			///< Year value after 1900, value range is 0~255
	u8  month;			///< Month, value range is 1~12
	u8  day;			///< Day, value range is 1~31
	u8  hour;			///< Hour, value range is 0~23
	u8  minute;			///< Minute, value range is 0~59
	u8  second;			///< Second, value range is 0~59
}MDLJPE_DateTime_t;	

typedef struct _MDLJPE_HEADERINFO {
    u8      u8headerFormat; // 0:EXIF, 1:JFIF
    u8      *pu8HeaderBuf;
    u16     u16HeaderBufOffset;
    u16     u16Config;
    u8      *pu8ThumbnailBuf;
    u32     u32ThumbnailBufSize;
    u8      u8Qscale;
    u32     u32BSChecksum;
    u16     u16OriImg_W;
    u16     u16OriImg_H;
    u8      *pu8MakeNoteBuf;
    u32     u32MakeNoteBufLen;
    u16     u16ThumbnailOffset;
    u8      u8enThumbnail;
    u16     *YQTable;       //pointer to Y Qtable of 64 entries
    u16     *CQTable;       //pointer to C Qtable of 64 entries
    MDLJPE_DateTime_t MDLJPE_DateTime; //Date/Time
    u8      exif_orientation;
    u8      u8JpegFormat;  // 0: 422, 1:420
} MDLJPE_HEADERINFO;



//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
#if 1
MSMIMGCAPErrcode_e MDLJPE_AddHeader(MDLJPE_HEADERINFO *pInfo);
#else
MSMIMGCAPErrcode_e JPE_Header_AddHeader(PJPE_PARAM pJpe_param, JPE_GLOBAL *pGlobal);
#endif
#endif //_DRVJPG_ADDHEADER_H
