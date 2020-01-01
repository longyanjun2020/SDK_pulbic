#************************************************************************
#Filename   : endptest.mak
#Description: 3G-324M test application sub-makefile
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
PROJECT_NAME := 3g324mendptest

# Project Makefile - relative path and name of this file.
# Must match path and name in main makefile.
PROJECT_MAKE := appl/3g324m/endptest/endptest.mak

# Project Path = relative path from main makefile to top of source
# directory tree for this project
PROJECT_PATH := appl/3g324m/endptest

# Module sub-directories - relative path from this makefile
MODULES :=

# Build executable application for this project - yes/no
BUILD_EXECUTABLE := yes
BUILD_EXECUTABLE_WITH_TK := no

# Libraries needed for linking executable (exclude lib prefix and extension)
EXE_LIBS_NEEDED := 3g324m h245 asn1 rvcommon

# This file must be included at the end of every project makefile
include $(PROJECT_MAKE_PATH)/project.mak

