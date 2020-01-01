/* ut_btobex_if.h */
#ifndef __UT_BTOBEX_IF_H__
#define __UT_BTOBEX_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getBtObex_If_UT(void);
int   noBtObex_If_UT(void);
void  releaseBtObex_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_BTOBEX_IF_H__ */
