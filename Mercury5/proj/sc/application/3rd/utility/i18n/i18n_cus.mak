PATH_H = \
    $(PATH_fc)/pub \
    $(PATH_i18n)/inc \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_sdk)/inc \
    $(PATH_sdk)/pub \
    $(PATH_trc)/pub

MMI_PATH_H = 
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#GEN_PREPROCESS = 1



#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST +=\
	nccport_i18n_cus.c

#delete original {MMI_}PATH_H
   
PATH_C =\
	$(PATH_i18n)/src_cus

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
	-DUAPP_PUSH_PROV	\
	-DMEM_USING_TESTING	\
	-DSUPPORT_FONT_MODE_DYNAMIC	\
	-D__FEATURE_VECTOR_FONT__	\
	-DSET_VECTOR_FONT_SIZE_BY_LIB	\
	-DNCC_EXTENDED_FILE_SUPPORT

ifeq ($(filter __BIG5_TO_UNICODE__, $(PP_OPT_COMMON)), __BIG5_TO_UNICODE__)
CFLAGS += \
	-DI18N_BIG5_SUPPORT	
endif

ifeq ($(filter __GB2312_TO_UNICODE__, $(PP_OPT_COMMON)), __GB2312_TO_UNICODE__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
CFLAGS += \
	-DI18N_GBK_TO_UNICODE_SUPPORT
else
CFLAGS += \
	-DI18N_GB2312_TO_UNICODE_SUPPORT
endif
endif

ifeq ($(filter __UNICODE_TO_GB2312__, $(PP_OPT_COMMON)), __UNICODE_TO_GB2312__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
CFLAGS += \
	-DI18N_UNICODE_TO_GBK_SUPPORT
else
CFLAGS += \
	-DI18N_UNICODE_TO_GB2312_SUPPORT
endif
endif

ifeq ($(COMPILER_VERSION),RVCTV22)
C_OPTIONS += --diag_suppress 1,9,42,47,66,68,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1215,1293,1294,1295,1296,2874
endif
