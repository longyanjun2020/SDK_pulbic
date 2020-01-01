#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_bus)/src

PATH_H +=\
  $(PATH_bus)/pub\
  $(PATH_emi)/pub/\
  $(PATH_dma)/pub/\
  $(PATH_acc_inc)/pub/\
  $(PATH_flash)/inc/\
  $(PATH_mz)/\
  $(PATH_bdma)/inc\
  $(PATH_bdma)/pub\
  $(PATH_hal)bdma\inc\
  $(PATH_spinand)/inc\
  $(PATH_spinand_hal)/inc\
  $(PATH_bus_hal)/inc\
  $(PATH_project_Dvr_CarDV_SDK_cfg_sdk)/inc\
  $(PATH_project_Dvr_CarDV_SDK_cfg_core)/inc
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_bus.c \
    drv_bus_spi.c \
    drv_bus_mspi.c \
    drv_bus_i2c.c \
    i2c_test.c \
    drv_bus_axi.c

#    spi_test.c \
#-------------------------------------------------------------------------------
#	List of source files of verification to generate
#-------------------------------------------------------------------------------
ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
PATH_H += $(PATH_system)/rtk/itf_open\
  $(PATH_storage)/pub

SRC_C_LIST += serialflash_test.c \
              spinand_test.c
endif

