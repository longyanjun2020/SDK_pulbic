#ifndef __KERNEL_ADCDMA_H__
#define __KERNEL_ADCDMA_H__

/************************************************/
/* ADC DMA Register Bank                        */
/************************************************/
#if 0 // XXX: redefined (@ hal_adcdump.h)

typedef struct KeAdcDma_s
{
    /* [0x00] */
    u32 reg_dma_reset                 :1 ; /// dma engine_reset
    u32 :31; /// [0x00]
    /* [0x01] */
    u32 reg_dma_start                 :1 ; /// dma start
    u32 :4 ; /// [0x01]
    u32 reg_dma_fail                  :1 ; /// dma fail
    u32 :2 ; /// [0x01]
    u32 reg_dma_req_thr               :5 ; /// request threshold
    u32 :19; /// [0x01]
    /* [0x02] */
    u32 reg_dma_done                  :5 ; /// dma_done
    u32 :27; /// [0x02]
    u32 :32; /// [0x03]
    u32 :32; /// [0x04]
    u32 :32; /// [0x05]
    /* [0x06] */
    u32 reg_dma_wpriority             :1 ; /// dma wpriority
    u32 :3 ; /// [0x06]
    u32 reg_dma_test_mode             :1 ; /// dma test mode enable
    u32 reg_dma_source_sel            :1 ; /// 1:adc_in1&2  0:adc_in1
    u32 reg_dma_adc_iqswap            :1 ; /// adc_ini/adc_inq swap enable; 1:enable
    u32 :25; /// [0x06]
    /* [0x07] */
    u32 reg_dma_up_addr_0             :16; /// dma_upper_addr
    u32 :16; /// [0x07]
    u32 reg_dma_up_addr_1             :11; /// @see reg_dma_up_addr_0
    u32 :21; /// [0x08]
    /* [0x09] */
    u32 reg_dma_low_addr_0            :16; /// dma_lower_addr
    u32 :16; /// [0x09]
    u32 reg_dma_low_addr_1            :11; /// @see reg_dma_low_addr_0
    u32 :21; /// [0x0A]
    /* [0x0B] */
    u32 reg_dma_addr_limit_en         :1 ; /// Address protection enable
    u32 reg_dma_overflow_clr          :1 ; /// Address overflow flag clear
    u32 reg_dma_addr_overflow         :1 ; /// Address overflow flag
    u32 :29; /// [0x0B]
    /* [0x0C] */
    u32 reg_dma_debug_sel             :3 ; /// dma debug select
    u32 :29; /// [0x0C]
    /* [0x0D] */
    u32 reg_dma_debug_0               :16; /// dma debug port
    u32 :16; /// [0x0D]
    u32 reg_dma_debug_1               :8 ; /// @see reg_dma_debug_0
    u32 :24; /// [0x0E]
    /* [0x0F] */
    u32 reg_fifo_cgen                 :1 ; /// Fifo clock dynamic gating
    u32 :31; /// [0x0F]
    /* [0x10] */
    u32 reg_dma_size0_0               :16; /// dma size0
    u32 :16; /// [0x10]
    u32 reg_dma_size0_1               :8 ; /// @see reg_dma_size0_0
    u32 :24; /// [0x11]
    /* [0x12] */
    u32 reg_dma_size1_0               :16; /// dma size1
    u32 :16; /// [0x12]
    u32 reg_dma_size1_1               :8 ; /// @see reg_dma_size1_0
    u32 :24; /// [0x13]
    /* [0x14] */
    u32 reg_dma_size2_0               :16; /// dma size2
    u32 :16; /// [0x14]
    u32 reg_dma_size2_1               :8 ; /// @see reg_dma_size2_0
    u32 :24; /// [0x15]
    /* [0x16] */
    u32 reg_dma_size3_0               :16; /// dma size3
    u32 :16; /// [0x16]
    u32 reg_dma_size3_1               :8 ; /// @see reg_dma_size3_0
    u32 :24; /// [0x17]
    /* [0x18] */
    u32 reg_dma_size4_0               :16; /// dma size4
    u32 :16; /// [0x18]
    u32 reg_dma_size4_1               :8 ; /// @see reg_dma_size4_0
    u32 :24; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    /* [0x20] */
    u32 reg_dma_st_addr0_0            :16; /// dma_st_addr0
    u32 :16; /// [0x20]
    u32 reg_dma_st_addr0_1            :11; /// @see reg_dma_st_addr0_0
    u32 :21; /// [0x21]
    /* [0x22] */
    u32 reg_dma_st_addr1_0            :16; /// dma_st_addr1
    u32 :16; /// [0x22]
    u32 reg_dma_st_addr1_1            :11; /// @see reg_dma_st_addr1_0
    u32 :21; /// [0x23]
    /* [0x24] */
    u32 reg_dma_st_addr2_0            :16; /// dma_st_addr2
    u32 :16; /// [0x24]
    u32 reg_dma_st_addr2_1            :11; /// @see reg_dma_st_addr2_0
    u32 :21; /// [0x25]
    /* [0x26] */
    u32 reg_dma_st_addr3_0            :16; /// dma_st_addr3
    u32 :16; /// [0x26]
    u32 reg_dma_st_addr3_1            :11; /// @see reg_dma_st_addr3_0
    u32 :21; /// [0x27]
    /* [0x28] */
    u32 reg_dma_st_addr4_0            :16; /// dma_st_addr4
    u32 :16; /// [0x28]
    u32 reg_dma_st_addr4_1            :11; /// @see reg_dma_st_addr4_0
    u32 :21; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_buffer_num                :3 ; /// Buffer number
    u32 :29; /// [0x30]
    /* [0x31] */
    u32 reg_done_clr                  :5 ; /// Buffer done clear
    u32 :27; /// [0x31]
    /* [0x32] */
    u32 reg_dma_done_int              :5 ; /// Buffer done interrupt
    u32 :27; /// [0x32]
    /* [0x33] */
    u32 reg_write_buf_index           :3 ; /// Writer buffer index
} KeAdcDma_t;

extern volatile KeAdcDma_t * const g_ptKeAdcDma;

#else  // XXX: redefined (@ hal_adcdump.h)

#define MSDRV_ADCDUMP_ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define MSDRV_ADCDUMP_IDX(idxs) (((1)?idxs)-((0)?idxs)+1)

#define MSDRV_ADCDUMP_BIT(_bit_)          (1 << (_bit_))
#define MSDRV_ADCDUMP_BITS(_bits_, _val_) ((MSDRV_ADCDUMP_BIT(((1)?_bits_)+1)-MSDRV_ADCDUMP_BIT(((0)?_bits_))) & (_val_<<((0)?_bits_)))
#define MSDRV_ADCDUMP_BITMASK(_bits_)     (MSDRV_ADCDUMP_BIT(((1)?_bits_)+1)-MSDRV_ADCDUMP_BIT(((0)?_bits_)))

#define MSDRV_ADCDUMP_WRITE_REG_MASK(reg, val, mask) ((reg) = (((reg) & ~(mask)) | ((val) & (mask))))

typedef struct KeAdcDma_s
{
    union
    {
        u32 val;

        #define IDX_ADCDMA_RESET                0x00:0x00
        #define IDX_ADCDMA_RESET_RESERVED01     0x0F:0x01

        #define MASK_ADCDMA_RESET               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_RESET)
        #define MASK_ADCDMA_RESET_RESERVED01    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_RESET_RESERVED01)

        #define BITS_ADCDMA_RESET(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_RESET, (x))
        #define BITS_ADCDMA_RESET_RESERVED01(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_RESET_RESERVED01, (x))

        struct
        {
            u32 reset               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_RESET);
            u32 reset_reserved01    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_RESET_RESERVED01);
        } _;
    } adcdma_reset;                         /* 0x00 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_START                0x00:0x00
        #define IDX_ADCDMA_START_RESERVED01     0x04:0x01
        #define IDX_ADCDMA_FAIL                 0x05:0x05
        #define IDX_ADCDMA_START_RESERVED06     0x07:0x06
        #define IDX_ADCDMA_REQ_THR              0x0C:0x08
        #define IDX_ADCDMA_START_RESERVED0D     0x0F:0x0D

        #define MASK_ADCDMA_START               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_START)
        #define MASK_ADCDMA_START_RESERVED01    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_START_RESERVED01)
        #define MASK_ADCDMA_FAIL                MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_FAIL)
        #define MASK_ADCDMA_START_RESERVED06    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_START_RESERVED06)
        #define MASK_ADCDMA_REQ_THR             MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_REQ_THR)
        #define MASK_ADCDMA_START_RESERVED0D    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_START_RESERVED0D)

        #define BITS_ADCDMA_START(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_START, (x))
        #define BITS_ADCDMA_START_RESERVED01(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_START_RESERVED01, (x))
        #define BITS_ADCDMA_FAIL(x)             MSDRV_ADCDUMP_BITS(IDX_ADCDMA_FAIL, (x))
        #define BITS_ADCDMA_START_RESERVED06(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_START_RESERVED06, (x))
        #define BITS_ADCDMA_REQ_THR(x)          MSDRV_ADCDUMP_BITS(IDX_ADCDMA_REQ_THR, (x))
        #define BITS_ADCDMA_START_RESERVED0D(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_START_RESERVED0D, (x))

        struct
        {
            u32 start               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_START);
            u32 start_reserved01    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_START_RESERVED01);
            u32 fail                : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_FAIL);
            u32 start_reserved06    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_START_RESERVED06);
            u32 reg_thr             : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_REQ_THR);
            u32 start_reserved0D    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_START_RESERVED0D);
        } _;
    } adcdma_start;                         /* 0x01 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_DONE                 0x04:0x00
        #define IDX_ADCDMA_DONE_RESERVED05      0x0F:0x05

        #define MASK_ADCDMA_DONE                MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DONE)
        #define MASK_ADCDMA_DONE_RESERVED05     MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DONE_RESERVED05)

        #define BITS_ADCDMA_DONE(x)             MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DONE, (x))
        #define BITS_ADCDMA_DONE_RESERVED05(x)  MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DONE_RESERVED05, (x))

        struct
        {
            u32 done                : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DONE);
            u32 done_reserved05     : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DONE_RESERVED05);
        } _;
    } adcdma_done;                          /* 0x02 */

    u32 adcdma_reserved03[MSDRV_ADCDUMP_IDX(0x05:0x03)];  /* 0x03, 0x04, 0x05 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_WPRIORITY                0x00:0x00
        #define IDX_ADCDMA_WPRIORITY_RESERVED01     0x03:0x01
        #define IDX_ADCDMA_TEST_MODE                0x04:0x04
        #define IDX_ADCDMA_SOURCE_SEL               0x05:0x05
        #define IDX_ADCDMA_ADC_IQSWAP               0x06:0x06
        #define IDX_ADCDMA_WPRIORITY_RESERVED07     0x0F:0x07

        #define MASK_ADCDMA_WPRIORITY               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_WPRIORITY)
        #define MASK_ADCDMA_WPRIORITY_RESERVED01    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_WPRIORITY_RESERVED01)
        #define MASK_ADCDMA_TEST_MODE               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_TEST_MODE)
        #define MASK_ADCDMA_SOURCE_SEL              MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_SOURCE_SEL)
        #define MASK_ADCDMA_ADC_IQSWAP              MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_ADC_IQSWAP)
        #define MASK_ADCDMA_WPRIORITY_RESERVED07    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_WPRIORITY_RESERVED07)

        #define BITS_ADCDMA_WPRIORITY(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_WPRIORITY)
        #define BITS_ADCDMA_WPRIORITY_RESERVED01(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_WPRIORITY_RESERVED01)
        #define BITS_ADCDMA_TEST_MODE(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_TEST_MODE)
        #define BITS_ADCDMA_SOURCE_SEL(x)           MSDRV_ADCDUMP_BITS(IDX_ADCDMA_SOURCE_SEL)
        #define BITS_ADCDMA_ADC_IQSWAP(x)           MSDRV_ADCDUMP_BITS(IDX_ADCDMA_ADC_IQSWAP)
        #define BITS_ADCDMA_WPRIORITY_RESERVED07(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_WPRIORITY_RESERVED07)

        struct
        {
            u32 wpriority               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_WPRIORITY);
            u32 wpriority_reserved01    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_WPRIORITY_RESERVED01);
            u32 test_mode               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_TEST_MODE);
            u32 source_sel              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_SOURCE_SEL);
#define ADCDMA_SOURCE_SEL_I         0
#define ADCDMA_SOURCE_SEL_I_AND_Q   1
            u32 adc_iqswap              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_ADC_IQSWAP);
            u32 wpriority_reserved07    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_WPRIORITY_RESERVED07);
        } _;

    } adcdma_wpriority;                     /* 0x06 */

    u32 adcdma_up_addr_l;                   /* 0x07 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_UP_ADDR_H                0x0A:0x00
        #define IDX_ADCDMA_UP_ADDR_H_RESERVED0B     0x0F:0x0B

        #define MASK_ADCDMA_UP_ADDR_H               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_UP_ADDR_H)
        #define MASK_ADCDMA_UP_ADDR_H_RESERVED0B    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_UP_ADDR_H_RESERVED0B)

        #define BITS_ADCDMA_UP_ADDR_H(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_UP_ADDR_H, (x))
        #define BITS_ADCDMA_UP_ADDR_H_RESERVED0B(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_UP_ADDR_H_RESERVED0B, (x))

        struct
        {
            u32 up_addr_h               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_UP_ADDR_H);
            u32 up_addr_h_reserved0b    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_UP_ADDR_H_RESERVED0B);
        } _;
    } adcdma_up_addr_h;                     /* 0x08 */

    u32 adcdma_low_addr_l;                  /* 0x09 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_LOW_ADDR_H                   0x0A:0x00
        #define IDX_ADCDMA_LOW_ADDR_H_RESERVED0B        0x0F:0x0B

        #define MASK_ADCDMA_LOW_ADDR_H                  MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_LOW_ADDR_H)
        #define MASK_ADCDMA_LOW_ADDR_H_RESERVED0B       MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_LOW_ADDR_H_RESERVED0B)

        #define BITS_ADCDMA_LOW_ADDR_H(x)               MSDRV_ADCDUMP_BITS(IDX_ADCDMA_LOW_ADDR_H, (x))
        #define BITS_ADCDMA_LOW_ADDR_H_RESERVED0B(x)    MSDRV_ADCDUMP_BITS(IDX_ADCDMA_LOW_ADDR_H_RESERVED0B, (x))

        struct
        {
            u32 low_addr_h              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_LOW_ADDR_H);
            u32 low_addr_h_reserved0b   : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_LOW_ADDR_H_RESERVED0B);
        } _;
    } adcdma_low_addr_h;                    /* 0x0A */

    union
    {
        u32 val;

        #define IDX_ADCDMA_ADDR_LIMIT_EN            0x00:0x00
        #define IDX_ADCDMA_OVERFLOW_CLR             0x01:0x01
        #define IDX_ADCDMA_ADDR_OVERFLOW            0x02:0x02
        #define IDX_ADCDMA_ADDR_LIMIT_EN_RESERVED03 0x0F:0x03

        #define MASK_ADCDMA_ADDR_LIMIT_EN               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_ADDR_LIMIT_EN)
        #define MASK_ADCDMA_OVERFLOW_CLR                MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_OVERFLOW_CLR)
        #define MASK_ADCDMA_ADDR_OVERFLOW               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_ADDR_OVERFLOW)
        #define MASK_ADCDMA_ADDR_LIMIT_EN_RESERVED03    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_ADDR_LIMIT_EN_RESERVED03)

        #define BITS_ADCDMA_ADDR_LIMIT_EN(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_ADDR_LIMIT_EN, (x))
        #define BITS_ADCDMA_OVERFLOW_CLR(x)             MSDRV_ADCDUMP_BITS(IDX_ADCDMA_OVERFLOW_CLR, (x))
        #define BITS_ADCDMA_ADDR_OVERFLOW(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_ADDR_OVERFLOW, (x))
        #define BITS_ADCDMA_ADDR_LIMIT_EN_RESERVED03(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_ADDR_LIMIT_EN_RESERVED03, (x))

        struct
        {
            u32 addr_limit_en               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_ADDR_LIMIT_EN);
            u32 overflow_clr                : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_OVERFLOW_CLR);
            u32 addr_overflow               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_ADDR_OVERFLOW);
            u32 addr_limit_en_reserved03    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_ADDR_LIMIT_EN_RESERVED03);
        } _;
    } adcdma_addr_limit_en;                 /* 0x0B */

    union
    {
        u32 val;

        #define IDX_ADCDMA_DEBUG_SEL                0x02:0x00
        #define IDX_ADCDMA_DEBUG_SEL_RESERVED03     0x0F:0x03

        #define MASK_ADCDMA_DEBUG_SEL               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DEBUG_SEL)
        #define MASK_ADCDMA_DEBUG_SEL_RESERVED03    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DEBUG_SEL_RESERVED03)

        #define BITS_ADCDMA_DEBUG_SEL(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DEBUG_SEL, (x))
        #define BITS_ADCDMA_DEBUG_SEL_RESERVED03(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DEBUG_SEL_RESERVED03, (x))

        struct
        {
            u32 debug_sel               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DEBUG_SEL);
            u32 debug_sel_reserved03    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DEBUG_SEL_RESERVED03);
        } _;
    } adcdma_debug_sel;                     /* 0x0C */

    u32 adcdma_debug_l;                     /* 0x0D */

    union
    {
        u32 val;

        #define IDX_ADCDMA_DEBUG_H                   0x07:0x00
        #define IDX_ADCDMA_DEBUG_H_RESERVED08        0x0F:0x08

        #define MASK_ADCDMA_DEBUG_H                  MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DEBUG_H)
        #define MASK_ADCDMA_DEBUG_H_RESERVED08       MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DEBUG_H_RESERVED08)

        #define BITS_ADCDMA_DEBUG_H(x)               MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DEBUG_H, (x))
        #define BITS_ADCDMA_DEBUG_H_RESERVED08(x)    MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DEBUG_H_RESERVED08, (x))

        struct
        {
            u32 debug_h             : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DEBUG_H);
            u32 debug_h_reserved08  : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DEBUG_H_RESERVED08);
        } _;
    } adcdma_debug_h;                       /* 0x0E */

    union
    {
        u32 val;

        #define IDX_ADCDMA_FIFO_CGEN                 0x00:0x00
        #define IDX_ADCDMA_FIFO_CGEN_RESERVED01      0x0F:0x01

        #define MASK_ADCDMA_FIFO_CGEN                MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_FIFO_CGEN)
        #define MASK_ADCDMA_FIFO_CGEN_RESERVED01     MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_FIFO_CGEN_RESERVED01)

        #define BITS_ADCDMA_FIFO_CGEN(x)             MSDRV_ADCDUMP_BITS(IDX_ADCDMA_FIFO_CGEN, (x))
        #define BITS_ADCDMA_FIFO_CGEN_RESERVED01(x)  MSDRV_ADCDUMP_BITS(IDX_ADCDMA_FIFO_CGEN_RESERVED01, (x))

        struct
        {
            u32 fifo_cgen               : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_FIFO_CGEN);
            u32 fifo_cgen_reserved01    : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_FIFO_CGEN_RESERVED01);
        } _;
    } adcdma_fifo_cgen;                     /* 0x0F */

    struct
    {
        u32 adcdma_size_l;

        union
        {
            u32 val;

            #define IDX_ADCDMA_SIZE_H                   0x07:0x00
            #define IDX_ADCDMA_SIZE_H_RESERVED08        0x0F:0x08

            #define MASK_ADCDMA_SIZE_H                  MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_SIZE_H)
            #define MASK_ADCDMA_SIZE_H_RESERVED08       MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_SIZE_H_RESERVED08)

            #define BITS_ADCDMA_SIZE_H(x)               MSDRV_ADCDUMP_BITS(IDX_ADCDMA_SIZE_H, (x))
            #define BITS_ADCDMA_SIZE_H_RESERVED08(x)    MSDRV_ADCDUMP_BITS(IDX_ADCDMA_SIZE_H_RESERVED08, (x))

            struct
            {
                u32 size_h              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_SIZE_H);
                u32 size_h_reserved08   : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_SIZE_H_RESERVED08);
            } _;
        } adcdma_size_h;
    } adcdma_size[5];                       /* 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19 */

    u32 adcdma_reserved1A[MSDRV_ADCDUMP_IDX(0x1F:0x1A)];  /* 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F */

    struct
    {
        u32 adcdma_st_addr_l;

        union
        {
            u32 val;

            #define IDX_ADCDMA_ST_ADDR_H                0x0A:0x00
            #define IDX_ADCDMA_ST_ADDR_H_RESERVED0B     0x0F:0x0B

            #define MASK_ADCDMA_ST_ADDR_H               MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_ST_ADDR_H)
            #define MASK_ADCDMA_ST_ADDR_H_RESERVED0B    MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_ST_ADDR_H_RESERVED0B)

            #define BITS_ADCDMA_ST_ADDR_H(x)            MSDRV_ADCDUMP_BITS(IDX_ADCDMA_ST_ADDR_H, (x))
            #define BITS_ADCDMA_ST_ADDR_H_RESERVED0B(x) MSDRV_ADCDUMP_BITS(IDX_ADCDMA_ST_ADDR_H_RESERVED0B, (x))

            struct
            {
                u32 st_addr_h              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_ST_ADDR_H);
                u32 st_addr_h_reserved0b   : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_ST_ADDR_H_RESERVED0B);
            } _;
        } adcdma_st_addr_h;
    } adcdma_st_addr[5];                    /* 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29 */

    u32 adcdma_reserved2A[MSDRV_ADCDUMP_IDX(0x2F:0x2A)];  /* 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F */

    union
    {
        u32 val;

        #define IDX_ADCDMA_BUFFER_NUM                   0x02:0x00
        #define IDX_ADCDMA_BUFFER_NUM_RESERVED03        0x0F:0x03

        #define MASK_ADCDMA_BUFFER_NUM                  MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_BUFFER_NUM)
        #define MASK_ADCDMA_BUFFER_NUM_RESERVED03       MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_BUFFER_NUM_RESERVED03)

        #define BITS_ADCDMA_BUFFER_NUM(x)               MSDRV_ADCDUMP_BITS(IDX_ADCDMA_BUFFER_NUM, (x))
        #define BITS_ADCDMA_BUFFER_NUM_RESERVED03(x)    MSDRV_ADCDUMP_BITS(IDX_ADCDMA_BUFFER_NUM_RESERVED03, (x))

        struct
        {
            u32 buffer_num              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_BUFFER_NUM);
            u32 buffer_num_reserved03   : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_BUFFER_NUM_RESERVED03);
        } _;
    } adcdma_buffer_num;                    /* 0x30 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_DONE_CLR                   0x04:0x00
        #define IDX_ADCDMA_DONE_CLR_RESERVED05        0x0F:0x05

        #define MASK_ADCDMA_DONE_CLR                  MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DONE_CLR)
        #define MASK_ADCDMA_DONE_CLR_RESERVED05       MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DONE_CLR_RESERVED05)

        #define BITS_ADCDMA_DONE_CLR(x)               MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DONE_CLR, (x))
        #define BITS_ADCDMA_DONE_CLR_RESERVED05(x)    MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DONE_CLR_RESERVED05, (x))

        struct
        {
            u32 done_clr              : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DONE_CLR);
            u32 done_clr_reserved05   : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DONE_CLR_RESERVED05);
        } _;
    } adcdma_done_clr;                      /* 0x31 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_DMA_DONE_INT                 0x04:0x00
        #define IDX_ADCDMA_DMA_DONE_INT_RESERVED05      0x0F:0x05

        #define MASK_ADCDMA_DMA_DONE_INT                MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DMA_DONE_INT)
        #define MASK_ADCDMA_DMA_DONE_INT_RESERVED05     MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_DMA_DONE_INT_RESERVED05)

        #define BITS_ADCDMA_DMA_DONE_INT(x)             MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DMA_DONE_INT, (x))
        #define BITS_ADCDMA_DMA_DONE_INT_RESERVED05(x)  MSDRV_ADCDUMP_BITS(IDX_ADCDMA_DMA_DONE_INT_RESERVED05, (x))

        struct
        {
            u32 dma_done_int            : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DMA_DONE_INT);
            u32 dma_done_intreserved05  : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_DMA_DONE_INT_RESERVED05);
        } _;
    } adcdma_dma_done_int;                  /* 0x32 */

    union
    {
        u32 val;

        #define IDX_ADCDMA_WRITE_BUF_INDEX                  0x02:0x00
        #define IDX_ADCDMA_WRITE_BUF_INDEX_RESERVED03       0x0F:0x03

        #define MASK_ADCDMA_WRITE_BUF_INDEX                 MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_WRITE_BUF_INDEX)
        #define MASK_ADCDMA_WRITE_BUF_INDEX_RESERVED03      MSDRV_ADCDUMP_BITMASK(IDX_ADCDMA_WRITE_BUF_INDEX_RESERVED03)

        #define BITS_ADCDMA_WRITE_BUF_INDEX(x)              MSDRV_ADCDUMP_BITS(IDX_ADCDMA_WRITE_BUF_INDEX, (x))
        #define BITS_ADCDMA_WRITE_BUF_INDEX_RESERVED03(x)   MSDRV_ADCDUMP_BITS(IDX_ADCDMA_WRITE_BUF_INDEX_RESERVED03, (x))

        struct
        {
            u32 write_buf_index             : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_WRITE_BUF_INDEX);
            u32 write_buf_index_reserved03  : MSDRV_ADCDUMP_IDX(IDX_ADCDMA_WRITE_BUF_INDEX_RESERVED03);
        } _;
    } adcdma_write_buf_index;               /* 0x33 */

} KeAdcDma_t;

#if defined(__I_SW__)
extern volatile KeAdcDma_t * const g_ptKeAdcDma;
#endif

#endif // XXX: redefined (@ hal_adcdump.h)
#endif /*__KERNEL_ADCDMA_H__*/
