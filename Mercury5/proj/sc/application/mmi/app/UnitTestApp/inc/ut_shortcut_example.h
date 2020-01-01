/* ut_shortcut_example.h */
#ifndef __UT_SHORTCUT_EXAMPLE_H__
#define __UT_SHORTCUT_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetShortcut_Example(void);
s32   NumShortcut_Example(void);
void  ReleaseShortcut_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SHORTCUT_EXAMPLE_H__ */


