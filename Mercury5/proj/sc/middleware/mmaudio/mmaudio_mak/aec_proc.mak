#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PP_OPT_COMMON += AECPROC

# paths to C source files in "src" directories
PATH_C +=\
$(PATH_mmaudio)/aecproc/src\
$(PATH_mmaudio)/mstar_drc/src

# path to C header files in "inc" directories
PATH_H +=\
$(PATH_mmaudio)/aecproc/src\
$(PATH_mmaudio)/aecproc/inc\
$(PATH_mmaudio)/mstar_drc/inc




#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST +=\
  audioaec_api.c\
  audioaec_stpmaec.c\
  audiofir_api.c\
  audiodrc_api.c\
  math_op.c\
  basicop2.c\
  log2.c\
  oper_32b.c\
  count.c\
  sqrt_l.c\
  audioaec_echosuppr.c
