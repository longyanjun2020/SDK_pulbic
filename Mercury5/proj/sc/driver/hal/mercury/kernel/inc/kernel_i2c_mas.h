/***************************************************************************
 *  kernel_i2c_mas.h
 *--------------------------------------------------------------------------
 *  Scope: I2C MAS related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_I2C_MAS_H__
#define __KERNEL_I2C_MAS_H__

#include "stdcomp.h"
#include "cpu_mem_map.hc"

/****************************************************************************/
/*        Master SPI registers                           */
/****************************************************************************/

typedef struct KeI2CMas_s
{
    /* [0x00] */
    u32 reg_i2c_dma_en                :1 ; /// Enable I2C master in DMA mode
    u32 reg_i2c_dma_bl                :4 ; /// (valid as reg_i2c_dma_en==1).
                                           /// Burst length of data, including addrss
    u32 reg_i2c_dma_milly             :1 ; /// Enable I2C master in DMA Milly mode
    u32 :26; /// [0x00]
    /* [0x01] */
    u32 reg_i2c_irq_mask_done           :1;
    u32 reg_i2c_irq_mask_wait_state     :1;
    u32 reg_i2c_irq_mask_write_nak      :1;
    u32 :29; /// [0x01]
    /* [0x02] */
    u32 reg_i2c_irq_force_done          :1;
    u32 reg_i2c_irq_force_wait_state    :1;
    u32 reg_i2c_irq_force_write_nak     :1;
    u32 :29; /// [0x02]
    /* [0x03] */
    u32 reg_i2c_irq_clr_done            :1;
    u32 reg_i2c_irq_clr_wait_state      :1;
    u32 reg_i2c_irq_clr_write_nak       :1;
    u32 :29; /// [0x03]
    /* [0x04] */
    u32 reg_i2c_irq_status_done         :1;
    u32 reg_i2c_irq_status_wait_state   :1;
    u32 reg_i2c_irq_status_write_nak    :1;
    u32 :29; /// [0x04]
    /* [0x05] */
    u32 reg_i2c_sw_rst                :1 ; /// I2C Software Reset
    u32 :31; /// [0x05]
    /* [0x06] */
    u32 reg_i2c_wack_status           :16; /// Acks of each write data byte 
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_i2c_scl_mismatch_level_sel:1 ; /// Select wait state level: 0: prescale                                    
                                           ///                                    1: reg_i2c_scl_mismatch_level
    u32 :31; /// [0x07]
    /* [0x08] */
    u32 reg_i2c_scl_mismatch_level    :16; /// Wait state level
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_i2c_scl_h_debounce_level_sel:1 ; /// Select scl high debounce level : 0: 1000
                                             ///                                                   1: reg_i2c_scl_h_debounce_leve
    u32 :31; /// [0x09]
    /* [0x0A] */
    u32 reg_i2c_scl_h_debounce_level  :16; /// scl high debounce level in slave wait state
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_i2c_debug_out_sel         :1 ; /// Select debug out group
    u32 :31; /// [0x0B]
    /* [0x0C] */
    u32 reg_i2c_no_debounce           :1 ; /// Disable debounce for wait state detection. 0: have debounce; 1: no debounce
    u32 :31; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    u32 :32; /// [0x0F]
    /* [0x10] */
    u32 reg_i2c_sw_ctrl               :1 ; /// I2C Signal Control
                                           /// # 1'b0: by HW
                                           /// # 1'b1: by SW
                                           ///  ( single buffer register)
    u32 reg_i2c_mode                  :1 ; /// I2C mode.
                                           /// # 1'b1: OmniVision SIF.
                                           /// # 1'b0: Others.
                                           ///  ( single buffer register )
    u32 reg_i2c_cmd_bl                :1 ; /// I2C command burst length
                                           /// (valid as reg_i2c_dma_en==0).
                                           /// # 1'b0: length is 1.
                                           /// # 1'b1: length is 2.
                                           ///  ( single buffer register )
    u32 reg_i2c_addr_mode              :1 ; /// I2C Register Address Mode
                                           /// (valid as reg_i2c_dma_milly==0).
                                           /// # 1'b0 : 8 bit mode
                                           /// # 1'b1 : 16 bit series mode
                                           ///  (single buffer register)
    u32 reserved                      :1 ; /// None
    u32 :8 ; /// [0x10]
    u32 reg_i2c_scl_i                 :1 ; /// I2C SCL Input
                                           ///  ( single buffer register )
    u32 reg_i2c_sda_i                 :1 ; /// I2C SDA Input
                                           ///  ( single buffer register )
    u32 reg_i2c_status                :1 ; /// I2C Status
                                           /// # 1'b0: Idle
                                           /// # 1'b1: Busy
                                           ///  ( single buffer register )
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_i2c_cmd                   :16; /// I2C command
                                           /// # [0]: 1: read, 0: write.
                                           /// # [7:1]: Slave address.
                                           /// # [15:8]: Register address for 8 bit mode / first register address for 16 bit series mode
                                           /// ([15:8] valid as reg_i2c_dma_milly==0).
                                           ///  ( single buffer register )
    u32 :16; /// [0x11]
    /* [0x12] */
		u32 reg_i2c_write_data0             :8;
		u32 reg_i2c_write_data1             :8;
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_i2c_prescale              :16; /// Factor of division for generating I2C clock.
                                           /// Must be programmed less than SYSCLK /(4*M2S_frequency) ¡V 1
                                           ///  ( single buffer register )
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_i2c_sw_scl_oen            :1 ; /// I2C SW scl control
                                           /// # 1'b0: scl low
                                           /// # 1'b1: scl high
    u32 reg_i2c_sw_sda_oen            :1 ; /// I2C SW sda control
                                           /// # 1'b0: sda output low
                                           /// # 1'b1: sda input or sda output high
    u32 :30; /// [0x14]
    /* [0x15] */
    u32 reg_i2c_read_data0              :8;
    u32 reg_i2c_read_data1              :8;  
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_i2c_cmd_addr1               :8;
} KeI2CMas_t;

extern volatile KeI2CMas_t* const g_ptKeI2CMas;

#endif // __KERNEL_I2C_MAS_H__
                                                 
