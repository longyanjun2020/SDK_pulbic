#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
	$(PATH_vpu_hal)/src
  
PATH_H +=\
	$(PATH_hal)\
	$(PATH_vpu_hal)/inc\
	$(PATH_hvd)/inc\
	$(PATH_hvd_hal)/inc\
	$(PATH_utopia_common)/inc\
	$(PATH_utopia_chip)/inc\
	$(PATH_utopia_msos)/inc\
	$(PATH_utopia_vdec)/inc\
	
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
	halVPU.c\
	#halCHIP.c

