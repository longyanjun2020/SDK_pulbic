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


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C =\
	$(PATH_NCCMms_target)/src

# for core
SRC_C_LIST = \
	charset_gb2utf8.c	\
	common_pushcode.c	\
	cps_common.c	\
	cps_createsmil.c	\
	cps_edit.c	\
	cps_public.c	\
	manager.c	\
	manager_adapter.c	\
	mms_fs_manager.c	\
	mms_fs_system.c	\
	mms_network.c	\
	nccport_mms_config.c	\
	nccport_mms_fs.c	\
	nccport_mms_net.c	\
	nccport_mms_string.c	\
	nccport_push.c	\
	par_input.c	\
	par_parse.c	\
	par_slideview.c	\
	prot_coder.c	\
	prot_encapsulation.c

#delete original {MMI_}PATH_H

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
