/* ut_fmradio_example.h */
#ifndef __UT_FMRADIO_EXAMPLE_H__
#define __UT_FMRADIO_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetFMRadio_Example(void);
s32  NumFMRadio_Example(void);
void  ReleaseFMRadio_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_FMRADIO_EXAMPLE_H__ */
