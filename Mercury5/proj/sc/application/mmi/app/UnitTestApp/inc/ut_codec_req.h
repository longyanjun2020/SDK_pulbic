#ifndef __UT_CODEC_REQ_H__
#define __UT_CODEC_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCodec_UT(void);
int   noCodec_UT(void);
void  releaseCodec_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CODEC_REQ_H__ */
