/* ut_touchshortcut_example.h */
#ifndef __UT_TOUCHSHORTCUT_EXAMPLE_H__
#define __UT_TOUCHSHORTCUT_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetTouchshortcut_Example(void);
s32   NumTouchshortcut_Example(void);
void  ReleaseTouchshortcut_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TOUCHSHORTCUT_EXAMPLE_H__ */


