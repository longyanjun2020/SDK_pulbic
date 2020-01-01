#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_ms_sdmmc)\
    $(PATH_ms_sdmmc)/src
    
PATH_H +=\
	$(PATH_sys)/pub\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_ms_sdmmc)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_kernel_hal)/inc\
	$(PATH_flash)/pub\
	$(PATH_fc)/pub\
	$(PATH_cam_os_wrapper)/pub\
	$(PATH_core_system_os)/inc\
	$(PATH_core_system_host_if)/inc
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    hal_card_timer.c\
    hal_card_regs.c\
    hal_card_intr_v5.c\
    hal_sdmmc_v5.c\
    hal_card_platform_MV5.c\
    ms_sdmmc_host.c\
    ms_sdmmc_verify.c

