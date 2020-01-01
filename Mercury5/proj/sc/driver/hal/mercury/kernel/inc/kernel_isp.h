#ifndef __KERNEL_ISP_H__
#define __KERNEL_ISP_H__

/************************************************/
/* RIU ISP (SENSOR_IF) Bank                     */
/************************************************/

typedef struct KeIsp_s
{
    /* [0x00] */
    u32 reg_sensor_vsync_polarity     :1 ; /// reg_sensor_vsync_polarity 
    u32 reg_sensor_hsync_polarity     :1 ; /// reg_sensor_hsync_polarity
    u32 reg_sensor_rgb_in             :1 ; /// reg_sensor_hsync_polarity
    u32 :29; /// [0x00]
    /* [0x01] */
    u32 reg_crop_start_x              :12; /// reg_crop_start_x 
    u32 :20; /// [0x01]
    /* [0x02] */
    u32 reg_crop_start_y              :12; /// reg_crop_start_y
    u32 :20; /// [0x02]
    /* [0x03] */
    u32 reg_crop_width                :12; /// reg_crop_width 
    u32 :20; /// [0x03]
    /* [0x04] */
    u32 reg_crop_high                 :12; /// reg_crop_high
    u32 :20; /// [0x04]
    /* [0x05] */
    u32 reg_isp_sensor_array          :2 ; /// reg_isp_sensor_array
    u32 :2 ; /// [0x05]
    u32 reg_isp_sensor_yuv_order      :1 ; /// reg_isp_sensor_yuv_order
    u32 :3 ; /// [0x05]
    u32 reg_skip_frame                :3 ; /// reg_skip_frame
    u32 :21; /// [0x05]
    /* [0x06] */
    u32 reg_sensor_if_reserve_0       :16; /// reserved as SW verification
                                           /// # [0]: always ack from post engine
                                           /// # [1]: choosing clk; 1: engine clock, 0: sensor_clk (pclk)
                                           /// # [2]: choosing SW SYNC signal when setting to 1
                                           /// # [3]: switching SW sensor_data when setting to 1
                                           /// # [4]: SW VSYNC
                                           /// # [5]: SW HSYNC
                                           /// # [6]: SW sensor_data[0]
                                           /// # [7]: SW sensor_data[1] 
                                           /// # [8]:  SW sensor_data[2]
                                           /// # [9]:  SW sensor_data[3]
                                           /// # [10]: SW sensor_data[4]
                                           /// #[11]:  SW sensor_data[5]
                                           /// #[12]:  SW sensor_data[6]
                                           /// #[13]:  SW sensor_data[7]
                                           /// #[14]:  SW sensor_data[8]
                                           /// #[15]:  SW sensor_data[9]
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_sensor_if_reserve_1       :16; /// reserved as SW verification
                                           /// # [0]: choosing SW sensor_if out data to post engine when setting to 1
                                           /// # [1]: reserved
                                           /// # [2]: reserved
                                           /// # [3]: reserved
                                           /// # [4]: Reserved
                                           /// # [5]: reserved
                                           /// # [6]: SW sensor_data[0]
                                           /// # [7]: SW sensor_data[1] 
                                           /// # [8]:  SW sensor_data[2]
                                           /// # [9]:  SW sensor_data[3]
                                           /// # [10]: SW sensor_data[4]
                                           /// #[11]:  SW sensor_data[5]
                                           /// #[12]:  SW sensor_data[6]
                                           /// #[13]:  SW sensor_data[7]
                                           /// #[14]:  SW sensor_data[8]
                                           /// #[15]:  SW sensor_data[9]
    u32 :16; /// [0x07]
    /* [0x08] */
    u32 reg_en_isp_clk_sensor_delay   :1 ; /// reg_en_isp_clk_sensor_delay
    u32 reg_isp_clk_sensor_delay      :2 ; /// reg_isp_clk_sensor_delay
    u32 reg_isp_clk_sensor_polarity   :1 ; /// reg_isp_clk_sensor_polarity
    u32 reg_isp_master_mode           :1 ; /// reg_isp_master_mode
    u32 :27; /// [0x08]
    /* [0x09] */
    u32 reg_c_irq_mask                :16; /// Interrupt Mask
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_c_irq_force               :16; /// Force Interrupt Enable
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_c_irq_clr                 :16; /// Interrupt Clear
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_irq_final_status          :16; /// Status of Interrupt on CPU side
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_irq_raw_status            :16; /// Status of Interrupt on IP side
                                           /// # [0]: ISP internal FIFO full
                                           /// # [1]: reserved
                                           /// # [2] reserved
                                           /// # [3] reserved
                                           /// # [4]: reserved
                                           /// # [5]: 
                                           /// # [6]: reserved
                                           /// # [7]: reserved
                                           /// # [8]: sensor_vsyn_isp
                                           /// # [9]: ~sensor_vsync_isp
                                           /// # [10]: reserved
                                           /// #[11]: reserved
                                           /// #[12]: sensor_vsync
                                           /// #[13]: ~sensor vsync
                                           /// #[14]: reserved
                                           /// #[15]: reserved
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_isp_sw_rst                :1 ; /// Software Reset for ISP
                                           /// # Low Active
                                           ///  ( single buffer register )
    u32 reg_sensor_sw_rst             :1 ; /// Software Reset for Sensor
                                           /// # Low Active
                                           ///  ( single buffer register )
    u32 :30; /// [0x0E]
    /* [0x0F] */
    u32 reg_pad_sr_pwr_dn             :1 ; /// Power Down Sensor
                                           /// # 1'b0: Disable
                                           /// # 1'b1: Power Down
                                           ///  ( single buffer register )
    u32 reg_pad_sr_rst                :1 ; /// Reset Sensor
                                           /// # 1'b0: Reset
                                           /// # 1'b1: No Reset
                                           ///  ( single buffer register )
    u32 reg_b3_fire_mode              :2 ; /// Fire mode
                                           /// # [0]: 1'b0: old (frame start)
                                           /// # [0]: 1'b1: new (frame end with delay)
                                           /// # [1]: 1'b1: new (frame end without delay)
                                           ///  ( single buffer register )
    u32 reg_b3_atv_fix                :1 ; /// ATV issue fix
                                           /// # 1'b0: old 
                                           /// # 1'b1: new (fix fifo full if h-total is less tham expect)
                                           ///  ( single buffer register )
    u32 :27; /// [0x0F]
    /* [0x10] */
    u32 reg_sen_m2s_sw_ctrl           :1 ; /// M2S Signal Control
                                           /// # 1'b0: by HW
                                           /// # 1'b1: by SW
                                           ///  ( single buffer register)
    u32 reg_sen_m2s_mode              :1 ; /// M2S mode.
                                           /// # 1'b1: OmniVision SIF.
                                           /// # 1'b0: Others.
                                           ///  ( single buffer register )
    u32 reg_sen_m2s_cmd_bl            :1 ; /// M2S burst command length.
                                           /// # 1'b0: length is 1.
                                           /// # 1'b1: length is 2.
                                           ///  ( single buffer register )
    u32 reg_sen_m2s_reg_adr_mode      :1 ; /// M2S Register Address Mode
                                           /// # 1'b0 : 8 bit mode
                                           /// # 1'b1 : 16 bit series mode
                                           ///  (single buffer register)
    u32 reserved                      :1 ; /// None
    u32 :9 ; /// [0x10]
    u32 reg_sda_i                     :1 ; /// M2S SDA Input
                                           ///  ( single buffer register )
    u32 reg_m2s_status                :1 ; /// M2S Status
                                           /// # 1'b0: Idle
                                           /// # 1'b1: Busy
                                           ///  ( single buffer register )
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_sen_m2s_cmd               :16; /// M2S command
                                           /// # [0]: 1: read, 0: write.
                                           /// # [7:1]: Slave address.
                                           /// # [15:8]: Register address for 8 bit mode / first register address for 16 bit series mode
                                           ///  ( single buffer register )
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_sen_m2s_rw_d              :16; /// M2S Write data.
                                           /// # [7:0]: The first byte of Write data.
                                           /// # [15:8]: The second byte of Write data.
                                           /// Not valid if reg_sen_m2s_cmd_bl is 0.
                                           ///  ( single buffer register )
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_sen_prescale              :10; /// Factor of division for generating M2S clock.
                                           /// Must be programmed less than SYSCLK /(4*M2S_frequency) ¡V 1
                                           ///  ( single buffer register )
    u32 :22; /// [0x13]
    /* [0x14] */
    u32 reg_sen_sw_scl_oen            :1 ; /// M2S scl control
                                           /// # 1'b0: scl low
                                           /// # 1'b1: scl high
    u32 reg_sen_sw_sda_oen            :1 ; /// M2S sda control
                                           /// # 1'b0: sda output low
                                           /// # 1'b1: sda input or sda output high
    u32 :30; /// [0x14]
    /* [0x15] */
    u32 reg_sen_rd                    :16; /// M2S Read data.
                                           /// # [7:0]: The first byte of Read data.
                                           /// # [15:8]: The second byte of Read data.
                                           /// Not valid if reg_sen_m2s_cmd_bl is 0.
                                           ///  ( single buffer register )
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_sen_m2s_2nd_reg_adr       :8 ; /// 2nd Register Address for 16 bit register address series mode
                                           ///  (single buffer)
    u32 :24; /// [0x16]
    /* [0x17] */
    u32 reg_spi_sensor                :1 ; /// SPI sensor
    u32 :31; /// [0x17]
    /* [0x18] */
    u32 reg_lsb_first                 :1 ; /// spi sensor lsb first
    u32 :31; /// [0x18]
    /* [0x19] */
    u32 reg_sensor_vsize              :10; /// sensor v size
    u32 :22; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    /* [0x20] */
    u32 reg_sensor_hsize              :10; /// sensor h size
} KeIsp_t;


extern volatile KeIsp_t   * const g_ptKeIsp;

#endif /*__KERNEL_ISP_H__*/
