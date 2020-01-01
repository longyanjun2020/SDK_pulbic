#************************************************************************
#Filename   : cflags.mak
#Description: General flags that can be used by most projects
#             compilations
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

ifeq ($(NOLOG), on)
USER_CFLAGS += -DRV_CFLAG_NOLOG
endif

ifeq ($(NOTHREADS), on)
USER_CFLAGS += -DRV_CFLAG_NOTHREADS
endif

ifeq ($(IPV6), on)
BINARIES_DIR := $(BINARIES_DIR)Ipv6
USER_CFLAGS += -DRV_CFLAG_IPV6
endif

ifeq ($(DNS), on)
BINARIES_DIR := $(BINARIES_DIR)Dns
USER_CFLAGS += -DRV_CFLAG_DNS
endif

ifeq ($(TLS), on)
BINARIES_DIR := $(BINARIES_DIR)Tls
USER_CFLAGS += -DRV_CFLAG_TLS
endif

ifeq ($(POLL), on)
USER_CFLAGS += -DRV_CFLAG_POLL
endif

ifeq ($(DEVPOLL), on)
USER_CFLAGS += -DRV_CFLAG_DEVPOLL
endif
