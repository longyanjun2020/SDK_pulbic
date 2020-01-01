#************************************************************************
#Filename   : appl.mak
#Description: sub-makefile that includes the list of general tests and
#			  internal applications
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

# GUI test application supplied with Windows and Unix packages
ifeq ($(TARGET_OS), $(findstring $(TARGET_OS),$(NON_EMBEDDED_OS)))
PROJECTS += appl/3g324m/testapp/testapp.mak
endif

# Console test application supplied with Embedded packages
PROJECTS += appl/3g324m/endptest/endptest.mak

# PMT sample
PROJECTS += appl/3g324m/monitor/monitor.mak

# H.223 Split sample
ifeq ($(SPLIT), on)
PROJECTS += appl/3g324m/h223app/h223app.mak
endif

# We use this file to remove from customers the knowledge about our
# internal test applications.
