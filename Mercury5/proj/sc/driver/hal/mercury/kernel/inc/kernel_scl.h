#ifndef __KERNEL_SCL_H__
#define __KERNEL_SCL_H__

/************************************************/
/* SCL Register Banks                           */
/************************************************/

typedef struct KeSc_s
{
    /* [0x00] */
    u32 :32; /// [0x00]
    /* [0x01] */
    u32 reg_sw_rst                    :1 ; /// Software reset, set ¡§1¡¨  to reset
    u32 reg_bypass_vsc                :1 ; /// Bypass Vertical scaling
    u32 reg_sc_dynamic_gating_en      :1 ; /// Enable dynamic clock gating for clk_sc
    u32 :29; /// [0x01]
    /* [0x02] */
    u32 reg_hsd_dst_hsize             :12; /// hsd_dst_hsize is HSD output pixel number -1
                                           /// 
    u32 :20; /// [0x02]
    /* [0x03] */
    u32 reg_hsc_dst_hsize             :12; /// hsc_dst_hsize is horizontal output pixel number -1
                                           /// 
    u32 :20; /// [0x03]
    /* [0x04] */
    u32 reg_vsc_dst_vsize             :12; /// vsc_dst_hsize is vertical output line number -1
                                           /// 
    u32 :20; /// [0x04]
    /* [0x05] */
    u32 reg_h_ini_fac_0               :16; /// Horizontal initial factor (s.20)
    u32 :16; /// [0x05]
    u32 reg_h_ini_fac_1               :5 ; /// @see reg_h_ini_fac_0
    u32 :27; /// [0x06]
    /* [0x07] */
    u32 reg_h_scl_fac_0               :16; /// Horizontal scaling factor (4.20)
    u32 :16; /// [0x07]
    u32 reg_h_scl_fac_1               :8 ; /// @see reg_h_scl_fac_0
    u32 :24; /// [0x08]
    /* [0x09] */
    u32 reg_v_ini_fac_0               :16; /// Vertical initial factor (s.20)
    u32 :16; /// [0x09]
    u32 reg_v_ini_fac_1               :5 ; /// @see reg_v_ini_fac_0
    u32 :27; /// [0x0A]
    /* [0x0B] */
    u32 reg_v_scl_fac_0               :16; /// Vertical scaling factor (4.20)
    u32 :16; /// [0x0B]
    u32 reg_v_scl_fac_1               :8 ; /// @see reg_v_scl_fac_0
    u32 :24; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    u32 :32; /// [0x0F]
    u32 :32; /// [0x10]
    u32 :32; /// [0x11]
    u32 :32; /// [0x12]
    u32 :32; /// [0x13]
    u32 :32; /// [0x14]
    u32 :32; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    /* [0x18] */
    u32 reg_hsd_en                    :1 ; /// HSD filter enable 0:disable 1:enable
    u32 reg_hsd_mode                  :2 ; /// HSD decrease mode :
                                           /// 0: 2x
                                           /// 1: 4x
                                           /// 2: 8x
                                           /// 3:16x
    u32 :5 ; /// [0x18]
    u32 reg_hsd_ini_avg               :5 ; /// HSD initial shift pixel (-15 ~ +15)
    u32 :19; /// [0x18]
    /* [0x19] */
    u32 :7 ; /// [0x19]
    u32 reg_avg_shift_vfac            :1 ; /// Enable auto shift vertical scaling factor with vertical average
    u32 :3 ; /// [0x19]
    u32 reg_hsd_cr_load_ini           :1 ; /// HSD cr_load_ini : 
                                           /// 0: initial load cb
                                           /// 1: initial load cr
    u32 reg_hsc_422to444_mode         :2 ; /// HSC 422to444_mode mode :
                                           /// 0x: duplicate
                                           /// 2: center
                                           /// 3: YC co-sited
    u32 reg_hsc_cr_load_ini           :1 ; /// HSC cr_load_ini :  0: initial load cb 1: initial load cr
    u32 :17; /// [0x19]
    /* [0x1A] */
    u32 reg_line_avg                  :2 ; /// VSC line average mode
                                           /// 0: no average
                                           /// 1: 2 lines average
                                           /// 2: 4 lines average
                                           /// 3: 8 lines average
    u32 :6 ; /// [0x1A]
    u32 reg_vsc_ini_avg               :4 ; /// VSC initial shift line (-7 ~ +7)
    u32 :20; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    /* [0x1F] */
    u32 reg_sram_cg_en                :1 ; /// SRAM CG enable
    u32 reg_bist_fail                 :2 ; /// BIST fail indicator
    u32 :1 ; /// [0x1F]
    u32 reg_debug_sel                 :2 ; /// Debug select
    u32 reg_mask_bi_extra             :1 ; /// Enable masking duplicated write last line to LB at 2-tap filter mode
    u32 reg_clr_after_last_out        :1 ; /// Enable clear all blocks after last pixel output to next IP
    u32 reg_sc_done                   :4 ; /// SC done status
    u32 :20; /// [0x1F]
    /* [0x20] */
    u32 reg_dummy0                    :16; /// reg_dummy0
    u32 :16; /// [0x20]
    /* [0x21] */
    u32 reg_vsc_status0               :16; /// internal status for debug
    u32 :16; /// [0x21]
    /* [0x22] */
    u32 reg_vsc_status1               :16; /// internal status for debug
    u32 :16; /// [0x22]
    /* [0x23] */
    u32 reg_hsd_status                :16; /// internal status for debug
    u32 :16; /// [0x23]
    /* [0x24] */
    u32 reg_hsc_status                :16; /// internal status for debug                                         /// (shift_en1,shift_en2,shift_en3,hcoef2sram_req,pix_cnt[11:0])
} KeSc_t;

extern volatile KeSc_t * const g_ptKeSc;

typedef struct KeSclDma_s
{
    /* [0x00] */
    u32 reg_scldma_en                 :1 ; /// enable scaler dma
    u32 reg_soft_rst                  :1 ; /// enable scldma soft reset
    u32 reg_crop_en                   :1 ; /// enable crop
    u32 reg_dither_en                 :1 ; /// enable dither
    u32 reg_dither_rstth              :3 ; /// dither reset threshold
    u32 reg_force_drdy_th_en          :1 ; /// force data ready threshold
    u32 reg_drdy_th                   :5 ; /// data ready threshold
    u32 reg_lbwmode_en                :1 ; /// enable low bandwidth mode
    u32 :18; /// [0x00]
    /* [0x01] */
    u32 reg_crop_xstart               :12; /// crop x-axle start
    u32 :20; /// [0x01]
    /* [0x02] */
    u32 reg_crop_xend                 :12; /// crop x-axle end
    u32 :20; /// [0x02]
    /* [0x03] */
    u32 reg_crop_ystart               :12; /// crop y-axle start
    u32 :20; /// [0x03]
    /* [0x04] */
    u32 reg_crop_yend                 :12; /// crop y-axle end
    u32 :20; /// [0x04]
    /* [0x05] */
    u32 reg_out_mode                  :4 ; /// scldma output mode
                                           /// 0: RGB565
                                           /// 1: RGB888
                                           /// 2: A8
                                           /// 3: DYUV422(display YUV422)
                                           /// 4: HW420TF(MB tiled frame mode)
                                           /// 5: HW420TR(MB tiled row mode)
                                           /// 6: JPE422F(JPEG Enc. frame mode)
                                           /// 7: JPE422R (JPEG Enc. Row mode)
                                           /// 8: SW420F(software YUV420)
    u32 reg_rotate_mode               :2 ; /// scldma rotation mode
                                           /// 0: no rotation
                                           /// 1: 90 degree rotation
                                           /// 2: 180 degree rotation
                                           /// 3: 270 degree rotation
    u32 reg_mirror_mode               :1 ; /// scldma mirror mode
    u32 reg_uv_swap                   :1 ; /// scldma uv swap
    u32 reg_clk_gated_en              :3 ; /// reg_clk_gated_en
                                           /// 0: domain 0 clock gating enable
                                           /// 1: domain 1 clock gating enable
                                           /// 2: domain 2 clock gating enable
                                           /// set to 3'b111 to turn on power saving mode
    u32 reg_mreq_always_active        :1 ; /// reg_mreq_always_active
                                           /// 1: mreq_scldma = 1
                                           /// 0: mreq_scldma = dynamic gating (default)
    u32 :1 ; /// [0x05]
    u32 reg_mreq_aggressive           :1 ; /// Big5 new aggressive mreq algo
    u32 reg_display_en                :1 ; /// enable direct path to DISPLAY
    u32 reg_wrt_emi_en                :1 ; /// enable non-lbw mode miu_a write ctrl
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_burst_mode                :2 ; /// scldma miu A burst mode length
                                           /// 0: 4
                                           /// 1: 8
                                           /// 2: 16
    u32 reg_ringmode_en               :1 ; /// enable ringmode for out_mode 4, 6
    u32 reg_jpe_nonblock_en           :1 ; /// hw420,jpe422 ring row mode block
    u32 reg_mreq_perf                 :2 ; /// 0 : always pre1t
                                           /// 1 : wait cnt = 7 => pre14t
                                           /// 2: wait cnt = 15 => pre14t
    u32 reg_rowdone_bypass            :1 ; /// 0:bypass, 1:wait wrapper output
    u32 reg_framedone_bypass          :1 ; /// 0:bypass, 1:wait wrapper output
    u32 reg_ring_buffer_size          :8 ; /// reg_ring_buffer_size
                                           /// for JPE422, 8N unit
                                           /// for Tile H263I, 16N unit
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_pitch_y                   :15; /// y pitch, byte unit
    u32 :17; /// [0x07]
    /* [0x08] */
    u32 reg_pitch_c                   :12; /// c pitch, 4 byte ubit
    u32 :20; /// [0x08]
    /* [0x09] */
    u32 reg_badr0_y_0                 :16; /// base address of buffer0 y, byte unit
    u32 :16; /// [0x09]
    u32 reg_badr0_y_1                 :13; /// @see reg_badr0_y_0
    u32 :19; /// [0x0A]
    /* [0x0B] */
    u32 reg_badr0_cb_0                :16; /// base address of buffer0 cb, 4 byte unit
    u32 :16; /// [0x0B]
    u32 reg_badr0_cb_1                :11; /// @see reg_badr0_cb_0
    u32 :21; /// [0x0C]
    /* [0x0D] */
    u32 reg_badr0_cr_0                :16; /// base address of buffer0 cr, 4 byte unit
    u32 :16; /// [0x0D]
    u32 reg_badr0_cr_1                :11; /// @see reg_badr0_cr_0
    u32 :21; /// [0x0E]
    /* [0x0F] */
    u32 reg_badr1_y_0                 :16; /// base address of buffer1 y, byte unit
    u32 :16; /// [0x0F]
    u32 reg_badr1_y_1                 :13; /// @see reg_badr1_y_0
    u32 :19; /// [0x10]
    /* [0x11] */
    u32 reg_badr1_cb_0                :16; /// base address of buffer1 cb, 4 byte unit
    u32 :16; /// [0x11]
    u32 reg_badr1_cb_1                :11; /// @see reg_badr1_cb_0
    u32 :21; /// [0x12]
    /* [0x13] */
    u32 reg_badr1_cr_0                :16; /// base address of buffer1 cr, 4 byte unit
    u32 :16; /// [0x13]
    u32 reg_badr1_cr_1                :11; /// @see reg_badr1_cr_0
    u32 :21; /// [0x14]
    /* [0x15] */
    u32 reg_mwpri_th                  :10; /// wpriority timer threshold
    u32 :22; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    /* [0x18] */
    u32 reg_c_irq_mask                :16; /// interrup mask
    u32 :16; /// [0x18]
    /* [0x19] */
    u32 reg_c_irq_force               :16; /// interrup force
    u32 :16; /// [0x19]
    /* [0x1A] */
    u32 reg_c_irq_clr                 :16; /// interrup clear
    u32 :16; /// [0x1A]
    /* [0x1B] */
    u32 reg_irq_final_status          :16; /// interrup status - host side
                                           /// [0]: frame done
                                           /// [1]: row mode block done
                                           /// [2]: row mode vstart
                                           /// [3]: xmeetint, for debug
                                           /// [4]: vmeetint, for debug
    u32 :16; /// [0x1B]
    /* [0x1C] */
    u32 reg_irq_raw_status            :16; /// interrup status - client side
    u32 :16; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    /* [0x20] */
    u32 reg_debug_sel                 :8 ; /// debug data mux selet
    u32 :24; /// [0x20]
    /* [0x21] */
    u32 reg_debug_data_h              :16; /// debug data high word[7:0]
    u32 :16; /// [0x21]
    /* [0x22] */
    u32 reg_debug_data_l              :16; /// debug data low word[15:0]
    u32 :16; /// [0x22]
    /* [0x23] */
    u32 reg_dbg_xcntint_th            :4 ; /// threshold = 2^N, N = this reg
                                           /// if x direction byte cnt is a mulitple of  the threshold, issue INT for debug.
    u32 reg_dbg_ycntint_th            :4 ; /// threshold = 2^N, N = this reg
                                           /// if y direction line cnt is a mulitple of  the threshold, issue INT for debug.
    u32 reg_dbg_refclk_en             :1 ; /// enable toggle clk to gen ref clk in dbbus
    u32 reg_dbg_force_wd_en           :1 ; /// force scldma out wd to xcnt, ycnt
    u32 reg_dbg_force_mpath           :1 ; /// force scldma miu_path
    u32 reg_dbg_mreq_manuon           :1 ; /// turn on mreq_on manually
    u32 :20; /// [0x23]
    /* [0x24] */
    u32 reg_lbwbadr_y_0               :16; /// base address of lbw y, byte unit
    u32 :16; /// [0x24]
    u32 reg_lbwbadr_y_1               :13; /// @see reg_lbwbadr_y_0
    u32 :19; /// [0x25]
    /* [0x26] */
    u32 reg_lbwbadr_c_0               :16; /// base address of lbw c, 4 byte unit
    u32 :16; /// [0x26]
    u32 reg_lbwbadr_c_1               :11; /// @see reg_lbwbadr_c_0
    u32 :21; /// [0x27]
    /* [0x28] */
    u32 reg_burst_mode_miuifb         :2 ; /// scldma miu burst mode length (miuifb)
                                           /// 0: 4
                                           /// 1: 8
                                           /// 2: 16
    u32 reg_burst_mode_miuifc         :2 ; /// scldma miu burst mode length (miuifc)
                                           /// 0: 4
                                           /// 1: 8
                                           /// 2: 16
    u32 :28; /// [0x28]
    /* [0x29] */
    u32 reg_mrpri_th_miuifb           :10; /// rpriority timer threshold (miuifb)
    u32 :22; /// [0x29]
    /* [0x2A] */
    u32 reg_mwpri_th_miuifc           :10; /// wpriority timer threshold (miuifc)
    u32 :22; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_dummy0                    :16; /// dummy register
    u32 :16; /// [0x30]
    /* [0x31] */
    u32 reg_dummy1                    :16; /// dummy register
} KeSclDma_t;

extern volatile KeSclDma_t * const g_ptKeSclDma;

typedef struct KeDynScl_s
{
    /* [0x00] */
    u32 :32; /// [0x00]
    /* [0x01] */
    u32 reg_ds_idx                    :4 ; /// Index of RDMA
                                           /// IDX F is to disable DS
    u32 :3 ; /// [0x01]
    u32 reg_ds_sw_trig                :1 ; /// Using SW to trig RDMA
    u32 reg_ds_en                     :1 ; /// Enable RDMA
    u32 :23; /// [0x01]
    /* [0x02] */
    u32 reg_idx_depth                 :12; /// The depth of specified idx (fetch number)
    u32 :20; /// [0x02]
    /* [0x03] */
    u32 reg_ds_trig_en                :8 ; /// Enable related signal to trig RDMA
                                           /// [7]:SW trigger enable
                                           /// [6:4]: reserved
                                           /// [3]: ISP fire trigger enable
                                           /// [2]: ICP done trigger enable
                                           /// [1]: SCLDMA done trigger enable
                                           /// [0]: JPE done trigger enable
    u32 :24; /// [0x03]
    /* [0x04] */
    u32 reg_ds_base_adr_0             :16; /// Base address of RDMA
    u32 :16; /// [0x04]
    u32 reg_ds_base_adr_1             :16; /// @see reg_ds_base_adr_0
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 :12; /// [0x06]
    u32 reg_idx_size                  :3 ; /// The size specified for every idx
                                           /// #h0: 16 
                                           /// #h1: 32
                                           /// #h2: 64
                                           /// #h3: 128
                                           /// #h4: 256
                                           /// #h5: 512
                                           /// #h6: 1024
                                           /// #h7: 2048
    u32 reg_req_pri                   :1 ; /// Priority of request
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_req_len                   :4 ; /// Lenth per request
                                           /// sould be 'h1~'h4 for 32-bit MIU
    u32 reg_req_th                    :4 ; /// Threshold to request
    u32 :24; /// [0x07]
    /* [0x08] */
    u32 reg_ds_riu_we                 :1 ; /// Write command to riu_bridge
    u32 :3 ; /// [0x08]
    u32 reg_ds_riu_be                 :2 ; /// Byte enable to riu_bridge
    u32 :26; /// [0x08]
    /* [0x09] */
    u32 reg_rstz_xiu                  :1 ; /// Reset in xiu domain, active high
    u32 reg_rstz_miu                  :1 ; /// Reset in miu domain, active high
    u32 :6 ; /// [0x09]
    u32 reg_en_clk_xiu                :1 ; /// Enable local clk_xiu

    u32 :3 ; /// [0x09]
    u32 reg_sram_gate_en              :1 ; /// Enable sram clock gating when no CE
    u32 :19; /// [0x09]
/*    	
    u32 :23; /// [0x09]
*/
    /* [0x0A] */
    u32 reg_ds_trig                   :8 ; /// Signal to trigger RDMA
                                           /// [7] SW trigger
                                           /// [6:0]External HW trigger
    u32 :24; /// [0x0A]
    u32 :32; /// [0x0B]
    u32 :32; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    /* [0x0F] */
    u32 reg_debug_sel                 :2 ; /// Debug out selection
    u32 :30; /// [0x0F]
    /* [0x10] */
    u32 reg_ds_int_sw                 :7 ; /// SW interrupt
    u32 reg_ds_int_hw                 :1 ; /// HW interrupt
    u32 reg_ds_int_mask_sw            :7 ; /// SW interrupt mask
    u32 reg_ds_int_mask_hw            :1 ; /// HW interrupt mask
    u32 :16; /// [0x10]
    u32 :32; /// [0x11]
    u32 :32; /// [0x12]
    u32 :32; /// [0x13]
    u32 :32; /// [0x14]
    u32 :32; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    u32 :32; /// [0x18]
    u32 :32; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    /* [0x20] */
    u32 :1 ; /// [0x20]
    u32 reg_mreq_always_active        :1 ; /// 1: mreq always active
                                           /// 0: mreq_dyn_scl control by SW or HW
    u32 :30; /// [0x20]
    u32 :32; /// [0x21]
    u32 :32; /// [0x22]
    u32 :32; /// [0x23]
    u32 :32; /// [0x24]
    u32 :32; /// [0x25]
    u32 :32; /// [0x26]
    u32 :32; /// [0x27]
    u32 :32; /// [0x28]
    u32 :32; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    u32 :32; /// [0x30]
    u32 :32; /// [0x31]
    u32 :32; /// [0x32]
    u32 :32; /// [0x33]
    u32 :32; /// [0x34]
    u32 :32; /// [0x35]
    u32 :32; /// [0x36]
    u32 :32; /// [0x37]
    u32 :32; /// [0x38]
    u32 :32; /// [0x39]
    u32 :32; /// [0x3A]
    u32 :32; /// [0x3B]
    u32 :32; /// [0x3C]
    u32 :32; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
    u32 :32; /// [0x40]
    u32 :32; /// [0x41]
    u32 :32; /// [0x42]
    u32 :32; /// [0x43]
    u32 :32; /// [0x44]
    u32 :32; /// [0x45]
    u32 :32; /// [0x46]
    u32 :32; /// [0x47]
    u32 :32; /// [0x48]
    u32 :32; /// [0x49]
    u32 :32; /// [0x4A]
    u32 :32; /// [0x4B]
    u32 :32; /// [0x4C]
    u32 :32; /// [0x4D]
    u32 :32; /// [0x4E]
    u32 :32; /// [0x4F]
    u32 :32; /// [0x50]
    u32 :32; /// [0x51]
    u32 :32; /// [0x52]
    u32 :32; /// [0x53]
    u32 :32; /// [0x54]
    u32 :32; /// [0x55]
    u32 :32; /// [0x56]
    u32 :32; /// [0x57]
    u32 :32; /// [0x58]
    u32 :32; /// [0x59]
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
    u32 :32; /// [0x70]
    u32 :32; /// [0x71]
    u32 :32; /// [0x72]
    u32 :32; /// [0x73]
    u32 :32; /// [0x74]
    u32 :32; /// [0x75]
    u32 :32; /// [0x76]
    u32 :32; /// [0x77]
    /* [0x78] */
    u32 reg_dummy                     :16; /// dummy register
} KeDynScl_t;

extern volatile KeDynScl_t * const g_ptKeDynScl;

#endif /*__KERNEL_SCL_H__*/
