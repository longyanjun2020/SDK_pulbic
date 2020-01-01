ifeq "$(OSTYPE)" "Win32"
OSTYPE=Win32
else
OS:=$(shell uname)
ifeq "$(OS)" "Linux"
OSTYPE = linux
else
OSTYPE = $(shell echo $$OSTYPE)
endif
endif
TNG:=$(TOP)./tng/
#PRODUCT was written by Perl, don't change it
PRODUCT=316d_32_128_msw
COMPILER_EXECUTABLE=arm-none-eabi-gcc
COMPILER_VERSION=ARMGCC
COMPILER_ARM=ARMGCC_arm
COMPILER_THUMB=ARMGCC_thumb
LINKER=ARMGCC_link
export FILTER=debug
COMMON=$(TOP)sc/customer/product/common/mak/
MAK=$(TOP)/mak/
EXISTED_LIBS=$(LIB_$(QUICK)_SET:%=$(OUT)%.lib)
EXISTED_DUO_LIBS=$(LIB_$(QUICK)_SET:%=$(OUT_DUP)%_2.axf)
EXISTED_LIBS_FILE=$(LIB_$(QUICK)_SET:%=$(LIBS_DIR_FOR_QUICK)%.lib)
#GLOBAL_HEADER must be defined before including the following two makefiles
#"GLOBAL_HEADER=TRUE" to enable global header file feature
GLOBAL_HEADER=FALSE
include $(TNG)config.mak
include $(TNG)compil.mak
PROFILE=QCIF
P4_ACC=full
