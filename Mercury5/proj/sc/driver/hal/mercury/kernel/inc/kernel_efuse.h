/***************************************************************************
 *  kernel_efuse.h
 *--------------------------------------------------------------------------
 *  Scope: eFuse related definitions
 *
 ****************************************************************************/
#ifndef __KERNEL_EFUSE_H__
#define __KERNEL_EFUSE_H__

#include "cpu_mem_map.hc"

/****************************************************************************/
/*        eFuse  registers                           */
/****************************************************************************/

/*efuse word size including padding.*/
#define EFUSE_SIZE_WORD_DATA    8

typedef struct EfuseReg_s
{
    /* [0x00] */
    u32         reg_efuse_mux_bit[EFUSE_SIZE_WORD_DATA];            // riu 0x00~0x07 (half-word address)
    /* [0x08] */
		u32         reg_efuse_overwrite_sel[EFUSE_SIZE_WORD_DATA];      // riu 0x08~0x0f
    /* [0x10] */
    u32         reg_efuse_overwrite_value[EFUSE_SIZE_WORD_DATA];    // riu 0x10~0x17
    /* [0x18] */
    u32         reg_efuse_raw_bit[EFUSE_SIZE_WORD_DATA];            // riu 0x18~0x1f
    /* [0x20] */
    u32 reg_prog_fu_en                :1 ; /// Efuse program enable bit
    u32 :31; /// [0x20]
    /* [0x21] */
    u32 reg_prog_fu_cnt               :9 ; /// program cycle count by 26Mz ( 10us )
                                           /// 260 * 1/26M ~= 10us
    u32 :23; /// [0x21]
    /* [0x22] */
    u32 reg_gadrr                     :6 ; /// efuse_bit_sel_address
    u32 :2 ; /// [0x22]
    u32 reg_gbank_sel                 :2 ; /// efuse_bank_sel_address; 
                                           /// [0] : enable //big5 48bit
                                           /// [1] : reserved
    u32 :22; /// [0x22]
    /* [0x23] */
    u32 reg_gmonsel                   :1 ; /// Efuse gmonsel input signal
                                           /// must be low when GPROG is high
    u32 reg_gmongate                  :1 ; /// Efuse gmgate input signal
                                           /// must be low when GPROG is high
    u32 :30; /// [0x23]
    /* [0x24] */
    u32 reg_reserved_0                :16; /// Efuse reserved register
    u32 :16; /// [0x24]
    u32 reg_reserved_1                :16; /// @see reg_reserved_0
    u32 :16; /// [0x25]
    /* [0x26] */
    u32 reg_gsigdev_p                 :1 ; /// read only flag ; efuse GSIGDEV_P
    u32 reg_gfset_p                   :1 ; /// read only flag ; efuse GFSET_P
    u32 reg_gprchg_n                  :1 ; /// read only flag ; efuse GPRCHG_N
    u32 reg_gbank_p                   :2 ; /// efuse_bank_sel_address; 2'b01 bank0, 2'b10 bank1
    u32 reg_gprog                     :1 ; /// read only flag ; efuse GPROG
    u32 reg_mux_gadrr                 :6 ; /// efuse_bit_sel_address
    u32 reg_mux_gmonsel               :1 ; /// Efuse gmonsel input signal
                                           /// must be low when GPROG is high
    u32 reg_mux_gmongate              :1 ; /// Efuse gmgate input signal
                                           /// must be low when GPROG is high
    u32 :18; /// [0x26]
    /* [0x27] */
    u32 reg_efuse_state               :16; /// Efuse read  FSM state
    u32 :16; /// [0x27]
    /* [0x28] */
    u32 reg_efuse_read                :1 ; /// Efuse read trigger
    u32 :31; /// [0x28]
    /* [0x29] */
    u32 reg_ctrl_from_pad             :1 ; /// efuse control from pad (GPIO)
                                           /// 0: read/write from fsm
                                           /// 1: read/write from pad
    u32 :31; /// [0x29]
    /* [0x2A] */
    u32 reg_efuse_clk_en              :1 ; /// efuse 32k enable
                                           /// 0: diable
                                           /// 1: enable
} EfuseReg_t;

extern volatile EfuseReg_t * const g_ptEfuseReg;  /*declared in kernel.c*/



#endif //__KERNEL_EFUSE_H__

