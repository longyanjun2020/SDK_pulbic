#===============================================================================
#  ** Platform Compile OPTIONS **
#
# Note:
# 1. The options below are not opened for customization. Please don't change
#    them unless you clearly know what you are doing.
# 2. They either involve part of software released in binaries or not fully
#    tested for non-default configuration. Switching them on/off will make
#    compilation fail or software not function properly.
#===============================================================================

include $(OPTIONS_CUS_MAK)

#-------------------------------------------------------------------------------
# Chip series related definition
#-------------------------------------------------------------------------------
ifneq ($(filter __MSW8533C__ __MSW8533CN__ __MSW8533N__ __MSW8536N__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_msw8533x.mak
endif
ifneq ($(filter __MSW8533D__ __MSW8532__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_msw8533d.mak
endif
ifneq ($(filter __MSW8532BL__ __MSW8532B__ __MSW8532B2__ __MSW8533BD__ __MSW8533BN__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_msw853xb.mak
endif
ifneq ($(filter __MSW8556__ __MSW8556R__ __MSW8556R2__ __MSW8556M__ __MSW8556M2__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_msw8556x.mak
endif
ifneq ($(filter  __MSW8573__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_msw8573.mak
endif
ifneq ($(filter __MSW8830N__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_msw8830x.mak
PP_OPT_COMMON += __G1__
endif
ifneq ($(filter __MSC316D__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_infinity.mak
PP_OPT_COMMON += __INFINITY__
endif
ifneq ($(filter __MSCXXXX__, $(CHIP_TYPE)),)
include $(COMMON)hal/options_mercury.mak
PP_OPT_COMMON += __INFINITY__
endif

#PP_OPT_COMMON += __MV5_FPGA__
#PP_OPT_COMMON += __MV5_ON_I3__

MERGETOBIN = MERGE_TO_BIN

ifeq (4MB, $(strip $(SMALL_ROM_SOLUTION)))
PP_OPT_COMMON += __SMALL_ROM_32__
PP_OPT_COMMON += __SMALL_ROM__
USB_UVC_DISABLE = TRUE
#USB_CDC_DISABLE = TRUE
else
ifeq (8MB, $(strip $(SMALL_ROM_SOLUTION)))
PP_OPT_COMMON += __SMALL_ROM__
else
ifeq (TRUE, $(strip $(SMALL_ROM_SUPPORT)))
PP_OPT_COMMON += __SMALL_ROM__
endif
endif
endif

#===============================================================================
# Common set
#===============================================================================
# Feature_Name = CAMERA
# Description = Option for camera feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CAMERA_SUPPORT = TRUE

# Feature_Name = Capture
# Description = Option for Capture feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CAPTURE_SUPPORT = TRUE

# Feature_Name = CAMCORDER
# Description = Option for camcorder feature
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CAMCORDER_SUPPORT = TRUE

# Feature_Name = Camera Multi-sensor Detection
# Description = Option to enable multi-sensor detection.
# Pre_Variable_True = N/A
# Pre_Variable_False = 5M_SENSOR_SUPPORT
# Option_Selection = TRUE, FALSE
MULTIPLE_SENSOR_TABLE_DETECTION_SUPPORT = TRUE

# Feature_Name = WAP
# Description = Option for WAP feature
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
WAP_SUPPORT = TRUE
else
ifeq (TRUE, $(strip $(SDK_API_WAP_MMS_ONLY_SUPPORT)))
WAP_SUPPORT = TRUE
else
WAP_SUPPORT = FALSE
endif
endif

# Feature_Name = Socket Service For MMI
# Description = Option To Enable Socket Service
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),__SMALL_ROM__)
SOCKETSR_SERVICE_SUPPORT = FALSE
else
SOCKETSR_SERVICE_SUPPORT = TRUE
endif

# Feature_Name = MMS
# Description = Option for MMS feature
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
MMS_SUPPORT = TRUE
else
ifeq (TRUE, $(strip $(SDK_API_WAP_MMS_ONLY_SUPPORT)))
MMS_SUPPORT = TRUE
else
MMS_SUPPORT = FALSE
endif
endif

# Feature_Name = hot key frequency
# Description = Option for hot key frequency
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
HOT_KEY_FREQUENCY_SUPPORT = FALSE

# Feature_Name = Dual IMEI
# Description = Option for supporting two IMEI value in one handset, this is
#           for dual sim hanset
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
DUAL_IMEI_SUPPORT = TRUE

# Feature_Name = Bluetooth Chip
# Description = [DRV] Enable bluetooth Chip
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT,CORE_SOFTWARE
# Option_Selection = __BLUETOOTH_DRV_S04__, __BLUETOOTH_DRV_TI6300__, __BLUETOOTH_DRV_RDA5868__, __BLUETOOTH_DRV_MSTAR__
BLUETOOTH_CHIP =

# Feature_Name = Extra Bluetooth Headset Profile Setting (MMI)
# Description = Add the extra profile setting item for Bluetooth headset
# Pre_Variable_True = BLUETOOTH_CHIP
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
EXTRA_BLUETOOTH_HEADSET_PROFILE_SUPPORT = TRUE

# Feature_Name = FAST GPIO access.
# Description = If this option is set, driver can access GPIO control register directly
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
FAST_GPIO_SUPPORT = TRUE

# Feature_Name = Audio Decoder Codec Support List
# Description = Option to Enable Audio Codec
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection =
MP3_DEC_SUPPORT = TRUE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
AAC_DEC_SUPPORT ?= TRUE
AMRNB_DEC_SUPPORT ?= TRUE
else
ifeq (SMALL_ROM_32_PROFILE_1, $(strip $(SMALL_ROM_32_SET)))
AAC_DEC_SUPPORT ?= TRUE
AMRNB_DEC_SUPPORT ?= TRUE
else
ifeq (SMALL_ROM_32_PROFILE_N, $(strip $(SMALL_ROM_32_SET)))
AAC_DEC_SUPPORT ?= TRUE
AMRNB_DEC_SUPPORT ?= TRUE
else
AAC_DEC_SUPPORT ?= FALSE
AMRNB_DEC_SUPPORT ?= FALSE
endif
endif
endif
WAV_DEC_SUPPORT = TRUE

# Feature_Name = Audio Encoder Codec Support List
# Description = Option to Enable Audio Codec
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection =
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
AMRNB_ENC_SUPPORT = TRUE
else
AMRNB_ENC_SUPPORT = FALSE
endif

# Feature_Name = Clock MIU 153MHz configuration
# Description = Option to Change clock miu from 156MHz to 153MHz
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
APLL_MIU_MODE_153MHZ = TRUE

# Feature_Name = AVI
# Description = Option for supporting AVI
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
AVI_SUPPORT = TRUE
else
AVI_SUPPORT = FALSE
endif

# Feature_Name = FM Radio
# Description = Option to enable FM radio application
# Pre_Variable_True = N/A
# Pre_Variable_False = MSTAR_CTA_SUPPORT
# Option_Selection = TRUE, FALSE
FM_RADIO_SUPPORT = TRUE

# Feature_Name = FM Radio Record
# Description = Option to enable FM radio record function
# Pre_Variable_True = FM_RADIO_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
FM_RADIO_RECORD_SUPPORT = TRUE
else
FM_RADIO_RECORD_SUPPORT = FALSE
endif

# Feature_Name = Shortcut List
# Description = Option to enable Shortcut List application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
SHORTCUTLIST_SUPPORT = TRUE
else
SHORTCUTLIST_SUPPORT = FALSE
endif

# Feature_Name = Voice Memo
# Description = Option to enable voice memo application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
VOICE_MEMO_SUPPORT = TRUE

# Feature_Name = Calendar
# Description = Option to enable calendar application
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
CALENDAR_SUPPORT = TRUE

# Feature_Name = Dual IMEI
# Description = Show dual IMEI value in *#06# and engineer mode
# Pre_Variable_True = DUAL_IMEI_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
DUAL_IMEI_MMI_SUPPORT = TRUE

# Feature_Name = SDK_API_SUPPORT
# Description = Option for sdk API
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
SDK_API_SUPPORT ?= TRUE
else
ifeq (TRUE, $(strip $(SDK_API_WAP_MMS_ONLY_SUPPORT)))
SDK_API_SUPPORT ?= TRUE
else
SDK_API_SUPPORT ?= FALSE
endif
endif

# Feature_Name = Battery icon is displayed in application or not.
# Description = Option for checking battery icon is displayed or not
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_32_SUPPORT
# Option_Selection = TRUE, FALSE
BATTERY_ICON_SUPPORT = TRUE

# Feature_Name = WBMP support
# Description = Option for enabling WBMP in image_codec
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
WBMP_SUPPORT ?= TRUE
else
ifeq (SMALL_ROM_32_PROFILE_1, $(strip $(SMALL_ROM_32_SET)))
WBMP_SUPPORT ?= TRUE
else
ifeq (SMALL_ROM_32_PROFILE_N, $(strip $(SMALL_ROM_32_SET)))
WBMP_SUPPORT ?= TRUE
else
WBMP_SUPPORT ?= FALSE
endif
endif
endif
#===============================================================================
# Connected options
#===============================================================================
# Feature_Name =
# Description = [SYS] RTK over ARM SLDLM mechanism
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(CHIP_NAND)))
RTK_OVER_ARM_SLDLM_SUPPORT = FALSE
else
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
RTK_OVER_ARM_SLDLM_SUPPORT = TRUE
else
RTK_OVER_ARM_SLDLM_SUPPORT = FALSE
endif
endif

# Feature_Name =
# Description = [SYS] RTK over ARM NAND IMI SLDLM mechanism
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(CHIP_NAND)))
RTK_OVER_ARM_NAND_IMI_SLDLM_SUPPORT = TRUE
else
RTK_OVER_ARM_NAND_IMI_SLDLM_SUPPORT = FALSE
endif

# Feature_Name = Load ATV driver from SLDLM
# Description = Option to enable SLDLM ATV driver
# Pre_Variable_True = ATV_CHIP
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ENABLE_ATV_DRIVER_SLDLM = TRUE
else
ENABLE_ATV_DRIVER_SLDLM = FALSE
endif

# Feature_Name = Load GPS driver from SLDLM
# Description = Option to enable SLDLM GPS driver
# Pre_Variable_True = CHIP_GPS
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ENABLE_GPS_DRIVER_SLDLM = TRUE
else
ENABLE_GPS_DRIVER_SLDLM = FALSE
endif

# Feature_Name = Font compression
# Description = Support Compressing Bitmap Font Resource in CUS.
#               It can reduce CUS size but need some additional memory.
# Pre_Variable_True = SMALL_ROM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
FONT_COMPRESSION_SUPPORT = TRUE
else
FONT_COMPRESSION_SUPPORT = FALSE
endif

# Feature_Name = String compression
# Description = Support compressing the string resource in CUS, it can reduce
#           CUS file size but need some additional memory.
# Pre_Variable_True = SMALL_ROM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
STRING_COMPRESSION_SUPPORT = TRUE
else
STRING_COMPRESSION_SUPPORT = FALSE
endif

# Feature_Name = FINT Disable DMA2D
# Description = [DRV] Disable DMA2D in FINT to speedup FINT process.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
FINT_DISABLE_DMA2D = FALSE

# Feature_Name = Clock source select for MIU
# Description = switch MIU clock src for RF sensitivity
# Pre_Variable_True = VLCM can always on
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(LCM_SLEEP_MODE_SUPPORT)))
MIU_CLK_SRV_APLL = TRUE
else
MIU_CLK_SRV_APLL = FALSE
endif

# Feature_Name = Audio seek
# Description = [MMI] Sppport audio seek function by gototime and FF/Rewind.
# Pre_Variable_True = N/A
# Pre_Variable_False = SMALL_ROM_SUPPORT
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
AUDIO_SEEK = FALSE
else
AUDIO_SEEK = TRUE
endif

# Feature_Name = Disable grouping for Phone Book
# Description = [MMI] Disable contact grouping for phone book.
# Pre_Variable_True = SMALL_PHB_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(SMALL_PHB_SUPPORT)))
PHBAP_DISABLE_GROUP = TRUE
endif

# Feature_Name = Disable import/export function for Phone Book
# Description = [MMI] Disable import and export functions for phone book.
# Pre_Variable_True = SMALL_PHB_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(SMALL_PHB_SUPPORT)))
PHB_DISABLE_IMPORT_EXPORT = TRUE
endif

# Feature_Name = Disable blacklist function for Phone Book
# Description = [MMI] Disable blacklist function for phone book.
# Pre_Variable_True = SMALL_PHB_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(SMALL_PHB_SUPPORT)))
PHB_DISABLE_BLACKLIST = TRUE
endif

# Feature_Name = Low memory config for MDL, MMI
# Description = [MDL] use low memory, it may cause performance degradation, [MMI] limit fg/bg ap concurrent
# Pre_Variable_True = __NOR__, LCD HVGA resolution, 4M PSRAM
# Pre_Variable_False = SMALL ROM 32
# Option_Selection = TRUE, FALSE
ifneq ($(filter __LCM_HVGA_320_480__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
ifneq ($(filter 0x00400000, $(SYS_PHY_RAM_SIZE_SETTING)),)
ifeq  ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
ifneq (TRUE, $(strip $(CHIP_NAND)))
MDL_LOW_MEMORY = TRUE
endif
endif
endif
endif

# Feature_Name = Low memory config for MDL, Camcorder
# Description = [MDL] set memory usage for camcorder
# Pre_Variable_True = CAMCORDER_MEMORY_REQ
# Pre_Variable_False = N/A
# Option_Selection = FULL, NORMAL, ECONOMY, FAST
# NORMAL: force to encode as row mode
# FAST: force to reduce video pool buffer to low bound
# ECONOMY: combine NORMAL and FAST conditions
ifneq ($(filter  NORMAL, $(CAMCORDER_MEMORY_REQ)),)
PP_OPT_COMMON += CAMCORDER_NORMAL_MODE
else
ifneq ($(filter  FAST, $(CAMCORDER_MEMORY_REQ)),)
PP_OPT_COMMON += CAMCORDER_FAST_MODE
else
ifneq ($(filter  ECONOMY, $(CAMCORDER_MEMORY_REQ)),)
PP_OPT_COMMON += CAMCORDER_ECONOMY_MODE
else
PP_OPT_COMMON += CAMCORDER_FULL_MODE
endif
endif
endif

# Feature_Name = LZMA2 preset dictionary
# Description = LZMA2 compression/decompression with preset dictionary
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(CHIP_NAND)))
LZMA2_PRESET_DICT_SUPPORT = FALSE
else
LZMA2_PRESET_DICT_SUPPORT = TRUE
endif

#===============================================================================
# ** Alpha Options **
#===============================================================================
MKV_SUPPORT ?= FALSE
TS_SUPPORT ?= FALSE
PS_SUPPORT ?= FALSE

#===============================================================================
# ** Engineer options **
#===============================================================================
BRAVO_TARGET_EVB ?= FALSE
EVB_WITHOUT_BATTERY_SUPPORT ?= FALSE
RADIO_USE_DB_SUPPORT ?= FALSE
SPI_MAX_SPEED ?= TRUE
SAMSUNG_K5L2833ATA_PAGE_PAGE_MODE ?= FALSE
LCM_ROTATE_SIMULATION ?= FALSE
BOOTUP_LOGO_BY_E2P_SUPPORT ?= FALSE
CUS_LCM_TABLE_SUPPORT ?= FALSE
CUS_DISPLAY_TABLE_SUPPORT ?= FALSE
OPT_A2DP_APP_DRCLIMITER_POWER ?= FALSE
OPT_A2DP_APP_SPEAKERPEQ_POWER ?= FALSE
SDK_MMI_TEST_SUPPORT ?= FALSE
VFS_TEST_CASE_SUPPORT ?= FALSE
SKIP_CALIBRATION_POINTS_CHECK ?= FALSE
CPU_FORCE_364MHZ_SUPPORT ?= FALSE
IQDUMP_FOR_SIMU_SUPPORT ?= FALSE
RADIO_LEGACY_ANALOG_SUPPORT ?= FALSE
LEGACY_KEYPAD_LIGHT_PATCH_SUPPORT ?= FALSE
LEGACY_AM_PATCH_SUPPORT ?= FALSE
LEGACY_VBUCK_CLOCK_PATCH_SUPPORT ?= FALSE
UNIT_TEST_APP_SUPPORT ?= FALSE
AUTO_TEST_SUPPORT ?= FALSE
DLM_SRVUT_SUPPORT ?= FALSE
DIAG_ERROR_SUPPORT ?= FALSE
SAVE_POOLSTATUS_MMI_SUPPORT ?= FALSE
CHECK_CPU_STATUS_BEFORE_SLEEP_SUPPORT ?= FALSE
MMI_NETWORK_SETTING_CUS_SUPPORT ?= FALSE
MMI_EM_AUDIO_APPTOSD_SUPPORT ?= FALSE
COMPATIBLE_CHIP_SUPPORT ?= FALSE

#===============================================================================
# ** Obsolete options **
#===============================================================================
TOUCH_SCREEN_SCALE_DOWN_SUPPORT ?= FALSE
MEMCARD_SUPPORT ?= TRUE
SMS_DISABLE_SIM_FOLDER_SUPPORT ?= FALSE
EMI_PAD_PWD_SUPPORT ?= FALSE

#-------------------------------------------------------------------------------
# From Options.mak
#-------------------------------------------------------------------------------
PP_OPT_COMMON += $(CHIP_TYPE)
PP_OPT_COMMON += __CHIP_STRING__="$(CHIP_TYPE)"

ifeq (32M, $(strip $(CHIP_EMBEDDED_RAM_SIZE)))
PP_OPT_COMMON += __EMBEDDED_RAM_32M__
endif

# NAND Flash support
ifeq (TRUE, $(strip $(CHIP_NAND)))
PP_OPT_COMMON += __NAND__
PP_OPT_COMMON += __NAND_DEBUG_CODE__
endif

ifneq (,$(strip $(CUS_FOLDER)))
PP_OPT_COMMON += $(CUS_FOLDER)
else
PP_OPT_COMMON += __CUS_DEFAULT__
endif

ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),__SMALL_ROM__)
ifeq (LOG_LEVEL_NO_TRACE, $(strip $(LOG_LEVEL_CUT_OPTION)))
PP_OPT_COMMON += __CRITICAL_TRACES_ONLY__  #System team's required identifier.
PP_OPT_COMMON += __NO_CRITICAL_TRACES__  #System team's required identifier.
else #else LOG_LEVEL_NO_TRACE
ifeq (LOG_LEVEL_CRITICAL_ONLY, $(strip $(LOG_LEVEL_CUT_OPTION)))
ifeq (1,$(CRITICAL_TRACE_OPTION))
PP_OPT_COMMON += __CRITICAL_TRACES_ONLY__  #System team's required identifier.
endif
else
ifeq (LOG_LEVEL_MMI_CUT_TRACE, $(strip $(LOG_LEVEL_CUT_OPTION)))
PP_OPT_COMMON += __LOG_LEVEL_MMI_CUT_TRACE__
else
ifeq (LOG_LEVEL_ALL, $(strip $(LOG_LEVEL_CUT_OPTION)))
PP_OPT_COMMON += __LOG_LEVEL_ALL__
else
#default
PP_OPT_COMMON += __LOG_LEVEL_ALL__
endif
endif
endif
endif #endif LOG_LEVEL_NO_TRACE
else
#default
PP_OPT_COMMON += __LOG_LEVEL_ALL__
endif

ifeq (TRUE, $(strip $(CORE_SOFTWARE)))
PP_OPT_COMMON += __CORE_SOFTWARE__
endif

# Feature_Name = Core Software Standalone mode
# Description = [DRV] Core Software Standalone mode
# Pre_Variable_True = CORE_SOFTWARE
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CORE_SOFTWARE)))
ifeq (TRUE, $(strip $(STANDALONE_MODE)))
PP_OPT_COMMON += __STANDALONE_MODE__
endif
endif

ifeq (TRUE, $(strip $(BRAVO_TARGET_EVB)))
PP_OPT_COMMON += __BRAVO_EVB__
endif

ifeq (TRUE, $(strip $(CAMERA_SUPPORT)))
PP_OPT_COMMON += __ENABLE_CAMERA__
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(CAMERA_PANORAMA_SUPPORT)))
PP_OPT_COMMON += __CAMERA_PANORAMA__
endif
endif
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(CAMERA_LOMO_SUPPORT)))
PP_OPT_COMMON += __CAMERA_LOMO__
endif
endif
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(CAMERA_MIRROR_SUPPORT)))
PP_OPT_COMMON += __CAMERA_MIRROR__
endif
endif
endif

ifneq (TRUE, $(strip $(CAMERA_SUPPORT)))
PP_OPT_COMMON += _DISABLE_CAMERA_
endif

ifneq (TRUE, $(strip $(CAPTURE_SUPPORT)))
PP_OPT_COMMON += __DISABLE_IMAGE_CAPTURE__
endif

ifeq (TRUE, $(strip $(CAMCORDER_SUPPORT)))
PP_OPT_COMMON += __ENABLE_CAMCORDER__
endif

ifneq (TRUE, $(strip $(CAMCORDER_SUPPORT)))
PP_OPT_COMMON +=  __DISABLE_VDR__
endif

ifneq ($(filter __ENABLE_CAMERA__ __ENABLE_CAMCORDER__, $(PP_OPT_COMMON)),)
ifeq (TRUE, $(strip $(DUAL_CAM_SUPPORT)))
PP_OPT_COMMON += __DUAL_CAM__
endif
endif

ifeq (TRUE, $(strip $(CHIP_WQVGA_RECORD_SUPPORTED)))
PP_OPT_COMMON += __MMI_WQVGA_RECORD_SUPPORT__
endif

ifeq (TRUE, $(strip $(CHIP_HVGA_RECORD_SUPPORTED)))
PP_OPT_COMMON += __MMI_HVGA_RECORD_SUPPORT__
endif

ifeq (TRUE, $(strip $(CHIP_AUTO_FOCUS_SUPPORTED)))
PP_OPT_COMMON += __MMI_AUTO_FOCUS_SUPPORT__
endif

ifeq (TRUE, $(strip $(MSTAR_CTA_SUPPORT)))
PP_OPT_COMMON += __MSTAR_CTA_VERSION__
endif

ifeq (TRUE, $(strip $(SDK_API_SUPPORT)))
PP_OPT_COMMON += __SDK_API__
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(SDK_API_WAP_MMS_ONLY_SUPPORT)))
PP_OPT_COMMON += __SDK_API_WAP_MMS_ONLY__
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(WAP_SUPPORT)))
PP_OPT_COMMON += __WAP__
endif
endif
endif

ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),)
ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(EMAIL_SUPPORT)))
PP_OPT_COMMON += __EMAIL_MMI__
endif
endif
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(MMS_SUPPORT)))
PP_OPT_COMMON += __MMS__
endif
endif
endif

ifeq (TRUE, $(strip $(MMI_VIEW_MSG_IN_OUTBOX_SUPPORT)))
PP_OPT_COMMON += __MMI_VIEW_MSG_IN_OUTBOX_SUPPORT__
endif

# Feature_Name = EMS Support (MMI)
# Description = Support Enhanced Messaging Service
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __EMS_MMI_SUPPORT__
endif

# Feature_Name = Smart Messaging Support (MMI)
# Description = Support Smart Messaging Service
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __SMART_MESSAGING_MMI_SUPPORT__
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (__JAVA_OAKMONT__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __JAVA_OAKMONT__
else
ifeq (__JAVA_OAKMONT_JAP0__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __JAVA_OAKMONT_JAP0__
else
ifeq (__JAVA_OAKMONT_JAP1_HI__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __JAVA_OAKMONT_JAP1_HI__
else
ifeq (__JAVA_OAKMONT_JAP2__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __JAVA_OAKMONT_JAP2__
else
ifeq (__JAVA_OAKMONT_JAP2C__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __JAVA_OAKMONT_JAP2C__
else
ifeq (__NCC_3RD_JAVA_PORTING_LAYER_S__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __NCC_3RD_JAVA_PORTING_LAYER__
PP_OPT_COMMON += __NCC_3RD_JAVA_PORTING_LAYER_S__
else
ifeq (__NCC_3RD_JAVA_PORTING_LAYER_M__, $(strip $(JAVA_SOLUTION)))
PP_OPT_COMMON += __NCC_3RD_JAVA_PORTING_LAYER__
PP_OPT_COMMON += __NCC_3RD_JAVA_PORTING_LAYER_M__
#PP_OPT_COMMON += __JAVA_LOW_MEM_CONCURRENT_HANDLE_MMI__
#PP_OPT_COMMON += __3RD_LOW_MEM_RELEASE_SUSPENDVIEW__
PP_OPT_COMMON += __APP_MMI_REDUCE_MEMORY_USAGE__
endif
endif
endif
endif
endif
endif
endif
endif
endif
endif

ifeq (G3D_SUPPORT, $(strip $(3D_SUPPORT)))
ifeq (TRUE, $(strip $(CHIP_G3D)))
PP_OPT_COMMON += __G3D__
endif
endif

# Description = [MMI] Option to enable 3D MGLS
#     Only support Portrait (QVGA, HVGA, WQVGA), and Landscape (QVGA, HVGA, WQVGA)
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (MGLS_SUPPORT, $(strip $(3D_SUPPORT)))
PP_OPT_COMMON += __FEATURE_MGLS__
endif
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifeq (__LCM_QVGA__, $(strip $(LCM_RESOLUTION)))
ifeq (TRUE, $(strip $(SKYENGINE_SUPPORT)))
PP_OPT_COMMON += __SKYENGINE__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_SKYENGINE__
endif
endif
endif
endif
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifeq (TRUE, $(strip $(SXMENGINE_SUPPORT)))
PP_OPT_COMMON += __SXMENGINE__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_SXMENGINE__
endif
endif
endif
endif
endif

# Feature_Name = ZMOL
# Description = Option for supporting zmol
# Pre_Condition_On = __SDK_API__
# Pre_Condition_Off = __MSTAR_CTA_VERSION__
# Option_Selection = N/A
ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifeq (TRUE, $(strip $(ZMOLENGINE_SUPPORT)))
PP_OPT_COMMON += __ZMOL__
#PP_OPT_COMMON += __ZM_QQ_BG_ONLINE__
#PP_OPT_COMMON += __ZM_MSTAR_PHONE_ADDR__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_ZMOLENGINE__
endif
endif
endif
endif
endif

# Feature_Name = ZYUE
# Description = Option for supporting zyue
# Pre_Condition_On = __SDK_API__
# Pre_Condition_Off = __MSTAR_CTA_VERSION__
# Option_Selection = N/A
ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifeq (TRUE, $(strip $(ZYUEENGINE_SUPPORT)))
PP_OPT_COMMON += __ZYUE_ENGINE__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_ZYUEENGINE__
endif
endif
endif
endif
endif
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(TTS_SUPPORT)))
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
PP_OPT_COMMON += __TTS__
endif
endif
endif

ifeq (TRUE, $(strip $(DUAL_BATTERY_SUPPORT)))
PP_OPT_COMMON += __DUAL_BATTERY__
ifeq (TRUE, $(strip $(DUAL_BATTERY_NO_ID_PIN_SUPPORT)))
PP_OPT_COMMON += __DUAL_BATTERY_NO_ID__
endif
endif

ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(BATTERY_ICON_SUPPORT)))
PP_OPT_COMMON += __MMI_BATTERY_ICON_DISPLAY__
endif
endif

ifeq (TRUE, $(strip $(SW_CHARGING_STOP_SUPPORT)))
PP_OPT_COMMON += __SW_STOP_CHARGING__
endif

ifeq (TRUE, $(strip $(CHIP_ADC_CALI_BY_EFUSE)))
PP_OPT_COMMON += __CHIP_ADC_CALI_BY_EFUSE__
ifeq (TRUE, $(strip $(ADC_CALI_BY_EFUSE_SUPPORT)))
PP_OPT_COMMON += __ADC_CALI_BY_EFUSE__
endif
endif

ifeq (TRUE, $(strip $(RTC_LOST_TIME_RECOVERY_SUPPORT)))
PP_OPT_COMMON += __RTC_LOST_TIME_RECOVERY__
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq (TRUE, $(strip $(GAME_ENGINE_EMU_SUPPORT)))
PP_OPT_COMMON += __GAME_ENGINE_EMU__
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq (TRUE, $(strip $(GAME_ENGINE_EMU_16BIT_SUPPORT)))
PP_OPT_COMMON += __GAME_ENGINE_EMU_16BIT__
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),)
ifeq (TRUE, $(strip $(CHIP_WLAN)))
ifeq (TRUE, $(strip $(CHIP_MPIF)))
ifeq (TRUE, $(strip $(WLAN_SUPPORT)))
PP_OPT_COMMON += __WLAN__
endif
endif
endif
endif
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifneq ($(filter CHIP_GPS_PIF CHIP_GPS_SPI, $(CHIP_GPS)),)
ifeq (TRUE, $(strip $(GPS_SUPPORT)))
PP_OPT_COMMON += __GPS__
endif
endif
endif
endif

#-------------------------------------------------------------------------------
# LCM, Panel, Boot Logo, Display related section
#-------------------------------------------------------------------------------

ifneq (,$(strip $(LCM_RESOLUTION)))
PP_OPT_COMMON += $(LCM_RESOLUTION)
endif

LCM_WIDTH	= 0
LCM_HEIGHT	= 0
SUB_LCM_WIDTH   = 0
SUB_LCM_HEIGHT  = 0

ifeq (__LCM_QVGA__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 240
LCM_HEIGHT	= 320
endif
ifeq (__LCM_WQVGA_240_400__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 240
LCM_HEIGHT	= 400
endif
ifeq (__LCM_QCIF_PLUS__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 176
LCM_HEIGHT	= 220
endif
ifeq (__LCM_HVGA_320_480__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 320
LCM_HEIGHT	= 480
endif
ifeq (__LCM_WVGA__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 480
LCM_HEIGHT	= 800
endif
ifeq (__LCM_LANDSCAPE_QVGA__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 320
LCM_HEIGHT	= 240
endif
ifeq (__LCM_LANDSCAPE_QCIF__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 220
LCM_HEIGHT	= 176
endif
ifeq (__LCM_LANDSCAPE_WQVGA_240_400__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 400
LCM_HEIGHT	= 240
endif
ifeq (__LCM_LANDSCAPE_HVGA__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 480
LCM_HEIGHT	= 320
endif
ifeq (__LCM_LANDSCAPE_WVGA__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH	= 800
LCM_HEIGHT	= 480
endif
ifeq (__LCM_QQVGA__, $(strip $(LCM_RESOLUTION)))
LCM_WIDTH = 128
LCM_HEIGHT = 160
endif


ifeq (TRUE, $(strip $(DUAL_LCD_SUPPORT)))
ifeq (__LCM_QVGA__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 240
SUB_LCM_HEIGHT	= 320
endif
ifeq (__LCM_WQVGA_240_400__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 240
SUB_LCM_HEIGHT	= 400
endif
ifeq (__LCM_QCIF_PLUS__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 176
SUB_LCM_HEIGHT	= 220
endif
ifeq (__LCM_HVGA_320_480__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 320
SUB_LCM_HEIGHT	= 480
endif
ifeq (__LCM_LANDSCAPE_QVGA__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 320
SUB_LCM_HEIGHT	= 240
endif
ifeq (__LCM_LANDSCAPE_QCIF__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 220
SUB_LCM_HEIGHT	= 176
endif
ifeq (__LCM_LANDSCAPE_WQVGA_240_400__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 400
SUB_LCM_HEIGHT	= 240
endif
ifeq (__LCM_LANDSCAPE_HVGA__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH	= 480
SUB_LCM_HEIGHT	= 320
endif
ifeq (__LCM_QQVGA__, $(strip $(LCM_SUB_RESOLUTION)))
SUB_LCM_WIDTH = 128
SUB_LCM_HEIGHT = 160
endif
endif

PP_OPT_COMMON += LCM_CONFIG_WIDTH=$(LCM_WIDTH)
PP_OPT_COMMON += LCM_CONFIG_HEIGHT=$(LCM_HEIGHT)

ifeq (,$(strip $(PANEL_PHYSICAL_WIDTH)))
PP_OPT_COMMON += __PANEL_DPM__=0
else
ifeq (0, $(strip $(PANEL_PHYSICAL_WIDTH)))
PP_OPT_COMMON += __PANEL_DPM__=0
else
PP_OPT_COMMON += __PANEL_DPM__=$(LCM_WIDTH)*1000*100/$(PANEL_PHYSICAL_WIDTH)
endif
endif

ifeq (__PNG__, $(strip $(BOOTUP_LOGO_TYPE)))
PP_OPT_COMMON += __PNG_BOOTUP_LOGO__
endif

ifeq (__BMP__, $(strip $(BOOTUP_LOGO_TYPE)))
PP_OPT_COMMON += __BMP_BOOTUP_LOGO__
endif

ifeq (__CUS_BMP__, $(strip $(BOOTUP_LOGO_TYPE)))
PP_OPT_COMMON += __CUS_BOOTUP_LOGO__
PP_OPT_COMMON += __BMP_BOOTUP_LOGO__
endif

ifeq (__CUS_PNG__, $(strip $(BOOTUP_LOGO_TYPE)))
PP_OPT_COMMON += __CUS_BOOTUP_LOGO__
PP_OPT_COMMON += __PNG_BOOTUP_LOGO__
endif

ifneq (0, $(strip $(LCM_ROTATE_DIRECTION_CCW)))
PP_OPT_COMMON += __LCM_ROTATE__
endif

ifeq (TRUE, $(strip $(QWERTY_KEYPAD_SUPPORT)))
PP_OPT_COMMON += __QWERTY_KEYPAD__
endif

# Feature_Name = Clock source select for MIU
# Description = switch MIU clock src for RF sensitivity
# Pre_Condition_On = VLCM can always on
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(MIU_CLK_SRV_APLL)))
PP_OPT_COMMON += __MIU_USE_APLL__
endif

ifneq (,$(strip $(TOUCH_SCREEN_DRIVER_SELECT)))
PP_OPT_COMMON += __TOUCH_SCREEN__
PP_OPT_COMMON += $(TOUCH_SCREEN_DRIVER_SELECT)
ifeq ($(filter __R_C_COEXIST__, $(TOUCH_SCREEN_DRIVER_SELECT)), __R_C_COEXIST__)
PP_OPT_COMMON += __TOUCH_SCREEN_R_C_COEXIST_DRV__
PP_OPT_COMMON += __TOUCH_SCREEN_FWUPDATE_MMI__
PP_OPT_COMMON += __MULTI_TOUCH__
ifeq (__90_ANGLE__, $(strip $(TOUCH_SCREEN_ANGLE_SELECT)))
PP_OPT_COMMON += __COORDINATE_SHIFT_90_ANGLE__
endif
ifeq (__180_ANGLE__, $(strip $(TOUCH_SCREEN_ANGLE_SELECT)))
PP_OPT_COMMON += __COORDINATE_SHIFT_180_ANGLE__
endif
ifeq (__270_ANGLE__, $(strip $(TOUCH_SCREEN_ANGLE_SELECT)))
PP_OPT_COMMON += __COORDINATE_SHIFT_270_ANGLE__
endif
else
ifneq ($(filter __R_MSTAR__, $(TOUCH_SCREEN_DRIVER_SELECT)), __R_MSTAR__)
PP_OPT_COMMON += __TOUCH_SCREEN_C_DRV__
PP_OPT_COMMON += __TOUCH_SCREEN_FWUPDATE_MMI__
PP_OPT_COMMON += __MULTI_TOUCH__
ifeq (__90_ANGLE__, $(strip $(TOUCH_SCREEN_ANGLE_SELECT)))
PP_OPT_COMMON += __COORDINATE_SHIFT_90_ANGLE__
endif
ifeq (__180_ANGLE__, $(strip $(TOUCH_SCREEN_ANGLE_SELECT)))
PP_OPT_COMMON += __COORDINATE_SHIFT_180_ANGLE__
endif
ifeq (__270_ANGLE__, $(strip $(TOUCH_SCREEN_ANGLE_SELECT)))
PP_OPT_COMMON += __COORDINATE_SHIFT_270_ANGLE__
endif
endif # __R_MSTAR__
endif # __R_C_COEXIST__
endif # TOUCH_SCREEN_DRIVER_SELECT

ifeq ($(filter __R_MSTAR__, $(TOUCH_SCREEN_DRIVER_SELECT)), __R_MSTAR__)
ifeq (TRUE, $(strip $(TOUCH_SCREEN_SLIM_SUPPORT)))
PP_OPT_COMMON +=  __MULTI_TOUCH_SLIM__
endif
endif

# Feature_Name = Touch Screen Interrupt Mode Select
# Description = If this option is set, touch screen ADC notify cpu by interrupt.
#           This also can alleviate touch screen jitter or smoothen the line.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(__R_MSTAR__), TOUCH_SCREEN_DRIVER_SELECT(__R_C_COEXIST__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifneq (,$(strip $(TOUCH_SCREEN_DRIVER_SELECT)))
ifneq ($(filter __R_MSTAR__ __R_C_COEXIST__, $(TOUCH_SCREEN_DRIVER_SELECT)),)
ifeq (TRUE, $(strip $(TOUCH_SCREEN_ADC_INTERRUPT_SUPPORT)))
PP_OPT_COMMON += __TSI_INTERRUPT_MODE_SUPPORT__
endif # TOUCH_SCREEN_ADC_INTERRUPT_SUPPORT
endif # TOUCH_SCREEN_DRIVER_SELECT: __R_MSTAR__ & __R_C_COEXIST__
endif # TOUCH_SCREEN_DRIVER_SELECT

# Feature_Name = Touch Screen synamic report rate mode
# Description = If this option is set, c-type touch screen could support dynamic report rate, and MMI could configure it by diffrent application.
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT(__CUST_CTP__), TOUCH_SCREEN_DRIVER_SELECT(__R_C_COEXIST__)
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifneq (,$(strip $(TOUCH_SCREEN_DRIVER_SELECT)))
ifneq ($(filter __CUST_CTP__ __R_C_COEXIST__, $(TOUCH_SCREEN_DRIVER_SELECT)),)
ifeq (TRUE, $(strip $(TOUCH_SCREEN_DYNAMIC_REPORT_RATE_SUPPORT)))
PP_OPT_COMMON += __DYNAMIC_REPORT_RATE_SUPPORT__
endif # TOUCH_SCREEN_DYNAMIC_REPORT_RATE_SUPPORT
endif # TOUCH_SCREEN_DRIVER_SELECT: __CUST_CTP__ & __R_C_COEXIST__
endif # TOUCH_SCREEN_DRIVER_SELECT

ifeq (TRUE, $(strip $(HALL_SWITCH_SUPPORT)))
PP_OPT_COMMON += __HALL_SWITCH__
ifneq (,$(strip $(HALL_SWITCH_BEHAVIOR)))
PP_OPT_COMMON += $(HALL_SWITCH_BEHAVIOR)
endif
endif

# Feature_Name = select hall switch behavior for open/slide
# Description = select hall switch behavior for open/slide
#           set hall switch status high as open or low as open
# Pre_Condition_On = __HALL_SWITCH__
# Pre_Condition_Off = N/A
ifeq (TRUE, $(strip $(HALL_SWITCH_SUPPORT)))
ifeq (__HIGH_OPEN__, $(strip $(HALL_SWITCH_POLARITY)))
PP_OPT_COMMON += __HALL_SWITCH_POLARITY_REVERSE__
endif
endif

ifneq (,$(strip $(FLASHLIGHT_CTRL_METHOD)))
PP_OPT_COMMON += __FLASHLIGHT__
PP_OPT_COMMON += $(FLASHLIGHT_CTRL_METHOD)
endif

ifeq (TRUE, $(strip $(FILLLIGHT_SUPPORT)))
PP_OPT_COMMON += __FILLLIGHT__
endif

ifneq (,$(strip $(BREATHLIGHT)))
PP_OPT_COMMON += __BREATHLIGHT__
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq (TRUE, $(strip $(DUAL_IMEI_SUPPORT)))
PP_OPT_COMMON += __DUAL_IMEI__
endif
endif

ifeq (TRUE, $(strip $(CAMERA_MOTION_DETECT_SUPPORT)))
ifneq ($(filter __ENABLE_CAMERA__ __ENABLE_CAMCORDER__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __CAMERA_MOTION_DETECT__
endif
endif

ifeq (TRUE, $(strip $(LANTERN_BY_AUDIO_SUPPORT)))
PP_OPT_COMMON += __LANTERN_BY_AUDIO__
endif

ifeq (TRUE, $(strip $(CLKGEN_NEWCODEGEN_2_SUPPORT)))
PP_OPT_COMMON += NEWCODEGEN_2
endif

ifeq (__35MM_HEADSET__, $(strip $(HEADSET_TYPE)))
PP_OPT_COMMON += __MIC_IN_CHANGED_TO_HANDSET_IF_3_SEGMENT_HEADSET__
PP_OPT_COMMON += __HOOKKEY_DEBOUNCE_TIMER__
PP_OPT_COMMON += __HOOKKEY_FAKE_KEY_TIMER__
ifneq (,$(strip $(HEADSET_DETECTOR_SUPPORT)))
PP_OPT_COMMON += $(HEADSET_DETECTOR_SUPPORT)
else
PP_OPT_COMMON += __SPK_DETECTOR_DRV__
endif
ifeq (TRUE, $(strip $(HOOKKEY_POLLING_SUPPORT)))
PP_OPT_COMMON += __HOOKKEY_POLLING_ENABLE__
endif
endif

ifeq (__USB_HEADSET__, $(strip $(HEADSET_TYPE)))
PP_OPT_COMMON += __HOOKKEY_FAKE_KEY_TIMER__
endif

ifeq (TRUE, $(strip $(SPEAKER_RECEIVER_MIX_SUPPORT)))
PP_OPT_COMMON += __SPK_RECEIVER_MIX_DRV__
endif

ifneq (,$(strip $(BACKLIGHT)))
PP_OPT_COMMON += __BACKLIGHT_DRV__
endif

ifneq (,$(strip $(BACKLIGHT_CTRL)))
PP_OPT_COMMON += $(BACKLIGHT_CTRL)
ifneq ($(filter __BACKLIGHT_DRV_FT3356Q__ __BACKLIGHT_DRV_RT9368A__ __BACKLIGHT_DRV_RP1364A__ __BACKLIGHT_DRV_AAT3194__ __BACKLIGHT_DRV_RT9364__ __BACKLIGHT_DRV_RT9379__, $(BACKLIGHT_CTRL)),)
PP_OPT_COMMON += __BACKLIGHT_CTRL_BY_GPIO__
else
ifeq (__BACKLIGHT_DRV_RT9284A__, $(strip $(BACKLIGHT_CTRL)))
PP_OPT_COMMON += __BACKLIGHT_CTRL_BY_PWM__
endif
endif
endif

ifneq ($(filter wled_embedded, $(BACKLIGHT)), )
ifeq (TRUE, $(strip $(BACKLIGHT_WLED_LDO_SWITCH_SUPPORT)))
PP_OPT_COMMON += __BACKLIGHT_WLED_LDO_SWITCH__
endif
endif

ifneq (,$(strip $(PSENSOR)))
PP_OPT_COMMON += __PROXIMITY_SENSOR_MMI__
PP_OPT_COMMON += __PROXIMITY_SENSOR_DRV__
endif

ifneq (,$(strip $(SUBBACKLIGHT)))
PP_OPT_COMMON += __SUBBACKLIGHT_MMI__
PP_OPT_COMMON += __SUBBACKLIGHT_DRV__
endif

ifneq (,$(strip $(EXT_AUDIO_OPAMP)))
PP_OPT_COMMON += $(EXT_AUDIO_OPAMP)
endif

ifneq (,$(strip $(EXT_AUDIO_CODEC_SOLUTION)))
ifeq (TRUE, $(strip $(CHIP_AUDIO_EXT_CODEC)))
PP_OPT_COMMON += __EXT_AUDIO_CODEC_DRV__
PP_OPT_COMMON += $(EXT_AUDIO_CODEC_SOLUTION)
endif
endif

ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(TOUCH_SCREEN_SCALE_DOWN_SUPPORT)))
PP_OPT_COMMON += __TPL_SCALE_DOWN_DRV__
endif
endif

ifeq (TRUE, $(strip $(LCD_PANEL_DETECT_BY_ADC_SUPPORT)))
PP_OPT_COMMON += __LCD_PANEL_DETECT_BY_ADC_DRV__
endif

ifeq (TRUE, $(strip $(DUAL_LCD_SUPPORT)))
PP_OPT_COMMON += __DUAL_LCD__
endif

ifneq (, $(strip $(OFN)))
PP_OPT_COMMON += __OFN_DRV__
endif

ifeq ($(filter __OFN_DRV__, $(PP_OPT_COMMON)), __OFN_DRV__)
ifeq (TRUE, $(strip $(OFN_DRV_GPIO_SIMU_I2C)))
PP_OPT_COMMON += __OFN_DRV_GPIO_SIMU_I2C__
endif
ifeq (TRUE, $(strip $(OFN_POWER_BY_LDO)))
PP_OPT_COMMON += __OFN_POWER_BY_LDO__
endif
ifeq (TRUE, $(strip $(OFN_REMAPPING_P2L)))
PP_OPT_COMMON += __DRV_OFN_REMAPPING_P2L__
endif
endif

# Feature_Name = Numonyx M18 MCP Support
# Description = Option to support numonyx M18 MCP
# Pre_Variable_True = N/A
# Pre_Variable_False = __NAND__
# Option_Selection = TRUE, FALSE
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq (TRUE, $(strip $(M18_MCP_SUPPORT)))
PP_OPT_COMMON += __M18_MCP_SUPPORT__
endif
endif

ifeq (TRUE, $(strip $(SKIP_LOGO_WHEN_POWER_ON_CHARGER_SUPPORT)))
PP_OPT_COMMON += __SKIP_LOGO_WHEN_POWER_ON_CHARGER__
endif

ifeq (TRUE, $(strip $(CUS_LCM_TABLE_SUPPORT)))
PP_OPT_COMMON += __CUS_LCM_TABLE_DRV__
endif

ifeq (TRUE, $(strip $(CUS_DISPLAY_TABLE_SUPPORT)))
PP_OPT_COMMON += __CUS_DISPLAY_TABLE_DRV__
endif

ifeq (TRUE, $(strip $(BOOTUP_LOGO_BY_E2P_SUPPORT)))
PP_OPT_COMMON += __BOOTUP_LOGO_BY_E2P__
endif

ifeq (TRUE, $(strip $(FMS_E2P_ON_RAI_SUPPORT)))
PP_OPT_COMMON += __FMS_E2P_ON_RAI__
endif

ifeq (TRUE, $(strip $(HALL_BALL_SUPPORT)))
PP_OPT_COMMON += __BALL_DRV__
endif

ifeq (TRUE, $(strip $(POWERON_ANIM_DONT_WAIT_MELODY_SUPPORT)))
PP_OPT_COMMON += __ONAPP_POWERON_ANIM_DONT_WAIT_MELODY__
endif

ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(TOUCH_HOTKEY_SUPPORT)))
PP_OPT_COMMON += __TOUCH_HOTKEY__
endif
endif

ifeq (TRUE, $(strip $(KING_MOVIE_SUPPORT)))
PP_OPT_COMMON += __MMI_KING_MOVIE__
PP_OPT_COMMON += __MDL_KING_MOVIE__
ifeq (TRUE, $(strip $(KING_MOVIE_3D_SUPPORT)))
ifeq (TRUE, $(strip $(INDEPENDENT_KING_MOVIE_3D_SUPPORT)))
PP_OPT_COMMON += __MMI_KING_MOVIE_3D_APP_INDIE__
endif
PP_OPT_COMMON += __MMI_KING_MOVIE_3D__
PP_OPT_COMMON += __MDL_KING_MOVIE_3D__
endif
endif

# Feature_Name = STEREO EFFECT
# Description = Option to enable video/picture stereo effect
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(STEREO_VIDEO_SUPPORT)))
PP_OPT_COMMON += __MDL_STEREO_VIDEO__
PP_OPT_COMMON += __MMI_STEREO_VIDEO__
endif

ifeq (TRUE, $(strip $(STEREO_IMAGE_SUPPORT)))
PP_OPT_COMMON += __MDL_STEREO_IMAGE__
PP_OPT_COMMON += __MMI_STEREO_IMAGE__
endif

ifeq (TRUE, $(strip $(RMVB_SUPPORT)))
PP_OPT_COMMON += __MDL_RMVB__
PP_OPT_COMMON += ENABLE_COOK_DEC
endif

ifeq (TRUE, $(strip $(AVI_SUPPORT)))
PP_OPT_COMMON += __MDL_AVI__
endif

ifeq (TRUE, $(strip $(FLV_SUPPORT)))
PP_OPT_COMMON += __MDL_FLV__
endif

ifeq (TRUE, $(strip $(PS_SUPPORT)))
PP_OPT_COMMON += __MDL_PS__
endif

ifeq (TRUE, $(strip $(TS_SUPPORT)))
PP_OPT_COMMON += __MDL_TS__
endif

ifeq (TRUE, $(strip $(MKV_SUPPORT)))
PP_OPT_COMMON += __MDL_MKV__
endif

ifeq (TRUE, $(strip $(SW_DITHER_SUPPORT)))
PP_OPT_COMMON += __IMGCODEC_ENABLE_SW_DITHER__
endif

ifneq (TRUE, $(strip $(WBMP_SUPPORT)))
PP_OPT_COMMON += __MDL_DISABLE_WBMP__
endif

ifeq (TRUE, $(strip $(IP_CALL_SUPPORT)))
PP_OPT_COMMON += __IP_CALL_MMI__
endif

ifeq (TRUE, $(strip $(AUTO_ANSWER_SUPPORT)))
PP_OPT_COMMON += __AUTO_ANSWER_MMI__
endif

ifeq (TRUE, $(strip $(ANSWER_INDICATOR_SUPPORT)))
PP_OPT_COMMON += __ANSWER_INDICATOR_MMI__
endif

ifeq (TRUE, $(strip $(PLAYLIST_COVER_SUPPORT)))
PP_OPT_COMMON += __PLAYLIST_COVER_MMI__
endif

ifeq (TRUE, $(strip $(CASHORGANIZER_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_CASHORGANIZER__
endif

ifeq (TRUE, $(strip $(NOTEPAD_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_NOTEPAD__
endif

ifeq (TRUE, $(strip $(SHORTCUTLIST_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_SHORTCUT__
endif

ifeq (TRUE, $(strip $(TODOLIST_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_TODOLIST__
endif

ifeq (TRUE, $(strip $(TODOLIST_SUPPORT)))
ifeq (TRUE, $(strip $(TODOLIST_SYNC_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_TODOLIST_SYNC__
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(CALL_FIREWALL)))
PP_OPT_COMMON += __MMI_CALL_FIREWALL__
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(TODOLIST_SUPPORT)))
ifeq (TRUE, $(strip $(TODOLIST_VTODO_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_TODOLIST_VTODO__
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_QCIF_PLUS__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_QCIF__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__, $(LCM_RESOLUTION)),)
ifeq (TRUE, $(strip $(FRUITGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_FRUIT__
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_QCIF_PLUS__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_QCIF__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__, $(LCM_RESOLUTION)),)
ifeq (TRUE, $(strip $(PACMANGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_PACMAN__
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_QCIF_PLUS__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_QCIF__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__, $(LCM_RESOLUTION)),)
ifeq (TRUE, $(strip $(BIG2GAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_BIG2__
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_HVGA_320_480__ __LCM_LANDSCAPE_HVGA__ __LCM_WQVGA_240_400__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_QVGA__ __LCM_LANDSCAPE_QVGA__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__, $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(PUZZLEGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_PUZZLE__
endif
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_HVGA_320_480__ __LCM_WQVGA_240_400__ __LCM_QVGA__ __LCM_WVGA__ , $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(LINKUPGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_LINKUP__
endif
endif
endif
endif

ifeq (TRUE, $(strip $(SOKOBANGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_SOKOBAN__
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_HVGA_320_480__ __LCM_WQVGA_240_400__ __LCM_QVGA__ __LCM_WVGA__ , $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(SUDOKUGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_SUDOKU__
endif
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_HVGA_320_480__ __LCM_WQVGA_240_400__ __LCM_QVGA__ __LCM_WVGA__ , $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(HAMSTERFIGHTGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_HAMSTERFIGHT__
endif
endif
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_HVGA_320_480__ __LCM_LANDSCAPE_HVGA__ __LCM_WQVGA_240_400__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_QVGA__ __LCM_LANDSCAPE_QVGA__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__, $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(GOBANGGAME_SUPPORT)))
PP_OPT_COMMON += __NATIVE_GAME_MMI_GOBANG__
endif
endif
endif
endif

ifeq (TRUE, $(strip $(BMI_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_BMI__
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(OMA_DRM_V1_SUPPORT)))
PP_OPT_COMMON += __MMI_OMA_DRM_V1__
PP_OPT_COMMON += __MDL_OMA_DRM_V1__
PP_OPT_COMMON += __APP_MMI_LICENSEMGR__
PP_OPT_COMMON += DB_USING_OMA_DOWNLOAD
endif
endif
endif

ifeq (TRUE, $(strip $(CALLER_LOCATION_SUPPORT)))
PP_OPT_COMMON += __CALLER_LOCATION__
endif

ifeq (TRUE, $(strip $(CALLER_LOCATION_SUPPORT)))
ifeq (TRUE, $(strip $(CALLER_LOCATION_USE_STATIC_DB)))
ifeq ($(filter __CUS_2__, $(PP_OPT_COMMON)), __CUS_2__)
PP_OPT_COMMON += __CALLER_LOCATION_USE_STATIC_DB__
endif
endif
endif

ifeq (TRUE, $(strip $(POWER_SAVING_PROFILE_MMI_SUPPORT)))
PP_OPT_COMMON += __POWER_SAVING_PROFILE_MMI__
endif


ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(POWERONOFF_USER_DEFINED_VIDEO_SUPPORT)))
PP_OPT_COMMON += __USER_DEFINE_POWERONOFF_VIDEO__
endif
endif

ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(POWERONOFF_USER_DEFINED_ANIM_SUPPORT)))
PP_OPT_COMMON += __USER_DEFINE_POWERONOFF_ANIM__
endif
endif

ifeq (TRUE, $(strip $(POWERONOFF_USER_DEFINED_RINGTONE_SUPPORT)))
PP_OPT_COMMON += __USER_DEFINE_POWERONOFF_MELODY__
endif

ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq (TRUE, $(strip $(VIDEO_WALLPAPER_SUPPORT)))
ifeq (FALSE, $(strip $(UI_STYLE_MMI_ANDROID_IDLE_SUPPORT)))
ifeq (FALSE, $(strip $(UI_STYLE_MMI_STYLE_SWITCH_SUPPORT)))
PP_OPT_COMMON += __VIDEO_WALLPAPER__
endif
endif
endif
endif

ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq (TRUE, $(strip $(MAINMENU_VIDEO_SUPPORT)))
ifeq (FALSE, $(strip $(UI_STYLE_MMI_ANDROID_MAIN_MENU_SUPPORT)))
ifeq (FALSE, $(strip $(UI_STYLE_MMI_STYLE_SWITCH_SUPPORT)))
PP_OPT_COMMON += __USER_DEFINE_MAINMENU_VIDEO__
endif
endif
endif
endif

ifeq (TRUE, $(strip $(NOSIM_CAMP_ON_TEST_NETWORK_SUPPORT)))
PP_OPT_COMMON += __NOSIM_CAMP_ON_TEST_NETWORK__
endif

# Feature_Name = Video Player fast forward & fast rewind Enable
# Description = Option to support fast forward and fast rewind feature in video player
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __VIDEOPLAYERAPP_FFREWIND_SUPPORT__
endif

ifeq (TRUE, $(strip $(PRIVATEPROTECT_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_PRIVATEPROTECT__
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq (TRUE, $(strip $(FM_RADIO_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_FM_RADIO__
ifeq (TRUE, $(strip $(FM_RADIO_RECORD_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_FM_RADIO_REC__
endif
ifeq (TRUE, $(strip $(FM_RADIO_SCHEDULE_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_FM_SCHEDULE__
endif
endif
endif

ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(SKETCHNOTE_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_SKETCHNOTE__
endif
endif

ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(SKIP_CALIBRATION_POINTS_CHECK)))
PP_OPT_COMMON += __APP_MMI_CALIBRATION_SKIP_POINTS_CHECK__
endif
endif

ifeq (TRUE, $(strip $(SHORTCUTLIST_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_SHORTCUTLIST__
endif

ifeq (TRUE, $(strip $(UNITCONVERTER_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_UNITCONVERTER__
endif

ifeq (TRUE, $(strip $(EVENTCENTER_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_EVENTCENTER__
endif

ifeq (TRUE, $(strip $(VOICE_MEMO_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_VOICE_MEMO__
endif

ifeq (TRUE, $(strip $(CALENDAR_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_CALENDAR__
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __CALENDARAPP_SEARCH_MMI__
PP_OPT_COMMON += __SEARCHAPP_SEARCH_CALENDAR_MMI__
PP_OPT_COMMON += __CALENDAR_EXPORT_VCS_MMI__
PP_OPT_COMMON += __CALENDAR_IMPORT_VCS_MMI__
ifneq ($(filter __CALENDARAPP_SEARCH_MMI__ __SEARCHAPP_SEARCH_CALENDAR_MMI__ , $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __EVENTDB_SEARCH_MMI__
endif
ifneq ($(filter __CALENDAR_IMPORT_VCS_MMI__ __CALENDAR_EXPORT_VCS_MMI__ , $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __CALENDAR_SUPPORT_VCS_MMI__
endif
endif
endif

# Feature_Name = Indian Calendar
# Description = Option to enable Indian Calendar
# Pre_Variable_True = CALENDAR_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(CALENDAR_SUPPORT)))
ifeq (TRUE, $(strip $(INDIAN_CALENDAR_SUPPORT)))
PP_OPT_COMMON += __INDIAN_CALENDAR__
endif
endif

ifeq (TRUE, $(strip $(CALENDAR_SUPPORT)))
ifeq (TRUE, $(strip $(CALENDAR_SMALL_DESCRIPTION_SUPPORT)))
PP_OPT_COMMON += __CALENDAR_SMALL_DESCRIPTION__
endif
endif

# Description = [MMI] Support NtpApp
# Pre_Condition_On = NTP_SUPPORT
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(NTP_SUPPORT)))
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __APP_MMI_NTP__
endif
endif


ifeq (TRUE, $(strip $(SMALL_PHB_SUPPORT)))
PP_OPT_COMMON += __SMALL_PHB_MMI__
endif

ifeq (TRUE, $(strip $(PHBAP_DISABLE_GROUP)))
PP_OPT_COMMON += __MMI_PHBAP_DISABLE_GROUP__
endif

ifeq (TRUE, $(strip $(SELECT_BK_FROM_PHB_SUPPORT)))
PP_OPT_COMMON += __PHB_SELECT_BK_FROM_PHB__
endif

ifeq (TRUE, $(strip $(PHB_DEFAULT_GROUP_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_PHB_DEFAULT_GROUP__
endif

ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __FDN_MMI__
endif

ifeq (TRUE, $(strip $(CALLLOG_SELECT_DISPLAY_SIM_SUPPORT)))
PP_OPT_COMMON += __CALLLOG_SELECT_DISPLAY_SIM__
endif

ifeq (TRUE, $(strip $(PHB_ALL_TAB_SUPPORT)))
PP_OPT_COMMON += __MMI_PHBAP_ALL_TAB__
endif

ifeq (TRUE, $(strip $(STOPWATCH_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_STOPWATCH__
endif

ifeq (TRUE, $(strip $(COUNTDOWN_TIMER_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_COUNTDOWN_TIMER__
endif

# Feature_Name = search app
# Description = Option to enable search app
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(MMI_SEARCH_APP_SUPPORT)))
PP_OPT_COMMON += __MMI_SEARCH_APP__
endif

# Description = [MMI] Option to enable Group Widget
#     Only support Portrait (QVGA, HVGA, WQVGA), and Landscape (QVGA, HVGA, WQVGA)
# Pre_Condition_On = __TOUCH_SCREEN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(MMI_GROUP_APP_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_GROUP_APP__
endif
endif
endif

# Description = [MMI] Support style switch
# Pre_Condition_On = __TOUCH_SCREEN__, and (__LCM_QVGA__ or __LCM_HVGA_320_480__ or __LCM_WQVGA_240_400__)
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_WVGA__, $(LCM_RESOLUTION)),)

ifeq (TRUE, $(strip $(UI_STYLE_MMI_STYLE_SWITCH_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_STYLE_SWITCH__
endif

endif
endif
endif

# Description = [MMI] Option to enable Blue Dialer Style
#     Only support Portrait (QVGA, HVGA, WQVGA), and Landscape (QVGA, HVGA, WQVGA)
# Pre_Condition_On = __TOUCH_SCREEN__
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(MMI_BLUE_DIALER_APP_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_BLUE_DIALER_APP__
endif
endif
endif
endif

# Description = [MMI] Support the display of Android Style
# Pre_Condition_On = __TOUCH_SCREEN__, and (__LCM_QVGA__ or __LCM_HVGA_320_480__ or __LCM_WQVGA_240_400__)
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_WVGA__, $(LCM_RESOLUTION)),)

ifeq (TRUE, $(strip $(UI_STYLE_MMI_ANDROID_4_0_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_4_0__

PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE__
PP_OPT_COMMON += __UI_STYLE_FLIPDCLOCK__
PP_OPT_COMMON += __GADGETS_MMI__
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_4_0_GADGET__

PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_MAIN_MENU__

PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_KEYGUARD__
PP_OPT_COMMON += __MMI_BALLSLIDE_WDG_SUPPORT__
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __ANDROID_4_0_KEYGUARD_SAVE_MEMORY__
endif

else ifeq ($(filter __UI_STYLE_MMI_STYLE_SWITCH__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_STYLE_SWITCH__)
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_4_0__
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE__
PP_OPT_COMMON += __UI_STYLE_FLIPDCLOCK__
PP_OPT_COMMON += __GADGETS_MMI__
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_4_0_GADGET__

PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_MAIN_MENU__

PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_KEYGUARD__
PP_OPT_COMMON += __MMI_BALLSLIDE_WDG_SUPPORT__
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __ANDROID_4_0_KEYGUARD_SAVE_MEMORY__
endif
else

ifeq (TRUE, $(strip $(UI_STYLE_MMI_ANDROID_MAIN_MENU_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_MAIN_MENU__
endif
ifeq (TRUE, $(strip $(UI_STYLE_MMI_ANDROID_KEYGUARD_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_KEYGUARD__
endif
ifeq (TRUE, $(strip $(UI_STYLE_MMI_ANDROID_IDLE_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE__
PP_OPT_COMMON += __UI_STYLE_FLIPDCLOCK__
PP_OPT_COMMON += __GADGETS_MMI__
endif

endif

ifeq ($(filter __UI_STYLE_MMI_ANDROID_IDLE__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_ANDROID_IDLE__)
ifneq ($(filter __UI_STYLE_MMI_ANDROID_MAIN_MENU__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_ANDROID_MAIN_MENU__)
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_MAIN_MENU__
endif
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE_ENABLE_PREVIEW__
else
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE_DESKTOP_LIMIT__
endif
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE_DRAG_WITH_MASK__
ifeq (TRUE, $(strip $(UI_STYLE_MMI_ANDROID_IDLE_MUTEX_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_ANDROID_IDLE_MUTEX__
endif
endif

endif
endif
endif

ifneq (,$(strip $(CAMERA_PRI_UI_LAYOUT)))
ifneq ($(filter __ENABLE_CAMERA__ __ENABLE_CAMCORDER__, $(PP_OPT_COMMON)),)
ifeq (__CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__, $(strip $(CAMERA_PRI_UI_LAYOUT)))
PP_OPT_COMMON += __CAMERA_PRI_LAYOUT_PORTRAIT_ONLY_MMI__
PP_OPT_COMMON += __SENSOR_PRI_LAYOUT_PORTRAIT__
else
ifeq (__CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__, $(strip $(CAMERA_PRI_UI_LAYOUT)))
PP_OPT_COMMON += __CAMERA_PRI_LAYOUT_LANDSCAPE_ONLY_MMI__
PP_OPT_COMMON += __SENSOR_PRI_LAYOUT_LANDSCAPE__
else
PP_OPT_COMMON += __CAMERA_PRI_LAYOUT_CUSTOMIZATION_MMI__
PP_OPT_COMMON += __SENSOR_PRI_LAYOUT_LANDSCAPE__
endif
endif
endif
endif

ifneq (,$(strip $(CAMERA_SEC_UI_LAYOUT)))
ifeq (TRUE, $(strip $(DUAL_CAM_SUPPORT)))
ifneq ($(filter __ENABLE_CAMERA__ __ENABLE_CAMCORDER__, $(PP_OPT_COMMON)),)
ifeq (__CAMERA_LAYOUT_PORTRAIT_ONLY_MMI__, $(strip $(CAMERA_SEC_UI_LAYOUT)))
PP_OPT_COMMON += __CAMERA_SEC_LAYOUT_PORTRAIT_ONLY_MMI__
PP_OPT_COMMON += __SENSOR_SEC_LAYOUT_PORTRAIT__
else
ifeq (__CAMERA_LAYOUT_LANDSCAPE_ONLY_MMI__, $(strip $(CAMERA_SEC_UI_LAYOUT)))
PP_OPT_COMMON += __CAMERA_SEC_LAYOUT_LANDSCAPE_ONLY_MMI__
PP_OPT_COMMON += __SENSOR_SEC_LAYOUT_LANDSCAPE__
else
PP_OPT_COMMON += __CAMERA_SEC_LAYOUT_CUSTOMIZATION_MMI__
PP_OPT_COMMON += __SENSOR_SEC_LAYOUT_LANDSCAPE__
endif
endif
endif
endif
endif

ifneq ($(filter __ENABLE_CAMERA__ __ENABLE_CAMCORDER__, $(PP_OPT_COMMON)),)
ifeq (TRUE, $(strip $(CAMERA_USE_PHONE_STORAGE_SUPPORT)))
ifneq (TRUE, $(strip $(ONBOARD_USER_STORAGE_SUPPORT)))
PP_OPT_COMMON += __CAMERA_MMI_USE_PHONE_STORAGE__
endif
endif
endif

ifeq (TRUE, $(strip $(CAMERA_SUPPORT)))
ifeq (TRUE, $(strip $(CAMERA_STICKER_SUPPORT)))
PP_OPT_COMMON += __CAMERA_STICKER_MMI__
endif
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(CAMERA_PANORAMA_SUPPORT)))
PP_OPT_COMMON += __CAMERA_PANORAMA_MMI__
endif
endif
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(CAMERA_MIRROR_SUPPORT)))
PP_OPT_COMMON += __CAMERA_MIRROR_MMI__
endif
endif
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(CAMERA_LOMO_SUPPORT)))
PP_OPT_COMMON += __CAMERA_LOMO_MMI__
endif
endif
endif

ifeq (TRUE, $(strip $(DUAL_CHARGER_SUPPORT)))
PP_OPT_COMMON += __DUAL_CHARGER_MMI__
endif

ifeq (TRUE, $(strip $(BAND_SELECTION_SUPPORT)))
PP_OPT_COMMON += __BAND_SELECTION_MMI__
endif

ifeq ($(filter __DUAL_IMEI__, $(PP_OPT_COMMON)), __DUAL_IMEI__)
ifeq (TRUE, $(strip $(DUAL_IMEI_MMI_SUPPORT)))
PP_OPT_COMMON += __DUAL_IMEI_MMI__
endif
endif

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifeq (TRUE, $(strip $(DUAL_SEND_KEY_SUPPORT)))
PP_OPT_COMMON += __DUAL_SEND_KEY_MMI__
endif
endif

ifeq (TRUE, $(strip $(NO_FULL_KEYPAD_SUPPORT)))
PP_OPT_COMMON += __NO_FULL_KEYPAD__
endif

ifeq (TRUE, $(strip $(PHB_CACHE_ADN_TO_RAM_SUPPORT)))
PP_OPT_COMMON += __PHB_CACHE_ADN_TO_RAM__
endif

ifeq (TRUE, $(strip $(NAVI_KEY_SUPPORT)))
PP_OPT_COMMON += __NAVI_KEY_MMI__
endif

ifeq (TRUE, $(strip $(E_BOOK_SUPPORT)))
PP_OPT_COMMON += __E_BOOK_MMI__
endif

ifeq (TRUE, $(strip $(DICTIONARY_SUPPORT)))
PP_OPT_COMMON += __DICTAPP_MMI__
endif

ifeq (TRUE, $(strip $(WORLDCLOCK_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_WORLDCLOCK__
endif

ifeq (TRUE, $(strip $(CALLLOG_BLOCK_CALL_SUPPORT)))
PP_OPT_COMMON += __MMI_CALLLOG_SUPPORT_BKLOG__
endif

ifeq (TRUE, $(strip $(CALLLOG_EDIT_BEFORE_CALL_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_EDIT_BEFORE_CALL__
endif

ifeq (TRUE, $(strip $(PHB_IMPORT_EXPORT_MULTI_FORMAT)))
PP_OPT_COMMON += __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__
endif

ifeq (TRUE, $(strip $(PHB_DISABLE_IMPORT_EXPORT)))
PP_OPT_COMMON += __MMI_PHB_DISABLE_IMPORT_EXPORT__
endif

ifeq (TRUE, $(strip $(PHB_DISABLE_BLACKLIST)))
PP_OPT_COMMON += __MMI_PHB_DISABLE_BLACKLIST__
endif

ifeq (TRUE, $(strip $(PHB_SEND_MULTI_VCARD_BY_BT_SUPPORT)))
PP_OPT_COMMON += __PHB_SEND_MULTI_VCARD_BY_BT__
endif

ifeq (__ORIGINAL_ICONS__, $(strip $(STATUSBAR_SHOW_UNREAD_MESSAGE_SUPPORT)))
PP_OPT_COMMON += __MMI_STATUSBAR_SUPPORT_UNREAD_MESSAGE__
endif

ifeq (TRUE, $(strip $(STATUSBAR_SHOW_MISSED_CALL_SUPPORT)))
PP_OPT_COMMON += __MMI_STATUSBAR_SUPPORT_MISSED_CALL__
endif

# Feature_Name = [MMI] Statusbar with profile icon
# Description = To show profile status in statusbar, vibrate will be disabled
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(STATUSBAR_PROFILE_STATUS_SUPPORT)))
PP_OPT_COMMON += __MMI_STATUSBAR_SUPPORT_PROFILE_STATUS__
endif

# Feature_Name = [MMI] Statusbar auto arrange icon
# Description = Statusbar auto arrange icon
# Pre_Condition_On = N/A
# Pre_Condition_Off = __LCM_QQVGA__, __LCM_LANDSCAPE_QQVGA__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(STATUSBAR_AUTO_ARRANGE_SUPPORT)))
ifneq ($(filter __LCM_QQVGA__, $(PP_OPT_COMMON)), __LCM_QQVGA__)
ifneq ($(filter __LCM_LANDSCAPE_QQVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_QQVGA__)
PP_OPT_COMMON += __MMI_STATUSBAR_AUTO_ARRANGE__
endif
endif
endif

ifeq (TRUE, $(strip $(BIDI_UI_SUPPORT)))
PP_OPT_COMMON += __MMI_BIDI_UI__
ifeq (FALSE, $(strip $(SCRIPT_EASY_BITMAP_FONT_SUPPORT)))
PP_OPT_COMMON += __BIDI_TEXT__
endif
endif

ifeq (TRUE, $(strip $(DEDICATE_END_KEY_SUPPORT)))
PP_OPT_COMMON += __DEDICATE_END_KEY_MMI__
endif

# Feature_Name = [MMI] VECTOR font
# Description = Option for vector font feature in MMI
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq (,$(strip $(VECTOR_FONT_SOLUTION)))
PP_OPT_COMMON += __FEATURE_VECTOR_FONT__
ifeq (__VECTOR_FONT_MMI_ETRUMP__, $(strip $(VECTOR_FONT_SOLUTION)))
PP_OPT_COMMON += __ETRUMP__
endif
endif
endif

# Feature_Name = [MMI] Vector Font Style
# Description = Option for Vector font Style feature in MMI
# Pre_Condition_On = __FEATURE_VECTOR_FONT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_VECTOR_FONT__, $(PP_OPT_COMMON)), __FEATURE_VECTOR_FONT__)
ifeq (TRUE, $(strip $(MMI_MUTI_FONT_IN_CUS_SUPPORT)))
PP_OPT_COMMON += __FEATURE_FONT_STYLE__
else
ifneq (,$(strip $(MMI_VECTOR_FONT_ON_T_CARD_SOLUTION)))
PP_OPT_COMMON += __FEATURE_FONT_STYLE__
endif
endif
endif

# Feature_Name = [MMI] Vector Font On T Card Solution
# Description = Option for Vector Font On T Card feature in MMI
# Pre_Condition_On = __FEATURE_VECTOR_FONT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_VECTOR_FONT__, $(PP_OPT_COMMON)), __FEATURE_VECTOR_FONT__)
ifeq (__VECTOR_FONT_ON_T_CARD_FROM_MEMORY__, $(strip $(MMI_VECTOR_FONT_ON_T_CARD_SOLUTION)))
PP_OPT_COMMON += __FEATURE_VECTOR_FONT_ON_T_CARD_FROM_MEMORY__
else
ifeq (__VECTOR_FONT_ON_T_CARD_ACCESS_FILE__, $(strip $(MMI_VECTOR_FONT_ON_T_CARD_SOLUTION)))
PP_OPT_COMMON += __FEATURE_VECTOR_FONT_ON_T_CARD_ACCESS_FILE__
endif
endif
endif

# Feature_Name = [MMI] Change font By Display language
# Description = Option for Change vector font By Display language feature in MMI
# Pre_Condition_On = VECTOR_FONT_SUPPORT
# Pre_Condition_Off = MMI_VECTOR_FONT_ON_T_CARD_SOLUTION
# Option_Selection = N/A
ifeq ($(filter __FEATURE_FONT_STYLE__, $(PP_OPT_COMMON)), __FEATURE_FONT_STYLE__)
ifeq (,$(strip $(MMI_VECTOR_FONT_ON_T_CARD_SOLUTION)))
ifeq (TRUE, $(strip $(MMI_CHANGE_FONT_BY_LANG_SUPPORT)))
PP_OPT_COMMON += __FEATURE_CHANGE_FONT_BY_LANG__
endif
endif
endif

# Description = [MMI] Enable code page string to unicode string conversion function
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __CODEPAGE_TO_UNICODE__
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(SDK_BACKGROUND_EXECUTION_SUPPORT)))
PP_OPT_COMMON += __SDK_BACKGROUND_EXECUTION__
endif
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(SDK_API_01_SMS_MMS_CC_SUPPORT)))
PP_OPT_COMMON += __SDK_API_01_SMS_MMS_CC__
endif
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(SDK_MMI_VENDOR_ENTRY_SUPPORT)))
PP_OPT_COMMON += __SDK_MMI_VENDOR_ENTRY__
ifeq (TRUE, $(strip $(SDK_MMI_TEST_SUPPORT)))
PP_OPT_COMMON += __SDK_MMI_TEST__
ifeq (TRUE, $(strip $(VFS_TEST_CASE_SUPPORT)))
PP_OPT_COMMON += __VFS_TEST_CASE_FTM__
endif
endif
endif
endif

ifneq (,$(strip $(IME_SOLUTION)))
PP_OPT_COMMON += $(IME_SOLUTION)
endif

ifeq (TRUE, $(strip $(SMS_CHAT_SUPPORT)))
ifeq ($(filter __LCM_QQVGA__ __LCM_LANDSCAPE_QQVGA__, $(LCM_RESOLUTION)),)
PP_OPT_COMMON += __MMI_SMS_CHAT__
endif
endif

ifeq (TRUE, $(strip $(SMS_EXPORT_SUPPORT)))
PP_OPT_COMMON += __MMI_SMS_EXPORT__
endif

ifeq (TRUE, $(strip $(SMS_TRASHBOX_SUPPORT)))
PP_OPT_COMMON += __MMI_SMS_TRASHBOX__
endif

ifeq (TRUE, $(strip $(SMS_SINGLE_TPSRR_SUPPORT)))
PP_OPT_COMMON += __SMS_SINGLE_TPSRR_FOR_CONCATESMS__
endif

ifeq (TRUE, $(strip $(SMS_3GPP_R8_SUPPORT)))
PP_OPT_COMMON += __SMS_3GPP_R8_SUPPORT__
endif

ifeq (TRUE, $(strip $(SMS_SEND_WHEN_FULL_SUPPORT)))
PP_OPT_COMMON += __SMS_SEND_FROM_BUFFER__
endif

ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(IME_SOFTKEYBOARD_7COLUMN_UI_SUPPORT)))
ifneq (__IME_MMI_CSTAR__, $(strip $(IME_SOLUTION)))
PP_OPT_COMMON += __IME_MMI_SOFTKEYBOARD_7COL_UI__
endif
endif
endif

ifeq ($(filter B3, $(CHIP_DSP_SEL)), B3)
ifeq (TRUE, $(strip $(DISTORTED_VOICE_SUPPORT)))
PP_OPT_COMMON += __DISTORTED_VOICE_MMI__
ifeq (TRUE, $(strip $(CCMTA_OPTION_MENU_SUPPORT)))
PP_OPT_COMMON += __CCMTA_OPTION_MENU_MMI__
endif
endif
endif

ifeq (TRUE, $(strip $(ANSWERING_MACHINE_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_ANSWERING_MACHINE__
endif

ifeq (TRUE, $(strip $(PHB_VIDEOTONE_SUPPORT)))
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __MMI_PHB_VIDEOTONE_SUPPORT__
endif
endif

ifeq (TRUE, $(strip $(CALL_BACKGROUND_SOUND_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_CALL_BACKGROUND_SOUND__
endif

ifeq (TRUE, $(strip $(AUTO_RECORDING_SUPPORT)))
ifeq (TRUE, $(strip $(IN_CALL_RECORDING_SUPPORT)))
PP_OPT_COMMON += __AUTO_RECORDING_MMI__
endif
endif

ifeq (TRUE, $(strip $(CALL_LIMIT_SUPPORT)))
PP_OPT_COMMON += __CALL_LIMIT_MMI__
endif

ifeq (TRUE, $(strip $(IN_CALL_RECORDING_SUPPORT)))
PP_OPT_COMMON += __IN_CALL_RECORDING_MMI__
endif

ifeq (TRUE, $(strip $(PROGRAM_TEMP_IMEI_SUPPORT)))
PP_OPT_COMMON +=  __PROGRAM_TEMP_IMEI_MMI__
endif

ifeq (TRUE, $(strip $(INDIC_FONT_SUPPORT)))
ifeq (FALSE, $(strip $(SCRIPT_EASY_BITMAP_FONT_SUPPORT)))
PP_OPT_COMMON += __INDIC_FONT__
endif
endif

# __THAI_FONT__ is defaultly enabled unless your product don't need Thai language support and want to save more code size especially for small-rom products
PP_OPT_COMMON += __THAI_FONT__

ifeq ($(filter __WLAN__, $(PP_OPT_COMMON)), __WLAN__)
ifeq (TRUE, $(strip $(WLAN_AUTOCONNECT_SUPPORT)))
PP_OPT_COMMON += __WLAN_AUTOCONNECT__
endif
endif

ifeq (TRUE, $(strip $(CHECK_DISK_APP_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_CHECKDISK__
PP_OPT_COMMON += __SUPPORT_FORMAT__
PP_OPT_COMMON += __SUPPORT_CHECKDISK__
ifeq (TRUE, $(strip $(CHECK_DISK_REMIND_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_CHECKDISK_REMIND__
endif
endif

ifeq (TRUE, $(strip $(HIDDEN_PARTITION_SUPPORT)))
PP_OPT_COMMON += __SUPPORT_HIDDEN_PARTITION__
endif

ifeq (TRUE, $(strip $(SD1_SD2_LAYOUT_SWAP_SUPPORT)))
PP_OPT_COMMON += __SD1_SD2_LAYOUTSWAP__
endif

ifeq (TRUE, $(strip $(AUDIO_SEEK)))
PP_OPT_COMMON += __MMI_AUDIO_SEEK__
endif

ifeq (TRUE, $(strip $(MP3_DEC_SUPPORT)))
ifeq (TRUE, $(strip $(ID3_TAG_SUPPORT)))
PP_OPT_COMMON += __MMI_ID3_SUPPORT__
endif
endif

ifeq (TRUE, $(strip $(SCREENSAVER_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_SCREENSAVER__
endif

ifeq (TRUE, $(strip $(ONCHIP_FMRX_ENABLE_SUPPORT)))
PP_OPT_COMMON += __ONCHIP_FMRX_ENABLE__
else
PP_OPT_COMMON += $(FM_AUDIO_PATH)
endif

ifeq (TRUE, $(strip $(MULTIPLE_SENSOR_TABLE_DETECTION_SUPPORT)))
ifneq (TRUE, $(strip $(5M_SENSOR_SUPPORT)))
PP_OPT_COMMON += __MULTIPLE_SENSOR_TABLE_DETECTION__
PP_OPT_COMMON += __SENSOR_LZF_SUPPORT__
endif
endif

ifeq (TRUE, $(strip $(5M_SENSOR_SUPPORT)))
PP_OPT_COMMON += __5M_SENSOR_SUPPORT__
endif

ifneq (__INTERFERE_CAMERA_PATCH_NONE__, $(strip $(INTERFERE_CAMERA_PATCH)))
PP_OPT_COMMON += $(INTERFERE_CAMERA_PATCH)
ifeq (TRUE, $(strip $(INTERFERE_CAMERA_PATCH_FOR_CAMERA_MAIN)))
PP_OPT_COMMON += __INTERFERE_CAMERA_PATCH_MAIN__
endif
ifeq (TRUE, $(strip $(INTERFERE_CAMERA_PATCH_FOR_CAMERA_SUB)))
PP_OPT_COMMON += __INTERFERE_CAMERA_PATCH_SUB__
endif
ifeq (TRUE, $(strip $(INTERFERE_CAMERA_PATCH_FOR_ATV)))
PP_OPT_COMMON += __INTERFERE_CAMERA_PATCH_ATV__
endif
endif

ifeq (TRUE, $(strip $(CHIP_VIDEO_STABILIZER_SUPPORT)))
ifeq (TRUE, $(strip $(VIDEO_STABILIZER_SUPPORT)))
PP_OPT_COMMON += __VIDEO_STABILIZER_ENABLE__
endif
endif

ifeq (TRUE, $(strip $(CHIP_SCL_LOW_BANDWIDTH_MODE)))
PP_OPT_COMMON += __SCL_LOW_BANDWIDTH_MODE__
endif

ifeq (TRUE, $(strip $(CHIP_CAMERA_SUPPORT_2M_BYPASS_SCALER)))
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __CAMERA_SUPPORT_2M_BYPASS_SCALER__
endif
endif

ifeq (TRUE, $(strip $(CPU_FORCE_364MHZ_SUPPORT)))
PP_OPT_COMMON += __CPU_FORCE_364MHZ__
endif

ifeq (TRUE, $(strip $(ABNORMAL_SLEEP_DEBUG_SUPPORT)))
PP_OPT_COMMON += __ABNORMAL_SLEEP_DEBUG__
endif

ifeq (TRUE, $(strip $(IQDUMP_FOR_SIMU_SUPPORT)))
PP_OPT_COMMON += __IQDUMP_FOR_SIMU__
endif

ifeq (TRUE, $(strip $(UNIT_TEST_APP_SUPPORT)))
PP_OPT_COMMON += __UNIT_TEST_APP__
PP_OPT_COMMON += __UNIT_TEST_SRV__
ifeq (TRUE, $(strip $(DLM_SRVUT_SUPPORT)))
PP_OPT_COMMON += __ENABLE_DLM_SRVUT__
endif
endif

ifeq (TRUE, $(strip $(DIAG_ERROR_SUPPORT)))
ifeq ($(filter __X86LINUXGCC__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __DIAG_ERROR__
endif
endif

ifeq (TRUE, $(strip $(CHIP_SUPPORT_BUS_FSP_SPI)))
PP_OPT_COMMON += __SUPPORT_BUS_FSP_SPI__
endif

ifeq (TRUE, $(strip $(CHIP_SPI_RESET_BY_OFF_VMEM)))
PP_OPT_COMMON += __SPI_RESET_BY_OFF_VMEM__
endif

ifeq (TRUE, $(strip $(CHIP_SUPPORT_BUS_FSP_SPI)))
ifeq (TRUE, $(strip $(CHIP_DUAL_SPI_FLASH_SUPPORT)))
ifneq ($(filter __MSW8556M__ __MSW8556M2__, $(CHIP_TYPE)),)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __DUAL_SPI_FLASH__
endif
endif
endif
endif

ifeq (TRUE, $(strip $(CHIP_SUPPORT_BUS_FSP_SPI)))
ifneq ($(filter __MSW8556R__ __MSW8556R2__, $(CHIP_TYPE)),)
PP_OPT_COMMON += __QBYTE_ADDR_SPI_FLASH__
endif
endif

ifeq ($(filter 128P3Mhz, $(CHIP_MIU_USE_APLL_SEL)), 128P3Mhz)
#ifeq (TRUE, $(strip $(CHIP_MIU_USE_APLL__128P3MHz)))
PP_OPT_COMMON += __MIU_USE_APLL__128P3MHz__
endif

ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq ($(filter ZERO_OHM, $(CLKOUT_26MHZ_BB_CONFIG)), ZERO_OHM)
PP_OPT_COMMON += __APLL_PWD_SLEEP__
endif
endif


ifeq (TRUE, $(strip $(SPI_MAX_SPEED)))
ifeq (TRUE, $(strip $(CHIP_SPI_MAX_SPEED)))
PP_OPT_COMMON += __SPI_MAX_SPEED__
endif
endif

ifeq (TRUE, $(strip $(FINT_DISABLE_DMA2D)))
PP_OPT_COMMON += __FINT_DISABLE_DMA2D__
endif

ifeq (TRUE, $(strip $(EVB_WITHOUT_BATTERY_SUPPORT)))
PP_OPT_COMMON += __EVB_WITHOUT_BATTERY__
endif

ifeq (TRUE, $(strip $(RADIO_USE_DB_SUPPORT)))
PP_OPT_COMMON += __RADIO_USE_DB__
endif

ifeq (TRUE, $(strip $(UPGRADE_SHARE_MEMORY_SUPPORT)))
PP_OPT_COMMON += __UPGRADE_SHARE_MEMORY__
endif

ifeq (TRUE, $(strip $(SHARE_MEMORY_DEBUG_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SHAREMEMORY_DEBUG__
endif

ifeq (TRUE, $(strip $(SHARE_MEMORY_LOOPBACK_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SHM_LOOPBACK__
endif

ifeq (TRUE, $(strip $(DISABLE_DMA_FOR_SHARE_MEMORY_SUPPORT)))
PP_OPT_COMMON += __DISABLE_DMA_FOR_SHM__
endif

ifeq (TRUE, $(strip $(UPGRADE_NVRAM_SUPPORT)))
PP_OPT_COMMON += __UPGRADE_NVRAM__
endif

ifeq (TRUE, $(strip $(THREE_G_SUPPORT)))
PP_OPT_COMMON += __3G__
endif

ifeq (TRUE, $(strip $(THREE_G_RIL_MMI_SUPPORT)))
PP_OPT_COMMON += __3G_RIL_MMI__
endif

ifeq (TRUE, $(strip $(SLIM_RIL_SUPPORT)))
PP_OPT_COMMON += __SLIM_RIL__
endif

ifeq (TRUE, $(strip $(SLIM_ATI_SUPPORT)))
PP_OPT_COMMON += __SLIM_ATI__
endif

ifeq (TRUE, $(strip $(DIALUP_NETWORKING_SUPPORT)))
PP_OPT_COMMON += __DIALUP_NETWORKING__
endif

ifeq (TRUE, $(strip $(G1_VIDEO_TELEPHONY_3G324M_SUPPORT)))
PP_OPT_COMMON += __VT_3G324M__
ifeq (TRUE, $(strip $(G1_VIDEO_TELEPHONY_MMI_FEATURE_SUPPORT)))
PP_OPT_COMMON += __APP_VIDEO_TELEPHONY__
endif
endif

ifeq (TRUE, $(strip $(CUS_MMAP_SUPPORT)))
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __MMAP__
PP_OPT_COMMON += __MMAP_CUS_MMI__

ifeq (MMAP_CUS_16MB, $(strip $(CUS_MMAP_SIZE)))
PP_OPT_COMMON += __MMAP_CUS_16MB__
endif

ifeq (MMAP_CUS_32MB, $(strip $(CUS_MMAP_SIZE)))
PP_OPT_COMMON += __MMAP_CUS_32MB__
endif

ifeq (MMAP_CUS_64MB, $(strip $(CUS_MMAP_SIZE)))
PP_OPT_COMMON += __MMAP_CUS_64MB__
endif

endif
endif

ifeq (TRUE, $(strip $(SAMSUNG_K5L2833ATA_PAGE_PAGE_MODE)))
PP_OPT_COMMON += __SAMSUNG_K5L2833ATA_PAGE_PAGE_MODE__
endif

ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __NEW_NOR_ARCH__
endif

ifeq (TRUE, $(strip $(LCM_SLEEP_MODE_SUPPORT)))
PP_OPT_COMMON += __LCM_SLEEP_MODE__
endif

ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __RTK_OVER_ARM_SLDLM__
endif

ifeq (TRUE, $(strip $(RTK_OVER_ARM_NAND_IMI_SLDLM_SUPPORT)))
PP_OPT_COMMON += __RTK_OVER_ARM_NAND_IMI_SLDLM__
endif


ifeq (TRUE, $(strip $(ANTI_STEAL_SUPPORT)))
PP_OPT_COMMON += __ANTI_STEAL_MMI__
endif

ifeq (TRUE, $(strip $(ANTI_STEAL_SUPPORT)))
ifeq (TRUE, $(strip $(ANTI_STEAL_REMOTE_CONTROL_SUPPORT)))
PP_OPT_COMMON += __ANTI_STEAL_REMOTE_CONTROL_MMI__
endif
endif

ifeq (TRUE, $(strip $(SMSBLACKLIST_SUPPORT)))
PP_OPT_COMMON += __SMSBLACKLIST_MMI__
endif

ifeq (TRUE, $(strip $(SMS_SEARCH_SUPPORT)))
PP_OPT_COMMON += __MMI_SMS_SEARCH__
endif

ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
ifeq (TRUE, $(strip $(SMS_WAPPUSH_SUPPORT)))
PP_OPT_COMMON += __MMI_SMS_WAPPUSH__
endif
endif

ifeq (TRUE, $(strip $(NETWORK_LOCK_SUPPORT)))
PP_OPT_COMMON += __NETWORK_LOCK_MMI__
endif

ifeq (TRUE, $(strip $(SP_LOCK_SUPPORT)))
PP_OPT_COMMON += __SERVICEPROVIDER_LOCK_MMI__
ifeq (FALSE, $(strip $(NETWORK_LOCK_SUPPORT)))
PP_OPT_COMMON += __NETWORK_LOCK_MMI__
endif
endif

ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq (TRUE, $(strip $(DPM_SUPPORT)))
PP_OPT_COMMON += __DPM__
ifeq (TRUE, $(strip $(EMMI_SLDPM_SUPPORT)))
PP_OPT_COMMON += __EMMI_SLDPM__
PP_OPT_COMMON += __ROM_REMAP_TO_EMMI_SLDPM_NEIGHBORHOOD__
# for 32/64, 32/32 product, compress with zlib preset dictionary
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
ifneq ($(filter 0x00800000 0x00400000, $(SYS_PHY_RAM_SIZE_SETTING)),)
PP_OPT_COMMON += __ZLIB_PRESET_DICT__
endif
endif
ifeq (TRUE, $(strip $(EMMI_SLDPM_CUS_SUPPORT)))
PP_OPT_COMMON += __CUS_IME_COMPRESSION__
PP_OPT_COMMON += __CUS_PLMN_COMPRESSION__
ifneq (,$(strip $(TOUCH_SCREEN_DRIVER_SELECT)))
ifneq (TRUE, $(strip $(DISABLE_HANDWRITING_INPUT_SUPPORT)))
ifneq (TRUE, $(strip $(HANDWRITING_DB_TCARD_SUPPORT)))
PP_OPT_COMMON += __CUS_HW_COMPRESSION__
endif
endif
endif
endif
endif
endif
endif

ifeq (TRUE, $(strip $(CHIP_DLM_OVER_ARM)))
PP_OPT_COMMON += __DLM_OVER_ARM__
endif

ifeq (TRUE, $(strip $(CHIP_MAK_ARM)))
PP_OPT_COMMON += __MAK_ARM__
endif

ifeq (TRUE, $(strip $(DWL_ALL_DSP_SUPPORT)))
PP_OPT_COMMON += __DWL_ALL_DSP_SUPPORT__
endif

ifeq (TRUE, $(strip $(STRING_COMPRESSION_SUPPORT)))
PP_OPT_COMMON += __CUS_STRING_COMPRESSION__

# Feature_Name = merge current language translation with default language
# Description =  if current language have any string with no translation, XRG use the translation of defalut language instead of it ( only apply in CUS file ).
#  if this feature is enabled, there is only current language to be load in heap.  otherwise, default and current language to be load in heap at the same time.
PP_OPT_COMMON += __ENABLE_TRANSLATION_MERGE__
endif

ifeq (TRUE, $(strip $(FONT_COMPRESSION_SUPPORT)))
PP_OPT_COMMON += __CUS_FONT_COMPRESSION__
endif

# for 32/64 product
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
ifeq (0x00800000, $(strip $(SYS_PHY_RAM_SIZE_SETTING)))
PP_OPT_COMMON += __CUS_WHOLE_PACKAGE_COMPRESS__
endif
endif

ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
ifeq (TRUE, $(strip $(VIDEO_HTTP_STREAMING_SUPPORT)))
PP_OPT_COMMON += __STREAMING_MODULE__
PP_OPT_COMMON += __HTTP_STREAMING__
PP_OPT_COMMON += __DOWNLOAD_PROGRESS__
endif

ifeq (TRUE, $(strip $(VIDEO_RTSP_STREAMING_SUPPORT)))
PP_OPT_COMMON += __STREAMING_MODULE__
PP_OPT_COMMON += __RTSP_STREAMING__
PP_OPT_COMMON += __DOWNLOAD_PROGRESS__
endif
endif
endif
endif

ifneq ($(filter __LCM_HVGA_320_480__ __LCM_WQVGA_240_400__ __LCM_QVGA__, $(PP_OPT_COMMON)),)
ifneq ($(filter __RTSP_STREAMING__ __HTTP_STREAMING__, $(PP_OPT_COMMON)),)
ifeq (TRUE, $(strip $(TUDOU_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_TUDOU__
PP_OPT_COMMON += __APP_MMI_TUDOU_MENU_ITEM_WDG__
PP_OPT_COMMON += __APP_MMI_TUDOU_RELEASE__
ifeq (TRUE, $(strip $(TUDOU_GPRS_ONLY_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_TUDOU_SUPPORT_GPRS_ONLY__
PP_OPT_COMMON += __SOCKETSRV_SUPPORT__
endif
endif
endif
endif




ifeq ($(filter 153Mhz, $(CHIP_MIU_USE_APLL_SEL)), 153Mhz)
#ifeq (TRUE, $(strip $(CHIP_MIU_USE_APLL__153Mhz)))
ifeq (TRUE, $(strip $(APLL_MIU_MODE_153MHZ)))
PP_OPT_COMMON += __MIU_USE_APLL__153MHz__
endif
endif
ifeq (TRUE, $(strip $(SAVE_POOLSTATUS_MMI_SUPPORT)))
PP_OPT_COMMON += __SAVEPOOLSTATUS_MMI__
endif

ifeq (TRUE, $(strip $(CHIP_WATCHDOG_RESET_PATCH)))
PP_OPT_COMMON += __WATCHDOG_RESET_PATCH__
endif

ifeq ($(filter B3, $(CHIP_DSP_SEL)), B3)
PP_OPT_COMMON += __DSP_B3__
DSP_VER = __DSP_B3__
endif

ifeq ($(filter B3, $(CHIP_BT_MAC_SEL)), B3)
PP_OPT_COMMON += __BT_MAC_B3__
endif

ifeq (TRUE, $(strip $(CHIP_AVP_ARM_9)))
PP_OPT_COMMON += __AVP_ARM_9__
endif

ifeq (TRUE, $(strip $(CHIP_MMAUDIO_ARM)))
PP_OPT_COMMON += __MMAUDIO_ARM__
endif

ifeq (TRUE, $(strip $(CHIP_RF_LDO_SLEEP_OFF)))
PP_OPT_COMMON += __RF_LDO_SLEEP_OFF__
endif

ifeq (TRUE, $(strip $(CHIP_SLEEP_HANDLER)))
PP_OPT_COMMON += __SLEEP_HANDLER__
endif

ifeq (TRUE, $(strip $(CHIP_NAND_PWD_NOTIFY)))
PP_OPT_COMMON += __NAND_PWD_NOTIFY__
endif

ifeq (TRUE, $(strip $(CHIP_LOW_BATTERY_DETECT_DEBOUNCE)))
PP_OPT_COMMON += __LOW_BATTERY_DETECT_DEBOUNCE__
endif

ifeq (TRUE, $(strip $(CHIP_RIU_INT_CTL)))
PP_OPT_COMMON += __RIU_INT_CTL__
endif

ifeq (TRUE, $(strip $(CHIP_RTK_DBG_INFO)))
PP_OPT_COMMON += __RTK_DBG_INFO__
endif

ifeq (TRUE, $(strip $(CHIP_SIM_SUSTAIN_SIGNALS)))
PP_OPT_COMMON += __SIM_SUSTAIN_SIGNALS__
endif

ifeq (TRUE, $(strip $(CHIP_SIM_USE_SRAM)))
PP_OPT_COMMON += __SIM_SRAM__
endif

ifeq (TRUE, $(strip $(CHIP_SIM_SRAM_ADDR_B9)))
PP_OPT_COMMON += __SIM_SRAM_ADDR_B9__
endif

ifeq (TRUE, $(strip $(CHIP_MMP_SLEEP_RESET)))
PP_OPT_COMMON += __MMP_SLEEP_RESET__
endif

ifeq (TRUE, $(strip $(CHIP_FCIE_SDIO_SHARE_IP)))
PP_OPT_COMMON += __FCIE_SDIO_SHARE_IP__
endif

ifeq (TRUE, $(strip $(CHIP_MMI_SMALL_CALLER_PHOTO)))
PP_OPT_COMMON += __MMI_SMALL_CALLER_PHOTO__
endif

ifeq ($(filter BRAVO, $(CHIP_DSP_SEL)), BRAVO)
PP_OPT_COMMON += __DSP_BRAVO__
DSP_VER = __DSP_BRAVO__
endif

ifeq ($(filter BRAVO, $(CHIP_BT_MAC_SEL)), BRAVO)
PP_OPT_COMMON += __BT_MAC_BRAVO__
endif

ifeq (TRUE, $(strip $(CHIP_NO_HW_JPD)))
PP_OPT_COMMON += __NO_HW_JPD__
endif

ifeq (TRUE, $(strip $(CHIP_DRV_NO_HW_DMA)))
PP_OPT_COMMON += __DRV_NO_HW_DMA__
endif


ifeq (TRUE, $(strip $(CHIP_AVP_HW_M4VD)))
PP_OPT_COMMON += __AVP_HW_M4VD__
endif

ifeq (TRUE, $(strip $(CHIP_AVP_AEON_R2)))
PP_OPT_COMMON += __AVP_AEON_R2__
endif

ifeq (TRUE, $(strip $(CHIP_MMAUDIO_AEON)))
PP_OPT_COMMON += __MMAUDIO_AEON__
endif

ifeq (TRUE, $(strip $(CHIP_G1_DEBUG_UART_PLATFORM_TYPE)))
ifneq (,$(strip $(G1_DEBUG_UART_PLATFORM_TYPE)))
PP_OPT_COMMON += $(G1_DEBUG_UART_PLATFORM_TYPE)
endif
endif

ifeq ($(filter B5, $(CHIP_DSP_SEL)), B5)
PP_OPT_COMMON += __DSP_B5__
DSP_VER = __DSP_B5__
endif

ifeq ($(filter B5, $(CHIP_BT_MAC_SEL)), B5)
PP_OPT_COMMON += __BT_MAC_B5__
endif

ifeq ($(filter BLOSSOM, $(CHIP_BT_MAC_SEL)), BLOSSOM)
PP_OPT_COMMON += __BT_MAC_BLOSSOM__
endif

ifeq ($(filter BLOSSOM, $(CHIP_DSP_SEL)), BLOSSOM)
PP_OPT_COMMON += __DSP_BLOSSOM__
DSP_VER = __DSP_BLOSSOM__
endif

PP_OPT_COMMON += __INCENSE_3__
PP_OPT_COMMON += __SHARE_MEM__

ifeq (TRUE, $(strip $(LZMA2_PRESET_DICT_SUPPORT)))
PP_OPT_COMMON += __LZMA2_PRESET_DICT__
endif

#===============================================================================
# ** Driver OPTIONS **
#===============================================================================
# Feature_Name = __NO_ASURA__
# Description = Erase Asura SPI access code
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_NO_ASURA)))
PP_OPT_COMMON += __NO_ASURA__
endif

# Feature_Name = ZLIB ROM
# Description = Option to support ZLIB RUN IN ROM
ifeq (TRUE, $(strip $(CHIP_ZLIB_IN_ROM)))
PP_OPT_COMMON += ZLIB_USE_ROM=1 ZLIB_BUILD_ROM=0
#PP_OPT_COMMON += __ZLIB_ROM_SIMULATOR__
else
PP_OPT_COMMON += ZLIB_USE_ROM=0 ZLIB_BUILD_ROM=0
endif

# Feature_Name = HW ZLIB
# Description = Option to support ZLIB
ifeq (TRUE, $(strip $(CHIP_HW_ZLIB)))
PP_OPT_COMMON += __HW_ZLIB_SUPPORT__
ifeq (TRUE, $(strip $(CHIP_HW_ZLIB_IN_ROM)))
PP_OPT_COMMON += HW_ZLIB_USE_ROM=1 HW_ZLIB_BUILD_ROM=0
#PP_OPT_COMMON += __ZLIB_ROM_SIMULATOR__
else
PP_OPT_COMMON += HW_ZLIB_USE_ROM=0 HW_ZLIB_BUILD_ROM=0
endif
endif

# Description = [DRV] DSP patch is downloaded by DwlWin
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_TARGET_DSP_PATCH_SOLO_BIN)))
PP_OPT_COMMON += __TARGET_DSP_PATCH_SOLO_BIN__
endif

# Description = [DRV] dbb/r2 watch dog timer driver
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_CHIPDRV_DBB_WDT)))
PP_OPT_COMMON += __CHIPDRV_DBB_WDT___
endif
ifeq (TRUE, $(strip $(CHIP_CHIPDRV_R2_WDT)))
PP_OPT_COMMON += __CHIPDRV_R2_WDT__
endif
ifeq (TRUE, $(strip $(CHIP_CHIPDRV_INFINITY_WDT)))
PP_OPT_COMMON += __CHIPDRV_INFINITY_WDT__
endif


# Description = [DRV] MultiMedia(MM) timer driver
# Pre_Condition_On = CHIP_CHIPDRV_MM_TIMER
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_CHIPDRV_MM_TIMER)))
PP_OPT_COMMON += __CHIPDRV_MM_TIMER___
endif

# Description = [DRV] If this flag is set, it disable integrity check of flash at power on.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __NO_INTEGRITY_CHK_AT_PWRON__

# Feature_Name = Display Engine (DRV)
# Description = Option to enable display engine driver layer
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __DISP_DRV__

# Description = [DRV] Audio Mix Support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_AUDIO_MIX_SUPPORT)))
PP_OPT_COMMON += __AUDIO_MIX_SUPPORT__
endif

# Description = [DRV] Rompatch Support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_ROMPATCH)))
PP_OPT_COMMON += __ROMPATCH_SUPPORT__
endif

# Description = [DRV] GDMA Support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_GDMA)))
PP_OPT_COMMON += __GDMA_SUPPORT__
endif


# Description = [DRV] FM & SD DYNAMIC CLOCK Support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_FMRX_SD_DYNAMIC_CLOCK)))
PP_OPT_COMMON += __FMRX_SD_DYNAMIC_CLOCK_SUPPORT__
endif



# Description = [DRV] WLED 2 channel Support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_WLED_SHUNT)))
PP_OPT_COMMON += __WLED_SHUNT_SUPPORT__
endif



# Description = [DRV] WLED level count
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq (,$(strip $(CHIP_WLED_LEVEL_COUNT)))
PP_OPT_COMMON += WLED_LEVEL_COUNT=$(CHIP_WLED_LEVEL_COUNT)
endif


#-------------------------------------------------------------------------------
# SD card related option
#-------------------------------------------------------------------------------

ifneq ($(filter __SD1_4_BITS_ONLY_NO_SD2__, $(SD_DATA_BUS_CONFIG)), __SD1_4_BITS_ONLY_NO_SD2__)
PP_OPT_COMMON += __DUAL_CARD__
endif

ifneq (,$(strip $(SD_DATA_BUS_CONFIG)))
PP_OPT_COMMON += $(SD_DATA_BUS_CONFIG)
endif

ifneq (,$(strip $(SD1_HOT_PLUG_SUPPORT)))
PP_OPT_COMMON += $(SD1_HOT_PLUG_SUPPORT)
endif
ifneq (,$(strip $(SD2_HOT_PLUG_SUPPORT)))
PP_OPT_COMMON += $(SD2_HOT_PLUG_SUPPORT)
endif

ifneq ($(filter __SD1_HOT_PLUG_INSERT_LOW__ __SD1_HOT_PLUG_INSERT_HIGH__, $(SD1_HOT_PLUG_SUPPORT)), )
PP_OPT_COMMON += __MEMCARD_HOTPLUG__
endif
ifneq ($(filter __SD2_HOT_PLUG_INSERT_LOW__ __SD2_HOT_PLUG_INSERT_HIGH__, $(SD2_HOT_PLUG_SUPPORT)), )
PP_OPT_COMMON += __MEMCARD_HOTPLUG__
endif

PP_OPT_COMMON += __DOWNGRADE_SD_CLOCK__=$(SD_CARD_CLOCK)

ifeq ($(filter CHIP_STG_IP_FCIE, $(CHIP_STORAGE_IP)), CHIP_STG_IP_FCIE)
PP_OPT_COMMON += __STG_IP_FCIE__
endif
ifeq ($(filter CHIP_STG_IP_SDIO, $(CHIP_STORAGE_IP)), CHIP_STG_IP_SDIO)
PP_OPT_COMMON += __STG_IP_SDIO__
endif
ifeq ($(filter CHIP_STG_IP_FCIE_SDIO, $(CHIP_STORAGE_IP)), CHIP_STG_IP_FCIE_SDIO)
PP_OPT_COMMON += __STG_IP_FCIE_SDIO__
endif

ifeq (TRUE, $(strip $(DUAL_CARD_SHARE_POWER_SUPPORT)))
PP_OPT_COMMON += __DUAL_CARD_SHARE_POWER__
endif

#-------------------------------------------------------------------------------

# Description = Option RAI debug, must remove when mp release
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __FMS_RAI_DEBUG__

# Description = Option E2P debug, must remove when mp release
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __FMS_E2P_DEBUG__

# Description = Option Resource Manager debug, must remove when mp release
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __RES_MGR_DEBUG__

# Description = Option E2P State management
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __FMS_E2P_STATE__

# Description = Option E2P factory interface
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __FMS_E2P_FAC_ITF__

# Description = [E2P] Turn on E2P Offset by external symbol
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __E2P_INDEX_SYM__
endif

# Description = [DRV] Enable ADC calibration
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __ADC_CALIB_DRV__

# Description = [DRV] Big endian panel display driver
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __BIG_ENDIAN_PANEL__

# Description = Option for supporting composite usb
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_V24_COMPOSITE_USB)))
PP_OPT_COMMON += __V24_COMPOSITE_USB___
endif

# Description = Option for usb G1 architect
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
ifeq (TRUE, $(strip $(CHIP_USB_ENABLE)))
PP_OPT_COMMON += __USB_ENABLE__
endif
endif

# Description = [DRV] Enable USB CDC
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __USB_CDC__

# Description = Option for G1 FUART IP Type
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_SYNOPSYS_UART)))
PP_OPT_COMMON += __SYNOPSYS_UART__
endif

# Description = [DRV] Enable V24 software flow control
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __V24_SOFT_FC__

# Description = [DRV] Enable power-on voltage adjustment
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __CHECK_VBATT_BY_CUS_AT_POWER_ON__

# Description = [DRV] Acqurie Battery information on frame interrupt. On some platform, there is no Fint to MMP.
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_BATT_ACQUIRE_WITHOUT_FINT)))
PP_OPT_COMMON += __BATT_ACQRIRE_WITHOUT_FINT__
endif

# Description = [DRV] If this flag is set, TMT can access Incense/M2 register.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __REGISTER_TEST_TOOL__

# Description = [DRV] Enable Montage power management
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MMP_PWR_MNGT__

# Description = [DRV] Enable EMA display mechanism
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __EMA_DISPLAY__

# Description = [DRV] Enable reset MMP after command timeout
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __MMP_COMMAND_TIMEOUT_RESET__

# Feature_Name = charging power on with no battery
# Description = Option to Enable charging power on with no battery at user mode
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHARGER_POWER_ON_WITHOUT_BATT_SUPPORT)))
PP_OPT_COMMON += __CHARGER_POWER_ON_WITHOUT_BATT__
endif

# Description = Option to let charging stop every once a while to read the real battery voltage value.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __CHARGER_POWER_ON_WITHOUT_BATT__
# Option_Selection = N/A
ifeq ($(filter __CHARGER_POWER_ON_WITHOUT_BATT__, $(PP_OPT_COMMON)), )
PP_OPT_COMMON += __PERIODIC_CHARGING_STOP_CHECK_BATTERY_VOLT__
endif

# Description = [DRV] If this flag is set, AT command can enable/disable charger mechanism.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __CHARGER_MECHANISM_SWITCH__

# Feature_Name = Replace PMOS with PNP, using charging volt & current to detect charger plug-out.
# Description = Option to Enable charging detection scheme with charging volt & current.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(PNP_CHARGING_SUPPORT)))
PP_OPT_COMMON += __PNP_CHARGING__
endif

# Feature_Name = Default Card
# Description = Option to support default card
# Pre_Condition_On = __DUAL_CARD__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __DUAL_CARD__, $(PP_OPT_COMMON)), __DUAL_CARD__)
PP_OPT_COMMON += __DEFAULT_CARD__
endif

# Feature_Name = WLAN
# Description = Option for WLAN feature
# Pre_Condition_On = __WLAN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WLAN__, $(PP_OPT_COMMON)), __WLAN__)
PP_OPT_COMMON += __WLAN_MEM_POOL__
ifeq (TRUE, $(strip $(CHIP_WLAN_PIF)))
PP_OPT_COMMON += __WLAN_PIF__
else
# WLAN interface is defined by WLAN_INTERFACE make variable instead
# Only PIF and SDIO types are allowed right now
$(if $(filter-out PIF SDIO, $(WLAN_INTERFACE)),\
  $(error Ambiguous definition of WLAN_INTERFACE = $(WLAN_INTERFACE)))
PP_OPT_COMMON += __WLAN_$(WLAN_INTERFACE)__
endif
endif

# Feature_Name = USB
# Description = Option for USB feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(USB_UMC_DISABLE)))
PP_OPT_COMMON += __DISABLE_USB_MASS_STORAGE_CLASS__
endif
ifeq (TRUE, $(strip $(USB_UVC_DISABLE)))
PP_OPT_COMMON += __DISABLE_USB_VIDEO_CLASS__
endif
ifeq (TRUE, $(strip $(USB_CDC_DISABLE)))
PP_OPT_COMMON += __DISABLE_USB_CDC_CLASS__
endif

# Description = Turn on this option, it will enable modem functionality.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __USB_MODEM__
endif

# Description = [DRV] G1 ADC calibration with AT Command
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_G1_ADC_CALIBRATION)))
PP_OPT_COMMON += __G1_ADC_CALIBRATION__
endif

# Description = Option to Enable Ring Tone Gain Table
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(RING_TONE_GAIN_TABLE_SUPPORT)))
PP_OPT_COMMON += __RING_TONE_GAIN_TABLE_ENABLE__
endif

# Description = Option to Enable AGC Tool Control
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __AGC_TOOL_CTRL_ENABLE__

# Feature_Name = MBAS
# Description = Option for MBAS feature
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_MBAS)))
ifeq (TRUE, $(strip $(MBAS_SUPPORT)))
PP_OPT_COMMON += __MBAS__
endif
endif

# Feature_Name = FAST GPIO access.
# Description = If this option is set, driver can access GPIO control register directly
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(FAST_GPIO_SUPPORT)))
PP_OPT_COMMON += __FAST_GPIO_ACCESS__
endif


# Feature_Name = Device Information
# Description = Support Show Device Information in engineer mode
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(DEVICE_INFO_SUPPORT)))
PP_OPT_COMMON += __DEVICE_INFO__
endif

ifeq (TRUE, $(strip $(AZAN_APP_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_AZAN__
endif

# Description = [MMI] Screen effects
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G3D__, __UI_STYLE_MMI_ANDROID_IDLE__
# Option_Selection = N/A
ifeq (FALSE, $(strip $(UI_STYLE_MMI_ANDROID_IDLE_SUPPORT)))
ifeq (TRUE, $(strip $(SCREEN_EFFECT_BEZIER_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_BEZIER_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_SNOW_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_SNOW_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_RIPPLE_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_RIPPLE_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_FIRE_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_FIRE_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_FIREFLY_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_FIREFLY_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_WATER_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_WATER_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_METEOR_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_METEOR_SUPPORT__
endif
ifeq (TRUE, $(strip $(SCREEN_EFFECT_SPACE_SUPPORT)))
PP_OPT_COMMON += __SCREEN_EFFECT_SPACE_SUPPORT__
endif

ifneq ($(filter __G3D__, $(PP_OPT_COMMON)), __G3D__)
ifneq ($(filter __SCREEN_EFFECT_BEZIER_SUPPORT__ __SCREEN_EFFECT_SNOW_SUPPORT__ __SCREEN_EFFECT_RIPPLE_SUPPORT__ __SCREEN_EFFECT_FIRE_SUPPORT__ __SCREEN_EFFECT_FIREFLY_SUPPORT__ __SCREEN_EFFECT_WATER_SUPPORT__ __SCREEN_EFFECT_METEOR_SUPPORT__ __SCREEN_EFFECT_SPACE_SUPPORT__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __SCREEN_EFFECTS_SUPPORT__
endif
endif
endif

# Description = Option to use UART2 as debug port
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __DBG_PORT_UART2__
else
ifeq ($(filter __INFINITY__, $(PP_OPT_COMMON)), __INFINITY__)
ifneq ($(filter __MV5_FPGA__, $(PP_OPT_COMMON)), __MV5_FPGA__)
PP_OPT_COMMON += __DBG_PORT_UART2__
endif
endif
endif

# Description=[ADC] ADC Module Select
# Pre_Condition_On= N/A
# Pre_Condition_Off= N/A
# Option_Selection= __ADC_SAR__, __ADC_ASURA__
ifeq ($(filter CHIP_ADC_SAR, $(CHIP_ADC_SEL)), CHIP_ADC_SAR)
PP_OPT_COMMON += __ADC_SAR__
endif
ifeq ($(filter CHIP_ADC_ASURA, $(CHIP_ADC_SEL)), CHIP_ADC_ASURA)
PP_OPT_COMMON += __ADC_ASURA__
endif

# Feature_Name = [DRV] SARADC sharing
# Description = Option for sharing PMU SARADC analog resource to Touch Screen and Battery
# Pre_Condition_On = __ADC_SAR__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __ADC_SAR__, $(PP_OPT_COMMON)), __ADC_SAR__)
ifeq (TRUE, $(strip $(CHIP_SHARE_SARADC)))
PP_OPT_COMMON += __SHARE_SAR_ADC_ANALOG_FOR_TOUCH_AND_BATT__
ifeq (TRUE, $(strip $(CHIP_SARADC_STOP_CHARGE_FOR_TOUCH)))
PP_OPT_COMMON += __TEMP_STOP_CHARGE_FOR_TOUCH__
endif
endif
endif

# Feature_Name = [DRV] MCP config table
# Description = Use MCP config table mechanism in download and target
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += MCP_CONFIG_TABLE

#===============================================================================
# ** Protocol stack (RF/L1/L3) OPTIONS **
#===============================================================================
# Description = [RF] Determine whether radio driver for Renesas B6PLD should be included in the software build.
# Pre_Condition_On = Corresponding E2P settings
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RADIO_B6PLD_DIG__

# Description = [RF] Determine whether radio driver for NXP Aero2 should be included in the software build.
# Pre_Condition_On = Corresponding E2P settings
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RADIO_RDA6210_ANALOG__

# Description = [RF] Determine whether radio driver for SKYWORKS 117 should be included in the software build.
# Pre_Condition_On = Corresponding E2P settings
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RADIO_SKY117_ANALOG__

# Description = [RF] RFDL Bugfix
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __BIG2_RFDL_BUG_FIX__

# Description = [RF] Option for RFMD front-end module, which does not need power ramping provided by TBU/RFDL. (Nearly obsolete)
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __HWL_RFMD_TXPWR_MNGT__

# Description = [RF] Integrate RF test mode into nominal software configuration, such that RF tuning and calibration can be done in single software.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_HWL_TINY_INTEGRATED)))
PP_OPT_COMMON += __HWL_TINY_INTEGRATED__
endif

# Description = [RF] Determine whether code implementing frequency compensation for PA (power, ramping, ..) is included.
# Pre_Condition_On = Corresponding E2P setting
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __PA_FREQ_COMP__

# Description = [RF] Determine whether code implementing frequency compensation for RX (mainly board gain) is included.
# Pre_Condition_On = Corresponding E2P setting
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __RX_FREQ_COMP__

# Description = [L1C] When this MAKE option is closing, L1C_IDLE_MEAS_IND is triggered when MSR_IDLE_TIMER expires. When this MAKE option is opening, L1C_IDLE_MEAS_IND is triggered only at BCCH or CCCH.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __REMOVE_MSR_IDLE_TIMER__

# Description = Option to activate bug fix of wrong MP_CHANGE_MARK management
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += _MP_CHANGE_MARK_

# Description = [L1C] Self-explanatory enough, determine whether L1C support GPRS functions
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __L1C_GPRS__

# Description = [L1C] Self-explanatory enough, determine whether L1C support GPRS functions
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __L1C_EGPRS__

# Description = [L1C] Turn on more L1 traces for debugging purpose.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
#PP_OPT_COMMON += __L1C_MORE_TRC__
endif

# Description = [L1C] Determine whether old L1/L3 interface (PH_XXX) is used. The difference is mainly in idle mode control.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __NO_OLD_L1C_MSG__

# Description = [L1C] If turning on this option, HACTIM will be executed in ISR thread, otherwise in the highest priority task. HACTIM is core GSM/GPRS routine and extremely timing critical, executing it in task thread is prone to be disturbed by other thread and harm GSM/GPRS behavior.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __NO_HACTIM_TASK__

# Description = [L1C] Turn on enhancement of sleep behavior. The enhancement is achieved by omitting L1 job anticipation, calculate sleep time more efficient and accurate.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __EXTENDED_SLEEP_MODE__

# Description = [L1C] Turn on 1-frame anticipation.
# Pre_Condition_On = __EXTENDED_SLEEP_MODE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __EXTENDED_SLEEP_MODE_PH2__

# Description = [L1C] Turn on further late wake-up and early sleep.
# Pre_Condition_On = __EXTENDED_SLEEP_MODE__, __EXTENDED_SLEEP_MODE_PH2__, __L1_SPEED_MANAGER__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __EXTENDED_SLEEP_MODE_PH3__

# Description = [L1C] Toolkit to coordinate short-term CPU speed increasing with long-term speed configuration.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __L1_SPEED_MANAGER__

# Description = [L1C] Toolkit to coordinate short-term CPU speed increasing with long-term speed configuration.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __DUMMY_PCH_DETECTION__

# Description = [L1C] Turn on feature which receive only 2 burst for each paging under good channel condition (4 originally). This helps in standby time.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __REDUCED_PAGING__

# Description = [L1C] Turn on feature which receive only 2 burst for each BCCH under good channel condition (4 originally). This helps in standby time.
# Pre_Condition_On = __REDUCED_PAGING__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __REDUCED_BCCH__

# Description = [L1] Turn on __1R7M_SUPPORT__ for a max of 7 measurement windows in the first frame of a paging block
# Pre_Condition_On = __REDUCED_PAGING__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __1R7M_SUPPORT__

# Description = [L1] Turn on __OPTIMIZED_MON_CELL_LIST_USAGE__ for optimizing monitor cell list
# Pre_Condition_On = __1R7M_SUPPORT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __OPTIMIZED_MON_CELL_LIST_USAGE__

# Description = [L1] Turn on __SPEED_UP_POWER_CAMPAIGN__ for a max of 7 measurement windows in PowerCampaign
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __SPEED_UP_POWER_CAMPAIGN__

# Description = [Audio] Workaround "guitar noise" which usually seen in uplink direction while HR speech codec is used. We do some trick in uplink DTX to prevent the problem.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __GUITAR_NOISE_WORKAROUND__

# Description = [Audio] Prevent or alleviate the audible pop noise caused by sudden speech signal on/off, by implementing fade-in and fade-out at transition.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __HANDOVER_POP_SUPPRESSION__

# Description=[DSP] DSP download by DSMA
# Pre_Condition_On= N/A
# Pre_Condition_Off= N/A
# Option_Selection= N/A
ifeq ($(filter __DSP_B3__, $(PP_OPT_COMMON)), __DSP_B3__)
PP_OPT_COMMON += __DSP_DOWNLOAD_BY_DSMA__
endif

# Description=[DSP] DSP download by DPRAM
# Pre_Condition_On= N/A
# Pre_Condition_Off= N/A
# Option_Selection= N/A
ifeq ($(filter __DSP_BRAVO__, $(PP_OPT_COMMON)), __DSP_BRAVO__)
PP_OPT_COMMON += __DSP_DOWNLOAD_BY_DPRAM__
endif

# Description=[DSP] DSP AEC selection
# Pre_Condition_On= N/A
# Pre_Condition_Off= N/A
# Option_Selection= N/A
ifeq ($(filter __DSP_B3__, $(PP_OPT_COMMON)), __DSP_B3__)
PP_OPT_COMMON += __MSTAR_AEC__
endif

ifeq ($(filter __MSTAR_AEC__, $(PP_OPT_COMMON)), __MSTAR_AEC__)
AEC_VER = __MSTAR_AEC__
else
AEC_VER = __SPIRIT_AEC__
endif

# Description = [SIM] Detemine whether SIM module suppoter smart card protocol T=1
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __WHAT_SIM_T1__

# Description = [PS] Turn on Lower Layer Reset mechanism.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __LOWER_LAYER_RESET__

# Description = [PS] Switch on quad-band support in GRR, L1C, HWL. Stack built with this option is quad-band capable, but with proper E2P setting stack can still operate in dual-band or single band mode. Please note that not all RF transceivers support true quad-band.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __QUAD_BAND_SUPPORT__

# Description = [PS] Switch on dual-SIM support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MSTAR_DUAL_SIM__

# Description = [PS] Switch on QUAD SIM DUAL STANDBY support
# Pre_Condition_On = __MSTAR_DUAL_SIM__
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(CHIP_QUAD_SIM_DUAL_STANDBY)))
PP_OPT_COMMON += __QUAD_SIM_DUAL_STANDBY__
endif
endif

# Description = [IP] Multiple datalink(Multiple PDP)
# Pre_Condition_On = N/A
# Pre_Condition_Off = __3G__
# Option_Selection = N/A
PP_OPT_COMMON += __MULTI_DATALINK__

# Description = [RF] Change to 3 ramps per band and put them into E2P
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __RADIO_MULTIRAMP_IN_E2P__

# Description = [HWL] Turn on more HWL traces for debugging purpose.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
#PP_OPT_COMMON += __HWL_MORE_TRC__
endif

# Description = [HWL] Turn on AMR debug trace
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __HWL_AMR_DBG__

# Description = [HWLRF] Support BLOSMMON TGGE RF
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_TGGE_RF)))
PP_OPT_COMMON += __TGGE_RF__
endif

#===============================================================================
# ** System OPTIONS **
#===============================================================================

# Description = [Debug] Option for source level debugging (the build time would be increased if it is turning on.)
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = TRUE/FALSE
SOURCE_LEVEL_DEBUG = TRUE

# Description = [CHIP] Indicates CPU Core & Platform
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_RTK_OVER_R2)))
PP_OPT_COMMON += __RTK_OVER_R2__
endif

# Description = [SYS] Allow unaligned memory access
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_CONFIG_ALLOW_UNALIGNED_MEM_ACCESS)))
#PP_OPT_COMMON += __CONFIG_ALLOW_UNALIGNED_MEM_ACCESS__
endif

# Description = [CHIP] Change DSP subsystem to R2 DSP which is used in G1
# Pre_Condition_On = __G1__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_UPGRADE_DSP_R2)))
PP_OPT_COMMON += __UPGRADE_DSP_R2__
endif

# Description = [Debug] Enable event-driven trace dump to SD card used protocol stack. This option only determines whether to use the facility. Whether the facility exists is determined by __TMT_TRACE_STORE_SD__.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __PS_DEBUG_TRACE_DUMP__

# Description = [Debug] Enable ANTF default trace
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __ENABLE_REDIRECT_DEFAULT_TRC__

# Description = [Debug] Enable auto store trace to SD
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __AUTO_STORE_TRACE_TO_SD__
endif

ifeq ($(filter __ISW_INFINITY__, $(PP_OPT_COMMON)), __ISW_INFINITY__)
PP_OPT_COMMON += __AUTO_STORE_TRACE_TO_SD__
endif
# Description = [Debug] Enable dumping of TMT trace into SD card while user requests so by pressing special hotkey combination. The intrusion to system behavior is lower than in real-time manner, but this mechanism is also less useful.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
ifneq ($(filter __CORE_SOFTWARE__, $(PP_OPT_COMMON)), __CORE_SOFTWARE__)
PP_OPT_COMMON += __HOTKEY_TRACE_DUMP__
endif
endif

ifeq ($(filter __ISW_INFINITY__, $(PP_OPT_COMMON)), __ISW_INFINITY__)
PP_OPT_COMMON += __HOTKEY_TRACE_DUMP__
endif
# Description = [Debug] Enable Hot Key Frequency mechainsm.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(HOT_KEY_FREQUENCY_SUPPORT)))
PP_OPT_COMMON += __DRV_HOT_KEY_FREQUENCY__
endif

# Description = [SYS] RTK internal compile option
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __RTK_RELEASE__

# Description = [SYS] Use GKI heap algorithm
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __GKI_HEAP__

# Description = [SYS] Use generic memory management
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __GMM__

# Description = [SYS] Directy GetMemory to AllocateMemory
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MEM_GENERIC__

# Description = [SYS] Memory shortage check in idle task
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MEM_SHORT_POLLING_CHECK__

# Description = [SYS] A FINT HISR task
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __FINTHISR__

# Description = [SYS] Null read write protect
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_NULL_READ_WRITE_EXEC_PROTECT)))
PP_OPT_COMMON += __NULL_READ_WRITE_EXEC_PROTECT__
endif

# Description = [SYS] Dump whole ram content as an exception happens
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __RAM_DUMP__
endif

# Description = [SYS] RTK Timer debug info
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RTK_TIMER_INFO__

# Description = [SYS] RTK internal debug option
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __DEBUG__

# Description = [SYS] Enable software watchdog mechanism
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __SOFTWARE_WATCHDOG__

# Description = [SYS] Enable kernel debug mechanism
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __KERNEL_DEBUG__

# Description = [SYS] Move kernel memory critical section to IMI
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MEM_CRITICAL_TO_IMI__

# Description = [SYS] If this flag is set, user can not allocate heap with 0 byte.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __HEAP_MEM_NULL_CHECK__

# Description = [SYS] Enable RTK back-trace enhance debug mechanism
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __RTK_DIAGNOSE_ENHANCE__
endif

# Description = [SYS] Enable RTK periodic timer function
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __RTK_TIMER_PERIODIC__


# Description = [SYS] enhance RTK get os tick function
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RTK_OSTICK_ENHANCE__


# Description = [SYS] Enable RTK Send suspension
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __RTK_SEND_SUSPENSION__
endif

# Description = [SYS] Provide kernel and user interrupt control
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __SEPARATE_INTERRUPT_API__
endif

# Description = [Debug] functional level porfiling
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
ifeq (TRUE, $(strip $(CHIP_RTK_PROFILE_ENHANCE)))
PP_OPT_COMMON += __RTK_PROFILE_ENHANCE__
endif
endif

# Description = [SYS] Enhance call stack overflow check
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
ifeq ($(filter __KERNEL_DEBUG__, $(PP_OPT_COMMON)), __KERNEL_DEBUG__)
PP_OPT_COMMON += __RTK_STACK_DIAGNOSE__
endif
else
ifeq ($(filter __INFINITY__, $(PP_OPT_COMMON)), __INFINITY__)
ifeq ($(filter __KERNEL_DEBUG__, $(PP_OPT_COMMON)), __KERNEL_DEBUG__)
PP_OPT_COMMON += __RTK_STACK_DIAGNOSE__
endif
endif
endif

# Description = [SYS] Enable CPU speed profile check mechanism in sleep mode
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __SYS_SOFTWARE_CPU_SPEED_CHECKING__

# Description = [SYS] Check CPU speed before sleep
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHECK_CPU_STATUS_BEFORE_SLEEP_SUPPORT)))
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __CHECK_CPU_STATUS_BEFORE_SLEEP__
endif
endif

# Description = [SYS] Enable HW watchdog timeout information
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __RTK_HW_WATCHDOG_DIAGNOSE_ENHANCE__
endif

# Description = [SYS] Enable HW watchdog to FIQ
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __HW_WATCHDOG_FIQ__
endif

# Description = [SYS]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __DEBUG_FILL_HOLE__

# Feature_Name = __MMU_DLMA__
# Description = Support virtual memory address for static linked DLM
# Pre_Condition_On = CHIP_MMU_DLMA
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_MMU_DLMA)))
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __MMU_DLMA__
endif
endif

# Description = [SYS] Read efuse for chip type identification
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __CHIP_TYPE_EFUSE__

# Description = [SYS] API to print trivial, non-critical traces
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __TRIVIAL_TRACES__

# Description = [SYS] Enable Backtrace Compression
# Pre_Condition_On = __SMALL_ROM__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __BACKTRACE_COMPRESSED__
endif

# Description = [SYS] Auto Cpu Speed
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_AUTO_CPU_SPEED)))
PP_OPT_COMMON += __AUTO_CPU_SPEED__
endif

# Description = [SYS] Time Slice Scheduling
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __TIME_SLICE_SCHEDULE__


# Feature_Name = [SYS] Ram text/data compression
# Description = Option to support Ram text/data compression
# Pre_Variable_True = __SMALL_ROM__
# Pre_Variable_False = __CORE_SOFTWARE__ __JAVA_OAKMONT__ __JAVA_OAKMONT_JAP0__ __JAVA_OAKMONT_JAP2__
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)),)
ifeq ($(filter __CORE_SOFTWARE__ __JAVA_OAKMONT__ __JAVA_OAKMONT_JAP0__ __JAVA_OAKMONT_JAP2__, $(PP_OPT_COMMON)),)
ifneq (TRUE, $(strip $(CHIP_HW_ZLIB)))
PP_OPT_COMMON += __BOOT_UNCOMPRESS__
endif
endif
endif

# Feature_Name = JUMP instructions compress
# Description = Option to modify JMP relative address to JMP absolute address
# Pre_Variable_True = __SMALL_ROM_32__
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
CMPR_PRE_PROC = JMP_OPT_ABSADR
endif

# Feature_Name = [SYS] Rom compression
# Description = Option to support Rom compression
# Pre_Variable_True = __SMALL_ROM__, __SMALL_ROM_32__, __BOOT_UNCOMPRESS__, SDK_API_WAP_MMS_ONLY_SUPPORT, RTK_OVER_ARM_SLDLM_SUPPORT, __BOOT_SLDLM__
# Pre_Variable_False = __CORE_SOFTWARE__
# Option_Selection = N/A
ifeq ($(filter __CORE_SOFTWARE__, $(PP_OPT_COMMON)),)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
ifeq ($(filter __BOOT_UNCOMPRESS__, $(PP_OPT_COMMON)),__BOOT_UNCOMPRESS__)
ifeq (TRUE, $(strip $(CHIP_EXTRACT_BOOT_IMAGE)))
PP_OPT_COMMON += __EXTRACT_BOOT_IMAGE__
endif
endif
ifneq ($(filter __JAVA_OAKMONT__ __JAVA_OAKMONT_JAP0__ __JAVA_OAKMONT_JAP2__, $(JAVA_SOLUTION)),)
$(error conflict on __SMALL_ROM_32__ and OAKMONT JAVA)
endif
ifneq ($(filter __NCC_3RD_JAVA_PORTING_LAYER_M__ __NCC_3RD_JAVA_PORTING_LAYER_S__, $(JAVA_SOLUTION)),)
$(error conflict on __SMALL_ROM_32__ and MJAVA)
endif
endif
endif

# Description = [SYS] Enable boot init section in SLDLM
# Pre_Condition_On = RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
ifeq ($(filter __EXTRACT_BOOT_IMAGE__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __BOOT_SLDLM__
endif
endif

# Feature_Name = [SYS] Rom compression [extend]
# Description = Option to support Rom compression
# Pre_Variable_True = __SMALL_ROM_32__, __BOOT_SLDLM__, SYS_PHY_RAM_SIZE_SETTING=0x00400000
# Pre_Variable_False = __CORE_SOFTWARE__
# Option_Selection = N/A
ifeq ($(filter __CORE_SOFTWARE__, $(PP_OPT_COMMON)),)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
ifeq ($(filter __BOOT_SLDLM__, $(PP_OPT_COMMON)),__BOOT_SLDLM__)
ifeq (0x00400000, $(strip $(SYS_PHY_RAM_SIZE_SETTING)))
#PP_OPT_COMMON += __COMPRESS_SELECTED_BIN__
#ifeq ($(strip $(SELECTED_BIN_SIZE)),)
#SELECTED_BIN_SIZE := 640
#endif
endif
endif
endif
endif

ifeq (TRUE, $(strip $(CHIP_COMPRESS_SELECTED_BIN)))
ifeq ($(filter __EXTRACT_BOOT_IMAGE__, $(PP_OPT_COMMON)),)
ifeq ($(filter __BOOT_SLDLM__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON+=__BOOT_SLDLM__
endif
ifeq ($(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON+=__COMPRESS_SELECTED_BIN__
ifeq ($(strip $(SELECTED_BIN_SIZE)),)
SELECTED_BIN_SIZE := 0
endif
endif
endif
endif


ifeq ($(filter __COMPRESS_SELECTED_BIN__, $(PP_OPT_COMMON)),__COMPRESS_SELECTED_BIN__)
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)),)
ifeq ($(filter __BOOT_UNCOMPRESS__, $(PP_OPT_COMMON)),)
ifneq ($(strip $(SELECTED_BIN_SIZE)),0)
$(error __COMPRESS_SELECTED_BIN__ need __BOOT_UNCOMPRESS__)
endif
endif
else
ifneq ($(filter __BOOT_UNCOMPRESS__, $(PP_OPT_COMMON)),)
$(error could not turn on __BOOT_UNCOMPRESS__ in NAND product)
endif
endif
ifeq ($(filter __EXTRACT_BOOT_IMAGE__, $(PP_OPT_COMMON)),__EXTRACT_BOOT_IMAGE__)
$(error conflict on __COMPRESS_SELECTED_BIN__ and __EXTRACT_BOOT_IMAGE__)
endif
endif

# Description = [SYS] SD download
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_SD_DOWNLOAD)))
PP_OPT_COMMON += __SD_DOWNLOAD__
endif


#===============================================================================
# ** Middleware (VML/ATI/RIL/MML) OPTIONS **
#===============================================================================
# Description = [Middleware] Turn on the feature that ATI sends +WIND: 18 unsolicited indication when a call is connected.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __FEATURE_STK_CALL__

# Description = [Middleware] Originally, it means that ATI acts as MMI. But this option is abandoned now, turning it on is meaningless.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __ATI_MMI__

# Description = [Middleware] Quite self-explanatory, it turns on CPHS (Common PCN Handset Specification) support.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __CPHS__

# Description = [Middleware] Turn on E-ONS (Enhanced Operator Name String) support.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __E_ONS__

# Description = [Middleware] Turn on ENS (Enhanced Network Selection) support.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_ENS)))
PP_OPT_COMMON += __ENS__
endif

# Description = [Middleware] Turn on ME personalization lock mode.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __LOCK_CNL__

# Description = [Middleware] Provide function-call-based interface for socket service. But our applications use message-based interface instead.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __IP_DIRECT_DATAFLOW__

# Description = [Middleware] Instead of providing full, world-wide operator name mapping, only operators in China, Hong-Kong and Taiwan are recognized.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __VML_REDUCED_PLMN_LIST__

# Description = [Middleware] SIM file access service is provided in a way that full path/name should be specific rather than file name only.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_FULL_SIM_PATH)))
PP_OPT_COMMON += __FULL_SIM_PATH__
endif

# Description = [Middleware] Protect flash object access by semaphore.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MMT_AFO_SEMAPHORE__

# Description = [Middleware] Turn on support of SyncML
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __SYNCML__

# Description = [Middleware] Indicate that VML MSL service is enabled, which provides the service of socket and GPRS session.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MSL__

# Description = [Middleware] Abandoned now. In old MMI platform, this option determine whether RIL or VML/MML is used.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __USE_MRL__

# Description = [Middleware] silent reboot
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_ENABLE_DBB_SILENT_REBOOT)))
PP_OPT_COMMON += __ENABLE_DBB_SILENT_REBOOT__
endif

# Description = [Middleware] Turn on multi-pipe support in RIL, such that more than one command thread can be performed simultaneously.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MULTI_PROXY__

# Description = [Middleware] Enable dual-SIM support of RIL.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_DUO_MRL)))
PP_OPT_COMMON += __DUO_MRL__
endif

# Description = [Middleware] Determine whether MML sits directly on VML (rather than via RIL/ATI), which is old, abandaned architecture.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __MML_ON_VML__

# Description = [Middleware] Remove logic not used by MMI/modem/production/GCF for core size reduction
# Pre_Condition_On = N/A
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_CSR_ATI_VML)))
PP_OPT_COMMON += __CSR_ATI_VML__
endif

# Description = [Middleware] GPRS auto attach when test sim is inserted
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __TEST_SIM_AUTOATTACH__

# Feature_Name = [Middleware] Support Network Counter App
# Description = To support Network Counter App
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = = N/A
PP_OPT_COMMON += __NETWORK_COUNTER_MDL__

# Feature_Name = [Middleware] Support MDL low memory mode
# Description = use low memory for VDR/IMG Viewer/Video player
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = = N/A
ifeq (TRUE, $(strip $(MDL_LOW_MEMORY)))
PP_OPT_COMMON += __MDL_LOW_MEMORY__
endif

#===============================================================================
# ** MMI OPTIONS **
#===============================================================================
# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __FEATURE_POWER_CONSUMPTION_LOG__
endif

# Description = [MMI] Enable main menu grid/list style
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __UI_STYLE_MMI_MAIN_MENU_GRID_AND_LIST__

# Description = [MMI] Use softkey as clear key
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MMI_SOFTKEY_AS_CLEAR__

# Description = [MMI] Enable dedicate power key UI
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __DEDICATE_POWER_KEY__

# Description = [MMI] Support hotkey launch keyguard
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(COMPOSITE_HOTKEY_LAUNCH_KEYGUARD_SUPPORT)))
PP_OPT_COMMON += __MMI_COMPOSITE_HOTKEY_LAUNCH_KEYGUARD__
endif

# Description = [MMI] Enable QQ application
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __MMI_QQ__

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifneq ($(filter __SDK_API_WAP_MMS_ONLY__, $(PP_OPT_COMMON)), __SDK_API_WAP_MMS_ONLY__)
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (NQQ, $(strip $(QQ_SOLUTION)))
PP_OPT_COMMON += __NCCQQ_MMI__
PP_OPT_COMMON += __MOBILE_QQ_V10__
PP_OPT_COMMON += __MULTIPLE_QQ__
else
ifeq (TENCENT_QQ, $(strip $(QQ_SOLUTION)))
ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __TENCENT_MCARE__
PP_OPT_COMMON += __TENCENT_WAP_SELECTION__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_TENCENT_MCARE__
endif
else
ifeq (TRUE, $(strip $(SDK_BACKGROUND_EXECUTION_SUPPORT)))
PP_OPT_COMMON += __TENCENT_MCARE__
PP_OPT_COMMON += __TENCENT_WAP_SELECTION__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_TENCENT_MCARE__
endif
endif

endif

endif
endif

ifeq (TENCENT_QXIN, $(strip $(QQ_SOLUTION)))
ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __TENCENT_MCARE__
PP_OPT_COMMON += __TENCENT_MCARE_QXIN__
PP_OPT_COMMON += __TENCENT_WAP_SELECTION__
else
ifeq (TRUE, $(strip $(SDK_BACKGROUND_EXECUTION_SUPPORT)))
PP_OPT_COMMON += __TENCENT_MCARE__
PP_OPT_COMMON += __TENCENT_MCARE_QXIN__
PP_OPT_COMMON += __TENCENT_WAP_SELECTION__
endif
endif
endif
endif



endif
endif
endif
endif

# Description = Enable SSL library
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (POLARSSL, $(strip $(SSL_SOLUTION)))
PP_OPT_COMMON += __ENABLE_POLARSSL__
endif

# Feature_Name = Support Simplified Chinese
# Description = Turn on this option, it will enable Simplified Chinese related character tranlation (e.g. GB2312 to unicode; PINYIN..etc)
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHINESE_S_SUPPORT)))
PP_OPT_COMMON += __CHINESE_S__
endif

# Feature_Name = Support Traditional Chinese
# Description = Turn on this option, it will enable Traditional Chinese related character tranlation  (e.g. Big5 to unicode; PINYIN..etc)
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHINESE_T_SUPPORT)))
PP_OPT_COMMON += __CHINESE_T__
endif

# Description = [MMI] Enable Big5 string to unicode string conversion function
# Pre_Condition_On = __CHINESE_T__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __CHINESE_T__, $(PP_OPT_COMMON)), __CHINESE_T__)
PP_OPT_COMMON += __BIG5_TO_UNICODE__
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __UNICODE_TO_BIG5__
endif
endif

# Description = [MMI] Enable GB2312 and unicode string conversion function
# Pre_Condition_On = __CHINESE_S__, UNICODE_TO_GB2312_CONVERSION
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __CHINESE_S__, $(PP_OPT_COMMON)), __CHINESE_S__)
PP_OPT_COMMON += __GB2312_TO_UNICODE__
ifeq (TRUE, $(strip $(UNICODE_TO_GB2312_CONVERSION)))
PP_OPT_COMMON += __UNICODE_TO_GB2312__
endif
PP_OPT_COMMON += __DECODER_USE_GB2312__
endif

# Description = [MMI] Enable Pinyin sorting / lunar calendar
# Pre_Condition_On = __CHINESE_S__ or __CHINESE_T__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __CHINESE_S__ __CHINESE_T__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __UNICODE_TO_PINYIN__
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __LUNAR_CALENDAR_MMI__
endif
endif

# Description = [MMI] Enable RAI Compression mechanism
# Pre_Condition_On = __SMALL_ROM__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),__SMALL_ROM__)
PP_OPT_COMMON += __RAI_COMPRESSION_MMI__
endif

# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __WINTONE__

# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __MMS__ __WAP__ __SDK_API__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __MSERVICES__
endif

# Description = [MMI] GPRS Support
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __MMS__ __WAP__ __SDK_API__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __GPRS_MMI__
endif

# Feature_Name = Content DB
# Description = Option to support content DB
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __DB_MMI_CONTENTDB__

# Feature_Name = SQLite
# Description = Enable Option to support SQLite.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(SQLITE_SUPPORT)))
PP_OPT_COMMON += __SQLITE__
endif

# Feature_Name = MMI POWER ON TIME INFORMATION
# Description = [MMI] Profiling MMI power on time
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __MMI_POWER_ON_TIME_INF__
endif

# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __APP_E2P_MML__

# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RELEASE_FOR_3RD_VENDOR__

# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __XMMI__

# Feature_Name = Hopper
# Description = Option for a hopper to testing bug
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __HOPPER__
endif

# Feature_Name = [MMI] OTA Provisioning
# Description = Option for OTA Provisioning
# Pre_Condition_On = __WAP__, WAP_OTA_SUPPORT
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(WAP_OTA_SUPPORT)))
ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
PP_OPT_COMMON += __WAP_MMI_OTA_PROV__
endif
endif

# Feature_Name = Fuzzy number search
# Description = Turn on this option, it will enable fuzzy number search in phonebook
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(SMART_NUMBER_FILTER_SUPPORT)))
PP_OPT_COMMON += __MMI_PHB_SMART_NUMBER_FILTER_SUPPORT__
endif

# Feature_Name = Smart Dialer
# Description = Turn on this option, it will enable quick number search in dialer
# Pre_Condition_On = __LCM_QCIF_PLUS__ __LCM_QVGA__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_HVGA__ __LCM_WQVGA_240_400__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__
# Pre_Condition_Off = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter $(LCM_RESOLUTION), __LCM_QCIF_PLUS__ __LCM_QVGA__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_HVGA__ __LCM_WQVGA_240_400__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_WVGA__ __LCM_LANDSCAPE_WVGA__), $(strip $(LCM_RESOLUTION)))
ifeq (TRUE, $(strip $(SMART_DIALER_SUPPORT)))
PP_OPT_COMMON += __SMART_DIALER__
PP_OPT_COMMON += __MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__
PP_OPT_COMMON += __MMI_PHB_SMART_NUMBER_FILTER_SUPPORT__
endif
endif

# Feature_Name = Speed Dialer
# Description = Option to enable hash key speed dialer function
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
SPEED_DIALER_SUPPORT = FALSE
else
SPEED_DIALER_SUPPORT = TRUE
endif

ifeq (TRUE, $(strip $(SPEED_DIALER_SUPPORT)))
PP_OPT_COMMON += __SPEED_DIALER_MMI__
endif

# Feature_Name = Shortcut Speed Dialer
# Description = Option to enable shortcut speed dialer function
# Pre_Variable_True = SHORTCUTLIST_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
DIAL_SHORTCUT_SUPPORT = FALSE
else
DIAL_SHORTCUT_SUPPORT = TRUE
endif

ifeq (TRUE, $(strip $(SHORTCUTLIST_SUPPORT)))
ifeq (TRUE, $(strip $(DIAL_SHORTCUT_SUPPORT)))
PP_OPT_COMMON += __DIAL_SHORTCUT_MMI__
endif
endif

# Feature_Name = Digit to laphabet mapping search
# Description = Turn on this option, it will enable digit to laphabet mapping search in phonebook
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = TRUE, FALSE
#PP_OPT_COMMON += __DIGIT_TO_ALPHABET__
ifeq (TRUE, $(strip $(SMART_ALPHABET_FILTER_SUPPORT)))
PP_OPT_COMMON += __MMI_PHB_SMART_ALPHABET_FILTER_SUPPORT__
endif

# Feature_Name = [MMI] MMS read report
# Description = Option for MMS read report
# Pre_Condition_On = __MMS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MMS__, $(PP_OPT_COMMON)), __MMS__)
ifeq (TRUE, $(strip $(MMS_READ_REPORT_SUPPORT)))
PP_OPT_COMMON += __MMS_READ_REPORT__
endif
endif

# Feature_Name = [MMI] MMS file deleter
# Description = Option for MMS file deleter before sending MMS
# Pre_Condition_On = __MMS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MMS__, $(PP_OPT_COMMON)), __MMS__)
ifeq (TRUE, $(strip $(USER_FILE_DELETER_SUPPORT)))
PP_OPT_COMMON += __USER_FILE_DELETER__
endif
endif

# Feature_Name = [MMI] MMS download limit size
# Description = Option to define MMS download limit size
# Pre_Condition_On = __MMS_MMI_CDMMS__
# Option_Selection = N/A
ifeq ($(filter __MMS_MMI_CDMMS__, $(PP_OPT_COMMON)), __MMS_MMI_CDMMS__)
ifeq (FALSE, $(strip $(MMS_DOWNLOAD_LIMIT_SUPPORT)))
PP_OPT_COMMON += __MMS_DOWNLOAD_LIMIT__
endif
endif

# Feature_Name = Picture Viewer enable slideshow function
# Description = Option to enable picture viewer enable slideshow feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_PICVIEWER_SLIDESHOW_ENABLE__
endif

# Feature_Name = Picture Viewer enable set contact function
# Description = [MMI] Option to enable picture viewer enable set contact feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_PICVIEWER_SET_CONTACT_ENABLE__
endif

# Feature_Name = Picture Viewer enable ZOOM function
# Description = Option to enable picture viewer enable zoom in/out feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_PICVIEWER_ZOOM_ENABLE__
endif

# Feature_Name = Picture Viewer moving seamless in Zoom view
# Description = [MMI] Picture Viewer, to enable moving display area in zoom view without showing black area.
#                     This has better user impression, but need some additional memory.
# Pre_Condition_On = __MMI_PICTURE_ZOOM_ENABLE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MMI_PICVIEWER_ZOOM_ENABLE__, $(PP_OPT_COMMON)), __MMI_PICVIEWER_ZOOM_ENABLE__)
PP_OPT_COMMON += __PICVIEWER_ZOOM_MOVING_SEAMLESS__
endif

ifeq ($(filter __MULTI_TOUCH__, $(PP_OPT_COMMON)), __MULTI_TOUCH__)
ifeq ($(filter __MMI_PICVIEWER_ZOOM_ENABLE__, $(PP_OPT_COMMON)), __MMI_PICVIEWER_ZOOM_ENABLE__)
PP_OPT_COMMON += __PICVIEWER_MULTI_FINGER__
endif
endif

ifeq ($(filter __MULTI_TOUCH__, $(PP_OPT_COMMON)), __MULTI_TOUCH__)
PP_OPT_COMMON += __CAMERA_MULTI_FINGER__
endif

# Feature_Name = Support HW JPEG/JPG Decoder in Picture Viewer(MMI)
# Description = [MMI] Option for supporting hardware JPEG/JPG decoder in Picture Viewer APP
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_IMAGE_JPD_HW_DECODE)))
PP_OPT_COMMON += __PICVIEWERAPP_SUPPORT_HW_JPD_MMI__
endif

# Feature_Name = [MMI] SLIM version of MMI
# Description = Option to use slim-version MMI, including apps, UI layout etc
# Pre_Condition_On = __SMALL_ROM_32__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
PP_OPT_COMMON += __SLIM_MMI__
endif

# Feature_Name = [MMI] Text enumeration for menuitems
# Description = enumerate each menuitem with plain text rather than images
# Pre_Condition_On = __SMALL_ROM_32__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
PP_OPT_COMMON += __TEXT_ENUM_MENUITEM_MMI__
endif

# Feature_Name = EM Audio support
# Description = Option for EM Audio support
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq ($(filter B3, $(CHIP_EM_AUDIO_SEL)), B3)
PP_OPT_COMMON += __EM_AUDIO_B3__
endif

ifeq ($(filter BRAVO, $(CHIP_EM_AUDIO_SEL)), BRAVO)
PP_OPT_COMMON += __EM_AUDIO_BRAVO__
endif

ifeq ($(filter B5, $(CHIP_EM_AUDIO_SEL)), B5)
PP_OPT_COMMON += __EM_AUDIO_B5__
endif

# Feature_Name = Engineering Mode Audio APP to SD Feature (MMI)
# Description = [MMI] Option for Engineering Mode Audio APP to SD Feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
ifeq (TRUE, $(strip $(MMI_EM_AUDIO_APPTOSD_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_EM_AUDIO_APPTOSD__
endif
endif

# Feature_Name = Simulator Chip support
# Description = Option for Simulator Chip support
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq ($(filter B3, $(CHIP_SIMULATOR_SEL)), B3)
PP_OPT_COMMON += __SIMULATOR_B3__
endif

ifeq ($(filter G1, $(CHIP_SIMULATOR_SEL)), G1)
PP_OPT_COMMON += __SIMULATOR_G1__
endif

# Feature_Name = Factory mode format internal
# Description = Turn on this option, it will format internal flash in factory mode
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(FACTORY_MODE_FORMAT_INTERNAL_FLASH)))
PP_OPT_COMMON += __MMI_FACTORY_FORMAT_INTERNAL_FLASH__
endif

# Feature_Name = Support Network Setting Cus
# Description = [MMI]
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(MMI_NETWORK_SETTING_CUS_SUPPORT)))
PP_OPT_COMMON += __NETWORK_SETTING_CUS__
endif

# Feature_Name = Support SIM NO Response
# Description = To support SIM NO Response
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = = N/A
ifeq (TRUE, $(strip $(SIM_NO_RESPONSE_HANDLING_SUPPORT)))
PP_OPT_COMMON +=__SIM_NO_RSP_HANDLING__
endif

# Feature_Name = Support all palette 8 image decoded as palette 8 buffer format
# Description = [MMI] Turn on this option, all 8 bit image can be decoded to 8 bit buffer as default
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(MMI_SUPPORT_ALL_PALETTE8_IMAGE)))
PP_OPT_COMMON += __SUPPORT_ALL_PALETTE8_IMAGE__
endif

#===============================================================================
# RFID related options
#===============================================================================
ifneq (,$(strip $(RFID_CHIP_TYPE)))
PP_OPT_COMMON += __RFID__
PP_OPT_COMMON += __RFID_E2P__
PP_OPT_COMMON += __SUPPORT_ABL_INTERFACE__
PP_OPT_COMMON += __RFID_MML_SUPPORT__

# RFID AP Related Options
#PP_OPT_COMMON += __RFID_MMI__
#PP_OPT_COMMON += __RFID_AUTO_UPD_FW__
#PP_OPT_COMMON += __RFID_BIZ__

ifeq (__MSR3110__, $(strip $(RFID_CHIP_TYPE)))
PP_OPT_COMMON += __USE_MSR3110__
PP_OPT_COMMON += __SUPPORT_JSR257__
#PP_OPT_COMMON += __SUPPORT_SIM_SWITCH__
endif	# ifeq (__MSR3110__, $(strip $(RFID_CHIP_TYPE)))

ifeq (__MSR3320__, $(strip $(RFID_CHIP_TYPE)))
PP_OPT_COMMON += __USE_MSR3320__
endif	# ifeq (__MSR3320__, $(strip $(RFID_CHIP_TYPE)))

ifeq (__MSR3330__, $(strip $(RFID_CHIP_TYPE)))
PP_OPT_COMMON += __USE_MSR3330__
endif	# ifeq (__MSR3330__, $(strip $(RFID_CHIP_TYPE)))

#RFID Chip Command Interface
ifneq (,$(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_UART0__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_UART0__
endif	# ifeq (__RFID_CMD_ITF_UART0__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_UART1__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_UART1__
endif	# ifeq (__RFID_CMD_ITF_UART1__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_STD_SPI__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_STD_SPI__
endif	# ifeq (__RFID_CMD_ITF_STD_SPI__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_GPIO_SPI__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_GPIO_SPI__
endif	# ifeq (__RFID_CMD_ITF_GPIO_SPI__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_PAGING_SPI__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_PAGING_SPI__
endif	# ifeq (__RFID_CMD_ITF_PAGING_SPI__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_STD_I2C__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_STD_I2C__
endif	# ifeq (__RFID_CMD_ITF_STD_I2C__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_GPIO_I2C__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_GPIO_I2C__
endif	# ifeq (__RFID_CMD_ITF_GPIO_I2C__, $(strip $(RFID_COMMAND_ITF_TYPE)))

ifeq (__RFID_CMD_ITF_USB__, $(strip $(RFID_COMMAND_ITF_TYPE)))
PP_OPT_COMMON += __CMD_USE_USB_HID__
endif	# ifeq (__RFID_CMD_ITF_USB__, $(strip $(RFID_COMMAND_ITF_TYPE)))

else	# ifneq (,$(strip $(RFID_COMMAND_ITF_TYPE)))

# Default Command Interface
PP_OPT_COMMON += __CMD_USE_GPIO_SPI__

endif	# ifneq (,$(strip $(RFID_COMMAND_ITF_TYPE)))

#RFID Chip FW Upgrade Interface
ifneq (,$(strip $(RFID_FWUPG_ITF_TYPE)))

ifeq (__RFID_FWU_ITF_CMD__, $(strip $(RFID_FWUPG_ITF_TYPE)))
PP_OPT_COMMON += __FWP_USE_CMD_ITF__
endif	# ifeq (__RFID_FWU_ITF_CMD__, $(strip $(RFID_FWUPG_ITF_TYPE)))

ifeq (__RFID_FWU_ITF_STD_I2C__, $(strip $(RFID_FWUPG_ITF_TYPE)))
PP_OPT_COMMON += __FWP_USE_STD_I2C__
endif	# ifeq (__RFID_FWU_ITF_STD_I2C__, $(strip $(RFID_FWUPG_ITF_TYPE)))

ifeq (__RFID_FWU_ITF_GPIO_I2C__, $(strip $(RFID_FWUPG_ITF_TYPE)))
PP_OPT_COMMON += __FWP_USE_GPIO_I2C__
endif	# ifeq (__RFID_FWU_ITF_GPIO_I2C__, $(strip $(RFID_FWUPG_ITF_TYPE)))

else	#ifneq (,$(strip $(RFID_FWUPG_ITF_TYPE)))

# Default FW Upgrade Interface
PP_OPT_COMMON += __FWP_USE_GPIO_I2C__

endif	#ifneq (,$(strip $(RFID_FWUPG_ITF_TYPE)))

ifneq (,$(strip $(BARCODE_SUPPORT)))
ifeq (TRUE, $(strip $(BARCODE_SUPPORT)))
PP_OPT_COMMON += __BARCODE__
endif	# ifeq (TRUE, $(strip $(BARCODE_SUPPORT)))
endif	# ifneq (,$(strip $(BARCODE_SUPPORT)))

endif	#ifneq (,$(strip $(RFID_CHIP_TYPE)))

#===============================================================================
# ** Other OPTIONS **
#===============================================================================
# Feature_Name = Crash Notification
# Description = Option to support crash notification by SMS
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
#ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
#PP_OPT_COMMON += __CRASH_NOTIFY_SMS__
#endif

# Feature_Name = Target
# Description = Determine whether the resulted software executes on target hardware or other environements (like simulator)
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __TARGET__

# Feature_Name = Diag Error
# Description = To treat compile warning message ID defined in diag_error.ini as compile error
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __DIAG_ERROR__

# Description = Check if there is any duplicate typedef
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __DIAG_DUPDEF__

# Description = Enable auto test script
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(AUTO_TEST_SUPPORT)))
PP_OPT_COMMON += __AUTO_TEST_SCRIPT__
endif

# Description = Enable SDK V1 adaption layer
# Pre_Condition_On = __SDK_API__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
PP_OPT_COMMON += __SDK_MMI_V1_ADAPTION__
endif

# Feature_Name = Fake Vendor
# Description = Option for a fake vendor to prevent frequent merging errors
# Pre_Condition_On = __SDK_API__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
PP_OPT_COMMON += __FAKE_VENDOR__
endif

# Description = Turn on this option, it will enable atsync functionality.
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __MSYNC_TOOL__
endif

# Feature_Name = MCP performance testing
# Description = Option for Psram performance testing feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = __NAND__
# Option_Selection = N/A
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
#PP_OPT_COMMON += __PSRAM_PERF_TEST__
endif

# Feature_Name = Component base configuration
# Description = Option to change to component base product configuration
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A, __COMPONENT_BASE_CONFIGURATION__
PP_OPT_COMMON += __COMPONENT_BASE_CONFIGURATION__

# Feature_Name = NEW AUTO TESTING
# Description = Option to enable new auto testing
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A,
ifeq ($(filter __AUTO_TEST_SCRIPT__, $(PP_OPT_COMMON)), __AUTO_TEST_SCRIPT__)
PP_OPT_COMMON += __NEW_AUTO_TESTING__
endif

# Feature_Name = Compatible chip download flag
# Description = Make Dwlwin to support compatible chip download
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = TRUE , FALSE
ifeq (TRUE, $(strip $(COMPATIBLE_CHIP_SUPPORT)))
PP_OPT_COMMON += __COMPATIBLE_CHIP_SUPPORT__
endif

# Feature_Name = TINY CMD ADC CALIBRATION
# Description = Option to enable ADC Calibration by Tiny command
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_TINY_CMD_ADC_CALIBRATION)))
PP_OPT_COMMON += __TINY_CMD_ADC_CALIBRATION__
endif

#===============================================================================
# ** Dependency handling **
#===============================================================================

#-------------------------------------------------------------------------------
# Indicate libs path, the default value is chip type
#-------------------------------------------------------------------------------
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq ($(filter __MSW8533D__, $(CHIP_TYPE)), __MSW8533D__)
LIBS_PATH_BY_CHIP = __MSW8532_64__
else
LIBS_PATH_BY_CHIP = $(subst __64,_64,$(CHIP_TYPE)64__)
endif
else
LIBS_PATH_BY_CHIP = $(CHIP_TYPE)
endif

ifeq (__NAND__,$(filter __NAND__,$(PP_OPT_COMMON)))
LIBS_PATH_BY_FEATURE = NAND
else
ifeq ($(filter __SMALL_ROM__,$(PP_OPT_COMMON)),__SMALL_ROM__)
LIBS_PATH_BY_FEATURE = NOR_64
else
ifeq (TRUE, $(strip $(CHIP_LIBS_PATH_BY_FEATURE_IS_3G)))
LIBS_PATH_BY_FEATURE = 3G
else
LIBS_PATH_BY_FEATURE = NOR
endif
endif
endif


# Description=[PS] SLDLM reduce codesize
# Pre_Condition_On= N/A
# Pre_Condition_Off= N/A
# Option_Selection= N/A
PP_OPT_COMMON += __SLDLM_STACK_L3__


ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (FALSE, $(strip $(SDK_API_WAP_MMS_ONLY_SUPPORT)))
PP_OPT_COMMON += __NO_GPRS__
endif
endif

ifeq ($(filter __MSTAR_DUAL_SIM__, $(PP_OPT_COMMON)), __MSTAR_DUAL_SIM__)
PP_OPT_COMMON +=                 \
  __MSTAR_DUAL_SIM_MM__          \
  __MSTAR_DUAL_SIM_RR__          \
  __MSTAR_DUAL_SIM_SIM_DUO__     \
  __MSTAR_DUAL_SIM_CE__          \
  __MSTAR_DUAL_SIM_E2P__         \
  __MSTAR_DUAL_SIM_FCM__         \
  __MO_CALL_PREEMPT_GPRS__

# Define options for DUAL SIM MMI feature
#G1 is single SIM, however, current platform cannot close MSTAR_DUAL_SIM compiler option
ifeq (TRUE, $(strip $(CHIP_DUAL_SIM_MMI)))
PP_OPT_COMMON += __DUAL_SIM_MMI__
endif
ifeq (TRUE, $(strip $(CHIP_MSTAR_DUAL_SIM_REDUCE_CODE)))
PP_OPT_COMMON += __MSTAR_DUAL_SIM_REDUCE_CODE__
endif

endif

# Feature_Name = MMCFG
# Description = Multimedia Configuration
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = __MMCFG_1__ (Type-C page mode), __MMCFG_2__ (Type-C burst mode), __MMCFG_3__ (Type-A), __MMCFG_DIPPER__ (Type-A GPS)
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __MMCFG_2__
else
ifeq ($(filter __GPS__, $(PP_OPT_COMMON)), __GPS__)
PP_OPT_COMMON += __MMCFG_DIPPER__
else
PP_OPT_COMMON += __MMCFG_3__
endif
endif

# Feature_Name = MM Middleware
# Description = Option for MM middleware
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MM_MIDDLEWARE__

# Feature_Name = __AMR_REC__
# Description = Option for supporting AMR recording
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __AMR_REC__

ifeq (TRUE, $(strip $(MP3_DEC_SUPPORT)))
PP_OPT_COMMON += ENABLE_MP3_DEC
endif

ifeq (TRUE, $(strip $(AAC_DEC_SUPPORT)))
PP_OPT_COMMON += ENABLE_AAC_DEC
endif

ifeq (TRUE, $(strip $(AMRNB_DEC_SUPPORT)))
PP_OPT_COMMON += ENABLE_AMRNB_DEC
endif

ifeq (TRUE, $(strip $(WAV_DEC_SUPPORT)))
PP_OPT_COMMON += ENABLE_WAV_DEC
endif

ifeq (TRUE, $(strip $(AMRWB_ENC_SUPPORT)))
PP_OPT_COMMON += ENABLE_AMRWB_DEC
else
ifeq (TRUE, $(strip $(AMRWB_DEC_SUPPORT)))
PP_OPT_COMMON += ENABLE_AMRWB_DEC
endif
endif

ifeq (TRUE, $(strip $(WMA_DEC_SUPPORT)))
PP_OPT_COMMON += ENABLE_WMA_DEC
endif

ifeq (TRUE, $(strip $(PCM_ENC_SUPPORT)))
PP_OPT_COMMON += ENABLE_PCM_ENC
endif

ifeq (TRUE, $(strip $(AMRNB_ENC_SUPPORT)))
PP_OPT_COMMON += ENABLE_AMRNB_ENC
endif

ifeq (TRUE, $(strip $(AMRWB_ENC_SUPPORT)))
PP_OPT_COMMON += ENABLE_AMRWB_ENC
endif

ifeq (TRUE, $(strip $(MP3_ENC_SUPPORT)))
PP_OPT_COMMON += ENABLE_MP3L3ENC
endif

ifeq (TRUE, $(strip $(WAV_ENC_SUPPORT)))
PP_OPT_COMMON += ENABLE_WAV_ENC
endif

ifeq (TRUE, $(strip $(AUD_SPECTRUM_SUPPORT)))
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += ENABLE_AUD_SPECTRUM
endif
endif

# Feature_Name = __MDL_VDR__
# Description = Option for video record
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __MDL_VDR__

# Feature_Name = __AUDIO_CODEC__
# Description = Option for audio codecs
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __RTK_OS__

# Feature_Name = Audio Pre-Processer(ARP) Engine ID Maping Rule
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)

PP_OPT_COMMON += __OPT_ARP_ENGINE_V001__

else

ifeq ($(filter USE_ARP_SWAGC, $(CHIP_ARP_AGC)), USE_ARP_SWAGC)
PP_OPT_COMMON += __OPT_ARP_ENGINE_V001__
endif

ifeq ($(filter USE_ARP_B3HWAGC, $(CHIP_ARP_AGC)), USE_ARP_B3HWAGC)
PP_OPT_COMMON += __OPT_ARP_ENGINE_V101__
endif

ifeq ($(filter USE_ARP_G1HWAGC, $(CHIP_ARP_AGC)), USE_ARP_G1HWAGC)
PP_OPT_COMMON += __OPT_ARP_ENGINE_V201__
endif

endif

# Feature_Name = Audio Pre-Processer(ARP) Engine ID Definition
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __AGC_TOOL_CTRL_ENABLE__, $(PP_OPT_COMMON)), __AGC_TOOL_CTRL_ENABLE__)

PP_OPT_COMMON += __OPT_ARP_RUN_ON_TARGET__
PP_OPT_COMMON += __OPT_ARP_ENGINE_ENABLE__

ifeq ($(filter __OPT_ARP_ENGINE_V001__, $(PP_OPT_COMMON)), __OPT_ARP_ENGINE_V001__)
PP_OPT_COMMON += ARP_SW_AGC_ENABLE
TARGET_ARP_ENGINE_ID = __OPT_ARP_ENGINE_V001__
endif

ifeq ($(filter __OPT_ARP_ENGINE_V101__, $(PP_OPT_COMMON)), __OPT_ARP_ENGINE_V101__)
PP_OPT_COMMON += ARP_BIG3HW_AGC_ENABLE
TARGET_ARP_ENGINE_ID = __OPT_ARP_ENGINE_V101__
endif

ifeq ($(filter __OPT_ARP_ENGINE_V201__, $(PP_OPT_COMMON)), __OPT_ARP_ENGINE_V201__)
PP_OPT_COMMON += ARP_G1HW_AGC_ENABLE
TARGET_ARP_ENGINE_ID = __OPT_ARP_ENGINE_V201__
endif

else

$(error "Please Add __AGC_TOOL_CTRL_ENABLE__ Option.")

endif

# Feature_Name = Audio Post-Processer(APP) Engine ID Maping Rule
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
	ifneq (TRUE, $(strip $(BLUETOOTH_A2DP_SUPPORT)))
PP_OPT_COMMON += __OPT_APP_ENGINE_V00A__
	else
		PP_OPT_COMMON += __OPT_APP_ENGINE_V01A__
	endif
else
	ifeq (TRUE, $(strip $(APP_SRS_WOWHD_SUPPORT)))
		ifeq ($(filter USE_APP_SRSWOWHD, $(CHIP_APP_SRSWOWHD)), USE_APP_SRSWOWHD)
		PP_OPT_COMMON += __OPT_APP_ENGINE_VE02__
		else
		$(error "Chip Type Not Support SRS WOWHD")
		endif

	else
ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00F__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V018__
         endif
    endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00E__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V017__
         endif
    endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00D__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V016__
         endif
    endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00C__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00F__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V014__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V008__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V009__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif
    endif
    endif

endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V018__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V028__
         endif
    endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V017__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V027__
         endif
    endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V016__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V026__
         endif
    endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V025__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V014__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V024__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V023__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V022__
         endif
    endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif
    endif
    endif

endif
endif
endif
endif


ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00E__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V017__
         endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00C__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         endif
    endif
    endif


    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V008__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif
    endif

endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V017__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V027__
         endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V025__
         endif
    endif
    endif


    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V023__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif
    endif

endif
endif
endif
endif


ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00D__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V016__
         endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00C__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V009__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif
    endif

endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V016__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V026__
         endif
    endif
    endif

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V025__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V022__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif
    endif

endif
endif
endif
endif


ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00C__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif

endif
endif
endif
endif


ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V015__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V025__
         endif
    endif

    ifneq ($(filter USE_APP_REVERB, $(CHIP_APP_REVERB)), USE_APP_REVERB)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif

endif
endif
endif
endif

ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V00F__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V014__
         endif
    endif
    endif

    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V008__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V009__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif
    endif

endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V014__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V024__
         endif
    endif
    endif

    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V023__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V022__
         endif
    endif
    endif

    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif
    endif

endif
endif
endif
endif


ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V009__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         endif
    endif

    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif

endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V013__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V023__
         endif
    endif

    ifneq ($(filter USE_APP_TIMESTRETCH, $(CHIP_APP_TIMESTETCH)), USE_APP_TIMESTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif

endif
endif
endif
endif

ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V009__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         endif
    endif

    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         endif
    endif

endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (TRUE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))

    ifeq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V012__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V022__
         endif
    endif

    ifneq ($(filter USE_APP_PITCHTRETCH, $(CHIP_APP_PITCHSTETCH)), USE_APP_PITCHTRETCH)
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
         PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
         else
         PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
         endif
    endif

endif
endif
endif
endif

ifeq (FALSE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))
     ifneq ($(filter USE_APP_DRCLIMITER_V2, $(CHIP_APP_LIMITER)), USE_APP_DRCLIMITER_V2)
     PP_OPT_COMMON += __OPT_APP_ENGINE_V005__
     else
     PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
     endif
endif
endif
endif
endif

ifeq (TRUE, $(strip $(APP_MSTAR_BASS_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_REVERB_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_TIMESTRETCH_SUPPORT)))
ifeq (FALSE, $(strip $(APP_MSTAR_PITCHSTRETCH_SUPPORT)))
         ifneq ($(filter USE_APP_BASS, $(CHIP_APP_BASS)), USE_APP_BASS)
     PP_OPT_COMMON += __OPT_APP_ENGINE_V011__
     else
     PP_OPT_COMMON += __OPT_APP_ENGINE_V021__
     endif
endif
endif
endif
endif


	endif
endif

# Feature_Name = Audio Post-Processer(APP) Engine
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __OPT_APP_RUN_ON_TARGET__
PP_OPT_COMMON += __OPT_APP_ENGINE_ENABLE__

ifeq ($(filter __OPT_APP_ENGINE_V005__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V005__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V005__
endif

ifeq ($(filter __OPT_APP_ENGINE_V008__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V008__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIME_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V008__
endif

ifeq ($(filter __OPT_APP_ENGINE_V009__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V009__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V009__
endif

ifeq ($(filter __OPT_APP_ENGINE_V00A__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V00A__)
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_DRC_LIMITER
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V00A__
endif

ifeq ($(filter __OPT_APP_ENGINE_V00C__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V00C__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V00C__
endif

ifeq ($(filter __OPT_APP_ENGINE_V00D__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V00D__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V00D__
endif

ifeq ($(filter __OPT_APP_ENGINE_V00E__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V00E__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V00E__
endif

ifeq ($(filter __OPT_APP_ENGINE_V00F__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V00F__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V00F__
endif

ifeq ($(filter __OPT_APP_ENGINE_V010__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V010__)
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V010__
endif

ifeq ($(filter __OPT_APP_ENGINE_V011__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V011__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V011__
endif

ifeq ($(filter __OPT_APP_ENGINE_V012__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V012__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V012__
endif

ifeq ($(filter __OPT_APP_ENGINE_V013__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V013__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIME_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V013__
endif

ifeq ($(filter __OPT_APP_ENGINE_V014__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V014__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V014__
endif

ifeq ($(filter __OPT_APP_ENGINE_V015__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V015__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V015__
endif

ifeq ($(filter __OPT_APP_ENGINE_V016__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V016__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V016__
endif

ifeq ($(filter __OPT_APP_ENGINE_V017__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V017__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V017__
endif

ifeq ($(filter __OPT_APP_ENGINE_V018__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V018__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V018__
endif

ifeq ($(filter __OPT_APP_ENGINE_V020__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V020__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
PP_OPT_COMMON += ENABLE_BASS
PP_OPT_COMMON += ENABLE_SRSWOWHD
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V020__
endif

ifeq ($(filter __OPT_APP_ENGINE_V021__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V021__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V021__
endif

ifeq ($(filter __OPT_APP_ENGINE_V022__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V022__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V022__
endif

ifeq ($(filter __OPT_APP_ENGINE_V023__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V023__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V023__
endif

ifeq ($(filter __OPT_APP_ENGINE_V024__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V024__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V024__
endif

ifeq ($(filter __OPT_APP_ENGINE_V025__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V025__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V025__
endif

ifeq ($(filter __OPT_APP_ENGINE_V026__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V026__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V026__
endif

ifeq ($(filter __OPT_APP_ENGINE_V027__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V027__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V027__
endif

ifeq ($(filter __OPT_APP_ENGINE_V028__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V028__)
PP_OPT_COMMON += ENABLE_3D_SURROUND
PP_OPT_COMMON += ENABLE_USER_PEQ
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER_V2
PP_OPT_COMMON += ENABLE_SC_FADE
PP_OPT_COMMON += ENABLE_REVERB
PP_OPT_COMMON += ENABLE_TIME_STRETCH
PP_OPT_COMMON += ENABLE_TIMEPITCH_STRETCH
PP_OPT_COMMON += ENABLE_BASS
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V028__
endif

ifeq ($(filter __OPT_APP_ENGINE_V01A__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_V01A__)
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_DRC_LIMITER
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_V01A__
endif

ifeq ($(filter __OPT_APP_ENGINE_VE02__, $(PP_OPT_COMMON)), __OPT_APP_ENGINE_VE02__)
PP_OPT_COMMON += ENABLE_SPEAKER_PEQ
PP_OPT_COMMON += ENABLE_VOL_CONTROL_EXP
PP_OPT_COMMON += ENABLE_SRSWOWHD
PP_OPT_COMMON += ENABLE_SC_FADE
TARGET_APP_ENGINE_ID = __OPT_APP_ENGINE_VE02__
endif


# Feature_Name = Force Turn Off APP IP's Power
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (FALSE, $(strip $(OPT_VIDEO_APP_DRCLIMITER_POWER)))
PP_OPT_COMMON += TURNOFF_VIDEO_APP_DRCLIMITER
endif

ifeq (FALSE, $(strip $(OPT_VIDEO_APP_SPEAKERPEQ_POWER)))
PP_OPT_COMMON += TURNOFF_VIDEO_APP_SPEAKERPEQ
endif

ifeq (FALSE, $(strip $(OPT_A2DP_APP_DRCLIMITER_POWER)))
PP_OPT_COMMON += TURNOFF_A2DP_APP_DRCLIMITER
endif

ifeq (FALSE, $(strip $(OPT_A2DP_APP_SPEAKERPEQ_POWER)))
PP_OPT_COMMON += TURNOFF_A2DP_APP_SPEAKERPEQ
endif

ifeq (TRUE, $(strip $(MIDI_DOWN_SAMPLERATE_SUPPORT)))
PP_OPT_COMMON += __MIDI_DOWN_SAMPLERATE_SUPPORT__
endif

# Description = Option to Enable FM PEQ
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(FM_PEQ_SUPPORT)))
PP_OPT_COMMON += __FM_PEQ_ENABLE__
endif

# Description = Option to Enable ATV PEQ
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(ATV_PEQ_SUPPORT)))
PP_OPT_COMMON += __ATV_PEQ_ENABLE__
endif

# Description = [PS] IP support WLAN
# Pre_Condition_On = __WLAN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WLAN__, $(PP_OPT_COMMON)), __WLAN__)
PP_OPT_COMMON += __WLAN_IP_SUPPORT__
PP_OPT_COMMON += __MDL_EXT__
PP_OPT_DUO += __DUPLICATE_IP_TASK__
endif

# Description = [SYS] Use EMI controller to protect pool clusters
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_EMI_POOL_PROTECT)))
PP_OPT_COMMON += __EMI_POOL_PROTECT__
endif

# Description = [SYS] Support Iram heap allocation
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __I_SW__, $(PP_OPT_COMMON)), __I_SW__)
PP_OPT_COMMON += __IRAM_ALLOC__
endif

# Description = [SYS] Support non-cached buffer allocation
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __NONCACHED_BUFFER__

# Description = [Debug] Enable function of storing TMT trace into SD card in real-time manner. This is extremely useful while debugging in field but imposes very heavy loading to system. Power consumption increases in noticeably and multimedia function may not work correctly.
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __AUTO_STORE_TRACE_TO_SD__, $(PP_OPT_COMMON)), __AUTO_STORE_TRACE_TO_SD__)
PP_OPT_COMMON +=                 \
  __TMT_TRACE_STORE_SD__         \
  __CHECK_TRACE_LOST__
#ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
#PP_OPT_COMMON +=                 \
#  __DYNA_FLASH_FREE_SPACE_INFO__
#endif
# check with Andy.Tso
ifeq (TRUE, $(strip $(CHIP_UPGRADE_GENIE_OVER_SHMCONN)))
PP_OPT_COMMON += __UPGRADE_GENIE_OVER_SHMCONN__
endif
ifeq (TRUE, $(strip $(CHIP_UPGRADE_HSL_OVER_SHMCONN)))
PP_OPT_COMMON += __UPGRADE_HSL_OVER_SHMCONN__
endif
ifeq (TRUE, $(strip $(CHIP_UPGRADE_RAMLOG_OVER_SHMCONN)))
PP_OPT_COMMON += __UPGRADE_RAMLOG_OVER_SHMCONN__
endif
ifeq (TRUE, $(strip $(CHIP_SYNC_VIA_HW_MAILBOX)))
PP_OPT_COMMON += __SYNC_VIA_HW_MAILBOX__
endif

endif

# Description = [SYS] Enable __RM_PROTECT_TX_BUFFER__
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __RM_PROTECT_TX_BUFFER__

# Description = [SYS] __COARSE_TIMER__
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_COARSE_TIMER)))
PP_OPT_COMMON += __COARSE_TIMER__
endif

# Description = [SYS] Enable Hardware watchdog enhance debug meechanism
# Pre_Condition_On = __RTK_DIAGNOSE_ENHANCE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_DIAGNOSE_ENHANCE__)
PP_OPT_COMMON += __RTK_WATCHDOG_DIAGNOSE_ENHANCE__
endif

PP_OPT_COMMON += __RTK_WATCHDOG_DIAGNOSE_ENHANCE__

# Description = [SYS] Lmit each mailbox size
# Pre_Condition_On = __RTK_DIAGNOSE_ENHANCE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_DIAGNOSE_ENHANCE__)
PP_OPT_COMMON += __EXPHDL_LIMIT_MBOX_SIZE__
endif

# Description = [SYS] Enable to record system history
# Pre_Condition_On = __RTK_DIAGNOSE_ENHANCE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_DIAGNOSE_ENHANCE__)
PP_OPT_COMMON += __EXPHDL_RECORD_SYS_HISTORY__
endif

# Description = [SYS] Enable to record the last primitive of each task
# Pre_Condition_On = __RTK_DIAGNOSE_ENHANCE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_DIAGNOSE_ENHANCE__)
PP_OPT_COMMON += __EXPHDL_RECORD_LAST_MSG__
endif

# Description = [SYS] Enable to backup the exception log
# Pre_Condition_On = __RTK_DIAGNOSE_ENHANCE__
# Pre_Condition_Off = N/A
# Option_Selection= N/A
#ifeq ($(filter __RTK_DIAGNOSE_ENHANCE__, $(PP_OPT_COMMON)), __RTK_DIAGNOSE_ENHANCE__)
#PP_OPT_COMMON += __EXPHDL_BACKUP_EXCEPTION__
#endif

# Description = [SYS] Enable VFS test case
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __VFS_TEST_CASE__

# Description = [SYS] Speech CTA cheating mode
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __DSP_B3__ __DSP_BRAVO__, $(PP_OPT_COMMON)), )
PP_OPT_COMMON += __SPEECH_CTA_CHEATING_MODE__
endif

PP_OPT_COMMON +=                 \
  __SHARE_MEM_DRV__              \
  __SHARE_MEM_SYS__


# Feature_Name = Dual Camera (DRV)
# Description = [DRV] Enable dual camer driver layer
# Pre_Condition_On = __DUAL_CAM__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __DUAL_CAM__, $(PP_OPT_COMMON)), __DUAL_CAM__)
PP_OPT_COMMON += __SENSORTABLE_DRV_DUAL__
PP_OPT_COMMON += __DUAL_CAMERA_MMI__
endif

# Feature_Name = Bluetooth Feature
# Description = Bluetooth Feature
ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifneq ($(filter __CORE_SOFTWARE__, $(PP_OPT_COMMON)), __CORE_SOFTWARE__)
ifneq (,$(strip $(BLUETOOTH_CHIP)))#NULL
PP_OPT_COMMON += $(BLUETOOTH_CHIP)
PP_OPT_COMMON += __BLUETOOTH__
PP_OPT_COMMON += __BLUETOOTH_OBEX__
PP_OPT_COMMON += __BLUETOOTH_DRV__
PP_OPT_COMMON += __BLUETOOTH_MMI__
PP_OPT_COMMON += __BTSRV_WRITE_BT_ADDR__
ifeq (__BLUETOOTH_DRV_RDA5868__, $(strip $(BLUETOOTH_CHIP)))
PP_OPT_COMMON += __BLUETOOTH_RDA_STACK__
PP_OPT_COMMON += __BLUETOOTH_CONCURRENT_LIMIT_MMI__
else #__BLUETOOTH_DRV_RDA5868__
ifeq (__BLUETOOTH_DRV_MSTAR__, $(strip $(BLUETOOTH_CHIP)))
PP_OPT_COMMON += __BLUETOOTH_DRV_MSTAR_ACRUX2__
PP_OPT_COMMON += __BLUETOOTH_ACRUX2_CONCURRENT_LIMIT_MMI__
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __ENABLE_SLDLM_BLUETOOTH__
endif
endif
endif #__BLUETOOTH_DRV_RDA5868__
ifeq ($(filter __BLUETOOTH_OBEX__, $(PP_OPT_COMMON)), __BLUETOOTH_OBEX__)
PP_OPT_COMMON += __BLUETOOTH_OBEX_DRV__
PP_OPT_COMMON += __BLUETOOTH_OBEX_MMI__
endif
ifeq (TRUE, $(strip $(BLUETOOTH_A2DP_SUPPORT)))
PP_OPT_COMMON += __BLUETOOTH_A2DP__
PP_OPT_COMMON += __BLUETOOTH_A2DP_DRV__
PP_OPT_COMMON += __BLUETOOTH_A2DP_MMI__
PP_OPT_COMMON += __BLUETOOTH_AVRCP_MMI__
endif
ifeq (TRUE, $(strip $(BLUETOOTH_USER_DEFINED_FOLDER_SUPPORT)))
PP_OPT_COMMON += __BLUETOOTH_USER_DEFINED_FOLDER_MMI__
endif
ifeq (TRUE, $(strip $(EXTRA_BLUETOOTH_HEADSET_PROFILE_SUPPORT)))
PP_OPT_COMMON += __EXTRA_BLUETOOTH_HEADSET_PROFILE_MMI__
endif
endif #NULL
endif #__CORE_SOFTWARE__
endif #__MSTAR_CTA_VERSION__

# Feature_Name = LCM Resolution - WVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_WVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_WVGA__, $(PP_OPT_COMMON)), __LCM_WVGA__)
PP_OPT_COMMON += __LCM_WVGA_DRV__
PP_OPT_COMMON += __LCM_WVGA_MMI__
endif

# Feature_Name = LCM Resolution - QVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_QVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_QVGA__, $(PP_OPT_COMMON)), __LCM_QVGA__)
PP_OPT_COMMON += __LCM_QVGA_DRV__
PP_OPT_COMMON += __LCM_QVGA_MMI__
endif

# Feature_Name = LCM Resolution - WQVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_WQVGA_240_400__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_WQVGA_240_400__, $(PP_OPT_COMMON)), __LCM_WQVGA_240_400__)
PP_OPT_COMMON += __LCM_WQVGA_240_400_DRV__
PP_OPT_COMMON += __LCM_WQVGA_240_400_MMI__
endif

# Feature_Name = LCM Resolution - QQVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_QQVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_QQVGA__, $(PP_OPT_COMMON)), __LCM_QQVGA__)
PP_OPT_COMMON += __LCM_QQVGA_DRV__
PP_OPT_COMMON += __LCM_QQVGA_MMI__
endif

# Feature_Name = LCD LOGO SIZE - SMALL_LCD_LOGO (RGB565 82 * 22)
# Description = LCD LOGO SIZE
# Pre_Condition_On = __LCM_QQVGA__ (128 * 160)
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_QQVGA__, $(PP_OPT_COMMON)), __LCM_QQVGA__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __SMALL_LCD_LOGO__
endif
endif

# Feature_Name = LCM Resolution - QCIF (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_QCIF_PLUS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_QCIF_PLUS__, $(PP_OPT_COMMON)), __LCM_QCIF_PLUS__)
PP_OPT_COMMON += __LCM_QCIF_PLUS_DRV__
PP_OPT_COMMON += __LCM_QCIF_PLUS_MMI__
endif

# Feature_Name = LCM Resolution - HVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_HVGA_320_480__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_HVGA_320_480__, $(PP_OPT_COMMON)), __LCM_HVGA_320_480__)
PP_OPT_COMMON += __LCM_HVGA_DRV__
PP_OPT_COMMON += __LCM_HVGA_320_480_MMI__
endif

# Feature_Name = LCM Resolution - LANDSCAPE QVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_LANDSCAPE_QVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_LANDSCAPE_QVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_QVGA__)
PP_OPT_COMMON += __LCM_LANDSCAPE__
PP_OPT_COMMON += __LCM_LANDSCAPE_QVGA_DRV__
PP_OPT_COMMON += __LCM_LANDSCAPE_QVGA_MMI__
endif

# Feature_Name = LCM Resolution - LANDSCAPE WVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_LANDSCAPE_WVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_LANDSCAPE_WVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_WVGA__)
PP_OPT_COMMON += __LCM_LANDSCAPE__
PP_OPT_COMMON += __LCM_LANDSCAPE_WVGA_DRV__
PP_OPT_COMMON += __LCM_LANDSCAPE_WVGA_MMI__
endif

# Feature_Name = LCM Resolution - LANDSCAPE HVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_LANDSCAPE_HVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_LANDSCAPE_HVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_HVGA__)
PP_OPT_COMMON += __LCM_LANDSCAPE__
PP_OPT_COMMON += __LCM_LANDSCAPE_HVGA_DRV__
PP_OPT_COMMON += __LCM_LANDSCAPE_HVGA_MMI__
endif

# Feature_Name = LCM Resolution - LANDSCAPE WQVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_LANDSCAPE_WQVGA_240_400__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_LANDSCAPE_WQVGA_240_400__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_WQVGA_240_400__)
PP_OPT_COMMON += __LCM_LANDSCAPE__
PP_OPT_COMMON += __LCM_LANDSCAPE_WQVGA_240_400_DRV__
PP_OPT_COMMON += __LCM_LANDSCAPE_WQVGA_240_400_MMI__
endif

# Feature_Name = LCM Resolution - LANDSCAPE QQVGA (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_LANDSCAPE_QQVGA__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_LANDSCAPE_QQVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_QQVGA__)
PP_OPT_COMMON += __LCM_LANDSCAPE__
PP_OPT_COMMON += __LCM_LANDSCAPE_QQVGA_DRV__
PP_OPT_COMMON += __LCM_LANDSCAPE_QQVGA_MMI__
endif

# Feature_Name = LCM Resolution - LANDSCAPE QCIF (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_LANDSCAPE_QCIF__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_LANDSCAPE_QCIF__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_QCIF__)
PP_OPT_COMMON += __LCM_LANDSCAPE__
PP_OPT_COMMON += __LCM_LANDSCAPE_QCIF_DRV__
PP_OPT_COMMON += __LCM_LANDSCAPE_QCIF_MMI__
endif

# Feature_Name = LCM ROTATE Resolution - (DRV)
# Description = LCM Resolution
# Pre_Condition_On = __LCM_ROTATE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __LCM_ROTATE__, $(PP_OPT_COMMON)), __LCM_ROTATE__)
#PP_OPT_COMMON += __LCM_ROTATE_DRV__

PP_OPT_COMMON += __LCM_ROTATE_DIRECTION_CCW__=$(strip $(LCM_ROTATE_DIRECTION_CCW))
ifeq (TRUE, $(strip $(LCM_ROTATE_SIMULATION)))
PP_OPT_COMMON += __LCM_ROTATE_DRV__
else
PP_OPT_COMMON += __LCM_ROTATE_MDL__
endif

ifeq ($(filter __LCM_ROTATE_MDL__, $(PP_OPT_COMMON)), __LCM_ROTATE_MDL__)
PP_OPT_COMMON += __LCM_ROTATE_MMI__
endif

endif

# Description = Option to enable touch screen driver
# Pre_Condition_On = __TOUCH_SCREEN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
PP_OPT_COMMON += __TOUCH_SCREEN_DRV__
PP_OPT_COMMON += __TOUCH_SCREEN_MMI__
endif

# Description = [MMI] BJX with Chinese language
# Pre_Condition_On = __CHINESE_S__ or __CHINESE_T__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __CHINESE_S__ __CHINESE_T__, $(PP_OPT_COMMON)),)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq ($(filter __TOUCH_SCREEN_MMI__, $(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
PP_OPT_COMMON += __APP_MMI_BJX__
endif
endif
endif

# Feature_Name = G-sensor chip
# Description = Option to support G-Sensor feature
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq (,$(strip $(GSENSOR)))
PP_OPT_COMMON += __G_SENSOR__
PP_OPT_COMMON += __G_SENSOR_DRV__
PP_OPT_COMMON += __G_SENSOR_MMI__
ifeq (TRUE, $(strip $(AUTO_ROTATE_DISPLAY_SUPPORT)))
ifneq ($(filter __LCM_LANDSCAPE__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE__)
PP_OPT_COMMON += __AUTO_ROTATE_DISPLAY__
endif
endif
endif
endif

ifeq (TRUE, $(strip $(MULTI_THEMES_ENABLED)))
PP_OPT_COMMON += __MULTI_THEMES_ENABLED__
endif
PP_OPT_COMMON += __THEME_COLOR_DEFAULT__

# Feature_Name = qwerty keypad Resolution(MMI)
# Description = qwerty keypad Resolution
# Pre_Condition_On = __QWERTY_KEYPAD__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __QWERTY_KEYPAD__, $(PP_OPT_COMMON)), __QWERTY_KEYPAD__)
PP_OPT_COMMON += __QWERTY_KEYPAD_DRV__
PP_OPT_COMMON += __QWERTY_KEYPAD_TYPE_H__
PP_OPT_COMMON += __QWERTY_KEYPAD_MMI__
PP_OPT_COMMON += __QWERTY_KEYPAD_INPUTMETHOD__
endif

# Feature_Name = Hall Switch.
# Description = Option to enable hall switch driver and MMI
# Pre_Condition_On = __HALL_SWITCH__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __HALL_SWITCH__, $(PP_OPT_COMMON)), __HALL_SWITCH__)
PP_OPT_COMMON += __HALL_SWITCH_DRV__
PP_OPT_COMMON += __HALL_SWITCH_MMI__
endif

# Feature_Name = flashlight driver / flashlight MMI
# Description = Option to enable flashlight driver / flashlight MMI
# Pre_Condition_On = __FLASHLIGHT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FLASHLIGHT__, $(PP_OPT_COMMON)), __FLASHLIGHT__)
PP_OPT_COMMON += __FLASHLIGHT_DRV__
PP_OPT_COMMON += __FLASHLIGHT_MMI__
endif

# Feature_Name = fill light driver / fill light MMI
# Description = Option to enable fill light driver / fill light MMI
# Pre_Condition_On = __FILLLIGHT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FILLLIGHT__, $(PP_OPT_COMMON)), __FILLLIGHT__)
PP_OPT_COMMON += __FILLLIGHT_DRV__
PP_OPT_COMMON += __FILLLIGHT_MMI__
endif

# Feature_Name = breath light driver / breath light MMI
# Description = Option to enable breath light driver / breath light MMI
# Pre_Condition_On = __BREATHLIGHT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __BREATHLIGHT__, $(PP_OPT_COMMON)), __BREATHLIGHT__)
PP_OPT_COMMON += __BREATHLIGHT_DRV__
PP_OPT_COMMON += __BREATHLIGHT_MMI__
endif

# Feature_Name = camera motion detect
# Description = Option to enable camera motion detect
# Pre_Condition_On = __CAMERA_MOTION_DETECT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __CAMERA_MOTION_DETECT__, $(PP_OPT_COMMON)), __CAMERA_MOTION_DETECT__)
PP_OPT_COMMON += __CAMERA_DETECT_MMI__
endif

# Feature_Name = camera number key enable
# Description = Option to enable camera number key
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_CAMERA_NUMBER_KEY_ENABLE__
endif

# Feature_Name = camera rich setting style
# Description = Option to enable or disable rich setting style
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_CAMERA_RICH_SETTING_STYLE__
endif

# Feature_Name = dual battery driver / dual battery MMI
# Description = Option to enable dual battery driver / dual battery MMI
# Pre_Condition_On = __DUAL_BATTERY__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __DUAL_BATTERY__, $(PP_OPT_COMMON)), __DUAL_BATTERY__)
PP_OPT_COMMON += __DUAL_BATT_DRV__
PP_OPT_COMMON += __DUAL_BATT_MMI__
endif

# Description = [DRV] Enable V24 software flow control XAuto Mode
# Pre_Condition_On = __V24_SOFT_FC__
# Pre_Condition_Off = __G1__
# Option_Selection = N/A
ifeq ($(filter __V24_SOFT_FC__, $(PP_OPT_COMMON)), __V24_SOFT_FC__)
ifeq (TRUE, $(strip $(CHIP_V24_SOFT_FC_XAUTO_MODE)))
PP_OPT_COMMON += __V24_SOFT_FC_XAUTO_MODE__
endif
endif

# Description = Option to enable G3D driver
# Pre_Condition_On = __G3D__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __G3D__, $(PP_OPT_COMMON)), __G3D__)
PP_OPT_COMMON += __G3D_DRV__
PP_OPT_COMMON += __G3D_DRV_512K__
endif

# Description = Option to enable WLAN driver
# Pre_Condition_On = __WLAN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WLAN__, $(PP_OPT_COMMON)), __WLAN__)
PP_OPT_COMMON += __WLAN_DRV__
endif

# Description = Option to enable MPIF HAL driver
# Pre_Condition_On = __WLAN_PIF__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WLAN_PIF__, $(PP_OPT_COMMON)), __WLAN_PIF__)
PP_OPT_COMMON += __MPIF_HAL__
endif

# Feature_Name = Auto Cpu Speed Detection (Drv)
# Description = Option to enable Cpu Speed Auto Detection
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_MDL_CPU_SPEED_AUTO_DETECT)))
PP_OPT_COMMON += __MDL_CPU_SPEED_AUTO_DETECT__
endif

# Feature_Name = Enable Dma2d HW
# Description = Option to enable dma2d
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CHIP_ENABLE_DMA2D_HW)))
PP_OPT_COMMON += __ENABLE_DMA2D_HW__
endif

# Feature_Name = NAND E2P mirror
# Description = Option to support NAND E2P mirror
# Pre_Condition_On = __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __FMS_E2P_NAND_MIRROR__
endif

# Feature_Name = Dynamic load CUS
# Description = Option to support Dynamic load CUS
# Pre_Condition_On = __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __CUS_DYNAMIC_LOAD__
endif

# Description = Option to enable dynamic load cus app resource
# Pre_Condition_On = __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifneq (TRUE, $(strip $(CUS_MMAP_SUPPORT)))
PP_OPT_COMMON += __CUS_DYNAMIC_LOAD_APPRES_MMI__
endif
endif

# Description = Option to enable dynamic load cus
# Pre_Condition_On = __CUS_DYNAMIC_LOAD__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __CUS_DYNAMIC_LOAD__, $(PP_OPT_COMMON)), __CUS_DYNAMIC_LOAD__)
PP_OPT_COMMON += __CUS_DYNAMIC_LOAD_DRV__
ifneq (TRUE, $(strip $(CUS_MMAP_SUPPORT)))
PP_OPT_COMMON += __CUS_DYNAMIC_LOAD_MMI__
endif
endif

# Description = [DRV] Get NRAI partition information from NAND driver
# Pre_Condition_On = __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += USE_GET_NRAI_INFO
endif

# Feature_Name = LCM use CS0 (DRV)
# Description = The LCM use chip select 0 bus
# Pre_Condition_On = N/A
# Pre_Condition_Off = __LCM_CS1_DRV__
# Option_Selection = N/A
ifneq ($(filter __LCM_CS1_DRV__, $(PP_OPT_COMMON)), __LCM_CS1_DRV__)
PP_OPT_COMMON += __LCM_CS0_DRV__
endif

# Feature_Name = ATV chip
HYBRID_ATV_LIST = __ATV_DRV_TLG1180__
CMMB_ATV_LIST = __ATV_DRV_MSB1303__ msb1303

ifneq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
ifneq (,$(strip $(ATV_CHIP)))
PP_OPT_COMMON += $(ATV_CHIP)
PP_OPT_COMMON += $(ATV_AUDIO_PATH)
PP_OPT_COMMON += __ATV__
PP_OPT_COMMON += __TV__
PP_OPT_COMMON += __ATV_DRV__
PP_OPT_COMMON += __ATV_MMI__

ifeq (TRUE, $(strip $(ATV_SUPPORT_ISDBT)))
PP_OPT_COMMON += __ATV_ISDBT__
endif

ifeq ($(filter $(ATV_CHIP), $(HYBRID_ATV_LIST)), $(ATV_CHIP))
PP_OPT_COMMON += __HYBRID_ATV__
endif

ifeq ($(filter $(ATV_CHIP), $(CMMB_ATV_LIST)), $(ATV_CHIP))
PP_OPT_COMMON += __ATV_CMMB__
endif

ifeq ($(filter __ATV_CMMB__, $(PP_OPT_COMMON)), __ATV_CMMB__)
PP_OPT_COMMON += __MPIF_HAL__
PP_OPT_COMMON += __MPIF_DRV__
endif

ifneq ($(filter __ATV_AUD_I2S__ , $(PP_OPT_COMMON)), __ATV_AUD_I2S__)
ifneq ($(filter __ATV_AUD_LINEIN__, $(PP_OPT_COMMON)), __ATV_AUD_LINEIN__)
$(error "Must assign ATV audio path if ATV is enabled." )
endif
endif

ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq (TRUE, $(strip $(ENABLE_ATV_DRIVER_SLDLM)))
PP_OPT_COMMON += __DLM_ATV_DRV__
endif
endif

ifeq (TRUE, $(strip $(ATV_27MCRYSTAL_ENABLE)))
PP_OPT_COMMON += __ATV_27MCRYSTAL_ENABLE__
endif

ifeq (TRUE, $(strip $(ENABLE_ATV_DRIVER_SLDLM)))
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_ATV_DRV__
else
$(error "Enable RTK_OVER_ARM_SLDLM_SUPPORT before enable ENABLE_ATV_DRIVER_SLDLM." )
endif
endif

endif
endif

# Feature_Name = GTV (DRV)
# Description = Option to enable GTV driver layer
# Pre_Condition_On = __GTV__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __GTV__, $(PP_OPT_COMMON)), __GTV__)
ifneq ($(filter __ATV__, $(PP_OPT_COMMON)), __ATV__)
PP_OPT_COMMON += __TV__
endif
PP_OPT_COMMON += __MMCFG_AILSA__
PP_OPT_COMMON += __GTV_DRV__
PP_OPT_COMMON += __GTV_MMI__
PP_OPT_COMMON += __AUDIOCODEC__
endif

# Feature_Name = GPS feature
# Description = If this option is set, Driver and MMI could support GPS functionality
# Pre_Condition_On = __GPS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __GPS__, $(PP_OPT_COMMON)), __GPS__)
PP_OPT_COMMON += __GPS_DRV__
PP_OPT_COMMON += __GPS_MMI__
endif

# Feature_Name=DualStar GPS Host Driver
# Description= Provide positioning function through GPS system
# Pre_Condition_On= __GPS_DRV__
# Pre_Condition_Off= N/A
# Option_Selection= N/A
ifeq ($(filter __GPS_DRV__ ,$(PP_OPT_COMMON)),__GPS_DRV__)
PP_OPT_COMMON += __GPS_DUALSTAR_DRV__
#PP_OPT_COMMON += __GPS_USE_BT_UART__
ifeq ($(filter CHIP_GPS_PIF, $(CHIP_GPS)), CHIP_GPS_PIF)
PP_OPT_COMMON += __GPS_USE_PIF__
endif
ifeq ($(filter CHIP_GPS_SPI, $(CHIP_GPS)), CHIP_GPS_SPI)
PP_OPT_COMMON += __GPS_USE_SPI__
endif
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
ifeq (TRUE, $(strip $(ENABLE_GPS_DRIVER_SLDLM)))
PP_OPT_COMMON += __GPS_USE_SLDLM__
endif
endif
endif

# Feature_Name=MPIF (DRV)
# Description=Option to enable MPIF driver layer
# Pre_Condition_On= N/A
# Pre_Condition_Off= N/A
# Option_Selection= N/A
ifneq ($(filter __GPS_USE_PIF__,$(PP_OPT_COMMON))$(filter __WLAN__,$(PP_OPT_COMMON)),)
PP_OPT_COMMON+= __MPIF_DRV__
PP_OPT_COMMON+= __MPIF_HAL__
endif

# Description = [DRV] init E2P and CUS before panel init
# Pre_Condition_On = __CUS_BOOTUP_LOGO__, __CUS_LCM_TABLE_DRV__, __CUS_DISPLAY_TABLE_DRV__
# Pre_Condition_Off = __NAND__
# Option_Selection = N/A
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifneq ($(filter __CUS_BOOTUP_LOGO__ __CUS_LCM_TABLE_DRV__ __CUS_DISPLAY_TABLE_DRV__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __FMS_PRE_PANEL_INIT__
endif
endif

# Feature_Name = LCD table driver
# Description = Option to enable LCD table driver and copy whole LCD table to mem first befor get LCM id
# Pre_Condition_On = __CUS_LCM_TABLE_DRV__, __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq ($(filter __CUS_LCM_TABLE_DRV__, $(PP_OPT_COMMON)), __CUS_LCM_TABLE_DRV__)
PP_OPT_COMMON += __CUS_LCM_TABLE_DRV_MEM__
endif
endif

# Feature_Name = Display table driver
# Description = Option to enable display table driver and copy whole display table to mem first befor get LCM id
# Pre_Condition_On = __CUS_DISPLAY_TABLE_DRV__, __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq ($(filter __CUS_DISPLAY_TABLE_DRV__, $(PP_OPT_COMMON)), __CUS_DISPLAY_TABLE_DRV__)
PP_OPT_COMMON += __CUS_LCM_TABLE_DRV_MEM__
endif
endif

# Feature_Name = Check CID, DID in display table
# Description = Option to enable to check CID, DID in display table
# Pre_Condition_On = __CUS_DISPLAY_TABLE_DRV__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __CUS_DISPLAY_TABLE_DRV__, $(PP_OPT_COMMON)), __CUS_DISPLAY_TABLE_DRV__)
PP_OPT_COMMON += __CHECK_DISPTBL_CID_DID__
endif

# Feature_Name = Music Cover Flow
# Description = Option to support music cover flow feature, which need to support G-Sensor first.
# Pre_Condition_On = __G_SENSOR_MMI__, __PLAYLIST_COVER_MMI__
# Pre_Condition_Off = __LCM_LANDSCAPE_QVGA__
# Option_Selection = N/A
ifneq ($(filter __LCM_LANDSCAPE_QVGA__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE_QVGA__)
ifeq ($(filter __G_SENSOR_MMI__, $(PP_OPT_COMMON)), __G_SENSOR_MMI__)
ifeq ($(filter __PLAYLIST_COVER_MMI__, $(PP_OPT_COMMON)), __PLAYLIST_COVER_MMI__)
PP_OPT_COMMON += __COVER_FLOW_MMI__
endif
endif
endif

# Feature_Name = Music Player EQ Enable
# Description = Option to enable music player EQ setting
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_MPLAYER_EQ_ENABLE__
endif

# Feature_Name = Music Player 3D Surround Support
# Description = Option to enable music player 3D surround support
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_MPLAYER_3DSURROUND_ENABLE__
endif

# Feature_Name = Music Player Lyric Enable
# Description = Option to enable music player lyric setting
# Pre_Condition_Off = __SMALL_ROM_32__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
PP_OPT_COMMON += __MMI_MPLAYER_LYRIC_ENABLE__
endif

# Feature_Name = Input Editor - Soft Kebyboard
# Description = [MMI] To on/off soft keyboard in input editor
# Pre_Condition_On = __TOUCH_SCREEN_MMI__
# Pre_Condition_Off = __LCM_QCIF_PLUS_MMI__
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN_MMI__, $(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
ifneq ($(filter __LCM_QCIF_PLUS_MMI__, $(PP_OPT_COMMON)), __LCM_QCIF_PLUS_MMI__)
#ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __IME_MMI_SOFTKEYBOARD__
#endif
endif
endif

# Feature_Name = Touch Screen - handwriting
# Description = [MMI] Handwriting
# Pre_Condition_On = __TOUCH_SCREEN_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq (TRUE, $(strip $(DISABLE_HANDWRITING_INPUT_SUPPORT)))
ifeq ($(filter __TOUCH_SCREEN_MMI__, $(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
PP_OPT_COMMON += __HANDWRITING_MMI__
endif
endif

# Feature_Name = Menu touch sliding
# Description = Option to default enable menu slide by finger
# Pre_Condition_On = __TOUCH_SCREEN_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN_MMI__, $(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
PP_OPT_COMMON += __MMI_MENU_DEFAULT_ENABLE_SLIDE_BY_FINGER__
endif

# Feature_Name = Fade out scrollbar
# Description = Option to enbale scrollbar auto fadeout style
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(MMI_FADEOUT_SCROLLBAR_SUPPORT)))
PP_OPT_COMMON += __FADE_OUT_SCROLLBAR__
endif

# Feature_Name = Touch Screen - handwriting solution
# Description = [MMI] Handwriting solution
# Pre_Condition_On = __HANDWRITING_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = __GUOBI_HW__, __HANWANG__+__HANWANG_FULL__
ifeq ($(filter __HANDWRITING_MMI__, $(PP_OPT_COMMON)), __HANDWRITING_MMI__)
PP_OPT_COMMON += __SINOVOICE_HW__
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __SINOVOICE_HW_V5__
endif

ifeq (TRUE, $(strip $(HANDWRITING_DB_TCARD_SUPPORT)))
PP_OPT_COMMON += __SINOVOICE_HW_TCARD__
endif

#PP_OPT_COMMON += __GUOBI_HW__
#PP_OPT_COMMON += __HANWANG__
#PP_OPT_COMMON += __HANWANG_FULL__
endif

# Feature_Name = Load handwriting library from SLDLM
# Description = Option to enable SLDLM handwriting library
# Pre_Variable_True = __SINOVOICE_HW__, RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SINOVOICE_HW__, $(PP_OPT_COMMON)), __SINOVOICE_HW__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_HANDWRITING__
endif
endif

# Feature_Name = Load IME MY library from SLDLM
# Description = Option to enable SLDLM handwriting library
# Pre_Variable_True = __SINOVOICE_HW__, RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __IME_MMI_MY__, $(PP_OPT_COMMON)), __IME_MMI_MY__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_IME_MY__
endif
endif

# Feature_Name = Load mr table library from SLDLM
# Description = Option to enable SLDLM for mr table
# Pre_Variable_True = RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)), __SMALL_ROM_32__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_MRFILE_BUFFER__
endif
endif

# Feature_Name = Load SLDLM for EmApp
# Description = Option to enable SLDLM for EmApp (Engineering Mode)
# Pre_Variable_True = RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_EMAPP_MMI__
endif
endif

# Feature_Name = Load SLDLM for OffApp
# Description = Option to enable SLDLM for OffApp
# Pre_Variable_True = RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_OFFAPP_MMI__
endif
endif

# Feature_Name = Load SLDLM for SokobanApp
# Description = Option to enable SLDLM for SokobanApp (a box-pushing game)
# Pre_Variable_True = RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(SOKOBANGAME_SUPPORT)))
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_SOKOBANAPP_MMI__
endif
endif
endif

# Feature_Name = Load SLDLM for Indian Calendar
# Description = Option to enable SLDLM for Indian Calendar
# Pre_Variable_True = RTK_OVER_ARM_SLDLM_SUPPORT
# Pre_Variable_False = N/A
# Option_Selection = TRUE, FALSE
ifeq (TRUE, $(strip $(CALENDAR_SUPPORT)))
ifeq (TRUE, $(strip $(INDIAN_CALENDAR_SUPPORT)))
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
PP_OPT_COMMON += __DLM_INDCALENDAR_MMI__
endif
endif
endif
endif

# Description = Option to support NAND flash
# Pre_Condition_On = __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __NAND_MMI__
endif

# Feature_Name = On board flash storage for user
# Description = Option to support external storage (file system used by sys/user and public for mass storage)
#               This storage will be mount as a public disk when user connect the handset to PC using mass storage.
#               This storage usually privoded by NAND, the file system used is usually FAT16/FAT32 and can be
#               accessed by standard IO library, such as file_fopen.
# Pre_Condition_On = __NAND_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(ONBOARD_USER_STORAGE_SUPPORT)))
PP_OPT_COMMON += __ONBOARD_USER_STORAGE_MMI__
endif

# Feature_Name = Auto partition
# Description = Option to enable auto partition for NOR Flash
# Pre_Condition_On = __ONBOARD_USER_STORAGE_MMI__
# Pre_Condition_Off = __NAND__
# Option_Selection = N/A
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
ifeq (TRUE, $(strip $(ONBOARD_USER_STORAGE_SUPPORT)))
ifeq (TRUE, $(strip $(AUTO_PARTITION_SUPPORT)))
PP_OPT_COMMON += __AUTO_PARTITION__
endif
endif
endif

# Feature_Name = Store the application data on phone
# Description = Option to support the application data store on phone, Currently this option effect MMS and WAP
#               which the data is stored in .system folder.
# Pre_Condition_On = __ONBOARD_USER_STORAGE_MMI__
# Pre_Condition_Off = __NAND_MMI__
# Option_Selection = N/A
ifeq (TRUE, $(strip $(APP_DATA_ON_PHONE_SUPPORT)))
ifeq ($(filter __ONBOARD_USER_STORAGE_MMI__, $(PP_OPT_COMMON)), __ONBOARD_USER_STORAGE_MMI__)
PP_OPT_COMMON += __APP_DATA_ON_PHONE__
endif
endif

# Feature_Name = Storage selection when storage is full(MMI)
# Description = [MMI] Allow users to select alternative storage when the current storage not sufficient
# Pre_Condition_On = __ONBOARD_USER_STORAGE_MMI__, __DUAL_CARD__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __ONBOARD_USER_STORAGE_MMI__ __DUAL_CARD__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __SPACE_FULL_STORAGE_SELECTION_MMI__
endif

# Feature_Name = Support HVGA resolution for king movie(MMI)
# Description = [MMI] Option for supporting HVGA resolution and *.hkmv file name extension in king movie APP
# Pre_Condition_On = __MMI_KING_MOVIE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MMI_KING_MOVIE__, $(PP_OPT_COMMON)), __MMI_KING_MOVIE__)
ifeq (TRUE, $(strip $(CHIP_KING_MOVIE_SUPPORT_HVGA_MMI)))
PP_OPT_COMMON += __KING_MOVIE_SUPPORT_HVGA_MMI__
endif
endif

# Feature_Name = MMI Multi Layer Mode
# Description = To swith if MMI support Multi layer
# Pre_Condition_On = __G3D__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __G3D__, $(PP_OPT_COMMON)), __G3D__)
PP_OPT_COMMON += __DISP_ML_MMI__
endif

# Feature_Name = G3D (MMI)
# Description = Option to support g3d feature
# Pre_Condition_On = __G3D__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __G3D__, $(PP_OPT_COMMON)), __G3D__)
PP_OPT_COMMON += __G3D_MMI__
PP_OPT_COMMON += __FEATURE_MGL__
#PP_OPT_COMMON += __MGL_DEMO__
PP_OPT_COMMON += __G3D_MMI_GLOBAL_3D__
#PP_OPT_COMMON += __G3D_MMI_DOUBLE_BUFFER__
#PP_OPT_COMMON += __G3D_MMI_DOUBLE_BUFFER_PARTIAL_UPDATE__
endif

# Feature_Name = SW 3D
# Description = Option to support SW 3D feature
# Pre_Condition_On = __FEATURE_MGLS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGLS__, $(PP_OPT_COMMON)), __FEATURE_MGLS__)
PP_OPT_COMMON += __FEATURE_MGL__
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(PHYSICAL_ENGINE_SUPPORT)))
PP_OPT_COMMON += __FEATURE_CHIPMUNK__
PP_OPT_COMMON += __FEATURE_PGL__
endif
endif

# Feature_Name = SW 3D low memory (128/32)
# Description = Option to turn on/off double buffer for low memory (128/32)
# Pre_Condition_On = MGLS_SUPPORT, MGLS_LOW_MEMORY_SUPPORT
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGLS__, $(PP_OPT_COMMON)), __FEATURE_MGLS__)
ifeq (TRUE, $(strip $(MGLS_LOW_MEMORY_SUPPORT)))
PP_OPT_COMMON += __MGLS_LOW_MEMORY__
else
ifeq (FALSE, $(strip $(MGLS_LOW_MEMORY_SUPPORT)))
PP_OPT_COMMON += __DISP_DOUBLE_BUFFER__
endif
endif
endif

# Feature_Name = 3D PICKING
# Description = Option to support 3D PICKING feature
# Pre_Condition_On = __TOUCH_SCREEN_MMI__, __FEATURE_MGLS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN_MMI__, $(PP_OPT_COMMON)), __TOUCH_SCREEN_MMI__)
ifeq ($(filter __FEATURE_MGLS__, $(PP_OPT_COMMON)), __FEATURE_MGLS__)
ifeq (TRUE, $(strip $(MGLS_PICKING_SUPPORT)))
PP_OPT_COMMON += __FEATURE_MGLS_PICKING__
endif
endif
endif

# Feature_Name = WDG 3D DEMO
# Description = Option to enable WDG 3D DEMO application
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
#PP_OPT_COMMON += __APP_MMI_WDG3DEMO__

# Feature_Name = 3D UI Statusbar
# Description = Option to Enable Drop Down Statusbar
# Pre_Condition_On =  __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(DROPDOWN_STATUSPAGE_SUPPORT)))
ifneq ($(filter __LCM_QVGA__ __LCM_LANDSCAPE_QVGA__ __LCM_WQVGA_240_400__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
PP_OPT_COMMON += __DROPDOWN_STATUSPAGE__
endif
endif
endif

# Feature_Name = Idle style selection
# Description = Option to select idle style
# Pre_Condition_On = N/A
# Pre_Condition_Off = UI_STYLE_MMI_ANDROID_IDLE_SUPPORT
# Option_Selection = N/A
ifneq ($(filter __UI_STYLE_MMI_ANDROID_IDLE__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_ANDROID_IDLE__)

ifeq (APP_MMI_IDLE_SIMPLE3D_STYLE, $(strip $(IDLE_EFFECT)))
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
PP_OPT_COMMON += __3D_UI_IDLE_SIMPLE__
else
PP_OPT_COMMON += __2D_UI_IDLE_SIMPLE__
endif
endif

ifeq (APP_MMI_IDLE_GADGETBAR_STYLE, $(strip $(IDLE_EFFECT)))
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __GADGETS_MMI__
PP_OPT_COMMON += __2D_UI_IDLE_GADGETBAR__
else
PP_OPT_COMMON += __2D_UI_IDLE_SIMPLE__
endif
else
PP_OPT_COMMON += __2D_UI_IDLE_SIMPLE__
endif
endif

ifeq (APP_MMI_IDLE_GADGETBAR3D_STYLE, $(strip $(IDLE_EFFECT)))
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifneq ($(filter __LCM_LANDSCAPE__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE__)
PP_OPT_COMMON += __3D_UI_IDLE_GADGETBAR__
PP_OPT_COMMON += __3D_VIEW_TRANSITION__
else
PP_OPT_COMMON += __3D_UI_IDLE_MULTIPAGE__
endif
else
PP_OPT_COMMON += __2D_UI_IDLE_SIMPLE__
endif
endif

ifeq (APP_MMI_IDLE_MULTIPAGE3D_STYLE, $(strip $(IDLE_EFFECT)))
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
PP_OPT_COMMON += __3D_UI_IDLE_MULTIPAGE__
else
PP_OPT_COMMON += __2D_UI_IDLE_SIMPLE__
endif
endif

ifeq ($(filter APP_MMI_IDLE_MULTIPAGE3D_STYLE APP_MMI_IDLE_SIMPLE3D_STYLE APP_MMI_IDLE_GADGETBAR3D_STYLE APP_MMI_IDLE_GADGETBAR_STYLE, $(IDLE_EFFECT)),)
PP_OPT_COMMON += __2D_UI_IDLE_SIMPLE__
endif

endif

# Feature_Name = 3D mainmenu app
# Description = Option to enable 3D mainmenu app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_MAINMENU_SUPPORT)))
PP_OPT_COMMON += __3D_UI_MAINMENU__
endif
endif

# Feature_Name = 3D keyguard app
# Description = Option to enable 3D keyguard app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (APP_MMI_UI_KEYGUARD_SIMPLE, $(strip $(KEYGUARD_EFFECT)))
PP_OPT_COMMON +=
else
PP_OPT_COMMON += __3D_UI_KEYGUARD__
ifeq (APP_MMI_UI_KEYGUARD_GLOW, $(strip $(KEYGUARD_EFFECT)))
PP_OPT_COMMON += __3D_UI_KEYGUARD_GLOW__
endif
ifeq (APP_MMI_UI_KEYGUARD_BEAUTY_CLK, $(strip $(KEYGUARD_EFFECT)))
PP_OPT_COMMON += __3D_UI_KEYGUARD_BEAUTY_CLK__
ifeq (TRUE, $(strip $(MMI_BEAUTY_CLK_APP_SUPPORT)))
PP_OPT_COMMON += __3D_UI_KEYGUARD_GLOW__
endif
endif
endif
endif

# Feature_Name = 3D e-book app
# Description = Option to enable 3D e-book app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_EBOOK_SUPPORT)))
PP_OPT_COMMON += __3D_UI_EBOOK__
endif
endif

# Feature_Name = 3D kingmovie app
# Description = Option to enable 3D kingmovie app
# Pre_Condition_On = __FEATURE_MGL__, __TOUCH_SCREEN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(MMI_3DUI_KINGMOVIE_SUPPORT)))
PP_OPT_COMMON += __3D_UI_KINGMOVIE__
endif
endif
endif

# Feature_Name = 3D music-player app
# Description = Option to enable 3D music-player app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_MPLAYER_SUPPORT)))
PP_OPT_COMMON += __3D_UI_MPLAYER__
endif
endif

# Feature_Name = 3D FM-radio app
# Description = Option to enable 3D FM-radio app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_FMRADIO_SUPPORT)))
PP_OPT_COMMON += __3D_UI_FMRADIO__
endif
endif

# Feature_Name = 3D phonebook app
# Description = Option to enable 3D phonebook app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_PHONEBOOK_SUPPORT)))
PP_OPT_COMMON += __3D_UI_PHONEBOOK__
endif
endif

# Feature_Name = 3D shortcut app
# Description = Option to enable shortcut app
# Pre_Condition_On = __FEATURE_MGL__, __APP_MMI_SHORTCUT__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __APP_MMI_SHORTCUT__, $(PP_OPT_COMMON)), __APP_MMI_SHORTCUT__)
ifeq (TRUE, $(strip $(MMI_3DUI_SHORTCUTAPP_SUPPORT)))
PP_OPT_COMMON += __3D_UI_SHORTCUTAPP__
endif
endif
endif

# Feature_Name = beauty clock
# Description = Option to enable beauty clock app
# Pre_Condition_On = __FEATURE_MGL__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_BEAUTY_CLK_APP_SUPPORT)))
PP_OPT_COMMON += __MMI_BEAUTY_CLK_APP__
endif
endif

# Feature_Name = ANIM IMAGE
# Description = Option to support animwidget
# Pre_Condition_On = __FEATURE_MGLS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __FEATURE_MGLS__, $(PP_OPT_COMMON)), __FEATURE_MGLS__)
ifeq ($(filter __3D_UI_IDLE_MULTIPAGE__, $(PP_OPT_COMMON)), __3D_UI_IDLE_MULTIPAGE__)
PP_OPT_COMMON += __WDG_ANIMIMAGE__
endif
endif

ifeq ($(filter __3D_UI_IDLE_MULTIPAGE__, $(PP_OPT_COMMON)), __3D_UI_IDLE_MULTIPAGE__)
PP_OPT_COMMON += __3D_MESSAGE_BOX__
ifeq (CUBEVIEW, $(strip $(IDLEPREVIEW_EFFECT)))
PP_OPT_COMMON += __3D_UI_IDLE_MULTIPAGE_CUBEVIEW__
else
PP_OPT_COMMON += __3D_UI_IDLE_MULTIPAGE_PAGEVIEW__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_OPTION_MENU_3D_EXT_SUPPORT)))
PP_OPT_COMMON += __OPTION_MENU_3D_EXT__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __COVER_FLOW_MMI__, $(PP_OPT_COMMON)), __COVER_FLOW_MMI__)
ifeq (TRUE, $(strip $(MMI_3DUI_COVERFLOW_SUPPORT)))
PP_OPT_COMMON += __3D_UI_COVERFLOW_MMI__
endif
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_GOGOBOX_GAME_SUPPORT)))
PP_OPT_COMMON += __GOGOBOX_GAME__
endif
endif

ifeq ($(filter __FEATURE_PGL__, $(PP_OPT_COMMON)), __FEATURE_PGL__)
ifeq (TRUE, $(strip $(MMI_ANGRYBIRD_GAME_SUPPORT)))
PP_OPT_COMMON += __ANGRYBIRD_GAME__
endif
endif

ifeq ($(filter __FEATURE_PGL__, $(PP_OPT_COMMON)), __FEATURE_PGL__)
ifeq (TRUE, $(strip $(MMI_VAMPIRE_GAME_SUPPORT)))
PP_OPT_COMMON += __VAMPIRE_GAME__
endif
endif

ifeq ($(filter __FEATURE_PGL__, $(PP_OPT_COMMON)), __FEATURE_PGL__)
ifeq (TRUE, $(strip $(MMI_ZOMBIE_GAME_SUPPORT)))
PP_OPT_COMMON += __ZOMBIE_GAME__
endif
endif

ifeq ($(filter __FEATURE_PGL__, $(PP_OPT_COMMON)), __FEATURE_PGL__)
ifeq (TRUE, $(strip $(MMI_FISHFURY_GAME_SUPPORT)))
PP_OPT_COMMON += __FISHFURY_GAME__
endif
endif

ifeq ($(filter __FEATURE_PGL__, $(PP_OPT_COMMON)), __FEATURE_PGL__)
ifeq (TRUE, $(strip $(MMI_CUTROPE_GAME_SUPPORT)))
PP_OPT_COMMON += __CUTROPE_GAME__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_FRUITSLICE_GAME_SUPPORT)))
PP_OPT_COMMON += __FRUITSLICE_GAME__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_RUBIKCUBE_GAME_SUPPORT)))
PP_OPT_COMMON += __RUBIKCUBE_GAME__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_LABYRINTH_GAME_SUPPORT)))
PP_OPT_COMMON += __LABYRINTH_GAME__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_IPLAYCUBE_GAME_SUPPORT)))
PP_OPT_COMMON += __IPLAYCUBE_GAME__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER__
PP_OPT_COMMON += __LIVE_WALLPAPER_IMAGE__

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_EARTHROT_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_EARTHROT__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_SOLARSYSTEM_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_SOLARSYSTEM__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_COMET_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_COMET__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_SNAKELINE_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_SNAKELINE__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_SEASHORE_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_SEASHORE__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_JUMPGATE_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_JUMPGATE__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_FALLSNOW_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_FALLSNOW__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_WEATHER_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_WEATHER__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_FLUTTERSNOW_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_FLUTTERSNOW__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_GRASSTRACE_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_GRASSTRACE__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_FISH_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_FISH__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_FARM_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_FARM__
endif

ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_BIRD_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_BIRD__
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_DROPLET_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_DROPLET__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_INWATER_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_INWATER__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_LIVE_WALLPAPER_INWATERSHOOT_SUPPORT)))
PP_OPT_COMMON += __LIVE_WALLPAPER_INWATERSHOOT__
endif
endif

endif

endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __MMI_PICVIEWER_SLIDESHOW_ENABLE__, $(PP_OPT_COMMON)), __MMI_PICVIEWER_SLIDESHOW_ENABLE__)
ifeq (TRUE, $(strip $(MMI_3DUI_PICVIEWER_SLIDESHOW_SUPPORT)))
PP_OPT_COMMON += __3D_UI_PICVIWER_SLIDESHOW__
endif
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_PHOTOSLIDE_SUPPORT)))
PP_OPT_COMMON += __3D_UI_PHOTOSLIDE_MMI__
ifneq ($(filter __3D_UI_IDLE_MULTIPAGE__, $(PP_OPT_COMMON)), __3D_UI_IDLE_MULTIPAGE__)
PP_OPT_COMMON += __WDG_ANIMIMAGE__
endif
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq (TRUE, $(strip $(MMI_3DUI_SCREENSAVER_EFFECT_SUPPORT)))
PP_OPT_COMMON += __3D_UI_SCREENSAVER_EFFECT__
endif
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifneq ($(filter __APP_MMI_GROUP_APP__, $(PP_OPT_COMMON)), __APP_MMI_GROUP_APP__)
ifeq (TRUE, $(strip $(MMI_3D_DIALER_SUPPORT)))
PP_OPT_COMMON += __APP_MMI_3D_DIALER__
endif
endif
endif
endif

ifeq ($(filter __APP_MMI_3D_DIALER__, $(PP_OPT_COMMON)), __APP_MMI_3D_DIALER__)
ifeq (APP_MMI_DIALER_BOX_TRANSITION, $(strip $(DIALER_EFFECT)))
PP_OPT_COMMON += __APP_MMI_DIALER_BOX_TRANSITION__
endif
endif

ifeq ($(filter __APP_MMI_3D_DIALER__, $(PP_OPT_COMMON)), __APP_MMI_3D_DIALER__)
ifeq (APP_MMI_DIALER_CUBE_TRANSITION, $(strip $(DIALER_EFFECT)))
PP_OPT_COMMON += __APP_MMI_DIALER_CUBE_TRANSITION__
endif
endif

ifneq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifneq ($(filter __LCM_QVGA__ __LCM_HVGA_320_480__, $(LCM_RESOLUTION)),)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __DUAL_LCD__, $(PP_OPT_COMMON)), __DUAL_LCD__)
ifeq (TRUE, $(strip $(UI_STYLE_IFONE_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_IFONE__
endif
endif
endif
endif
endif
endif

ifeq ($(filter __UI_STYLE_MMI_IFONE__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_IFONE__)
#PP_OPT_COMMON += __IFONESTYLE_SUPPROT_NIVIGATIONKEY__
PP_OPT_COMMON += __MAINMENUIFONE_PRELOAD_ANIMBMP__
PP_OPT_COMMON += __IFONE_STYLE_MMI_COUNTDOWN_TIMER__
PP_OPT_COMMON += __IFONE_STYLE_MMI_VOICEMEMO__
endif

ifeq (TRUE, $(strip $(UI_STYLE_SPIN_MAIN_MENU_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_MAIN_MENU_SPIN__
endif

ifeq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
ifeq ($(filter __UI_STYLE_MMI_MAIN_MENU_SPIN__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_MAIN_MENU_SPIN__)
ifeq (TRUE, $(strip $(UI_STYLE_3D_SPIN_MAIN_MENU_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_MAIN_MENU_3D_SPIN__
endif
endif
endif

ifneq ($(filter __3D_UI_MAINMENU__, $(PP_OPT_COMMON)), __3D_UI_MAINMENU__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __UI_STYLE_MMI_ANDROID_MAIN_MENU__, $(PP_OPT_COMMON)), __UI_STYLE_MMI_ANDROID_MAIN_MENU__)
ifeq (TRUE, $(strip $(UI_STYLE_ANIMATION_MAIN_MENU_SUPPORT)))
PP_OPT_COMMON += __UI_STYLE_MMI_MAIN_MENU_ANIMATION__
ifeq (TRUE, $(strip $(MMI_ANIMATED_MENU_EFFECT_SUPPORT)))
PP_OPT_COMMON += __MMI_ENABLE_ANIMATED_MENU_EFFECT__
endif
endif
endif
endif
endif

# Feature_Name = 2DUI (MMI)
# Description = IMG used only in 2D project
# Pre_Condition_On = N/A
# Pre_Condition_Off = __FEATURE_MGL__
# Option_Selection = N/A
ifneq ($(filter __FEATURE_MGL__, $(PP_OPT_COMMON)), __FEATURE_MGL__)
PP_OPT_COMMON += __MMI_2DUI__
endif

# Feature_Name = SMS Inbox Location Setting (MMI)
# Description = Option to enable the SMS inbox location setting
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __SMS_MMI_INBOX_LOCATION__

# Feature_Name = WAP (MMI)
# Description = Option for WAP feature in MMI
# Pre_Condition_On = __WAP__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP__, $(PP_OPT_COMMON)), __WAP__)
PP_OPT_COMMON += __WAP_MMI__
endif

# Feature_Name = WAP (CDWAP)
# Description = Option to enable WAP function using CDWAP solution
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
PP_OPT_COMMON += __WAP_MMI_CDWAP__
endif

# Feature_Name = __CDW_ALLOW_NO_TCARD__ (CDWAP)
# Description = Option to enable WAP function using wap without tcard
# Pre_Condition_On = __WAP_MMI_CDWAP__
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI_CDWAP__, $(PP_OPT_COMMON)), __WAP_MMI_CDWAP__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __CDW_ALLOW_NO_TCARD__
endif
endif

# Feature_Name = __MOVE_DEF_FOLDER_TO_FLASH__ (CDWAP)
# Description = Option to enable WAP function using wap without tcard and move default folder to flash
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
ifeq ($(filter __APP_DATA_ON_PHONE__, $(PP_OPT_COMMON)), __APP_DATA_ON_PHONE__)
PP_OPT_COMMON += __MOVE_DEF_FOLDER_TO_FLASH__
endif
endif

# Feature_Name =  WSP feature in WAP (CDWAP)
# Description = Option to enable WSP feature in WAP
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += NCC_WSP
endif

# Feature_Name =  Pictogram feature in WAP (CDWAP)
# Description = Option to enable Pictogram feature in WAP
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
ifeq (TRUE, $(strip $(WAP_PICTOGRAM_SUPPORT)))
PP_OPT_COMMON += __DB_USING_PICTOGRAM__
endif
endif

# Feature_Name =  HTML feature in WAP (CDWAP)
# Description = Option to enable HTML feature in WAP
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
ifneq (FALSE, $(strip $(WAP_HTML_SUPPORT)))
PP_OPT_COMMON += __NCC_BROWSER_HTML__
endif
endif

# Feature_Name =  SSL feature in WAP (CDWAP)
# Description = Option to enable SSL feature in WAP
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
ifneq (FALSE, $(strip $(WAP_SSL_SUPPORT)))
PP_OPT_COMMON += __NCC_BROWSER_TLS__
endif
endif

# Feature_Name = Browse record feature in WAP (CDWAP)
# Description = Option to enable browse record feature in WAP
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
ifneq (FALSE, $(strip $(WAP_RECORD_SUPPORT)))
PP_OPT_COMMON += __NCC_BROWSER_RECORD__
endif
endif

# Feature_Name = WAP shortcut to portal
# Description = Option to enable WAP shortcut to portal
# Pre_Condition_On = __WAP_MMI__
# Pre_Condition_On = __STREAMING_MODULE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WAP_MMI__, $(PP_OPT_COMMON)), __WAP_MMI__)
ifeq (TRUE, $(strip $(VIDEO_RTSP_STREAMING_SUPPORT)))
#PP_OPT_COMMON += __YOUTUBE_MMI_CDWAP__
#PP_OPT_COMMON += __YOUKU_MMI_CDWAP__
#PP_OPT_COMMON += __VUCLIP_MMI_CDWAP__
#PP_OPT_COMMON += __BAIDU_MMI_CDWAP__
else
ifeq (TRUE, $(strip $(VIDEO_HTTP_STREAMING_SUPPORT)))
#PP_OPT_COMMON += __YOUTUBE_MMI_CDWAP__
#PP_OPT_COMMON += __YOUKU_MMI_CDWAP__
#PP_OPT_COMMON += __VUCLIP_MMI_CDWAP__
#PP_OPT_COMMON += __BAIDU_MMI_CDWAP__
endif
endif
endif

# Feature_Name = HTTP memory streaming mode
# Description = Option to enable HTTP memory streaming mode
# Pre_Condition_On = __STREAMING_MODULE__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __STREAMING_MODULE__, $(PP_OPT_COMMON)),)
#PP_OPT_COMMON += __SUPPORT_HTTP_MEMORY_STREAMING__
endif

# Feature_Name = MMS (CDMMS)
# Description = Option to enable MMS function using CDMMS solution
# Pre_Condition_On = __MMS__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MMS__, $(PP_OPT_COMMON)), __MMS__)
PP_OPT_COMMON += __MMS_MMI_CDMMS__
ifeq ($(filter __APP_DATA_ON_PHONE__, $(PP_OPT_COMMON)), __APP_DATA_ON_PHONE__)
ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __MMS_MMI_CDMMS_STORAGE_SWITCH__
endif
endif
endif

# Feature_Name = Message Select Sim box
# Description = Option to enable message Select Sim box
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(SMS_SELECT_DISPLAY_SIM_SUPPORT)))
PP_OPT_COMMON += __SMS_MMI_SIM_MESSAGE_BOX_SUPPORT__
endif

# Feature_Name = MMS Template support (CDMMS)
# Description = Option to enable CDMMS with MMI support MMS Template (like sms template)
# Pre_Condition_On = __MMS_MMI_CDMMS__
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq ($(filter __MMS_MMI_CDMMS__, $(PP_OPT_COMMON)), __MMS_MMI_CDMMS__)
ifeq (TRUE, $(strip $(MMS_TEMPLATE_SUPPORT)))
PP_OPT_COMMON += __MMS_MMI_CDMMS_TEMPLATE__
endif
endif
endif

# Feature_Name = Disable MMS Resize Image Function
# Description = Option to disable the MMS resize image function
# Pre_Condition_On = __MMS_MMI_CDMMS__
# Option_Selection = N/A
ifeq ($(filter __MMS_MMI_CDMMS__, $(PP_OPT_COMMON)), __MMS_MMI_CDMMS__)
ifeq (FALSE, $(strip $(MMS_DISABLE_RESIZE_IMAGE_SUPPORT)))
PP_OPT_COMMON += __MMS_SUPPORT_RESIZE_IMAGE__
endif
endif

# Feature_Name = Disable MMS Play Video Function
# Description = Option to disable the MMS play video function
# Pre_Condition_On = __MMS_MMI_CDMMS__
# Option_Selection = N/A
ifeq ($(filter __MMS_MMI_CDMMS__, $(PP_OPT_COMMON)), __MMS_MMI_CDMMS__)
ifeq (FALSE, $(strip $(MMS_DISABLE_PLAY_VIDEO_SUPPORT)))
PP_OPT_COMMON += __MMS_SUPPORT_PLAY_VIDEO__
endif
endif

# Description = [MMI] Enable input controller Chinese support
# Pre_Condition_On = __CHINESE_S__ or __CHINESE_T__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __CHINESE_S__, $(PP_OPT_COMMON)), __CHINESE_S__)
PP_OPT_COMMON += __INPUTCONTROLLER_CHINESE_SUPPORT__
else
ifeq ($(filter __CHINESE_T__, $(PP_OPT_COMMON)), __CHINESE_T__)
PP_OPT_COMMON += __INPUTCONTROLLER_CHINESE_SUPPORT__
endif
endif

# Description = [MMI] Enable input controller smart support
# Pre_Condition_On = __SMALL_ROM__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __INPUTCONTROLLER_SMART_SUPPORT__
endif

# Description = [MMI] Use MingYi multi dictionary
# Pre_Condition_On = __IME_MMI_MY__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __IME_MMI_MY__, $(PP_OPT_COMMON)), __IME_MMI_MY__)
#PP_OPT_COMMON += __IME_MMI_MY_MULTI_DICTIONARY__
endif

# Description = [MMI] Enable input helper for MingYi IME
# Pre_Condition_On = __IME_MMI_MY__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __IME_MMI_MY__, $(PP_OPT_COMMON)), __IME_MMI_MY__)
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __IME_MMI_MY_INPUT_HELPER__
endif
endif

ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (__IME_MMI_SG__, $(strip $(IME_SOLUTION)))
$(error "Can not support __IME_MMI_SG__ in small rom product. Please use __IME_MMI_MY__")
endif
endif

ifeq (__IME_MMI_SG__, $(strip $(IME_SOLUTION)))
ifeq (TRUE, $(strip $(IME_SG_FOREIGN_ONLY)))
ifeq ($(filter __IME_SG_CHINESE_S__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_CHINESE_S__)
$(error "When IME_SG_FOREIGN_ONLY is TRUE, __IME_SG_CHINESE_S__ must be not selected in IME_SG_LANG_SUPPORT")
endif
endif
ifeq (,$(strip $(IME_SG_LANG_SUPPORT)))
$(error "IME_SG_LANG_SUPPORT must with value when IME_SOLUTION is __IME_MMI_SG__")
endif
endif

# Feature_Name = Engineering Mode Touch Panel Enhance Test Feature (MMI)
# Description = [MMI] Option for Engineering Mode Touch Panel Enhance Test Feature
# Pre_Condition_On = __TOUCH_SCREEN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __R_MSTAR__, $(TOUCH_SCREEN_DRIVER_SELECT)), __R_MSTAR__)
ifneq ($(filter __R_C_COEXIST__, $(TOUCH_SCREEN_DRIVER_SELECT)), __R_C_COEXIST__)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)),__TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(EM_TOUCHSCREEN_TEST_ENHANCE_SUPPORT)))
PP_OPT_COMMON += __EM_TOUCHSCREEN_TEST_ENHANCE__
endif
endif
endif
endif

#===============================================================================
# KMX IME & KMX Language Pack Setting
#===============================================================================
# Feature_Name = KOMOXO IME option
# Description = KOMOXO IME option
# Pre_Variable_True = __IME_MMI_CSTAR__
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq (__IME_MMI_CSTAR__, $(strip $(IME_SOLUTION)))
PP_OPT_COMMON += __MMI_IME_CSTAR_FORMAT__
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (IME_CSTAR_VK_DIGIT, $(strip $(IME_CSTAR_VK_STYLE)))
PP_OPT_COMMON += __MMI_IME_KMX_VK_DIGIT__
endif
ifeq (IME_CSTAR_VK_QWERTY, $(strip $(IME_CSTAR_VK_STYLE)))
PP_OPT_COMMON += __MMI_IME_KMX_VK_QWERTY__
endif
ifeq (IME_CSTAR_VK_DIGIT_P_QWERTY_L, $(strip $(IME_CSTAR_VK_STYLE)))
ifeq (TRUE, $(strip $(AUTO_ROTATE_DISPLAY_SUPPORT)))
PP_OPT_COMMON += __MMI_IME_KMX_VK_QWERTY__
PP_OPT_COMMON += __MMI_IME_KMX_VK_DIGIT__
PP_OPT_COMMON += __MMI_IME_KMX_VK_DIGIT_P_QWERTY_L__
else
ifneq ($(filter __LCM_LANDSCAPE__, $(PP_OPT_COMMON)), __LCM_LANDSCAPE__)
PP_OPT_COMMON += __MMI_IME_KMX_VK_DIGIT__
else
PP_OPT_COMMON += __MMI_IME_KMX_VK_QWERTY__
endif
endif
endif
endif
endif

# Feature_Name = KOMOXO ScriptEasy Font engine option
# Description = KOMOXO ScriptEasy Font engine option
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(SCRIPT_EASY_BITMAP_FONT_SUPPORT)))
PP_OPT_COMMON += __MMI_SCRIPT_EASY__
PP_OPT_COMMON += __MMI_SCRIPT_EASY_EDITOR__
endif

ifeq (__IME_MMI_CSTAR__, $(strip $(IME_SOLUTION)))
ifeq (TRUE, $(strip $(KMX_USER_DATA_ENABLED)))
PP_OPT_COMMON += __KMX_USER_DATA_ENABLED__
endif
endif

#===============================================================================
# Sogou IME Setting
#===============================================================================
# Feature_Name = Sogou IME option
# Description = Sogou IME option
# Pre_Variable_True = __IME_MMI_SG__
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq (__IME_MMI_SG__, $(strip $(IME_SOLUTION)))
PP_OPT_COMMON += __APP_MMI_SOHU_UPDATER__

ifeq (TRUE, $(strip $(IME_SG_FOREIGN_ONLY)))
PP_OPT_COMMON += __IME_MMI_SG_FOREIGN__
else
PP_OPT_COMMON += __IME_MMI_SG_CHINESE_S__
endif

ifeq ($(filter __IME_SG_ARABIC__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_ARABIC__)
PP_OPT_COMMON += __IME_MMI_SG_ARABIC__
endif

ifeq ($(filter __IME_SG_BENGALI__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_BENGALI__)
PP_OPT_COMMON += __IME_MMI_SG_BENGALI__
endif

ifeq ($(filter __IME_SG_CZECH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_CZECH__)
PP_OPT_COMMON += __IME_MMI_SG_CZECH__
endif

ifeq ($(filter __IME_SG_DUTCH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_DUTCH__)
PP_OPT_COMMON += __IME_MMI_SG_DUTCH__
endif

ifeq ($(filter __IME_SG_ENGLISH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_ENGLISH__)
PP_OPT_COMMON += __IME_MMI_SG_ENGLISH__
endif

ifeq ($(filter __IME_SG_FRENCH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_FRENCH__)
PP_OPT_COMMON += __IME_MMI_SG_FRENCH__
endif

ifeq ($(filter __IME_SG_GERMAN__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_GERMAN__)
PP_OPT_COMMON += __IME_MMI_SG_GERMAN__
endif

ifeq ($(filter __IME_SG_GREEK__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_GREEK__)
PP_OPT_COMMON += __IME_MMI_SG_GREEK__
endif

ifeq ($(filter __IME_SG_HINDI__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_HINDI__)
PP_OPT_COMMON += __IME_MMI_SG_HINDI__
endif

ifeq ($(filter __IME_SG_INDONESIAN__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_INDONESIAN__)
PP_OPT_COMMON += __IME_MMI_SG_INDONESIAN__
endif

ifeq ($(filter __IME_SG_ITALIAN__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_ITALIAN__)
PP_OPT_COMMON += __IME_MMI_SG_ITALIAN__
endif

ifeq ($(filter __IME_SG_MALAY__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_MALAY__)
PP_OPT_COMMON += __IME_MMI_SG_MALAY__
endif

ifeq ($(filter __IME_SG_PERSIAN__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_PERSIAN__)
PP_OPT_COMMON += __IME_MMI_SG_PERSIAN__
endif

ifeq ($(filter __IME_SG_POLISH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_POLISH__)
PP_OPT_COMMON += __IME_MMI_SG_POLISH__
endif

ifeq ($(filter __IME_SG_PORTUGUESE__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_PORTUGUESE__)
PP_OPT_COMMON += __IME_MMI_SG_PORTUGUESE__
endif

ifeq ($(filter __IME_SG_RUSSIAN__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_RUSSIAN__)
PP_OPT_COMMON += __IME_MMI_SG_RUSSIAN__
endif

ifeq ($(filter __IME_SG_SPANISH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_SPANISH__)
PP_OPT_COMMON += __IME_MMI_SG_SPANISH__
endif

ifeq ($(filter __IME_SG_THAI__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_THAI__)
PP_OPT_COMMON += __IME_MMI_SG_THAI__
endif

ifeq ($(filter __IME_SG_TURKISH__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_TURKISH__)
PP_OPT_COMMON += __IME_MMI_SG_TURKISH__
endif

ifeq ($(filter __IME_SG_VIETNAMESE__, $(strip $(IME_SG_LANG_SUPPORT))), __IME_SG_VIETNAMESE__)
PP_OPT_COMMON += __IME_MMI_SG_VIETNAMESE__
endif
endif

# Feature_Name = Map Core, GPS, LBS
# Description = [MMI] Map Core, GPS, LBS
# Pre_Condition_On = __MAP__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MAP__, $(PP_OPT_COMMON)), __MAP__)
PP_OPT_COMMON += __MAP_CORE__
PP_OPT_COMMON += __MAP_MMI__
endif

# Feature_Name = Map Core ,GPS, LBS
# Description = [MMI] LBS
# Pre_Condition_On = __MAP_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MAP_MMI__, $(PP_OPT_COMMON)), __MAP_MMI__)
#PP_OPT_COMMON += __MAP_MMI_LBS__
endif

# Feature_Name = Map Core ,GPS, LBS
# Description = [MMI] GPS where am I feature; __MAP_MMI_GPS_PLUGIN__ is to apply GPS position correction for China MAP
# Pre_Condition_On = __MAP_MMI__, __GPS_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MAP_MMI__, $(PP_OPT_COMMON)), __MAP_MMI__)
ifeq ($(filter __GPS_MMI__, $(PP_OPT_COMMON)), __GPS_MMI__)
PP_OPT_COMMON += __MAP_MMI_GPS__
PP_OPT_COMMON += __MAP_MMI_GPS_PLUGIN__
endif
endif

# Feature_Name = Map Core ,GPS, LBS
# Description = [MMI] GPS where am I feature; __MAP_MMI_GPS_PLUGIN_LIB__ is to link existed GPS position correction library for China MAP
# Pre_Condition_On = __MAP_MMI_GPS_PLUGIN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MAP_MMI_GPS_PLUGIN__, $(PP_OPT_COMMON)), __MAP_MMI_GPS_PLUGIN__)
#PP_OPT_COMMON += __MAP_MMI_GPS_PLUGIN_LIB__
endif

# Feature_Name = EMU Emulator - MMI
# Description = Option to enable EMU emulator engine in MMI
# Pre_Condition_On = __GAME_ENGINE_EMU__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __GAME_ENGINE_EMU__, $(PP_OPT_COMMON)), __GAME_ENGINE_EMU__)
PP_OPT_COMMON += __GAME_ENGINE_EMU_MMI__
endif

# Feature_Name = Dynamic Game
# Description =
# Pre_Condition_On = __GAME_ENGINE_EMU_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __GAME_ENGINE_EMU_MMI__, $(PP_OPT_COMMON)), __GAME_ENGINE_EMU_MMI__)
PP_OPT_COMMON += __FEATURE_DYNAMIC_GAME__
PP_OPT_COMMON += __FEATURE_DYNAMIC_GAME_ON_CARD__
endif

# Feature_Name = EMU Applet Virtual Keypad
# Description = Option to enable virtual keypad to play EMU game
#               Only supported in NAND flash or in NOR flash without enabling EMU 16-bit game
# Pre_Condition_On = __GAME_ENGINE_EMU_MMI__, __TOUCH_SCREEN__, LCM_RESOLUTION(__LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_HVGA_320_480__, __LCM_WVGA__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_WQVGA_240_400__, __LCM_LANDSCAPE_HVGA__, __LCM_LANDSCAPE_WVGA__)
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_WVGA__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_WQVGA_240_400__ __LCM_LANDSCAPE_HVGA__ __LCM_LANDSCAPE_WVGA__, $(LCM_RESOLUTION)),)
ifeq ($(filter __GAME_ENGINE_EMU_MMI__, $(PP_OPT_COMMON)), __GAME_ENGINE_EMU_MMI__)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
ifeq (TRUE, $(strip $(EMU_VIRTUAL_KEYPAD_SUPPORT)))

ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __EMU_VIRTUAL_KEYPAD_ENABLE__
else
ifneq ($(filter __GAME_ENGINE_EMU_16BIT__, $(PP_OPT_COMMON)), __GAME_ENGINE_EMU_16BIT__)
PP_OPT_COMMON += __EMU_VIRTUAL_KEYPAD_ENABLE__
endif
endif

endif
endif
endif
endif

# Feature_Name = EMU Landscape Mode
# Description = Play EMU games in landscape mode
# Pre_Condition_On = __GAME_ENGINE_EMU_MMI__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __GAME_ENGINE_EMU_MMI__, $(PP_OPT_COMMON)), __GAME_ENGINE_EMU_MMI__)
ifeq (TRUE, $(strip $(EMU_PLAY_IN_LANDSCAPE_MODE)))
PP_OPT_COMMON += __EMU_PLAY_IN_LANDSCAPE_MODE_MMI__
endif
endif

# Description = [MMI] Enable sdk display manager for 3rd developement
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SDK_BACKGROUND_EXECUTION__, $(PP_OPT_COMMON)), __SDK_BACKGROUND_EXECUTION__)
PP_OPT_COMMON += __SDK_MMI_DISPLAY_MANAGER__
endif

# Feature_Name = 3rd party app backgruond execution
# Description = Option to enable countdown timer application
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SDK_BACKGROUND_EXECUTION__, $(PP_OPT_COMMON)), __SDK_BACKGROUND_EXECUTION__)
PP_OPT_COMMON += __APP_MMI_BACKGROUND_EXECUTION__
endif

# Feature_Name = Dual SIM One Standby (CTA)
# Description = Provide Dual SIM card Single standby function for CTA usage
# Pre_Condition_On = __MSTAR_CTA_VERSION__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __MSTAR_CTA_VERSION__, $(PP_OPT_COMMON)), __MSTAR_CTA_VERSION__)
PP_OPT_COMMON += __DUAL_SIM_ONE_STANDBY_MMI__
endif

# Description = [MMI] For small rom APP
# Pre_Condition_On = __SMALL_ROM__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __APP_MMI_SMALLROM__
PP_OPT_COMMON += __WIDGET_DISABLE_FINGERCOMMAND__
PP_OPT_COMMON += __WIDGET_DISABLE_DATEICON__
PP_OPT_COMMON += __WIDGET_DISABLE_RINGLIST__
PP_OPT_COMMON += __WIDGET_DISABLE_TRANSITION__
PP_OPT_COMMON += __WIDGET_ONLY_ANIMATION_LINEAR__
PP_OPT_COMMON += __MAE_DISABLE_ERROR_ASSERT__
#PP_OPT_COMMON += __GSS_DISABLE_32BITS_FUNCTIONS__
# PP_OPT_COMMON += __GSS_DISABLE_24BITS_FUNCTIONS__
# PP_OPT_COMMON += __GSS_DISABLE_ENHANCE_BLT_FUNCTIONS__
# PP_OPT_COMMON += __GSS_DISABLE_PARTIAL_ROP_FUNCTIONS__
#PP_OPT_COMMON += __GSS_DISABLE_UNUSED_ROP_OPERATIONS__
PP_OPT_COMMON += __REMOVE_USELESS_GRAPHIC_ENGINE__
PP_OPT_COMMON += __VENDOR_SMALLROM__

ifeq (TRUE, $(strip $(EMMI_SLDPM_SUPPORT)))
ifeq (TRUE, $(strip $(MIDI_SLDPM_SUPPORT)))
PP_OPT_COMMON += __MIDI_DPM__
else
PP_OPT_COMMON += __ZIP_MIDI_TABLE__
endif
else
PP_OPT_COMMON += __ZIP_MIDI_TABLE__
endif

PP_OPT_COMMON += __SMALL_LCD_LOGO__
endif

# Description = [MMI] For Chinese IME of reduced version run in small rom platform.
# Pre_Condition_On = __SMALL_ROM__, __CHINESE_S__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq ($(filter __CHINESE_S__, $(PP_OPT_COMMON)), __CHINESE_S__)
PP_OPT_COMMON += __REDUCED_CHINESE_IME__
endif
endif

# Description = [MMI] For Display phone storage in file manager APP
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
PP_OPT_COMMON += __FILEMGRAPP_PHONESTORAGE__
else
ifeq (TRUE, $(strip $(ONBOARD_USER_STORAGE_SUPPORT)))
PP_OPT_COMMON += __FILEMGRAPP_PHONESTORAGE__
endif
endif

# Description = [MMI] For small rom APP
# Pre_Condition_On = N/A
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(CHIP_VIEW_TRANSITION)))
ifneq (FALSE, $(strip $(UI_STYLE_VIEW_TRANSITION)))
PP_OPT_COMMON += __VIEW_TRANSITION__
endif
else
PP_OPT_COMMON += __VIEW_TRANSITION__
endif
endif

# Description = [MMI] WLAN
# Pre_Condition_On = __WLAN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __WLAN__, $(PP_OPT_COMMON)), __WLAN__)
PP_OPT_COMMON += __WLAN_MMI__
endif

# Description = Option for bluetooth RDA chip and wifi MStar chip exclusion
# Pre_Condition_On = __BLUETOOTH_DRV_RDA5868__, __WLAN__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (__BLUETOOTH_DRV_RDA5868__, $(strip $(BLUETOOTH_CHIP)))
ifeq ($(filter __WLAN__, $(PP_OPT_COMMON)), __WLAN__)
PP_OPT_COMMON += __BLUETOOTH_RDA__
endif
endif

# Description = Option for NRAI fast boot debug
# Pre_Condition_On = NONE
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __NRAI_FAST_BOOT_DEBUG__

# Description = [MMI] JAVA Oakmont solution
# Pre_Condition_On = __JAVA_OAKMONT__
# Pre_Condition_Off = N/A
# Option_Selection = __JAVA_OAKMONT__
# JSRs scope options
#	1. Check if support CLDC HI (__JAVA_OAKMONT_SUP_CLDC_HI__)
#	2. Select one JSRs scope (__JAVA_OAKMONT_SCOPE_XXX__)
# Supported JSRs of __JAVA_OAKMONT_SCOPE_JAP0__
#   JSR-118(MIDP 2.0), JSR-139(CLDC 1.1), Nokia UI extension
# Supported JSRs of __JAVA_OAKMONT_SCOPE_JTWI__
#   JSR-118(MIDP 2.0), JSR-139(CLDC 1.1), JSR-185(JTWI), JSR-120(WMA 1.0), JSR-135(MMAPI 1.2),
#   JSR-75(FileConnection), Nokia UI extension
# Supported JSRs of __JAVA_OAKMONT_SCOPE_JTWI_184__
#   All of JTWI scope with JSR-184
ifeq ($(filter __JAVA_OAKMONT__, $(PP_OPT_COMMON)), __JAVA_OAKMONT__)
PP_OPT_COMMON += __JAVA__
PP_OPT_COMMON += __JAVA_MMI__
PP_OPT_COMMON += __JAVA_OAKMONT_SUP_TCK_TEST__
#PP_OPT_COMMON += __JAVA_OAKMONT_SUP_CLDC_HI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP0__
PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI_184__
PP_OPT_COMMON += AJ_PLATFORM_ARM
PP_OPT_COMMON += KJAVA_GFX_DISPLAY_565
PP_OPT_COMMON += AJSC_SUPPORT_NOKIA_EXTENSION
else
ifeq ($(filter __JAVA_OAKMONT_JAP0__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_JAP0__)
PP_OPT_COMMON += __JAVA_OAKMONT__
PP_OPT_COMMON += __JAVA__
PP_OPT_COMMON += __JAVA_MMI__
PP_OPT_COMMON += __JAVA_OAKMONT_SUP_TCK_TEST__
#PP_OPT_COMMON += __JAVA_OAKMONT_SUP_CLDC_HI__
PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP0__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI_184__
PP_OPT_COMMON += AJ_PLATFORM_ARM
PP_OPT_COMMON += KJAVA_GFX_DISPLAY_565
PP_OPT_COMMON += AJSC_SUPPORT_NOKIA_EXTENSION
endif

ifeq ($(filter __JAVA_OAKMONT_JAP1_HI__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_JAP1_HI__)
PP_OPT_COMMON += __JAVA_OAKMONT__
PP_OPT_COMMON += __JAVA__
PP_OPT_COMMON += __JAVA_MMI__
PP_OPT_COMMON += __JAVA_OAKMONT_SUP_TCK_TEST__
#PP_OPT_COMMON += __JAVA_OAKMONT_SUP_CLDC_HI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP0__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI__
PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP1_HI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI_184__
PP_OPT_COMMON += AJ_PLATFORM_ARM
PP_OPT_COMMON += KJAVA_GFX_DISPLAY_565
PP_OPT_COMMON += AJSC_SUPPORT_NOKIA_EXTENSION

endif

ifeq ($(filter __JAVA_OAKMONT_JAP2__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_JAP2__)
PP_OPT_COMMON += __JAVA_OAKMONT__
PP_OPT_COMMON += __JAVA__
PP_OPT_COMMON += __JAVA_MMI__
PP_OPT_COMMON += __JAVA_OAKMONT_SUP_TCK_TEST__
#PP_OPT_COMMON += __JAVA_OAKMONT_SUP_CLDC_HI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP0__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI_184__
PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP2__
PP_OPT_COMMON += AJ_PLATFORM_ARM
PP_OPT_COMMON += KJAVA_GFX_DISPLAY_565
PP_OPT_COMMON += AJSC_SUPPORT_NOKIA_EXTENSION

#   JAP2 specific definition
#		JSR 257 related definition.
PP_OPT_COMMON += __JAVA_OAKMONT_NFC_READER_SUPPORT__
PP_OPT_COMMON += __JAVA_OAKMONT_NFC_PUSH_SUPPORT__

# __RFID_MML_SUPPORT__ should define at RFID_SUPPORT
ifeq ($(filter __RFID_MML_SUPPORT__, $(PP_OPT_COMMON)), __RFID_MML_SUPPORT__)
PP_OPT_COMMON += __RFID_SDK_SUPPORT__
endif

endif

ifeq ($(filter __JAVA_OAKMONT_JAP2C__, $(PP_OPT_COMMON)), __JAVA_OAKMONT_JAP2C__)
PP_OPT_COMMON += __JAVA_OAKMONT__
PP_OPT_COMMON += __JAVA__
PP_OPT_COMMON += __JAVA_MMI__
PP_OPT_COMMON += __JAVA_OAKMONT_SUP_TCK_TEST__
#PP_OPT_COMMON += __JAVA_OAKMONT_SUP_CLDC_HI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP0__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JTWI_184__
#PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP2__
PP_OPT_COMMON += __JAVA_OAKMONT_SCOPE_JAP2C__
PP_OPT_COMMON += AJ_PLATFORM_ARM
PP_OPT_COMMON += KJAVA_GFX_DISPLAY_565
PP_OPT_COMMON += AJSC_SUPPORT_NOKIA_EXTENSION

#   JAP2 specific definition
#		JSR 257 related definition.
PP_OPT_COMMON += __JAVA_OAKMONT_NFC_READER_SUPPORT__
PP_OPT_COMMON += __JAVA_OAKMONT_NFC_PUSH_SUPPORT__

# __RFID_MML_SUPPORT__ should define at RFID_SUPPORT
ifeq ($(filter __RFID_MML_SUPPORT__, $(PP_OPT_COMMON)), __RFID_MML_SUPPORT__)
PP_OPT_COMMON += __RFID_SDK_SUPPORT__
endif

endif
endif


# Description = [MMI] JAVA Oakmont reduce memory
# Pre_Condition_On = JAVA_OAKMONT_LOW_MEMORY, JAVA_SOLUTION (__JAVA_OAKMONT__, __JAVA_OAKMONT_JAP0__, __JAVA_OAKMONT_JAP2__)
# Pre_Condition_Off = N/A
ifeq ($(filter __JAVA_OAKMONT__, $(PP_OPT_COMMON)), __JAVA_OAKMONT__)
ifeq (TRUE, $(strip $(JAVA_OAKMONT_LOW_MEMORY)))
PP_OPT_COMMON += __JAVA_OAKMONT_LOW_MEMORY__
PP_OPT_COMMON += __ALARM_MEMORY_LOW_KILL_3RD_VENDOR__
PP_OPT_COMMON += __MEMORY_LOW_KILL_3RD_VENDOR__
PP_OPT_COMMON += __APP_MMI_REDUCE_MEMORY_USAGE__
PP_OPT_COMMON += __3RD_LOW_MEM_RELEASE_SUSPENDVIEW__
endif
endif

# Description = [MMI] SLDLM for JAVA Oakmont
# Pre_Condition_On = RTK_OVER_ARM_SLDLM_SUPPORT, JAVA_SOLUTION (__JAVA_OAKMONT__, __JAVA_OAKMONT_JAP0__, __JAVA_OAKMONT_JAP2__)
# Pre_Condition_Off = N/A
ifeq ($(filter __JAVA_OAKMONT__, $(PP_OPT_COMMON)), __JAVA_OAKMONT__)
ifeq (TRUE, $(strip $(RTK_OVER_ARM_SLDLM_SUPPORT)))
#PP_OPT_COMMON += __ENABLE_SLDLM_JAVA_OAKMONT__
endif
endif

# Description = [MMI] NCC 3rd Java porting layer
# Pre_Condition_On = __NCC_3RD_JAVA_PORTING_LAYER__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __NCC_3RD_JAVA_PORTING_LAYER__, $(PP_OPT_COMMON)), __NCC_3RD_JAVA_PORTING_LAYER__)
PP_OPT_COMMON += __JAVA__
PP_OPT_COMMON += __JAVA_MMI__
PP_OPT_COMMON += __SLDLM_MJAVA__

ifeq (TRUE, $(strip $(ONBOARD_USER_STORAGE_SUPPORT)))
ifeq (TRUE, $(strip $(JAVA_PREINSTALL_DATA_SUPPORT)))
PP_OPT_COMMON += __NCC_3RD_JAVA_WITH_PREINSTALL__
endif
ifeq (TRUE, $(strip $(JAVA_INSTALL_TO_PHONE_SUPPORT)))
PP_OPT_COMMON += __NCC_3RD_JAVA_INSTALL_NAND__
endif
endif

PP_OPT_COMMON += JAVAAMS_UPDATE
endif

# Description = [VM] dalvik solution
# Pre_Condition_On = __SDK_API__
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifeq (TRUE, $(strip $(DALVIK_SOLUTION_SUPPORT)))
PP_OPT_COMMON += __DALVIK__
endif
endif

# Description = Enable user level pthread
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(USER_LEVEL_PTHREAD_SUPPORT)))
PP_OPT_COMMON += __USER_LEVEL_PTHREAD__
endif

# Description = [DRV] Enable UART1 control for SDK
# Pre_Condition_On = __JAVA__
# Pre_Condition_Off = __DALVIK__
# Option_Selection = N/A
ifeq ($(filter __JAVA__, $(PP_OPT_COMMON)), __JAVA__)
ifneq ($(filter __DALVIK__, $(PP_OPT_COMMON)), __DALVIK__)
PP_OPT_COMMON += __SDK_DEVICE_CONTROL__
endif
endif

ifeq ($(filter __G3D_DRV__, $(PP_OPT_COMMON)), __G3D_DRV__)
PP_OPT_COMMON +=                 \
  __KHR_EXPORTS                  \
  INCLUDE_EGL                    \
  INCLUDE_G3D                    \
  RTK
endif

ifneq (,$(strip $(RFIC)))
ifneq (,$(strip $(PA)))
RF_E2P = rfparam_$(strip $(RFIC))_$(strip $(PA)).e2p

ifeq ($(strip $(RFIC)), $(filter $(RFIC),msr7100 msr7100d))
RF_E2P += MSR7100_8533x_family.e2p
endif

ifeq (msr7120, $(strip $(RFIC)))
RF_E2P += MSR7120_8533x_family.e2p
endif

ifeq (TRUE, $(strip $(RF_26MHZ_AUXCLK_SUPPORT)))
PP_OPT_COMMON += __RF_26MHZ_AUXCLK_SUPPORT__
endif

ifeq (tgge_rf, $(strip $(RFIC)))
RF_E2P += tgge_rf_8556_family.e2p
endif

ifneq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
RF_E2P += default_calibration_$(strip $(RFIC))_$(strip $(PA)).e2p
endif

endif
endif

# Description = [DRV] Enable Legacy Clock
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
ifneq ($(RF_E2P), rfparam_aero2_4210_rfmd7163.e2p)
PP_OPT_COMMON += __RF_WITH_LEGACY__
endif

# Description = [RFDRV] Enable smart alignment for RF calibration
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = N/A
PP_OPT_COMMON += __SMART_ALIGNMENT__

PP_OPT_COMMON += SLDLM_MMAUDIO

ifeq (TRUE, $(strip $(OPT_LOW_BATT_DETECT)))
PP_OPT_COMMON += __LOW_BATT_DETECT__
endif

# Feature_Name = Binary compression
# Description = To compress target binary image
# Pre_Condition_On = (CHIP_IMAGE_COMPRESSION = TRUE) and __NAND__
# Pre_Condition_Off = N/A
# Option_Selection = = N/A
ifeq (TRUE, $(strip $(CHIP_IMAGE_COMPRESSION)))
ifeq ($(filter __NAND__, $(PP_OPT_COMMON)), __NAND__)
PP_OPT_COMMON += __IMAGE_COMPRESSION__
endif
endif


# Feature_Name = Support Display GPRS Traffic in Statusbar
# Description = To support display GPRS traffic in statusbar
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = = N/A
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(SUPPORT_DISPLAY_GPRS_TRAFFIC)))
PP_OPT_COMMON += __MMI_DISPLAY_GPRS_TRAFFIC__
endif
endif


# Feature_Name = Native Game Support
# Description = This option is added if exist any native game
# Pre_Condition_On =
# Pre_Condition_Off = N/A
# Option_Selection = = N/A
ifneq ($(filter __NATIVE_GAME_MMI_FRUIT__ __NATIVE_GAME_MMI_PACMAN__ __NATIVE_GAME_MMI_BIG2__ , $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __GAME_NATIVE_MMI__
endif

# Feature_Name = Support Network Counter App
# Description = To support Network Counter App
# Pre_Condition_On = __SDK_API__
# Pre_Condition_Off = __SMALL_ROM__
# Option_Selection = = N/A
ifeq ($(filter __SDK_API__, $(PP_OPT_COMMON)), __SDK_API__)
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifeq (TRUE, $(strip $(NETWORK_COUNTER_MMI_SUPPORT)))
PP_OPT_COMMON += __NETWORK_COUNTER_MMI__
endif
endif
endif

ifeq ($(filter __DUAL_SIM_MMI__, $(PP_OPT_COMMON)), __DUAL_SIM_MMI__)
ifeq (TRUE, $(strip $(DUAL_PROFILE_MMI_SUPPORT)))
PP_OPT_COMMON += __DUAL_PROFILE_MMI__
endif
endif

ifeq ($(filter __DUAL_SIM_MMI__, $(PP_OPT_COMMON)), __DUAL_SIM_MMI__)
ifeq (__ICONS_WITH_SIM_NUMBER__, $(strip $(STATUSBAR_SHOW_UNREAD_MESSAGE_SUPPORT)))
PP_OPT_COMMON += __MMI_STATUSBAR_SUPPORT_UNREAD_MESSAGE_BY_IMSI__
endif
endif

# Feature_Name = Calculator(MMI)
# Description = Option for calculator style
# Pre_Variable_True = TOUCH_SCREEN_DRIVER_SELECT, LCM_RESOLUTION(__LCM_QVGA__, __LCM_WQVGA_240_400__, __LCM_HVGA_320_480__, __LCM_LANDSCAPE_QVGA__, __LCM_LANDSCAPE_HVGA__), G_SENSOR_TYPE
# Pre_Variable_False = N/A
# Option_Selection = __CALCULATOR_NORMAL_STYLE__, __CALCULATOR_PLUS_STYLE__
ifeq (__CALCULATOR_NORMAL_STYLE__, $(strip $(CALCULATOR_STYLE)))
PP_OPT_COMMON += __APP_MMI_CALCULATOR__
else
ifeq (__CALCULATOR_PLUS_STYLE__, $(strip $(CALCULATOR_STYLE)))
ifneq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)), __SMALL_ROM__)
ifneq ($(filter __LCM_QVGA__ __LCM_WQVGA_240_400__ __LCM_HVGA_320_480__ __LCM_LANDSCAPE_QVGA__ __LCM_LANDSCAPE_HVGA__, $(LCM_RESOLUTION)),)
ifeq ($(filter __TOUCH_SCREEN__, $(PP_OPT_COMMON)), __TOUCH_SCREEN__)
PP_OPT_COMMON += __APP_MMI_CALCULATOR_PLUS__
endif
endif
endif
ifneq ($(filter __APP_MMI_CALCULATOR_PLUS__, $(PP_OPT_COMMON)), __APP_MMI_CALCULATOR_PLUS__)
PP_OPT_COMMON += __APP_MMI_CALCULATOR__
endif
endif
endif

# Feature_Name = Connection Setting(MMI)
# Description = Option for connection setting
# Pre_Variable_True = __MMS_MMI_CDMMS__, __WAP_MMI__, __JAVA_MMI__, __MAP_MMI_LBS__
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifneq ($(filter __MMS_MMI_CDMMS__ __WAP_MMI__  __JAVA_MMI__ __MAP_MMI_LBS__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __MMI_CONNECT_SETTING__
endif

# Feature_Name = Cell broadcast area code(MMI)
# Description = There are regulations in some country (ex:Brasil) to specifically display CBMs with channel-50 on Idle screen,
#               but not treat them as normal CBM.
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq (TRUE, $(strip $(CBM_AREA_CODE_SUPPORT)))
PP_OPT_COMMON += __MMI_CBM_AREA_CODE__
endif

# Feature_Name = Socket Service (MMI)
# Description = Option To Enable Socket Service
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = SOCKETSR_SERVICE_SUPPORT
ifeq (TRUE, $(strip $(SOCKETSR_SERVICE_SUPPORT)))
PP_OPT_COMMON += __SOCKETSRV_SUPPORT__
endif

# Feature_Name = RAI Storage configuration (MMI)
# Description = Indicate the RAI size for deciding the number of phone book contacts and SMS
# Pre_Variable_True = N/A
# Pre_Variable_False = N/A
# Option_Selection = N/A
ifeq ($(filter __SMALL_ROM__, $(PP_OPT_COMMON)),__SMALL_ROM__)
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),)
PP_OPT_COMMON += __LOW_RAI_STORAGE_SIZE__
endif
endif
ifeq ($(filter __SMALL_ROM_32__, $(PP_OPT_COMMON)),__SMALL_ROM_32__)
ifeq (0x00400000, $(strip $(SYS_PHY_RAM_SIZE_SETTING)))
PP_OPT_COMMON += __TINY_RAI_STORAGE_SIZE__
else
PP_OPT_COMMON += __LOW_RAI_STORAGE_SIZE__
endif
endif


#===============================================================================
# Memory Map Size
#===============================================================================
# Description = [SYS] Memory Map Size
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = 32MB, 64MB, 128MB
ifeq (32MB, $(strip $(MEM_MAP_SIZE)))
PP_OPT_COMMON += __MEM_MAP_32MB__
endif
ifeq (64MB, $(strip $(MEM_MAP_SIZE)))
PP_OPT_COMMON += __MEM_MAP_64MB__
endif
ifeq (128MB, $(strip $(MEM_MAP_SIZE)))
PP_OPT_COMMON += __MEM_MAP_128MB__
endif

#===============================================================================
# ** Mercury5 **
#===============================================================================
PP_OPT_COMMON += ALL_FW
PP_OPT_COMMON += BUILD_CE
PP_OPT_COMMON += VIDEO_DECODER

#=============== WIFI =======================
ifeq (TRUE, $(strip $(WIFI_PORT)))
PP_OPT_COMMON += WIFI_PORT
PP_OPT_COMMON += TARGETOS_car\
                 $(NET_OPT)
#PP_OPT_COMMON += MTK_7601_WIFI
#PP_OPT_COMMON += BCM_AP6181_WIFI
PP_OPT_COMMON += RTK_8188ftv_WIFI
#PP_OPT_COMMON += ATBM_6022_WIFI
endif

#PP_OPT_COMMON += __GNUC__

#===============================================================================
# Embeded SPI flash size
#===============================================================================
# Description = [DRV] Embeded SPI flash size
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = 0x400000
ifneq ($(filter __MSW8556M__ __MSW8556M2__, $(CHIP_TYPE)),)
DRV_EMBEDED_SPI_FLASH_SIZE = 0x400000
endif
ifeq ($(filter __MSW8556M__ __MSW8556M2__, $(CHIP_TYPE)),)
DRV_EMBEDED_SPI_FLASH_SIZE = 0
endif

#===============================================================================
# User tick length
#===============================================================================
# Description = [SYS] Memory Map Size
# Pre_Condition_On = N/A
# Pre_Condition_Off = N/A
# Option_Selection = 32MB, 64MB, 128MB
ifeq (1ms, $(strip $(RTK_USER_TICK)))
PP_OPT_COMMON += __RTK_USER_TICK_1MS__
endif
ifeq (15ms, $(strip $(RTK_USER_TICK)))
PP_OPT_COMMON += __RTK_USER_TICK_15MS__
endif
ifeq (4.6ms, $(strip $(RTK_USER_TICK)))
PP_OPT_COMMON += __RTK_USER_TICK_4DOT6MS__
endif


#===============================================================================
# ** For Java preinstall in final_product.mak **
#===============================================================================
JAVA_OPTION=__JAVA_OAKMONT__
JAVA_PREINSTALL_SOURCE=$(PATH_customer_default)mmi/resource/project/java
JAVA_PREINSTALL_TARGET = $(PATH_customer_default)mmi/resource/$(CUS_RES_PERL)/system/global_Res/java

#===============================================================================
# A mechanism use to auto select CUS (CUS_PROJECT,CUS_RES) & SIMULATOR_PROFILE parameter depend on LCM_RESOLUTION
# the script generate the CUS_PROJECT_PERL and CUS_RES_PERL ( in cus_parameter.mak) to instead of CUS_PROJECT and CUS_RES
# the mechanism is implement in configure.pl ( key word: #Auto select resolution parameter )
# set the relation with LCM_RESOLUTION , CUS and SIMULATOR_PROFILE
# format : LCM_SUPPORT = (LCM_RESOLUTION,CUS_RES,SIMULATOR_PROFILE),(LCM_RESOLUTION,CUS_RES,SIMULATOR_PROFILE)....
# if MULTI_THEMES_ENABLED is enabled and CUS_PROJECT = AUTO, auto select CommonPortraitTheme or CommonLandscapeTheme
# if SMALL_ROM_SUPPORT is enabled, auto add "SmallRom" in CUS_RES ( for example: QVGA_Res ==> QVGA_Smallrom_Res )
#===============================================================================
LCM_SUPPORT = (__LCM_QVGA__,QVGA_Res,QVGA),(__LCM_WQVGA_240_400__,WQVGA_Res,WQVGA),(__LCM_QCIF_PLUS__,QCIF_Res,QCIF),(__LCM_HVGA_320_480__,HVGA_Res,HVGA),(__LCM_LANDSCAPE_QVGA__,QVGA_Res,Landscape_QVGA),(__LCM_LANDSCAPE_QCIF__,QCIF_Res,Landscape_QCIF),(__LCM_LANDSCAPE_HVGA__,HVGA_Res,Landscape_HVGA),(__LCM_QQVGA__,QQVGA_Res,QQVGA),(__LCM_LANDSCAPE_QQVGA__,QQVGA_Res,Landscape_QQVGA),(__LCM_LANDSCAPE_WQVGA_240_400__,WQVGA_Res,Landscape_WQVGA),(__LCM_LANDSCAPE_WVGA__,WVGA_Res,Landscape_WVGA),(__LCM_WVGA__,WVGA_Res,WVGA)

#===============================================================================
# ** Platform SW version **
#===============================================================================
ifeq ($(call FILE_EXISTED, $(COMMON)version.mak), TRUE)
include $(COMMON)version.mak
endif

#===============================================================================
# ** Platform Customer SW version **
#===============================================================================
include $(COMMON)version_cus.mak

#===============================================================================
# ** To include compiler options **
#===============================================================================
include $(COMMON)compiler_option.mak
