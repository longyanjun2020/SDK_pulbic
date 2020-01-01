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
#ifndef _MDRV_RQCT_ST_H_
#define _MDRV_RQCT_ST_H_

#define RQCTIF_MAJ              1   //!< major version: Major number of driver-I/F version.
#define RQCTIF_MIN              1   //!< minor version: Minor number of driver-I/F version.
#define RQCTIF_EXT              1   //!< extended code: Extended number of version. It should increase when "mdrv_rqct_io.h/mdrv_rqct_st.h" changed.

//! RQCT Interface version number.
#define RQCTIF_VERSION_ID       ((RQCTIF_MAJ<<22)|(RQCTIF_MIN<<12)|(RQCTIF_EXT))
//! Acquire version number.
#define RQCTIF_GET_VER(v)       (((v)>>12))
//! Acquire major version number.
#define RQCTIF_GET_MJR(v)       (((v)>>22)&0x3FF)
//! Acquire minor version number.
#define RQCTIF_GET_MNR(v)       (((v)>>12)&0x3FF)
//! Acquire extended number.
#define RQCTIF_GET_EXT(v)       (((v)>> 0)&0xFFF)

//! rqct-factory : support 3 factory.
enum rqct_factory {
    RQCT_FACTORY_ARQC = 0,
};

//! rqct-method : support 3 types - CQP, CBR, VBR.
enum rqct_method {
    RQCT_METHOD_CQP = 0,    //!< constant QP.
    RQCT_METHOD_CBR,        //!< constant bitrate.
    RQCT_METHOD_VBR,        //!< variable bitrate.
};

//! mvhe_superfrm_mode indicates super frame mechanism
enum rqct_superfrm_mode {
    RQCT_SUPERFRM_NONE = 0, //!< super frame mode none.
    RQCT_SUPERFRM_DISCARD,  //!< super frame mode discard.
    RQCT_SUPERFRM_REENCODE, //!< super frame mode reencode.
};

//! rqct_conf is used to apply/query rq-configs during streaming period.
typedef union _drv_rqct_cfg {
    //! rqct-config type.
    enum rqct_conf_e {
    RQCT_CONF_SEQ = 0,  //!< set sequence rate-control.
    RQCT_CONF_FORCE_I,  //!< set force I frame configuration.
    RQCT_CONF_SKIP,     //!< set skip frame configuration.
    RQCT_CONF_BPS,      //!< set bitrate.
    RQCT_CONF_QP,      	//!< set QP initial value.
    RQCT_CONF_DQP,      //!< set delta-QP between I/P.
    RQCT_CONF_QPR,      //!< set QP range.
    RQCT_CONF_LOG,      //!< turn on/off rqct log message.
    RQCT_CONF_PEN,      //!< penalties for mfe.
    RQCT_CONF_VBV,      //!< leaky buffer settings.
    RQCT_CONF_FPS,      //!< frame rate
    RQCT_CONF_END,      //!< end of rqct-conf-enum.
    } type;             //!< indicating config. type.

    struct _seq {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_SEQ.
    int                 i_period;           //!< ip-period.
    unsigned char       b_runtime_upd;      //!< run time update.
    } seq;

    struct _force_i {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_FORCE_I.
    unsigned char       b_force_Ifrm;       //!< force I frame.
    unsigned char       b_set_Ifrm;         //!< set I frame.
    unsigned char       b_insert_spspps;    //!< insert SPS, PPS.
    } force_i;

    struct _skip {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_SKIP.
    int                 i_skippable;        //!< RC can skip frames or not
    int                 i_skipType;         //!< 0: direct skip, 1: smooth skip
    int                 i_skipBypass;       //!< bypass current frame RC skip
    int                 i_skipThd;          //!< skip frame threshold
    unsigned char       b_runtime_upd;      //!< run time update
    } skip;

    struct _bps {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_BPS.
    enum rqct_method    i_method;           //!< indicating rqct-method.
    int                 i_btrate;           //!< bitrate.
    int                 i_layerbr[2];       //!< layer bitrate
    unsigned char       b_runtime_upd;      //!< run time update
    } bps;

    struct _qp {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_QP.
    int                 i_leadqp;           //!< lead QP.
    int                 i_layerqp[2][3];    //!< layer QP [layer][frm_type]
    } qp;

    struct _dqp {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_DQP.
    int                 i_dqp;              //!< dif-qp between I/P.
    } dqp;

    struct _qpr {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_QPR.
    int                 i_iupperq;          //!< I frame upperq.
    int                 i_ilowerq;          //!< I frame lowerq.
    int                 i_pupperq;          //!< P frame upperq.
    int                 i_plowerq;          //!< P frame lowerq.
    int                 i_qptype_mask;      //!< frame QP type mask
    } qpr;

    struct _log {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_LOG.
    int                 b_logm;             //!< switch of log-message.
    } log;

    struct _pen {
    enum rqct_conf_e    i_type;             //!< i_type MUST be RQCT_CFG_PEN.
    short               b_i16pln;           //!< enable intra16 planar.
    short               i_peni4x;           //!< penalty intra4x4.
    short               i_peni16;           //!< penalty intra16.
    short               i_penint;           //!< penalty inter.
    short               i_penYpl;           //!< penalty planar luma.
    short               i_penCpl;           //!< penalty planar cbcr.
    } pen;

    struct _vbv {
    enum rqct_conf_e    i_type;             //!< i_type MUST be MVHE_PARM_VBV.
    int                 i_leakyBufSzInMs[2];//!< leady buffer size
    unsigned char       b_runtime_upd;      //!< run time update
    } vbv;

    struct {
    enum rqct_conf_e    i_type;             //!< MUST BE "RQCT_CFG_FPS"
    short               n_fps;              //!< FPS numerator
    short               d_fps;              //!< FPS denominator
    short               n_snrfps;          	//!< FPS numerator
    short               d_snrfps;          	//!< FPS denominator
    } fps;
} drv_rqct_cfg;

#endif //_MDRV_RQCT_ST_H_
//! @}
