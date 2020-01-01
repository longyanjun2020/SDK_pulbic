#ifndef __DRV_VIF__
#define __DRV_VIF__

#include "vm_types.ht"
#include <drv_isp.h>

typedef enum {
    VIF_CHANNEL_0,
    VIF_CHANNEL_1,
    VIF_CHANNEL_2,
    VIF_CHANNEL_NUM,
} VIF_CHANNEL_e;

typedef enum {
    VIF_DISABLE,
    VIF_ENABLE,
} VIF_ONOFF_e;

typedef enum {
    VIF_CH_SRC_MIPI_0 = 0, //MIPI 4 lane
    VIF_CH_SRC_MIPI_1 = 1, //MIPI 2 lane
    VIF_CH_SRC_MIPI_2 = 2,
    VIF_CH_SRC_MIPI_3 = 3,
    VIF_CH_SRC_HISPI_0 = 4,
    VIF_CH_SRC_HISPI_1 = 5,
    VIF_CH_SRC_HISPI_2 = 6,
    VIF_CH_SRC_HISPI_3 = 7,
    VIF_CH_SRC_MIPI0_VC0 = 8,
    VIF_CH_SRC_MIPI0_VC1 = 9,
    VIF_CH_SRC_MIPI0_VC2 = 10,
    VIF_CH_SRC_MIPI0_VC3 = 11,
    VIF_CH_SRC_MIPI1_VC0 = 12,
    VIF_CH_SRC_MIPI1_VC1 = 13,
    VIF_CH_SRC_MIPI1_VC2 = 14,
    VIF_CH_SRC_MIPI1_VC3 = 15,
    VIF_CH_SRC_PARALLEL_SENSOR_0 = 16,
    VIF_CH_SRC_PARALLEL_SENSOR_1 = 17,
    VIF_CH_SRC_BT656 = 18,
    VIF_CH_SRC_BT601 = 19,
    VIF_CH_SRC_MAX = 20,
} VIF_CHANNEL_SOURCE_e;

typedef enum {
    VIF_HDR_SRC_MIPI0,
    VIF_HDR_SRC_MIPI1,
    VIF_HDR_SRC_MIPI2,
    VIF_HDR_SRC_MIPI3,
    VIF_HDR_SRC_HISPI0,
    VIF_HDR_SRC_HISPI1,
    VIF_HDR_SRC_HISPI2,
    VIF_HDR_SRC_HISPI3,
} VIF_HDR_SOURCE_e;

typedef enum {
    VIF_STROBE_POLARITY_HIGH_ACTIVE,
    VIF_STROBE_POLARITY_LOW_ACTIVE,
} VIF_STROBE_POLARITY_e;

typedef enum {
    VIF_STROBE_VERTICAL_ACTIVE_START,
    VIF_STROBE_VERTICAL_BLANKING_START,
} VIF_STROBE_VERTICAL_START_e;

typedef enum {
    VIF_STROBE_SHORT,
    VIF_STROBE_LONG,
} VIF_STROBE_MODE_e;

typedef enum {
    VIF_SENSOR_POLARITY_HIGH_ACTIVE = 0,
    VIF_SENSOR_POLARITY_LOW_ACTIVE  = 1,
} VIF_SENSOR_POLARITY_e;

typedef enum {
    VIF_SENSOR_FORMAT_8BIT = 0,
    VIF_SENSOR_FORMAT_10BIT = 1,
    VIF_SENSOR_FORMAT_16BIT = 2,
    VIF_SENSOR_FORMAT_12BIT = 3,
} VIF_SENSOR_FORMAT_e;

typedef enum {
    VIF_SENSOR_INPUT_FORMAT_YUV422,
    VIF_SENSOR_INPUT_FORMAT_RGB,
} VIF_SENSOR_INPUT_FORMAT_e;

typedef enum {
    VIF_SENSOR_BIT_MODE_0,
    VIF_SENSOR_BIT_MODE_1,
    VIF_SENSOR_BIT_MODE_2,
    VIF_SENSOR_BIT_MODE_3,
} VIF_SENSOR_BIT_MODE_e;

typedef enum {
    VIF_SENSOR_YC_SEPARATE,
    VIF_SENSOR_YC_16BIT,
} VIF_SENSOR_YC_INPUT_FORMAT_e;

typedef enum {
    VIF_SENSOR_VS_FALLING_EDGE,
    VIF_SENSOR_VS_FALLING_EDGE_DELAY_2_LINE,
    VIF_SENSOR_VS_FALLING_EDGE_DELAY_1_LINE,
    VIF_SENSOR_VS_RISING_EDGE,
} VIF_SENSOR_VS_DELAY_e;

typedef enum {
    VIF_SENSOR_HS_RISING_EDGE,
    VIF_SENSOR_HS_FALLING_EDGE,
} VIF_SENSOR_HS_DELAY_e;

typedef enum {
    VIF_SENSOR_BT656_YC,
    VIF_SENSOR_BT656_CY,
} VIF_SENSOR_BT656_FORMAT_e;

typedef enum {
    VIF_INTERRUPT_VREG_RISING_EDGE,
    VIF_INTERRUPT_VREG_FALLING_EDGE,
    VIF_INTERRUPT_HW_FLASH_STROBE_DONE,
    VIF_INTERRUPT_PAD2VIF_VSYNC_RISING_EDGE,
    VIF_INTERRUPT_PAD2VIF_VSYNC_FALLING_EDGE,
    VIF_INTERRUPT_VIF_TO_ISP_LINE_COUNT_HIT0,
    VIF_INTERRUPT_VIF_TO_ISP_LINE_COUNT_HIT1,
} VIF_INTERRUPT_e;

typedef enum {
    VIF_RGRG_GBGB,
    VIF_GRGR_BGBG,
    VIF_BGBG_GRGR,
    VIF_GBGB_RGRG,
} VIF_BAYER_MODE_e;

typedef enum {
    VIF_CYCY,
    VIF_YCYC,
} VIF_INPUT_PRIORITY_YUV_e;

typedef enum {
    VIF_SUCCESS,
    VIF_FAIL,
    VIF_ISR_CREATE_FAIL,
} VIF_STATUS_e;

typedef enum
{
    VIF_INTS_FRAME_START_CH0 = 0x00000001,
    VIF_INTS_FRAME_START_CH1 = 0x00000002,
    VIF_INTS_FRAME_START_CH2 = 0x00000004,
    VIF_INTS_FRAME_LINE_CNT0_CH0 = 0x00000008,
    VIF_INTS_FRAME_LINE_CNT0_CH1 = 0x00000010,
    VIF_INTS_FRAME_LINE_CNT0_CH2 = 0x00000020,
    VIF_INTS_FRAME_LINE_CNT1_CH0 = 0x00000040,
    VIF_INTS_FRAME_LINE_CNT1_CH1 = 0x00000080,
    VIF_INTS_FRAME_LINE_CNT1_CH2 = 0x00000100,
} VIF_INTS_EVENT_TYPE_e;

typedef enum
{
    VIF_CLK_CSI2_MAC_0 = 0,//000: clk_csi2_mac_toblk0_buf0_p
    VIF_CLK_CSI2_MAC_1 = 1,//001: clk_csi2_mac_toblk0_4_buf0_p
    VIF_CLK_BT656_P0_0_P = 2,//010: clk_bt656_p0_0_p
    VIF_CLK_BT656_P0_1_P = 3,//011: clk_bt656_p0_1_p
    VIF_CLK_BT656_P1_0_P = 4,//100: clk_bt656_p1_0_p
    VIF_CLK_BT656_P1_1_P = 5,//101: clk_bt656_p1_1_p*/
    VIF_CLK_PARALLEL = 6,//110: clk_parllel*/
    VIF_CLK_FPGA_BT656 = 7, //111: TBD.
};

typedef enum
{
    VIF_BT656_EAV_DETECT = 0,
    VIF_BT656_SAV_DETECT = 1,
} VIF_BT656_CHANNEL_SELECT_e;

typedef enum
{
    VIF_BT656_VSYNC_DELAY_1LINE = 0,
    VIF_BT656_VSYNC_DELAY_2LINE = 1,
    VIF_BT656_VSYNC_DELAY_0LINE = 2,
    VIF_BT656_VSYNC_DELAY_AUTO = 3,
} VIF_BT656_VSYNC_DELAY_e;

typedef enum
{
    SENSOR_PAD_GROUP_A = 0,
    SENSOR_PAD_GROUP_B = 1,
} SENSOR_PAD_GROUP_e;

typedef struct VifCfg_s
{
    VIF_CHANNEL_SOURCE_e eSrc;
    VIF_HDR_SOURCE_e eHdrSrc;
    VIF_SENSOR_POLARITY_e HsyncPol;
    VIF_SENSOR_POLARITY_e VsyncPol;
    VIF_SENSOR_POLARITY_e ResetPinPol;
    VIF_SENSOR_POLARITY_e PdwnPinPol;
    VIF_SENSOR_FORMAT_e ePixelDepth;
    VIF_BAYER_MODE_e eBayerID;      
    u32 FrameStartLineCount; // lineCount0 for FS ints
    u32 FrameEndLineCount;   // lineCount1 for FE ints
} VifSensorCfg_t;

typedef struct VifBT656Cfg_s
{
    u32 bt656_ch_det_en;
    VIF_BT656_CHANNEL_SELECT_e bt656_ch_det_sel;
    u32 bt656_bit_swap;
    u32 bt656_8bit_mode;
    VIF_BT656_VSYNC_DELAY_e bt656_vsync_delay;
    u32 bt656_hsync_inv;
    u32 bt656_vsync_inv;
    u32 bt656_clamp_en;
} VifBT656Cfg_t;

typedef struct VifPatGenCfg_s
{
    u32 nWidth;
    u32 nHeight;
    u32 nFps;
} VifPatGenCfg_t;

int DrvVif_InitIntFlag(void);
int DrvVif_UnInitIntFlag(void);
void DrvVif_SetInt(MS_S32 value);
MS_S32 DrvVif_WaitInt(MS_S32 nIntForWait);
#if 0
int DrvVif_CreateFSTask(void);
int DrvVif_DeleteFSTask(void);
int DrvVif_CreateFETask(void);
int DrvVif_DeleteFETask(void);
#endif
int DrvVif_SensorLineCount(VIF_CHANNEL_e ch, int iline_cnt0,  int iline_cnt1);
int DrvVif_SensorReset(SENSOR_PAD_GROUP_e pad_group,int reset);
int DrvVif_SensorPdwn(SENSOR_PAD_GROUP_e pad_group, int Pdwn);
int DrvVif_SensorSWReset(VIF_CHANNEL_e ch, bool ben);
int DrvVif_ChannelEnable(VIF_CHANNEL_e ch, bool ben);
int DrvVif_SetDefaultIntsMask(void);
void DrvVif_DisableInt(void);
void DrvVif_EnableInt(void);
int DrvVif_ConfigParallelIF(VIF_CHANNEL_e ch,
                            VIF_SENSOR_INPUT_FORMAT_e svif_sensor_in_format,
                            VIF_SENSOR_FORMAT_e PixDepth,
                            CLK_POL PclkPol,
                            CLK_POL VsyncPol,
                            CLK_POL HsyncPol,
                            u32 nImgWidth);
int DrvVif_ConfigBT656IF(SENSOR_PAD_GROUP_e pad_group, VIF_CHANNEL_e ch, VifBT656Cfg_t *pvif_bt656_cfg);
int DrvVif_SetChannelSource(SENSOR_PAD_GROUP_e pad_group, VIF_CHANNEL_e ch, VIF_CHANNEL_SOURCE_e svif_ch_src, unsigned int bt656_total_ch, unsigned int bt656_cur_ch);
int DrvVif_Init(void);
int DrvVif_DeInit(void);
void DrvVif_ConfigLIHDRIF(u32 nImgHeight);

#endif
