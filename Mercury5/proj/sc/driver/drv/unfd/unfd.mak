#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_unfd)/src
    
PATH_H += $(PATH_unfd)/pub    
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
UNFD_DRV_INC +=\
	inc
SRC_C_LIST = \
	     abi_headers_unfd.c  \
	     app_main.c          \
	     drvNAND_ftl.c       \
	     drvNAND_hal.c       \
	     drvNAND_rom.c       \
	     drvNAND_prg.c       \
	     drvNAND_utl.c       \
	     drvNAND_ip_verify.c \
	     drvNAND_platform.c  \
	     drvNAND_bkgnd_task.c

PATH_H += $(addprefix $(PATH_unfd)/, $(UNFD_DRV_INC))

