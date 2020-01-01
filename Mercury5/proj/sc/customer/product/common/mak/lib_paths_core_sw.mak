#===============================================================================
# Core Software Modules
#===============================================================================

# Specify all libraries which should not be compiled from source code
# in PRODUCT_LIB, and note that:
# 1. Library name specified here should not appear in PRODUCT_SC again.
# 2. Don't specify any library name which was not originally specified in
#    PRODUCT_SC. For example, "mmi", "camera" shall not be specified in
#    PRODUCT_LIB.
#

#= GSM stack modules ===========================================================
PRODUCT_LIB = \
  csn1\
  cc\
  ce\
  data\
  dl\
  fax\
  fcm\
  hwl\
  hwl_cus\
  hwl_rf_aero2\
  hwl_rf_msr7100\
  hwl_rf_msr7120\
  hwl_prod\
  hwl_tiny\
  ip\
  l1c\
  llc\
  mmc\
  mmc_cus\
  mmp\
  mmp_cus\
  mms\
  mnp2\
  ngip\
  ngos\
  ngppp\
  pps\
  rld\
  rlu\
  sim\
  sim_cus\
  tel_cus\
  smg\
  sms\
  sn\
  ss\
  v42\
  v42b\
  ip_dummy

ifeq ($(COMPILER_VERSION), RVCTV22)
PRODUCT_LIB += \
  rrc1\
  rrc2\
  rrc3\
  rrd\
  rrs\
  rrm\
  rrt\
  rrp
endif

#= System modules ==============================================================
PRODUCT_SC = \
  MsWrapper\
  rtk\
  rtk_cus\
  sys\
  sys_cus\
  trc\
  trc_cus\
  v24\
  v24_cus

ifeq ($(COMPILER_VERSION), RVCTV22)
PRODUCT_SC += \
  boot\
  arm
endif

#= Middleware modules ==========================================================
PRODUCT_SC +=\
  ati_main\
  ati_cc\
  ati_cphs\
  ati_phb\
  ati_ps\
  ati_mm\
  ati_modem\
  ati_serial\
  ati_sim\
  ati_sms\
  ati_ss\
  dynldr\
  dynldr_cus\
  vml_ase\
  vml_cc\
  vml_cphs\
  vml_ps\
  vml_sms\
  vml_sim\
  vml_phb\
  vml_mm\
  vml_ss\
  vml_stlk\
  vml_util

PRODUCT_SC +=\
  cus_app\
  cus_app_lib\
  cus_app_sc

PRODUCT_SC_MDL = \
  audio\
  abb_mdl\
  audio_mdl\
  batt\
  fms_cus\
  pm_mdl\
  rai\
  usb_mdl\
  gpd_mdl\
  mtmgr\
  vfs\
  cpu_mdl\
  camera_mdl




ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), TRUE)
ifeq ($(call FIND_COMPILER_OPTION, __STANDALONE_MODE__), TRUE)

PRODUCT_SC_MDL += storage_mdl

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRODUCT_SC_MDL += fms_nand
else
PRODUCT_SC_MDL += fms_nor
endif

endif
endif

#= Driver modules ==============================================================
PRODUCT_SC_DRV =\
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
  drvutil_hal\
  emi\
  emi_hal\
  flash\
  gpd_drv\
  gpd_hal\
  int\
  int_hal\
  io\
  io_hal\
  kernel_hal\
  keypad\
  keypad_hal\
  pll_hal\
  pm\
  pm_hal\
  pmu_hal\
  power\
  rtc\
  rtc_hal\
  timer\
  timer_hal\
  uart\
  uart_hal\
  glue

ifeq ($(filter __ROMPATCH_SUPPORT__ ,$(PP_OPT_COMMON)),__ROMPATCH_SUPPORT__)
PRODUCT_SC_DRV +=\
  rompatch_hal
endif

ifeq ($(call FIND_COMPILER_OPTION, __CORE_SOFTWARE__), TRUE)
ifeq ($(call FIND_COMPILER_OPTION, __STANDALONE_MODE__), TRUE)

PRODUCT_SC_DRV += \
  fcie\
  sdio\
  storage

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRODUCT_SC_DRV += \
  unfd\
  unfd_hal
endif

PRODUCT_SC_DRV += shmcl shmcl_mmp

endif
endif

#= SYS section ================================================================

PRODUCT_SC_SYS = \
  cust_sys\
  bsp_837\
  bsp_8f4\
  bsp_833\
  bsp_737\
  bsp_838\
  bsp_c3c

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
FLAVOR_data = _cork

ifeq (TRUE, $(strip $(CORE_SOFTWARE)))
# Render core SW a simplified cus_app
FLAVOR_cus_app = _core
endif



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
# Core SW group source code
PATH_C +=\
    $(PATH_cus_app)/src\
    $(PATH_cus_app_lib)/src\
    $(PATH_cus_app_sc)/src

PATH_H +=\
    $(PATH_app)\
    $(PATH_core)/interface/inc\
    $(PATH_cus_app)/inc\
    $(PATH_MsWrapper)/inc

# MMI group source code
PATH_H +=\
    $(PATH_mmicomn)/inc

# MDL group source code

PATH_H +=\
    $(PATH_mmmanager)/inc\
    $(PATH_mmmanager_lib)/inc\
    $(PATH_vfs)/inc



ifeq ($(call FIND_COMPILER_OPTION, __ATV__), TRUE)
PATH_H +=\
    $(PATH_tv_mdl)/inc
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
PATH_H +=\
    $(PATH_gps_mdl)/inc
endif

# DRV group source code
PATH_H +=\
    $(PATH_audio_hal)/inc\
    $(PATH_disk)/inc\
    $(PATH_clkgen_hal)\inc\
    $(PATH_pmu_hal)/inc


# WIFI
PATH_H +=\
    $(PATH_wlan_cus)/inc\
    $(PATH_supplicant_cus)/inc


ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
PATH_H +=\
    $(PATH_g3d)/inc \
    $(PATH_g3d)/inc/EGL \
    $(PATH_g3d)/inc/GLES \
    $(PATH_g3d)/inc/KHR \
    $(PATH_g3d)/inc/g3d
PATH_EXT_LIB +=\
    $(PATH_g3d)/lib
endif


ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
ifeq (,$(strip $(PATH_atv)))
$(error Unsupported atv: $(ATV_CHIP))
endif

CHECK_ATV_DRIVER := $(wildcard $(PATH_atv))
ifeq ($(strip $(CHECK_ATV_DRIVER)),)
$(error Cannot find driver of $(ATV_CHIP) in $(PATH_atv))
endif


PATH_C +=\
    $(PATH_atv)/src
PATH_H +=\
    $(PATH_atv)/inc \
	$(PATH_atv_itf)
endif



ifeq ($(call FIND_COMPILER_OPTION, __OFN_DRV__), TRUE)
PATH_C +=\
    $(PATH_ofn_hal)/src
PATH_H +=\
    $(PATH_ofn_hal)/inc
endif


ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
ifneq ($(QUICK),MSZ)
ifeq ($(RELEASE_PROCESS),0)
PATH_C +=\
    $(PATH_gps)/Baseband/src\
    $(PATH_gps)/ME/src\
    $(PATH_gps)/PE/src\
    $(PATH_gps)/PLATFORM/RTK/src
PATH_H +=\
    $(PATH_gps)/Baseband/inc\
    $(PATH_gps)/ME/inc\
    $(PATH_gps)/PE/inc
endif
endif
PATH_H +=\
    $(PATH_gps)/PLATFORM/Common/inc\
    $(PATH_gps)/PLATFORM/RTK/inc
endif

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PATH_H +=\
    $(PATH_unfd_hal)/inc
endif

ifneq ($(filter __NO_HW_JPD__ ,$(PP_OPT_COMMON)),__NO_HW_JPD__)
PATH_C +=\
    $(PATH_jpd_hal)/src
endif

ifeq ($(call FIND_COMPILER_OPTION, __WLAN__), TRUE)
PATH_C += $(PATH_wlan_hal)/src
PATH_H += $(PATH_wlan_drv)/inc
PATH_H += $(PATH_wlan_hal)/inc
endif

# SYS group source code
PATH_C +=\
    $(PATH_application)sys/file_mgr/src\
    $(PATH_hopper)/src\
    $(PATH_cn)/src\
    $(PATH_ResMgr)/src/ABL \
    $(PATH_ResMgr)/src/DataStruct \
    $(PATH_ResMgr)/src/DBL \
    $(PATH_ResMgr)/src/HAL \
    $(PATH_ResMgr)/src/MediaCmd \
    $(PATH_ResMgr)/src/ResMgr \
    $(PATH_ResMgr)/src/Simulator \
    $(PATH_ResMgr)/src/Util \
    $(PATH_ResMgr)/src/SocketCore \
    $(PATH_ResMgr)/src/SocketResMgr \
    $(PATH_bsp_837)/src \
    $(PATH_bsp_8f4)/src \
    $(PATH_bsp_833)/src \
    $(PATH_bsp_737)/src \
    $(PATH_bsp_838)/src \
    $(PATH_bsp_c3c)/src

PATH_H +=\
    $(PATH_application)sys/file_mgr/inc\
    $(PATH_hopper)/inc\
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
    $(PATH_mae)/inc \

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
    $(PATH_core)/interface/inc\

# CUS group source code
PATH_C +=\

PATH_H +=\




































#
#= virtual libs group ==========================================================================
#


# This library set defines the libs which use ARM mode in compiling
# Note that it is a virtual libs group which indicate these libs use ARM mode,
# RD must add same lib name at above lib group.  e.g PRODUCT_LIB
ARM_LIB_LIST = \
#   dlm_entry


# This library set defines the libs which disable feedback options in compiling and linking
# Note that it is a virtual libs group which indicate these libs disable feedback options,
# RD must add same lib name at above lib group.  e.g PRODUCT_LIB
ifeq ($(filter __UNIT_TEST_APP__ ,$(PP_OPT_COMMON)),__UNIT_TEST_APP__)
UT_LIB_LIST = \
    dlm_entry \
    ut_mdl \
    MsWrapper

ifeq ($(filter __ENABLE_DLM_SRVUT__ ,$(PP_OPT_COMMON)),__ENABLE_DLM_SRVUT__)
UT_LIB_LIST += \
    SrvWrapper \
    UnitTestApp
endif

endif

UT_LIB_LIST += \
   mp3dec_codec \
   aacdec_codec

# This library set defines the libs which would not be linked to image.
# Note that it is a virtual libs group which indicate these libs would not be linked to image.
# RD must add same lib at above lib group.  e.g PRODUCT_LIB

# Description = [RF] Determine which radio driver should be included in the software build.
ifeq ($(strip $(RFIC)), $(filter $(RFIC),msr7100 msr7100d))
# For Legacy
DUMMY_LIB_LIST +=\ hwl_rf_aero2
DUMMY_LIB_LIST +=\ hwl_rf_msr7120
else
ifeq ($(strip $(RFIC)),msr7120)
# For Apus
DUMMY_LIB_LIST +=\ hwl_rf_aero2
DUMMY_LIB_LIST +=\ hwl_rf_msr7100
else
# For Aero2
DUMMY_LIB_LIST +=\ hwl_rf_msr7100
DUMMY_LIB_LIST +=\ hwl_rf_msr7120
endif
endif

# For bsp
BSP_FILE_LIST = $(foreach n, $(wildcard $(PATH_system)bsp/bsp*.mak), $(n:$(PATH_system)bsp/%.mak=%))
DUMMY_LIB_LIST += $(addprefix \ , $(filter-out $(BSP_ID) bsp_mn bsp_c0f, $(BSP_FILE_LIST)))

# Internal Audio Codec / Control


# Audio Post-Processer IPs
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_3D_SURROUND), TRUE)
DUMMY_LIB_LIST +=\ 3dsurround
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_USER_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SPEAKER_PEQ), TRUE)
DUMMY_LIB_LIST +=\ peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_GEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_GEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_geq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_GEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_GEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_geq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SPEAKER_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_USER_PEQ), TRUE)
DUMMY_LIB_LIST +=\ peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_PEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_PEQ), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_PEQ), TRUE)
DUMMY_LIB_LIST +=\ hw_peq
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_VOL_CONTROL_EXP), TRUE)
DUMMY_LIB_LIST +=\ exp_vol
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_DRC_LIMITER), TRUE)
DUMMY_LIB_LIST +=\ drc_limiter
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_DRC_LIMITER_V2), TRUE)
DUMMY_LIB_LIST +=\ drc_limiter_v2
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_LOOKAHEAD_DRC_LIMITER), TRUE)
DUMMY_LIB_LIST +=\ drclookahead_limiter
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_HARD_LIMITER), TRUE)
DUMMY_LIB_LIST +=\ hard_limiter
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_DRC), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_DRC), TRUE)
DUMMY_LIB_LIST +=\ hw_drc
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_G1HW_DRC), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BIG3HW_DRC), TRUE)
DUMMY_LIB_LIST +=\ hw_drc
endif
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SC_FADE), TRUE)
DUMMY_LIB_LIST +=\ sc_fade
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_TIME_STRETCH), TRUE)
DUMMY_LIB_LIST +=\ time_stretch
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_TIMEPITCH_STRETCH), TRUE)
DUMMY_LIB_LIST +=\ timepitch_stretch
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_DM2), TRUE)
DUMMY_LIB_LIST +=\ dm2
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_REVERB), TRUE)
DUMMY_LIB_LIST +=\ reverb
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_BASS), TRUE)
DUMMY_LIB_LIST +=\ bass
endif

ifneq ($(call FIND_COMPILER_OPTION, ENABLE_SRSWOWHD), TRUE)
DUMMY_LIB_LIST +=\ srs_wowhd
endif


# Audio Pre-Processer IPs
ifneq ($(call FIND_COMPILER_OPTION, ARP_SW_GAINCTR_ENABLE), TRUE)
DUMMY_LIB_LIST +=\ arp_exp_vol
endif

ifneq ($(call FIND_COMPILER_OPTION, ARP_SW_AGC_ENABLE), TRUE)
DUMMY_LIB_LIST +=\ arp_sw_agc
endif

ifneq ($(call FIND_COMPILER_OPTION, ARP_BIG3HW_AGC_ENABLE), TRUE)
ifneq ($(call FIND_COMPILER_OPTION, ARP_G1HW_AGC_ENABLE), TRUE)
DUMMY_LIB_LIST +=\ arp_hw_agc
endif
endif


DUMMY_LIB_LIST +=\ cust_drv_dummy

ifeq ($(call FIND_COMPILER_OPTION, __WLAN_IP_SUPPORT__), TRUE)
DUMMY_LIB_LIST +=\ ip_dummy
endif

#
# The following lib set e.g. LIB_MSZ_SET and LIB_MSC_SET identify
# libs which do not want to release for each specified accounts.
#

#
# MSZ
#
LIB_MSZ_SET = \
  csn1 \
  cc \
  ce \
  data \
  dl \
  fax \
  rrc1\
  rrc2\
  rrc3\
  rrd\
  rrs\
  rrm\
  rrt\
  rrp\
  hwl \
  hwl_rf_aero2\
  hwl_rf_msr7100\
  hwl_rf_msr7120\
  hwl_prod\
  hwl_tiny \
  ip \
  ip_dummy \
  l1c \
  llc \
  mmc \
  mmc_cus \
  mmp \
  mmp_cus \
  mms \
  mnp2 \
  ngip \
  ngos \
  ngppp \
  pps \
  rld \
  rlu \
  sim \
  sim_cus\
  tel_cus\
  smg \
  sms \
  sn \
  ss \
  v42 \
  v42b \



ifeq ($(filter __G3D_DRV__ ,$(PP_OPT_COMMON)),__G3D_DRV__)
LIB_MSZ_SET += g3d
endif

ifeq ($(filter __GPS_DUALSTAR_DRV__ ,$(PP_OPT_COMMON)),__GPS_DUALSTAR_DRV__)
LIB_MSZ_SET += gps
endif

ifeq ($(filter __FEATURE_MGL__ ,$(PP_OPT_COMMON)),__FEATURE_MGL__)
ifneq ($(filter __FEATURE_MGLS__ ,$(PP_OPT_COMMON)),__FEATURE_MGLS__)
LIB_MSZ_SET += $(PRODUCT_LIB_MMI_MGL)
endif
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
# MST, MST is a special case, it contains all module except acc & keypad
#
LIB_MST_SET := $(PRODUCT_ALL)
LIB_MST_SET := $(filter-out acc keypad, $(LIB_MST_SET))


#
# for MSC/MST/MSZ it does not need libs in LIB_(MSC/MST/MSZ)_SET
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
ifeq ($(QUICK),MST)
PRODUCT_ALL:=$(filter-out $(LIB_$(QUICK)_SET),$(PRODUCT_ALL))
PRODUCT_ALL_STACK2:=$(filter-out $(LIB_$(QUICK)_SET),$(PRODUCT_ALL_STACK2))
endif

