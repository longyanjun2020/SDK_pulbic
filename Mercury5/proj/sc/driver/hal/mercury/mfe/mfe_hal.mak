#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_mfe_hal)/src

PATH_H +=\
    $(PATH_mfe_hal)/inc\
    $(PATH_mhve)/pub\
    $(PATH_cam_os_wrapper)/pub\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_include_application)\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    hal_mfe_ios.c\
    hal_h264_enc.c\
    hal_mfe_ops.c\
    hal_mfe_arqc.c\
    hal_mfe_pmbr.c\
