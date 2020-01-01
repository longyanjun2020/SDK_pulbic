#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C = \
    $(PATH_tudou)/src

REL_SRC_C_LIST = \
    com_data_factory.c \
    com_json_core.c \
    com_json_parser.c
    
PATH_H += \
    $(PATH_TuDouApp)/inc \
    $(PATH_SoHuUpdaterApp)/inc/util \
    $(PATH_widget)/pub \
    $(PATH_model)/pub \
    $(PATH_SrvWrapper)/pub \
    $(PATH_mmicomn)/cfg \
    $(PATH_build) \
    $(PATH_CusDefine)/pub \
    $(PATH_bluetooth)/pub \
    $(PATH_image_codec)/pub \
    $(PATH_AppLauncher)/inc \
    $(PATH_mmicomn)/inc \
    $(PATH_gss)/pub
    
