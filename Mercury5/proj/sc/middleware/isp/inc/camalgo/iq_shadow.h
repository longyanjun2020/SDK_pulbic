/*
 * iq_shadow.h
 *
 *  Created on: 2017/6/8
 *      Author: Daniel.Yu
 */

#ifndef __iq_shadow__
#define __iq_shadow__

#define FAIL        (-1)
//#define SUCCESS     0

#include <stdio.h>
#include <pthread.h>
#include <isp_types.h>
#include "iq_struct.h"
#include <isp_reg_shadow.h>
//#include "../../../../driver/hal/mercury/scl/inc/drv/drv_scl_verchk.h"
#include <drv_scl_verchk.h>

#define LCE_CURVE_SECTION_NUM       16          ///< VIP_LCE_CURVE_SECTION_NUM
#define PEAKING_BAND_NUM            8           ///< VIP_PEAKING_BAND_NUM
#define PEAKING_ADP_Y_LUT_NUM       8           ///< VIP_PEAKING_ADP_Y_LUT_NUM
#define PEAKING_BAND_TERM_NUM       16          ///< VIP_PEAKING_BAND_TERM_NUM
#define DLC_HISTOGRAM_SECTION_NUM   7           ///< VIP_DLC_HISTOGRAM_SECTION_NUM
#define DLC_HISTOGRAM_REPORT_NUM    8           ///< VIP_DLC_HISTOGRAM_REPORT_NUM
#define DLC_LUMA_SECTION_NUM        64          ///< VIP_DLC_LUMA_SECTION_NUM
#define IHC_COLOR_NUM               16          ///< VIP_IHC_COLOR_NUM
#define IHC_USER_COLOR_NUM          16          ///< VIP_IHC_USER_COLOR_NUM
#define ICE_COLOR_NUM               16          ///< VIP_ICE_COLOR_NUM
#define IBC_COLOR_NUM               16          ///< VIP_IBC_COLOR_NUM
#define FCC_YWIN_LUT_ENTRY_NUM      17          ///< VIP_FCC_YWIN_LUT_ENTRY_NUM
#define NLM_DISTWEIGHT_NUM          9           ///< VIP_NLM_DISTWEIGHT_NUM
#define NLM_WEIGHT_NUM              32          ///< VIP_NLM_WEIGHT_NUM
#define NLM_LUMAGAIN_NUM            64          ///< VIP_NLM_LUMAGAIN_NUM
#define NLM_POSTLUMA_NUM            16          ///< VIP_NLM_POSTLUMA_NUM
#define CMDQ_MEM_256K               0x0040000   ///< VIP_CMDQ_MEM_164K
#define CMDQ_MEM_196K               0x0030000   ///< VIP_CMDQ_MEM_164K
#define CMDQ_MEM_164K               0x0028000   ///< VIP_CMDQ_MEM_164K
#define CMDQ_MEM_128K               0x0020000   ///< VIP_CMDQ_MEM_128K
#define CMDQ_MEM_64K                0x0010000   ///< VIP_CMDQ_MEM_64K
#define CMDQ_MEM_32K                0x0008000   ///< VIP_CMDQ_MEM_32K
#define CMDQ_MEM_16K                0x0004000   ///< VIP_CMDQ_MEM_16K
#define CMDQ_MEM_TEST               0x0001000   ///< VIP_CMDQ_MEM_TEST
#define VTRACK_KEY_SETTING_LENGTH   8           ///< VIP_VTRACK_KEY_SETTING_LENGTH
#define VTRACK_SETTING_LENGTH       23          ///< VIP_VTRACK_SETTING_LENGTH

#define VIP_VERSION                 0x0101      ///< H:Major L:minor H3:Many Change H2:adjust Struct L1:add struct L0:adjust driver

#if 1
//enable SCL version check
#define VIP_INFO(a) FILL_VERCHK_TYPE((a),(a).VerChk_Version,(a).VerChk_Size,VERCHK_VERSION_MASK)
#endif



/**
* Used to setup the AIP  of vip device
*/
typedef enum
{
    EN_AIP_YEE = 0,           ///< yee
    EN_AIP_YEE_AC_LUT,        ///< yee ac lut
    EN_AIP_WDR_GLOB,          ///< wdr glob
    EN_AIP_WDR_LOC,           ///< wdr loc
    EN_AIP_MXNR,              ///< mxnr
    EN_AIP_UVADJ,             ///< uvadj
    EN_AIP_XNR,               ///< xnr
    EN_AIP_YCUVM,             ///< ycuvm
    EN_AIP_COLORTRAN,         ///< ct
    EN_AIP_GAMMA,             ///< gamma
    EN_AIP_422TO444,          ///< 422to444
    EN_AIP_YUVTORGB,          ///< yuv2rgb
    EN_AIP_GM10TO12,          ///< 10 to 12
    EN_AIP_CCM,               ///< ccm
    EN_AIP_HSV,               ///< hsv
    EN_AIP_GM12TO10,          ///< gm12to10
    EN_AIP_RGBTOYUV,          ///< rgb2yuv
    EN_AIP_444TO422,          ///< 4442422
    EN_AIP_NUM,               ///< Num
}EN_AIP_TYPE;

/**
* Used to setup the AIP SRAM of vip device
*/
typedef enum
{
    EN_AIP_SRAM_GAMMA_Y,    ///< gamma y
    EN_AIP_SRAM_GAMMA_U,    ///< gamma u
    EN_AIP_SRAM_GAMMA_V,    ///< gamma v
    EN_AIP_SRAM_GM10to12_R, ///< gamma R
    EN_AIP_SRAM_GM10to12_G, ///< gamma G
    EN_AIP_SRAM_GM10to12_B, ///< gamma B
    EN_AIP_SRAM_GM12to10_R, ///< gamma R
    EN_AIP_SRAM_GM12to10_G, ///< gamma G
    EN_AIP_SRAM_GM12to10_B, ///< gamma B
    EN_AIP_SRAM_WDR,        ///< wdr
}EN_AIP_SRAM_TYPE;

typedef enum {
    ISP_REG_BANK0,
    ISP_REG_BANK1,
    ISP_REG_BANK2,
    ISP_REG_BANK3,
    ISP_REG_BANK4,
    ISP_REG_BANK5,
    ISP_REG_BANK6,
    ISP_REG_BANK7,
    ISP_REG_BANK8,
    ISP_REG_BANK9,
    ISP_REG_BANK10,
    ISP_REG_BANK11,
    ISP_REG_BANK12,
    ISP_REG_BANK_NONE=255,
} ISP_REG_BANK;

//isp
int IspRegSetINIT(iq_handle_t *handle);
int IspRegSetDECOMP(iq_handle_t *handle, IQ_DECOMP_CFG *cfg);
int IspRegSetFPN(iq_handle_t *handle, IQ_FPN_CFG *cfg);
int IspRegSetFPN_P1(iq_handle_t *handle, IQ_FPN_P1_CFG *cfg);
int IspRegSetOBC(iq_handle_t *handle, IQ_OBC_CFG *cfg);
int IspRegSetOBC_P1(iq_handle_t *handle, IQ_OBC_P1_CFG *cfg);
int IspRegSetGAMA_16to16_ISP(iq_handle_t *handle, IQ_GAMA_16to16_ISP_CFG *cfg);
int IspRegSetGAMA_C2C_P1_ISP(iq_handle_t *handle, IQ_GAMA_C2C_P1_ISP_CFG *cfg);
int IspRegSetLSC(iq_handle_t *handle, IQ_LSC_CFG *cfg);
int IspRegSetLSC_P1(iq_handle_t *handle, IQ_LSC_P1_CFG *cfg);
int IspRegSetALSC(iq_handle_t *handle, IQ_ALSC_CFG *cfg);
int IspRegSetALSC_P1(iq_handle_t *handle, IQ_ALSC_P1_CFG *cfg);
int IspRegSetHDR(iq_handle_t *handle, IQ_HDR_CFG *cfg);
int IspRegSetHDR_16to10(iq_handle_t *handle, IQ_HDR_16to10_CFG *cfg);
int IspRegSetDPC(iq_handle_t *handle, IQ_DPC_CFG *cfg);
int IspRegSetGE(iq_handle_t *handle, IQ_GE_CFG *cfg);
int IspRegSetANTICT(iq_handle_t *handle, IQ_ANTICT_CFG *cfg);
int IspRegSetRGBIR(iq_handle_t *handle, IQ_RGBIR_CFG *cfg);
int IspRegSetSpikeNR(iq_handle_t *handle, IQ_SpikeNR_CFG *cfg);
int IspRegSetSDC(iq_handle_t *handle, IQ_SDC_CFG *cfg);
int IspRegSetBSNR(iq_handle_t *handle, IQ_BSNR_CFG *cfg);
int IspRegSetNM(iq_handle_t *handle, IQ_NM_CFG *cfg);
int IspRegSetDM(iq_handle_t *handle, IQ_DM_CFG *cfg);
int IspRegSetPostDN(iq_handle_t *handle, IQ_PostDN_CFG *cfg);
int IspRegSetFalseColor(iq_handle_t *handle, IQ_FalseColor_CFG *cfg);
int IspRegSetGAMA_A2A_ISP(iq_handle_t *handle, IQ_GAMA_A2A_ISP_CFG *cfg);
//scl
int IspRegSetMCNR(iq_handle_t *handle, IQ_MCNR_CFG *cfg);
int IspRegSetNLM(iq_handle_t *handle, IQ_NLM_CFG *cfg, MS_U16 *u16GainGLut);
int IspRegSetXNR(iq_handle_t *handle, IQ_XNR_CFG *cfg);
int IspRegSetLDC(iq_handle_t *handle, IQ_LDC_CFG *cfg);
int IspRegSetGAMA_A2C_SC(iq_handle_t *handle, IQ_GAMA_A2C_SC_CFG *cfg);
int IspRegSetCCM(iq_handle_t *handle, IQ_CCM_CFG *cfg);
int IspRegSetHSV(iq_handle_t *handle, IQ_HSV_CFG *cfg);
int IspRegSetGAMA_C2A_SC(iq_handle_t *handle, IQ_GAMA_C2A_SC_CFG *cfg);
int IspRegSetR2Y(iq_handle_t *handle, IQ_R2Y_CFG *cfg);
int IspRegSetTwoDPK(iq_handle_t *handle, IQ_TwoDPK_CFG *cfg);
int IspRegSetLCE(iq_handle_t *handle, IQ_LCE_CFG *cfg);
int IspRegSetDLC(iq_handle_t *handle, IQ_DLC_CFG *cfg);
int IspRegSetHIST(iq_handle_t *handle, IQ_DLC_CFG *cfg);
int IspRegSetUVC(iq_handle_t *handle, IQ_UVC_CFG *cfg);
int IspRegSetIHC(iq_handle_t *handle, IQ_IHC_CFG *ihccfg, IQ_IHCICC_CFG *ihcicccfg);
int IspRegSetICC(iq_handle_t *handle, IQ_ICC_CFG *cfg, MS_U8 forceICC);
int IspRegSetIBC(iq_handle_t *handle, IQ_IBC_CFG *cfg);
int IspRegSetFCC(iq_handle_t *handle, IQ_FCC_CFG *cfg);
int IspRegSetACK(iq_handle_t *handle, IQ_ACK_CFG *cfg);
int IspRegSetYEE(iq_handle_t *handle, IQ_YEE_CFG *cfg);
int IspRegSetACLUT(iq_handle_t *handle, IQ_ACLUT_CFG *cfg);
int IspRegSetWDR_GBL(iq_handle_t *handle, IQ_WDR_GBL_CFG *cfg);
int IspRegSetWDR_LOC(iq_handle_t *handle, IQ_WDR_LOC_CFG *cfg);
int IspRegSetADJUV(iq_handle_t *handle, IQ_ADJUV_CFG *cfg);
int IspRegSetMXNR(iq_handle_t *handle, IQ_MXNR_CFG *cfg);
int IspRegSetYUVGAMA(iq_handle_t *handle, IQ_YUVGAMA_CFG *cfg);
int IspRegSetYCUVM10(iq_handle_t *handle, IQ_YCUVM10_CFG *cfg);
int IspRegSetCOLORTRANS(iq_handle_t *handle, IQ_COLORTRANS_CFG *cfg);

//mload
int IspMLoadSetFPN(iq_handle_t *handle);
int IspMLoadSetFPN_P1(iq_handle_t *handle);
int IspMLoadSetALSC(iq_handle_t *handle);
int IspMLoadSetALSC_P1(iq_handle_t *handle);
int IspMLoadSetDPC(iq_handle_t *handle);
int IspMLoadSetGAMA_16to16_ISP(iq_handle_t *handle);
int IspMLoadSetGAMA_C2C_P1_ISP(iq_handle_t *handle);
int IspMLoadSetGAMA_A2A_ISP(iq_handle_t *handle);
int IspMLoadSetGAMA_A2C_SC(iq_handle_t *handle);
int IspMLoadSetGAMA_C2A_SC(iq_handle_t *handle);
int IspMLoadSetYUVGAMA_Y(iq_handle_t *handle);
int IspMLoadSetYUVGAMA_VU(iq_handle_t *handle);
int IspMLoadSetWDR_LOC1(iq_handle_t *handle);
int IspMLoadSetWDR_LOC2(iq_handle_t *handle);

#endif //__iq_shadow__
