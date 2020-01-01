////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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


/**
* @file     hal_mipi_dsi.h
* @version
* @Platform I3
* @brief    This file defines the HAL SCL utility interface
*
*/

#ifndef __HAL_MIPI_DSI_H__
#define __HAL_MIPI_DSI_H__


typedef unsigned char   u8;
typedef signed   char   s8;
typedef          char   ascii;
typedef unsigned short  u16;
typedef          short  s16;
typedef unsigned int    u32;
typedef unsigned int    U32;
typedef          int    s32;
typedef unsigned long long u64;
typedef      long long s64;
typedef unsigned char   bool;


#define NULL 0
#define TRUE 1
#define FALSE 0

#define     DSI_DCS_MAXIMUM_RETURN_PACKET_SIZE  0x37
#define     DSI_DCS_SHORT_PACKET_ID_0           0x05
#define     DSI_DCS_SHORT_PACKET_ID_1           0x15
#define     DSI_DCS_LONG_WRITE_PACKET_ID        0x39
#define     DSI_DCS_READ_PACKET_ID              0x06

#define     DSI_GERNERIC_SHORT_PACKET_ID_0      0x03
#define     DSI_GERNERIC_SHORT_PACKET_ID_1      0x13
#define     DSI_GERNERIC_SHORT_PACKET_ID_2      0x23
#define     DSI_GERNERIC_LONG_WRITE_PACKET_ID   0x29
#define     DSI_GERNERIC_READ_0_PARAM_PACKET_ID 0x04
#define     DSI_GERNERIC_READ_1_PARAM_PACKET_ID 0x14
#define     DSI_GERNERIC_READ_2_PARAM_PACKET_ID 0x24


// ESD recovery method for video mode LCM
#define     METHOD_NONCONTINUOUS_CLK            (0x1)
#define     METHOD_BUS_TURN_AROUND              (0x2)

#define     DSI_VDO_VSA_VS_STATE                (0x008)
#define     DSI_VDO_VSA_HS_STATE                (0x010)
#define     DSI_VDO_VSA_VE_STATE                (0x020)
#define     DSI_VDO_VBP_STATE                   (0x040)
#define     DSI_VDO_VACT_STATE                  (0x080)
#define     DSI_VDO_VFP_STATE                   (0x100)


#define     DSI_GERNERIC_READ_1_RESPONSE    0x11
#define     DSI_GERNERIC_READ_2_RESPONSE    0x12
#define     DSI_GERNERIC_READ_LONG_RESPONSE 0x1A

#define     DSI_DCS_READ_1_RESPONSE 0x21
#define     DSI_DCS_READ_2_RESPONSE 0x22
#define     DSI_DCS_READ_LONG_RESPONSE  0x1C

//Acknowledge error bit
#define DSI_ACK_SOT_ERR   (1<<0)
#define DSI_ACK_SOT_SYNC_ERR   (1<<1)
#define DSI_ACK_EOT_SYC_ERR   (1<<2)
#define DSI_ACK_ESCAPE_MODE_ENTRY_CMD_ERR   (1<<3)
#define DSI_ACK_LOW_POWER_TRANISMIT_SYNC_ERR   (1<<4)
#define DSI_ACK_HS_RECEIVE_TIMEOUT_ERR   (1<<5)

#define DSI_ACK_ECC_1BIT_ERR   (1<<8)
#define DSI_ACK_ECC_MULTI_BIT_ERR   (1<<9)
#define DSI_ACK_CHECKSUM_ERR   (1<<10)
#define DSI_ACK_DSI_TYPE_NOT_RECOGNIZED   (1<<11)
#define DSI_ACK_DSI_VC_ID_INVAID   (1<<12)


typedef enum _DSI_LANE_SEL {
       DSI_DATA_LANE0_SEL,
       DSI_DATA_LANE1_SEL,
       DSI_CLK_LANE_SEL,
       DSI_DATA_LANE2_SEL,
       DSI_DATA_LANE3_SEL,
} E_DSI_LANE_SEL;

typedef enum _DSI_TOP_CLK_SEL {
       DSI_TOP_CLK_LPLL,
    DSI_TOP_CLK_MPLL_108M,
    DSI_TOP_CLK_MPLL_144M,
    DSI_TOP_CLK_MPLL_160M,
    DSI_TOP_CLK_MPLL_216M,
    DSI_TOP_CLK_MPLL_240M
} E_DSI_TOP_CLK_SEL;


typedef enum _DSI_TOP_RGB_ORDER {
       DSI_TOP_RGB_ORDER,
       DSI_TOP_BGR_ORDER,
} E_DSI_TOP_RGB_ORDER;

typedef enum
{
    DSI_STATUS_OK = 0,
    DSI_STATUS_PACKET_TYPE_ERROR,

    DSI_STATUS_ERROR,
} DSI_STATUS;


typedef enum
{
    SHORT_PACKET_RW = 0,
    FB_WRITE        = 1,
    LONG_PACKET_W   = 2,
    FB_READ         = 3,
} DSI_INS_TYPE;


typedef enum
{
    DISABLE_BTA = 0,
    ENABLE_BTA  = 1,
} DSI_CMDQ_BTA;

typedef enum
{
    LOW_POWER   = 0,
    HIGH_SPEED  = 1,
} DSI_CMDQ_HS;

typedef enum
{
    DISABLE_TE  = 0,
    ENABLE_TE   = 1,
} DSI_CMDQ_TE;


typedef enum
{
    DSI_CMD_MODE = 0,
    DSI_SYNC_PULSE_MODE,
    DSI_SYNC_EVENT_MODE,
    DSI_BURST_MODE
} DSI_MODE_CTL;


typedef enum
{
    DSI_LANE_DIS = 0,
    DSI_LANE_NUM_1 = 1,
    DSI_LANE_NUM_2,
    DSI_LANE_NUM_3,
    DSI_LANE_NUM_4
} DSI_TOTAL_LANE_NUM;


typedef enum _DSI_INT_SEL {
	DSI_SKEWCAL_DONE_INT,
	DSI_VM_VFP_STR_INT,
	DSI_VM_VACT_STR_INT,
	DSI_VM_VBP_STR_INT,
	DSI_TE_TIMEOUT_INT,
	DSI_SLEEPOUT_DONE_INT,
	DSI_VM_CMD_DONE_INT,
	DSI_FRAME_DONE_INT,
	DSI_VM_DONE_INT,
	DSI_TE_RDY_INT,
	DSI_CMD_DONE_INT,
	DSI_LPRX_RD_RDY_INT
} E_DSI_INT_SEL;

typedef struct
{
    unsigned        type    : 2;
    unsigned        BTA     : 1;
    unsigned        HS      : 1;
    unsigned        CL      : 1;
    unsigned        TE      : 1;
    unsigned        Rsv     : 1;
    unsigned        RPT     : 1;
} DSI_CMDQ_CONFG, *PDSI_CMDQ_CONFIG;


//Type0 Used for DSI short packet read/write command
typedef struct
{
    u8 CONFG        ;
    u8 Data_ID      ;
    u8 Data0            ;
    u8 Data1            ;
} DSI_T0_INS, *PDSI_T0_INS;


//Type2 Used for DSI generic long packet write command
typedef struct
{
    unsigned CONFG  :8;
    unsigned Data_ID        : 8;
    unsigned WC16           : 16;
    unsigned int *pdata;
} DSI_T2_INS, *PDSI_T2_INS;

//Type3 Used for DSI frame buffer read command (short packet)
typedef struct
{
    unsigned CONFG      :8;
    unsigned Data_ID        : 8;
    unsigned mem_start0     : 8;
    unsigned mem_start1     : 8;
} DSI_T3_INS, *PDSI_T3_INS;



typedef struct
{
    unsigned char byte0;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char byte3;
} DSI_CMDQ, *PDSI_CMDQ;

typedef struct
{
    DSI_CMDQ data[32];
} DSI_CMDQ_REGS, *PDSI_CMDQ_REGS;


typedef struct
{
    unsigned TXDIV0         : 2;
    unsigned TXDIV1         : 2;
    unsigned FBK_SEL        : 2;
    unsigned FBK_DIV        : 7;
    unsigned PRE_DIV        : 2;
    unsigned RG_BR          : 2;
    unsigned RG_BC          : 2;
    unsigned RG_BIR         : 4;
    unsigned RG_BIC         : 4;
    unsigned RG_BP          : 4;
}DSI_PLL_CONFIG;


typedef struct
{
    unsigned char LPX;
    unsigned char HS_PRPR;
    unsigned char HS_ZERO;
    unsigned char HS_TRAIL;
} DSI_PHY_TIMCON0_REG, *PDSI_PHY_TIMCON0_REG;


typedef struct
{
    unsigned char TA_GO;
    unsigned char TA_SURE;
    unsigned char TA_GET;
    unsigned char DA_HS_EXIT;
} DSI_PHY_TIMCON1_REG, *PDSI_PHY_TIMCON1_REG;


typedef struct
{
    unsigned char CONT_DET;
    unsigned char RSV8;
    unsigned char CLK_ZERO;
    unsigned char CLK_TRAIL;
} DSI_PHY_TIMCON2_REG, *PDSI_PHY_TIMCON2_REG;


typedef struct
{
    unsigned char CLK_HS_PRPR;
    unsigned char CLK_HS_POST;
    unsigned char CLK_HS_EXIT;
    unsigned      rsv24     : 8;
} DSI_PHY_TIMCON3_REG, *PDSI_PHY_TIMCON3_REG;

#if 0
typedef struct
{
    DSI_PHY_TIMCON0_REG CTRL0;
    DSI_PHY_TIMCON1_REG CTRL1;
    DSI_PHY_TIMCON2_REG CTRL2;
    DSI_PHY_TIMCON3_REG CTRL3;
} DSI_PHY_TIMCON_REG, *PDSI_PHY_TIMCON_REG;
#endif

typedef enum
{
    DSI_FORMAT_RGB565,
    DSI_FORMAT_RGB666,
    DSI_FORMAT_LOOSELY_RGB666,
    DSI_FORMAT_RGB888
} DSI_FORMAT;


typedef struct
{
    u8 HS_TRAIL;
    u8 HS_PRPR;
    u8 HS_ZERO;
    u8 CLK_HS_PRPR;
    u8 CLK_HS_EXIT;
    u8 CLK_TRAIL;
    u8 CLK_ZERO;
    u8 CLK_HS_POST;
    u8 DA_HS_EXIT;

	///////////////////////////////////////////
    //Low power mode related
    ///////////////////////////////////////////
    u8 CONT_DET;
    u8 LPX;
    u8 TA_GET;
    u8 TA_SURE;
    u8 TA_GO;

	///////////////////////////////////////////
    //unused
    ///////////////////////////////////////////
    s8 pll_div2;
    s8 pll_div1;
    s8 fbk_sel;
    s8 fbk_div;

	///////////////////////////////////////////
    //Horizontal timing related
    ///////////////////////////////////////////
    u32 u32HActive;
    u32 u32HPW;
    u32 u32HBP;
    u32 u32HFP;
	///////////////////////////////////////////
    //Vertical timing related
    ///////////////////////////////////////////
    u32 u32VActive;
    u32 u32VPW;
    u32 u32VBP;
    u32 u32VFP;

    u32 u32BLLP; 				// only for burst mode
    u8 u8FPS;
    u8 u8LaneNum;
    DSI_FORMAT format;
    DSI_MODE_CTL vdo_mode;
    E_DSI_TOP_RGB_ORDER rgbOrder;

    ///////////////////////////////////////////
    //HS clock related
    ///////////////////////////////////////////
    u8 u8ClkExtSkew ;   		//clock skew setting, range 1~15,  0: use default setting
    bool bClkMode;       		/// 0: continuous-clock,
								/// 1:non-continuous clock (HS enter LP period whne VBlanking and HBlank)
    bool bNonContClkAutoMode;   /// 0:auto calculation HSTX LP period when non-continuous clock is on,
								/// 1: manually config HSTX LP period
    u16  u16HSLPeriod;       	/// range:0~2^14, take effect when bClkMode=1 and bNonContClkAutoMode=1
}LCM_PARAMS;

u32         Hal_MIPI_DSI_RegisterRead(u32 u32Addr);
void        Hal_MIPI_DSI_RegisterWrite(u32 u32Addr, u32  u32value);
void        Hal_MIPI_DSI_RegisterWriteBit(u32 u32Addr, bool bitValue, u8  u8bitpos);

DSI_STATUS  Hal_DSI_TXRX_Control(bool cksm_en,
                                bool ecc_en,
                                u8 lane_num,
                                u8 vc_num,
                                bool null_packet_en,
                                bool err_correction_en,
                                bool dis_eotp_en,
                                bool hstx_cklp_en,
                                u32 max_return_size);
DSI_STATUS  Hal_DSI_WriteShortPacket(u8 count, u8 cmd, u8 *para_list);
DSI_STATUS  Hal_DSI_WriteLongPacket(u8 count, u8 cmd, u8 *para_list);

DSI_STATUS  Hal_DSI_ReadShortPacket(u8 u8ReadBackCount, u8 u8RegAddr);
DSI_STATUS  Hal_DSI_ReadLongPacket(u8 u8ReadBackCount, u8 u8RegAddr);
DSI_STATUS  Hal_DSI_PHY_TIMCONFIG(LCM_PARAMS *lcm_params);
DSI_STATUS  Hal_DSI_Config_VDO_Timing(LCM_PARAMS *lcm_params);
DSI_STATUS  Hal_DSI_DHY_Init(void);
DSI_STATUS  Hal_DSI_Switch_Mode(DSI_MODE_CTL mode);
DSI_STATUS  Hal_DSI_SetLaneNum(DSI_TOTAL_LANE_NUM LaneNum);
void        Hal_DSI_LPLL(LCM_PARAMS *lcm_params);
LCM_PARAMS  Hal_DSI_GetInfo(void);
bool        Hal_DSI_GetDSIClkSt(void);
void        Hal_DSI_PowerOn(void);
void        Hal_DSI_PowerOff(void);
void        Hal_DSI_EnableClk(void);
void        Hal_DSI_DisableClk(void);
bool        Hal_DSI_clk_HS_state(void);
void        Hal_DSI_clk_HS_mode(bool enter);

#endif /*__HAL_MIPI_DSI_H__ */
