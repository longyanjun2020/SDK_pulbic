/***********************************************************************
        Copyright (c) 2003 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV_MSG_H
#define _RV_MSG_H

#include "rvtypes.h"
#include "rverror.h"

#ifdef __cplusplus
extern "C" {
#endif


#if (RV_LOGMASK != RV_LOGLEVEL_NONE)

/* Open the log configuration, parse it, and start the listeners */
RVAPI void RVCALLCONV msOpen(void);

/* Close log listeners */
RVAPI void RVCALLCONV msClose(void);

/* Add module to debug printing list */
RVAPI int RVCALLCONV msAdd(IN const RvChar *moduleName);

/* Delete module from debug printing list */
RVAPI int RVCALLCONV msDelete(IN const RvChar *moduleName);

/* Delete all modules from debug printing list */
RVAPI int RVCALLCONV msDeleteAll(void);

/* Set the configuration file name */
RVAPI void RVCALLCONV msFile(IN const RvChar *name);

/* Get the debug level */
RVAPI int RVCALLCONV msGetDebugLevel(void);

/* Set the log output file name */
RVAPI void RVCALLCONV msLogFile(IN const RvChar *name);

/* Get the current log output file name */
RVAPI RvStatus RVCALLCONV msGetLogFilename(IN RvUint32 nameLength, OUT RvChar *name);

/* Set the debug level */
RVAPI int RVCALLCONV msSetDebugLevel(IN int debugLevel);

/* Set function to be called when logging messages are being written */
RVAPI void RVCALLCONV msSetStackNotify(void (*sN)(IN char *line,...));

/* Add sink */
RVAPI int RVCALLCONV msSinkAdd(IN const RvChar *sinkName);

/* Delete sink */
RVAPI int RVCALLCONV msSinkDelete(IN const RvChar *sinkName);


#else

#define msOpen()
#define msClose()
#define msAdd(_moduleName) RV_ERROR_NOTSUPPORTED
#define msDelete(_moduleName) RV_ERROR_NOTSUPPORTED
#define msDeleteAll() RV_ERROR_NOTSUPPORTED
#define msFile(_name)
#define msGetDebugLevel() 0
#define msLogFile(_name)
#define msGetLogFilename(_nameLength, _name) RV_ERROR_NOTSUPPORTED
#define msSetDebugLevel(_debugLevel) 0
#define msSetStackNotify(_sN)
#define msSinkAdd(_sinkName) RV_ERROR_NOTSUPPORTED
#define msSinkDelete(_sinkName) RV_ERROR_NOTSUPPORTED


#endif  /* RV_LOGMASK */

#ifdef __cplusplus
}
#endif

#endif  /* _RV_MSG_H */
