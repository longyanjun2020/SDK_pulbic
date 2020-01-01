/***********************************************************************
Filename   : rvloginternal.h
Description: log handling
             These definitions shouldn't be used outside of the
             address module directly
************************************************************************
        Copyright (c) 2001 RADVISION Inc. and RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Inc. and RADVISION Ltd.. No part of this document may be
reproduced in any form whatsoever without written prior approval by
RADVISION Inc. or RADVISION Ltd..

RADVISION Inc. and RADVISION Ltd. reserve the right to revise this
publication and make changes without obligation to notify any person of
such revisions or changes.
***********************************************************************/

#ifndef RV_LOG_INTERNAL_H
#define RV_LOG_INTERNAL_H


#if defined(__cplusplus)
extern "C" {
#endif


/********************************************************************


            type definitions written in this file should not
            be accessed directly from outside the core. They
            may vary greatly between core versions!


 ********************************************************************/


/* Maximum number of sources a log manager can handle */
#define RV_LOG_MAX_SOURCES RvInt32Const(256)


/************************************************************************
 * RvLogSourceInternal
 * Information of a single source of messages of a log manager.
 * We have this defined here and not used externally, since we want to
 * be able to make operations globally on these elements.
 ************************************************************************/
struct RvLogSourceInternal
{
    RvLogMgr*           logMgr;           /* Log manager this source is in */
    RvChar              name[12];         /* Name of source we're dealing with */
    RvUint32            timesConstructed; /* Reference count of constructions */
    RvLogMessageType    messageTypes;     /* Mask of messages that should be logged */
};


/************************************************************************
 * RvLogMgrInternal
 * Log manager object information.
 ************************************************************************/
struct RvLogMgrInternal
{
    RvInt32             level;        /* Log level. 0 none, 1 masks, 2 all */
    RvInt32             numSources;   /* Number of allocated sources (including destructed ones !) */
    RvLogMessageType    defaultMask;  /* Default mask to use for new sources */
    struct RvLogSourceInternal source[RV_LOG_MAX_SOURCES]; /* Sources of this log manager */
    RvLogSource         sema4Source;
    RvLogSource         mutexSource;
    RvLogSource         lockSource;
    RvLogSource         memorySource;
    RvLogSource         threadSource;
    RvLogSource         socketSource;
    RvLogSource         prangeSource;
    RvLogSource         selectSource;
    RvLogSource         queueSource;
    RvLogSource         timerSource;
	RvLogSource         clockSource;
    RvLogSource         tstampSource;
    RvLogSource         tmSource;
    RvLogSource         hostSource;
	RvLogSource         TLSSource;
    RvLogSource         dnsSource;
    RvLogSource         sctpSource;
#if (RV_IMS_IPSEC_ENABLED == RV_YES)    
    RvLogSource         imsIpsecSource;
#endif

    RvInt32             numListeners; /* Number of registered listeners */
    RvLogPrintCb        listener[RV_LOG_MAX_LISTENERS]; /* Listeners of this log manager */
    void*               listenerUserData[RV_LOG_MAX_LISTENERS]; /* User data used when calling a listener function */
	RvInt               selectUsageCnt;
	RvBool              isDestructed;
    RvInt               statInfo[RV_LOG_NUM_MESSAGE_TYPES];  /* Statistics information */
    RvBool              printThreadId;

    RvLock              lock;         /* Non-recoursive lock for protecting the database */
};



/************************************************************************
 * RvLogRecordInternal
 * Log information associated with a log message. This struct is given
 * to the printing function on each log message.
 ************************************************************************/
struct RvLogRecordInternal
{
    RvBool              printThreadId; /* Indicates whether the next item is really
                                          a thread name or a thread id */
    RvChar*             threadName;    /* Name of thread where the message occured (can be "Unknown") */
    RvLogSource*        source;        /* Source of log message */
    RvInt               messageType;   /* Type of message */
    const RvChar*       text;
};


typedef enum {
	RV_LOG_DESTRUCT_REASON_STACK = 1,
	RV_LOG_DESTRUCT_REASON_SELECT
} RvLogDestructReason;

/********************************************************************************************
 * RvLogSelectUsageDec - Decrements select usage counter of the log manager
 *
 * INPUT   : logMgr - Log manager to destruct
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RVCALLCONV RvLogSelectUsageDec(RvLogMgr *logMgr);

/********************************************************************************************
 * RvLogSelectUsageInc - Increment select usage counter of the log manager
 *
 * INPUT   : logMgr - Log manager to destruct
 * OUTPUT  : None
 * RETURN  : RV_OK on success, other on failure
 */
RvStatus RVCALLCONV RvLogSelectUsageInc(RvLogMgr *logMgr);

#if defined(__cplusplus)
}
#endif

#endif /* RV_LOG_INTERNAL_H */
