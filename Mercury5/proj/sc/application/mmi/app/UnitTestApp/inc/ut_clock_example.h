/* ut_clock_example.h */
#ifndef __UT_CLOCK_EXAMPLE_H__
#define __UT_CLOCK_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetCLOCK_Example(void);
int   NumCLOCK_Example(void);
void  ReleaseCLOCK_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CLOCK_EXAMPLE_H__ */
