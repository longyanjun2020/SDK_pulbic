#ifndef __KERNEL_REG_DPHY_CSI2__
#define __KERNEL_REG_DPHY_CSI2__

#include "cpu_mem_map.hc"

typedef struct DPHYAna_s{
	// h0000, bit: 0
	/* local software reset, active low*/
	#define offset_of_dphy_ana_reg_sw_rstz (0)
	#define mask_of_dphy_ana_reg_sw_rstz (0x1)
	unsigned int reg_sw_rstz:1;

	// h0000, bit: 1
	/* enable dyn gating clk_ns*/
	#define offset_of_dphy_ana_reg_en_gate_clk_ns (0)
	#define mask_of_dphy_ana_reg_en_gate_clk_ns (0x2)
	unsigned int reg_en_gate_clk_ns:1;

	// h0000, bit: 2
	/* clock divide 4.5X enable*/
	#define offset_of_dphy_ana_reg_clk4p5_diven (0)
	#define mask_of_dphy_ana_reg_clk4p5_diven (0x4)
	unsigned int reg_clk4p5_diven:1;

	// h0000, bit: 3
	/* LPTX VREG TSET EN*/
	#define offset_of_dphy_ana_reg_en_ldo_tst (0)
	#define mask_of_dphy_ana_reg_en_ldo_tst (0x8)
	unsigned int reg_en_ldo_tst:1;

	// h0000, bit: 5
	/* LPTX VREG select*/
	#define offset_of_dphy_ana_reg_ldo_vset (0)
	#define mask_of_dphy_ana_reg_ldo_vset (0x30)
	unsigned int reg_ldo_vset:2;

	// h0000, bit: 6
	/* power down LPTX VREG*/
	#define offset_of_dphy_ana_reg_pd_ldo (0)
	#define mask_of_dphy_ana_reg_pd_ldo (0x40)
	unsigned int reg_pd_ldo:1;

	// h0000, bit: 7
	/* */
	unsigned int :1;

	// h0000, bit: 10
	/* enable sw LPCD*/
	#define offset_of_dphy_ana_reg_en_sw_lpcd (0)
	#define mask_of_dphy_ana_reg_en_sw_lpcd (0x700)
	unsigned int reg_en_sw_lpcd:3;

	// h0000, bit: 11
	/* */
	unsigned int :1;

	// h0000, bit: 14
	/* sw LPCD*/
	#define offset_of_dphy_ana_reg_sw_lpcd (0)
	#define mask_of_dphy_ana_reg_sw_lpcd (0x7000)
	unsigned int reg_sw_lpcd:3;

	// h0000, bit: 15
	/* */
	unsigned int :1;

	// h0000
	unsigned int /* padding 16 bit */:16;

	// h0001, bit: 0
	/* pd hs mode*/
	#define offset_of_dphy_ana_reg_pd_ib_dphy (2)
	#define mask_of_dphy_ana_reg_pd_ib_dphy (0x1)
	unsigned int reg_pd_ib_dphy:1;

	// h0001, bit: 1
	/* pd whole dphy analog */
	#define offset_of_dphy_ana_reg_pd_dphy (2)
	#define mask_of_dphy_ana_reg_pd_dphy (0x2)
	unsigned int reg_pd_dphy:1;

	// h0001, bit: 3
	/* rx pre-amp test*/
	#define offset_of_dphy_ana_reg_hsrx_pre_test (2)
	#define mask_of_dphy_ana_reg_hsrx_pre_test (0xc)
	unsigned int reg_hsrx_pre_test:2;

	// h0001, bit: 6
	/* HSRX clock skew setting*/
	#define offset_of_dphy_ana_reg_rxclk_dly (2)
	#define mask_of_dphy_ana_reg_rxclk_dly (0x70)
	unsigned int reg_rxclk_dly:3;

	// h0001, bit: 7
	/* HSRX clock skew enable*/
	#define offset_of_dphy_ana_reg_rxclk_skewen (2)
	#define mask_of_dphy_ana_reg_rxclk_skewen (0x80)
	unsigned int reg_rxclk_skewen:1;

	// h0001, bit: 9
	/* LPREF test*/
	#define offset_of_dphy_ana_reg_lpref_test (2)
	#define mask_of_dphy_ana_reg_lpref_test (0x300)
	unsigned int reg_lpref_test:2;

	// h0001, bit: 11
	/* trimming bit
	00: 100%
	01: 91%
	10: 111%
	11: 125%*/
	#define offset_of_dphy_ana_reg_trim_rterm (2)
	#define mask_of_dphy_ana_reg_trim_rterm (0xc00)
	unsigned int reg_trim_rterm:2;

	// h0001, bit: 12
	/* disbale CD when ulps*/
	#define offset_of_dphy_ana_reg_dis_cd_ulps (2)
	#define mask_of_dphy_ana_reg_dis_cd_ulps (0x1000)
	unsigned int reg_dis_cd_ulps:1;

	// h0001, bit: 13
	/* SW settign ULPS */
	#define offset_of_dphy_ana_reg_sw_ulps (2)
	#define mask_of_dphy_ana_reg_sw_ulps (0x2000)
	unsigned int reg_sw_ulps:1;

	// h0001, bit: 14
	/* enable ULPS contorl by FSM*/
	#define offset_of_dphy_ana_reg_en_ulps (2)
	#define mask_of_dphy_ana_reg_en_ulps (0x4000)
	unsigned int reg_en_ulps:1;

	// h0001, bit: 15
	/* enable power down DPHY HS mode in ULPS*/
	#define offset_of_dphy_ana_reg_en_pd_ib_dphy_ulps (2)
	#define mask_of_dphy_ana_reg_en_pd_ib_dphy_ulps (0x8000)
	unsigned int reg_en_pd_ib_dphy_ulps:1;

	// h0001
	unsigned int /* padding 16 bit */:16;

	// h0002, bit: 1
	/* VREG setting*/
	#define offset_of_dphy_ana_reg_vreg_bit (4)
	#define mask_of_dphy_ana_reg_vreg_bit (0x3)
	unsigned int reg_vreg_bit:2;

	// h0002, bit: 2
	/* 1.8V enable*/
	#define offset_of_dphy_ana_reg_v18_en (4)
	#define mask_of_dphy_ana_reg_v18_en (0x4)
	unsigned int reg_v18_en:1;

	// h0002, bit: 3
	/* */
	unsigned int :1;

	// h0002, bit: 6
	/* LP-TX Resistor option*/
	#define offset_of_dphy_ana_reg_lptx_rsel (4)
	#define mask_of_dphy_ana_reg_lptx_rsel (0x70)
	unsigned int reg_lptx_rsel:3;

	// h0002, bit: 7
	/* */
	unsigned int :1;

	// h0002, bit: 10
	/* LP-TX Cap option*/
	#define offset_of_dphy_ana_reg_lptx_csel (4)
	#define mask_of_dphy_ana_reg_lptx_csel (0x700)
	unsigned int reg_lptx_csel:3;

	// h0002, bit: 11
	/* */
	unsigned int :1;

	// h0002, bit: 14
	/* test clock input*/
	#define offset_of_dphy_ana_reg_clk_test_ch (4)
	#define mask_of_dphy_ana_reg_clk_test_ch (0x7000)
	unsigned int reg_clk_test_ch:3;

	// h0002, bit: 15
	/* */
	unsigned int :1;

	// h0002
	unsigned int /* padding 16 bit */:16;

	// h0003, bit: 0
	/* sw setting dphy cken*/
	#define offset_of_dphy_ana_reg_sw_dphy_cken (6)
	#define mask_of_dphy_ana_reg_sw_dphy_cken (0x1)
	unsigned int reg_sw_dphy_cken:1;

	// h0003, bit: 1
	/* enable sw setting dphy cken*/
	#define offset_of_dphy_ana_reg_en_sw_dphy_cken (6)
	#define mask_of_dphy_ana_reg_en_sw_dphy_cken (0x2)
	unsigned int reg_en_sw_dphy_cken:1;

	// h0003, bit: 3
	/* */
	unsigned int :2;

	// h0003, bit: 6
	/* sw setting clklane_en*/
	#define offset_of_dphy_ana_reg_sw_clklane_en (6)
	#define mask_of_dphy_ana_reg_sw_clklane_en (0x70)
	unsigned int reg_sw_clklane_en:3;

	// h0003, bit: 7
	/* enable sw setting clklane_en*/
	#define offset_of_dphy_ana_reg_en_sw_clklane_en (6)
	#define mask_of_dphy_ana_reg_en_sw_clklane_en (0x80)
	unsigned int reg_en_sw_clklane_en:1;

	// h0003, bit: 14
	/* reg_pd_dphy delay time*/
	#define offset_of_dphy_ana_reg_pd_dphy_delay (6)
	#define mask_of_dphy_ana_reg_pd_dphy_delay (0xff00)
	unsigned int reg_pd_dphy_delay:8;

	// h0003
	unsigned int /* padding 16 bit */:16;

	// h0004, bit: 0
	/* ch0 sw setting LP TX p data*/
	#define offset_of_dphy_ana_reg_sw_lptx_dinp0 (8)
	#define mask_of_dphy_ana_reg_sw_lptx_dinp0 (0x1)
	unsigned int reg_sw_lptx_dinp0:1;

	// h0004, bit: 1
	/* ch0 enable sw setting LP_TX p data*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_dinp0 (8)
	#define mask_of_dphy_ana_reg_en_sw_lptx_dinp0 (0x2)
	unsigned int reg_en_sw_lptx_dinp0:1;

	// h0004, bit: 2
	/* ch0 sw setting LP TX n data*/
	#define offset_of_dphy_ana_reg_sw_lptx_dinn0 (8)
	#define mask_of_dphy_ana_reg_sw_lptx_dinn0 (0x4)
	unsigned int reg_sw_lptx_dinn0:1;

	// h0004, bit: 3
	/* ch0 enable sw setting LP_TX n data*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_dinn0 (8)
	#define mask_of_dphy_ana_reg_en_sw_lptx_dinn0 (0x8)
	unsigned int reg_en_sw_lptx_dinn0:1;

	// h0004, bit: 4
	/* ch0 sw setting lptx enable*/
	#define offset_of_dphy_ana_reg_sw_lptx_en0 (8)
	#define mask_of_dphy_ana_reg_sw_lptx_en0 (0x10)
	unsigned int reg_sw_lptx_en0:1;

	// h0004, bit: 5
	/* ch0 enable sw setting lptx enable*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_en0 (8)
	#define mask_of_dphy_ana_reg_en_sw_lptx_en0 (0x20)
	unsigned int reg_en_sw_lptx_en0:1;

	// h0004, bit: 6
	/* ch0 sw setting lprx power down, active low*/
	#define offset_of_dphy_ana_reg_sw_lprx_en0 (8)
	#define mask_of_dphy_ana_reg_sw_lprx_en0 (0x40)
	unsigned int reg_sw_lprx_en0:1;

	// h0004, bit: 7
	/* ch0 enable sw setting lprx power down*/
	#define offset_of_dphy_ana_reg_en_sw_lprx_en0 (8)
	#define mask_of_dphy_ana_reg_en_sw_lprx_en0 (0x80)
	unsigned int reg_en_sw_lprx_en0:1;

	// h0004, bit: 9
	/* ch0 sw setting outconf
	00 : HS_TX off
	01 : differential data
	1x : reserved*/
	#define offset_of_dphy_ana_reg_sw_outconf_ch0_bit (8)
	#define mask_of_dphy_ana_reg_sw_outconf_ch0_bit (0x300)
	unsigned int reg_sw_outconf_ch0_bit:2;

	// h0004, bit: 10
	/* */
	unsigned int :1;

	// h0004, bit: 11
	/* ch0 enable sw setting outconf*/
	#define offset_of_dphy_ana_reg_en_sw_outconf_ch0_bit (8)
	#define mask_of_dphy_ana_reg_en_sw_outconf_ch0_bit (0x800)
	unsigned int reg_en_sw_outconf_ch0_bit:1;

	// h0004, bit: 14
	/* */
	unsigned int :4;

	// h0004
	unsigned int /* padding 16 bit */:16;

	// h0005, bit: 7
	/* ch0 sw setting hs tx data*/
	#define offset_of_dphy_ana_reg_sw_dati_dphy_ch0_bit (10)
	#define mask_of_dphy_ana_reg_sw_dati_dphy_ch0_bit (0xff)
	unsigned int reg_sw_dati_dphy_ch0_bit:8;

	// h0005, bit: 8
	/* ch0 enable sw setting hs tx data*/
	#define offset_of_dphy_ana_reg_en_sw_dati_dphy_ch0_bit (10)
	#define mask_of_dphy_ana_reg_en_sw_dati_dphy_ch0_bit (0x100)
	unsigned int reg_en_sw_dati_dphy_ch0_bit:1;

	// h0005, bit: 9
	/* */
	unsigned int :1;

	// h0005, bit: 10
	/* ch0 sw setting hsrx_pdn*/
	#define offset_of_dphy_ana_reg_sw_hsrx_en_ch0 (10)
	#define mask_of_dphy_ana_reg_sw_hsrx_en_ch0 (0x400)
	unsigned int reg_sw_hsrx_en_ch0:1;

	// h0005, bit: 11
	/* ch0 enable sw setting hsx pdn*/
	#define offset_of_dphy_ana_reg_en_sw_hsrx_en_ch0 (10)
	#define mask_of_dphy_ana_reg_en_sw_hsrx_en_ch0 (0x800)
	unsigned int reg_en_sw_hsrx_en_ch0:1;

	// h0005, bit: 14
	/* */
	unsigned int :4;

	// h0005
	unsigned int /* padding 16 bit */:16;

	// h0006, bit: 0
	/* ch0 hs tx polarity setting*/
	#define offset_of_dphy_ana_reg_ds_pol_ch0 (12)
	#define mask_of_dphy_ana_reg_ds_pol_ch0 (0x1)
	unsigned int reg_ds_pol_ch0:1;

	// h0006, bit: 1
	/* ch0 enable sw lane selection*/
	#define offset_of_dphy_ana_reg_en_sw_ch0_lanesel (12)
	#define mask_of_dphy_ana_reg_en_sw_ch0_lanesel (0x2)
	unsigned int reg_en_sw_ch0_lanesel:1;

	// h0006, bit: 3
	/* ch0 lane selection*/
	#define offset_of_dphy_ana_reg_sw_ch0_lanesel (12)
	#define mask_of_dphy_ana_reg_sw_ch0_lanesel (0xc)
	unsigned int reg_sw_ch0_lanesel:2;

	// h0006, bit: 11
	/* */
	unsigned int :8;

	// h0006, bit: 13
	/* ch0 data selection*/
	#define offset_of_dphy_ana_reg_ch0_dat_sel (12)
	#define mask_of_dphy_ana_reg_ch0_dat_sel (0x3000)
	unsigned int reg_ch0_dat_sel:2;

	// h0006, bit: 14
	/* */
	unsigned int :1;

	// h0006, bit: 15
	/* ch0 hs data MSB/LSB swap*/
	#define offset_of_dphy_ana_reg_ch0_hs_ml_swap (12)
	#define mask_of_dphy_ana_reg_ch0_hs_ml_swap (0x8000)
	unsigned int reg_ch0_hs_ml_swap:1;

	// h0006
	unsigned int /* padding 16 bit */:16;

	// h0007, bit: 14
	/* */
	unsigned int :16;

	// h0007
	unsigned int /* padding 16 bit */:16;

	// h0008, bit: 0
	/* ch1 sw setting LP TX p data*/
	#define offset_of_dphy_ana_reg_sw_lptx_dinp1 (16)
	#define mask_of_dphy_ana_reg_sw_lptx_dinp1 (0x1)
	unsigned int reg_sw_lptx_dinp1:1;

	// h0008, bit: 1
	/* ch1 enable sw setting LP_TX p data*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_dinp1 (16)
	#define mask_of_dphy_ana_reg_en_sw_lptx_dinp1 (0x2)
	unsigned int reg_en_sw_lptx_dinp1:1;

	// h0008, bit: 2
	/* ch1 sw setting LP TX n data*/
	#define offset_of_dphy_ana_reg_sw_lptx_dinn1 (16)
	#define mask_of_dphy_ana_reg_sw_lptx_dinn1 (0x4)
	unsigned int reg_sw_lptx_dinn1:1;

	// h0008, bit: 3
	/* ch1 enable sw setting LP_TX n data*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_dinn1 (16)
	#define mask_of_dphy_ana_reg_en_sw_lptx_dinn1 (0x8)
	unsigned int reg_en_sw_lptx_dinn1:1;

	// h0008, bit: 4
	/* ch1 sw setting lptx enable*/
	#define offset_of_dphy_ana_reg_sw_lptx_en1 (16)
	#define mask_of_dphy_ana_reg_sw_lptx_en1 (0x10)
	unsigned int reg_sw_lptx_en1:1;

	// h0008, bit: 5
	/* ch1 enable sw setting lptx enable*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_en1 (16)
	#define mask_of_dphy_ana_reg_en_sw_lptx_en1 (0x20)
	unsigned int reg_en_sw_lptx_en1:1;

	// h0008, bit: 6
	/* ch1 sw setting lprx power down, active low*/
	#define offset_of_dphy_ana_reg_sw_lprx_en1 (16)
	#define mask_of_dphy_ana_reg_sw_lprx_en1 (0x40)
	unsigned int reg_sw_lprx_en1:1;

	// h0008, bit: 7
	/* ch1 enable sw setting lprx power down*/
	#define offset_of_dphy_ana_reg_en_sw_lprx_en1 (16)
	#define mask_of_dphy_ana_reg_en_sw_lprx_en1 (0x80)
	unsigned int reg_en_sw_lprx_en1:1;

	// h0008, bit: 9
	/* ch1 sw setting outconf
	00 : HS_TX off
	01 : differential data
	1x : reserved*/
	#define offset_of_dphy_ana_reg_sw_outconf_ch1_bit (16)
	#define mask_of_dphy_ana_reg_sw_outconf_ch1_bit (0x300)
	unsigned int reg_sw_outconf_ch1_bit:2;

	// h0008, bit: 10
	/* */
	unsigned int :1;

	// h0008, bit: 11
	/* ch1 enable sw setting outconf*/
	#define offset_of_dphy_ana_reg_en_sw_outconf_ch1_bit (16)
	#define mask_of_dphy_ana_reg_en_sw_outconf_ch1_bit (0x800)
	unsigned int reg_en_sw_outconf_ch1_bit:1;

	// h0008, bit: 14
	/* */
	unsigned int :4;

	// h0008
	unsigned int /* padding 16 bit */:16;

	// h0009, bit: 7
	/* ch1 sw setting hs tx data*/
	#define offset_of_dphy_ana_reg_sw_dati_dphy_ch1_bit (18)
	#define mask_of_dphy_ana_reg_sw_dati_dphy_ch1_bit (0xff)
	unsigned int reg_sw_dati_dphy_ch1_bit:8;

	// h0009, bit: 8
	/* ch1 enable sw setting hs tx data*/
	#define offset_of_dphy_ana_reg_en_sw_dati_dphy_ch1_bit (18)
	#define mask_of_dphy_ana_reg_en_sw_dati_dphy_ch1_bit (0x100)
	unsigned int reg_en_sw_dati_dphy_ch1_bit:1;

	// h0009, bit: 9
	/* */
	unsigned int :1;

	// h0009, bit: 10
	/* ch1 sw setting hsrx_pdn*/
	#define offset_of_dphy_ana_reg_sw_hsrx_en_ch1 (18)
	#define mask_of_dphy_ana_reg_sw_hsrx_en_ch1 (0x400)
	unsigned int reg_sw_hsrx_en_ch1:1;

	// h0009, bit: 11
	/* ch1 enable sw setting hsx pdn*/
	#define offset_of_dphy_ana_reg_en_sw_hsrx_en_ch1 (18)
	#define mask_of_dphy_ana_reg_en_sw_hsrx_en_ch1 (0x800)
	unsigned int reg_en_sw_hsrx_en_ch1:1;

	// h0009, bit: 14
	/* */
	unsigned int :4;

	// h0009
	unsigned int /* padding 16 bit */:16;

	// h000a, bit: 0
	/* ch1 hs tx polarity setting*/
	#define offset_of_dphy_ana_reg_ds_pol_ch1 (20)
	#define mask_of_dphy_ana_reg_ds_pol_ch1 (0x1)
	unsigned int reg_ds_pol_ch1:1;

	// h000a, bit: 1
	/* ch1 enable sw lane selection*/
	#define offset_of_dphy_ana_reg_en_sw_ch1_lanesel (20)
	#define mask_of_dphy_ana_reg_en_sw_ch1_lanesel (0x2)
	unsigned int reg_en_sw_ch1_lanesel:1;

	// h000a, bit: 3
	/* ch1 lane selection*/
	#define offset_of_dphy_ana_reg_sw_ch1_lanesel (20)
	#define mask_of_dphy_ana_reg_sw_ch1_lanesel (0xc)
	unsigned int reg_sw_ch1_lanesel:2;

	// h000a, bit: 11
	/* */
	unsigned int :8;

	// h000a, bit: 13
	/* ch1 data selection*/
	#define offset_of_dphy_ana_reg_ch1_dat_sel (20)
	#define mask_of_dphy_ana_reg_ch1_dat_sel (0x3000)
	unsigned int reg_ch1_dat_sel:2;

	// h000a, bit: 14
	/* */
	unsigned int :1;

	// h000a, bit: 15
	/* ch1 hs data MSB/LSB swap*/
	#define offset_of_dphy_ana_reg_ch1_hs_ml_swap (20)
	#define mask_of_dphy_ana_reg_ch1_hs_ml_swap (0x8000)
	unsigned int reg_ch1_hs_ml_swap:1;

	// h000a
	unsigned int /* padding 16 bit */:16;

	// h000b, bit: 14
	/* */
	unsigned int :16;

	// h000b
	unsigned int /* padding 16 bit */:16;

	// h000c, bit: 0
	/* ch2 sw setting LP TX p data*/
	#define offset_of_dphy_ana_reg_sw_lptx_dinp2 (24)
	#define mask_of_dphy_ana_reg_sw_lptx_dinp2 (0x1)
	unsigned int reg_sw_lptx_dinp2:1;

	// h000c, bit: 1
	/* ch2 enable sw setting LP_TX p data*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_dinp2 (24)
	#define mask_of_dphy_ana_reg_en_sw_lptx_dinp2 (0x2)
	unsigned int reg_en_sw_lptx_dinp2:1;

	// h000c, bit: 2
	/* ch2 sw setting LP TX n data*/
	#define offset_of_dphy_ana_reg_sw_lptx_dinn2 (24)
	#define mask_of_dphy_ana_reg_sw_lptx_dinn2 (0x4)
	unsigned int reg_sw_lptx_dinn2:1;

	// h000c, bit: 3
	/* ch2 enable sw setting LP_TX n data*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_dinn2 (24)
	#define mask_of_dphy_ana_reg_en_sw_lptx_dinn2 (0x8)
	unsigned int reg_en_sw_lptx_dinn2:1;

	// h000c, bit: 4
	/* ch2 sw setting lptx enable*/
	#define offset_of_dphy_ana_reg_sw_lptx_en2 (24)
	#define mask_of_dphy_ana_reg_sw_lptx_en2 (0x10)
	unsigned int reg_sw_lptx_en2:1;

	// h000c, bit: 5
	/* ch2 enable sw setting lptx enable*/
	#define offset_of_dphy_ana_reg_en_sw_lptx_en2 (24)
	#define mask_of_dphy_ana_reg_en_sw_lptx_en2 (0x20)
	unsigned int reg_en_sw_lptx_en2:1;

	// h000c, bit: 6
	/* ch2 sw setting lprx power down, active low*/
	#define offset_of_dphy_ana_reg_sw_lprx_en2 (24)
	#define mask_of_dphy_ana_reg_sw_lprx_en2 (0x40)
	unsigned int reg_sw_lprx_en2:1;

	// h000c, bit: 7
	/* ch2 enable sw setting lprx power down*/
	#define offset_of_dphy_ana_reg_en_sw_lprx_en2 (24)
	#define mask_of_dphy_ana_reg_en_sw_lprx_en2 (0x80)
	unsigned int reg_en_sw_lprx_en2:1;

	// h000c, bit: 9
	/* ch2 sw setting outconf
	00 : HS_TX off
	01 : differential data
	1x : reserved*/
	#define offset_of_dphy_ana_reg_sw_outconf_ch2_bit (24)
	#define mask_of_dphy_ana_reg_sw_outconf_ch2_bit (0x300)
	unsigned int reg_sw_outconf_ch2_bit:2;

	// h000c, bit: 10
	/* */
	unsigned int :1;

	// h000c, bit: 11
	/* ch2 enable sw setting outconf*/
	#define offset_of_dphy_ana_reg_en_sw_outconf_ch2_bit (24)
	#define mask_of_dphy_ana_reg_en_sw_outconf_ch2_bit (0x800)
	unsigned int reg_en_sw_outconf_ch2_bit:1;

	// h000c, bit: 14
	/* */
	unsigned int :4;

	// h000c
	unsigned int /* padding 16 bit */:16;

	// h000d, bit: 7
	/* ch2 sw setting hs tx data*/
	#define offset_of_dphy_ana_reg_sw_dati_dphy_ch2_bit (26)
	#define mask_of_dphy_ana_reg_sw_dati_dphy_ch2_bit (0xff)
	unsigned int reg_sw_dati_dphy_ch2_bit:8;

	// h000d, bit: 8
	/* ch2 enable sw setting hs tx data*/
	#define offset_of_dphy_ana_reg_en_sw_dati_dphy_ch2_bit (26)
	#define mask_of_dphy_ana_reg_en_sw_dati_dphy_ch2_bit (0x100)
	unsigned int reg_en_sw_dati_dphy_ch2_bit:1;

	// h000d, bit: 9
	/* */
	unsigned int :1;

	// h000d, bit: 10
	/* ch2 sw setting hsrx_pdn*/
	#define offset_of_dphy_ana_reg_sw_hsrx_en_ch2 (26)
	#define mask_of_dphy_ana_reg_sw_hsrx_en_ch2 (0x400)
	unsigned int reg_sw_hsrx_en_ch2:1;

	// h000d, bit: 11
	/* ch2 enable sw setting hsx pdn*/
	#define offset_of_dphy_ana_reg_en_sw_hsrx_en_ch2 (26)
	#define mask_of_dphy_ana_reg_en_sw_hsrx_en_ch2 (0x800)
	unsigned int reg_en_sw_hsrx_en_ch2:1;

	// h000d, bit: 14
	/* */
	unsigned int :4;

	// h000d
	unsigned int /* padding 16 bit */:16;

	// h000e, bit: 0
	/* ch2 hs tx polarity setting*/
	#define offset_of_dphy_ana_reg_ds_pol_ch2 (28)
	#define mask_of_dphy_ana_reg_ds_pol_ch2 (0x1)
	unsigned int reg_ds_pol_ch2:1;

	// h000e, bit: 1
	/* ch2 enable sw lane selection*/
	#define offset_of_dphy_ana_reg_en_sw_ch2_lanesel (28)
	#define mask_of_dphy_ana_reg_en_sw_ch2_lanesel (0x2)
	unsigned int reg_en_sw_ch2_lanesel:1;

	// h000e, bit: 3
	/* ch2 lane selection*/
	#define offset_of_dphy_ana_reg_sw_ch2_lanesel (28)
	#define mask_of_dphy_ana_reg_sw_ch2_lanesel (0xc)
	unsigned int reg_sw_ch2_lanesel:2;

	// h000e, bit: 11
	/* */
	unsigned int :8;

	// h000e, bit: 13
	/* ch2 data selection*/
	#define offset_of_dphy_ana_reg_ch2_dat_sel (28)
	#define mask_of_dphy_ana_reg_ch2_dat_sel (0x3000)
	unsigned int reg_ch2_dat_sel:2;

	// h000e, bit: 14
	/* */
	unsigned int :1;

	// h000e, bit: 15
	/* ch2 hs data MSB/LSB swap*/
	#define offset_of_dphy_ana_reg_ch2_hs_ml_swap (28)
	#define mask_of_dphy_ana_reg_ch2_hs_ml_swap (0x8000)
	unsigned int reg_ch2_hs_ml_swap:1;

	// h000e
	unsigned int /* padding 16 bit */:16;

	// h000f, bit: 14
	/* */
	unsigned int :16;

	// h000f
	unsigned int /* padding 16 bit */:16;

	// h0010, bit: 2
	/* LP CDN status*/
	#define offset_of_dphy_ana_reg_lp_cdn (32)
	#define mask_of_dphy_ana_reg_lp_cdn (0x7)
	unsigned int reg_lp_cdn:3;

	// h0010, bit: 3
	/* */
	unsigned int :1;

	// h0010, bit: 6
	/* LP CDP status*/
	#define offset_of_dphy_ana_reg_lp_cdp (32)
	#define mask_of_dphy_ana_reg_lp_cdp (0x70)
	unsigned int reg_lp_cdp:3;

	// h0010, bit: 7
	/* */
	unsigned int :1;

	// h0010, bit: 10
	/* LP RXN status*/
	#define offset_of_dphy_ana_reg_lp_rxdon (32)
	#define mask_of_dphy_ana_reg_lp_rxdon (0x700)
	unsigned int reg_lp_rxdon:3;

	// h0010, bit: 11
	/* */
	unsigned int :1;

	// h0010, bit: 14
	/* LP RXNP status*/
	#define offset_of_dphy_ana_reg_lp_rxdop (32)
	#define mask_of_dphy_ana_reg_lp_rxdop (0x7000)
	unsigned int reg_lp_rxdop:3;

	// h0010, bit: 15
	/* */
	unsigned int :1;

	// h0010
	unsigned int /* padding 16 bit */:16;

	// h0011, bit: 7
	/* HSRX lane 0 staus*/
	#define offset_of_dphy_ana_reg_hsrx_dout0 (34)
	#define mask_of_dphy_ana_reg_hsrx_dout0 (0xff)
	unsigned int reg_hsrx_dout0:8;

	// h0011, bit: 14
	/* HSRX lane 1 status*/
	#define offset_of_dphy_ana_reg_hsrx_dout1 (34)
	#define mask_of_dphy_ana_reg_hsrx_dout1 (0xff00)
	unsigned int reg_hsrx_dout1:8;

	// h0011
	unsigned int /* padding 16 bit */:16;

	// h0012, bit: 7
	/* HSRX lane 2 status*/
	#define offset_of_dphy_ana_reg_hsrx_dout2 (36)
	#define mask_of_dphy_ana_reg_hsrx_dout2 (0xff)
	unsigned int reg_hsrx_dout2:8;

	// h0012, bit: 14
	/* */
	unsigned int :8;

	// h0012
	unsigned int /* padding 16 bit */:16;

	// h0013, bit: 1
	/* fifo wr/rd offset selection
	00 : read after write 2
	01 : read after write 3
	1x : read after write 4*/
	#define offset_of_dphy_ana_reg_fifo_rd_off_sel (38)
	#define mask_of_dphy_ana_reg_fifo_rd_off_sel (0x3)
	unsigned int reg_fifo_rd_off_sel:2;

	// h0013, bit: 3
	/* csi rx extern rx selection*/
	#define offset_of_dphy_ana_reg_wr_ext (38)
	#define mask_of_dphy_ana_reg_wr_ext (0xc)
	unsigned int reg_wr_ext:2;

	// h0013, bit: 7
	/* debug bus selection*/
	#define offset_of_dphy_ana_reg_debug_bus_sel (38)
	#define mask_of_dphy_ana_reg_debug_bus_sel (0xf0)
	unsigned int reg_debug_bus_sel:4;

	// h0013, bit: 14
	/* */
	unsigned int :8;

	// h0013
	unsigned int /* padding 16 bit */:16;

	// h0014, bit: 14
	/* dummy register 0*/
	#define offset_of_dphy_ana_reg_dummy0 (40)
	#define mask_of_dphy_ana_reg_dummy0 (0xffff)
	unsigned int reg_dummy0:16;

	// h0014
	unsigned int /* padding 16 bit */:16;

	// h0015, bit: 14
	/* dummy register 1*/
	#define offset_of_dphy_ana_reg_dummy1 (42)
	#define mask_of_dphy_ana_reg_dummy1 (0xffff)
	unsigned int reg_dummy1:16;

	// h0015
	unsigned int /* padding 16 bit */:16;

	// h0016, bit: 7
	/* skip hs clock when into HSRX mode*/
	#define offset_of_dphy_ana_reg_csi_rx_clk_skip_ns (44)
	#define mask_of_dphy_ana_reg_csi_rx_clk_skip_ns (0xff)
	unsigned int reg_csi_rx_clk_skip_ns:8;

	// h0016, bit: 14
	/* skip hs data when into HSRX mode*/
	#define offset_of_dphy_ana_reg_csi_rx_data_skip_ns (44)
	#define mask_of_dphy_ana_reg_csi_rx_data_skip_ns (0xff00)
	unsigned int reg_csi_rx_data_skip_ns:8;

	// h0016
	unsigned int /* padding 16 bit */:16;

	// h0017, bit: 2
	/* HSRX data lane0 skew setting*/
	#define offset_of_dphy_ana_reg_d0_skew_dly (46)
	#define mask_of_dphy_ana_reg_d0_skew_dly (0x7)
	unsigned int reg_d0_skew_dly:3;

	// h0017, bit: 3
	/* HSRX data lane0 skew enable*/
	#define offset_of_dphy_ana_reg_d0_skew_en (46)
	#define mask_of_dphy_ana_reg_d0_skew_en (0x8)
	unsigned int reg_d0_skew_en:1;

	// h0017, bit: 6
	/* HSRX data lane1 skew setting*/
	#define offset_of_dphy_ana_reg_d1_skew_dly (46)
	#define mask_of_dphy_ana_reg_d1_skew_dly (0x70)
	unsigned int reg_d1_skew_dly:3;

	// h0017, bit: 7
	/* HSRX data lane1 skew enable*/
	#define offset_of_dphy_ana_reg_d1_skew_en (46)
	#define mask_of_dphy_ana_reg_d1_skew_en (0x80)
	unsigned int reg_d1_skew_en:1;

	// h0017, bit: 14
	/* */
	unsigned int :8;

	// h0017
	unsigned int /* padding 16 bit */:16;

	// h0018, bit: 3
	/* */
	#define offset_of_dphy_ana_reg_ckg_rx_hs_short (48)
	#define mask_of_dphy_ana_reg_ckg_rx_hs_short (0xf)
	unsigned int reg_ckg_rx_hs_short:4;

	// h0018, bit: 7
	/* */
	#define offset_of_dphy_ana_reg_ckg_rx_hs_nor (48)
	#define mask_of_dphy_ana_reg_ckg_rx_hs_nor (0xf0)
	unsigned int reg_ckg_rx_hs_nor:4;

	// h0018, bit: 11
	/* */
	#define offset_of_dphy_ana_reg_ckg_bist_tx (48)
	#define mask_of_dphy_ana_reg_ckg_bist_tx (0xf00)
	unsigned int reg_ckg_bist_tx:4;

	// h0018, bit: 14
	/* */
	unsigned int :4;

	// h0018
	unsigned int /* padding 16 bit */:16;

	// h0019, bit: 3
	/* */
	#define offset_of_dphy_ana_reg_ckg_rx_lp_clk (50)
	#define mask_of_dphy_ana_reg_ckg_rx_lp_clk (0xf)
	unsigned int reg_ckg_rx_lp_clk:4;

	// h0019, bit: 7
	/* */
	#define offset_of_dphy_ana_reg_ckg_rx_lp_d0 (50)
	#define mask_of_dphy_ana_reg_ckg_rx_lp_d0 (0xf0)
	unsigned int reg_ckg_rx_lp_d0:4;

	// h0019, bit: 11
	/* */
	#define offset_of_dphy_ana_reg_ckg_rx_lp_d1 (50)
	#define mask_of_dphy_ana_reg_ckg_rx_lp_d1 (0xf00)
	unsigned int reg_ckg_rx_lp_d1:4;

	// h0019, bit: 14
	/* */
	unsigned int :4;

	// h0019
	unsigned int /* padding 16 bit */:16;

	// h001a, bit: 14
	/* */
	unsigned int :16;

	// h001a
	unsigned int /* padding 16 bit */:16;

	// h001b, bit: 14
	/* */
	unsigned int :16;

	// h001b
	unsigned int /* padding 16 bit */:16;

	// h001c, bit: 0
	/* data lane 0 bist lock*/
	#define offset_of_dphy_ana_reg_d0_bist_lock (56)
	#define mask_of_dphy_ana_reg_d0_bist_lock (0x1)
	unsigned int reg_d0_bist_lock:1;

	// h001c, bit: 1
	/* data lane 0 bist pass*/
	#define offset_of_dphy_ana_reg_d0_bist_pass (56)
	#define mask_of_dphy_ana_reg_d0_bist_pass (0x2)
	unsigned int reg_d0_bist_pass:1;

	// h001c, bit: 2
	/* data lane 0 bist fail*/
	#define offset_of_dphy_ana_reg_d0_bist_fail (56)
	#define mask_of_dphy_ana_reg_d0_bist_fail (0x4)
	unsigned int reg_d0_bist_fail:1;

	// h001c, bit: 3
	/* */
	unsigned int :1;

	// h001c, bit: 4
	/* data lane 1 bist lock*/
	#define offset_of_dphy_ana_reg_d1_bist_lock (56)
	#define mask_of_dphy_ana_reg_d1_bist_lock (0x10)
	unsigned int reg_d1_bist_lock:1;

	// h001c, bit: 5
	/* data lane 1 bist pass*/
	#define offset_of_dphy_ana_reg_d1_bist_pass (56)
	#define mask_of_dphy_ana_reg_d1_bist_pass (0x20)
	unsigned int reg_d1_bist_pass:1;

	// h001c, bit: 6
	/* data lane 1 bist fail*/
	#define offset_of_dphy_ana_reg_d1_bist_fail (56)
	#define mask_of_dphy_ana_reg_d1_bist_fail (0x40)
	unsigned int reg_d1_bist_fail:1;

	// h001c, bit: 12
	/* */
	unsigned int :6;

	// h001c, bit: 13
	/* csi bist tx clock enable */
	#define offset_of_dphy_ana_reg_hs_bist_clk_en (56)
	#define mask_of_dphy_ana_reg_hs_bist_clk_en (0x2000)
	unsigned int reg_hs_bist_clk_en:1;

	// h001c, bit: 14
	/* hs bist data enable */
	#define offset_of_dphy_ana_reg_hs_bist_data_en (56)
	#define mask_of_dphy_ana_reg_hs_bist_data_en (0x4000)
	unsigned int reg_hs_bist_data_en:1;

	// h001c, bit: 15
	/* hs bist enable*/
	#define offset_of_dphy_ana_reg_hs_bist_en (56)
	#define mask_of_dphy_ana_reg_hs_bist_en (0x8000)
	unsigned int reg_hs_bist_en:1;

	// h001c
	unsigned int /* padding 16 bit */:16;

	// h001d, bit: 0
	/* HSRX auto-skip enable*/
	#define offset_of_dphy_ana_reg_auto_skip_en (58)
	#define mask_of_dphy_ana_reg_auto_skip_en (0x1)
	unsigned int reg_auto_skip_en:1;

	// h001d, bit: 1
	/* HSRX voltage offset*/
	#define offset_of_dphy_ana_reg_ofs_add (58)
	#define mask_of_dphy_ana_reg_ofs_add (0x2)
	unsigned int reg_ofs_add:1;

	// h001d, bit: 2
	/* spaced one hot decode error clear*/
	#define offset_of_dphy_ana_reg_osh_decode_err_clr (58)
	#define mask_of_dphy_ana_reg_osh_decode_err_clr (0x4)
	unsigned int reg_osh_decode_err_clr:1;

	// h001d, bit: 5
	/* */
	unsigned int :3;

	// h001d, bit: 6
	/* LP bist pattern mode
	0: PBRS
	1: sw bist pattern*/
	#define offset_of_dphy_ana_reg_dphy_lp_bist_mode (58)
	#define mask_of_dphy_ana_reg_dphy_lp_bist_mode (0x40)
	unsigned int reg_dphy_lp_bist_mode:1;

	// h001d, bit: 7
	/* LP bist pattern enable*/
	#define offset_of_dphy_ana_reg_dphy_lp_bist_en (58)
	#define mask_of_dphy_ana_reg_dphy_lp_bist_en (0x80)
	unsigned int reg_dphy_lp_bist_en:1;

	// h001d, bit: 14
	/* LP sw bist pattern*/
	#define offset_of_dphy_ana_reg_dphy_lp_bist_sw_pat (58)
	#define mask_of_dphy_ana_reg_dphy_lp_bist_sw_pat (0xff00)
	unsigned int reg_dphy_lp_bist_sw_pat:8;

	// h001d
	unsigned int /* padding 16 bit */:16;

	// h001e, bit: 0
	/* */
	#define offset_of_dphy_ana_reg_dmux_clear_en (60)
	#define mask_of_dphy_ana_reg_dmux_clear_en (0x1)
	unsigned int reg_dmux_clear_en:1;

	// h001e, bit: 1
	/* */
	#define offset_of_dphy_ana_reg_dmux_clear (60)
	#define mask_of_dphy_ana_reg_dmux_clear (0x2)
	unsigned int reg_dmux_clear:1;

	// h001e, bit: 14
	/* */
	unsigned int :14;

	// h001e
	unsigned int /* padding 16 bit */:16;

	// h001f, bit: 14
	/* */
	unsigned int :16;

	// h001f
	unsigned int /* padding 16 bit */:16;

	// h0020, bit: 14
	/* */
	unsigned int :16;

	// h0020
	unsigned int /* padding 16 bit */:16;

	// h0021, bit: 14
	/* */
	unsigned int :16;

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
	/* */
	unsigned int :16;

	// h0028
	unsigned int /* padding 16 bit */:16;

	// h0029, bit: 14
	/* */
	unsigned int :16;

	// h0029
	unsigned int /* padding 16 bit */:16;

	// h002a, bit: 14
	/* */
	unsigned int :16;

	// h002a
	unsigned int /* padding 16 bit */:16;

	// h002b, bit: 14
	/* */
	unsigned int :16;

	// h002b
	unsigned int /* padding 16 bit */:16;

	// h002c, bit: 14
	/* */
	unsigned int :16;

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
	/* */
	unsigned int :16;

	// h0030
	unsigned int /* padding 16 bit */:16;

	// h0031, bit: 14
	/* */
	unsigned int :16;

	// h0031
	unsigned int /* padding 16 bit */:16;

	// h0032, bit: 14
	/* */
	unsigned int :16;

	// h0032
	unsigned int /* padding 16 bit */:16;

	// h0033, bit: 14
	/* */
	unsigned int :16;

	// h0033
	unsigned int /* padding 16 bit */:16;

	// h0034, bit: 14
	/* */
	unsigned int :16;

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
	/* */
	unsigned int :16;

	// h0038
	unsigned int /* padding 16 bit */:16;

	// h0039, bit: 14
	/* */
	unsigned int :16;

	// h0039
	unsigned int /* padding 16 bit */:16;

	// h003a, bit: 14
	/* */
	unsigned int :16;

	// h003a
	unsigned int /* padding 16 bit */:16;

	// h003b, bit: 14
	/* */
	unsigned int :16;

	// h003b
	unsigned int /* padding 16 bit */:16;

	// h003c, bit: 14
	/* */
	unsigned int :16;

	// h003c
	unsigned int /* padding 16 bit */:16;

	// h003d, bit: 14
	/* */
	unsigned int :16;

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

	// h004d, bit: 14
	/* */
	unsigned int :16;

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

}  __attribute__((packed, aligned(1))) DPHYAna_t;

extern volatile DPHYAna_t * const g_ptDPHYAna;

#endif
