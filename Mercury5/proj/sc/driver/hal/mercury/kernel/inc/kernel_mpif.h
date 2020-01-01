#ifndef __KERNEL_MPIF_H__
#define __KERNEL_MPIF_H__

/************************************************/
/* RIU MPIF Bank                                */
/************************************************/

typedef struct KeMpif_s
{
    /* [0x00] */
    u32 reg_mpif_lc1a_vld             :1 ; /// MPIF Logical Channel 1a valid
    u32 reg_mpif_lc1a_rw              :1 ; /// MPIF Logical Channel 1a read/write
    u32 reg_mpif_lc1a_sid             :2 ; /// MPIF Logical Channel 1a Slave ID
    u32 reg_mpif_lc1a_idx             :3 ; /// MPIF Logical Channel 1a index
    u32 :1 ; /// [0x00]
    u32 reg_mpif_lc1a_data            :8 ; /// MPIF Logical Channel 1a data
    u32 :24; /// [0x00]
    u32 reg_sts_mpif_lc1a_data        :8 ; /// MPIF Logical Channel 1a data
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_mpif_lc2a_vld             :1 ; /// MPIF Logical Channel 2a valid
    u32 reg_mpif_lc2a_rw              :1 ; /// MPIF Logical Channel 2a read/write
    u32 reg_mpif_lc2a_sid             :2 ; /// MPIF Logical Channel 2a Slave ID
    u32 reg_mpif_lc2a_chk             :1 ; /// MPIF Logical Channel 2a check enable
    u32 :1 ; /// [0x01]
    u32 reg_mpif_lc2a_retrx_limit     :2 ; /// MPIF re-transmit/receive count limit
                                           /// 0: 0 time
                                           /// 1: 1 times
                                           /// 2: 2 times
                                           /// 3: 3 times
    u32 :24; /// [0x01]
    /* [0x02] */
    u32 reg_mpif_lc2a_adr             :16; /// MPIF Logical Channel 2a address
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_mpif_lc2a_data            :16; /// MPIF Logical Channel 2a data
    u32 :16; /// [0x03]
    /* [0x03] */
    u32 reg_sts_mpif_lc2a_data        :16; /// MPIF Logical Channel 2a data
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_mpif_lc2b_vld             :1 ; /// MPIF Logical Channel 2b valid
    u32 reg_mpif_lc2b_rw              :1 ; /// MPIF Logical Channel 2b read/write
    u32 reg_mpif_lc2b_sid             :2 ; /// MPIF Logical Channel 2b Slave ID
    u32 reg_mpif_lc2b_chk             :1 ; /// MPIF Logical Channel 2b check enable
    u32 :1 ; /// [0x04]
    u32 reg_mpif_lc2b_retrx_limit     :2 ; /// MPIF re-transmit/receive count limit
                                           /// 0: 0 time
                                           /// 1: 1 times
                                           /// 2: 2 times
                                           /// 3: 3 times
    u32 :24; /// [0x04]
    /* [0x05] */
    u32 reg_mpif_lc2b_adr             :16; /// MPIF Logical Channel 2b address
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_mpif_lc2b_data            :16; /// MPIF Logical Channel 2b data
    u32 :16; /// [0x06]
    /* [0x06] */
    u32 reg_sts_mpif_lc2b_data        :16; /// MPIF Logical Channel 2b data
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_mpif_lc3a_vld             :1 ; /// MPIF Logical Channel 3a valid
    u32 reg_mpif_lc3a_rw              :1 ; /// MPIF Logical Channel 3a read/write
    u32 reg_mpif_lc3a_sid             :2 ; /// MPIF Logical Channel 3a Slave ID
    u32 reg_mpif_lc3a_chk             :1 ; /// MPIF Logical Channel 3a check enable
    u32 reg_mpif_lc3a_retrx           :1 ; /// MPIF Logical Channel 3a re-transmit/receive packet indicator
    u32 reg_mpif_lc3a_retrx_limit     :2 ; /// MPIF re-transmit/receive count limit
                                           /// 0: 0 time
                                           /// 1: 1 times
                                           /// 2: 2 times
                                           /// 3: 3 times
    u32 reg_mpif_lc3a_src             :1 ; /// MPIF Logical Channel 3a source/destination selection 
                                           /// 0: to/from RIU 
                                           /// 1: to/from MIU
    u32 reg_mpif_lc3a_miusel          :1 ; /// MPIF Logical Channel 3a MIU path selection 
                                           /// 0: MIU (SRAM)
                                           /// 1: EMI (SDRAM)
    u32 reg_mpif_lc3a_fmode           :1 ; /// MPIF Logical Channel 3a fast read/write mode 
    u32 reg_mpif_lc3a_rx_nwmiu        :1 ; /// MPIF Logical Channel 3a not wait miu done 
    u32 reg_mpif_lc3a_wcnt            :4 ; /// MPIF Logical Channel 3a max wait number 
    u32 :16; /// [0x07]
    /* [0x08] */
    u32 reg_mpif_lc3a_pktlen          :16; /// MPIF Logical Channel 3a packet total length
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_mpif_lc3a_data_0          :16; /// MPIF Logical Channel 3a data
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_1          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_2          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_3          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_4          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_5          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_6          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x09]
    u32 reg_mpif_lc3a_data_7          :16; /// @see reg_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    /* [0x10] */
    u32 reg_sts_mpif_lc3a_data_0      :16; /// MPIF Logical Channel 3a data
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_1      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_2      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_3      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_4      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_5      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_6      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x10]
    u32 reg_sts_mpif_lc3a_data_7      :16; /// @see reg_sts_mpif_lc3a_data_0
    u32 :16; /// [0x17]
    /* [0x17] */
    u32 reg_mpif_lc3a_madr_0          :16; /// MPIF Logical Channel 3a data to/from MIU base address
    u32 :16; /// [0x17]
    u32 reg_mpif_lc3a_madr_1          :16; /// @see reg_mpif_lc3a_madr_0
    u32 :16; /// [0x18]
    /* [0x18] */
    u32 reg_mpif_lc3b_vld             :1 ; /// MPIF Logical Channel 3b valid
    u32 reg_mpif_lc3b_rw              :1 ; /// MPIF Logical Channel 3b read/write
    u32 reg_mpif_lc3b_sid             :2 ; /// MPIF Logical Channel 3b Slave ID
    u32 reg_mpif_lc3b_chk             :1 ; /// MPIF Logical Channel 3b check enable
    u32 reg_mpif_lc3b_retrx           :1 ; /// MPIF Logical Channel 3b re-transmit/receive packet indicator
    u32 reg_mpif_lc3b_retrx_limit     :2 ; /// MPIF re-transmit/receive count limit
                                           /// 0: 0 time
                                           /// 1: 1 times
                                           /// 2: 2 times
                                           /// 3: 3 times
    u32 reg_mpif_lc3b_src             :1 ; /// MPIF Logical Channel 3b source/destination selection 
                                           /// 0: to/from RIU 
                                           /// 1: to/from MIU
    u32 reg_mpif_lc3b_miusel          :1 ; /// MPIF Logical Channel 3b MIU path selection 
                                           /// 0: MIU (SRAM)
                                           /// 1: EMI (SDRAM)
    u32 reg_mpif_lc3b_fmode           :1 ; /// MPIF Logical Channel 3b fast read/write mode 
    u32 reg_mpif_lc3b_rx_nwmiu        :1 ; /// MPIF Logical Channel 3b not wait miu done 
    u32 reg_mpif_lc3b_wcnt            :4 ; /// MPIF Logical Channel 3b max wait number 
    u32 :16; /// [0x18]
    /* [0x18] */
    u32 reg_mpif_lc3b_pktlen          :16; /// MPIF Logical Channel 3b packet total length
    u32 :16; /// [0x18]
    /* [0x18] */
    u32 reg_mpif_lc3b_data_0          :16; /// MPIF Logical Channel 3b data/
                                           /// SPI data for RIU path
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_1          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_2          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_3          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_4          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_5          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_6          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x18]
    u32 reg_mpif_lc3b_data_7          :16; /// @see reg_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    /* [0x1F] */
    u32 reg_sts_mpif_lc3b_data_0      :16; /// MPIF Logical Channel 3b data/
                                           /// SPI data for RIU path
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_1      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_2      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_3      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_4      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_5      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_6      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x1F]
    u32 reg_sts_mpif_lc3b_data_7      :16; /// @see reg_sts_mpif_lc3b_data_0
    u32 :16; /// [0x26]
    /* [0x26] */
    u32 reg_mpif_lc3b_madr_0          :16; /// MPIF Logical Channel 3b data to/from MIU base address
    u32 :16; /// [0x26]
    u32 reg_mpif_lc3b_madr_1          :16; /// @see reg_mpif_lc3b_madr_0
    u32 :16; /// [0x27]
    /* [0x27] */
    u32 reg_mpif_lc4a_vld             :1 ; /// MPIF Logical Channel 4a valid
    u32 reg_mpif_lc4a_rw              :1 ; /// MPIF Logical Channel 4a read/write
    u32 reg_mpif_lc4a_sid             :2 ; /// MPIF Logical Channel 4a Slave ID
    u32 :2 ; /// [0x27]
    u32 reg_mpif_lc4a_retrx_limit     :2 ; /// MPIF re-transmit/receive count limit
                                           /// 0: 0 time
                                           /// 1: 1 times
                                           /// 2: 2 times
                                           /// 3: 3 times
    u32 reg_mpif_lc4a_rx_nwmiu        :1 ; /// MPIF Logical Channel 4a not wait miu done 
    u32 reg_mpif_lc4a_miusel          :1 ; /// MPIF Logical Channel 4a MIU path selection 
                                           /// 0: MIU (SRAM)
                                           /// 1: EMI (SDRAM)
    u32 reg_mpif_lc4a_granular        :2 ; /// MPIF Logical Channel 4a breakpoint 
                                           /// 00: 1x256 bytes 
                                           /// 01: 2x256 bytes 
                                           /// 10: 3x256 bytes 
                                           /// 11: 4x256 bytes
    u32 reg_mpif_lc4a_wcnt            :4 ; /// MPIF Logical Channel 4a max wait number 
    u32 :16; /// [0x27]
    /* [0x27] */
    u32 reg_mpif_lc4a_stmlen          :16; /// MPIF Logical Channel 4a stream total length (byte unit)
    u32 :16; /// [0x27]
    /* [0x27] */
    u32 reg_mpif_lc4a_madr_0          :16; /// MPIF Logical Channel 4a data to/from MIU base address
    u32 :16; /// [0x27]
    u32 reg_mpif_lc4a_madr_1          :16; /// @see reg_mpif_lc4a_madr_0
    u32 :16; /// [0x28]
    /* [0x28] */
    u32 reg_mpif_4wspi_vld            :1 ; /// MPIF 4-wire SPI valid
    u32 reg_mpif_4wspi_rw             :1 ; /// MPIF 4-wire SPI read/write
    u32 reg_mpif_4wspi_duplex         :1 ; /// MPIF 4-wire SPI duplex enable
                                           /// Note: only valid for read command
    u32 :29; /// [0x28]
    /* [0x28] */
    u32 reg_mpif_3wspi_vld            :1 ; /// MPIF 3-wire SPI valid
    u32 reg_mpif_3wspi_rw             :1 ; /// MPIF 3-wire SPI read/write
    u32 :30; /// [0x28]
    /* [0x28] */
    u32 reg_mpif_spi_sid              :2 ; /// MPIF SPI Slave ID
    u32 reg_mpif_spi_cpha             :1 ; /// MPIF SPI clock phase
    u32 reg_mpif_spi_cpol             :1 ; /// MPIF SPI clock polarity
    u32 reg_mpif_spi_tl               :2 ; /// MPIF SPI leading cycle
    u32 reg_mpif_spi_tt               :2 ; /// MPIF SPI trailing cycle
    u32 reg_mpif_spi_cmd_len          :3 ; /// MPIF SPI command length
                                           /// "000" - 0 byte
                                           /// "001" - 1 bytes
                                           /// "010" - 2 bytes
                                           /// "011" - 3 bytes
                                           /// "100" - 4 bytes
                                           /// "101" - 5 bytes
                                           /// "110" - 6 bytes
                                           /// "111" - 7 bytes
    u32 reg_mpif_spi_src              :1 ; /// MPIF SPI source/destination selection 
                                           /// 0: to/from RIU 
                                           /// 1: to/from MIU
    u32 reg_mpif_spi_miusel           :1 ; /// MPIF SPI MIU path selection 
                                           /// 0: MIU (SRAM)
                                           /// 1: EMI (SDRAM)
    u32 reg_mpif_spi_sep_io           :1 ; /// MPIF SPI separate IO mode
    u32 reg_mpif_spi_rx_nwmiu         :1 ; /// MPIF SPI not wait miu done 
    u32 :17; /// [0x28]
    /* [0x28] */
    u32 reg_mpif_spi_cmd_0            :16; /// MPIF SPI command value
    u32 :16; /// [0x28]
    u32 reg_mpif_spi_cmd_1            :16; /// @see reg_mpif_spi_cmd_0
    u32 :16; /// [0x29]
    /* [0x29] */
    u32 reg_mpif_spi_dat_len          :16; /// MPIF SPI data total length (byte unit)
    u32 :16; /// [0x29]
    /* [0x29] */
    u32 reg_mpif_spi_madr_0           :16; /// MPIF SPI MIU base address
    u32 :16; /// [0x29]
    u32 reg_mpif_spi_madr_1           :16; /// @see reg_mpif_spi_madr_0
    u32 :16; /// [0x2A]
    /* [0x2B] */
    u32 reg_mpif_4wspi_busy           :1 ; /// MPIF 4-wire SPI busy flag
    u32 reg_mpif_3wspi_busy           :1 ; /// MPIF 3-wire SPI busy flag
    u32 reg_mpif_lc1a_busy            :1 ; /// MPIF Logical Channel 1a busy flag
    u32 reg_mpif_lc2a_busy            :1 ; /// MPIF Logical Channel 2a busy flag
    u32 reg_mpif_lc2b_busy            :1 ; /// MPIF Logical Channel 2b busy flag
    u32 reg_mpif_lc3a_busy            :1 ; /// MPIF Logical Channel 3a busy flag
    u32 reg_mpif_lc3b_busy            :1 ; /// MPIF Logical Channel 3b busy flag
    u32 reg_mpif_lc4a_busy            :1 ; /// MPIF Logical Channel 4a busy flag
    u32 :24; /// [0x2B]
    /* [0x2C] */
    u32 reg_mpif_int_enable           :15; /// MPIF Interrupt event enable
                                           /// [0]: 4-wire SPI trx done
                                           /// [1]: 3-wire SPI trx done
                                           /// [2]: Logical Channel 1a trx done
                                           /// [3]: Logical Channel 2a trx done
                                           /// [4]: Logical Channel 2b trx done
                                           /// [5]: Logical Channel 3a trx done
                                           /// [6]: Logical Channel 3b trx done
                                           /// [7]: Logical Channel 4a trx done
                                           /// [8]: Logical Channel 2a trx error
                                           /// [9]: Logical Channel 2b trx error
                                           /// [10]: Logical Channel 3a trx error
                                           /// [11]: Logical Channel 3b trx error
                                           /// [12]: Logical Channel 4a trx error
                                           /// [13]: Busy time out
                                           /// [14]: Slave request
    u32 :17; /// [0x2C]
    /* [0x2D] */
    u32 reg_mpif_4wspi_done           :1 ; /// 4-wire SPI trx done
    u32 reg_mpif_3wspi_done           :1 ; /// 3-wire SPI trx done
    u32 reg_mpif_lc1a_done            :1 ; /// Logical Channel 1a trx done
    u32 reg_mpif_lc2a_done            :1 ; /// Logical Channel 2a trx done
    u32 reg_mpif_lc2b_done            :1 ; /// Logical Channel 2b trx done
    u32 reg_mpif_lc3a_done            :1 ; /// Logical Channel 3a trx done
    u32 reg_mpif_lc3b_done            :1 ; /// Logical Channel 3b trx done
    u32 reg_mpif_lc4a_done            :1 ; /// Logical Channel 4a trx done
    u32 reg_mpif_lc2a_err             :1 ; /// Logical Channel 2a trx error
    u32 reg_mpif_lc2b_err             :1 ; /// Logical Channel 2b trx error
    u32 reg_mpif_lc3a_err             :1 ; /// Logical Channel 3a trx error
    u32 reg_mpif_lc3b_err             :1 ; /// Logical Channel 3b trx error
    u32 reg_mpif_lc4a_err             :1 ; /// Logical Channel 4a trx error
    u32 reg_mpif_busy_timeout         :1 ; /// MPIF busy time out
    u32 reg_mpif_slave_req            :1 ; /// Slave request
    u32 :17; /// [0x2D]
    /* [0x2E] */
    u32 reg_mpif_timeout              :16; /// MPIF wait time limit for busy de-assert
    u32 :16; /// [0x2E]
    /* [0x2F] */
    u32 reg_sts_busy_to               :16; /// Busy time out status
                                           /// [4:0]: command id
                                           ///   "00000" - MPIF_1A_R
                                           ///   "00001" - MPIF_1A_W
                                           ///   "00010" - MPIF_2A_R
                                           ///   "00011" - MPIF_2A_W
                                           ///   "00100" - MPIF_2A_RC
                                           ///   "00101" - MPIF_2A_WC
                                           ///   "00110" - MPIF_2B_R
                                           ///   "00111" - MPIF_2B_W
                                           ///   "01000" - MPIF_2B_RC
                                           ///   "01001" - MPIF_2B_WC
                                           ///   "01010" - MPIF_3A_R
                                           ///   "01011" - MPIF_3A_W
                                           ///   "01100" - MPIF_3A_RC
                                           ///   "01101" - MPIF_3A_WC
                                           ///   "01110" - MPIF_3B_R
                                           ///   "01111" - MPIF_3B_W
                                           ///   "10000" - MPIF_3B_RC
                                           ///   "10001" - MPIF_3B_WC
                                           ///   "10010" - MPIF_4A_R
                                           ///   "10011" - MPIF_4A_W
                                           /// [9:8]: slave id
    u32 :16; /// [0x2F]
    /* [0x30] */
    u32 reg_mpif_swrstn               :1 ; /// MPIF software reset, active low
    u32 :1 ; /// [0x30]
    u32 reg_mpif_tr_cycle             :2 ; /// MPIF read/write turn around cycle (MSB=h31.[3])
                                           /// 0: 0T
                                           /// 1: 1T
                                           /// 2: 2T
                                           /// 3: 3T
                                           /// 4: 4T
                                           /// 5: 5T
                                           /// 6: 6T
                                           /// 7: 7T
    u32 reg_mpif_wait_cycle           :2 ; /// MPIF wait ACK/NAK cycle
                                           /// 0: 0T
                                           /// 1: 1T
                                           /// 2: 2T
                                           /// 3: 3T
    u32 reg_mpif_slv0_dw              :2 ; /// Slave 0 data width
                                           /// 0: 1
                                           /// 1: 2
                                           /// 2: 4
                                           /// 3: 8
    u32 reg_mpif_slv1_dw              :2 ; /// Slave 1 data width
                                           /// 0: 1
                                           /// 1: 2
                                           /// 2: 4
                                           /// 3: 8
    u32 reg_mpif_slv2_dw              :2 ; /// Slave 2 data width
                                           /// 0: 1
                                           /// 1: 2
                                           /// 2: 4
                                           /// 3: 8
    u32 reg_mpif_slv3_dw              :2 ; /// Slave 3 data width
                                           /// 0: 1
                                           /// 1: 2
                                           /// 2: 4
                                           /// 3: 8
    u32 reg_mpif_cmd_dw               :2 ; /// Slave 3 data width
                                           /// 0: 1
                                           /// 1: 2
                                           /// 2: 4
                                           /// 3: 8
    u32 :16; /// [0x30]
    /* [0x31] */
    u32 reg_mpif_wwtr_cycle           :3 ; /// MPIF write/write turn around cycle for LC3A/LC3B/LC4A
                                           /// 0: 0T
                                           /// 1: 1T
                                           /// 2: 2T
                                           /// 3: 3T
                                           /// 4: 4T
                                           /// 5: 5T
                                           /// 6: 6T
                                           /// 7: 7T
    u32 reg_mpif_tr_cycle_b2          :1 ; /// MPIF read/write turn around cycle MSB bit
    u32 :1 ; /// [0x31]
    u32 reg_clr_lc2x_errcnt           :1 ; /// Clear Logical Channel 2A/2B error counter
    u32 reg_clr_lc3x_errcnt           :1 ; /// Clear Logical Channel 3A/3B error counter
    u32 reg_clr_lc4x_errcnt           :1 ; /// Clear Logical Channel 4A error counter
    u32 reg_mpif_miu_pri0             :1 ; /// MPIF MIU interface 0 priority
    u32 reg_mpif_miu_pri1             :1 ; /// MPIF MIU interface 1 priority
    u32 reg_mpif_miu_w4wlast_done     :1 ; /// reg_mpif_miu_w4wlast_done
    u32 :1 ; /// [0x31]
    u32 reg_mpif_extrdcmd_cycle       :3 ; /// MPIF RX command state extend cycle
    u32 reg_lc3x_nochk_tog_en         :1 ; /// Enable LC3X_NOCHK toggle bit enable
    u32 :16; /// [0x31]
    /* [0x32] */
    u32 reg_rx_fb_on                  :1 ; /// MPIF RX via Feedback path
    u32 reg_sync_8b                   :1 ; /// MPIF RX via Feedback path sync boundary
                                           /// 0: 4 byte boundary
                                           /// 1: 8 byte boundary
    u32 reg_mpif_bsy_sync_en          :1 ; /// MPIF Busy Sync Enable
    u32 reg_mpif_bypass_dly           :1 ; /// MPIF Bypass delay chain
    u32 reg_clk_dly                   :4 ; /// PIF_CLK delay selection
    u32 reg_csn_dly                   :4 ; /// PIF_CSN delay selection
    u32 reg_di0_dly                   :4 ; /// PIF_DI0 delay selection
    u32 :16; /// [0x32]
    /* [0x33] */
    u32 reg_mpif_sync_len             :3 ; /// MPIF Sync pattern length
                                           /// 0: 1 bit
                                           /// ??
                                           /// 7: 8 bits
    u32 :5 ; /// [0x33]
    u32 reg_mpif_sync_pat             :8 ; /// MPIF Sync pattern, LSB first
    u32 :16; /// [0x33]
    /* [0x34] */
    u32 reg_sts_spi_ucplt_trx_len     :16; /// MPIF SPI transmit/receive un-complete data length
    u32 :16; /// [0x34]
    /* [0x35] */
    u32 reg_mpif_miu_mask_wr          :1 ; /// MPIF MIU write request mask
    u32 reg_mpif_miuwr_clr_ob         :1 ; /// Clear MIU write out of range status
    u32 reg_mpif_dummy_write_en       :1 ; /// MPIF MIU dummy write enable
    u32 reg_mpif_dummy_wr_len         :1 ; /// MPIF MIU dummy write length
                                           /// 0: 2
                                           /// 1: 4
    u32 :4 ; /// [0x35]
    u32 reg_sts_miuwr_ob              :1 ; /// MPIF MIU write address out of range
    u32 :23; /// [0x35]
    /* [0x36] */
    u32 reg_mpif_miu_adr_lb_0         :16; /// MPIF MIU write address lower bound
    u32 :16; /// [0x36]
    u32 reg_mpif_miu_adr_lb_1         :16; /// @see reg_mpif_miu_adr_lb_0
    u32 :16; /// [0x37]
    /* [0x38] */
    u32 reg_mpif_miu_adr_ub_0         :16; /// MPIF MIU write address upper bound
    u32 :16; /// [0x38]
    u32 reg_mpif_miu_adr_ub_1         :16; /// @see reg_mpif_miu_adr_ub_0
    u32 :16; /// [0x39]
    /* [0x3A] */
    u32 reg_mpif_d_gpo_en             :4 ; /// MPIF data pins uased as GPO enable
    u32 reg_mpif_d_gpo                :4 ; /// MPIF data pins uased as GPO value
    u32 reg_mpif_cs_gpo_en            :4 ; /// MPIF cs pins uased as GPO enable
    u32 reg_mpif_cs_gpo               :4 ; /// MPIF cs pins uased as GPO value
    u32 :16; /// [0x3A]
    /* [0x3B] */
    u32 reg_mpif_throttle_rate        :2 ; /// MPIF clock throttle rate
                                           /// 0: 0 cycle
                                           /// 1: 1 cycle
                                           /// 2: 2 cycle
                                           /// 3: 3 cycle
    u32 :2 ; /// [0x3B]
    u32 reg_mpif_throttle_size        :2 ; /// MPIF clock throttle boundary in data phase
                                           /// 0: 4 bytes boundary
                                           /// 1: 8 bytes boundary
                                           /// 2: 16 bytes boundary
                                           /// 3: 32 bytes boundary
    u32 :26; /// [0x3B]
    u32 :32; /// [0x3C]
    u32 :32; /// [0x3D]
    /* [0x3E] */
    u32 reg_mpif_spare_0              :16; /// MPIF spare registers
    u32 :16; /// [0x3E]
    u32 reg_mpif_spare_1              :16; /// @see reg_mpif_spare_0
    u32 :16; /// [0x3F]
    /* [0x40] */
    u32 reg_mpif_dbgsel               :3 ; /// Debug probe selection:
                                           /// 0: dbg_if_ctrl0
                                           /// 1: dbg_if_ctrl1
                                           /// 2: dbg_if_ctrl2
                                           /// 3: dbg_if_ctrl3
                                           /// 4: dbg_ch_ctrl
                                           /// 5: dbg_buf_ctrl
                                           /// 6: dbg_mif
                                           /// 7: dbg_rxif_ctrl
    u32 reg_mpif_dbg_en               :1 ; /// enable mpif dbg bus
    u32 :28; /// [0x40]
    /* [0x41] */
    u32 reg_sts_chkcrc_0              :16; /// Checksum/CRC
    u32 :16; /// [0x41]
    u32 reg_sts_chkcrc_1              :16; /// @see reg_sts_chkcrc_0
    u32 :16; /// [0x42]
    /* [0x43] */
    u32 reg_sts_if_ctrl0              :16; /// MPIF_IF_Ctrl status 1:
                                           /// [15:11]: cur_cmd
                                           /// [10:6]: if_state
                                           /// [5]: mpif_busy_err
                                           /// [4]: byte_end
                                           /// [3]: pkt0_cmd_done
                                           /// [2]: pkt1_cmd_done
                                           /// [1]: stm0_cmd_done
                                           /// [0]: stm0_cmdlast
    u32 :16; /// [0x43]
    /* [0x44] */
    u32 reg_sts_if_ctrl1              :16; /// MPIF_IF_Ctrl status 2:
                                           /// [15:6]: byte_cnt
                                           /// [5:4]: 2'b0
                                           /// [3:0]: bit_cnt
                                           /// 
    u32 :16; /// [0x44]
    /* [0x45] */
    u32 reg_sts_pkt3a_cnt             :16; /// Logical Channel 3A packet down counter
    u32 :16; /// [0x45]
    /* [0x46] */
    u32 reg_sts_pkt3b_cnt             :16; /// Logical Channel 3B packet down counter
    u32 :16; /// [0x46]
    /* [0x47] */
    u32 reg_sts_stm0_cnt              :16; /// Logical Channel 4A stream down counter
    u32 :16; /// [0x47]
    /* [0x48] */
    u32 reg_sts_lc2x_errcnt           :16; /// Logical Channel 2A/2B error count accumulator
    u32 :16; /// [0x48]
    /* [0x49] */
    u32 reg_sts_lc3x_errcnt           :16; /// Logical Channel 3A/3B error count accumulator
    u32 :16; /// [0x49]
    /* [0x4A] */
    u32 reg_sts_lc4x_errcnt           :16; /// Logical Channel 4A error count accumulator
    u32 :16; /// [0x4A]
    /* [0x4B] */
    u32 reg_m2i_bistfail              :1 ; /// TX fifo (mi2mpif_buf) bist test indicator
    u32 reg_i2m_bistfail              :1 ; /// RX fifo (mpif2mi_buf) bist test indicator
    u32 :30; /// [0x4B]
    /* [0x4C] */
    u32 reg_mpif_miu_mask_rd          :1 ; /// MPIF MIU read request mask
    u32 :31; /// [0x4C]
    /* [0x4D] */
    u32 reg_mpif2mi_sel_bit           :3 ; /// mpif2mi_sel setting
                                           /// 0: mpif2mi_sel  from [25]  (256MB)
                                           /// 1: mpif2mi_sel  from [24]  (128MB)
                                           /// 2: mpif2mi_sel  from [23]  (64MB) 
                                           /// 3: mpif2mi_sel  from [22]  (32MB)
                                           /// 4: mpif2mi_sel  from [21]  (16MB)
                                           /// 5: mpif2mi_sel  from [20]  (8MB)
                                           /// 6: mpif2mi_sel  from [19]  (4MB)
                                           /// 7: mpif2mi_sel  from [18]  (2MB)
    u32 reg_mpif_clk_gpo_en           :1 ; /// MPIF clk pins uased as GPO enable
    u32 reg_mpif_clk_gpo              :1 ; /// MPIF clk pins uased as GPO value
    u32 reg_mpif_lastdonez            :1 ; /// MPIF lastdonez value
    u32 :26; /// [0x4D]
    /* [0x4E] */
    u32 reg_clk_mpif_src_bypass_dly   :1 ; /// bypass clk_mpif delay
    u32 reg_clk_mpif_src_dly          :3 ; /// clk_mpif delay selection
    u32 reg_mpif_dynamic_gate_en      :1 ; /// MPIF dynamic clock gating enable
    u32 reg_mpif_dynamic_clk_mpif_en  :1 ; /// MPIF dynamic clk_mpif gating enable
    u32 reg_mpif_dynamic_clk_miu_en   :1 ; /// MPIF dynamic clk_miu gating enable
} KeMpif_t;

extern volatile KeMpif_t   * const g_ptKeMpif;

#endif /*__KERNEL_MPIF_H__*/
