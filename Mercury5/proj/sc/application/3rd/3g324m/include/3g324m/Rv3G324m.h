/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV3G324M_H_
#define _RV3G324M_H_

/************************************************************************
 * Here for backward compatability...
 * Applications that use the definitions written below should add
 * RV_3G324M_VERSION_DEFINITIONS with the version value to their compiler
 * definitions when compiling the 3G-324M Protocol Toolkit.
 *
 * Valid values for RV_3G324M_VERSION_DEFINITIONS are:
 * 100
 *
 * We preserve this part for backward compatibility.
 * Application writers are encouraged to remove this definition and use
 * the new definitions. The new definitions insure that the stack doesn't
 * declare anything that might be declared by the operating system or
 * other libraries.
 ************************************************************************/
#if !defined(RV_3G324M_VERSION_DEFINITIONS)

#define RV_3G324M_VERSION_DEFINITIONS 300

#endif



#include "h245.h"
#include "msg.h"
#include "ci.h"
#include "Rv3G324mGeneral.h"
#include "cmH245GeneralDefs.h"
#include "cmctrl.h"
#include "Rv3G324mCall.h"
#include "Rv3G324mCallTransport.h"
#include "Rv3G324mHa.h"
#include "rvh324mwatchdog.h"
#include "Rv3G324mCallH223Glue.h"


#if (RV_H245_SUPPORT_H223_PARAMS != 1)
#error H.245 package must support H.223!
#endif


#endif /* _RV3G324M_H_ */
