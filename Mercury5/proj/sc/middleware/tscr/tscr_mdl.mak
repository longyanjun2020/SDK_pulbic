#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PATH_C +=\
    $(PATH_tscr_mdl)/src

PATH_H +=\
$(PATH_tscr_mdl)/pub\
$(PATH_tscr_mdl)/inc\
$(PATH_gss)/pub\
$(PATH_keypad_mdl)/pub\
$(PATH_tscr)/pub\
$(PATH_acc_inc)/pub\
$(PATH_adc)/pub\
$(PATH_lcd)/pub


#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
SRC_C_LIST =\
    abi_headers_tscr_mdl.c\
    mdl_touch_screen.c\
    mdl_touch_screen_handler.c