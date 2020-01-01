/* ut_touchshortcut_if.h */
#ifndef __UT_TOUCHSHORTCUT_IF_H__
#define __UT_TOUCHSHORTCUT_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTouchShortCut_If_UT(void);
int   noTouchShortCut_If_UT(void);
void  releaseTouchShortCut_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TOUCHSHORTCUT_IF_H__ */
