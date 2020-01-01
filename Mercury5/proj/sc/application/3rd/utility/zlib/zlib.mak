PATH_H = \
    $(PATH_fc)/pub \
    $(PATH_MsWrapper)/pub \
    $(PATH_rtk)/pub \
    $(PATH_sys)/pub \
    $(PATH_timer)/pub \
    $(PATH_trc)/pub \
    $(PATH_zlib)/inc

ifeq ($(filter __HW_ZLIB_SUPPORT__ ,$(PP_OPT_COMMON)),__HW_ZLIB_SUPPORT__)
PATH_H +=\
    $(PATH_zlib_drv)/pub
endif

MMI_PATH_H =
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS		= lib

#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST +=\
	adler32.c\
	compress.c\
	crc32.c\
	deflate.c\
	inffast.c\
	inflate.c\
	inftrees.c\
	trees.c\
	uncompr.c\
	zutil.c \
	zlib_rom_fun_tab.c

#delete original {MMI_}PATH_H

PATH_C =\
	$(PATH_zlib)/src

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
	-DNCC_MMSNET_TIMER_DRIVER	\
	-DUAPP_MMS_WHTTP	\
	-DUAPP_PUSH_PROV	\
	-DMEM_USING_TESTING	\
	-DUSE_OLD_OPENSSL	\
	-DSUPPORT_FONT_MODE_DYNAMIC	\
	-D__FEATURE_VECTOR_FONT__	\
	-DSET_VECTOR_FONT_SIZE_BY_LIB	\
	-DNCC_EXTENDED_FILE_SUPPORT

CFLAGS += -DNOBYFOUR

ifeq ($(COMPILER_VERSION),RVCTV22)
C_OPTIONS += --diag_suppress 1,9,42,47,66,68,111,117,120,144,152,161,167,170,174,175,177,186,188,191,192,223,236,260,513,514,546,550,767,815,940,991,1215,1293,1294,1295,1296,2874
endif
