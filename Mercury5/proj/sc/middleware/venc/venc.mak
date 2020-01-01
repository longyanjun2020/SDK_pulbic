

#------------------------------------------------------------------------------
# Description of some variables owned by the library
#------------------------------------------------------------------------------

# Library module (lib) or Binary module (bin)
PROCESS = lib

PP_OPT_COMMON += NDEBUG
PP_OPT_COMMON += IOCTL_TEST
PP_OPT_COMMON += _R2_DMA_
PP_OPT_COMMON += _USE_SIMD_
PP_OPT_COMMON += _HAS_QMEM_
PP_OPT_COMMON += AEONDEV

#PP_OPT_COMMON += USE_SWHW_PIPELINE
#PP_OPT_COMMON += VENC_CACHE
#PP_OPT_COMMON += USE_CMODEL
#PP_OPT_COMMON += OUTPUT_CRC
#PP_OPT_COMMON += __VER_VENC__

#   PATH_H += $(PATH_middleware)../driver/drv/jpd/inc \
#             $(PATH_middleware)../driver/drv/jpe/inc


#------------------------------------------------------------------------------
# List of source files of the library or executable to generate
#------------------------------------------------------------------------------

SRC_C_LIST = \
            abi_headers_venc.c \
            swvenc_aeon-util.c \
            swvenc_udma_share.c \
            swvenc_CheckSum.c \
            swvenc_divx_idct.c \
            swvenc_idct_z0a.c \
            swvenc_mstar_fdctaa.c \
            swvenc_mstar_jpd_idct.c \
            swvenc_h263_frm.c \
            swvenc_h263_mode_sel.c \
            swvenc_h263_vlc.c \
            swvenc_h263_vlc_tab.c \
            swvenc_h263_dat.c \
            swvenc_h263_ioctl.c \
            swvenc_h263_tab.c \
            swvenc_h263venc.c \
            swvenc_h263_mc.c \
            swvenc_h263_dsp1.c \
            swvenc_h263_dsp.c \
            swvenc_h263_me_ejo.c \
            swvenc_h263_me_mgr.c \
            swvenc_h263_me_mvfast.c \
            swvenc_h263_me_sub.c \
            swvenc_h263_outstrm.c \
            swvenc_h263_quant.c \
            swvenc_h263_rc.c \
            swvenc_IntraUpdate.c

PATH_venc_inc = $(PATH_venc)/inc

PATH_H += \
   $(PATH_venc_inc) \
   $(PATH_venc_inc)/dct \
   $(PATH_venc_inc)/h263v \
   $(PATH_venc_inc)/mc \
   $(PATH_venc_inc)/me \
   $(PATH_venc_inc)/outbits \
   $(PATH_venc_inc)/quant \
   $(PATH_venc_inc)/rc \
   $(PATH_venc_inc)/common \
   $(PATH_venc_inc)/crco \
   $(PATH_venc_inc)/flow \

ifeq ($(filter __VER_VENC__ ,$(PP_OPT_COMMON)),__VER_VENC__)
#PP_OPT_COMMON += __SWVENC_UT_ENABLE__
SRC_C_LIST += h263_ioctl_test.c
#SRC_C_LIST += venc_test.c
endif

ifeq ($(filter _USE_SIMD_ ,$(PP_OPT_COMMON)),_USE_SIMD_)
PP_OPT_COMMON += _AG_V64_
ifeq ($(filter _HAS_QMEM_ ,$(PP_OPT_COMMON)),_HAS_QMEM_)
PP_OPT_COMMON += USE_QMEM
PP_OPT_COMMON += HAS_QMEM
else
endif
else
ifeq ($(filter _HAS_QMEM_ ,$(PP_OPT_COMMON)),_HAS_QMEM_)
$(error QMEM need SIMD open)
endif
endif


