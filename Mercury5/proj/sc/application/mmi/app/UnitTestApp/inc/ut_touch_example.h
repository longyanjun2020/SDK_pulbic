/* ut_touch_example.h */
#ifndef __UT_TOUCH_EXAMPLE_H__
#define __UT_TOUCH_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetTouch_Example(void);
s32   NumTouch_Example(void);
void  ReleaseTouch_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TOUCH_EXAMPLE_H__ */

