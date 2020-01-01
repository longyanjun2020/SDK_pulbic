
#ifndef _RQCT_CFG_H_
#define _RQCT_CFG_H_

typedef union  rqct_cfg rqct_cfg;
typedef struct rqct_buf rqct_buf;
typedef union  arqc_ctl arqc_ctl;

union rqct_cfg {
    enum rqct_cfg_e {
    RQCT_CFG_SEQ = 0,
    RQCT_CFG_FORCE_I,
    RQCT_CFG_SKIP,
    RQCT_CFG_BPS,
    RQCT_CFG_QP,
    RQCT_CFG_DQP,
    RQCT_CFG_QPR,
    RQCT_CFG_LOG,
    RQCT_CFG_PEN,
    RQCT_CFG_VBV,
    RQCT_CFG_FPS,
    RQCT_CFG_RES = 32,
    RQCT_CFG_ROI,
    RQCT_CFG_DQM,
    RQCT_CFG_PSKIP,
    } type;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_SEQ"
    int             i_period;           /* GOP */
    bool            b_runtime_upd;      /* Run Time Update */
    } seq;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_FORCE_I"
    bool            b_force_Ifrm;      	/* Force I Frame */
    bool            b_set_Ifrm;         /* Set I Frame Type from MiddleWare */
    bool            b_insert_spspps;    /* Insert SPS, PPS*/
    } force_i;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_BPS"
    int             i_skippable;        /* RC can skip frames or not */
    int             i_skipType;         /* 0: direct skip, 1: smooth skip */
    int             i_skipBypass;       /* Bypass current frame RC skip */
    int             i_skipThd;          /* Skip Frame Threshold */
    bool            b_runtime_upd;      /* Run Time Update */
    } skip;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_BPS"
    enum rqct_mode {
        RQCT_MODE_CQP = 0,
        RQCT_MODE_CBR,
        RQCT_MODE_VBR,
    }               i_method;           /* Rate Control Method */
    int             i_btrate;           /* Bitrate */
    int             i_layerbr[2];       /* Layer Bitrate */
    bool            b_runtime_upd;      /* Run Time Update */
    } bps;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_QP"
    int             i_leadqp;           /* Frame Level QP */
    int             i_layerqp[2][3];    /* Layer QP [layer][frm_type] */
    } qp;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_DQP"
    int             i_dqp;              /* QP Delta Range */
    } dqp;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_QPR"
    int             i_iupperq;          /* QP Upper Bound */
    int             i_ilowerq;          /* QP Lower Bound */
    int             i_pupperq;          /* QP Upper Bound */
    int             i_plowerq;          /* QP Lower Bound */
    int             i_qptype_mask;      /* Frame QP Type Mask */
    } qpr;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_LOG"
    int             b_logm;             /* Log Enable */
    } log;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_PEN"
    short           b_i16pln;           /* Intra 16x16 Planar Mode Enable */
    short           i_peni4x;           /* Intra 4x4 Cost Penalty */
    short           i_peni16;           /* Intra 16x16 Cost Penalty */
    short           i_penint;           /* Inter Cost Penalty */
    short           i_penYpl;           /* Intra 16x16 Lume Cost Penalty */
    short           i_penCpl;           /* Intra 8x8 Chroma Cost Penalty */
    } pen;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST be RQCT_CFG_VBV.
    int             i_leakyBufSzInMs[2];/* Leaky Buffer Size */
    bool            b_runtime_upd;      /* Run Time Update */
    } vbv;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_FPS"
    short           n_fps;              /* FPS Numerator */
    short           d_fps;              /* FPS Denominator */
    short           n_snrfps;           /* Sensor FPS Numerator */
    short           d_snrfps;           /* Sensor FPS Denominator */
    } fps;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_RES"
    short           i_picw;             /* Picture Width */
    short           i_pich;             /* Picture Height */
    } res;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_ROI"
    short           i_roiidx;           /* ROI Rectangle Index */
    short           i_roidqp;           /* ROI Rectangle QP Delta Range */
    short           i_posx;             /* ROI Rectangle StartX */
    short           i_posy;             /* ROI Rectangle StartY */
    short           i_recw;             /* ROI Rectangle Width */
    short           i_rech;             /* ROI Rectangle Height */
    } roi;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_DQM"
    unsigned int    u_phys;             /* DQM Buffer Physical Address */
    void*           p_kptr;             /* DQM Buffer Virtual Address */
    short           i_dqmw;             /* DQM MB Width */
    short           i_dqmh;             /* DQM MB Height */
    int             i_size;             /* DQM Buffer Size */
    int             i_unit;
    } dqm;

    struct {
    enum rqct_cfg_e i_type;             //!< MUST BE "RQCT_CFG_PSKIP"
    int             i_zmv_thd;
    int             i_non_zmv_thd;
    } pskip;
};

struct  rqct_buf {
    unsigned int    u_config;   /* Not Used Now */
};

#endif //_RQCT_CFG_H_
