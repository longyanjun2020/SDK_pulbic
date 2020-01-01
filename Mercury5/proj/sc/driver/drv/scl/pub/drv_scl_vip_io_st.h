////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2011 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 *  @file drv_scl_vip_io_st.h
 *  @brief hvsp Driver struct parameter interface
 */

/**
* \ingroup sclvip_group
* @{
*/

#ifndef __DRV_SCL_VIP_IO_ST_H__
#define __DRV_SCL_VIP_IO_ST_H__

//=============================================================================
// Defines
//=============================================================================
#define DRV_SCLVIP_VERSION                        0x0101


#define DRV_SCLVIP_IO_LCE_CURVE_SECTION_NUM       16          ///< DRV_SCLVIP_IO_LCE_CURVE_SECTION_NUM
#define DRV_SCLVIP_IO_PEAKING_BAND_NUM            8           ///< DRV_SCLVIP_IO_PEAKING_BAND_NUM
#define DRV_SCLVIP_IO_PEAKING_ADP_Y_LUT_NUM       8           ///< DRV_SCLVIP_IO_PEAKING_ADP_Y_LUT_NUM
#define DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM       16          ///< DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM
#define DRV_SCLVIP_IO_DLC_HISTOGRAM_SECTION_NUM   7           ///< DRV_SCLVIP_IO_DLC_HISTOGRAM_SECTION_NUM
#define DRV_SCLVIP_IO_DLC_HISTOGRAM_REPORT_NUM    8           ///< DRV_SCLVIP_IO_DLC_HISTOGRAM_REPORT_NUM
#define DRV_SCLVIP_IO_DLC_LUMA_SECTION_NUM        64          ///< DRV_SCLVIP_IO_DLC_LUMA_SECTION_NUM
#define DRV_SCLVIP_IO_IHC_COLOR_NUM               16          ///< DRV_SCLVIP_IO_IHC_COLOR_NUM
#define DRV_SCLVIP_IO_IHC_USER_COLOR_NUM          16          ///< DRV_SCLVIP_IO_IHC_USER_COLOR_NUM
#define DRV_SCLVIP_IO_ICE_COLOR_NUM               16          ///< DRV_SCLVIP_IO_ICE_COLOR_NUM
#define DRV_SCLVIP_IO_IBC_COLOR_NUM               16          ///< DRV_SCLVIP_IO_IBC_COLOR_NUM
#define DRV_SCLVIP_IO_FCC_YWIN_LUT_ENTRY_NUM      17          ///< DRV_SCLVIP_IO_FCC_YWIN_LUT_ENTRY_NUM
#define DRV_SCLVIP_IO_NLM_DISTWEIGHT_NUM          9           ///< DRV_SCLVIP_IO_NLM_DISTWEIGHT_NUM
#define DRV_SCLVIP_IO_NLM_WEIGHT_NUM              32          ///< DRV_SCLVIP_IO_NLM_WEIGHT_NUM
#define DRV_SCLVIP_IO_NLM_LUMAGAIN_NUM            64          ///< DRV_SCLVIP_IO_NLM_LUMAGAIN_NUM
#define DRV_SCLVIP_IO_NLM_POSTLUMA_NUM            16          ///< DRV_SCLVIP_IO_NLM_POSTLUMA_NUM
#define DRV_SCLVIP_IO_CMDQ_MEM_196K               0x0030000   ///< DRV_SCLVIP_IO_CMDQ_MEM_164K
#define DRV_SCLVIP_IO_CMDQ_MEM_164K               0x0028000   ///< DRV_SCLVIP_IO_CMDQ_MEM_164K
#define DRV_SCLVIP_IO_CMDQ_MEM_128K               0x0020000   ///< DRV_SCLVIP_IO_CMDQ_MEM_128K
#define DRV_SCLVIP_IO_CMDQ_MEM_64K                0x0010000   ///< DRV_SCLVIP_IO_CMDQ_MEM_64K
#define DRV_SCLVIP_IO_CMDQ_MEM_32K                0x0008000   ///< DRV_SCLVIP_IO_CMDQ_MEM_32K
#define DRV_SCLVIP_IO_CMDQ_MEM_16K                0x0004000   ///< DRV_SCLVIP_IO_CMDQ_MEM_16K
#define DRV_SCLVIP_IO_CMDQ_MEM_TEST               0x0001000   ///< DRV_SCLVIP_IO_CMDQ_MEM_TEST
#define DRV_SCLVIP_IO_VTRACK_KEY_SETTING_LENGTH       8       ///< DRV_SCLVIP_IO_VTRACK_KEY_SETTING_LENGTH
#define DRV_SCLVIP_IO_VTRACK_SETTING_LENGTH           23      ///< DRV_SCLVIP_IO_VTRACK_SETTING_LENGTH


//=============================================================================
// enum
//=============================================================================
/// @cond
typedef enum
{
    E_DRV_SCLVIP_IO_ID_1,
    E_DRV_SCLVIP_IO_ID_NUM,
} DrvSclVipIoIdType_e;
/// @endcond

//=============================================================================
// enum
//=============================================================================
/**
* source type of SCLVIP
*/
typedef enum
{
    E_DRV_SCLVIP_IO_SRC_ISP,  ///< VIP src ISP
    E_DRV_SCLVIP_IO_SRC_BT656,///< VIP src BT656
    E_DRV_SCLVIP_IO_SRC_DRAM, ///< VIP src DRAM
    E_DRV_SCLVIP_IO_SRC_NUM,  ///< VIP src max number
}__attribute__ ((__packed__))DrvSclVipIoSrcType_e;

/**
* LCE_Y_AVE select type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_LCE_Y_AVE_5X11   = 0x0,      ///<  LCE_Y_AVE type: 5X11
    E_DRV_SCLVIP_IO_LCE_Y_AVE_5X7    = 0x10,     ///<  LCE_Y_AVE type: 5X7
}__attribute__ ((__packed__))DrvSclVipIoLceYAveSelType_e;


/**
* UVC_ADP_Y input select type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_UVC_ADP_Y_INPUT_SEL_UVC_LOCATE    = 0x0,      ///<  UVC_ADP_Y input select type:
    E_DRV_SCLVIP_IO_UVC_ADP_Y_INPUT_SEL_RGB_Y_OUTPUT  = 0x40,     ///<  UVC_ADP_Y input select type: RGB Y Output
    E_DRV_SCLVIP_IO_UVC_ADP_Y_INPUT_SEL_DLC_Y_INPUT   = 0x80,     ///<  UVC_ADP_Y input select type: DLC Y Input
    E_DRV_SCLVIP_IO_UVC_ADP_Y_INPUT_SEL_RGB_Y_INPUT   = 0xC0,     ///<  UVC_ADP_Y input select type: RGB Y Input
}__attribute__ ((__packed__))DrvSclVipIoUvcAdpYInputSelType_e;

/**
* LDC bypass type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_LDC_MENULOAD,         ///< LDC menuload
    E_DRV_SCLVIP_IO_LDC_BYPASS,           ///< LDC bypass
    E_DRV_SCLVIP_IO_LDC_BYPASS_TYPE_NUM,  ///< number of LDC bypass type
}__attribute__ ((__packed__))DrvSclVipIoLdcBypassType_e;
/**
* LDCLC Bank Mode Type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_LDCLCBANKMODE_64,  ///< LDCLCBANKMODE: 64p
    E_DRV_SCLVIP_IO_LDCLCBANKMODE_128, ///< LDCLCBANKMODE: 128p
}__attribute__ ((__packed__))DrvSclVipIoLdclcBankModeType_e;

/**
* LDC_422_444 type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_LDC_422_444_DUPLICATE = 0x1,  ///< LDC_422_444 type: duplicate
    E_DRV_SCLVIP_IO_LDC_422_444_QUARTER   = 0x2,  ///< LDC_422_444 type: quarter
    E_DRV_SCLVIP_IO_LDC_422_444_AVERAGE   = 0x3,  ///< LDC_422_444 type: average
}__attribute__ ((__packed__))DrvSclVipIoLdc422444Type_e;
/**
* LDC_444_422 type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_LDC_444_422_DROP      = 0x0,  ///< LDC_444_422 type: drop
    E_DRV_SCLVIP_IO_LDC_444_422_AVERAGE   = 0x4,  ///< LDC_444_422 type: average
}__attribute__ ((__packed__))DrvSclVipIoLdc444422Type_e;
/**
* NLM_Average Type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_NLM_Average_3x3_mode = 0x0,   ///< NLM_Average Type: 3x3
    E_DRV_SCLVIP_IO_NLM_Average_5x5_mode = 0x2,   ///< NLM_Average Type: 5x5
}__attribute__ ((__packed__))DrvSclVipIoNlmAverageType_e;
/**
* NLM_DSW Type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_NLM_DSW_16x8_mode     = 0x0,  ///< NLM_DSW Type: 16x8
    E_DRV_SCLVIP_IO_NLM_DSW_32x16_mode    = 0x20, ///< NLM_DSW Type: 32x16
}__attribute__ ((__packed__))DrvSclVipIoNlmDswType_e;
/**
* FCC_Y_DIS type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_FCC_Y_DIS_CR_DOWN,            ///< FCC_Y_DIS type: cr down
    E_DRV_SCLVIP_IO_FCC_Y_DIS_CR_UP,              ///< FCC_Y_DIS type: cr up
    E_DRV_SCLVIP_IO_FCC_Y_DIS_CB_DOWN,            ///< FCC_Y_DIS type: cb down
    E_DRV_SCLVIP_IO_FCC_Y_DIS_CB_UP,              ///< FCC_Y_DIS type: cb up
    E_DRV_SCLVIP_IO_FCC_Y_DIS_NUM,                ///< number of FCC_Y_DIS type
}__attribute__ ((__packed__))DrvSclVipIoFccYDisType_e;
/**
* IHC_ICE_ADP_Y type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_IHC_ICE_ADP_Y_SECTION_0,      ///< IHC_ICE_ADP_Y type: section 0
    E_DRV_SCLVIP_IO_IHC_ICE_ADP_Y_SECTION_1,      ///< IHC_ICE_ADP_Y type: section 1
    E_DRV_SCLVIP_IO_IHC_ICE_ADP_Y_SECTION_2,      ///< IHC_ICE_ADP_Y type: section 2
    E_DRV_SCLVIP_IO_IHC_ICE_ADP_Y_SECTION_3,      ///< IHC_ICE_ADP_Y type: section 3
    E_DRV_SCLVIP_IO_IHC_ICE_ADP_Y_SECTION_NUM,    ///< number of IHC_ICE_ADP_Y type
}__attribute__ ((__packed__))DrvSclVipIoIhcIceAdpYSectionType_e;
/**
*  Controlling configuration of SclVip
*/
typedef enum
{
    E_DRV_SCLVIP_IO_ACK_CONFIG           = 0x1,      ///< ACK
    E_DRV_SCLVIP_IO_IBC_CONFIG           = 0x2,      ///< IBC
    E_DRV_SCLVIP_IO_IHCICC_CONFIG        = 0x4,      ///< ICCIHC
    E_DRV_SCLVIP_IO_ICC_CONFIG           = 0x8,      ///< ICE
    E_DRV_SCLVIP_IO_IHC_CONFIG           = 0x10,     ///< IHC
    E_DRV_SCLVIP_IO_FCC_CONFIG           = 0x20,     ///< FCC
    E_DRV_SCLVIP_IO_UVC_CONFIG           = 0x40,     ///< UVC
    E_DRV_SCLVIP_IO_DLC_HISTOGRAM_CONFIG = 0x80,     ///< DLC Histogram
    E_DRV_SCLVIP_IO_DLC_CONFIG           = 0x100,    ///< DLC
    E_DRV_SCLVIP_IO_LCE_CONFIG           = 0x200,    ///< LCE
    E_DRV_SCLVIP_IO_PEAKING_CONFIG       = 0x400,    ///< Peaking
    E_DRV_SCLVIP_IO_NLM_CONFIG           = 0x800,    ///< NLM
    E_DRV_SCLVIP_IO_LDC_MD_CONFIG        = 0x1000,   ///< LDCMD
    E_DRV_SCLVIP_IO_LDC_DMAP_CONFIG      = 0x2000,   ///< LDCDMAP
    E_DRV_SCLVIP_IO_LDC_SRAM_CONFIG      = 0x4000,   ///< LDC SRAM
    E_DRV_SCLVIP_IO_LDC_CONFIG           = 0x8000,   ///< LDC
    E_DRV_SCLVIP_IO_CONFIG               = 0x40000,  ///< 19 bit to control 19 IOCTL
}__attribute__ ((__packed__))DrvSclVipIoConfigType_e;
/**
* Vtrack enable/disalbe type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_VTRACK_ENABLE_ON,      ///< Vtrack on
    E_DRV_SCLVIP_IO_VTRACK_ENABLE_OFF,     ///< Vtrack off
    E_DRV_SCLVIP_IO_VTRACK_ENABLE_DEBUG,   ///< Vtrack debug
}DrvSclVipIoVtrackEnableType_e;
/**
* Controlling type of AIP
*/
typedef enum
{
    E_DRV_SCLVIP_IO_AIP_YEE = 0,           ///< yee
    E_DRV_SCLVIP_IO_AIP_YEE_AC_LUT,        ///< yee ac lut
    E_DRV_SCLVIP_IO_AIP_WDR_GLOB,          ///< wdr glob
    E_DRV_SCLVIP_IO_AIP_WDR_LOC,           ///< wdr loc
    E_DRV_SCLVIP_IO_AIP_MXNR,              ///< mxnr
    E_DRV_SCLVIP_IO_AIP_UVADJ,             ///< uvadj
    E_DRV_SCLVIP_IO_AIP_XNR,               ///< xnr
    E_DRV_SCLVIP_IO_AIP_YCUVM,             ///< ycuvm
    E_DRV_SCLVIP_IO_AIP_COLORTRAN,         ///< ct
    E_DRV_SCLVIP_IO_AIP_GAMMA,             ///< gamma
    E_DRV_SCLVIP_IO_AIP_422TO444,          ///< 422to444
    E_DRV_SCLVIP_IO_AIP_YUVTORGB,          ///< yuv2rgb
    E_DRV_SCLVIP_IO_AIP_GM10TO12,          ///< 10 to 12
    E_DRV_SCLVIP_IO_AIP_CCM,               ///< ccm
    E_DRV_SCLVIP_IO_AIP_HSV,               ///< hsv
    E_DRV_SCLVIP_IO_AIP_GM12TO10,          ///< gm12to10
    E_DRV_SCLVIP_IO_AIP_RGBTOYUV,          ///< rgb2yuv
    E_DRV_SCLVIP_IO_AIP_444TO422,          ///< 4442422
    E_DRV_SCLVIP_IO_AIP_NUM,               ///< Num
}DrvSclVipIoAipType_e;

/**
* AIP Sram controlling type
*/
typedef enum
{
    E_DRV_SCLVIP_IO_AIP_SRAM_GAMMA_Y, ///< gamma y
    E_DRV_SCLVIP_IO_AIP_SRAM_GAMMA_U, ///< gamma u
    E_DRV_SCLVIP_IO_AIP_SRAM_GAMMA_V, ///< gamma v
    E_DRV_SCLVIP_IO_AIP_SRAM_GM10to12_R, ///< gamma R
    E_DRV_SCLVIP_IO_AIP_SRAM_GM10to12_G, ///< gamma G
    E_DRV_SCLVIP_IO_AIP_SRAM_GM10to12_B, ///< gamma B
    E_DRV_SCLVIP_IO_AIP_SRAM_GM12to10_R, ///< gamma R
    E_DRV_SCLVIP_IO_AIP_SRAM_GM12to10_G, ///< gamma G
    E_DRV_SCLVIP_IO_AIP_SRAM_GM12to10_B, ///< gamma B
    E_DRV_SCLVIP_IO_AIP_SRAM_WDR, ///< wdr
}DrvSclVipIoAipSramType_e;


/// @cond
/**
* Used to setup the error type of hvsp device
*/
typedef enum
{
    E_DRV_SCLVIP_IO_ERR_OK    =  0, ///< No Error
    E_DRV_SCLVIP_IO_ERR_FAULT = -1, ///< Fault
    E_DRV_SCLVIP_IO_ERR_INVAL = -2, ///< Invalid value
    E_DRV_SCLVIP_IO_ERR_MULTI = -3, ///< MultiInstance Fault
}DrvSclVipIoErrType_e;
/// @endcond

//=============================================================================
// struct
//=============================================================================

/**
* version of SclVip
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    u32   u32Version;      ///< version
    u32   VerChk_Size;     ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclVipIoVersionConfig_t;

/**
* Setup CMDQ configuration
*/
typedef struct
{
    bool bEn;         ///<  enable CMDQ
    u8 u8framecnt;    ///<  assign framecount
}DrvSclVipIoFcConfig_t;
/**
* Setup AIP configuration
*/
typedef struct
{
    u32   VerChk_Version ;          ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;   ///< CMDQ configuration
    u32 u32Viraddr;                 ///< Base address of AIP setting
    DrvSclVipIoAipType_e enAIPType; ///< AIP Type
    u32   VerChk_Size;              ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoAipConfig_t;
/**
* Setup AIP SRAM Configuration
*/
typedef struct
{
    u32   VerChk_Version ;              ///< structure version
    u32 u32Viraddr;                     ///< Base Address of AIP SRAM setting
    DrvSclVipIoAipSramType_e enAIPType; ///< AIP SRAM type
    u32   VerChk_Size;                  ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoAipSramConfig_t;

/**
* Setup MCNR configuration
*/
typedef struct
{
    u32   VerChk_Version ;          ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;   ///< CMDQ configuration
    bool bEnMCNR;                   ///< MCNR On/Off
    bool bEnCIIR;                   ///< CIIR On/Off
    u32  u32Viraddr;                ///< Base Address of MCNR setting
    u32  VerChk_Size;               ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoMcnrConfig_t;


/**
* Setup LDC On/Off configuration
*/
typedef struct
{
    u8 bLdc_path_sel;   ///<  reg_ldc_path_sel
    u8 bEn_ldc;         ///<  reg_en_ldc(nonuse just bypass)
} __attribute__ ((__packed__)) DrvSclVipIoLdcOnOffConfig_t;
/**
* Setup LDC 444/422 configuration
*/
typedef struct
{
    DrvSclVipIoLdc422444Type_e en422to444;    ///<  reg_422to444_md
    DrvSclVipIoLdc444422Type_e en444to422;    ///<  reg_444to422_md
} __attribute__ ((__packed__)) DrvSclVipIoLdc422444Config_t;

/**
* Setup LDC configuration
*/
typedef struct
{
    u32   VerChk_Version ;                          ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;                   ///< CMDQ cofiguration
    DrvSclVipIoLdcOnOffConfig_t stEn;               ///< be bypass
    DrvSclVipIoLdc422444Config_t stmd;              ///< set mode
    DrvSclVipIoLdclcBankModeType_e enLDCType;       ///< LDC 64p or 128p
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                          ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoLdcConfig_t;

/**
* Setup LDC mode cofiguration
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;               ///< CMDQ cofiguration
    u8 u8FBidx;                                 ///<  reg_ldc_fb_sw_idx
    u8 u8FBrwdiff;                              ///<  reg_ldc_fb_hw_rw_diff
    u8 bEnSWMode;                               ///<  reg_ldc_fb_sw_mode
    DrvSclVipIoLdcBypassType_e enbypass;        ///<  reg_ldc_ml_bypass
    DrvSclVipIoLdclcBankModeType_e enLDCType;   ///< LDC 64p or 128p
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                          ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoLdcMdConfig_t;
/**
* Setup LDC DMAP configuration
*/
typedef struct
{
    u32   VerChk_Version ;          ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;   ///< CMDQ configuration
    u32 u32DMAPaddr;                ///<  reg_ldc_dmap_st_addr
    u16 u16DMAPWidth;               ///<  reg_ldc_dmap_pitch
    u8  u8DMAPoffset;               ///<  reg_ldc_dmap_blk_xstart
    u8  bEnPowerSave;               ///<  reg_ldc_en_power_saving_mode
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;              ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoLdcDmapConfig_t;

/**
* Setup LDC SRAM configuration
*/
typedef struct
{
    u32   VerChk_Version ;          ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;   ///< CMDQ configuration
    u32 u32loadhoraddr;             ///<  reg_ldc_load_st_addr0
    u16 u16SRAMhorstr;              ///<  reg_ldc_sram_st_addr0
    u16 u16SRAMhoramount;           ///<  reg_ldc_load_amount0
    u32 u32loadveraddr;             ///<  reg_ldc_load_st_addr1
    u16 u16SRAMverstr;              ///<  reg_ldc_sram_st_addr1
    u16 u16SRAMveramount;           ///<  reg_ldc_load_amount1
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;              ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoLdcSramConfig_t;

/**
* Setup NLM configuration
*/
typedef struct
{
    u8 bNlm_en;                                             ///<  reg_nlm_en
    DrvSclVipIoNlmAverageType_e enAvgmode;                  ///<  reg_nlm_avg_mode :0:3x3 1:5x5
    u8 bnlm_bdry_en;                                        ///<  reg_nlm_bdry_en
    u8 bnlm_post_luma_adap_en;                              ///<  reg_nlm_post_luma_adap_en
    u8 bnlm_luma_adap_en;                                   ///<  reg_nlm_luma_adap_en
    u8 bnlm_dsw_adap_en;                                    ///<  reg_nlm_dsw_adap_en
    u8 bnlmdsw_lpf_en;                                      ///<  reg_nlm_dsw_lpf_en
    u8 bnlm_region_adap_en;                                 ///<  reg_nlm_region_adap_en
    DrvSclVipIoNlmDswType_e u8nlm_region_adap_size_config;  ///<  reg_nlm_region_adap_size_config 0:16x8 1:32x16
    u8 bnlm_histIIR_en;                                     ///<  reg_nlm_histiir_adap_en
    u8 bnlm_bypass_en;                                      ///<  reg_nlm_bypass_en
    u8 u8nlm_fin_gain;                                      ///<  reg_nlm_fin_gain
    u8 u8nlm_histIIR;                                       ///<  reg_nlm_histiir_adap_ratio
    u8 u8nlm_sad_shift;                                     ///<  reg_nlm_sad_shift
    u8 u8nlm_sad_gain;                                      ///<  reg_nlm_sad_gain
    u8 u8nlm_dsw_ratio;                                     ///<  reg_nlm_dsw_ratio
    u8 u8nlm_dsw_offset;                                    ///<  reg_nlm_dsw_offset
    u8 u8nlm_dsw_shift;                                     ///<  reg_nlm_dsw_shift
    u8 u8nlm_weight_lut[DRV_SCLVIP_IO_NLM_WEIGHT_NUM];                ///<  reg_nlm_weight_lut0-31 ,Qmap has adjust register squence
    u8 u8nlm_luma_adap_gain_lut[DRV_SCLVIP_IO_NLM_LUMAGAIN_NUM];      ///<  reg_nlm_luma_adap_gain_lut0-63,adjust register squence
    u8 u8nlm_post_luma_adap_gain_lut[DRV_SCLVIP_IO_NLM_POSTLUMA_NUM]; ///<  reg_nlm_post_luma_adap_gain_lut0-15,adjust register squence
    u8 u8nlm_dist_weight_7x7_lut[DRV_SCLVIP_IO_NLM_DISTWEIGHT_NUM];   ///<  reg_nlm_dist_weight_7x7_lut0-8,adjust register squence
    u8 u8nlm_main_snr_lut[DRV_SCLVIP_IO_NLM_POSTLUMA_NUM];            ///<  reg_main_snr_lut
    u8 u8nlm_wb_snr_lut[DRV_SCLVIP_IO_NLM_POSTLUMA_NUM];              ///<  reg_wb_snr_lut
} __attribute__ ((__packed__)) DrvSclVipIoNlmMainConfig_t;
/**
* Setup NLM SRAM configuration
*/
typedef struct
{
    bool bEn;         ///<  Enable/Disable auto downlaod
    u32 u32Baseadr;   ///<  physical addrress of NLM SRAM
    u32 u32viradr;    ///<  virtual address of NLM SRAM
} __attribute__ ((__packed__)) DrvSclVipIoNlmSramConfig_t;
/**
* Setup NLM configuration
*/
typedef struct
{
    u32   VerChk_Version ;              ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;       ///< CMDQ configuration
    DrvSclVipIoNlmMainConfig_t stNLM;   ///< NLM setting
    DrvSclVipIoNlmSramConfig_t stSRAM;  ///< Autodownload
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                  ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoNlmConfig_t;


/**
* Setup 422to444 configuration
*/
typedef struct
{
    u8 bvip_422to444_en;    ///<  reg_vip_422to444_en
    u8 u8vip_422to444_md;   ///<  reg_vip_422to444_md
} __attribute__ ((__packed__)) DrvSclVipIo422444Config_t;

/**
* Setup bypass configuration
*/
typedef struct
{
    u8 bvip_fun_bypass_en;  ///<  reg_vip_fun_bypass_en :except DNR,SNR,NLM,LDC
} __attribute__ ((__packed__)) DrvSclVipIoBypassConfig_t;

/**
* Setup VPS SRAM configuration
*/
typedef struct
{
    u8 u8vps_sram_act;      ///<  reg_vps_sram_act
} __attribute__ ((__packed__)) DrvSclVipIoLineBufferConfig_t;
/**
* Setup mix vip configuration
*/
typedef struct
{
    u32   VerChk_Version ;                ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;         ///< CMDQ configuration
    DrvSclVipIo422444Config_t st422_444;  ///< 422 to 444
    DrvSclVipIoBypassConfig_t stBypass;   ///< bypass
    DrvSclVipIoLineBufferConfig_t stLB;   ///<  VIP Mixed
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                  ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoConfig_t;

/**
* Setup Peaking HLPF configuration
*/
typedef struct
{
    u8 u8main_y_lpf_coef;           ///<  reg_main_y_lpf_coef
} __attribute__ ((__packed__)) DrvSclVipIoHlpfConfig_t;

/**
* Setup Peaking HLPF dither configuration
*/
typedef struct
{
    u8 hlpf_dither_en;              ///<  reg_hlpf_dither_en
} __attribute__ ((__packed__)) DrvSclVipIoHlpfDitherConfig_t;

/**
* Setup Peaking VLPF configuration
*/
typedef struct
{
    u8 main_v_lpf_coef;             ///<  reg_main_v_lpf_coef_1,2
} __attribute__ ((__packed__)) DrvSclVipIoVlpfCoefConfig_t;

/**
* Setup Peaking VLPF dither configuration
*/
typedef struct
{
    u8 vlpf_dither_en;              ///<  reg_vlpf_dither_en
} __attribute__ ((__packed__)) DrvSclVipIoVlpfDitherConfig_t;


/**
* Setup Peaking On/Off configuration
*/
typedef struct
{
    u8 bpost_peaking_en;            ///<  reg_main_post_peaking_en
    u8 u8vps_sram_act;              ///<  reg_vps_sram_act
    u8 u8band6_dia_filter_sel;      ///<  reg_main_band6_dia_filter_sel
    u8 u8peaking_ac_yee_mode;       ///<  reg_peaking_ac_yee_mode
} __attribute__ ((__packed__)) DrvSclVipIoPeakingOnOffConfig_t;

/**
* Setup Peaking band configuration
*/
typedef struct
{
    u8 bBand_En[DRV_SCLVIP_IO_PEAKING_BAND_NUM];              ///<  reg_main_band1_peaking_en 1-8
    u8 u8Band_COEF_STEP[DRV_SCLVIP_IO_PEAKING_BAND_NUM];      ///<  reg_main_band1_coef_step 1-8
    u8 u8Band_COEF[DRV_SCLVIP_IO_PEAKING_BAND_NUM];           ///<  reg_main_band1_coef 1-8
    u8 u8peaking_term[DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM];   ///<  reg_main_peaking_term1_select 1-16
    u8 u8Band_Over[DRV_SCLVIP_IO_PEAKING_BAND_NUM];           ///<  reg_band1_overshoot_limit 1-8
    u8 u8Band_Under[DRV_SCLVIP_IO_PEAKING_BAND_NUM];          ///<  reg_band1_undershoot_limit 1-8
    u8 u8Band_coring_thrd[DRV_SCLVIP_IO_PEAKING_BAND_NUM];    ///<  reg_main_band1_coring_thrd 1-8
    u8 u8alpha_thrd;                                ///<  reg_main_alpha_thrd
} __attribute__ ((__packed__)) DrvSclVipIoPeakingBandConfig_t;

/**
* Setup Peaking adptive configuration
*/
typedef struct
{
    u8 badaptive_en[DRV_SCLVIP_IO_PEAKING_BAND_NUM];                                  ///<  reg_main_band1_adaptive_en 1-8
    u8 u8hor_lut[DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM];                                ///<  reg_hor_lut_0-15
    u8 u8ver_lut[DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM];                                ///<  reg_ver_lut_0-15
    u8 u8low_diff_thrd_and_adaptive_gain_step[DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM];   ///<  alternation(reg_band1_adaptive_gain_step, reg_band1_low_diff_thrd) 1-8
    u8 u8dia_lut[DRV_SCLVIP_IO_PEAKING_BAND_TERM_NUM];                                ///<  reg_dia_lut_0-15
} __attribute__ ((__packed__)) DrvSclVipIoPeakingAdptiveConfig_t;

/**
* Setup Peaking PreCoring configuration
*/
typedef struct
{
    u8 u8coring_thrd_1;     ///<  reg_main_coring_thrd_1
    u8 u8coring_thrd_2;     ///<  reg_main_coring_thrd_2
    u8 u8coring_thrd_step;  ///<  reg_main_coring_thrd_step
} __attribute__ ((__packed__)) DrvSclVipIoPeakingPCoringConfig_t;

/**
* Setup Peaking Adp_Y configuration
*/
typedef struct
{
    u8 bcoring_adp_y_en;                                    ///<  reg_main_coring_adp_y_en
    u8 bcoring_adp_y_alpha_lpf_en;                          ///<  reg_main_coring_adp_y_alpha_lpf_en
    u8 u8coring_y_low_thrd;                                 ///<  reg_main_coring_y_low_thrd
    u8 u8coring_adp_y_step;                                 ///<  reg_main_coring_adp_y_step
    u8 u8coring_adp_y_alpha_lut[DRV_SCLVIP_IO_PEAKING_ADP_Y_LUT_NUM]; ///<  reg_main_coring_adp_y_alpha_lut_0-7
} __attribute__ ((__packed__)) DrvSclVipIoPeakingAdpYConfig_t;

/**
* Setup Peaking gain configuration
*/
typedef struct
{
    u8 u8osd_sharpness_ctrl ;       ///<  reg_main_osd_sharpness_ctrl
    u8 bosd_sharpness_sep_hv_en;    ///<  reg_main_osd_sharpness_sep_hv_en
    u8 u8osd_sharpness_ctrl_h  ;    ///<  reg_main_osd_sharpness_ctrl_h
    u8 u8osd_sharpness_ctrl_v ;     ///<  reg_main_osd_sharpness_ctrl_v
} __attribute__ ((__packed__)) DrvSclVipIoPeakingGainConfig_t;

/**
* Setup Peaking AdpY gain configuration
*/
typedef struct
{
    u8 bpk_adp_y_en;                                    ///<  reg_main_coring_adp_y_en
    u8 bpk_adp_y_alpha_lpf_en;                          ///<  reg_main_coring_adp_y_alpha_lpf_en
    u8 u8pk_y_low_thrd;                                 ///<  reg_main_coring_y_low_thrd
    u8 u8pk_adp_y_step;                                 ///<  reg_main_coring_adp_y_step
    u8 u8pk_adp_y_alpha_lut[DRV_SCLVIP_IO_PEAKING_ADP_Y_LUT_NUM]; ///<  reg_main_coring_adp_y_alpha_lut_0-7
} __attribute__ ((__packed__)) DrvSclVipIoPeakingGainAdpYConfig_t;

/**
* Setup Peaking YC gain configuration
*/
typedef struct
{
    u16 u16Dlc_in_y_gain;   ///<  reg_dlc_in_y_gain 16bit
    u16 u16Dlc_in_y_offset; ///<  reg_dlc_in_y_offset 16 bit
    u16 u16Dlc_in_c_gain;   ///<  reg_dlc_in_c_gain 16 bit
    u16 u16Dlc_in_c_offset; ///<  reg_dlc_in_c_offset 16 bit
    u16 u16Dlc_out_y_gain;  ///<  reg_dlc_out_y_gain 16 bit
    u16 u16Dlc_out_y_offset;///<  reg_dlc_out_y_offset 16 bit
    u16 u16Dlc_out_c_gain;  ///<  reg_dlc_out_c_gain 16 bit
    u16 u16Dlc_out_c_offset;///<  reg_dlc_out_c_offset 16 bit
} __attribute__ ((__packed__)) DrvSclVipIoYcGainOffsetConfig_t;

/**
* Setup Peaking configuration
*/
typedef struct
{
    u32   VerChk_Version ; ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;                     ///< CMDQ configuration
    DrvSclVipIoHlpfConfig_t stHLPF;                   ///< HLPF
    DrvSclVipIoHlpfDitherConfig_t stHLPFDith;         ///< HDither
    DrvSclVipIoVlpfCoefConfig_t stVLPFcoef1;          ///< VLPF coef1
    DrvSclVipIoVlpfCoefConfig_t stVLPFcoef2;          ///< VLPF coef2
    DrvSclVipIoVlpfDitherConfig_t stVLPFDith;         ///< VDither
    DrvSclVipIoPeakingOnOffConfig_t stOnOff;          ///< peaking onoff
    DrvSclVipIoPeakingBandConfig_t stBand;            ///< peaking band
    DrvSclVipIoPeakingAdptiveConfig_t stAdp;          ///< peaking adp
    DrvSclVipIoPeakingPCoringConfig_t stPcor;         ///< peaking precore
    DrvSclVipIoPeakingAdpYConfig_t stAdpY;            ///< peaking adp y
    DrvSclVipIoPeakingGainConfig_t stGain;            ///< peaking gain
    DrvSclVipIoPeakingGainAdpYConfig_t stGainAdpY;    ///< peaking Y gain
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size; ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoPeakingConfig_t;


/**
* Setup LCE On/Off configuration
*/
typedef struct
{
    bool bLCE_En;     ///< LCE en
    u8 u8ControlNum;  ///<  vip control guard pipe number
} __attribute__ ((__packed__)) DrvSclVipIoLceOnOffConfig_t;


/**
* Setup LCE dither configuration
*/
typedef struct
{
    bool bLCE_Dither_En;   ///< LCE dither
} __attribute__ ((__packed__)) DrvSclVipIoLceDitherConfig_t;

/**
* setup LCE setting configuration
*/
typedef struct
{
    u8 bLCE_sodc_alpha_en;                      ///<  reg_main_lce_sodc_alpha_en
    u8 bLce_dering_alpha_en;                    ///<  reg_main_lce_dering_alpha_en
    DrvSclVipIoLceYAveSelType_e enLce_y_ave_sel;  ///<  reg_main_lce_y_ave_sel (1'b1: 5x7; 1'b0:5x11)
    u8 bLce_3curve_en;                          ///<  reg_lce_3curve_en
    u8 u8Lce_std_slop1;                         ///<  reg_main_lce_std_slop1
    u8 u8Lce_std_slop2;                         ///<  reg_main_lce_std_slop2
    u8 u8Lce_std_th1;                           ///<  reg_main_lce_std_th1
    u8 u8Lce_std_th2;                           ///<  reg_main_lce_std_th2
    u8 u8Lce_gain_min;                          ///<  reg_main_lce_gain_min
    u8 u8Lce_gain_max;                          ///<  reg_main_lce_gain_max
    u8 u8Lce_sodc_low_alpha;                    ///<  reg_main_lce_sodc_low_alpha
    u8 u8Lce_sodc_low_th;                       ///<  reg_main_lce_sodc_low_th
    u8 u8Lce_sodc_slop;                         ///<  reg_main_lce_sodc_slop
    u8 u8Lce_diff_gain;                         ///<  reg_main_lce_diff_gain
    u8 u8Lce_gain_complex;                      ///<  reg_main_lce_gain_complex
    u8 u8Lce_dsw_minsadgain;                    ///<  reg_dsptch_lce_dsw_minsadgain
    u8 u8Lce_dsw_gain;                          ///<  reg_dsptch_lce_dsw_gian
    u8 u8LCE_dsw_thrd;                          ///<  reg_dsptch_lce_dsw_thrd
} __attribute__ ((__packed__)) DrvSclVipIoVipLceSettingConfig_t;

/**
* Setup LCE curve configuration
*/
typedef struct
{
    u8 u8Curve_Thread[4];                       ///<  reg_main_lce_curve_a-d
    u16 u16Curve1[DRV_SCLVIP_IO_LCE_CURVE_SECTION_NUM];   ///<  reg_lce_curve_lut1_08-f8 (lsb|msb) 16bit
    u16 u16Curve2[DRV_SCLVIP_IO_LCE_CURVE_SECTION_NUM];   ///<  reg_lce_curve_lut2_08-f8 (lsb|msb) 16bit
    u16 u16Curve3[DRV_SCLVIP_IO_LCE_CURVE_SECTION_NUM];   ///<  reg_lce_curve_lut3_08-f8 (lsb|msb) 16bit
} __attribute__ ((__packed__)) DrvSclVipIoLceCurveConfig_t;

/**
* Setup LCE configuration
*/
typedef struct
{
    u32   VerChk_Version ;                  ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;             ///< CMDQ
    DrvSclVipIoLceOnOffConfig_t stOnOff;      ///< bEn
    DrvSclVipIoLceDitherConfig_t stDITHER;    ///< dither
    DrvSclVipIoVipLceSettingConfig_t stSet;   ///< config
    DrvSclVipIoLceCurveConfig_t stCurve;      ///< curve
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                      ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoLceConfig_t;

/**
* Setup DLC programing configuration
*/
typedef struct
{
    u8    u8VARCP[DRV_SCLVIP_IO_DLC_LUMA_SECTION_NUM]; ///<  reg_curve_fit_var_cp1 -64
    u8    u8Tbln0;                           ///<  reg_main_curve_table_n0
    u8    u8Tbln0LSB;                        ///<  reg_main_curve_table_n0_LSB
    u8    u8Tbln0sign;                       ///<  reg_main_curve_table_n0_sign
    u16  u16Tbl64;                           ///<  reg_main_curve_table64 16 bit
    u8    u8Tbl64LSB;                        ///<  reg_main_curve_table64_LSB
} __attribute__ ((__packed__)) DrvSclVipIoDlcProgConfig_t;


/**
* Setup DLC curve configuration
*/
typedef struct
{
    u8    u8InLuma[DRV_SCLVIP_IO_DLC_LUMA_SECTION_NUM];     ///< reg_main_curve_table0-63
    u8    u8InLumaLSB[DRV_SCLVIP_IO_DLC_LUMA_SECTION_NUM];  ///<  reg_main_curve_table0-63 LSB
    DrvSclVipIoDlcProgConfig_t ProgCfg;                     ///< dlc proc
} __attribute__ ((__packed__)) DrvSclVipIoDlcCurveConfig_t;

/**
* Setup DLC On/Off configuration
*/
typedef struct
{
    u8  bcurve_fit_var_pw_en;               ///<  reg_main_curve_fit_var_pw_en
    DrvSclVipIoDlcCurveConfig_t stCurve;    ///< curve config
    u8  bcurve_fit_en;                      ///<  reg_main_curve_fit_en
    u8  bstatistic_en;                      ///<  reg_main_statistic_en
} __attribute__ ((__packed__)) DrvSclVipIoDlcEnableConfig_t;

/**
* Setup DLC dither configuration
*/
typedef struct
{
    u8  bDLCdither_en;   ///< bdlc dither
} __attribute__ ((__packed__)) DrvSclVipIoDlcDitherConfig_t;

/**
* Setup DLC histogram on/off configuration
*/
typedef struct
{
    bool u8brange_en;  ///< brange
} __attribute__ ((__packed__)) DrvSclVipIoDlcHistogramEnConfig_t;

/**
* Setup DLC histogram H configuration
*/
typedef struct
{
    u16 u16statistic_h_start;   ///< reg_main_statistic_h_start 16 bit
    u16 u16statistic_h_end;     ///< reg_main_statistic_h_end  16 bit
} __attribute__ ((__packed__)) DrvSclVipIoDlcHistogramHConfig_t;

/**
* Setup  DLC hisgotram V configuration
*/
typedef struct
{
    u16 u16statistic_v_start;   ///< reg_main_statistic_v_start 16 bit
    u16 u16statistic_v_end;     ///< reg_main_statistic_v_end  16 bit
} __attribute__ ((__packed__)) DrvSclVipIoDlcHistogramVConfig_t;

/**
* Setup DLC PC configuration
*/
typedef struct
{
    u8 bhis_y_rgb_mode_en;      ///<  reg_his_y_rgb_mode_en
    u8 bcurve_fit_rgb_en;       ///<  reg_main_curve_fit_rgb_en
} __attribute__ ((__packed__)) DrvSclVipIoDlcPcConfig_t;
/**
* Setup DLC configuration
*/
typedef struct
{
    u32   VerChk_Version ;                            ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;                     ///< CMDQ configuration
    DrvSclVipIoYcGainOffsetConfig_t stGainOffset;     ///< Gain
    DrvSclVipIoDlcEnableConfig_t stEn;                ///< EN
    DrvSclVipIoDlcDitherConfig_t stDither;            ///< Dither
    DrvSclVipIoDlcHistogramEnConfig_t sthist;         ///< hist
    DrvSclVipIoDlcHistogramHConfig_t stHistH;         ///<hhsit
    DrvSclVipIoDlcHistogramVConfig_t stHistV;         ///<vhist
    DrvSclVipIoDlcPcConfig_t stPC;                    ///< PC
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                              ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoDlcConfig_t;
/**
* Setup DLC histogram configuration
*/
typedef struct
{
    u32   VerChk_Version ;                              ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;                       ///< FC config
    u8 bVariable_Section;                               ///< reg_variable_range_en
    u8 bstatic;                                         ///< reg_main_statistic_en
    u8 bcurve_fit_en;                                   ///< reg_main_curve_fit_en
    u8 bhis_y_rgb_mode_en;                              ///< reg_his_y_rgb_mode_en
    u8 bcurve_fit_rgb_en;                               ///< reg_main_curve_fit_rgb_en
    u8 bDLCdither_en;                                   ///< reg_ycv_dither_en
    u8 bstat_MIU;                                       ///< reg_vip_stat_miu_en
    u8 bRange;                                          ///< reg_main_range_en
    u16 u16Vst;                                         ///< reg_main_statistic_v_start
    u16 u16Vnd;                                         ///< reg_main_statistic_v_end
    u16 u16Hst;                                         ///< reg_main_statistic_h_start
    u16 u16Hnd;                                         ///< reg_main_statistic_v_end
    u8 u8HistSft;                                       ///< reg_histrpt_sft
    u8 u8trig_ref_mode;                                 ///< reg_vip_stat_trig_ref_md
    unsigned char u8SWTrigger;                          ///<  reg_vip_stat_sw_trig|reg_vip_stat_sw_trig_baseidx
    u32 u32StatBase[2];                                 ///< reg_vip_stat_base0,reg_vip_stat_base1
    u8 u8Histogram_Range[DRV_SCLVIP_IO_DLC_HISTOGRAM_SECTION_NUM];///<  reg_histogram_range1-7
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                                  ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoDlcHistogramConfig_t;

/**
* DLC histogram report configuration
*/
typedef struct
{
    u32 u32Histogram[DRV_SCLVIP_IO_DLC_HISTOGRAM_REPORT_NUM];   ///<  reg_total_1f-ff_00
    u32 u32PixelWeight;                                         ///<  reg_main_total_pixel_weight
    u32 u32PixelCount;                                          ///<  reg_main_total_pixel_count
    u8 u8MinPixel;                                              ///<  reg_main_min_pixel
    u8 u8MaxPixel;                                              ///<  reg_main_max_pixel
    u8 u8Baseidx;                                               ///<  reg_vip_stat_baseidx
} __attribute__ ((__packed__)) DrvSclVipIoDlcHistogramReport_t;

/**
* Setup UVC configuration
*/
typedef struct
{
    u8 buvc_en;                         ///<  reg_main_uvc_en
    u8 u8uvc_locate;                    ///<  reg_main_uvc_locate
    u8 u8uvc_gain_high_limit_lsb;       ///<  reg_main_uvc_gain_high_limit_lsb
    u8 u8uvc_gain_high_limit_msb;       ///<  reg_main_uvc_gain_high_limit_msb
    u8 u8uvc_gain_low_limit_lsb;        ///<  reg_main_uvc_gain_low_limit_lsb
    u8 u8uvc_gain_low_limit_msb;        ///<  reg_main_uvc_gain_low_limit_msb
    u8 buvc_adaptive_luma_en;           ///<  reg_main_uvc_adaptive_luma_en
    u8 u8uvc_adaptive_luma_y_input;     ///<  reg_main_uvc_adaptive_luma_y_input
    u8 u8uvc_adaptive_luma_black_step;  ///<  reg_main_uvc_adaptive_luma_black_step
    u8 u8uvc_adaptive_luma_white_step;  ///<  reg_main_uvc_adaptive_luma_white_step
    u8 u8uvc_adaptive_luma_black_th;    ///<  reg_main_uvc_adaptive_luma_black_thrd
    u8 u8uvc_adaptive_luma_white_th;    ///<  reg_main_uvc_adaptive_luma_white_thrd
    u8 u8uvc_adaptive_luma_gain_low;    ///<  reg_main_uvc_adaptive_luma_gain_low
    u8 u8uvc_adaptive_luma_gain_med;    ///<  reg_main_uvc_adaptive_luma_gain_med
    u8 u8uvc_adaptive_luma_gain_high;   ///<  reg_main_uvc_adaptive_luma_gain_high
    u8 buvc_rgb_en;                     ///<  reg_main_uvc_rgb_en
    u8 buvc_dlc_fullrange_en;           ///<  reg_main_uvc_dlc_fullrange_en
    u8 u8uvc_low_sat_prot_thrd;         ///<  reg_main_uvc_low_sat_prot_thrd
    u8 u8uvc_low_sat_min_strength;      ///<  reg_main_uvc_low_sat_min_strength
    u8 buvc_low_y_sat_prot_en;          ///<  reg_main_uvc_low_y_sat_prot_en
    u8 buvc_lpf_en;                     ///<  reg_main_uvc_lpf_en
    u8 buvc_low_sat_prot_en;            ///<  reg_main_uvc_low_sat_prot_en
    u8 buvc_low_y_prot_en;              ///<  reg_main_uvc_low_y_prot_en
    u8 u8uvc_low_sat_prot_slope;        ///<  reg_main_uvc_low_sat_prot_slope
    u8 u8uvc_low_y_prot_slope;          ///<  reg_main_uvc_low_y_prot_slope
    DrvSclVipIoUvcAdpYInputSelType_e enAdp_Ysel;    ///<  reg_main_uvc_low_y_sel
    u8 u8uvc_low_y_prot_thrd;           ///<  reg_main_uvc_low_y_prot_thrd
    u8 u8uvc_low_y_min_strength;        ///<  reg_main_uvc_low_y_min_strength
} __attribute__ ((__packed__)) DrvSclVipIoUvcMainConfig_t;
/**
* Setup VC format configuration
*/
typedef struct
{
    u32   VerChk_Version ;           ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;      ///< CMDQ configuration
    DrvSclVipIoUvcMainConfig_t stUVC;  ///< UVC
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;              ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoUvcConfig_t;
/**
* Used to setup FCC adp of vip device
*/
typedef struct
{
    u8 u8fcc_adp_Y_LUT[DRV_SCLVIP_IO_FCC_YWIN_LUT_ENTRY_NUM];  ///<  reg_main_fcc_adp_Y_LUT_win0_0-16
} __attribute__ ((__packed__)) DrvSclVipIoFccAdpYLutConfig_t;

/**
* Setup FCC full range configuration
*/
typedef struct
{
    u8 bfcc_fr_en;                              ///<  reg_main_fcc_fr_en
    u8 bEn[4];                                  ///<  reg_main_fcc_adp_Y_win0_en 0-3
    u8 u8YWinNum[4];                            ///<  reg_main_fcc_adp_Y_win0_NUM 0-3
    DrvSclVipIoFccAdpYLutConfig_t u8Ywin_LUT[4];  ///<  reg_main_fcc_adp_Y_LUT_win0-3_0
} __attribute__ ((__packed__)) DrvSclVipIoFccFullRangeConfig_t;

/**
* Setup FCC Tx configuration
*/
typedef struct
{
    u8 bEn;                                 ///<  reg_main_fcc_t_en
    u8 u8Cb;                                ///<  reg_fcc_cb_t
    u8 u8Cr;                                ///<  reg_fcc_cr_t
    u8 u8K;                                 ///<  reg_fcc_k_t
    u8 u8Range[E_DRV_SCLVIP_IO_FCC_Y_DIS_NUM];        ///<  reg_fcc_win_cr_down~reg_fcc_win_cb_up
    u8 u8LSB_Cb;                            ///<  reg_fcc_fr_cb_t_lsb  for FR reg_fcc_cb_t lsb
    u8 u8LSB_Cr;                            ///<  reg_fcc_fr_cr_t_lsb  for FR reg_fcc_cr_t lab
    u16 u16FullRange[E_DRV_SCLVIP_IO_FCC_Y_DIS_NUM];  ///<  reg_fcc_fr_win_cr_down ~reg_fcc_fr_win_cb_up full range 16 bit
} __attribute__ ((__packed__)) DrvSclVipIoFccTConfig_t;

/**
* Setup FCC T9 configuration
*/
typedef struct
{
    u8 bEn;                                 ///<  reg_main_fcc_9t_en
    u8 u8K;                                 ///<  reg_fcc_k_9t
    u8 u8Cr;                                ///<  reg_fcc_win9_cr
    u8 u8Cb;                                ///<  reg_fcc_win9_cb
    u8 bfirstEn;                            ///<  reg_main_fcc_9t_first_en
    u8 u8frCb;                              ///<  reg_fcc_fr_cb_t9
    u8 u8LSB_Cb;                            ///<  reg_fcc_fr_cb_t9_lsb
    u8 u8frCr;                              ///<  reg_fcc_fr_cr_t9
    u8 u8LSB_Cr;                            ///<  reg_fcc_fr_cr_t9_lsb
    u16 u16FullRange[E_DRV_SCLVIP_IO_FCC_Y_DIS_NUM];  ///<  reg_fcc_fr_win9_cr_down ~reg_fcc_fr_win9_cb_up full range 16 bit
} __attribute__ ((__packed__)) DrvSclVipIoFccT9Config_t;

/**
* Setup FCC configuration
*/
typedef struct
{
    u32   VerChk_Version ;              ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;         ///< CMDQ
    DrvSclVipIoFccFullRangeConfig_t stfr; ///< full range
    DrvSclVipIoFccTConfig_t stT[8];       ///< STx
    DrvSclVipIoFccT9Config_t stT9;        ///< ST9
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                  ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoFccConfig_t;

/**
* Setup IHC On/Off configuration
*/
typedef struct
{
    u8 bIHC_en;    ///<  reg_main_ihc_en
} __attribute__ ((__packed__)) DrvSclVipIhcOnOffConfig_t;

/**
* Setup IHC Ymode configuration
*/
typedef struct
{
    u8 bIHC_y_mode_en;                  ///<  reg_main_ihc_y_mode_en
    u8 bIHC_y_mode_diff_color_en;       ///<  reg_main_ihc_y_mode_diff_color_en
} __attribute__ ((__packed__)) DrvSclVipIoIhcYModeConfig_t;

/**
* Setup IHC dither configuration
*/
typedef struct
{
    u8 bIHC_dither_en;    ///<  reg_ihc_dither_en
} __attribute__ ((__packed__)) DrvSclVipIoIhcDitherConfig_t;

/**
* Setup IHC user configuration
*/
typedef struct
{
    u8 u8hue_user_color;        ///<  reg_main_hue_user_color0
    u8 u8hue_user_color_sec0;   ///<  reg_main_hue_user_color0_0
    u8 u8hue_user_color_sec1;   ///<  reg_main_hue_user_color0_1
    u8 u8hue_user_color_sec2;   ///<  reg_main_hue_user_color0_2
} __attribute__ ((__packed__)) DrvSclVipIoIhcUserConfig_t;

/**
* Setup IHC settting configuration
*/
typedef struct
{
    DrvSclVipIoIhcUserConfig_t stIHC_color[DRV_SCLVIP_IO_IHC_USER_COLOR_NUM];///<  0-15
} __attribute__ ((__packed__)) DrvSclVipIoIhcSettingConfig_t;

/**
* Setup IHC configuration
*/
typedef struct
{
    u32   VerChk_Version ;                  ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;           ///<CMDQ configuration
    DrvSclVipIhcOnOffConfig_t stOnOff;      ///<onoff
    DrvSclVipIoIhcYModeConfig_t stYmd;      ///<Ymode
    DrvSclVipIoIhcDitherConfig_t stDither;  ///<dither
    DrvSclVipIoIhcSettingConfig_t stset;    ///<set
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                      ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoIhcConfig_t;

/**
* Setup ICC On/Off configuration
*/
typedef struct
{
    u8 bICC_en;             ///<  reg_main_icc_en
    u8 bcbcr_to_uv_en;      ///<  reg_main_cbcr_to_uv
    u8 u8common_minus_gain; ///<  reg_common_minus_gain
    u8 u8sa_min;            ///<  reg_sa_min
    u16 u16step_sa_user;    ///<  reg_main_step_sa_user 16 bit
} __attribute__ ((__packed__)) DrvSclVipIoIccEnableConfig_t;

/**
* Setup ICC YmodeIn configurationa
*/
typedef struct
{
    u8 u8sa_user_color_sec0;        ///<  control en
    u8 u8sign_sa_user_color_sec0;   ///< [6:0] User adjust hue, color 0~9
    u8 u8sa_user_color_sec1;        ///<  control en
    u8 u8sign_sa_user_color_sec1;   ///< [6:0] User adjust hue, color 0~9
    u8 u8sa_user_color_sec2;        ///<  control en
    u8 u8sign_sa_user_color_sec2;   ///< [6:0] User adjust hue, color 0~9
} __attribute__ ((__packed__)) DrvSclVipIoIccYmodeinConfig_t;

/**
* Setup ICC Ymode configuration
*/
typedef struct
{
    u8 icc_y_mode_en;                                           ///<  reg_main_icc_y_mode_en
    u8 icc_y_mode_diff_color_en;                                ///<  reg_main_icc_y_mode_diff_color_en
    DrvSclVipIoIccYmodeinConfig_t stICC_color[DRV_SCLVIP_IO_ICE_COLOR_NUM]; ///<  DrvSclVipIoIccYmodeinConfig_t
} __attribute__ ((__packed__)) DrvSclVipIoIccYmodeConfig_t;

/**
* Setup ICC dither configuration
*/
typedef struct
{
    u8 bICC_dither_en;    ///<  reg_icc_dither_en
} __attribute__ ((__packed__)) DrvSclVipIccDitherConfig_t;
/**
* Setup ICC user configuration
*/
typedef struct
{
    u8 u8sa_user_color;     ///<  reg_main_sa_user_colo
    u8 u8sign_sa_user_color;///< reg_main_sign_sa_user_color
} __attribute__ ((__packed__)) DrvSclVipIoIccUserConfig_t;

/**
* Setup ICC setting configuration
*/
typedef struct
{
    DrvSclVipIoIccUserConfig_t stICC_color[DRV_SCLVIP_IO_ICE_COLOR_NUM];   ///< 0-15
} __attribute__ ((__packed__)) DrvSclVipIoIccSettingConfig_t;

/**
* Setup ICC configuration
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;               ///<CMDQ configuration
    DrvSclVipIoIccEnableConfig_t stEn;          ///<En
    DrvSclVipIoIccYmodeConfig_t stYmd;          ///<Ymode
    DrvSclVipIccDitherConfig_t stDither;        ///<dither
    DrvSclVipIoIccSettingConfig_t stSet;        ///<set
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                          ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoIccConfig_t;

/**
* Setup IHC ICC  YMode configuration
*/
typedef struct
{
    u8 u8ihc_icc_y[E_DRV_SCLVIP_IO_IHC_ICE_ADP_Y_SECTION_NUM];               ///< reg_main_ihc_icc_y_0-3
} __attribute__ ((__packed__)) DrvSclVipIoYmodeYvalueAllConfig_t;

/**
* Setup IHC ICC user configuration
*/
typedef struct
{
    u8 u8ihc_icc_color_sec0; ///<sec0
    u8 u8ihc_icc_color_sec1; ///<sec1
    u8 u8ihc_icc_color_sec2; ///<sec2
    u8 u8ihc_icc_color_sec3; ///<sec3
} __attribute__ ((__packed__)) DrvSclVipIoYvalueUserConfig_t;

/**
* Setup IHC ICC  YMode setting configuration
*/
typedef struct
{
    DrvSclVipIoYvalueUserConfig_t stYmode_Yvalue_color[DRV_SCLVIP_IO_ICE_COLOR_NUM];///< 0-15
} __attribute__ ((__packed__)) DrvSclVipIoYmodeYvalueSettingConfig_t;

/**
* Setup IHC ICC configuration
*/
typedef struct
{
    u32   VerChk_Version ;                          ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;                   ///<CMDQ configuration
    DrvSclVipIoYmodeYvalueAllConfig_t stYmdall;     ///<Ymode
    DrvSclVipIoYmodeYvalueSettingConfig_t stYmdset; ///<Ymodeset
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                              ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoIhcIccConfig_t;

/**
* Setup IBC On/Off configuration
*/
typedef struct
{
    u8 bIBC_en;             ///<  reg_main_ibc_en
    u8 u8IBC_coring_thrd;   ///<  reg_ibc_coring_thrd
    u8 bIBC_y_adjust_lpf_en;///<  reg_ibc_y_adjust_lpf_en
} __attribute__ ((__packed__)) DrvSclVipIoIbcEnableConfig_t;

/**
* Setup IBC dither configuration
*/
typedef struct
{
    u8 bIBC_dither_en;    ///<  reg_ibc_dither_en
} __attribute__ ((__packed__)) DrvSclVipIoIbcDitherConfig_t;

/**
* Setup IBC setting configuration
*/
typedef struct
{
    u8 u8ycolor_adj[DRV_SCLVIP_IO_IBC_COLOR_NUM];   ///<  reg_main_ycolor0_adj 0-15
    u8 u8weightcminlimit;                           ///< reg_weight_c_min_limit
    u8 u8weightcmaxlimit;                           ///< reg_weight_y_min_limit
} __attribute__ ((__packed__)) DrvSclVipIoIbcSettingConfig_t;

/**
* Setup IBC configuration
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;               ///< CMDQ configuration
    DrvSclVipIoIbcEnableConfig_t stEn;          ///< bEn
    DrvSclVipIoIbcDitherConfig_t stDither;      ///< dither
    DrvSclVipIoIbcSettingConfig_t stSet;        ///< setting
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                          ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoIbcConfig_t;

/**
* Setup ACK setting configuration
*/
typedef struct
{
    u8 backen;              ///<  reg_main_ack_en
    u8 bYswitch_dithen;     ///<  reg_y_switch_dither_en
    u8 bYswitchen;          ///<  reg_main_y_switch_en
    u8 u8Uswitch;           ///<  reg_u_switch_coef
    u8 u8Vswitch;           ///<  reg_v_switch_coef
    u8 u8Ythrd;             ///<  reg_ack_y_thrd
    u8 u8offset;            ///<  reg_ack_offset
    u8 u8yslot;             ///<  reg_ack_y_slop
    u8 u8limit;             ///<  reg_ack_limit
    u8 bCcompen;            ///<  reg_ack_c_comp_en
    u8 u8Cthrd;             ///<  reg_ack_c_thrd
    u8 u8Crange;            ///<  reg_ack_c_range
} __attribute__ ((__packed__)) DrvSclVipIoAckMainConfig_t;
/**
* Setup clamp configuration
*/
typedef struct
{
    u8 bclamp_en;       ///<  reg_vip_main_clamp_en
    u16 u16y_max_clamp; ///<  reg_main_y_max_clamp 16bit
    u16 u16y_min_clamp; ///<  reg_main_y_min_clamp 16bit
    u16 u16cb_max_clamp;///<  reg_main_cb_max_clamp 16bit
    u16 u16cb_min_clamp;///<  reg_main_cr_min_clamp 16bit
    u16 u16cr_max_clamp;///<  reg_main_cb_max_clamp 16bit
    u16 u16cr_min_clamp;///<  reg_main_cr_min_clamp 16bit
} __attribute__ ((__packed__)) DrvSclVipIoYcbcrClipMainConfig_t;

/**
* Setup ACK configuration
*/
typedef struct
{
    u32   VerChk_Version ;                      ///< structure version
    DrvSclVipIoFcConfig_t stFCfg;               ///<CMDQ configuration
    DrvSclVipIoAckMainConfig_t stACK;           ///<ACK setting
    DrvSclVipIoYcbcrClipMainConfig_t stclip;    ///<clamp
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                          ///< structure size for version checking
} __attribute__ ((__packed__)) DrvSclVipIoAckConfig_t;


/**
* Setup CMDQ configuration
*/
typedef struct
{
    DrvSclVipIoFcConfig_t stFCfg;   ///< CMDQ configuration
    u32 u32Addr;                    ///< address
    u16 u16Data;                    ///< cmd
    u16 u16Mask;                    ///< mask
    u8 u8framecnt;                  ///< count
    u8 bfire;                       ///< fire
    u8 bCnt;                        ///< bframecount
} __attribute__ ((__packed__)) DrvSclVipIoCmdqConfig_t;

/**
* Setup susupend setting configuration
*/
typedef struct
{
    u32 bresetflag;                                 ///< flag
    u32 bAIPreflag;                                 ///< flag
    DrvSclVipIoAckConfig_t stack;                     ///< ack
    DrvSclVipIoIbcConfig_t stibc;                     ///< ibc
    DrvSclVipIoIhcIccConfig_t stihcicc;               ///< iccihc
    DrvSclVipIoIccConfig_t sticc;                     ///< icc
    DrvSclVipIoIhcConfig_t stihc;                     ///< ihc
    DrvSclVipIoFccConfig_t stfcc;                     ///< fcc
    DrvSclVipIoUvcConfig_t stuvc;                     ///< uvc
    DrvSclVipIoDlcHistogramConfig_t sthist;           ///< hist
    DrvSclVipIoDlcConfig_t stdlc;                     ///< dlc
    DrvSclVipIoLceConfig_t stlce;                     ///< lce
    DrvSclVipIoPeakingConfig_t stpk;                  ///< pk
    DrvSclVipIoNlmConfig_t stnlm;                     ///< nlm
    DrvSclVipIoLdcMdConfig_t stldcmd;                 ///< ldc
    DrvSclVipIoLdcDmapConfig_t stldcdmap;             ///< ldc
    DrvSclVipIoLdcSramConfig_t stldcsram;             ///< ldc
    DrvSclVipIoLdcConfig_t stldc;                     ///< ldc
    DrvSclVipIoMcnrConfig_t stmcnr;                   ///<Mcnr
    DrvSclVipIoConfig_t stvip;                        ///< vipmix
    DrvSclVipIoAipConfig_t staip[E_DRV_SCLVIP_IO_AIP_NUM];   ///<AIP
} __attribute__ ((__packed__)) DrvSclVipIoSuspendConfig_t;
/**
* Setup  susupend configuration
*/
typedef struct
{
    u32   VerChk_Version ;                  ///< structure version
    DrvSclVipIoSuspendConfig_t stvipCfg;    ///< suspend setting
    u32   VerChk_Size;                      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclVipIoAllSetConfig_t;

/**
* Setup Vtrack On/Off configuration
*/
typedef struct
{
    u32   VerChk_Version ;                  ///< structure version
    DrvSclVipIoVtrackEnableType_e EnType;   ///< On/Off
    u8 u8framerate;                         ///< frame rate
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclVipIoVtrackOnOffConfig_t;
/**
* Setup Vtrack configuration
*/
typedef struct
{
    u32   VerChk_Version ;                                  ///< structure version
    bool bSetKey;                                           ///< key
    bool bSetUserDef;                                       ///< user def
    u8 u8SetKey[DRV_SCLVIP_IO_VTRACK_KEY_SETTING_LENGTH];   ///< key
    u8 u8SetUserDef[DRV_SCLVIP_IO_VTRACK_SETTING_LENGTH];   ///< userdef
    u8 u8OperatorID;                                        ///< operator
    u16 u16Timecode;                                        ///< timecode
    // VerChk_Version & VerChk_Size must be the latest 2 parameter and
    // the order can't be changed
    u32   VerChk_Size;                                      ///< structure size for version checking
}__attribute__ ((__packed__)) DrvSclVipIoVtrackConfig_t;

/// @cond
typedef void (*PollCB) (void *);

typedef struct
{
    u8   u8retval;           ///< return
    u8   u8pollval;          ///< get
    u32  u32Timeout;         ///< u32Timeout
    PollCB *pCBFunc;
}__attribute__ ((__packed__)) DrvSclVipIoPollConfig_t;
/// @endcond

#endif //
/** @} */ // end of sclvip_group