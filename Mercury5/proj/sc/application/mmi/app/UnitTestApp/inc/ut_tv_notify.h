/* ut_tv_notify.h */
#ifndef __UT_TV_NOTIFY_H__
#define __UT_TV_NOTIFY_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTvNotifyUT(void);
int   noTvNotifyUT(void);
void  releaseTvNotifyUT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TV_NOTIFY_H__ */
