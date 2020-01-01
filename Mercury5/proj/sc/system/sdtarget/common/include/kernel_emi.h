/***************************************************************************
 *  kernel_emi.h
 *--------------------------------------------------------------------------
 *  Scope: External Memory Interface
 *
 *  Contents:  */
/****************************************************************************/
#ifndef __KERNEL_EMI_H__
#define __KERNEL_EMI_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "cpu_mem_map.h"


/*
 * \brief EMI Static Memory Controler Configuration
 */

typedef struct KeEmiSmc_s
{
    u32 status                  ; // 0x00, 16 bits, Memory Controller Status
    u32 cfg                     ; // 0x04, 2 bits, Reserved ([1]: Clock gating, [0]: Halt MIU Path) // <-@@@
    u32 direct_addr             ; // 0x08, 16 bits, Direct Command ([15:0] Direct address) // <-@@@
    u32 direct_addr_h           ; // 0x0C, Direct Command ([13:12] Chip select, [7:0] Direct address[16..23] ) // <-@@@
    u32 direct_wd               ; // 0x10, 16 bits, Write data for Direct Command
    u32 direct_wd_h             ; // 0x14, 16 bits, Write data for Direct Command High HWord // <-@@@
    u32 direct_cmd_issue        ; // 0x18, Issue Direct Command ([8]: reset, [1]: overflow, [0]: busy/issue) // <-@@@
    u32 direct_cmd_cfg          ; // 0x1C, Direct Command Configuration ([4]: 0 Asyn 1 Burst, [3]: Force mode, [2]: OPUpdate, [1]: CRE, [0]: R/W) // <-@@@
    u32 direct_rd               ; // 0x20, 32 bits, Read data of Last Direct Command // <-@@@
    u32 direct_rd_h             ; // 0x24 // <-@@@
    u32 reserved1[6]            ; // 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C // <-@@@
    u32 cycle0                  ; // 0x40, 16 bits, Set Cycles Register ([15:12] WEN cycle, [11:8] OEN after CEN, [7:4] CEN cycle (WRITE), [3:0] CEN cycle (READ))
    u32 cycle0_h		        ; // 0x44  Set Cycles Register ([23:20] Turn around cycle, [19:16] Page address cycle)
    u32 opmode0                 ; // 0x48, 4 bits,  Set Opmode Register ([2] Burst read, [1] Burst write, [0] Page mode) // <-@@@
    u32 admode0                 ; // 0x4C, 2 bits,  Set A/D Mux mode (#b00: x8, non-multiplexed mode, #b01: x16, non-multiplexed mode, #b10: x16, multiplexed mode, #b11: x32, multiplexed mode)
    u32 burst0                  ; // 0x50, 4 bits, [2:0] Burst ahead cycles // <-@@@
    u32 align0                  ; // 0x54, 16 bits, Set Address Align & Wait cycle ([15:12] Burst read wait cycle, [11:8] Burst write wait cycle, [7:4] Page address align,[3:0] Burst address align)
    u32 divide0                 ; // 0x58, Set clock divide ratio of SMC operation
    u32 stretch0                ; // 0x5C, [15:12] Stretch wait cycle, [11:0]: Max stretch data length
    u32 max0                    ; // 0x60, [9:0] Max cen cycles (0: disable)
    u32 reserved2[7]            ; // 0x64, 0x68, 0x6C, 0x70, 0x74, 0x78, 0x7C
    u32 cycle1                  ; // 0x80, 32 bits, Set Cycles Register
    u32 cycle1_h		        ; // 0x84
    u32 opmode1                 ; // 0x88, 4 bits,  Set Opmode Register
    u32 admode1                 ; // 0x8C, 2 bits,  Set A/D Mux mode
    u32 burst1                  ; // 0x90, 4 bits, [2:0] Burst ahead cycles // <-@@@
    u32 align1                  ; // 0x94, 16 bits, Set Address Align & Wait cycle
    u32 divide1                 ; // 0x98, Set clock divide ratio of SMC operation
    u32 stretch1                ; // 0x9C, [15:12] Stretch wait cycle, [11:0]: Max stretch data length
    u32 max1                    ; // 0xA0, [9:0] Set max cycles
    u32 reserved3[7]            ; // 0xA4, 0xA8, 0xAC, 0xB0, 0xB4, 0xB8, 0xBC
    u32 cycle2                  ; // 0xC0, 32 bits, Set Cycles Register
    u32 cycle2_h		        ; // 0xC4
    u32 opmode2                 ; // 0xC8, 4 bits,  Set Opmode Register
    u32 admode2                 ; // 0xCC, 2 bits,  Set A/D Mux mode
    u32 burst2                  ; // 0xD0, 4 bits, [2:0] Burst ahead cycles // <-@@@
    u32 align2                  ; // 0xD4, 16 bits, Set Address Align & Wait cycle
    u32 divide2                 ; // 0xD8, Set clock divide ratio of SMC operation
    u32 stretch2                ; // 0xDC, [15:12] Stretch wait cycle, [11:0]: Max stretch data length
    u32 reserved4[8]            ; // 0xE0, 0xE4, 0xE8, 0xEC, 0xF0, 0xF4, 0xF8, 0xFC
    u32 cycle3                  ; // 0x100, 16 bits, Set Cycles Register
    u32 cycle3_h		        ; // 0x104
    u32 opmode3                 ; // 0x108, 4 bits,  Set Opmode Register
    u32 admode3                 ; // 0x10C, 2 bits,  Set A/D Mux mode
    u32 burst3                  ; // 0x110, 4 bits, [2:0] Burst ahead cycles // <-@@@
    u32 align3                  ; // 0x114, 16 bits, Set Address Align & Wait cycle
    u32 divide3                 ; // 0x118, Set clock divide ratio of SMC operation
    u32 stretch3                ; // 0x11C, [15:12] Stretch wait cycle, [11:0]: Max stretch data length
} KeEmiSmc_t;

#define X8_BITS_NON_MULTIPLEXED     0x00 // x8, non-multiplexed mode,
#define X16_BITS_NON_MULTIPLEXED    0x01 // x16, non-multiplexed mode (reset value)
#define X16_BITS_MULTIPLEXED        0x02 // x16, multiplexed mode
#define X32_BITS_MULTIPLEXED        0x03 // x32, multiplexed mode

#define SMC_OP_MODE_POS				0
#define SMC_OP_MODE_MSK				((u32)0x0F<<SMC_OP_MODE_POS)

#define SMC_BURST_SIZE_POS                  8
#define SMC_BURST_SIZE_MSK                  ((u32)0x0F<<SMC_BURST_SIZE_POS)
#define SMC_BURST_WAIT_POLARITY_POS         6
#define SMC_BURST_WAIT_POLARITY_MSK         ((u32)0x01<<SMC_BURST_WAIT_POLARITY_POS)
#define SMC_BURST_VALID_EACH_2_CYCLE_POS    5
#define SMC_BURST_VALID_EACH_2_CYCLE_MSK    ((u32)0x01<<SMC_BURST_VALID_EACH_2_CYCLE_POS)
#define SMC_BURST_WRAP_ENABLE_POS           4
#define SMC_BURST_WRAP_ENABLE_MSK           ((u32)0x01<<SMC_BURST_WRAP_ENABLE_POS)
#define SMC_BURST_AHEAD_CYCLE_POS           0
#define SMC_BURST_AHEAD_CYCLE_MSK           ((u32)0x0F<<SMC_BURST_AHEAD_CYCLE_POS)

#define SMC_TYPE_NOR				0
#define SMC_TYPE_CELLULAR_RAM		1
#define SMC_TYPE_COSMORAM			2
#define SMC_TYPE_UTRAM				3
#define SMC_TYPE_SRAM				4

#define SMC_CYCLE_CEN_READ_POS		0
#define SMC_CYCLE_CEN_READ_MSK		((u32)0x0F<<SMC_CYCLE_CEN_READ_POS)
#define SMC_CYCLE_CEN_WRITE_POS		4
#define SMC_CYCLE_CEN_WRITE_MSK		((u32)0x0F<<SMC_CYCLE_CEN_WRITE_POS)
#define SMC_CYCLE_OEN_DELAY_POS		8
#define SMC_CYCLE_OEN_DELAY_MSK		((u32)0x0F<<SMC_CYCLE_OEN_DELAY_POS)
#define SMC_CYCLE_WEN_POS			12
#define SMC_CYCLE_WEN_MSK			((u32)0x0F<<SMC_CYCLE_WEN_POS)
#define SMC_CYCLE_PAG_ADDCYCLE_POS	0
#define SMC_CYCLE_PAG_ADDCYCLE_MSK	((u32)0x0F<<SMC_CYCLE_PAG_ADDCYCLE_POS)
#define SMC_CYCLE_TA_CYCLE_POS		4
#define SMC_CYCLE_TA_CYCLE_MSK		((u32)0x0F<<SMC_CYCLE_TA_CYCLE_POS)
#define SMC_CYCLE_WEN_DELAY_POS		8
#define SMC_CYCLE_WEN_DELAY_MSK		((u32)0x0F<<SMC_CYCLE_WEN_DELAY_POS)
#define SMC_CYCLE_OEN_END_POS		12
#define SMC_CYCLE_OEN_END_MSK		((u32)0x0F<<SMC_CYCLE_OEN_END_POS)

#define SMC_ALIGN_BURST_ADDSIZE_POS	0
#define SMC_ALIGN_BURST_ADDSIZE_MSK	((u32)0x0F<<SMC_ALIGN_BURST_ADDSIZE_POS)
#define SMC_ALIGN_PAG_ADDSIZE_POS	4
#define SMC_ALIGN_PAG_ADDSIZE_MSK	((u32)0x0F<<SMC_ALIGN_PAG_ADDSIZE_POS)
#define SMC_ALIGN_BURST_WR_WAIT_POS	8
#define SMC_ALIGN_BURST_WR_WAIT_MSK ((u32)0x0F<<SMC_ALIGN_BURST_WR_WAIT_POS)
#define SMC_ALIGN_BURST_RD_WAIT_POS	12
#define SMC_ALIGN_BURST_RD_WAIT_MSK	((u32)0x0F<<SMC_ALIGN_BURST_RD_WAIT_POS)

#define SMC_DCI_CMD_FORCEMODE_POS   3 // <-@@@, direct_cmd_cfg
#define SMC_DCI_CMD_FORCEMODE_MSK   ((u32)1<<SMC_DCI_CMD_FORCEMODE_POS)
#define SMC_DCI_CMD_OPUPDATE_POS    2 // <-@@@, direct_cmd_cfg
#define SMC_DCI_CMD_OPUPDATE_MSK    ((u32)1<<SMC_DCI_CMD_OPUPDATE_POS)
#define SMC_DCI_CMD_CRE_POS         1 // <-@@@, direct_cmd_cfg
#define SMC_DCI_CMD_CRE_MSK         ((u32)1<<SMC_DCI_CMD_CRE_POS)
#define SMC_DCI_CMD_WR_POS          0 // <-@@@, direct_cmd_cfg
#define SMC_DCI_CMD_WR_EN           ((u32)1<<SMC_DCI_CMD_WR_POS)

#define SMC_DCI_CMD_CS_POS          12 // 28 - 16 // <-@@@
#define SMC_DCI_CMD_CS_MSK          ((u32)3<<SMC_DCI_CMD_CS_POS)
#define SMC_DCI_CMD_CS_CS0          0
#define SMC_DCI_CMD_CS_CS1          1
#define SMC_DCI_CMD_CS_CS2          2
#define SMC_DCI_CMD_CS_CS3          3
#define SMC_DCI_CMD_RS_POS          2
#define SMC_DCI_CMD_RS_MSK          ((u32)3<<SMC_DCI_CMD_RS_POS)
#define SMC_DCI_CMD_ADD_POS         0
#define SMC_DCI_CMD_ADD_MSK         ((u32)0xFFFF<<SMC_DCI_CMD_ADD_POS)
#define SMC_DCI_CMD_ADD_H_POS       0
#define SMC_DCI_CMD_ADD_H_MSK       ((u32)0xFF<<SMC_DCI_CMD_ADD_H_POS)

#define SMC_DCI_CMD_OM_POS          15
#define SMC_DCI_CMD_OM_MSK          ((u32)1<<SMC_DCI_CMD_OM_POS)
#define SMC_DCI_CMD_IL_POS          14
#define SMC_DCI_CMD_IL_MSK          ((u32)1<<SMC_DCI_CMD_IL_POS)
#define SMC_DCI_CMD_LC_POS          11
#define SMC_DCI_CMD_LC_MSK          ((u32)7<<SMC_DCI_CMD_LC_POS)
#define SMC_DCI_CMD_WP_POS          10
#define SMC_DCI_CMD_WP_MSK          ((u32)1<<SMC_DCI_CMD_WP_POS)
#define SMC_DCI_CMD_WC_POS          8
#define SMC_DCI_CMD_WC_MSK          ((u32)3<<SMC_DCI_CMD_WC_POS)
#define SMC_DCI_CMD_DS_POS          4
#define SMC_DCI_CMD_DS_MSK          ((u32)0xF<<SMC_DCI_CMD_DS_POS)
#define SMC_DCI_CMD_BW_POS          3
#define SMC_DCI_CMD_BW_MSK          ((u32)1<<SMC_DCI_CMD_BW_POS)
#define SMC_DCI_CMD_BL_POS          0
#define SMC_DCI_CMD_BL_MSK          ((u32)3<<SMC_DCI_CMD_BL_POS)

#define SMC_DCI_WD_POS				0
#define SMC_DCI_WD_MSK				((u32)0xFFFF<<SMC_DCI_WD_POS)
#define SMC_DCI_RD_POS				0                                   // TODO: used by rd last -_-a // <-@@@
#define SMC_DCI_RD_MSK				((u32)0xFFFF<<SMC_DCI_RD_POS)       // TODO: used by rd_last -_-a // <-@@@
#define SMC_DCI_CMD_ISSUE			((u32)1<<0)


/*
 * \brief EMI Controler Configuration
 */
typedef struct EMI_RST_CFG
{
	u32 smc_rst : 1; 	/* 1 bit, Reset signal of SMC. High active      */
	u32 dmc_rst : 1; 	/* 1 bit, Reset signal of DMC. High active      */
	u32 arb_rst : 1; 	/* 1 bit, Reset signal of Arbiter. High active  */
	u32 emi_rst : 1;    /* 1 bit, Reset signal of EMI. High active      */ // <-@@@
	u32 reserved : 28; // <-@@@
} EmiRstCfg_t;



#define IDX(idxs) (((1)?idxs)-((0)?idxs)+1) // <-@@@

typedef struct KeEmi_s
{
    u32 emi_clk_gating;                     /* 0x00 */
    u32 smc_ob_n_dll;                       /* 0x01 */
    u32 smc_rx_p_dll;                       /* 0x02 */
    u32 smc_rx_n_dll;                       /* 0x03 */
    u32 reserved04[IDX(0x04:0x04)];         /* 0x04 */
    u32 boot;                               /* 0x05 */
    u32 reserved06[IDX(0x07:0x06)];         /* 0x06, 0x07 */
    u32 mpad_csn;                           /* 0x08 */
    u32 emi_spare;                          /* 0x09 */
    u32 reserved0A[IDX(0x0F:0x0A)];         /* 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F */
    u32 ahb2miu_type;                       /* 0x10 */
    u32 reserved11[IDX(0x13:0x11)];         /* 0x11, 0x12, 0x13 */
    u32 rst;                                /* 0x14 */
    u32 reserved15[IDX(0x1F:0x15)];         /* 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F */
    u32 rq0_qofs;                           /* 0x20 */
    u32 period_length;                      /* 0x21 */
    u32 rq0_bw_ls[IDX(0x23:0x22)];          /* 0x22, 0x23 */
    u32 reserved24[IDX(0x27:0x24)];         /* 0x24, 0x25, 0x26, 0x27 */
    u32 rq0_use_bw[IDX(0x29:0x28)];         /* 0x28, 0x29 */
    u32 reserved2A[IDX(0x2D:0x2A)];         /* 0x2A, 0x2B, 0x2C, 0x2D */
    u32 rq0_cnt[IDX(0x2F:0x2E)];            /* 0x2E, 0x2F */
    u32 reserved30[IDX(0x33:0x30)];         /* 0x30, 0x31, 0x32, 0x33 */
    u32 rq0_total_latency[IDX(0x37:0x34)];  /* 0x34, 0x35, 0x36, 0x37 */
    u32 reserved38[IDX(0x3F:0x38)];         /* 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F */
    u32 period_clear;                       /* 0x40 */
    u32 period_number;                      /* 0x41 */
} KeEmi_t;

#define EMI_CLK_GATING_EMI_POS  0
#define EMI_CLK_GATING_EMI_MSK  ((u32)0x01<<EMI_CLK_GATING_EMI_POS)
#define EMI_CLK_GATING_SMC_POS  1
#define EMI_CLK_GATING_SMC_MSK  ((u32)0x01<<EMI_CLK_GATING_SMC_POS)
#define EMI_CLK_GATING_DMC_POS  2
#define EMI_CLK_GATING_DMC_MSK  ((u32)0x01<<EMI_CLK_GATING_DMC_POS)

#define SMC_CLK_DLL_POS         0
#define SMC_CLK_DLL_MSK         ((u32)0x07<<SMC_CLK_DLL_POS)
#define SMC_CLK_DLL_INV_POS     4
#define SMC_CLK_DLL_INV_MSK     ((u32)0x01<<SMC_CLK_DLL_INV_POS)

#define EMI_BOOT_ADMUX_POS      0
#define EMI_BOOT_ADMUX_MSK      ((u32)0x01<<EMI_BOOT_ADMUX_POS)
#define EMI_BOOT_NUMO_POS       1
#define EMI_BOOT_NUMO_MSK       ((u32)0x01<<EMI_BOOT_NUMO_POS)
#define EMI_BOOT_SAMSUNG_POS    2
#define EMI_BOOT_SAMSUNG_MSK    ((u32)0x01<<EMI_BOOT_SAMSUNG_POS)
#define EMI_BOOT_NAND_107_POS   3
#define EMI_BOOT_NAND_107_MSK   ((u32)0x01<<EMI_BOOT_NAND_107_POS)
#define EMI_BOOT_NAND_149_POS   4
#define EMI_BOOT_NAND_149_MSK   ((u32)0x01<<EMI_BOOT_NAND_149_POS)

#define EMI_RST_SMC_POS         0
#define EMI_RST_SMC_MSK         ((u32)0x01<<EMI_RST_SMC_POS)
#define EMI_RST_DMC_POS         1
#define EMI_RST_DMC_MSK         ((u32)0x01<<EMI_RST_DMC_POS)
#define EMI_RST_ARB_POS         2
#define EMI_RST_ARB_MSK         ((u32)0x01<<EMI_RST_ARB_POS)
#define EMI_RST_EMI_POS         3
#define EMI_RST_EMI_MSK         ((u32)0x01<<EMI_RST_EMI_POS)

typedef struct KeEmiSc_s // <-@@@
{
    u32 mem_protect_ctrl;           /* 0x00 */
    u32 mem_protect_add_rule;       /* 0x01 */
    u32 mem_protect_hit;            /* 0x02 */
    u32 reserved03[IDX(0x03:0x03)]; /* 0x03 */

    struct
    {
        u32 id_0_1;
        u32 start;
        u32 start_h;
        u32 end;
        u32 end_h;
        u32 reserved;
    } mem_protect[8];               /* 0x04 ~ 0x33 */

    u32 mem_buswatch_en;            /* 0x34 */
    u32 mem_buswatch_hit;           /* 0x35 */
    u32 mem_buswatch_hit_ad;        /* 0x36 */
    u32 mem_buswatch_hit_ad_h;      /* 0x37 */
    u32 reserved38[IDX(0x3F:0x38)]; /* 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F */

    struct
    {
        u32 sa;
        u32 sa_h;
        u32 ea;
        u32 ea_h;
        u32 pattern;
        u32 pattern_h;
        u32 range;
        u32 offset;
    } mem_buswatch[8];              /* 0x40 ~ 0x7F */
} KeEmiSc_t; // <-@@@

#define MAX_MEM_PROTECT_ID  (sizeof(((KeEmiSc_t *)(0))->mem_protect)/sizeof (((KeEmiSc_t *)(0))->mem_protect[0]) - 1)
#define MAX_MEM_BUSWATCH_ID (sizeof(((KeEmiSc_t *)(0))->mem_buswatch)/sizeof(((KeEmiSc_t *)(0))->mem_buswatch[0]) - 1)

#define EMISC_MEM_PROTECT_CTRL_EN_POS   0
#define EMISC_MEM_PROTECT_CTRL_EN_MSK   ((u32)0x01<<EMISC_MEM_PROTECT_CTRL_EN_POS)
#define EMISC_MEM_PROTECT_CTRL_INV_POS  8
#define EMISC_MEM_PROTECT_CTRL_INV_MSK  ((u32)0x01<<EMISC_MEM_PROTECT_CTRL_INV_POS)

#define EMISC_MEM_PROTECT_HIT_CLR_POS   0
#define EMISC_MEM_PROTECT_HIT_CLR_MSK   ((u32)0x01<<EMISC_MEM_PROTECT_HIT_CLR_POS)
#define EMISC_MEM_PROTECT_HIT_HIT_POS   2
#define EMISC_MEM_PROTECT_HIT_HIT_MSK   ((u32)0x01<<EMISC_MEM_PROTECT_HIT_HIT_POS)
#define EMISC_MEM_PROTECT_HIT_NO_POS    4
#define EMISC_MEM_PROTECT_HIT_NO_MSK    ((u32)0x07<<EMISC_MEM_PROTECT_HIT_NO_POS)
#define EMISC_MEM_PROTECT_HIT_ID_POS    8
#define EMISC_MEM_PROTECT_HIT_ID_MSK    ((u32)0x3F<<EMISC_MEM_PROTECT_HIT_ID_POS)

#define EMI_CLK_SEL_POS		0
#define EMI_CLK_SEL_MSK		((u32)0x07<<EMI_CLK_SEL_POS)
#define SMC_CLK_SEL_POS		0
#define SMC_CLK_SEL_MSK		((u32)0x07<<SMC_CLK_SEL_POS)
#define EMI_CLK_26MHZ		0x00
#define EMI_CLK_39MHZ       0x06 // code refine
#define EMI_CLK_52MHZ		0x01
#define EMI_CLK_66MHZ       0x07
#define EMI_CLK_78MHZ		0x02
#define EMI_CLK_104MHZ		0x03
#define EMI_CLK_130MHZ		0x04
#define EMI_CLK_156MHZ      0x05 // code refine
#define EMI_CLK_MIU			0x05
#define EMI_SMC_CLK_APLL	0x05

typedef struct KeEmiDmc_s
{
	u32 dmc_ctrl;				/*0x00*/
	u32 dmc_cfg;				/*0x04*/
	u32 dmc_clk_cfg;			/*0x08*/
	u32 dmc_ref_cycle;			/*0x0C*/
	u32 dmc_cycle;				/*0x10*/
	u32 dmc_cycle1;				/*0x14*/
	u32 dmc_cycle2;				/*0x18*/
	u32 dmc_trfc_cycle;			/*0x1C*/
	u32 dmc_debug_ctrl;			/*0x20*/
	u32 dmc_debug_bus;			/*0x24*/
	u32 dmc_mrd_ext;			/*0x28*/
	u32 dmc_mrd_ext2;			/*0x2C*/
	u32 dmc_mrd_ext3;			/*0x30*/
	u32 unused;					/*0x34*/
	u32 dmc_internal_test_ctrl;	/*0x38*/
	u32 dmc_miu;				/*0x3C*/
	u32 dmc_ddr_cfg;			/*0x40*/
	u32 dmc_ddr_clk;			/*0x44*/
	u32 dmc_ddr_pll;			/*0x48*/
	u32 dmc_ddr_pll1;			/*0x4C*/
	u32 dmc_ddr_at;				/*0x50*/
	u32 dmc_ddr_pll2;			/*0x54*/
	u32 dmc_sdr_cke_ctrl;		/*0x58*/
	u32 dmc_auto_phase;			/*0x5C*/
	u32 dmc_clkph;				/*0x60*/
	u32 dmc_dqs;				/*0x64*/
	u32 dmc_cko_dqs;			/*0x68*/
	u32 dmc_dq_dqs_driving;		/*0x6C*/
	u32 dmc_ddr_pll_lock;		/*0x70*/
	u32 reserved2[3];			/* 0x74, 0x78, 0x7C*/
	u32 dmc_rq0_ctrl;			/*0x80*/
	u32 dmc_re0_grop;			/*0x84*/
	u32 dmc_rq0_timeout;		/*0x88*/
	u32 dmc_rq0_mask;			/*0x8C*/
	u32 dmc_rq0_hpmask;			/*0x90*/
	u32 dmc_rq0_priority;		/*0x94*/
	u32 dmc_rq0_priority1;		/*0x98*/
	u32 dmc_rq0_priority2;		/*0x9C*/
	u32 dmc_rq0_priority3;		/*0xA0*/
	u32 dmc_rq0_deadline;		/*0xA4*/
	u32 dmc_rq0_cnt0;			/*0xA8*/
	u32 dmc_rq0_cnt1;			/*0xAC*/
	u32 dmc_rq0_cnt2;			/*0xB0*/
	u32 reserved3[35];
	u32 dmc_clkpha_cfg;         /*0x140*/
	u32 reserved4[31];
	u32 dmc_miu_test;			/*0x1C0*/
	u32 dmc_test_base;			/*0x1C4*/
	u32 dmc_test_length_l;		/*0x1C8*/
	u32 dmc_test_length_h;		/*0x1CC*/
	u32 dmc_test_data;			/*0x1D0*/
	u32 dmc_test_status;		/*0x1D4*/
	u32 reserved5[6];			/*0x1D8, 0x1DC, 0x1E0, 0x1E4, 0x1E8, 0x1EC*/
	u32 dmc_wdcrc_ctl;			/*0x1F0*/
	u32 dmc_ptn_mode;			/*0x1F4*/
	u32 dmc_ptn_data;			/*0x1F8*/
	u32 dmc_read_crc;			/*0x1FC*/
} KeEmiDmc_t;

/* dmc_test_... */
#define TESTBASE_CFG_VAL            0x0000
#define TESTLENL_CFG_VAL            0x0400
#define TESTLENH_CFG_VAL            0x0000
#define TESTDATA_CFG_VAL            0x5AA5

/* dmc_miu_test */
#define TESTCFG_EN_SET              (0x01 << 0)
#define TESTCFG_MODE_OFF            1
#define TESTCFG_MODE_VAL(_value_)   (((_value_) & 0x03) << TESTCFG_MODE_OFF)
#define TESTCFG_MODE_NUM            4
#define TESTCFG_FAIL_IND            (0x01 << 14)
#define TESTCFG_FIN_IND             (0x01 << 15)

/* dmc_clkpha_cfg */
#define CLKPHA_DQSM_RDTIMING_OFF    0x0
#define CLKPHA_DQSM_RDTIMING_MSK    (0x0F << CLKPHA_DQSM_RDTIMING_OFF)
#define CLKPHA_DQSM_RDTIMING_VAL(_value_)   \
                                    (((_value_) & 0x0F) << CLKPHA_DQSM_RDTIMING_OFF)
#define CLKPHA_DQSM_SKEW_OFF        4
#define CLKPHA_DQSM_SKEW_SET        (0x01 << CLKPHA_DQSM_SKEW_OFF)
#define CLKPHA_FIXSDR_CLKINV_SET    (0x01 << 5)
#define CLKPHA_FIXSDR_DLYSEL_NUM    2
#define CLKPHA_FIXSDR_CLKSEL_PLL    (0x00 << 8)
#define CLKPHA_FIXSDR_CLKSEL_FIX    (0x01 << 8)
#define CLKPHA_FIXSDR_DLYSEL_OFF    12
#define CLKPHA_FIXSDR_DLYSEL_VAL(_value_)   \
                                    (((_value_) & 0x07) << CLKPHA_FIXSDR_DLYSEL_OFF)
#define CLKPHA_FIXSDR_CFG           (CLKPHA_FIXSDR_CLKINV_SET | \
                                     CLKPHA_FIXSDR_CLKSEL_FIX | \
                                     CLKPHA_FIXSDR_DLYSEL_VAL(0x00))

/*
 * \brief EMI DMC Controler Configuration
 */
typedef struct DMC_CTRL
{
	u32 dmc_init_miu		: 1;
	u32 dmc_arbiter_off		: 1;
	u32 dmc_no_rq_ctrl_en	: 1;
	u32 unused				: 5;
	u32 dmc_single_step		: 1;
	u32 dmc_trig_precharg	: 1;
	u32 dmc_trig_refresh	: 1;
	u32 dmc_trig_lmr		: 1;
	u32 dmc_trig_lmr_ext	: 1;
	u32 dmc_trig_deep_pd	: 1;
	u32 unused1				: 1;
	u32 dmc_init_done		: 1;
	u32 unused2				: 16;
} DmcCtrl_t;

/*
 * \brief DMC 0x04
 */
typedef struct DMC_CFG
{
	u32 dmc_cke_on			: 1; //1:on, 0:off
	u32 dmc_self_refresh	: 1; //enter self refresh cycle
	u32 dmc_dyn_cke			: 1; //dynamic cke
	u32 dmc_dyn_ck_odt		: 1; //dynamic turn on/off output clock
	u32 dmc_dram_bus		: 2; //0:16bits, 1:32bits, 2:64bits
	u32 dmc_dram_type		: 2; //0:sdr, 1:ddr2, 2:ddr, 3:reserved
	u32 dmc_4ba				: 1; //0:2 bank, 1:4 bank
	u32 dmc_col				: 2; //00:8 column, 01:9 column, 10:10 column
	u32 dmc_8ba				: 1; //0: reference reg_4ba, 1: 8 bank
	u32 dmc_cke_oenz		: 1;
	u32 dmc_dq_oenz			: 1;
	u32 dmc_addr_oenz		: 1;
	u32 dmc_cs_z			: 1;
	u32 unused2				: 16;
} DmcCfg_t;

/*
 * \brief DMC 0x08
 */
typedef struct DMC_CLK_CFG
{
	u32 rd_in_phase 		: 1; //read data phase, 0 : normal, 1:inverse
	u32 sdr_din_bypass 		: 1; //sdr read data clk bypass mode enable
	u32 sdr_din_clk_sel		: 1; //sdr read data clk sel, 0: fb_clk, 1: pll_clk
	u32 odt					: 1; //turn on odt for ddr2
	u32 rd_timing			: 4; //read data cycle
	u32 cas_latency			: 3; //cas latency, sdr : 2/3, ddr : 2/6
	u32 reg_4x_mode			: 1; //turn on 4x data mode
	u32 ddr_bga				: 1; //ddr package type, 0: tsop, 1:bga
	u32 unused				: 19;
} DmcClkCfg_t;

/*DMC_MIU*/
#define EMI_DMC_RESET			(1<<0)

/*DMC_CKE*/
#define EMI_DMC_FORCE_CKE_IN	(1<<1)

#endif // __KERNEL_EMI_H__
