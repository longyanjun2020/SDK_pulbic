
#ifndef _PMBR_CFG_H_
#define _PMBR_CFG_H_

#define PMBR_MEM_MB_MAP_IN  0
#define PMBR_MEM_MB_MAP_OUT 1
#define PMBR_MEM_LUT        2
#define PMBR_MEM_NUM        3

// Look-up Table Size
#define PMBR_LUT_SIZE       15
#define PMBR_LOG2_HIST_SIZE 5

typedef union _pmbr_cfg {
    enum pmbr_cfg_e {
    PMBR_CFG_SEQ = 0,
    PMBR_CFG_QPR,
    PMBR_CFG_TC,
    PMBR_CFG_PC,
    PMBR_CFG_SS,
    PMBR_CFG_MEM
    } type;

    struct {
    enum pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_SEQ"
    int             i_enable;   /* PMBR Enable */
    int             i_mbw;      /* MB Width */
    int             i_mbh;      /* MB Height */
    } seq;

    struct {
    enum pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_QPR"
    int             i_iupperq;  /* QP Upper Bound */
    int             i_ilowerq;  /* QP Lower Bound */
    int             i_pupperq;  /* QP Upper Bound */
    int             i_plowerq;  /* QP Lower Bound */
    int             i_qptype_mask; /* Frame QP type mask */
    } qpr;
    
    struct {
    enum pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_TC"
    int             i_LutEntryClipRange;
    int             i_TextWeightType;
    int             i_SkinLvShift;
    int             i_WeightOffset;
    int             i_TcOffset;
    int             i_TcToSkinAlpha;
    int             i_TcGradThr;
    } tc;

    struct {
    enum pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_PC"
    int             i_PwYMax;
    int             i_PwYMin;
    int             i_PwCbMax;
    int             i_PwCbMin;
    int             i_PwCrMax;
    int             i_PwCrMin;
    int             i_PwCbPlusCrMin;
    int             i_PwAddConditionEn;
    int             i_PwCrOffset;
    int             i_PwCbCrOffset;
    int             i_PcDeadZone;
    } pc;
    
    struct {
    enum pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_SS"
    int             i_SmoothEn;
    int             i_SmoothClipMax;
    int             i_SecStgAlpha;
    int             i_SecStgBitWghtOffset;
    } ss;

    struct {
    enum pmbr_cfg_e i_type;     //!< MUST BE "PMBR_CFG_MEM"
    unsigned int    u_phys[PMBR_MEM_NUM];
    void*           p_kptr[PMBR_MEM_NUM];
    int             i_size[PMBR_MEM_NUM];
    } mem;
} pmbr_cfg;

#endif //_PMBR_CFG_H_
