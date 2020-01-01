/**
 * @file mmi_req_vendor.h
 *
 * This header file defines all the request functions to vendor
 *
 * @version $Id: mmi_req_vendor.h 41649 2009-09-29 02:45:43Z christoph.kuo $
 */


#ifndef __MMI_REQ_VENDOR_H__
#define __MMI_REQ_VENDOR_H__

#include "mmi_vendorsrv_req_st.h"
#include "mmi_srv_usb.h"
#include "mmi_calllogsrv_def.h"

enum
{
	MMI_VEN_RET_SUCCESS = 0,
	MMI_VEN_RET_PLAY_FINISHED,
	MMI_VEN_RET_NOT_PLAYING,
	MMI_VEN_RET_ERROR
};
typedef u32 MmiVenRespCode_t;

void mmi_ven_sync_rsp(u32 apID, u32 SemID);
void mmi_codec_open_media_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, s32 mediaHandle);
void mmi_codec_open_media_codec_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_open_media_req_t* pOpenMediaReq);
void mmi_codec_close_media_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_close_media_codec_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_close_media_req_t* pCloseMediaReq);
void mmi_codec_get_playing_time_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, u32 playingTime);
void mmi_codec_get_playing_time_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, u32 playingTime, mmi_codec_get_playing_time_req_t* pGetPlayingTimeReq);
void mmi_codec_play_audio_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_play_audio_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_play_audio_req_t* pPlayAudioReq);
void mmi_codec_play_audio_raw_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_play_audio_raw_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_play_audio_raw_req_t* pPlayAudioRawReq);
void mmi_codec_play_midi_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_play_midi_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_play_midi_req_t* pPlayMidiReq);
void mmi_codec_pause_audio_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_pause_audio_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_pause_audio_req_t* pPauseAudioReq);
void mmi_codec_resume_audio_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_resume_audio_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_resume_audio_req_t* pResumeAudioReq);
void mmi_codec_stop_audio_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_stop_audio_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_stop_audio_req_t* pStopAudioReq);
void mmi_codec_set_audio_volume_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_set_audio_volume_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_set_audio_volume_req_t* pSetAudioVolReq);
void mmi_codec_get_audio_volume_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, u8 volume);
void mmi_codec_get_audio_volume_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, u8 volume, mmi_codec_get_audio_volume_req_t* pGetAudioVolReq);
void mmi_codec_play_video_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_play_video_sync_rsp(u32 apID, u32 SemID);
void mmi_codec_play_video_ind(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, mmi_ven_video_status_e eStatus, u32 nStatusData);
void mmi_codec_videostraming_filechange_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_videostraming_DLItf_rsp(u32 APID, s32 mediaHandle, void *pDLItfCb, s32 event, s32 DataLen, void *pData,MmiVenRespCode_t ret );
void mmi_codec_open_image_codec_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, s32 imgCodecHandle);
void mmi_codec_open_image_codec_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_open_image_handle_req_t *pOpenImgHandleReq);
void mmi_codec_close_image_codec_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_codec_close_image_codec_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_close_image_handle_req_t *pCloseImgHandleReq);
void mmi_codec_decode_image_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, s32 imgCodecHandle, ImageStatus_t *pDecodeStatus);
void mmi_codec_decode_image_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_decode_image_req_t *pDecodeImgReq, ImageStatus_t *pDecodeStatus);
void mmi_codec_get_next_image_frame_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, s32 imgCodecHandle, ImageStatus_t *pDecodeStatus);
void mmi_codec_get_next_image_frame_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_codec_decode_next_frame_req_t *pDecodeImgReq, ImageStatus_t *pDecodeStatus);
void mmi_ts_send_input_ind(u32 apID, u32 x, u32 y, u32 evt);
void mmi_cc_make_call_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_Ret retCode);
void mmi_cc_send_DTMF_rsp(mmi_cc_send_DTMF_req_t* pDTMFReq, boolean retCode);
#ifdef __SDK_API_01_SMS_MMS_CC__
void mmi_cc_make_call_get_call_id_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_Ret retCode, s32 state, s32 callID);
void mmi_cc_release_call_sync_rsp(u32 apID, u32 SemID, mmi_cc_release_call_req_t* pReleaseCallReq, s32 result);
#endif
void mmi_cc_call_status_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, u32 ret);
void mmi_cc_register_incomingcall_rsp(mmi_cc_register_incoming_call_req_t *pReq, MAE_Ret retCode);
u8 mmi_cc_register_incomingcall_filter(u8 *pCallNumber, u32 usrData, void *pFilterFunc);
void mmi_cc_register_incomingcall_ind(u32 apID, u8 indType, u8 *pCallNumber, u32 callID, u32 usrData, void *pHandlerFunc);
void mmi_cc_register_add_call_log_rsp(mmi_cc_register_add_call_log_req_t *pReq, MAE_Ret retCode);
void mmi_cc_register_add_call_log_ind(u32 apID, Mmi_CallLogLogChangedNotify_t *pCallLogNotify, u32 usrData, void *pCallLogListener);
void mmi_phb_browse_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_WChar *pStr, u16 nStrlen, u8 markedSize);
void mmi_phb_browse_sync_rsp(u32 apID, u32 SemID, mmi_phb_browse_req_t* pBrowseReq, MAE_WChar *pData, u16 dataLen, u8 markedSize);
void mmi_phb_add_contact_sync_rsp(u32 apID, u32 SemID, void *pRet, MmiVenRespCode_t ret);
void mmi_phb_add_contact_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_phb_write_contact_sync_rsp(u32 apID, u32 SemID, void *pRet, MmiVenRespCode_t ret);
void mmi_phb_write_contact_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, u16 u16Index, bool bNeedReturnIndex, MmiVenRespCode_t ret);
void mmi_phb_delete_contact_sync_rsp(u32 apID, u32 SemID, void *pRet, MmiVenRespCode_t ret);
void mmi_phb_delete_contact_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_phb_save_contact_by_handle_sync_rsp(u32 apID, u32 SemID, void *pRet, MmiVenRespCode_t ret);
void mmi_phb_save_contact_by_handle_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, u16 u16NewIndex, bool bNeedReturnIndex, MmiVenRespCode_t ret);
void mmi_phb_register_ready_sync_rsp(mmi_phb_register_ready_req_t *pReq, MAE_Ret retCode);
void mmi_phb_register_ready_ind(mmi_phb_register_ready_req_t *pReq);
void mmi_file_browse_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_WChar *pStr, u16 nStrlen, u8 markedSize);
void mmi_file_browse_sync_rsp(u32 apID, u32 SemID, mmi_file_browse_req_t* pBrowseReq, MAE_WChar *pData, u16 dataLen, u8 markedSize);
void mmi_file_browse_ex_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_WChar *pStr, u16 nStrlen, u8 markedSize);
void mmi_file_browse_ex_sync_rsp(u32 apID, u32 SemID, mmi_file_browse_req_t* pBrowseReq, MAE_WChar *pData, u16 dataLen, u8 markedSize);
void mmi_file_select_folder_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_WChar *pStr, u16 nStrlen);
void mmi_file_select_folder_sync_rsp(u32 apID, u32 SemID, mmi_file_select_folder_req_t* pReq, MAE_WChar *pData, u16 dataLen);
void mmi_sen_btapp_send_file_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_Ret retCode);
void mmi_sen_btapp_send_file_sync_rsp(u32 apID, u32 SemID, mmi_ven_sen_btapp_send_file_req_t* pReq, MAE_Ret retCode);
void mmi_cam_launch_app_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, void *pData);
void mmi_editor_edit_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_WChar *pStr, u16 nStrlen, editor_reult_t result);
void mmi_editor_edit_sync_rsp(u32 apID, u32 SemID, mmi_editor_edit_req_t* pEditReq, MAE_WChar *pData, u16 dataLen, editor_reult_t result);
void mmi_editor_close_sync_rsp(u32 apID, u32 SemID, mmi_editor_close_req_t* pReq, MAE_Ret retCode);
void mmi_editor_datetime_edit_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, bool bDate, u16 nYear, u8 nMonth, u8 nDay, u8 nHoue, u8 nMinute, u8 nSecond, editor_reult_t nResult);
void mmi_setting_select_SIM_rsp(u32 apID, mmi_ven_select_sim_req_t *pReqData, MAE_Ret nGetResult, mmi_ven_select_sim_t SIM_ID);

void mmi_msg_register_port_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_register_port_req_t* pRegPortReq);
void mmi_msg_deregister_port_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_deregister_port_req_t* pDeRegPortReq);
void mmi_msg_deregister_all_ports_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_deregister_all_port_req_t* pDeRegAllPortsReq);
void mmi_msg_register_telno_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_register_telno_req_t *pRegTelNoReq);
void mmi_msg_register_all_sms_msg_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_register_all_sms_msg_req_t* pRegAllPortsReq);

void mmi_msg_deregister_telno_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_deregister_telno_req_t *pDeRegTelNoReq);
void mmi_msg_deregister_all_telnos_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_deregister_all_telno_req_t *pDeRegAllTelNosReq);
void mmi_msg_register_srv_ready_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_register_srv_ready_t* pRegSrvReadyReq);
void mmi_msg_deregister_srv_ready_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_deregister_srv_ready_t* pDeRegSrvReadyReq);
void mmi_msg_keep_telno_msg_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_msg_keep_telno_msg_req_t *pKepTelNoMsgReq);
void mmi_msg_send_sms_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, msg_sms_send_result_t result, u8 sentPage);

bool mmi_msg_icoming_msg_filter(mmi_msg_header_t *pMsgHead, u16 *pMsgContent, u32 userData, void *pFilterFunc);
void mmi_msg_incoming_msg_ind(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, msg_type_t msgType, u32 msgId, u16 *pData, u16 dataByteLen);
void mmi_msg_srv_ready_ind(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, msg_type_t msgType);
void mmi_msg_get_srv_ready_rsp(u32 apID, boolean bReady, MmiVenRespCode_t ret, mmi_ven_Callback_Info_t* pCBInfo, msg_type_t msgType);
void mmi_msg_get_srv_ready_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, boolean bReady, mmi_msg_get_srv_ready_req_t *pReq);
void mmi_msg_received_msg_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, SMS_3rd_ReceiveData_t* pReceivedData, mmi_msg_get_received_sms_req_t* pReceivedSMS);
void mmi_msg_received_msg_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret, u16 msgId, SMS_3rd_ReceiveData_t* pReceivedData);

void mmi_msg_editor_sync_rsp(u32 apID, u32 SemID, mmi_msg_open_editor_req_t* pMsgEditorReq, MAE_Ret retCode);
void mmi_msg_editor_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_Ret retCode);

void mmi_msg_query_sms_srv_center_sync_rsp(mmi_msg_query_sms_srv_center_t *pSmsSrvCenterReq, MAE_Ret retCode);
void mmi_msg_set_sms_srv_center_sync_rsp(mmi_msg_set_sms_srv_center_t *pSmsSrvCenterReq, MAE_Ret retCode);
#ifdef __SDK_API_01_SMS_MMS_CC__
void mmi_msg_sms_get_header_list_sync_rsp(mmi_msg_sms_get_header_list_req_t *pMsgReq, MAE_Ret retCode, u32 num, mmi_msg_header_t *pHeaderList);
void mmi_msg_sms_get_header_list_async_rsp(mmi_msg_sms_get_header_list_req_t *pMsgReq, MAE_Ret retCode, u32 num, mmi_msg_header_t *pHeaderList);
void mmi_msg_sms_modify_header_sync_rsp(mmi_msg_sms_modify_header_req_t *pMsgReq, MAE_Ret retCode);
void mmi_msg_delete_sync_rsp(mmi_msg_delete_req_t *pMsgReq, MAE_Ret retCode);
void mmi_msg_delete_async_rsp(mmi_msg_delete_req_t *pMsgReq, MAE_Ret retCode);
void mmi_msg_mms_send_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MAE_Ret retCode, u8 responseStatus);
#endif //__SDK_API_01_SMS_MMS_CC__
void mmi_msg_sms_backup_sync_rsp(mmi_msg_sms_backup_req_t *pMsgReq, MAE_Ret retCode);
void mmi_msg_sms_backup_async_rsp(mmi_msg_sms_backup_req_t *pMsgReq, MAE_Ret retCode, mmi_msg_sms_backup_info_t* pBackupInfo);
void mmi_msg_sms_restore_sync_rsp(mmi_msg_sms_restore_req_t *pMsgReq, MAE_Ret retCode);
void mmi_msg_sms_restore_async_rsp(mmi_msg_sms_restore_req_t *pMsgReq, MAE_Ret retCode);
void mmi_msg_sms_add_sync_rsp(mmi_msg_sms_add_req_t *pMsgReq, MAE_Ret retCode, u16 msgId);
void mmi_msg_sms_add_async_rsp(mmi_msg_sms_add_req_t *pMsgReq, MAE_Ret retCode, u16 msgId);
MAE_Ret mmi_start_ven_req(u32 apID, void *pData, u32 data_len, bool bSessionOpen);
MAE_Ret mmi_stop_ven_req(u32 apID);
MAE_Ret mmi_suspend_ven_req(u32 apID);
MAE_Ret mmi_resume_ven_req(u32 apID);
MAE_Ret mmi_background_ven_req(u32 apID, void *pData, u32 data_len);
MAE_Ret mmi_foreground_ven_req(u32 apID, void *pData, u32 data_len);
void mmi_stc_stutus_change_cnf(u32 apID, mmi_ven_stc_t statusInd, mmi_ven_Callback_Info_t *pCBInfo, mmi_ven_stc_ret_t ret);
void mmi_stc_stutus_change_sync_cnf(mmi_ven_stc_ind_t *pStcInd, mmi_ven_stc_ret_t ret);

u32 mmi_ven_TransferToVenSettingRetCode(MAE_Ret ret);
MAE_Ret mmi_send_user_extend_msg(u32 apID, void * UserMsg);

void mmi_ven_gra_get_vis_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_ven_gra_get_vis_req_t *pMmiReq, u8 bVis);
void mmi_ven_gra_set_vis_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_ven_gra_set_vis_req_t *pMmiReq);
void mmi_ven_gra_set_display_mode_sync_rsp(mmi_ven_gra_set_display_mode_req_t *pMsgReq, MAE_Ret retCode);
void mmi_ven_gra_set_display_mode_async_rsp(mmi_ven_gra_set_display_mode_req_t *pMsgReq, MAE_Ret retCode);

void mmi_ven_ui_show_comp_async_rsp(u32 apID, mmi_ven_ui_show_comp_rsp_t *pUiRsp, mmi_ven_Callback_Info_t* pCBInfo);
void mmi_ven_ui_show_comp_sync_rsp(u32 apID, u32 SemID, mmi_ven_ui_show_comp_sync_rsp_t *pRet, u32 *pRetCode, void *pMmiUsrRsp);
void mmi_ven_ui_close_comp_sync_rsp(u32 apID, u32 SemID, mmi_ven_ui_ret_t ret, u32 *pRetCode);
void mmi_ven_ui_set_interrupt_level_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, mmi_ven_ui_ret_t ret);
void mmi_ven_ui_set_interrupt_level_sync_rsp(u32 apID, u32 SemID, mmi_ven_ui_ret_t ret, u32 *pRetCode);
void mmi_ven_ui_set_backlight_behavior_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, mmi_ven_ui_ret_t ret);
void mmi_ven_ui_set_backlight_behavior_sync_rsp(u32 apID, u32 SemID, mmi_ven_ui_ret_t ret, u32 *pRetCode);
void mmi_ven_ui_backlight_ind(u32 apID, boolean bBacklightOn);
void mmi_ven_ui_update_comp_sync_rsp(u32 apID, u32 SemID, mmi_ven_ui_show_comp_sync_rsp_t *pRet, u32 *pRetCode);
void mmi_ui_get_applet_status_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, u32 ret);
void mmi_ven_ui_enable_launch_keyguard_async_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, mmi_ven_ui_ret_t ret);
void mmi_ven_ui_enable_launch_keyguard_sync_rsp(u32 apID, u32 SemID, mmi_ven_ui_ret_t ret, u32 *pRetCode);

void mmi_stc_start_cnf(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, mmi_ven_stc_ret_t ret);

#ifdef __WAP_MMI_CDWAP__
void mmi_wap_open_browser_rsp(u32 apID, mmi_ven_Callback_Info_t* pCBInfo, MmiVenRespCode_t ret);
void mmi_wap_open_browser_sync_rsp(u32 apID, u32 SemID, mmi_wap_open_browser_req_t* pMsgOpenBrowserReq, MAE_Ret retCode);
#endif

MAE_Ret mmi_graphics_get_vendor_display_frame_buffer(u32 apID, BitmapBase_t **ppBitmapBase);
void mmi_graphics_enable_vendor_display_update(u32 apID, u8 bEnable);

void mmi_usb_status_ind(MMI_USB_STATUS_E usbStatus);

void mmi_util_get_cellinfo_sync_rsp(u32 apID, u32 SemID, mmi_ven_util_get_cellinfo_req_t* pGetCellinfoReq, MAE_Ret retCode);
void mmi_mm_register_listener_sync_rsp(u32 apID, u32 SemID, MmiVenRespCode_t ret, mmi_ven_mm_register_listener_req_t* pMMIReq);
void mmi_mm_incoming_msg_ind(u32 apID, mmi_ven_Callback_Info_t* pCbInfo, u32 nEventType, u32 nUserEventMask, u32 param1, u32 param2);
s32 mmi_codec_videostraming_Avp_DLItf_Req(s32 message_type, s32 data_size, void *data);
#if defined (__G_SENSOR__)
void mmi_sen_gsensor_reg_notify_ind(u32 apID, u16 x, u16 y, u16 z, u32 usrData, void *pGsensorNotify);
void mmi_sen_gsensor_reg_notify_sync_rsp(mmi_ven_sen_gsensor_reg_notify_req_t *pReq, MAE_Ret retCode);
void mmi_sen_gsensor_reg_notify_async_rsp(mmi_ven_sen_gsensor_reg_notify_req_t *pReq, MAE_Ret retCode);
void mmi_sen_gsensor_get_devinfo_sync_rsp(mmi_ven_sen_gsensor_get_devinfo_req_t *pReq, MAE_Ret retCode);
void mmi_sen_gsensor_get_devinfo_async_rsp(mmi_ven_sen_gsensor_get_devinfo_req_t *pReq, MAE_Ret retCode, u16 nAxisNum, u16 nSensitiveLevel);
void mmi_sen_gsensor_reg_motion_listener_ind(u32 apID, u32 type, u32 value, u32 usrData, void *pMotionListener);
void mmi_sen_gsensor_reg_motion_listener_sync_rsp(mmi_ven_sen_gsensor_reg_motion_listener_req_t *pReq, MAE_Ret retCode);
void mmi_sen_gsensor_reg_motion_listener_async_rsp(mmi_ven_sen_gsensor_reg_motion_listener_req_t *pReq, MAE_Ret retCode);
void mmi_sen_gsensor_get_last_motion_sync_rsp(mmi_ven_sen_gsensor_get_last_motion_req_t *pReq, MAE_Ret retCode);
void mmi_sen_gsensor_get_last_motion_async_rsp(mmi_ven_sen_gsensor_get_last_motion_req_t *pReq, MAE_Ret retCode, u32 type, u32 motionInfo); 
#endif //#if defined (__G_SENSOR__)
#endif //__MMI_REQ_VENDOR_H__
