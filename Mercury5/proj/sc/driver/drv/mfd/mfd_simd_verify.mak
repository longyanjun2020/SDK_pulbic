
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
  $(PATH_mfd)/mmio_lib \
  $(PATH_mfd)/viddecoder/common \
  $(PATH_mfd)/viddecoder/src/snippet \
  $(PATH_mfd)/viddecoder/src/videc \
  $(PATH_mfd)/viddecoder/src/videc/avcvdec \
  $(PATH_mfd)/viddecoder/src/videc/mp2vdec \
  $(PATH_mfd)/viddecoder/src/videc/mp4vdec \
  $(PATH_mfd)/viddecoder/src/videc/h263dec \
  $(PATH_mfd)/viddecoder/src/videc/flv1dec \
  $(PATH_mfd)/viddecoder/src/videc/shared/idct \
  $(PATH_mfd)/viddecoder/src/videc/shared/framing \
  $(PATH_mfd)/viddecoder/src/videc/shared/filter \
  $(PATH_mfd)/viddecoder/src/videc/lib/gbuf \
  $(PATH_mfd)/viddecoder/src/videc/lib/crco \
  $(PATH_mfd)/viddecoder/src/videc/lib/clock

SRC_C_LIST += \
  drv_mfd_main.c \
  drv_mfd_global_buffer.c \
  drv_mfd_CheckSum.c \
  drv_mfd_videc.c \
  drv_mfd_framing.c \
  drv_mfd_mvc_mmclock.c \
  drv_mfd_bitsbuf.c \
  drv_mfd_mp4vdec.c \
  drv_mfd_m4vHeader.c \
  drv_mfd_m4vMBlock.c \
  drv_mfd_m4vBlock.c \
  drv_mfd_m4vBlock1.c \
  drv_mfd_m4vMC.c \
  drv_mfd_m4vVLD.c \
  drv_mfd_m4vfilter.c \
  drv_mfd_m4vPicture.c \
  drv_mfd_iquant.c \
  drv_mfd_mvdec.c \
  drv_mfd_getbits.c \
  drv_mfd_h263Header.c \
  drv_mfd_h263MBlock.c \
  drv_mfd_h263Block.c \
  drv_mfd_h263Tables.c \
  drv_mfd_copyblkf.c \
  drv_mfd_divx_idct_c.c \
  drv_mfd_flv1Header.c \
  drv_mfd_getpic.c \
  drv_mfd_gethdr.c \
  drv_mfd_mp2vdec.c \
  drv_mfd_getvlc.c \
  drv_mfd_motion.c \
  drv_mfd_recon.c \
  drv_mfd_getblk.c \
  \
  drv_mfd_mbuffer.c \
  drv_mfd_image.c \
  drv_mfd_annexb.c \
  drv_mfd_avcHeader.c \
  drv_mfd_avcHeader1.c \
  drv_mfd_parset.c \
  drv_mfd_uvlc.c \
  drv_mfd_avcdec.c \
  drv_mfd_loopFilter.c \
  drv_mfd_macroblock.c \
  drv_mfd_macroblock1.c \
  drv_mfd_avc_copyblkq.c \
  drv_mfd_avc_copyblke.c \
  drv_mfd_block.c \
  drv_mfd_avc_pred.c \
  drv_mfd_CAVLC_Table.c \
  \
  drv_mfd_test.c \
  drv_mfd_dwl_linux.c \
  drv_mfd_dwl_x170_linux_no_drv.c \
  MMIOApi.c \
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
  drv_mfd_h264hwd_vui.c \
  \
  drv_mfd_aeon-util.c \
  drv_mfd_aeon-simd.c

PATH_H += \
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
  $(PATH_mfd)/mmio_lib \
  $(PATH_mfd)/viddecoder/include \
  $(PATH_mfd)/viddecoder/platshim \
  $(PATH_mfd)/viddecoder/common \
  $(PATH_mfd)/viddecoder/src/snippet \
  $(PATH_mfd)/viddecoder/src/videc \
  $(PATH_mfd)/viddecoder/src/videc/bitstream/h264 \
  $(PATH_mfd)/viddecoder/src/videc/bitstream/mpeg2 \
  $(PATH_mfd)/viddecoder/src/videc/bitstream/mpeg4 \
  $(PATH_mfd)/viddecoder/src/videc/bitstream/h263 \
  $(PATH_mfd)/viddecoder/src/videc/bitstream/flv1 \
  $(PATH_mfd)/viddecoder/src/videc/v64 \
  $(PATH_mfd)/viddecoder/src/videc/v64/avcvdec \
  $(PATH_mfd)/viddecoder/src/videc/mp2vdec \
  $(PATH_mfd)/viddecoder/src/videc/mp4vdec \
  $(PATH_mfd)/viddecoder/src/videc/h263dec \
  $(PATH_mfd)/viddecoder/src/videc/avcvdec \
  $(PATH_mfd)/viddecoder/src/videc/flv1dec \
  $(PATH_mfd)/viddecoder/src/videc/s32/avcvdec \
  $(PATH_mfd)/viddecoder/src/videc/plain \
  $(PATH_mfd)/viddecoder/src/videc/shared/filter \
  $(PATH_mfd)/viddecoder/src/videc/shared/intra_pred \
  $(PATH_mfd)/viddecoder/src/videc/lib/clock \
  $(PATH_mfd)/viddecoder/src/videc/lib/crco \
  $(PATH_mfd)/viddecoder/src/videc/shared/idct \
  $(PATH_mfd)/viddecoder/src/videc/shared/parsing \
  $(PATH_mfd)/viddecoder/src/videc/shared/framing \
  $(PATH_mfd)/viddecoder/src/videc/shared/statistic \
  $(PATH_viddecoder)/../include


PP_OPT_COMMON += \
  _SOC_\
  _M4VD_GBUF_ \
  _HANTRO_M2V_EN_ \
  NOAPP \
  INPUT_FROM_MEMORY \
  _SUPPORT_CIF_ \
  SUPPORT_M2V \
  SUPPORT_M4V \
  SUPPORT_AVC \
  SUPPORT_FLV1 \
  _DIVX_IDCT_ \
  _AEON
