/*
*
* @file ut_camera_notify.h
*
* Class Id:
*
* @version $Id$*/

#ifndef __UT_CAMERA_NOTIFY_H__
#define __UT_CAMERA_NOTIFY_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCameraNotifyUT(void);
int   noCameraNotifyUT(void);
void  releaseCameraNotifyUT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAMERA_NOTIFY_H__ */
