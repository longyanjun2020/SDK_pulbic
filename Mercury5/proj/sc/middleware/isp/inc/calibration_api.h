#ifndef __CALIBRATION_API_HEADER_H__
#define __CALIBRATION_API_HEADER_H__

//#include "MsTypes.h"

typedef unsigned char       u8;
typedef signed   char       s8;
typedef unsigned short      u16;
typedef signed   short      s16;
typedef unsigned int        u32;
typedef signed   int        s32;
typedef unsigned long long  u64;
typedef signed   long long  s64;

#define CALI_DATA_HDR_VER_1   0x00000001
#define CALI_DATA_HDR_VER_2   0x00000002

#define CALI_Data_TYPE_AWB          0x10000
#define CALI_Data_TYPE_SHADING      0x20000
#define CALI_Data_TYPE_SENSOR       0x30000
#define CALI_Data_TYPE_AE           0x40000
#define CALI_Data_TYPE_OBC          0x50000
#define CALI_Data_TYPE_DEFECT_PIXEL 0x60000

#define CALIBRATION_DATA_VERSION                (3)

#define CALI_OBC_WEIGHT_X_NUM                   (3)
#define CALI_OBC_WEIGHT_Y_NUM                   (3)
#define CALI_OBC_WEIGHT_NUM                     (CALI_OBC_WEIGHT_X_NUM * CALI_OBC_WEIGHT_Y_NUM)
#define CALI_OBC_GAIN_INDEX_NUM                 (16)
#define CALI_OBC_GAIN_BASE                      (1024)

#define CALI_ALSC_GRID_X                        (61)
#define CALI_ALSC_GRID_Y                        (69)
#define CALI_ALSC_GRID_NUM                      (CALI_ALSC_GRID_X * CALI_ALSC_GRID_Y)
#define CALI_ALSC_CCT_NUM                       (3)
#define CALI_ALSC_RGB_NUM                       (3)
#define CALI_ALSC_RATION_TABLE_SIZE             (32)

#define CALI_SDC_TABLE_SIZE                     (1024)
#define CALI_SDC_CTRL_ITEM_NUMBER               (2)

#define CALI_FPN_TABLE_SIZE                     (2816)

#define CALI_SDC_FLAG_TYPE_CALI_CLUSTER         (0x00000001)// hex for 0000 0000 0000 0000 0000 0000 0000 0001
#define CALI_SDC_FLAG_TYPE_CALI_OPTION02        (0x00000002)// hex for 0000 0000 0000 0000 0000 0000 0000 0010
#define CALI_SDC_FLAG_TYPE_CALI_OPTION03        (0x00000004)// hex for 0000 0000 0000 0000 0000 0000 0000 0100
#define CALI_SDC_FLAG_TYPE_CALI_OPTION04        (0x00000008)// hex for 0000 0000 0000 0000 0000 0000 0000 1000
#define CALI_SDC_FLAG_TYPE_CALI_OPTION05        (0x00000010)// hex for 0000 0000 0000 0000 0000 0000 0001 0000
#define CALI_SDC_FLAG_TYPE_CALI_OPTION06        (0x00000020)// hex for 0000 0000 0000 0000 0000 0000 0010 0000
#define CALI_SDC_FLAG_TYPE_CALI_OPTION07        (0x00000040)// hex for 0000 0000 0000 0000 0000 0000 0100 0000
#define CALI_SDC_FLAG_TYPE_CALI_OPTION08        (0x00000080)// hex for 0000 0000 0000 0000 0000 0000 1000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_TAB_RESULT      (0x00000100)// hex for 0000 0000 0000 0000 0000 0001 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_CAL_TIME        (0x00000200)// hex for 0000 0000 0000 0000 0000 0010 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_RAW_IMAGE       (0x00000400)// hex for 0000 0000 0000 0000 0000 0100 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_OPTION04        (0x00000800)// hex for 0000 0000 0000 0000 0000 1000 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_OPTION05        (0x00001000)// hex for 0000 0000 0000 0000 0001 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_OPTION06        (0x00002000)// hex for 0000 0000 0000 0000 0010 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_OPTION07        (0x00004000)// hex for 0000 0000 0000 0000 0100 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DUMP_OPTION08        (0x00008000)// hex for 0000 0000 0000 0000 1000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_MESSAGE         (0x00010000)// hex for 0000 0000 0000 0001 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_HIST_STATISTIC  (0x00020000)// hex for 0000 0000 0000 0010 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION03        (0x00040000)// hex for 0000 0000 0000 0100 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION04        (0x00080000)// hex for 0000 0000 0000 1000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION05        (0x00100000)// hex for 0000 0000 0001 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION06        (0x00200000)// hex for 0000 0000 0010 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION07        (0x00400000)// hex for 0000 0000 0100 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION08        (0x00800000)// hex for 0000 0000 1000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION09        (0x01000000)// hex for 0000 0001 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION10        (0x02000000)// hex for 0000 0010 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION11        (0x04000000)// hex for 0000 0100 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION12        (0x08000000)// hex for 0000 1000 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION13        (0x10000000)// hex for 0001 0000 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION14        (0x20000000)// hex for 0010 0000 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION15        (0x40000000)// hex for 0100 0000 0000 0000 0000 0000 0000 0000
#define CALI_SDC_FLAG_TYPE_DISP_OPTION16        (0x80000000)// hex for 1000 0000 0000 0000 0000 0000 0000 0000

typedef struct
{
    u32	nHeaderLength;
    u32	nDataType;
    u32	nVersion;
    u32 nChecksum;
    u32	nReserved[8];
} CaliDataHeader;
////////////// ISP header /////////////////////////////
typedef struct
{
    u32 u4Version;
    u32 u4Rsvd[4];
} ISP_CALI_HEADER;

////////////// OBC Calibration ///////////////
typedef enum __attribute__ ((aligned (4)))
{
	eOBC_CALI_OK,
	eOBC_CALI_NG
} OBC_CALI_ERROR;

typedef struct
{
	u16 u2R_offset;		// 0 ~ 65535, OB result @ 16bit
	u16 u2Gr_offset;
	u16 u2Gb_offset;
	u16 u2B_offset;
} OBC_CALI_INFO;

typedef struct
{
	OBC_CALI_ERROR eRet;
	u8	bAutoAssign;
	u16 u2Target;					    // 0 ~ 255, the remaining value after calibration
	u16 u2Weight[CALI_OBC_WEIGHT_NUM];	// 0 ~ 16, the 3*3 image weightinh in raw data calculation
	u32 u4CaliGain;					    // 0 ~ 1000 x 1024
} OBC_CALI_CTRL;

typedef struct
{
    ISP_CALI_HEADER strHeader;
    OBC_CALI_CTRL   param;
    OBC_CALI_INFO   result[CALI_OBC_GAIN_INDEX_NUM];
} OB_CALI_DATAv3;

////////////// AutoWhiteBalance Calibration ///////////////


typedef enum __attribute__ ((aligned (4)))
{
    eAWB_CALI_OK,
	eAWB_CALI_NG
} AWB_UNIT_CALI_ERROR;

typedef enum __attribute__ ((aligned (4)))
{
    AWB_UNIT_CALIB_GOLDEN_H = 0,
    AWB_UNIT_CALIB_GOLDEN_L = 1,
    AWB_UNIT_CALIB_H = 2,
    AWB_UNIT_CALIB_L = 3,
    AWB_UNIT_CALIB_VERIFY = 4,
    AWB_UNIT_CALIB_NUM = 5,
} AWB_UNIT_CALIB_STATE;

typedef struct
{
    u16 u2HighRg;              //RW, RGain of high color temperature lightsource , Range: [64, 4095]
    u16 u2HighBg;              //RW, BGain of high color temperature lightsource , Range: [64, 4095]
    u16 u2LowRg;               //RW, RGain of low color temperature lightsource , Range: [64, 4095]
    u16 u2LowBg;               //RW, BGain of low color temperature lightsource , Range: [64, 4095]
} AWB_CALI_UNIT_GAIN;

typedef struct
{
    AWB_UNIT_CALI_ERROR eRet;
    AWB_UNIT_CALIB_STATE eCaliState;    //RW, Calibration State
    u8  uCaliNum;                       //RW, Color temperature of calibration lightsource Number.  Range: [1, 2]
    u32 u4HighCT;                       //RW, Color temperature of calibration lightsource.         Range: [1000, 10000]
    u32 u4LowCT;                        //RW, Color temperature of calibration lightsource.         Range: [1000, 10000]
    AWB_CALI_UNIT_GAIN sGolden;
} AWB_UNIT_CALI_CTRL;

typedef struct
{
    ISP_CALI_HEADER strHeader;
    AWB_UNIT_CALI_CTRL param;
    AWB_CALI_UNIT_GAIN sGolden;
    AWB_CALI_UNIT_GAIN sModule;
} AWB_CALI_UNIT_DATAv3;

////////////// ALSC Calibration ///////////////
typedef enum __attribute__ ((aligned (4)))
{
    eALSC_CALI_OK,
    eALSC_CALI_NG
} ALSC_CALI_ERROR;

typedef struct
{
	u16 *pRGBGain[CALI_ALSC_RGB_NUM];                       // Index : 0 ~ 1 ~ 2 --> R ~ G ~ B
	u16 *pRGBData[CALI_ALSC_RGB_NUM];                       // Index : 0 ~ 1 ~ 2 --> R ~ G ~ B
	u16 *pRGBData_Grid[CALI_ALSC_RGB_NUM];                  // Index : 0 ~ 1 ~ 2 --> R ~ G ~ B
} ALSC_CALI_BUFFER_INFO;

typedef struct
{
	u8	uFlag;												//	0 ~ 7
	u16 u2CCT;												//	0 ~ 65535
	u16 u2Tbl[CALI_ALSC_RGB_NUM][CALI_ALSC_GRID_NUM];		//	0 ~ 65535 [RGB][TBL]
} ALSC_CALI_INFO;

typedef struct
{
    ALSC_CALI_ERROR eRet;
    u8              uTid;                                   // 0 ~ 2
    u8              uRatioTbl[CALI_ALSC_RATION_TABLE_SIZE]; // 0 ~ 255
    u16             u2ColorTemp;                            // 0 ~ 65535
    OBC_CALI_INFO   tObcInfo;
} ALSC_CALI_CTRL;

typedef struct
{
    ISP_CALI_HEADER strHeader;
    ALSC_CALI_CTRL param[CALI_ALSC_CCT_NUM];                //  0, 1, 2 --> L, M, H
    ALSC_CALI_INFO result[CALI_ALSC_CCT_NUM];
} ALSC_CALI_DATAv3;

////////////// Static Defect Correction(SDC) Calibration ///////////////
typedef enum __attribute__ ((aligned (4)))
{
    eSDC_CALI_WHITE = 0,
    eSDC_CALI_BLACK,
    eSDC_CALI_MIXER
} SDC_CALI_CTRL_ITEM;

typedef enum __attribute__ ((aligned (4)))
{
    eSDC_CALI_OK,
    eSDC_CALI_NO_SUPPORT_WHITL_AND_BLOCK_AT_THE_SAME_TIME,
    eSDC_CALI_SET_PARA_NG,
    eSDC_CALI_GET_PARA_NG,
    eSDC_CALI_CALC_SDC_NG,
    eSDC_CALI_CALC_SDC_GET_RAW_HIST_STATIST_NG,
    eSDC_CALI_CALC_SDC_GET_RAW_ADAP_THRESHOLD_NG,
    eSDC_CALI_CALC_SDC_GET_RAW_CALI_AMOUNTS_NG,
    eSDC_CALI_CALC_SDC_GET_RAW_CALI_CALLOC_EMORY_NG,
    eSDC_CALI_CALC_SDC_FIND_CLUSTER_POSITION_NG,
    eSDC_CALI_CALC_SDC_FIND_CLUSTER_CURRENT_WINDOW_NG,
    eSDC_CALI_CALC_SDC_FIND_CLUSTER_CURRENT_WINDOW_AVERAGE_NG,
    eSDC_CALI_CALC_SDC_CHECK_CURRENT_WINDOW_IS_CLUSTER_NG,
    eSDC_CALI_CALC_SDC_DATA_SORTING_INIT_NG,
    eSDC_CALI_CALC_SDC_DATA_SORTING_FIRST_NG,
    eSDC_CALI_CALC_SDC_DATA_SORTING_SECOND_NG,
    eSDC_CALI_GET_SDC_RESULT_NG,
    eSDC_CALI_SET_SDC_DATA_EQUAL_NULL,
    eSDC_CALI_SET_SDC_DATA_FROM_DRAM_TO_SRAM_NG,
    eSDC_CALI_SET_SDC_DATA_AND_MENULOAD_NON_EQUAL
} SDC_CALI_ERROR;

typedef enum __attribute__ ((aligned (4)))
{
    eCALI_SDC_FLAG_TYPE_CALI_CLUSTER,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION02,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION03,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION04,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION05,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION06,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION07,
    eCALI_SDC_FLAG_TYPE_CALI_OPTION08,
    eCALI_SDC_FLAG_TYPE_DUMP_TAB_RESULT,
    eCALI_SDC_FLAG_TYPE_DUMP_CAL_TIME,
    eCALI_SDC_FLAG_TYPE_DUMP_RAW_IMAGE,
    eCALI_SDC_FLAG_TYPE_DUMP_OPTION04,
    eCALI_SDC_FLAG_TYPE_DUMP_OPTION05,
    eCALI_SDC_FLAG_TYPE_DUMP_OPTION06,
    eCALI_SDC_FLAG_TYPE_DUMP_OPTION07,
    eCALI_SDC_FLAG_TYPE_DUMP_OPTION08,
    eCALI_SDC_FLAG_TYPE_DISP_MESSAGE,
    eCALI_SDC_FLAG_TYPE_DISP_HIST_STATISTIC,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION03,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION04,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION05,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION06,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION07,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION08,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION09,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION10,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION11,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION12,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION13,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION14,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION15,
    eCALI_SDC_FLAG_TYPE_DISP_OPTION16
} SDC_CALI_FLAG_TYPE;

typedef struct
{
    u16 x;                      // Range: [0, 4095]
    u16 y;                      // Range: [0, 4095]
    u16 intensity;              // Range: [0, 4095]
} ISP_CALI_INFO;

typedef struct
{
    SDC_CALI_ERROR     eRet;
    SDC_CALI_CTRL_ITEM eItem;
    u8 uMixerRatio;                                         // Range: [0,  100]
    u8 uCaliImgNum[CALI_SDC_CTRL_ITEM_NUMBER];              // Range: [1,  255]
    u8 uInvalidRatio[CALI_SDC_CTRL_ITEM_NUMBER];            // Range: [0,  100]
    u32 u4CaliFlag[CALI_SDC_CTRL_ITEM_NUMBER];              // Range: [0,    1]
    u16 u2ValidValue[CALI_SDC_CTRL_ITEM_NUMBER];            // Range: [0, 65535]
    u32 u4TotalAmount[CALI_SDC_CTRL_ITEM_NUMBER];           // Range: [0, 3840*2160] (image size)
    u32 u4ClusterAmount[CALI_SDC_CTRL_ITEM_NUMBER];         // Range: [0, 3840*2160] (image size)
} SDC_CALI_CTRL;

typedef struct
{
    ISP_CALI_HEADER strHeader;
    SDC_CALI_CTRL param;
    ISP_CALI_INFO sdc_white_table[CALI_SDC_TABLE_SIZE]; // Range: [0, 4095]
    ISP_CALI_INFO sdc_black_table[CALI_SDC_TABLE_SIZE]; // Range: [0, 4095]
    ISP_CALI_INFO sdc_mixer_table[CALI_SDC_TABLE_SIZE]; // Range: [0, 4095]
} SDC_CALI_DATAv3;

//////////// FPN //////////////
typedef enum __attribute__ ((aligned (4)))
{
    eFPN_CALI_OK,
    eFPN_CALI_NG
} FPN_CALI_ERROR;

typedef struct
{
    FPN_CALI_ERROR eRet;
    u32 caliNum;
    u32 caliGain;
    u32 strX;
    u32 strY;
    u32 winWidth;
    u32 winHeight;
    u32 diffThd;
    u32 stdThd;
} FPN_CALI_CTRL;

typedef struct
{
    ISP_CALI_HEADER srtHeader;
    FPN_CALI_CTRL param;
    u16 pTable[CALI_FPN_TABLE_SIZE];
} FPN_CALI_DATAv3;

#endif
