#ifndef __UT_AUDIOPLAYER_REQ_H__
#define __UT_AUDIOPLAYER_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAudioplayer_UT(void);
int   noAudioplayer_UT(void);
void  releaseAudioplayer_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIOPLAYER_REQ_H__ */
