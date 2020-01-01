#************************************************************************
#Filename   : common.mak
#Description: common core library sub-makefile
#************************************************************************
#      Copyright (c) 2001,2002 RADVISION Inc. and RADVISION Ltd.
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

# Project Name - must be unique within build tree. Actual target names will
# be based on this name (for example, on Solaris, the resulting library
# will be called libNAME.a and the excutable, if any, will be NAME.
PROJECT_NAME := rvcommon

# Project Makefile - relative path and name of this file.
# Must match path and name in main makefile.
PROJECT_MAKE := common/common.mak

# Project Path = relative path from main makefile to top of source
# directory tree for this project
PROJECT_PATH := common

# Construct the list of adapters
ADAPTERS := $(ADAPTERS_$(TARGET_OS)_$(TARGET_OS_VERSION))
ifeq ($(ADAPTERS), )
ADAPTERS := $(ADAPTERS_$(TARGET_OS))
endif

# Module sub-directories - relative path from this makefile
MODULES := ccore cutils ceutils cbase config ccore/memdrivers ccore/netdrivers \
           config/arch config/os config/tool adapters $(ADAPTERS:%=adapters/%) ares \
	   security ldap sctp

# Build executable application for this project - yes/no
BUILD_EXECUTABLE := no

# Build shared library - yes/no
BUILD_SHARED_LIB := no

# Libraries needed for linking executable (exclude lib prefix and extension)
EXE_LIBS_NEEDED :=

# List of files that should be exported
INCLUDE_FILES_LIST += common/ceutils/rvlist.h   \
                      common/ceutils/rvalloc.h  \
                      common/ceutils/rvvector.h \
                      common/cutils/rvtypes.h   \
                      common/cutils/rverror.h   \
                      common/cutils/rv64bits.h  \
                      common/config/rvconfig.h  \
                      common/config/rvdependencies.h \
                      common/config/rvusrconfig.h \
                      common/config/rvinterfacesdefs.h \
                      common/config/rvcflags.h \
                      common/config/rvbuildconfig.h \
                      common/config/arch/rvarchconfig.h \
                      common/config/arch/rvarchdefs.h \
                      common/config/os/rvosconfig.h \
                      common/config/os/rvosdefs.h \
                      common/config/os/rv$(TARGET_OS).h \
                      common/config/tool/rvtoolconfig.h \
                      common/config/tool/rvtooldefs.h \
                      common/ccore/rvccoreconfig.h \
                      common/ccore/rvccoredefs.h \
                      common/ccore/rvassert.h \
                      common/ccore/rvccore.h \
                      common/ccore/netdrivers/rvnettypes.h \
                      common/config/tool/rv$(COMPILER_TOOL).h 
#		      common/ipsec/rvimsipsecpublic.h

# This file must be included at the end of every project makefile
include $(PROJECT_MAKE_PATH)/project.mak
