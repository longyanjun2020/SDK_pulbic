#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_otg)/src

PATH_H +=\
	$(PATH_MsWrapper)/pub\
  $(PATH_otg)/inc
  
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
			phy-ms-usb.c



