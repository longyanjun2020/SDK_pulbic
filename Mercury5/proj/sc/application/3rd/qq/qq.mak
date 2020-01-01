#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C = \
    $(PATH_qq)/src

REL_SRC_C_LIST = \
    qq_app.c \
    qq_trans_mgr.c

PATH_H += \
    $(PATH_srv)/pub \
    $(PATH_qq)/inc \
    $(PATH_qq)/inc/priv \
    $(PATH_qq)/itf \
    $(PATH_mserv)/inc

