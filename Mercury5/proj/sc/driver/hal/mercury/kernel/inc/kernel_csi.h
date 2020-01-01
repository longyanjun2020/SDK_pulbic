#ifndef __KERNEL_CSI_H__
#define __KERNEL_CSI_H__

#include "cpu_mem_map.hc"

typedef struct CSImac_s {
	// h0000, bit: 0
	/* */
	unsigned int :1;

	// h0000, bit: 1
	/* error correction off*/
	#define offset_of_csimac_reg_ecc_off (0)
	#define mask_of_csimac_reg_ecc_off (0x2)
	unsigned int reg_ecc_off:1;

	// h0000, bit: 5
	/* data lane enable
	[0]: lane0 enable
	[1]: lane1 enable
	[2]: lane2 enable
	[3] lane3 enable*/
	#define offset_of_csimac_reg_lane_en (0)
	#define mask_of_csimac_reg_lane_en (0x3c)
	unsigned int reg_lane_en:4;

#define CSI_LAN0_EN 0x01
#define CSI_LAN1_EN 0x02
#define CSI_LAN2_EN 0x04
#define CSI_LAN3_EN 0x08

	// h0000, bit: 6
	/* remove erroneous start of transmission (sot)*/
	#define offset_of_csimac_reg_rm_err_sot (0)
	#define mask_of_csimac_reg_rm_err_sot (0x40)
	unsigned int reg_rm_err_sot:1;

	// h0000, bit: 8
	/* mac function mode
	0: normal mode
	1: one frame mode
	2: stream bypass
	3: stream bypass*/
	#define offset_of_csimac_reg_fun_md (0)
	#define mask_of_csimac_reg_fun_md (0x180)
	unsigned int reg_fun_md:2;

	// h0000, bit: 12
	/* virtual channel enable
	[0]: vc0 enable
	[1]: vc1 enable
	[2]: vc2 enable
	[3]: vc3 enable*/
	#define offset_of_csimac_reg_vc_en (0)
	#define mask_of_csimac_reg_vc_en (0x1e00)
	unsigned int reg_vc_en:4;
	
#define CSI_VC0_EN 0x01
#define CSI_VC1_EN 0x02
#define CSI_VC2_EN 0x04
#define CSI_VC3_EN 0x08

	// h0000, bit: 13
	/* remove erroneous frame start (fs)*/
	#define offset_of_csimac_reg_rm_err_fs (0)
	#define mask_of_csimac_reg_rm_err_fs (0x2000)
	unsigned int reg_rm_err_fs:1;

	// h0000, bit: 14
	/* YUV422 8bit output mode
	0: YU / YV (highByte: Y, LowByte : U/V)
	1: UY / VY (highByte: U/V, LowByte : Y)*/
	#define offset_of_csimac_reg_uy_vy_sel (0)
	#define mask_of_csimac_reg_uy_vy_sel (0x4000)
	unsigned int reg_uy_vy_sel:1;

	// h0000, bit: 15
	/* */
	unsigned int :1;

	// h0000
	unsigned int /* padding 16 bit */:16;

	// h0001, bit: 2
	/* virtual channel0 hsync. mode
	0: packet header edge
	1: line end edge
	2: line start edge
	3: packet footer edge
	Others: packet header edge
	*/
	#define offset_of_csimac_reg_vc0_hs_mode (2)
	#define mask_of_csimac_reg_vc0_hs_mode (0x7)
	unsigned int reg_vc0_hs_mode:3;

	// h0001, bit: 5
	/* virtual channel1 hsync. mode*/
	#define offset_of_csimac_reg_vc1_hs_mode (2)
	#define mask_of_csimac_reg_vc1_hs_mode (0x38)
	unsigned int reg_vc1_hs_mode:3;

	// h0001, bit: 8
	/* virtual channel2 hsync. mode*/
	#define offset_of_csimac_reg_vc2_hs_mode (2)
	#define mask_of_csimac_reg_vc2_hs_mode (0x1c0)
	unsigned int reg_vc2_hs_mode:3;

	// h0001, bit: 11
	/* virtual channel3 hsync. mode*/
	#define offset_of_csimac_reg_vc3_hs_mode (2)
	#define mask_of_csimac_reg_vc3_hs_mode (0xe00)
	unsigned int reg_vc3_hs_mode:3;

	// h0001, bit: 14
	/* 1: lane_merge phy clk domain signals
	2: lane_merge mac clk domain signals
	3: ecc related debug signals
	4: packet decode related debug signals
	5: packet decode related debug signals
	6: timing gen related debug signals
	7: unpack related debug signals
	8: dphy related debug signals
	9: clkgen related debug signals*/
	#define offset_of_csimac_reg_debug_sel (2)
	#define mask_of_csimac_reg_debug_sel (0xf000)
	unsigned int reg_debug_sel:4;

	// h0001
	unsigned int /* padding 16 bit */:16;

	// h0002, bit: 2
	/* virtual channel0 vsync. mode
	0: frame start edge
	1: frame end edge
	others: frame start edge*/
	#define offset_of_csimac_reg_vc0_vs_mode (4)
	#define mask_of_csimac_reg_vc0_vs_mode (0x7)
	unsigned int reg_vc0_vs_mode:3;

	// h0002, bit: 5
	/* virtual channel1 vsync. mode*/
	#define offset_of_csimac_reg_vc1_vs_mode (4)
	#define mask_of_csimac_reg_vc1_vs_mode (0x38)
	unsigned int reg_vc1_vs_mode:3;

	// h0002, bit: 8
	/* virtual channel2 vsync. mode*/
	#define offset_of_csimac_reg_vc2_vs_mode (4)
	#define mask_of_csimac_reg_vc2_vs_mode (0x1c0)
	unsigned int reg_vc2_vs_mode:3;

	// h0002, bit: 11
	/* virtual channel3 vsync. mode*/
	#define offset_of_csimac_reg_vc3_vs_mode (4)
	#define mask_of_csimac_reg_vc3_vs_mode (0xe00)
	unsigned int reg_vc3_vs_mode:3;

//#define CSI_V_SYNC_MODE_FS 0x00
//#define CSI_V_SYNC_MODE_FE 0x01

	// h0002, bit: 12
	/* {reg_g8spd_wc, reg_g8spd_dt} =
	 reg_debug_en ? mac_debug_out : {g8spd_wc, g8spd_dt} */
	#define offset_of_csimac_reg_debug_en (4)
	#define mask_of_csimac_reg_debug_en (0x1000)
	unsigned int reg_debug_en:1;

	// h0002, bit: 14
	/* */
	unsigned int :3;

	// h0002
	unsigned int /* padding 16 bit */:16;

	// h0003, bit: 14
	/* mac layer interrupt mask
	[14]: overrun_err
	[13]: ls_err
	[12]: le_err
	[11]: con_fs_err (consecutive fs)
	[10]: con_fe_err (consecutive fe)
	[9]: raw10_lens_err (not 5n alignment)
	[8]: pa_wc_eq0 (payload word count eqaul to 0)
	[7]: crc error
	[6]: ecc 2bit error
	[5]: frame end error
	[4]: frame start error (hardware auto-ignore)
	[3]: ecc 1bit error (hardware auto-correct)
	[2]: ph_lens_err (packet header lengths error)
	[1]: pa_lens_err (payload lenghts error shorten than wc)
	[0]: dt_err (reserved and not supported data type)*/
	#define offset_of_csimac_reg_mac_err_int_mask (6)
	#define mask_of_csimac_reg_mac_err_int_mask (0x7fff)
	unsigned int reg_mac_err_int_mask:15;

#define MAC_ERR_INT_OVERRUN_ERR (0x4000)
#define MAC_ERR_INT_LS_ERR (0x2000)
#define MAC_ERR_INT_LE_ERR (0x1000)
#define MAC_ERR_INT_CON_FS_ERR (0x0800)
#define MAC_ERR_INT_CON_FE_ERR (0x0400)
#define MAC_ERR_INT_RAW10_LENS_ERR (0x0200)
#define MAC_ERR_INT_PA_WC_EQ0 (0x0100)
#define MAC_ERR_INT_CRC_ERROR (0x0080)
#define MAC_ERR_INT_ECC_2BIT_ERR (0x0040)
#define MAC_ERR_INT_FRAME_END_ERR (0x0020)
#define MAC_ERR_INT_FRAME_START_ERR (0x0010)
#define MAC_ERR_INT_ECC_1BIT_ERR (0x0008)
#define MAC_ERR_INT_PH_LENS_ERR (0x0004)
#define MAC_ERR_INT_PA_LENS_ERR (0x0002)
#define MAC_ERR_INT_DT_ERR (0x0001)

	// h0003, bit: 15
	/* */
	unsigned int :1;

	// h0003
	unsigned int /* padding 16 bit */:16;

	// h0004, bit: 14
	/* mac layer error interrupt force*/
	#define offset_of_csimac_reg_mac_err_int_force (8)
	#define mask_of_csimac_reg_mac_err_int_force (0x7fff)
	unsigned int reg_mac_err_int_force:15;

	// h0004, bit: 15
	/* */
	unsigned int :1;

	// h0004
	unsigned int /* padding 16 bit */:16;

	// h0005, bit: 14
	/* mac layer error interrupt clear*/
	#define offset_of_csimac_reg_mac_err_int_clr (10)
	#define mask_of_csimac_reg_mac_err_int_clr (0x7fff)
	unsigned int reg_mac_err_int_clr:15;

	// h0005, bit: 15
	/* */
	unsigned int :1;

	// h0005
	unsigned int /* padding 16 bit */:16;

	// h0006, bit: 6
	/* mac layer report interrupt mask
	[6] report vc0 frame done
	[5] report vc1 frame done
	[4] report vc2 frame done
	[3] report vc3 frame done
	[2] report generic 8 bit short packet data
	[1] report frame number
	[0] report line number*/
	#define offset_of_csimac_reg_mac_rpt_int_mask (12)
	#define mask_of_csimac_reg_mac_rpt_int_mask (0x7f)
	unsigned int reg_mac_rpt_int_mask:7;
	
#define CSI_LINE_INT    0x01
#define CSI_FRAME_INT  0x02
#define CSI_VC3_FE_INT  0x08
#define CSI_VC2_FE_INT  0x10
#define CSI_VC1_FE_INT  0x20
#define CSI_VC0_INT    0x40  //FS or FE depend on reg_mac_rpt_int_src[1] selection

	// h0006, bit: 14
	/* */
	unsigned int :9;

	// h0006
	unsigned int /* padding 16 bit */:16;

	// h0007, bit: 6
	/* mac layer report interrupt force*/
	#define offset_of_csimac_reg_mac_rpt_int_force (14)
	#define mask_of_csimac_reg_mac_rpt_int_force (0x7f)
	unsigned int reg_mac_rpt_int_force:7;

	// h0007, bit: 14
	/* */
	unsigned int :9;

	// h0007
	unsigned int /* padding 16 bit */:16;

	// h0008, bit: 6
	/* mac layer report interrupt clear*/
	#define offset_of_csimac_reg_mac_rpt_int_clr (16)
	#define mask_of_csimac_reg_mac_rpt_int_clr (0x7f)
	unsigned int reg_mac_rpt_int_clr:7;

	// h0008, bit: 14
	/* */
	unsigned int :9;

	// h0008
	unsigned int /* padding 16 bit */:16;

	// h0009, bit: 9
	/* phy layer interrupt mask
	[0]: err_control0
	[1]: err_sync_esc0
	[2]: err_esc0
	[3]: err_sot_sync_hs0
	[4]: err_sot_hs0
	[5]: err_control1
	[6]: err_sync_esc1
	[7]: err_esc1
	[8]: err_sot_sync_hs1
	[9]: err_sot_hs1*/
	#define offset_of_csimac_reg_phy_int_mask (18)
	#define mask_of_csimac_reg_phy_int_mask (0x3ff)
	unsigned int reg_phy_int_mask:10;

#define ERR_CONTROL0 (0x0001)
#define ERR_SYNC_ESC0 (0x0002)
#define ERR_ESC0 (0x0004)
#define ERR_SOT_SYNC_HS0 (0x0008)
#define ERR_SOT_HS0 (0x0010)
#define ERR_CONTROL1 (0x0020)
#define ERR_SYNC_ESC1 (0x0040)
#define ERR_ESC1 (0x0080)
#define ERR_SOT_SYNC_HS1 (0x0100)
#define ERR_SOT_HS1 (0x0200)

	// h0009, bit: 14
	/* */
	unsigned int :6;

	// h0009
	unsigned int /* padding 16 bit */:16;

	// h000a, bit: 9
	/* phy layer interrupt force*/
	#define offset_of_csimac_reg_phy_int_force (20)
	#define mask_of_csimac_reg_phy_int_force (0x3ff)
	unsigned int reg_phy_int_force:10;

	// h000a, bit: 14
	/* */
	unsigned int :6;

	// h000a
	unsigned int /* padding 16 bit */:16;

	// h000b, bit: 9
	/* phy layer interrupt clear*/
	#define offset_of_csimac_reg_phy_int_clr (22)
	#define mask_of_csimac_reg_phy_int_clr (0x3ff)
	unsigned int reg_phy_int_clr:10;

	// h000b, bit: 14
	/* */
	unsigned int :6;

	// h000b
	unsigned int /* padding 16 bit */:16;

	// h000c, bit: 14
	/* mac layer error interrupt source*/
	#define offset_of_csimac_reg_mac_err_int_src (24)
	#define mask_of_csimac_reg_mac_err_int_src (0x7fff)
	unsigned int reg_mac_err_int_src:15;

	// h000c, bit: 15
	/* */
	unsigned int :1;

	// h000c
	unsigned int /* padding 16 bit */:16;

	// h000d, bit: 14
	/* mac layer error interrupt raw source*/
	#define offset_of_csimac_reg_mac_err_int_raw_src (26)
	#define mask_of_csimac_reg_mac_err_int_raw_src (0x7fff)
	unsigned int reg_mac_err_int_raw_src:15;

	// h000d, bit: 15
	/* */
	unsigned int :1;

	// h000d
	unsigned int /* padding 16 bit */:16;

	// h000e, bit: 6
	/* mac layer report interrupt source*/
	#define offset_of_csimac_reg_mac_rpt_int_src (28)
	#define mask_of_csimac_reg_mac_rpt_int_src (0x7f)
	unsigned int reg_mac_rpt_int_src:7;

	// h000e, bit: 14
	/* */
	unsigned int :9;

	// h000e
	unsigned int /* padding 16 bit */:16;

	// h000f, bit: 6
	/* mac layer report interrupt raw source*/
	#define offset_of_csimac_reg_mac_rpt_int_raw_src (30)
	#define mask_of_csimac_reg_mac_rpt_int_raw_src (0x7f)
	unsigned int reg_mac_rpt_int_raw_src:7;

	// h000f, bit: 14
	/* */
	unsigned int :9;

	// h000f
	unsigned int /* padding 16 bit */:16;

	// h0010, bit: 9
	/* phy layer interrupt source*/
	#define offset_of_csimac_reg_phy_int_src (32)
	#define mask_of_csimac_reg_phy_int_src (0x3ff)
	unsigned int reg_phy_int_src:10;

	// h0010, bit: 14
	/* */
	unsigned int :6;

	// h0010
	unsigned int /* padding 16 bit */:16;

	// h0011, bit: 9
	/* phy layer interrupt raw source*/
	#define offset_of_csimac_reg_phy_int_raw_src (34)
	#define mask_of_csimac_reg_phy_int_raw_src (0x3ff)
	unsigned int reg_phy_int_raw_src:10;

	// h0011, bit: 14
	/* */
	unsigned int :6;

	// h0011
	unsigned int /* padding 16 bit */:16;

	// h0012, bit: 14
	/* frame number*/
	#define offset_of_csimac_reg_frm_num (36)
	#define mask_of_csimac_reg_frm_num (0xffff)
	unsigned int reg_frm_num:16;

	// h0012
	unsigned int /* padding 16 bit */:16;

	// h0013, bit: 14
	/* line number*/
	#define offset_of_csimac_reg_line_num (38)
	#define mask_of_csimac_reg_line_num (0xffff)
	unsigned int reg_line_num:16;

	// h0013
	unsigned int /* padding 16 bit */:16;

	// h0014, bit: 14
	/* gereric 8 bit short packet data (word count)*/
	#define offset_of_csimac_reg_g8spd_wc (40)
	#define mask_of_csimac_reg_g8spd_wc (0xffff)
	unsigned int reg_g8spd_wc:16;

	// h0014
	unsigned int /* padding 16 bit */:16;

	// h0015, bit: 7
	/* gereric 8 bit short packet data (data type)*/
	#define offset_of_csimac_reg_g8spd_dt (42)
	#define mask_of_csimac_reg_g8spd_dt (0xff)
	unsigned int reg_g8spd_dt:8;

	// h0015, bit: 14
	/* */
	unsigned int :8;

	// h0015
	unsigned int /* padding 16 bit */:16;

	// h0016, bit: 0
	/* mac engine idle*/
	#define offset_of_csimac_reg_mac_idle (44)
	#define mask_of_csimac_reg_mac_idle (0x1)
	unsigned int reg_mac_idle:1;

	// h0016, bit: 14
	/* */
	unsigned int :15;

	// h0016
	unsigned int /* padding 16 bit */:16;

	// h0017, bit: 0
	/* 1 frame trigger*/
	#define offset_of_csimac_reg_1frame_trig (46)
	#define mask_of_csimac_reg_1frame_trig (0x1)
	unsigned int reg_1frame_trig:1;

	// h0017, bit: 14
	/* */
	unsigned int :15;

	// h0017
	unsigned int /* padding 16 bit */:16;

	// h0018, bit: 5
	/* [0]: clk_csi_mac_gate
	[1]: clk_csi_mac_inv
	[5:2]: clk_csi_mac_sel
	0: clk_csi_mac
	1: clk_csi_mac_div2
	2: clk_csi_mac_div4
	3: clk_csi_mac_div8
	4: clk_csi_mac_div16
	5: clk_csi_mac_div32
	6: clk_csi_mac_div64
	7: clk_csi_mac_div128*/
	#define offset_of_csimac_reg_ckg_csi_mac (48)
	#define mask_of_csimac_reg_ckg_csi_mac (0x3f)
	unsigned int reg_ckg_csi_mac:6;

#define CLK_CSI_MAC_DIV1 (0x0001)
#define CLK_CSI_MAC_DIV2 (0x0002)
#define CLK_CSI_MAC_DIV4 (0x0004)
#define CLK_CSI_MAC_DIV8 (0x0008)
#define CLK_CSI_MAC_DIV16 (0x0010)
#define CLK_CSI_MAC_DIV32 (0x0020)
#define CLK_CSI_MAC_DIV64 (0x0040)
#define CLK_CSI_MAC_DIV128 (0x0080)

	// h0018, bit: 7
	/* */
	unsigned int :2;

	// h0018, bit: 12
	/* [0]: clk_csi_mac_lptx_gate
	[1]: clk_csi_mac_lptx_inv
	[4:2]: clk_csi_mac_lptx_sel
	0: clk_csi_mac_lptx
	1: clk_csi_mac_lptx_div2
	2: clk_csi_mac_lptx_div4
	3: clk_csi_mac_lptx_div8
	4: clk_csi_mac_lptx_div16
	5: clk_csi_mac_lptx_div32
	6: clk_csi_mac_lptx_div64
	7: clk_csi_mac_lptx_div128*/
	#define offset_of_csimac_reg_ckg_csi_mac_lptx (48)
	#define mask_of_csimac_reg_ckg_csi_mac_lptx (0x1f00)
	unsigned int reg_ckg_csi_mac_lptx:5;

	// h0018, bit: 14
	/* */
	unsigned int :3;

	// h0018
	unsigned int /* padding 16 bit */:16;

	// h0019, bit: 4
	/* [0]: clk_ns_gate
	[1]: clk_ns_inv
	[4:2]: clk_ns_sel
	0: clk_ns
	1: clk_ns_div2
	2: clk_ns_div4
	3: clk_ns_div8
	4: clk_ns_div16
	5: clk_ns_div32
	6: clk_ns_div64
	7: clk_ns_div128*/
	#define offset_of_csimac_reg_ckg_ns (50)
	#define mask_of_csimac_reg_ckg_ns (0x1f)
	unsigned int reg_ckg_ns:5;

	// h0019, bit: 14
	/* */
	unsigned int :11;

	// h0019
	unsigned int /* padding 16 bit */:16;

	// h001a, bit: 14
	/* */
	#define offset_of_csimac_reg_csi_mac_reserved (52)
	#define mask_of_csimac_reg_csi_mac_reserved (0xffff)
	unsigned int reg_csi_mac_reserved:16;

	// h001a
	unsigned int /* padding 16 bit */:16;

	// h001b, bit: 14
	/* */
	#define offset_of_csimac_reg_csi_mac_reserved1 (54)
	#define mask_of_csimac_reg_csi_mac_reserved1 (0xffff)
	unsigned int reg_csi_mac_reserved1:16;

	// h001b
	unsigned int /* padding 16 bit */:16;

	// h001c, bit: 14
	/* */
	#define offset_of_csimac_reg_csi_mac_reserved2 (56)
	#define mask_of_csimac_reg_csi_mac_reserved2 (0xffff)
	unsigned int reg_csi_mac_reserved2:16;

	// h001c
	unsigned int /* padding 16 bit */:16;

	// h001d, bit: 14
	/* long packet type enable
	[0]: Null
	[1]: blinking
	[2]: embedded
	[14]: YUV422_8B
	[26]: RAW8
	[27]: RAW10
	[28]: RAW12
	[32]: UD1
	[33]: UD2
	[34]: UD3
	[35]: UD4
	[36]: UD5
	[37]: UD6
	[38]: UD7
	[39]: UD8*/
	#define offset_of_csimac_reg_dt_en (58)
	#define mask_of_csimac_reg_dt_en (0xffff)
	unsigned int reg_dt_en:16;

	// h001d
	unsigned int /* padding 16 bit */:16;

	// h001e, bit: 14
	/* long packet type enable
	[0]: Null
	[1]: blinking
	[2]: embedded
	[14]: YUV422_8B
	[26]: RAW8
	[27]: RAW10
	[28]: RAW12
	[32]: UD1
	[33]: UD2
	[34]: UD3
	[35]: UD4
	[36]: UD5
	[37]: UD6
	[38]: UD7
	[39]: UD8*/
	#define offset_of_csimac_reg_dt_en_1 (60)
	#define mask_of_csimac_reg_dt_en_1 (0xffff)
	unsigned int reg_dt_en_1:16;

	// h001e
	unsigned int /* padding 16 bit */:16;

	// h001f, bit: 14
	/* long packet type enable
	[0]: Null
	[1]: blinking
	[2]: embedded
	[14]: YUV422_8B
	[26]: RAW8
	[27]: RAW10
	[28]: RAW12
	[32]: UD1
	[33]: UD2
	[34]: UD3
	[35]: UD4
	[36]: UD5
	[37]: UD6
	[38]: UD7
	[39]: UD8*/
	#define offset_of_csimac_reg_dt_en_2 (62)
	#define mask_of_csimac_reg_dt_en_2 (0xffff)
	unsigned int reg_dt_en_2:16;

	// h001f
	unsigned int /* padding 16 bit */:16;

	// h0020, bit: 0
	/* software reset*/
	#define offset_of_csimac_reg_sw_rst (64)
	#define mask_of_csimac_reg_sw_rst (0x1)
	unsigned int reg_sw_rst:1;

	// h0020, bit: 1
	/* mac enable*/
	#define offset_of_csimac_reg_mac_en (64)
	#define mask_of_csimac_reg_mac_en (0x2)
	unsigned int reg_mac_en:1;

	// h0020, bit: 2
	/* enable don't care data type*/
	#define offset_of_csimac_reg_dont_care_dt (64)
	#define mask_of_csimac_reg_dont_care_dt (0x4)
	unsigned int reg_dont_care_dt:1;

	// h0020, bit: 14
	/* */
	unsigned int :13;

	// h0020
	unsigned int /* padding 16 bit */:16;

	// h0021, bit: 1
	/* select one lane's act and sync signal to generate sot*/
	#define offset_of_csimac_reg_raw_l_sot_sel (66)
	#define mask_of_csimac_reg_raw_l_sot_sel (0x3)
	unsigned int reg_raw_l_sot_sel:2;

	// h0021, bit: 2
	/* select sot source: 0:from d-phy, 1:auto gen*/
	#define offset_of_csimac_reg_sot_sel (66)
	#define mask_of_csimac_reg_sot_sel (0x4)
	unsigned int reg_sot_sel:1;

	// h0021, bit: 3
	/* select sot source: 0:from d-phy, 1:auto gen*/
	#define offset_of_csimac_reg_eot_sel (66)
	#define mask_of_csimac_reg_eot_sel (0x8)
	unsigned int reg_eot_sel:1;

	// h0021, bit: 4
	/* select  report frame num. Condition: 0:frame start 1:frame end*/
	#define offset_of_csimac_reg_rpt_fnum_cond (66)
	#define mask_of_csimac_reg_rpt_fnum_cond (0x10)
	unsigned int reg_rpt_fnum_cond:1;

#define CSI_RPT_FS 0x0    //report frame start
#define CSI_RTP_FE 0x01  //report frame end

	// h0021, bit: 5
	/* select  report line num. Condition: 0:line start 1:line end*/
	#define offset_of_csimac_reg_rpt_lnum_cond (66)
	#define mask_of_csimac_reg_rpt_lnum_cond (0x20)
	unsigned int reg_rpt_lnum_cond:1;

	// h0021, bit: 14
	/* */
	unsigned int :10;

	// h0021
	unsigned int /* padding 16 bit */:16;

	// h0022, bit: 14
	/* */
	unsigned int :16;

	// h0022
	unsigned int /* padding 16 bit */:16;

	// h0023, bit: 14
	/* */
	unsigned int :16;

	// h0023
	unsigned int /* padding 16 bit */:16;

	// h0024, bit: 14
	/* */
	unsigned int :16;

	// h0024
	unsigned int /* padding 16 bit */:16;

	// h0025, bit: 14
	/* */
	unsigned int :16;

	// h0025
	unsigned int /* padding 16 bit */:16;

	// h0026, bit: 14
	/* */
	unsigned int :16;

	// h0026
	unsigned int /* padding 16 bit */:16;

	// h0027, bit: 14
	/* */
	unsigned int :16;

	// h0027
	unsigned int /* padding 16 bit */:16;

	// h0028, bit: 14
	/* clk lane FSM status interrupt mask*/
	#define offset_of_csimac_reg_clk_lane_fsm_sts_int_mask (80)
	#define mask_of_csimac_reg_clk_lane_fsm_sts_int_mask (0xffff)
	unsigned int reg_clk_lane_fsm_sts_int_mask:16;

	// h0028
	unsigned int /* padding 16 bit */:16;

	// h0029, bit: 14
	/* clk lane FSM status interrupt force*/
	#define offset_of_csimac_reg_clk_lane_fsm_sts_int_force (82)
	#define mask_of_csimac_reg_clk_lane_fsm_sts_int_force (0xffff)
	unsigned int reg_clk_lane_fsm_sts_int_force:16;

	// h0029
	unsigned int /* padding 16 bit */:16;

	// h002a, bit: 14
	/* clk lane FSM status interrupt clear*/
	#define offset_of_csimac_reg_clk_lane_fsm_sts_int_clr (84)
	#define mask_of_csimac_reg_clk_lane_fsm_sts_int_clr (0xffff)
	unsigned int reg_clk_lane_fsm_sts_int_clr:16;

	// h002a
	unsigned int /* padding 16 bit */:16;

	// h002b, bit: 14
	/* clk lane FSM status interrupt source*/
	#define offset_of_csimac_reg_clk_lane_fsm_sts_int_src (86)
	#define mask_of_csimac_reg_clk_lane_fsm_sts_int_src (0xffff)
	unsigned int reg_clk_lane_fsm_sts_int_src:16;

	// h002b
	unsigned int /* padding 16 bit */:16;

	// h002c, bit: 14
	/* clk lane FSM status interrupt raw source*/
	#define offset_of_csimac_reg_clk_lane_fsm_sts_int_raw_src (88)
	#define mask_of_csimac_reg_clk_lane_fsm_sts_int_raw_src (0xffff)
	unsigned int reg_clk_lane_fsm_sts_int_raw_src:16;

	// h002c
	unsigned int /* padding 16 bit */:16;

	// h002d, bit: 14
	/* */
	unsigned int :16;

	// h002d
	unsigned int /* padding 16 bit */:16;

	// h002e, bit: 14
	/* */
	unsigned int :16;

	// h002e
	unsigned int /* padding 16 bit */:16;

	// h002f, bit: 14
	/* */
	unsigned int :16;

	// h002f
	unsigned int /* padding 16 bit */:16;

	// h0030, bit: 14
	/* data lane 0 FSM status interrupt mask*/
	#define offset_of_csimac_reg_data_lane0_fsm_sts_int_mask (96)
	#define mask_of_csimac_reg_data_lane0_fsm_sts_int_mask (0xffff)
	unsigned int reg_data_lane0_fsm_sts_int_mask:16;

	// h0030
	unsigned int /* padding 16 bit */:16;

	// h0031, bit: 14
	/* data lane 0 FSM status interrupt force*/
	#define offset_of_csimac_reg_data_lane0_fsm_sts_int_force (98)
	#define mask_of_csimac_reg_data_lane0_fsm_sts_int_force (0xffff)
	unsigned int reg_data_lane0_fsm_sts_int_force:16;

	// h0031
	unsigned int /* padding 16 bit */:16;

	// h0032, bit: 14
	/* data lane 0 FSM status interrupt clear*/
	#define offset_of_csimac_reg_data_lane0_fsm_sts_int_clr (100)
	#define mask_of_csimac_reg_data_lane0_fsm_sts_int_clr (0xffff)
	unsigned int reg_data_lane0_fsm_sts_int_clr:16;

	// h0032
	unsigned int /* padding 16 bit */:16;

	// h0033, bit: 14
	/* data lane 0 FSM status interrupt source*/
	#define offset_of_csimac_reg_data_lane0_fsm_sts_int_src (102)
	#define mask_of_csimac_reg_data_lane0_fsm_sts_int_src (0xffff)
	unsigned int reg_data_lane0_fsm_sts_int_src:16;

	// h0033
	unsigned int /* padding 16 bit */:16;

	// h0034, bit: 14
	/* data lane 0 FSM status interrupt raw source*/
	#define offset_of_csimac_reg_data_lane0_fsm_sts_int_raw_src (104)
	#define mask_of_csimac_reg_data_lane0_fsm_sts_int_raw_src (0xffff)
	unsigned int reg_data_lane0_fsm_sts_int_raw_src:16;

	// h0034
	unsigned int /* padding 16 bit */:16;

	// h0035, bit: 14
	/* */
	unsigned int :16;

	// h0035
	unsigned int /* padding 16 bit */:16;

	// h0036, bit: 14
	/* */
	unsigned int :16;

	// h0036
	unsigned int /* padding 16 bit */:16;

	// h0037, bit: 14
	/* */
	unsigned int :16;

	// h0037
	unsigned int /* padding 16 bit */:16;

	// h0038, bit: 14
	/* data lane 1 FSM status interrupt mask*/
	#define offset_of_csimac_reg_data_lane1_fsm_sts_int_mask (112)
	#define mask_of_csimac_reg_data_lane1_fsm_sts_int_mask (0xffff)
	unsigned int reg_data_lane1_fsm_sts_int_mask:16;

	// h0038
	unsigned int /* padding 16 bit */:16;

	// h0039, bit: 14
	/* data lane 1 FSM status interrupt force*/
	#define offset_of_csimac_reg_data_lane1_fsm_sts_int_force (114)
	#define mask_of_csimac_reg_data_lane1_fsm_sts_int_force (0xffff)
	unsigned int reg_data_lane1_fsm_sts_int_force:16;

	// h0039
	unsigned int /* padding 16 bit */:16;

	// h003a, bit: 14
	/* data lane 1 FSM status interrupt clear*/
	#define offset_of_csimac_reg_data_lane1_fsm_sts_int_clr (116)
	#define mask_of_csimac_reg_data_lane1_fsm_sts_int_clr (0xffff)
	unsigned int reg_data_lane1_fsm_sts_int_clr:16;

	// h003a
	unsigned int /* padding 16 bit */:16;

	// h003b, bit: 14
	/* data lane 1 FSM status interrupt source*/
	#define offset_of_csimac_reg_data_lane1_fsm_sts_int_src (118)
	#define mask_of_csimac_reg_data_lane1_fsm_sts_int_src (0xffff)
	unsigned int reg_data_lane1_fsm_sts_int_src:16;

	// h003b
	unsigned int /* padding 16 bit */:16;

	// h003c, bit: 14
	/* data lane 1 FSM status interrupt raw source*/
	#define offset_of_csimac_reg_data_lane1_fsm_sts_int_raw_src (120)
	#define mask_of_csimac_reg_data_lane1_fsm_sts_int_raw_src (0xffff)
	unsigned int reg_data_lane1_fsm_sts_int_raw_src:16;

	// h003c
	unsigned int /* padding 16 bit */:16;

	// h003d, bit: 0
	/* UD1 8-to-16 bit output mode*/
	#define offset_of_csimac_reg_8to16_mode (122)
	#define mask_of_csimac_reg_8to16_mode (0x1)
	unsigned int reg_8to16_mode:1;

	// h003d, bit: 14
	/* */
	unsigned int :15;

	// h003d
	unsigned int /* padding 16 bit */:16;

	// h003e, bit: 14
	/* */
	unsigned int :16;

	// h003e
	unsigned int /* padding 16 bit */:16;

	// h003f, bit: 14
	/* */
	unsigned int :16;

	// h003f
	unsigned int /* padding 16 bit */:16;

	// h0040, bit: 14
	/* */
	unsigned int :16;

	// h0040
	unsigned int /* padding 16 bit */:16;

	// h0041, bit: 14
	/* */
	unsigned int :16;

	// h0041
	unsigned int /* padding 16 bit */:16;

	// h0042, bit: 14
	/* */
	unsigned int :16;

	// h0042
	unsigned int /* padding 16 bit */:16;

	// h0043, bit: 14
	/* */
	unsigned int :16;

	// h0043
	unsigned int /* padding 16 bit */:16;

	// h0044, bit: 14
	/* */
	unsigned int :16;

	// h0044
	unsigned int /* padding 16 bit */:16;

	// h0045, bit: 14
	/* */
	unsigned int :16;

	// h0045
	unsigned int /* padding 16 bit */:16;

	// h0046, bit: 14
	/* */
	unsigned int :16;

	// h0046
	unsigned int /* padding 16 bit */:16;

	// h0047, bit: 14
	/* */
	unsigned int :16;

	// h0047
	unsigned int /* padding 16 bit */:16;

	// h0048, bit: 14
	/* */
	unsigned int :16;

	// h0048
	unsigned int /* padding 16 bit */:16;

	// h0049, bit: 14
	/* */
	unsigned int :16;

	// h0049
	unsigned int /* padding 16 bit */:16;

	// h004a, bit: 14
	/* */
	unsigned int :16;

	// h004a
	unsigned int /* padding 16 bit */:16;

	// h004b, bit: 14
	/* */
	unsigned int :16;

	// h004b
	unsigned int /* padding 16 bit */:16;

	// h004c, bit: 14
	/* */
	unsigned int :16;

	// h004c
	unsigned int /* padding 16 bit */:16;

	// h004d, bit: 0
	/* enable sony 290 326 sensor output*/
	#define offset_of_csimac_reg_sony_hdr (154)
	#define mask_of_csimac_reg_sony_hdr (0x1)
	unsigned int reg_sony_hdr:1;

	// h004d, bit: 1
	/* */
	unsigned int :1;

	// h004d, bit: 2
	/* for embedded 8-bit data HDR format*/
	#define offset_of_csimac_reg_raw8_ed (154)
	#define mask_of_csimac_reg_raw8_ed (0x4)
	unsigned int reg_raw8_ed:1;

	// h004d, bit: 3
	/* for embedded raw10 data HDR format*/
	#define offset_of_csimac_reg_raw10_ed (154)
	#define mask_of_csimac_reg_raw10_ed (0x8)
	unsigned int reg_raw10_ed:1;

	// h004d, bit: 4
	/* for embedded raw12 data HDR format*/
	#define offset_of_csimac_reg_raw12_ed (154)
	#define mask_of_csimac_reg_raw12_ed (0x10)
	unsigned int reg_raw12_ed:1;

	// h004d, bit: 14
	/* */
	unsigned int :11;

	// h004d
	unsigned int /* padding 16 bit */:16;

	// h004e, bit: 14
	/* */
	unsigned int :16;

	// h004e
	unsigned int /* padding 16 bit */:16;

	// h004f, bit: 14
	/* */
	unsigned int :16;

	// h004f
	unsigned int /* padding 16 bit */:16;

	// h0050, bit: 14
	/* */
	unsigned int :16;

	// h0050
	unsigned int /* padding 16 bit */:16;

	// h0051, bit: 14
	/* */
	unsigned int :16;

	// h0051
	unsigned int /* padding 16 bit */:16;

	// h0052, bit: 14
	/* */
	unsigned int :16;

	// h0052
	unsigned int /* padding 16 bit */:16;

	// h0053, bit: 14
	/* */
	unsigned int :16;

	// h0053
	unsigned int /* padding 16 bit */:16;

	// h0054, bit: 14
	/* */
	unsigned int :16;

	// h0054
	unsigned int /* padding 16 bit */:16;

	// h0055, bit: 14
	/* */
	unsigned int :16;

	// h0055
	unsigned int /* padding 16 bit */:16;

	// h0056, bit: 14
	/* */
	unsigned int :16;

	// h0056
	unsigned int /* padding 16 bit */:16;

	// h0057, bit: 14
	/* */
	unsigned int :16;

	// h0057
	unsigned int /* padding 16 bit */:16;

	// h0058, bit: 14
	/* */
	unsigned int :16;

	// h0058
	unsigned int /* padding 16 bit */:16;

	// h0059, bit: 14
	/* */
	unsigned int :16;

	// h0059
	unsigned int /* padding 16 bit */:16;

	// h005a, bit: 14
	/* */
	unsigned int :16;

	// h005a
	unsigned int /* padding 16 bit */:16;

	// h005b, bit: 14
	/* */
	unsigned int :16;

	// h005b
	unsigned int /* padding 16 bit */:16;

	// h005c, bit: 14
	/* */
	unsigned int :16;

	// h005c
	unsigned int /* padding 16 bit */:16;

	// h005d, bit: 14
	/* */
	unsigned int :16;

	// h005d
	unsigned int /* padding 16 bit */:16;

	// h005e, bit: 14
	/* */
	unsigned int :16;

	// h005e
	unsigned int /* padding 16 bit */:16;

	// h005f, bit: 14
	/* */
	unsigned int :16;

	// h005f
	unsigned int /* padding 16 bit */:16;

	// h0060, bit: 14
	/* */
	unsigned int :16;

	// h0060
	unsigned int /* padding 16 bit */:16;

	// h0061, bit: 14
	/* */
	unsigned int :16;

	// h0061
	unsigned int /* padding 16 bit */:16;

	// h0062, bit: 14
	/* */
	unsigned int :16;

	// h0062
	unsigned int /* padding 16 bit */:16;

	// h0063, bit: 14
	/* */
	unsigned int :16;

	// h0063
	unsigned int /* padding 16 bit */:16;

	// h0064, bit: 14
	/* */
	unsigned int :16;

	// h0064
	unsigned int /* padding 16 bit */:16;

	// h0065, bit: 14
	/* */
	unsigned int :16;

	// h0065
	unsigned int /* padding 16 bit */:16;

	// h0066, bit: 14
	/* */
	unsigned int :16;

	// h0066
	unsigned int /* padding 16 bit */:16;

	// h0067, bit: 14
	/* */
	unsigned int :16;

	// h0067
	unsigned int /* padding 16 bit */:16;

	// h0068, bit: 14
	/* */
	unsigned int :16;

	// h0068
	unsigned int /* padding 16 bit */:16;

	// h0069, bit: 14
	/* */
	unsigned int :16;

	// h0069
	unsigned int /* padding 16 bit */:16;

	// h006a, bit: 14
	/* */
	unsigned int :16;

	// h006a
	unsigned int /* padding 16 bit */:16;

	// h006b, bit: 14
	/* */
	unsigned int :16;

	// h006b
	unsigned int /* padding 16 bit */:16;

	// h006c, bit: 14
	/* */
	unsigned int :16;

	// h006c
	unsigned int /* padding 16 bit */:16;

	// h006d, bit: 14
	/* */
	unsigned int :16;

	// h006d
	unsigned int /* padding 16 bit */:16;

	// h006e, bit: 14
	/* */
	unsigned int :16;

	// h006e
	unsigned int /* padding 16 bit */:16;

	// h006f, bit: 14
	/* */
	unsigned int :16;

	// h006f
	unsigned int /* padding 16 bit */:16;

	// h0070, bit: 14
	/* */
	unsigned int :16;

	// h0070
	unsigned int /* padding 16 bit */:16;

	// h0071, bit: 14
	/* */
	unsigned int :16;

	// h0071
	unsigned int /* padding 16 bit */:16;

	// h0072, bit: 14
	/* */
	unsigned int :16;

	// h0072
	unsigned int /* padding 16 bit */:16;

	// h0073, bit: 14
	/* */
	unsigned int :16;

	// h0073
	unsigned int /* padding 16 bit */:16;

	// h0074, bit: 14
	/* */
	unsigned int :16;

	// h0074
	unsigned int /* padding 16 bit */:16;

	// h0075, bit: 14
	/* */
	unsigned int :16;

	// h0075
	unsigned int /* padding 16 bit */:16;

	// h0076, bit: 14
	/* */
	unsigned int :16;

	// h0076
	unsigned int /* padding 16 bit */:16;

	// h0077, bit: 14
	/* */
	unsigned int :16;

	// h0077
	unsigned int /* padding 16 bit */:16;

	// h0078, bit: 14
	/* */
	unsigned int :16;

	// h0078
	unsigned int /* padding 16 bit */:16;

	// h0079, bit: 14
	/* */
	unsigned int :16;

	// h0079
	unsigned int /* padding 16 bit */:16;

	// h007a, bit: 14
	/* */
	unsigned int :16;

	// h007a
	unsigned int /* padding 16 bit */:16;

	// h007b, bit: 14
	/* */
	unsigned int :16;

	// h007b
	unsigned int /* padding 16 bit */:16;

	// h007c, bit: 14
	/* */
	unsigned int :16;

	// h007c
	unsigned int /* padding 16 bit */:16;

	// h007d, bit: 14
	/* */
	unsigned int :16;

	// h007d
	unsigned int /* padding 16 bit */:16;

	// h007e, bit: 14
	/* */
	unsigned int :16;

	// h007e
	unsigned int /* padding 16 bit */:16;

	// h007f, bit: 14
	/* */
	unsigned int :16;

	// h007f
	unsigned int /* padding 16 bit */:16;

} __attribute__((packed, aligned(1))) CSImac_t;

extern volatile CSImac_t * const g_ptCSI;

#endif
