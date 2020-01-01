#************************************************************************
#Filename   : 3g324m.mak
#Description: 3G-324M library sub-makefile
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

PROCESS		= lib

# Project Name - must be unique within build tree. Actual target names will
# be based on this name (for example, on Solaris, the resulting library
# will be called libNAME.a and the excutable, if any, will be NAME.
PROJECT_NAME := 3g324m

# Project Makefile - relative path and name of this file.
# Must match path and name in main makefile.
PROJECT_MAKE := 3g324m/3g324m.mak

# Project Path = relative path from main makefile to top of source
# directory tree for this project
PROJECT_PATH := 3g324m

# Module sub-directories - relative path from this makefile
MODULES := asn_objects callmanager h223 h223/algo middle stackmanager

# Build executable application for this project - yes/no
BUILD_EXECUTABLE := no

# Libraries needed for linking executable (exclude lib prefix and extension)
EXE_LIBS_NEEDED :=

# List of files that should be exported
INCLUDE_FILES_LIST += 3g324m/callmanager/Rv3G324mCall.h 3g324m/callmanager/Rv3G324mCallTypes.h 3g324m/callmanager/Rv3G324mCallTransport.h
INCLUDE_FILES_LIST += 3g324m/callmanager/Rv3G324mHa.h 3g324m/callmanager/Rv3G324mCallH223Glue.h
INCLUDE_FILES_LIST += 3g324m/stackmanager/Rv3G324mGeneral.h 3g324m/stackmanager/Rv3G324m.h
INCLUDE_FILES_LIST += 3g324m/middle/rvh324mwatchdog.h
#../../avp/stackmanager/Rv3G324m.h

# This file must be included at the end of every project makefile
include $(PROJECT_MAKE_PATH)/project.mak
