#ifndef __HAL_CSI__
#define __HAL_CSI__

#include "isp_types.h"
#include "kernel_csi.h"
#include "kernel_dphy_ana.h"
#include "kernel_dphy_dig.h"
#include "kernel_csi_mac_4lane.h"
#include "kernel_dphy_ana_4lane.h"
#include "kernel_dphy_dig_4lane.h"
#include "drv_csi.h"

void HalCsi_ECCOff(CSI_ONOFF_e csi_on_off);
void HalCsi_DataLaneEnable(CSI_DATA_LANE_e csi_data_lane, CSI_ONOFF_e csi_on_off);
void HalCsi_RemoveErroneousSOT(CSI_ONOFF_e csi_on_off);
void HalCsi_MACFuncMode(CSI_MAC_FUNC_MODE_e csi_func_mode);
void HalCsi_VirtualChannelEnable(CSI_VIRTUAL_CHANNEL_e csi_vc, CSI_ONOFF_e csi_on_off);
void HalCsi_RemoveErroneousFS(CSI_ONOFF_e csi_on_off);
void HalCsi_YUV422_8bitOutMode(CSI_YUV422_8BIT_OUT_MODE_e csi_yuv422_8bit_out_mode);
void HalCsi_VirtualChannelHsyncMode(CSI_VIRTUAL_CHANNEL_e csi_vc, CSI_VIRTUAL_CHANNEL_HSYNC_MODE_e csi_vc_ch_hsync_mode);
void HalCsi_VirtualChannelVsyncMode(CSI_VIRTUAL_CHANNEL_e csi_vc, CSI_VIRTUAL_CHANNEL_VSYNC_MODE_e csi_vc_ch_vsync_mode);
void HalCsi_DebugEnable(CSI_ONOFF_e csi_on_off);
u32 HalCsi_PhyIntMaskGet();
void HalCsi_PhyIntMask(u32 csi_phy_int_mask);
void HalCsi_PhyIntForce(u32 csi_phy_int_force);
void HalCsi_PhyIntClear(u32 csi_phy_int_clear);
void HalCsi_CkgMac(u32 csi_mac_div, u32 csi_mac_gate, CSI_CLK_POLARITY_e csi_mac_inv);
void HalCsi_CkgMacLptx(u32 csi_mac_div, u32 csi_mac_gate, CSI_CLK_POLARITY_e csi_mac_inv);
void HalCsi_CkgNs(u32 csi_mac_div, u32 csi_mac_gate, CSI_CLK_POLARITY_e csi_mac_inv);
void HalCsi_DtEnable(u32 csi_dt_en, u32 csi_dt_en_1, u32 csi_dt_en_2);
void HalCsi_SoftwareReset(CSI_ONOFF_e csi_on_off);
void HalCsi_MacEnable(CSI_ONOFF_e csi_on_off);
void HalCsi_DontCareDt(CSI_ONOFF_e csi_on_off);
void HalCsi_SOT_EOT_Sel(u32 csi_raw_l_sot_sel, u32 csi_sot_sel, u32 csi_eot_sel);
void HalCsi_ReportFrameNum(CSI_REPORT_FRAME_NUM_e csi_rpt_frm_num);
void HalCsi_ReportLineNum(CSI_REPORT_LINE_NUM_e csi_rpt_line_num);
u32 HalCsi_FSMIntMaskGet(CSI_FSM_LANE_TYPE_e csi_lane_type);
u32 HalCsi_FSMIntSrcGet(CSI_FSM_LANE_TYPE_e csi_lane_type);
u32 HalCsi_FSMIntRawSrcGet(CSI_FSM_LANE_TYPE_e csi_lane_type);
void HalCsi_FSMIntMask(CSI_FSM_LANE_TYPE_e csi_lane_type, u32 csi_fsm_int_mask);
void HalCsi_FSMIntForce(CSI_FSM_LANE_TYPE_e csi_lane_type, u32 csi_fsm_int_force);
void HalCsi_FSMIntClear(CSI_FSM_LANE_TYPE_e csi_lane_type, u32 csi_fsm_int_clear);
void HalCsi_UD1_8TO16BitOutputMode(CSI_ONOFF_e csi_on_off);
void HalCsi_HDRType(CSI_HDR_MODE_e csi_hdr_mode, CSI_ONOFF_e csi_on_off);
u32 HalCsi_GetRptIntStatus();
void HalCsi_MaskRptInt(u32 mask);
void HalCsi_ClearRptInt(u32 clear);
u32 HalCsi_GetErrorIntStatus();
void HalCsi_MaskErrorInt(u32 mask);
u32 HalCsi_ErrIntMaskGet();
void HalCsi_ForceErrorInt(u32 clear);
void HalCsi_ClearErrorInt(u32 clear);

void HalCsiAna_HsRxTxAttribute(u32 csi_ckg_rx_hs_short, u32 csi_ckg_rx_hs_nor, u32 csi_ckg_bist_tx);
void HalCsiAna_LpAttribute(u32 csi_ckg_rx_lp_clk, u32 csi_ckg_rx_lp_d0, u32 csi_ckg_rx_lp_d1);
void HalCsiAna_DmuxClear(CSI_ONOFF_e csi_dmux_clear, CSI_ONOFF_e csi_dmux_clear_en);
void HalCsiAna_SoftwareReset(CSI_ONOFF_e csi_on_off);
void HalCsiAna_DynGatingClkNsEnable(CSI_ONOFF_e csi_on_off);
void HalCsiAna_ClockDivide4Dot5XEnable(CSI_ONOFF_e csi_on_off);
void HalCsiAna_LPTX_VREG_TSET_EN(CSI_ONOFF_e csi_on_off);
void HalCsiAna_LPTX_VREG_select(u32 csi_lptx_vreg_sel);
void HalCsiAna_PowerDown_LPTX_VREG(u32 csi_pd_lptx_vreg);
void HalCsiAna_Sw_LPCD_Enable(u32 csi_sw_lpcd_en);
void HalCsiAna_PdHsMode(CSI_ONOFF_e csi_on_off);
void HalCsiAna_PdWholeDphyAnalog(CSI_ONOFF_e csi_on_off);
void HalCsiAna_HsrxPreTest(u32 csi_hx_pre_test);
void HalCsiAna_HSRXClockSkew(CSI_ONOFF_e csi_on_off, u32 csi_rxclk_dly);
void HalCsiAna_LprefTest(u32 csi_lpref_test);
void HalCsiAna_TrimBit(u32 csi_trim_bit);
void HalCsiAna_UlpsSetting(CSI_ONOFF_e csi_dis_cd_ulps, CSI_ONOFF_e csi_sw_ulps, CSI_ONOFF_e csi_en_ulps, CSI_ONOFF_e csi_en_pd_ib_dphy_ulps);
void HalCsiAna_ClockLaneSetting(CSI_ONOFF_e csi_sw_dphy_cken, CSI_ONOFF_e csi_sw_en_sw_dphy_cken, u32 csi_pd_dphy_delay, u32 csi_sw_clklane_en, CSI_ONOFF_e csi_en_sw_clklane_en);
void HalCsiAna_SetLP_TXp(CSI_CHANNEL_e csi_data_ch, u32 csi_lptx_dinp, CSI_ONOFF_e csi_en_sw_lptx_dinp);
void HalCsiAna_SetLP_TXn(CSI_CHANNEL_e csi_data_ch, u32 csi_lptx_dinn, CSI_ONOFF_e csi_en_sw_lptx_dinn);
void HalCsiAna_SetLP_TXEnable(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_lptx_en, CSI_ONOFF_e csi_sw_lptx_en);
void HalCsiAna_SetLP_RXEnable(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_lprx_en, CSI_ONOFF_e csi_sw_lprx_en);
void HalCsiAna_SetOutconf(CSI_CHANNEL_e csi_data_ch, u32 csi_outconf_ch, CSI_ONOFF_e csi_en_sw_outconf);
void HalCsiAna_SetHsTxData(CSI_CHANNEL_e csi_data_ch, u32 csi_dati_dphy, CSI_ONOFF_e csi_en_sw_dati_dphy);
void HalCsiAna_SetHsTxPolarity(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_ds_pol);
void HalCsiAna_SetLaneSelect(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_en_sw_ch_lanesel, u32 csi_sw_ch_lanesel, u32 csi_ch_dat_sel, CSI_ONOFF_e csi_ch_hs_ml_swap);
void HalCsiAna_SkipHsInHSRXMode(u32 csi_rx_clk_skip_ns, u32 csi_rx_data_skip_ns);
void HalCsiAna_SkewDelay(CSI_DATA_LANE_e csi_data_lane, u32 csi_skew_dly, CSI_ONOFF_e csi_skew_en);
void HalCsiAna_HSRXSetting(CSI_ONOFF_e csi_auto_skip_en, CSI_ONOFF_e csi_ofs_add);
void HalCsiAna_SpacedOneHotDecodeErrorClear(CSI_ONOFF_e csi_osh_decode_err_clr);
void HalCsiAna_LpBistSetting(CSI_ONOFF_e csi_lp_bist_mode, CSI_ONOFF_e csi_lp_bist_en, u32 csi_lp_bist_sw_pat);
void HalCsiDig_SoftwareReset(CSI_ONOFF_e csi_sw_rstz);
void HalCsiDig_Enable8b9bDecode(CSI_ONOFF_e csi_en_8b9b_decode);
void HalCsiDig_HsDataParallelToSerialMsb_LsbSwap(CSI_ONOFF_e csi_hs_ml_swap);
void HalCsiDig_HsRxDelayForRetiming(u32 csi_hs_rx_dly);
void HalCsiDig_ClearDataLaneSyncSkew(CSI_ONOFF_e csi_clr_sync_skew);
void HalCsiDig_EnableSyncPatternWith1BitError(CSI_ONOFF_e csi_en_err_sot_hs);
void HalCsiDig_LpRxDelayForRetiming(u32 csi_lp_rx_dly);
void HalCsiDig_EnableEscapeMode(CSI_ONOFF_e csi_esc_en);
void HalCsiDig_ClearSkewOverFlag(CSI_ONOFF_e csi_clear);
void HalCsiDig_SampleSkewIndexOnce(CSI_ONOFF_e csi_sample_skew);
void HalCsiDig_EnableReportRuntimeSkewIndex(CSI_ONOFF_e csi_runtime_skew);
void HalCsiDig_EnableDataChannelDeskew(CSI_ONOFF_e csi_en_data_ch);

void HalCsiMac4Lane_ECCOff(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_DataLaneEnable(CSI_DATA_LANE_e csi_data_lane, CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_RemoveErroneousSOT(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_MACFuncMode(CSI_MAC_FUNC_MODE_e csi_func_mode);
void HalCsiMac4Lane_VirtualChannelEnable(CSI_VIRTUAL_CHANNEL_e csi_vc, CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_RemoveErroneousFS(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_YUV422_8bitOutMode(CSI_YUV422_8BIT_OUT_MODE_e csi_yuv422_8bit_out_mode);
void HalCsiMac4Lane_VirtualChannelHsyncMode(CSI_VIRTUAL_CHANNEL_e csi_vc, CSI_VIRTUAL_CHANNEL_HSYNC_MODE_e csi_vc_ch_hsync_mode);
void HalCsiMac4Lane_VirtualChannelVsyncMode(CSI_VIRTUAL_CHANNEL_e csi_vc, CSI_VIRTUAL_CHANNEL_VSYNC_MODE_e csi_vc_ch_vsync_mode);
void HalCsiMac4Lane_DebugEnable(CSI_ONOFF_e csi_on_off);
u32 HalCsiMac4Lane_PhyIntMaskGet(u32 csi_lane2_3);
void HalCsiMac4Lane_PhyIntMask(u32 csi_lane2_3, u32 csi_phy_int_mask);
void HalCsiMac4Lane_PhyIntForce(u32 csi_lane2_3, u32 csi_phy_int_force);
void HalCsiMac4Lane_PhyIntClear(u32 csi_lane2_3, u32 csi_phy_int_clear);
void HalCsiMac4Lane_CkgMac(u32 csi_mac_div, u32 csi_mac_gate, CSI_CLK_POLARITY_e csi_mac_inv);
void HalCsiMac4Lane_CkgMacLptx(u32 csi_mac_div, u32 csi_mac_gate, CSI_CLK_POLARITY_e csi_mac_inv);
void HalCsiMac4Lane_CkgNs(u32 csi_mac_div, u32 csi_mac_gate, CSI_CLK_POLARITY_e csi_mac_inv);
void HalCsiMac4Lane_DtEnable(u32 csi_dt_en, u32 csi_dt_en_1, u32 csi_dt_en_2);
void HalCsiMac4Lane_SoftwareReset(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_MacEnable(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_DontCareDt(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_SOT_EOT_Sel(u32 csi_raw_l_sot_sel, u32 csi_sot_sel, u32 csi_eot_sel);
void HalCsiMac4Lane_ReportFrameNum(CSI_REPORT_FRAME_NUM_e csi_rpt_frm_num);
void HalCsiMac4Lane_ReportLineNum(CSI_REPORT_LINE_NUM_e csi_rpt_line_num);
u32 HalCsiMac4Lane_FSMIntMaskGet(CSI_FSM_LANE_TYPE_e csi_lane_type);
u32 HalCsiMac4Lane_FSMIntSrcGet(CSI_FSM_LANE_TYPE_e csi_lane_type);
u32 HalCsiMac4Lane_FSMIntRawSrcGet(CSI_FSM_LANE_TYPE_e csi_lane_type);
void HalCsiMac4Lane_FSMIntMask(CSI_FSM_LANE_TYPE_e csi_lane_type, u32 csi_fsm_int_mask);
void HalCsiMac4Lane_FSMIntForce(CSI_FSM_LANE_TYPE_e csi_lane_type, u32 csi_fsm_int_force);
void HalCsiMac4Lane_FSMIntClear(CSI_FSM_LANE_TYPE_e csi_lane_type, u32 csi_fsm_int_clear);
void HalCsiMac4Lane_UD1_8TO16BitOutputMode(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_DOLHDREn(CSI_ONOFF_e csi_on_off);
void HalCsiMac4Lane_HDRType(CSI_HDR_MODE_e csi_hdr_mode, CSI_ONOFF_e csi_on_off);
u32 HalCsiMac4Lane_GetRptIntStatus();
void HalCsiMac4Lane_MaskRptInt(u32 mask);
void HalCsiMac4Lane_ClearRptInt(u32 clear);
u32 HalCsiMac4Lane_GetErrorIntStatus();
void HalCsiMac4Lane_MaskErrorInt(u32 mask);
u32 HalCsiMac4Lane_ErrIntMaskGet();
void HalCsiMac4Lane_ForceErrorInt(u32 clear);
void HalCsiMac4Lane_ClearErrorInt(u32 clear);

void HalCsiAna4Lane_HsRxTxAttribute(u32 csi_ckg_rx_hs_short, u32 csi_ckg_rx_hs_nor, u32 csi_ckg_bist_tx);
void HalCsiAna4Lane_LpAttribute(u32 csi_ckg_rx_lp_clk, u32 csi_ckg_rx_lp_d0, u32 csi_ckg_rx_lp_d1, u32 csi_ckg_rx_lp_d2, u32 csi_ckg_rx_lp_d3);
void HalCsiAna4Lane_DmuxClear(CSI_ONOFF_e csi_dmux_clear, CSI_ONOFF_e csi_dmux_clear_en);
void HalCsiAna4Lane_SoftwareReset(CSI_ONOFF_e csi_on_off);
void HalCsiAna4Lane_DynGatingClkNsEnable(CSI_ONOFF_e csi_on_off);
void HalCsiAna4Lane_ClockDivide4Dot5XEnable(CSI_ONOFF_e csi_on_off);
void HalCsiAna4Lane_LPTX_VREG_TSET_EN(CSI_ONOFF_e csi_on_off);
void HalCsiAna4Lane_LPTX_VREG_select(u32 csi_lptx_vreg_sel);
void HalCsiAna4Lane_PowerDown_LPTX_VREG(u32 csi_pd_lptx_vreg);
void HalCsiAna4Lane_Sw_LPCD_Enable(u32 csi_sw_lpcd_en);
void HalCsiAna4Lane_PdHsMode(CSI_ONOFF_e csi_on_off);
void HalCsiAna4Lane_PdWholeDphyAnalog(CSI_ONOFF_e csi_on_off);
void HalCsiAna4Lane_HsrxPreTest(u32 csi_hx_pre_test);
void HalCsiAna4Lane_HSRXClockSkew(CSI_ONOFF_e csi_on_off, u32 csi_rxclk_dly);
void HalCsiAna4Lane_LprefTest(u32 csi_lpref_test);
void HalCsiAna4Lane_TrimBit(u32 csi_trim_bit);
void HalCsiAna4Lane_UlpsSetting(CSI_ONOFF_e csi_dis_cd_ulps, CSI_ONOFF_e csi_sw_ulps, CSI_ONOFF_e csi_en_ulps, CSI_ONOFF_e csi_en_pd_ib_dphy_ulps);
void HalCsiAna4Lane_ClockLaneSetting(CSI_ONOFF_e csi_sw_dphy_cken, CSI_ONOFF_e csi_sw_en_sw_dphy_cken, u32 csi_pd_dphy_delay, u32 csi_sw_clklane_en, CSI_ONOFF_e csi_en_sw_clklane_en);
void HalCsiAna4Lane_SetLP_TXp(CSI_CHANNEL_e csi_data_ch, u32 csi_lptx_dinp, CSI_ONOFF_e csi_en_sw_lptx_dinp);
void HalCsiAna4Lane_SetLP_TXn(CSI_CHANNEL_e csi_data_ch, u32 csi_lptx_dinn, CSI_ONOFF_e csi_en_sw_lptx_dinn);
void HalCsiAna4Lane_SetLP_TXEnable(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_lptx_en, CSI_ONOFF_e csi_sw_lptx_en);
void HalCsiAna4Lane_SetLP_RXEnable(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_lprx_en, CSI_ONOFF_e csi_sw_lprx_en);
void HalCsiAna4Lane_SetOutconf(CSI_CHANNEL_e csi_data_ch, u32 csi_outconf_ch, CSI_ONOFF_e csi_en_sw_outconf);
void HalCsiAna4Lane_SetHsTxData(CSI_CHANNEL_e csi_data_ch, u32 csi_dati_dphy, CSI_ONOFF_e csi_en_sw_dati_dphy);
void HalCsiAna4Lane_SetHsTxPolarity(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_ds_pol);
void HalCsiAna4Lane_SetLaneSelect(CSI_CHANNEL_e csi_data_ch, CSI_ONOFF_e csi_en_sw_ch_lanesel, u32 csi_sw_ch_lanesel, u32 csi_ch_dat_sel, CSI_ONOFF_e csi_ch_hs_ml_swap);
void HalCsiAna4Lane_SkipHsInHSRXMode(u32 csi_rx_clk_skip_ns, u32 csi_rx_data_skip_ns);
void HalCsiAna4Lane_SkewDelay(CSI_DATA_LANE_e csi_data_lane, u32 csi_skew_dly, CSI_ONOFF_e csi_skew_en);
void HalCsiAna4Lane_HSRXSetting(CSI_ONOFF_e csi_auto_skip_en, CSI_ONOFF_e csi_ofs_add);
void HalCsiAna4Lane_SpacedOneHotDecodeErrorClear(CSI_ONOFF_e csi_osh_decode_err_clr);
void HalCsiAna4Lane_LpBistSetting(CSI_ONOFF_e csi_lp_bist_mode, CSI_ONOFF_e csi_lp_bist_en, u32 csi_lp_bist_sw_pat);

void HalCsiDig4Lane_SoftwareReset(CSI_ONOFF_e csi_sw_rstz);
void HalCsiDig4Lane_Enable8b9bDecode(CSI_ONOFF_e csi_en_8b9b_decode);
void HalCsiDig4Lane_HsDataParallelToSerialMsb_LsbSwap(CSI_ONOFF_e csi_hs_ml_swap);
void HalCsiDig4Lane_HsRxDelayForRetiming(u32 csi_hs_rx_dly);
void HalCsiDig4Lane_ClearDataLaneSyncSkew(CSI_ONOFF_e csi_clr_sync_skew);
void HalCsiDig4Lane_EnableSyncPatternWith1BitError(CSI_ONOFF_e csi_en_err_sot_hs);
void HalCsiDig4Lane_LpRxDelayForRetiming(u32 csi_lp_rx_dly);
void HalCsiDig4Lane_EnableEscapeMode(CSI_ONOFF_e csi_esc_en);
void HalCsiDig4Lane_ClearSkewOverFlag(CSI_ONOFF_e csi_clear);
void HalCsiDig4Lane_SampleSkewIndexOnce(CSI_ONOFF_e csi_sample_skew);
void HalCsiDig4Lane_EnableReportRuntimeSkewIndex(CSI_ONOFF_e csi_runtime_skew);
void HalCsiDig4Lane_EnableDataChannelDeskew(CSI_ONOFF_e csi_en_data_ch);

void HalCsi_RegInit();
void HalCsi_RegUninit();

#endif
