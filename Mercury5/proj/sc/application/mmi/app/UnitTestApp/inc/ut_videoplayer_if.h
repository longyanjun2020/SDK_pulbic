/* ut_videoplayer_if.h */
#ifndef __UT_VIDEOPLAYER_IF_H__
#define __UT_VIDEOPLAYER_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getVideoplayer_If_UT(void);
int   noVideoplayer_If_UT(void);
void  releaseVideoplayer_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_VIDEOPLAYER_IF_H__ */
