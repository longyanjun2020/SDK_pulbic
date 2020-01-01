#ifndef __DRV_CSI__
#define __DRV_CSI__

#include "isp_types.h"

#define CSI_SHIFTBITS(a)      (0x01<<(a))
#define CSI_CHECKBITS(a, b)   ((a) & ((u32)0x01 << (b)))
#define CSI_SETBIT(a, b)      (a) |= (((u32)0x01 << (b)))
#define CSI_CLEARBIT(a, b)    (a) &= (~((u32)0x01 << (b)))
#define INC_CSI_ERR_COUNT(name) (gpcsi_dev_data->csi_err_int_count[name]++)

//#define DEBUG
#ifndef DEBUG
#define DBG_INFO(fmt, args...)
#define DBG_INFO_1(fmt, args...)
#else
#define DBG_INFO(fmt, args...) UartSendTrace("[DrvCSI] Info, " fmt, ## args)
#define DBG_INFO_1(fmt,args...) UartSendTrace("[DrvCSI] Info, " fmt, ## args)
#endif
//// CSI ////
typedef enum {
    CSI_DISABLE = 0,
    CSI_ENABLE = 1,
} CSI_ONOFF_e;

typedef enum {
    CSI_DATA_LANE_0 = 0,
    CSI_DATA_LANE_1 = 1,
    CSI_DATA_LANE_2 = 2,
    CSI_DATA_LANE_3 = 3,
} CSI_DATA_LANE_e;

typedef enum {
    CSI_MAC_FUNC_MODE_NORMAL = 0,
    CSI_MAC_FUNC_MODE_ONE_FRAME = 1,
    CSI_MAC_FUNC_MODE_STREAM_BYPASS1 = 2,
    CSI_MAC_FUNC_MODE_STREAM_BYPASS2 = 3,
} CSI_MAC_FUNC_MODE_e;

typedef enum {
    CSI_CHANNEL_0 = 0,
    CSI_CHANNEL_1 = 1,
    CSI_CHANNEL_2 = 2,
    CSI_CHANNEL_3 = 3,
    CSI_CHANNEL_4 = 4,
} CSI_CHANNEL_e;

typedef enum {
    CSI_VIRTUAL_CHANNEL_0 = 0,
    CSI_VIRTUAL_CHANNEL_1 = 1,
    CSI_VIRTUAL_CHANNEL_2 = 2,
    CSI_VIRTUAL_CHANNEL_3 = 3,
} CSI_VIRTUAL_CHANNEL_e;

typedef enum {
    CSI_YUV422_8BIT_OUT_MODE_YUYV = 0,
    CSI_YUV422_8BIT_OUT_MODE_UYVY = 1,
} CSI_YUV422_8BIT_OUT_MODE_e;

typedef enum {
    CSI_VIRTUAL_CHANNEL_HSYNC_MODE_PACKET_HEADER_EDGE = 0,
    CSI_VIRTUAL_CHANNEL_HSYNC_MODE_LINE_END_EDGE = 1,
    CSI_VIRTUAL_CHANNEL_HSYNC_MODE_LINE_START_EDGE = 2,
    CSI_VIRTUAL_CHANNEL_HSYNC_MODE_PACKET_FOOTER_EDGE = 3,
} CSI_VIRTUAL_CHANNEL_HSYNC_MODE_e;

typedef enum {
    CSI_VIRTUAL_CHANNEL_VSYNC_MODE_FRAME_START_EDGE = 0,
    CSI_VIRTUAL_CHANNEL_VSYNC_MODE_FRAME_END_EDGE = 1,
} CSI_VIRTUAL_CHANNEL_VSYNC_MODE_e;

typedef enum {
    CSI_CLK_POLARITY_HIGH_ACTIVE = 0,
    CSI_CLK_POLARITY_LOW_ACTIVE  = 1,
} CSI_CLK_POLARITY_e;

typedef enum {
    CSI_REPORT_FRAME_NUM_START = 0,
    CSI_REPORT_FRAME_NUM_END  = 1,
} CSI_REPORT_FRAME_NUM_e;

typedef enum {
    CSI_REPORT_LINE_NUM_START = 0,
    CSI_REPORT_LINE_NUM_END  = 1,
} CSI_REPORT_LINE_NUM_e;

typedef enum {
    CSI_FSM_LANE_TYPE_CLK = 0,
    CSI_FSM_LANE_TYPE_DATA0  = 1,
    CSI_FSM_LANE_TYPE_DATA1  = 2,
    CSI_FSM_LANE_TYPE_DATA2  = 3,
    CSI_FSM_LANE_TYPE_DATA3  = 4,
} CSI_FSM_LANE_TYPE_e;

typedef enum {
    CSI_HDR_MODE_NONE = 0,
    CSI_HDR_MODE_SONY_290_326 = 1, //Sony DOL
    CSI_HDR_MODE_DCG = 2,
    CSI_HDR_MODE_EMBEDDED_RAW8 = 3,
    CSI_HDR_MODE_EMBEDDED_RAW10 = 4,
    CSI_HDR_MODE_EMBEDDED_RAW12 = 5,
    CSI_HDR_MODE_EMBEDDED_RAW16 = 6, //Only for OV2718?
} CSI_HDR_MODE_e;

typedef enum {
    CSI_CLK_DIV_1 = 0,
    CSI_CLK_DIV_2  = 1,
    CSI_CLK_DIV_4  = 2,
    CSI_CLK_DIV_8  = 3,
    CSI_CLK_DIV_16  = 4,
    CSI_CLK_DIV_32  = 5,
    CSI_CLK_DIV_64  = 6,
    CSI_CLK_DIV_128  = 7,
} CSI_CLK_DIV_e;

typedef enum
{
    RPT_INT_LINE   = 0,
    RPT_INT_FRAME  = 1,
    RPT_INT_VC0  = 6,
    RPT_INT_VC1  = 5,
    RPT_INT_VC2  = 4,
    RPT_INT_VC4  = 3
} CSI_RPT_INT_STATUS;

#define CSI_LONG_PACKET_TYPE_NONE  (0x1<<0)
#define CSI_LONG_PACKET_TYPE_BLINKING  (0x1<<1)
#define CSI_LONG_PACKET_TYPE_EMBEDDED  (0x1<<2)
#define CSI_LONG_PACKET_TYPE_YUV422_8B  (0x1<<14)
#define CSI_LONG_PACKET_TYPE_RAW8  (0x1<<26)
#define CSI_LONG_PACKET_TYPE_RAW10  (0x1<<27)
#define CSI_LONG_PACKET_TYPE_RAW12  (0x1<<28)
#define CSI_LONG_PACKET_TYPE_RAW14  (0x1<<29)
#define CSI_LONG_PACKET_TYPE_RAW16  (0x1<<30)

//// CSI Error////
typedef enum
{
    ERR_INT_DT          =  0,
    ERR_INT_PA_LENS     =  1,
    ERR_INT_PH_LENS     =  2,
    ERR_INT_ECC_ONEBIT  =  3,
    ERR_INT_FRAME_START =  4,
    ERR_INT_FRAME_END   =  5,
    ERR_INT_ECC_TWOBIT  =  6,
    ERR_INT_CRC         =  7,
    ERR_INT_PA_WC_EQ0   =  8,
    ERR_INT_RAW10_LENS  =  9,
    ERR_INT_CON_FE      = 10,
    ERR_INT_CON_FS      = 11,
    ERR_INT_LE          = 12,
    ERR_INT_LS          = 13,
    ERR_INT_OVERRUN     = 14,
    CSI_ERR_INT_MAX     = 15,
} CSI_ERR_INT_STATUS;

typedef struct
{
    u64 count;
    //spinlock_t lock;
    u8 frame_end; //frame end interrupt flag
    u8 frame_start;

    u32 fs_int_count;    //frame start interrput count
    u32 vc0_int_count; //virtual channel 0 count

    //wait_queue_head_t *p_wq_fe;
    //wait_queue_head_t *p_wq_fs;

    //HAL
    //void* reg_base;
    //void* hal_handle;

    u32 csi_err_int_count[CSI_ERR_INT_MAX];
    //struct device *sysfs_dev;
} csi_dev_data;

void Drv_CSISetClk(u16 usmipi_pad, 
				   CSI_CLK_DIV_e csi_mac_div, 
				   CSI_CLK_POLARITY_e csi_mac_inv, 
				   CSI_CLK_DIV_e csi_lptx_div, 
				   CSI_CLK_POLARITY_e csi_lptx_mac_inv);
void Drv_CSISetLane(u16 usmipi_pad, u16 lane, u8 bon_off, u32 *DataLaneSel, u32 *HsTxPolarity);
void Drv_CSISetVC0HSMode(u16 usmipi_pad, CSI_VIRTUAL_CHANNEL_e virtual_ch_num, u16 hs_mode);
void Drv_CSISetLongPacket(u16 usmipi_pad, u32 ctl_cfg0_15, u32 ctl_cfg16_31, u32 ctl_cfg32_47);
void Drv_CSISetClkDataSkip(u16 usmipi_pad, u8 rx_clk_skip_ns, u8 rx_data_skip_ns);
void Drv_CSISetHDRMode(u16 usmipi_pad, CSI_HDR_MODE_e csi_hdr_mode, u8 bon_off);
void Drv_CSISetDOLHDREn(u8 bon_off);
void Drv_CSISetHDR_UD1_8TO16BitOutputMode(u16 usmipi_pad, CSI_ONOFF_e csi_on_off);
int Drv_CSIInit(void);
int Drv_CSIUnInit(void);
void Drv_CSIShowInts();

#endif
