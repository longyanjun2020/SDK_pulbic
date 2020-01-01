#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_rfid_mdl)/src

PATH_H +=\
	$(PATH_MsWrapper)/inc \
	$(PATH_esl)/pub \
	$(PATH_rfid)/inc\
	$(PATH_rfid_mdl)/pub

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
REL_SRC_C_LIST =\
	abi_headers_rfid_mdl.c\
	mdl_rfid.c
