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

/**
* @file    drv_disp_types.h
* @version
* @brief   This module defines the data types for Display driver
*
*/

#ifndef __DRV_DISP_TYPES_H__
#define __DRV_DISP_TYPES_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "vm_types.ht"


#define ColorKeyLayer1EnShift    (8)
#define ColorKeyLayer1EnMask     (~(0x1<<ColorKeyLayer1EnShift))
#define ColorKeyLayer1OpShift    (0)
#define ColorKeyLayer1OpMask     (~(0x3<<ColorKeyLayer1OpShift))

#define ColorKeyLayer2EnShift    (9)
#define ColorKeyLayer2EnMask     (~(0x1<<ColorKeyLayer2EnShift))
#define ColorKeyLayer2OpShift    (2)
#define ColorKeyLayer2OpMask     (~(0x3<<ColorKeyLayer2OpShift))


#define ColorKeyLayer3EnShift    (10)
#define ColorKeyLayer3EnMask     (~(0x1<<ColorKeyLayer3EnShift))
#define ColorKeyLayer3OpShift    (4)
#define ColorKeyLayer3OpMask     (~(0x3<<ColorKeyLayer3OpShift))

#define   DeGammaNumbers          32
#define   EnableDispOnly          0x1
#define   DISP_MASKALL_INT        0xF00


#define DISP_REG_DAT_EN_RPRI_HI         (0x0001)
#define DISP_REG_DAT_LINE_BUF_TH        (0x0002)
#define DISP_REG_DAT_EOM_DELAY          (0x000F)


#define DISPLAY_REG_NUMBER        173
#define FORCE_UPDAGE_NUMBER       67

#define DISP_CLOCK_SRC                  0xBF83B090
#define DISP_CLOCK_DIV                  0xBF83B094


#define DISP_LAYER0_SET_MUX             0x3
#define DISP_LAYER0_SET_DeMUX           (~0x3)

#define LAYER0_SHIFT                    0
#define LAYER1_SHIFT                    2
#define LAYER2_SHIFT                    4
#define LAYER3_SHIFT                    6
#define LAYERSHIFT_FACTOR               2

#define DISP_LAYER0_SET_BITS            0x3
#define DISP_LAYER0_SET_NOT_BITS        (~0x3)

#define DISP_LAYER1_SET_BITS            0xC
#define DISP_LAYER1_SET_NOT_BITS        (~0xC)

#define DISP_LAYER2_SET_BITS            0x30
#define DISP_LAYER2_SET_NOT_BITS        (~0x30)

#define DISP_LAYER3_SET_BITS            0xC0
#define DISP_LAYER3_SET_NOT_BITS        (~0xC0)

#define DISP_BURST_LENGTH_16            (0x0<<5)
#define DISP_BURST_LENGTH_8             (0x1<<5)
#define DISP_BURST_LENGTH_4             (0x2<<5)

#define DISP_VBUF_SCAN_DEFAULT          0x0
#define DISP_VBUF_H_INCREASE            0x0
#define DISP_VBUF_H_DECREASE            0x1
#define DISP_VBUF_V_INCREASE            0x0
#define DISP_VBUF_V_DECREASE            0x2
#define DISP_VBUF_SCAN_H_FIRST          0x0
#define DISP_VBUF_SCAN_V_FIRST          0x4

#define DISP_ROTATION_90                (DISP_VBUF_SCAN_V_FIRST | DISP_VBUF_V_DECREASE)
#define DISP_ROTATION_180               (DISP_VBUF_H_DECREASE | DISP_VBUF_V_DECREASE)
#define DISP_ROTATION_270               (DISP_VBUF_SCAN_V_FIRST | DISP_VBUF_H_DECREASE)
#define DISP_X_MIRROR                   DISP_VBUF_H_DECREASE
#define DISP_Y_MIRROR                   DISP_VBUF_V_DECREASE
#define DISP_XY_MIRROR                  DISP_ROTATION_180

#define CMD_ROTATION_90                 0x1
#define CMD_ROTATION_180                0x2
#define CMD_ROTATION_270                0x3
#define CMD_X_MIRROR                    0x4
#define CMD_Y_MIRROR                    0x5
#define CMD_XY_MIRROR                   0x6

#define CMD_DISP_X_MIRROR               1
#define CMD_DISP_Y_MIRROR               2

#define   EXIF_TAG_VALUE_1              DISP_VBUF_SCAN_DEFAULT
#define   EXIF_TAG_VALUE_2              DISP_X_MIRROR
#define   EXIF_TAG_VALUE_3              (DISP_X_MIRROR | DISP_Y_MIRROR)
#define   EXIF_TAG_VALUE_4              DISP_Y_MIRROR

#define   EXIF_TAG_VALUE_5              DISP_VBUF_SCAN_V_FIRST
#define   EXIF_TAG_VALUE_6              DISP_ROTATION_90
#define   EXIF_TAG_VALUE_7              (DISP_VBUF_SCAN_V_FIRST | DISP_X_MIRROR | DISP_Y_MIRROR)
#define   EXIF_TAG_VALUE_8              DISP_ROTATION_270


#define   DISPLAY_ENABLE                0x1
#define   DISPLAY_DISABLE               0x0


#define DISP_TRACE                  (_CUS2|LEVEL_17)
#define DISP_TRACE2                 (_CUS2|LEVEL_16)

/*--------------------------------------------------------------------------*/
/* MACRO DEFINITION                                                         */
/*--------------------------------------------------------------------------*/

#define WRITE_DISP_REG(addr, type, data)  ((*(volatile type *)(addr)) = (data))
#define READ_DISP_REG(addr, type, data)   ((data) = (*(volatile type *)(addr)))

/*--------------------------------------------------------------------------*/
/* DATA TYPE DEFINITION                                                     */
/*--------------------------------------------------------------------------*/



///Define Display Source Color Key Operation Moded Selection
typedef enum
{
    DISP_SCK_OPMODE_FALSE = 0,
    DISP_SCK_OPMODE_TRUE,
    DISP_SCK_OPMODE_MAX
} DispSckOpMode_e;

///Define Display Source Color Key Operation Selection
typedef enum
{
    DISP_SCK_OUT_SRC2DST = 0,
    DISP_SCK_OUT_BKC,
    DISP_SCK_OUT_MAX
} DispSckOutSel_e;

///Define Display Alpha Value of Alpha Blending
typedef enum
{
    DISP_ALPHA_BLENDING_0 = 0,
    DISP_ALPHA_BLENDING_1,
    DISP_ALPHA_BLENDING_A,
    DISP_ALPHA_BLENDING_1_A,
    DISP_ALPHA_BLENDING_MAX
} DispAlphaDef_e;

///Define Display Alpha Value of Any Possible Selection
typedef enum
{
    ///Display alpha value from layer global alpha
    DISP_ALPHA_SEL_GA = 0,
    ///Display alpha value from layer per pixel alpha
    DISP_ALPHA_SEL_PIXEL,
    ///Display alpha value from layer channel R
    DISP_ALPHA_SEL_R,
    ///Display alpha value from layer channel G
    DISP_ALPHA_SEL_G,
    ///Display alpha value from layer channel B
    DISP_ALPHA_SEL_B,
    DISP_ALPHA_SEL_MAX
} DispAlphaSel_e;

typedef enum
{
    DISP_YC_NORMAL = 0,
    DISP_YC_SWAP = 1,
    DISP_CBCR_SWAP = 2,
    DISP_Y0Y1_SWAP = 4,
} DispYCSwap_e;


//Mask DISP interrupt
//[0] mask int from frame done
//[1] mask int from fmark pulse with delay cnt
//[2] mask int from disp vsync out (vs_mode)
//[3] mask int from LCM fmark (fmark mode)

typedef enum
{
    DISP_INT_FRAME_DONE = 0,
    DISP_INT_FMARK_PULSE,
    DISP_INT_VSYNC,
    DISP_INT_LCM_FMARK,
} DispIntType_e;

typedef struct
{
    u8 SCK_R_L;
    u8 SCK_R_H;
    u8 SCK_G_L;
    u8 SCK_G_H;
    u8 SCK_B_L;
    u8 SCK_B_H;
} DispSckValue_t;

typedef struct
{
    DispAlphaSel_e      AlphaCoef;
    DispAlphaDef_e      AlphaLowerDef;
    DispAlphaDef_e      AlphaUpperDef;
    u16                 u16Alpha;
} DispAlphaSet_t;



///Define Display Video Buffer Format
typedef enum
{
    DISP_BUF_ARGB1555 = 0,
    DISP_BUF_ARGB4444 = 1,
    DISP_BUF_ARGB8888 = 2,
    DISP_BUF_RGB565   = 3,
    DISP_BUF_RGB888   = 4,
    DISP_BUF_4BITPAL  = 5,
    DISP_BUF_YUV422   = 6,
    DISP_BUF_ARGB6666 = 7,
    DISP_BUF_ARGB8565 = 8,
    DISP_BUF_FMT_MAX,
} DispBufFmt_e;

///Define Enable Selection of Display Basic Property
typedef enum
{
    /// Enable Main Display Engine = 0;
    DISP_MAIN_EN = 0,
    /// Enable Sub Display Engine = 1;
    DISP_SUB_EN,
    /// Enable Dither function = 2;
    DISP_DITHER_EN,
    /// Enable Single frame trigger = 3;
    DISP_SINGLEFRAME_EN,
    /// Enable Display Video Buffer = 4;
    DISP_V0_EN,
    /// Enable Display G0 Buffer= 5;
    DISP_G0_EN,
    /// Enable Display G1 Buffer = 6;
    DISP_G1_EN,
    /// Enable Display G3D Buffer = 7;
    DISP_G3D_EN,

    DISP_PROPERTY_MAX
} DispProperty_e;

typedef enum
{
    DISP_RSMODE_CMD = 0,
    DISP_RSMODE_DATA,
} DispRSInv_e;

typedef enum
{
    DISP_WRITE_LCD_CMD = 0,
    DISP_WRITE_LCD_DATA,
}DispLCDWrite_e;

///Define Display Window Selection
typedef enum
{
    /// Select Main Display Window = 0;
    DISP_CHIPSEL_MAIN = 0,
    /// Select SUB Display Window = 1;
    DISP_CHIPSEL_SUB,
    /// Select NO Display Window = 2;
    DISP_CHIPSEL_MAX
}  DispChipSel_e;


///Define LCM Mode
typedef enum
{
    /// DISP LCM Mode I80 = 0;
    DISP_LCM_MD_I80 = 0,
    /// DISP LCM Mode M68 = 1;
    DISP_LCM_MD_M68,
    /// DISP LCM Mode CCIR656 = 2;
    DISP_LCM_MD_CCIR656,
    /// DISP LCM Mode RGB Interface = 3;
    DISP_LCM_MD_RGBInt,
    DISP_LCM_MD_MAX,
}DispLcmMode_e;

///Define LCM Bus Width
typedef enum
{
    /// DISP LCM Bus Width with 8BP = 0;
    DISP_LCM_BUS_W_8BP = 0,
    /// DISP LCM Bus Width with 16BP = 1;
    DISP_LCM_BUS_W_16BP,
    DISP_LCM_BUS_W_MAX
}DispLcmBusWidth_e;


///Define LCM Bus Format
typedef enum
{
    /// LCM Bus Format 666_18 = 0;
    DISP_LCM_BUS_FMT_666_18 = 0,
    /// LCM Bus Format 666_99 = 1;
    DISP_LCM_BUS_FMT_666_99,
    /// LCM Bus Format 666_666 = 2;
    DISP_LCM_BUS_FMT_666_666,
    /// LCM Bus Format 565_16 = 3;
    DISP_LCM_BUS_FMT_565_16,
    /// LCM Bus Format 565_88 = 4;
    DISP_LCM_BUS_FMT_565_88,
    /// LCM Bus Format 444_12 = 5;
    DISP_LCM_BUS_FMT_444_12,
    /// LCM Bus Format 444_84 = 6;
    DISP_LCM_BUS_FMT_444_84,
    /// LCM Bus Format 332_8 = 7;
    DISP_LCM_BUS_FMT_332_8,
    /// LCM Bus Format 888_24 = 8;
    DISP_LCM_BUS_FMT_888_24,
    /// LCM Bus Format 888_168 = 9;
    DISP_LCM_BUS_FMT_888_168,
    /// LCM Bus Format 888_888 = A;
    DISP_LCM_BUS_FMT_888_888,

    /// LCM Bus Format 666_888 = B;
    DISP_LCM_BUS_FMT_666_24,

    /// LCM Bus Format 666_99 = C; (align to 18-bits MSB)
    /// LCM Bus Format 565_88 = D; (align to 16-bits MSB)
    /// LCM Bus Format 565_18 = E; (b0 & b8 tie 0)

    DISP_LCM_BUS_FMT_MAX
} DispLcmBusFmt_e;

typedef enum
{
    DISP_SHARE_COMMANDBUS = 0,
    DISP_OWN_COMMANDBUS,
} DISP_COMMAND_PHASE;



//-------------------------------------------------
/// Define Display IRQ Status.
typedef struct
{
    u8 bClear : 4;
    u8 bForce : 4;
    u8 bMask : 4;
} DispIRQ_t;


///Define Color Key Enable Parameter
typedef enum
{
    /// R Color Key = 0;
    DISP_CLRKEY_R = 0,
    /// G Color Key = 1;
    DISP_CLRKEY_G,
    /// Enable B Color Key = 2;
    DISP_CLRKEY_B,
    DISP_CLRKEY_MAX
} DispClrKey_e;

typedef enum
{
    DISP_NO_FORCEUPDATE = 0,
    DISP_FORCEUPDATE    = 1,
    DISP_WAIT_INTERRUPT = 2,
} DispUpdateMode_e;





///Define Display Buffer Showing Style
typedef enum
{
    DISPBUF_STYLE_NORMAL = 0,
    DISPBUF_STYLE_PARTIAL,
    DISPBUF_STYLE_MAX
} DispBufStyle_e;



///Define Display RGB Component Order
typedef enum
{
    DISP_COMP_R = 0,
    DISP_COMP_G,
    DISP_COMP_B,
    DISP_COMP_MAX
} DispComp_e;


#define DISP_ORDER_RGB      ( DISP_COMP_R + (DISP_COMP_G << 2) + (DISP_COMP_B << 4) )
#define DISP_ORDER_BGR      ( DISP_COMP_B + (DISP_COMP_G << 2) + (DISP_COMP_R << 4) )
#define DISP_ORDER_GBR      ( DISP_COMP_G + (DISP_COMP_B << 2) + (DISP_COMP_R << 4) )
#define DISP_ORDER_RBG      ( DISP_COMP_R + (DISP_COMP_B << 2) + (DISP_COMP_G << 4) )
#define DISP_ORDER_GRB      ( DISP_COMP_G + (DISP_COMP_R << 2) + (DISP_COMP_B << 4) )
#define DISP_ORDER_BRG      ( DISP_COMP_B + (DISP_COMP_R << 2) + (DISP_COMP_B << 4) )


///Define Display Layer Selection
typedef enum
{
    ///Display layer select video
    DISP_BUF_VIDEO = 0,
    ///Display layer select grphaic 0
    DISP_BUF_G0,
    ///Display layer select grphaic 1
    DISP_BUF_G1,
    ///Display layer select G3D
    DISP_BUF_G3D,
    DISP_BUF_MAX
} DispBufferSel_e;

///Define Display Window Selection
typedef enum
{
    DISP_LAYER_0   = 0,
    DISP_LAYER_1   = 1,
    DISP_LAYER_2   = 2,
    DISP_LAYER_3   = 3,
    DISP_LAYER_MAX
} DispLayers_e;


///Define Display Global Register Sequence
typedef enum
{
    Disp_LCM_Interface = 0,
    Disp_Buffer_Format,
    Disp_Layer_Selection,
    DISP_Global_RegNum
} Disp_RegSequece;

typedef enum
{
    DISP_FIRSTBUFFER = 0,
    DISP_SECONDBUFFER,
    DISP_SINGLEBUFFER,
    DISP_ATVBUFFER,
} DispFlipBuffer_e;

typedef enum
{
    DISP2LCM_CONTINUE = 0,
    DISP2LCM_SINGLE,
} DispToLcmMode_e;

typedef enum
{
    G3D_PIXBYTE_16BIT = 2,
    G3D_PIXBYTE_32BIT = 4,
} DispG3DPixByte_e;

typedef enum
{
    DISP_G3D_MD_LINEAR = 0,
    DISP_G3D_MD_TILE,
} DispG3DTileMD_e;

typedef enum
{
    DISP_G3D_TILEBPP_16 = 0,
    DISP_G3D_TILEBPP_32,
} DispG3DTileBpp_e;

typedef enum
{
    DISP_G3D_ADRCTRL_SW = 0,
    DISP_G3D_ADRCTRL_HW,
} DispG3DAdrCtrl_e;

typedef enum
{
    DISP_G3D_ACKCTRL_START = 0,
    DISP_G3D_ACKCTRL_DONE,
} DispG3DAckCtrl_e;

typedef enum
{
    DISP_ORDER_UYVY = 0,
    DISP_ORDER_YUYV = 1,
    DISP_ORDER_VYUY = 2,
    DISP_ORDER_UY1VY0 = 4,
} DispYUVOrder_e;



typedef enum
{
    DISP_NORMAL_PANEL = 0,
    DISP_FMARK_PANEL,
    DISP_VSYNC_PANEL,
    DISP_RGB_PANEL,
	DISP_SPI_PANEL,
} DispPanelType_e;

typedef enum
{
    DISP_SHARED_WITH_PSRAM = 0,
    DISP_NONSHARED_WITH_PSRAM,
} DispSharedStatus_e;

//CLKGEN_6MHZ,
//CLKGEN_10MHZ,
//CLKGEN_13MHZ,
//CLKGEN_19P5MHZ,
//CLKGEN_26MHZ,


typedef enum
{
	DISP_CLOCK_6M = 0,
    DISP_CLOCK_10M,
    DISP_CLOCK_10P3M,
    DISP_CLOCK_13M,
	DISP_CLOCK_19P5M,
	DISP_CLOCK_26M,
    DISP_CLOCK_30M,	  
    DISP_CLOCK_39P8M,    
	DISP_CLOCK_52M,
	DISP_CLOCK_60M,    

	DISP_CLOCK_READ = 0x100,
	DISP_CLOCK_WRITE,
} DISP_CLOCK_SEL;

typedef enum
{
	DISP_SLCM_CLOCK_6M = 0,
    DISP_SLCM_CLOCK_13M,
	DISP_SLCM_CLOCK_19P5M,
	DISP_SLCM_CLOCK_26M,
	DISP_SLCM_CLOCK_31P2M,
    DISP_SLCM_CLOCK_39M,
    DISP_SLCM_CLOCK_44P5M,
    DISP_SLCM_CLOCK_52M,
    DISP_SLCM_CLOCK_60M,

	DISP_SLCM_CLOCK_READ = 0x100,
	DISP_SLCM_CLOCK_WRITE,
} DISP_SLCM_CLOCK_SEL;

typedef enum
{
	DISP_UPDATE_NORMAL = 0,
	DISP_UPDATE_NONOS,
} DISP_UPDATE_TYPE;

typedef enum
{
	DISPFUN_ERR_OK = 0,
	DISPFUN_ERR_FAIL,
	DISPFUN_ERR_UNSUPPORT,
} DISPFUN_ERRCODE;

typedef enum
{
    DISP_FROM_BUFFER = 0,
    DISP_SCL_DIRECT,
}DISPSCL_MODE_e;

typedef enum
{
    DISP_DELAY_LV0 = 0,
    DISP_DELAY_LV1,
    DISP_DELAY_LV2,
    DISP_DELAY_LV3,
    DISP_DELAY_LV4,
}DispTimingDelay_e;

typedef enum
{
    DISP_PIN_WR = 0,
    DISP_PIN_RD,
}DispAdjustPinSel_e;


typedef enum
{
    SingleCMD_Data = 0,
    Double8BitCMD_Data_HL,
    Double8BitCMD_Data_LH,
    Double9BitCMD_Data_HL,
    Double9BitCMD_Data_LH
} DispCmdDataType_e;

/*****************************************************************/
// Data struct
//-------------------------------------------------

/// Define the Display Properties.
typedef struct
{
    union
    {
        struct
        {
            u16  bEnMain   : 1;
            u16  bEnSub    : 1;
            u16  bDither   : 1;
            u16  bSingleFM : 1;
            u16  bV0       : 1;
            u16  bG0       : 1;
            u16  bG1       : 1;
            u16  bG3D      : 1;
            u16  b7Reserve : 7;
            u16  bSelfTest : 1;
        } dispReg;
        u16  u16Disp_Prop;
    }param;
} DispProperty_t, *pDispProperty;

//-------------------------------------------------
/// Define the Display Interfaces.
typedef struct
{
    /* Lcm */
    union
    {
        struct
        {
            u8 u8LcmMode : 2;
            u8 u8LcmBusWidth : 2;
            u8 u8LcmBusFmt : 4;
        }lcmReg;
        u8 u8LCM_Interface;
    }param;
} DispItf_t;

//-------------------------------------------------
/// Define the Display Background Color Component.
typedef struct
{
    u8 u8BkcR;
    u8 u8BkcG;
    u8 u8BkcB;
} DispBKC_t;

//-------------------------------------------------
/// Define the Display Color Component Order.
typedef struct
{
    /* color component & color order */
    union
    {
        struct
        {
            u8 u8DispC0 : 2;
            u8 u8DispC1 : 2;
            u8 u8DispC2 : 2;
            u8 u8Order : 1;
        }reg;
        u16  u16Disp_Comp_Ord;
    }param;
} DispCompOrd_t;


//-------------------------------------------------
/// Define Display LCM Status.
typedef struct
{
    union
    {
        struct
        {
            u8 bLcm_cs_m_inv : 1;
            u8 bLcm_cs_s_inv : 1;
            u8 bLcm_rs_inv : 1;
            u8 bLcm_en_inv : 1;
            u8 bLcm_rw_inv : 1;
        }reg;
        u16  u16LCM_CSC;
    }param;
} DISP_LCM_STATE;


//-------------------------------------------------
/// Define Display De-Gamma Settings.
typedef struct
{
    u8 u8Offset;
    u8 u8Slope;
} DISP_DEGAMMA;


typedef struct
{
    u8  EnBKClr;
    u8  u8R;
    u8  u8G;
    u8  u8B;
} DispBKClr_t;


//-------------------------------------------------
/// Define Display Buffer Api Structure.
typedef struct
{
    u16                 u16Width;
    u16                 u16Height;
    DispBufFmt_e        u16Format;
    DispBufferSel_e     u16Buf_Sel;
    DispLayers_e        u16Layer_Sel;

    u32                 u32BufSize;
    u32                 u32MemoryAddr;
    u16                 u16MemoryPitch;
    u16                 u16OnMemoryX0;
    u16                 u16OnMemoryY0;
    s16                 s16OnScreenX0;
    s16                 s16OnScreenY0;
    s16                 s16OnScreenXEnd;
    s16                 s16OnScreenYEnd;
    DispAlphaSet_t      Alphas;
    DispSckValue_t      SCKValue;
    u8                  SCKEn;
    DispSckOpMode_e     SCK_OPMODE;
    DispSckOutSel_e     SCK_OP;
    DispYUVOrder_e      YUVOrder;
    DispBKClr_t         BKClr;
} DispLayerProp_t;

typedef struct
{
    u16     u16X0;
    u16     u16Y0;
    u16     u16XEnd;
    u16     u16YEnd;
} DispOnScrBound_t, *pDispOnScrBound;

typedef struct
{
	u16  x;
	u16  y;
	u16  stride;
	u16  width;
	u16  height;

}DISP_UpdateRegion;

typedef void (*PfnIntCallback)(void);

typedef struct
{
    DispLayerProp_t      DispBuf[DISP_LAYER_MAX];
    //DispAlphaSet_t       Alphas[DISP_LAYER_MAX];

    //DispSckValue_t       sck;
	DISP_UpdateRegion    region;
    u8                   u8VSyncEn;
    u8                   u8FMarkEn;
    DISPSCL_MODE_e       SclMode;
    u8                   isFire;

    DispChipSel_e        Panel_Sel;
    PfnIntCallback       pFinishUserCallback;
} LayerFormat;

typedef struct _DISP_INIT_
{
    DispLcmMode_e       LCM_MODE;
    DispLcmBusWidth_e   LCM_BUS_WIDTH;
    DispLcmBusFmt_e     LCM_BUS_FMT;
    DispPanelType_e     PANEL_TYPE;
    u32                 PANEL_PARAMETER;
    u16                 DISP_CLR_ORDER;
} DISPINIT_PARAS;


#endif //__DRV_DISP_TYPES_H__
