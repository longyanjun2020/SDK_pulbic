
#
# For DLM mocule makefile path e.g. dlmTest0.mak
#

#
# To store dlm module in normal build ;
# To restore dlm module in release build.
#
PATH_DLM_LIB=$(PATH_dlm)/dlm_lib/


#
# Default
#
PATH_dlmTest0=$(PATH_dlm_kernel)dlmTest0/


#
# DLM_MP3DEC
#
ifeq ($(filter DLM_MP3DEC, $(PP_OPT_COMMON)), DLM_MP3DEC)
PATH_dlm_mp3dec=$(PATH_dlm_kernel)dlm_mp3dec/
endif
#
# DLM_AACDEC
#
ifeq ($(filter DLM_AACDEC, $(PP_OPT_COMMON)), DLM_AACDEC)
PATH_dlm_aacdec=$(PATH_dlm_kernel)dlm_aacdec/
endif
# DLM_AMRNBENNC
#
ifeq ($(filter DLM_AMRNB_CODEC, $(PP_OPT_COMMON)), DLM_AMRNB_CODEC)
PATH_dlm_amrnbenc=$(PATH_dlm_kernel)dlm_amrnbenc/
endif
#
# DRV group
#
PATH_ut_drv_timer_tc0=$(PATH_dlm_kernel)/ut_drv_timer_tc0/
PATH_ut_drv_sandbox_tc0=$(PATH_dlm_kernel)/ut_drv_sandbox_tc0/
PATH_ut_drv_audio_rt0=$(PATH_dlm_kernel)/ut_drv_audio_rt0/
PATH_ut_drv_audio_mt0=$(PATH_dlm_kernel)/ut_drv_audio_mt0/
PATH_ut_drv_clkgen_tc0=$(PATH_dlm_kernel)/ut_drv_clkgen_tc0/

#
# SYS group
#
PATH_DlmUtDynTskSemRecover=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUtDynTskDynSemRecover=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUtDynTskFlagWaiting=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUtDynTskMsgWaiting=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUtDynTskWaitSend=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUtDtTimedWaitSend=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUtDynTskTimer=$(PATH_dlm_kernel)/DlmSysUT/DeleteDynamicTask/
PATH_DlmUTEqualPriority=$(PATH_dlm_kernel)/DlmSysUT/EqualPriority/
PATH_DlmUtTskPrioChange=$(PATH_dlm_kernel)/DlmSysUT/ChangeTskPrio/

#
# MDL group
#
PATH_dlmTest0=$(PATH_dlm_kernel)/dlmTest0/
PATH_ut_template_0=$(PATH_dlm_kernel)/ut_template_0/
PATH_ut_template_1=$(PATH_dlm_kernel)/ut_template_1/
PATH_ut_template_2=$(PATH_dlm_kernel)/ut_template_2/
PATH_ut_mdl_eml_tc0=$(PATH_dlm_kernel)/ut_mdl_eml_tc0/
PATH_ut_mdl_eml_tc1=$(PATH_dlm_kernel)/ut_mdl_eml_tc1/
PATH_ut_mdl_eml_tc2=$(PATH_dlm_kernel)/ut_mdl_eml_tc2/
PATH_ut_mdl_eml_tc3=$(PATH_dlm_kernel)/ut_mdl_eml_tc3/
PATH_ut_mdl_eml_tc4=$(PATH_dlm_kernel)/ut_mdl_eml_tc4/
PATH_ut_mdl_eml_tc5=$(PATH_dlm_kernel)/ut_mdl_eml_tc5/
PATH_ut_mdl_cam_tc0=$(PATH_dlm_kernel)/ut_mdl_cam_tc0/
PATH_ut_mdl_avp_tc0=$(PATH_dlm_kernel)/ut_mdl_avp_tc0/
PATH_ut_mdl_avp_tc1=$(PATH_dlm_kernel)/ut_mdl_avp_tc1/
PATH_ut_mdl_mmaudio_tc0=$(PATH_dlm_kernel)/ut_mdl_mmaudio_tc0/
PATH_ut_mdl_mmaudio_tc2=$(PATH_dlm_kernel)/ut_mdl_mmaudio_tc2/
PATH_ut_mdl_image_codec_tc0=$(PATH_dlm_kernel)/ut_mdl_image_codec_tc0/
PATH_DlmUtFileSystem=$(PATH_dlm_kernel)/DlmUtFileSystem/
PATH_ut_mdl_vdr_tc0=$(PATH_dlm_kernel)/ut_mdl_vdr_tc0/
PATH_ut_mdl_imgcapture_tc0=$(PATH_dlm_kernel)/ut_mdl_imgcapture_tc0/
PATH_ut_mdl_imgcapture_tc1=$(PATH_dlm_kernel)/ut_mdl_imgcapture_tc1/

#
# SRV
#
PATH_DlmUt=$(PATH_dlm_kernel)/DlmUt/
PATH_DlmUtAccIf=$(PATH_dlm_kernel)/DlmUtAccIf/
PATH_DlmUtAccessoryIf=$(PATH_dlm_kernel)/DlmUtAccessoryIf/
PATH_DlmUtAccessoryReq=$(PATH_dlm_kernel)/DlmUtAccessoryReq/
PATH_DlmUtAlarmIf=$(PATH_dlm_kernel)/DlmUtAlarmIf/
PATH_DlmUtAlarmReq=$(PATH_dlm_kernel)/DlmUtAlarmReq/
PATH_DlmUtAtsyncIf=$(PATH_dlm_kernel)/DlmUtAtsyncIf/
PATH_DlmUtAtsyncReq=$(PATH_dlm_kernel)/DlmUtAtsyncReq/
PATH_DlmUtAudioenvReq=$(PATH_dlm_kernel)/DlmUtAudioenvReq/
PATH_DlmUtAudioplayerIf=$(PATH_dlm_kernel)/DlmUtAudioplayerIf/
PATH_DlmUtAudioplayerReq=$(PATH_dlm_kernel)/DlmUtAudioplayerReq/
PATH_DlmUtAudiorecorderIf=$(PATH_dlm_kernel)/DlmUtAudiorecorderIf/
PATH_DlmUtAudiorecorderReq=$(PATH_dlm_kernel)/DlmUtAudiorecorderReq/
PATH_DlmUtBatteryIf=$(PATH_dlm_kernel)/DlmUtBatteryIf/
PATH_DlmUtBatteryReq=$(PATH_dlm_kernel)/DlmUtBatteryReq/
PATH_DlmUtBtIf=$(PATH_dlm_kernel)/DlmUtBtIf/
PATH_DlmUtBtReq=$(PATH_dlm_kernel)/DlmUtBtReq/
PATH_DlmUtBtobexIf=$(PATH_dlm_kernel)/DlmUtBtobexIf/
PATH_DlmUtBtobexReq=$(PATH_dlm_kernel)/DlmUtBtobexReq/
PATH_DlmUtCalllogReq=$(PATH_dlm_kernel)/DlmUtCalllogReq/
PATH_DlmUtCamcoderIf=$(PATH_dlm_kernel)/DlmUtCamcoderIf/
PATH_DlmUtCamcoderReq=$(PATH_dlm_kernel)/DlmUtCamcoderReq/
PATH_DlmUtCameraIf=$(PATH_dlm_kernel)/DlmUtCameraIf/
PATH_DlmUtCameraReq=$(PATH_dlm_kernel)/DlmUtCameraReq/
PATH_DlmUtCapabilityReq=$(PATH_dlm_kernel)/DlmUtCapabilityReq/
PATH_DlmUtCbsIf=$(PATH_dlm_kernel)/DlmUtCbsIf/
PATH_DlmUtCbsReq=$(PATH_dlm_kernel)/DlmUtCbsReq/
PATH_DlmUtCcIf=$(PATH_dlm_kernel)/DlmUtCcIf/
PATH_DlmUtCcReq=$(PATH_dlm_kernel)/DlmUtCcReq/
PATH_DlmUtCfgReq=$(PATH_dlm_kernel)/DlmUtCfgReq/
PATH_DlmUtClientReq=$(PATH_dlm_kernel)/DlmUtClientReq/
PATH_DlmUtClipboardReq=$(PATH_dlm_kernel)/DlmUtClipboardReq/
PATH_DlmUtClockIf=$(PATH_dlm_kernel)/DlmUtClockIf/
PATH_DlmUtClockReq=$(PATH_dlm_kernel)/DlmUtClockReq/
PATH_DlmUtCodecReq=$(PATH_dlm_kernel)/DlmUtCodecReq/
PATH_DlmUtConfigIf=$(PATH_dlm_kernel)/DlmUtConfigIf/
PATH_DlmUtConfigReq=$(PATH_dlm_kernel)/DlmUtConfigReq/
PATH_DlmUtCoreReq=$(PATH_dlm_kernel)/DlmUtCoreReq/
PATH_DlmUtCphsReq=$(PATH_dlm_kernel)/DlmUtCphsReq/
PATH_DlmUtDatamgrReq=$(PATH_dlm_kernel)/DlmUtDatamgrReq/
PATH_DlmUtDbutilityReq=$(PATH_dlm_kernel)/DlmUtDbutilityReq/
PATH_DlmUtEventdbIf=$(PATH_dlm_kernel)/DlmUtEventdbIf/
PATH_DlmUtEventdbReq=$(PATH_dlm_kernel)/DlmUtEventdbReq/
PATH_DlmUtEvtcenterIf=$(PATH_dlm_kernel)/DlmUtEvtcenterIf/
PATH_DlmUtEvtcenterReq=$(PATH_dlm_kernel)/DlmUtEvtcenterReq/
PATH_DlmUtFdnIf=$(PATH_dlm_kernel)/DlmUtFdnIf/
PATH_DlmUtFdnReq=$(PATH_dlm_kernel)/DlmUtFdnReq/
PATH_DlmUtFilemgrReq=$(PATH_dlm_kernel)/DlmUtFilemgrReq/
PATH_DlmUtFmradioReq=$(PATH_dlm_kernel)/DlmUtFmradioReq/
PATH_DlmUtImagemakerReq=$(PATH_dlm_kernel)/DlmUtImagemakerReq/
PATH_DlmUtJavaIf=$(PATH_dlm_kernel)/DlmUtJavaIf/
PATH_DlmUtJavaReq=$(PATH_dlm_kernel)/DlmUtJavaReq/
PATH_DlmUtMciReq=$(PATH_dlm_kernel)/DlmUtMciReq/
PATH_DlmUtMmIf=$(PATH_dlm_kernel)/DlmUtMmIf/
PATH_DlmUtMmsIf=$(PATH_dlm_kernel)/DlmUtMmsIf/
PATH_DlmUtMmsReq=$(PATH_dlm_kernel)/DlmUtMmsReq/
PATH_DlmUtMmstxIf=$(PATH_dlm_kernel)/DlmUtMmstxIf/
PATH_DlmUtMmstxReq=$(PATH_dlm_kernel)/DlmUtMmstxReq/
PATH_DlmUtMobilitymgrIf=$(PATH_dlm_kernel)/DlmUtMobilitymgrIf/
PATH_DlmUtMobilitymgrReq=$(PATH_dlm_kernel)/DlmUtMobilitymgrReq/
PATH_DlmUtMoiIf=$(PATH_dlm_kernel)/DlmUtMoiIf/
PATH_DlmUtMoiReq=$(PATH_dlm_kernel)/DlmUtMoiReq/
PATH_DlmUtMotiondetectorIf=$(PATH_dlm_kernel)/DlmUtMotiondetectorIf/
PATH_DlmUtMotiondetectorReq=$(PATH_dlm_kernel)/DlmUtMotiondetectorReq/
PATH_DlmUtMplayerReq=$(PATH_dlm_kernel)/DlmUtMplayerReq/
PATH_DlmUtMsgmgrIf=$(PATH_dlm_kernel)/DlmUtMsgmgrIf/
PATH_DlmUtMsgmgrReq=$(PATH_dlm_kernel)/DlmUtMsgmgrReq/
PATH_DlmUtEmugameReq=$(PATH_dlm_kernel)/DlmUtEmugameReq/
PATH_DlmUtObjprocessingIf=$(PATH_dlm_kernel)/DlmUtObjprocessingIf/
PATH_DlmUtObjprocessingReq=$(PATH_dlm_kernel)/DlmUtObjprocessingReq/
PATH_DlmUtPhbIf=$(PATH_dlm_kernel)/DlmUtPhbIf/
PATH_DlmUtPhbReq=$(PATH_dlm_kernel)/DlmUtPhbReq/
PATH_DlmUtPlaylistIf=$(PATH_dlm_kernel)/DlmUtPlaylistIf/
PATH_DlmUtPlaylistReq=$(PATH_dlm_kernel)/DlmUtPlaylistReq/
PATH_DlmUtPreviewline2Req=$(PATH_dlm_kernel)/DlmUtPreviewline2Req/
PATH_DlmUtProfileIf=$(PATH_dlm_kernel)/DlmUtProfileIf/
PATH_DlmUtProfileReq=$(PATH_dlm_kernel)/DlmUtProfileReq/
PATH_DlmUtSensormgrIf=$(PATH_dlm_kernel)/DlmUtSensormgrIf/
PATH_DlmUtSensormgrReq=$(PATH_dlm_kernel)/DlmUtSensormgrReq/
PATH_DlmUtShortcutReq=$(PATH_dlm_kernel)/DlmUtShortcutReq/
PATH_DlmUtSimIf=$(PATH_dlm_kernel)/DlmUtSimIf/
PATH_DlmUtSimReq=$(PATH_dlm_kernel)/DlmUtSimReq/
PATH_DlmUtSmsIf=$(PATH_dlm_kernel)/DlmUtSmsIf/
PATH_DlmUtSmsReq=$(PATH_dlm_kernel)/DlmUtSmsReq/
PATH_DlmUtSmstxIf=$(PATH_dlm_kernel)/DlmUtSmstxIf/
PATH_DlmUtSmstxReq=$(PATH_dlm_kernel)/DlmUtSmstxReq/
PATH_DlmUtSsIf=$(PATH_dlm_kernel)/DlmUtSsIf/
PATH_DlmUtSsReq=$(PATH_dlm_kernel)/DlmUtSsReq/
PATH_DlmUtStkIf=$(PATH_dlm_kernel)/DlmUtStkIf/
PATH_DlmUtStkReq=$(PATH_dlm_kernel)/DlmUtStkReq/
PATH_DlmUtSubjectresconflictReq=$(PATH_dlm_kernel)/DlmUtSubjectresconflictReq/
PATH_DlmUtTaskdbReq=$(PATH_dlm_kernel)/DlmUtTaskdbReq/
PATH_DlmUtTaskdbmgrIf=$(PATH_dlm_kernel)/DlmUtTaskdbmgrIf/
PATH_DlmUtTaskdbmgrReq=$(PATH_dlm_kernel)/DlmUtTaskdbmgrReq/
PATH_DlmUtTouchReq=$(PATH_dlm_kernel)/DlmUtTouchReq/
PATH_DlmUtTouchshortcutIf=$(PATH_dlm_kernel)/DlmUtTouchshortcutIf/
PATH_DlmUtTouchshortcutReq=$(PATH_dlm_kernel)/DlmUtTouchshortcutReq/
PATH_DlmUtTvIf=$(PATH_dlm_kernel)/DlmUtTvIf/
PATH_DlmUtTvReq=$(PATH_dlm_kernel)/DlmUtTvReq/
PATH_DlmUtUsbReq=$(PATH_dlm_kernel)/DlmUtUsbReq/
PATH_DlmUtVcalparserReq=$(PATH_dlm_kernel)/DlmUtVcalparserReq/
PATH_DlmUtVcalstoreReq=$(PATH_dlm_kernel)/DlmUtVcalstoreReq/
PATH_DlmUtVendorIf=$(PATH_dlm_kernel)/DlmUtVendorIf/
PATH_DlmUtVendorReq=$(PATH_dlm_kernel)/DlmUtVendorReq/
PATH_DlmUtVideoplayerIf=$(PATH_dlm_kernel)/DlmUtVideoplayerIf/
PATH_DlmUtVideoplayerReq=$(PATH_dlm_kernel)/DlmUtVideoplayerReq/
PATH_DlmUtVoicecallReq=$(PATH_dlm_kernel)/DlmUtVoicecallReq/
PATH_DlmUtWlanIf=$(PATH_dlm_kernel)/DlmUtWlanIf/
PATH_DlmUtWlanReq=$(PATH_dlm_kernel)/DlmUtWlanReq/

#
# DLM_RVCDEC
#
PATH_dlm_rvcdec=$(PATH_dlm_kernel)/dlm_rvcdec/
