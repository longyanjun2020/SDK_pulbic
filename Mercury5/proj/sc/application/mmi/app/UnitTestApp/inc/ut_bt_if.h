/* ut_bt_if.h */
#ifndef __UT_BT_IF_H__
#define __UT_BT_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getBt_If_UT(void);
int   noBt_If_UT(void);
void  releaseBt_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_BT_IF_H__ */
