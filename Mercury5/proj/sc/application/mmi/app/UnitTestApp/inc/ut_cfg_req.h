/* ut_cfg_req.h */
#ifndef __UT_CFG_REQ_H__
#define __UT_CFG_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCfg_UT(void);
int   noCfg_UT(void);
void  releaseCfg_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CFG_REQ_H__ */
