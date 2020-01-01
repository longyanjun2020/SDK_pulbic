/* ut_audioplayer_if.h */
#ifndef __UT_AUDIOPLAYER_IF_H__
#define __UT_AUDIOPLAYER_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAudioplayer_If_UT(void);
int   noAudioplayer_If_UT(void);
void  releaseAudioplayer_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_AUDIOPLAYER_IF_H__ */
