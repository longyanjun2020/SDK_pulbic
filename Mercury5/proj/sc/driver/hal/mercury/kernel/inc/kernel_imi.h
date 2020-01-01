#ifndef __KERNEL_IMI_H__
#define __KERNEL_IMI_H__

/************************************************/
/* RIU IMI Bank                                 */
/************************************************/

typedef struct KeImi_s
{
    /* [0x00] */
    u32 reg_imi_token                 :4 ; /// Current arbitration result
    u32 :28; /// [0x00]
    /* [0x00] */
    u32 reg_imi_update                :1 ; /// Update register to IMI
    u32 :3 ; /// [0x00]
    u32 reg_imi_hpr                   :4 ; /// High Priority Request
    u32 reg_imi_prm                   :4 ; /// Priority Request
    u32 reg_imi_hpr_mode              :1 ; /// High Priority Mode
    u32 :19; /// [0x00]
    /* [0x01] */
    u32 reg_imi_pr_table              :16; /// None
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_imi_hit_table             :16; /// None
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_imi_no_resp               :16; /// No response limit (4bit, 0 = Off)
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_imi_burst_size_0          :16; /// Burst size of each client (8bit, 0 = Off)
    u32 :16; /// [0x04]
    u32 reg_imi_burst_size_1          :16; /// @see reg_imi_burst_size_0
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_imi_soft_latency_0        :16; /// Soft latency cycle (8bit, 0 = Off)
    u32 :16; /// [0x06]
    u32 reg_imi_soft_latency_1        :16; /// @see reg_imi_soft_latency_0
    u32 :16; /// [0x07]
    /* [0x08] */
    u32 reg_imi_hard_latency_0        :16; /// Hard latency cycle (8bit, 0 = Off)
    u32 :16; /// [0x08]
    u32 reg_imi_hard_latency_1        :16; /// @see reg_imi_hard_latency_0
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_imi_ignore_last           :4 ; /// Ignore last signal from client
    u32 reg_imi_ignore_pr             :4 ; /// Ignore pr signal from client
    u32 reg_imi_mask_req              :4 ; /// Mask request from client
    u32 reg_imi_read_only             :4 ; /// Read only from client
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_imi_parking_client        :2 ; /// Force/Preferred parking client
    u32 :2 ; /// [0x0B]
    u32 reg_imi_force_parking         :1 ; /// Force SRAM to client enable
    u32 :3 ; /// [0x0B]
    u32 reg_imi_prefer_parking        :8 ; /// Prefered parking idle cycles (0 = Off)
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_imi_latency_clear         :1 ; /// Clear Latency counter
    u32 reg_imi_sram_cg_disable       :1 ; /// Disable CG_EN of SRAM
    u32 reg_imi_reset                 :1 ; /// Reset
    u32 reg_imi_sram_bist_fail        :1 ; /// SRAM_BIST_FAIL
    u32 reg_imi_spare                 :12; /// Spare
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_imi_latency_counter_0     :16; /// Latency counter of each client (8bit)
    u32 :16; /// [0x0D]
    u32 reg_imi_latency_counter_1     :16; /// @see reg_imi_latency_counter_0
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_imi_no_resp_rec           :8 ; /// No response record
    u32 :24; /// [0x0F]
    /* [0x0F] */
    u32 reg_imi_no_resp_clear         :1 ; /// Clear no response record
    u32 :7 ; /// [0x0F]
    u32 reg_imi_no_resp_id            :6 ; /// No response id
} KeImi_t;

#define IDX(idxs) (((1)?idxs)-((0)?idxs)+1)

#ifdef BIT
#undef BIT
#endif
#define BIT(_bit_)          (1 << (_bit_))
#define BITS(_bits_, _val_) ((BIT(((1)?_bits_)+1)-BIT(((0)?_bits_))) & (_val_<<((0)?_bits_)))
#define BITMASK(_bits_)     (BIT(((1)?_bits_)+1)-BIT(((0)?_bits_)))

typedef struct KeImiBw_s
{
    union
    {
        u32 val;

        #define IDX_IMI_BW_EN                           0x01:0x00
        #define IDX_IMI_BW_EN_RESERVED02                0x0F:0x02

        #define MASK_IMI_BW_EN                          BITMASK(IDX_IMI_BW_EN)
        #define MASK_IMI_BW_EN_RESERVED02               BITMASK(IDX_IMI_BW_EN_ESERVED02)

        #define BITS_IMI_BW_EN(x)                       BITS(IDX_IMI_BW_EN, (x))
        #define BITS_IMI_BW_EN_RESERVED02(x)            BITS(IDX_IMI_BW_EN_RESERVED02, (x))

        struct
        {
            u32 en          : IDX(IDX_IMI_BW_EN);
            u32 reserved02  : IDX(IDX_IMI_BW_EN_RESERVED02);
        } _;
    } imi_bw_en;                                        /* 0x00 */

    union
    {
        u32 val;

        #define IDX_IMI_BW_CLR                          0x00:0x00
        #define IDX_IMI_BW_CLR_RESERVED01               0x07:0x01
        #define IDX_IMI_BW_HIT                          0x0F:0x08

        #define MASK_IMI_BW_CLR                         BITMASK(IDX_IMI_BW_CLR)
        #define MASK_IMI_BW_CLR_RESERVED01              BITMASK(IDX_IMI_BW_CLR_ESERVED01)
        #define MASK_IMI_BW_HIT                         BITMASK(IDX_IMI_BW_HIT)

        #define BITS_IMI_BW_CLR(x)                      BITS(IDX_IMI_BW_CLR, (x))
        #define BITS_IMI_BW_CLR_RESERVED01(x)           BITS(IDX_IMI_BW_CLR_RESERVED01, (x))
        #define BITS_IMI_BW_HIT(x)                      BITS(IDX_IMI_BW_HIT, (x))

        struct
        {
            u32 clr         : IDX(IDX_IMI_BW_CLR);
            u32 reserved01  : IDX(IDX_IMI_BW_CLR_RESERVED01);
            u32 hit         : IDX(IDX_IMI_BW_HIT);
        } _;
    } imi_bw_clr_hit;                                   /* 0x01 */

    u32 imi_bw_hit_result_s[IDX(0x11:0x02)];            /* 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11 */
    u32 reserved12[IDX(0x17:0x12)];                     /* 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 */

    struct
    {
        u32 imi_bw_sa;                                  /* 0x18 */
        u32 reserved19[IDX(0x19:0x19)];                 /* 0x19 */
        u32 imi_bw_ea;                                  /* 0x1A */
        u32 reserved1B[IDX(0x1B:0x1B)];                 /* 0x1B */
        u32 imi_bw_pattern[IDX(0x1D:0x1C)];             /* 0x1C, 0x1D */

        union
        {
            u32 val;

            #define IDX_IMI_BW_RANGE                    0x02:0x00
            #define IDX_IMI_BW_RANGE_RESERVED03         0x0F:0x03

            #define MASK_IMI_BW_RANGE                   BITMASK(IDX_IMI_BW_RANGE)
            #define MASK_IMI_BW_RANGE_RESERVED03        BITMASK(IDX_IMI_BW_RANGE_RESERVED03)

            #define BITS_IMI_BW_RANGE(x)                BITS(IDX_IMI_BW_RANGE, (x))
            #define BITS_IMI_BW_RANGE_RESERVED03(x)     BITS(IDX_IMI_BW_RANGE_RESERVED03, (x))

            struct
            {
                u32 range       :  IDX(IDX_IMI_BW_RANGE);
                u32 reserved03  :  IDX(IDX_IMI_BW_RANGE_RESERVED03);
            } _;
        } imi_bw_range;                                 /* 0x1E */

        union
        {
            u32 val;

            #define IDX_IMI_BW_OFFSET                   0x08:0x00
            #define IDX_IMI_BW_OFFSET_RESERVED09        0x0F:0x09

            #define MASK_IMI_BW_OFFSET                  BITMASK(IDX_IMI_BW_OFFSET)
            #define MASK_IMI_BW_OFFSET_RESERVED09       BITMASK(IDX_IMI_BW_OFFSET_RESERVED09)

            #define BITS_IMI_BW_OFFSET(x)               BITS(IDX_IMI_BW_OFFSET, (x))
            #define BITS_IMI_BW_OFFSET_RESERVED09(x)    BITS(IDX_IMI_BW_OFFSET_RESERVED09, (x))

            struct
            {
                u32 offset      :  IDX(IDX_IMI_BW_OFFSET);
                u32 reserved09  :  IDX(IDX_IMI_BW_OFFSET_RESERVED09);
            } _;
        } imi_bw_offset;                                /* 0x1F */
    } cfg[2];

} KeImiBw_t;

extern volatile KeImi_t   * const g_ptKeImi;
extern volatile KeImiBw_t * const g_ptKeImiBw;

#endif /*__KERNEL_IMI_H__*/
