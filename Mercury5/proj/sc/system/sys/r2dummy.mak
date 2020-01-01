#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib


#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
			  sys_c_start.c

PATH_I +=\
		 $(PATH_sc)/driver/hal/msw8830x/kernel/inc\
		 $(PATH_sc)/system/rtk/inc\
		 $(PATH_sc)/system/rtk/pub

E2P_LIST_FOR_W_E2P_STACK =\
