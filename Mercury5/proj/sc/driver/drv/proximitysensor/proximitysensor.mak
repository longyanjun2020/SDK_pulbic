#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PROXIMITYSENSOR_DRV_INC +=\
  inc

PATH_C +=\
    $(PATH_proximitysensor)/src

PATH_H +=\
$(PATH_proximitysensor)/pub\
$(PATH_storage_mdl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  drv_proximity_sensor.c \
  abi_headers_proximitysensor.c
#  drv_proximity_sensor_isl29011.c \
#  drv_proximity_sensor_aux.c \
#  drv_proximity_sensor_al3006.c

PATH_H += $(addprefix $(PATH_proximitysensor)/, $(PROXIMITYSENSOR_DRV_INC))
PATH_H += $(PATH_proximitysensor_hal)/inc
PATH_H += $(PATH_cust_drv)/proximitysensor/inc