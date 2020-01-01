PATH_H = \
    $(PATH_fc)/pub \
    $(PATH_i18n)/inc \
    $(PATH_mserv)/inc \
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

PATH_C =\
	$(PATH_NCCBrowser_target)/src \
	$(PATH_NCCMms_target)/src

# for core
SRC_C_LIST = \
	common_array.c	\
	common_blockmmrg.c	\
	common_bmpconv.c	\
	common_code.c	\
	common_dataparse.c	\
	common_encode.c	\
	common_liburl.c	\
	common_list.c	\
	common_malloc.c	\
	common_memory.c	\
	common_stack.c	\
	common_vector.c	\
	consms.c	\
	nccport_file.c	\
	nccport_os.c	\
	nccport_prov.c	\
	nccport_time.c	\
	nccport_wsp_netporting.c	\
	nccsms_push.c	\
	prov_check.c	\
	prov_file.c	\
	prov_manager.c	\
	prov_parser.c	\
	prov_wbxml.c	\
	prov_writeback.c	\
	prov_xml.c	\
	wsp_code.c	\
	wsp_codingtable.c	\
	wsp_header.c

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
	-DMEM_TESTING_IN_EMMI \
	-DSUPPORT_FONT_MODE_DYNAMIC	\
	-D__FEATURE_VECTOR_FONT__	\
	-DNCC_EXTENDED_FILE_SUPPORT

ifeq ($(filter __WAP_MMI_OTA_PROV__, $(PP_OPT_COMMON)), __WAP_MMI_OTA_PROV__)
CFLAGS +=\
	-DUAPP_PUSH_PROV
endif

ifeq ($(COMPILER_VERSION), RVCTV22)
C_OPTIONS += --diag_suppress 1,9,42,47,66,68,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1215,1293,1294,1295,1296,2874
endif
