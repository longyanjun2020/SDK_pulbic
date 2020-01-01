
#ifndef _MHVE_OPS_H_
#define _MHVE_OPS_H_

typedef struct mhve_ops mhve_ops;
typedef struct mhve_vpb mhve_vpb;
typedef struct mhve_cpb mhve_cpb;
typedef union  mhve_cfg mhve_cfg;

typedef signed long long   int64;
typedef unsigned int       uint;

typedef int MfeOPsSyncPSCBFunc(int, int, int);

#define MFE_FORCE_NO_CROP (0)
#define MFE_ARQC_VBR_TEST (0)
#define TEST_VBR_CONSTANT (1)

#define MFE_W_ALIGN_SHIFT_YUV422    (4) // Base 2^4
#define MFE_H_ALIGN_SHIFT_YUV422    (4) // Base 2^4
#define MFE_W_ALIGN_SHIFT_NV12      (4) // Base 2^4
#define MFE_H_ALIGN_SHIFT_NV12      (4) // Base 2^4

#define _MAX(a,b)   ((a)>(b)?(a):(b))
#define _MIN(a,b)   ((a)<(b)?(a):(b))

#define MHVE_FLAGS_FORCEI   (1 << 0)
#define MHVE_FLAGS_DISREF   (1 << 1)

// Video picture buffer
struct mhve_vpb {
    int     i_index;    // Buffer index
    uint    u_flags;    // Control flag
    int64   i_stamp;    // Time-stamp of current frame
    int     i_pitch;    // Buffer line-offset
    struct {
    uint    u_phys;     // Buffer address
    int     i_bias;     // CHECK!
    int     i_size;     // Buffer size
    } planes[2];
    struct {
    uint    u_phys;     // Buffer address
    int     i_bias;     // CHECK!
    int     i_size;     // Buffer size
    } gplanes[2];
};

#define MHVE_FLAGS_EOP      (1<<31)
#define MHVE_FLAGS_SOP      (1<<30)

// Coded picture buffer
struct mhve_cpb {
    int     i_index;    // Buffer index
    int     i_flags;    // Control flag
    int64   i_stamp;    // Time-stamp of current frame
    int     i_count;    // [Not Used]
    struct {
    uint    u_phys;     // Buffer address
    int     i_size;     // Buffer size
    } planes[2];
};

typedef enum mhve_pix_e {
    MHVE_PIX_NV12 = 0,
    MHVE_PIX_NV21,
    MHVE_PIX_YUYV,
    MHVE_PIX_YVYU,
} mhve_pix_e;

#define MHVE_INTER_4x4          (1<<0)  //!< bit-field of  4x4  block
#define MHVE_INTER_8x4          (1<<1)  //!< bit-field of  8x4  block
#define MHVE_INTER_4x8          (1<<2)  //!< bit-field of  4x8  block
#define MHVE_INTER_8x8          (1<<3)  //!< bit-field of  8x8  block
#define MHVE_INTER_16x8         (1<<4)  //!< bit-field of 16x8  block
#define MHVE_INTER_8x16         (1<<5)  //!< bit-field of  8x16 block
#define MHVE_INTER_16x16        (1<<6)  //!< bit-field of 16x16 block
#define MHVE_INTER_SKIP         (1<<7)  //!< bit-field of skip

#define MHVE_AVC_PROFILE_BP     66      //!< H.264 Base Line Profile
#define MHVE_AVC_PROFILE_MP     77      //!< H.264 Main Profile

#define MHVE_AVC_LEVEL_3        30      //!< H.264 Level-3.0
#define MHVE_AVC_LEVEL_31       31      //!< H.264 Level-3.1
#define MHVE_AVC_LEVEL_32       32      //!< H.264 Level-3.2
#define MHVE_AVC_LEVEL_4        40      //!< H.264 Level-4.0

union  mhve_cfg {
    enum mhve_cfg_e {
        MHVE_CFG_RES = 0,
        MHVE_CFG_DMA,
        MHVE_CFG_MOT,
        MHVE_CFG_AVC,
        MHVE_CFG_HEV,
        MHVE_CFG_VUI,
        MHVE_CFG_LFT,
        MHVE_CFG_SPL,
        MHVE_CFG_BAC,
    } type;
    struct {
        enum mhve_cfg_e i_type;
        mhve_pix_e      e_pixf;                         // Input frame format
        short           i_pixw, i_pixh;                 // Input frame width / height
        int             i_rpbn;                         // Reference buffer count
#define MHVE_CFG_COMPR  (1<<0)
#define MHVE_CFG_OMMAP  (1<<1)
        uint            u_conf;                         // [Not Used]
        char            i_ClkEn;                        // MFE clock enable
        char            i_ClkSor;                       // MFE clock source
    } res;
    struct {
        enum mhve_cfg_e i_type;
        int             i_dmem;                         // 0~1:For reference buffer -1:For Output bitstream buffer -2:GN buffer
        void*           p_vptr;                         // Buffer virtual address
        uint            u_phys;                         // Buffer physical address
        uint            u_phys0_st;                     // Buffer0 physical start address (Double Buffer Use)
        uint            u_phys0_ed;                     // Buffer0 physical end address (Double Buffer Use)
        uint            u_phys1_st;                     // Buffer1 physical start address (Double Buffer Use)
        uint            u_phys1_ed;                     // Buffer1 physical end address (Double Buffer Use)
        int             i_size[6];                      // Buffer size
    } dma;
    struct {
        enum mhve_cfg_e i_type;
        int             i_subp;                         // Sub-Pixel prediction
        short           i_dmvx;                         // Motion estimation X range
        short           i_dmvy;                         // Motion estimation Y range
        uint            i_blkp[2];                      // Motion estimation block size
    } mot;
    struct {
        enum mhve_cfg_e i_type;
        unsigned short  i_profile;                      // Profile.
        unsigned short  i_level;                        // Level.
        unsigned char   i_num_ref_frames;               // Ref.frames count.
        unsigned char   i_poc_type;                     // Poc_type: support 0,2.
        unsigned char   b_entropy_coding_type;          // Entropy: cabac/cavlc.
        unsigned char   b_constrained_intra_pred;       // Constrained intra pred.
        unsigned char   b_deblock_filter_control;       // Deblock filter control.
        unsigned char   i_disable_deblocking_idc;       // Disable deblocking idc.
          signed char   i_alpha_c0_offset;              // Offset alpha div2.
          signed char   i_beta_offset;                  // Offset beta div2.
    } avc;
    struct {
        enum mhve_cfg_e i_type;
        unsigned short  i_profile;                      // [Not Used] : profile.
        unsigned short  i_level;                        // [Not Used] : level.
        unsigned char   i_log2_max_cb_size;             // [Not Used] : max ctb size.
        unsigned char   i_log2_min_cb_size;             // [Not Used] : min ctb size.
        unsigned char   i_log2_max_tr_size;             // [Not Used] : max trb size.
        unsigned char   i_log2_min_tr_size;             // [Not Used] : min trb size.
        unsigned char   i_tr_depth_intra;               // [Not Used] : tr depth intra.
        unsigned char   i_tr_depth_inter;               // [Not Used] : tr depth inter.
        unsigned char   b_scaling_list_enable;          // [Not Used] : scaling list enable.
        unsigned char   b_sao_enable;                   // [Not Used] : sao enable.
        unsigned char   b_strong_intra_smoothing;       // [Not Used] : strong intra smoothing.
        unsigned char   b_ctu_qp_delta_enable;          // [Not Used] : ctu qp delta enable.
        unsigned char   b_constrained_intra_pred;       // [Not Used] : constrained intra prediction.
        unsigned char   b_deblocking_override_enable;   // [Not Used] : deblocking override enable.
          signed char   i_cqp_offset;                   // [Not Used] : cqp offset: -12 to 12 (inclusive)
        unsigned char   b_deblocking_disable;           // [Not Used] : deblocking disable.
          signed char   i_tc_offset_div2;               // [Not Used] : tc_offset_div2: -6 to 6 (inclusive)
          signed char   i_beta_offset_div2;             // [Not Used] : beta_offset_div2: -6 to 6 (inclusive)
    } hev;
    struct {
        enum mhve_cfg_e i_type;
        int             i_sar_w, i_sar_h;
        int             b_video_full_range;             // Indicates the black level and range of the luma and chroma signals
        int             b_video_signal_pres;
        int             i_video_format;
        int             b_colour_desc_pres;
        int             b_timing_info_pres;
    } vui;
    struct {
        enum mhve_cfg_e i_type;
        signed char     b_override;                     // [Not Used]
        signed char     b_disable;                      // [Not Used]
        signed char     i_offsetA;                      // [Not Used]
        signed char     i_offsetB;                      // [Not Used]
    } lft;
    struct {
        enum mhve_cfg_e i_type;
        short           i_rows;                         // Multi-Slice MB Row Count
        short           i_bits;                         // Multi-Slice Bit Count
    } spl;
    struct {
        enum mhve_cfg_e i_type;
        int             b_init;                         // [Not Used]
    } bac;
};

struct mhve_ops {
    char   mhvename[16];
    void  (*release) (mhve_ops*);               //! Release this object.
    void*(*rqct_ops) (mhve_ops*);               //! Get rqct_ops handle.
    void*(*pmbr_ops) (mhve_ops*);               //! Get pmbr_ops handle.
    void*(*mhve_job) (mhve_ops*);               //! Get mhve_job object.
    int  (*seq_sync) (mhve_ops*);               //! Start sequence encoding.
    int  (*seq_conf) (mhve_ops*);               //! Configure sequence setting.
    int  (*seq_done) (mhve_ops*);               //! Finish sequence encoding.
    int  (*enc_buff) (mhve_ops*, mhve_vpb*);    //! Enqueue video buffer.
    int  (*deq_buff) (mhve_ops*, mhve_vpb*);    //! Dequeue video buffer.
    int  (*enc_conf) (mhve_ops*);               //! Configure current encode setting.
    int  (*put_data) (mhve_ops*, void*,int);    //! Put user data to output bit.
    int  (*enc_done) (mhve_ops*);               //! Finish encode frame.
    int  (*out_buff) (mhve_ops*, mhve_cpb*);    //! Output coded buffer.
    int  (*set_conf) (mhve_ops*, mhve_cfg*);    //! Apply configuration.
    int  (*get_conf) (mhve_ops*, mhve_cfg*);    //! Query configuration.
    int  (*set_syncPSfunc) (mhve_ops*, void*);  //! Set sync parameter set callback function.
    int  (*skip_buff) (mhve_ops*, mhve_vpb*);    //! Enqueue video buffer.
    int  (*skip_done) (mhve_ops*);               //! Finish skip frame.
};

#endif /*_MHVE_OPS_H_*/
