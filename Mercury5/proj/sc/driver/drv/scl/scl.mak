#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS   = lib
SCL_CHIP = infinity
#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_C += \
          $(PATH_scl)/src\
          $(PATH_scl)/src/rtk\
          $(PATH_scl)/src/pq\
          $(PATH_scl_hal)/src/drv\
          $(PATH_scl_hal)/src/drv/rtk\
          $(PATH_scl_hal)/src/hal

PATH_H += $(PATH_scl_hal)/inc/hal\
          $(PATH_scl_hal)/inc/drv\
          $(PATH_scl_hal)/inc/rtk\
          $(PATH_scl_hal)/inc/pq\
          $(PATH_scl)/src/pq\
          $(PATH_scl)/inc/pq\
          $(PATH_scl)/inc/rtk\
          $(PATH_scl)/pub\
          $(PATH_scl)/pub/rtk\
          $(PATH_lcd)/pub\
          $(PATH_cam_os_wrapper)/pub\
          $(PATH_cam_os_wrapper)/inc\
          $(PATH_project_Dvr_CarDV_SDK_cfg_pq)/inc
SRC_C_LIST = \
      drv_scl_os.c \
      drv_scl_hvsp_io.c \
      drv_scl_dma_io.c \
      drv_scl_pnl_io.c \
      drv_scl_vip_io.c \
      drv_scl_proc.c \
 	  drv_scl_pq_bin.c \
 	  drv_scl_pq.c


