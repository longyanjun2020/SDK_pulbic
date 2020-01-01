//==============================================================================
//
//  File        : mmpf_vif.h
//  Description : INCLUDE File for the Firmware VIF Control driver function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_VIF_H_
#define _MMPF_VIF_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_MIPI_DATA_LANE_NUM  (4)
#define MAX_MIPI_VC_NUM			(4)

#define VIF_WHILE_TIMEOUT		(0x100000)

#define MMPF_VIF_MDL_ID0        (0)
#define MMPF_VIF_MDL_ID1        (1)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_VIF_IN_TYPE {
    MMPF_VIF_PARALLEL = 0,
    MMPF_VIF_MIPI
} MMPF_VIF_IN_TYPE;

typedef enum _MMPF_VIF_MDL_ID {
    MMPF_VIF_MDL_ID_0 = MMPF_VIF_MDL_ID0,
    MMPF_VIF_MDL_ID_1 = MMPF_VIF_MDL_ID1,
    MMPF_VIF_MDL_NUM
} MMPF_VIF_MDL_ID;

typedef enum _MMPF_VIF_IF {
	MMPF_VIF_IF_PARALLEL        = 0,
	MMPF_VIF_IF_MIPI_SINGLE_0   = 1,
	MMPF_VIF_IF_MIPI_SINGLE_1   = 2,
	MMPF_VIF_IF_MIPI_SINGLE_2   = 3,
	MMPF_VIF_IF_MIPI_SINGLE_3   = 4,
	MMPF_VIF_IF_MIPI_DUAL_01    = 5,
	MMPF_VIF_IF_MIPI_DUAL_02    = 6,
	MMPF_VIF_IF_MIPI_DUAL_03    = 7,
	MMPF_VIF_IF_MIPI_DUAL_12    = 8,
	MMPF_VIF_IF_MIPI_DUAL_13    = 9,
	MMPF_VIF_IF_MIPI_DUAL_23    = 10,
	MMPF_VIF_IF_MIPI_QUAD       = 11
} MMPF_VIF_IF;

typedef enum _MMPF_VIF_INT_EVENT {
    MMPF_VIF_INT_EVENT_FRM_ST = 0,
    MMPF_VIF_INT_EVENT_FRM_ED,
    MMPF_VIF_INT_EVENT_GRAB_ED,
    MMPF_VIF_INT_EVENT_LINE0,
    MMPF_VIF_INT_EVENT_NUM
} MMPF_VIF_INT_EVENT;

typedef enum _MMPF_VIF_PATH {
    MMPF_VIF_PATH1_BAYER_TO_ISP = 0,
    MMPF_VIF_PATH2_YCbCr422_2_YCbCr444_BYPASS_ISP,
    MMPF_VIF_PATH3_YCbCr422_2_BAYER,
    MMPF_VIF_PATH4_YCbCr422_2_YUV444,
    MMPF_VIF_PATH5_BAYER_TO_RAWPROC,
    MMPF_VIF_PATH6_JPG2RAWPROC,        
    MMPF_VIF_PATH7_YCbCr422_2_YCbCr420_TO_RAWPROC,
    MMPF_VIF_PATH8_VC_DATA
} MMPF_VIF_PATH;

typedef enum _MMPF_VIF_COLOR_ID {
    MMPF_VIF_COLORID_00 = 0,
    MMPF_VIF_COLORID_01,
    MMPF_VIF_COLORID_10,
    MMPF_VIF_COLORID_11,
    MMPF_VIF_COLORID_UNDEF
} MMPF_VIF_COLOR_ID;

typedef enum _MMPF_VIF_SNR_PHASE_DELAY {
    MMPF_VIF_SNR_PHASE_DELAY_NONE = 0,
    MMPF_VIF_SNR_PHASE_DELAY_0_5F,
    MMPF_VIF_SNR_PHASE_DELAY_1_0F,
    MMPF_VIF_SNR_PHASE_DELAY_1_5F        
} MMPF_VIF_SNR_PHASE_DELAY;

typedef enum _MMPF_VIF_SNR_CLK_POLARITY {
    MMPF_VIF_SNR_CLK_POLARITY_POS = 0,
    MMPF_VIF_SNR_CLK_POLARITY_NEG       
} MMPF_VIF_SNR_CLK_POLARITY;

typedef enum _MMPF_VIF_SNR_LATCH_TIMING {
    MMPF_VIF_SNR_LATCH_POS_EDGE = 0,
    MMPF_VIF_SNR_LATCH_NEG_EDGE      
} MMPF_VIF_SNR_LATCH_TIMING;

typedef enum _MMPF_VIF_SNR_CLK_SRC {
    MMPF_VIF_SNR_CLK_SRC_PMCLK = 0,
    MMPF_VIF_SNR_CLK_SRC_VIFCLK
} MMPF_VIF_SNR_CLK_SRC;

typedef enum _MMPF_VIF_MIPI_DATA_SRC {
    MMPF_VIF_MIPI_DATA_SRC_PHY_0 = 0,
    MMPF_VIF_MIPI_DATA_SRC_PHY_1,
    MMPF_VIF_MIPI_DATA_SRC_PHY_2,
    MMPF_VIF_MIPI_DATA_SRC_PHY_3,
    MMPF_VIF_MIPI_DATA_SRC_PHY_UNDEF
} MMPF_VIF_MIPI_DATA_SRC;

typedef enum _MMPF_VIF_SNR_PARAL_BITMODE {
    MMPF_VIF_SNR_PARAL_BITMODE_16 = 0,  // Sensor data bus [15:0] would be enabled
    MMPF_VIF_SNR_PARAL_BITMODE_10,      // Sensor data bus [15:6] would be enabled
    MMPF_VIF_SNR_PARAL_BITMODE_NUM     
} MMPF_VIF_SNR_PARAL_BITMODE;

typedef enum _MMPF_VIF_TO_RAW_STORE_FMT {
    MMPF_VIF_TO_RAW_STORE_FMT_BAYER = 0,
    MMPF_VIF_TO_RAW_STORE_FMT_YUV420,
    MMPF_VIF_TO_RAW_STORE_FMT_YUV422,
    MMPF_VIF_TO_RAW_STORE_FMT_NUM
} MMPF_VIF_TO_RAW_STORE_FMT;

typedef enum _MMPF_VIF_SNR_TYPE {
    MMPF_VIF_SNR_TYPE_BAYER = 0,
    MMPF_VIF_SNR_TYPE_YUV,
    MMPF_VIF_SNR_TYPE_YUV_TV_DEC,
    MMPF_VIF_SNR_TYPE_NUM
} MMPF_VIF_SNR_TYPE;

typedef enum _MMPF_VIF_YUV422_ORDER {
    MMPF_VIF_YUV422_YUYV = 0,
    MMPF_VIF_YUV422_YVYU,
    MMPF_VIF_YUV422_UYVY,
    MMPF_VIF_YUV422_VYUY
} MMPF_VIF_YUV422_ORDER;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMPF_VIF_GRAB_INFO {
    MMP_USHORT                  usStartX;
    MMP_USHORT                  usStartY;
    MMP_USHORT                  usGrabW;
    MMP_USHORT                  usGrabH;
} MMPF_VIF_GRAB_INFO;

typedef struct _MMPF_VIF_GRAB_POS {
    MMP_USHORT                  usStartX;
    MMP_USHORT                  usStartY;
    MMP_USHORT                  usEndX;
    MMP_USHORT                  usEndY;
} MMPF_VIF_GRAB_POS;

typedef struct _MMPF_VIF_DATA_OFFSET {
    MMP_UBYTE                   ubCompId;
    MMP_BOOL                    bPostive;
    MMP_UBYTE                   ubOffVal;
} MMPF_VIF_DATA_OFFSET;

typedef struct _MMPF_VIF_MCLK_ATTR {
    MMP_BOOL                    bClkOutEn;
    MMP_UBYTE                   ubClkFreqDiv;       // If ubClkFreqDiv = 0, Use ulMClkFreq and ulDesiredFreq to calculate division.
    MMP_ULONG                   ulMClkFreq;         // Input clock  : kHz
    MMP_ULONG                   ulDesiredFreq;      // Output clock : kHz
    MMPF_VIF_SNR_PHASE_DELAY    ubClkPhase;
    MMPF_VIF_SNR_CLK_POLARITY   ubClkPolarity;
    MMPF_VIF_SNR_CLK_SRC        ubClkSrc;
} MMPF_VIF_MCLK_ATTR;

typedef struct _MMPF_VIF_PARAL_ATTR {
    MMPF_VIF_SNR_LATCH_TIMING   ubLatchTiming;
    MMPF_VIF_SNR_CLK_POLARITY   ubHsyncPolarity;
    MMPF_VIF_SNR_CLK_POLARITY   ubVsyncPolarity;
    MMPF_VIF_SNR_PARAL_BITMODE  ubBusBitMode;
} MMPF_VIF_PARAL_ATTR;

typedef struct _MMPF_MIPI_RX_ATTR {
    MMP_BOOL                    bClkDelayEn;
    MMP_BOOL                    bClkLaneSwapEn;
    MMP_USHORT                  usClkDelay;
    MMPF_VIF_SNR_LATCH_TIMING   ubBClkLatchTiming;
    MMP_BOOL                    bDataLaneEn[MAX_MIPI_DATA_LANE_NUM];
    MMP_BOOL                    bDataDelayEn[MAX_MIPI_DATA_LANE_NUM]; 
    MMP_BOOL                    bDataLaneSwapEn[MAX_MIPI_DATA_LANE_NUM];
    MMP_UBYTE                   ubDataLaneSrc[MAX_MIPI_DATA_LANE_NUM];
    MMP_USHORT                  usDataDelay[MAX_MIPI_DATA_LANE_NUM];
    MMP_UBYTE                  	ubDataSotCnt[MAX_MIPI_DATA_LANE_NUM];
} MMPF_MIPI_RX_ATTR;

typedef struct _MMPF_VIF_IGBT_ATTR {
    MMP_BOOL                    bEnable;
    MMP_USHORT                  usStartLine;
    MMP_USHORT                  usStartOfst;
    MMP_USHORT                  usEndCycle;
} MMPF_VIF_IGBT_ATTR;

typedef struct _MMPF_MIPI_VC_ATTR {
    MMP_BOOL                    bEnable;
    MMP_BOOL                    bAllChannel2Isp;
    MMP_BOOL                    bVC2Isp[MAX_MIPI_VC_NUM];
    MMP_BOOL                    bVC2Raw[MAX_MIPI_VC_NUM];
    MMP_BOOL	                bSlowFsForStagger;
} MMPF_MIPI_VC_ATTR;

typedef struct _MMPF_VIF_YUV_ATTR {
    MMP_BOOL                    bRawStoreEnable;
    MMP_BOOL                    bYuv422ToYuv420;
    MMP_BOOL                    bYuv422ToYuv422;
    MMP_BOOL                    bYuv422ToBayer;
    MMPF_VIF_YUV422_ORDER       ubYuv422Order;
} MMPF_VIF_YUV_ATTR;

//==============================================================================
//
//                              PUBLIC VARIABLES
//
//==============================================================================

typedef void VifCallBackFunc(void *argu);

extern VifCallBackFunc  *CallBackFuncVif[MMPF_VIF_MDL_NUM][MMPF_VIF_INT_EVENT_NUM];
extern void             *CallBackArguVif[MMPF_VIF_MDL_NUM][MMPF_VIF_INT_EVENT_NUM];

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR	    MMPF_VIF_SetPIODir(MMP_UBYTE ubVifId, MMP_UBYTE mask, MMP_BOOL bOutput);
MMP_ERR	    MMPF_VIF_SetPIOOutput(MMP_UBYTE ubVifId, MMP_UBYTE mask, MMP_BOOL bSetHigh);
MMP_BOOL    MMPF_VIF_GetPIOOutput(MMP_UBYTE ubVifId, MMP_UBYTE mask);

MMP_ERR     MMPF_VIF_ResetModule(MMP_UBYTE ubVifId);
MMP_ERR     MMPF_VIF_SetInputInterface(MMP_UBYTE ubVifId, MMPF_VIF_IN_TYPE type);
MMP_ERR	    MMPF_VIF_SetSensorType(MMP_UBYTE ubVifId, MMPF_VIF_SNR_TYPE type);
MMP_ERR 	MMPF_VIF_IsInterfaceEnable(MMP_UBYTE ubVifId, MMP_BOOL *bEnable);
MMP_ERR 	MMPF_VIF_EnableInputInterface(MMP_UBYTE ubVifId, MMP_BOOL enable);
MMP_ERR     MMPF_VIF_IsOutputEnable(MMP_UBYTE ubVifId, MMP_BOOL *bEnable);
MMP_ERR 	MMPF_VIF_EnableOutput(MMP_UBYTE ubVifId, MMP_BOOL bEnable);
MMP_ERR 	MMPF_VIF_EnableVIFToISP(MMP_UBYTE ubVifId, MMP_BOOL bEnable);

MMP_ERR 	MMPF_VIF_SetGrabPosition(MMP_UBYTE ubVifId, MMPF_VIF_GRAB_INFO *pGrab);
MMP_ERR 	MMPF_VIF_GetGrabResolution(MMP_UBYTE ubVifId, MMP_ULONG *ulWidth, MMP_ULONG *ulHeight);
MMP_ERR 	MMPF_VIF_SetInterruptLine(MMP_UBYTE ubVifId, MMP_USHORT usLineCnt);
MMP_ERR     MMPF_VIF_GetGrabPosition(MMP_UBYTE ubVifId, MMP_USHORT *usPixelStart, MMP_USHORT *usPixelEnd,
                                     MMP_USHORT *usLineStart, MMP_USHORT *usLineEnd);
MMP_ERR     MMPF_VIF_EnableInterrupt(MMP_UBYTE ubVifId, MMP_UBYTE ubFlag, MMP_BOOL bEnable);
MMP_ERR 	MMPF_VIF_OpenInterrupt(MMP_BOOL bEnable);
MMP_ERR 	MMPF_VIF_CheckFrameSig(MMP_UBYTE ubVifId, MMPF_VIF_INT_EVENT ubEvent, MMP_USHORT usFrameCount);

MMP_ERR 	MMPF_VIF_SetRawOutPath(MMP_UBYTE ubVifId, MMP_BOOL bOutISP, MMP_BOOL bOutRaw);
MMP_ERR     MMPF_VIF_SetFormatAndPath(MMP_UBYTE ubVifId, MMPF_VIF_PATH path);
MMP_ERR     MMPF_VIF_SetFixedDataOut(MMP_UBYTE ubVifId, MMP_BOOL bEnable, MMP_UBYTE ubData);
MMP_ERR     MMPF_VIF_SetColorID(MMP_UBYTE ubVifId, MMPF_VIF_COLOR_ID clrId);
MMP_ERR     MMPF_VIF_SetFrameSkip(MMP_UBYTE ubVifId, MMP_BOOL bEnable, MMP_UBYTE ubSkipIdx);
MMP_ERR     MMPF_VIF_SetDownSample(MMP_UBYTE ubVifId, MMP_BOOL bEnable, 
                               		MMP_UBYTE ubHratio, MMP_UBYTE ubVratio, MMP_BOOL bHsmooth);
MMP_ERR     MMPF_VIF_AdjustInputPixel(MMP_UBYTE ubVifId, MMP_BOOL bEnable, MMPF_VIF_DATA_OFFSET* pOffset);
MMP_ERR     MMPF_VIF_SetSensorMClockAttr(MMP_UBYTE ubVifId, const MMPF_VIF_MCLK_ATTR* pAttr);
MMP_ERR     MMPF_VIF_SetParallelTimingAttr(MMP_UBYTE ubVifId, const MMPF_VIF_PARAL_ATTR* pAttr);
MMP_ERR     MMPF_VIF_SetSensorMipiAttr(MMP_UBYTE ubVifId, const MMPF_MIPI_RX_ATTR* pAttr);
MMP_ERR 	MMPF_VIF_SetVirtualChannel(MMP_UBYTE ubVifId, const MMPF_MIPI_VC_ATTR* pAttr);
MMP_ERR     MMPF_VIF_SetIGBT(MMP_UBYTE ubVifId, const MMPF_VIF_IGBT_ATTR* pAttr);
MMP_ERR     MMPF_VIF_PowerDownMipiRx(void);
MMP_ERR     MMPF_VIF_SetYUVAttr(MMP_UBYTE ubVifId, const MMPF_VIF_YUV_ATTR* pAttr);
MMP_ERR     MMPF_VIF_RegisterIntrCallBack(  MMP_UBYTE           ubVifId,
                                            MMPF_VIF_INT_EVENT  event,
                                            VifCallBackFunc     *pCallBack,
                                            void                *pArgument);

#endif // _MMPF_VIF_H_
