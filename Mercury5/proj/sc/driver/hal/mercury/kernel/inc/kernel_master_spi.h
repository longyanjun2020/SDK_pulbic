/***************************************************************************
 *  kernel_master_spi.h
 *--------------------------------------------------------------------------
 *  Scope: Master SPI related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_MASTER_SPI_H__
#define __KERNEL_MASTER_SPI_H__

#include "stdcomp.h"
#include "cpu_mem_map.hc"

/****************************************************************************/
/*        Master SPI registers                           */
/****************************************************************************/

typedef struct KeMasterSpi_s
{
#if 0
    //0x0~0x3[rw] Write buffer
    u8 reg_mspi_wd[16];
    //0x4~0x7[r] Read buffer
    u8 reg_mspi_rd[16];
#else
    //0x0[rw] Write Buffer0
    u32 reg_mspi_wd0            :8;
    u32 reg_mspi_wd1            :8;
    u32                         :16;
    //0x1[rw] Write Buffer1
    u32 reg_mspi_wd2            :8;
    u32 reg_mspi_wd3            :8;
    u32                         :16;
    //0x2[rw] Write Buffer2
    u32 reg_mspi_wd4            :8;
    u32 reg_mspi_wd5            :8;
    u32                         :16;
    //0x3[rw] Write Buffer3
    u32 reg_mspi_wd6            :8;
    u32 reg_mspi_wd7            :8;
    u32                         :16;
    //0x4[r] Read Buffer0
    u32 reg_mspi_rd0            :8;
    u32 reg_mspi_rd1            :8;
    u32                         :16;
    //0x5[r] Read Buffer1
    u32 reg_mspi_rd2            :8;
    u32 reg_mspi_rd3            :8;
    u32                         :16;
    //0x6[r] Read Buffer2
    u32 reg_mspi_rd4            :8;
    u32 reg_mspi_rd5            :8;
    u32                         :16;
    //0x7[r] Read Buffer3
    u32 reg_mspi_rd6            :8;
    u32 reg_mspi_rd7            :8;
    u32                         :16;
#endif
    //0x8[rw] How many bytes will be transferred and received
    u32 reg_mspi_wbf_size       :8;     //0~8 bytes
    u32 reg_mspi_rbf_size       :8;     //0~8 bytes
    u32                         :16;
    //0x9[rw] Control and clock rate register
    u32 reg_mspi_ctrl_enable    :1;     //0:Disable 1:Enable
    u32 reg_mspi_ctrl_reset     :1;     //0:Disable 1:Enable
    u32 reg_mspi_ctrl_interrupt :1;     //0:Disable 1:Enable
    u32                         :1;
    u32 reg_mspi_ctrl_threewire :1;     //0:Disable 1:Enable
    u32                         :1;
    u32 reg_mspi_ctrl_cpha      :1;
    u32 reg_mspi_ctrl_cpol      :1;
    u32 reg_mspi_clock_rate     :3;
    u32                         :21;
    //0xa[rw] The time from trigger to first clock and the time from last clock to done flag
    u32 reg_mspi_tr_start_time  :8;
    u32 reg_mspi_tr_end_time    :8;
    u32                         :16;
    //0xb[rw] The time between byte to byte and the time between last write and first read
    u32 reg_mspi_byte_interval  :8;
    u32 reg_mspi_turn_around    :8;
    u32                         :16;
    //0xc[rw] Bit len selection for write buffer0~3
    u32 reg_mspi_wd0_bit_sel    :3;
    u32 reg_mspi_wd1_bit_sel    :3;
    u32 reg_mspi_wd2_bit_sel    :3;
    u32 reg_mspi_wd3_bit_sel    :3;
    u32                         :20;
    //0xd[rw] Bit len selection for write buffer4~7
    u32 reg_mspi_wd4_bit_sel    :3;
    u32 reg_mspi_wd5_bit_sel    :3;
    u32 reg_mspi_wd6_bit_sel    :3;
    u32 reg_mspi_wd7_bit_sel    :3;
    u32                         :20;
    //0xe[rw] Bit len selection for read buffer0~3
    u32 reg_mspi_rd0_bit_sel    :3;
    u32 reg_mspi_rd1_bit_sel    :3;
    u32 reg_mspi_rd2_bit_sel    :3;
    u32 reg_mspi_rd3_bit_sel    :3;
    u32                         :20;
    //0xf[rw] Bit len selection for read buffer4~7
    u32 reg_mspi_rd4_bit_sel    :3;
    u32 reg_mspi_rd5_bit_sel    :3;
    u32 reg_mspi_rd6_bit_sel    :3;
    u32 reg_mspi_rd7_bit_sel    :3;
    u32                         :20;
    //0x10 dummy
    u32 :32;
    //0x11 dummy
    u32 :32;
    //0x12 dummy
    u32 :32;
    //0x13 dummy
    u32 :32;
    //0x14 dummy
    u32 :32;
    //0x15 dummy
    u32 :32;
    //0x16 dummy
    u32 :32;
    //0x17 dummy
    u32 :32;
    //0x18 dummy
    u32 :32;
    //0x19 dummy
    u32 :32;
    //0x1a[w] Start data transfer
    u32 reg_mspi_trigger        :1;
    u32                         :31;
    //0x1b[r] Busy status
    u32 reg_mspi_done_flag      :1;     //0:Busy 1:Done
    u32                         :31;
    //0x1c[w] Clear done flag
    u32 reg_mspi_clear          :1;
    u32                         :31;
    //0x1d dummy
    u32 :32;
    //0x1e dummy
    u32 :32;
    //0x1f[rw] Chip select
    u32 reg_mspi_chip_select1   :1;     //0:Enable 1:Disable
    u32 reg_mspi_chip_select2   :1;     //0:Enable 1:Disable
    u32 reg_mspi_chip_select3   :1;     //0:Enable 1:Disable
    u32 reg_mspi_chip_select4   :1;     //0:Enable 1:Disable
    u32 reg_auto_clr_done_flag1 :1;     //1:Enable 0:Disable
    u32 reg_auto_clr_done_flag2 :1;     //1:Enable 0:Disable
    u32 reg_mspi_gdma_mode      :1;     //0:riu mode 1:gdma mode[default]
    u32 reg_mspi_diff_clock     :1;
    u32                         :24;
    //0x20[rw]
    u32 reg_mspi_ctrler_cmd00   :8;
    u32 reg_mspi_ctrler_cmd01   :8;
    u32                         :16;
    //0x21[rw]
    u32 reg_mspi_ctrler_cmd02   :8;
    u32 reg_mspi_ctrler_cmd03   :8;
    u32                         :16;
    //0x22[rw]
    u32 reg_mspi_ctrler_cmd04   :8;
    u32 reg_mspi_ctrler_cmd05   :8;
    u32                         :16;
    //0x23[rw]
    u32 reg_mspi_ctrler_cmd10   :8;
    u32 reg_mspi_ctrler_cmd2    :8;
    u32                         :16;
    //0x24[rw]
    u32 reg_mspi_ctrler_cmd2_end_sts        :8;
    u32 reg_mspi_ctrler_cmd2_end_sts_msk    :8;
    u32                                     :16;
    //0x25[rw]
    u32 reg_mspi_ctrler_cmd_len0            :8;
    u32 reg_mspi_ctrler_cmd_len1            :8;
    u32                                     :16;
    //0x26[rw]
    u32 reg_mspi_ctrler_cmd_len2            :8;
    u32 reg_reserved_1                      :8;
    u32                                     :16;
    //0x27[rw]
    u32 reg_mspi_ctrler_cmd_addr_add0       :8;
    //u32 reg_mspi_ctrler_cmd_addr_add1       :8;    
    //u32                                     :16;
    u32                                     :24;
    //0x28[rw]
    u32 reg_mspi_ctrler_cfg0                :8;
    u32 reg_mspi_ctrler_cfg1                :8;
    u32                                     :16;
    //0x29[rw]
    //u32 reg_mspi_cs_time_cnt_len0           :16;
    u32 reg_mspi_cs_time_cnt_len0           :8;
    //u32 reg_mspi_cs_time_cnt_len01          :8;
    //u32                                     :16;
    u32                                     :24;
    //0x2a[rw]
    u32 :32;
    //0x2b[rw]
    u32 :32;
    //0x2c[rw]
    u32 :32;
    //0x2d[rw]
    u32 :32;
    //0x2e[rw]
    u32 :32;
    //0x2f[rw]
    u32 :32;
    //0x30[rw]
    //u32 reg_mspi_cs_time_cnt_len1           :16;
    u32 reg_mspi_cs_time_cnt_len1           :8;
    //u32 reg_mspi_cs_time_cnt_len11          :8;
    //u32                                     :16;
    u32                                     :24;
    //0x31[rw]
    //u32 reg_mspi_cs_time_cnt_len2           :16;
    u32 reg_mspi_cs_time_cnt_len2           :8;
    //u32 reg_mspi_cs_time_cnt_len21          :8;
    //u32                                     :16;
    u32                                     :24;
    //0x32[rw]
    u32 reg_mspi_ctrler_err_sts             :8;
    u32 reg_mspi_ctrler_err_sts_msk         :8;
    u32                                     :16;
    //0x33[rw]
    u32 reg_mspi_dummy0                     :8;
    //u32 reg_mspi_dummy1                     :8;
    //u32                                     :16;
    u32                                     :24;
#if 1
    //0x34[r]
    u32 reg_mspi_dbg0                       :8;
    u32 reg_mspi_dbg1                       :8;
    u32                                     :16;
#else
    //0x34[rw]
    u32 reg_mspi_dummy2                     :8;
    u32 reg_mspi_dummy3                     :8;
    u32                                     :16;
    //0x35[rw]
    u32 reg_mspi_dummy4                     :8;
    u32 reg_mspi_dummy5                     :8;
    u32                                     :16;
    //0x36[r]
    u32 reg_mspi_dbg0                       :8;
    u32 reg_mspi_dbg1                       :8;
    u32                                     :16;
    //0x37[r]
    u32 reg_mspi_dbg2                       :8;
    u32 reg_mspi_dbg3                       :8;
    u32                                     :16;
    //0x38[r]
    u32 reg_mspi_dbg4                       :8;
    u32 reg_mspi_dbg5                       :8;
    u32                                     :16;
#endif
} KeMasterSpi_t;

extern volatile KeMasterSpi_t* const g_ptKeMasterSpi;

#endif // __KERNEL_MASTER_SPI_H__

