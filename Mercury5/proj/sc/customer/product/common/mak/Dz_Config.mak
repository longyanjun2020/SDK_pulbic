#This file is the configuration of DZ package.
#There are two major DZ package parameter: DZ_REDOWNLOAD_PARAMETER and DZ_NORMAL_PARAMETER

include $(PATH_common_mak)driver_resource.mak


ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)), __NAND__)
#########################################################
# this is for NAND
#########################################################

# Flah Type
DZ_FLASH = -flash NAND

BIN_LIST = $(PRODUCT)$(BINPOSTFIX).prt

# WT is wintarget file
WT = $(WINTARGET)
NAND_CONFIG = NANDINFO_v2.nni PARTITION_v2.pni nand_partition.ini

#########################################################
# end of NAND configuration
#########################################################

else

##########################################################
# this is for NOR
#########################################################

# Flah Type
DZ_FLASH = -flash NOR

BIN_LIST = $(PRODUCT).wpb
ifeq (TRUE, $(strip $(ONBOARD_USER_STORAGE_SUPPORT)))
BIN_LIST += custo_nor_*.wpb
endif
ifeq (TRUE, $(strip $(HIDDEN_PARTITION_SUPPORT)))
BIN_LIST += hidden_nor_*.fat
endif

# wintarget file
WT = $(WINTARGET)

#########################################################
# end of NOR configuration
#########################################################
endif

DZ_BB_CPU = -cpu $(DZ_BB_CPU_NAME)

DZ_SET = setting.miu

# BIN File
DZ_BIN = $(addprefix -b $(OUT), $(BIN_LIST))

# all E2P files
E2P_ALL_LIST = $(wildcard $(OUT)*.e2p)

# default calibration E2P files
E2P_DEFAULT_CALIBRATION = $(wildcard $(OUT)default_calibration*.e2p)

# all factory E2p files
E2P_FACTORY_LIST = $(wildcard $(OUT)*factory*.e2p)

E2P_NORMAL_LIST     = $(E2P_ALL_LIST)
E2P_FILTER_LIST     = $(E2P_FACTORY_LIST) $(E2P_DEFAULT_CALIBRATION)
E2P_REDOWNLOAD_LIST = $(filter-out $(E2P_FILTER_LIST), $(E2P_NORMAL_LIST))

DZ_E2P_NORMAL       = $(addprefix -e , $(E2P_NORMAL_LIST))
DZ_E2P_REDOWNLOAD   = $(addprefix -e , $(E2P_REDOWNLOAD_LIST))

# CUS Files
ifeq ($(filter DEFAULT, $(LANGUAGE_PACK_LIST)), DEFAULT)
CUS_XRG = TP_DefaultLangPack0000.CUS
else
FIRST_CUS="$(firstword $(LANGUAGE_PACK_LIST))"
CUS_XRG = TP_Default$(FIRST_CUS).CUS
endif

ifeq ($(filter __MULTIPLE_SENSOR_TABLE_DETECTION__ ,$(PP_OPT_COMMON)),__MULTIPLE_SENSOR_TABLE_DETECTION__)
ifeq ($(strip $(FIRST_SENSOR_CUS)),)
CUS_SENSOR_FIRST =
else
CUS_SENSOR_FIRST = $(FIRST_SENSOR_CUS_PREFIX)$(FIRST_SENSOR_CUS).cus
endif
CUS_SENSOR = $(SENSOR_CUS_FILE)
endif

ifeq ($(filter __CUS_LCM_TABLE_DRV__ ,$(PP_OPT_COMMON)),__CUS_LCM_TABLE_DRV__)
CUS_LCM = $(LCD_CUS_FILE)
endif

ifeq ($(filter __CUS_DISPLAY_TABLE_DRV__ ,$(PP_OPT_COMMON)),__CUS_DISPLAY_TABLE_DRV__)
CUS_DISPTbl = $(DISPTBL_CUS_FILE)
endif

ifeq ($(filter __EMMI_SLDPM__, $(PP_OPT_COMMON)), __EMMI_SLDPM__)
CUS_EMMI_SLDPM = DP_PAGE.CUS
endif

ifeq ($(call FILE_EXISTED, $(OUT)DLM_bin.CUS), TRUE)
CUS_DLM += DLM_bin.CUS
endif

ifeq ($(call FILE_EXISTED, $(OUT)SLDLM_bin.CUS), TRUE)
CUS_DLM += SLDLM_bin.CUS
endif

CUS_LIST = $(CUS_XRG) $(CUS_SENSOR_FIRST) $(CUS_SENSOR) $(CUS_LCM) $(CUS_DISPTbl) $(CUS_EMMI_SLDPM) $(CUS_DLM)
DZ_CUS = $(addprefix -c $(OUT), $(CUS_LIST))

# add files
ifeq ($(filter __TARGET_DSP_PATCH_SOLO_BIN__ ,$(PP_OPT_COMMON)),__TARGET_DSP_PATCH_SOLO_BIN__)
ADD_FILE_LIST = $(WT) DlSequence.ini dsp.pat $(NAND_CONFIG)
ifeq ($(MERGE_TO_BIN),MergeAll.dll)
ADD_FILE_LIST += $(MERGE_TO_BIN)
endif
DZ_ADD_LIST = $(addprefix -checkadd $(OUT), $(ADD_FILE_LIST))
ADD_FILE_NOT_CHECK_LIST = Config.ini $(BOOTLOADER) $(BOOTSTRAP) $(DZ_SET)
DZ_ADD_NOT_CHECK_LIST = $(addprefix -add $(OUT), $(ADD_FILE_NOT_CHECK_LIST))
else
ADD_FILE_LIST = $(WT) DlSequence.ini $(NAND_CONFIG)
ifeq ($(MERGE_TO_BIN),MergeAll.dll)
ADD_FILE_LIST += $(MERGE_TO_BIN)
endif
DZ_ADD_LIST = $(addprefix -checkadd $(OUT), $(ADD_FILE_LIST))
ADD_FILE_NOT_CHECK_LIST = Config.ini dsp.pat $(BOOTLOADER) $(BOOTSTRAP) $(DZ_SET)
DZ_ADD_NOT_CHECK_LIST = $(addprefix -add $(OUT), $(ADD_FILE_NOT_CHECK_LIST))
endif

ifneq ($(filter __NAND__ ,$(PP_OPT_COMMON)), __NAND__)
ifeq ($(filter MCP_CONFIG_TABLE ,$(PP_OPT_COMMON)), MCP_CONFIG_TABLE)
ifeq ($(MERGE_TO_BIN),)
ADD_FILE_LIST += MergeAll.dll
endif
ADD_FILE_LIST += MemSettings.prm
endif
endif

ifdef BINPOSTFIX
# extra added for NVRAM files
DBB_LIST := tdd fdd
# NRO file
DZ_ADD_NOT_CHECK_LIST += $(if $(wildcard $(OUT)*.nro), $(addprefix -add , $(wildcard $(OUT)*.nro)))
ifeq ($(filter __UPGRADE_NVRAM_ENHANCED__ ,$(PP_OPT_COMMON)), __UPGRADE_NVRAM_ENHANCED__)
# NRW file, automatically extract the wanted file by parsing BINPOSTFIX variable
DZ_NRW_FILE := $(addprefix $(OUT), \
                 $(foreach dbb,$(DBB_LIST), \
                   $(if $(findstring -$(dbb), $(BINPOSTFIX)), nvram_rw_$(CUST_NVRAM_CFG).nrw)))
DZ_ADD_NOT_CHECK_LIST += $(if $(wildcard $(DZ_NRW_FILE)), $(addprefix -add , $(wildcard $(DZ_NRW_FILE))))
# Temporarily added for merger files
MERGER_LIST := merge.ini NvramMerge.exe merge.dll nvram.i merge.val
DZ_ADD_NOT_CHECK_LIST += $(addprefix -add $(OUT), $(MERGER_LIST))
endif
endif

# calibration table
CALTBL_LIST := app_calibration_table_$(strip $(CALTBL)).c arp_calibration_table_$(strip $(CALTBL)).c
DZ_ADD_NOT_CHECK_LIST += $(addprefix -add $(OUT), $(CALTBL_LIST))

# Bootlogo parameter
ifeq ($(filter __BOOTUP_LOGO_BY_E2P__ ,$(PP_OPT_COMMON)), __BOOTUP_LOGO_BY_E2P__)
LOGO_LIST := boot_logo_param.h
DZ_ADD_NOT_CHECK_LIST += $(addprefix -add $(OUT)/../, $(LOGO_LIST))
endif

# Lock Bin
DZ_LOCK_BIN = -i $(WT)

# Chip type
DZ_CHIP = -chiptype $(DZ_CHIP_TYPE)

# Compatible chip
ifeq ($(call FIND_COMPILER_OPTION, __COMPATIBLE_CHIP_SUPPORT__), TRUE)
COMMA = ,
DZ_COMPATIBLE = -compatible $(subst +,$(COMMA),$(DZ_COMPATIBLE_CHIP))
endif

# Others
DZ_OTHERS = -eo -ec -r --keep -eb
DZ_ERASE_ALL = -ew

# Output File
DZ_VERSION_STRING = $(VERSION_CUS)
ifeq ($(strip $(BINPOSTFIX)),)
DZ_OUTPUT_NORMAL = -o $(OUT)$(DZ_VERSION_STRING)dz
DZ_OUTPUT_REDOWNLOAD = -o $(OUT)$(DZ_VERSION_STRING)redownload.dz
else
DZ_OUTPUT_NORMAL = -o $(OUT)$(DZ_VERSION_STRING)$(BINPOSTFIX).dz
DZ_OUTPUT_REDOWNLOAD = -o $(OUT)$(DZ_VERSION_STRING)redownload.$(BINPOSTFIX).dz
endif
DZ_VERSION = -f $(DZ_VERSION_STRING)

COMMON_PARAM = $(DZ_BIN) $(DZ_CUS) $(DZ_LOCK_BIN) $(DZ_OTHERS) $(DZ_VERSION) $(DZ_BB_CPU) $(DZ_ADD_LIST) $(DZ_ADD_NOT_CHECK_LIST) $(DZ_FLASH) $(DZ_CHIP) $(DZ_COMPATIBLE)

# DZ packages
DZ_REDOWNLOAD_PARAMETER = $(COMMON_PARAM) $(DZ_E2P_REDOWNLOAD) $(DZ_OUTPUT_REDOWNLOAD)
DZ_NORMAL_PARAMETER     = $(COMMON_PARAM) $(DZ_ERASE_ALL) $(DZ_E2P_NORMAL) $(DZ_OUTPUT_NORMAL)
