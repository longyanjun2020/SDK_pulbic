
TARGET=sdtarget

include $(CONFIG_MAK)

ifeq ($(filter __NAND__ ,$(PP_OPT_COMMON)), __NAND__)
FLASH_TYPE = nand
all:
	$(WARN) NAND SD DL is not support now
genlib:
	$(WARN) NAND SD DL is not support now
cus:
	$(WARN) NAND SD DL is not support now
else
ifneq ($(filter msw8556x, $(BB_CHIP_ID)),)
FLASH_TYPE = nor

all:
	$(WARN) build sdtarget
	rm -rf $(PATH_system)sdtarget/backlight/cust/src/
	rm -rf $(PATH_system)sdtarget/lcd/cust/src/
	$(MKDIR) $(PATH_system)sdtarget/backlight/cust/src
	$(MKDIR) $(PATH_system)sdtarget/lcd/cust/src
	$(COPY) $(OUT)/cust_backlight*.c $(PATH_system)sdtarget/backlight/cust/src/
	$(COPY) $(OUT)/cust_gpio_sddl*.c $(PATH_system)sdtarget/backlight/cust/src/
	$(COPY) $(OUT)/cust_lcd*.c $(PATH_system)sdtarget/lcd/cust/src/
	$(shell cd $(PATH_system)sdtarget/)
	$(WARN) Change directory to $(PATH_system)sdtarget
	$(MAKE) -C $(PATH_system)sdtarget/ -r -f Makefile TARGET=sdtarget CHIP=$(BB_CHIP_ID) FLASH=$(FLASH_TYPE) cleanall
	$(MAKE) -C $(PATH_system)sdtarget/ -r -f Makefile TARGET=sdtarget CHIP=$(BB_CHIP_ID) FLASH=$(FLASH_TYPE)
	$(COPY) $(PATH_system)sdtarget/SDTARGET_$(BB_CHIP_ID).BIN $(PATH_system)sddl/SDTARGET_$(PRODUCT).BIN
	
genlib:
	$(WARN) generate sdtarget lib
	rm -rf $(PATH_system)sdtarget/backlight/cust/src/
	rm -rf $(PATH_system)sdtarget/lcd/cust/src/
	$(MKDIR) $(PATH_system)sdtarget/backlight/cust/src
	$(MKDIR) $(PATH_system)sdtarget/lcd/cust/src
	$(COPY) $(OUT)/cust_backlight*.c $(PATH_system)sdtarget/backlight/cust/src/
	$(COPY) $(OUT)/cust_gpio_sddl*.c $(PATH_system)sdtarget/backlight/cust/src/
	$(COPY) $(OUT)/cust_lcd*.c $(PATH_system)sdtarget/lcd/cust/src/
	$(shell cd $(PATH_system)sdtarget/)
	$(WARN) Change directory to $(PATH_system)sdtarget
	$(MAKE) -C $(PATH_system)sdtarget/ -r -f Makefile TARGET=sdtarget CHIP=$(BB_CHIP_ID) FLASH=$(FLASH_TYPE) cleanall
	$(MAKE) -C $(PATH_system)sdtarget/ -r -f Makefile TARGET=sdtarget CHIP=$(BB_CHIP_ID) FLASH=$(FLASH_TYPE) genlib
	$(COPY) $(PATH_system)sdtarget/SDTARGET_$(BB_CHIP_ID).BIN $(PATH_system)sddl/SDTARGET_$(PRODUCT).BIN
	
cus:
	$(WARN) build sdtarget by from lib
	rm -rf $(PATH_system)sdtarget/backlight/cust/src/
	rm -rf $(PATH_system)sdtarget/lcd/cust/src/
	$(MKDIR) $(PATH_system)sdtarget/backlight/cust/src
	$(MKDIR) $(PATH_system)sdtarget/lcd/cust/src
	$(COPY) $(OUT)/cust_backlight*.c $(PATH_system)sdtarget/backlight/cust/src/
	$(COPY) $(OUT)/cust_gpio_sddl*.c $(PATH_system)sdtarget/backlight/cust/src/
	$(COPY) $(OUT)/cust_lcd*.c $(PATH_system)sdtarget/lcd/cust/src/
	$(shell cd $(PATH_system)sdtarget/)
	$(WARN) Change directory to $(PATH_system)sdtarget
	$(MAKE) -C $(PATH_system)sdtarget/ -r -f Makefile TARGET=sdtarget CHIP=$(BB_CHIP_ID) FLASH=$(FLASH_TYPE) cus_clean
	$(MAKE) -C $(PATH_system)sdtarget/ -r -f Makefile TARGET=sdtarget CHIP=$(BB_CHIP_ID) FLASH=$(FLASH_TYPE) cus
	$(COPY) $(PATH_system)sdtarget/SDTARGET_$(BB_CHIP_ID).BIN $(PATH_system)sddl/SDTARGET_$(PRODUCT).BIN       	
else
all:
	$(WARN) This Platform is not support SD DL
genlib:
	$(WARN) This Platform is not support SD DL
cus:
	$(WARN) This Platform is not support SD DL	
endif
endif	