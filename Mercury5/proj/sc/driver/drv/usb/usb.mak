#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_usb)/src

PATH_H +=\
  $(PATH_usb)/inc\
  $(PATH_core_system_usb_dev_vendor)/inc\
  
#  $(PATH_usb_hal)/inc   
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
			drv_usb_function.c	\
			drv_usb_drc.c	\
			drv_usb_handler.c	\
			drv_usb_otg.c	\
			drv_usb_cpu.c	\
			drv_usb_dma.c	\
#			drvUSBDwld.c \
#			ms_dma.c	\
#			ms_drc.c	\
#			ms_function.c	\
#			ms_msd_global.c	\
#			ms_otg.c	\
#			ms_usb.c	\
#			msd_fn_scsi.c	\
#			msd_fn_xfer.c	\



