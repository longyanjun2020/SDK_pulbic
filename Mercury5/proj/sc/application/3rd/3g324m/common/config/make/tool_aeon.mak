#************************************************************************
#Filename   : gnu.mak
#Description: GNU compiler tool definitions
#************************************************************************
#        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
#************************************************************************
#NOTICE:
#This document contains information that is confidential and proprietary
#to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
#reproduced in any form whatsoever without written prior approval by
#RADVISION Inc. or RADVISION Ltd..
#
#RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
#publication and make changes without obligation to notify any person of
#such revisions or changes.
#************************************************************************

# Set supported TARGET_OS's for these compiler tools
LEGAL_COMPILER_OS := rtk solaris vxworks linux unixware symbian freebsd mac netbsd

# Set legal values for COMPILER_TOOL_VERSION
LEGAL_COMPILER_TOOL_VERSION := cyg-2.7 2.9 3.0 3.2 3.3 3.4 4.1 4.2 4.3

# Set up rvbuildconfig.h definitions for COMPILER_TOOL and COMPILER_TOOL_VERSION
# to map to rvtooldefs.h
COMPILER_TOOL_LINE := RV_TOOL_TYPE_AEON
ifeq ($(COMPILER_TOOL_VERSION), cyg-2.7)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_CYG_2_7
endif
ifeq ($(COMPILER_TOOL_VERSION), 2.9)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_2_9
endif
ifeq ($(COMPILER_TOOL_VERSION), 3.0)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_3_0
endif
ifeq ($(COMPILER_TOOL_VERSION), 3.2)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_3_2
endif
ifeq ($(COMPILER_TOOL_VERSION), 3.3)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_3_3
endif
ifeq ($(COMPILER_TOOL_VERSION), 3.4)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_3_4
endif
ifeq ($(COMPILER_TOOL_VERSION), 4.1)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_4_1
endif
ifeq ($(COMPILER_TOOL_VERSION), 4.2)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_4_2
endif


ifdef RELAX_CHECKS

ISLEGAL := $(findstring $(COMPILER_TOOL_VERSION), $(LEGAL_COMPILER_TOOL_VERSION))

ifeq ($(ISLEGAL),)

$(warning "**** GCC-$(COMPILER_TOOL_VERSION) isnt supported officially ****")

LEGAL_COMPILER_TOOL_VERSION += $(COMPILER_TOOL_VERSION)
COMPILER_TOOL_VERSION_LINE := RV_TOOL_GNU_$(shell echo $(COMPILER_TOOL_VERSION) | sed "s/\./_/")

endif

endif


RV_TOOL_USTRING := "GNU-$(COMPILER_TOOL_VERSION)"


# Add required info to master lists
# MAKE_LIST - List any OS dependent makefiles (inclduing this one)
# INCLUDE_DIRS - List any OS dependent include directories in search order
# LIBS_LIST - List any OS dependent libraries needed to link executables
# MAKE_LIST +=

#MAKEDEP=$(BIN)makedepend
#ARM_CC   = $(CCACHE) aeon-gcc -pipe
#ARM_AS   = $(CCACHE) aeon-gcc -pipe -xassembler-with-cpp
#ARM_AR   = aeon-ar
#ARM_ELF  = aeon-objdump
#ARM_LINK = aeon-gcc
#ARM_OBJDUMP = aeon-objdump
#ARM_OBJCOPY = aeon-objcopy
#ARM_RANLIB = aeon-ranlib


# Compiler setup - GNU defaults for all targets
CC := $(CCACHE) aeon-elf-gcc -pipe
#aeon-elf-gcc   $(ARM_CC)
CFLAGS += -Wall -W -DRV_TOOL_USTRING=$(RV_TOOL_USTRING) -Winline
SHARED_LIB_C_FLAG := -fPIC
# Options required to produce shared libraries
# -shared produces a shared object, should be used with the same flags
#  that where used to generate code (SHARED_LIB_CFLAG)
# --export-dynamic
#     When creating a dynamically linked executable, add all symbols to
#     the dynamic symbol table.  The dynamic symbol table is the set of
#     symbols which are visible from dynamic objects at run time.

SHARED_LINK_FLAGS := $(SHARED_LIB_C_FLAG) -Wl,--export-dynamic  -shared 
INCLUDE_FLAG := -I
C_DEBUGFLAG := -g
C_OPTFLAG := -O2
COMPILE_ONLY_FLAG := -c
OBJ_EXTENSION := .o
SHARED_OBJ_EXTENSION := .shared_o
CC_OBJ_OUTPUT = -o $@
AR := aeon-elf-ar
ARFLAGS := -rc
LIB_EXTENSION := .lib
SHARED_LIB_EXTENSION := .so
LIB_PREFIX := lib
LIB_OUTPUT = $@
LIBS_FLAG := -l
LIBS_DIRFLAG:= -L

ifneq ($(call flagset,FIPS),)

LINK := env FIPSLD_CC=gcc $(OPENSSL_BIN)/fipsld

else

LINK := aeon-elf-gcc

endif

LDFLAGS +=
LD_DEBUGFLAG := $(C_DEBUGFLAG)
DEPEND_EXTENSION:= .d

# Currently, we're not compliant with strict aliasing rules of C99, so
# just disable applying these rules. GCC 2.7 doesn't support this option
# at all, so under this compiler dont't add this flag.
ifneq ($(COMPILER_TOOL_VERSION),cyg-2.7)
CFLAGS += -fno-strict-aliasing
endif

# Check for gprof support
ifeq ($(PROF), on)
CFLAGS += -pg
LDFLAGS += -pg
endif

# Compiler setup - GNU for VxWorks specifics
ifeq ($(TARGET_OS), vxworks)
CC := cc$(TARGET_CPU_FAMILY)
AR := ar$(TARGET_CPU_FAMILY)
LINK := cc$(TARGET_CPU_FAMILY)
ifeq ($(TARGET_OS_VERSION), 2.0)
# Only Tornado 2.0 should use this flag
CFLAGS += -nostdinc
endif
ifeq ($(TARGET_CPU_FAMILY), ppc)
# "-mcpu=xxx" is required for PPC only
CFLAGS += -fno-builtin -mcpu=$(TARGET_CPU_ID) -mlongcall -DCPU=$(TARGET_CPU_HEADERS) -D_GNU_TOOL
else
CFLAGS += -fno-builtin -DCPU=$(TARGET_CPU_HEADERS) -D_GNU_TOOL
endif
LIBS_LIST += 
# Following are flags enabling tornado to download the outputs to the target.
# they will affirm the creation of a single object file, instead of archive.
LDFLAGS += -nostdlib -Wl,-i -Wl,-X 
ifeq ($(TARGET_CPU_FAMILY), simpc)
LDFLAGS += -Wl,--force-stabs-reloc
endif
LIB_EXTENSION := .a
endif


ifeq ($(TARGET_OS), rtk)
CFLAGS += \
	-Wall\
	-Wno-packed\
	-Wcast-align\
	-ggdb\
	-O2\
	-fomit-frame-pointer\
	-EL\
	-ffunction-sections\
	-fdata-sections\
	-fshort-wchar\
	-march=aeonR2\
	-mredzone-size=4\
	-mno-sibcall\
	-mlong-calls\
	-mstruct-size-boundary=1

CFLAGS += \
	-D__VER_INFO__="$(VERSION)" \
	-D__VER_INFO_MMP__="$(M2_VER)" \
	-D__VER_INFO_CUS__="$(VERSION_CUS)" \
	-D__CUST_ID__="$(CUST_ID)" \
	-D__PRODUCT_ID__="$(PRODUCT_ID)" \
	-D__LAN_ID__="$(LAN_ID)" \
	-D__SW_MAJ_VER__="$(SW_MAJ_VER)" \
	-D__SW_MIN_VER__="$(SW_MIN_VER)"
endif

	
# Compiler setup - GNU for Solaris specifics
ifeq ($(TARGET_OS), solaris)
CFLAGS += -D_REENTRANT -D_POSIX_C_SOURCE=199506L -D__EXTENSIONS__ -DBSD_COMP
C_OPTFLAG := -O3 -fno-schedule-insns
SHARED_LINK_FLAGS := $(SHARED_LIB_C_FLAG) -G 
endif

# Compiler setup - GNU for Linux specifics
ifeq ($(TARGET_OS), linux)
ifneq ($(findstring redhat,$(TARGET_OS_VERSION)), )
CFLAGS += -pthread -D_GNU_SOURCE
LDFLAGS += -pthread
endif
ifneq ($(findstring redhat,$(TARGET_OS_VERSION)), )
CFLAGS += -pthread -D_GNU_SOURCE
LDFLAGS += -pthread
endif
ifneq ($(findstring SUSE,$(TARGET_OS_VERSION)), )
CFLAGS += -pthread -D_GNU_SOURCE
LDFLAGS += -pthread
endif
ifneq ($(findstring MontaVista,$(TARGET_OS_VERSION)), )
CC := $(TARGET_CPU_FAMILY)-gcc
AR := $(TARGET_CPU_FAMILY)-ar
LINK := $(TARGET_CPU_FAMILY)-gcc
CFLAGS += -pthread -D_GNU_SOURCE
LDFLAGS += -pthread
endif
ifneq ($(findstring uclinux,$(TARGET_OS_VERSION)), )
CC := $(TARGET_CPU_FAMILY)-gcc
AR := $(TARGET_CPU_FAMILY)-ar
LINK := $(TARGET_CPU_FAMILY)-gcc
CFLAGS += -m$(TARGET_CPU_HEADERS) -D_GNU_SOURCE
LDFLAGS += -m$(TARGET_CPU_HEADERS) -Wl,-elf2flt
endif
endif

# Compiler setup - GNU for FreeBSD specifics
ifeq ($(TARGET_OS), freebsd)
CFLAGS += -pthread -D_GNU_SOURCE
LDFLAGS += -pthread
endif

# Compiler setup - GNU for NetBSD specifics
ifeq ($(TARGET_OS), netbsd)
CFLAGS += -pthread -D_GNU_SOURCE
LDFLAGS += -pthread
endif


# Compiler setup - GNU for UnixWare specifics
ifeq ($(TARGET_OS), unixware)
LDFLAGS += -pthread
endif

# Compiler setup - GNU for Symbian specifics
ifeq ($(TARGET_OS), symbian)
ifeq ($(CSL_ARM_TOOLCHAIN),)
$(error Environment variable CSL_ARM_TOOLCHAIN must be set to the CSL Arm Toolchain installation folder)
endif
CFLAGS += -Wno-unknown-pragmas  -fexceptions -march=armv5t -mapcs -pipe -nostdinc 
CFLAGS += -msoft-float -DNDEBUG -D_UNICODE -D__GCCE__  -D__SYMBIAN32__ -D__GCCE__ -D__EPOC32__ -D__MARM__ 
CFLAGS += -D__EABI__ -D__MARM_ARMV5__ -D_DEBUG -DRVCORE_EXPORTS -D__SUPPORT_CPP_EXCEPTIONS__ -D__MARM_ARMV5__
CFLAGS += -D__PRODUCT_INCLUDE__="$(SYMBIAN_ROOT)/include/variant/Symbian_OS_v$(TARGET_OS_VERSION).hrh" 
CFLAGS += -include $(SYMBIAN_ROOT)/INCLUDE/GCCE/GCCE.h
C_SPECIFIC_FLAGS = -x c
CPP_SPECIFIC_FLAGS = -Wno-ctor-dtor-privacy -x c++ 
INCLUDE_DIRS += $(CSL_ARM_TOOLCHAIN)/lib/gcc/arm-none-symbianelf/3.4.3/include
AR := arm-none-symbianelf-ar
LIB_EXTENSION := .lib
CC := arm-none-symbianelf-g++
endif

# Check for insure++ support
ifeq ($(INSURE), on)
CC := insure
LINK := insure
endif

#ifeq ($(TERM),cygwin)
ifeq ($(findstring CYGWIN,$(OS_NAME)), CYGWIN)
MAKECYGPATH := gawk -f build/makedepend.awk rvSplit=yes | $(cygpath) -f - | gawk -f build/makedepend.awk |
endif

# Define full .d file generation command since they vary so much. The
# target will be the dependency file and the first dependency will be
# the .c file. Keep this at the end of the file for OS specifics.
# Notes: 
#  1. the equal sign (=) is used as a delimiter for sed's substitute command
#  2. sed is used to add dependency file itself as additional target to the rule
#     Advanced versions of gnu CPP support -MT option that can be used instead.
#  3. Additional CPP flags:
#     -M - output a rule suitable for 'make' describing the dependencies of the main source file
#     -P - inhibit generation of linemarkers in the output from the preprocessor 
#       (otherwise it confuses following sed command)
#
# add -I/cygdrive/c/Program\ Files to workaround windows native path
MAKEDEPEND = set -e; $(CC) -P -I/cygdrive/c/Program\ Files -c $(CFLAGS) -M $(CPP_SPECIFIC_FLAGS) $< | $(MAKECYGPATH) \
		sed '1s=^=$@ $(PROJECT_OBJ_DIR)/$(*D)/=' > $@;\
		[ -s $@ ] || rm -f $@

#MAKEDEPEND = set -e; $(CC) $(CFLAGS) $(CPP_SPECIFIC_FLAGS) $< | $(MAKECYGPATH) \
#		sed '1s=^=$@ $(PROJECT_OBJ_DIR)/$(*D)/=' > $@;\
#		[ -s $@ ] || rm -f $@
		
ifeq ($(nodepend), on)
MAKEDEPEND = touch $@
endif

# Note -MT option specifies alternate target for dependency rule,
#  so -MT $@ adds .d file as the first target and -MT $(@:.d=.o) adds .o
#  file as the second target

  

