/*
*
* @file ut_camcoder_notify.h
*
* Class Id:
*
* @version $Id$*/

#ifndef __UT_CAMCODER_NOTIFY_H__
#define __UT_CAMCODER_NOTIFY_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCamcoderNotifyUT(void);
int   noCamcoderNotifyUT(void);
void  releaseCamcoderNotifyUT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAMCODER_NOTIFY_H__ */
