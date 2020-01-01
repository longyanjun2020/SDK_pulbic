# ****************************************************************************
# *  File    : $Workfile:   $       $Revision:  $
# *--------------------------------------------------------------------------*
# *  Scope   :   Description of the library to generate                     *
# *                                                                          *
# *                                                                          *
# ****************************************************************************




#------------------------------------------------------------------------------
#	Description des variables propre ?la bibliothèque
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib
PATH_C +=\
  $(PATH_flash)/src


PATH_H +=\
  $(PATH_emi)/pub\
  $(PATH_flash)/pub\
  $(PATH_bus)/inc\
  $(PATH_flash)/inc\
  $(PATH_flash_hal)/inc\
  $(PATH_kernel_hal)/inc\
  $(PATH_acc_inc)/pub
#------------------------------------------------------------------------------
#	Liste des fichiers sources de la bibliothèque ou de l'éxecutable ?générer
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------
#ifeq ($(call FIND_COMPILER_OPTION, __SUPPORT_BUS_FSP_SPI__), TRUE)
SRC_C_LIST =\
  abi_headers_flash.c\
  drv_flash_lowl_spi.c\
  drv_flash_lowl_comm.c\
  drv_serial_flash.c
#  drvDeviceInfo.c

#endif
