PATH_H = \
    $(PATH_audio)/pub \
    $(PATH_batt)/pub \
    $(PATH_battery)/pub \
    $(PATH_cc)/itf_open \
    $(PATH_clkgen)/pub \
    $(PATH_core)/pub \
    $(PATH_cpu_mdl)/pub \
    $(PATH_cus_app)/inc \
    $(PATH_esl)/pub \
    $(PATH_fc)/pub \
    $(PATH_FileMgr)/pub \
    $(PATH_fms)/itf_open \
    $(PATH_fms)/pub \
    $(PATH_gpd_mdl)/pub \
    $(PATH_grr)/itf_open \
    $(PATH_gss)/pub \
    $(PATH_hal)/kernel/inc \
    $(PATH_i18n)/inc \
    $(PATH_image_codec)/pub \
    $(PATH_io)/pub \
    $(PATH_ip)/itf_open \
    $(PATH_keypad)/pub \
    $(PATH_keypad_mdl)/pub \
    $(PATH_mae)/inc \
    $(PATH_mae)/pub \
    $(PATH_mmicomn)/inc \
    $(PATH_mmmanager)/inc \
    $(PATH_mmmanager)/pub \
    $(PATH_mserv)/inc \
    $(PATH_mserv)/itf \
    $(PATH_MsWrapper)/pub \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_ResMgr)/inc/SocketCore \
    $(PATH_ResMgr)/inc/SocketResMgr \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/pub \
    $(PATH_rtc)/inc \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub\
    $(PATH_sdk)/src \
    $(PATH_sim)/itf \
    $(PATH_sim)/itf_open \
    $(PATH_sys)/pub \
    $(PATH_time)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_ucs2)/pub \
    $(PATH_utility)/inc \
    $(PATH_vfs)/pub \
    $(PATH_vml)/itf \
    $(PATH_wap)/itf \
    $(PATH_widget)/inc \
    $(PATH_widget)/pub \
    $(PATH_middleware)/ball/pub \
    $(PATH_avp)/pub
MMI_PATH_H = 

#
#	Important :	This software is protected	by	Copyright and the	information
#					contained herein is confidential. Distribution,	reproduction
#					as	well as exploitation	and transmission of its	contents	is
#					not allowed	except if expressly permitted. Infringments
#					result in damage claims
#					Copyright Wavecom	S.A. (c)	$JustDate:$
#

# ****************************************************************************
# *  File	 :	$Workfile:$			$Revision:$
# *--------------------------------------------------------------------------*
# *  Scope	 :	  Description of the	librarie	to	generate							  *
# *																								  *
# *  Notes	 :	  to launch	the compilation of the current library,			  *
# *				  type from	output directory :										  *
# *						 make	-r	-f	..//gen.mak	TARGET=<target>					  *
# *																								  *
# *																								  *
# *																								  *
# *  Changes	 :																				  *
# *--------------------------------------------------------------------------*
# *  Version VSS	| Date			  | Author |	Modification					  *
# *--------------------------------------------------------------------------*
# *	$Log:$
#
# ****************************************************************************

#SCE_OPTIONS = -R -G -Cysc.cfg -N
#SCE_OPTIONS = -R -N

#------------------------------------------------------------------------------
#	Description	des variables propre	a la bibliothèque
#	Description	of	some variables	own to the librairie
#------------------------------------------------------------------------------
# Library module (lib) or Binary	module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	Liste	des fichiers sources	de	la	bibliothèque ou de l'éxecutable a générer
#	List of source	files	of	the library	or	executable to generate
#------------------------------------------------------------------------------
ifeq ($(filter __SDK_API__ ,$(PP_OPT_COMMON)),__SDK_API__)
SRC_C_LIST += \
  ven_acc.c\
  ven_cc.c\
  ven_cc_msg_parser.c\
  ven_codec.c\
  ven_codec_msg_parser.c\
  ven_dbg.c\
  ven_drv.c\
  ven_editor.c\
  ven_editor_msg_parser.c\
  ven_file.c\
  ven_file_msg_parser.c\
  ven_fileUtil.c\
  ven_font.c\
  ven_graphics.c\
  ven_graphics_msg_parser.c\
  ven_handle.c\
  ven_helper.c\
  ven_ker.c\
  ven_kpd.c\
  ven_kpd_msg_parser.c\
  ven_msg.c\
  ven_msg_msg_parser.c\
  ven_os.c\
  ven_os_msg_parser.c\
  ven_phb.c\
  ven_phb_msg_parser.c\
  ven_setting.c\
  ven_setting_msg_parser.c\
  ven_stc.c\
  ven_stc_msg_parser.c\
  ven_time.c\
  ven_time_msg_parser.c\
  ven_ts.c\
  ven_ts_msg_parser.c\
  ven_socket.c\
  ven_socket_msg_parser.c\
  ven_clipboard.c\
  ven_user.c\
  ven_user_msg_parser.c\
  ven_uart.c\
  ven_ui.c\
  ven_ui_msg_parser.c\
  ven_util.c\
  ven_integration.c\
  ven_wap_msg_parser.c\
  ven_wap.c\
  ven_cam.c\
  ven_cam_msg_parser.c\
  ven_cus.c\
  ven_gps.c\
  ven_gps_msg_parser.c\
  ven_mm.c\
  ven_mm_msg_parser.c\
  ven_rfid.c\
  ven_rfid_msg_parser.c\
  ven_sensor.c\
  ven_sensor_msg_parser.c\
  ven_wlan.c
endif
#delete original {MMI_}PATH_H

#------------------------------------------------------------------------------
# Add support on RFID   __RFID_SDK_SUPPORT__ define at common_option.mak
#------------------------------------------------------------------------------
#ifeq ($(filter __RFID_SDK_SUPPORT__, $(PP_OPT_COMMON)), __RFID_SDK_SUPPORT__)
#SRC_C_LIST += \
#	ven_rfid.c\
#	ven_rfid_msg_parser.c
#endif

#------------------------------------------------------------------------------
#  source files of SDK V1
#------------------------------------------------------------------------------
SRC_C_LIST += \
  ven_adapt_sdkv1.c

ifeq ($(filter __SDK_DEVICE_CONTROL__ ,$(PP_OPT_COMMON)),__SDK_DEVICE_CONTROL__)
MMI_PATH_H += \
	$(PATH_fcm)/pub \
	$(PATH_hal)/int/inc \
	$(PATH_hal)/int/pub \
	$(PATH_hal)/io/pub \
	$(PATH_hal)/pm/inc \
	$(PATH_hal)/uart/inc \
	$(PATH_mux)/pub \
	$(PATH_pm_mdl)/pub \
	$(PATH_pm)/inc \
	$(PATH_uart)/pub \
	$(PATH_v24)/pub 
endif

ifeq ($(filter __OFN_DRV__ ,$(PP_OPT_COMMON)), __OFN_DRV__)
MMI_PATH_H += \
	$(PATH_middleware)/ofn/pub
endif

#------------------------------------------------------------------------------
#  ABI checker file
#------------------------------------------------------------------------------
SRC_C_LIST += \
  abi_headers_sdk.c
