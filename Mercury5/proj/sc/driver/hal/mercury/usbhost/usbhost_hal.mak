#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_usbhost_hal)/src

PATH_H +=\
  $(PATH_usbhost_hal)/inc
#  $(PATH_usb_hal)/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
			hal_usbhost.c \
