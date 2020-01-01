/**
 * @file    mmi_req_mm.h
 * @brief   The file handles all the MM request function to RIL
 * @author  lih.wang@mstarsemi.com
 * 
 * @version $Id: mmi_req_mm.h 22488 2009-02-12 09:00:58Z lih.wang $
 */
#ifndef __MMI_REQ_MM_H__
#define __MMI_REQ_MM_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

#include "mmi_mmsrv_def.h"


void mmi_mm_search_network_req(u8 DualID);
void mmi_mm_clean_BA_list_req(u8 DualID);
#ifdef __3G_RIL_MMI__
void mmi_mm_register_network_req(MMI_MMSRV_RegMode_e mode, MMI_MMSRV_Oper_Format_e format, u8 *pOper, MMI_MMSRV_RR_ACT_e eAct, u8 DualID);
void mmi_mm_update_preferred_list_req(u8 index, MMI_MMSRV_Oper_Format_e operFormat, u8* pOper, u16 uAct, u8 DualID);
void mmi_mm_change_band_req(MMSRV_BandSelectionInfo_t bandSel, u8 DualID);
void mmi_mm_mspn_req(u8 DualID);
#else // #ifdef __3G_RIL_MMI__
void mmi_mm_register_network_req(MMI_MMSRV_RegMode_e mode, MMI_MMSRV_Oper_Format_e format, u8 *pOper, u8 DualID);
void mmi_mm_update_preferred_list_req(u8 index, MMI_MMSRV_Oper_Format_e operFormat, u8* pOper, u8 DualID);
void mmi_mm_change_band_req(MMI_MMSRV_Band_e  bandID, u8 DualID);
#endif // #ifdef __3G_RIL_MMI__ 
//void mmi_mm_query_preferred_list_req(u8 DualID);
//void mmi_mm_query_band_req(u8 DualID);
//void mmi_mm_change_line_req(MMI_MMSRV_Line_Service_e  lineNumber, u8 DualID);
//void mmi_mm_query_line_req(u8 DualID);
#ifdef __GPRS_MMI__
void mmi_mm_gprs_attach_req(MMI_MMSRV_GPRS_Reg_e operation, u8 DualID);
#endif //__GPRS_MMI__
void mmi_mm_abort_req(u8 DualID);
#ifndef __3G_RIL_MMI__
void mmi_mm_get_cell_info_req(MMI_MMSRV_CellMode_e eCellMode, MMI_MMSRV_Cell_ReqDump_e reqDump, u8 DualID);
#endif //__3G_RIL_MMI__
void mmi_mm_query_diverted_call_req(u8 DualID);
void mmi_mm_radio_on_off_req(u8 DualID, MMI_MMSRV_Radio_OnOff_e flag);

#ifdef __3G_RIL_MMI__
#ifndef __SDK_SIMULATION__
void mmi_mm_send_unsolicited_info_to_ril(void *pData);
#endif  // ifndef __SDK_SIMULATION__
void mmi_mm_read_musermode_req(u8 DualID);

#endif //__3G_RIL_MMI__



#ifdef __MM_TEST__
// Unit test code
//void mmi_mm_search_network_req(IBase *pRecipient, u8 DualID);
//void mmi_mm_register_network_req(IBase *pRecipient, MMI_MMSRV_RegMode_e mode, MMI_MMSRV_Oper_Format_e format, u8 *pOper, u8 DualID);
//void mmi_mm_update_preferred_list_req(IBase *pRecipient, u8 index, MMI_MMSRV_Oper_Format_e operFormat, u8* pOper, u8 DualID);
void mmi_mm_query_registered_plmn_info_req(IBase *pRecipient, u8 DualID);
void mmi_mm_query_preferred_list_req(IBase *pRecipient, u8 DualID);
//void mmi_mm_change_band_req(IBase *pRecipient, MMI_MMSRV_Band_e  bandID, u8 DualID);
void mmi_mm_query_band_req(IBase *pRecipient, u8 DualID);
void mmi_mm_change_line_req(IBase *pRecipient, MMI_MMSRV_Line_Service_e  lineNumber, u8 DualID);
void mmi_mm_query_line_req(IBase *pRecipient, u8 DualID);
//void mmi_mm_gprs_attach_req(IBase *pRecipient, MMI_MMSRV_GPRS_Reg_e operation, u8 DualID);
//void mmi_mm_abort_req(IBase *pRecipient, u8 DualID);
//void mmi_mm_get_cell_info_req(IBase *pRecipient, MMI_MMSRV_CellMode_e eCellMode, u8 DualID);
//void mmi_mm_query_diverted_call_req(IBase *pRecipient, u8 DualID);
#ifdef __GPRS_MMI__
void mmi_mm_set_msclass_req(IBase *pRecipient, u8 DualID, MMI_MMSRV_GPRS_MSClass_e MSClass);
void mmi_mm_query_msclass_req(IBase *pRecipient, u8 DualID);
void mmi_mm_gprs_session_activate_req(IBase *pRecipient, u8 Cid, u8 DualID);
void mmi_mm_gprs_session_deactivate_req(IBase *pRecipient, u8 Cid, u8 DualID);
void mmi_mm_gprs_add_pdp_context_req(IBase *pRecipient, u8 DualID, MMSRV_GPRSPDPContextAddReq_t *pReq);
void mmi_mm_gprs_del_pdp_context_req(IBase *pRecipient, u8 DualID, u8 Cid);
void mmi_mm_gprs_set_qos_req(IBase *pRecipient, u8 DualID, MMSRV_GPRSQoSSetReq_t *pReq);
void mmi_mm_gprs_query_qos_req(IBase *pRecipient, u8 DualID, MMSRV_GPRSQoSQueReq_t *pReq);
//void mmi_mm_get_cell_info_req(IBase *pRecipient, MMI_MMSRV_CellMode_e eCellMode, MMI_MMSRV_Cell_ReqDump_e reqDump, u8 DualID);
//void mmi_mm_radio_on_off_req(IBase *pRecipient, u8 DualID, MMI_MMSRV_Radio_OnOff_e flag);
void mmi_mm_set_wgprs_req(IBase *pRecipient, u8 DualID, u8 Cid, MMI_MMSRV_WGPRS_Mode_e Mode, MMI_MMSRV_WGPRS_StatusOnOff_e Status, MMI_MMSRV_WGPRS_MultiSlotClass_e SlotClass);
void mmi_mm_query_wgprs_req(IBase *pRecipient, u8 DualID, MMI_MMSRV_WGPRS_Mode_e Mode, u8 Cid);
#endif //__GPRS_MMI__
#ifdef __PROGRAM_TEMP_IMEI_MMI__
void mmi_mm_store_imei_req(IBase *pRecipient, u8 DualID, u8 *pIMEI);
#endif
#else

//void mmi_mm_search_network_req(u8 DualID);
//void mmi_mm_register_network_req(MMI_MMSRV_RegMode_e mode, MMI_MMSRV_Oper_Format_e format, u8 *pOper, u8 DualID);
//void mmi_mm_update_preferred_list_req(u8 index, MMI_MMSRV_Oper_Format_e operFormat, u8* pOper, u8 DualID);
void mmi_mm_query_registered_plmn_info_req(u8 DualID);
void mmi_mm_query_preferred_list_req(u8 DualID);
//void mmi_mm_change_band_req(MMI_MMSRV_Band_e  bandID, u8 DualID);
void mmi_mm_query_band_req(u8 DualID);
void mmi_mm_change_line_req(MMI_MMSRV_Line_Service_e  lineNumber, u8 DualID);
void mmi_mm_query_line_req(u8 DualID);
//void mmi_mm_gprs_attach_req(MMI_MMSRV_GPRS_Reg_e operation, u8 DualID);
//void mmi_mm_abort_req(u8 DualID);
//void mmi_mm_get_cell_info_req(MMI_MMSRV_CellMode_e eCellMode, u8 DualID);
//void mmi_mm_query_diverted_call_req(u8 DualID);
#ifdef __GPRS_MMI__
void mmi_mm_set_msclass_req(u8 DualID, MMI_MMSRV_GPRS_MSClass_e MSClass);
void mmi_mm_query_msclass_req(u8 DualID);
void mmi_mm_gprs_session_activate_req(u8 Cid, u8 DualID);
void mmi_mm_gprs_session_deactivate_req(u8 Cid, u8 DualID);
void mmi_mm_gprs_add_pdp_context_req(u8 DualID, MMSRV_GPRSPDPContextAddReq_t *pReq);
void mmi_mm_gprs_del_pdp_context_req(u8 DualID, u8 Cid);
void mmi_mm_gprs_set_qos_req(u8 DualID, MMSRV_GPRSQoSSetReq_t *pReq);
void mmi_mm_gprs_query_qos_req(u8 DualID, MMSRV_GPRSQoSQueReq_t *pReq);
//void mmi_mm_get_cell_info_req(MMI_MMSRV_CellMode_e eCellMode, MMI_MMSRV_Cell_ReqDump_e reqDump, u8 DualID);
//void mmi_mm_radio_on_off_req(u8 DualID, MMI_MMSRV_Radio_OnOff_e flag);
void mmi_mm_set_wgprs_req(u8 DualID, u8 Cid, MMI_MMSRV_WGPRS_Mode_e Mode, MMI_MMSRV_WGPRS_StatusOnOff_e Status, MMI_MMSRV_WGPRS_MultiSlotClass_e SlotClass);
void mmi_mm_query_wgprs_req(u8 DualID, MMI_MMSRV_WGPRS_Mode_e Mode, u8 Cid);
#endif //__GPRS_MMI__
#ifdef __PROGRAM_TEMP_IMEI_MMI__
void mmi_mm_store_imei_req(u8 DualID, u8 *pIMEI);
#endif
#endif

#ifdef __3G_RIL_MMI__
void mmi_mm_get_cell_info_req(MMI_MMSRV_CellMode_e eCellMode, MMI_MMSRV_Cell_ReqDump_e reqDump, u8 DualID);
void mmi_ril_misc_cmgr_req(u8 DualID);
void mmi_ril_misc_imei_req(u8 DualID);
void mmi_ril_misc_set_mcfg_req(u8 DualID, u8 bitLen, u8 *pData);
void mmi_ril_misc_query_mcfg_req(u8 DualID);
void mmi_ril_misc_dbb_reboot_req(u8 DualID, u8 bReboot);
void mmi_ril_rr_force_req(u8 DualID, MMI_MMSRV_RR_FORCE_CMD_e cmd, u32 ARFCN, u32 cellid);
void mmi_ril_misc_dbb_reset_factory_req(u8 DualID);

#ifdef __SDK_SIMULATION__
void mmi_ril_misc_send_test_dbb_reboot_req(u8 DualID);
#endif //__SDK_SIMULATION__
#endif // __3G_RIL_MMI__

#endif /* __MMI_REQ_MM_H__ */
