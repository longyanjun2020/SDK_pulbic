#************************************************************************
#Filename   : linux.mak
#Description: linux definitions
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

# Assumes default include paths for the compilers are set properly

# Set legal values for TARGET_OS_VERSION
LEGAL_TARGET_OS_VERSION := rtk RADV RTK_RADV_1.0 redhat-6.0 redhat-6.1 redhat-6.2 redhat-7.0 redhat-7.1 redhat-7.2 redhat-7.3 redhat-9 redhat-WS redhat-AS  redhat-ES redhat-Server MontaVista_2.1 MontaVista_3.0 MontaVista_3.1 MontaVista_4.0 MontaVista_5.0 uclinux-2.4 redhat-AS SUSE_8 SUSE_9 SUSE_10

# Set up rvbuildconfig.h definitions for TARGET_OS and TARGET_OS_VERSION
# to map to rvosdefs.h
TARGET_OS_LINE := RV_OS_TYPE_RTK


#
#  RTK
#
ifeq ($(TARGET_OS_VERSION), RTK_RADV_1.0)
TARGET_OS_VERSION_LINE := RTK_RADV_1_0
endif
ifeq ($(TARGET_OS_VERSION), RADV)
TARGET_OS_VERSION_LINE := RADV
endif
ifeq ($(TARGET_OS_VERSION), rtk)
TARGET_OS_VERSION_LINE := rtk
endif
#
#  Red Hat
#
ifeq ($(TARGET_OS_VERSION), redhat-6.0)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_6_0
endif
ifeq ($(TARGET_OS_VERSION), redhat-6.1)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_6_1
endif
ifeq ($(TARGET_OS_VERSION), redhat-6.2)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_6_2
endif
ifeq ($(TARGET_OS_VERSION), redhat-7.0)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_7_0
endif
ifeq ($(TARGET_OS_VERSION), redhat-7.1)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_7_1
endif
ifeq ($(TARGET_OS_VERSION), redhat-7.2)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_7_2
endif
ifeq ($(TARGET_OS_VERSION), redhat-7.3)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_7_3
endif
ifeq ($(TARGET_OS_VERSION), redhat-9)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_9
endif
ifeq ($(TARGET_OS_VERSION), redhat-WS)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_WS
endif
ifeq ($(TARGET_OS_VERSION), redhat-AS)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_AS
endif
ifeq ($(TARGET_OS_VERSION), redhat-Server)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_AS
endif
ifeq ($(TARGET_OS_VERSION), redhat-ES)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_REDHAT_ES
endif

#
#  MontaVista
#
ifeq ($(TARGET_OS_VERSION), MontaVista_2.1)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_MVISTA_2_1
endif
ifeq ($(TARGET_OS_VERSION), MontaVista_3.0)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_MVISTA_3_0
endif
ifeq ($(TARGET_OS_VERSION), MontaVista_3.1)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_MVISTA_3_1
endif
ifeq ($(TARGET_OS_VERSION), MontaVista_4.0)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_MVISTA_4_0
endif
ifeq ($(TARGET_OS_VERSION), MontaVista_5.0)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_MVISTA_5_0
endif

#
#  uClinux
#
ifeq ($(TARGET_OS_VERSION), uclinux-2.4)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_UCLINUX_2_4
endif
#
#  SUSE
#
ifeq ($(TARGET_OS_VERSION), SUSE_8)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_SUSE_8
endif
ifeq ($(TARGET_OS_VERSION), SUSE_9)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_SUSE_9
endif
ifeq ($(TARGET_OS_VERSION), SUSE_10)
TARGET_OS_VERSION_LINE := RV_OS_LINUX_SUSE_10
endif

ifneq ($(OPENSSL_INC),)
$(warning OPENSSL_INC is set to $(OPENSSL_INC) )
INCLUDE_DIRS += $(OPENSSL_INC)
endif

ifneq ($(OPENSSL_LIB),)
$(warning OPENSSL_LIB is set to $(OPENSSL_LIB) )
LIB_DIRS += $(OPENSSL_LIB)
endif


# Add required info to master lists
# MAKE_LIST - List any OS dependent makefiles (inclduing this one)
# INCLUDE_DIRS - List any OS dependent include directories in search order
# LIBS_LIST - List any OS dependent libraries needed to link executables
# LIBS_TK_DIRS - List any OS dependent include directories in search order for use of Tcl-Tk
# LIBS_TK_LIST - List any OS dependent libraries needed to link executables that use Tcl-Tk
MAKE_LIST +=
#
#  Red Hat
#
ifneq ($(findstring redhat,$(TARGET_OS_VERSION)), )

INCLUDE_DIRS += /usr/include/kaffe

LIB_DIRS += /usr/local/kaffe/jre/lib/i386 /usr/local/lib
LIBS_LIST += nsl dl rt
TARGET_CPU_RES := $(shell uname -i)
ifeq ($(TARGET_CPU_RES),x86_64)
LIBS_TK_DIRS += /usr/X11R6/lib64 /usr/X11R6 /usr/X/lib64 /usr/X11/lib64 /usr/local/X11R5/lib64
else
LIBS_TK_DIRS += /usr/X11R6/lib /usr/X11R6 /usr/X/lib /usr/X11/lib /usr/local/X11R5/lib
endif
LIBS_TK_LIST = $(BASIC_TCL_TK_LIBS) Xmu Xt Xext
endif
#
#  MontaVista
#
ifneq ($(findstring MontaVista,$(TARGET_OS_VERSION)), )
LIBS_LIST += pthread rt nsl dl ssl crypto
LIBS_TK_DIRS +=
LIBS_TK_LIST += tcl8.3 tk8.3 X11 m
endif
#
#  uClinux
#
ifneq ($(findstring uclinux,$(TARGET_OS_VERSION)), )
INCLUDE_DIRS += /usr/local/m68k-elf/include
LIBS_LIST += pthread c
endif
#
#  SUSE
#
ifneq ($(findstring SUSE,$(TARGET_OS_VERSION)), )
INCLUDE_DIRS += /usr/include/kaffe
LIB_DIRS += /usr/local/kaffe/jre/lib/i386
LIBS_LIST += nsl rt dl resolv
LIBS_TK_DIRS += /usr/X11R6/lib
LIBS_TK_LIST += tcl8.3 tk8.3
endif

ifneq ($(JAVA_HOME),)
INCLUDE_DIRS += $(JAVA_HOME)/include $(JAVA_HOME)/include/linux  
endif

ifeq ($(TLS), on)
LIBS_LIST += ssl crypto
endif

ifneq ($(call flagset,SCTP),)
LIBS_LIST += sctp
endif

ifeq ($(LDAP), on)
LIBS_LIST += ldap lber
endif

# List the required adapters
ifneq ($(findstring $(LINUX_TYPE),UCLINUX), )
ADAPTERS_$(TARGET_OS) := rtklock rtkmutex rtkthread rtktstamp
#ADAPTERS_$(TARGET_OS) := pmutex posix utstamp ptstamp
else
ADAPTERS_$(TARGET_OS) := rtklock rtkmutex rtkthread rtktstamp
#ADAPTERS_$(TARGET_OS) := pmutex posix ptstamp pclock
endif
SHARED_LIBS_LIST += $(LIBS_LIST) c


# Indicate if executable targets can be built for this OS via these makefiles
# Set to yes if they can be built, no if they can't.
OS_BUILD_EXECUTABLE := no

# Extension to target name for executable (ie .exe for Windows)
EXECUTE_EXTENSION :=
