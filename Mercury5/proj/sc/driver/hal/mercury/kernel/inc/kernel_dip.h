#ifndef __KERNEL_DIP_H__
#define __KERNEL_DIP_H__

typedef struct KeDipHvsp_s
{
    // h00
    u32	reg00_dummy;
    // h01
    u32 reg_ini_factor_ho_l     : 16;
    u32                         : 16;
    // h02
    u32 reg_ini_factor_ho_h     : 4;
    u32                         : 28;
    // h03
    u32 reg_ini_factor_ve_l     : 16;
    u32                         : 16;
    // h04
    u32 reg_ini_factor_ve_h     : 8;
    u32                         : 24;
    // h05
    u32 reg05_dummy;
    // h06
    u32 reg06_dummy;
    // h07
    u32	reg_scale_factor_ho_l   : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_GET_FACTOR_H(src, target)   (((1<<20)/(target))*(src))
        #define DIP_SCL_FACTOR_HO_L_MASK            0xFFFF
        #define DIP_SCL_FACTOR_HO_L(x)              ((x) & DIP_SCL_FACTOR_HO_L_MASK)
        /*------------------------------------------------------------*/
    u32                         : 16;
    // h08
    u32 reg_scale_factor_ho_h   : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_FACTOR_HO_H_MASK            0x00FF
        #define DIP_SCL_FACTOR_HO_H(x)              (((x)>>16) & DIP_SCL_FACTOR_HO_H_MASK)
        /*------------------------------------------------------------*/
    u32 reg_scale_ho_en         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_H_SCALE_EN_MASK                 0x0001
        #define DIP_H_SCALE_SET_EN(x)               ((x) & DIP_H_SCALE_EN_MASK)
        #define DIP_H_SCALE_OFF                     0x00
        #define DIP_H_SCALE_EN                      0x01
        /*------------------------------------------------------------*/
    u32 reg_h_shift_mode_en     : 1;
    u32                         : 22;
    // h09
    u32 reg_scale_factor_ve_l   : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_GET_FACTOR_V(src, target)   (((1<<20)/(target))*(src))
        #define DIP_SCL_FACTOR_VE_L_MASK            0xFFFF
        #define DIP_SCL_FACTOR_VE_L(x)              ((x) & DIP_SCL_FACTOR_VE_L_MASK)
        /*------------------------------------------------------------*/
    u32                         : 16;
    // h0A
    u32 reg_scale_factor_ve_h   : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_FACTOR_VE_H_MASK            0x00FF
        #define DIP_SCL_FACTOR_VE_H(x)              (((x)>>16) & DIP_SCL_FACTOR_VE_H_MASK)
    u32 reg_scale_ve_en         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_V_SCALE_EN_MASK                 0x0001
        #define DIP_V_SCALE_SET_EN(x)               ((x) & DIP_V_SCALE_EN_MASK)
        #define DIP_V_SCALE_OFF                     0x00
        #define DIP_V_SCALE_EN                      0x01
        /*------------------------------------------------------------*/
    u32 reg_v_shift_mode_en     : 1;
    u32                         : 22;
    // h0B
    u32 reg_mode_y_ho           : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_Y_HO_MODE_BYPASS            0x00
        #define DIP_SCL_Y_HO_MODE_BILINEAR          0x01
        /*------------------------------------------------------------*/
    u32 reg_mode_c_ho           : 3;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_C_HO_MODE_BYPASS            0x00
        #define DIP_SCL_C_HO_MODE_BILINEAR          0x01
        #define DIP_SCL_C_HO_MODE_SRAM_TBL0         0x02
        #define DIP_SCL_C_HO_MODE_SRAM_TBL1         0x03
        /*------------------------------------------------------------*/
    u32 reg_c_ram_en_ho         : 1;
    u32 reg_c_ram_sel_ho        : 1;
    u32 reg_y_ram_en_ho         : 1;
    u32 reg_y_ram_sel_ho        : 1;
    u32 reg_mode_y_ve           : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_Y_VE_MODE_BYPASS            0x00
        #define DIP_SCL_Y_VE_MODE_BILINEAR          0x01
        /*------------------------------------------------------------*/
    u32 reg_mode_c_ve           : 3;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_C_VE_MODE_BYPASS            0x00
        #define DIP_SCL_C_VE_MODE_BILINEAR          0x01
        #define DIP_SCL_C_VE_MODE_SRAM_TBL0         0x02
        #define DIP_SCL_C_VE_MODE_SRAM_TBL1         0x03
        /*------------------------------------------------------------*/
    u32 reg_c_ram_en_ve         : 1;
    u32 reg_c_ram_sel_ve        : 1;
    u32 reg_y_ram_en_ve         : 1;
    u32 reg_y_ram_sel_ve        : 1;
    u32                         : 16;
    // h0C
    u32 reg_hsp_dith_en         : 1;
    u32 reg_vsp_dith_en         : 1;
    u32                         : 6;
    u32 reg_hsp_coring_en_c     : 1;
    u32 reg_hsp_coring_en_y     : 1;
    u32 reg_vsp_coring_en_c     : 1;
    u32 reg_vsp_coring_en_y     : 1;
    u32                         : 20;
    // h0D
    u32 reg_hsp_coring_th_c     : 8;
    u32 reg_hsp_coring_th_y     : 8;
    u32                         : 16;
    // h0E
    u32 reg_vsp_coring_th_c     : 8;
    u32 reg_vsp_coring_th_y     : 8;
    u32                         : 16;
    // h0F
    u32 reg_hsp_de_ring_w_ogain : 6;
    u32 reg_hsp_de_ring_th0     : 4;
    u32 reg_hsp_de_ring_w_ugain : 6;
    u32                         : 16;

    // h10
    u32 reg_hsp_de_ring_effect_mode : 2;
    u32 reg_hsp_de_ring_detect_mode : 2;
    u32 reg_hsp_de_ring_min_offset  : 4;
    u32 reg_hsp_de_ring_max_offset  : 4;
    u32 reg_hsp_de_ring_filter161_en : 1;
    u32                         : 19;
    // h11
    u32	reg11[2];
    // h13
    u32                         : 4;
    u32 reg_hsp_6tap_en         : 1;
    u32                         : 1;
    u32 reg_h_nl_en             : 1;
    u32                         : 1;
    u32 reg_h_nl_w0_lsb         : 1;
    u32 reg_h_nl_w1_lsb         : 1;
    u32 reg_h_nl_w2_lsb         : 1;
    u32 reg_h_nl_w0_lsb2        : 1;
    u32 reg_h_nl_w1_lsb2        : 1;
    u32 reg_h_nl_w2_lsb2        : 1;
    u32                         : 18;
    // h14
    u32 reg_h_nl_w0             : 8;
    u32 reg_h_nl_w1             : 8;
    u32                         : 16;
    // h15
    u32 reg_h_nl_w2             : 8;
    u32 reg_h_nl_d_ini          : 7;
    u32 reg_h_nl_s_ini          : 1;
    u32                         : 16;
    // h16
    u32 reg_h_nl_d0             : 8;
    u32 reg_h_nl_d1             : 8;
    u32                         : 16;
    // h17
    u32 reg17[9];

    // h20
    u32 reg_hsp_de_ring_weight_dps  : 8;
    u32                         : 24;
    // h21
    u32 reg21;
    // h22
    u32 reg_h_size              : 13;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_SRC_H_SIZE_MASK             0x1FFF
        #define DIP_SCL_SRC_H_SIZE(x)               ((x) & DIP_SCL_SRC_H_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                         : 19;
    // h23
    u32 reg_v_size              : 12;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_SRC_V_SIZE_MASK             0x0FFF
        #define DIP_SCL_SRC_V_SIZE(x)               ((x) & DIP_SCL_SRC_V_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                         : 20;
    // h24
    u32 reg_scl_h_size          : 13;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_DEST_H_SIZE_MASK            0x1FFF
        #define DIP_SCL_DEST_H_SIZE(x)              ((x) & DIP_SCL_DEST_H_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                         : 19;
    // h25
    u32 reg_scl_v_size          : 12;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_DEST_V_SIZE_MASK            0x0FFF
        #define DIP_SCL_DEST_V_SIZE(x)              ((x) & DIP_SCL_DEST_V_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                         : 20;
    // h26
    u32 reg_h_size_rpt          : 13;
    u32                         : 19;
    // h27
    u32 reg_v_size_rpt          : 12;
    u32                         : 20;
    // h28
    u32 reg_scl_h_size_rpt      : 13;
    u32                         : 19;
    // h29
    u32 reg_scl_v_size_rpt      : 12;
    u32                         : 20;
    // h2A
    u32 reg_debug_clr           : 1;
    u32                         : 31;
    // h2B
    u32	reg2B_dummy[22];
    // h41
    u32 reg_yram_rw_en          : 1;
    u32 reg_cram_rw_en          : 1;
    u32                         : 5;
    u32 reg_ram_cen             : 1;
    u32 reg_ram_w_pulse         : 1;
    u32 reg_ram_r_pulse         : 1;
    u32                         : 22;
    // h42
    u32 reg_ram_addr            : 8;
    u32                         : 24;
    // h43
    u32 reg_ram_wdata_48bit_0   : 16;
    u32                         : 16;
    // h44
    u32 reg_ram_wdata_48bit_1   : 16;
    u32                         : 16;
    // h45
    u32 reg_ram_wdata_48bit_2   : 16;
    u32                         : 16;
    // h46
    u32 reg_ram_rdata_48bit_0   : 16;
    u32                         : 16;
    // h47
    u32 reg_ram_rdata_48bit_1   : 16;
    u32                         : 16;
    // h48
    u32 reg_ram_rdata_48bit_2   : 16;
    u32                         : 16;
    // h49
    u32 reg_ram_wdata_12bit     : 12;
    u32                         : 20;
    // h4A
    u32	reg4A;
    // h4B
    u32 reg_ram_rdata_12bit     : 12;
    u32                         : 20;
    // h4C
    u32	reg4C[5];
    // h51
    u32 reg_pseudo_vclr_en      : 1;
    u32 reg_pseudo_vclr_no      : 2;
    u32                         : 29;
    // h52
    u32	reg52;
    // h53
    u32	                        : 8;
    u32 reg_hsp_de_ring_debug   : 1;
    u32                         : 23;
    // h54
    u32 reg_121_bi_alpha        : 6;
    u32                         : 1;
    u32 reg_121_bi_en           : 1;
    u32                         : 24;
    // h55
    u32 reg_3d_top_bot_en       : 1;
    u32 reg_3d_sbs_en           : 1;
    u32                         : 30;
    // h56
    u32	reg56[2];
    // h58
    u32 reg_dummy_0             : 16;
    u32                         : 16;
    // h59
    u32 reg_dummy_1             : 16;
    u32                         : 16;
    // h5A
    u32 reg_dummy_2             : 16;
    u32                         : 16;
    // h5B
    u32 reg_dummy_3             : 16;
    u32                         : 16;
    // h5C
    u32 reg_dummy_4             : 16;
    u32                         : 16;
    // h5D
    u32 reg_dummy_5             : 16;
    u32                         : 16;
    // h5E
    u32 reg_dummy_6             : 16;
    u32                         : 16;
    // h5F
    u32 reg_dummy_7             : 16;
    u32                         : 16;
    // h60
    u32	reg_bist_fail           : 16;
    u32                         : 16;
    // h61
    u32	reg61[15];
    // h70
    u32 reg_dip_hvsp_sw_rst     : 1;
    u32 reg_dip_hvsp_sel        : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SCL_HVSP_SEL_DWIN0              0x00
        #define DIP_SCL_HVSP_SEL_DWIN1              0x01
        #define DIP_SCL_HVSP_SEL_DIP                0x02
        #define DIP_SCL_HVSP_SEL_DISABLE            0x03
        /*------------------------------------------------------------*/
    u32                         : 12;
    u32 reg_dip_vs_dly          : 1;
    u32                         : 16;
    // h71
    u32 reg_vsync_delay_num     : 16;
    u32                         : 16;
} KeDipHvsp_t;

typedef struct KeDipTop_s
{
    // h00
    u32 reg00;
    // h01
    u32 reg_dip_hsd_dithen          : 1;
    u32 reg_dip_vsd_dithen          : 1;
    u32 reg_dip_vs_inv              : 1;
    u32                             : 1;
    u32 reg_dip_vsd_422             : 1;
    u32                             : 2;
    u32 reg_dip_vfac_sht            : 1;
    u32                             : 4;
    u32 reg_dip_hout_proc           : 1;
    u32 reg_dip_vout_proc           : 1;
    u32 reg_dip_hdmi_422_in         : 1;
    u32                             : 17;
    // h02
    u32 reg_dip_hfac_ini_l          : 16;
    u32                             : 16;
    // h03
    u32 reg_dip_hfac_ini_h          : 4;
    u32                             : 28;
    // h04
    u32 reg_dip_hfac_l              : 16;
    u32                             : 16;
    // h05
    u32 reg_dip_hfac_h              : 7;
    u32                             : 7;
    u32 reg_dip_prehsd_mode         : 1;
    u32 reg_dip_prehsd_en           : 1;
    u32                             : 16;
    // h06
    u32 reg_dip_vfac_ini_t          : 16;
    u32                             : 16;
    // h07
    u32 reg_dip_vfac_ini_b          : 16;
    u32                             : 16;
    // h08
    u32 reg_dip_vfac_l              : 16;
    u32                             : 16;
    // h09
    u32 reg_dip_vfac_h              : 7;
    u32                             : 5;
    u32 reg_dip_prev_down_3d        : 1;
    u32 reg_dip_vsd_dup_black       : 1;
    u32 reg_dip_pre_vdown_mode      : 1;
    u32 reg_dip_pre_vdown           : 1;
    u32                             : 16;
    // h0A
    u32 reg_dip_clip_en_r           : 1;
    u32 reg_dip_align_en_r          : 1;
    u32 reg_dip_c_filter_r          : 2;
    u32 reg_dip_cbcr_swap_r         : 1;
    u32 reg_dip_f422en_r            : 1;
    u32 reg_dip_pdw_src_422_r       : 1;
    u32 reg_dip_r2y_dithen_r        : 1;
    u32 reg_dip_r2y_en_r            : 1;
    u32 reg_dip_r2y_eq_sel_r        : 2;
    u32 reg_dip_src_pdw_r           : 1;
    u32 reg_dip_vs_inv_r            : 1;
    u32 reg_bist_fail_status_ext    : 2;
    u32                             : 17;
    // h0B
    u32 reg_dip_clip_h_st_r         : 12;
    u32 reg_dip_f422en_osd          : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_F422EN_OSD_MASK                 0x0001
        #define DIP_F422EN_OSD_OFF                  0x00
        #define DIP_F422EN_OSD_EN                   0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_c_filter_osd        : 2;
    u32 reg_dip_cbcr_swap_osd       : 1;
    u32                             : 16;
    // h0C
    u32 reg_dip_clip_h_end_r        : 12;
    u32 reg_freq_div                : 4;
    u32                             : 16;
    // h0D
    u32 reg_dip_clip_v_st_r         : 12;
    u32 reg_gating_db_en            : 1;
    u32                             : 19;
    // h0E
    u32 reg_dip_clip_v_end_r        : 12;
    u32                             : 20;
    // h0F
    u32 reg_dip_clip_pre_h_max_nsec : 13;
    u32                             : 2;
    u32 reg_dip_clip_pre_en_nsec    : 1;
    u32                             : 16;

    // h10
    u32 reg_dip_osd_en              : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_OSD_OFF                         0x00
        #define DIP_OSD_EN                          0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_osd_de_mode         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_OSD_DE_MODE_OFF                 0x00
        #define DIP_OSD_DE_MODE_EN                  0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_osd_foregnd         : 1;
    u32 reg_dip_osd_hs_sel          : 1;
    u32 reg_dip_osd_alpha_sel       : 2;
    u32 reg_dip_osd_vs_inv          : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_OSD_VSYNC_INV_OFF               0x00
        #define DIP_OSD_VSYNC_INV_ON                0x01
        /*------------------------------------------------------------*/
    u32 reg_rot_type                : 1;
    u32 reg_dip_osd_alpha           : 6;
    u32 reg_rotate_mode             : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_ROTATE_DEG_MASK                 0x0001
        #define DIP_ROTATE_DEG_90                   0x01
        #define DIP_ROTATE_DEG_270                  0x00
        /*------------------------------------------------------------*/
    u32 reg_rotate_en               : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_ROTATE_EN_MASK                  0x0001
        #define DIP_ROTATE_OFF                      0x00
        #define DIP_ROTATE_EN                       0x01
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h11
    u32 reg_dip_osd_en_r            : 1;
    u32 reg_dip_osd_de_mode_r       : 1;
    u32 reg_dip_osd_foregnd_r       : 1;
    u32 reg_dip_osd_hs_sel_r        : 1;
    u32 reg_dip_osd_alpha_sel_r     : 2;
    u32 reg_dip_osd_vs_inv_r        : 1;
    u32                             : 1;
    u32 reg_dip_osd_alpha_r         : 6;
    u32                             : 18;
    // h12
    u32 reg_dip_hfac_ini_r_l        : 16;
    u32                             : 16;
    // h13
    u32 reg_dip_hfac_ini_r_h        : 4;
    u32                             : 9;
    u32 reg_dip_hout_proc_r         : 1;
    u32 reg_dip_hsd_dithen_r        : 1;
    u32 reg_dip_hsd_flt_mode_r      : 1;
    u32                             : 16;
    //h14
    u32 reg_dip_hfac_r_l            : 16;
    u32                             : 16;
    //h15
    u32 reg_dip_hfac_r_h            : 7;
    u32                             : 1;
    u32 reg_dip_osdb_method_sel     : 2;
    u32 reg_dip_mode1_alpha_en      : 1;
    u32 reg_dip_mode1_px_en         : 1;
    u32 reg_dip_mode1_sum_en        : 1;
    u32 reg_dip_osdb_switch         : 1;
    u32 reg_dip_prehsd_mode_r       : 1;
    u32 reg_dip_prehsd_en_r         : 1;
    u32                             : 16;
    // h16
    u32 reg_dip_hsd_yt0_c0          : 8;
    u32                             : 24;
    // h17
    u32 reg_dip_hsd_yt0_c1          : 8;
    u32                             : 24;
    // h18
    u32 reg_dip_hsd_yt0_c2          : 8;
    u32                             : 24;
    // h19
    u32 reg_dip_hsd_yt1_c0          : 8;
    u32                             : 24;
    // h1A
    u32 reg_dip_hsd_yt1_c1          : 8;
    u32                             : 24;
    // h1B
    u32 reg_dip_hsd_yt1_c2          : 8;
    u32                             : 24;
    // h1C
    u32 reg_dip_hsd_yt1_c3          : 8;
    u32                             : 24;
    // h1D
    u32 reg_dip_hsd_yt1_c4          : 8;
    u32                             : 24;
    // h1E
    u32 reg_dip_hsd_yt1_c5          : 8;
    u32                             : 24;
    // h1F
    u32 reg_dip_hsd_yt2_c0          : 8;
    u32                             : 24;

    // h20
    u32 reg_dip_hsd_yt2_c1          : 8;
    u32                             : 24;
    // h21
    u32 reg_dip_hsd_yt2_c2          : 8;
    u32                             : 24;
    // h22
    u32 reg_dip_hsd_ct0_c1          : 8;
    u32                             : 24;
    // h23
    u32 reg_dip_hsd_ct0_c2          : 8;
    u32                             : 24;
    // h24
    u32 reg_dip_hsd_ct1_c1          : 8;
    u32                             : 24;
    // h25
    u32 reg_dip_hsd_ct1_c2          : 8;
    u32                             : 24;
    // h26
    u32 reg_dip_hsd_ct1_c3          : 8;
    u32                             : 24;
    // h27
    u32 reg_dip_hsd_ct1_c4          : 8;
    u32                             : 24;
    // h28
    u32 reg_dip_hsd_ct2_c1          : 8;
    u32                             : 24;
    // h29
    u32 reg_dip_hsd_ct2_c2          : 8;
    u32                             : 24;
    // h2A
    u32 reg_4k_hfacini_l            : 16;
    u32                             : 16;
    // h2B
    u32 reg_4k_hfacini_h            : 4;
    u32 reg_4k_hsd_dither           : 1;
    u32 reg_4k_out_dithen           : 1;
    u32                             : 26;
    // h2C
    u32 reg_4k_hfactor_l            : 16;
    u32                             : 16;
    // h2D
    u32 reg_4k_hfactor_h            : 7;
    u32                             : 25;
    // h2E
    u32 reg_read_hsd_out_4k         : 13;
    u32                             : 19;
    // h2F
    u32 reg_dip_clip_pre_v_max_nsec : 13;
    u32                             : 19;

    //h30
    u32 reg_dip_f422en              : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_F422EN_MASK                   0x0001
        #define DIP_W_F422EN_OFF                    0x00
        #define DIP_W_F422EN_EN                     0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_c_filter            : 2;
    u32 reg_dip_cbcr_swap           : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_CBCR_SWAP_MASK                0x0001
        #define DIP_W_CBCR_SWAP(x)                  ((x) & DIP_DEST_CBCR_SWAP_MASK)
        #define DIP_W_CBCR_SWAP_OFF                 0x00
        #define DIP_W_CBCR_SWAP_EN                  0x01
        /*------------------------------------------------------------*/
    u32                             : 1;
    u32 reg_dip_pdw_src_422         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_PDW_SRC_422_SELECT_MASK       0x0001
        #define DIP_W_PDW_SRC_422_SELECT(x)         ((x) & DIP_PDW_SRC_422_SELECT_MASK)
        #define DIP_W_PDW_SRC_422_SELECT_OFF        0x00
        #define DIP_W_PDW_SRC_422_SELECT_EN         0x01
        // 1: select...select what?, 0: de-select Check with designer.
        /*------------------------------------------------------------*/
    u32                             : 26;
    // h31
    u32 reg_dip_r2y_en              : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_R2Y_EN_MASK                   0x0001
        #define DIP_W_R2Y_SET_EN(x)                 ((x) & DIP_W_R2Y_EN_MASK)
        #define DIP_W_R2Y_EN                        1
        #define DIP_W_R2Y_DIS                       0
        /*------------------------------------------------------------*/
    u32 reg_dip_r2y_eq_sel          : 2;
    u32 reg_dip_r2y_dithen          : 1;
    u32                             : 28;
    // h32
    u32 reg32[4];
    // h36
    u32 reg_dip_vsd_in_number       : 13;
    u32                             : 2;
    u32 reg_dip_vin_ctrl_en         : 1;
    u32                             : 16;
    // h37
    u32 reg_dip_vsd_out_number      : 13;
    u32                             : 2;
    u32 reg_dip_vout_ctrl_en        : 1;
    u32                             : 16;
    // h38
    u32 reg_dip_vfac_ini_t_r        : 16;
    u32                             : 16;
    // h39
    u32 reg_dip_vfac_ini_b_r        : 16;
    u32                             : 16;
    // h3A
    u32 reg_dip_vfac_r_l            : 16;
    u32                             : 16;
    // h3B
    u32 reg_dip_vfac_r_h            : 7;
    u32 reg_dip_vsd_dithen_r        : 1;
    u32 reg_dip_vfac_sht_r          : 1;
    u32 reg_dip_vsd_422_r           : 1;
    u32 reg_dip_vout_proc_r         : 1;
    u32 reg_dip_vsd_fac_auto_rst_en_r : 1;
    u32 reg_dip_prev_down_3d_r      : 1;
    u32 reg_dip_vsd_dup_black_r     : 1;
    u32 reg_dip_pre_vdown_mode_r    : 1;
    u32 reg_dip_pre_vdown_r         : 1;
    u32                             : 16;
    // h3C
    u32 reg_dip_vsd_in_number_r     : 13;
    u32                             : 2;
    u32 reg_dip_vin_ctrl_en_r       : 1;
    u32                             : 16;
    // h3D
    u32 reg_dip_vsd_out_number_r    : 13;
    u32                             : 2;
    u32 reg_dip_vout_ctrl_en_r      : 1;
    u32                             : 16;
    // h3E
    u32 reg_dip_hsd_out_cnt         : 13;
    u32                             : 19;
    // h3F
    u32 reg_dip_clip_po_h_max_nsec  : 13;
    u32                             : 19;
    // h40
    u32 reg_dip_frc_fac             : 6;
    u32                             : 26;
    // h41
    u32 reg_dip_frc_rst_p           : 1;
    u32                             : 31;
    // h42
    u32 reg_adr_map_b0              : 4;
    u32 reg_adr_map_b1              : 4;
    u32 reg_adr_map_b2              : 4;
    u32 reg_adr_map_b3              : 4;
    u32                             : 16;
    // h43
    u32 reg_adr_map_b4              : 4;
    u32 reg_adr_map_b5              : 4;
    u32 reg_adr_map_b6              : 4;
    u32 reg_adr_map_b7              : 4;
    u32                             : 16;
    // h44
    u32 reg_adr_map_b8              : 4;
    u32 reg_adr_map_b9              : 4;
    u32 reg_adr_map_b10             : 4;
    u32 reg_adr_map_b11             : 4;
    u32                             : 16;
    // h45
    u32 reg_adr_map_b12             : 4;
    u32 reg_adr_map_b13             : 4;
    u32 reg_adr_map_b14             : 4;
    u32 reg_adr_map_b15             : 4;
    u32                             : 16;
    // h46
    u32 reg46[2];
    // h48
    u32 reg_dip_fetch_num_wbe       : 13;
    u32                             : 1;
    u32 reg_rot_with_lb_wbe_en      : 1;
    u32 reg_rot_with_lb             : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_ROT_WITH_LB_OFF                 0x00
        #define DIP_ROT_WITH_LB_EN                  0x01
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h49
    u32 reg_dip_vcnt_num_wbe        : 12;
    u32                             : 20;
    // h4A
    u32 reg4A[5];
    // h4F
    u32 reg_dip_clip_po_v_max_nsec  : 13;
    u32                             : 19;
    // h50
    u32 reg_dip_hsd_flt_mode        : 1;
    u32 reg_4k_gb_size_r            : 9;
    u32                             : 5;
    u32 reg_avg_2pto1p_path         : 1;
    u32                             : 16;
    // h51
    u32 reg_dip_hsd_yt3_c0          : 8;
    u32                             : 24;
    // h52
    u32 reg_dip_hsd_yt3_c1          : 8;
    u32                             : 24;
    // h53
    u32 reg_dip_hsd_yt3_c2          : 8;
    u32                             : 24;
    // h54
    u32 reg_dip_hsd_yt3_c3          : 8;
    u32                             : 24;
    // h55
    u32 reg_dip_hsd_yt3_c4          : 8;
    u32                             : 24;
    // h56
    u32 reg_dip_hsd_yt3_c5          : 8;
    u32                             : 24;
    // h57
    u32 reg_dip_hsd_yt4_c0          : 8;
    u32                             : 24;
    // h58
    u32 reg_dip_hsd_yt4_c1          : 8;
    u32                             : 24;
    // h59
    u32 reg_dip_hsd_yt4_c2          : 8;
    u32                             : 24;
    // h5A
    u32 reg_dip_hsd_yt4_c3          : 8;
    u32                             : 24;
    // h5B
    u32 reg_dip_hsd_yt4_c4          : 8;
    u32                             : 24;
    // h5C
    u32 reg_dip_hsd_yt4_c5          : 8;
    u32                             : 24;
    // h5D
    u32 reg_dip_mfdec_swap          : 1;
    u32 reg_dip_mfdec_lossy0        : 1;
    u32 reg_dip_mfdec_lossy00       : 1;
    u32 reg_dip_mfdec_lossy01       : 1;
    u32 reg_dip_cmdq_swap           : 1;
    u32                             : 27;
    // h5E
    u32 reg5E[2];
    // h60
    u32 reg_dip_clip_en             : 1;
    u32 reg_dip_align_en            : 1;
    u32                             : 2;
    u32 reg_4k_h_size_r             : 12;
    u32                             : 16;
    // h61
    u32 reg_dip_clip_h_st           : 13;
    u32                             : 19;
    // h62
    u32 reg_dip_clip_h_end          : 13;
    u32                             : 19;
    // h63
    u32 reg_dip_clip_v_st           : 13;
    u32                             : 19;
    // h64
    u32 reg_dip_clip_v_end          : 13;
    u32                             : 19;
    // h65
    u32 reg65[2];
    // h67
    u32 reg_dip_op_pre_sel          : 2;
    u32 reg_dip_ip_pre_sel          : 3;
    u32 reg_dip_op_pre_sel_r        : 2;
    u32 reg_dip_ip_pre_sel_r        : 3;
    u32 reg_dip_src_pre_sel_r       : 2;
    u32 reg_dip_src_last_sel        : 1;
    u32                             : 19;
    // h68
    u32 reg_422to444_md             : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_TOP_422to444_MD_MASK            0x0003
        #define DIP_TOP_422to444_MD(x)              ((x) & DIP_TOP_422to444_MD_MASK)
        #define DIP_TOP_422to444_MD_DISABLE         0x00 //disable
        #define DIP_TOP_422to444_MD_DUPLICATE       0x01 //duplicate
        #define DIP_TOP_422to444_MD2                0x02 //?
        #define DIP_TOP_422to444_MD3                0x03 //?
        // Check with designer
        /*------------------------------------------------------------*/
    u32 reg_cr_load_ini             : 1;
    u32                             : 3;
    u32 reg_dip_vsd_fac_auto_rst_en : 1;
    u32                             : 3;
    u32 reg_idclk3_gate_usr_md      : 2;
    u32 reg_idclk3_ip_src_usr_md    : 4;
    u32                             : 16;
    // h69
    u32 reg_422to444_md_r           : 2;
    u32 reg_cr_load_ini_r           : 1;
    u32 reg_dip_pdw_dith_en_r       : 1;
    u32 reg_dip_rgb_swap_r          : 1;
    u32 reg_dip_yc_swap_r           : 1;
    u32 reg_dipw_cbcr_swap_r        : 1;
    u32 reg_dipw_align_en_r         : 1;
    u32 reg_dipw_align_num_sel_r    : 1;
    u32 reg_dipw_align_num_r        : 5;
    u32 reg_dipw_clip_en_r          : 1;
    u32 reg_dip_y2r_en_r            : 1;
    u32                             : 16;
    // h6A
    u32 reg_dip_frame_buf_num_r     : 3;
    u32 reg_dip_format_r            : 2;
    u32 reg_dip_intlac_src_r        : 1;
    u32 reg_dip_intlac_w_r          : 1;
    u32 reg_dip_no_color_r          : 1;
    u32 reg_dip_422to420_ratio_r    : 5;
    u32 reg_dip_prog_420c_sel_r     : 1;
    u32 reg_dip_420_linear_r        : 1;
    u32 reg_dip_yc422_sep_r         : 1;
    u32                             : 16;
    // h6B
    u32 reg_dip_argb_alpha_r        : 8;
    u32 reg_dip_yuvi_force_base_r   : 1;
    u32 reg_dip_i420_r              : 1;
    u32 reg_dipw_src_dpk_r          : 1;
    u32 reg_wfifo_src_rlb_r         : 1;
    u32 reg_h_mirror_r              : 1;
    u32 reg_v_flip_r                : 1;
    u32                             : 18;
    // h6C
    u32 reg_4k_gb_size              : 9;
    u32 reg_4k_422to444_md          : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_TOP_4K_422to444_MD_MASK         0x0600
        #define DIP_TOP_4K_422to444_MD(x)           ((x) & DIP_TOP_4K_422to444_MD_MASK)
        #define DIP_TOP_4K_422to444_MD0             0x00 //disable
        #define DIP_TOP_4K_422to444_MD1             0x01 //duplicate
        #define DIP_TOP_4K_422to444_MD2             0x02
        #define DIP_TOP_4K_422to444_MD3             0x03
        //0: disable, 1: ?, 2: ?, 3: ? check with designer
        /*------------------------------------------------------------*/
    u32 reg_4k_cr_load_ini          : 1;
    u32 reg_4k_left_only            : 1;
    u32 reg_4k_hsd_mode             : 2;
    u32 reg_4k_hsd_en               : 1;
    u32                             : 16;
    // h6D
    u32 reg_4k_h_size               : 12;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_4K_H_SIZE_MASK                  0x0FFF
        #define DIP_4K_H_SIZE(x)                    (((x)>>1) & DIP_4K_H_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32 reg_avg_rounding            : 1;
    u32 reg_avg_bypass1             : 1;
    u32 reg_avg_en                  : 1;
    u32 reg_4k_path_on              : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_4K_PATH_ON_MASK                 0x0001
        #define DIP_4K_PATH_OFF                     0x00
        #define DIP_4K_PATH_ON                      0x01
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h6E
    u32 reg_lb_sec_size             : 8;
    u32 reg_rot_422                 : 1;
    u32 reg_rot_444to422_mode       : 2;
    u32 reg_new_rotate_en           : 1;
    u32 reg_remap_en                : 1;
    u32 reg_remap_md                : 1;
    u32 reg_rot_dst                 : 2;
    u32                             : 16;
    // h6F
    u32 reg_dipr_src_sel            : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_R_SRC_SEL_MASK                  0x0003
        #define DIP_R_SRC_SEL(x)                    ((x) & DIP_R_SRC_SEL_MASK)
        #define DIP_R_SRC_DWIN0                     0x00
        #define DIP_R_SRC_DWIN1                     0x01
        #define DIP_R_SRC_DIP                       0x02
        /*------------------------------------------------------------*/
    u32 reg_rotate_adr_mode         : 3;
    u32                             : 8;
    u32 reg_rotate_lb_sel           : 1;
    u32 reg_rot_sw_rst              : 1;
    u32 reg_rotate_conti_mode       : 1;
    u32                             : 16;
    // h70
    u32 reg_dip_base_adr0_r_l       : 16;
    u32                             : 16;
    // h71
    u32 reg_dip_base_adr0_r_h       : 11;
    u32                             : 21;
    // h72
    u32 reg_dip_base_adr1_r_l       : 16;
    u32                             : 16;
    // h73
    u32 reg_dip_base_adr1_r_h       : 11;
    u32                             : 21;
    // h74
    u32 reg_dip_base_adr2_r_l       : 16;
    u32                             : 16;
    // h75
    u32 reg_dip_base_adr2_r_h       : 11;
    u32                             : 21;
    // h76
    u32 reg_dip_frm_offset_r_l      : 16;
    u32                             : 16;
    // h77
    u32 reg_dip_frm_offset_r_h      : 8;
    u32                             : 24;
    // h78
    u32 reg_dip_c_base_frm_offset_r_l   : 16;
    u32                             : 16;
    // h79
    u32 reg_dip_c_base_frm_offset_r_h   : 8;
    u32                             : 24;
    // h7A
    u32 reg_dip_fetch_num_r         : 13;
    u32                             : 19;
    // h7B
    u32 reg_dip_ln_offset_r         : 13;
    u32                             : 19;
    // h7C
    u32 reg_dip_vcnt_num_r          : 12;
    u32 reg_dip_nsec_sel            : 1;
    u32                             : 1;
    u32 reg_src_yc_swap             : 1;
    u32 reg_src_di_sel              : 1;
    u32                             : 16;
    // h7D
    u32 reg_dip_dummy               : 16;
    u32                             : 16;
    // h7E
    u32 reg_db_en                   : 1;
    u32 reg_dip_hdmi_sw_mode        : 1;
    u32 reg_dip_edclk_gate_en       : 1;
    u32 reg_dip_edclk_gate_md       : 1;
    u32 reg_dip_sram_pd             : 4;
    u32 reg_pdw0_ip_mux             : 4;
    u32 reg_pdw1_ip_mux             : 4;
    u32                             : 16;
    // h7F
    u32 reg_sw_rst                  : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SW_RESET_DIS                    (0)
        #define DIP_SW_RESET_EN                     (1)
        /*------------------------------------------------------------*/
    u32 reg_force_ack_1             : 1;
    u32 reg_dip_bist_fail_status    : 1;
    u32 reg_pseudo_stop             : 1;
    u32 reg_dip_edclk_en            : 1;
    u32 reg_dip_edclk_en_usr_md     : 1;
    u32 reg_dip_src_pdw             : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_SRC_FROM_PDW_EN_MASK          0x0001
        #define DIP_W_SRC_FROM_PDW_SET_EN(x)        ((x) & DIP_W_SRC_FROM_PDW_EN_MASK)
        #define DIP_W_SRC_FROM_PDW_EN               1
        #define DIP_W_SRC_FROM_PDW_DIS              0
        /*------------------------------------------------------------*/
    u32 reg_dip_clk_en_sel          : 2;
    u32 reg_dip_hdmi_repeat_mode    : 1;
    u32 reg_dip_time_share          : 1;
    u32 reg_dip_one_shot_md         : 1;
    u32 reg_dipr_dst_sel            : 2;
    u32 reg_dip_src_pre_sel         : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_SRC_PRE_SEL_MASK              0x0003
        #define DIP_W_SRC_PRE_SEL(x)                ((x) & DIP_W_SRC_PRE_SEL_MASK)
        #define DIP_W_SRC_PRE_SEL_CAPTURE           0x00
        #define DIP_W_SRC_PRE_SEL_VR                0x01
        #define DIP_W_SRC_PRE_SEL_DIP               0x02
        /*------------------------------------------------------------*/
    u32                             : 16;
} KeDipTop_t;

typedef struct KeDipPdw_s
{
    // h00
    u32 reg00;
    // h01
    u32 reg_dip_frame_buf_num       : 3;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_FRAME_BUF_NUM_MASK            0x0007
        #define DIP_W_FRAME_BUF_NUM(x)              (((x)-1) & DIP_W_FRAME_BUF_NUM_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dip_intlac_w            : 1;
    u32 reg_dip_format              : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_COLOR_FORMAT_MASK          0x0003
        #define DIP_DEST_COLOR_FORMAT(x)            ((x) & DIP_DEST_COLOR_FORMAT_MASK)
        #define DIP_DEST_COLOR_FORMAT_YUV422        0x00
        #define DIP_DEST_COLOR_FORMAT_RGB           0x02
        #define DIP_DEST_COLOR_FORMAT_YUV420        0x03
        /*------------------------------------------------------------*/
    u32 reg_dip_dwin_en             : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_DWIN_EN_MASK                  0x0001
        #define DIP_W_DWIN_SET_EN(x)                ((x) & DIP_W_DWIN_EN_MASK)
        #define DIP_W_DWIN_EN                       1
        #define DIP_W_DWIN_DIS                      0
        /*------------------------------------------------------------*/
    u32 reg_dip_wbe_mask            : 1;
    u32 reg_dip_422to420_ratio      : 5;
    u32 reg_dip_prog_420c_sel       : 1;
    u32 reg_dip_no_color            : 1;
    u32 reg_dip_intlac_src          : 1;
    u32                             : 16;
    //h02
    u32 reg_dip_argb_alpha          : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_ARGB_ALPHA_MASK               0x00FF
        #define DIP_W_ARGB_ALPHA(x)                 ((x) & DIP_W_ARGB_ALPHA_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dip_pdw_src_sel         : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_PDW_SRC_SEL_MASK              0x0003
        #define DIP_W_PDW_SRC_SEL(x)                ((x) & DIP_W_PDW_SRC_SEL_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dip_pdw_off             : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_PDW_EN_MASK                   0x0001
        #define DIP_W_PDW_SET_EN(x)                 ((!x) & DIP_W_PDW_EN_MASK)
        #define DIP_W_PDW_OFF                       0x00
        #define DIP_W_PDW_EN                        0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_pdw_dith_en         : 1;
    u32 reg_dip_force_wreq_thrd     : 1;
    u32 reg_dipw_pdw2mi_sel         : 1;
    u32 reg_dipw_cbcr_swap          : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_CBCR_SWAP_OFF              0x00
        #define DIP_DEST_CBCR_SWAP_EN               0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_yc_swap             : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_YC_SWAP_OFF                0x00
        #define DIP_DEST_YC_SWAP_EN                 0x01
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h03
    u32 reg_dip_hi_pri_num          : 5;
    u32 reg_dip_top_field_inv       : 1;
    u32 reg_dip_yc422_sep           : 1;
    u32 reg_dip_alpha_sel           : 1;
    u32 reg_dip_dwin_wt_once        : 1;
    u32 reg_dip_dwin_wt_once_trig   : 1;
    u32 reg_dip_lb_full_clean       : 1;
    u32 reg_dip_miu_mode            : 1;
    u32 reg_dip_alpha_inv           : 1;
    u32 reg_dipr_rgb2argb           : 1;
    u32 reg_dip_420_linear          : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_FORMAT_420SP_OFF           0x00 //420 planer?? check with designer.
        #define DIP_DEST_FORMAT_420SP_EN            0x01
        /*------------------------------------------------------------*/
    u32 reg_dip_blk_tile            : 1;
    u32                             : 16;
    // h04
    u32                             : 4;
    u32 reg_dip_w_over_mask         : 1;
    u32 reg_dip_w_over_force        : 1;
    u32 reg_dip_w_over_clr          : 1;
    u32 reg_w_over_read_back        : 1;
    u32 reg_dipw_status0            : 7;
    u32 reg_miu_wfifo_full          : 1;
    u32                             : 16;
    // h05
    u32 reg_dipw_status1            : 10;
    u32 reg_miu_rfifo_empty_evd     : 1;
    u32 reg_miu_rfifo_full_evd      : 1;
    u32 reg_miu_rfifo_empty         : 1;
    u32 reg_miu_rfifo_full          : 1;
    u32 reg_miu_wfifo_empty         : 1;
    u32 reg_dipw_field              : 1;
    u32                             : 16;
    // h06
    u32 reg_dipw_status2            : 12;
    u32 reg_bist_fail_status_evd    : 1;
    u32 reg_bist_fail_status        : 3;
    u32                             : 16;
    // h07
    u32 reg_pdw_chk_sum_en          : 1;
    u32 reg_pdw_chk_sum_vcnt        : 4;
    u32 reg_bist_fail_status_ext    : 9;
    u32 reg_dipr_420_linear         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_FORMAT_420SP_OFF            0x00 //420 planer?? check with designer.
        #define DIP_SRC_FORMAT_420SP_EN             0x01
        /*------------------------------------------------------------*/
    u32 reg_dipw_pdw2mi_sel_ext     : 1;
    u32                             : 16;
    // h08
    u32 reg_dipw_irq_mask           : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_IRQ_MASK(x)                   ((x) & 0x00FF)
        /*------------------------------------------------------------*/
    u32 reg_dipw_irq_force          : 8;
    u32                             : 16;
    // h09
    u32 reg_dipw_irq_clr            : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_W_IRQ_CLR(x)                    ((x) & 0x00FF)
        /*------------------------------------------------------------*/
    u32 reg_ds_idx_read_back        : 8;
    u32                             : 16;
    // h0A
    u32 reg_dipw_irq_final_status   : 8;
    u32 reg_dipw_irq_raw_status     : 8;
    u32                             : 16;
    // h0B
    u32 reg_dipw_align_num          : 5;
    u32 reg_dipw_align_num_sel      : 1;
    u32 reg_dipw_align_en           : 1;
    u32 reg_dip_miu_gate_en         : 1;
    u32 reg_dip_miu_gate_inv        : 1;
    u32 reg_h_mirror                : 1;
    u32 reg_v_flip                  : 1;
    u32 reg_rot_8x8_blk_mode        : 1;
    u32 reg_tile_32x16              : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_TILE_FORMAT_32X16_OFF      0x00
        #define DIP_DEST_TILE_FORMAT_32X16_EN       0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_tile_32x16         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_TILE_FORMAT_32X16_OFF       0x00
        #define DIP_SRC_TILE_FORMAT_32X16_EN        0x01
        /*------------------------------------------------------------*/
    u32 reg_tile_32x32              : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_TILE_FORMAT_32X32_OFF      0x00
        #define DIP_DEST_TILE_FORMAT_32X32_EN       0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_tile_32x32         : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_TILE_FORMAT_32X32_OFF       0x00
        #define DIP_SRC_TILE_FORMAT_32X32_EN        0x01
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h0C
    u32 reg_wreq_delta_en           : 1;
    u32 reg_wreq_delta_md           : 2;
    u32 reg_rreq_delta_en           : 1;
    u32 reg_rreq_delta_md           : 2;
    u32 reg_sav_bw                  : 1;
    u32                             : 3;
    u32 reg_clk_gate_auto_off       : 1;
    u32                             : 21;
    // h0D
    u32 reg0D;
    // h0E
    u32 reg_dipw_status3            : 16;
    u32                             : 16;
    // h0F
    u32 reg_dipw_status4            : 16;
    u32                             : 16;
    // h10
    u32 reg_dip_base_adr0_l         : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_Y_BASE_ADDR_L_MASK         0xFFFF
        #define DIP_DEST_Y_BASE_ADDR_L(x)           (((x)>>4) & DIP_DEST_Y_BASE_ADDR_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h11
    u32 reg_dip_base_adr0_h         : 11;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_Y_BASE_ADDR_H_MASK         0x07FF
        #define DIP_DEST_Y_BASE_ADDR_H(x)           (((x)>>20) & DIP_DEST_Y_BASE_ADDR_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 21;
    // h12
    u32 reg_dip_evd_base_adr0_l     : 16;
    u32                             : 16;
    // h13
    u32 reg_dip_evd_base_adr0_h     : 11;
    u32                             : 21;
    // h14
    u32 reg_dip_evd_base_adr1_l     : 16;
    u32                             : 16;
    // h15
    u32 reg_dip_evd_base_adr1_h     : 11;
    u32                             : 21;
    // h16
    u32 reg_max_length_r0           : 8;
    u32 reg_max_length_r1           : 8;
    u32                             : 16;
    // h17
    u32 reg_max_length_all          : 8;
    u32 reg_hpmask                  : 2;
    u32 reg_req_mask                : 2;
    u32 reg_debug_clr               : 1;
    u32 reg_dip_evd_10b_mode        : 2;
    u32 reg_dip_evd_10b             : 1;
    u32                             : 16;
    // h18
    u32 reg_dip_base_adr2_l         : 16;
    u32                             : 16;
    // h19
    u32 reg_dip_base_adr2_h         : 11;
    u32                             : 21;
    // h1A
    u32 reg_hp_cut_min0             : 8;
    u32 reg_hp_cut_min1             : 8;
    u32                             : 16;
    // h1B
    u32 reg_no_answer_cnt_latch     : 12;
    u32 reg_wff_full_status         : 1;
    u32 reg_rff_full_status         : 1;
    u32 reg_hp_cut_in_en0           : 1;
    u32 reg_hp_cut_in_en1           : 1;
    u32                             : 16;
    // h1C
    u32 reg_dipr_tile_req_num_evd   : 5;
    u32                             : 8;
    u32 reg_ds_idx_sel              : 1;
    u32 reg_arb_vs_rst_en           : 1;
    u32 reg_mrq_vs_rst_en           : 1;
    u32                             : 16;
    // h1D
    u32 reg_dipr_ln_offset_evd      : 12;
    u32                             : 20;
    // h1E
    u32 reg_ddi_en                  : 1;
    u32                             : 31;
    // h1F
    u32 reg_dip_fetch_num           : 13;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_H_SIZE_MASK                0x1FFF
        #define DIP_DEST_H_SIZE(x)                  ((x) & DIP_DEST_H_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                             : 19;

    // h20
    u32 reg_dip_base_adr1_l         : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_C_BASE_ADDR_L_MASK         0xFFFF
        #define DIP_DEST_C_BASE_ADDR_L(x)           (((x)>>4) & DIP_DEST_C_BASE_ADDR_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h21
    u32 reg_dip_base_adr1_h         : 11;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_C_BASE_ADDR_H_MASK         0x07FFF
        #define DIP_DEST_C_BASE_ADDR_H(x)           (((x)>>20) & DIP_DEST_C_BASE_ADDR_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 21;
    // h22
    u32 reg22[5];
    // h27
    u32 reg_dipr_fetch_num          : 13;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_H_SIZE_MASK                 0x1FFF
        #define DIP_SRC_H_SIZE(x)                   ((x) & DIP_SRC_H_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                             : 19;
    // h28
    u32 reg_dipw_cmdq_irq_mask      : 8;
    u32 reg_dipw_cmdq_irq_force     : 8;
    u32                             : 16;
    // h29
    u32 reg_dipw_cmdq_irq_clr       : 8;
    u32 reg_dipw_tlb                : 1;
    u32                             : 23;
    // h2A
    u32 reg_dipw_cmdq_irq_final_status : 8;
    u32 reg_dipw_cmdq_irq_raw_status : 8;
    u32                             : 16;
    // h2B
    u32 reg2B[4];
    // h2F
    u32 reg_dip_vcnt_num            : 12;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_V_SIZE_MASK                0x0FFF
        #define DIP_DEST_V_SIZE(x)                  ((x) & DIP_DEST_V_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                             : 20;

    // h30
    u32 reg_dip_w_limit_adr_l       : 16;
    u32                             : 16;
    // h31
    u32 reg_dip_w_limit_adr_h       : 11;
    u32                             : 4;
    u32 reg_dip_w_limit_en          : 1;
    u32                             : 16;
    // h32
    u32 reg32[5];
    // h37
    u32 reg_dipr_vcnt_num           : 12;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_V_SIZE_MASK                 0x0FFF
        #define DIP_SRC_V_SIZE(x)                   ((x) & DIP_SRC_V_SIZE_MASK)
        /*------------------------------------------------------------*/
    u32                             : 20;
    // h38
    u32 reg_dipr_irq_mask           : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_R_IRQ_MASK(x)                   ((x) & 0x00FF)
        /*------------------------------------------------------------*/
    u32 reg_dipr_irq_force          : 8;
    u32                             : 16;
    // h39
    u32 reg_dipr_irq_clr            : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_R_IRQ_CLR(x)                    ((x) & 0x00FF)
        /*------------------------------------------------------------*/
    u32 reg_dipr_tlb                : 1;
    u32                             : 23;
    // h3A
    u32 reg_dipr_irq_final_status   : 8;
    u32 reg_dipr_irq_raw_status     : 8;
    u32                             : 16;
    // h3B
    u32 reg_dipw_force_frm_index    : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_FORCE_FRM_INDEX_OFF            0x00
        #define DIP_DEST_FORCE_FRM_INDEX_EN             0x01
        /*------------------------------------------------------------*/
    u32 reg_dipw_frm_index          : 3;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_FORCE_FRM_0                    0x00
        #define DIP_DEST_FORCE_FRM_1                    0x01
        #define DIP_DEST_FORCE_FRM_2                    0x02
        #define DIP_DEST_FORCE_FRM_3                    0x03
        #define DIP_DEST_FORCE_FRM_4                    0x04
        #define DIP_DEST_FORCE_FRM_5                    0x05
        #define DIP_DEST_FORCE_FRM_6                    0x06
        #define DIP_DEST_FORCE_FRM_7                    0x07
        /*------------------------------------------------------------*/
    u32                             : 28;
    // h3C
    u32 reg3C[3];
    // h3F
    u32 reg_dip_ln_offset           : 13;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_LINE_OFFSET_MASK               0x1FFF
        #define DIP_DEST_LINE_OFFSET(x)                 ((x)    & DIP_DEST_LINE_OFFSET_MASK)
        /*------------------------------------------------------------*/
    u32                             : 19;

    // h40
    u32 reg_dip_c_base_w_limit_adr_l : 16;
    u32                             : 16;
    // h41
    u32 reg_dip_c_base_w_limit_adr_h : 11;
    u32                             : 21;
    // h42
    u32 reg42[6];
    // h48
    u32 reg_dipr_cmdq_irq_mask      : 8;
    u32 reg_dipr_cmdq_irq_force     : 8;
    u32                             : 16;
    // h49
    u32 reg_dipr_cmdq_irq_clr       : 8;
    u32                             : 24;
    // h4A
    u32 reg_dipr_cmdq_irq_final_status : 8;
    u32 reg_dipr_cmdq_irq_raw_status : 8;
    u32                             : 16;
    // h4B
    u32 reg_field_index             : 8;
    u32 reg_field_index_ext         : 8;
    u32                             : 16;
    // h4C
    u32 reg4C[4];

    // h50
    u32 reg_dip_frm_offset_l        : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_Y_FRAME_OFFSET_L_MASK      0xFFFF
        #define DIP_DEST_Y_FRAME_OFFSET_L(x)        ((x) & DIP_DEST_Y_FRAME_OFFSET_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h51
    u32 reg_dip_frm_offset_h        : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_Y_FRAME_OFFSET_H_MASK      0x00FF
        #define DIP_DEST_Y_FRAME_OFFSET_H(x)        ((x) & DIP_DEST_Y_FRAME_OFFSET_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 24;
    // h52
    u32 reg52[6];
    // h58
    u32 reg_dipw_ext_irq_mask       : 8;
    u32 reg_dipw_ext_irq_force      : 8;
    u32                             : 16;
    // h59
    u32 reg_dipw_ext_irq_clr        : 8;
    u32                             : 24;
    // h5A
    u32 reg_dipw_ext_irq_final_status : 8;
    u32 reg_dipw_ext_irq_raw_status : 8;
    u32                             : 16;
    // h5B
    u32 reg5B[5];

    // h60
    u32 reg_dip_c_base_frm_offset_l : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_C_FRAME_OFFSET_L_MASK      0xFFFF
        #define DIP_DEST_C_FRAME_OFFSET_L(x)        ((x) & DIP_DEST_C_FRAME_OFFSET_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h61
    u32 reg_dip_c_base_frm_offset_h : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_C_FRAME_OFFSET_H_MASK      0x00FF
        #define DIP_DEST_C_FRAME_OFFSET_H(x)        ((x) & DIP_DEST_C_FRAME_OFFSET_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 24;
    // h62
    u32 reg_vbk_num                 : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_OSDB_VBK_NUM_MASK               0xFFFF
        #define DIP_OSDB_VBK_NUM(x)                 ((x) & DIP_OSDB_VBK_NUM_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h63
    u32 reg63[5];
    // h68
    u32 reg_dipw_ext_cmdq_irq_mask  : 8;
    u32 reg_dipw_ext_cmdq_irq_force : 8;
    u32                             : 16;
    // h69
    u32 reg_dipw_ext_cmdq_irq_clr   : 8;
    u32                             : 24;
    // h6A
    u32 reg_dipw_ext_cmdq_irq_final_status  : 8;
    u32 reg_dipw_ext_cmdq_irq_raw_status    : 8;
    u32                             : 16;
    // h6B
    u32 reg6B[4];
    // h6F
    u32 reg_dip_wreq_thrd           : 6;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_WRITE_REQ_THRD_MASK        0x003F
        #define DIP_DEST_WRITE_REQ_THRD(x)          ((x) & DIP_DEST_WRITE_REQ_THRD_MASK)
        /*------------------------------------------------------------*/
    u32                             : 2;
    u32 reg_dip_wreq_max            : 7;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_WRITE_REQ_MAX_NUM_MASK     0x007F
        #define DIP_DEST_WRITE_REQ_MAX_NUM(x)       ((x) & DIP_DEST_WRITE_REQ_MAX_NUM_MASK)
        /*------------------------------------------------------------*/
    u32                             : 17;

    // h70
    u32 reg_dipr_sw_frm_offset_l    : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_Y_FRAME_OFFSET_L_MASK       0xFFFF
        #define DIP_SRC_Y_FRAME_OFFSET_L(x)         ((x) & DIP_SRC_Y_FRAME_OFFSET_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h71
    u32 reg_dipr_sw_frm_offset_h    : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_Y_FRAME_OFFSET_H_MASK       0x00FF
        #define DIP_SRC_Y_FRAME_OFFSET_H(x)         ((x) & DIP_SRC_Y_FRAME_OFFSET_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 24;
    // h72
    u32 reg_dipr_sw_c_base_frm_offset_l : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_C_FRAME_OFFSET_L_MASK       0xFFFF
        #define DIP_SRC_C_FRAME_OFFSET_L(x)         ((x) & DIP_SRC_C_FRAME_OFFSET_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h73
    u32 reg_dipr_sw_c_base_frm_offset_h : 8;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_C_FRAME_OFFSET_H_MASK       0x00FF
        #define DIP_SRC_C_FRAME_OFFSET_H(x)         ((x) & DIP_SRC_C_FRAME_OFFSET_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 24;
    // h74
    u32 reg_dipr_sw_ln_offset       : 13;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_LINE_OFFSET_MASK            0x1FFF
        #define DIP_SRC_LINE_OFFSET(x)              ((x) & DIP_SRC_LINE_OFFSET_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dipr_sw_frame_buf_num   : 3;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_R_FRAME_BUF_NUM_MASK            0x0007
        #define DIP_R_FRAME_BUF_NUM(x)              (((x)-1) & DIP_R_FRAME_BUF_NUM_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h75
    u32 reg_mask_hbk_num            : 5;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_OSDB_HBK_NUM_MASK               0x001F
        #define DIP_OSDB_HBK_NUM(x)                 ((x) & DIP_OSDB_HBK_NUM_MASK)
        /*------------------------------------------------------------*/
    u32 reg_mask_hbk                : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_OSDB_HBK_OFF                    0x00
        #define DIP_OSDB_HBK_EN                     0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_mfdec_en           : 1;
    u32                             : 25;
    // h76
    u32 reg_pdw_arb_max_req_num     : 8;
    u32 reg_pdw_arb_rdy1_first      : 1;
    u32 reg_pdw_arb_flow_ctrl_en    : 1;
    u32 reg_pdw_arb_thd_hit_last_en : 1;
    u32 reg_pdw_arb_bypass_en       : 1;
    u32 reg_pdw_arb_sw_rst          : 1;
    u32 reg_dipr_pdw2mi_c_sel       : 2;
    u32 reg_yc_sep_miu              : 1;
    u32                             : 16;
    // h77
    u32 reg_pdw_arb_rdy0_thd        : 8;
    u32 reg_pdw_arb_rdy1_thd        : 8;
    u32                             : 16;
    // h78
    u32 reg_dipr_base_adr0_l        : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_Y_BASE_ADDR_L_MASK          0xFFFF
        #define DIP_SRC_Y_BASE_ADDR_L(x)            (((x)>>4) & DIP_SRC_Y_BASE_ADDR_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h79
    u32 reg_dipr_base_adr0_h        : 11;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_Y_BASE_ADDR_H_MASK          0x07FF
        #define DIP_SRC_Y_BASE_ADDR_H(x)            (((x)>>20) & DIP_SRC_Y_BASE_ADDR_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 21;
    // h7A
    u32 reg_dipr_base_adr1_l        : 16;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_C_BASE_ADDR_L_MASK          0xFFFF
        #define DIP_SRC_C_BASE_ADDR_L(x)            (((x)>>4) & DIP_SRC_C_BASE_ADDR_L_MASK)
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h7B
    u32 reg_dipr_base_adr1_h        : 11;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_C_BASE_ADDR_H_MASK          0x07FFF
        #define DIP_SRC_C_BASE_ADDR_H(x)            (((x)>>20) & DIP_SRC_C_BASE_ADDR_H_MASK)
        /*------------------------------------------------------------*/
    u32                             : 21;
    // h7C
    //DIP processing YUV422 only?? check with designer.
    u32 reg_dipr_yc_swap            : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_YC_SWAP_OFF                 0x00
        #define DIP_SRC_YC_SWAP_EN                  0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_rgb_swap           : 1;
    u32 reg_dipr_cbcr_swap          : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_CBCR_SWAP_OFF               0x00
        #define DIP_SRC_CBCR_SWAP_EN                0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_420to422           : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_420_TO_422_OFF              0x00
        #define DIP_SRC_420_TO_422_EN               0x01
        /*------------------------------------------------------------*/
    u32 reg_wfifo_src_rlb           : 1;
    u32 reg_dipw_src_dpk            : 1;
    u32 reg_dipr_fd_toggle_md       : 1;
    u32 reg_dipr_fd                 : 1;
    u32 reg_dipr_force_frm_index    : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_FORCE_FRM_INDEX_OFF         0x00
        #define DIP_SRC_FORCE_FRM_INDEX_EN          0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_frm_index          : 3;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_FORCE_FRM_0                 0x00
        #define DIP_SRC_FORCE_FRM_1                 0x01
        #define DIP_SRC_FORCE_FRM_2                 0x02
        #define DIP_SRC_FORCE_FRM_3                 0x03
        #define DIP_SRC_FORCE_FRM_4                 0x04
        #define DIP_SRC_FORCE_FRM_5                 0x05
        #define DIP_SRC_FORCE_FRM_6                 0x06
        #define DIP_SRC_FORCE_FRM_7                 0x07
        /*------------------------------------------------------------*/
    u32 reg_dipr_top_field_inv      : 1;
    u32 reg_dipr_2_fd               : 1;
    u32 reg_dipr_pdw2mi_sel_ext     : 1;
    u32 reg_dipr_sw_trig            : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SW_TRIGGER                      0x01
        /*------------------------------------------------------------*/
    u32                             : 16;
    // h7D
    u32 reg_dipr_req_thrd           : 6;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_READ_REQ_THRD_MASK          0x003F
        #define DIP_SRC_READ_REQ_THRD(x)            ((x) & DIP_SRC_READ_REQ_THRD_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dipr_format             : 2;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_COLOR_FORMAT_MASK           0x003
        #define DIP_SRC_COLOR_FORMAT(x)             ((x) & DIP_SRC_COLOR_FORMAT_MASK)
        #define DIP_SRC_COLOR_FORMAT_YUV422         0x00
        #define DIP_SRC_COLOR_FORMAT_RGB            0x02
        #define DIP_SRC_COLOR_FORMAT_YUV420         0x03
        /*------------------------------------------------------------*/
    u32 reg_dipr_hi_pri_num         : 5;
    u32 reg_dipr_force_rreq_thrd    : 1;
    u32 reg_dipr_en                 : 1;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_R_EN_MASK                       0x0001
        #define DIP_R_SET_EN                        ((x) & DIP_R_EN_MASK)
        #define DIP_R_OFF                           0x00
        #define DIP_R_EN                            0x01
        /*------------------------------------------------------------*/
    u32 reg_dipr_pdw2mi_sel         : 1;
    u32                             : 16;
    // h7E
    u32 reg_dip_tile_req_num        : 7;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_DEST_TILE_BURST_LENGTH_MASK     0x007F
        #define DIP_DEST_TILE_BURST_LENGTH(x)       ((x) & DIP_DEST_TILE_BURST_LENGTH_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dip_yuvi_force_base     : 1;
    u32 reg_422to444_md             : 2;
    u32 reg_cr_load_ini             : 1;
    u32 reg_dip_y2r_en              : 1;
    u32 reg_dipw_clip_en            : 1;
    u32 reg_dip_rgb_swap            : 1;
    u32 reg_dip_i420                : 1;
    u32 reg_dipw2mi_i64             : 1;
    u32                             : 16;
    // h7F
    u32 reg_dipr_tile_req_num       : 7;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_TILE_BURST_LENGTH_MASK      0x007F
        #define DIP_SRC_TILE_BURST_LENGTH(x)        ((x) & DIP_SRC_TILE_BURST_LENGTH_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dipw_db_en              : 1;
    u32 reg_dipr_req_max            : 7;
        /*-DEFINE-----------------------------------------------------*/
        #define DIP_SRC_READ_REQ_MAX_NUM_MASK       0x007F
        #define DIP_SRC_READ_REQ_MAX_NUM(x)         ((x) &  DIP_SRC_READ_REQ_MAX_NUM_MASK)
        /*------------------------------------------------------------*/
    u32 reg_dipr_intlac_r           : 1;
    u32                             : 16;
} KeDipPdw_t;

extern volatile KeDipHvsp_t *   const g_ptDipHvsp;
extern volatile KeDipTop_t *    const g_ptDipTop;
extern volatile KeDipPdw_t *    const g_ptDipPdw;

#endif //__KERNEL_DIP_H__
