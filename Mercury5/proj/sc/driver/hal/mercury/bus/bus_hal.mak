#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_bus_hal)/src

PATH_H +=\
$(PATH_dma)/pub\
$(PATH_bus)/inc\
$(PATH_bus)/pub\
$(PATH_timer_hal)/pub\
$(PATH_gdma_hal)/inc\
$(PATH_flash)/inc
#$(PATH_MsWrapper)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
	hal_bus_qspi.c \
	hal_bus_i2c.c \
	hal_bus_i2c_adpt.c \
	hal_bus_axi.c\
	hal_bus_mspi.c

	#hal_bus_fsp_spi.c \
	#hal_bus_spi_adpt.c \
	#hal_bus_qspi. \
	#hal_bus_fs_spi.c \
	#hal_bus_paging_spi.c \
	#hal_bus_i2s.c \
	#hal_bus_master_spi.c \
