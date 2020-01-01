/* ut_audioenv_req.h */
#ifndef __UT_Audioenv_REQ_H__
#define __UT_Audioenv_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAudioenv_UT(void);
int   noAudioenv_UT(void);
void  releaseAudioenv_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_Audioenv_REQ_H__ */
