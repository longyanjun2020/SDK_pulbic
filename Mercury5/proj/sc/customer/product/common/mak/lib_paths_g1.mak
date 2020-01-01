


#-------------------------------------------------------------------------------
#
# scope: Specify which module should be link!
#
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
# WARNING: Do not add any path definition and path to this file
#
# WARNING: The following path should be placed to dedicated file !!!
#
#          e.g.  PATH_sys = $(PATH_system)/sys
#					--> please add to 'paths.mak'
#
#          e.g.  PATH_C += $(PATH_sys)/src
#					--> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/inc
#					--> it is private path, please add to '$(moduel).mak' e.g. sys.mak
#
#          e.g.  PATH_H += $(PATH_sys)/pub
#					--> it is public path, please add to 'paths_pub.mak'
#
#          e.g. path is telecom folder
#                   --> it is telecom path, please add to 'paths_tel.mak'
#
#-------------------------------------------------------------------------------







# Specify all libraries which should not be compiled from source code
# in PRODUCT_LIB, and note that:
# 1. Library name specified here should not appear in PRODUCT_SC again.
# 2. Don't specify any library name which was not originally specified in
#    PRODUCT_SC. For example, "mmi", "camera" shall not be specified in
#    PRODUCT_LIB.
#
PRODUCT_LIB = \
                csn1\
                fcm\
                obex\
                v24\
                v24_cus\
		            hwl\
		            hwl_prod

PRODUCT_LIB += \
                cust_sys\
                mmplayer \
                viddecoder \
                demuxer \
                mmp_common \
                mp4demux
#= DUO section =================================================================
# -- Modification for project DUO
# JY: Place the name of module you want to duplicate here. An additional library
#     will be produced with all exported symbols renamed (by post-fix "_2")
#
# Alex: Add sim module to duplicate for B2/B3.
PRODUCT_LIB_STACK2 =        \

PRODUCT_LIB_STACK2_MERGE =     \
#                stack_2

#===============================================================================

PRODUCT_SC += \
				boot\
                r2\
                cus_app\
                cus_app_lib\
                cus_app_sc\
                MsWrapper\
                rtk\
                rtk_cus\
                sys\
                sys_cus\
		r2dummy\
                libc\
                trc\
                trc_cus

PRODUCT_SC += \
                dlm_entry

#= DUO section ================================================================
# -- Modification for project DUO
# JY: Place the name of module you want to duplicate here. An additional library
#     will be produced with all exported symbols renamed (by post-fix "_2")
#
# Alex: Add sim module to duplicate for B2/B3.
PRODUCT_SC_STACK2 =        \


#= MDL section ================================================================

PRODUCT_SC_MDL = \
  audio\
  abb_mdl\
  audio_mdl\
  batt\
  compression_mdl\
  cpu_mdl\
  fms_cus\
  gpd_mdl\
  gss\
  image_codec\
  image_config\
  keypad_mdl\
  pm_mdl\
  rai\
  tscr_mdl\
  vfs\
  camera_mdl\
  camera_top\
  camera_ip\
  efat\
  efat_wrapper\
  eml_dlm\
  image_capture\
  mmaudio_common\
  mmaudio_common_release\
  mmaudio_getinfo \
  midi\
  mp3dec_codec\
  aacdec_codec\
  amrnbdec_codec\
  amrnbenc_codec\
  amrwbdec_codec\
  amrwbenc_codec\
  wmadec_codec\
  cookdec_codec\
  mp3enc_codec\
  sbcenc_codec\
  wavenc_codec\
  wavdec_codec\
  mmaudio_spectrum\
  mmmanager\
  mmmanager_lib\
  aec_proc\
  ns_proc\
  3dsurround\
  peq\
  hw_geq\
  hw_peq\
  exp_vol\
  drc_limiter\
  drc_limiter_v2\
  drclookahead_limiter\
  hard_limiter\
  hw_drc\
  reverb\
  srs_wowhd\
  sc_fade\
  time_stretch\
  timepitch_stretch\
  app_mgr\
  app_mgr_shell\
  arp_exp_vol\
  arp_sw_agc\
  arp_hw_agc\
  arp_mgr\
  arp_mgr_shell\
  venc\
  storage_mdl\
  usb_mdl\
  mtmgr\
  vdr\
  vdr_top\
  vdr_mux


ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
PRODUCT_SC_MDL += \
    vt_mm \
    vt_task
endif

ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PRODUCT_SC_MDL += \
  ofn_mdl
endif

ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PRODUCT_SC_MDL += \
  ball_mdl
endif


PRODUCT_SC_MDL +=\
  3g_ip\
  3g_ngip\
  3g_ngos\
  3g_cm\
  3g_ppp\
  3g_ril\
  3g_conn\
  3g_mdlut\
  3g_atp\
  3g_mux\
  3g_vml

PRODUCT_SC_MDL += fms_nand

#= DRV section ===============================================================

PRODUCT_SC_DRV = \
  acc\
  adc\
  adc_hal\
  audio_drv\
  audio_hal\
  batt_hal\
  battery\
  bus\
  bus_hal\
  clkgen\
  clkgen_hal\
  cust_drv\
  cust_drv_dummy\
  disp\
  disp_hal\
  emi\
  emi_hal\
  flash\
  gpd_drv\
  gpd_hal\
  gsensor\
  proximitysensor\
  backlight\
  int\
  int_hal\
  io\
  io_hal\
  kernel_hal\
  keypad\
  keypad_hal\
  lcd\
  lcd_hal\
  pll_hal\
  pm\
  pm_hal\
  power\
  rtc\
  rtc_hal\
  timer\
  timer_hal\
  tscr\
  tscr_hal\
  uart\
  uart_hal\
  misc_hal\
  time\
  disk\
  disk_storage\
  drvutil_hal\
  drvtable_hal\
  dynscl\
  dynscl_hal\
  fmrx\
  fmrx_hal\
  etmi\
  etmi_hal\
  mfd\
  mfd_hal\
  jpd\
  jpd_hal\
  jpe\
  jpe_hal\
  pmu_hal\
  scl\
  scl_hal\
  sensorif\
  sensorif_hal\
  sensordriver\
  unfd\
  unfd_hal\
  usb\
  usb_hal\
  mbas\
  mbas_hal\
  storage\
  fcie\
  sdio\
  hwconfig\
  hwconfig_hal\
  nvram_drv\
  g3d_hal




ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PRODUCT_SC_DRV += \
  ball\
  ball_hal
endif

ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PRODUCT_SC_DRV += \
  ofn\
  ofn_hal
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
PRODUCT_SC_DRV +=\
  bluetooth
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
PRODUCT_LIB_DRV +=\
    g3d
endif

ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
PRODUCT_SC_DRV +=\
    atv
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR_ACRUX2__)
## for bluetooth library
PRODUCT_LIB_DRV +=\
	bt_host_acrux2 \
	bt_mac_normal  \
	bt_mac_critical
ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
PRODUCT_LIB_DRV +=\
	a2dp
endif
else
PRODUCT_LIB_DRV +=\
	bt_host
endif
endif




#= SYS section ================================================================

PRODUCT_SC_SYS = \
  cn\
  ResMgr\
  truetype\
  ucs2\
  bsp_c0f\
  sqlite

PRODUCT_SC_MMI_APP = \
  app\
  cust_mmi

ifeq ($(filter __UNIT_TEST_APP__ ,$(PP_OPT_COMMON)),__UNIT_TEST_APP__)
PRODUCT_SC_MMI_APP += \
  UnitTestApp
endif

PRODUCT_SC_MMI_CUSDEFINE = \
  CusDefine

PRODUCT_SC_MMI_SRVWRAPPER = \
  SrvWrapper

PRODUCT_SC_MMI_SRV = \
  srv

ifeq ($(filter __UNIT_TEST_SRV__ ,$(PP_OPT_COMMON)),__UNIT_TEST_SRV__)
PRODUCT_SC_MMI_SRV += \
  UnitTestSrv
endif

PRODUCT_SC_MMI_MAE = \
  mae

PRODUCT_SC_MMI_MAE_PORTING = \
  mae_porting

PRODUCT_LIB_MMI_MGL = \
  mgl

PRODUCT_SC_MMI_CORE = \
  core

PRODUCT_SC_MMI_MMICOMN = \
  mmicomn

PRODUCT_SC_MMI_WIDGET = \
  widget\
  widget_priv

PRODUCT_SC_MMI_MODEL = \
  model

PRODUCT_SC_MMI_APP_LAUNCHER = \
  AppLauncher

PRODUCT_SC_MMI_NCCMms_ = \
  NCCMms_target
PRODUCT_SC_MMI_NCCMms_cus_ = \
  NCCMms_cus
PRODUCT_SC_MMI_NCCCommon_ = \
  NCCCommon_target
PRODUCT_SC_MMI_NCCCommon_wsp_ = \
  NCCCommon_wsp
PRODUCT_SC_MMI_NCCCommon_cus_ = \
  NCCCommon_cus
PRODUCT_SC_MMI_NCCBrowser_ = \
  NCCBrowser_target
PRODUCT_SC_MMI_NCCBrowser_cus_ = \
  NCCBrowser_cus

PRODUCT_SC_MMI = \
  $(PRODUCT_SC_MMI_CORE)\
  $(PRODUCT_SC_MMI_MAE)\
  $(PRODUCT_SC_MMI_MAE_PORTING)\
  $(PRODUCT_SC_MMI_MMICOMN)\
  $(PRODUCT_SC_MMI_SRVWRAPPER)\
  $(PRODUCT_SC_MMI_WIDGET)\
  $(PRODUCT_SC_MMI_SRV)\
  $(PRODUCT_SC_MMI_MODEL)\
  $(PRODUCT_SC_MMI_APP_LAUNCHER)\
  $(PRODUCT_SC_MMI_CUSDEFINE)\
  $(PRODUCT_SC_MMI_NCCMms_)\
  $(PRODUCT_SC_MMI_NCCMms_cus_)\
  $(PRODUCT_SC_MMI_NCCCommon_)\
  $(PRODUCT_SC_MMI_NCCCommon_cus_)\
  $(PRODUCT_SC_MMI_NCCBrowser_)\
  $(PRODUCT_SC_MMI_NCCBrowser_cus_)\
  $(PRODUCT_SC_MMI_APP)

ifeq ($(filter NCC_WSP ,$(PP_OPT_COMMON)),NCC_WSP)
PRODUCT_SC_MMI += $(PRODUCT_SC_MMI_NCCCommon_wsp_)
endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
PRODUCT_LIB_MMI += $(PRODUCT_LIB_MMI_MGL)
endif

PRODUCT_SC_CUS = \




#
# module FLAVOR setting
#

#FLAVOR_bus = _cork
#FLAVOR_io  = _cork
#FLAVOR_ir   = _cork
#FLAVOR_sim = _cork
FLAVOR_v42  = _cork
FLAVOR_fax  = _cork









#
# for paths
#
include $(COMMON)paths.mak











#==============================================================================#
#
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
# WARNING: The folling path should be moved to $(module).mak   e.g. sys.mak
#
#==============================================================================#





# CUS group source code

#==============================================================================#
PATH_C +=\
    $(PATH_cus_app)/src\
    $(PATH_cus_app_lib)/src\
    $(PATH_cus_app_sc)/src

PATH_H +=\
    $(PATH_app)\
    $(PATH_core)/interface/inc\
    $(PATH_cus_app)/inc

# MDL group source code
PATH_C += \
   $(PATH_venc_src) \
   $(PATH_venc_src)/dct \
   $(PATH_venc_src)/h263v \
   $(PATH_venc_src)/mc \
   $(PATH_venc_src)/me \
   $(PATH_venc_src)/outbits \
   $(PATH_venc_src)/quant \
   $(PATH_venc_src)/rc  \
   $(PATH_venc_src)/flow \
   $(PATH_venc_src)/common \
   $(PATH_venc_src)/crco \
   $(PATH_hopper)/src

PATH_H +=\
    $(PATH_3g_ril)/itf\
    $(PATH_compression_mdl)/inc\
    $(PATH_mmmanager)/inc\
    $(PATH_mmmanager_lib)/inc\
    $(PATH_hopper)/inc\



ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PATH_H +=\
    $(PATH_ball_mdl)/inc
endif


ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
PATH_H +=\
    $(PATH_g3d)/inc \
    $(PATH_g3d)/inc/EGL \
    $(PATH_g3d)/inc/GLES \
    $(PATH_g3d)/inc/KHR \
    $(PATH_g3d)/inc/g3d \
    $(PATH_g3d_hal)/inc\

PATH_EXT_LIB +=\
    $(PATH_g3d)/lib
endif


# DRV group source code
PATH_C +=\
    $(PATH_acc)/opxc\
    $(PATH_acc)/src
    

PATH_H +=\
    $(PATH_esl)/itf\
    $(PATH_ema)/main/inc\
    $(PATH_bluetooth)/inc\
    $(PATH_rtc)/inc\
    $(PATH_scl)/inc\
    $(PATH_scl_hal)/inc\
    $(PATH_tscr_hal)/inc\
    $(PATH_audio_hal)/inc\
    $(PATH_mmicomn)/inc\
    $(PATH_etmi_hal)/inc\
    $(PATH_jpd)/inc\
    $(PATH_jpd_hal)/inc\
    $(PATH_jpe)/inc\
    $(PATH_jpe_hal)/inc\
    $(PATH_bus)/inc\
    $(PATH_bus_hal)/inc\
    $(PATH_unfd_hal)/inc\
    $(PATH_mbas)/inc\
    $(PATH_mbas_hal)/inc\
    $(PATH_pmu_hal)/inc\
    $(PATH_misc_hal)/inc\
    $(PATH_nvram_drv)/inc\
    $(PATH_disk)/inc



ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
PATH_C +=\
    $(PATH_g3d_hal)/src
endif

ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
PATH_C +=\
    $(PATH_atv)/src
endif



ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
PATH_H +=\
    $(PATH_atv)/inc
endif

ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PATH_C +=\
    $(PATH_ofn_hal)/src
PATH_H +=\
    $(PATH_ofn_hal)/inc
endif

ifeq ($(call FIND_COMPILER_OPTION, __BALL_DRV__), TRUE)
PATH_H +=\
    $(PATH_ball)/inc\
    $(PATH_ball_hal)/inc
endif


# SYS group source code
PATH_C +=\
    $(PATH_application)sys/file_mgr \
    $(PATH_application)sys/file_mgr/src \
    $(PATH_cn)/src\
    $(PATH_bsp_c0f)/src

ifneq ($(QUICK),MSC)
PATH_C +=\
    $(PATH_ResMgr)/src/ABL \
    $(PATH_ResMgr)/src/DataStruct \
    $(PATH_ResMgr)/src/DBL \
    $(PATH_ResMgr)/src/HAL \
    $(PATH_ResMgr)/src/MediaCmd \
    $(PATH_ResMgr)/src/ResMgr \
    $(PATH_ResMgr)/src/Simulator \
    $(PATH_ResMgr)/src/Util \
    $(PATH_ResMgr)/src/SocketCore \
    $(PATH_ResMgr)/src/SocketResMgr
endif

PATH_H +=\
    $(PATH_application)sys/file_mgr \
    $(PATH_application)sys/file_mgr/inc \
    $(PATH_ResMgr)/inc \
    $(PATH_ResMgr)/inc/ABL \
    $(PATH_ResMgr)/inc/DataStruct \
    $(PATH_ResMgr)/inc/DBL \
    $(PATH_ResMgr)/inc/HAL \
    $(PATH_ResMgr)/inc/MediaCmd \
    $(PATH_ResMgr)/inc/ResMgr \
    $(PATH_ResMgr)/inc/Util \
    $(PATH_ResMgr)/inc/SocketCore \
    $(PATH_ResMgr)/inc/SocketResMgr \

#MMI group source code

MMI_PATH_H +=\
    $(PATH_mae)/porting/inc\
    $(PATH_mae)/inc \
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmi_res)\
    $(PATH_cust_mmi)/inc

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
MMI_PATH_H +=\
    $(PATH_mgl)/mAnimation/inc\
    $(PATH_mgl)/mCore/inc\
    $(PATH_mgl)/mEffect/inc\
    $(PATH_mgl)/mEgl/inc\
    $(PATH_mgl)/mFont/inc\
    $(PATH_mgl)/mScene/inc\
    $(PATH_mgl)/mTexture/inc\
    $(PATH_mgl)/mUtility/inc
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
MMI_PATH_H +=\
    $(PATH_g3d)/inc \
    $(PATH_g3d)/inc/EGL \
    $(PATH_g3d)/inc/GLES \
    $(PATH_g3d)/inc/KHR \
    $(PATH_g3d)/inc/g3d
endif

MMI_PATH_H +=\
    $(PATH_core) \
    $(PATH_core)/interface/inc

# CUS group source code
PATH_C +=\

PATH_H +=\

#r2
PATH_C +=\
  $(PATH_r2)/src\

PATH_H +=\
  $(PATH_r2)/inc\

PATH_ASM +=\
    $(PATH_r2)/src\
    $(PATH_libc)/src

PATH_I +=\
    $(PATH_r2)/inc






























#
#= virtual libs group ==========================================================================
#

#
# The following lib set e.g. LIB_MSZ_SET and LIB_MSC_SET identify
# libs which do not want to release for each specified accounts.
#

#
# MSZ
#
LIB_MSZ_SET = \
        3g_cm \
        3g_conn \
        3g_ip \
        3g_mdlut \
        3g_mux \
        3g_ngip \
        3g_ngos \
        3g_ppp \
        3g_ril \
        3g_atp \
        3g_vml \
        csn1 \
        cust_sys \
        demuxer \
        fcm \
        mmp_common \
        mmplayer \
        mp4demux \
        obex \
        v24 \
        v24_cus \
        viddecoder \
        hwl_prod \
        hwl

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
LIB_MSZ_SET += \
    g3d
endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
LIB_MSZ_SET += \
    $(PRODUCT_LIB_MMI_MGL)
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR_ACRUX2__)
## for B3 G1
LIB_MSZ_SET +=\
	bt_host_acrux2 \
	bt_mac_normal  \
	bt_mac_critical
ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
LIB_MSZ_SET +=\
	a2dp
endif
else
LIB_MSZ_SET +=\
	bt_host
endif
endif

#
# MSC
#
LIB_MSC_SET = \
        venc \
        3g_ip \
        3g_ngip \
        3g_ngos \
        abb_mdl \
        compression_mdl \
        acc \
        adc \
        adc_hal \
        app \
        3dsurround \
        exp_vol \
        time_stretch\
        timepitch_stretch \
        reverb\
        srs_wowhd\
        sc_fade \
        peq \
        hw_geq \
        hw_peq \
        drc_limiter \
        drc_limiter_v2 \
        drclookahead_limiter \
        hard_limiter \
        hw_drc \
        app_mgr \
        app_mgr_shell \
        arp_exp_vol\
        arp_sw_agc\
        arp_hw_agc\
        arp_mgr \
        arp_mgr_shell \
        AppLauncher \
        audio \
        audio_drv \
        audio_hal \
        audio_mdl \
        backlight \
        batt \
        battery \
        batt_hal \
        bus \
        bus_hal \
		boot \
        camera_mdl \
        clkgen \
        clkgen_hal \
        cn \
        core \
        cpu_mdl \
        csn1 \
        demuxer \
        disp \
        disp_hal \
        dlm_entry \
        drvtable_hal \
        drvutil_hal \
        misc_hal \
        dynscl \
        dynscl_hal \
        efat \
        emi \
        emi_hal \
        eml_dlm \
        etmi \
        etmi_hal \
        fakevendor \
        fcie \
        sdio\
        fcm \
        flash \
        fmrx \
        fmrx_hal \
        fms \
        fms_cus \
        gpd_drv \
        gpd_hal \
        gpd_mdl \
        gsensor \
        proximitysensor \
        gss \
        hwconfig \
        hwconfig_hal \
        hzrecog_aeon \
        i18n \
        image_capture \
        image_codec \
        image_config \
        int \
        int_hal \
        io \
        io_hal \
        jpd \
        jpd_hal \
        jpe \
        jpe_hal \
        kernel_hal \
        keypad \
        keypad_hal \
        keypad_mdl \
        lcd \
        libc \
        mae \
        mae_porting \
        mbas \
        mbas_hal \
        mfd \
        mfd_hal \
        mmaudio_common \
        mmaudio_common_release \
        mmaudio_getinfo \
        midi \
        mmicomn \
        mmplayer \
        mmp_common \
        model \
        mp4demux \
        mserv \
        MsWrapper \
        mtmgr \
        NCCBrowser_target \
        NCCCommon_target \
        NCCMms_target \
        obex \
        pll_hal \
        pm \
        pmu_hal \
        pm_hal \
        pm_mdl \
        power \
        r2 \
        rai \
        ResMgr \
        mmmanager \
        mmmanager_lib \
        rtc \
        rtc_hal \
        rtk \
        rtk_cus \
        scl \
        scl_hal \
        sdk \
        sensordriver \
        sensorif \
        sensorif_hal \
        srv \
        SrvWrapper \
        sys \
        sys_cus \
        timer \
        timer_hal \
        trc \
        trc_cus \
        truetype \
        tscr \
        tscr_hal \
        tscr_mdl \
        uart \
        uart_hal \
        ucs2 \
        unfd \
        unfd_hal \
        usb \
        usb_hal \
        usb_mdl \
        utility \
        v24 \
        v24_cus \
        vdr \
        vdr_top \
        vfs \
        viddecoder \
        wap \
        widget \
        widget_priv \
        zlib \
        hwl \
        hwl_prod \
        nvram_drv \
        time

ifeq ($(filter __VT_3G324M__ ,$(PP_OPT_COMMON)),__VT_3G324M__)
LIB_MSC_SET += \
    vt_mm \
    vt_task
endif

ifeq ($(filter __IME_MMI_MY__ ,$(PP_OPT_COMMON)),__IME_MMI_MY__)
LIB_MSC_SET += \
    ime
endif

ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
LIB_MSC_SET += \
    g3d
endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
LIB_MSC_SET += \
    $(PRODUCT_LIB_MMI_MGL)
endif

ifeq ($(filter __SDK_MMI_VENDOR_ENTRY__ ,$(PP_OPT_COMMON)),__SDK_MMI_VENDOR_ENTRY__)
LIB_MSC_SET += \
    vendor
endif

ifeq ($(filter __BLUETOOTH_DRV_MSTAR__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR__)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__, $(PP_OPT_COMMON)), __BLUETOOTH_DRV_MSTAR_ACRUX2__)
## for B3 G1
LIB_MSC_SET +=\
	bt_host_acrux2 \
	bt_mac_normal  \
	bt_mac_critical
ifeq ($(filter __BLUETOOTH_A2DP__, $(PP_OPT_COMMON)), __BLUETOOTH_A2DP__)
LIB_MSC_SET +=\
	a2dp
endif
else
LIB_MSC_SET +=\
	bt_host
endif
endif

#
# for G1 DPM
#
include $(PATH_common_mak)lib_paths_g1_dpm.mak

#
# PRODUCT_ALL = all library group
#
PRODUCT_ALL=$(PRODUCT_SC) $(PRODUCT_LIB) \
	$(PRODUCT_SC_MDL) $(PRODUCT_LIB_MDL)  \
	$(PRODUCT_SC_DRV) $(PRODUCT_LIB_DRV)  \
	$(PRODUCT_SC_SYS) $(PRODUCT_LIB_SYS)  \
	$(PRODUCT_SC_MMI) $(PRODUCT_LIB_MMI)  \
	$(PRODUCT_SC_3RD) $(PRODUCT_LIB_3RD)

ifeq ($(RELEASE_PROCESS),1)
PRODUCT_ALL += $(PRODUCT_SC_CUS)
else
PRODUCT_ALL_STACK2 += $(PRODUCT_SC_STACK2) $(PRODUCT_LIB_STACK2)
endif

#
# for MSC/MSZ it does not need libs in LIB_MSC_SET/LIB_MSZ_SET
# so we need filter-out unnecessary libraries
#
ifeq ($(QUICK),MSZ)
PRODUCT_ALL:=$(filter-out $(LIB_MSZ_SET),$(PRODUCT_ALL))
PRODUCT_ALL_STACK2:=$(filter-out $(LIB_MSZ_SET),$(PRODUCT_ALL_STACK2))
endif
ifeq ($(QUICK),MSC)
PRODUCT_ALL:=$(filter-out $(LIB_MSC_SET),$(PRODUCT_ALL))
PRODUCT_ALL_STACK2:=$(filter-out $(LIB_MSC_SET),$(PRODUCT_ALL_STACK2))
endif

# this library set defines the libs which would not be linked to image.
# note that it is a virtual libs group which indicate these libs would not be linked to image
# RD must add same lib at above lib group. e.g. PRODUCT_LIB
#
DUMMY_LIB_LIST +=       \
       r2dummy          \
       cust_drv_dummy
