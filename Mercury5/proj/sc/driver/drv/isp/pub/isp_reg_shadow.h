#ifndef ISP_SHADOW_H
#define ISP_SHADOW_H
#include <mercury5_reg.h>
#include <mdrv_vip_io_i3_st.h>
#include <mdrv_vip_io_i3.h>
#include <hal_isp.h>
#include <drv_isp.h>

/* IQ shadow IndBlk*/
typedef enum
{
    SHAD_DECOMP,                //[0]
    SHAD_FPN,                   //[1]
    SHAD_FPN_P1,                //[2]
    SHAD_OBC,                   //[3]
    SHAD_OBC_P1,                //[4]
    SHAD_GAMA_16to16_ISP,       //[5]
    SHAD_GAMA_C2C_P1_ISP,       //[6]
    SHAD_LSC,                   //[7]
    SHAD_LSC_P1,                //[8]
    SHAD_ALSC,                  //[9]
    SHAD_ALSC_P1,               //[10]
    SHAD_HDR,                   //[11]
    SHAD_HDR_16to10,            //[12]
    SHAD_DPC,                   //[13]
    SHAD_GE,                    //[14]
    SHAD_ANTICT,                //[15]
    SHAD_RGBIR,                 //[16]
    SHAD_SpikeNR,               //[17]
    SHAD_SDC,                   //[18]
    SHAD_BSNR,                  //[19]
    SHAD_NM,                    //[20]
    SHAD_DM,                    //[21]
    SHAD_PostDN,                //[22]
    SHAD_FalseColor,            //[23]
    SHAD_GAMA_A2A_ISP,          //[24]
    SHAD_MCNR,                  //[25]
    SHAD_NLM,                   //[26]
    SHAD_XNR,                   //[27]
    SHAD_LDC,                   //[28]
    SHAD_Y2R,                   //[29]
    SHAD_GAMA_A2C_SC,           //[30]
    SHAD_CCM,                   //[31]
    SHAD_HSV,                   //[32]
    SHAD_GAMA_C2A_SC,           //[33]
    SHAD_R2Y,                   //[34]
    SHAD_TwoDPK,                //[35]
    SHAD_LCE,                   //[36]
    SHAD_DLC,                   //[37]
    SHAD_HIST,                  //[38]
    SHAD_UVC,                   //[39]
    SHAD_IHC,                   //[40]
    SHAD_ICC,                   //[41]
    SHAD_IBC,                   //[42]
    SHAD_IHCICC,                //[43]
    SHAD_FCC,                   //[44]
    SHAD_ACK,                   //[45]
    SHAD_YEE,                   //[46]
    SHAD_ACLUT,                 //[47]
    SHAD_WDR_GBL,               //[48]
    SHAD_WDR_LOC,               //[49]
    SHAD_ADJUV,                 //[50]
    SHAD_MXNR,                  //[51]
    SHAD_YUVGAMA,               //[52]
    SHAD_YCUVM10,               //[53]
    SHAD_COLORTRANS,            //[54]
    SHAD_MLOAD_FPN,             //[56]
    SHAD_MLOAD_FPN_P1,          //[57]
    SHAD_MLOAD_ALSC,            //[58]
    SHAD_MLOAD_ALSC_P1,         //[59]
    SHAD_MLOAD_GAMA_16to16_ISP, //[60]
    SHAD_MLOAD_GAMA_C2C_P1_ISP, //[61]
    SHAD_MLOAD_GAMA_A2A_ISP,    //[62]
    SHAD_MLOAD_DPC,             //[63]
    SHAD_MLOAD_GAMA_A2C_SC,     //[64]
    SHAD_MLOAD_GAMA_C2A_SC,     //[65]
    SHAD_MLOAD_YUVGAMA_Y,       //[66]
    SHAD_MLOAD_YUVGAMA_VU,      //[67]
    SHAD_MLOAD_WDR_LOC1,        //[68]
    SHAD_MLOAD_WDR_LOC2,        //[69]
    SHAD_BLKMAX,
} IQ_SHAD_ENUM;


typedef struct
{
    //isp
    mercury5_reg_isp0       isp0_cfg;
    mercury5_reg_isp1       isp1_cfg;
    mercury5_reg_isp2       isp2_cfg;
    mercury5_reg_isp3       isp3_cfg;
    mercury5_reg_isp4       isp4_cfg;
    mercury5_reg_isp5       isp5_cfg;
    mercury5_reg_isp6       isp6_cfg;
    mercury5_reg_isp7       isp7_cfg;
    mercury5_reg_isp8       isp8_cfg;
    mercury5_reg_isp9       isp9_cfg;
    mercury5_reg_isp10      isp10_cfg;
    mercury5_reg_isp11      isp11_cfg;
    mercury5_reg_isp12      isp12_cfg;

    //mload
    MLoadLayout             mload_cfg;
/*
    //alsc
    MS_U32  alsc_h_tbl[33];
    MS_U32  alsc_v_tbl[33];
*/
    //awb
    IQ_WBG_CFG wbg;

    //ae dgain
    u16 isp_gain_p0;
    u16 isp_gain_p1;

    //scl
    ST_IOCTL_VIP_ALL_CONFIG vip_cfg;

    //scl_sram
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_gama_a2c_sc_r;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_gama_a2c_sc_g;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_gama_a2c_sc_b;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_gama_c2a_sc_r;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_gama_c2a_sc_g;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_gama_c2a_sc_b;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_yuvgama_y;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_yuvgama_u;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_yuvgama_v;
    ST_IOCTL_VIP_AIP_SRAM_CONFIG sram_wdr_loc;

    //scl_sram_tbl
    MS_U16 tbl_gama_a2c_sc_r[256];
    MS_U16 tbl_gama_a2c_sc_g[256];
    MS_U16 tbl_gama_a2c_sc_b[256];
    MS_U16 tbl_gama_c2a_sc_r[256];
    MS_U16 tbl_gama_c2a_sc_g[256];
    MS_U16 tbl_gama_c2a_sc_b[256];
    MS_U16 tbl_yuvgama_y[256];
    MS_U16 tbl_yuvgama_u[128];
    MS_U16 tbl_yuvgama_v[128];
    MS_U16 tbl_wdr_loc[648];

    //scl_tbl
    MS_U8  scl_mcnr[134];
    MS_U8  scl_xnr[24];
    MS_U8  scl_y2r[30];
    MS_U8  scl_gama_a2c_sc[5];
    MS_U8  scl_ccm[33];
    MS_U8  scl_hsv[73];
    MS_U8  scl_gama_c2a_sc[5];
    MS_U8  scl_r2y[30];
    MS_U8  scl_yee[210];
    MS_U8  scl_aclut[67];
    MS_U8  scl_wdr_gbl[123];
    MS_U8  scl_wdr_loc[139+1];
    MS_U8  scl_adjuv[68];
    MS_U8  scl_mxnr[20];
    MS_U8  scl_yuvgama[9];
    MS_U8  scl_ycuvm[8];
    MS_U8  scl_colortrans[28];

    //Apply Shadow Flag
    MS_BOOL dirty[SHAD_BLKMAX];

    //SCL Chn ID
    MS_S32  nSclCh;

}IspRegShd_t;

/* IQ shadow API*/
typedef enum
{
    eIspShdInit,
    eIspShdRuntime,
    eIspShdVsyncEnd,
}IspShdStage_e;
int DrvIsp_ApplyShadow(ISP_DRV_HANDLE handle,IspRegShd_t *pIspShd,IQ_SHAD_ENUM BlkInd);
int DrvIsp_ApplyShadowEx(ISP_DRV_HANDLE handle,IspRegShd_t *pIspShd,IspShdStage_e eStage);
#endif
