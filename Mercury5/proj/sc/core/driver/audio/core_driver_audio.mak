#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_core_driver_audio)/src\

PATH_H +=\
    $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc\
    $(PATH_core_include_application)\
    $(PATH_core_include_img_pipe)\
    $(PATH_core_driver_common)/inc\
    $(PATH_core_driver_bsp)/inc\
    $(PATH_core_driver_audio)/inc\
    $(PATH_core_driver_img_pipe)/inc\

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mmpf_i2s_ctl.c\

