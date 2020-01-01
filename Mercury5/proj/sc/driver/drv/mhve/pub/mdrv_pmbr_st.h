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

//! @file mdrv_rqct_st.h
//! @author MStar Semiconductor Inc.
//! @brief VHE Driver IOCTL User's Interface.
//! \ingroup rqct_group VHE driver
//! @{
#ifndef _MDRV_PMBR_ST_H_
#define _MDRV_PMBR_ST_H_

#define DRV_PMBR_MEM_MB_MAP_IN  0
#define DRV_PMBR_MEM_MB_MAP_OUT 1
#define DRV_PMBR_MEM_LUT        2
#define DRV_PMBR_MEM_NUM        3

typedef union _drv_pmbr_cfg {
    enum drv_pmbr_cfg_e {
    DRV_PMBR_CFG_SEQ = 0,
    DRV_PMBR_CFG_QPR,
    DRV_PMBR_CFG_TC,
    DRV_PMBR_CFG_PC,
    DRV_PMBR_CFG_SS,
    DRV_PMBR_CFG_MEM,
    DRV_PMBR_CFG_END
    } type;
    
    struct {
    enum drv_pmbr_cfg_e i_type;     //!< MUST BE "DRV_PMBR_CFG_SEQ"
    int                 i_enable;   /* PMBR Enable */
    int                 i_mbw;      /* MB Width */
    int                 i_mbh;      /* MB Height */
    } seq;
    
    struct {
    enum drv_pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_QPR"
    int                 i_iupperq;  /* QP Upper Bound */
    int                 i_ilowerq;  /* QP Lower Bound */
    int                 i_pupperq;  /* QP Upper Bound */
    int                 i_plowerq;  /* QP Lower Bound */
    int                 i_qptype_mask; /* Frame QP type mask */
    } qpr;

    struct {
    enum drv_pmbr_cfg_e i_type;     //!< MUST BE "DRV_PMBR_CFG_TC"
    int                 i_LutEntryClipRange;
    int                 i_TextWeightType;
    int                 i_SkinLvShift;
    int                 i_WeightOffset;
    int                 i_TcOffset;
    int                 i_TcToSkinAlpha;
    int                 i_TcGradThr;
    } tc;
    
    struct {
    enum drv_pmbr_cfg_e i_type;     //!< MUST BE "DRV_PMBR_CFG_PC"
    int                 i_PwYMax;
    int                 i_PwYMin;
    int                 i_PwCbMax;
    int                 i_PwCbMin;
    int                 i_PwCrMax;
    int                 i_PwCrMin;
    int                 i_PwCbPlusCrMin;
    int                 i_PwAddConditionEn;
    int                 i_PwCrOffset;
    int                 i_PwCbCrOffset;
    int                 i_PcDeadZone;
    } pc;
    
    struct {
    enum drv_pmbr_cfg_e i_type;     //!< MUST BE "DRV_PMBR_CFG_SS"
    int                 i_SmoothEn;
    int                 i_SmoothClipMax;
    int                 i_SecStgAlpha;
    int                 i_SecStgBitWghtOffset;
    } ss;
    
    struct {
    enum drv_pmbr_cfg_e i_type;     //!< MUST BE "DRV_PMBR_CFG_MEM"
    unsigned int        u_phys[DRV_PMBR_MEM_NUM];
    void*               p_kptr[DRV_PMBR_MEM_NUM];
    int                 i_size[DRV_PMBR_MEM_NUM];
    } mem;
} drv_pmbr_cfg;

#endif //_MDRV_PMBR_ST_H_
//! @}
