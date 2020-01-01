#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_pm)/src
  
PATH_H +=\
  $(PATH_adc)/pub\
  $(PATH_adc_hal)/pub  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
  drv_pm_ldo.c\
  drv_pmu_irq.c\
  drv_abb.c\
  abi_headers_pm.c
  