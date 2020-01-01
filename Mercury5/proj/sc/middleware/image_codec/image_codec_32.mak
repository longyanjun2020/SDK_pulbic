#-------------------------------------------------------------------------------
#	Description of some variables owned by the library
#-------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS = lib

PP_OPT_COMMON += IMGCODEC_USE_HW_SCL
PP_OPT_COMMON += IMGCODEC_SMALL_ROM_32

ifneq ($(filter __G1__ ,$(PP_OPT_COMMON)),__G1__)
PP_OPT_COMMON += ICP_SW_PATCH
endif

PATH_H += \
            $(PATH_image_codec)/inc\
            $(PATH_image_codec)/pub\
            $(PATH_gss)/pub\
            $(PATH_scl)/pub\
            $(PATH_jpd)/pub\
            $(PATH_drm_vfs)/pub

PATH_C += \
            $(PATH_image_codec)/src

#-------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#-------------------------------------------------------------------------------

SRC_C_LIST = \
  abi_headers_image_codec.c \
  imgcodec_bmp.c \
  imgcodec_color.c \
  imgcodec_color_func.c \
  imgcodec_gif.c \
  imgcodec_jpdDecoder.c \
  imgcodec_jpdBaiscFun.c \
  imgcodec_jpdHeader.c \
  imgcodec_jpdgDecoder.c \
  imgcodec_jpdgHeader.c \
  imgcodec_jpdghwidct.c \
  imgcodec_jpdgGlobal.c \
  imgcodec_jpg_jdapi.c \
  imgcodec_jpg_jdatasrc.c \
  imgcodec_jpg_jdcoefct.c \
  imgcodec_jpg_jdcolor.c \
  imgcodec_jpg_jddctmgr.c \
  imgcodec_jpg_jdhuff.c \
  imgcodec_jpg_jdinput.c \
  imgcodec_jpg_jdmainct.c \
  imgcodec_jpg_jdmarker.c \
  imgcodec_jpg_jdmaster.c \
  imgcodec_jpg_jdpostct.c \
  imgcodec_jpg_jdsample.c \
  imgcodec_jpg_jerror.c \
  imgcodec_jpg_jidct.c \
  imgcodec_jpg_jmemmgr.c \
  imgcodec_jpg_jmemnobs.c \
  imgcodec_jpg_jutils.c \
  imgcodec_jpg.c \
  imgcodec_jpg2_memmgr.c \
  imgcodec_jpg2.c \
  imgcodec_main.c\
  imgcodec_main_old.c\
  imgcodec_memmgr.c \
  imgcodec_mjpd_hwDecoder.c \
  imgcodec_mjpd_swDecoder.c \
  imgcodec_png.c \
  imgcodec_png_zlib.c \
  imgcodec_pngfunc.c \
  imgcodec_render.c \
  imgcodec_surfmgr.c \
  imgcodec_swscl.c \
  imgcodec_util.c \
  imgcodec_wapbmp.c
