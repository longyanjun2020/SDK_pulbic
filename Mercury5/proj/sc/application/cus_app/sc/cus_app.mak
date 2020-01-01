#------------------------------------------------------------------------------
#   List of source  files   of  the library or  executable to generate
#------------------------------------------------------------------------------
PATH_H +=\
  $(PATH_sys)/inc\
  $(PATH_sys)/itf\
    $(PATH_bluetooth)/pub\
	$(PATH_emi)/pub\
	$(PATH_storage)/pub\
	$(PATH_storage_mdl)/pub\
	$(PATH_usb_mdl)/pub\
	$(PATH_gss)/pub\
	$(PATH_tscr_mdl)/pub\
	$(PATH_image_codec)/pub\
	$(PATH_batt)/pub\
	$(PATH_keypad_mdl)/pub\
	$(PATH_image_capture)/pub\
	$(PATH_drv)/ofn/pub\
	$(PATH_acc_inc)/pub\
	$(PATH_tscr)/pub\
	$(PATH_acc_inc)/pub\
	$(PATH_lcd)/pub\
	$(PATH_gpd_mdl)/pub\
	$(PATH_rtc)/pub

ifneq ($(filter __ENABLE_SLDLM_JAVA_OAKMONT__, $(PP_OPT_COMMON)),)
PATH_H +=\
    $(PATH_system)/dynldr/inc\
    $(PATH_system)/dynldr/pub
endif

ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PATH_H += $(PATH_ofn_mdl)/pub
endif
ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PATH_H += \
		$(PATH_ball_mdl)/pub\
		$(PATH_ball)/pub
endif
SRC_C_LIST =    \
	cus_3rd.c\
	cus_capability.c\
	cus_app.c \
	cus_hotkey.c\
	cus_ps.c\
	cus_trace.c\
	cus_wtest.c \
	task_app.c \
	dev_gss.c    \
	dev_task.c \
	cus_autotest.c \
	sw_ver_cus.c \
	cus_audio_qlog.c \
	cus_backtrace.c

