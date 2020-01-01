#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_H += \
  $(PATH_fcm)/inc

# path to C source files in "opxc" directories
PATH_C +=\
 $(PATH_fcm)/src\
 $(PATH_fcm)/opxc

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  opec_fcm.c
  
ifneq ($(filter __NO_GPRS__ ,$(PP_OPT_COMMON)),__NO_GPRS__)
SRC_C_LIST +=\
  abi_headers_fcm.c\
  fcm_main.c\
  fcm_fal.c\
  fcm_trc.c
endif
  
  
