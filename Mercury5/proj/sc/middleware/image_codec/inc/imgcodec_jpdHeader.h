#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION

//For --------Montage Image Decoder-------------//
#ifndef _MW_JPDHEADER_H
#define _MW_JPDHEADER_H

#include "imgcodec_jpdBaiscFun.h"

#if 0
#define JPDStatusCheck(status)
#else
#define JPDStatusCheck(status) { \
                                   if(status!= IMAGE_SUCCESS) \
                                   {\
                                       img_error2("JPD (%d) status=%x\n",__LINE__,status);\
                                       return status; \
                                   }\
                               }
#endif

//#define JPD_HEADER_DBG //dump header table for debugging

static const int BytesPerFormat[] = {0,1,1,2,4,8,1,1,2,4,8,4,8};
#define NUM_FORMATS 12

#define FMT_BYTE       1
#define FMT_STRING     2
#define FMT_USHORT     3
#define FMT_ULONG      4
#define FMT_URATIONAL  5
#define FMT_SBYTE      6
#define FMT_UNDEFINED  7
#define FMT_SSHORT     8
#define FMT_SLONG      9
#define FMT_SRATIONAL 10
#define FMT_SINGLE    11
#define FMT_DOUBLE    12

#define JPD_Max_Resoltion_Width    8176
#define JPD_Max_Resoltion_Height   8176
#define JPD_Min_Resoltion_Width    32
#define JPD_Min_Resoltion_Height   32
#define MJPD_SRAM_BITSTREAM_BUFSIZE         4096
#define JPD_SRAM_BITSTREAM_BUFSIZE          16384 //2+4818+134+19+420+14+3488+1=8896

#define JPD_8x8MAXWIDTH_SIZE                512 //JPD_Max_Resoltion_Width

#define MJPD_SRAM_ICP_BUFSIZE               (720*16*2*2)
#define JPD_SRAM_ICP_BUFSIZE                (JPD_8x8MAXWIDTH_SIZE * 2 * 8 * 2 * 2)//encode also use the same buffer; before mode gua
#define JPD_SRAM_HEADER_ARRAYSIZE           4096
#define JPD_SRAM_GROUPTABLE_BUFSIZE         (16*4*4)
#define JPD_SRAM_DC_GROUPTABLE_BUFSIZE      (4*4)
#define JPD_SRAM_SYMBOLTABLE_BUFSIZE        (256/4*2*4)
#define JPD_SRAM_MEM_STACK_BUFSIZE          (5*1024)
#define JPGD_INBUFSIZE_LIMIT                150*1024  //jpeg file Max size
#define JPGD_INBUFSIZE                      160*1024  //jpeg file Max size
#define JPD_FILE_LIMIT                      64*1024   //64k
#define HALF_FILE_POOL_SIZE                 JPD_FILE_POOL_SIZE/2
#define JPD_STRUCTURE_SIZE                  12*1024
#define JPD_STACKBUF_SIZE                   5*1024
#define JPD_BACKDECODE_STACKSIZE            10*1024
#define JPD_DRAM_ICP_BUFSIZE                (1024 * 8 * 2 * 2)
//#define JPD_DRAM_BITSTREAM_BUFSIZE          16384 //2+4818+134+19+420+14+3488+1=8896
#define JPD_DRAM_BITSTREAM_BUFSIZE          1024*1024*2 //CModel is defined to decode maximum 2M file size...
#define JPD_SRAM_CCR_BUFSIZE                (8*1024)
#define JPEGDEC_MEM_BITSTREAM_BUFSIZE      16384 //2+4818+134+19+420+14+3488+1=8896
#define HALF_JPD_MEM_BITSTREAM_BUFSIZE     JPEGDEC_MEM_BITSTREAM_BUFSIZE/2
#define JPEGDEC_PRG_ICPOUT_BUSIZE          (0)
#define JPEGDEC_PRG_BITSTREAM_BUFSIZE      (50*1024)//(16384) //idct RLV buffer
#define JPEGDEC_PRG_DUMMYBUFSIZE           64 * 4 //For a macro block
#define JPEGDEC_PRG_ICP_BUFSIZE            (1024 * 16 * 2)//encode also use the same buffer; before mode gua
#define JPEGDEC_PRG_BUFSIZE                (300*1024)//encode also use the same buffer; before mode gua
#define JpegDecPRGBitstreamBufSize         JPEGDEC_PRG_BITSTREAM_BUFSIZE
#define JpegDecPRGICPBufSize               JPEGDEC_PRG_ICP_BUFSIZE
#define JpegDecPRGBufSize                  JPEGDEC_PRG_BUFSIZE
#define ALIGNMENT_RESERVED                 128
#define JpgProgISramHeapSize               (32*1024 + 32) //B3 just for IDCT buffer, no JPD output buffer
/*
|------------|-------|
| BitStream  |  150K |
|------------|-------|
| SWDecode   |  150K |
|------------|-------|
| HWIDCT     |  50K  |
|------------|-------|
| JPDOutput  |  32K  |
|------------|-------|
*/


/* Describes tag values */

#define TAG_EXIF_VERSION      0x9000
#define TAG_EXIF_OFFSET       0x8769
#define TAG_INTEROP_OFFSET    0xa005
#define TAG_GPS_OFFSET		  0x8825

#define TAG_MAKE              0x010F
#define TAG_MODEL             0x0110

#define TAG_ORIENTATION       0x0112
#define TAG_XRESOLUTION       0x011A
#define TAG_YRESOLUTION       0x011B
#define TAG_RESOLUTIONUNIT    0x0128

#define TAG_EXPOSURETIME      0x829A
#define TAG_FNUMBER           0x829D

#define TAG_SHUTTERSPEED      0x9201
#define TAG_APERTURE          0x9202
#define TAG_BRIGHTNESS        0x9203
#define TAG_MAXAPERTURE       0x9205
#define TAG_FOCALLENGTH       0x920A

#define TAG_DATETIME_ORIGINAL 0x9003
#define TAG_USERCOMMENT       0x9286

#define TAG_SUBJECT_DISTANCE  0x9206
#define TAG_FLASH             0x9209

#define TAG_FOCALPLANEXRES    0xa20E
#define TAG_FOCALPLANEYRES    0xa20F
#define TAG_FOCALPLANEUNITS   0xa210
#define TAG_EXIF_IMAGEWIDTH   0xA002
#define TAG_EXIF_IMAGELENGTH  0xA003

/* the following is added 05-jan-2001 vcs */
#define TAG_EXPOSURE_BIAS     0x9204
#define TAG_WHITEBALANCE      0x9208
#define TAG_METERING_MODE     0x9207
#define TAG_EXPOSURE_PROGRAM  0x8822
#define TAG_ISO_EQUIVALENT    0x8827
#define TAG_COMPRESSION_LEVEL 0x9102

#define TAG_THUMBNAIL_OFFSET  0x0201
#define TAG_THUMBNAIL_LENGTH  0x0202

#define TAG_GPS_VERSION_ID    0x0
#define TAG_GPS_LATITUDE_REF  0x1 //indicates whether the latitude is north or south latitude, 'N','S'
#define TAG_GPS_LATITUDE      0x2
#define TAG_GPS_LONGITUDE_REF 0x3 //indicates whether the longitude is east or west longtitude, 'E','W'
#define TAG_GPS_LONGITUDE     0x4
#define TAG_GPS_ALTITUDE_REF  0x5
#define TAG_GPS_ALTITUDE	  0x6
#define TAG_GPS_TIMESTAMP     0x7
#define TAG_GPS_SATELLITES    0x8
#define TAG_GPS_STATUS        0x9
#define TAG_GPS_MEAS_MODE     0xA  //'2' means two dimensions, '3' means three dimensions.
#define TAG_GPS_DOP           0xB  //(DOP-->data degree of precision)
#define TAG_GPS_SPEED_REF     0xC  //receiver speed of movement
#define TAG_GPS_SPEED		  0xD  //indicates the speed of GPS receiver
#define TAG_GPS_TRACK_REF     0xE  // 'T' denotes the true direction, 'M' is magnetic direction
#define TAG_GPS_TRACK		  0xF
#define TAG_GPS_IMGDIR_REF    0x10
#define TAG_GPS_IMGDIR		  0x11
#define TAG_GPS_MAPDATUM      0x12
#define TAG_GPS_DSTLAT_REF    0x13
#define TAG_GPS_DSTLAT		  0x14
#define TAG_GPS_DSTLONG_REF   0x15
#define TAG_GPS_DSTLONG		  0x16
#define TAG_GPS_DSTBEAR_REF   0x17
#define TAG_GPS_DSTBEAR		  0x18
#define TAG_GPS_DSTDIST_REF   0x19
#define TAG_GPS_DSTDIST		  0x1A
#define TAG_GPS_PROC_METHOD	  0x1B
#define TAG_GPS_AREA_INFO     0x1C
#define TAG_GPS_DATA_STAMP    0x1D
#define TAG_GPS_DIFF          0x1E

#define MAX_GPSDatum_Len      100
#define MAX_COMMENT 1000
#define MAX_SECTIONS 20

/* Return value is one of: */
#define JPEG_SUSPENDED		0 /* Suspended due to lack of input data */
#define JPEG_HEADER_OK		1 /* Found valid image datastream */
#define JPEG_HEADER_TABLES_ONLY	2 /* Found valid table-specs-only datastream */

/* #define JPEG_SUSPENDED	0    Suspended due to lack of input data */
#define JPEG_REACHED_SOS	1 /* Reached start of new scan */
#define JPEG_REACHED_EOI	2 /* Reached end of image */
#define JPEG_ROW_COMPLETED	3 /* Completed one iMCU row */
#define JPEG_SCAN_COMPLETED	4 /* Completed last iMCU row of a scan */

/* If you pass require_image = TRUE (normal case), you need not check for
 * a TABLES_ONLY return code; an abbreviated file will cause an error exit.
 * JPEG_SUSPENDED is only possible if you use a data source module that can
 * give a suspension return (the stdio source module doesn't).
 */
#define DCTSIZE		        8	/* The basic DCT block is 8x8 samples */
#define DCTSIZE2	        64	/* DCTSIZE squared; # of elements in a block */
#define NUM_QUANT_TBLS      4	/* Quantization tables are numbered 0..3 */
#define NUM_HUFF_TBLS       4	/* Huffman tables are numbered 0..3 */
#define MAX_COMPS_IN_SCAN   4	/* JPEG limit on # of components in one scan */
#define MAX_SAMP_FACTOR     4	/* JPEG limit on sampling factors */

#define MCU_FACTOR                 8
//#define SupportUserCommet

#define JPD_FILE_POOL_SIZE                  (100*1024)
#define JPD_HEADER_PASER_MAX_SIZE	        (300*1024)
#define JPD_HEADER_PASER_MARK_MAX_LEN       (64*1024) //Max 2^16 bytes

typedef enum {			// JPEG marker codes //
  M_SOF0  = 0xc0,
  M_SOF1  = 0xc1,
  M_SOF2  = 0xc2,
  M_SOF3  = 0xc3,

  M_SOF5  = 0xc5,
  M_SOF6  = 0xc6,
  M_SOF7  = 0xc7,

  M_JPG   = 0xc8,
  M_SOF9  = 0xc9,
  M_SOF10 = 0xca,
  M_SOF11 = 0xcb,

  M_SOF13 = 0xcd,
  M_SOF14 = 0xce,
  M_SOF15 = 0xcf,

  M_DHT   = 0xc4,

  M_DAC   = 0xcc,

  M_RST0  = 0xd0,
  M_RST1  = 0xd1,
  M_RST2  = 0xd2,
  M_RST3  = 0xd3,
  M_RST4  = 0xd4,
  M_RST5  = 0xd5,
  M_RST6  = 0xd6,
  M_RST7  = 0xd7,

  M_SOI   = 0xd8,
  M_EOI   = 0xd9,
  M_SOS   = 0xda,
  M_DQT   = 0xdb,
  M_DNL   = 0xdc,
  M_DRI   = 0xdd,
  M_DHP   = 0xde,
  M_EXP   = 0xdf,

  M_APP0  = 0xe0,
  M_APP1  = 0xe1,
  M_APP2  = 0xe2,
  M_APP3  = 0xe3,
  M_APP4  = 0xe4,
  M_APP5  = 0xe5,
  M_APP6  = 0xe6,
  M_APP7  = 0xe7,
  M_APP8  = 0xe8,
  M_APP9  = 0xe9,
  M_APP10 = 0xea,
  M_APP11 = 0xeb,
  M_APP12 = 0xec,
  M_APP13 = 0xed,
  M_APP14 = 0xee,
  M_APP15 = 0xef,

  M_JPG0  = 0xf0,
  M_JPG13 = 0xfd,
  M_COM   = 0xfe,

  M_TEM   = 0x01,

  M_ERROR = 0x100
} JPEG_MARKER;


typedef enum {
	JCS_UNKNOWN,		/* error/unspecified */
	JCS_GRAYSCALE,		/* monochrome */
	JCS_RGB,		/* red/green/blue */
	JCS_YCbCr,		/* Y/Cb/Cr (also known as YUV) */
	JCS_CMYK,		/* C/M/Y/K */
	JCS_YCCK		/* Y/Cb/Cr/K */
} J_COLOR_SPACE;

//the original one is the Y=1,Cb=2,Cr=3
typedef enum
{
    comp_id_Y = 0,
    comp_id_Cb,
    comp_id_Cr,
} J_Comp_Id;


typedef enum
{
    NonMotor = 0,
    Motor = 1,
} MotorOrder;

typedef struct
{
    u16 Year;
    u8  Month;
    u8  Day;
    u8  Hour;
    u8  Minute;
    u8  Second;
} FileDateTime;


typedef struct tag_GPSInfo
{
	u8  GPS_Ver_ID[4];
	u8  GPS_LAT_REF[2];
	u32 GPS_LATITUDE[6];
	u8  GPS_LONG_REF[2];
	u32 GPS_LONGITUDE[6];
	u8  GPS_ALTI_REF;
	u32 GPS_ALTITUDE[6];
	u32 GPS_TIME_STAMP[6];
	//GPS Satellite...
	u8  GPS_STATUS[2];
	u8  GPS_Meas_Mode[2];
	u32 GPS_DOP;
	u8  GPS_SPEED_REF[2];
	u32 GPS_SPEED;
	u8  GPS_TRACK_REF[2];
	u32 GPS_TRACK;
	u8  GPS_ImgDir_REF[2];
	u32 GPS_ImgDir;
	u8  GPS_MapDatum[MAX_GPSDatum_Len];
	u8  GPS_DSTLAT_REF[2];
	u32 GPS_DSTLATITUDE[6];
	u8  GPS_DSTLONG_REF[2];
	u32 GPS_DSTLONGITUDE[6];
	u8  GPS_DSTBEAR_REF[2];
	u32 GPS_DSTBEAR;
	u8  GPS_DSTDIST_REF[2];
	u32 GPS_DSTDIST;
	//GPS Processing Method
	//GPS Area Information
	u8  GPS_DATASTAMP[11];
	u16 GPS_DIFFER;
} GPS_TAG_INFO;

typedef struct tag_ExifInfo
{
	s8    Version      [5];
    s8    CameraMake   [32];
    s8    CameraModel  [40];
    s8    DateTime     [20];
    FileDateTime DateTimes;
    u32   Height, Width;
    u16   Orientation;
    s32   IsColor;
    s32   Process;
    s32   FlashUsed;
    u32   FocalLength[2];
    u32   ExposureTime[2];
    u32   ApertureFNumber[2];
    u32   Distance[2];
    //float CCDWidth;
    s32   ExposureBias[2];
    u16   Whitebalance;
    u16   MeteringMode;
    u16   ExposureProgram;
    u16   ISOequivalent;
    u32   CompressionLevel[2];
	u32   FocalplaneXRes[2];
	u32   FocalplaneYRes[2];
	u16   FocalplaneUnits;
	u32   Xresolution[2];
	u32   Yresolution[2];
	u16   ResolutionUnit;
	s32   Brightness[2];
#ifdef SupportUserCommet
    s8    Comments[MAX_COMMENT];
#endif

    u8*   ThumbnailPointer;  /* Pointer at the thumbnail */
    u32   ThumbnailSize;     /* Size of thumbnail. */

	bool  IsExif;
} EXIFINFO;

typedef struct tag_Section_t{
    u8*      Data;
    s32      Type;
    u32      Size;
} Section_t;

/* Basic info about one component (color channel). */

/* Types for JPEG compression parameters and working tables. */

/* DCT coefficient quantization tables. */

typedef struct
{
    /* This array gives the coefficient quantizers in natural array order
    * (not the zigzag order in which they are stored in a JPEG DQT marker).
    * CAUTION: IJG versions prior to v6a kept this array in zigzag order.
    */
    u8 quantval[DCTSIZE2];	/* quantization step for each coefficient */
    /* This field is used only during compression.  It's initialized FALSE when
    * the table is created, and set TRUE when it's been output to the file.
    * You could suppress output of a table by setting this to TRUE.
    * (See jpeg_suppress_tables for an example.)
    */
    u8 sent_table;		/* TRUE when table has been output */
} JQUANT_TBL;

/* Huffman coding tables. */

typedef struct
{
  /* These two fields directly represent the contents of a JPEG DHT marker */
  u8 bits[17];		/* bits[k] = # of symbols with codes of */
				/* length k bits; bits[0] is unused */
  u8 huffval[256];		/* The symbols, in order of incr code length */
  /* This field is used only during compression.  It's initialized FALSE when
   * the table is created, and set TRUE when it's been output to the file.
   * You could suppress output of a table by setting this to TRUE.
   * (See jpeg_suppress_tables for an example.)
   */
  u8 sent_table;		/* TRUE when table has been output */
} JHUFF_TBL;


typedef struct
{
  /* These values are fixed over the whole image. */
  /* For compression, they must be supplied by parameter setup; */
  /* for decompression, they are read from the SOF marker. */
  u8 component_id;		/* identifier for this component (0..255) */
  u8 component_index;		/* its index in SOF or cinfo->comp_info[] */
  u8 h_samp_factor;		/* horizontal sampling factor (1..4) */
  u8 v_samp_factor;		/* vertical sampling factor (1..4) */
  u8 quant_tbl_no;		/* quantization table selector (0..3) */
  /* These values may vary between scans. */
  /* For compression, they must be supplied by parameter setup; */
  /* for decompression, they are read from the SOS marker. */
  /* The decompressor output side may not use these variables. */
  u8 dc_tbl_no;		/* DC entropy table selector (0..3) */
  u8 ac_tbl_no;		/* AC entropy table selector (0..3) */

  /* Remaining fields should be treated as private by applications. */

  /* These values are computed during compression or decompression startup: */
  /* Component's size in DCT blocks.
   * Any dummy blocks added to complete an MCU are not counted; therefore
   * these values do not depend on whether a scan is interleaved or not.
   */
  u32 width_in_blocks;
  u32 height_in_blocks;
  /* Size of a DCT block in samples.  Always DCTSIZE for compression.
   * For decompression this is the size of the output from one DCT block,
   * reflecting any scaling we choose to apply during the IDCT step.
   * Values of 1,2,4,8 are likely to be supported.  Note that different
   * components may receive different IDCT scalings.
   */
  u32 DCT_scaled_size;
  /* The downsampled dimensions are the component's actual, unpadded number
   * of samples at the main buffer (preprocessing/compression interface), thus
   * downsampled_width = ceil(image_width * Hi/Hmax)
   * and similarly for height.  For decompression, IDCT scaling is included, so
   * downsampled_width = ceil(image_width * Hi/Hmax * DCT_scaled_size/DCTSIZE)
   */
  u32 downsampled_width;	 /* actual width in samples */
  u32 downsampled_height; /* actual height in samples */
  /* This flag is used only for decompression.  In cases where some of the
   * components will be ignored (eg grayscale output from YCbCr image),
   * we can skip most computations for the unused components.
   */
  u8 component_needed;	/* do we need the value of this component? */

  /* These values are computed before starting a scan of the component. */
  /* The decompressor output side may not use these variables. */
  u32 MCU_width;		/* number of blocks per MCU, horizontally */
  u32 MCU_height;		/* number of blocks per MCU, vertically */
  u32 MCU_blocks;		/* MCU_width * MCU_height */
  u32 MCU_sample_width;		/* MCU width in samples, MCU_width*DCT_scaled_size */
  u32 last_col_width;		/* # of non-dummy blocks across in last MCU */
  u32 last_row_height;		/* # of non-dummy blocks down in last MCU */

  /* Saved quantization table for component; NULL if none yet saved.
   * See jdinput.c comments about the need for this information.
   * This field is currently used only for decompression.
   */
  JQUANT_TBL * quant_table;

  /* Private per-component storage for DCT or IDCT subsystem. */
  void *dct_table;
} jpeg_component_info;


typedef struct _jpd_header_
{
    EXIFINFO ExifInfo;
    EXIFINFO *m_exifinfo;
    GPS_TAG_INFO GPSInfo;
	GPS_TAG_INFO *m_GPSInfo;

    //Local Variable//
    s32 JPDReadFlag; //Jason
    u8  single_byte;
    u16 single_word;
    u8  *JPD_Pool;
    u32 FileTotalSize; //s32 FileTotalSize; to fix lint error in imgcodec_jpdHeader.c
    u32 ThumbnailSize;
    u32 length_of_file;
    u32 bytes_in_buffer;
    u32 FilePoolSize;
    u8  *SrcAddr;
    u8  *Memory;
    u32 position;
	u8 FilePoolLoopIndex;
    u32 JFIF_Position;
    u32 ThumbNail_Start_Position;
    s32 Ori_Position;
    u32 unread_marker;
    u8  saw_SOI;
    u8  saw_SOF;
    u8  is_progressive;
    u8  is_EXIF;
    u8  ParseEXIF_Correct;
    u8  is_Thumbnail;
    u8  data_precision;
    u8  progressive_mode;	/* TRUE if SOFn specifies progressive mode */
    u8  arith_code;		/* TRUE=arithmetic coding, FALSE=Huffman */
    u8  is_srcFromBuf;
    u8  is_motionJpg;
	u8  has_DHT;

	u8  FrameMode;

    JQUANT_TBL quant_tbl[NUM_QUANT_TBLS];
    /* ptrs to coefficient quantization tables, or NULL if not defined */

    JHUFF_TBL dc_huff_tbl[NUM_HUFF_TBLS];
    JHUFF_TBL ac_huff_tbl[NUM_HUFF_TBLS];
    /* ptrs to Huffman coding tables, or NULL if not defined */

    u8 hufftbl_index[10];
    u8 hufftbl_index_cnt;


    u32 restart_interval; /* MCUs per restart interval, or 0 for no restart */

    /* These fields record data obtained from optional markers recognized by
    * the JPEG library.
    */
    u8  saw_JFIF_marker;	/* TRUE iff a JFIF APP0 marker was found */
    /* Data copied from JFIF marker; only valid if saw_JFIF_marker is TRUE: */
    u8  JFIF_major_version;	/* JFIF version number */
    u8  JFIF_minor_version;
    u8  density_unit;		/* JFIF code for pixel size units */
    u16 X_density;		/* Horizontal pixel density */
    u16 Y_density;		/* Vertical pixel density */
    u8  saw_Adobe_marker;	/* TRUE iff an Adobe APP14 marker was found */
    u8  Adobe_transform;	/* Color transform code from Adobe marker */

    u8  CCIR601_sampling;	/* TRUE=first samples are cosited */

    u8  MotorolaOrder;

    u16 image_width;	/* nominal image width (from SOF marker) */
    u16 image_height;	/* nominal image height */
    u16 round_width;
    u16 round_height;
    u16 crop_width;
    u16 crop_height;
    u16 JPD_Width;
    u16 JPD_Height;

    u32 num_components;		/* # of color components in JPEG image */
    J_COLOR_SPACE jpeg_color_space; /* colorspace of JPEG image */

    jpeg_component_info comp_info_phy[MAX_COMPS_IN_SCAN];
    jpeg_component_info *comp_info;
    u32 discarded_bytes;

    u32 Ss, Se, Ah, Al;		/* progressive JPEG parameters for scan */
    u32 next_restart_num;
    u32 input_scan_number;
    u32 comps_in_scan;
    jpeg_component_info *cur_comp_info[MAX_COMPS_IN_SCAN];

    u32 YDC_Num,YAC_Num,CbDC_Num,CbAC_Num;

    u8  y_h_samp_factor;		/* horizontal sampling factor (1..4) */
    u8  y_v_samp_factor;		/* vertical sampling factor (1..4) */
    u16 IDCTType;

    void *pThumb;

    u8   ThumbNailReadFlag;

    u8   ROI_Enable;
    u16  ROI_Width, ROI_Height;
    u16  ROI_XStartPos, ROI_YStartPos;

    u32  SymbolTableLength_YAC;
    u32  SymbolTableLength_UVAC;
    u32  GroupTableLength_YDC;
    u32  GroupTableLength_UVDC;
    u32  *GroupTable;
    u8   *DC_GroupTable;
    u8   *SymbolTable;

    u8  *JPD_DstBuf0;
    u8  *JPD_DstBuf1;
    u8  *ICP_SrcBuf0;
    u8  *ICP_SrcBuf1;
    u8  *JpegDecThumbnailBuf;

    u8  *SrcFloorAddr;
    u8  *SrcCeilAddr;

    u8   *JPD_Src_HighBuf;
    u8   *JPD_Src_LowBuf;
    u32  BufferSize;

    struct _jpd_header_ *pThumbHeader;

    ImgFSFunc_st *pFuncFS; //Unify IO

}JPD_Header;

#ifdef JPDCModel
//Jason Testing++ Big3 ImageInfo format
//===============================================
// formats
typedef enum
{
	IMAGE_FORMAT_ERR = 0,
	IMAGE_FORMAT_BMP,
	IMAGE_FORMAT_PNG,
	IMAGE_FORMAT_GIF,
	IMAGE_FORMAT_JPG,
    IMAGE_FORMAT_GIFA,
	IMAGE_FORMAT_MMP,
    IMAGE_FORMAT_WAVBMP,
    IMAGE_FORMAT_WAPBMP,
    IMAGE_FORMAT_TOTAL,
}IMGCODEC_FORMAT,*PIMGCODEC_FORMAT;

//===============================================

//===============================================
// information structure
typedef enum
{
    IMAGE_LATITUDE_NORTH,  /**< North latitude*/
    IMAGE_LATITUDE_SOUTH,  /**< South latitude*/
    IMAGE_LATITUDE_NONE
} IMGCODEC_GPS_LATITUDE;

typedef enum
{
    IMAGE_LONGITUDE_EAST, /**< East latitude*/
    IMAGE_LONGITUDE_WEST,
    IMAGE_LONGITUDE_NONE
} IMGCODEC_GPS_LONGITUDE;

typedef struct {
  u32           numerator;       /**< numerator of gps data */
  u32           denominator;     /**< denominator of gps data */
} Imgage_gpsData_t;

typedef struct {
  IMGCODEC_GPS_LATITUDE   latitude;       /**< Latitude of GPS info in EXIF */
  Imgage_gpsData_t        latDegree;      /**< Degree of latitude */
  Imgage_gpsData_t        latMin;         /**< Minute of latitude */
  Imgage_gpsData_t        latSec;         /**< Second of latitude */

  IMGCODEC_GPS_LONGITUDE  longitude;      /**< longitude of GPS info in EXIF */
  Imgage_gpsData_t        lonDegree;      /**< Degree of longitude */
  Imgage_gpsData_t        lonMin;         /**< Minute of longitude */
  Imgage_gpsData_t        lonSec;         /**< Second of longitude */
} Imgage_EXIF_t;

typedef struct _st_image_information_
{
    IMGCODEC_FORMAT format;     // file format
    u16             width_p;    // image width
    u16             height_p;   // image height
    u32             TotalFrames;
    u32             size_p;     // bytes of entire file.
    Imgage_EXIF_t   exifInfo;   // EXIF information
    u8              *pFileName;
    u16             fileNameLens;
    u8              orientation; /*Jpeg orientation tag*/
    bool            bIsFile;
    bool            bIsProgressive;
}Image_Info_t;
//Jason Testing-- Big3 ImageInfo format
#endif //JPDCModel
s32 get_default_dht (JPD_Header *pJPDHeader);
s32 read_markers (JPD_Header *pJPDHeader);
void default_decompress_parms (JPD_Header *pJPDHeader);

image_Errmsg MwJpgHeaderParse(ImageFSFunc_t *pImgFSFun, JPD_Header *pJPDHeader, u8 *BitStrPtr, u32 Size);

void jpg_set_sharebuffer(void);

#endif //_MW_JPDHEADER_H
#endif

