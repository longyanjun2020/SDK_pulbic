PATH_H = \
    $(PATH_dynldr)/pub \
    $(PATH_fc)/pub \
    $(PATH_i18n)/inc \
    $(PATH_mserv)/inc \
    $(PATH_NCCBrowser_target)/inc \
    $(PATH_NCCEmail_target)/inc \
    $(PATH_NCCMms_target)/inc \
    $(PATH_clkgen)/pub \
    $(PATH_timer)/pub \
    $(PATH_rtc)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sdk)/inc \
	$(PATH_sdk)/pub \
    $(PATH_sys)/pub \
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
	$(PATH_NCCEmail_target)/src

# for core
SRC_C_LIST = \
	email_smtp.c	\
	email_fs.c	\
	nccport_email_fs.c	\
	email_pop3.c	\
	email_prot.c

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
	-DI18N_GB2312_SUPPORT	\
	-DI18N_GBK_SUPPORT	\
	-DI18N_BIG5_SUPPORT	\
	-DI18N_LATIN1_SUPPORT	\
	-DI18N_UTF8_UTF16_SUPPORT	\
	-DNCC_MMSNET_TIMER_DRIVER	\
	-DNCC_WSP	\
	-DUAPP_MMS_WHTTP	\
	-DUAPP_PUSH_PROV_NO	\
	-DMEM_USING_TESTING	\
	-DSUPPORT_FONT_MODE_DYNAMIC	\
	-D__FEATURE_VECTOR_FONT__	\
	-DNCC_EXTENDED_FILE_SUPPORT

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
CFLAGS += \
	-DNCCEMAIL_SUPPORT_SSL
endif
endif

