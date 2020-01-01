ifeq ($(COMPILER_VERSION), RVCTV22)
C_OPTIONS += --diag_suppress 1,494,1295,177,550,68,188,940,167,226,152,186,2874
endif
PROCESS		= lib

ifeq ($(filter __ZMOL__ ,$(PP_OPT_COMMON)),__ZMOL__)
PP_OPT_COMMON += __MMI_ZMOL__
endif

ifeq ($(filter __ZMOL__ ,$(PP_OPT_COMMON)),__ZMOL__)
REL_SRC_C_LIST += zm_gui.c
REL_SRC_C_LIST += zm_appconfig.c
REL_SRC_C_LIST += zm_appmem.c
REL_SRC_C_LIST += zm_btmouse.c
REL_SRC_C_LIST += zm_file.c
REL_SRC_C_LIST += zm_gdi.c
REL_SRC_C_LIST += zm_gui.c
REL_SRC_C_LIST += zm_ipqq_ptr.c
REL_SRC_C_LIST += zm_memory.c
REL_SRC_C_LIST += zm_multimedia.c
REL_SRC_C_LIST += zm_phone.c
REL_SRC_C_LIST += zm_socket.c
REL_SRC_C_LIST += zm_string.c

PATH_H +=\
$(PATH_keypad_mdl)/pub

endif
