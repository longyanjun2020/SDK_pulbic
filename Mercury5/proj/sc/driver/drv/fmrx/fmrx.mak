#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_fmrx)/src

PATH_H +=\
$(PATH_fmrx)/pub\
$(PATH_gss)/pub\
$(PATH_gsensor)/pub\
$(PATH_fmrx_hal)/inc\
$(PATH_audio_drv)/pub\
$(PATH_scl)/pub

ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H += $(PATH_middleware)/tv/pub
endif


#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  abi_headers_fmrx.c \
  drv_fmrx.c \
  fmrx_parse.c \
  fmrx_i2c.c \
  dev_nxp5760.c \
  dev_rda5800.c \
  dev_rda5802.c \
  dev_silab4702.c

ifeq ($(BB_CHIP_ID),msw8535x)
  SRC_C_LIST += drv_fmrx_stub.c
else
  SRC_C_LIST += drv_fmrx_mstar.c
endif


#-------------------------------------------------------------------------------
#	List of source files of verification to generate
#-------------------------------------------------------------------------------
ifeq ($(BB_CHIP_ID),msw8535x)
else
  ifeq ($(call FIND_COMPILER_OPTION, __I_SW__), TRUE)
SRC_C_LIST += fmrx_test.c
endif
endif

