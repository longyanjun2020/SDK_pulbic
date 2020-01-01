/* ut_mplayer_req.h */
#ifndef __UT_MPLAYER_H__
#define __UT_MPLAYER_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMPlayer_UT(void);
int   noMPlayer_UT(void);
void  releaseMPlayer_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MPLAYER_H__ */
