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

#ifndef _H324M_LOG_H_
#define _H324M_LOG_H_


#include "rvlog.h"
#include "cmH245GeneralDefs.h"


#ifdef __cplusplus
extern "C" {
#endif



#if (!(RV_LOGMASK & RV_LOGLEVEL_ENTER))
#define H324mLogAPIEnter(_args)
#define H324mLogCBEnter(_args)
#define _H324mLogAPIEnter NULL
#define _H324mLogCBEnter NULL
#else
#define H324mLogAPIEnter(_args) _H324mLogAPIEnter _args
#define H324mLogCBEnter(_args) _H324mLogCBEnter _args
void _H324mLogAPIEnter(HAPP hApp,const char*line,...);
void _H324mLogCBEnter(HAPP hApp,const char*line,...);
#endif

#if (!(RV_LOGMASK & RV_LOGLEVEL_LEAVE))
#define H324mLogAPIExit(_args)
#define H324mLogCBExit(_args)
#define _H324mLogAPIExit NULL
#define _H324mLogCBExit NULL
#else
#define H324mLogAPIExit(_args) _H324mLogAPIExit _args
#define H324mLogCBExit(_args) _H324mLogCBExit _args
void _H324mLogAPIExit(HAPP hApp,const char*line,...);
void _H324mLogCBExit(HAPP hApp,const char*line,...);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _H324M_LOG_H_ */

