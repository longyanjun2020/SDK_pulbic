#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

# generate preprocess file (e.g. A.c --> A.o.pp)
GEN_PREPROCESS = 1


#-------------------------------------------------------------------------------
# if turn on __DIAG_ERROR__, build system would treat warning as error
# this is use to suppress the #66, 186 warning  
#------------------------------------------------------------------------------- 
ifeq ($(COMPILER_VERSION),RVCTV22)
#C_OPTIONS+=--diag_suppress 123 456
endif

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST =\
  init.c\
  cus_app.c

PATH_H += $(PATH_sys)/inc
PATH_H += $(PATH_sys)/itf
PATH_H += $(PATH_sys)/itf_open

PATH_H +=	$(PATH_storage)/pub
PATH_H +=	$(PATH_storage_mdl)/pub
PATH_H += $(PATH_gpd_mdl)/pub
PATH_H += $(PATH_lcd)/pub

PATH_C += $(PATH_sys)/src
PATH_C += $(PATH_sys)/src_cus
PATH_C += $(PATH_cus_app)/src
  