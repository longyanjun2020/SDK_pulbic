#************************************************************************
#Filename   : environment.mak
#Description: sub-makefile that checks default.mak for errors
#************************************************************************
#      Copyright (c) 2003 RADVISION Inc. and RADVISION Ltd.
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

# This file must be included from the main Makefile

# List of supported built types.
LEGAL_BUILD_TYPES:= debug release

# List of support Host OS's
LEGAL_HOST_OS:= rtk solaris win32 linux tru64 hpux unixware solarispc freebsd mac netbsd

# List of supported Compiler Tools
LEGAL_COMPILER_TOOLS:= aeon gnu sun diab ghs ads msvc compaqc cadul hpuxc metrowerks icc

# List of supported Target OS's
LEGAL_TARGET_OS:= rtk solaris vxworks psos win32 linux ose nucleus tru64 hpux unixware solarispc symbian mopi integrity freebsd mac netbsd

# List of supported cpu modes
LEGAL_TARGET_CPU_ENDIAN:= little big

# List of supported bit models
LEGAL_TARGET_CPU_BITS:= 32 64


# Actual checks start here
##########################

# Check to make sure required parameters are set to legal values
ifndef BUILD_TYPE
$(error BUILD_TYPE must be set in default.mak)
endif
ifneq ($(BUILD_TYPE), $(findstring $(BUILD_TYPE),$(LEGAL_BUILD_TYPES)))
$(error "$(findstring $(BUILD_TYPE),$(LEGAL_BUILD_TYPES))" The BUILD_TYPE "$(BUILD_TYPE)" is not supported. Legal values are: $(LEGAL_BUILD_TYPES))
endif

ifndef HOST_OS
$(error HOST_OS must be set in default.mak)
endif
ifneq ($(HOST_OS), $(findstring $(HOST_OS),$(LEGAL_HOST_OS)))
$(error The HOST_OS "$(HOST_OS)" is not supported. Legal values are: $(LEGAL_HOST_OS))
endif

ifndef COMPILER_TOOL
$(error COMPILER_TOOL must be set in default.mak)
endif
ifneq ($(COMPILER_TOOL), $(findstring $(COMPILER_TOOL),$(LEGAL_COMPILER_TOOLS)))
$(error The Compiler Tool "$(COMPILER_TOOL)" is not supported. Legal values are: $(LEGAL_COMPILER_TOOLS))
endif

ifndef TARGET_OS
$(error TARGET_OS must be set in default.mak)
endif
ifneq ($(TARGET_OS), $(findstring $(TARGET_OS),$(LEGAL_TARGET_OS)))
$(error The TARGET_OS "$(TARGET_OS)" is not supported. Legal values are: $(LEGAL_TARGET_OS))
endif

ifndef TARGET_CPU_ENDIAN
$(error TARGET_CPU_ENDIAN must be set in default.mak)
endif
ifneq ($(TARGET_CPU_ENDIAN), $(findstring $(TARGET_CPU_ENDIAN),$(LEGAL_TARGET_CPU_ENDIAN)))
$(error The TARGET_CPU_ENDIAN "$(TARGET_CPU_ENDIAN)" is not supported. Legal values are: $(LEGAL_TARGET_CPU_ENDIAN))
endif

ifndef TARGET_CPU_BITS
$(error TARGET_CPU_BITS must be set in default.mak)
endif
ifneq ($(TARGET_CPU_BITS), $(findstring $(TARGET_CPU_BITS),$(LEGAL_TARGET_CPU_BITS)))
$(error The TARGET_CPU_BITS "$(TARGET_CPU_BITS)" is not supported. Legal values are: $(LEGAL_TARGET_CPU_BITS))
endif

# If goal is install, make sure INSTALL_ROOT is set
ifeq (install, $(findstring install,$(MAKECMDGOALS)))
ifndef INSTALL_ROOT
$(error INSTALL_ROOT must be set in default.mak)
endif
endif


# Set up rvbuildconfig lines for Architecture options. Map default.mak
# options to definitions rvarchdefs.h. Do this here since there's no
# architecture specific makefiles.
ifeq ($(TARGET_CPU_ENDIAN), little)
TARGET_CPU_ENDIAN_LINE := RV_ARCH_LITTLE_ENDIAN
else
TARGET_CPU_ENDIAN_LINE := RV_ARCH_BIG_ENDIAN
endif

ifeq ($(TARGET_CPU_BITS), 64)
TARGET_CPU_BITS_LINE := RV_ARCH_BITS_64
else
TARGET_CPU_BITS_LINE := RV_ARCH_BITS_32
endif
