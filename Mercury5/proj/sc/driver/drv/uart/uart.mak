#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_uart)/src

PATH_H +=\
$(PATH_uart_hal)/inc
    
UART_DRV_INC +=\
  inc

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------


ifneq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST =\
    abi_headers_uart.c\
    drv_uart_api.c\
    drv_ven_uart.c
else
SRC_C_LIST =\
    uart_test_i_sw.c\
    abi_headers_uart.c\
    drv_uart.c\
#    drv_ven_uart.c\

PATH_H +=\
  $(PATH_dma)/pub
endif

ifeq ($(call FIND_COMPILER_OPTION, __BARCODE__), TRUE)
SRC_C_LIST += drv_uart.c
endif

PATH_H += $(addprefix $(PATH_uart)/, $(UART_DRV_INC))

