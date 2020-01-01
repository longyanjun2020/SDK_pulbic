/***************************************************************************
 *  kernel_qspi.h
 *--------------------------------------------------------------------------
 *  Scope: QSPI related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_QSPI_H__
#define __KERNEL_QSPI_H__

#include "cpu_mem_map.hc"

/****************************************************************************/
/*        QSPI registers                                                     */
/****************************************************************************/

typedef struct KeQspi_s
{
    //0x40[rw]
    u32 reg_delay_tree_sel          :3;  // The value of the delay tree
    u32                             :29;
    //0x41[rw]
    u32                             :32;
    //0x42[rw]
    u32                             :32;
    //0x43[rw]
    u32                             :32;
    //0x44[rw]
    u32                             :32;
    //0x45[rw]
    u32                             :32;
    //0x46[rw]
    u32                             :32;
    //0x47[rw]
    u32                             :32;
    //0x48[rw]
    u32                             :32;
    //0x49[rw]
    u32                             :32;
    //0x4a[rw]
    u32                             :32;
    //0x4b[rw]
    u32                             :32;
    //0x4c[rw]
    u32                             :32;
    //0x4d[rw]
    u32                             :32;
    //0x4e[rw]
    u32                             :32;
    //0x4f[rw]
    u32                             :32;

    //0x50[rw]
    u32 reg_cmd_111_m0              :8;  // The user defined command for 1-1-1 normal read mode
    u32 reg_cmd_111_m1              :8;  // The user defined command for 1-1-1 fast read mode
    u32                             :16;
    //0x51[rw]
    u32 reg_cmd_112                 :8;  // The user defined command for 1-1-2 read mode
    u32 reg_cmd_122                 :8;  // The user defined command for 1-2-2 read mode
    u32                             :16;
    //0x52[rw]
    u32 reg_cmd_114                 :8;  // The user defined command for 1-1-4 read mode
    u32 reg_cmd_144                 :8;  // The user defined command for 1-4-4 read mode
    u32                             :16;
    //0x53[rw]
    u32 reg_cmd_444_m0              :8;  // The user defined command for 4-4-4 read mode (dummy cycle = 4)
    u32 reg_cmd_444_m1              :8;  // The user defined command for 4-4-4 read mode (dummy cycle = 6)
    u32                             :16;
    //0x54[rw]
    u32 reg_dummy_cyc_val           :8;  // The user defined dummy cycle value
    u32                             :24;
    //0x55[rw]
    u32                             :32;
    //0x56[rw]
    u32                             :32;
    //0x57[rw]
    u32                             :32;
    //0x58[rw]
    u32 reg_2_cmd_111_m0            :8;  // The user defined command for 1-1-1 normal read mode for CS1
    u32 reg_2_cmd_111_m1            :8;  // The user defined command for 1-1-1 fast read mode for CS1
    u32                             :16;
    //0x59[rw]
    u32 reg_2_cmd_112               :8;  // The user defined command for 1-1-2 read mode for CS1
    u32 reg_2_cmd_122               :8;  // The user defined command for 1-2-2 read mode for CS1
    u32                             :16;
    //0x5a[rw]
    u32 reg_2_cmd_114               :8;  // The user defined command for 1-1-4 read mode for CS1
    u32 reg_2_cmd_144               :8;  // The user defined command for 1-4-4 read mode for CS1
    u32                             :16;
    //0x5b[rw]
    u32 reg_2_cmd_444_m0            :8;  // The user defined command for 4-4-4 read mode for CS1 (dummy cycle = 4)
    u32 reg_2_cmd_444_m1            :8;  // The user defined command for 4-4-4 read mode for CS1 (dummy cycle = 6)
    u32                             :16;
    //0x5c[rw]
    u32 reg_2_dummy_cyc_val         :8;  // The user defined dummy cycle value for CS1
    u32                             :24;
    //0x5d[rw]
    u32                             :32;
    //0x5e[rw]
    u32                             :32;
    //0x5f[rw]
    u32                             :32;

    //0x60[rw]
    u32 reg_second_ckg_spi          :8;  // Bit[3:0] : user defined dummy cycle number for CS1
                                         // Bit[4]: user defined dummy cycle mode enable for CS1
                                         // 0: disable
                                         // 1: enable
    u32 reg_second_cfg_qspi         :8;  // Bit[8] : CMD_Bypass_Mode for CS1
                                         // Bit[11] : 3/4 byte address mode
                                         // 0: 3 byte
                                         // 1: 4 byte
    u32                             :16;
    //0x61[rw]
    u32 reg_second_csz_high         :4;  // CSZ deselect time for CS1 (SCZ = high).
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_second_csz_setup        :4;  // CSZ setup time for CS1. (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_second_csz_hold         :4;  // CSZ hold time for CS1. (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32                             :20;
    //0x62[rw]
    u32 reg_second_mode_sel         :4;  // Second SPI model select for CS1.
                                         // 0x0: Normal mode(1-1-1), (SPI command is 0x03)
                                         // 0x1: Enable fast read mode(1-1-1), (SPI command is 0x0B)
                                         // 0x2: Enable (1-1-2) mode, (SPI command is 0x3B)
                                         // 0x3: Enable (1-2-2) mode, (SPI command is 0xBB)
                                         // 0xa: Enable (1-1-4) mode, (SPI command is 0x6B)
                                         // 0xb: Enable (1-4-4) mode, (SPI command is 0xEB)
                                         // 0xc: Enable (4-4-4) mode with 4 dummy cycle, (SPI command is 0x0B)
                                         // 0xd: Enable (4-4-4) mode with 6 dummy cycle, (SPI command is 0xEB)
    u32                             :28;
    //0x63[rw]
    u32 reg_second_replaced_cmd     :8;  // the second replaced cmd for CS1
    u32                             :24;
    //0x64[rw]
    u32 reg_clk_div_cnt_sel         :3;  // spi receive div. counter output mux select
    u32 reg_clk_div_cnt_en          :1;  // spi receive div. counter enable
    u32                             :28;
    //0x65[rw]
    u32                             :32;
    //0x66[rw]
    u32 reg_timeout_cnt_value_15_0  :16; // timeout counter value[15:0]
    u32                             :16;
    //0x67[rw]
    u32 reg_timeout_cnt_value_23_16 :8;  // timeout counter value[23:16]
    u32                             :6;
    u32 reg_timeout_cnt_rst         :1;  // timeout counter reset
    u32 reg_timeout_cnt_en          :1;  // timeout counter enable
    u32                             :16;
    //0x68[rw]
    u32 reg_csz_replace_en          :4;  // csz signal replaced by register value en
                                         // B0: CS0 replace en
                                         // B1: CS1 replace en
                                         // B2: CS2 replace en
                                         // B3: CS3 replace en
    u32 reg_csz_replace_val         :4;  // csz signal replaced by register value
                                         // B0: CS0 replace value
                                         // B1: CS1 replace value
                                         // B2: CS2 replace value
                                         // B3: CS3 replace value
    u32                             :24;
    //0x69[rw]
    u32                             :32;
    //0x6a[rw]
    u32                             :32;
    //0x6b[rw]
    u32                             :32;
    //0x6c[rw]
    u32                             :32;
    //0x6d[rw]
    u32 reg_fsp_csz_high            :4;  // CSZ deselect time for FSP (SCZ = high).
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_fsp_csz_setup           :4;  // CSZ setup time for FSP (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_fsp_csz_hold            :4;  // CSZ hold time for FSP (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32                             :20;
    //0x6e[rw]
    u32 reg_fsp2_csz_high           :4;  // CSZ deselect time for FSP2 (SCZ = high).
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_fsp2_csz_setup          :4;  // CSZ setup time for FSP2 (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_fsp2_csz_hold           :4;  // CSZ hold time for FSP2 (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32                             :20;
    //0x6f[rw]
    u32                             :32;

    //0x70[rw]
    u32 reg_ckg_spi                 :8;  // Bit[3:0] : user defined dummy cycle number
                                         // Bit[4]: user defined dummy cycle mode enable
                                         //  0: disable
                                         //  1: enable
                                         // Bit[5]: Force to disable address continue at FSP mode
                                         //  0: disable
                                         //  1: enable
    u32 reg_cfg_qspi                :8;  // Bit[8] : CMD_Bypass_Mode
                                         // Bit[9] : Disable address continue
                                         // Bit[10] : wait FSP done
                                         // Bit[11] : 3/4 byte address mode
                                         // 0: 3 byte
                                         // 1: 4 byte
    u32                             :16;
    //0x71[rw]
    u32 reg_csz_high                :4;  // CSZ deselect time (SCZ = high).
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_csz_setup               :4;  // CSZ setup time. (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32 reg_csz_hold                :4;  // CSZ hold time. (relative to SCK)
                                         // 4'h0: 1 SPI clock cycle
                                         // 4.h1: 2 SPI clock cycles
                                         // 4'hf: 16 SPI clock cycles
    u32                             :20;
    //0x72[rw]
    u32 reg_mode_sel                :4;  // SPI model select (command-address-data).
                                         // 0x0: Normal mode(1-1-1), (SPI command is 0x03)
                                         // 0x1: Enable fast read mode(1-1-1), (SPI command is 0x0B)
                                         // 0x2: Enable (1-1-2) mode, (SPI command is 0x3B)
                                         // 0x3: Enable (1-2-2) mode, (SPI command is 0xBB)
                                         // 0xa: Enable (1-1-4) mode, (SPI command is 0x6B)
                                         // 0xb: Enable (1-4-4) mode, (SPI command is 0xEB)
                                         // 0xc: Enable (4-4-4) mode with 4 dummy cycle, (SPI command is 0x0B)
                                         // 0xd: Enable (4-4-4) mode with 6 dummy cycle, (SPI command is 0xEB)
    u32                             :28;
    //0x73[rw]
    u32 reg_replaced_cmd            :8;  // the replaced cmd
    u32                             :24;
    //0x74[rw]
    u32 reg_spare_0                 :16; // Bit[0] : wrap mode for CS0 flash, fow SW to write when the flash is enter wrap mode
                                         //  0: not wrap mode
                                         //  1: wrap mode
                                         // Bit[1] : wrap 16 byte for CS0 flash, fow SW to write
                                         //  0: not 16 byte
                                         //  1: 16 byte
                                         // Bit[2] : wrap 32 byte for CS0 flash, fow SW to write
                                         //  0: not 32 byte
                                         //  1: 32 byte
                                         // Bit[3] : wrap 64 byte for CS0 flash, fow SW to write
                                         //  0: not 64 byte
                                         //  1: 64 byte
                                         // Bit[4] : wrap 128 byte for CS0 flash, fow SW to write
                                         //  0: not 128 byte
                                         //  1: 128 byte
                                         // Bit[7:5] : reserved, keep the data as default value
                                         // Bit[8] : wrap mode for CS1 flash, fow SW to write when the flash is enter wrap mode
                                         //  0: not wrap mode
                                         //  1: wrap mode
                                         // Bit[9] : wrap 16 byte for CS1 flash, fow SW to write
                                         //  0: not 16 byte
                                         //  1: 16 byte
                                         // Bit[10] : wrap 32 byte for CS1 flash, fow SW to write
                                         //  0: not 32 byte
                                         //  1: 32 byte
                                         // Bit[11] : wrap 64 byte for CS1 flash, fow SW to write
                                         //  0: not 64 byte
                                         //  1: 64 byte
                                         // Bit[12] : wrap 128 byte for CS1 flash, fow SW to write
                                         //  0: not 128 byte
                                         //  1: 128 byte
                                         // Bit[15:13] : reserved, keep the data as default value
    u32                             :16;
    //0x75[rw]
    u32                             :32;
    //0x76[r]
    u32 reg_debug_bus_0             :16;
    u32                             :16;
    //0x77[r]
    u32 reg_debug_bus_1             :16;
    u32                             :16;
    //0x78[r]
    u32 reg_debug_bus_2             :16;
    u32                             :16;
    //0x79[r]
    u32 reg_debug_bus_3             :16;
    u32                             :16;
    //0x7a[rw]
    u32 reg_chip_select             :2;
    u32                             :30;
    //0x7b[r]
    u32 reg_switch_cs_busy          :1;
    u32                             :31;
    //0x7c[rw]
    u32 reg_func_setting_def1       :16;
                                        //Bit[0] : cs select by address enable
                                        //  0: disable
                                        //  1: enable
                                        //Bit[1] : use comb. CSZ setting (setup and high)
                                        //  0: disable
                                        //  1: enable
                                        //Bit[2] : HST2 bit number
                                        //  0: 16 bits
                                        //  1: 32 bits
                                        //Bit[3] : Embedded flash size
                                        //  0: 16Mb
                                        //  1: 32Mb
                                        //Bit[15:4] : reserved, keep the data as default value
    u32                             :16;
    //0x7d[w]
    u32 reg_func_setting_def0       :16;
                                        //Bit[0] : use index to support 4 byte address
                                        //0: disable
                                        //1: enable
                                        //Bit[1] : one burst data over two flash enable
                                        //0: disable
                                        //1: enable
                                        //Bit[2] : 4 byte address mode enable
                                        //0: disable
                                        //1: enable
                                        //Bit[3] : use user defined command
                                        //0: use default command
                                        //1: use user defined command
                                        //Bit[4] : use user defined dummy cycle value at cmd bypass mode
                                        //0: use 0xa5
                                        //1: use user defined value
                                        //Bit[5] : wrap command at flash non-wrap mode support enable
                                        //0: disable
                                        //1: enable
                                        //Bit[6] : incremental command at flash wrap mode support enable
                                        //0: disable
                                        //1: enable
                                        //Bit[15:7] : reserved, keep the data as default value
    u32                             :16;
    //0x7e[r]
    u32                             :32;
    //0x7f[w]
    u32 reg_endia                   :1;
    u32                             :31;
} KeQspi_t;

extern volatile KeQspi_t* const g_ptKeQspi;

#endif // __KERNEL_QSPI_H__

