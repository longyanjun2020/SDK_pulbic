
/* Primitives send FROM Vendor SDK */
#define VEN_OUT_PRIM_ITEMS \
    MAKE_PRIM_ITEM(I_VEN_STC_START_RSP,                     NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_SUSPEND_RSP,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_RESUME_RSP,                    NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_STOP_RSP,                      NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_BACKGROUND_RSP,                NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_FOREGROUND_RSP,                NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_NOTIFY_STOP,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_NOTIFY_START,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_NOTIFY_FOREGROUND,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_STC_NOTIFY_BACKGROUND,             NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_FILE_STR_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_SET_URL_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_VOLUME_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_VIBRATION_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_KEYPAD_TONE_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_NETWORK_PROFILE_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_NETWORK_PROFILE_EX_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_SET_NETWORK_PROFILE_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_SET_NETWORK_PROFILE_EX_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_SELECT_SIM_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_DEFAULT_SIM_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_SIM_ICCID_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_LANGUAGE_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_NETWORK_PROFILE_NUM_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_NETWORK_PROFILE_BY_IDX_REQ,    NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_DATA_ACCOUNT_NUM_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_DATA_ACCOUNT_BY_IDX_REQ,    NULL), \
	MAKE_PRIM_ITEM(I_VEN_SETTING_QUERY_AIRPLANE_MODE_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_SIM_STATUS_REQ,        NULL), \
	MAKE_PRIM_ITEM(I_VEN_SETTING_GET_DEFAULT_CAM_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_OPEN_MEDIA_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_CLOSE_MEDIA_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_PLAYING_TIME_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_AUDIO_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_AUDIO_RAW_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_MIDI_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PAUSE_AUDIO_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_RESUME_AUDIO_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STOP_AUDIO_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_SET_VOLUME_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_VOLUME_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_START_AUDIO_STREAM_RECORD_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STOP_AUDIO_STREAM_RECORD_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_IS_AUDIO_STREAMING_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_CHECK_DRMRIGHTS_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_CONSUME_DRMRIGHTS_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_VIDEO_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_VIDEOSTREAM_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STOP_VIDEOSTREAM_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_VIDEOSTREAMINGINFO_REQ,  NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_VIDEOSTREAM_FILECHANGE_REQ,  NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_ONOFF_VIDEOSEEK_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STREAM_DOWNLOAD_NOTIFY_REQ,  NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_AVP_DLITF_VIDEOSTREAM_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_OPEN_IMAGE_CODEC_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_CLOSE_IMAGE_CODEC_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_DECODE_IMAGE_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_NEXT_IMAGE_FRAME_REQ,    NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_FILE_BROWSE_REQ,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_FILE_BROWSE_EX_REQ,                NULL), \
    MAKE_PRIM_ITEM(I_VEN_FILE_SELECT_FOLDER_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_FILE_GET_AVAIL_PATH_REQ,         	NULL), \
    MAKE_PRIM_ITEM(I_VEN_FILE_SYNC_FOLDER_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_FILE_FILE_ACCESS_IND,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_BROWSE_REQ,                    NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_SAVE_CONTACT_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_WRITE_CONTACT_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_DELETE_CONTACT_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_SAVE_CONTACT_BY_HANDLE_REQ,    NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_FIND_FIRST_REQ,                NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_FIND_NEXT_REQ,                 NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_GET_MEM_STATUS_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_NUMBER_FUZZY_SEARCH_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_GET_CHECKVALUE_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_QUERY_READY_REQ,            	NULL), \
    MAKE_PRIM_ITEM(I_VEN_PHB_REGISTER_READY_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_EDITOR_EDIT_REQ,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_EDITOR_CLOSE_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_EDITOR_DATETIMEEDIT_REQ,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_MAKE_CALL_REQ,                  NULL), \
	MAKE_PRIM_ITEM(I_VEN_CC_MAKE_CALL_GET_CALL_ID_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_RELEASE_CALL_REQ,                NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_GET_CALL_STATUS_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_REGISTER_INCOMING_CALL_REQ,     NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_REGISTER_ADD_CALL_LOG_REQ,     	NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_SEND_DTMF_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_ABORT_DTMF_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_CC_ENABLE_DL_VOICE_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SEND_SMS_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SEND_SMS_EX_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_REGISTER_PORT_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_DEREGISTER_PORT_REQ,           NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_REGISTER_ALL_SMS_MSG_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_DEREGISTER_ALL_PORT_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_REGISTER_TELNO_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_DEREGISTER_TELNO_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_DEREGISTER_ALL_TELNO_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_KEEP_TELNO_MSG_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_GET_RECEIVED_SMS_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_OPEN_EDITOR_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_REGISTER_SRV_READY_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_DEREGISTER_SRV_READY_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_GET_SRV_READY_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_QUERY_SMS_SRV_CENTER_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SET_SMS_SRV_CENTER_REQ,      NULL), \
	MAKE_PRIM_ITEM(I_VEN_MSG_GET_SIM_CAPACITY_REQ, 			NULL), \
	MAKE_PRIM_ITEM(I_VEN_MSG_GET_PHONE_MAX_NUM_REQ, 		NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SMS_GET_NUM_REQ,      			NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SMS_GET_HEADER_LIST_REQ, 		NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SMS_MODIFY_HEADER_REQ, 		NULL), \
    MAKE_PRIM_ITEM(I_VEN_MSG_DELETE_REQ, 					NULL), \
	MAKE_PRIM_ITEM(I_VEN_MSG_MMS_SEND_REQ, 					NULL), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_BACKUP_REQ, 				NULL), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_RESTORE_REQ, 				NULL), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_ADD_REQ, 					NULL), \
    \
	MAKE_PRIM_ITEM(I_VEN_MM_REGISTER_LISTENER_REQ,          NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_TIME_SET_TIME_REQ,                 NULL), \
    MAKE_PRIM_ITEM(I_VEN_TIME_SET_TIME_ZONE_REQ,            NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_CAM_LAUNCH_APP_REQ,                NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTBYNAME_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATESOCKET_REQ,           NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSESOCKET_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CONNECT_REQ,                NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SEND_REQ,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SENDTO_REQ,                 NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REGRECVCB_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REGRECVFROMCB_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECEIVE_READY_IND,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECV_REQ,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECVFROM_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATE_DATALINK_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATE_DATALINK_EX_REQ,     NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_DATALINK_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_DATALINK_EX_REQ,      NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_ALL_DATALINKS_EX_REQ, NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REG_STATUS_CB_REQ,          NULL), \
	MAKE_PRIM_ITEM(I_VEN_SOCKET_DEREG_STATUS_CB_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_REG_STATUS_CB_EX_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_DEREG_STATUS_CB_EX_REQ,     NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SETSOCKOPT_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETSOCKOPT_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SHUTDOWN_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_HTONL_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_HTONS_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_INET_ADDR_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_INET_NTOA_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_INET_ATON_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_NTOHL_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_NTOHS_REQ,                  NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTBYADDR_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTNAME_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETSERVBYPORT_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETSERVBYNAME_REQ,          NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETPROTOBYNUMBER_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETPROTOBYNAME_REQ,         NULL), \
	MAKE_PRIM_ITEM(I_VEN_SOCKET_QUERY_DATALINK_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_BIND_REQ,                   NULL), \
	MAKE_PRIM_ITEM(I_VEN_SOCKET_PING_REQ,                   NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_WLAN_GET_CUR_CONNECTED_DEVICE_INFO_REQ,  NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_CLIPBOARD_GET_SETTING_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_CLIPBOARD_COPY_TEXT_REQ,           NULL), \
    MAKE_PRIM_ITEM(I_VEN_CLIPBOARD_GET_COPY_TEXT_REQ,       NULL), \
    MAKE_PRIM_ITEM(I_VEN_CLIPBOARD_HAS_COPY_TEXT_REQ,       NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_SET_SBVIS_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_GET_SBVIS_REQ,            NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_SET_SKVIS_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_GET_SKVIS_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_SET_DISPLAY_MODE_REQ, 	NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_UI_SHOW_COMPONENT_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_CLOSE_COMPONENT_REQ,            NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_SET_INTERRUPT_LEVEL_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_STATUSBAR_DRAW_ICON_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_STATUSBAR_DRAW_IMAGE_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_SET_BACKLIGHT_BEHAVIOR_REQ,     NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_SET_BACKLIGHT_REQ,     			NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_GET_BACKLIGHT_INFO_REQ,         NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_ENABLE_LAUNCH_KEYGUARD_REQ,     NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_UPDATE_COMPONENT_REQ,           NULL), \
    MAKE_PRIM_ITEM(I_VEN_UI_GET_APPLET_STATUS_REQ,            NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_KPD_SUBSCRIBE_REQ,                 NULL), \
    MAKE_PRIM_ITEM(I_VEN_KPD_RESET_BACKLIGHT_REQ,           NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_WAP_OPEN_BROWSER_CONFIG_REQ,       NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_CAM_OPEN_CAMERA_REQ,               NULL), \
    MAKE_PRIM_ITEM(I_VEN_CAM_CLOSE_CAMERA_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CAM_START_PREVIEW_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_CAM_STOP_PREVIEW_REQ,              NULL), \
    MAKE_PRIM_ITEM(I_VEN_CAM_CAPTURE_IMAGE_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_CAM_CONVERT_IMAGE_REQ,             NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_CUS_GET_VEN_DATA_REQ,              NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_CUS_GET_VEN_THIRD_DATA_REQ,        NULL), \
    MAKE_PRIM_ITEM(I_VEN_CUS_GET_VEN_THIRD_SIZE_REQ,        NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_USER_EXTEND_OUT_MSG,               NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_QUERY_NETWORKSTAUTS_REQ,        NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_GET_IMSI_REQ,        				NULL), \
    MAKE_PRIM_ITEM(I_VEN_UTIL_GET_CELLINFO_REQ,             NULL), \
    MAKE_PRIM_ITEM(I_VEN_GET_USBINFO_REQ,                   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_REG_NOTIFY_REQ,     	NULL), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_GET_DEVINFO_REQ,     	NULL), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_REG_MOTION_LISTENER_REQ,   NULL), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_GET_LAST_MOTION_REQ,     	NULL), \
    MAKE_PRIM_ITEM(I_VEN_SEN_BTAPP_SEND_FILE_REQ,     	NULL), \
    \


#ifdef __RFID_SDK_SUPPORT__
#define RFID_CMD_RSP_ITEM MAKE_PRIM_ITEM(I_VEN_RFID_CMD_RSP,                      ven_rfid_cmd_rsp),
#define RFID_LISTENER_RSP_ITEM     MAKE_PRIM_ITEM(I_VEN_RFID_LISTENER_RSP,                      ven_rfid_listener_rsp),
#else
#define RFID_CMD_RSP_ITEM
#define RFID_LISTENER_RSP_ITEM
#endif



/* Primitives send TO Vendor SDK */
#define VEN_IN_PRIM_ITEMS \
    MAKE_PRIM_ITEM(I_VEN_STC_START_REQ,                     ven_stc_handle_start_req), \
    MAKE_PRIM_ITEM(I_VEN_STC_SUSPEND_REQ,                   ven_stc_handle_suspend_req), \
    MAKE_PRIM_ITEM(I_VEN_STC_RESUME_REQ,                    ven_stc_handle_resume_req), \
    MAKE_PRIM_ITEM(I_VEN_STC_STOP_REQ,                      ven_stc_handle_stop_req), \
    MAKE_PRIM_ITEM(I_VEN_STC_BACKGROUND_REQ,                ven_stc_handle_background_req), \
    MAKE_PRIM_ITEM(I_VEN_STC_FOREGROUND_REQ,                ven_stc_handle_foreground_req), \
    MAKE_PRIM_ITEM(I_VEN_STC_BACKGROUND_CNF,                ven_stc_handle_status_change_cnf), \
    MAKE_PRIM_ITEM(I_VEN_STC_FOREGROUND_CNF,                ven_stc_handle_status_change_cnf), \
    MAKE_PRIM_ITEM(I_VEN_STC_START_CNF,                     ven_stc_handle_start_cnf), \
    \
    MAKE_PRIM_ITEM(I_VEN_OS_MESSAGE_REQ,                    ven_os_msg_ind), \
    \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_FILE_STR_RSP,          ven_setting_getFileStr_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_SET_URL_RSP,               ven_setting_setURL_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_VOLUME_RSP,            ven_setting_getVolume_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_VIBRATION_RSP,         ven_setting_getVibration_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_KEYPAD_TONE_RSP,       ven_setting_getKeypadTone_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_NETWORK_PROFILE_RSP,   ven_setting_getNetworkProfile_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_NETWORK_PROFILE_EX_RSP,   ven_setting_getNetworkProfile_ex_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_SET_NETWORK_PROFILE_RSP,   ven_setting_setNetworkProfile_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_SELECT_SIM_RSP,        ven_setting_getSelectSIM_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_DEFAULT_SIM_RSP,       ven_setting_getDefaultSIM_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_LANGUAGE_RSP,          ven_setting_getCurrentLanguage_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SETTING_GET_SIM_STATUS_RSP,        ven_setting_getSIMStatus_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_CODEC_OPEN_MEDIA_RSP ,             ven_codec_openMedia_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_CLOSE_MEDIA_RSP ,            ven_codec_closeMedia_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_FILE_INFO_RSP,           ven_codec_getFileInfo_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_VDO_EXT_INFO_RSP,           ven_codec_getVdoExtInfo_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_PLAYING_TIME_RSP,        ven_codec_getPlayingTime_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_RESOURCE_STATE_IND,        ven_codec_Resource_State_ind), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_AUDIO_RSP,              ven_codec_playAudio_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_AUDIO_RAW_RSP,          ven_codec_playAudioRaw_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_MIDI_RSP,               ven_codec_playMidi_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PAUSE_AUDIO_RSP,             ven_codec_pauseAudio_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_RESUME_AUDIO_RSP,            ven_codec_resumeAudio_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STOP_AUDIO_RSP,              ven_codec_stopAudio_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_SETPOS_AUDIO_RSP,            ven_codec_setAudioPos_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_SET_VOLUME_RSP,              ven_codec_setAudioVolume_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_VOLUME_RSP,              ven_codec_getAudioVolume_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_START_AUDIO_STREAM_RECORD_RSP,      ven_codec_startAudioStreamRecord_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STOP_AUDIO_STREAM_RECORD_RSP,       ven_codec_stopAudioStreamRecord_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_IS_AUDIO_STREAMING_RSP, ven_codec_isAudioStreaming_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_VIDEO_RSP,              ven_codec_playVideo_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_VIDEO_IND,              ven_codec_playVideo_ind), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_PLAY_AUDIO_STREAMING_RSP,    ven_codec_playAudioStreaming_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_OPEN_IMAGE_CODEC_RSP,        ven_codec_openImageCodec_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_VIDEOSTREAMING_INFO_RSP, ven_codec_getVideoStreamInfo_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_VIDEOSTREAMING_FILECHANGE_RSP, ven_codec_VideoStream_FileChange_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_VIDEOSTREAMING_DLITF_RSP,     ven_codec_VideoStream_DLItf_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_CLOSE_IMAGE_CODEC_RSP,       ven_codec_closeImageCodec_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_DECODE_IMAGE_RSP,            ven_codec_decodeImage_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_ENCODE_IMAGE_RSP,            ven_codec_encodeImage_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_GET_NEXT_IMAGE_FRAME_RSP,    ven_codec_getNextImageFrame_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_START_RECORD_RSP,    ven_codec_startAudioRecord_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CODEC_STOP_RECORD_RSP,    ven_codec_stopAudioRecord_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_FILE_BROWSE_RSP,                   ven_file_browse_rsp), \
    MAKE_PRIM_ITEM(I_VEN_FILE_SELECT_FOLDER_RSP,            ven_file_select_folder_rsp), \
    MAKE_PRIM_ITEM(I_VEN_FILE_SYNC_FOLDER_RSP,              ven_file_sync_folder_rsp), \
    MAKE_PRIM_ITEM(I_VEN_FILE_ASYNC_OPERATION_RSP,          ven_file_async_operation_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_BROWSE_RSP,                    ven_phb_browse_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_ADD_CONTACT_RSP,              	ven_phb_addContact_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_WRITE_CONTACT_RSP,             ven_phb_writeContact_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_DELETE_CONTACT_RSP,            ven_phb_deleteContact_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_SAVE_CONTACT_BY_HANDLE_RSP,    ven_phb_saveContactByHandle_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_FIND_FIRST_RSP,                ven_phb_findFirst_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_FIND_NEXT_RSP,                 ven_phb_findNext_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_GET_MEM_STATUS_RSP,            ven_phb_getMemStatus_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_NUMBER_FUZZY_SEARCH_RSP,       ven_phb_NumberFuzzySearch_rsp), \
    MAKE_PRIM_ITEM(I_VEN_PHB_REGISTER_READY_IND,       		ven_phb_register_ready_ind), \
    MAKE_PRIM_ITEM(I_VEN_EDITOR_EDIT_RSP,                   ven_editor_edit_rsp), \
    MAKE_PRIM_ITEM(I_VEN_EDITOR_DATETIME_RSP,                   ven_editor_datetime_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CC_MAKE_CALL_RSP,                  ven_cc_make_call_rsp), \
	MAKE_PRIM_ITEM(I_VEN_CC_MAKE_CALL_GET_CALL_ID_RSP,      ven_cc_make_call_get_call_id_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CC_CALL_STATUS_RSP,                ven_cc_get_call_status_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CC_REGISTER_INCOMING_CALL_IND,     ven_cc_register_incoming_call_ind), \
    MAKE_PRIM_ITEM(I_VEN_CC_REGISTER_CALL_LOG_IND,     		ven_cc_register_call_log_ind), \
    MAKE_PRIM_ITEM(I_VEN_CC_SEND_DTMF_RSP,                  ven_cc_send_DTMF_rsp), \
    MAKE_PRIM_ITEM(I_VEN_MSG_SEND_SMS_RSP,                  ven_msg_send_sms_rsp), \
    MAKE_PRIM_ITEM(I_VEN_MSG_INCOMING_MSG_IND,              ven_msg_incoming_msg_ind), \
    MAKE_PRIM_ITEM(I_VEN_MSG_GET_RECEIVED_SMS_RSP,          ven_msg_get_received_sms_rsp), \
    MAKE_PRIM_ITEM(I_VEN_MSG_OPEN_EDITOR_RSP,               ven_msg_open_editor_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SRV_READY_IND,                 ven_msg_srv_ready_ind), \
	MAKE_PRIM_ITEM(I_VEN_MSG_GET_SRV_READY_RSP,             ven_msg_get_srv_ready_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_GET_SIM_CAPACITY_RSP,        	ven_msg_get_sim_capacity_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_GET_NUM_RSP,        		ven_msg_sms_get_num_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_GET_HEADER_LIST_RSP,       ven_msg_sms_get_header_list_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_MMS_SEND_RSP,       			ven_msg_mms_send_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_DELETE_RSP,       				ven_msg_delete_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_BACKUP_RSP,       			ven_msg_sms_backup_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_RESTORE_RSP,       		ven_msg_sms_restore_rsp), \
	MAKE_PRIM_ITEM(I_VEN_MSG_SMS_ADD_RSP,       			ven_msg_sms_add_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_TIME_SET_TIME_RSP,                 ven_time_setTime_rsp), \
    MAKE_PRIM_ITEM(I_VEN_TIME_SET_TIME_ZONE_RSP,            ven_time_setTimeZone_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_TS_INPUT_IND,                      ven_ts_input_ind), \
    \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_GETHOSTBYNAME_RSP,          ven_socket_gethostbyname_rsp), \
	MAKE_PRIM_ITEM(I_VEN_SOCKET_PING_RSP,                   ven_socket_ping_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSESOCKET_RSP,            ven_socket_closesocket_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CONNECT_RSP,                ven_socket_connect_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SEND_RSP,                   ven_socket_send_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_SENDTO_RSP,                 ven_socket_sendto_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECV_NOTIFY,                ven_socket_recv_notify), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_RECVFROM_NOTIFY,            ven_socket_recvfrom_notify), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATE_DATALINK_RSP,        ven_socket_create_datalink_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CREATE_DATALINK_EX_RSP,     ven_socket_create_datalink_ex_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_DATALINK_RSP,         ven_socket_close_datalink_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_DATALINK_EX_RSP,      ven_socket_close_datalink_ex_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_CLOSE_ALL_DATALINKS_EX_RSP, ven_socket_close_all_datalinks_ex_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_STATUS_INDICATION,          ven_socket_status_indication), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_STATUS_INDICATION_EX,       ven_socket_status_indication_ex), \
    MAKE_PRIM_ITEM(I_VEN_SOCKET_DEQUE_REQ,                  NULL), \
    \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_SET_SBVIS_RSP,            ven_graphics_set_sbvis_rsp), \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_GET_SBVIS_RSP,            ven_graphics_get_sbvis_rsp), \
    MAKE_PRIM_ITEM(I_VEN_GRAPHICS_SET_DISPLAY_MODE_RSP,     ven_graphics_set_display_mode_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_UI_SHOW_COMPONENT_RSP,             ven_ui_show_rsp), \
    MAKE_PRIM_ITEM(I_VEN_UI_SET_INTERRUPT_LEVEL_RSP,        ven_ui_set_interrupt_level_rsp), \
    MAKE_PRIM_ITEM(I_VEN_UI_SET_BACKLIGHT_BEHAVIOR_RSP,     ven_ui_set_backlight_behavior_rsp), \
    MAKE_PRIM_ITEM(I_VEN_UI_BACKLIGHT_IND,                  ven_ui_backlight_ind), \
    MAKE_PRIM_ITEM(I_VEN_UI_GET_APPLET_STATUS_RSP,          ven_ui_get_applet_status_rsp), \
    MAKE_PRIM_ITEM(I_VEN_UI_GET_BACKLIGHT_INFO_RSP,         ven_ui_get_backlight_info_rsp), \
    MAKE_PRIM_ITEM(I_VEN_UI_ENABLE_LAUNCH_KEYGUARD_RSP,     ven_ui_enable_launch_keyguard_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_DRV_ACS_IND,                       ven_drv_acs_ind), \
    MAKE_PRIM_ITEM(I_VEN_DRV_USB_IND,                       ven_drv_usb_ind), \
    MAKE_PRIM_ITEM(I_VEN_DRV_BACKLIGHT_IND,                 ven_drv_backlight_ind), \
    \
    MAKE_PRIM_ITEM(I_VEN_WAP_OPEN_BROWSER_RSP,              ven_wap_open_browser_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_CAM_OPEN_CAMERA_RSP,               ven_cam_open_camera_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CAM_CLOSE_CAMERA_RSP,              ven_cam_close_camera_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CAM_START_PREVIEW_RSP,             ven_cam_start_preview_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CAM_STOP_PREVIEW_RSP,              ven_cam_stop_preview_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CAM_CAPTURE_IMAGE_RSP,             ven_cam_capture_image_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CAM_CONVERT_IMAGE_RSP,             ven_cam_convert_image_rsp), \
    MAKE_PRIM_ITEM(I_VEN_CAM_LAUNCH_APP_RSP,       			ven_cam_launch_app_rsp), \
    \
    MAKE_PRIM_ITEM(I_VEN_GPS_DATA_IND,                      ven_gps_data_ind), \
    \
    MAKE_PRIM_ITEM(I_VEN_MM_REGISTER_LISTENER_RSP,          ven_mm_register_listener_rsp), \
    RFID_CMD_RSP_ITEM\
    RFID_LISTENER_RSP_ITEM\
    \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_REG_NOTIFY_IND,     	ven_sen_gsensor_reg_notify_ind), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_REG_NOTIFY_RSP,     	ven_sen_gsensor_reg_notify_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_GET_DEVINFO_RSP,     	ven_sen_gsensor_get_devinfo_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_REG_MOTION_LISTENER_IND,   ven_sen_gsensor_reg_motion_listener_ind), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_REG_MOTION_LISTENER_RSP,   ven_sen_gsensor_reg_motion_listener_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SEN_GSENSOR_GET_LAST_MOTION_RSP,     	ven_sen_gsensor_get_last_motion_rsp), \
    MAKE_PRIM_ITEM(I_VEN_SEN_BTAPP_SEND_FILE_RSP,     		ven_sen_btapp_send_file_rsp), \
    \


