#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_H +=\
  $(PATH_vml)/inc\
  $(PATH_fms)/itf\
  $(PATH_fms)/inc\
  $(PATH_flash)/inc\
  $(PATH_fms)/itf_open\
  $(PATH_vfs)/itf

PATH_C +=\
  $(PATH_fms)/src\
  $(PATH_fms_cus)/src_cus

C_E2P_OBJS = fms_e2p_m18.o fms_atcmd.o

ifeq ($(COMPILER_VERSION),RVCTV22)
$(C_E2P_OBJS:%=$(OUT)%): C_OPTIONS += --diag_suppress 1296,170
endif

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  fms_atcmd.c \
  fms_m18.c \
  fms_rai_src.c \
  fms_e2p_m18.c \
  fms_e2p_itf_wrapper.c \
  fms_core_wrapper.c
