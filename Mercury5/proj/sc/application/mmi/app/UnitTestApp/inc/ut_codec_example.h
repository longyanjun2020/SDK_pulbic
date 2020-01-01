/* ut_codec_example.h */
#ifndef __UT_CODEC_EXAMPLE_H__
#define __UT_CODEC_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetCodec_Example(void);
int NumCodec_Example(void);
void ReleaseCodec_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif /*__UT_CODEC_EXAMPLE_H__ */