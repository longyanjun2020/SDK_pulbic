/* ut_bt_req.h */
#ifndef __UT_BT_REQ_H__
#define __UT_BT_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getBT_UT(void);
int   noBT_UT(void);
void  releaseBT_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_BT_REQ_H__ */
