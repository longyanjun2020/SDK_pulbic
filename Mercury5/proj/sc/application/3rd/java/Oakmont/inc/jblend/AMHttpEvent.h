/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMHttpEvent.h
 * HTTP/HTTPS Event Notification JBI
 */
#ifndef ___AM_HTTP_EVENT_H
#define ___AM_HTTP_EVENT_H

#include "JkTypes.h"
#include "JkTypesHttpEvent.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup HTTP_HTTPS_Event_Notification_JBI
 * @{
 */
/**
 *  Notifies an HTTP/HTTPS event to JBlend.
 * @param param
 *    Set the param parameter passed when the HTTP/HTTPS connection for which the event 
 *    occurred was created by #JkHttpOpen().
 * @param cause
 *    Set a value appropriate for the event.
 * @param option
 *    Event details.
 *    Set a value appropriate for the event.
 * @return
 *    JK_TRUE is returned if notification succeeded, or JK_FALSE if it failed.
 */
JKBool AmNotifyHttpEvent( JKSint32 param, JKSint32 cause, JKSint32 option );

/**
 * @} end of group
 */

#ifdef __cplusplus
}
#endif

#endif

