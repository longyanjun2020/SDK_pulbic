/***************************************************************************
 *  kernel_emi.h
 *--------------------------------------------------------------------------
 *  Scope: External Memory Interface
 *
 *  Contents:  */
/****************************************************************************/
#ifndef __KERNEL_EMI_H__
#define __KERNEL_EMI_H__

#include "cpu_mem_map.hc"

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
    u32 reserved0[2]            ; // 0x28, 0x2C // <-@@@
    u32 smc_dft_divide          ; // 0x30 // <-@@@
    u32 reserved1[3]            ; // 0x34, 0x38, 0x3C // <-@@@
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

#if 0   // TODO: burst // <-@@@
#define SMC_TYPE_POS				0
#define SMC_TYPE_MSK				((u32)0x0F<<SMC_TYPE_POS)
#else   // TODO: burst // <-@@@
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
#endif  // TODO: burst // <-@@@

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

#if 0 // <-@@@
typedef struct EMI_SMC_CFG
{
	u32 smc_clk_sel 	: 3;
	u32 reserved1   	: 1;
	u32 smcob_clk_dll 	: 3;
	u32 reserved2		: 1;
	u32 smcib_clk_dll	: 3;
	u32 reserved3		: 1;
	u32 smcib_pad_fb	: 1;
	u32 reserved4		: 19;
} EmiSmcCfg_t;
#endif // <-@@@

#if 0 // <-@@@
typedef struct EMI_DMC_CFG
{
	u32 dmc_clk_sel		: 3;
	u32 reserved1		: 1;
	u32 dmcob_clk_dll 	: 3;
	u32 reserved2		: 1;
	u32 dmcib_clk_dll	: 3;
	u32 reserved3		: 1;
	u32 dmcib_pad_fb	: 1;
	u32 reserved4		: 19;
} EmiDmcCfg_t;
#endif // <-@@@

#define IDX(idxs) (((1)?idxs)-((0)?idxs)+1) // <-@@@

typedef struct KeEmi_s
{
#if 1 // <-@@@
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
    u32 reserved11[IDX(0x13:0x11)];         /* 0x11, 0x12, 0x13*/
    u32 rst;                                /* 0x14 */
    u32 reserved18[IDX(0x1F:0x15)];         /* 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F */
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
#else // <-@@@
	u32 status; 		/* 0x00 3 bits,
						   000: Current Arbitration 0: SMC 1: DMC
						   001: SMC Busy
						   010: DMC Busy
						*/
	u32 cfg; 			/* 0x04, 2 bits, 00: Halt EMI	*/
	u32 int_sram;				/* 0x08, use internal sram */
	u32 unused;					/* 0x0C*/
	u32 mpif_bank_sel;			/* 0x10 */
	u32 spi_boot_smc_ad;		/* 0x14 */
	u32 reserved[2];			/* 0x18, 0x1C */
	u32 map_csn;				/* 0x20 */
	u32 emi_spare;				/* 0x24 */
	u32 reserved1[2];			/* 0x28, 0x2C */
	u32 emi_async_mask;			/* 0x30 */
	u32 reserved2[3];			/* 0x34, 0x38, 0x3C */
	u32 dmc_arb;				/* 0x40 */
	u32 dmc_arb_weight_l;		/* 0x44 */
	u32 dmc_arb_weight_h;		/* 0x48 */
	u32 dmc_arb_ignore_hold; 	/* 0x4C */
	u32 dmc_arb_suppress;		/* 0x50 */
	u32 reserved3[3];			/* 0x54, 0x58, 0x5C */
	u32 smc_arb_hold;			/* 0x60 */
	u32 smc_arb_weight_l;		/* 0x64 */
	u32 smc_arb_weight_h;		/* 0x68 */
	u32 smc_arb_ignore_hold;	/* 0x6C */
	u32 smc_arb_suppress;		/* 0x70 */
	u32 reserved4[3];			/* 0x74, 0x78, 0x7C */
	u32 emi_clk_sel;	/* 0x80 */
	u32 smc_cfg;		/* 0x84 */
	u32 dmc_cfg;  		/* 0x88 */
	u32 only_dmc_clk;			/* 0x8C */
	u32 emi_rst;				/* 0x90 */
	u32 reserved5[7];			/* 0x94, 0x98, 0x9C, 0xA0, 0xA4, 0xA8, 0xAC */
	u32 emi_mea_start_loop;		/* 0xB0 */
	u32 reserved6[3];			/* 0xB4, 0xB8, 0xBC */
	u32 emi_mea_done_reset;		/* 0xC0 */
	u32 emi_mea_use_rw_sel;		/* 0xC4 */
	u32 emi_mea_id_0;			/* 0xC8 */
	u32 emi_mea_id_1;			/* 0xCC */
	u32 emi_mea_id_2;			/* 0xD0 */
	u32 emi_mea_id_3;			/* 0xD4 */
	u32 emi_mea_mi_sel_l;		/* 0xD8 */
	u32 emi_mea_mi_sel_h;		/* 0xDC */
	u32 emi_mea_match_0;		/* 0xE0 */
	u32 emi_mea_match_1;		/* 0xE4 */
	u32 emi_mea_match_2;		/* 0xE8 */
	u32 emi_mea_match_3;		/* 0xEC */
	u32 reserved7[4];			/* 0xF0, 0xF4, 0xF8, 0xFC */
	u32 emi_mea_result_0;		/* 0x100 */
	u32 emi_mea_result_1;		/* 0x104 */
	u32 emi_mea_result_2;		/* 0x108 */
	u32 emi_mea_result_3;		/* 0x10C */
	u32 emi_mea_result_4;		/* 0x110 */
	u32 emi_mea_result_5;		/* 0x114 */
	u32 emi_mea_result_6;		/* 0x118 */
	u32 emi_mea_result_7;		/* 0x11C */
	u32 emi_mea_result_8;		/* 0x120 */
	u32 emi_mea_result_9;		/* 0x124 */
	u32 emi_mea_result_10;		/* 0x128 */
	u32 emi_mea_result_11;		/* 0x12C */
	u32 emi_mea_result_12;		/* 0x130 */
	u32 emi_mea_result_13;		/* 0x134 */
	u32 emi_mea_result_14;		/* 0x138 */
	u32 emi_mea_result_15;		/* 0x13C */
	u32 reserved8[12];			/* 0x140, 0x144, 0x148, 0x14C, 0x150, 0x154, 0x158, 0x15C
								   0x160, 0x164, 0x168, 0x16C */
	u32 mem_protect_ctrl;		/* 0x170 */
	u32 mem_protect_hit_smc;	/* 0x174 */
	u32 mem_protect_hit_dmc;	/* 0x178 */
	u32 unused1;				/* 0x17C */
	u32 mem_protect0_id_0_1;	/* 0x180 */
	u32 mem_protect0_id_2_3; 	/* 0x184 */
	u32 mem_protect0_start;		/* 0x188 */
	u32 mem_protect0_end;		/* 0x18C */
	u32 mem_protect1_id_0_1;	/* 0x190 */
	u32 mem_protect1_id_2_3;	/* 0x194 */
	u32 mem_protect1_start;		/* 0x198 */
	u32 mem_protect1_end;		/* 0x19C */
	u32 mem_protect2_id_0_1;	/* 0x1A0 */
	u32 mem_protect2_id_2_3;	/* 0x1A4 */
	u32 mem_protect2_start;		/* 0x1A8 */
	u32 mem_protect2_end;		/* 0x1AC */
	u32 mem_protect3_id_0_1;	/* 0x1B0 */
	u32 mem_protect3_id_2_3;	/* 0x1B4 */
	u32 mem_protect3_start;		/* 0x1B8 */
	u32 mem_protect3_end;		/* 0x1BC */
	u32 emi_test_cfg;			/* 0x1C0 */
	u32 emi_test_base;			/* 0x1C4 */
	u32 emi_test_length_l;		/* 0x1C8 */
	u32 emi_test_length_h;		/* 0x1CC */
	u32 emi_test_data;			/* 0x1D0 */
	u32 emi_test_status;		/* 0x1D4 */
	u32 emi_test_base_h;		/* 0x1D8 */
	u32 unused2;				/* 0x1DC */
	u32 smi_test_cfg;			/* 0x1E0 */
	u32 smi_test_base;			/* 0x1E4 */
	u32 smi_test_length_l;		/* 0x1E8 */
	u32 smi_test_length_h;		/* 0x1EC */
	u32 smi_test_data;			/* 0x1F0 */
	u32 smi_test_status;		/* 0x1F4 */
	u32 smi_test_base_h;		/* 0x1F8 */
	u32 trace_match_ctrl;		/* 0x1FC */
	u32 trace_c0;				/* 0x200 */
	u32 trace_ref0;				/* 0x204 */
	u32 trace_pa0_l;			/* 0x208 */
	u32 trace_pa0_h;			/* 0x20C */
	u32 trace_pe0_l;			/* 0x210 */
	u32 trace_pe0_h;			/* 0x214 */
	u32 trace_c1;				/* 0x218 */
	u32 trace_ref1;				/* 0x21C */
	u32 trace_pa1_l;			/* 0x220 */
	u32 trace_pa1_h;			/* 0x224 */
	u32 trace_pe1_l;			/* 0x228 */
	u32 trace_pe1_h;			/* 0x22C */
	u32 trace_c2;				/* 0x230 */
	u32 trace_ref2;				/* 0x234 */
	u32 trace_pa2_l;			/* 0x238 */
	u32 trace_pa2_h;			/* 0x23C */
	u32 trace_pe2_l;			/* 0x240 */
	u32 trace_pe2_h;			/* 0x244 */
	u32 trace_c3;				/* 0x248 */
	u32 trace_ref3;				/* 0x24C */
	u32 trace_pa3_l;			/* 0x250 */
	u32 trace_pa3_h;			/* 0x254 */
	u32 trace_pe3_l;			/* 0x258 */
	u32 trace_pe3_h;			/* 0x25C */
	u32 trace_c4;				/* 0x260 */
	u32 trace_ref4;				/* 0x264 */
	u32 trace_pa4_l;			/* 0x268 */
	u32 trace_pa4_h;			/* 0x26C */
	u32 trace_pe4_l;			/* 0x270 */
	u32 trace_pe4_h;			/* 0x274 */
	u32 trace_c5;				/* 0x278 */
	u32 trace_ref5;				/* 0x27C */
	u32 trace_pa5_l;			/* 0x280 */
	u32 trace_pa5_h;			/* 0x284 */
	u32 trace_pe5_l;			/* 0x288 */
	u32 trace_pe5_h;			/* 0x28C */
	u32 trace_c6;				/* 0x290 */
	u32 trace_ref6;				/* 0x294 */
	u32 trace_pa6_l;			/* 0x298 */
	u32 trace_pa6_h;			/* 0x29C */
	u32 trace_pe6_l;			/* 0x2A0 */
	u32 trace_pe6_h;			/* 0x2A4 */
	u32 trace_c7;				/* 0x2A8 */
	u32 trace_ref7;				/* 0x2AC */
	u32 trace_pa7_l;			/* 0x2B0 */
	u32 trace_pa7_h;			/* 0x2B4 */
	u32 trace_pe7_l;			/* 0x2B8 */
	u32 trace_pe7_h;			/* 0x2BC */
#endif // <-@@@
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

typedef struct KeEmiSc1_s
{
	/*00*/
	u32 :32 ;

	/*04*/
	u32 :32 ;

	/*08*/
	u32 :32 ;

	/*0C*/
	u32 :32 ;

	/*10*/
	u32 :32 ;

	/*14*/
	u32 :32 ;

	/*18*/
	u32 :32 ;

	/*1C*/
	u32 :32 ;

	/*20*/
	u32 reg_emi_mea_start : 2 ;
	u32 : 6 ;
	u32 reg_emi_mea_loop :2 ;
	u32 : 22 ;

	/*24*/
	u32 reg_emi_mea_done :2 ;
	u32 : 6 ;
	u32 reg_emi_mea_reset :2 ;
	u32 : 22 ;

	/*28*/
	u32 reg_emi_mea_use_rw :2 ;
	u32 : 6 ;
	u32 reg_emi_mea_rw_sel : 2 ;
	u32 : 22 ;

	/*2C*/
	u32 reg_emi_mea_be_id : 16 ;
	u32 : 16 ;

	/*30*/
	u32 :32 ;

	/*34*/
	u32 :32 ;

	/*38*/
	u32 :32 ;

	/*3C*/
	u32 reg_emi_mea_mi_sel : 8 ;
	u32 :24 ;

	/*40*/
	u32 :32 ;

	/*44*/
	u32 reg_emi_mea_cycsel : 8 ;
	u32 :24 ;

	/*48*/
	u32 :32 ;

	/*4c*/
	u32 reg_emi_mea_match :16 ;
	u32 :16 ;

	/*50*/
	u32 :32 ;

	/*54*/
	u32 :32 ;

	/*58*/
	u32 :32 ;

	/*5c-60-64-68*/
	u32 reg_emi_mea_result[4] ;

	/*6c*/
	u32 :32 ;

	/*70*/
	u32 :32 ;

	/*74*/
	u32 :32 ;

	/*78*/
	u32 :32 ;

	/*7c*/
	u32 :32 ;

	/*80*/
	u32 :32 ;

	/*84*/
	u32 :32 ;

	/*88*/
	u32 :32 ;

	/*8c*/
	u32 :32 ;

	/*90*/
	u32 :32 ;

	/*94*/
	u32 :32 ;

	/*98*/
	u32 :32 ;

	/*9c*/
	u32 reg_emi_mea_result_sel : 2 ;
	u32 :30 ;

	/*a0-a4*/
	u32 reg_emi_mea_latency[2] ;

	/*a8*/
	u32 :32 ;

	/*ac*/
	u32 :32 ;

	/*b0*/
	u32 :32 ;

	/*b4*/
	u32 :32 ;

	/*b8*/
	u32 :32 ;

	/*bc*/
	u32 :32 ;

	/*c0*/
	u32 :32 ;

	/*c4*/
	u32 reg_ps_wait : 1 ;
	u32 :31 ;

	/*c8*/
	u32 reg_tx_ctrl : 5 ;
	u32 reg_tx_ctrl_ovr : 1 ;
	u32 reg_pull_ovr : 1 ;
	u32 reg_emi_oen_pass:1 ;
	u32 reg_emi_out_pass : 1 ;
	u32 :23 ;

	/*cc*/
	u32 reg_apll_clk_en : 2 ;
	u32 : 20 ;

	/*d0*/
	u32 reg_emi_7_0_drv : 16 ;
	u32 : 16;

	/*d4*/
	u32 reg_emi_15_8_drv : 16 ;
	u32 :16 ;

	/*d8*/
	u32 reg_emi_23_16_drv : 16 ;
	u32 :16 ;

	/*dc*/
	u32 reg_emi_31_24_drv : 16 ;
	u32 : 16 ;

	/*e0*/
	u32 reg_emi_39_32_drv : 16 ;
	u32 :16 ;

	/*e4*/
	u32 reg_emi_47_40_drv : 16 ;
	u32 :16 ;

	/*e8*/
	u32 reg_emi_51_48_drv :8 ;
	u32 :24 ;

	/*ec*/
	u32 reg_emi_testin_en :11 ;
	u32 :21 ;

	/*f0*/
	u32 reg_misc_spare: 16 ;
	u32 :16 ;

} KeEmiSc1_t;

#define MAX_MIU_PROTECT_ENTRY   1
#define MAX_BUS_WATCH_ENTRY     (sizeof(((KeEmiSc_t *)(0))->mem_buswatch)/sizeof(((KeEmiSc_t *)(0))->mem_buswatch[0]))

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

#if 1 // <-@@@
#define EMI_CLK_SEL_POS		0
#define EMI_CLK_SEL_MSK		((u32)0x07<<EMI_CLK_SEL_POS)
#define SMC_CLK_SEL_POS		0
#define SMC_CLK_SEL_MSK		((u32)0x07<<SMC_CLK_SEL_POS)
#if 0
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
#else
typedef enum {
	EMI_CLK_26MHZ 		= 0x00,
	EMI_CLK_39MHZ		= 0x06,// code refine
	EMI_CLK_52MHZ		= 0x01,
	EMI_CLK_66MHZ		= 0x07,
	EMI_CLK_78MHZ		= 0x02,
	EMI_CLK_104MHZ		= 0x03,
	EMI_CLK_130MHZ		= 0x04,
	EMI_CLK_156MHZ		= 0x05, // code refine
	EMI_CLK_133MHZ		= 0x08,
	EMI_CLK_166MHZ		= 0x09,
	EMI_CLK_200MHZ		= 0x0A,
	EMI_CLK_DONTCARE	= 0xFFFF,
} EMI_CLK_ENUM;
#endif

#endif // <-@@@

#define EMI_DRVING_HIGHEST  0xFFFF
#define EMI_DRVING_HIGH     0xCCCC
#define EMI_DRVING_MIDDLE   0x3333
#define EMI_DRVING_LOW      0x0

#if 0 // <-@@@
/*trace match*/
#define EMI_TRACE_MATCH_POS		8
#define EMI_TRACE_MATCH_MSK		(0xFF << EMI_TRACE_MATCH_POS)
#define EMI_TRACE_CTRL_EN		1
#define EMI_TRACE_INT_CLEAR		(0x1<<1)
#endif // <-@@@

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
	u32 reserved3[67];
	u32 dmc_miu_test;			/*0x1C0*/
	u32 dmc_test_base;			/*0x1C4*/
	u32 dmc_test_length_l;		/*0x1C8*/
	u32 dmc_test_length_h;		/*0x1CC*/
	u32 dmc_test_data;			/*0x1D0*/
	u32 dmc_test_status;		/*0x1D4*/
	u32 reserved4[6];			/*0x1D8, 0x1DC, 0x1E0, 0x1E4, 0x1E8, 0x1EC*/
	u32 dmc_wdcrc_ctl;			/*0x1F0*/
	u32 dmc_ptn_mode;			/*0x1F4*/
	u32 dmc_ptn_data;			/*0x1F8*/
	u32 dmc_read_crc;			/*0x1FC*/
} KeEmiDmc_t;

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

extern volatile KeEmiSmc_t* const g_ptKeEmiSmc;
extern volatile KeEmi_t* const g_ptKeEmi;
extern volatile KeEmiDmc_t* const g_ptKeEmiDmc;
extern volatile KeEmiSc_t* const g_ptKeEmiSc;
extern volatile KeEmiSc1_t* const g_ptKeEmiSc1;


#endif // __KERNEL_EMI_H__

