ifeq (RVCTV22,$(COMPILER_VERSION))
C_OPTIONS += --diag_suppress 1,494,1295,223,167,177,940,188,68,111,144,1293,2874,550,236,767
endif
# Library module (lib) or Binary	module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source	files	of	the library	or	executable to generate
#------------------------------------------------------------------------------
# Add zhangyue source file here

#QVGA
ifeq ($(filter __LCM_QVGA__, $(PP_OPT_COMMON)), __LCM_QVGA__)
PP_OPT_COMMON += __MMI_MAINLCD_240X320__
endif
ifeq ($(filter __LCM_LANDSCAPE_QVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_QVGA__)
PP_OPT_COMMON += __MMI_MAINLCD_320X240__
endif


#WQVGA
ifeq ($(filter __LCM_LANDSCAPE_WQVGA_240_400__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_WQVGA_240_400__)
PP_OPT_COMMON += __MMI_MAINLCD_240X400__
endif
ifeq ($(filter __LCM_WQVGA_240_400__, $(PP_OPT_COMMON)), __LCM_WQVGA_240_400__)
PP_OPT_COMMON += __MMI_MAINLCD_240X320__
endif

#HVGA
ifeq ($(filter __LCM_HVGA_320_480__, $(PP_OPT_COMMON)), __LCM_HVGA_320_480__)
PP_OPT_COMMON += __MMI_MAINLCD_320X480__
endif
ifeq ($(filter __LCM_LANDSCAPE_HVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_HVGA__)
PP_OPT_COMMON += __MMI_MAINLCD_480X320__
endif

REL_SRC_C_LIST +=\
	pbk_entry.c \
	pbk_launcher.c\
	pbk_gui.c\
	pbk_file.c\
	pbk_log.c\
	pbk_media.c\
	pbk_memory.c\
	pbk_sms.c\
	pbk_socket.c\
	pbk_string.c\
	pbk_sys.c\
	pbk_fileUtil.c\
	pbk_os_res.c
