#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_usbhost)/src\
    $(PATH_usbhost)/pub

PATH_H +=\
  $(PATH_usbhost)/pub\
  $(PATH_usbhost)/src\
  $(PATH_usbhost)/inc\
  $(PATH_usbhost)/inc/include\
  $(PATH_MsWrapper)/pub\
  $(PATH_utopia)/common/inc\
  $(PATH_utopia)/msos/inc\
  $(PATH_usbhost_hal)/inc

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
			drvBulktran.c	\
			drvBus.c	\
			drvConfig.c	\
			drvDriver.c	\
			drvEhciHcd.c	\
			drvEHsTest.c	\
			drvHcdBuf.c	\
			drvHub.c	\
			drvKernel.c	\
			drvMassStor.c	\
			drvMM.c		\
			drvMSC.c	\
			drvMsg.c	\
			drvPCIMEM.c	\
			drvPipe.c	\
			drvTimer.c	\
			drvUSB.c	\
			drvUsbd.c	\
			drvUSBDisk.c	\
			drvUSBEntry.c	\
			drvUSBHwCtl.c	\
			msos_api_wrapper.c	\
