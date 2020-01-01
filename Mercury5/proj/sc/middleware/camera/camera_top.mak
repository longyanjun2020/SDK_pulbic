#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_camera_top)/src
#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------
PATH_H += $(PATH_camera_mdl)/inc\
          $(PATH_camera_top)/inc\
          $(PATH_camera_top)/pub\
          $(PATH_sensorif)/pub\
          $(PATH_scl)/pub\
          $(PATH_disp)/pub
          
PATH_H +=\
    $(PATH_dynscl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
      mdl_camera_top.c
