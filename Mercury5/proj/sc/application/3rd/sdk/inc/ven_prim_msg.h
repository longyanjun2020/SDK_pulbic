/**
 *
 * @file    ven_prim_msg.h
 * @brief   This file defines the messages body for sdk
 * @author  Jorena.Ku
 * @version $Id: ven_prim_msg.h 45590 2009-11-13 18:24:53Z william.lien $
 *
 */

#ifndef __VEN_PRIM_MSG_H__
#define __VEN_PRIM_MSG_H__

#include "ven_common_def.h"
#include "ven_prim.h"
#include "ven_setting_stmsg.h"
#include "ven_file_msgt.h"
#include "ven_phb_msgt.h"
#include "ven_codec_msgt.h"
#include "ven_cc_msgt.h"
#include "ven_editor_msgt.h"
#include "ven_time_msgt.h"
#include "ven_msg_msgt.h"
#include "ven_ts_msgt.h"
#include "ven_stc_msgt.h"
#include "ven_socket_stmsg.h"
#include "ven_clipboard_stmsg.h"
#include "ven_graphics_msgt.h"
#include "ven_user_stmsg.h"
#include "ven_os_msgt.h"
#include "ven_ui_msgt.h"
#include "ven_kpd_msgt.h"
#include "ven_drv_msgt.h"
#include "ven_wap_msgt.h"
#include "ven_cam_msgt.h"
#include "ven_gps_msgt.h"
#include "ven_cus_msgt.h"
#include "ven_util.h"
#include "ven_util_msgt.h"
#include "ven_mm_msgt.h"
#include "ven_sensor_msgt.h"
#include "ven_wlan_msgt.h"
#ifdef __RFID_SDK_SUPPORT__
#include "ven_rfid_msgt.h"
#endif


/* ---------------------------------------------------------------------------- */
/*                        - Definition of the Body_t union -                    */
/* ---------------------------------------------------------------------------- */



typedef union
{
    iVen_setting_getFileStr_req_t iVen_setting_getFileStr_req;
    iVen_setting_getFileStr_rsp_t iVen_setting_getFileStr_rsp;
    iVen_setting_setFileURL_req_t iVen_setting_setFileURL_req;
    iVen_setting_setFileURL_rsp_t iVen_setting_setFileURL_rsp;

    iVen_setting_getVolume_req_t iVen_setting_getVolume_req;
    iVen_setting_getVolume_rsp_t iVen_setting_getVolume_rsp;

    iVen_setting_getVibrate_req_t iVen_setting_getVibrate_req;
    iVen_setting_getVibrate_rsp_t iVen_setting_getVibrate_rsp;

    iVen_setting_getKeypadTone_req_t iVen_setting_getKeypadTone_req;
    iVen_setting_getKeypadTone_rsp_t iVen_setting_getKeypadTone_rsp;

    iVen_setting_getNetworkProfile_req_t iVen_setting_getNetworkProfile_req;
	iVen_setting_getNetworkProfile_ex_req_t iVen_setting_getNetworkProfile_ex_req;
    iVen_setting_getNetworkProfile_rsp_t iVen_setting_getNetworkProfile_rsp;
	iVen_setting_getNetworkProfile_ex_rsp_t iVen_setting_getNetworkProfile_ex_rsp;
    iVen_setting_setNetworkProfile_req_t iVen_setting_setNetworkProfile_req;
	iVen_setting_setNetworkProfile_ex_req_t iVen_setting_setNetworkProfile_ex_req;
    iVen_setting_setNetworkProfile_rsp_t iVen_setting_setNetworkProfile_rsp;
    iVen_setting_getSelectSIM_req_t iVen_setting_getSelectSIM_req;
    iVen_setting_getSelectSIM_rsp_t iVen_setting_getSelectSIM_rsp;
    iVen_setting_getDefaultSIM_req_t iVen_setting_getDefaultSIM_req;
    iVen_setting_getDefaultSIM_rsp_t iVen_setting_getDefaultSIM_rsp;
    iVen_setting_getSIMStatus_req_t iVen_setting_getSIMStatus_req;
    iVen_setting_getSIMStatus_rsp_t iVen_setting_getSIMStatus_rsp;
    iVen_setting_getSIMIccId_req_t  iVen_setting_getSIMIccId_req;
    iVen_setting_getLanguage_req_t  iVen_setting_getLanguage_req;
    iVen_setting_getLanguage_rsp_t  iVen_setting_getLanguage_rsp;
    iVen_setting_getNetworkProfileNum_req_t iVen_setting_getNetworkProfileNum_req;
    iVen_setting_getNetworkProfileByIdx_req_t iVen_setting_getNetworkProfileByIdx_req;
    iVen_setting_getDataAccountNum_req_t iVen_setting_getDataAccountNum_req;
    iVen_setting_getDataAccountByIdx_req_t iVen_setting_getDataAccountByIdx_req;
    iVen_setting_queryAirplaneMode_req_t iVen_setting_queryAirplaneMode_req;

    iVen_file_browse_req_t iVen_file_browse_req;
    iVen_file_browse_rsp_t iVen_file_browse_rsp;
    iVen_file_browse_ex_req_t iVen_file_browse_ex_req;
    iVen_file_browse_ex_rsp_t iVen_file_browse_ex_rsp;

	iVen_file_select_folder_req_t iVen_file_select_folder_req;
    iVen_file_select_folder_rsp_t iVen_file_select_folder_rsp;
	iVen_file_get_avail_path_req_t iVen_file_get_avail_path_req;

    iVen_file_sync_folder_req_t iVen_file_sync_folder_req;
    iVen_file_sync_folder_rsp_t iVen_file_sync_folder_rsp;

    iVen_file_file_access_ind_t iVen_file_file_access_ind;

    iVen_file_async_operation_rsp_t iVen_file_async_operation_rsp;

	iVen_time_set_time_req_t iVen_time_set_time_req;
    iVen_time_set_time_rsp_t iVen_time_set_time_rsp;

    iVen_time_set_timezone_req_t iVen_time_set_timezone_req;
    iVen_time_set_timezone_rsp_t iVen_time_set_timezone_rsp;

    iVen_socket_gethostbyname_req_t iVen_socket_gethostbyname_req;
    iVen_socket_gethostbyname_rsp_t iVen_socket_gethostbyname_rsp;
    iVen_socket_createsocket_req_t        iVen_socket_createsocket_req;
    iVen_socket_closesocket_req_t iVen_socket_closesocket_req;
    iVen_socket_closesocket_rsp_t iVen_socket_closesocket_rsp;
    iVen_socket_connect_req_t iVen_socket_connect_req;
    iVen_socket_connect_rsp_t iVen_socket_connect_rsp;
    iVen_socket_regRecvCB_req_t iVen_socket_regRecvCB_req;
    iVen_socket_recv_notify_t iVen_socket_recv_notify;
    iVen_socket_regRecvFromCB_req_t iVen_socket_regRecvFromCB_req;
    iVen_socket_recvfrom_notify_t iVen_socket_recvfrom_notify;
    iVen_socket_send_req_t iVen_socket_send_req;
    iVen_socket_send_rsp_t iVen_socket_send_rsp;
    iVen_socket_sendto_req_t iVen_socket_sendto_req;
    iVen_socket_sendto_rsp_t iVen_socket_sendto_rsp;
    iVen_socket_create_datalink_req_t iVen_socket_create_datalink_req;
    iVen_socket_create_datalink_rsp_t iVen_socket_create_datalink_rsp;
	iVen_socket_query_datalink_req_t iVen_socket_query_datalink_available_req;
    iVen_socket_close_datalink_req_t iVen_socket_close_datalink_req;
    iVen_socket_close_datalink_rsp_t iVen_socket_close_datalink_rsp;
    iVen_socket_regStatusCB_req_t iVen_socket_regStatusCB_req;
	iVen_socket_regStatusCB_req_t iVen_socket_deregStatusCB_req;
    iVen_socket_status_indication_t iVen_socket_status_indication;
    iVen_socket_receiveReady_ind_t iVen_socket_receiveReady_ind;
    iVen_socket_setsockopt_req_t iVen_socket_setsockopt_req;
    iVen_socket_getsockopt_req_t iVen_socket_getsockopt_req;
    iVen_socket_shutdown_req_t iVen_socket_shutdown_req;
    iVen_socket_recv_req_t iVen_socket_recv_req;
    iVen_socket_recvfrom_req_t iVen_socket_recvfrom_req;
    //////////////////////////////////////////////////////////////////////////
    iVen_socket_create_datalink_ex_req_t iVen_socket_create_datalink_ex_req;
    iVen_socket_close_datalink_ex_req_t iVen_socket_close_datalink_ex_req;
    iVen_socket_create_datalink_ex_rsp_t iVen_socket_create_datalink_ex_rsp;
    iVen_socket_close_datalink_ex_rsp_t iVen_socket_close_datalink_ex_rsp;
    iVen_socket_close_all_datalinks_ex_rsp_t iVen_socket_close_all_datalinks_ex_rsp;
    iVen_socket_regStatusCB_ex_req_t iVen_socket_regStatusCB_ex_req;
    iVen_socket_deregStatusCB_ex_req_t iVen_socket_deregStatusCB_ex_req;
    iVen_socket_close_all_datalinks_ex_req_t iVen_socket_close_all_datalinks_ex_req;
	  iVen_socket_ping_req_t iVen_socket_ping_req;
	  iVen_socket_ping_rsp_t iVen_socket_ping_rsp;
	  iVen_socket_bind_req_t iVen_socket_bind_req;
    //////////////////////////////////////////////////////////////////////////
    iVen_wlan_get_cur_connected_device_info_req_t iVen_wlan_get_cur_connected_device_info_req;

    iVen_ts_input_ind_t  iVen_ts_input_ind;

    iVen_stc_start_req_t iVen_stc_start_req;
    iVen_stc_suspend_req_t iVen_stc_suspend_req;
    iVen_stc_resume_req_t iVen_stc_resume_req;
    iVen_stc_stop_req_t iVen_stc_stop_req;
    iVen_stc_rsp_t iVen_stc_stat_ctrl_rsp;
    iVen_stc_notify_stop_t iVen_stc_notify_stop;
    iVen_stc_notify_start_t iVen_stc_notify_start;
    iVen_stc_start_cnf_t iVen_stc_start_cnf;
    iVen_stc_notify_status_change_t iVen_stc_notify_status_change;
    iVen_stc_status_change_cnf_t iVen_stc_status_change_cnf;	

    iVen_gra_set_vis_req_t iVen_gra_set_vis_req;
    iVen_gra_get_vis_req_t iVen_gra_get_vis_req;
    iVen_gra_set_display_mode_req_t iVen_gra_set_display_mode_req;
    iVen_gra_set_display_mode_rsp_t iVen_gra_set_display_mode_rsp;	
    iVen_os_message_ind_t  iVen_os_message_ind;

    iVen_ui_show_comp_req_t iVen_ui_show_comp_req;
    iVen_ui_show_comp_rsp_t iVen_ui_show_cmop_rsp;
    iVen_ui_close_comp_req_t iVen_ui_close_comp_req;
    iVen_ui_set_interrupt_level_req_t iVen_ui_set_interrupt_level_req;
    iVen_ui_set_interrupt_level_rsp_t iVen_ui_set_interrupt_level_rsp;
    iVen_ui_statusbar_draw_icon_req_t iVen_ui_statusbar_draw_icon_req;
    iVen_ui_statusbar_draw_image_req_t iVen_ui_statusbar_draw_image_req;
    iVen_ui_set_backlight_behavior_req_t iVen_ui_set_backlight_behavior_req;
    iVen_ui_set_backlight_req_t iVen_ui_set_backlight_req;
    iVen_ui_set_backlight_behavior_rsp_t iVen_ui_set_backlight_behavior_rsp;
    iVen_ui_enable_launch_keyguard_req_t        iVen_ui_enable_launch_keyguard_req;
    iVen_ui_enable_launch_keyguard_rsp_t        iVen_ui_enable_launch_keyguard_rsp;
    iVen_ui_backlight_ind_t iVen_ui_backlight_ind;
    iVen_ui_get_backlight_info_req_t            iVen_ui_get_backlight_info_req;
    iVen_ui_get_backlight_info_rsp_t            iVen_ui_get_backlight_info_rsp;
    iVen_ui_update_comp_req_t iVen_ui_update_comp_req;
    iVen_ui_get_applet_status_req_t iVen_ui_get_applet_status_req;
    iVen_ui_get_applet_status_rsp_t iVen_ui_get_applet_status_rsp;	

    iVen_kpd_subscribe_req_t iVen_kpd_subscribe_req;
    iVen_kpd_reset_backlight_req_t iVen_kpd_reset_backlight_req;
	
    iVen_drv_acs_ind_t iVen_drv_acs_ind;
    iVen_drv_usb_ind_t iVen_drv_usb_ind;
    iVen_drv_backlight_ind_t iVen_drv_backlight_ind;
    iVen_drv_UsbInfo_t iVen_drv_UsbInfo;

    iVen_wap_open_browser_req_t iVen_wap_open_browser_req;
    iVen_wap_open_browser_rsp_t iVen_wap_open_browser_rsp;
	
#ifdef __3G_RIL_MMI__
    iVen_query_NetworkStatus_req_t iVen_query_NetworkStatus_req;
    iVen_Get_IMSI_req_t iVen_Get_IMSI_req;
#endif // _3G_RIL_MMI__   	
	
#ifndef __SDK_API_WAP_MMS_ONLY__
    iVen_setting_getDefaultCam_req_t iVen_setting_getDefaultCam_req;

    iVen_clipboard_getSetting_req_t     iVen_clipboard_getSetting_req;
    iVen_clipboard_copyText_req_t       iVen_clipboard_copyText_req;
    iVen_clipboard_getCopyText_req_t    iVen_clipboard_getCopyText_req;
    iVen_clipboard_hasCopyText_req_t    iVen_clipboard_hasCopyText_req;

    iVen_codec_open_media_req_t iVen_codec_open_media_req;
    iVen_codec_open_media_rsp_t iVen_codec_open_media_rsp;

    iVen_phb_browse_req_t iVen_phb_browse_req;
    iVen_phb_browse_rsp_t iVen_phb_browse_rsp;

    iVen_phb_save_contact_req_t iVen_phb_save_contact_req;
    iVen_phb_save_contact_rsp_t iVen_phb_save_contact_rsp;

    iVen_phb_write_contact_req_t iVen_phb_write_contact_req;
    iVen_phb_write_contact_rsp_t iVen_phb_write_contact_rsp;
    
    iVen_phb_delete_contact_req_t iVen_phb_delete_contact_req;
    iVen_phb_delete_contact_rsp_t iVen_phb_delete_contact_rsp;
    
    iVen_phb_save_contact_by_handle_req_t iVen_phb_save_contact_by_handle_req;
    iVen_phb_save_contact_by_handle_rsp_t iVen_phb_save_contact_by_handle_rsp;
    
    iVen_phb_find_first_req_t iVen_phb_find_first_req;
    iVen_phb_find_first_rsp_t iVen_phb_find_first_rsp;

    iVen_phb_find_next_req_t iVen_phb_find_next_req;
    iVen_phb_find_next_rsp_t iVen_phb_find_next_rsp;

    iVen_phb_get_mem_status_req_t iVen_phb_get_mem_status_req;
    iVen_phb_get_mem_status_rsp_t iVen_phb_get_mem_status_rsp;

    iVen_phb_number_fuzzy_search_req_t iVen_phb_number_fuzzy_search_req;
    iVen_phb_number_fuzzy_search_rsp_t iVen_phb_number_fuzzy_search_rsp;

	iVen_phb_query_ready_req_t iVen_phb_query_ready_req;
	iVen_phb_register_ready_req_t iVen_phb_register_ready_req;
	iVen_phb_register_ready_ind_t iVen_phb_register_ready_ind;
    iVen_codec_close_media_req_t iVen_codec_close_media_req;
    iVen_codec_close_media_rsp_t iVen_codec_close_media_rsp;

	iVen_codec_resource_state_ind_t iVen_codec_resource_state_ind;

    iVen_codec_get_file_info_rsp_t iVen_codec_get_file_info_rsp;

    /// the request is provided by ABL_VdoGetFileInfoSyncReq/ABL_VdoGetFileInfoReq
    iVen_codec_get_vdo_ext_info_rsp_t iVen_codec_get_vdo_ext_info_rsp;

    iVen_codec_get_playing_time_req_t iVen_codec_get_playing_time_req;
    iVen_codec_get_playing_time_rsp_t iVen_codec_get_playing_time_rsp;

    iVen_codec_play_audio_req_t iVen_codec_play_audio_req;
    iVen_codec_play_audio_rsp_t iVen_codec_play_audio_rsp;

    iVen_codec_play_audio_raw_req_t iVen_codec_play_audio_raw_req;
    iVen_codec_play_audio_raw_rsp_t iVen_codec_play_audio_raw_rsp;

    iVen_codec_play_midi_req_t iVen_codec_play_midi_req;
    iVen_codec_play_midi_rsp_t iVen_codec_play_midi_rsp;


    iVen_codec_pause_audio_req_t iVen_codec_pause_audio_req;
    iVen_codec_pause_audio_rsp_t iVen_codec_pause_audio_rsp;

    iVen_codec_resume_audio_req_t iVen_codec_resume_audio_req;
    iVen_codec_resume_audio_rsp_t iVen_codec_resume_audio_rsp;

    iVen_codec_stop_audio_req_t iVen_codec_stop_audio_req;
    iVen_codec_stop_audio_rsp_t iVen_codec_stop_audio_rsp;

    iVen_codec_set_audio_pos_rsp_t iVen_codec_set_audio_pos_rsp;

    iVen_codec_set_audio_volume_req_t iVen_codec_set_audio_volume_req;
    iVen_codec_set_audio_volume_rsp_t iVen_codec_set_audio_volume_rsp;

    iVen_codec_get_audio_volume_req_t iVen_codec_get_audio_volume_req;
    iVen_codec_get_audio_volume_rsp_t iVen_codec_get_audio_volume_rsp;
    iVen_codec_play_audio_streaming_rsp_t iVen_codec_play_audio_streaming_rsp;

    iVen_codec_audio_start_record_rsp_t iVen_codec_audio_start_record_rsp;
    iVen_codec_audio_stop_record_rsp_t iVen_codec_audio_stop_record_rsp;

    iVen_codec_start_audio_stream_record_req_t iVen_codec_start_audio_stream_record_req;
    iVen_codec_start_audio_stream_record_rsp_t iVen_codec_start_audio_stream_record_rsp;

    iVen_codec_stop_audio_stream_record_req_t iVen_codec_stop_audio_stream_record_req;
    iVen_codec_stop_audio_stream_record_rsp_t iVen_codec_stop_audio_stream_record_rsp;
#ifdef __MMI_OMA_DRM_V1__
    iVen_codec_check_drmrights_req_t iVen_codec_check_drmrights_req;
    iVen_codec_consume_drmrights_req_t iVen_codec_consume_drmrights_req;
#endif
    iVen_codec_play_video_req_t iVen_codec_play_video_req;
    iVen_codec_play_video_rsp_t iVen_codec_play_video_rsp;
    iVen_codec_play_video_ind_t iVen_codec_play_video_ind;

    iVen_codec_play_videostreaming_req_t iVen_codec_play_videostream_req;
    /// it uses iVen_codec_play_video_ind as iVen_codec_play_videostream_rsp
    iVen_codec_stop_video_req_t iVen_codec_stop_video_req;
    /// it uses iVen_codec_play_video_rsp as iVen_codec_stop_video_rsp
    iVen_codec_set_video_seek_req_t iVen_codec_set_video_seek_req;
    /// it uses iVen_codec_play_video_rsp as iVen_codec_set_video_seek_rsp
    iVen_codec_videostreaming_download_req_t iVen_codec_videostream_download_req;
    ///
    iVen_codec_videostreaming_status_change_notify_req_t iVen_codec_videostreaming_status_change_notify_req;
    iVen_codec_get_videostreaminginfo_req_t iVen_codec_get_videostreaminfo_req;
    iVen_codec_get_videostreaminginfo_rsp_t iVen_codec_get_videostreaminfo_rsp; 
    iVen_codec_videostreaming_filechange_req_t iVen_codec_videostream_filechange_req;
    iVen_codec_videostreaming_filechange_rsp_t iVen_codec_videostreaming_filechage_rsp; 
    iVen_codec_videostreaming_DLItf_rsp_t iVen_codec_videostreaming_DLItf_rsp;

    iVen_codec_open_image_codec_req_t iVen_codec_open_image_codec_req;
    iVen_codec_open_image_codec_rsp_t iVen_codec_open_image_codec_rsp;

    iVen_codec_close_image_codec_req_t iVen_codec_close_image_codec_req;
    iVen_codec_close_image_codec_rsp_t iVen_codec_close_image_codec_rsp;

    iVen_codec_decode_image_req_t iVen_codec_decode_image_req;
    iVen_codec_decode_image_rsp_t iVen_codec_decode_image_rsp;
    iVen_codec_encode_image_rsp_t iVen_codec_jpg_encode_image_rsp;

    iVen_codec_get_next_image_frame_req_t iVen_codec_get_next_image_frame_req;
    iVen_codec_get_next_image_frame_rsp_t iVen_codec_get_next_image_frame_rsp;

    iVen_cc_make_call_req_t iVen_cc_make_call_req;
	iVen_cc_make_call_rsp_t	iVen_cc_make_call_rsp;
	
    iVen_cc_send_DTMF_req_t iVen_cc_send_DTMF_req;
    iVen_cc_send_DTMF_rsp_t iVen_cc_send_DTMF_rsp;
    iVen_cc_abort_DTMF_req_t iVen_cc_abort_DTMF_req;
    iVen_cc_enable_DL_voice_req_t iVen_cc_enable_DL_voice_req;
#ifdef __SDK_API_01_SMS_MMS_CC__	
	iVen_cc_make_call_get_call_id_rsp_t	iVen_cc_make_call_get_call_id_rsp;
	iVen_cc_release_call_req_t iVen_cc_hangup_call_req;
#endif	

	iVen_cc_register_incoming_call_req_t iVen_cc_register_incoming_call_req;
	iVen_cc_register_incoming_call_ind_t iVen_cc_register_incoming_call_ind;
	iVen_cc_register_add_call_log_req_t iVen_cc_register_add_call_log_req;
	iVen_cc_register_call_log_ind_t iVen_cc_register_call_log_ind;
    iVen_cc_get_call_status_req_t iVen_cc_get_call_status_req;
    iVen_cc_get_call_status_rsp_t iVen_cc_get_call_status_rsp;	
	
    iVen_editor_edit_req_t iVen_editor_edit_req;
    iVen_editor_edit_rsp_t iVen_editor_edit_rsp;
	iVen_editor_close_req_t iVen_editor_close_req;	
	iVen_editor_datetime_req_t iVen_editor_datetime_req;
	iVen_editor_datetime_rsp_t iVen_editor_datetime_rsp;

    iVen_msg_send_sms_req_t iVen_msg_send_sms_req;
    iVen_msg_send_sms_rsp_t iVen_msg_send_sms_rsp;
    iVen_msg_register_port_req_t iVen_msg_register_port_req;
    iVen_msg_deregister_port_req_t iVen_msg_deregister_port_req;
    iVen_msg_deregister_all_port_req_t iVen_msg_deregister_all_port_req;
    iVen_msg_register_all_sms_msg_req_t         iVen_msg_register_all_sms_msg_req;
    iVen_msg_register_telno_req_t iVen_msg_register_telno_req;
    iVen_msg_deregister_telno_req_t iVen_msg_deregister_telno_req;
    iVen_msg_deregister_all_telno_req_t iVen_msg_deregister_all_telno_req;
    iVen_msg_keep_telno_msg_req_t iVen_msg_keep_telno_msg_req;
    iVen_msg_incoming_msg_ind_t  iVen_msg_incoming_msg_ind;

    iVen_msg_get_received_sms_req_t iVen_msg_get_received_sms_req;
    iVen_msg_get_received_sms_rsp_t iVen_msg_get_received_sms_rsp;

    iVen_msg_open_editor_req_t iVen_msg_open_editor_req;
    iVen_msg_open_editor_rsp_t iVen_msg_open_editor_rsp;

    iVen_msg_register_srv_ready_req_t iVen_msg_register_srv_ready_req;
    iVen_msg_deregister_srv_ready_req_t iVen_msg_deregister_srv_ready_req;
    iVen_msg_srv_ready_ind_t iVen_msg_srv_ready_ind;
    iVen_msg_get_srv_ready_req_t iVen_msg_get_srv_ready_req;
    iVen_msg_get_srv_ready_rsp_t iVen_msg_get_srv_ready_rsp;
    iVen_msg_query_sms_srv_center_req_t iVen_msg_query_sms_srv_center_req;
    iVen_msg_set_sms_srv_center_req_t iVen_msg_set_sms_srv_center_req;
#ifdef __SDK_API_01_SMS_MMS_CC__	
	iVen_msg_get_sim_capacity_req_t iVen_msg_get_sim_capacity_req;
	iVen_msg_get_sim_capacity_rsp_t iVen_msg_get_sim_capacity_rsp;
	iVen_msg_get_phone_max_num_req_t iVen_msg_get_phone_max_num_req;
	iVen_msg_sms_get_num_req_t iVen_msg_sms_get_num_req;
	iVen_msg_sms_get_num_rsp_t iVen_msg_sms_get_num_rsp;
	iVen_msg_sms_get_header_list_req_t iVen_msg_sms_get_header_list_req;
	iVen_msg_sms_get_header_list_rsp_t iVen_msg_sms_get_header_list_rsp;
	iVen_msg_sms_modify_header_req_t iVen_msg_sms_modify_header_req;
	iVen_msg_delete_req_t iVen_msg_delete_req;
	iVen_msg_delete_rsp_t iVen_msg_delete_rsp;	
	iVen_msg_mms_send_req_t iVen_msg_mms_send_req;
	iVen_msg_mms_send_rsp_t iVen_msg_mms_send_rsp;
#endif
	iVen_msg_sms_backup_req_t iVen_msg_sms_backup_req;
	iVen_msg_sms_backup_rsp_t iVen_msg_sms_backup_rsp;
	iVen_msg_sms_restore_req_t iVen_msg_sms_restore_req;
	iVen_msg_sms_restore_rsp_t iVen_msg_sms_restore_rsp;
	iVen_msg_sms_add_req_t iVen_msg_sms_add_req;
	iVen_msg_sms_add_rsp_t iVen_msg_sms_add_rsp;	
    iVen_user_extend_msg_t iVen_user_extend_msg;

    iVen_cam_open_camera_req_t iVen_cam_open_camera_req;
    iVen_cam_open_camera_rsp_t iVen_cam_open_camera_rsp;
    iVen_cam_close_camera_req_t iVen_cam_close_camera_req;
    iVen_cam_close_camera_rsp_t iVen_cam_close_camera_rsp;
    iVen_cam_start_preview_req_t iVen_cam_start_preview_req;
    iVen_cam_start_preview_rsp_t iVen_cam_start_preview_rsp;
    iVen_cam_stop_preview_req_t iVen_cam_stop_preview_req;
    iVen_cam_stop_preview_rsp_t iVen_cam_stop_preview_rsp;
    iVen_cam_capture_image_req_t iVen_cam_capture_image_req;
    iVen_cam_capture_image_rsp_t iVen_cam_capture_image_rsp;
    iVen_cam_convert_image_req_t iVen_cam_convert_image_req;
    iVen_cam_convert_image_rsp_t iVen_cam_convert_image_rsp;
    iVen_cam_launch_app_req_t iVen_cam_launch_app_req;
    iVen_cam_launch_app_rsp_t iVen_cam_launch_app_rsp;
	
    iVen_gps_data_ind_t iVen_gps_data_ind;
	iVen_util_get_cellinfo_req_t iVen_util_get_cellinfo_req;

    iVen_cus_get_ven_data_req_t iVen_cus_get_ven_data_req;
    iVen_cus_get_ven_third_data_req_t iVen_cus_get_ven_third_data_req;
    iVen_cus_get_ven_third_Size_req_t iVen_cus_get_ven_third_Size_req;

    iVen_mm_register_listener_req_t iVen_mm_register_listener_req;
    iVen_mm_register_listener_rsp_t iVen_mm_register_listener_rsp;
    /*
        *   RFID  reltaed response structure
        */
#ifdef __RFID_SDK_SUPPORT__
    iVen_rfid_cmd_rsp_t                         iVen_rfid_cmd_rsp;
    iVen_rfid_listener_rsp_t                    iVen_rfid_listener_rsp;

    //iVen_rfid_cmd_req_t                         iVen_rfid_cmd_req;

    //ema_RfidCmdReq_t  RfidReq;
#endif
#if defined (__G_SENSOR__)
	iVen_sen_gsensor_reg_notify_req_t iVen_sen_gsensor_reg_notify_req;
	iVen_sen_gsensor_reg_notify_ind_t iVen_sen_gsensor_reg_notify_ind;
	iVen_sen_gsensor_reg_notify_rsp_t iVen_sen_gsensor_reg_notify_rsp;
	iVen_sen_gsensor_get_devinfo_req_t iVen_sen_gsensor_get_devinfo_req;
	iVen_sen_gsensor_get_devinfo_rsp_t iVen_sen_gsensor_get_devinfo_rsp;
	iVen_sen_gsensor_reg_motion_listener_req_t iVen_sen_gsensor_reg_motion_listener_req;
	iVen_sen_gsensor_reg_motion_listener_ind_t iVen_sen_gsensor_reg_motion_listener_ind;
	iVen_sen_gsensor_reg_motion_listener_rsp_t iVen_sen_gsensor_reg_motion_listener_rsp;
	iVen_sen_gsensor_get_last_motion_req_t iVen_sen_gsensor_get_last_motion_req;
	iVen_sen_gsensor_get_last_motion_rsp_t iVen_sen_gsensor_get_last_motion_rsp;	
#endif //#if defined (__G_SENSOR__)
	iVen_sen_btapp_send_file_req_t iVen_sen_btapp_send_file_req;
	iVen_sen_btapp_send_file_rsp_t iVen_sen_btapp_send_file_rsp;
#endif //#ifndef __SDK_API_WAP_MMS_ONLY__		
} vm_msgBody_t;





#endif //__VEN_PRIM_MSG_H__
