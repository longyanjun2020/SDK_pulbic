#
# 
#
#.SILENT:

ifndef CHIP
CHIP = b3
endif
export CHIP

ifndef TARGET
TARGET = bootrom
endif
export TARGET

ifndef PURPOSE
PURPOSE = download
endif
export PURPOSE

ifeq ($(TARGET), sdtarget)
ifndef FLASH
FLASH = nor
endif
export FLASH
endif

#VENDOR: MSTAR, GAX
ifndef VENDOR
VENDOR = MSTAR
endif
export VENDOR

ifeq ($(TARGET), sdtarget)
MSTARLIB = lib_$(CHIP)
export MSTARLIB
OUT_LIB_DIR = out_$(CHIP)/sdtarget
else
MSTARLIB = MStarLib
export MSTARLIB
OUT_LIB_DIR = out_$(CHIP)/wintarget
endif

all:
	@echo "building $(CHIP) $(TARGET) $(VENDOR)"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	@echo "USE VENDOR=GAX if your are building wintarget for GAX since GAX wintarget has different compile option"
	make -f Makefile_$(CHIP)

cleanall: clean
	rm -rf dep_$(CHIP) out_$(CHIP)

clean:
	make -f Makefile_$(CHIP) clean

dep:
	make -f Makefile_$(CHIP) dep

genlib:
	make -f Makefile_$(CHIP)
	@if [ -e $(MSTARLIB) ];then\
		echo $(MSTARLIB) folder exists;\
	else\
		mkdir $(MSTARLIB);\
		echo Make $(MSTARLIB) folder;\
		echo;\
	fi;
	cp $(OUT_LIB_DIR)/*.a $(MSTARLIB)/
	cp $(OUT_LIB_DIR)/*.lib $(MSTARLIB)/
	cp $(OUT_LIB_DIR)/emi_init.o $(MSTARLIB)/
ifeq ($(TARGET), sdtarget)
	cp $(OUT_LIB_DIR)/veneer_sd.o $(MSTARLIB)/
	cp $(OUT_LIB_DIR)/importsym_sd.def $(MSTARLIB)/
else
	cp $(OUT_LIB_DIR)/veneer.o $(MSTARLIB)/
ifeq ($(CHIP), b5)
	cp $(OUT_LIB_DIR)/importsym_b5.def $(MSTARLIB)/
else
ifeq ($(CHIP), b9)
	cp $(OUT_LIB_DIR)/importsym_b9.def $(MSTARLIB)/
else
	cp $(OUT_LIB_DIR)/importsym.def $(MSTARLIB)/
endif
endif
endif
	cp $(OUT_LIB_DIR)/main.o $(MSTARLIB)/
	cp $(OUT_LIB_DIR)/arm.inc $(MSTARLIB)/
	cp $(OUT_LIB_DIR)/Inc.mak $(MSTARLIB)/

cus:
	make -f Makefile_$(CHIP)_cus

cus_clean:
	make -f Makefile_$(CHIP)_cus clean
ifeq ($(TARGET), sdtarget)
	rm -rf dep_$(CHIP) out_$(CHIP)
endif
ifeq ($(TARGET), sdtarget)
source_clean:
	echo source clean
	@find . -type f \( -name '*.c' \
	                  ! -name 'mcp_drv.c' \
	                  ! -name 'hal_aux*.c' \
	                  ! -name 'hal_disp*.c' \
	                  ! -name 'hal_gpd*.c' \
	                  ! -name '*_io_chip*.c' \
	                  ! -name 'drv_lcd*.c' \
	                  ! -name 'dwl_version.c' \
	                  ! -name 'drv_backlight*.c' \
	                  ! -name 'cust_gpio_*.c' \
	                  ! -name 'cust_backlight*.c' \
	                  ! -name 'cust_lcd*.c' \) -print0 | xargs -0 rm -f
endif