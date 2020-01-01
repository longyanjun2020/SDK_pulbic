


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

#= DUO section =================================================================
# -- Modification for project DUO
# JY: Place the name of module you want to duplicate here. An additional library
#     will be produced with all exported symbols renamed (by post-fix "_2")
#
# Alex: Add sim module to duplicate for B2.
PRODUCT_LIB_STACK2 =        \

PRODUCT_LIB_STACK2_MERGE =     \
				stack_2

#===============================================================================

PRODUCT_SC = \
                I_SW_Other\
                fcie\
                storage\
                storage_mdl\
                sdio\
                arm\
                boot\
                kernel_hal\
                int\
                int_hal\
                timer\
                timer_hal\
                clkgen\
                clkgen_hal\
                pll_hal\
                drvutil_hal\
                dynscl\
                dynscl_hal\
                efat\
                efat_wrapper\
                efat_cust\
                disk\
                disk_storage\
                mtmgr\
                MsWrapper\
                cust_sys\
                pm\
                pm_hal\
                power\
                dynldr\
                rai\

#                power_hal
#                asura_hal\
#                sdio\
#                sdio_hal\

# ===================================
# === ADD YOUR DRIVER MODULE HERE ===

#=============== SIM =======================
#PP_OPT_COMMON += __VER_SIM__
#PRODUCT_SC += sim_i_sw

#=============== EMI =======================
PRODUCT_SC += emi \
               emi_hal \
               flash \
               fms_cus\
               acc

ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRODUCT_SC += fms_nand
else
PRODUCT_SC += fms_nor
endif

PP_OPT_COMMON += __VER_EMI__
PP_OPT_COMMON += __VER_IMI__
#                                __VER_IMI__ \
#                                __VER_IMIBW__ \

#=============== FMRX =======================
PRODUCT_SC += fmrx \
              fmrx_hal
PP_OPT_COMMON += __VER_FMRX__

#=============== ADCDUMP =======================
PRODUCT_SC += adcdump \
              adcdump_hal
PP_OPT_COMMON += __VER_ADCDMA__

#=============== Timer =======================
PP_OPT_COMMON += __VER_TIMER__

#=============== IO =======================
PRODUCT_SC += io \
              io_hal \
              cust_drv
PP_OPT_COMMON += __VER_IO__

#=============== Misc =======================
PRODUCT_SC += misc \

PP_OPT_COMMON += __VER_MISC__

#=============== PADCTRL =======================
PP_OPT_COMMON += __VER_PADCTRL__

#=============== USB =======================
PRODUCT_SC += usb\
              usb_hal\
              usb_mdl
PP_OPT_COMMON += __VER_USB__

#=============== Camera =======================
PRODUCT_SC += camera_mdl

PP_OPT_COMMON += __VER_CAMERA__
#=============== UNFD =======================
ifeq ($(call FIND_COMPILER_OPTION, __NAND__), TRUE)
PRODUCT_SC += unfd \
              unfd_hal
endif

#PP_OPT_COMMON += __VER_UNFD__
#PP_OPT_COMMON += __VER_UNFD_FTL__

#=============== BUS =======================
PRODUCT_SC += bus\
              bus_hal
PP_OPT_COMMON += __VER_I2C__
PP_OPT_COMMON += __VER_SPI__
PP_OPT_COMMON += __VER_ASURA_PMU__

#=============== GDMA =======================
PRODUCT_SC += gdma_hal

PP_OPT_COMMON += __VER_GDMA__

#=============== DMA =======================
PRODUCT_SC += dma\
              dma_hal
ifeq ($(filter __DRV_HW_DMA__, $(PP_OPT_COMMON)), __DRV_HW_DMA__)
PP_OPT_COMMON += __VER_DMA__
endif


#=============== JPD =======================
#PRODUCT_SC += jpd\

#              jpd_hal
#PP_OPT_COMMON += __VER_JPD__

#=============== JPE =======================
PRODUCT_SC += jpe\
              jpe_hal
#PP_OPT_COMMON += __VER_JPE__

#=============== JPEMIDDLE =======================
PRODUCT_SC += image_capture

#PP_OPT_COMMON += __VER_JPEMID__

#=============== DMA2D =======================
PRODUCT_SC += dma2d\
              dma2d_hal
PP_OPT_COMMON += __VER_DMA2D__

#=============== Sensor Driver =======================
PRODUCT_SC += sensordriver\

PP_OPT_COMMON += __VER_SENSORDRIVER__
#=============== SensorIF =======================
PRODUCT_SC += sensorif\
              sensorif_hal
PP_OPT_COMMON += __VER_SENSORIF__
#=============== SCL =======================
PRODUCT_SC += scl\
              scl_hal
#PP_OPT_COMMON += __VER_SCL__

#=============== DISP =======================
PRODUCT_SC += disp\
              disp_hal

PP_OPT_COMMON += __VER_DISP__

#=============== IMAGE =======================
#PRODUCT_SC += image_codec\

#PP_OPT_COMMON += __VER_IMAGE__

#=============== RTC =======================
PRODUCT_SC += rtc\
              rtc_hal

PP_OPT_COMMON += __VER_RTC__

#=============== AUX =======================
PRODUCT_SC += tscr \
              tscr_hal \

PP_OPT_COMMON += __VER_AUX__


#=============== AUDIO =======================
PRODUCT_SC += audio_drv\
              audio_hal

PP_OPT_COMMON += __VER_AUD__

#=============== ZLIB =======================
ifeq ($(filter __HW_ZLIB_SUPPORT__ ,$(PP_OPT_COMMON)),__HW_ZLIB_SUPPORT__)
PRODUCT_SC += zlib_drv\
			  zlib_hal

PP_OPT_COMMON += __VER_ZLIB__
endif

#=============== PREVIEW =======================
#PRODUCT_SC += preview

#PP_OPT_COMMON += __VER_PREVIEW__

#=============== UART ======================
PP_OPT_COMMON += __VER_UART__
PRODUCT_SC += uart \

#=============== FCS_GEA ======================
PRODUCT_SC += hwl_i_sw

PP_OPT_COMMON += __VER_FCS_GEA__

#=============== ASURA ADC =======================

PRODUCT_SC += adc_hal\
              batt_hal
#              athena_hal

#              athena\

PP_OPT_COMMON += __VER_ASURA_ADC__
PP_OPT_COMMON += __VER_SARADC__

#============== RGBLED ===========================
PRODUCT_SC += gpd_hal

PP_OPT_COMMON += __VER_RGBLED__

#============== B3_PMU ===========================
PRODUCT_SC += pmu_hal

PP_OPT_COMMON += __VER_B3_PMU__

ifeq ($(call FIND_COMPILER_OPTION, __ISW_8533D__), TRUE)
#=============== Bravo Efuse ======================
PP_OPT_COMMON += __VER_BRAVO_EFUSE__
else ifeq ($(call FIND_COMPILER_OPTION, __ISW_8532B__), TRUE)
#=============== Bravo Efuse ======================
PP_OPT_COMMON += __VER_BRAVO_EFUSE__
else ifeq ($(call FIND_COMPILER_OPTION, __ISW_8556R__), TRUE)
#=============== Bravo Efuse ======================
PP_OPT_COMMON += __VER_BRAVO_EFUSE__
endif


#=============== CMU ======================
PP_OPT_COMMON += __VER_CMU__

#=============== CLKGEN ===================
PP_OPT_COMMON += __VER_CLKGEN__

#=============== PLL ======================
PP_OPT_COMMON += __VER_PLL__

#=============== DynScl ======================
PP_OPT_COMMON += __VER_DYNSCL__


PRODUCT_SC += keypad\
              keypad_hal

PP_OPT_COMMON += __VER_KEYPAD__


#=============== DSP =======================
PRODUCT_SC += dsp_isw

PP_OPT_COMMON += __VER_DSP__

#=============== SharedIF =======================
PRODUCT_SC += sharedif

PP_OPT_COMMON += __VER_SHARED_IF__

#=============== VDR ======================
PRODUCT_SC += vdr_i_sw

PP_OPT_COMMON += __VER_VDR__

#=============== INTC ======================
PP_OPT_COMMON += __VER_INTC__

#=============== EXT_INT ======================
PP_OPT_COMMON += __VER_EXTINT__

#=============== Bluetooth =======================
PRODUCT_SC += bt_mac_normal bt_mac_critical

PP_OPT_COMMON += __VER_BLUETOOTH__

ifeq ($(call FIND_COMPILER_OPTION, __ISW_8533D__), TRUE)
#=============== ROM PATCH ======================
PRODUCT_SC += rompatch_hal
PP_OPT_COMMON += __VER_ROMPATCH__
else ifeq ($(call FIND_COMPILER_OPTION, __ISW_8532B__), TRUE)
#=============== ROM PATCH ======================
PRODUCT_SC += rompatch_hal
PP_OPT_COMMON += __VER_ROMPATCH__
else ifeq ($(call FIND_COMPILER_OPTION, __ISW_8556R__), TRUE)
#=============== ROM PATCH ======================
PRODUCT_SC += rompatch_hal
PP_OPT_COMMON += __VER_ROMPATCH__
endif

# == THE END OF DRIVER MODULE LIST ==
# ===================================


#= DUO section =================================================================
# -- Modification for project DUO
# JY: Place the name of module you want to duplicate here. An additional library
#     will be produced with all exported symbols renamed (by post-fix "_2")
#
# Alex: Add sim module to duplicate for B2.
PRODUCT_SC_STACK2 =        \

#===============================================================================


#
# module FLAVOR setting
#

#FLAVOR_bus = _cork
#FLAVOR_io  = _cork
#FLAVOR_ir   = _cork
#FLAVOR_sim = _cork
FLAVOR_v42  = _cork
FLAVOR_fax  = _cork













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


ifeq ($(filter __TEST_LOAD__ ,$(PP_OPT_COMMON)),__TEST_LOAD__)
PATH_zlib = $(PATH_3rd)/utility/zlib
PRODUCT_SC += zlib
PATH_C += $(PATH_zlib)/src
PATH_H += $(PATH_zlib)/inc
endif


PATH_dsp_isw = $(PATH_drv)/dsp_isw
PATH_sharedif = $(PATH_drv)/sharedif




PATH_C +=\
    $(PATH_system)/trc/src\
    $(PATH_system)/sys/src\
    $(PATH_system)/sys/src_cus\
    $(PATH_drv)/int/src\
    $(PATH_cus_app)/src\
    $(PATH_telecom)/csn1/gen/src\

PATH_C +=\
    $(PATH_dma_hal)/src\
    $(PATH_uart)/src\
    $(PATH_uart_hal)/src\
    $(PATH_dma2d)/src\
    $(PATH_dma2d_hal)/src\
    $(PATH_scl)/src\
    $(PATH_scl_hal)/src\
    $(PATH_sensordriver)/src\
    $(PATH_sensorif)/src\
    $(PATH_sensorif_hal)/src\
    $(PATH_camera_mdl)/src\
    $(PATH_dsp_isw)/src\
    $(PATH_dsp_isw)/src/dsp_code\
    $(PATH_sharedif)/src\
    $(PATH_sharedif)/src/dsp_code\
    $(PATH_disk)/src

PATH_H +=\
    $(PATH_system)/sys/itf\
    $(PATH_system)/sys/inc\
    $(PATH_system)/sys/itf_open\
    $(PATH_system)/rtk/inc\
    $(PATH_dma_hal)/inc\
    $(PATH_dma2d)/inc\
    $(PATH_dma2d_hal)/inc\
    $(PATH_scl)/inc\
    $(PATH_scl_hal)/inc\
    $(PATH_sensordriver)/inc\
    $(PATH_sensorif)/inc\
    $(PATH_sensorif_hal)/inc\
    $(PATH_camera_mdl)/inc\
    $(PATH_mmp_common)/../../include\
    $(PATH_dsp_isw)/inc\
    $(PATH_sharedif)/inc\
    $(PATH_disk)/inc\

# CUS group source code

#==============================================================================#
PATH_C +=\
    $(PATH_cus_app_lib)/src\
    $(PATH_cus_app_sc)/src

PATH_H +=\
    $(PATH_app)\
    $(PATH_mae)/inc\
    $(PATH_core)/interface/inc\
    $(PATH_cus_app)/inc

# MDL group source code
PATH_C +=\
    $(PATH_storage_mdl)/src\
    $(PATH_ril)/ril/src\
	$(PATH_sril)/src\
    $(PATH_tscr_mdl)/src\
    $(PATH_gpd_mdl)/src\
    $(PATH_usb_mdl)/src\
    $(PATH_camera)/src\
    $(PATH_mmmanager)/src\
    $(PATH_mmmanager_lib)/src

PATH_H +=\
    $(PATH_storage_mdl)/inc\
    $(PATH_tscr_mdl)/inc\
    $(PATH_gpd_mdl)/inc\
    $(PATH_usb_mdl)/inc\
    $(PATH_audio_mdl)/inc\
    $(PATH_camera)/inc\
    $(PATH_batt)/inc\
    $(PATH_mmmanager)/inc\
    $(PATH_mmmanager_lib)/inc


PATH_EXT_LIB += $(PATH_stereo_video)
PATH_EXT_LIB += $(PATH_stereo_image)

# DRV group source code
PATH_C +=\
    $(PATH_unfd)/src\
    $(PATH_unfd_hal)/src\
    $(PATH_mtmgr)/src\
    $(PATH_vfs)/src\
    $(PATH_acc)/opxc\
    $(PATH_acc)/src\
    $(PATH_adcdump)/src\
    $(PATH_adcdump_hal)/src\
    $(PATH_image_codec)/src\
	$(PATH_image_capture_i_sw)/src\
    $(PATH_vfs)/src\
    $(PATH_bluetooth)/src\
    $(PATH_fmrx)/src\
    $(PATH_fmrx_hal)/src\
    $(PATH_gpd)/src\
    $(PATH_gsensor)/src\
    $(PATH_tscr)/src\
    $(PATH_disp)/src\
    $(PATH_tscr_hal)/src\
    $(PATH_gpd_hal)/src\
    $(PATH_power)/src\
    $(PATH_audio_drv)/src\
    $(PATH_audio_hal)/src\
    $(PATH_dynscl)/src\
    $(PATH_dynscl_hal)/src\
    $(PATH_storage)/src\
    $(PATH_sdio)/src\
    $(PATH_jpe)/src\
    $(PATH_jpe_hal)/src\
    $(PATH_jpd)/src\
    $(PATH_usb)/src\
    $(PATH_usb_hal)/src\
    $(PATH_uart)/src\
    $(PATH_efat)/src\
    $(PATH_efat_wrapper)/src\
    $(PATH_pmu_hal)/src\
    $(PATH_adc_hal)/src\
    $(PATH_lcd)/inc\
    $(PATH_vdr_i_sw)/src\

#    $(PATH_athena_hal)/src\
#    $(PATH_asura_hal)/src\
#    $(PATH_athena)/src\

ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
PATH_C +=\
    $(PATH_atv)/src
endif

PATH_H +=\
    $(PATH_unfd)/inc\
    $(PATH_unfd)/pub\
    $(PATH_unfd_hal)/inc\
    $(PATH_mtmgr)/itf\
    $(PATH_vfs)/itf\
    $(PATH_image_codec)/inc\
	$(PATH_image_capture_i_sw)/inc\
    $(PATH_acc_inc)/inc\
    $(PATH_acc_inc)/itf\
    $(PATH_adcdump)/inc\
    $(PATH_adcdump_hal)/inc\
    $(PATH_esl)/itf\
    $(PATH_acc_inc)/itf_open\
    $(PATH_vfs)/itf\
    $(PATH_vfs)/inc\
    $(PATH_ema)/main/inc\
    $(PATH_bluetooth)/inc\
    $(PATH_fmrx)/inc\
    $(PATH_fmrx_hal)/inc\
    $(PATH_gpd)/inc\
    $(PATH_tscr)/inc\
    $(PATH_rtc)/inc\
    $(PATH_disp)/inc\
    $(PATH_tscr_hal)/inc\
    $(PATH_gpd_hal)/inc\
    $(PATH_power)/inc\
    $(PATH_audio_drv)/inc\
    $(PATH_audio_hal)/inc\
    $(PATH_zlib_drv)/inc\
    $(PATH_zlib_hal)/inc\
    $(PATH_dynscl)/inc\
    $(PATH_dynscl)/pub\
    $(PATH_dynscl_hal)/inc\
    $(PATH_storage)/inc\
    $(PATH_sdio)/inc\
    $(PATH_jpd)/src\
    $(PATH_usb)/inc\
    $(PATH_usb_hal)/inc\
    $(PATH_uart)/inc\
    $(PATH_uart_hal)/inc\
    $(PATH_mmicomn)/inc\
    $(PATH_efat)/inc\
    $(PATH_efat_wrapper)/inc\
    $(PATH_pmu_hal)/inc\
    $(PATH_adc_hal)/inc\
    $(PATH_jpe)/inc\
    $(PATH_jpe_hal)/inc\
    $(PATH_jpd)/inc\
    $(PATH_io)/inc\
    $(PATH_vdr_i_sw)/inc\

#    $(PATH_athena_hal)/inc\

PATH_gdma_hal = $(PATH_hal)gdma
PATH_C +=\
  $(PATH_gdma_hal)/src
PATH_H +=\
  $(PATH_gdma_hal)/inc


#    $(PATH_asura_hal)/inc\
#    $(PATH_athena)/inc\

ifeq ($(filter __ATV_DRV__ ,$(PP_OPT_COMMON)),__ATV_DRV__)
PATH_H +=\
    $(PATH_atv)/inc
endif

# SYS group source code
PATH_C +=\
    #$(PATH_fat)/src\
    $(PATH_cn)/src\
    $(PATH_ResMgr)/src/ABL \
    $(PATH_ResMgr)/src/DataStruct \
    $(PATH_ResMgr)/src/DBL \
    $(PATH_ResMgr)/src/HAL \
    $(PATH_ResMgr)/src/MediaCmd \
    $(PATH_ResMgr)/src/ResMgr \
    $(PATH_ResMgr)/src/Util \
    $(PATH_cust_sys)/src

PATH_H +=\
    #$(PATH_fat)/inc\
    #$(PATH_fat)/itf\
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
    $(PATH_cust_sys)/inc\


#MMI group source code

MMI_PATH_H +=\
    $(PATH_mae)/inc \
    $(PATH_mae)/extras/sqlite3\
    $(PATH_mmi_res)/resourceLib \
    $(PATH_mmi_res)\
    $(PATH_vdr_i_sw)/inc\

MMI_PATH_H +=\
    $(PATH_core) \
    $(PATH_core)/interface/inc\
    $(PATH_lcd)/inc\
    $(PATH_lcd_hal)/inc


# CUS group source code
PATH_C +=\

PATH_H +=\

PRODUCT_SC += \
                sys_I_SW\
                rtk\
                rtk_cus

ifneq ($(call FIND_COMPILER_OPTION, __G1__), TRUE)
ARM_LIB_LIST = \
    arm \
    opec \
    viddecoder
endif

# redefine the unneccesary libraries for I_SW
PRODUCT_SC_MDL = \

PRODUCT_SC_DRV = \

PRODUCT_SC_SYS = \

PRODUCT_SC_MMI_APP = \

PRODUCT_SC_MMI_SRV = \

PRODUCT_SC_MMI_MAE = \

PRODUCT_SC_MMI_MAE_PORTING = \

PRODUCT_SC_MMI_CORE = \

PRODUCT_SC_MMI_MMICOMN = \

PRODUCT_SC_MMI_WIDGET = \

PRODUCT_SC_MMI_MODEL = \

PRODUCT_SC_3RD = \

PRODUCT_SC_CUS = \

ifeq ($(call FIND_COMPILER_OPTION, __ISW_8533D__), TRUE)
PATH_C +=\
  $(PATH_rompatch_hal)/src
PATH_ASM +=\
  $(PATH_rompatch_hal)/src
PATH_H +=\
  $(PATH_rompatch_hal)/inc
else ifeq ($(call FIND_COMPILER_OPTION, __ISW_8532B__), TRUE)
PATH_C +=\
  $(PATH_rompatch_hal)/src
PATH_ASM +=\
  $(PATH_rompatch_hal)/src
PATH_H +=\
  $(PATH_rompatch_hal)/inc
else ifeq ($(call FIND_COMPILER_OPTION, __ISW_8556R__), TRUE)
PATH_C +=\
  $(PATH_rompatch_hal)/src
PATH_ASM +=\
  $(PATH_rompatch_hal)/src
PATH_H +=\
  $(PATH_rompatch_hal)/inc
endif

PATH_C +=\
    $(PATH_hwll1)/src

PATH_H +=\
    $(PATH_hwll1)/inc\

