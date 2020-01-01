#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
          $(PATH_sensorif)/src\
          $(PATH_sensordriver)/src
          
          
PATH_H +=\
$(PATH_sensordriver)/inc\
$(PATH_sensorif)/pub\
$(PATH_sensorif)/inc\
$(PATH_isp_mdl)/inc\
$(PATH_isp_hal)/inc\
$(PATH_isp)/inc\
$(PATH_isp)/pub\
$(PATH_cam_os_wrapper)/pub \


SRC_C_LIST = \
  drv_SensorIF.c\
  SensorIF_test.c\


#------------------------------------------------------------
# List of source files of verification to generate
#------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += SensorIF_test.c

PATH_H +=\
  $(PATH_camera_mdl)/pub\
  $(PATH_scl_hal)/pub\
  $(PATH_disp)/pub
endif

