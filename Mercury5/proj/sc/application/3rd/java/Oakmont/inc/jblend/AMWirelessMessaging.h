/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */
/* 
 * $Id: AMWirelessMessaging.h 28349 2009-04-15 02:10:31Z code.lin $
 */


/**
 * @file AMWirelessMessaging.h
 *  @if WMA20
 *  Wireless Messaging API SMS/CBS Communication JBI Header File
 *  @else
 *  Wireless Messaging Communication JBI Header File
 *  @endif
 */

/**
 *  @if WMA20
 *  @addtogroup WMA_SMS_JBI
 *  @else
 *  @addtogroup WMA_STD_JBI
 *  @endif
 * @{
 */
#ifndef __AM_WIRELESSMESSAGING_H__
#define __AM_WIRELESSMESSAGING_H__

#include "JKWirelessMessagingTypedef.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 *  Event type definitions
 */

/**
 * Message sending is complete.
 */
#define	AM_WMA_EVENT_MESSAGE_SENT       1

/**
 * Message sending timed out.
 */
#define	AM_WMA_EVENT_TIMEOUT  2

/**
 * A message arrived.
 */
#define	AM_WMA_EVENT_MESSAGE_ARRIVED  3

/**
 * An I/O error occurred.
 */
#define	AM_WMA_EVENT_IO_ERROR       4


/**
 *  @if WMA20
 *  Notifies JBlend of an event occurring on a connection used for SMS/CBS.
 *  @else
 *  Notifies JBlend of an event occurring on a Wireless Messaging API connection.
 *  @endif
 *   @param connectionHandle
 *     Handle of the connection on which the event occurred
 *     Designate the handle value issued by #JkWmaOpen().
 *   @param event
 *     The event for notification. Designate one of the following.
 *     <dl>
 *      <dt>#AM_WMA_EVENT_MESSAGE_SENT</dt>
 *       <dd>Message sending is complete.</dd>      
 *      <dt>#AM_WMA_EVENT_TIMEOUT</dt>
 *       <dd>Message sending timed out.</dd>      
 *      <dt>#AM_WMA_EVENT_MESSAGE_ARRIVED</dt>
 *       <dd>An inbound message arrived.</dd>  
 *      <dt>#AM_WMA_EVENT_IO_ERROR</dt>
 *       <dd>An I/O error occurred.</dd>      
 *     </dl>
 *   @param option
 *     Optional parameters for each notification event.<br>
 *
 * Use this function to notify JBlend of the result of send processing 
 * started by #JkWmaSendMessage() and of incoming message arrival.
 *
 * When the JVM is in suspended state, JBlend cannot accept an event 
 * by this function.
 * To notify JBlend of the events that occur in that state, 
 * the native system must call this function after JVM resumes. 
 *
 */
void AMWmaEventPost( JKHandle connectionHandle, int event, JKSint32 option);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__AM_WIRELESSMESSAGING_H__ */

/** @} end of group */

