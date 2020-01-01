#************************************************************************
#Filename   : 3g324mtoolkit.mak
#Description: sub-makefile with the list of projects required for the
#             3G-323M toolkit.
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

NON_EMBEDDED_OS := solaris linux hpux tru64 unixware
# H.32x Related (ASN.1 and H.245 support)
PROJECTS += asn1/asn1.mak h245/h245.mak

# 3G-324M Related
PROJECTS += 3g324m/3g324m.mak

# 3G-324M Addons
PROJECTS += h323addons/gef/gef.mak
PROJECTS += h323addons/h245AutoCaps/h245AutoCaps.mak
PROJECTS += 3g324maddons/pmt/pmt.mak
ifeq ($(SPLIT), on)
PROJECTS += 3g324maddons/h223split/h223split.mak 3g324m/3g324mSplit.mak
endif




# The following is a list of makefiles
# used internally for testing purposes.
#######################################

# 3G-324M Applications
-include appl/3g324m/appl.mak
-include samples/3g324m/samples.mak
-include testers/3g324m/testers.mak
