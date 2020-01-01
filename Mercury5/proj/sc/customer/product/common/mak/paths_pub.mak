


#-------------------------------------------------------------------------------
#
# scope: Specify public path   e.g. PATH_H += $(PATH_system)/pub
#
# WARNING: Do not add any private path e.g. inc/src/opec/itf... to this file
# WARNING: Do not add any private path e.g. inc/src/opec/itf... to this file
# WARNING: Do not add any private path e.g. inc/src/opec/itf... to this file
# WARNING: Do not add any private path e.g. inc/src/opec/itf... to this file
# WARNING: Do not add any private path e.g. inc/src/opec/itf... to this file
#
# WARNING: The following path should be placed to dedicated file !!!
#
#          e.g.  PATH_C += $(PATH_sys)/src
#					--> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/inc
#					--> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g. path is telecom folder
#                   --> it is telecom path, please add to 'paths_tel.mak'
#
#-------------------------------------------------------------------------------








#-------------------------------------------------------------------------------
# public path for application
#-------------------------------------------------------------------------------
PUBLIC_PATH_H += $(PATH_srv)/pub
PUBLIC_PATH_H += $(PATH_hopper)/pub
PUBLIC_PATH_H += $(PATH_application)sys/file_mgr/pub
PUBLIC_PATH_H += $(PATH_ResMgr)/pub
PUBLIC_PATH_H += $(PATH_mae)/pub
PUBLIC_PATH_H += $(PATH_core)/pub
PUBLIC_PATH_H += $(PATH_cn)/pub
PUBLIC_PATH_H += $(PATH_core)/pub
PUBLIC_PATH_H += $(PATH_esl)/pub
PUBLIC_PATH_H += $(PATH_core)/pub
PUBLIC_PATH_H += $(PATH_ema)/main/pub

# for I SW
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
	PUBLIC_PATH_H += $(PATH_fat)/pub
endif



# for MMI PATH
MMI_PATH_H += $(PATH_mae)/pub
MMI_PATH_H += $(PATH_core)/pub
#MMI_PATH\_H += $(PATH_lcd)/pub

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
	MMI_PATH_H += $(PATH_mgl)/pub
endif







#-------------------------------------------------------------------------------
# public path for system
#-------------------------------------------------------------------------------
PUBLIC_PATH_H += $(PATH_sys)/pub
PUBLIC_PATH_H += $(PATH_dynldr)/pub
PUBLIC_PATH_H += $(PATH_fc)/pub
PUBLIC_PATH_H += $(PATH_fcm)/pub
PUBLIC_PATH_H += $(PATH_rtk)/pub
PUBLIC_PATH_H += $(PATH_arm)/pub
PUBLIC_PATH_H += $(PATH_v24)/pub
PUBLIC_PATH_H += $(PATH_mux)/pub
PUBLIC_PATH_H += $(PATH_trc)/pub
PUBLIC_PATH_H += $(PATH_ucs2)/pub
PUBLIC_PATH_H += $(PATH_time)/pub
PUBLIC_PATH_H += $(PATH_bsp_837)/pub
PUBLIC_PATH_H += $(PATH_bsp_8f4)/pub
PUBLIC_PATH_H += $(PATH_bsp_833)/pub
PUBLIC_PATH_H += $(PATH_bsp_737)/pub
PUBLIC_PATH_H += $(PATH_bsp_838)/pub
PUBLIC_PATH_H += $(PATH_bsp_c3c)/pub
PUBLIC_PATH_H += $(PATH_bsp_mn)/pub
PUBLIC_PATH_H += $(PATH_MsWrapper)/pub

ifeq ($(filter __MSW8830N__, $(PP_OPT_COMMON)), __MSW8830N__)
	PUBLIC_PATH_H += $(PATH_r2)/pub
endif

# asm include file
PUBLIC_PATH_I += $(PATH_sys)/pub
PUBLIC_PATH_I += $(PATH_rtk)/pub

ifeq ($(filter __MSW8830N__, $(PP_OPT_COMMON)), __MSW8830N__)
	PUBLIC_PATH_I += $(PATH_r2)/pub
endif

# for I SW
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
	PUBLIC_PATH_H += $(PATH_bsp)/pub
endif


#-------------------------------------------------------------------------------
# public path for drv/hal
#-------------------------------------------------------------------------------
PUBLIC_PATH_H += $(PATH_bus)/pub
PUBLIC_PATH_H += $(PATH_int)/pub
PUBLIC_PATH_H += $(PATH_sensorif)/pub
PUBLIC_PATH_H += $(PATH_flash)/pub
PUBLIC_PATH_H += $(PATH_io)/pub
PUBLIC_PATH_H += $(PATH_clkgen)/pub
PUBLIC_PATH_H += $(PATH_timer)/pub
PUBLIC_PATH_H += $(PATH_timer_hal)/pub
PUBLIC_PATH_H += $(PATH_keypad)/pub
PUBLIC_PATH_H += $(PATH_power)/pub
PUBLIC_PATH_H += $(PATH_battery)/pub
PUBLIC_PATH_H += $(PATH_pm)/pub
PUBLIC_PATH_H += $(PATH_uart)/pub
PUBLIC_PATH_H += $(PATH_sensordriver)/pub
PUBLIC_PATH_H += $(PATH_rtc)/pub
PUBLIC_PATH_H += $(PATH_glue)/pub

PUBLIC_PATH_H += $(PATH_io_hal)/pub
PUBLIC_PATH_H += $(PATH_int_hal)/pub

ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)
	#G
	PUBLIC_PATH_H += $(PATH_etmi)/pub
	PUBLIC_PATH_H += $(PATH_mfd)/pub
	PUBLIC_PATH_H += $(PATH_hwconfig)/pub
	PUBLIC_PATH_H += $(PATH_hwconfig_hal)/pub
	PUBLIC_PATH_H += $(PATH_bsp_c0f)/pub
endif # ifeq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)

PUBLIC_PATH_H += $(PATH_wlan_drv)/pub
PUBLIC_PATH_H += $(PATH_wlan_hal)/pub


#-------------------------------------------------------------------------------
# public path for middleware
#-------------------------------------------------------------------------------
PUBLIC_PATH_H += $(PATH_fms)/pub
PUBLIC_PATH_H += $(PATH_vfs)/pub
PUBLIC_PATH_H += $(PATH_mmaudio_codec)/pub
PUBLIC_PATH_H += $(PATH_efat)/pub
PUBLIC_PATH_H += $(PATH_cpu_mdl)/pub
PUBLIC_PATH_H += $(PATH_audio_mdl)/pub
PUBLIC_PATH_H += $(PATH_mmmanager)/pub
PUBLIC_PATH_H += $(PATH_mmmanager_lib)/pub
PUBLIC_PATH_H += $(PATH_mtmgr)/pub
PUBLIC_PATH_H += $(PATH_pm_mdl)/pub
PUBLIC_PATH_H += $(PATH_stereo_video)/pub
PUBLIC_PATH_H += $(PATH_stereo_image)/pub
PUBLIC_PATH_H += $(PATH_wlan)/pub

#-------------------------------------------------------------------------------
# public path for telserv
#-------------------------------------------------------------------------------
PUBLIC_PATH_H += $(PATH_ril)/pub



ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
	PUBLIC_PATH_H += $(PATH_vt_mm)/pub
	PUBLIC_PATH_H += $(PATH_vt_task)/pub
endif


ifneq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)
else
#G
	PUBLIC_PATH_H += $(PATH_middleware)venc/pub
endif # ifneq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)






#-------------------------------------------------------------------------------
# public path for others
#-------------------------------------------------------------------------------
#PUBLIC_PATH_H +=




















#-------------------------------------------------------------------------------
# DO NOT MODUFY FOLLOWING RULE
#-------------------------------------------------------------------------------
PATH_H += $(PUBLIC_PATH_H) $(PATH_build)/$(PRODUCT)
PATH_I += $(PUBLIC_PATH_I)


