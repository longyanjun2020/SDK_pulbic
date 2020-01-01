#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib
PATH_C +=\
  $(PATH_gss)/src

ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __GSS_DISABLE_32BITS_FUNCTIONS__
endif

ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __GSS_DISABLE_24BITS_FUNCTIONS__
PP_OPT_COMMON += __GSS_DISABLE_ENHANCE_BLT_FUNCTIONS__
PP_OPT_COMMON += __GSS_DISABLE_PARTIAL_ROP_FUNCTIONS__
PP_OPT_COMMON += __GSS_DISABLE_UNUSED_ROP_OPERATIONS__
PP_OPT_COMMON += __GSS_DISABLE_8BITS_PALETTE_FUNCTIONS__
PP_OPT_COMMON += __REMOVE_USELESS_GRAPHIC_ENGINE__
endif

PATH_H +=  \
$(PATH_gss)/inc\
$(PATH_gss)/itf\
$(PATH_gss)/pub\
$(PATH_dma2d)/pub\
$(PATH_image_codec)/pub\
$(PATH_lcd)/pub\
$(PATH_disp)/pub\
$(PATH_scl)/pub
#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------
#   gss_lcdc_drv.c
#	gss_lcdc_itf.c
#	gss_2dgp_drv.c
#	gss_2dgp_itf.c
#	gss_cisi_drv.c
#	gss_cisi_itf.c
#	gss_jpg_drv.c
#	gss_jpg_itf.c
#	gss_ctrl.c
#	gss_display.c

SRC_C_LIST =\
    abi_headers_gss.c\
    bitblt.c\
    bltpattern.c\
    dispbasicgrap.c\
    dispinit.c\
    displine.c\
    dispsurfmgr.c\
    panelinfohw.c\
    panelinfommp.c\
    panelinfo.c\
    colorkey.c\
    stretchblt.c\
    dispG3D.c\
    disp_ctrl.c\
    mdl_disp_task.c\
    Gss_parse.c
