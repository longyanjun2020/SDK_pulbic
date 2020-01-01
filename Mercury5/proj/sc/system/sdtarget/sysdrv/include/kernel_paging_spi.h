/***************************************************************************
 *  kernel_paging_spi.h
 *--------------------------------------------------------------------------
 *  Scope: Paging SPI related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_PAGING_SPI_H__
#define __KERNEL_PAGING_SPI_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "riubridge.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define ISP_MODE_PASSWD         0xAAAA
#define TRIGGER_MODE_PASSWD     0x3333

#define PAGINGSPI_BIG_ENDIAN    1
#define PAGINGSPI_LITTLE_ENDIAN 0


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
typedef enum 
{
    PAGING_SPI_CLK_DIV2 = 0x001,
//    PAGING_SPI_CLK_DIV3 = 0x002,    // Reserved
    PAGING_SPI_CLK_DIV4 = 0x004,
//    PAGING_SPI_CLK_DIV5 = 0x008,    // Reserved
//    PAGING_SPI_CLK_DIV6 = 0x010,    // Reserved
//    PAGING_SPI_CLK_DIV7 = 0x020,    // Reserved
    PAGING_SPI_CLK_DIV8 = 0x040,
    PAGING_SPI_CLK_DIV16 = 0x080,
    PAGING_SPI_CLK_DIV32 = 0x100,
    PAGING_SPI_CLK_DIV64 = 0x200,
    PAGING_SPI_CLK_DIV128 = 0x400
} PagingSpiClkDiv_e;

typedef enum 
{
    PAGING_SPI_CS_1 = 0x01,
    PAGING_SPI_CS_2 = 0x02,
    PAGING_SPI_DEV_MODE = 0x04
} PagingSpiChipSelect_e;

/************************************************/
/* Paging SPI registers definition              */
/************************************************/
typedef struct KePagingSpi_s
{
    /* [0x00] */
    u32 reg_isp_password              :16; /// ISP Password 0xAAAA,
                                           /// If password correct, enable ISP
                                           /// If password incorrect, disable ISP
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_spi_command               :8 ; /// SPI command, 
                                           /// If write data to this port, ISP will start operation
    u32 :24; /// [0x01]
    /* [0x02] */
    u32 reg_address1                  :8 ; /// SPI address 1, A[7:0]
    u32 reg_adderss2                  :8 ; /// SPI address 2, A[15:8]
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_address3                  :8 ; /// SPI address 3, A[23:16]
    u32 :24; /// [0x03]
    /* [0x04] */
    u32 reg_wdata                     :8 ; /// SPI write data register
    u32 :24; /// [0x04]
    /* [0x05] */
    u32 reg_rdata                     :8 ; /// SPI read data register
    u32 :24; /// [0x05]
    /* [0x06] */
    u32 reg_spi_clk_div               :11;
    u32 :21; /// [0x06]
/*
    u32 reg_spi_clk_div2              :1 ; /// SPI_CLOCK = MCU_CLOCK/2
    u32 reg_spi_clk_div3              :1 ; /// Reserved
    u32 reg_spi_clk_div4              :1 ; /// SPI_CLOCK = MCU_CLOCK/4
    u32 reg_spi_clk_div5              :1 ; /// Reserved
    u32 reg_spi_clk_div6              :1 ; /// Reserved
    u32 reg_spi_clk_div7              :1 ; /// Reserved
    u32 reg_spi_clk_div8              :1 ; /// SPI_CLOCK = MCU_CLOCK/8
    u32 reg_spi_clk_div16             :1 ; /// SPI_CLOCK = MCU_CLOCK/16
    u32 reg_spi_clk_div32             :1 ; /// SPI_CLOCK = MCU_CLOCK/32
    u32 reg_spi_clk_div64             :1 ; /// SPI_CLOCK = MCU_CLOCK/64
    u32 reg_spi_clk_div128            :1 ; /// SPI_CLOCK = MCU_CLOCK/128
*/
    /* [0x07] */
    u32 reg_device_select             :3 ; /// Select Device.
                                           /// 000: PMC.MXIC
                                           /// 001: NextFlash. 
                                           /// 010: ST.
                                           /// 011: SST.
                                           /// 100: ATMEL
    u32 :29; /// [0x07]
    /* [0x08] */
    u32 reg_spi_ce_clr                :1 ; /// SPI chip enable clear. software can force SPI chip disable at burst SPI read/write, this bit is write-then-clear register
                                           /// 1: for clear
                                           /// 0: for not clear
    u32 :31; /// [0x08]
    /* [0x09] */
    u32 reg_tces_time                 :16; /// SPI Chip enable setup/hold time   
                                           /// 0x0000: Delay 1 SPI clock
                                           /// 0x0001: Delay 2 SPI clock
                                           /// 0x000f: Delay 16 SPI clock
                                           /// 0xffff: Delay 64k SPI clock 
                                           /// Default delay 2 SPI clock                
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_tbp_time                  :16; /// Byte-Program time for device SST
                                           /// 0x0000: Delay 1 SPI clock
                                           /// 0x0001: Delay 2 SPI clock
                                           /// 0x000f: Delay 16 SPI clock
                                           /// 0xffff: Delay 64k SPI clock
                                           /// Default delay 500 SPI clock,
                                           /// Assume SPI clock 40ns, Delay 500*40 = 20 us
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_tceh_time                 :16; /// SPI Chip enable pulse high time
                                           /// 0x0000: Delay 1 SPI clock
                                           /// 0x0001: Delay 2 SPI clock
                                           /// 0x000f: Delay 16 SPI clock
                                           /// 0xffff: Delay 64k SPI clock 
                                           /// Default delay 5 SPI clock           
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_spi_rd_req                :1 ; /// SPI READ Data Request, For CPU read SPI data via RIU, 
                                           /// If CPU read SPI data via XIU, request not needed. 
    u32 :31; /// [0x0C]
    /* [0x0D] */
    u32 reg_isp_rp_adr1               :16; /// Programmable ISP Read port address[15:0]
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_isp_rp_adr2               :16; /// Programmable ISP Read port address[31:0]
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_endian_sel_spi            :1 ; /// 0: Big_endian
                                           /// 1: Little_endian
    u32 :31; /// [0x0F]
    /* [0x10] */
    u32 reg_isp_active                :1 ; /// ISP ACTIVE FLAG
    u32 :31; /// [0x10]
    /* [0x11] */
    u32 :1 ; /// [0x11]
    u32 reg_cpu_active                :1 ; /// CPU_ACTIVE FLAG
    u32 :30; /// [0x11]
    /* [0x12] */
    u32 :2 ; /// [0x12]
    u32 reg_dma_active                :1 ; /// DMA_ACTIVE FLAG
    u32 :29; /// [0x12]
    /* [0x13] */
    u32 reg_isp_fsm                   :6 ; /// ISP_FSM
    u32 :26; /// [0x13]
    /* [0x14] */
    u32 reg_spi_master_fsm            :3 ; /// SPI_MASTER_FSM
    u32 :29; /// [0x14]
    /* [0x15] */
    u32 reg_spi_rd_data_rdy           :1 ; /// SPI Read Data Ready flag
                                           /// 1: read data ready
                                           /// 0: read data not ready
    u32 :31; /// [0x15]
    /* [0x16] */
    u32 reg_spi_wr_data_rdy           :1 ; /// SPI Write Ready flag
                                           /// 1: Write data ready
                                           /// 0: Write data not ready
    u32 :31; /// [0x16]
    /* [0x17] */
    u32 reg_spi_wr_cm_rdy             :1 ; /// SPI Write Command Ready flag
                                           /// 1: Write command ready
                                           /// 0: Write command not ready
    u32 :31; /// [0x17]
    /* [0x18] */
    u32 reg_cpu_rst_fm_isp            :1 ; /// ISP generate reset to CUP,
                                           /// When ISP programming done, software maybe can 
                                           /// issue a reset to CPU.
    u32 :31; /// [0x18]
    /* [0x19] */
    u32 reg_isp_old_en                :1 ; /// Read flag, for isp_old_en
    u32 :31; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    /* [0x20] */
    u32 reg_force_isp_idle            :1 ; /// FORCE_ISP_IDLE
    u32 :31; /// [0x20]
    /* [0x21] */
    u32 reg_aai_num                   :16; /// For SST SPI FLASH USE. 
                                           /// At AAI mode, set how many data will be written. 
                                           /// 0x0000: For 1 byte programming
                                           /// 0x0001: For 2 byte programming
                                           /// 0xFFFF: For 64k byte programming
    u32 :16; /// [0x21]
    /* [0x22] */
    u32 reg_aai_reg                   :1 ; /// FORCE SPI COMMAND
                                           /// Force AAI mode
    u32 reg_rdsr_reg                  :1 ; /// FORCE SPI COMMAND
                                           /// Force RDSR
    u32 reg_wrsr_reg                  :1 ; /// FORCE SPI COMMAND
                                           /// Force WRSR
    u32 reg_rdcr_reg                  :1 ; /// FORCE SPI COMMAND
                                           /// Force RDCR
    u32 reg_wrcr_reg                  :1 ; /// FORCE SPI COMMAND
                                           /// Force WRCR
    u32 reg_read_reg                  :1 ; /// FORCE SPI COMMAND
                                           /// Force READ
    u32 reg_fast_read_reg             :1 ; /// FORCE SPI COMMAND
                                           /// Force FAST READ
    u32 reg_page_pro_reg              :1 ; /// FORCE SPI COMMAND
                                           /// Force PAGE PROGRAMMING 
    u32 reg_b_erase_reg               :1 ; /// FORCE SPI COMMAND
                                           /// Force BLOCK ERASE
    u32 reg_man_id_reg                :1 ; /// FORCE SPI COMMAND
                                           /// Force READ MANUFACTURER ID
    u32 :22; /// [0x22]
    u32 :32; /// [0x23]
    u32 :32; /// [0x24]
    /* [0x25] */
    u32 reg_test_mode                 :16; /// TEST_MODE,
                                           /// User define SPI waveform,
                                           /// 0x7777: User define.
                                           /// others: not User define,
                                           /// Before entry TEST_MODE, Please make sure 
                                           /// ISP/DMA disable
    u32 :16; /// [0x25]
    /* [0x26] */
    u32 reg_test_spi_ceb              :1 ; /// User generate SPI chip enable waveform
    u32 :31; /// [0x26]
    /* [0x27] */
    u32 reg_test_spi_sck              :1 ; /// User generate SPI clock waveform
    u32 :31; /// [0x27]
    /* [0x28] */
    u32 reg_test_spi_si               :1 ; /// User generate SPI data waveform.
    u32 :31; /// [0x28]
    /* [0x29] */
    u32 reg_test_spi_so               :1 ; /// SPI Data output. for RIU read
                                           /// Please delay 1us for every setting(TEST MODE).
                                           /// EX1. W(0x21,0x0) --> delay 1us --> W(0x23,0x1) -->
                                           /// delay 1us --> W(0x22,0x1) --> delay 1us -->
                                           /// W(0x22,0x0) --> delay 1us ........--> W(ox21,0x1)
                                           /// EX2. W(0x21,0x0) --> delay 1us --> W(0x22,0x1) --> 
                                           /// delay 1us --> W(0x22,0x0) --> delay 1us --> 
                                           /// R(0x24) --> delay 1us .........> W(0x21,01)
    u32 :31; /// [0x29]
    /* [0x2A] */
    u32 reg_trigger_mode              :16; /// TRIGGER_MODE,,
                                           /// 0x3333: Trigger mode.
                                           /// others: not Trigger mode.
                                           /// Before entry Trigger mode, Please make sure 
                                           /// ISP/DMA disable
    u32 :16; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    /* [0x2F] */
    u32 reg_spi_pre_fetch_en          :1 ; /// Reserved
    u32 reg_spi_abort_en              :1 ; /// Reserved
    u32 reg_branch_counter_clear      :1 ; /// Clear counter for CPU branch
                                           /// 1: Clear
                                           /// 0: Not Clear
    u32 reg_branch_counter_start      :1 ; /// Start counter for CPU branch
                                           /// 1: Start
                                           /// 0: Not Start
    u32 :28; /// [0x2F]
    /* [0x30] */
    u32 reg_dma_start                 :1 ; /// DMA Start, DMA between MIU and SPI device
    u32 :31; /// [0x30]
    /* [0x31] */
    u32 reg_dma_cnt                   :16; /// DMA Transfer size (byte),
    u32 :16; /// [0x31]
    /* [0x32] */
    u32 reg_dma_miu_start_adr1        :16; /// DMA source address, Unit word address, MIU_Address[15:0]
    u32 :16; /// [0x32]
    /* [0x33] */
    u32 reg_dma_miu_start_adr2        :16; /// DMA source address, Unit word address, MIU_Address[31:16]
    u32 :16; /// [0x33]
    /* [0x34] */
    u32 reg_dma_busy                  :1 ; /// DMA busy FLAG
    u32 reg_dma_done                  :1 ; /// DMA done FLAG
    u32 :30; /// [0x34]
    /* [0x35] */
    u32 reg_dma_cnt_status            :16; /// DMA counter status
    u32 :16; /// [0x35]
    /* [0x36] */
    u32 reg_chip_select               :3 ; /// chip select
/*
    u32 reg_chip_select1              :1 ; /// #1 Flash chip select
    u32 reg_chip_select2              :1 ; /// #2 Flash chip select
    u32 reg_device_mode               :1 ; /// Enable SPI device mode
*/
    u32 :29; /// [0x36]
    /* [0x37] */
    u32 reg_cpol                      :1 ; /// Clock Polarity
                                           /// Configures the idle state of "SCLK" serial clock when SPI is enabled (when disabled, "SCLK" is in high level). When 1, the "SCLK" output is set (SCLK = 1) otherwise it is cleared(SCLK = 0).
    u32 reg_cpha                      :1 ; /// Configures the data sampling point. When 0, data is sampled when "SCLK" goes to active state(see reg_cpol). When 1, data is sampled when "SCLK" goes to idle state(see reg_cpol)
    u32 :30; /// [0x37]
    u32 :32; /// [0x38]
    u32 :32; /// [0x39]
    u32 :32; /// [0x3A]
    u32 :32; /// [0x3B]
    u32 :32; /// [0x3C]
    u32 :32; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
    /* [0x40] */
    u32 reg_isp_top_reset_z           :1 ; /// Software reset isp_top.
                                           /// 0: reset
                                           /// 1: not reset
    u32 reg_spi_arbiter_reset_z       :1 ; /// Software reset spi arbiter
                                           /// 0: reset
                                           /// 1 not reset
    u32 reg_spi_burst_reset_z         :1 ; /// Software reset spi_burst
                                           /// 0: reset
                                           /// 1: not reset
} KePagingSpi_t;

#endif // __KERNEL_PAGING_SPI_H__
