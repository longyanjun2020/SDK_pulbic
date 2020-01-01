#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq ($(filter __SDK_SIMULATION__ ,$(PP_OPT_COMMON)),)
PP_OPT_COMMON += CAMERA_SLDLM
endif
endif

PATH_C +=\
    $(PATH_isp_mdl)/src \
    $(PATH_isp_mdl)/src/camalgo\
    $(PATH_isp_mdl)/src/common

#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_H += $(PATH_isp_mdl)/inc\
          $(PATH_isp)/inc\
          $(PATH_isp_mdl)/inc/common\
          $(PATH_isp_mdl)/inc/camalgo\
          $(PATH_isp)/pub\
          $(PATH_sensorif)/inc\
          $(PATH_isp_hal)/inc\
          $(PATH_isp)/inc\
		  $(PATH_mfe)/pub\
		  $(PATH_scl)/pub/rtk\
		  $(PATH_scl)/pub\
		  $(PATH_scl_hal)/inc/drv\
          $(PATH_mz)\
          $(PATH_ahc)/inc\
          $(PATH_project_Dvr_CarDV_SDK_UI)/inc\
          $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
          $(PATH_core_application_mmps_fs)/inc\
          $(PATH_core_application_mmpd_fs)/inc\
          $(PATH_core_system_host_if)/inc\
          $(PATH_core_system_os)/inc\
          $(PATH_core_lib_fs)/inc\
          $(PATH_core_lib_gui)/inc\Core\
        
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
PATH_H += \
  $(PATH_lcd)/pub\
  $(PATH_scl_hal)/pub
endif

ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H += $(PATH_tv_mdl)/pub
endif
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), FALSE)
SRC_C_LIST =\
	libcamera.c\
	libcamera_mdl.c\
	libcamera_io.c\
	isp_ut.c\
	iqserver_cmd_handle.c\
	drv_ms_rwcfg.c\
	isp_sys_api.c\
	drv_cam_autowhitebalance.c\
	drv_cam_autoexposure.c\
	ae_utility.c\
	drv_cam_iq.c\
	iq_apiset.c\
	iq_feature.c\
	iq_paraprint.c\
	iq_regset.c\
	iq_shadow.c\
	iq_utility.c\
	isp_file_mgr.c\
	iniparser.c\
	dictionary.c
else    
SRC_C_LIST =
endif


