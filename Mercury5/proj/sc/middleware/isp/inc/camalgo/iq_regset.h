/*
 * iq_regset
 *
 *  Created on: 2017/6/6
 *      Author: Daniel.Yu
 */

#ifndef __iq_regset__
#define __iq_regset__

#include <isp_types.h>


#define GAMMA_TBL                 (256)
#define ALSC_TBL_W                (61)
#define ALSC_TBL_H                (69)
#define ALSC_TBL                  (4209)
#define DEFECTPIX_TBL             (2048) 
#define FPN_TBL                   (2816)
#define YUVGAMMA_Y_TBL            (256)
#define YUVGAMMA_VU_TBL           (128)
#define WDR_LOC_TBL               (88)

typedef struct
{
    MS_U32 u4TSIdx;
    struct timespec ts[2];
} PROF_t;
/*
void pIQ_Profiling(PROF_t *strTS, char *pItemName);
void get_cfgdata(ISP_DBGBUF_HANDLE iq_dbg, int tag, void *dst, int offset);
void set_cfgdata(ISP_DBGBUF_HANDLE iq_dbg, int tag, void *src, int offset);
int  twos_complement_to_inter(int in);
int  interto_twos_complement(int in);
int  get_cfgcnt(int tag);
int  IQ_PARAMETER_TYPE(int type);
*/
#if 1
typedef struct
{
    MS_U8 s;
    MS_U8 m[100];
} INTER_EN;

typedef struct
{
    IQ2_TEMPTURE_CFG paraL;
    IQ2_TEMPTURE_CFG paraR;
    MS_U32 TempArr[3]; //[L, now, R]
    MS_U32 TempMin;
} INTERPA_TCtrl_t;

typedef struct
{
    IQ_DECOMP_CFG *paraL;
    IQ_DECOMP_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_DECOMP_t;

typedef struct
{
    IQ_FPN_CFG *paraL;
    IQ_FPN_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_FPN_t;

typedef struct
{
    IQ_FPN_P1_CFG *paraL;
    IQ_FPN_P1_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_FPN_P1_t;

typedef struct
{
    IQ_OBC_CFG *paraL;
    IQ_OBC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_OBC_t;

typedef struct
{
    IQ_OBC_P1_CFG *paraL;
    IQ_OBC_P1_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_OBC_P1_t;

typedef struct
{
    IQ_GAMA_16to16_ISP_CFG *paraL;
    IQ_GAMA_16to16_ISP_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_GAMA_16to16_ISP_t;

typedef struct
{
    IQ_GAMA_C2C_P1_ISP_CFG *paraL;
    IQ_GAMA_C2C_P1_ISP_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_GAMA_C2C_P1_ISP_t;

typedef struct
{
    IQ_LSC_CFG *paraL;
    IQ_LSC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U8 cctind;
    MS_U32 GainArr[3]; //[L, now, R]
    MS_U32 CctArr[3]; //[L, now, R]
} INTERPA_LSC_t;

typedef struct
{
    IQ_LSC_P1_CFG *paraL;
    IQ_LSC_P1_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U8 cctind;
    MS_U32 GainArr[3]; //[L, now, R]
    MS_U32 CctArr[3]; //[L, now, R]
} INTERPA_LSC_P1_t;

typedef struct
{
    IQ_ALSC_CFG *paraL;
    IQ_ALSC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U8 cctind;
    MS_U32 GainArr[3]; //[L, now, R]
    MS_U32 CctArr[3]; //[L, now, R]
} INTERPA_ALSC_t;

typedef struct
{
    IQ_ALSC_P1_CFG *paraL;
    IQ_ALSC_P1_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U8 cctind;
    MS_U32 GainArr[3]; //[L, now, R]
    MS_U32 CctArr[3]; //[L, now, R]
} INTERPA_ALSC_P1_t;

typedef struct
{
    IQ_HDR_CFG *paraL;
    IQ_HDR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_HDR_t;

typedef struct
{
    IQ_HDR_16to10_CFG *paraL;
    IQ_HDR_16to10_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_HDR_16to10_t;

typedef struct
{
    IQ_DPC_CFG *paraL;
    IQ_DPC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_DPC_t;

typedef struct
{
    IQ_GE_CFG *paraL;
    IQ_GE_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_GE_t;

typedef struct
{
    IQ_ANTICT_CFG *paraL;
    IQ_ANTICT_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_ANTICT_t;

typedef struct
{
    IQ_RGBIR_CFG *paraL;
    IQ_RGBIR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_RGBIR_t;

typedef struct
{
    IQ_SpikeNR_CFG *paraL;
    IQ_SpikeNR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_SpikeNR_t;

typedef struct
{
    IQ_SDC_CFG *paraL;
    IQ_SDC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_SDC_t;

typedef struct
{
    IQ_BSNR_CFG *paraL;
    IQ_BSNR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_BSNR_t;

typedef struct
{
    IQ_NM_CFG *paraL;
    IQ_NM_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_NM_t;

typedef struct
{
    IQ_DM_CFG *paraL;
    IQ_DM_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_DM_t;

typedef struct
{
    IQ_PostDN_CFG *paraL;
    IQ_PostDN_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_PostDN_t;

typedef struct
{
    IQ_FalseColor_CFG *paraL;
    IQ_FalseColor_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_FalseColor_t;

typedef struct
{
    IQ_GAMA_A2A_ISP_CFG *paraL;
    IQ_GAMA_A2A_ISP_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_GAMA_A2A_ISP_t;

typedef struct
{
    IQ_MCNR_CFG *paraL;
    IQ_MCNR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_MCNR_t;

typedef struct
{
    IQ_NLM_CFG *paraL;
    IQ_NLM_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_NLM_t;

typedef struct
{
    IQ_XNR_CFG *paraL;
    IQ_XNR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_XNR_t;

typedef struct
{
    IQ_LDC_CFG *paraL;
    IQ_LDC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_LDC_t;

typedef struct
{
    IQ_GAMA_A2C_SC_CFG *paraL;
    IQ_GAMA_A2C_SC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_GAMA_A2C_SC_t;

typedef struct
{
    IQ_CCM_CFG ccmL;
    IQ_CCM_CFG ccmR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U8 cctind;
    MS_U8 cctindNew;
    MS_U32 GainArr[3]; //[L, now, R]
    MS_U32 CctArr[3]; //[L, now, R]
} INTERPA_CCM_t;

typedef struct
{
    IQ_HSV_CFG *paraL;
    IQ_HSV_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
    MS_U32 CctArr[3]; //[L, now, R]
} INTERPA_HSV_t;

typedef struct
{
    IQ_GAMA_C2A_SC_CFG *paraL;
    IQ_GAMA_C2A_SC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_GAMA_C2A_SC_t;

typedef struct
{
    IQ_R2Y_CFG *paraL;
    IQ_R2Y_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_R2Y_t;

typedef struct
{
    IQ_TwoDPK_CFG *paraL;
    IQ_TwoDPK_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_TwoDPK_t;

typedef struct
{
    IQ_LCE_CFG *paraL;
    IQ_LCE_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_LCE_t;

typedef struct
{
    IQ_DLC_CFG *paraL;
    IQ_DLC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_DLC_t;

typedef struct
{
    IQ_UVC_CFG *paraL;
    IQ_UVC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_UVC_t;

typedef struct
{
    IQ_IHC_CFG paraL;
    IQ_IHC_CFG paraR;
    IQ_IHCICC_CFG *para2L;
    IQ_IHCICC_CFG *para2R;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_IHC_t;

typedef struct
{
    IQ_ICC_CFG paraL;
    IQ_ICC_CFG paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_ICC_t;

typedef struct
{
    IQ_IBC_CFG paraL;
    IQ_IBC_CFG paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_IBC_t;

typedef struct
{
    IQ_FCC_CFG *paraL;
    IQ_FCC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_FCC_t;

typedef struct
{
    IQ_ACK_CFG *paraL;
    IQ_ACK_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_ACK_t;

typedef struct
{
    IQ_YEE_CFG *paraL;
    IQ_YEE_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_YEE_t;

typedef struct
{
    IQ_ACLUT_CFG *paraL;
    IQ_ACLUT_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_ACLUT_t;

typedef struct
{
    IQ_WDR_GBL_CFG *paraL;
    IQ_WDR_GBL_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_WDR_GBL_t;

typedef struct
{
    IQ_WDR_LOC_CFG *paraL;
    IQ_WDR_LOC_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_WDR_LOC_t;

typedef struct
{
    IQ_ADJUV_CFG *paraL;
    IQ_ADJUV_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_ADJUV_t;

typedef struct
{
    IQ_MXNR_CFG *paraL;
    IQ_MXNR_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_MXNR_t;

typedef struct
{
    IQ_YUVGAMA_CFG *paraL;
    IQ_YUVGAMA_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_YUVGAMA_t;

typedef struct
{
    IQ_YCUVM10_CFG *paraL;
    IQ_YCUVM10_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_YCUVM10_t;

typedef struct
{
    IQ_COLORTRANS_CFG *paraL;
    IQ_COLORTRANS_CFG *paraR;
    MS_U8 isoind;
    MS_U8 blkind;
    MS_U32 GainArr[3]; //[L, now, R]
} INTERPA_COLORTRANS_t;
#endif

int IQ_CCMSaturctionCalc(IQ_CCM_CFG *ccm, MS_U16 sat[3], MS_BOOL doCT);
int IQ_UVCMSaturctionCalc(IQ_R2Y_CFG *uvcm, MS_U16 sat);

//=====[CFG Set][S]=====//
#if 1
int IQ_Set_InterpSet_CFG(iq_handle_t *handle, MS_U8 mode);
int IQ_Set_TempCtrl_CFG(iq_handle_t *handle, MS_U8 tind, MS_U8 mode);
int IQ_Set_INIT_CFG(iq_handle_t *handle);

int IQ_Set_DECOMP_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_FPN_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_FPN_P1_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_OBC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_OBC_P1_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_GAMA_16to16_ISP_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_GAMA_C2C_P1_ISP_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_LSC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Set_LSC_P1_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Set_ALSC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Set_ALSC_P1_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Set_HDR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_HDR_16to10_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_DPC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_GE_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_ANTICT_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_RGBIR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_SpikeNR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_SDC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_BSNR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_NM_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_DM_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_PostDN_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_FalseColor_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_GAMA_A2A_ISP_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_MCNR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_NLM_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_XNR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_LDC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_GAMA_A2C_SC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_CCM_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Set_HSV_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Set_GAMA_C2A_SC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_R2Y_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_TwoDPK_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_LCE_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_DLC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_HIST_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_UVC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_IHC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_ICC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode, MS_U8 forceICC);
int IQ_Set_IBC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_FCC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_ACK_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_YEE_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_ACLUT_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_WDR_GBL_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_WDR_LOC_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_ADJUV_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_MXNR_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_YUVGAMA_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_YCUVM10_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
int IQ_Set_COLORTRANS_CFG(iq_handle_t *handle, MS_U8 isoind, MS_U8 blkind, MS_U8 mode);
#endif


//=====[CFG Get][S]=====//
#if 1
int IQ_Get_DECOMP_CFG(iq_handle_t *handle, IQ_DECOMP_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_FPN_CFG(iq_handle_t *handle, IQ_FPN_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_FPN_P1_CFG(iq_handle_t *handle, IQ_FPN_P1_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_OBC_CFG(iq_handle_t *handle, IQ_OBC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_OBC_P1_CFG(iq_handle_t *handle, IQ_OBC_P1_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_GAMA_16to16_ISP_CFG(iq_handle_t *handle, IQ_GAMA_16to16_ISP_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_GAMA_C2C_P1_ISP_CFG(iq_handle_t *handle, IQ_GAMA_C2C_P1_ISP_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_LSC_CFG(iq_handle_t *handle, IQ_LSC_CFG *cfg, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Get_LSC_P1_CFG(iq_handle_t *handle, IQ_LSC_P1_CFG *cfg, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Get_ALSC_CFG(iq_handle_t *handle, IQ_ALSC_CFG *cfg, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Get_ALSC_P1_CFG(iq_handle_t *handle, IQ_ALSC_P1_CFG *cfg, MS_U8 blkind, MS_U8 cctind, MS_U8 mode);
int IQ_Get_HDR_CFG(iq_handle_t *handle, IQ_HDR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_HDR_16to10_CFG(iq_handle_t *handle, IQ_HDR_16to10_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_DPC_CFG(iq_handle_t *handle, IQ_DPC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_GE_CFG(iq_handle_t *handle, IQ_GE_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_ANTICT_CFG(iq_handle_t *handle, IQ_ANTICT_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_RGBIR_CFG(iq_handle_t *handle, IQ_RGBIR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_SpikeNR_CFG(iq_handle_t *handle, IQ_SpikeNR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_SDC_CFG(iq_handle_t *handle, IQ_SDC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_BSNR_CFG(iq_handle_t *handle, IQ_BSNR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_NM_CFG(iq_handle_t *handle, IQ_NM_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_DM_CFG(iq_handle_t *handle, IQ_DM_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_PostDN_CFG(iq_handle_t *handle, IQ_PostDN_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_FalseColor_CFG(iq_handle_t *handle, IQ_FalseColor_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_GAMA_A2A_ISP_CFG(iq_handle_t *handle, IQ_GAMA_A2A_ISP_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_MCNR_CFG(iq_handle_t *handle, IQ_MCNR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_NLM_CFG(iq_handle_t *handle, IQ_NLM_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_XNR_CFG(iq_handle_t *handle, IQ_XNR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_GAMA_A2C_SC_CFG(iq_handle_t *handle, IQ_GAMA_A2C_SC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_CCM_CFG(iq_handle_t *handle, IQ_CCM_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_HSV_CFG(iq_handle_t *handle, IQ_HSV_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_GAMA_C2A_SC_CFG(iq_handle_t *handle, IQ_GAMA_C2A_SC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_R2Y_CFG(iq_handle_t *handle, IQ_R2Y_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_TwoDPK_CFG(iq_handle_t *handle, IQ_TwoDPK_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_LCE_CFG(iq_handle_t *handle, IQ_LCE_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_DLC_CFG(iq_handle_t *handle, IQ_DLC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_UVC_CFG(iq_handle_t *handle, IQ_UVC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_IHC_CFG(iq_handle_t *handle, IQ_IHC_CFG *cfg, IQ_IHCICC_CFG *cfg1, MS_U8 blkind, MS_U8 mode);
int IQ_Get_ICC_CFG(iq_handle_t *handle, IQ_ICC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_IBC_CFG(iq_handle_t *handle, IQ_IBC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_FCC_CFG(iq_handle_t *handle, IQ_FCC_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_ACK_CFG(iq_handle_t *handle, IQ_ACK_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_YEE_CFG(iq_handle_t *handle, IQ_YEE_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_ACLUT_CFG(iq_handle_t *handle, IQ_ACLUT_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_ADJUV_CFG(iq_handle_t *handle, IQ_ADJUV_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_MXNR_CFG(iq_handle_t *handle, IQ_MXNR_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_YUVGAMA_CFG(iq_handle_t *handle, IQ_YUVGAMA_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_YCUVM10_CFG(iq_handle_t *handle, IQ_YCUVM10_CFG *cfg, MS_U8 blkind, MS_U8 mode);
int IQ_Get_COLORTRANS_CFG(iq_handle_t *handle, IQ_COLORTRANS_CFG *cfg, MS_U8 blkind, MS_U8 mode);
/*==Functions for Get Values from Sinale Block (E)==*/
#endif
//=====[CFG Get][E]=====//

#endif /* __iq_regset__ */
