

#-------------------------------------------------------------------------------
# LINK: Decide which libs would be linked to image.
#-------------------------------------------------------------------------------
#ifeq ($(LINKER),AEONGCC_link)
#LINK += $(OUT)sys_boot_g1_vectors.o $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC:%=$(OUT)%.lib))  $(EXT_LIBS:%=$(OUT)%)
#else
#EXT_LIBS += sig_ta.lib
#LINK += $(OUT)drv_keypad.o $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC:%=$(OUT)%.lib))  $(EXT_LIBS:%=$(OUT)%)
#endif

ifeq ($(LINKER),AEONGCC_link)
LINK += $(OUT)sys_c_start.o $(PRODUCT_SC:%=$(OUT)%.lib) $(EXT_LIBS:%=$(OUT)%)
else
ifeq ($(LINKER),ARMGCC_link)
LINK += $(PRODUCT_SC:%=$(OUT)%.lib) $(EXT_LIBS:%=$(OUT)%)
else
EXT_LIBS += sig_ta.lib
LINK += $(OUT)sys_boot_blossom.o $(PRODUCT_SC:%=$(OUT)%.lib) $(EXT_LIBS:%=$(OUT)%)
endif
endif

#LINK+=$(EXISTED_LIBS_FILE)
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_LIB:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_LIB_MMI:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_LIB_MDL:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_LIB_DRV:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_LIB_3RD:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_LIB_SYS:%=$(OUT)%.lib))
#LINK += $(filter-out $(EXISTED_LIBS), $(PRODUCT_SC_MMI_LIB:%=$(OUT)%.lib))
#LINK += $(EXISTED_LIBS)


LINK += $(PRODUCT_LIB:%=$(OUT)%.lib)
LINK += $(PRODUCT_LIB_MMI:%=$(OUT)%.lib)
LINK += $(PRODUCT_LIB_MDL:%=$(OUT)%.lib)
LINK += $(PRODUCT_LIB_DRV:%=$(OUT)%.lib)
LINK += $(PRODUCT_LIB_3RD:%=$(OUT)%.lib)
LINK += $(PRODUCT_LIB_SYS:%=$(OUT)%.lib)
LINK += $(PRODUCT_SC_MMI_LIB:%=$(OUT)%.lib)


ifneq ($(BB_CHIP_ID),msw8830x)
ifeq ($(filter __WLAN_IP_SUPPORT__ ,$(PP_OPT_COMMON)),__WLAN_IP_SUPPORT__)
LINK += $(OUT_DUP)stack_2.axf
endif
endif

ifeq ($(CHIP_BT_MAC_SEL),BRAVO)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__ ,$(PP_OPT_COMMON)),__BLUETOOTH_DRV_MSTAR_ACRUX2__)
ifeq ($(filter __BT_ROM_U02__ ,$(PP_OPT_COMMON)),__BT_ROM_U02__)
LINK += $(PATH_bt_mac)/rom/bt_rom_msw8533d_u02.sym
else
LINK += $(PATH_bt_mac)/rom/bt_rom_msw8533d_u03.sym
endif
endif
endif

ifeq ($(CHIP_BT_MAC_SEL),B5)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__ ,$(PP_OPT_COMMON)),__BLUETOOTH_DRV_MSTAR_ACRUX2__)
LINK += $(PATH_bt_mac)/rom/bt_rom_msw853xb_u03.sym
endif
endif

ifeq ($(CHIP_BT_MAC_SEL),BLOSSOM)
ifeq ($(filter __BLUETOOTH_DRV_MSTAR_ACRUX2__ ,$(PP_OPT_COMMON)),__BLUETOOTH_DRV_MSTAR_ACRUX2__)
LINK += $(PATH_bt_mac)/rom/bt_rom_msw8556x_u01.sym
endif
endif

ifeq (ZLIB_USE_ROM=1,$(filter ZLIB_USE_ROM=1,$(PP_OPT_COMMON)))
LINK += $(PATH_sc)/application/3rd/utility/zlib/zlib_rom_symbol_$(BB_CHIP_ID).sym
endif

ifeq ($(filter __E2P_INDEX_SYM__ ,$(PP_OPT_COMMON)), __E2P_INDEX_SYM__)
LINK += $(OUT)e2p_symbol.sym
endif

#-------------------------------------------------------------------------------
# Remove dummy lib
#-------------------------------------------------------------------------------
LINK:=$(filter-out $(DUMMY_LIB_LIST:%=$(OUT)%.lib), $(LINK))


#-------------------------------------------------------------------------------
# Remove dummy lib and add pure lib in release build
#-------------------------------------------------------------------------------
#include $(FEATURE_LIB_LIST_FILE)
include $(COMMON_LIB_LIST_FILE)

ifeq ($(RELEASE_PROCESS),1)
include $(SC_LIB_LIST)
ifeq (LOG_LEVEL_CRITICAL_ONLY,$(strip $(LOG_LEVEL_CUT_OPTION)))
include $(NON_CT_LIST)
#LIB_LIST: pure lib list
#NON_CRITICAL_TRACE_LIST: libs without critical trace
LINK := $(filter-out $(LIB_LIST:%=$(OUT)%.lib),$(LINK))

pure-libs:=$(filter $(NON_CRITICAL_TRACE_LIST),$(filter-out $(DUMMY_LIB_LIST),$(LIB_LIST)))
ct-pure-libs:=$(filter-out $(NON_CRITICAL_TRACE_LIST),$(filter-out $(DUMMY_LIB_LIST),$(LIB_LIST)))

PURE_COMMON_LIST 	:= $(call filter_common_libs,$(pure-libs))
PURE_COMMON_CT_LIST := $(call filter_common_libs,$(ct-pure-libs))
PURE_FEATURE_LIST 	:= $(call filter_feature_libs,$(pure-libs))
PURE_FEATURE_CT_LIST:= $(call filter_feature_libs,$(ct-pure-libs))
PURE_BSP_LIST		:= $(call filter_bsp_libs,$(pure-libs))
PURE_BSP_CT_LIST	:= $(call filter_bsp_libs,$(ct-pure-libs))
PURE_CHIP_LIST 		:= $(call filter_chip_libs,$(pure-libs))
PURE_CHIP_CT_LIST 	:= $(call filter_chip_libs,$(ct-pure-libs))

LINK := $(LINK) \
	$(PURE_COMMON_LIST:%=./sc/libs/COMMON/%) \
	$(PURE_COMMON_CT_LIST:%=./sc/libs/COMMON/ct/%.lib) \
	$(PURE_FEATURE_LIST:%=./sc/libs/$(LIBS_PATH_BY_FEATURE)/%.lib) \
	$(PURE_FEATURE_CT_LIST:%=./sc/libs/$(LIBS_PATH_BY_FEATURE)/ct/%.lib) \
	$(PURE_BSP_LIST:%=./sc/libs/$(LIBS_PATH_BY_BSP)/%.lib) \
	$(PURE_BSP_CT_LIST:%=./sc/libs/$(LIBS_PATH_BY_BSP)/ct/%.lib) \
	$(PURE_CHIP_LIST:%=./sc/libs/$(LIBS_PATH_BY_CHIP)/%.lib) \
	$(PURE_CHIP_CT_LIST:%=./sc/libs/$(LIBS_PATH_BY_CHIP)/ct/%.lib) \

else
LINK 				:= $(filter-out $(LIB_LIST:%=$(OUT)%.lib),$(LINK))
pure-libs 			:= $(filter-out $(DUMMY_LIB_LIST),$(LIB_LIST))

PURE_COMMON_LIST	:= $(call filter_common_libs,$(pure-libs))
PURE_FEATURE_LIST	:= $(call filter_feature_libs,$(pure-libs))
PURE_BSP_LIST		:= $(call filter_bsp_libs,$(pure-libs))
PURE_CHIP_LIST		:= $(call filter_chip_libs,$(pure-libs))

LINK 				:= $(LINK) \
	$(PURE_COMMON_LIST:%=./sc/libs/COMMON/%.lib) \
	$(PURE_FEATURE_LIST:%=./sc/libs/$(LIBS_PATH_BY_FEATURE)/%.lib) \
	$(PURE_BSP_LIST:%=./sc/libs/$(LIBS_PATH_BY_BSP)/%.lib) \
	$(PURE_CHIP_LIST:%=./sc/libs/$(LIBS_PATH_BY_CHIP)/%.lib)
endif
endif


#-------------------------------------------------------------------------------
# all mmi lib list, it would be used in scatter file
#-------------------------------------------------------------------------------
__ALL_MMI_LIB__=$(filter-out $(PRODUCT_SC_MMI_APP),$(PRODUCT_SC_MMI))
__ALL_MMI_LIB__:=$(__ALL_MMI_LIB__:%=*%\#\#.\#\#lib) $(PRODUCT_LIB_MMI:%=*%\#\#.\#\#lib)
__ALL_MMI_APP_LIB__:=$(PRODUCT_SC_MMI_APP:%=*%\#\#.\#\#lib)
#__ALL_STACK_LIB__:= $(filter-out arm boot l1c hwl hwl_prod cus_app cus_app_lib cus_app_sc MsWrapper rtk rtk_cus sys sys_cus trc trc_cus dynldr dynldr_cus, $(PRODUCT_SC) $(PRODUCT_LIB))
#__ALL_STACK_LIB__:=$(__ALL_STACK_LIB__:%=*%\#\#.\#\#lib)
__ATV_3RD_LIBS_LIST__=$(ATV_3RD_LIBS_LIST:%.lib=*%\#\#.\#\#lib)
ifneq ($(strip $(ATV_3RD_LIBS_LIST)),)
__ATV_3RD_LIBS_LIST_RW__ = $(addsuffix (+RO,+RW),$(__ATV_3RD_LIBS_LIST__))
__ATV_3RD_LIBS_LIST_ZI__ = $(addsuffix (+ZI),$(__ATV_3RD_LIBS_LIST__))
endif

SPECIAL_D= -D__ALL_MMI_LIB__='$(__ALL_MMI_LIB__)'  -D__ALL_MMI_APP_LIB__='$(__ALL_MMI_APP_LIB__)'\
	-D__ATV_3RD_LIBS_LIST_RORW__='$(__ATV_3RD_LIBS_LIST_RW__)' -D__ATV_3RD_LIBS_LIST_ZI__='$(__ATV_3RD_LIBS_LIST_ZI__)'


#-------------------------------------------------------------------------------
# SCATTER: Scatter file
#-------------------------------------------------------------------------------
ifeq ($(filter __ISW_8532B__, $(PP_OPT_COMMON)), __ISW_8532B__)
SCATTER = $(PATH_cust_scatter)scatter_8532b_isw.dsc
SCATTER_OUT = $(OUT)scatter.dsc
else # __ISW_8532B__
ifeq ($(filter __ISW_8556R__, $(PP_OPT_COMMON)), __ISW_8556R__)
ifeq ($(LINKER),ARMGCC_link)
SCATTER = $(PATH_cust_scatter)scatter_8556r_isw.lds
SCATTER_OUT = $(OUT)scatter.lds
else
SCATTER = $(PATH_cust_scatter)scatter_8556r_isw.dsc
SCATTER_OUT = $(OUT)scatter.dsc
endif
else # __ISW_8556R__
ifeq ($(BB_CHIP_ID),msw8830x)
SCATTER = $(PATH_cust_scatter)scatter_8830n.ldi
SCATTER_DPM = $(PATH_cust_scatter)scatter_8830n_dpm.lds
SCATTER_OUT = $(OUT)scatter_8830n.lds
else # MSW8830X
ifeq ($(LINKER),ARMGCC_link)
SCATTER = $(PATH_cust_scatter)$(CHIP_SCATTER).lds
SCATTER_OUT = $(OUT)scatter.lds
else
SCATTER = $(PATH_cust_scatter)$(CHIP_SCATTER).dsc
SCATTER_OUT = $(OUT)scatter.dsc
endif # ARMGCC_link
endif # msw8830x
endif # __ISW_8556R__
endif # __ISW_8532B__

CUST_ALL_OBJS_LIST :=

# $(call add-cust-objs, precedence_position_objs, wildcard_objs)
define add-cust-objs
    TEMP_1ST_OBJS := $(wildcard $(addprefix $(OUT), $(notdir $1)))
    TEMP_2ND_OBJS := $(filter-out $(wildcard $(addprefix $(OUT), $(notdir $1))), \
                       $(sort $(wildcard $(2:%=$(OUT)%))))
    CUST_ALL_OBJS_LIST += $$(TEMP_1ST_OBJS) $$(TEMP_2ND_OBJS)
endef

#: Add for keeping cust table variables
ifneq ($(filter __CUS_LCM_TABLE_DRV__, $(PP_OPT_COMMON)), __CUS_LCM_TABLE_DRV__)
$(eval $(call add-cust-objs, $(LCD_SRC_PRECEDENCE_LINK:%.c=%.o), $(LCD_SRC_LIST:%.c=%.o) cust_lcd_*.o))
endif

$(eval $(call add-cust-objs, , cust_backlight_*.o))

ifneq (, $(strip $(SUBBACKLIGHT)))
$(eval $(call add-cust-objs, , cust_subbacklight_*.o))
endif

ifneq (, $(strip $(OFN)))
$(eval $(call add-cust-objs, , cust_ofn_*.o))
endif

ifeq ($(filter __G_SENSOR_DRV__, $(PP_OPT_COMMON)), __G_SENSOR_DRV__)
ifneq (,$(strip $(GSENSOR)))
$(eval $(call add-cust-objs, , cust_gsensor_*.o))
endif
endif

ifneq (,$(strip $(TOUCH_SCREEN_DRIVER_SELECT)))
$(eval $(call add-cust-objs, , cust_tscr_*.o))
endif

ifneq (, $(strip $(PSENSOR)))
$(eval $(call add-cust-objs, , cust_proximity_sensor_*.o))
endif

ifneq (, $(strip $(BREATHLIGHT)))
$(eval $(call add-cust-objs, , cust_breathlight_*.o))
endif


#-------------------------------------------------------------------------------
# LDFLAGS component
#-------------------------------------------------------------------------------

VERBOSE_OPTION=$(if $(filter 1, $(LINK_VERBOSE)), --verbose)
CALL_GRAPH_OPTION=$(if $(filter 1, $(LINK_CALL_GRAPH)), --callgraph)

KEEP_OPTION=
KEEP_OPTION += --keep lcdFuncT_*
KEEP_OPTION += --keep *_BacklightInterfaceTable
KEEP_OPTION += --keep address_for_BIN_END

ifneq (, $(strip $(SUBBACKLIGHT)))
KEEP_OPTION += --keep *_SubBacklightInterfaceTable
endif

ifneq (, $(strip $(OFN)))
KEEP_OPTION += --keep *_OfnFuncTbl
endif

ifeq ($(filter __G_SENSOR_DRV__, $(PP_OPT_COMMON)), __G_SENSOR_DRV__)
ifneq (,$(strip $(GSENSOR)))
KEEP_OPTION += --keep *_GsensorFuncTbl
endif
endif

ifneq (,$(strip $(TOUCH_SCREEN_DRIVER_SELECT)))
KEEP_OPTION += --keep *_TscrFuncTbl
endif

ifneq (, $(strip $(PSENSOR)))
KEEP_OPTION += --keep *_PsensorFuncTbl
endif

ifneq (, $(strip $(BREATHLIGHT)))
KEEP_OPTION += --keep *_BreathlightInterfaceTable
endif

#
# The load address of second load region taken by arm is the end of first load region after "decompression"
# (it shoulde be "compression"). Therefore, arm takes wrong load region to do decompression of second load region.
# There are two ways to fixed above problem, 1) turn off rw data compression
# 2) now, we place each execution region to a dedicated load region. Place all of them to one load region.
#
ifeq ($(LINKER),RVCTV22_link)
ifeq ($(filter __BOOT_UNCOMPRESS__, $(PP_OPT_COMMON)),)
RW_DATA_COMPRESSION=--datacompressor off
endif
endif

#-------------------------------------------------------------------------------
# LDFLAGS: the options for linker
#-------------------------------------------------------------------------------

ifeq ($(LINKER),ADSV12_link)
LDFLAGS=-elf -noremove -info sizes -info unused -xref -list $(OUT)link.info
endif
ifeq ($(LINKER),RVCTV22_link)
ifeq ($(filter __I_SW__ ,$(PP_OPT_COMMON)),__I_SW__)
LDFLAGS=--elf --noremove --map --symbols --info sizes --info unused --xref --entry 0x0 --list $(OUT)link.info --symdefs symdefs.info
else
# Eric: Use RVCT linker functional link to save unused section
LDFLAGS=--elf --remove --map --symbols --info sizes --info unused --xref $(VERBOSE_OPTION) --entry 0x0 --list $(OUT)link.info --symdefs symdefs.info  $(KEEP_OPTION) $(FEEDBACK_OPTION) $(CALL_GRAPH_OPTION) $(RW_DATA_COMPRESSION) --diag_suppress 6312,6314,6329
endif
endif
ifeq ($(LINKER),AEONGCC_link)
#LDFLAGS=-EL -nostdlib -march=aeonR2f1 -Bstatic -Wl,--fatal-warnings -Wl,--gc-sections -nostartfiles -Wl,--cref
LDFLAGS=-EL -nostdlib -march=aeonR2 -Bstatic -Wl,--fatal-warnings -Wl,--gc-sections -nostartfiles -Wl,--cref -Wl,-Map,$(STEM).map -Wl,--start-group  -Wl,--end-group -lgcc
endif
ifeq ($(LINKER),ARMGCC_link)
ifeq (arm-linux-gnueabihf-gcc,$(COMPILER_EXECUTABLE))
ifeq (TRUE, $(strip $(WIFI_PORT)))
LDFLAGS=-Bstatic -Wl,--build-id=none -march=armv7-a -static-libgcc -Wl,--gc-sections -nostartfiles -Wl,--cref -Wl,-Map,$(STEM).map -lgcc -lc -lm -Wl,--whole-archive $(OUT)sensordriver.lib -Wl,--whole-archive $(OUT)vendor_RTC.lib -Wl,--whole-archive $(OUT)vendor_gsensor.lib -Wl,--whole-archive $(OUT)vendor_gps.lib -Wl,--whole-archive $(OUT)vendor_touchpanel.lib -Wl,--whole-archive $(OUT)core_system_net_cgi.lib -Wl,--whole-archive $(OUT)core_system_net_lib.lib -Wl,--whole-archive $(OUT)core_system_net_streaming_server.lib -Wl,--no-whole-archive
else
LDFLAGS=-Bstatic -Wl,--build-id=none -march=armv7-a -static-libgcc -Wl,--gc-sections -nostartfiles -Wl,--cref -Wl,-Map,$(STEM).map -lgcc -lc -lm -Wl,--whole-archive $(OUT)sensordriver.lib -Wl,--whole-archive $(OUT)vendor_RTC.lib -Wl,--whole-archive $(OUT)vendor_gsensor.lib -Wl,--whole-archive $(OUT)vendor_gps.lib -Wl,--whole-archive $(OUT)vendor_touchpanel.lib -Wl,--no-whole-archive
endif
else
ifeq (TRUE, $(strip $(WIFI_PORT)))
LDFLAGS=-Bstatic -Wl,--build-id=none -march=armv7-a -static-libgcc -Wl,--gc-sections -nostartfiles -Wl,--cref -Wl,-Map,$(STEM).map -lrdimon -lgcc -lc -lm -Wl,--whole-archive $(OUT)sensordriver.lib -Wl,--whole-archive $(OUT)vendor_RTC.lib -Wl,--whole-archive $(OUT)vendor_gsensor.lib -Wl,--whole-archive $(OUT)vendor_gps.lib -Wl,--whole-archive $(OUT)vendor_touchpanel.lib -Wl,--whole-archive $(OUT)core_system_net_cgi.lib -Wl,--whole-archive $(OUT)core_system_net_lib.lib -Wl,--whole-archive $(OUT)core_system_net_streaming_server.lib -Wl,--no-whole-archive
else
LDFLAGS=-Bstatic -Wl,--build-id=none -march=armv7-a -static-libgcc -Wl,--gc-sections -nostartfiles -Wl,--cref -Wl,-Map,$(STEM).map -lrdimon -lgcc -lc -lm -Wl,--whole-archive $(OUT)sensordriver.lib -Wl,--whole-archive $(OUT)vendor_RTC.lib -Wl,--whole-archive $(OUT)vendor_gsensor.lib -Wl,--whole-archive $(OUT)vendor_gps.lib -Wl,--whole-archive $(OUT)vendor_touchpanel.lib -Wl,--no-whole-archive
endif
endif
endif


#-------------------------------------------------------------------------------
# Folders in out, DPM, SLDLM, compression
#-------------------------------------------------------------------------------

STEM=$(OUT)$(PRODUCT)
LDRGN_BIN_DIR=$(OUT)LdRgnBin
LDRGN_CMPR_BIN_DIR=$(OUT)LdRgnBin_Cmpr
CMPR_BIN_DIR=$(OUT)CmprBin
CMPR_BIN_DIR_CMPR=$(OUT)CmprBin_Cmpr

ifeq ($(filter __EMMI_SLDPM__, $(PP_OPT_COMMON)), __EMMI_SLDPM__)
DPM_LIST += emmi_sldpm
endif

DICT_GEN_DIR=$(TNG)MsDictGen


SCATTER_STACK_LIB=$(PATH_cust_scatter)scatter_85xx_stack_lib.dsc
SCATTER_SYS_LIB=$(OUT)scatter_85xx_sys_lib.dsc
SCATTER_DRV_LIB=$(OUT)scatter_85xx_drv_lib.dsc
SCATTER_MDL_LIB=$(OUT)scatter_85xx_mdl_lib.dsc
SCATTER_3RD_LIB=$(OUT)scatter_85xx_3rd_lib.dsc
SCATTER_3RDLIB_LIB=$(OUT)scatter_85xx_3rdlib_lib.dsc
SCATTER_MMI_APP_LIB=$(OUT)scatter_85xx_mmi_app_lib.dsc

ALL_GROUP_SCATTER= $(SCATTER_SYS_LIB) $(SCATTER_DRV_LIB) $(SCATTER_MDL_LIB) $(SCATTER_3RD_LIB) $(SCATTER_3RDLIB_LIB) $(SCATTER_MMI_APP_LIB)

