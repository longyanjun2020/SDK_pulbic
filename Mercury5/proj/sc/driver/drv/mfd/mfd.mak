
#------------------------------------------------------------------------------
#	Description of some variables owned by the library
#------------------------------------------------------------------------------
# Library module (lib) or Binary module (bin)
PROCESS		= lib


#------------------------------------------------------------------------------
#	List of source files of the library or executable to generate
#------------------------------------------------------------------------------

PATH_C += \
  $(PATH_mfd)/src \
  $(PATH_mfd)/hantro_driver \
  $(PATH_mfd)/hantro_driver/source/common \
  $(PATH_mfd)/hantro_driver/source/mpeg2 \
  $(PATH_mfd)/hantro_driver/source/mpeg4 \
  $(PATH_mfd)/hantro_driver/source/h264 \
  $(PATH_mfd)/hantro_driver/source/h264/legacy \
  $(PATH_mfd)/hantro_driver/dwl/dwl \

SRC_C_LIST += \
  \
  drv_mfd_dwl_linux.c \
  drv_mfd_dwl_x170_linux_no_drv.c \
  drv_mfd_regdrv.c \
  drv_mfd_udma_share.c \
  drv_mfd_main_share.c \
  \
  drv_mfd_main_mpeg2.c \
  drv_mfd_mpeg2decapi.c \
  drv_mfd_mpeg2decapi_internal.c \
  drv_mfd_mpeg2hwd_utils.c \
  drv_mfd_mpeg2hwd_strm.c \
  drv_mfd_mpeg2hwd_headers.c \
  \
  drv_mfd_main_mpeg4.c \
  drv_mfd_mp4decapi.c \
  drv_mfd_mp4decapi_internal.c \
  drv_mfd_mp4dechwd_utils.c \
  drv_mfd_mp4dechwd_strmdec.c \
  drv_mfd_mp4dechwd_motiontexture.c \
  drv_mfd_mp4dechwd_videopacket.c \
  drv_mfd_mp4dechwd_error_conceal.c \
  drv_mfd_mp4dechwd_shortvideo.c \
  drv_mfd_mp4dechwd_headers.c \
  drv_mfd_mp4dechwd_vop.c \
  drv_mfd_mp4dechwd_vlc.c \
  drv_mfd_mp4dechwd_rvlc.c \
  \
  drv_mfd_main_h264.c \
  drv_mfd_h264decapi.c \
  drv_mfd_h264hwd_decoder.c \
  drv_mfd_h264hwd_dpb.c \
  drv_mfd_h264hwd_storage.c \
  drv_mfd_h264hwd_asic.c \
  drv_mfd_h264_pp_pipeline.c \
  \
  drv_mfd_h264hwd_pic_order_cnt.c \
  drv_mfd_h264hwd_byte_stream.c \
  drv_mfd_h264hwd_nal_unit.c \
  drv_mfd_h264hwd_slice_header.c \
  drv_mfd_h264hwd_pic_param_set.c \
  drv_mfd_h264hwd_seq_param_set.c \
  drv_mfd_h264hwd_stream.c \
  drv_mfd_h264hwd_vlc.c \
  drv_mfd_h264hwd_util.c \
  drv_mfd_h264hwd_vui.c

PATH_H += \
  $(PATH_mfd)/inc \
  $(PATH_mfd)/hantro_driver \
  $(PATH_mfd)/hantro_driver/source/inc \
  $(PATH_mfd)/hantro_driver/source/config \
  $(PATH_mfd)/hantro_driver/source/common \
  $(PATH_mfd)/hantro_driver/source/mpeg2 \
  $(PATH_mfd)/hantro_driver/source/mpeg4 \
  $(PATH_mfd)/hantro_driver/source/h264 \
  $(PATH_mfd)/hantro_driver/source/h264/legacy \
  $(PATH_mfd)/hantro_driver/dwl/dwl \
  $(PATH_mfd)/hantro_driver/dwl/memalloc \
  $(PATH_mfd)/hantro_driver/dwl/ldriver/kernel_26x \
  $(PATH_mfd)/hantro_driver/dwl/mpeg2 \
  $(PATH_mfd)/hantro_driver/dwl/mpeg4 \
  $(PATH_mfd)/hantro_driver/dwl/h264 \
  $(PATH_mfd_hal)/inc \
  $(PATH_mfd_hal)/src/mmio_lib

PP_OPT_COMMON += \
  _SOC_\
  _M4VD_GBUF_ \
  _HANTRO_M2V_EN_ \
  _SUPPORT_D1_ \
  NDEBUG
