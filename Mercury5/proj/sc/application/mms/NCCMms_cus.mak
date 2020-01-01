#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C =\
	$(PATH_NCCMms_target)/src_cus

# for core
SRC_C_LIST = \
	mms_network_cus.c \
	mms_fs_system_cus.c

PATH_H +=\
	$(PATH_NCCMms_target)/inc	\
	$(PATH_NCCBrowser_target)/inc \
	$(PATH_i18n)/inc

CFLAGS +=\
	-DHAVE_MEMMOVE	\
	-DNCC_WHTTP	\
	-DNCC_MULTIPART	\
	-DNCC_BROWSER_XML	\
	-DNCC_BROWSER_CACHE	\
	-DNCC_BROWSER_ZLIB	\
	-DNCC_WITH_CONSMS	\
	-DMMS_UTF8_CHARSET	\
	-DMMS_DUAL_SIM_SUPPORT	\
	-DI18N_LATIN1_SUPPORT	\
	-DI18N_UTF8_UTF16_SUPPORT	\
	-DNCC_MMSNET_TIMER_DRIVER	\
	-DUAPP_MMS_WHTTP	\
	-DMEM_USING_TESTING	\
	-DSUPPORT_FONT_MODE_DYNAMIC	\
	-D__FEATURE_VECTOR_FONT__	\
	-DNCC_EXTENDED_FILE_SUPPORT

ifeq ($(filter __WAP_MMI_OTA_PROV__, $(PP_OPT_COMMON)), __WAP_MMI_OTA_PROV__)
CFLAGS +=\
	-DUAPP_PUSH_PROV	\
	-DUSE_OLD_OPENSSL
endif

ifeq ($(COMPILER_VERSION), RVCTV22)
C_OPTIONS += --diag_suppress 1,9,42,47,66,68,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1215,1293,1294,1295,1296,2874
endif
