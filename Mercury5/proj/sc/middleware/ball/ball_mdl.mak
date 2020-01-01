#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
    $(PATH_ball_mdl)/src

PATH_H +=\
$(PATH_keypad_mdl)/pub\
$(PATH_ball_hal)/pub\
$(PATH_drv)/ball/pub\
$(PATH_ball_mdl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    mdl_ball.c

PATH_H += $(PATH_ball_mdl)\inc

