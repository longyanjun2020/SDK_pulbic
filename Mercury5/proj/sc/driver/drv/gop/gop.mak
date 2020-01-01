#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
          $(PATH_gop)/src\
          $(PATH_gop)/src/rtk\

PATH_H += $(PATH_gop_hal)/inc\
          $(PATH_gop)/inc\
          $(PATH_gop)/pub\
          $(PATH_gop)/pub/rtk\
          $(PATH_gop_hal)/pub\
          $(PATH_lcd)/pub\
          $(PATH_cam_os_wrapper)/pub

SRC_C_LIST = \
    drv_gop.c \
    drv_gop_io.c



#------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
    SRC_C_LIST += gop_test.c
endif

