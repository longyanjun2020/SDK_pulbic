#************************************************************************
#Filename   : project.mak
#Description: sub-makefile that must be included by all project makefiles
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

# This file must be included at the end of every project makefile

# Derived info
LIBNAME := $(LIB_PREFIX)$(PROJECT_NAME)$(LIB_EXTENSION)
SHAREDLIBNAME := $(LIB_PREFIX)$(PROJECT_NAME)$(SHARED_LIB_EXTENSION)
EXENAME := $(PROJECT_NAME)$(EXECUTE_EXTENSION)
DIRLIST := $(PROJECT_PATH) $(MODULES:%=$(PROJECT_PATH)/%)
SOURCE := $(foreach dir,$(DIRLIST),$(wildcard $(dir)/*.c))
CPPSRC := $(foreach dir,$(DIRLIST),$(wildcard $(dir)/*.cpp))
INCLUDES := $(foreach dir,$(DIRLIST),$(wildcard $(dir)/*.h))
ifeq ($(BUILD_SHARED_LIB), yes)
OBJLIST := $(foreach src,$(SOURCE),$(PROJECT_OBJ_DIR)/$(src:.c=$(SHARED_OBJ_EXTENSION)))
CPPOBJS := $(foreach src,$(CPPSRC),$(PROJECT_OBJ_DIR)/$(src:.cpp=$(SHARED_OBJ_EXTENSION)))
else
OBJLIST := $(foreach src,$(SOURCE),$(PROJECT_OBJ_DIR)/$(src:.c=$(OBJ_EXTENSION)))
CPPOBJS := $(foreach src,$(CPPSRC),$(PROJECT_OBJ_DIR)/$(src:.cpp=$(OBJ_EXTENSION)))
endif
OBJLIST += $(CPPOBJS)

ifeq ($(OS_BUILD_EXECUTABLE), no)
BUILD_EXECUTABLE := no
endif
ifeq ($(BUILD_EXECUTABLE), yes)
TARGETNAME := $(PROJECT_BIN_DIR)/$(EXENAME)
# Create special variable to remember linking information
$(TARGETNAME)_EXE_OBJ_LIST := $(OBJLIST)
$(TARGETNAME)_EXE_LIBS_NEEDED := $(EXE_LIBS_NEEDED)
ifeq ($(BUILD_EXECUTABLE_WITH_TK), yes)
ifneq ($(TK_TCL_WAS_ADDED), yes)
LIB_DIRS += $(LIBS_TK_DIRS)
LIBS_LIST += $(LIBS_TK_LIST)
TK_TCL_WAS_ADDED := yes
endif
endif
else
ifeq ($(BUILD_SHARED_LIB), yes)
TARGETNAME := $(PROJECT_LIB_DIR)/$(SHAREDLIBNAME)
$(TARGETNAME)_EXE_LIBS_NEEDED := $(EXE_LIBS_NEEDED)
else
TARGETNAME := $(PROJECT_LIB_DIR)/$(LIBNAME)
endif
endif

# Add to master lists
SOURCE_DIRS += $(DIRLIST)
OBJECT_LIST += $(OBJLIST)
CPP_OBJECTS += $(CPPOBJS)
ifeq ($(PROJECT_NAME), $(MAKECMDGOALS))
PRJ_OBJECT_LIST := $(OBJLIST)
endif
OTHER_TARGET_LIST +=
ifeq ($(BUILD_EXECUTABLE), yes)
EXE_TARGET_LIST += $(TARGETNAME)
DEMO_INSTALL_LIST += $(EXENAME)
else
LIBS_TARGET_LIST += $(TARGETNAME)
INCLUDE_INSTALL_LIST += $(INCLUDES)
endif
NAMED_TARGET_LIST += $(PROJECT_NAME)

# Handle "per-project" exported files
ifneq ($(INCLUDE_PROJ_FILES), )
INCLUDE_TARGETS_LIST += $(foreach h,$(INCLUDE_PROJ_FILES),$(APPL_INCLUDE_DIR)/$(INCLUDE_SUBDIR)/$(notdir $(h)))
endif

# Create the base object dependencies specific to this project directory
$(OBJLIST): $(PROJECT_MAKE)

# Make sure the project's name is a valid target
.PHONY: $(PROJECT_NAME)
$(PROJECT_NAME): $(TARGETNAME)
	@echo Target $@ made.

# Create the target dependencies specific to this project directory
$(TARGETNAME): $(OBJLIST) $(addprefix $(PROJECT_LIB_DIR)/, $(EXE_LIBS_NEEDED:%=$(LIB_PREFIX)%$(LIB_EXTENSION))) $(PROJECT_MAKE)
