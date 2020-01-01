//==============================================================================
//
//  File        : mmpf_event.h
//  Description : Header file of event handler
//  Author      : Alterman Lin
//  Revision    : 1.0
//
//==============================================================================
#include "includes_fw.h"
#if 0//(HANDLE_EVENT_BY_TASK == 1)

#ifndef _MMPF_EVENT_H_
#define _MMPF_EVENT_H_

/** @addtogroup MMPF_EVENT
@{
*/

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#define EVENT_MSGQ_DEPTH        (20)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef void (MMPF_Event_Callback) (void);

typedef struct _MMPF_EVENT_MSG {
    MMPF_OS_SEMID       semID;  // semaphore for blocking event. 0 for non-blocking
    MMPF_Event_Callback *cb;    // callback function for the event
} MMPF_EVENT_MSG;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR MMPF_EVENT_PostEvent(MMP_BOOL bBlocking, MMPF_OS_SEMID semID, MMPF_Event_Callback cb);

/// @}

#endif //_MMPF_EVENT_H_
#endif
