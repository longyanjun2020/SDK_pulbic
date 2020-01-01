/* ut_camcoder_example.h */

#ifndef __UT_CAMCODER_EXAMPLE_H__
#define __UT_CAMCODER_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetCamcoder_Example(void);
int   NumCamcoder_Example(void);
void  ReleaseCamcoder_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAMCODER_EXAMPLE_H__ */