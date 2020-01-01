#ifndef __KERNEL_ICP_H__
#define __KERNEL_ICP_H__

/************************************************/
/* RIU ICP Bank                                 */
/************************************************/

typedef struct KeIcp_s
{
    /* [0x00] */
    u32 reg_icp_src                   :1 ; /// ICP Source Select
                                           /// 0:From Sensor
                                           /// 1:From MIU
    u32 :1 ; /// [0x00]
    u32 reg_en_expand_yuv             :1 ; /// Enable Expand Input Luma, Chroma Active Range
                                           /// Luma: (16~235) to (0~255)
                                           /// Chroma: (16~240) to (0~255)
    u32 :6 ; /// [0x00]
    u32 reg_swap_src_rb               :1 ; /// Swap ICP Source Chroma/Luma 422
                                           /// 0 : RGB
                                           /// 1 : BGR
    u32 reg_swap_src_a_rgb            :1 ; /// Swap ICP Source Chroma/Luma 422
                                           /// 0 : ARGB
                                           /// 1 : RGBA
    u32 reg_swap_src_yc               :1 ; /// Swap ICP Source Chroma/Luma 422
                                           /// 0 : Y1VY0U
                                           /// 1 : VY1UY0
    u32 reg_swap_src_uv               :1 ; /// Swap ICP Source Chroma 
                                           /// 0 : Y1VY0U
                                           /// 1 : Y1UY0V
    u32 reg_swap_uv_cbcr              :1 ; /// Swap ICP Source Chroma Cb/Cr to U/V
                                           /// 0 : Cb/Cr
                                           /// 1 : U/V
    u32 :18; /// [0x00]
    /* [0x01] */
    u32 reg_en_icp                    :1 ; /// Enable ICP
    u32 reg_icp_sw_rst                :1 ; /// ICP Software Reset, High Active
    u32 reg_sensor_jpg                :1 ; /// Sensor jpeg mode
    u32 reg_en_row_mode               :1 ; /// enable row mode
    u32 reg_shot_frame                :4 ; /// Hardware auto disable ICP after shot # frames.
                                           /// #0000 : turn off auto disable ICP function.
    u32 reg_skip_frame                :3 ; /// Skip Frame. (skip frame / in every frame)
                                           /// 000 : No skip
                                           /// 001 : Always Skip
                                           /// 010 : 1 / 3
                                           /// 011 : 2 / 3
                                           /// 100 : 1 / 4
                                           /// 101 : 2 / 4
                                           /// 111 : 3 / 4
    u32 :21; /// [0x01]
    /* [0x02] */
    u32 reg_miu_auto_priority         :1 ; /// MIU automatic priority
                                           /// 0: disable
                                           /// 1: enable
    u32 reg_miu_vmq                   :1 ; /// MIU automatic row
                                           /// 0: disable
                                           /// 1: enable
    u32 reg_miu_auto_row              :1 ; /// MIU automatic row
                                           /// 0: disable (SW)
                                           /// 1: enable (HW auto)
    u32 reg_miu_vmq_mode              :1 ; /// MIU vmq mode
                                           /// 0: miu access number mode
                                           /// 1: line count mode
    u32 reg_wmiu_th                   :4 ; /// Write MIU Threshold (-1)
    u32 reg_wmiu_hth                  :4 ; /// Write MIU High Threshold (-1)
    u32 :2 ; /// [0x02]
    u32 reg_en_flex_burst             :1 ; /// The burst length will between wmiu_th to 16
    u32 reg_en_last_done_z            :1 ; /// Using last done signal
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_rmiu_th                   :4 ; /// Read MIU Threshold (-1), big5 only support {reg_rmiu_th[3:1], 1'b0}
    u32 :4 ; /// [0x03]
    u32 reg_rmiu_hth                  :4 ; /// Read MIU High Threshold (-1)
    u32 reg_yv12_imi_md               :1 ; /// YV12 bandwidth saving mode
    u32 :19; /// [0x03]
    /* [0x04] */
    u32 reg_src_hcnt                  :12; /// The Width of the Source Image in the unit of pixel (-1)
    u32 :20; /// [0x04]
    /* [0x05] */
    u32 reg_src_vcnt                  :12; /// The Hight of the Source Image in the unit of line (-1)
    u32 :20; /// [0x05]
    /* [0x06] */
    u32 reg_src_fmt                   :4 ; /// The source format
                                           /// 0: YUV422
                                           /// 1: YV12 (420)
                                           /// 2: NV12
                                           /// 3: RGB565
                                           /// 4: RGB888
                                           /// 5: ARGB8888 RGB
                                           /// 6: ARGB8888 A
                                           /// 7: A8
                                           /// 8: YV12 (422)
    u32 :28; /// [0x06]
    u32 :32; /// [0x07]
    u32 :32; /// [0x08]
    u32 :32; /// [0x09]
    u32 :32; /// [0x0A]
    /* [0x0B] */
    u32 reg_src_bufsize               :12; /// The Buffer size of Source Image
    u32 :20; /// [0x0B]
    /* [0x0C] */
    u32 reg_src_miu_fire              :1 ; /// The fire signal to get source
    u32 reg_src_buf_fire              :1 ; /// The fire signal to get buf
    u32 reg_src_adc                   :1 ; /// YV12 bandwidth saving mode
    u32 reg_sw_vsync                  :1 ; /// The software vsync for src from sensor
    u32 :28; /// [0x0C]
    u32 :32; /// [0x0D]
    /* [0x0E] */
    u32 reg_vmq_bufsize_0             :16; /// The size of virtual memory queue 
                                           /// (unit 2byte) (miu access number mode)
                                           /// (unit line) (line count mode)
    u32 :16; /// [0x0E]
    u32 reg_vmq_bufsize_1             :12; /// @see reg_vmq_bufsize_0
    u32 :20; /// [0x0F]
    /* [0x10] */
    u32 reg_src_base0_0               :16; /// Source Packet YUV Base 0 Address of ICP
                                           /// Source Planer Y Base
                                           /// Source RGB565 Base
                                           /// Source RGB888 Base
                                           /// (pixel alignment) (unit byte)
                                           /// VMQ Base
                                           /// (2byte alignment)
    u32 :16; /// [0x10]
    u32 reg_src_base0_1               :13; /// @see reg_src_base0_0
    u32 :19; /// [0x11]
    /* [0x12] */
    u32 reg_src_base1_0               :16; /// Source Packet YUV Base 1 Address of ICP
                                           /// Source Planer UV Base
                                           /// Source Planer U Base
                                           /// (pixel alignment) (unit byte)
    u32 :16; /// [0x12]
    u32 reg_src_base1_1               :13; /// @see reg_src_base1_0
    u32 :19; /// [0x13]
    /* [0x14] */
    u32 reg_src_base2_0               :16; /// Source Planer V Base
                                           /// (pixel alignment) (unit byte)
    u32 :16; /// [0x14]
    u32 reg_src_base2_1               :13; /// @see reg_src_base2_0
    u32 :19; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    /* [0x18] */
    u32 reg_src_pitch0                :14; /// The Pitch of the Source Packet YUV 0
                                           /// The Pitch of the Source Planer Y
                                           /// (pixel alignment) (unit: byte)
                                           /// The Pitch of VMQ
                                           /// (2byte alignment)
    u32 :18; /// [0x18]
    /* [0x19] */
    u32 reg_src_pitch1                :14; /// The Pitch of the Source Packet YUV 1
                                           /// The Pitch of the Source Planer UV
                                           /// The Pitch of the Source Planer U
                                           /// (pixel alignment) (unit: byte)
    u32 :18; /// [0x19]
    /* [0x1A] */
    u32 reg_src_pitch2                :14; /// The Pitch of the Source Planer V
                                           /// (pixel alignment) (unit: byte)
    u32 :18; /// [0x1A]
    /* [0x1B] */
    u32 reg_icp_dummy_0               :16; /// The Pitch of the Source Planer V
                                           /// (pixel alignment) (unit: byte)
    u32 :16; /// [0x1B]
    u32 reg_icp_dummy_1               :16; /// @see reg_icp_dummy_0
    u32 :16; /// [0x1C]
    /* [0x1D] */
    u32 reg_r_priority_ctrl           :12; /// read priority control
    u32 :20; /// [0x1D]
    u32 :32; /// [0x1E]
    /* [0x1F] */
    u32 reg_hsync_adj                 :8 ; /// hsync adjustment
    u32 :4 ; /// [0x1F]
    u32 reg_fire_wffclr_dy            :1 ; /// isp fire wfifo clear delay
    u32 reg_hsync_wffclr_dy           :1 ; /// hsync wfifo clear delay
    u32 :18; /// [0x1F]
    /* [0x20] */
    u32 reg_rot0_base0_0              :16; /// Rotation :
                                           /// Destination Planer Y Base
                                           /// Destination RGB565 Base
                                           /// Destination YUV422 Base
                                           /// (2-byte alignment) 
    u32 :16; /// [0x20]
    u32 reg_rot0_base0_1              :13; /// @see reg_rot0_base0_0
    u32 :19; /// [0x21]
    /* [0x22] */
    u32 reg_rot0_base1_0              :16; /// Rotation :
                                           /// Destination Planer U Base
                                           /// Destination YV12-420 IMI mode V Base
                                           /// (2-byte alignment) 
    u32 :16; /// [0x22]
    u32 reg_rot0_base1_1              :13; /// @see reg_rot0_base1_0
    u32 :19; /// [0x23]
    /* [0x24] */
    u32 reg_rot0_base2_0              :16; /// Rotation :
                                           /// Destination Planer V Base
                                           /// Destination YV12-420 IMI mode U Base
                                           /// (2-byte alignment) 
    u32 :16; /// [0x24]
    u32 reg_rot0_base2_1              :13; /// @see reg_rot0_base2_0
    u32 :19; /// [0x25]
    /* [0x26] */
    u32 reg_rot0_pitch0               :14; /// Rotation :
                                           /// The pitch of reg_rot_base0
                                           /// (2-byte alignment) 
    u32 :18; /// [0x26]
    /* [0x27] */
    u32 reg_rot0_pitch1               :14; /// Rotation :
                                           /// The pitch of reg_rot_base1
                                           /// (2-byte alignment) 
    u32 :18; /// [0x27]
    /* [0x28] */
    u32 reg_rot0_pitch2               :14; /// Rotation :
                                           /// The pitch of reg_rot_base2
                                           /// (2-byte alignment) 
    u32 :18; /// [0x28]
    u32 :32; /// [0x29]
    /* [0x2A] */
    u32 reg_icp_rot                   :2 ; /// 2'b00 : rotate    0 degrees
                                           /// 2'b01 : rotate   90 degrees
                                           /// 2'b10 : rotate 180 degrees
                                           /// 2'b11 : rotate 270 degrees
    u32 reg_icp_brstlen               :2 ; /// retate fifo burst length 4, 8, 16
    u32 reg_swap_rot_src_yc           :1 ; /// Swap ICP Source Chroma/Luma 422
                                           /// 0 : Y1VY0U
                                           /// 1 : VY1UY0
    u32 :27; /// [0x2A]
    /* [0x2B] */
    u32 reg_imi_auto_priority         :1 ; /// IMI auto priority
    u32 reg_imi_priority_ctrl         :12; /// IMI priority control
    u32 :19; /// [0x2B]
    /* [0x2C] */
    u32 reg_rot_dummy_0               :16; /// reg_rot_dummy
    u32 :16; /// [0x2C]
    u32 reg_rot_dummy_1               :16; /// @see reg_rot_dummy_0
    u32 :16; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_rot1_base0_0              :16; /// Rotation : for pinpon
                                           /// Destination Planer Y Base
                                           /// Destination RGB565 Base
                                           /// Destination YUV422 Base
                                           /// (2-byte alignment) 
    u32 :16; /// [0x30]
    u32 reg_rot1_base0_1              :13; /// @see reg_rot1_base0_0
    u32 :19; /// [0x31]
    /* [0x32] */
    u32 reg_rot1_base1_0              :16; /// Rotation : for pinpon
                                           /// Destination Planer U Base
                                           /// Destination YV12-420 IMI mode V Base
                                           /// (2-byte alignment) 
    u32 :16; /// [0x32]
    u32 reg_rot1_base1_1              :13; /// @see reg_rot1_base1_0
    u32 :19; /// [0x33]
    /* [0x34] */
    u32 reg_rot1_base2_0              :16; /// Rotation : for pinpon
                                           /// Destination Planer V Base
                                           /// Destination YV12-420 IMI mode U Base
                                           /// (2-byte alignment) 
    u32 :16; /// [0x34]
    u32 reg_rot1_base2_1              :13; /// @see reg_rot1_base2_0
    u32 :19; /// [0x35]
    /* [0x36] */
    u32 reg_rot1_pitch0               :14; /// Rotation : for pinpon
                                           /// The pitch of reg_rot_base0
                                           /// (2-byte alignment) 
    u32 :18; /// [0x36]
    /* [0x37] */
    u32 reg_rot1_pitch1               :14; /// Rotation : for pinpon
                                           /// The pitch of reg_rot_base1
                                           /// (2-byte alignment) 
    u32 :18; /// [0x37]
    /* [0x38] */
    u32 reg_rot1_pitch2               :14; /// Rotation : for pinpon
                                           /// The pitch of reg_rot_base2
                                           /// (2-byte alignment) 
    u32 :18; /// [0x38]
    u32 :32; /// [0x39]
    /* [0x3A] */
    u32 reg_rot_src_hcnt              :12; /// The Width of the Rotate Source Image in the unit of pixel (-1)
    u32 :20; /// [0x3A]
    /* [0x3B] */
    u32 reg_rot_src_vcnt              :12; /// The Hight of the Rotate Source Image in the unit of line (-1)
    u32 :20; /// [0x3B]
    u32 :32; /// [0x3C]
    u32 :32; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
    /* [0x40] */
    u32 reg_adr_remap_en              :1 ; /// address remapper enable
                                           /// 0:disable
                                           /// 1:enable
    u32 :3 ; /// [0x40]
    u32 reg_seg0_en                   :1 ; /// addr remap segment0 enable
                                           /// 0:disable
                                           /// 1:enable
    u32 reg_seg1_en                   :1 ; /// addr remap segment1 enable
                                           /// 0:disable
                                           /// 1:enable
    u32 reg_seg2_en                   :1 ; /// addr remap segment2 enable
                                           /// 0:disable
                                           /// 1:enable
    u32 reg_seg3_en                   :1 ; /// addr remap segment3 enable
                                           /// 0:disable
                                           /// 1:enable
    u32 :24; /// [0x40]
    u32 :32; /// [0x41]
    /* [0x42] */
    u32 reg_seg0_src_base_0           :16; /// addr remap segment0 source address (4-byte unit)
    u32 :16; /// [0x42]
    u32 reg_seg0_src_base_1           :14; /// @see reg_seg0_src_base_0
    u32 :18; /// [0x43]
    /* [0x44] */
    u32 reg_seg0_data_len_0           :16; /// addr remap segment0 data lenth (4-byte unit)
    u32 :16; /// [0x44]
    u32 reg_seg0_data_len_1           :5 ; /// @see reg_seg0_data_len_0
    u32 :27; /// [0x45]
    /* [0x46] */
    u32 reg_seg0_dst_base_0           :16; /// addr remap segment0 destionation address (4-byte unit)
    u32 :16; /// [0x46]
    u32 reg_seg0_dst_base_1           :14; /// @see reg_seg0_dst_base_0
    u32 :18; /// [0x47]
    /* [0x48] */
    u32 reg_seg1_src_base_0           :16; /// addr remap segment1 source address (4-byte unit)
    u32 :16; /// [0x48]
    u32 reg_seg1_src_base_1           :14; /// @see reg_seg1_src_base_0
    u32 :18; /// [0x49]
    /* [0x4A] */
    u32 reg_seg1_data_len_0           :16; /// addr remap segment1 data lenth (4-byte unit)
    u32 :16; /// [0x4A]
    u32 reg_seg1_data_len_1           :5 ; /// @see reg_seg1_data_len_0
    u32 :27; /// [0x4B]
    /* [0x4C] */
    u32 reg_seg1_dst_base_0           :16; /// addr remap segment1 destionation address (4-byte unit)
    u32 :16; /// [0x4C]
    u32 reg_seg1_dst_base_1           :14; /// @see reg_seg1_dst_base_0
    u32 :18; /// [0x4D]
    /* [0x4E] */
    u32 reg_seg2_src_base_0           :16; /// addr remap segment2 source address (4-byte unit)
    u32 :16; /// [0x4E]
    u32 reg_seg2_src_base_1           :14; /// @see reg_seg2_src_base_0
    u32 :18; /// [0x4F]
    /* [0x50] */
    u32 reg_seg2_data_len_0           :16; /// addr remap segment2 data lenth (4-byte unit)
    u32 :16; /// [0x50]
    u32 reg_seg2_data_len_1           :5 ; /// @see reg_seg2_data_len_0
    u32 :27; /// [0x51]
    /* [0x52] */
    u32 reg_seg2_dst_base_0           :16; /// addr remap segment2 destionation address (4-byte unit)
    u32 :16; /// [0x52]
    u32 reg_seg2_dst_base_1           :14; /// @see reg_seg2_dst_base_0
    u32 :18; /// [0x53]
    /* [0x54] */
    u32 reg_seg3_src_base_0           :16; /// addr remap segment3 source address (4-byte unit)
    u32 :16; /// [0x54]
    u32 reg_seg3_src_base_1           :14; /// @see reg_seg3_src_base_0
    u32 :18; /// [0x55]
    /* [0x56] */
    u32 reg_seg3_data_len_0           :16; /// addr remap segment3 data lenth (4-byte unit)
    u32 :16; /// [0x56]
    u32 reg_seg3_data_len_1           :5 ; /// @see reg_seg3_data_len_0
    u32 :27; /// [0x57]
    /* [0x58] */
    u32 reg_seg3_dst_base_0           :16; /// addr remap segment3 destionation address (4-byte unit)
    u32 :16; /// [0x58]
    u32 reg_seg3_dst_base_1           :14; /// @see reg_seg3_dst_base_0
    u32 :18; /// [0x59]
    u32 :32; /// [0x5A]
    u32 :32; /// [0x5B]
    u32 :32; /// [0x5C]
    u32 :32; /// [0x5D]
    u32 :32; /// [0x5E]
    u32 :32; /// [0x5F]
    u32 :32; /// [0x60]
    u32 :32; /// [0x61]
    u32 :32; /// [0x62]
    u32 :32; /// [0x63]
    u32 :32; /// [0x64]
    u32 :32; /// [0x65]
    u32 :32; /// [0x66]
    u32 :32; /// [0x67]
    u32 :32; /// [0x68]
    u32 :32; /// [0x69]
    u32 :32; /// [0x6A]
    u32 :32; /// [0x6B]
    u32 :32; /// [0x6C]
    u32 :32; /// [0x6D]
    u32 :32; /// [0x6E]
    u32 :32; /// [0x6F]
    /* [0x70] */
    u32 reg_icp_busy                  :1 ; /// ICP Status
    u32 :31; /// [0x70]
    /* [0x71] */
    u32 :8 ; /// [0x71]
    u32 reg_debug_sel                 :5 ; /// Hardwire Debug Signal Set Selector
    u32 :19; /// [0x71]
    /* [0x72] */
    u32 reg_icp_vcnt                  :12; /// ICP Internal Line Count
    u32 :20; /// [0x72]
    /* [0x73] */
    u32 reg_icp_debug_0               :16; /// ICP Debus Data
    u32 :16; /// [0x73]
    u32 reg_icp_debug_1               :8 ; /// @see reg_icp_debug_0
    u32 :24; /// [0x74]
    /* [0x75] */
    u32 reg_sensor_frame              :15; /// Sensor frame count
    u32 reg_clr_sensor_frame          :1 ; /// Clear sensor frame count
    u32 :16; /// [0x75]
    /* [0x76] */
    u32 reg_scl_frame                 :15; /// To SCL frame count
    u32 reg_clr_scl_frame             :1 ; /// Clear scaler frame count
    u32 :16; /// [0x76]
    /* [0x77] */
    u32 reg_sen_hcnt                  :12; /// ICP Sensor Pixel Count
    u32 :20; /// [0x77]
    /* [0x78] */
    u32 reg_c_irq_mask                :16; /// Interrupt Mask
    u32 :16; /// [0x78]
    /* [0x79] */
    u32 reg_c_irq_force               :16; /// Force Interrupt Enable
    u32 :16; /// [0x79]
    /* [0x7A] */
    u32 reg_c_irq_clr                 :16; /// Interrupt Clear
    u32 :16; /// [0x7A]
    /* [0x7B] */
    u32 reg_irq_final_status          :16; /// Status of Interrupt on CPU Side
    u32 :16; /// [0x7B]
    /* [0x7C] */
    u32 reg_irq_raw_status            :16; /// Status of Interrupt on IP Side
                                           /// [6] sensor vsync
                                           /// [7] to sensor fifo full
                                           /// [8] icp busy rising edge
                                           /// [9] icp busy falling edge
                                           /// [10] sensor hcnt is not right
                                           /// [11] icp disable frame
                                           /// [12] icp read finish from miu
                                           /// [13] vmq ==0 
                                           /// [14] icp clear buffer 1
                                           /// [15] icp clear buffer 0
    u32 :16; /// [0x7C]
    /* [0x7D] */
    u32 reg_blank_time                :9 ; /// clk_scl cycle blank time
    u32 :23; /// [0x7D]
    u32 :32; /// [0x7E]
    /* [0x7F] */
    u32 :11; /// [0x7F]
    u32 reg_mreq_icp_save             :2 ; /// 0: force mreq_icp=1
                                           /// 1: Turn on the vblank mreq_icp
                                           /// 2: Turn on the request mreq_icp
    u32 reg_clk_gating_sram           :1 ; /// Turn off the clock in ICP SRAM
    u32 reg_pwr_save                  :2 ; /// 0: Turn off the dynamic power saving
                                           /// 1: Turn on the hblank power saving
                                           /// 2: Turn on the vblank power saving
                                           /// 3: Turn on the h/v blank power saving
} KeIcp_t;


extern volatile KeIcp_t   * const g_ptKeIcp;

#endif /*__KERNEL_ICP_H__*/
