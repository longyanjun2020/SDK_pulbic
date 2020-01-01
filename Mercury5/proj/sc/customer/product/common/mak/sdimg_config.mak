#This file is the configuration of sd package.

#ifndef SDTYPE
#SDTYPE = dz_redownload
#endif

# unzip execution file path
UNZIP = $(TNG)cygwin/unzip.exe

# final sd image destination folder
#ifeq (dz_normal, $(strip $(SDTYPE)))
#SDIMGFOLDER = SDimgNormal
#else
#ifeq (dz_redownload, $(strip $(SDTYPE)))
#SDIMGFOLDER = SDimgReload
#else
#SDIMGFOLDER = SDimgDefault
#endif
#endif

# source folder of dz unzip image and sd image destination folder after MergeSD
SRCFOLDER = SDimgSrc
DSTFOLDER = SDimg
MERGESD = $(TOP)/sc/system/sddl/MergeSD.exe
MERGESDLOG = LogMergeSD.txt

# NAND packfat execution path
# NAND configurtion file path
# NAND Pre FAT folder path
ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)), __NAND__)
PACKFAT = ../Tools/PackFat/packfat.exe
NANDINFO_NNI = $(BUILD)$(PRODUCT)/$(SRCFOLDER)/NANDINFO_v2.nni
PARTITION_PIN = $(BUILD)$(PRODUCT)/$(SRCFOLDER)/PARTITION_v2.pni
#FATNORMAL = $(BUILD)$(PRODUCT)/fatNormal
#FATHIDDEN = $(BUILD)$(PRODUCT)/fatHidden
FATNORMAL =
FATHIDDEN =
endif

ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)),)
MAINDES_SRC  = $(TOP)/sc/system/sddl/MAIN0000_NOR.DES
else
MAINDES_SRC  = $(TOP)/sc/system/sddl/MAIN0000_NAND.DES
endif

#after option_msw853xb.mak, option_msw8556x.mak commit, this should be removed.
ifndef SDAPPRAM
SDAPPRAM = SDAPPRAM_MSW853xb.BIN
endif

SDAPPRAM_SRC = $(TOP)/sc/system/sddl/$(SDAPPRAM)
SDTARGET_SRC = $(TOP)/sc/system/sddl/SDTARGET_$(PRODUCT).BIN

LCD_CUS = $(OUT)/LT_LcdPack.cus