#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib

#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
    $(PATH_core_application_mmph)/src\

PATH_H += \
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_system_algorithm)/inc\
    $(PATH_core_system_host_if)/inc\
    $(PATH_core_system_os)/inc\
    $(PATH_MsWrapper)/pub\
    $(PATH_core_application_mmph)/inc\

SRC_C_LIST = \
    mmph_hif.c\
