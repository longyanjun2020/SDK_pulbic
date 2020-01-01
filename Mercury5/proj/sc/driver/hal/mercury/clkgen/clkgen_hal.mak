#-------------------------------------------------------------------------------
#   Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_clkgen_hal)/src

PATH_H +=\
  $(PATH_emi)/pub

#-------------------------------------------------------------------------------
#   List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    hal_clkgen.c\
    hal_clkgen_cmu.c\
    hal_clkgen_top.c\
    hal_clkgen_module.c

